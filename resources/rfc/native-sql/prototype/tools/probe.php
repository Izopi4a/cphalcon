<?php
/**
 * Which SQL constructs make it through PHQL, and does the database accept the same thing natively?
 *
 * For every case:
 *   parse   Query\Lang::parsePHQL()     the C parser of the loaded phalcon.so
 *   compile Query::getSql()             AST -> IR -> Dialect (metadata resolution, column checks)
 *   native  the equivalent hand-written SQL sent straight through the Pdo adapter (SQLite here)
 *
 * {Users}/{Orders} expand to the fixture model class names in PHQL; the native SQL uses tables.
 * Usage: ./run.sh tools/probe.php [--markdown]
 */
declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Mvc\Model\Query;
use Phalcon\Mvc\Model\Query\Lang;
use Phalcon\NativeSql\Tests\Fixtures\Database;

$markdown = in_array('--markdown', $argv, true);
$fixtures = new Database();

/** @var list<array{0: string, 1: string, 2: ?string}> label, PHQL, native SQL (null = not on SQLite) */
$cases = [
    ['find("created_at > NOW()") style function', "SELECT u.* FROM {Users} u WHERE u.created_at > datetime('now', '-7 days')", "SELECT * FROM users u WHERE u.created_at > datetime('now', '-7 days')"],
    ['IF() / IIF() as a function', "SELECT IIF(u.active = 1, 'yes', 'no') AS a FROM {Users} u", "SELECT IIF(u.active = 1, 'yes', 'no') AS a FROM users u"],
    ['simple CASE x WHEN 1', "SELECT CASE u.active WHEN 1 THEN 'yes' ELSE 'no' END AS a FROM {Users} u", "SELECT CASE u.active WHEN 1 THEN 'yes' ELSE 'no' END AS a FROM users u"],
    ['searched CASE WHEN cond', "SELECT CASE WHEN u.active = 1 THEN 'yes' ELSE 'no' END AS a FROM {Users} u", "SELECT CASE WHEN u.active = 1 THEN 'yes' ELSE 'no' END AS a FROM users u"],
    ['EXISTS (subquery)', 'SELECT u.* FROM {Users} u WHERE EXISTS (SELECT o.id FROM {Orders} o WHERE o.user_id = u.id)', 'SELECT * FROM users u WHERE EXISTS (SELECT o.id FROM orders o WHERE o.user_id = u.id)'],
    ['IN (subquery)', 'SELECT u.* FROM {Users} u WHERE u.id IN (SELECT o.user_id FROM {Orders} o)', 'SELECT * FROM users u WHERE u.id IN (SELECT o.user_id FROM orders o)'],
    ['COUNT(DISTINCT x)', 'SELECT COUNT(DISTINCT u.country) AS c FROM {Users} u', 'SELECT COUNT(DISTINCT u.country) AS c FROM users u'],
    ['UNION ALL', 'SELECT u.id FROM {Users} u UNION ALL SELECT o.user_id FROM {Orders} o', 'SELECT u.id FROM users u UNION ALL SELECT o.user_id FROM orders o'],
    ['UNION inside IN (...)', 'SELECT u.* FROM {Users} u WHERE u.id IN (SELECT o.user_id FROM {Orders} o UNION SELECT 3)', 'SELECT * FROM users u WHERE u.id IN (SELECT o.user_id FROM orders o UNION SELECT 3)'],
    ['CTE  WITH x AS (...)', 'WITH big AS (SELECT o.user_id FROM {Orders} o WHERE o.total > 20) SELECT u.* FROM {Users} u WHERE u.id IN (SELECT user_id FROM big)', 'WITH big AS (SELECT o.user_id FROM orders o WHERE o.total > 20) SELECT * FROM users u WHERE u.id IN (SELECT user_id FROM big)'],
    ['window function OVER (...)', 'SELECT u.id, ROW_NUMBER() OVER (PARTITION BY u.country ORDER BY u.id) AS rn FROM {Users} u', 'SELECT u.id, ROW_NUMBER() OVER (PARTITION BY u.country ORDER BY u.id) AS rn FROM users u'],
    ['derived table FROM (SELECT ...)', 'SELECT t.c FROM (SELECT COUNT(*) AS c FROM {Users} u) t', 'SELECT t.c FROM (SELECT COUNT(*) AS c FROM users u) t'],
    ['ORDER BY ... NULLS LAST', 'SELECT u.* FROM {Users} u ORDER BY u.email DESC NULLS LAST', 'SELECT * FROM users u ORDER BY u.email DESC NULLS LAST'],
    ['LIKE ... ESCAPE', "SELECT u.* FROM {Users} u WHERE u.name LIKE 'A!%' ESCAPE '!'", "SELECT * FROM users u WHERE u.name LIKE 'A!%' ESCAPE '!'"],
    ['string concat ||', "SELECT u.name || '@' || u.country AS tag FROM {Users} u", "SELECT u.name || '@' || u.country AS tag FROM users u"],
    ['JSON ->> operator', "SELECT u.* FROM {Users} u WHERE json_object('c', u.country) ->> '$.c' = 'BG'", "SELECT * FROM users u WHERE json_object('c', u.country) ->> '$.c' = 'BG'"],
    ['GROUP_CONCAT(x, sep)', "SELECT GROUP_CONCAT(u.name, ',') AS n FROM {Users} u", "SELECT GROUP_CONCAT(u.name, ',') AS n FROM users u"],
    ['INSERT ... SELECT', 'INSERT INTO {Orders} (user_id, total) SELECT u.id, 0 FROM {Users} u', 'INSERT INTO orders (user_id, total) SELECT u.id, 0 FROM users u'],
    ['upsert (ON CONFLICT / ON DUPLICATE KEY)', "INSERT INTO {Users} (id, name) VALUES (1, 'Ana') ON CONFLICT(id) DO UPDATE SET name = 'Ana'", "INSERT INTO users (id, name) VALUES (1, 'Ana') ON CONFLICT(id) DO UPDATE SET name = 'Ana'"],
    ['MySQL: DATE_SUB(NOW(), INTERVAL 7 DAY)', 'SELECT u.* FROM {Users} u WHERE u.created_at > DATE_SUB(NOW(), INTERVAL 7 DAY)', null],
    ['MySQL: REGEXP operator', "SELECT u.* FROM {Users} u WHERE u.email REGEXP '^a'", null],
    ['MySQL: GROUP_CONCAT(x SEPARATOR ...)', "SELECT GROUP_CONCAT(u.name SEPARATOR ',') AS n FROM {Users} u", null],
    ['PostgreSQL: x::text cast', 'SELECT u.id::text AS t FROM {Users} u', null],
];

