"""Cook the Volt NFR parser changes into patches, for any subset of features.

The prototype's parser changes are written as edits against the hand-written
Volt parser sources (ext/phalcon/mvc/view/engine/volt: scanner.h, scanner.re,
base.c, parser.php.lemon, parser.php.inc.h). Every edit anchors on upstream
text that the other features leave in place, so any subset of features can
be applied, in any order, to a clean upstream checkout.

    python3 -I tools/cook.py --series
        regenerate patches/NN-*.patch (all features, the prototype's build)

    python3 -I tools/cook.py null-safe embed --out /tmp/cooked
        one patch per chosen feature (cumulative, canonical order) plus
        combined.patch, against clean upstream; lemon-checked

    python3 -I tools/cook.py --check-all
        apply every one of the 127 subsets and run lemon on each

Features: nested-blocks, block-function, is-not, null-coalescing, null-safe,
embed (requires nested-blocks, added automatically), set-capture. The C side only: the compiler side of each feature is in
the PHP prototype (src/) and goes into Compiler.zep in the real PR.
"""
import itertools
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent.parent
REPO = HERE.parents[3]
REL = Path('ext/phalcon/mvc/view/engine/volt')
FILES = ['scanner.h', 'scanner.re', 'base.c', 'parser.php.lemon', 'parser.php.inc.h']

cur = None  # the tree being edited, set by apply()

def edit(name, old, new):
    path = cur / REL / name
    text = path.read_text()
    found = text.count(old)
    if found != 1:
        sys.exit(f"{name}: expected 1 match, found {found}:\n{old}")
    path.write_text(text.replace(old, new))


def before(name, anchor, insert):
    edit(name, anchor, insert + anchor)


def after(name, anchor, insert):
    edit(name, anchor, anchor + insert)


CASE_ANCHOR = "\t\t\tcase PHVOLT_T_MACRO:\n"
NAME_ANCHOR = '  { SL("BLOCK"),         PHVOLT_T_BLOCK },\n'
RULE_ANCHOR = "expr(R) ::= expr(O1) IS expr(O2) . {"
STATEMENT_ANCHOR = """statement(R) ::= block_statement(E) . {
	R = E;
}
"""
DEFINE_ANCHOR = "#define PHVOLT_T_ENDSWITCH 414\n"
ENDBLOCK_RULE = """		'endblock' {
			token->opcode = PHVOLT_T_ENDBLOCK;
			return 0;
		}
"""


def case(token, body):
    return f"\t\t\tcase PHVOLT_T_{token}:\n{body}\t\t\t\tbreak;\n\n"


def feed(token):
    return case(token, f"\t\t\t\tphvolt_(phvolt_parser, PHVOLT_{token}, NULL, parser_status);\n")


def nested_blocks():
    edit("base.c", """				if (state->block_level > 0) {
					phvolt_create_error_msg(parser_status, "Embedding blocks into other blocks is not supported");
					parser_status->status = PHVOLT_PARSING_FAILED;
					break;
				} else {
					state->block_level++;
				}
				phvolt_(phvolt_parser, PHVOLT_BLOCK, NULL, parser_status);
""", """				/*
				 * Blocks may nest, and may sit inside if/for/switch: the
				 * compiler resolves inheritance on the AST
				 */
				state->block_level++;
				phvolt_(phvolt_parser, PHVOLT_BLOCK, NULL, parser_status);
""")


def block_function():
    edit("scanner.re", """		'block' {
			s->statement_position++;
			token->opcode = PHVOLT_T_BLOCK;
			return 0;
		}
""", """		'block' {
			s->statement_position++;
			token->opcode = PHVOLT_T_BLOCK;
			token->value = estrndup(start, YYCURSOR - start);
			token->len = YYCURSOR - start;
			return 0;
		}
""")
    after("base.c", "\t\t\tcase PHVOLT_T_BLOCK:\n", """				/*
				 * "block" opens a {% block %} statement only right after the
				 * opening delimiter; anywhere else ({{ block("title") }},
				 * article.block) it is a plain identifier, like "default"
				 */
				if (prev_token != PHVOLT_T_OPEN_DELIMITER) {
					phvolt_parse_with_token(phvolt_parser, PHVOLT_T_IDENTIFIER, PHVOLT_IDENTIFIER, &token, parser_status);
					break;
				}

				efree(token.value);

""")


