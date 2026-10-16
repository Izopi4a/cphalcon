<?php

/**
 * ./spin cli.php [title filter] [-v]
 *
 * Runs every scenario on the PHQL path and on the native compiler and prints
 * the verdict, the SQL each path sent and (with -v) the results.
 */

declare(strict_types=1);

require __DIR__ . '/bootstrap.php';
require __DIR__ . '/runner.php';

$args    = array_slice($argv, 1);
$verbose = in_array('-v', $args, true);
$filter  = array_values(array_filter($args, fn ($a) => $a !== '-v'))[0] ?? null;

$di = spinDi();
warmMetadata();

$colors = ['same' => 32, 'native-only' => 36, 'api' => 35, 'differs' => 33, 'REGRESSION' => 31, 'both-fail' => 31];
$group  = null;
$tally  = [];

foreach (runAll($di, $filter) as $s) {
    if ($s['group'] !== $group) {
        $group = $s['group'];
        echo "\n\033[1m== {$group}\033[0m\n";
    }
    $tally[$s['verdict']] = ($tally[$s['verdict']] ?? 0) + 1;

    printf("\n\033[%dm[%s]\033[0m #%d %s\n", $colors[$s['verdict']], $s['verdict'], $s['index'], $s['title']);

    foreach (['phql' => 'PHQL  ', 'native' => 'native'] as $key => $label) {
        $run = $s[$key];
        if ($run === null) {
            continue;
        }
        if (!$run['ok']) {
            printf("  %s \033[31m%s\033[0m\n", $label, $run['error']);
        }
        foreach ($run['sql'] as $q) {
            printf("  %s %s\n", $label, preg_replace('/\s+/', ' ', $q['sql']));
        }
    }

    if ($verbose && $s['native']['ok']) {
        echo '  result ', json_encode($s['native']['result'], JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES), "\n";
    }
}

echo "\n";
foreach ($tally as $verdict => $n) {
    printf("\033[%dm%s\033[0m: %d  ", $colors[$verdict], $verdict, $n);
}
echo "\n";
