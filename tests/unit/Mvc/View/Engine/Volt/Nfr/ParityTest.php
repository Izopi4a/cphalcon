<?php

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

declare(strict_types=1);

namespace Phalcon\Tests\Unit\Mvc\View\Engine\Volt\Nfr;

use Phalcon\Mvc\View;
use Phalcon\Mvc\View\Engine\Volt\Compiler;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

/**
 * Every Volt template of the upstream test fixtures compiles to the same PHP
 * as before inheritance moved to the AST. Fixtures/parity holds the output of
 * the compiler before the change (master's Volt), one file per template.
 */
final class ParityTest extends TestCase
{
    private const VIEWS = __DIR__ . '/../../../../../../support/assets/views/';

    /**
     * @return array<string, array{string}>
     */
    public static function fixtures(): array
    {
        $views = realpath(self::VIEWS) . '/';
        $list  = [];
        $files = new \RecursiveIteratorIterator(new \RecursiveDirectoryIterator($views, \FilesystemIterator::SKIP_DOTS));
        foreach ($files as $file) {
            if (str_ends_with($file->getFilename(), '.volt')) {
                $relative        = substr($file->getPathname(), strlen($views));
                $list[$relative] = [$relative];
            }
        }
        ksort($list);

        return $list;
    }

    #[DataProvider('fixtures')]
    public function testCompilesLikeBefore(string $template): void
    {
        $expected = (string) file_get_contents(
            __DIR__ . '/Fixtures/parity/' . str_replace('/', '__', $template) . '.txt'
        );

        $this->assertSame($expected, $this->compile($template));
    }

    private function compile(string $template): string
    {
        $views = realpath(self::VIEWS) . '/';
        $cache = sys_get_temp_dir() . '/volt-parity-' . getmypid() . '/';
        @mkdir($cache, 0777, true);

        // fixtures name their parents relative to one of these roots
        $view = new View();
        $view->setViewsDir([$views, $views . 'blocks/', dirname($views, 4) . '/']);

        $compiler = new Compiler($view);
        $compiler->setOptions(['path' => $cache, 'always' => true]);

        try {
            $result = $compiler->compile($views . $template);
        } catch (\Throwable $e) {
            return 'EXCEPTION: ' . get_class($e) . ': ' . $e->getMessage();
        }

        return is_string($result) ? $result : (string) file_get_contents($compiler->getCompiledTemplatePath());
    }
}