def is_not():
    after("scanner.h", DEFINE_ANCHOR, "\n/* \"is not\": a negated test, distinct from != */\n#define PHVOLT_T_ISNOT 422\n")
    for rule in ["'is not' {", "[i][s][ ]+[n][o][t] {"]:
        edit("scanner.re", f"""		{rule}
			s->statement_position++;
			token->opcode = PHVOLT_T_NOTEQUALS;""", f"""		{rule}
			s->statement_position++;
			token->opcode = PHVOLT_T_ISNOT;""")
    after("base.c", NAME_ANCHOR, '  { SL("IS NOT"),        PHVOLT_T_ISNOT },\n')
    before("base.c", CASE_ANCHOR, feed("ISNOT"))
    edit("parser.php.lemon",
         "%left IS EQUALS NOTEQUALS LESS GREATER GREATEREQUAL LESSEQUAL IDENTICAL NOTIDENTICAL .\n",
         "%left IS ISNOT EQUALS NOTEQUALS LESS GREATER GREATEREQUAL LESSEQUAL IDENTICAL NOTIDENTICAL .\n")
    rules = "/* is not <test>: a negated test, distinct from != */\n"
    for test, node in [("DEFINED", "NOT_ISSET"), ("EMPTY", "NOT_ISEMPTY"), ("EVEN", "NOT_ISEVEN"), ("ODD", "NOT_ISODD"),
                       ("NUMERIC", "NOT_ISNUMERIC"), ("SCALAR", "NOT_ISSCALAR"), ("ITERABLE", "NOT_ISITERABLE")]:
        rules += f"expr(R) ::= expr(O1) ISNOT {test} . {{\n\tphvolt_ret_expr(&R, PHVOLT_T_{node}, &O1, NULL, NULL, status->scanner_state);\n}}\n\n"
    rules += "expr(R) ::= expr(O1) ISNOT expr(O2) . {\n\tphvolt_ret_expr(&R, PHVOLT_T_ISNOT, &O1, &O2, NULL, status->scanner_state);\n}\n\n"
    before("parser.php.lemon", RULE_ANCHOR, rules)


def coalesce():
    after("scanner.h", DEFINE_ANCHOR, "\n/* a ?? b */\n#define PHVOLT_T_COALESCE 420\n")
    before("scanner.re", """		"?" {
			token->opcode = PHVOLT_T_QUESTION;""", """		"??" {
			token->opcode = PHVOLT_T_COALESCE;
			return 0;
		}

""")
    after("base.c", NAME_ANCHOR, '  { SL("??"),            PHVOLT_T_COALESCE },\n')
    before("base.c", CASE_ANCHOR, feed("COALESCE"))
    edit("parser.php.lemon", "%left QUESTION COLON .\n", "%left QUESTION COLON .\n%right COALESCE .\n")
    before("parser.php.lemon", RULE_ANCHOR, "/* a ?? b */\nexpr(R) ::= expr(O1) COALESCE expr(O2) . {\n\tphvolt_ret_expr(&R, PHVOLT_T_COALESCE, &O1, &O2, NULL, status->scanner_state);\n}\n\n")


def nullsafe():
    after("scanner.h", DEFINE_ANCHOR, "\n/* a?.b */\n#define PHVOLT_T_NULLSAFE 421\n")
    before("scanner.re", """		"?" {
			token->opcode = PHVOLT_T_QUESTION;""", """		"?." {
			token->opcode = PHVOLT_T_NULLSAFE;
			return 0;
		}

""")
    after("base.c", NAME_ANCHOR, '  { SL("?."),            PHVOLT_T_NULLSAFE },\n')
    before("base.c", CASE_ANCHOR, feed("NULLSAFE"))
    edit("parser.php.lemon", "%left DOT .\n", "%left DOT NULLSAFE .\n")
    before("parser.php.lemon", RULE_ANCHOR, "/* a?.b, a?.b() */\nexpr(R) ::= expr(O1) NULLSAFE expr(O2) . {\n\tphvolt_ret_expr(&R, PHVOLT_T_NULLSAFE, &O1, &O2, NULL, status->scanner_state);\n}\n\n")


