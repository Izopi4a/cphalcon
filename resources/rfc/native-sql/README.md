# Phalcon v7 ORM native SQL NFR: working notes (branch nfr-orm-native-sql)

Handoff file. If you are a new session or model picking this up, read this first, then
`walkthrough.md` (how `find()` becomes SQL today and on the proposed path), then
`native-sql-rfc.md`.

## Goal
Let SQL that the database supports reach it, while keeping `Users::find()`,
`Users::find("created_at > NOW()")`, Criteria and the Builder unchanged. Get there by compiling
the `find()` family (and later the Builder) straight into the `Phalcon\Db\Dialect::select()`
definition, with no PHQL string, C parser, AST or IR. Add a first-class native SQL API. Make PHQL
an optional front end. The aim is less code to maintain in three places (C grammar, Zephir Query,
PHP port), not a new ORM.

## Decisions already made (2026-10-16)
- Target: upstream `7.0.x` (v7). The branch is cut from `upstream/7.0.x` @ fb9e42f866
  (2026-04-27), the same base as the Forms branch T17106. niden said on PR #17142 that CTE/UNION
  support "needs a major one … consider it for v7". That comment is the opening for this NFR.
- Process, the same as the Forms NFR: research surveys → RFC in niden's NFR shape (Problem / Why /
  Proposed approach / Milestones / BC / Open questions) → PHP prototype as proof → user review →
  post. Code in Zephir only after a maintainer yes.
- Prototype in plain PHP over the built 7.0.x extension, in `prototype/`. Design validation only;
  delete it before any upstream PR. Everything real must be Zephir in `phalcon/`; never hand-edit
  `ext/*.zep.c`, never commit `ext/`.
- Commit trailer, as on the Forms branch: `Assisted-by: Claude Code`.
- **Repo hygiene in this checkout** (`~/projects/github.com/izopi4a/cphalcon`): `origin` = the
  user's fork Izopi4a/cphalcon, `upstream` = phalcon/cphalcon (added 2026-10-16; local `master`
  tracks `upstream/master`). The other clone, `~/projects/github.com/phalcon/cphalcon`, uses the
  opposite naming (`origin` = upstream, `fork` = Izopi4a). **Push only to the fork, and only when
  the user asks.**

## Toolchain
- This checkout has no Zephir build. `prototype/run.sh` uses `ext/modules/phalcon.so` if present,
  else the 7.0.x build in the sibling clone
  (`~/projects/github.com/phalcon/cphalcon/ext/modules/phalcon.so`, built 2026-10-15 from
  T17106 = 7.0.x + RFC files only). Override with `PHALCON_SO=…`.
- PHPUnit: `composer install` was run here (vendor/ is gitignored).
- Commands:
  - `cd resources/rfc/native-sql/prototype`
  - `./run.sh test`: 65 tests, SQLite in-memory;
  - `./run.sh tools/trace.php [n] [--full]`: every pipeline stage for 6 queries, plus the native
    path;
  - `./run.sh tools/probe.php [--markdown]`: which SQL PHQL refuses vs what PDO accepts.
- The system PHP 8.5.4 has no `pdo_mysql` / `pdo_pgsql`, so MySQL/PostgreSQL runs need those
  extensions plus a database container.

## Files
| file | what |
|---|---|
| `walkthrough.md` | reading guide: today's 6 hops with real data at each one, the Dialect definition format, the same query compiled natively, what is given up, a reading order |
| `native-sql-rfc.md` | the NFR draft |
| `survey-query-core.md` | parser → AST → IR → Dialect internals (`Query.zep`, `Dialect.zep`) |
| `survey-producers.md` | everything that produces/consumes PHQL (find family, Builder, Criteria, relations, validators, paginator) |
| `survey-execution.md` | hydration, resultsets, the SQLite row count, PHQL DML semantics, binds, events, `orm.*` |
| `survey-upstream-context.md` | issue history, niden's #17142 comment, the PHP port, 7.0.x vs master grammar, the probe table, side findings |
| `prototype/src/Compiler/FindCompiler.php` | find() params → Dialect definition |
| `prototype/src/Compiler/FragmentRewriter.php` | the only "parsing": placeholders, `[Model]`, columnMap |
| `prototype/src/NativeSql.php`, `NativeFinder.php` | `find`/`findFirst`/`findBySql`/`rows` entry points; the trait the fixtures use |
| `prototype/src/Db/CountedResult.php` | row count that survives `WITH` and multi-line SQL on SQLite |
| `prototype/tests/` | FindParity (vs `Model::find`), Passthrough (PHQL refuses, native passes), FindBySql, FragmentRewriter, Findings/ReferenceParams |

## Status
- [x] branch created from upstream/7.0.x, local master synced to upstream/master
- [x] surveys: query core, producers, execution, upstream context (3 reading agents + own checks)
- [x] trace tool + probe tool against the built extension
- [x] PHP prototype M0: find()/findFirst() compiled to the Dialect, findBySql, rows. 65 tests
      green (2026-10-16).
- [x] walkthrough.md written for the user's code reading
- [x] native-sql-rfc.md drafted (awaiting user review)
- [ ] user review of walkthrough + RFC
- [ ] MySQL + PostgreSQL runs of the prototype (needs pdo_mysql/pdo_pgsql)
- [ ] decide where to post: a new NFR issue referencing #17142 / #14608, or a comment on #17142
- [ ] side findings: report the 7.0.x reference bug (7.0.x needs master's Zephir kernel) and the
      SQLite `numRows()` bug as normal issues

## Side findings (details in survey-upstream-context.md)
1. 7.0.x `find()` silently drops `conditions`/`bind` passed as PHP references. A WHERE dropped
   means every row is returned. It is a Zephir kernel `ZVAL_DEREF` gap, fixed on master in
   2e00fe0c69. Test: `prototype/tests/Findings/ReferenceParamsTest.php` (asserts the current
   behaviour; invert it once 7.0.x is fixed). PHPUnit data providers trigger it, which is why the
   parity tests call `FindParityTest::detach()`.
2. `PdoResult::numRows()` on SQLite: a statement starting with `WITH` is counted as 0 rows, and
   multi-line SQL breaks the COUNT query.
3. Builder quirks: `groupBy()` strips spaces, array `orderBy` drops `NULLS LAST`, `offset`
   without `limit` is ignored, empty `notInWhere` emits `expr != expr`.

## Next step ideas, if the maintainers like the direction
- Builder prototype (M3 shape): implicit joins from `Manager::getRelationsBetween()`, multi-model
  columns → Complex column types, without PHQL.
- Run the existing `tests/database/Mvc/Model/*` suites through the prototype compiler, as the
  real parity check.
