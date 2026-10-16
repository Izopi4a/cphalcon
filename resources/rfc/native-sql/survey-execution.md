# Survey: execution, hydration and DML semantics on 7.0.x

Read from branch `nfr-orm-native-sql` (upstream 7.0.x). Q = `phalcon/Mvc/Model/Query.zep`.
Items marked (runtime) were confirmed with the prototype against the built extension.

## executeSelect → resultset
- **Simple vs Complex** (Q:1069-1111):
  - exactly one object column and no scalars → Simple over the model;
  - only aliased scalars → Simple over `Row`;
  - several objects, or objects + scalars → Complex.
- **Complex column types** (Q:1119-1188): per object alias it stores `instance`, `attributes`,
  `columnMap` (only if `orm.column_renaming`) and `keepSnapshots`. SQL columns are aliased
  `_<alias>_<column>` (runtime: trace case 5). Scalars become `[expr, null, alias]`.
- **Simple column map** (Q:1302-1358):
  - `metaData->getColumnMap(model)`, or a typed `[attribute, type]` map when
    `orm.cast_on_hydrate` is on. Casting is never applied on the Complex path;
  - `keepSnapshots = manager->isKeepingSnapshots(model)`, which is always true while
    `orm.dynamic_update` (default on) is on;
  - a custom `getResultsetClass()` is honoured only for Simple.
- `RawValue` binds are pasted into the SQL with `str_replace` (Q:1256-1267). This is naive:
  `:a` would also match inside `:ab`. This is the existing "raw fragment" escape hatch, but it is
  only allowed at a placeholder position in a statement PHQL accepts.
- Hydration modes RECORDS/ARRAYS/OBJECTS (Resultset.zep:79-87), set after construction.
- Cache (Q:285-350, 421-432): user-supplied `key`, `modelsCache` service, SELECT only.

## The SQLite row count (affects raw SQL) (runtime)
- `Resultset::__construct()` calls `numRows()` immediately (Resultset.zep:200).
- `PdoResult::numRows()` (Db/Result/PdoResult.zep:278-337) uses `rowCount()` for mysql/pgsql.
  For everything else (SQLite) it runs
  `preg_match("/^SELECT\s+(.*)/i")` + `SELECT COUNT(*) "numrows" FROM (SELECT <match>)`.
  - **No `/s` flag**: a multi-line statement is cut at the first newline, and the COUNT query
    fails ("no such column").
  - **Requires a leading `SELECT`**: a statement starting with `WITH` (or a comment) keeps row
    count 0, so the resultset is silently empty.
  - The prototype works around both with `src/Db/CountedResult.php`, which wraps the whole
    statement. The RFC proposes the same fix in `numRows()`.
- Rows are fetched by cursor unless `orm.resultset_prefetch_records` > 0 (default "0").
  `dataSeek`, `refresh` and `Simple::toArray()` re-execute the statement without firing
  `db:*` events.

## Resultset constructors
- `Simple(columnMap, model, result, cache = null, keepSnapshots = false)` (Resultset/Simple.zep:58).
  `current()` calls `Model::cloneResultMap()`, or `{Class}::cloneResultMap` with
  `orm.late_state_binding`.
- `Complex(columnTypes, result = null, cache = null)` (Complex.zep:57) needs the internal
  `columnTypes` structure. An all-null object slot becomes null (the LEFT JOIN case).
- `Model::cloneResultMap()` (Model.zep:973-1149):
  - clones the base instance (no `onConstruct` per row);
  - looks up `columnMap` first, then the reverse map. An unknown column throws unless
    `orm.ignore_unknown_columns` is set;
  - keeps snapshots, then fires `afterFetch`.
- With today's public API:
  - **(a) one model per row works** (`NativeSql::findBySql` does exactly this, runtime);
  - (b) several models per row and (c) model + scalars need a hand-built `columnTypes` array
    plus the `_alias_column` naming convention.
  - Missing: a public result-mapping builder, and a row count that does not depend on the SQL
    text.

## PHQL DML runs the model lifecycle per record
- DELETE (Q:781-865): loads the records through a SELECT IR and calls `record->delete()` each,
  in begin/commit. No transaction is passed to the loading query.
- UPDATE (Q:1415-1582): resolves SET values, loads the records, calls
  `record->assign()->update()` each.
- INSERT (Q:872-1007): maps values and calls `manager->load()->assign()->create()`.
  `bindTypes` is ignored.
- So PHQL UPDATE/DELETE fire `beforeUpdate`/`beforeDelete`, validation, behaviours, virtual FKs
  and cascades. **A raw SQL UPDATE/DELETE bypasses all of it.** This is why the RFC keeps PHQL
  DML (or an equivalent per-record API) and does not suggest "just run raw UPDATE".

## Binds
- PHQL → SQL: `?0` → `:0`, `:name:` → `:name`, `{name}` → `:name`;
  `{name:int|str|...}` sets the bind type; `{name:array}` expands through `bindCounts` in the
  Dialect (Q:1886-2014, D:262-280).
- `AbstractPdo::query()` (689-743) always does `prepare` + `executePrepared`.
  `executePrepared()` (478-571):
  - int keys are 1-based;
  - **array values bind as `name0, name1…`** (542-563), so the SQL must already contain
    `:name0, :name1`. The adapter does not rewrite the SQL;
  - `db.force_casting` casts scalars.
- Unverified: an IR-cache hit skips `getExpression`, so `{x:int}` bind types may not be
  re-applied on a second Query with the same PHQL.

## Events on the find path
- `db:beforeQuery` / `db:afterQuery` around every statement (AbstractPdo.zep:703, 730). The
  SQLite count query fires a second pair.
- `afterFetch` fires for every hydrated model (Model.zep:1144).
- `modelsManager:afterInitialize` fires once per class.
- Query, Builder and the resultsets fire no events of their own.
- The profiler only runs when attached to `db:*`.

## orm.* settings on the query path
| setting (default) | effect |
|---|---|
| `orm.enable_literals` (true) | rejects literals, **in the C parser only** (base.c:338-385). Reportedly read from the C global, so `Settings::set` would not affect it (unverified) |
| `orm.column_renaming` (true) | columnMap used for SQL and hydration. When off, `getColumnMap()` returns null |
| `orm.cast_on_hydrate` (false) | typed hydration, Simple only |
| `orm.late_state_binding` (false) | `{Class}::cloneResultMap` |
| `orm.ignore_unknown_columns` (false) | skip instead of throw on unmapped result columns |
| `orm.dynamic_update` (true) | forces snapshots on for every model |
| `orm.resultset_prefetch_records` ("0") | bulk-fetch threshold |
| `orm.enable_implicit_joins` (true) | PHQL `JOIN X` without ON |
| `db.force_casting` (false), `db.escape_identifiers` (true) | bind casting, identifier quoting |
