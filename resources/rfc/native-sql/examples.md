# Examples: what PHQL refuses today, and how the same code reads after the change

Every "today" error and every "after" result below was captured from a real run against the
7.0.x extension (SQLite in-memory):

```sh
cd resources/rfc/native-sql/prototype
./run.sh tools/examples.php        # all examples; exits 1 if one stops behaving as documented
./run.sh tools/examples.php E7     # one example, with the SQL PDO received
```

**In v7 the "after" code is the same call you write today.** `Users::find()` stays
`Users::find()`; only what it accepts grows. The prototype has to keep both paths side by side,
so there it is spelled differently:

| v7 API (proposed) | prototype spelling | status |
|---|---|---|
| `Users::find()`, `findFirst()`, `count()`, `Criteria`, ... | `Users::findNative()`, `findFirstNative()` | same signature, same parameter keys |
| `Users::findBySql($sql, $bind, $types)` | same | new: any SQL → real `Users` models |
| `$this->modelsManager->nativeQuery($sql, $bind, $types)` | `NativeSql::rows()` | new: any SQL → `Row` objects |

The new method names are proposals (RFC open question). `nativeQuery` could as well be `rawSql`.

Fixture data used by every example:

```
users:     1 Ana  BG active   (signed up 2 days ago)     orders: Ana 10.5, Ana 99.0
           2 Ben  SE active   (30 days ago)                      Ben 5.0
           3 Cleo BG inactive (1 day ago)                        Dan 42.0
           4 Dan  JP active   (400 days ago)
customers: table cst_id, cst_name, cst_created; model properties id, name, createdAt (columnMap)
```

---

## E1. What works today keeps working

```php
Users::find(["created_at > datetime('now', '-7 days')", 'order' => 'name']);
```

| | result |
|---|---|
| today | `["Ana", "Cleo"]` |
| after | `["Ana", "Cleo"]` |

The SQL differs a little. PHQL qualifies every column (`"users"."created_at"`); the compiled path
sends your condition as written:

```sql
-- today
SELECT "users"."id", ... FROM "users" WHERE "users"."created_at" > datetime('now', '-7 days') ORDER BY "users"."name"
-- after
SELECT "users"."id", ... FROM "users" WHERE created_at > datetime('now', '-7 days') ORDER BY name
```

On MySQL this is the `Users::find("created_at > NOW()")` you know. Function calls always worked
in PHQL. The trouble starts with anything that is not a function call.

---

## E2. `UNION` inside a condition: big spenders plus one VIP

```php
Users::find([
    'id IN (SELECT user_id FROM orders WHERE total > :min: UNION SELECT :vip:)',
    'bind'  => ['min' => 40, 'vip' => 3],
    'order' => 'name',
]);
```

**Today:**
```
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token IDENTIFIER(UNION), near to ' SELECT :vip:) ORDER BY name'
```

**After:** `["Ana", "Cleo", "Dan"]`
```sql
SELECT "users"."id", ... FROM "users"
WHERE id IN (SELECT user_id FROM orders WHERE total > :min UNION SELECT :vip) ORDER BY name
```

The PHQL placeholders (`:min:`, `:vip:`) keep working; they are rewritten to PDO's `:min`, `:vip`.

---

## E3. Searched `CASE` in `order`: Bulgarian users first

```php
Users::find(['order' => "CASE WHEN country = 'BG' THEN 0 ELSE 1 END, name"]);
```

**Today:**
```
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token WHEN, near to ' country = 'BG' THEN 0 ELSE 1 END, name'
```
(PHQL only knows the short form `CASE country WHEN 'BG' THEN …`.)

**After:** `["Ana", "Cleo", "Ben", "Dan"]`

---

## E4. Window function in `columns`: signup order per country

```php
$rows = Users::find([
    'columns' => 'name, country, ROW_NUMBER() OVER (PARTITION BY country ORDER BY created_at) AS nth_in_country',
    'order'   => 'country, nth_in_country',
]);
```

**Today:**
```
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token (, near to 'PARTITION BY country ORDER BY created_at) AS nth_in_country FROM […
```

**After:** `Phalcon\Mvc\Model\Row` objects, exactly like any `find()` with `columns` today:
```php
[
    ['name' => 'Ana',  'country' => 'BG', 'nth_in_country' => 1],
    ['name' => 'Cleo', 'country' => 'BG', 'nth_in_country' => 2],
    ['name' => 'Dan',  'country' => 'JP', 'nth_in_country' => 1],
    ['name' => 'Ben',  'country' => 'SE', 'nth_in_country' => 1],
]
```

