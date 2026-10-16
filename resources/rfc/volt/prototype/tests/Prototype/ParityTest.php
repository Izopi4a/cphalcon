<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\Mvc\View;
use Phalcon\Mvc\View\Engine\Volt\Compiler as StockCompiler;
use Phalcon\VoltNfr\Compiler as NfrCompiler;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

/**
 * Every Volt template of the upstream test fixtures compiles to the same PHP
 * with the prototype compiler (inheritance resolved on the AST) as with the
 * stock compiler (compiled-block splicing): extends chains, super(),
 * includes, macros, filters, switch. tools/parity.php prints the same check.
 */
final class ParityTest extends TestCase
{
    private const VIEWS = __DIR__ . '/../../../../../../tests/support/assets/views/';

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
    public function testCompilesLikeTheStockCompiler(string $template): void
    {
        $this->assertSame(
            $this->compile(StockCompiler::class, $template),
            $this->compile(NfrCompiler::class, $template)
        );
    }

    private function compile(string $class, string $template): string
    {
        $views = realpath(self::VIEWS) . '/';
        $cache = sys_get_temp_dir() . '/volt-parity-' . getmypid() . '-' . md5($class) . '/';
        @mkdir($cache, 0777, true);

        // fixtures name their parents relative to one of these roots
        $view = new View();
        $view->setViewsDir([$views, $views . 'blocks/', dirname($views, 4) . '/']);

        /** @var StockCompiler $compiler */
        $compiler = new $class($view);
        $compiler->setOptions(['path' => $cache, 'always' => true]);
        $result = $compiler->compile($views . $template);

        return is_string($result) ? $result : (string) file_get_contents($compiler->getCompiledTemplatePath());
    }
}
