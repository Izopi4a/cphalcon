<?php
/**
 * Runs every example in ../examples.md and prints what PHQL does today ("before") next to what
 * the proposed path returns ("after"), so the outputs in examples.md are captured, not invented.
 *
 * In v7 the "after" call is the SAME public call (Users::find(...)); the prototype calls it
 * findNative()/findBySql()/NativeSql::rows() only because both paths must coexist here.
 *
 * Exits 1 if an example stops behaving as documented (a refused query starts parsing, or a native
 * one stops returning what examples.md shows).
 *
 * Usage: ./run.sh tools/examples.php [E-number]
 */
declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Db\Column;
use Phalcon\Db\Enum;
use Phalcon\NativeSql\NativeSql;
use Phalcon\NativeSql\Tests\Fixtures\Customers;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Users;

$only     = isset($argv[1]) ? strtoupper($argv[1]) : null;
$failures = 0;

/**
 * @param callable(): mixed $before PHQL today
 * @param callable(): mixed $after  proposed path
 * @param mixed             $expect what "after" must return (after normalising with $show)
 * @param bool              $beforeFails whether PHQL is expected to throw
 */
$example = static function (string $id, string $title, callable $before, callable $after, mixed $expect, bool $beforeFails = true) use ($only, &$failures): void {
    if ($only !== null && $only !== $id) {
        return;
    }

    $fixtures = new Database();
    echo str_repeat('-', 100), "\n{$id}  {$title}\n", str_repeat('-', 100), "\n";

    try {
        $result = $before();
        echo 'BEFORE (PHQL)  ok: ', json_encode($result, JSON_UNESCAPED_SLASHES), "\n";
        if ($beforeFails) {
            echo "  !! expected PHQL to refuse this\n";
            $failures++;
        }
    } catch (Throwable $e) {
        echo 'BEFORE (PHQL)  ', (new ReflectionClass($e))->getShortName(), ': ', shorten($e->getMessage()), "\n";
        if (!$beforeFails) {
            $failures++;
        }
    }

    $fixtures->resetLog();
    try {
        $result = $after();
        echo 'AFTER          ', json_encode($result, JSON_UNESCAPED_SLASHES | JSON_PRETTY_PRINT), "\n";
        foreach ($fixtures->selects() as $sql) {
            echo "  PDO <- {$sql}\n";
        }
        if ($expect !== null && $result !== $expect) {
            echo '  !! expected ', json_encode($expect), "\n";
            $failures++;
        }
    } catch (Throwable $e) {
        echo 'AFTER          ', $e::class, ': ', $e->getMessage(), "\n";
        $failures++;
    }
    echo "\n";

    \Phalcon\Di\Di::reset();
};

$names = static fn (iterable $rows): array => array_map(static fn ($r) => $r->name, iterator_to_array($rows, false));

// E1 - works today, keeps working ---------------------------------------------------------------
$example('E1', 'find() with a function in the condition: works today, keeps working',
    fn () => $names(Users::find(["created_at > datetime('now', '-7 days')", 'order' => 'name'])),
    fn () => $names(Users::findNative(["created_at > datetime('now', '-7 days')", 'order' => 'name'])),
    ['Ana', 'Cleo'],
    beforeFails: false,
);

// E2 - UNION inside a condition -------------------------------------------------------------------
$e2 = [
    'id IN (SELECT user_id FROM orders WHERE total > :min: UNION SELECT :vip:)',
    'bind'  => ['min' => 40, 'vip' => 3],
    'order' => 'name',
];
$example('E2', 'UNION inside a find() condition: big spenders plus one VIP',
    fn () => $names(Users::find($e2)),
    fn () => $names(Users::findNative($e2)),
    ['Ana', 'Cleo', 'Dan'],
);

// E3 - searched CASE in ORDER BY ------------------------------------------------------------------
$e3 = ['order' => "CASE WHEN country = 'BG' THEN 0 ELSE 1 END, name"];
$example('E3', 'searched CASE in order: Bulgarian users first',
    fn () => $names(Users::find($e3)),
    fn () => $names(Users::findNative($e3)),
    ['Ana', 'Cleo', 'Ben', 'Dan'],
);

// E4 - window function in columns -------------------------------------------------------------------
$e4 = [
    'columns' => 'name, country, ROW_NUMBER() OVER (PARTITION BY country ORDER BY created_at) AS nth_in_country',
    'order'   => 'country, nth_in_country',
];
$example('E4', 'window function in columns: signup order per country (rows, not models)',
    fn () => Users::find($e4)->toArray(),
    fn () => Users::findNative($e4)->toArray(),
    [
        ['name' => 'Ana', 'country' => 'BG', 'nth_in_country' => 1],
        ['name' => 'Cleo', 'country' => 'BG', 'nth_in_country' => 2],
        ['name' => 'Dan', 'country' => 'JP', 'nth_in_country' => 1],
        ['name' => 'Ben', 'country' => 'SE', 'nth_in_country' => 1],
    ],
);

// E5 - string concatenation --------------------------------------------------------------------------
$e5 = ["name || '@' || country = :tag:", 'bind' => ['tag' => 'Dan@JP']];
$example('E5', 'string concatenation || in a condition',
    fn () => $names(Users::find($e5)),
    fn () => $names(Users::findNative($e5)),
    ['Dan'],
);

