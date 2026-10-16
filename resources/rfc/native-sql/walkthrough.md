# How `find()` becomes SQL, today and compiled straight through the Dialect

A reading guide for the code behind the NFR. Every step names the file and line on this branch
(upstream `7.0.x`) and shows the real data at that point, captured from the built extension with
`prototype/tools/trace.php`.

Run it yourself (it uses the 7.0.x `phalcon.so` from the sibling clone, see `prototype/run.sh`):

```sh
cd resources/rfc/native-sql/prototype
./run.sh tools/trace.php          # all 6 cases, abbreviated AST/IR
./run.sh tools/trace.php 3 --full # one case, full AST/IR
```

The example below is trace case 3, a model with a `columnMap` (table `customers`, columns
`cst_id, cst_name, cst_created`, properties `id, name, createdAt`). It shows the most work being
done:

```php
Customers::find(['conditions' => 'name LIKE :n:', 'bind' => ['n' => 'A%'], 'order' => 'createdAt']);
```

## Part 1. Today: one array, serialised to a string, parsed back to an array

```
find() params ──► Builder ──► "PHQL string" ──► C scanner + Lemon parser ──► AST
   (array)                                                                    │
                                                         Query::_prepareSelect ▼
PDO ◄── SQL ◄── Dialect::select(IR) ◄── executeSelect (expand columns) ◄──── IR (array)
 │
 └──► Resultset\Simple (columnMap, snapshots) ──► Customers objects
```

### Step 1: `Model::find()` hands the params to a Builder
- `phalcon/Mvc/Model.zep:1740` `find()` wraps a string param as `[$p]` and calls
  `getPreparedQuery()` (`Model.zep:5623`).
- `getPreparedQuery()` does `modelsManager->createBuilder($params)` (`Manager.zep:820`), then
  `->from(static::class)`, then `getQuery()`. It also re-applies `bind`/`bindTypes`, `transaction`
  and `cache` to the Query.
- `Builder::__construct()` (`Query/Builder.zep:145`) copies the keys (`conditions`/`0`, `bind`,
  `columns`, `order`, `group`, `having`, `limit`, `offset`, `for_update`, `distinct`, `joins`, ...)
  into properties. **At this point the query is fully structured data.**

### Step 2: the Builder glues that data into a PHQL string
`Builder::getPhql()` (`Builder.zep:684`). Model names are wrapped in `[...]`, conditions and
order are pasted in verbatim, and limit/offset become hidden placeholders `:APL0:`/`:APL1:`.

```
SELECT [Phalcon\NativeSql\Tests\Fixtures\Customers].* FROM [Phalcon\NativeSql\Tests\Fixtures\Customers] WHERE name LIKE :n: ORDER BY createdAt
```

### Step 3: the C parser turns the string back into a tree (AST)
- `Builder::getQuery()` (`Builder.zep:1045`) creates `new Query($phql)`.
- `Query::execute()` (`Query.zep:276`) calls `parse()` (`Query.zep:579`), which calls
  `Lang::parsePHQL()` (`Query/Lang.zep:38`), which calls C `phql_parse_phql()`
  (`ext/phalcon/mvc/model/query/base.c:153`).
- That runs the re2c scanner (`scanner.re`) and the Lemon grammar (`parser.php.lemon`).
- **This is the step that refuses `UNION`, CTEs, window functions, `INTERVAL`, ...** (see
  `survey-upstream-context.md`). Type codes are in `scanner.h`: 309 = SELECT, 355 = qualified
  name, 268 = LIKE, 274 = `:name:` placeholder.

```json
{ "type": 309,
  "select": { "columns": [{"type": 353, "column": "...\\Customers"}],
              "tables":  {"qualifiedName": {"type": 355, "name": "...\\Customers"}} },
  "where":   { "type": 268, "left": {"type": 355, "name": "name"}, "right": {"type": 274, "value": "n"} },
  "orderBy": { "column": {"type": 355, "name": "createdAt"} },
  "id": 3 }
```

### Step 4: `Query` resolves the tree against model metadata (IR)
`_prepareSelect()` (`Query.zep:3718`) walks the AST:
- `getExpression()` (`Query.zep:1632`) handles every node;
- `getQualified()` (`Query.zep:2985`) maps `name` to `cst_name` through the reverse columnMap,
  qualifies it with the table, and checks for ambiguous or unknown columns;
- the model becomes `tables: ["customers"]` via `getSource()/getSchema()`;
- `:n:` becomes `:n`.

The result is the **intermediate representation**. It is cached per AST id in
`Query::$internalPhqlCache`, so steady-state requests skip steps 3-4.