---

## E5. String concatenation `||`

```php
Users::find(["name || '@' || country = :tag:", 'bind' => ['tag' => 'Dan@JP']]);
```

**Today:**
```
Phalcon\Mvc\Model\Exception: Scanner: Unknown opcode 402
```
(Upstream master added `||` in June 2026; 7.0.x does not have it yet.)

**After:** `["Dan"]`

---

## E6. A whole statement into real models: `findBySql()`

```php
$users = Users::findBySql(
    'WITH big_spenders AS (
         SELECT user_id, SUM(total) AS spent FROM orders GROUP BY user_id HAVING SUM(total) > :min
     )
     SELECT u.* FROM users u JOIN big_spenders b ON b.user_id = u.id ORDER BY b.spent DESC',
    ['min' => 40],
    ['min' => Column::BIND_PARAM_INT],
);

foreach ($users as $user) {
    echo get_class($user), '#', $user->id, ' ', $user->name, "\n";
}

$ana = $users->getFirst();
$ana->country = 'GR';
$ana->save();
```

**Today:** PHQL cannot express it at all:
```
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token WITH, near to ' big AS (SELECT o.user_id FROM [...Orders] o …
```

**After:**
```
Phalcon\NativeSql\Tests\Fixtures\Users#1 Ana
Phalcon\NativeSql\Tests\Fixtures\Users#4 Dan
save(): true, changed: country
```
```sql
PDO <- WITH big_spenders AS ( ... ) SELECT u.* FROM users u JOIN big_spenders b ON b.user_id = u.id ORDER BY b.spent DESC
PDO <- UPDATE "users" SET "country" = ? WHERE "id" = ?
```

These are real models: snapshots are kept, `getUpdatedFields()` works, `save()` writes only the
changed column, and `afterFetch` fires. Rule: the statement must return the model's real column
names (`u.*`); the columnMap is applied on the way in.

> SQLite note: `SUM(total) > '40'` (a text bind) is false on SQLite, which is why the int bind
> type is passed. PHQL behaves exactly the same today (0 rows untyped, 2 rows with
> `BIND_PARAM_INT`). MySQL casts implicitly.

---

## E7. rawSql: my own complicated report, as rows I can `foreach` and `print_r`

The case from the original idea: a real reporting query (CTE + `LEFT JOIN` + aggregates + a
window function + `CASE`) whose result is your own data, not a model.

```php
$sql = <<<'SQL'
    WITH revenue AS (
        SELECT u.country,
               u.name,
               COALESCE(SUM(o.total), 0)                                         AS spent,
               COUNT(o.id)                                                       AS orders,
               RANK() OVER (PARTITION BY u.country ORDER BY SUM(o.total) DESC)   AS rank_in_country
          FROM users u
          LEFT JOIN orders o ON o.user_id = u.id
         WHERE u.active = :active
         GROUP BY u.id
    )
    SELECT country,
           SUM(spent)                                         AS revenue,
           SUM(orders)                                        AS orders,
           MAX(CASE WHEN rank_in_country = 1 THEN name END)   AS top_customer
      FROM revenue
     GROUP BY country
     ORDER BY revenue DESC
    SQL;

$rows = $this->modelsManager->nativeQuery($sql, ['active' => 1]);   // prototype: NativeSql::rows()

foreach ($rows as $row) {
    echo "{$row->country}: {$row->revenue} from {$row->orders} orders, top customer {$row['top_customer']}\n";
}

$myOwnDataArray = $rows->toArray();
print_r($myOwnDataArray[0]);
```

**Today:**
```
$this->modelsManager->executeQuery($sql)
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token WITH, near to ' revenue AS ( SELECT u.country, u.name, COALESCE(SUM(o.total), …
```

**After:**
```
BG: 109.5 from 2 orders, top customer Ana
JP: 42 from 1 orders, top customer Dan
SE: 5 from 1 orders, top customer Ben

Array
(
    [country] => BG
    [revenue] => 109.5
    [orders] => 2
    [top_customer] => Ana
)
```

**Honest note: plain arrays from raw SQL already work today**, through the connection:

```php
$myOwnDataArray = $this->db->fetchAll($sql, \Phalcon\Db\Enum::FETCH_ASSOC, ['active' => 1]);
```

`examples.php` checks that it returns exactly the same arrays. What `nativeQuery()` adds on top:
- `Row` objects (`$row->country` and `$row['country']`);
- the full resultset API (`count()`, `getFirst()`, `getLast()`, `filter()`, `toArray()`,
  `jsonSerialize()`); a `cache` option like `find()` has is planned but not in the prototype;
- rows fetched lazily by cursor instead of all at once;
- a correct row count for `WITH` and multi-line statements on SQLite, where
  `PdoResult::numRows()` gets both wrong today (RFC §4);
- with `findBySql()` (E6), rows come back as models instead of arrays.

---

## E8. A model with a columnMap: property names inside new SQL still map

`Customers` maps `cst_name` → `name` and `cst_created` → `createdAt`.

```php
Customers::find(["CASE WHEN name LIKE 'A%' THEN 1 ELSE 0 END = 1 AND createdAt IS NOT NULL"]);
```

**Today:**
```
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token WHEN, near to ' name LIKE 'A%' THEN 1 ELSE 0 END = 1 AND createdAt IS NOT NULL'
```

**After:** `["Acme"]`. The properties were rewritten to columns, and only those:
```sql
SELECT "customers"."cst_id", "customers"."cst_name", "customers"."cst_created" FROM "customers"
WHERE CASE WHEN cst_name LIKE 'A%' THEN 1 ELSE 0 END = 1 AND cst_created IS NOT NULL
```
The string `'A%'`, the keywords and the function names are untouched (contract:
`prototype/tests/FragmentRewriterTest.php`).

---

## E9. Database-specific syntax: MySQL `INTERVAL` and `REGEXP`

```php
Users::find(['created_at > NOW() - INTERVAL 7 DAY AND email REGEXP :re:', 'bind' => ['re' => '^a']]);
```

**Today:**
```
Phalcon\Mvc\Model\Exception: Syntax error, unexpected token INTEGER(7), near to ' DAY AND email REGEXP :re:'
```

**After:** passed through unchanged (shown compiled, not run: these fixtures are SQLite, and on
MySQL the identifiers are quoted with backticks):
```sql
SELECT "users"."id", ... FROM "users" WHERE created_at > NOW() - INTERVAL 7 DAY AND email REGEXP :re
```

The same goes for PostgreSQL's `id::text`. Today PHQL silently turns it into the broken
identifier `"id::text"`; after, it reaches PostgreSQL as written.

---

## E10. What changes: mistakes are reported by the database

```php
Users::find(['nmae = :n:', 'bind' => ['n' => 'Ana']]);   // typo
```

| | error |
|---|---|
| today | `Phalcon\Mvc\Model\Exception: Column 'nmae' does not belong to any of the selected models (1)` |
| after | `PDOException: SQLSTATE[HY000]: General error: 1 no such column: nmae` |

You still get an error, just from the database instead of Phalcon, and after the round trip
instead of before it.

---

## Rules that come with it

- **Values go in `bind`, never into the string.** A condition string has always been code, not
  data. PHQL's grammar only limited what it could contain; after this change it is plain SQL.

  ```php
  Users::find("name = '$name'");                                      // never
  Users::find(['name = :name:', 'bind' => ['name' => $name]]);        // always
  Users::query()->inWhere('id', $ids)->execute();                     // helpers bind for you
  ```
- **You write SQL for your database.** `INTERVAL` is MySQL, `::text` is PostgreSQL. PHQL never
  translated function names either, so a portable app keeps to portable SQL in its conditions.
- **On SQLite, compare aggregates against typed binds** (`BIND_PARAM_INT`), as E6 shows. That is
  the same as today.

## Not covered by this NFR

- **Writes** such as `INSERT … ON CONFLICT`, `INSERT … SELECT` or bulk `UPDATE … JOIN`. PHQL
  refuses them today, and they stay `$this->db->execute($sql, $bind)`, which already works.
  Model events, validation and behaviours do not run for them, which is why PHQL's per-record
  `UPDATE`/`DELETE` keep their place (RFC §6).
- **Several models per row from raw SQL** (`SELECT u.*, o.* …` into `Users` + `Orders`) needs a
  public result mapping. That is RFC milestone M3; today only the Builder/PHQL path does it.
