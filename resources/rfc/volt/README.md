# Phalcon v7 Volt NFR: working notes (branch nfr-volt)

Handoff file. If you are a new session or model picking this up, read this first, then
`walkthrough.md` (how a template becomes PHP today and on the proposed path), then
`volt-rfc.md`.

## Goal
Make Volt's template inheritance complete (nested blocks, blocks in `if`/`for`, `block()`,
`embed`, `extends` from a variable). Make declaring a function/filter/test mean "register a
callable" instead of "write a PHP code generator", and document today's API properly. Make the
cache aware of what was inlined into a template. Do it with small grammar changes, because Volt
exists three times: the C parser, the Zephir compiler and the PHP port `phalcon/volt`.

## Decisions already made (2026-10-16)
- Third NFR, after Forms (#17106, branch T17106-forms-overhaul) and native SQL (branch
  nfr-orm-native-sql). The process is the same: research surveys → RFC in niden's NFR shape →
  PHP prototype as proof → user review → post. Code in Zephir/C only after a maintainer yes.
- **Base: upstream `master` (5.23.0, `33f1076a88`), not `7.0.x`.** Volt changed a lot on master
  after 7.0.x forked in April 2026 (verbatim #17085, multi-path #17269, nested inherits #17294,
  CP-17668). 7.0.x has nothing for Volt that master lacks. The RFC still targets v7, with M0 for 5.x.
- niden has no Volt NFR of his own. The related issues are #17053 (TagTranslator), #17271 (extends
  from a variable), #17668 (perf, done) and #17564/#17566 (small 7.0 bugs). #17145 (nested blocks)
  is assigned to him with the 7.0 label.
- A caching issue with `stat => false` and inheritance came up during research. The user reported
  it to niden privately (Discord, 2026-10-16). **Keep its details out of this repository** until
  the user says otherwise.
- Commit trailer, as on the other NFR branches: `Assisted-by: Claude Code`.
- **Repo hygiene in this checkout** (`~/projects/github.com/izopi4a/cphalcon`): `origin` = the user's
  fork, `upstream` = phalcon/cphalcon. This branch has no upstream tracking. **Push only to the
  fork, and only when the user asks.** `vendor/` was reinstalled from master's composer.lock
  (adds phalcon/talon; PHPUnit 10.5.66).

## Toolchain
- No Zephir here. The prototype is PHP over a built extension; parser changes are a `.patch`
  applied to a copy of `ext/` at build time. The branch itself never modifies `ext/` or `phalcon/`.
- `cd resources/rfc/volt/prototype`
  - `./build.sh stock` and `./build.sh patched`: build HEAD's `ext/` into `.build/<flavor>/`
    (gitignored), about 3 minutes each. They need phpize, gcc and re2c (4.4 here). lemon is built from
    `3rdparty/lemon` with `-std=gnu99`, because current gcc refuses it otherwise.
  - `./run.sh test`: `tests/Today` (38) on stock, `tests/Prototype` (122) on patched.
  - `./run.sh tools/examples.php [--write]`: checks or regenerates `../examples.md`.
  - `./run.sh tools/parity.php [--diff]`: upstream fixtures, stock vs prototype compiler.
  - `./run.sh tools/trace.php`: pipeline stages, used in `walkthrough.md`.
  - `./run.sh bench [calls]`: per-call cost of runtime functions, on a clean PHP with JIT.
- The upstream Volt suite against the patched parser:
  `php -d extension=resources/rfc/volt/prototype/.build/patched/ext/modules/phalcon.so vendor/bin/phpunit -c resources/phpunit.xml.dist tests/unit/Mvc/View`
  gives 718/720; the 2 failures pin `a is not b` == `a != b`, which is the intended change.
- **Zephir (for the real PRs):** `vendor/bin/zephir` (phalcon/zephir 1.6.1, a composer dev dependency).
  It has a built-in pure-PHP parser, so the `zephir_parser` extension is optional (a speed-up only).
  Upstream CI runs `vendor/bin/zephir fullclean && vendor/bin/zephir generate`, then phpize/make.
  `generate` takes about 21 s. **On PHP 8.5 it rewrites two unrelated files**
  (`ext/phalcon/db/enum.zep.c`, `ext/phalcon/datamapper/pdo/connection/abstractconnection.zep.c`)
  because PDO's fetch flags were renumbered in 8.5 (bug draft `issues/20-…`). Keep those out of
  Volt PRs.
