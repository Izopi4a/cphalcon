<?php
/**
 * Where the time of a find() goes, today vs the compiled path, for a correct query.
 *
 * SQLite in-memory: the database work is near zero, so framework overhead shows up as large as
 * it ever will. Over a network (MySQL/PG) every case below gets the same round trip added on top.
 *
 *   PHQL cold   a PHQL string not seen yet in this request: Builder string, C parse, prepare
 *               (metadata), Dialect, execute, hydrate. In production (PHP-FPM) this is every
 *               query's first run in each request: the AST cache dies in PHP_RSHUTDOWN
 *               (ext/phalcon.c:1384) and the IR cache is a static property of an internal
 *               class, which PHP also resets per request.
 *   PHQL warm   the same PHQL string again in the same request (AST + IR cache hits)
 *   native      the prototype: FindCompiler (plain PHP) + Dialect + execute + hydrate
 *   floor       $db->query() + fetch of the same SQL: the adapter + PDO + SQLite, no ORM
 *
 * Usage: ./run.sh bench [iterations]   (clean PHP: no Xdebug/pcov, opcache + JIT on; see run.sh)
 */
declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Db\Enum;
use Phalcon\Mvc\Model\Query\Lang;
use Phalcon\NativeSql\NativeSql;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Users;

$n        = (int) ($argv[1] ?? 3000);
$fixtures = new Database();
$fixtures->db->setEventsManager(new \Phalcon\Events\Manager()); // drop the query log listener
$manager  = $fixtures->di->getShared('modelsManager');

$params = static fn (int $i): array => [
    // the "AND id > -$i" term makes every iteration a NEW PHQL string (cold) when $i varies,
    // without changing the result
    'conditions' => "country = :c: AND active = :a: AND id > -{$i}",
    'bind'       => ['c' => 'BG', 'a' => 1],
    'order'      => 'name',
    'limit'      => 10,
];

$hydrate = static function (iterable $rows): int {
    $n = 0;
    foreach ($rows as $row) {
        $n += strlen($row->name); // touch a property so every row is really hydrated
    }

    return $n;
};

/**
 * Median microseconds per call over 5 batches. Every call of every stage gets a number no other
 * call has used, so "new PHQL string" stages never hit an AST/IR cache filled by another stage.
 */
$bench = static function (string $label, callable $fn) use ($n): float {
    static $stage = 0;
    $base = ++$stage * 10_000_000;
    $fn($base); // warm metadata / autoload
    $batches = [];
    for ($b = 0; $b < 5; $b++) {
        $start = hrtime(true);
        for ($i = 1; $i <= $n; $i++) {
            $fn($base + $b * $n + $i);
        }
        $batches[] = (hrtime(true) - $start) / 1000 / $n;
    }
    sort($batches);
    printf("  %-44s %8.1f µs\n", $label, $batches[2]);

    return $batches[2];
};

$sameSql = NativeSql::compiler()->compile(Users::class, $params(1));

printf("PHP %s, opcache %s, JIT %s, %d iterations x 5 batches, median\n\n", PHP_VERSION,
    ini_get('opcache.enable_cli') ? 'on' : 'off', (ini_get('opcache.jit') && ini_get('opcache.jit') !== 'disable' && ini_get('opcache.enable_cli')) ? ini_get('opcache.jit') : 'off', $n);

echo "Whole find() (query + fully hydrated result):\n";
$cold   = $bench('PHQL cold   (new PHQL string)', fn (int $i) => $hydrate(Users::find($params($i))));
$warm   = $bench('PHQL warm   (same PHQL string)', fn (int $i) => $hydrate(Users::find($params(1))));
$native = $bench('native      (prototype, PHP compiler)', fn (int $i) => $hydrate(Users::findNative($params($i))));
$floor  = $bench('floor       ($db->query + fetch, no ORM)', function (int $i) use ($fixtures, $sameSql): int {
    $result = $fixtures->db->query($sameSql->sql, $sameSql->bind, $sameSql->bindTypes);
    $result->setFetchMode(Enum::FETCH_ASSOC);
    $n = 0;
    while ($row = $result->fetch()) {
        $n += strlen($row['name']);
    }

    return $n;
});

