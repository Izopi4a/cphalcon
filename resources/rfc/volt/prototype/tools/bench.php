<?php

/**
 * Per-call cost of a template function, compiled five ways:
 *   inline     today's addFunction('fmt', 'number_format'): fmt(x) -> \number_format($x)
 *   static     runtime VoltFunction with a static callable: compiled to the same direct call
 *   closure    runtime VoltFunction with a closure: a registry lookup memoized on the engine
 *   service    runtime VoltFunction [service, method]: same lookup, instance from DI once
 *   today-di   the same service call with today's compile-time API:
 *              $this->getDI()->getShared("formatter")->fmt($x)
 *
 *   ./run.sh bench [calls]
 *
 * Numbers include the template loop itself; compare the rows, not the
 * absolute values. ./run.sh bench runs it on a clean PHP (no Xdebug, JIT on).
 */

declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Di\FactoryDefault;
use Phalcon\Mvc\View\Simple;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Volt;

final class BenchFormatter
{
    public function fmt(float $n): string
    {
        return number_format($n, 2);
    }
}

$calls = (int) ($argv[1] ?? 100000);
$dir   = sys_get_temp_dir() . '/volt-bench-' . getmypid() . '/';
@mkdir($dir . 'cache', 0777, true);
file_put_contents($dir . 'loop.volt', '{% for i in 1..calls %}{{ fmt(i) }}{% endfor %}');

$variants = [
    'inline'  => static fn (Volt $v) => $v->getCompiler()->addFunction('fmt', 'number_format'),
    'static'  => static fn (Volt $v) => $v->addFunction(new VoltFunction('fmt', 'number_format')),
    'closure' => static fn (Volt $v) => $v->addFunction(new VoltFunction('fmt', static fn (float $n): string => number_format($n, 2))),
    'service' => static fn (Volt $v) => $v->addFunction(new VoltFunction('fmt', ['formatter', 'fmt'])),
    // the same service call written with today's compile-time API
    'today-di' => static fn (Volt $v) => $v->getCompiler()->addFunction(
        'fmt',
        static fn (string $args): string => '$this->getDI()->getShared("formatter")->fmt(' . $args . ')'
    ),
];

printf("%-9s %12s %14s  %s\n", 'variant', 'ms total', 'ns per call', 'compiled');
foreach ($variants as $name => $setup) {
    $di = new FactoryDefault();
    $di->setShared('formatter', BenchFormatter::class);

    $view = new Simple();
    $view->setDI($di);
    $view->setViewsDir($dir);
    $view->registerEngines([
        '.volt' => function ($v) use ($di, $dir, $setup, $name) {
            $volt = new Volt($v, $di);
            $volt->setOptions(['path' => $dir . 'cache/' . $name . '-', 'always' => false]);
            $setup($volt);

            return $volt;
        },
    ]);

    $view->render('loop', ['calls' => 10]); // compile + warm up
    $best = INF;
    for ($run = 0; $run < 5; $run++) {
        $start = hrtime(true);
        $view->render('loop', ['calls' => $calls]);
        $best = min($best, hrtime(true) - $start);
    }

    $compiled = file_get_contents(glob($dir . 'cache/' . $name . '-*loop.volt.php')[0]);
    preg_match('/<\?= (.*?) \?>/', $compiled, $m);
    printf("%-9s %12.1f %14.1f  %s\n", $name, $best / 1e6, $best / $calls, $m[1] ?? '?');
}
