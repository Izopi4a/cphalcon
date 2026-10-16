# Survey: everything that produces or consumes PHQL on 7.0.x

Read from branch `nfr-orm-native-sql` (upstream 7.0.x). Paths under `phalcon/`. This decides what
keeps working if `find()`/Builder stop emitting PHQL, and what still needs a PHQL front end.

## Model static finders
- `find()` Mvc/Model.zep:1740:
  - non-array params become `[$p]`;
  - `getPreparedQuery()` (5623-5675): `createBuilder($params)->from(static::class)`, then binds,
    `transaction` and `cache` are re-applied to the Query;
  - `hydration` is applied after execute (1765). `findFirst()` (1859) ignores it.
- `getPreparedQuery()` always uses `Di::getDefault()` (5628) and `from()` overrides a user
  `models` key.
- Aggregates `count/sum/average/maximum/minimum` go through `groupResult()` (4704-4790). Their
  `column`, `distinct` and `group` keys are opaque strings spliced into the column list.
  `count()` drops `order`.
- Magic `findBy*/findFirstBy*/countBy*` (`invokeFinder` 4800-4915) build
  `"[field] = ?0"` / `"[field] IS NULL"`, with the field resolved through the reverse columnMap.
- Accepted find() keys (`Builder::__construct`, Query/Builder.zep:145-307):
  - `0`/`conditions`: a string, which is opaque PHQL; a number, which is a PK lookup with
    `:APK0:`; or an array of `[cond, bind, types]`;
  - `bind`, `bindTypes`, `columns`, `joins`, `group`, `having`, `order`, `limit`, `offset`,
    `distinct`, `for_update`, `shared_lock`;
  - Model-only: `cache`, `hydration`, `transaction`.

## Query\Builder (48 public methods)
- `getPhql()` (Builder.zep:684) is string assembly:
  - `autoescape()` (417) wraps names in `[...]`;
  - columns, WHERE, HAVING and string ORDER BY are pasted verbatim;
  - joins without ON rely on PHQL implicit joins;
  - limit/offset become `:APL0:`/`:APL1:` int placeholders (1019-1026);
  - `inWhere/notInWhere/betweenWhere` mint `:AP{n}:` (1607-1764).
- Quirks found on the way:
  - `groupBy("a, b")` strips all spaces (1111-1116), which breaks expressions like `IF(x, 1, 0)`;
  - ORDER BY in array form keeps only the 2nd token, so `NULLS LAST` is lost (973-978);
  - `offset` without `limit` is dropped (993);
  - empty `notInWhere` emits `expr != expr` (1750);
  - `getPhql()` mutates `bindParams` as a side effect.
- Structured enough to compile without parsing: models and aliases, default `Model.*` columns,
  join type and target, joins without ON (via the relation lookup), limit/offset, distinct,
  forUpdate, sharedLock, binds, the in/between helpers, plain `ident [ASC|DESC]` order/group items.
- Opaque, would pass through verbatim: where/having strings, join ON strings, column strings and
  array values, order/group strings, the aggregate keys.

## Criteria
- Accumulates the same keys as the Builder constructor. `execute()` (Criteria.zep:272-285) calls
  `{model}::find(getParams())`, exactly the find path.
- Its own hidden placeholders are `:ACP{n}:`.
- `where()` merges binds with `array_merge`, which renumbers int keys and breaks `?0`
  (876, 890).
- `fromInput()` (300-380) builds `"[field] LIKE :field:"` through the columnMap.

## Other producers and consumers
- `Manager::createQuery()/executeQuery()` (Manager.zep:853, 907) take **arbitrary PHQL**,
  including INSERT/UPDATE/DELETE. These are the public PHQL entry points that must keep a PHQL
  front end (or a deprecation) in v7.
- Relations (`Manager::getRelationRecords`, Manager.zep:1339-1580):
  - many-to-many and has-one-through use a Builder with
    `innerJoin(Intermediate, "[I].[f] = [R].[rf]")` + `andWhere(":APR0:")`;
  - direct relations call `Referenced::find/findFirst/count` with `"[Referenced].[rf] = :APR{n}:"`
    plus the relation's `params` option, which is opaque PHQL.
- FK checks in Model (`checkForeignKeysRestrict` 3582, reverse cascade/restrict 3751, 3869) and
  has-one-through saves (5423) go through `count/findFirst` with `"[field] = ?N"`.
- `Filter/Validation/Validator/Uniqueness` (306-422) builds `attr = ?N`, `attr <> ?N`,
  `attr NOT IN (...)` fragments and calls `{class}::count()`.
- `Paginator/Adapter/QueryBuilder`:
  - requires the concrete `Builder` (75-80);
  - clones it, sets `COUNT(*) [rowcount]` columns, and with HAVING wraps `getSql()` in raw
    `SELECT COUNT(*) … FROM (<sql>)` (182-248).
  - `Paginator/Adapter/Model` goes through `count()` + `find()`.
- Not PHQL, already raw SQL or Dialect:
  - `Model::has()` (4606);
  - **`Model::refresh()`, which calls `dialect->select([...])` directly with a raw `where`
    string (Model.zep:2654)**;
  - model writes (adapter `insert/update/delete`);
  - `PdoResult::numRows` (see survey-execution.md).
- `AbstractPdo::convertBoundParams()` (328-365) converts `?N`/`:name:` to `?`. It is public, but
  nothing calls it.

## Today's raw SQL path
- There is no `findBySql`/`rawSql` API (grep found nothing).
- Workable today: `new Resultset\Simple($columnMap, $model, $db->query($sql, $bind, $types),
  null, $keepSnapshots)`.
- Multi-model rows need `Resultset\Complex` with the internal `columnTypes` structure and
  `_alias_column` SQL aliases. That is not ergonomic and not documented.
- The `Query(null)` + `setType(PHQL_T_SELECT)` + `setIntermediate($ir)` bypass works (Query uses
  it internally). Whether the `PHQL_T_SELECT` constant is reachable from userland is unverified.