- `git archive` skips `phalcon/`, `resources/` and `tests/` (`export-ignore` in `.gitattributes`);
  copy sources with `git ls-files -z … | xargs -0 cp --parents`.
- `prototype/tools/cook.py`: patches for any subset of the parser features, plus `--check-all`.
  `prototype/tools/check-features.sh`: builds each feature alone (incrementally, from a copy of the
  stock build) and runs the upstream Volt suite.
- Probe gotcha: Volt's `stat` recompiles when the source and the compiled file have the same mtime
  second. Back-date sources (the test base does `touch(-3600)`), or staleness probes lie.
- Phalcon binds engine factories and service closures to the container: they must not be `static`.
- Zephir gap: `array_walk_recursive()` by reference leaves IS_REFERENCE elements, which the stock
  `expression()` does not dereference. The prototype rebuilds AST arrays by copy.

## Files
| file | what |
|---|---|
| `volt-rfc.md` | the NFR draft |
| `walkthrough.md` | reading guide: today's pipeline with real data, the AST resolver, runtime functions, costs, reading order |
| `examples.md` | ten cases, today vs proposed, generated by `prototype/tools/examples.php` |
| `docs-extending-volt.md` | replacement "Extending Volt" docs for today's 5.x API, every snippet tested (`tests/Today/DocsDraftTest.php`) |
| `survey-issues.md` | 565 issues/PRs + docs, Discussions, phalcon/volt: themes by demand, open items, maintainer quotes |
| `survey-volt-current.md` | implementation: pipeline, inheritance internals, syntax inventory, extension contract, escaping, 7.0.x vs master |
| `survey-twig-gap.md` | feature gap vs Twig 3.x, declaring a function side by side, docs review |
| `prototype/patches/NN-*.patch` | the C changes as a series, one patch per feature, applied in order: 01 nested blocks (12 lines), 02 `block()`/`article.block`, 03 `is not` token, 04 `??`, 05 `?.`, 06 `embed`, 07 set capture; 0 Lemon conflicts after each |
| `issues/` | ticket drafts, split per feature as niden asked; `issues/README.md` is the plan |
| `prototype/src/Inheritance/Resolver.php` | inheritance resolved on the AST |
| `prototype/src/Compiler.php` | compileSource/compile/compileFile/compileEcho/compileInclude overrides |
| `prototype/src/NodeCompiler.php` | extension hooks for runtime calls and the new nodes |
| `prototype/src/Runtime/*`, `src/Volt.php` | VoltFunction/VoltFilter/VoltTest, registry, engine API |
| `prototype/src/Cache/Dependencies.php` | the `.deps.php` sidecar |

## Status
- [x] branch from upstream/master, surveys (3 agents + own probes on 5.23.0 and 7.0.x builds)
- [x] parser patch, 0 Lemon conflicts; stock + patched builds
- [x] prototype: resolver, runtime registry, escaping, dependency cache, embed, dynamic extends
- [x] tests: Today 38 (stock), Prototype 122 (patched), including 50/50 fixture parity
- [x] examples.md, walkthrough.md, docs draft, bench, RFC draft
- [ ] user review of walkthrough + RFC + docs draft
- [ ] decide where to post: a new NFR referencing #17145/#17271, or a comment on #17145
- [ ] M0 bug issues (compiler drift): `//` parsed as modulo, `{% call %}` drops its body, `{% cache %}`
      parses then fails, `|e` escaped twice under autoescape, `is not` with function tests
- [ ] docs PR to phalcon/documentation with `docs-extending-volt.md` (independent of the NFR)
- [x] split per niden: `issues/` (plan + wave 1 drafts), independent per-feature patches (`cook.py`)
- [ ] PRs for the tickets once they are open: C from `cook.py`, Zephir in `Compiler.zep`, tests in
      `tests/unit/Mvc/View/Engine/Volt`, the same change in phalcon/volt

## Side findings
1. Compiler/grammar drift, listed above (M0). All reproduced in `tests/Today`.
2. `{% for x in y if cond %}` increments `block_level` on the `if` and never decrements it (#1636,
   #13155). The patch no longer checks `block_level` for blocks, but the counter imbalance still
   affects "Child templates only may contain blocks". Not verified further.
3. The `stat => false` caching issue (private, see above).
