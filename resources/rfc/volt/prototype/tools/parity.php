<?php

/**
 * Parity check: compile every Volt template of the upstream test fixtures
 * (tests/support/assets/views) with the stock compiler and with the
 * prototype compiler, and compare the compiled PHP.
 *
 *   ./run.sh tools/parity.php [--diff]
 *
 * Exits 1 when a template compiles differently and the difference is not
 * in the list of expected differences below.
 */

declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Mvc\View\Engine\Volt\Compiler as StockCompiler;
use Phalcon\Mvc\View;
use Phalcon\VoltNfr\Compiler as NfrCompiler;

$root     = dirname(__DIR__, 5);
$viewsDir = $root . '/tests/support/assets/views/';
$showDiff = in_array('--diff', $argv, true);

/**
 * Expected differences, with the reason. Everything else must be identical.
 */
$expected = [];

$compile = static function (string $class, string $file) use ($viewsDir): array {
    $cache = sys_get_temp_dir() . '/volt-parity-' . getmypid() . '-' . md5($class) . '/';
    @mkdir($cache, 0777, true);

    // some fixtures name their parents from the repository root
    $view = new View();
    $view->setViewsDir([$viewsDir, $viewsDir . 'blocks/', dirname($viewsDir, 4) . '/']);

    /** @var StockCompiler $compiler */
    $compiler = new $class($view);
    $compiler->setOptions(['path' => $cache, 'always' => true]);

    try {
        $result = $compiler->compile($file);
        $code   = is_string($result) ? $result : file_get_contents($compiler->getCompiledTemplatePath());

        return ['ok', $code];
    } catch (Throwable $e) {
        return ['error', get_class($e) . ': ' . preg_replace('/ in .* on line \d+$/', '', $e->getMessage())];
    }
};

$files = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($viewsDir, FilesystemIterator::SKIP_DOTS));
$list  = [];
foreach ($files as $file) {
    if (str_ends_with($file->getFilename(), '.volt')) {
        $list[] = substr($file->getPathname(), strlen($viewsDir));
    }
}
sort($list);

$counts     = ['identical' => 0, 'expected' => 0, 'different' => 0, 'same error' => 0];
$unexpected = 0;

foreach ($list as $relative) {
    [$stockStatus, $stock] = $compile(StockCompiler::class, $viewsDir . $relative);
    [$nfrStatus, $nfr]     = $compile(NfrCompiler::class, $viewsDir . $relative);

    if ($stockStatus === 'error' && $nfrStatus === 'error' && $stock === $nfr) {
        $verdict = 'same error';
    } elseif ($stockStatus === $nfrStatus && $stock === $nfr) {
        $verdict = 'identical';
    } elseif (isset($expected[$relative])) {
        $verdict = 'expected';
    } else {
        $verdict = 'different';
        $unexpected++;
    }

    $counts[$verdict]++;
    printf("%-11s %s%s\n", $verdict, $relative, $verdict === 'expected' ? '  (' . $expected[$relative] . ')' : '');

    if ($verdict === 'different' || ($showDiff && $verdict === 'expected')) {
        printf("    stock [%s]: %s\n    nfr   [%s]: %s\n", $stockStatus, substr(trim($stock), 0, 400), $nfrStatus, substr(trim($nfr), 0, 400));
    }
}

echo PHP_EOL, count($list), ' templates: ';
echo implode(', ', array_map(static fn ($k, $v) => "$v $k", array_keys($counts), $counts)), PHP_EOL;

exit($unexpected > 0 ? 1 : 0);
