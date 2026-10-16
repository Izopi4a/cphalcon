# native-sql playground

A small shop on PostgreSQL that runs every scenario twice: with
`orm.native_compiler` off (today's PHQL parser) and on (find()/Builder compiled
straight to SQL), showing the SQL each path sent, plus the new native SQL API
(`Model::findBySql()`, `Model::findFirstBySql()`, `Manager::nativeQuery()`).

## Run it

    # 1. build the extension from this branch (ext/ is already generated)
    cd ext && phpize && ./configure && make -j"$(nproc)" && cd ..

    # 2. a database and the demo data
    cd resources/native-sql-playground
    docker compose up -d                 # PostgreSQL 18 on 127.0.0.1:54329
    cp .env.example .env
    ./spin seed.php                      # schema + 40 customers, 250 orders

    # 3. look at it
    ./run.sh                             # http://127.0.0.1:8085  scenarios + playground
    ./spin cli.php -v                    # the same in the terminal

PHP 8.3+ with pdo_pgsql. `./spin` is `php -d extension=<the branch's phalcon.so>`;
add `PHALCON_SO=/path/to/phalcon.so` to `.env` to use another build. `.env` is
read by both PHP (parse_ini_file) and docker compose, so keep it to plain
`KEY=value` lines.

## Files

- `scenarios.php` - every scenario is a closure; the page shows its source next to the SQL
- `models.php` - Customer (prefixed columns behind a columnMap), Order, Product (jsonb), OrderItem
- `public/index.php` - the page (Phalcon Micro), `/playground` takes your own find() params or raw SQL

`ext/` was generated on PHP 8.5: Zephir inlines `\PDO::FETCH_*` at generate
time, so `Db\Enum::FETCH_*` carry 8.5's values (FETCH_GROUP and friends differ
on 8.3/8.4). Regenerating on your PHP fixes that; nothing in the playground
uses those modes.