$classes = [
    '{Users}'  => '[Phalcon\\NativeSql\\Tests\\Fixtures\\Users]',
    '{Orders}' => '[Phalcon\\NativeSql\\Tests\\Fixtures\\Orders]',
];

$rows = [];
foreach ($cases as [$label, $phql, $native]) {
    $phql = strtr($phql, $classes);

    $parse = $compile = $nativeResult = '-';
    try {
        Lang::parsePHQL($phql);
        $parse = 'ok';
        try {
            $query = new Query($phql, $fixtures->di);
            $query->parse();
            $compile = 'ok';
            if (str_starts_with($phql, 'SELECT')) {
                $sql = $query->getSql()['sql'];
                try {
                    $query->execute();
                } catch (Throwable $e) {
                    // compiled, but into something the database cannot run (e.g. `x::text` -> "x::text")
                    $compile = 'MANGLED: ' . short($sql);
                }
            }
        } catch (Throwable $e) {
            $compile = 'FAIL: ' . short($e->getMessage());
        }
    } catch (Throwable $e) {
        $parse = 'REFUSED: ' . short($e->getMessage());
    }

    if ($native === null) {
        $nativeResult = 'n/a (not SQLite)';
    } else {
        try {
            $fixtures->db->begin();
            str_starts_with($native, 'INSERT') ? $fixtures->db->execute($native) : $fixtures->db->fetchAll($native);
            $nativeResult = 'ok';
        } catch (Throwable $e) {
            $nativeResult = 'FAIL: ' . short($e->getMessage());
        } finally {
            $fixtures->db->rollback();
        }
    }

    $rows[] = [$label, $parse, $compile, $nativeResult];
}

\Phalcon\Di\Di::reset();

if ($markdown) {
    echo "| construct | PHQL parse | PHQL compile | raw SQL via PDO (SQLite) |\n|---|---|---|---|\n";
    foreach ($rows as $r) {
        echo '| ', implode(' | ', array_map(static fn (string $c): string => str_replace('|', '\\|', $c), $r)), " |\n";
    }
    exit(0);
}

printf("%-42s %-34s %-34s %s\n", 'construct', 'PHQL parse', 'PHQL compile', 'raw SQL via PDO (SQLite)');
foreach ($rows as $r) {
    printf("%-42s %-34s %-34s %s\n", ...$r);
}

function short(string $message): string
{
    $message = preg_replace('/, when parsing: .*/s', '', $message);
    $message = preg_replace('/\s+/', ' ', $message);

    return mb_strimwidth($message, 0, 60, '…');
}
