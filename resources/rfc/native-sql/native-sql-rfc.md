# [NFR] v7 ORM: compile `find()` and the Builder straight to the Dialect, add first-class native SQL, make PHQL optional

Status: DRAFT for discussion. Target: `7.0.x` (v7).
Related: #17142 / #17141 (CTE support, deferred to v7), #12867 and #2882 (UNION), #14608 (NFR vote
list), #14954 (new PHQL operators), #16984 (UPDATE … JOIN).
Evidence: a working PHP prototype on 7.0.x with 65 tests (`prototype/`, SQLite so far; MySQL
and PostgreSQL runs are pending), a probe of what PHQL accepts (`survey-upstream-context.md`),
a stage-by-stage trace of today's pipeline (`walkthrough.md`), and before/after usage examples
with captured output (`examples.md`).

## Problem

**PHQL stands between the application and SQL the database already supports.** Run against the
7.0.x extension, PHQL refuses 12 constructs that SQLite runs fine as raw SQL through the same Pdo
adapter:
- searched `CASE WHEN`, `UNION [ALL]`, CTEs, window functions, derived tables;
- `NULLS LAST`, `LIKE … ESCAPE`, `||`, JSON `->>`;
- `INSERT … SELECT`, upserts.

It also refuses MySQL's `INTERVAL`, `REGEXP` and `GROUP_CONCAT(… SEPARATOR …)`, and silently
compiles PostgreSQL's `id::text` into `"u"."id::text"`. On master, the June 2026 grammar work
added `||` and the JSON operators. The other ten remain.

