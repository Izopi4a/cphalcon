# Survey: the PHQL query core on 7.0.x (parser → AST → IR → Dialect)

Read from branch `nfr-orm-native-sql` (upstream 7.0.x, 2026-04-27). Q = `phalcon/Mvc/Model/Query.zep`,
D = `phalcon/Db/Dialect.zep`. The AST builders (`phql_ret_*`) are in
`ext/phalcon/mvc/model/query/parser.php.inc.h` and the type codes in `scanner.h`. Items marked
(runtime) were confirmed with `prototype/tools/trace.php` against the built extension.

## Pipeline
- `Query::execute()` Q:276-444:
  - resultset-cache lookup, then `parse()`;
  - binds merged with `+`, so query-level values win;
  - dispatch to `executeSelect/Insert/Update/Delete`;
  - cache store (SELECT only), then `getFirst()` if `uniqueRow`.
- `parse()` Q:579-660:
  - returns `this->intermediate` early if it is preset, so `setIntermediate()` (Q:729) +
    `setType()` (Q:759) is a public way to skip the parser;
  - otherwise `Lang::parsePHQL` (Lang.zep:38) → C `phql_parse_phql` (base.c:153), which throws
    `Mvc\Model\Exception` on a syntax error;
  - then `_prepareSelect/Insert/Update/Delete` (Q:3718, 3637, 4097, 3539);
  - the IR is cached by AST id in `static $internalPhqlCache` (Q:603-612, 653-655).
- C side caching: AST cache keyed by a hash of the PHQL string (base.c:187-196, `orm.cache_level`
  default 3). The AST `id` comes from a per-request counter (base.c:568-571). In steady state a
  repeated `find()` costs Builder string building, one hash and two cache lookups; the C parse and
  `_prepareSelect` run once per distinct PHQL string per request.
- `executeSelect()` Q:1013-1409:
  - connection choice: read, or write if `forUpdate`, a transaction wins;
    `selectReadConnection` hooks (Q:1031-1067);
  - Simple/Complex/Row classification (Q:1069-1111);
  - column expansion into Dialect format (Q:1113-1205), bind normalisation (`?N` keys → `:N`,
    `bindCounts` for arrays, Q:1210-1239);
  - **`dialect->select(intermediate)` Q:1246**, then `sharedLock` (Q:1248);
  - `RawValue` binds pasted into the SQL with `str_replace` (Q:1256-1267);
  - `getSql()` returns `{sql, bind, bindTypes}` (Q:1272-1278);
  - `connection->query` (Q:1283);
  - `Simple` / custom `getResultsetClass()` / `Complex` (Q:1300-1408).
- PHQL INSERT runs `model->assign()->create()` (Q:872-1007). UPDATE/DELETE load the records
  through a hand-built SELECT IR (`getRelatedRecords` Q:3193-3237, using `setIntermediate`) and
  call `update()`/`delete()` per record inside a transaction (Q:1546-1579, 829-859).
  **`Dialect::select` is the only statement builder Query uses.**

## AST shape (C parser output) (runtime: `trace.php --full`)
- SELECT = `{type: 309, select: {distinct?, columns, tables, joins?}, where?, groupBy?, having?,
  orderBy?, limit?: {number, offset?}, forUpdate?, id}`.
- One-element FROM/JOIN/ORDER/GROUP lists are not wrapped in a list (lemon:210-212 …), which is
  why Query keeps testing `isset x[0]`.
- Nodes are `{type, left?, right?}`:
  - qualified name 355 `{domain?, name}`; function call 350 `{name, arguments?, distinct?}`;
  - placeholders 273 `?N`, 274 `:name:`, 277 `{name[:type]}`;
  - literals 258/259/260 (string, unquoted)/414; CASE 409/WHEN 410/ELSE 411;
  - subquery 407, EXISTS 408.
- The grammar only has `CASE expr WHEN …` (simple CASE), lemon:788. The searched
  `CASE WHEN cond` is refused (runtime: probe).

## IR shape (what Dialect::select receives)
- `models` (class names, used for connections), `tables`, `columns`, `distinct`, `joins`,
  `where`, `group`, `having`, `order`, `limit`, `forUpdate`. Q:4035-4077.
- `columns` entries:
  - object `{type: "object", model, column: table-or-alias, balias}`;
  - scalar `{type: "scalar", column: expr, balias?, sqlAlias?}`.
- `executeSelect` rewrites them into `[attribute, table]` (Simple) or
  `[attribute, table, "_alias_attribute"]` (Complex) before calling the Dialect (Q:1148-1188).
- Expressions:
  - `binary-op {op, left, right}`, `unary-op`;
  - `qualified {domain, name: real column, balias: property}`;
  - `literal {value}` (strings already quoted and escaped by Q:1860-1884);
  - `placeholder {value: ":name", rawValue?, times?}`;
  - `functionCall`, `parentheses`, `cast`, `convert`, `case`, `select {value: IR}`, `list`.
- Gap: `^` and `~` parse but throw "Unknown expression type" in `getExpression` (Q:2203).

## Dialect::select (D:471-572)
- Required keys: `tables`, `columns`. It never reads `models` and has no metadata.
- `where`/`group`/`order`/FROM accept a raw string, emitted verbatim (D:1166-1170, 847, 1071, 759).
- `having` must be an expression array (D:863). A non-array column item is escaped as one
  identifier (D:154-156).
- `getSqlExpression` (D:219-372): **`literal` returns `value` verbatim (D:259-260)**.
  `placeholder` with `times`/`bindCounts` expands to `:name0, :name1…` (D:262-280).
  `functionCall` honours custom dialect functions (D:793).
- No dialect subclass overrides `select`/`limit`/`getSqlExpression`. Only the escape char
  (`` ` `` vs `"`) and `sharedLock` differ.

## What AST → IR resolves using metadata
- model → source/schema (Q:3827-3843; joins Q:2336-2358);
- aliases and their uniqueness (Q:3849-3879, 2462-2590);
- **columnMap** property → column in every expression, through `getQualified` (Q:2985-3150).
  Unknown properties throw;
- **ambiguity**: an unqualified column must exist in exactly one model (Q:3062-3095);
- **implicit joins**: `JOIN X` without ON goes through `getRelationsBetween` →
  `getSingleJoin`/`getMultiJoin` (many-to-many adds the intermediate model) (Q:2605-2937).
  Reading only: composite-key joins look broken (`conditions: null`, Q:3430-3476);
- `WITH` eager loading (Q:3881-3942);
- placeholders `?N`/`:name:`/`{name}`/`{name:type}`/`{name:array}` (Q:1886-2014). `{x:array}`
  needs the bind value at prepare time;
- **`orm.enable_literals`** is enforced only in the C token loop (base.c:338-385). Query and the
  Dialect have no check of their own.

## Single-model `find()` vs hand-written PHQL
- Needed even for `find()`: model → table, columnMap in conditions/order/group/having,
  placeholder forms, column expansion and hydration map, scalar columns (`columns`, aggregates),
  connection selection, cache.
- Only needed for multi-model PHQL: joins (implicit and explicit), cross-model ambiguity,
  `Complex` resultsets, `WITH`, subquery alias scoping, all DML.
- Caveat: `find()` conditions may legally contain `IN (SELECT … FROM [Other])`. Today that is
  resolved against `Other`'s metadata; on the native path it is raw SQL.
