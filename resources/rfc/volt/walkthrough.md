# Volt NFR walkthrough: how a template becomes PHP, today and proposed

Reading guide for `volt-rfc.md`. Section 1 follows a child template through today's pipeline, with
the real data at each step. Section 2 shows where user functions plug in. Sections 3 and 4 show the
proposed path for the same template. Section 5 lists what the proposal costs. Section 6 is a reading
order for the code.

All data below comes from `prototype/tools/trace.php` and `prototype/tools/examples.php`, run on an
extension built from upstream master (5.23.0, `33f1076a88`). `C:` is
`phalcon/Mvc/View/Engine/Volt/Compiler.zep`, `B:` is `ext/phalcon/mvc/view/engine/volt/base.c`.

## 1. Today: from `.volt` to a cached `.php`

```
page.volt ──► scanner.re ──► base.c token loop ──► parser.php.lemon ──► AST ──► Compiler.zep ──► cache/…page.volt.php
             (re2c tokens)   (context rules)        (Lemon grammar)    (arrays)  (one method      required inside
                                                                                  per node type)  Volt::render()
```

The two templates used throughout:

```twig
{# layout.volt #}
<h1>{% block title %}Shop{% endblock %}</h1>{% block content %}{% endblock %}

{# page.volt #}
{% extends "layout.volt" %}{% block title %}Orders{% endblock %}{% block content %}{{ count }} open{% endblock %}
```

**Scanner and token loop.** `scanner.re` produces tokens. `base.c` feeds them to the Lemon parser
one by one and enforces the rules that the grammar does not express: `extends` must come first, a
child template may only contain blocks, and a block may not open while `block_level > 0`
(`B:654-663`). `block_level` is also incremented by `if`, `for` and `switch`
(`B:487`, `B:528`, `B:555`), which is why a block inside an `if` fails with the nesting message too.

**Parser.** The grammar builds plain PHP arrays. `Compiler::parse()` returns them:

```json
[
  {"type": 310, "path": {"type": 260, "value": "layout.volt"}},
  {"type": 307, "name": "title",   "block_statements": [{"type": 357, "value": "Orders"}]},
  {"type": 307, "name": "content", "block_statements": [{"type": 359, "expr": {"type": 265, "value": "count"}},
                                                        {"type": 357, "value": " open"}]}
]
```

(310 extends, 307 block, 357 raw text, 359 echo, 265 identifier, 260 string; `file`/`line` keys removed.)

**Compiler: inheritance is spliced from compiled pieces.** `statementList()` (`C:2718`) walks the
child. At `extends` it compiles the parent in "extends mode" (`C:2880-2916`), which writes a second
cache file holding the parent as a serialized map. Integer keys are raw text, already compiled;
string keys are block names, holding the parent's block AST:

```
cache/…layout.volt%%e%%.php
a:4:{i:0;s:4:"<h1>";s:5:"title";a:1:{i:0;a:4:{s:4:"type";i:357;s:5:"value";s:4:"Shop";…}}i:1;s:5:"</h1>";s:7:"content";N;}
```

`compileSource()` (`C:2403-2450`) then walks that map. A key the child defines is replaced by the
child's block, compiled; any other key is compiled from the parent's AST or copied as text. The
result is one file per rendered template:

```
cache/…page.volt.php
<h1>Orders</h1><?= $count ?> open
```

This model has one flat level of names and one `currentBlock`. That is the root of four
limitations:

| limitation | where |
|---|---|
| a block cannot contain a block, and cannot sit in `if`/`for` | refused in `B:655` before the compiler sees it; the name map has no nesting |
| `extends` takes a string literal only | `C:2884-2888` reads `path["value"]`; `{% extends layout %}` looks for a file named `layout` |
| a block cannot be printed twice (`block("title")`) | `block` is a keyword token everywhere (scanner) |
| editing the parent does not recompile the child | the parent is inlined, but `compare_mtime()` (`C:475`) only checks the child's own file |

The same applies to static includes, which are compiled and inlined (`C:1023-1055`).

## 2. Today: where a user function plugs in

`functionCall()` (`C:1829`) resolves a name in this order:

1. extension objects, `compileFunction(name, compiledArgs, argsAst)`; the first string returned wins (`C:1791-1820`);
2. `addFunction()` definitions (`C:1883-1903`):
   - a string is pasted as a function name: `name(args)`;
   - a Closure is **called now, at compile time**, as `fn(string $resolvedArgs, ?array $exprArgs)`,
     and its return value is pasted into the compiled file as PHP source;
   - anything else, an array callable or an invokable object, throws `InvalidUserFunctionDefinition`;
3. built-ins (`content`, `partial`, `url`, tag helpers…);
4. otherwise `$this->callMacro('name', [...])`, which fails at run time if no macro has that name.

So a Volt function is a code generator. From `examples.md` E5:

```text
$compiler->addFunction('year', fn () => date('Y'));
compile {{ year() }}          → <?= 2026 ?>          (the value is frozen in the cache)
$compiler->addFunction('greeting', fn ($args) => 'Hello ' . $args);
compile {{ greeting(name) }}  → <?= Hello $name ?>   (not PHP; fails when the file is required)
```

Filters follow the same contract, with the filtered value prepended to `$resolvedArgs`
(`C:2585-2602`). There is no test API: an unknown test name compiles to `==` (`C:2264-2267`).
Autoescape wraps every echo in `$this->escaper->html()` (`C:675-677`); there is no way to mark a
function's output as HTML, and escaping filters get wrapped again.

## 3. Proposed: inheritance resolved on the AST

`prototype/src/Inheritance/Resolver.php` runs before compiling, in `compileSource()`:

1. load the chain leaf → … → root as ASTs, following `extends`;
2. collect every level's blocks by name, **at any depth** (inside blocks, `if`, `for`, `switch`);
3. expand the root's statements. A block node becomes the statements of its most derived
   definition, expanded recursively. `{{ super() }}` becomes the next definition up the chain.
   `{{ block("name") }}` becomes the most derived definition again.

The result is a flat statement list with no extends or block nodes. For `page.volt` it is:

```json
[
  {"type": 357, "value": "<h1>"}, {"type": 357, "value": "Orders"}, {"type": 357, "value": "</h1>"},
  {"type": 359, "expr": {"type": 265, "value": "count"}}, {"type": 357, "value": " open"}
]
```

The stock, unchanged `statementList()` compiles it to the same file as today:

```
cache/…page.volt.php
<h1>Orders</h1><?= $count ?> open
```

and no `%%e%%` file is written. A sidecar records what was inlined:

```php
// cache/…page.volt.php.deps.php
<?php return array (
  'files' => array ('/views/layout.volt' => 1792155166),
  'signature' => 'volt-nfr-1|da39a3ee…|autoescape=false|strictTests=true',
);
```

With `stat` on, the compiled file is rebuilt when any listed file or the compiler signature changes
(runtime registry, autoescape). With `stat` off, nothing is checked, as today.

**Parity.** All 50 templates of the upstream fixtures (`tests/support/assets/views`, including the
three-level `extends/nested/*` and the themes) compile byte-identical with the stock compiler and
with the prototype (`tests/Prototype/ParityTest.php`, `tools/parity.php`). The output model does not
change: one PHP file per rendered template, with no block dispatch at run time.

**What the same resolver enables.** These need no new compiler code beyond the expansion step:

| feature | how |
|---|---|
| nested blocks, blocks in `if`/`for` | collection at any depth; `base.c` stops refusing them (patch) |
| `{{ block("title") }}` | expands the most derived `title` again; `block` stays a keyword only right after `{%` (patch, like `default` already is) |
| `{% embed "card.volt" with [...] %}{% block body %}…{% endblock %}{% endembed %}` | the embed body is an anonymous child of `card.volt`, resolved on its own and inlined inside a scope closure |
| `{% extends layoutVar %}` (#17271) | compiles to `$this->renderDynamicExtends(expr, child, vars)`, which compiles the child once per parent (`variant%%<hash>.php`) |
| editing a parent, include or embed recompiles the child | the resolver and `compileInclude()` record every inlined file |

**The parser patches** (`prototype/patches/01-…07-*.patch`, one per feature, 237 changed lines over five hand-written files;
`scanner.c`, `parser.php.c` and `parser.c` are regenerated by `build.sh`, as `bin/genparsers.sh`
does):

| change | files |
|---|---|
| allow `block` at any depth; relabel `block` as an identifier unless it follows `{%` | `base.c`, `scanner.re` |
| `??` (right-associative, below comparison) and `?.` (with `.`) | `scanner.re`, `scanner.h`, `parser.php.lemon`, `base.c` |
| `is not` as its own token: `a is not premium` is a negated test, distinct from `a != premium` | same |
| `{% embed %}…{% endembed %}`, `{% set x %}…{% endset %}` | same, plus two AST builders in `parser.php.inc.h` |

Lemon reports 0 conflicts. The upstream Volt unit suite passes on the patched parser except two
cases that pin `{% if a is not b %}` compiling to `$a != $b` (633/635, the intended change; see the
RFC's BC section).

## 4. Proposed: functions, filters and tests that run at render time

```php
$volt->addFunction(new VoltFunction('money', [Money::class, 'format']));       // static: a direct call
$volt->addFunction(new VoltFunction('price', ['prices', 'format']));           // DI service, resolved on first call
$volt->addFunction(new VoltFunction('stars', $closure, ['safe' => true]));     // HTML, not escaped
$volt->addFilter(new VoltFilter('money', Money::format(...)));
$volt->addTest(new VoltTest('premium', fn (User $u) => $u->isPremium()));
$volt->addExtension(new ShopExtension());                                      // getFunctions/getFilters/getTests
```

What they compile to (`tools/trace.php`, `examples.md` E5/E6):

```php
{{ ucwords(name) }}            <?= \ucwords($name) ?>
{{ money(total, "EUR") }}      <?= ($this->runtime['function:money'] ??= $this->getRuntimeFunction('money'))($total, 'EUR') ?>
{{ money("currency": "USD", "amount": total) }}
                               <?= \App\Money::format(currency: 'USD', amount: $total) ?>
{% if u is not premium %}      <?php if (!(($this->runtime['test:premium'] ??= $this->getRuntimeTest('premium'))($u))) { ?>
```

- A function name or a static method is compiled to a direct call, exactly like today's string form.
- Anything else is looked up in the engine's registry once per render and called. `[name, method]`
  with a non-static method gets its instance from the container, so compiling never touches the
  container.
- `'name': value` arguments become PHP named arguments.
- `safe` results, `|raw`, and escaping filters are not wrapped by autoescape again
  (`Compiler::compileEcho()`, prototype).
- `is <test>` with an unknown name is a compile error. `is null`/`is none` are built in.
  `strictTests => false` keeps today's `==` fallback.

The compile-time API stays as it is, for real code generators. The names become explicit in the
RFC: "compile-time functions" and "runtime functions".

## 5. What it costs

| cost | size |
|---|---|
| runtime function call | `./run.sh bench`, 200k calls, clean PHP with JIT: a static callable is the same direct call as today (~85 ns per iteration including the loop); a closure or service function ~265 ns; the same service call written with today's API (`$this->getDI()->getShared(...)->fmt()`) ~390 ns |
| compile time | the resolver parses each parent once per compile; today the parent is compiled once per compile too |
| dynamic extends | one compiled file per (child, parent) pair actually rendered |
| embed, include-with | a closure call per use, for the separate scope |
| `stat` on | one extra `stat()` per inlined file per render, plus an opcache-served sidecar include |

BC is listed in the RFC: `a is not b` stops meaning `a != b`; unknown tests become errors;
`embed`, `endembed` and `endset` become reserved words; duplicate block names in one template and
`super()` without a parent definition become errors; `include … with` sees the includer's
variables.

## 6. Reading order

1. `examples.md`: ten cases, today vs proposed, with real output.
2. `prototype/src/Inheritance/Resolver.php`: the expansion, 315 lines with comments.
3. `prototype/src/Compiler.php`: the `compileSource()`, `compile()`/`compileFile()` (dependencies),
   `compileEcho()` and `compileInclude()` overrides.
4. `prototype/src/NodeCompiler.php` and `prototype/src/Runtime/*`: runtime functions, filters, tests
   and the new nodes.
5. `prototype/patches/`: the series, starting with the 12-line `01-nested-blocks.patch`.
6. `prototype/tests/Today/*` next to `prototype/tests/Prototype/*`: the same templates, failing and working.
7. `survey-volt-current.md` §2 for the full inheritance internals; `survey-twig-gap.md` for the gap
   list; `survey-issues.md` for the issue history.
