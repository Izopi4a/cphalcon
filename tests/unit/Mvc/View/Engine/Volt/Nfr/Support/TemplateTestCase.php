<?php

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Nfr\Support;

use Phalcon\Di\FactoryDefault;
use Phalcon\Mvc\View\Engine\Volt as StockVolt;
use Phalcon\Mvc\View\Simple;
use Phalcon\Mvc\View\Engine\Volt as NfrVolt;
use PHPUnit\Framework\TestCase;

/**
 * Writes templates to a temporary views directory and renders them through
 * View\Simple + a Volt engine: the stock one (tests/Today, stock .so) or the
 * prototype (tests/Prototype, patched .so).
 */
abstract class TemplateTestCase extends TestCase
{
    /** @var class-string<StockVolt> */
    protected string $engine = NfrVolt::class;

    protected string $dir = '';

    protected FactoryDefault $di;

    protected function setUp(): void
    {
        $this->dir = sys_get_temp_dir() . '/volt-nfr-' . bin2hex(random_bytes(6)) . '/';
        mkdir($this->dir . 'cache', 0777, true);
        $this->di = new FactoryDefault();
    }

    protected function tearDown(): void
    {
        $files = new \RecursiveIteratorIterator(
            new \RecursiveDirectoryIterator($this->dir, \FilesystemIterator::SKIP_DOTS),
            \RecursiveIteratorIterator::CHILD_FIRST
        );
        foreach ($files as $file) {
            $file->isDir() ? rmdir($file->getPathname()) : unlink($file->getPathname());
        }
        rmdir($this->dir);
    }

    /**
     * @param array<string, string> $files name (without .volt) => source
     */
    protected function views(array $files): void
    {
        foreach ($files as $name => $source) {
            $path = $this->dir . $name . '.volt';
            @mkdir(dirname($path), 0777, true);
            file_put_contents($path, $source);
            // older than any compiled file: stat compares mtimes with >=
            touch($path, time() - 3600);
        }
        clearstatcache();
    }

    /**
     * Rewrites a template later, with a newer mtime.
     */
    protected function edit(string $name, string $source): void
    {
        $path = $this->dir . $name . '.volt';
        file_put_contents($path, $source);
        touch($path, time() + 10);
        clearstatcache();
    }

    /**
     * @param callable(StockVolt): void|null $setup
     */
    protected function render(string $view, array $params = [], array $options = [], ?callable $setup = null): string
    {
        $di     = $this->di;
        $dir    = $this->dir;
        $engine = $this->engine;

        $simple = new Simple();
        $simple->setDI($di);
        $simple->setViewsDir($dir);
        // not static: Phalcon binds engine factories to the container
        $simple->registerEngines([
            '.volt' => function ($view) use ($di, $dir, $engine, $options, $setup) {
                $volt = new $engine($view, $di);
                $volt->setOptions($options + ['path' => $dir . 'cache/', 'always' => false, 'stat' => true]);
                if ($setup !== null) {
                    $setup($volt);
                }

                return $volt;
            },
        ]);

        // View\Simple leaves its buffers open when a template throws
        $level = ob_get_level();
        try {
            return $simple->render($view, $params);
        } finally {
            while (ob_get_level() > $level) {
                ob_end_clean();
            }
        }
    }

    /**
     * Compiled PHP for a template string.
     *
     * @param callable(StockVolt): void|null $setup
     */
    protected function compile(string $source, array $options = [], ?callable $setup = null): string
    {
        $simple = new Simple();
        $simple->setViewsDir($this->dir);

        $volt = new ($this->engine)($simple, $this->di);
        $volt->setOptions($options);
        if ($setup !== null) {
            $setup($volt);
        }

        return $volt->getCompiler()->compileString($source);
    }

    protected function assertThrowsMessage(string $fragment, callable $callback): void
    {
        try {
            $callback();
        } catch (\Throwable $e) {
            $this->assertStringContainsString($fragment, $e->getMessage(), get_class($e));

            return;
        }

        $this->fail("Expected an exception containing: $fragment");
    }
}
