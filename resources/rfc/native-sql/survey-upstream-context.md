# Survey: upstream context, history, and what PHQL accepts today

Collected 2026-10-16 from github.com/phalcon/cphalcon, phalcon/phql and phalcon/phalcon, plus
runs of `prototype/tools/probe.php`.

## Where the code lives
- **cphalcon, C parser:** `ext/phalcon/mvc/model/query/`:
  - `scanner.re` (re2c), `parser.php.lemon` (Lemon), `base.c` (`phql_parse_phql`, AST cache);
  - on master these are 635 + 996 + 657 source lines; the generated `scanner.c` + `parser.c`
    add about 9k more.
  - The Zephir bridge is `Mvc/Model/Query/Lang::parsePHQL()`, wired through
    `optimizers/PhqlParsePhqlOptimizer.php`.
- **cphalcon, Zephir core:** `Mvc/Model/Query.zep` (4,672 lines on master; AST → IR → execution)
  and `Query/Builder.zep` (1,853 lines; it produces the PHQL).
- **phalcon/phql:** the PHQL parser ported to PHP. Created 2024-12, maintained by niden,
  last synced from cphalcon 2026-06-14. `src/Parser.php` + `src/Scanner/*`, with the Lemon
  grammar kept in `c/`.
- **phalcon/phalcon** (pure-PHP Phalcon): `src/Mvc/Model/Query.php` (5,001 lines) uses
  `Phalcon\Phql\Parser`. Its composer requires `phalcon/phql: 1.0.x-dev`, and it is synced from
  cphalcon regularly (last 2026-10-08).
- So PHQL is maintained in **three places**: the C grammar, the Zephir Query, and the PHP port
  of both.

## PHQL is actively worked on
- 56 PHQL-related commits on cphalcon master in 2026.
- New grammar on master:
  - `[#14954] support for new operators`, 2026-06-09: JSON `-> ->> #> #>>`, PG
    `@@ @> <@ &&`, `||` concat;
  - `[#16984] support for update/set`: `UPDATE … JOIN`;
  - `hardening lemon parsers` (2026-08-24), `hardening parsers for escape sequences`
    (2026-08-26), `[CP-17585] fixing the scanner to escape sequences` (2026-09-09).
- **This branch is based on 7.0.x (2026-04-27), which has none of those.** 7.0.x and master have
  diverged (master is 2,397 commits ahead of this branch).

## History of the request
- #2882 "PHQL - Union" (2014): closed.
- #12867 "[NFR] UNION ALL" (2017): closed. The answers were "use raw SQL" and "PHQL doesn't
  support UNION".
- #17141 "[NFR] Add PHQL support for common table expressions" (2026-06-12): closed
  2026-09-17 "in favor of #14608", the NFR vote list.
- **PR #17142 "Add PHQL common table expression support"** (2026-06-12, +5320 −2724, still open).
  niden replied on 2026-06-26:
  > "I investigated the use of WITH and CTEs and after a lot of pain and suffering I opted not
  > to implement them. There are fundamental issues here primarily with how the existing code is
  > structured. […] we are breaking backwards compatibility. […] The biggest problem is the lexer
  > which mixes union and recursive. […] this cannot be added - at least not without serious
  > refactoring which cannot happen in one minor version - this needs a major one. We can
  > certainly consider it for v7, the next cphalcon release but not today."

## What PHQL accepts (probe: parse → compile → same SQL natively through PDO on SQLite)
"7.0.x" is the built extension this branch targets. "master" is `phalcon/phql`, whose grammar
rules match upstream master rule for rule (parse only).

| construct | 7.0.x | master | raw SQL via PDO |
|---|---|---|---|
| `find("created_at > NOW()")`-style function call | ok | ok | ok |
| `IF()`/`IIF()` as a function | ok | ok | ok |
| simple `CASE x WHEN 1 …` | ok | ok | ok |
| **searched `CASE WHEN cond …`** | refused | refused | ok |
| `EXISTS (subquery)`, `IN (subquery)`, `COUNT(DISTINCT x)` | ok | ok | ok |
| **`UNION` / `UNION ALL`** (also inside `IN (…)`) | refused | refused | ok |
| **CTE `WITH x AS (…)`** | refused | refused | ok |
| **window functions `OVER (…)`** | refused | refused | ok |
| **derived table `FROM (SELECT …) t`** | refused | refused | ok |
| **`ORDER BY … NULLS LAST`** | refused | refused | ok |
| **`LIKE … ESCAPE`** | refused | refused | ok |
| `\|\|` concat | refused (scanner: "Unknown opcode 402") | ok | ok |
| JSON `->>` | refused | ok | ok |
| **`INSERT … SELECT`** | refused | refused | ok |
| **upsert `ON CONFLICT` / `ON DUPLICATE KEY UPDATE`** | refused | refused | ok |
| MySQL `DATE_SUB(NOW(), INTERVAL 7 DAY)` | refused | refused | (MySQL only) |
| MySQL `REGEXP` | refused | refused | (MySQL only) |
| MySQL `GROUP_CONCAT(x SEPARATOR ',')` | refused | refused | (MySQL only) |
| PostgreSQL `x::text` | **parses, then compiles to `"u"."id::text"`** (broken SQL) | parses | (PG only) |

`IF`/`ELSEIF`/`WHILE` as control flow are stored-procedure syntax. The database rejects them in
a plain statement as well, so they are out of scope for any query layer.

## Side findings while prototyping (not part of the NFR)
1. **7.0.x drops referenced `find()` params.**
   - `Users::find([0 => &$cond])` runs with no WHERE and returns every row; a referenced `bind`
     is sent unbound.
   - Cause: the 7.0.x Zephir kernel (`phalcon/zephir: dev-development`, locked) has no
     `ZVAL_DEREF` in `zephir_array_isset_*_fetch` (`ext/kernel/array.c:219-226` …).
   - Fixed on master by the ext refresh of 2026-09-08 (2e00fe0c69, Zephir ^1.5.0).
   - `foreach ($params as &$v)` and PHPUnit data providers both produce such arrays.
   - Documented in `prototype/tests/Findings/ReferenceParamsTest.php`. **7.0.x needs master's
     Zephir kernel.**
2. **`PdoResult::numRows()` on SQLite** fails on multi-line SQL and returns 0 rows for statements
   starting with `WITH` (see survey-execution.md). It matters for any raw-SQL API.
3. Builder quirks noticed on the way (survey-producers.md): `groupBy()` strips spaces, array
   `orderBy` drops `NULLS LAST`, `offset` without `limit` is ignored, empty `notInWhere` emits
   `expr != expr`.