def embed():
    after("scanner.h", DEFINE_ANCHOR, "\n/* {% embed %}...{% endembed %} */\n#define PHVOLT_T_EMBED 423\n#define PHVOLT_T_ENDEMBED 424\n")
    after("scanner.re", ENDBLOCK_RULE, """
		'embed' {
			s->statement_position++;
			token->opcode = PHVOLT_T_EMBED;
			return 0;
		}

		'endembed' {
			token->opcode = PHVOLT_T_ENDEMBED;
			return 0;
		}
""")
    after("base.c", NAME_ANCHOR, '  { SL("EMBED"),         PHVOLT_T_EMBED },\n  { SL("ENDEMBED"),      PHVOLT_T_ENDEMBED },\n')
    before("base.c", CASE_ANCHOR, case("EMBED", """				if (state->extends_mode == 1 && state->block_level == 0) {
					phvolt_create_error_msg(parser_status, "Child templates only may contain blocks");
					parser_status->status = PHVOLT_PARSING_FAILED;
					break;
				}

				state->block_level++;
				phvolt_(phvolt_parser, PHVOLT_EMBED, NULL, parser_status);
""") + case("ENDEMBED", """				state->block_level--;
				phvolt_(phvolt_parser, PHVOLT_ENDEMBED, NULL, parser_status);
"""))
    before("parser.php.inc.h", "/* {{{ phvolt_ret_do_statement */", """/* {{{ phvolt_ret_embed_statement */
static void phvolt_ret_embed_statement(zval *ret, zval *path, zval *params, zval *block_statements,
	phvolt_scanner_state *state)
{
	array_init(ret);

	add_assoc_long(ret, "type", PHVOLT_T_EMBED);

	add_assoc_zval(ret, "path", path);
	if (params) {
		add_assoc_zval(ret, "params", params);
	}

	if (block_statements) {
		add_assoc_zval(ret, "block_statements", block_statements);
	}

	Z_TRY_ADDREF_P(state->active_file);
	add_assoc_zval(ret, "file", state->active_file);
	add_assoc_long(ret, "line", state->active_line);
}
/* }}} */

""")
    after("parser.php.lemon", STATEMENT_ANCHOR, "\nstatement(R) ::= embed_statement(E) . {\n\tR = E;\n}\n")
    rules = '/* {% embed "card.volt" [with expr] %} {% block x %}...{% endblock %} {% endembed %} */\n'
    for params, body in [(False, True), (False, False), (True, True), (True, False)]:
        head = "OPEN_DELIMITER EMBED expr(E) " + ("WITH expr(P) " if params else "") + "CLOSE_DELIMITER "
        tail = ("statement_list(T) " if body else "") + "OPEN_DELIMITER ENDEMBED CLOSE_DELIMITER"
        args = "&E, " + ("&P" if params else "NULL") + ", " + ("&T" if body else "NULL")
        rules += f"embed_statement(R) ::= {head}{tail} . {{\n\tphvolt_ret_embed_statement(&R, {args}, status->scanner_state);\n}}\n\n"
    before("parser.php.lemon", "cache_statement(R) ::= OPEN_DELIMITER CACHE expr(E) CLOSE_DELIMITER statement_list(T)", rules)


def set_capture():
    after("scanner.h", DEFINE_ANCHOR, "\n/* {% set name %}...{% endset %} */\n#define PHVOLT_T_ENDSET 425\n#define PHVOLT_T_SET_CAPTURE 426\n")
    after("scanner.re", ENDBLOCK_RULE, """
		'endset' {
			token->opcode = PHVOLT_T_ENDSET;
			return 0;
		}
""")
    after("base.c", NAME_ANCHOR, '  { SL("ENDSET"),        PHVOLT_T_ENDSET },\n')
    before("base.c", CASE_ANCHOR, feed("ENDSET"))
    before("parser.php.inc.h", "/* {{{ phvolt_ret_do_statement */", """/* {{{ phvolt_ret_set_capture_statement */
static void phvolt_ret_set_capture_statement(zval *ret, phvolt_parser_token *name, zval *block_statements,
	phvolt_scanner_state *state)
{
	array_init(ret);

	add_assoc_long(ret, "type", PHVOLT_T_SET_CAPTURE);

	phvolt_add_assoc_stringl(ret, "name", name->token, name->token_len, 0);
	efree(name->token);
	efree(name);

	if (block_statements) {
		add_assoc_zval(ret, "block_statements", block_statements);
	}

	Z_TRY_ADDREF_P(state->active_file);
	add_assoc_zval(ret, "file", state->active_file);
	add_assoc_long(ret, "line", state->active_line);
}
/* }}} */

""")
    after("parser.php.lemon", STATEMENT_ANCHOR, "\nstatement(R) ::= set_capture_statement(E) . {\n\tR = E;\n}\n")
    before("parser.php.lemon", "cache_statement(R) ::= OPEN_DELIMITER CACHE expr(E) CLOSE_DELIMITER statement_list(T)", """/* {% set name %}...{% endset %} */
set_capture_statement(R) ::= OPEN_DELIMITER SET IDENTIFIER(I) CLOSE_DELIMITER statement_list(T) OPEN_DELIMITER ENDSET CLOSE_DELIMITER . {
	phvolt_ret_set_capture_statement(&R, I, &T, status->scanner_state);
}

set_capture_statement(R) ::= OPEN_DELIMITER SET IDENTIFIER(I) CLOSE_DELIMITER OPEN_DELIMITER ENDSET CLOSE_DELIMITER . {
	phvolt_ret_set_capture_statement(&R, I, NULL, status->scanner_state);
}

""")