Users have asked for these since 2014 (#2882, #12867). The answer each time was "use raw SQL",
yet raw SQL has no first-class API either:
- `new Resultset\Simple($map, $model, $db->query($sql))` works for one model per row;
- several models per row need `Resultset\Complex` with an internal column structure and
  `_alias_column` aliases;
- on SQLite, `PdoResult::numRows()` returns 0 rows for a statement starting with `WITH` and
  breaks on multi-line SQL.

**Every new construct costs a change in three implementations.** The re2c scanner and Lemon
grammar in C, AST → IR in `Query.zep` (4,672 lines on master), and the Dialect, then the same in
the PHP port (`phalcon/phql` + `phalcon/phalcon`'s `Query.php`). The CTE attempt (#17142, +5320
lines) was declined because "there are fundamental issues here primarily with how the existing
code is structured … this needs a major one. We can certainly consider it for v7."

**The common path does not need a grammar at all.** `Model::find()` receives structured
parameters. Today they make this trip:
1. `Builder::getPhql()` glues them into a string;
2. the C parser turns that string back into a tree;
3. `Query::_prepareSelect()` resolves the tree against metadata into an IR;
4. `Dialect::select()` serialises the IR into SQL.

Steps 1-3 exist to recover the array the Builder already had. What step 3 adds (model → table,
property → column, placeholder forms) needs metadata, not a parser.

## Why change the architecture instead of growing the grammar

- **The grammar can never catch up.** The SQL that people reach for (CTEs, window functions,
  JSON, upserts, `LATERAL`, `RETURNING`, full-text variants) differs per database and keeps
  growing. Each addition is a C + Zephir + PHP change with BC risk in the lexer, as #17142
  showed. Passing SQL through ends that race.
- **The Dialect already supports pass-through.** `Dialect::select()` accepts raw strings for
  `where`/`group`/`order`/FROM, and an expression of type `literal` is emitted verbatim
  (`Db/Dialect.zep:259-260`). Phalcon already uses the Dialect without PHQL in two places:
  - `Model::refresh()` calls `dialect->select()` with a raw `where` string (`Model.zep:2654`);
  - PHQL's own UPDATE/DELETE build an IR by hand and run it through `setIntermediate()`
    (`Query.zep:3193-3237`).
- **Performance is not the argument, maintenance and capability are.** With the AST and IR
  caches, a repeated `find()` mostly skips parsing already. The cost is in the code that has to
  exist in three places and still refuses SQL.
- **Keeping `find()` exactly as it is and changing only the backend is what makes this
  affordable.** Applications do not change. Only the SQL that used to be rejected starts working.

## Proposed approach

### 1. `find()` family compiled straight to the Dialect definition

`Model::find/findFirst/count/sum/average/maximum/minimum`, `Criteria::execute()` and the magic
`findBy*` keep their signatures and parameter keys. Their backend becomes a compiler that builds
the `Dialect::select()` definition directly. The prototype (`prototype/src/Compiler/FindCompiler.php`)
does it like this:

| definition key | built from |
|---|---|
| `tables` | `getSource()` / `getSchema()` |
| `columns` | `metaData->getAttributes()` as `[column, table]`, the same expansion `executeSelect` does today; or the caller's `columns`, which hydrate into `Row` as today |
| `where`, `order`, `group`, `having` | the caller's string, through the fragment rewriter (§2), as `{type: literal}` |
| `limit` / `offset` | `:APL0` / `:APL1` int placeholders, the same names and types as today |
| `distinct`, `forUpdate`, `sharedLock` | booleans |

Hydration does not change: the same `Resultset\Simple($columnMap, $model, $result, $cache,
$keepSnapshots)` call as `Query::executeSelect()`. Snapshots, `afterFetch`, `save()`, caching and
custom resultset classes behave the same.

```php
// all four are refused by PHQL today; the last three are prototype tests (SQLite), the first is
// MySQL syntax and not yet run against MySQL
Users::find("created_at > NOW() - INTERVAL 7 DAY");
Users::find(['id IN (SELECT user_id FROM orders WHERE total > :min: UNION SELECT :vip:)', 'bind' => [...]]);
Users::find(['order' => "CASE WHEN country = 'BG' THEN 0 ELSE 1 END, id"]);
Users::find(['columns' => 'id, ROW_NUMBER() OVER (PARTITION BY country ORDER BY id) AS rn']); // Row objects
```

### 2. The fragment rewriter replaces the grammar on this path

A single left-to-right scan over each raw fragment (`prototype/src/Compiler/FragmentRewriter.php`,
173 lines, contract in `FragmentRewriterTest`). It rewrites only Phalcon's own spellings:
- placeholders: `:name:` → `:name`, `?0` → `:0`, `{name}` / `{name:type}` → `:name`,
  `{name:array}` → `:name0, :name1, …`. These are exactly the SQL placeholders PHQL emits today;
- `[Fully\Qualified\Model]` → its table, for the queried model;
- **columnMap**: a bare `property`, or `alias.property`, of the queried model → its column.
  Function names, `AS` aliases and other domains are left alone.

String literals, quoted identifiers, keywords, operators, function names and `::` casts are never
touched. Everything else reaches the database byte for byte.

### 3. First-class native SQL

```php
Users::findBySql(string $sql, array $bind = [], array $bindTypes = []): ResultsetInterface;   // into the model
$modelsManager->nativeQuery(string $sql, array $bind = [], array $bindTypes = []): ResultsetInterface; // into Row
```

- The SQL returns real column names. The model's columnMap and snapshots apply on hydration
  (prototype: `NativeSql::findBySql`, `::rows`; `FindBySqlTest` covers a CTE into models, a
  columnMap model, a snapshot then `save()`, a window function into rows, and a derived table).
- Several models per row (`SELECT u.*, o.* …`) need a public result mapping in place of
  `Complex`'s internal `columnTypes`. That is milestone 3, with a shape to agree on (open
  question 6).

### 4. Fix the row count raw SQL depends on

`PdoResult::numRows()` (`Db/Result/PdoResult.zep:278-337`) should wrap the whole statement
(`SELECT COUNT(*) FROM (<sql>)`) instead of `preg_match("/^SELECT\s+(.*)/i")`. That covers
`WITH`, comments and newlines. Better still, it could count lazily, so a resultset does not run a
second query just to be constructed. The prototype's `src/Db/CountedResult.php` is the
first variant.

### 5. Builder on the compiler

The Builder already stores structured state. It compiles the same way as `find()`:
- explicit join `ON` strings go through the rewriter as `literal` conditions;
- **implicit joins** (`->join(Orders::class)` with no `ON`) are resolved from
  `Manager::getRelationsBetween()`, which needs relations, not a grammar. Today's
  `getSingleJoin`/`getMultiJoin` logic moves over, many-to-many included;
- multi-model columns (`u.*, o.*`) produce the Complex column types structurally, since the
  Builder knows every alias;
- `Paginator\Adapter\QueryBuilder`, relations (`Manager::getRelationRecords`), the FK checks and
  the `Uniqueness` validator all go through Builder/`find()`, so they move with it.

### 6. PHQL becomes an optional front end

- `Manager::createQuery()` / `executeQuery()` and `new Query($phql)` keep working in v7,
  marked `@deprecated`. A PHQL string is parsed as today and its IR handed to the same executor.
