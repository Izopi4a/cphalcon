<?php

declare(strict_types=1);

use Phalcon\Support\Settings;

/**
 * Runs one scenario on one path and returns what happened
 *
 * @return array{ok: bool, result: mixed, error: ?string, sql: list<array>, ms: float}
 */
function runScenario(array $scenario, $di, bool $native): array
{
    Settings::set('orm.native_compiler', $native);
    SqlLog::reset();

    $db    = $di->getShared('db');
    $start = hrtime(true);

    try {
        $db->begin();
        $result = plain(($scenario['run'])($di));
        $db->commit();
        $error  = null;
    } catch (Throwable $e) {
        if ($db->isUnderTransaction()) {
            $db->rollback();
        }
        $result = null;
        $error  = (new ReflectionClass($e))->getShortName() . ': ' . $e->getMessage();
    }

    $ms  = (hrtime(true) - $start) / 1e6;
    $sql = array_values(array_filter(
        SqlLog::$entries,
        fn ($e) => !preg_match('/^(BEGIN|COMMIT|ROLLBACK|SAVEPOINT|RELEASE)/i', $e['sql'])
    ));

    Settings::set('orm.native_compiler', true);

    return ['ok' => $error === null, 'result' => $result, 'error' => $error, 'sql' => $sql, 'ms' => $ms];
}

/**
 * The source of a scenario's closure, as written in scenarios.php
 */
function scenarioSource(array $scenario): string
{
    $fn    = new ReflectionFunction($scenario['run']);
    $lines = file($fn->getFileName());
    $code  = implode('', array_slice($lines, $fn->getStartLine() - 1, $fn->getEndLine() - $fn->getStartLine() + 1));
    $code  = preg_replace('/^\s*\'run\'\s*=>\s*/', '', $code);
    $code  = rtrim($code, ", \n");

    // drop the common indentation
    preg_match_all('/^( *)\S/m', $code, $m);
    $indent = min(array_map('strlen', array_slice($m[1], 1) ?: ['']));
    return preg_replace('/^ {0,' . $indent . '}/m', '', $code);
}

/**
 * Runs every scenario on both paths
 *
 * @return list<array>
 */
function runAll($di, ?string $filter = null): array
{
    $scenarios = require __DIR__ . '/scenarios.php';
    $out       = [];

    foreach ($scenarios as $index => $scenario) {
        if ($filter !== null && stripos($scenario['title'], $filter) === false) {
            continue;
        }
        $native = runScenario($scenario, $di, true);
        $phql   = empty($scenario['api']) ? runScenario($scenario, $di, false) : null;

        $verdict = match (true) {
            $phql === null                       => 'api',
            $phql['ok'] && $native['ok']
                && $phql['result'] == $native['result'] => 'same',
            !$phql['ok'] && $native['ok']        => 'native-only',
            $phql['ok'] && !$native['ok']        => 'REGRESSION',
            !$phql['ok'] && !$native['ok']       => 'both-fail',
            default                              => 'differs',
        };

        $out[] = $scenario + [
            'index'   => $index + 1,
            'source'  => scenarioSource($scenario),
            'native'  => $native,
            'phql'    => $phql,
            'verdict' => $verdict,
        ];
    }

    return $out;
}