STEPS = {
    'nested-blocks':   ('01', nested_blocks),
    'block-function':  ('02', block_function),
    'is-not':          ('03', is_not),
    'null-coalescing': ('04', coalesce),
    'null-safe':       ('05', nullsafe),
    'embed':           ('06', embed),
    'set-capture':     ('07', set_capture),
}


# A block inside an embed body is a nested block, so embed needs nested-blocks
# (on the compiler side both need the AST inheritance resolver).
REQUIRES = {
    'embed': ['nested-blocks'],
}


def with_requirements(features):
    chosen = list(dict.fromkeys(features))
    for name in list(chosen):
        for required in REQUIRES.get(name, []):
            if required not in chosen:
                print(f"{name} requires {required}: added")
                chosen.append(required)
    return chosen


def pristine(work):
    tree = work / 'tree'
    if tree.exists():
        shutil.rmtree(tree)
    (tree / REL).mkdir(parents=True)
    for f in FILES:
        shutil.copy(REPO / REL / f, tree / REL / f)
    return tree


def lemon_binary(work):
    binary = work / 'lemon'
    if not binary.exists():
        subprocess.run(['gcc', '-std=gnu99', '-w', str(REPO / '3rdparty/lemon/lemon.c'), '-o', str(binary)], check=True)
    return binary


def lemon_check(work, tree):
    """'N states, 0 conflicts' or the error."""
    d = work / 'lemon-run'
    if d.exists():
        shutil.rmtree(d)
    d.mkdir()
    shutil.copy(tree / REL / 'parser.php.lemon', d)
    shutil.copy(REPO / '3rdparty/lemon/lempar.c', d)
    res = subprocess.run([str(lemon_binary(work)), '-s', 'parser.php.lemon'], cwd=d, capture_output=True, text=True)
    lines = [l.strip() for l in (res.stdout + res.stderr).splitlines() if 'conflicts' in l]
    return lines[-1] if lines else (res.stdout + res.stderr).strip()


def diff(work, before, after_tree):
    for name, src in (('a', before), ('b', after_tree)):
        if (work / name).exists():
            shutil.rmtree(work / name)
        shutil.copytree(src, work / name)
    return subprocess.run(['diff', '-ru', 'a', 'b'], cwd=work, capture_output=True, text=True).stdout


def cook(features, out, work):
    """One cumulative patch per feature (canonical order) + combined.patch."""
    global cur
    order = sorted(features, key=lambda f: STEPS[f][0])
    cur = pristine(work)
    start = work / 'start'
    if start.exists():
        shutil.rmtree(start)
    shutil.copytree(cur, start)
    out.mkdir(parents=True, exist_ok=True)
    for old in out.glob('*.patch'):
        old.unlink()
    for name in order:
        prev = work / 'prev'
        if prev.exists():
            shutil.rmtree(prev)
        shutil.copytree(cur, prev)
        STEPS[name][1]()
        patch = diff(work, prev, cur)
        (out / f"{STEPS[name][0]}-{name}.patch").write_text(patch)
        changed = sum(1 for l in patch.splitlines() if l[:1] in '+-' and l[:3] not in ('+++', '---'))
        print(f"{STEPS[name][0]}-{name:18s} {changed:4d} changed lines   {lemon_check(work, cur)}")
    return order


def main(argv):
    work = Path(tempfile.mkdtemp())
    try:
        if argv[:1] == ['--series']:
            cook(list(STEPS), HERE / 'patches', work)
        elif argv[:1] == ['--check-all']:
            global cur
            names, bad = list(STEPS), 0
            for size in range(1, len(names) + 1):
                for subset in itertools.combinations(names, size):
                    for order in (subset, tuple(reversed(subset))):
                        cur = pristine(work)
                        for name in order:
                            STEPS[name][1]()
                        result = lemon_check(work, cur)
                        if ' 0 conflicts' not in result:
                            bad += 1
                            print('FAIL', ' + '.join(order), result)
            print(f"checked {2 ** len(names) - 1} subsets in both orders: {'all 0 conflicts' if not bad else f'{bad} failed'}")
            return 1 if bad else 0
        else:
            if '--out' not in argv:
                sys.exit(__doc__)
            out = Path(argv[argv.index('--out') + 1])
            features = [a for a in argv if a in STEPS]
            unknown = [a for i, a in enumerate(argv) if a not in STEPS and a != '--out' and argv[i - 1] != '--out']
            if unknown or not features:
                sys.exit(f"unknown feature(s): {unknown}; known: {', '.join(STEPS)}")
            cook(with_requirements(features), out, work)
            (out / 'combined.patch').write_text(diff(work, work / 'start', cur))
            print(f"wrote {out}/")
        return 0
    finally:
        shutil.rmtree(work)


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