echo "\nPHQL cold, by stage (one stage at a time, new string each call):\n";
$sBuilder = $bench('Builder::getPhql()', fn (int $i) => $manager->createBuilder($params($i))->from(Users::class)->getPhql());
$phqls    = [];
$sParse   = $bench('C parser alone: Lang::parsePHQL()', function (int $i) use ($manager, $params): array {
    return Lang::parsePHQL('SELECT [' . Users::class . "].* FROM [" . Users::class . "] WHERE country = :c: AND active = :a: AND id > -{$i} ORDER BY name LIMIT :APL0:");
});
$phqlOf   = static fn (int $i): string => 'SELECT [' . Users::class . "].* FROM [" . Users::class . "] WHERE country = :c: AND active = :a: AND id > -{$i} ORDER BY name LIMIT :APL0:";
$sPrepare = $bench('C parse + prepare to IR: Query->parse()', fn (int $i) => (new \Phalcon\Mvc\Model\Query($phqlOf($i), $fixtures->di))->parse());
$sToSql   = $bench('Builder + parse + prepare + Dialect (getSql)', fn (int $i) => $manager->createBuilder($params($i))->from(Users::class)->getQuery()->getSql());
$sToSqlW  = $bench('  same, warm (same string every call)', fn (int $i) => $manager->createBuilder($params(1))->from(Users::class)->getQuery()->getSql());

echo "\nnative, by stage:\n";
$sCompile = $bench('FindCompiler::compile() (PHP, incl. Dialect)', fn (int $i) => NativeSql::compiler()->compile(Users::class, $params($i)));
$bench('  of which: modelsManager->load(Users)', fn (int $i) => $manager->load(Users::class));
$rewriter = new \Phalcon\NativeSql\Compiler\FragmentRewriter(null, ['users'], Users::class, 'users');
$bench('  of which: FragmentRewriter (PHP char scan)', fn (int $i) => $rewriter->rewrite("country = :c: AND active = :a: AND id > -{$i}"));
$definition = $sameSql->definition;
$dialect    = $fixtures->db->getDialect();
$bench('  of which: Dialect::select(definition)', fn (int $i) => $dialect->select($definition));
$sExec    = $bench('execute + hydrate (same as PHQL path)', fn (int $i) => $hydrate(NativeSql::execute($sameSql)));

printf("\nSummary\n");
printf("  framework overhead over the floor:  PHQL cold %+.1f µs, PHQL warm %+.1f µs, native %+.1f µs\n", $cold - $floor, $warm - $floor, $native - $floor);
printf("  getting to SQL:                     PHQL cold %.1f µs (C parser alone %.1f, parse+prepare %.1f), PHQL warm %.1f µs, native compile %.1f µs\n", $sToSql, $sParse, $sPrepare, $sToSqlW, $sCompile);
printf("  execute + hydrate (shared by both):  %.1f µs\n", $sExec);


// PHQL keeps every distinct PHQL string's AST (C, orm.parser_cache) and IR (Query::$internalPhqlCache)
// until request shutdown. In PHP-FPM that is per request; in a long-running worker (queue
// consumer, Swoole, RoadRunner, FrankenPHP worker mode) it is the life of the process.
$distinct = 5000;
gc_collect_cycles();
$before = memory_get_usage();
for ($i = 1; $i <= $distinct; $i++) {
    Users::find(['conditions' => "id = {$i}"]); // a literal in the string: every call is a new PHQL string
}
gc_collect_cycles();
$phqlGrowth = memory_get_usage() - $before;
$before = memory_get_usage();
for ($i = 1; $i <= $distinct; $i++) {
    Users::findNative(['conditions' => "id = {$i}"]);
}
gc_collect_cycles();
printf("  memory kept after %d distinct find() strings: PHQL %+.1f MB (%.1f KB each), native %+.1f MB\n",
    $distinct, $phqlGrowth / 1048576, $phqlGrowth / $distinct / 1024, (memory_get_usage() - $before) / 1048576);

\Phalcon\Di\Di::reset();
