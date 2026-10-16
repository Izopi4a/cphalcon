**Describe the bug**

On PHP 8.5, `Phalcon\Db\Enum::FETCH_GROUP` and the other PDO fetch flags have the wrong values, and `DataMapper\Pdo\Connection::fetchGroup()` throws with its default arguments.

`phalcon/Db/Enum.zep` declares `const FETCH_GROUP = \PDO::FETCH_GROUP;`, and `AbstractConnection::fetchGroup()` uses `\PDO::FETCH_GROUP | flags`. Zephir inlines the value of `\PDO::FETCH_*` from the PHP that runs `zephir generate`, so the committed `ext/` carries the old numbers. PHP 8.5 renumbered these flags:

| constant | in the committed `ext/` (generated before 8.5) | `PDO::` on PHP 8.5.4 |
|---|---|---|
| `FETCH_GROUP` | 65536 | 32 |
| `FETCH_UNIQUE` | 196608 | 64 |
| `FETCH_CLASSTYPE` | 262144 | 128 |
| `FETCH_SERIALIZE` | 524288 | 512 |
| `FETCH_PROPS_LATE` | 1048576 | 256 |

**To Reproduce**

```php
// PHP 8.5, Phalcon 5.23.0 built from the committed ext/
$connection = new \Phalcon\DataMapper\Pdo\Connection('sqlite::memory:');
$connection->exec('create table t (k, v)');
$connection->exec("insert into t values (1, 'a'), (1, 'b'), (2, 'c')");

$connection->fetchGroup('select k, v from t');
// ValueError: PDOStatement::fetchAll(): Argument #1 ($mode) must be a bitmask of PDO::FETCH_* constants

$db = new \Phalcon\Db\Adapter\Pdo\Sqlite(['dbname' => ':memory:']);
$db->execute('create table t (k, v)');
$db->fetchAll('select k, v from t', \Phalcon\Db\Enum::FETCH_GROUP | \Phalcon\Db\Enum::FETCH_COLUMN);
// ValueError: PDOStatement::setFetchMode(): Argument #1 ($mode) must be a bitmask of PDO::FETCH_* constants

var_dump(\Phalcon\Db\Enum::FETCH_GROUP, \PDO::FETCH_GROUP);
// int(65536) int(32)
```

**Expected behavior**

`Phalcon\Db\Enum::FETCH_*` equals `PDO::FETCH_*` on the PHP the extension runs on, and `fetchGroup()` works.

**Details**
 - Phalcon version: 5.23.0 (master `33f1076a88`, built from the committed `ext/`)
 - PHP Version: 8.5.4
 - Operating System: Linux
 - Installation type: Compiling from source

**Additional context**

- Running `vendor/bin/zephir generate` on PHP 8.5 changes exactly two files, `ext/phalcon/db/enum.zep.c` and `ext/phalcon/datamapper/pdo/connection/abstractconnection.zep.c`, to the 8.5 numbers. But then a build for PHP 8.4 or older gets the wrong values instead, because a single committed `ext/` serves every PHP version.
- So the values must not be fixed at generate time. Options:
  - read them from PDO when the module starts, or at call time (e.g. `constant("PDO::FETCH_GROUP")` in `fetchGroup()`);
  - or keep `Db\Enum` only for constants whose values did not change.
- Other `\PDO::` constants used in the sources have the same value on 8.4 and 8.5, since regenerating changes nothing else.