// E6 - CTE into real models -----------------------------------------------------------------------------
$example('E6', 'findBySql(): a CTE hydrated into real Users models, then saved',
    fn () => Phalcon\Mvc\Model\Query\Lang::parsePHQL(
        'WITH big AS (SELECT o.user_id FROM [' . Phalcon\NativeSql\Tests\Fixtures\Orders::class . '] o WHERE o.total > 40) SELECT u.* FROM [' . Users::class . '] u'
    ),
    function () {
        $users = Users::findBySql(
            'WITH big_spenders AS (
                 SELECT user_id, SUM(total) AS spent FROM orders GROUP BY user_id HAVING SUM(total) > :min
             )
             SELECT u.* FROM users u JOIN big_spenders b ON b.user_id = u.id ORDER BY b.spent DESC',
            ['min' => 40],
            ['min' => Column::BIND_PARAM_INT], // SQLite: SUM(...) > '40' (text) is false, same as with PHQL today
        );
        $out = [];
        foreach ($users as $user) {
            $out[] = $user::class . '#' . $user->id . ' ' . $user->name;
        }
        $first = $users->getFirst();
        $first->country = 'GR';
        $out[] = 'save(): ' . var_export($first->save(), true) . ', changed: ' . implode(',', $first->getUpdatedFields());

        return $out;
    },
    ['Phalcon\NativeSql\Tests\Fixtures\Users#1 Ana', 'Phalcon\NativeSql\Tests\Fixtures\Users#4 Dan', 'save(): true, changed: country'],
);

// E7 - the "my own complicated report" case -------------------------------------------------------------
$report = <<<'SQL'
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
$example('E7', 'nativeQuery(): my own complicated report -> rows I can foreach / print_r',
    fn () => \Phalcon\Di\Di::getDefault()->getShared('modelsManager')->executeQuery($report, ['active' => 1])->toArray(),
    function () use ($report) {
        $rows = NativeSql::rows($report, ['active' => 1], ['active' => Column::BIND_PARAM_INT]);

        ob_start();
        foreach ($rows as $row) {
            echo "{$row->country}: {$row->revenue} from {$row->orders} orders, top customer {$row['top_customer']}\n";
        }
        $foreach = ob_get_clean();

        $myOwnDataArray = $rows->toArray();
        ob_start();
        print_r($myOwnDataArray[0]);
        $printed = ob_get_clean();

        echo "foreach output:\n{$foreach}\nprint_r(\$myOwnDataArray[0]):\n{$printed}\n";

        return [
            'rows'                       => count($myOwnDataArray),
            'row class'                  => $rows->getFirst()::class,
            'same query, $db->fetchAll()' => \Phalcon\Di\Di::getDefault()->getShared('db')->fetchAll($report, Enum::FETCH_ASSOC, ['active' => 1]) === $myOwnDataArray,
        ];
    },
    ['rows' => 3, 'row class' => 'Phalcon\Mvc\Model\Row', 'same query, $db->fetchAll()' => true],
);

// E8 - columnMap still applies ------------------------------------------------------------------------------
$e8 = ["CASE WHEN name LIKE 'A%' THEN 1 ELSE 0 END = 1 AND createdAt IS NOT NULL"];
$example('E8', 'model with a columnMap: property names inside new SQL still map to columns',
    fn () => $names(Customers::find($e8)),
    function () use ($e8) {
        return [
            'names' => $names = array_map(static fn ($c) => $c->name, iterator_to_array(Customers::findNative($e8), false)),
            'sql'   => NativeSql::compiler()->compile(Customers::class, $e8)->sql,
        ];
    },
    null,
);

// E9 - MySQL syntax: shown compiled, not executed (SQLite here) ------------------------------------------------
$e9 = ['created_at > NOW() - INTERVAL 7 DAY AND email REGEXP :re:', 'bind' => ['re' => '^a']];
$example('E9', 'MySQL-only syntax (INTERVAL, REGEXP): refused today, passed through unchanged after',
    fn () => $names(Users::find($e9)),
    fn () => NativeSql::compiler()->compile(Users::class, $e9)->sql,
    'SELECT "users"."id", "users"."name", "users"."email", "users"."country", "users"."active", "users"."created_at" FROM "users" WHERE created_at > NOW() - INTERVAL 7 DAY AND email REGEXP :re',
);

// E10 - what changes: errors come from the database ---------------------------------------------------------------
$example('E10', 'typo in a column name: Phalcon error today, database error after',
    fn () => $names(Users::find(['nmae = :n:', 'bind' => ['n' => 'Ana']])),
    function () {
        try {
            Users::findNative(['nmae = :n:', 'bind' => ['n' => 'Ana']]);
        } catch (Throwable $e) {
            return (new ReflectionClass($e))->getShortName() . ': ' . $e->getMessage();
        }

        return 'no error';
    },
    'PDOException: SQLSTATE[HY000]: General error: 1 no such column: nmae',
);

if ($only === null) {
    echo $failures === 0 ? "all examples behave as documented\n" : "{$failures} example(s) do NOT behave as documented\n";
}
exit($failures === 0 ? 0 : 1);

function shorten(string $message): string
{
    $message = preg_replace('/, when (parsing|preparing): .*/s', '', $message);

    return mb_strimwidth(preg_replace('/\s+/', ' ', $message), 0, 110, '…');
}