- PHQL `UPDATE`/`DELETE` keep their per-record semantics (they run `update()`/`delete()` on
  each record, with events, validation and cascades). That is the one thing raw SQL cannot
  replace, so it needs an equivalent before PHQL can go, e.g.
  `Users::updateWhere($params, $values)` / `deleteWhere($params)` (open question 5).
- v8: the C parser and the IR builder leave cphalcon. `phalcon/phql` can stay as an opt-in
  package for applications that want PHQL strings.

## Milestones

- **M0 (done, prototype):**
  - `find()`/`findFirst()` params → Dialect, `findBySql()`, `rows()`, in plain PHP over the 7.0.x
    extension (`resources/rfc/native-sql/prototype`);
  - 65 tests: 17 parity cases against `Model::find()` on the same data, 9 SQL constructs PHQL
    refuses that now pass, 6 native-SQL cases, the 26-case rewriter contract, 4 documented
    findings.
- **M1:** the compiler in Zephir (`Mvc/Model/Query/Compiler`), used by the `find()` family and
  `Criteria`. The existing `tests/database/Mvc/Model/*` suites run unchanged against it. Behind
  `orm.native_compiler` (default on in 7.0? open question 1).
- **M2:** `findBySql()` / `nativeQuery()` + the `numRows()` fix + docs.
- **M3:** Builder on the compiler (joins, implicit joins via relations, multi-model hydration,
  paginator) + a public result mapping for native multi-model SQL.
- **M4:** relations, FK checks, `Uniqueness` on the compiler; PHQL entry points deprecated;
  per-record `updateWhere`/`deleteWhere`.
- **v8:** remove the PHQL parser and `_prepare*` from cphalcon.

## Backwards compatibility

What stays the same:
- every `find()`/`findFirst()`/aggregate/`Criteria`/Builder signature and parameter key;
- placeholder spellings, columnMap in conditions for the queried model, hydration, snapshots,
  events, cache;
- PHQL strings through `createQuery`/`executeQuery` in v7.

What changes, and is visible:

| today (PHQL) | compiled path |
|---|---|
| an unknown property in a condition throws `Mvc\Model\Exception` before the query runs | the database raises it (`PDOException`, different message) |
| bare columns are qualified (`"users"."created_at"`) | left as written. Irrelevant for single-model `find()`; joins are qualified by the Builder (M3) |
| `IN (SELECT … FROM [Other])` resolves `Other`'s table and columnMap | `[Other]` is resolved to its table; `Other`'s columnMap inside the subquery is open question 3 |
| `orm.enable_literals = false` rejects literals (C parser) | the rewriter sees every literal token, so the rule can be kept (open question 4) |
| conditions are limited to PHQL syntax | anything the database accepts |

**Security, stated plainly.** A string condition (`find("…")`, `findFirst("…")`, `where("…")`)
was always SQL-like code, never data; the PHQL grammar only narrowed what it could contain. On
the compiled path it is plain SQL. The contract does not change, the consequences of breaking it
get bigger:
- external input must go through `bind` (or the in/between helpers);
- every place inside the framework that passes a value into a string condition must bind it.
  The audit list is part of M1.

## Open questions for the maintainers

1. **Timing:** compiler on by default in 7.0, or behind a flag in 7.0 and the default in 7.1?
2. **PHQL in v7:** keep the C parser compiled in (deprecated), or move PHQL strings to the
   `phalcon/phql` package now, since it is already the PHP port's parser?
3. **Subqueries on other models:** should the rewriter resolve `[Other].property` →
   `other.column` through `Other`'s columnMap (cheap, structural), or is raw SQL inside
   subqueries acceptable?
4. **`orm.enable_literals`:** enforce it in the rewriter (it already tokenises literals), or
   retire it together with PHQL?
5. **PHQL DML:** replace per-record PHQL `UPDATE`/`DELETE` with `updateWhere`/`deleteWhere`, or
   keep them as the last PHQL feature?
6. **Native multi-model mapping:** a Doctrine-style result-set mapping object, or the existing
   `_alias_column` alias convention made public?
7. **The PHP port:** the compiler is plain PHP-shaped code (the prototype is PHP). Should it land
   in `phalcon/phalcon` first and be ported to Zephir, or the other way round?

## Out of scope

- Translating SQL between databases. A raw fragment is written for the database it runs on.
  PHQL's portability was partial anyway: function names were never translated.
- Changes to `Phalcon\Db\Adapter` beyond the `numRows()` fix.
- Query caching semantics. The resultset cache keys are user-supplied and do not depend on the
  PHQL text, so they carry over unchanged.