```json
{ "models":  ["...\\Customers"],
  "tables":  ["customers"],
  "columns": { "...\\Customers": {"type": "object", "model": "...\\Customers", "column": "customers"} },
  "where":   { "type": "binary-op", "op": "LIKE",
               "left":  {"type": "qualified", "domain": "customers", "name": "cst_name", "balias": "name"},
               "right": {"type": "placeholder", "value": ":n"} },
  "order":   [[ {"type": "qualified", "domain": "customers", "name": "cst_created", "balias": "createdAt"} ]] }
```

### Step 5: the Dialect turns the IR into SQL text
- `executeSelect()` (`Query.zep:1013`) picks the read connection.
- It decides Simple or Complex resultset (`Query.zep:1069-1111`).
- It expands the `object` column into `[column, table]` pairs from `metaData->getAttributes()`
  (`Query.zep:1174-1176`).
- Then it calls **`dialect->select($intermediate)` (`Query.zep:1246`)**.

`Dialect::select()` (`Db/Dialect.zep:471`) is plain serialisation. It has no metadata, no models
and no validation (Part 2).

```sql
SELECT "customers"."cst_id", "customers"."cst_name", "customers"."cst_created" FROM "customers"
WHERE "customers"."cst_name" LIKE :n ORDER BY "customers"."cst_created"
```

### Step 6: PDO and hydration
- `connection->query($sql, $bind, $types)` (`Query.zep:1283`), then `AbstractPdo::query()`
  (`Db/Adapter/Pdo/AbstractPdo.zep:689`): `prepare` + `executePrepared` (`:478`), with
  `db:beforeQuery`/`db:afterQuery` events.
- Then `new Resultset\Simple($columnMap, $model, $result, $cache, $keepSnapshots)`
  (`Query.zep:1392`, ctor `Resultset/Simple.zep:58`).
- Each row goes through `Model::cloneResultMap()` (`Model.zep:973`): it renames `cst_name` to
  `name`, keeps snapshots and fires `afterFetch`.

**What to notice:** steps 2 to 4 exist to turn a string back into the array that the Builder
already had in step 1. The only thing they add is the metadata resolution in step 4: model to
table, property to column, qualification, validation, implicit joins.

## Part 2. The Dialect definition is the real target format

`Dialect::select(array $definition)` (`Db/Dialect.zep:471`) reads these keys:

| key | shape | notes |
|---|---|---|
| `tables` (required) | `["users"]` or `[[table, schema, alias]]` or a string | a string is emitted verbatim |
| `columns` (required) | `[[column, domain, alias?], ...]` or expression arrays | a bare string is escaped as ONE identifier, so raw columns need `literal` |
| `distinct` | bool | `SELECT DISTINCT` / `SELECT ALL` |
| `joins` | `[{type, source: [table, schema, alias], conditions: [expr]}]` | no conditions gives `ON 1` |
| `where` | expression array **or string (verbatim)** | `Dialect.zep:1162-1171` |
| `group` | list of expressions **or string** | |
| `having` | expression array only | wrap raw SQL as `literal` |
| `order` | `[[expr, "ASC"/"DESC"?], ...]` **or string** | |
| `limit` | `{number: expr, offset?: expr}` or int | `Dialect.zep:932` |
| `forUpdate` | bool | appends ` FOR UPDATE` |
| `bindCounts` | `{name: n}` | expands `{name:array}` placeholders |

Expressions are dispatched in `getSqlExpression()` (`Dialect.zep:219`). The one that makes this
NFR cheap is:

```zephir
case "literal":
    return expression["value"];      // Dialect.zep:259-260, emitted verbatim
```

**A `literal` node can carry any SQL fragment through the Dialect today, with no Zephir change.**

Phalcon already uses the Dialect without PHQL in two places:
- `Model::refresh()` (`Model.zep:2654`) calls `dialect->select()` directly with a raw `where`
  string.
- `Query::getRelatedRecords()` (`Query.zep:3193`) builds an IR by hand and runs it through
  `setIntermediate()` (`Query.zep:729`), skipping the parser. PHQL UPDATE/DELETE use it to load
  the records they then change one by one.

## Part 3. The same `find()`, compiled straight through the Dialect

```
find() params ──► FindCompiler (metadata + FragmentRewriter) ──► definition ──► Dialect::select ──► SQL ──► PDO
                                                                                                      │
                                            Customers objects ◄── Resultset\Simple (same as step 6) ◄─┘
```

`prototype/src/Compiler/FindCompiler.php` builds the definition from the same metadata calls
`_prepareSelect` uses:

| definition key | built from |
|---|---|
| `tables` | `$model->getSource()` / `getSchema()` |
| `columns` | `metaData->getAttributes()`, as `[column, table]` pairs (what step 5 produces), or the caller's `columns` as `literal` items |
| `where`, `order`, `group`, `having` | the user's raw string, passed through `FragmentRewriter`, wrapped as `{type: literal}` |
| `limit` | the `:APL0`/`:APL1` int placeholders, same names and types PHQL uses |
| `distinct`, `forUpdate` | booleans from the params |

`prototype/src/Compiler/FragmentRewriter.php` is the whole replacement for the grammar on this
path. It is a single scan that rewrites:
- `:n:` to `:n`, `?0` to `:0`, `{n}` to `:n`, `{ids:array}` to `:ids0, :ids1, …`;
- `[Model]` to its table;
- `property` to `column` for the queried model (columnMap).

It never touches string literals, quoted identifiers, keywords, function names, operators or
`::` casts. Everything else reaches the database byte for byte. The contract is
`prototype/tests/FragmentRewriterTest.php`.

What `trace.php 3` prints for the native path (N1/N2):

```json
{ "models":  ["...\\Customers"],
  "tables":  [["customers", null, null]],
  "columns": [["cst_id", "customers"], ["cst_name", "customers"], ["cst_created", "customers"]],
  "where":   {"type": "literal", "value": "cst_name LIKE :n"},
  "order":   [[ {"type": "literal", "value": "cst_created"} ]] }
```
```sql
SELECT "customers"."cst_id", "customers"."cst_name", "customers"."cst_created" FROM "customers"
WHERE cst_name LIKE :n ORDER BY cst_created
-- -> 1 row(s), same rows as the PHQL path
```

Hydration is unchanged. `NativeSql::findBySql()` (`prototype/src/NativeSql.php`) builds the same
`Resultset\Simple($columnMap, $model, $result, null, $keepSnapshots)` as step 6, so models come
back with snapshots, `afterFetch`, and a working `save()` (`FindParityTest::testHydratedModelsAreFullModels`).

Because the condition is now opaque to Phalcon, it can contain anything the database accepts:

```php
Users::find(['id IN (SELECT user_id FROM orders WHERE total > 40 UNION SELECT 3)']);         // UNION
Users::find(['order' => "CASE WHEN country = 'BG' THEN 0 ELSE 1 END, id"]);                  // searched CASE
Users::find(['columns' => 'id, ROW_NUMBER() OVER (PARTITION BY country ORDER BY id) AS rn']); // window fn -> Row
Users::findBySql('WITH big AS (SELECT user_id FROM orders WHERE total > :min) SELECT u.* FROM users u WHERE u.id IN (SELECT user_id FROM big)', ['min' => 40]);
```

All of these throw `Syntax error` on PHQL today. Each one is a test in
`prototype/tests/PassthroughTest.php` or `FindBySqlTest.php` that asserts both sides.

## Part 4. What the native path gives up (it has no grammar)

| PHQL does it in step 4 | native path |
|---|---|
| qualify bare columns (`created_at` → `"users"."created_at"`) | left bare. Only matters once a join is added; Builder joins are milestone 2 |
| unknown / ambiguous column check | the database reports it (different exception and message) |
| columnMap inside a subquery on **another** model | only the queried model's domains are rewritten (open question in the RFC) |
| implicit `JOIN Orders` without `ON` (`getJoins`, `Query.zep:2605`) | not on the `find()` path. For the Builder it is a relation lookup (`Manager::getRelationsBetween`), with no grammar needed |
| `orm.enable_literals` (enforced only in the C token loop, `base.c:338-385`) | not enforced yet. The rewriter already sees every literal, so it can throw on them (RFC open question) |
| cross-database portability of what you type | none: you write SQL for your database. It was only partial before, since function names were never translated |

## Reading order, if you have an hour

1. `Model.zep:1740-1890` (`find`/`findFirst`) and `5623-5675` (`getPreparedQuery`).
2. `Query/Builder.zep:145-307` (constructor) and `684-1040` (`getPhql`). Watch how much is just
   string concatenation.
3. `Query.zep:579-660` (`parse` + IR cache), then skim `3718-4091` (`_prepareSelect`) and
   `2985-3150` (`getQualified`, where columnMap and ambiguity live).
4. `Query.zep:1013-1409` (`executeSelect`). The key line is 1246, `dialect->select(intermediate)`.
5. `Db/Dialect.zep:471-572` (`select`) and `219-372` (`getSqlExpression`, `literal` at 259).
6. `Model.zep:2593-2700` (`refresh`), a model already talking to the Dialect directly.
7. `prototype/src/Compiler/FindCompiler.php` and `FragmentRewriter.php`, the proposal in about
   350 lines.
