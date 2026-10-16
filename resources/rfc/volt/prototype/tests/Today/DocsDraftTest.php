<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Today;

use Phalcon\Mvc\View\Engine\Volt;
use Phalcon\Mvc\View\Engine\Volt\Compiler;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;

/**
 * Every snippet of ../../docs-extending-volt.md, on the stock build: the
 * draft documents today's API, so each claim has to hold on 5.23.0.
 */
final class DocsDraftTest extends TemplateTestCase
{
    protected string $engine = Volt::class;

    private function compiler(array $options = []): Compiler
    {
        $compiler = new Compiler();
        $compiler->setOptions($options);

        return $compiler;
    }

    public function testReturnCodeNotValues(): void
    {
        $compiler = $this->compiler();
        $compiler->addFunction('year', fn () => date('Y'));
        $this->assertSame('<?= ' . date('Y') . ' ?>', $compiler->compileString('{{ year() }}'));

        $compiler = $this->compiler();
        $compiler->addFunction('year', fn () => 'date("Y")');
        $this->assertSame('<?= date("Y") ?>', $compiler->compileString('{{ year() }}'));
    }

    public function testStringDefinitions(): void
    {
        $compiler = $this->compiler();
        $compiler->addFunction('shuffle', 'str_shuffle');
        $compiler->addFunction('money', 'App\Money::format');

        $this->assertSame("<?= str_shuffle('abc') ?>", $compiler->compileString('{{ shuffle("abc") }}'));
        $this->assertSame("<?= App\\Money::format(\$total, 'EUR') ?>", $compiler->compileString('{{ money(total, "EUR") }}'));
    }

    public function testClosureArgumentsAndReturn(): void
    {
        $seen     = null;
        $compiler = $this->compiler();
        $compiler->addFunction('money', function (string $resolvedArgs, ?array $exprArgs) use (&$seen): string {
            $seen = [$resolvedArgs, $exprArgs[0]['expr']['type'], $exprArgs[0]['expr']['value'], $exprArgs[1]['expr']['type'], $exprArgs[1]['expr']['value']];

            return '\App\Money::format(' . $resolvedArgs . ')';
        });

        $this->assertSame("<?= \\App\\Money::format(\$total, 'EUR') ?>", $compiler->compileString('{{ money(total, "EUR") }}'));
        $this->assertSame(["\$total, 'EUR'", 265, 'total', 260, 'EUR'], $seen);
    }

    public function testExprArgsAreNullWithoutArguments(): void
    {
        $seen     = 'unset';
        $compiler = $this->compiler();
        $compiler->addFunction('now', function (string $resolvedArgs, ?array $exprArgs) use (&$seen): string {
            $seen = $exprArgs;

            return 'time()';
        });
        $compiler->compileString('{{ now() }}');

        $this->assertNull($seen);
    }

    public function testCompilingOneArgument(): void
    {
        $compiler = $this->compiler();
        $compiler->addFunction(
            'repeat',
            function (string $resolvedArgs, ?array $exprArgs) use ($compiler): string {
                $text  = $compiler->expression($exprArgs[0]['expr']);
                $times = $exprArgs[1]['expr']['value'] ?? '2';

                return 'str_repeat(' . $text . ', ' . (int) $times . ')';
            }
        );

        $this->assertSame('<?= str_repeat($name, 3) ?>', $compiler->compileString('{{ repeat(name, 3) }}'));
    }

    public function testCommonMistakeNamedArguments(): void
    {
        $compiler = $this->compiler();
        $compiler->addFunction('money', 'App\Money::format');

        $this->assertSame(
            "<?= App\\Money::format('currency' => 'EUR', 'amount' => \$total) ?>",
            $compiler->compileString("{{ money('currency': 'EUR', 'amount': total) }}")
        );
    }

    public function testCallingAService(): void
    {
        $compiler = $this->compiler();
        $compiler->addFunction(
            'price',
            fn (string $args): string => '$this->getDI()->getShared("prices")->format(' . $args . ')'
        );
        $this->assertSame('<?= $this->getDI()->getShared("prices")->format($total) ?>', $compiler->compileString('{{ price(total) }}'));

        $this->di->setShared('prices', fn () => new \stdClass());
        $compiler = $this->compiler();
        $compiler->setDI($this->di);
        $this->assertSame('<?= $this->prices->format($total) ?>', $compiler->compileString('{{ prices.format(total) }}'));

        $compiler = $this->compiler();
        $compiler->setDI(new \Phalcon\Di\Di());
        $this->assertSame('<?= $prices->format($total) ?>', $compiler->compileString('{{ prices.format(total) }}'));
    }

    public function testHtmlAndAutoescape(): void
    {
        $compiler = $this->compiler(['autoescape' => true]);
        $compiler->addFunction('badge', 'badge');

        $this->assertSame('<?= $this->escaper->html(badge($user)) ?>', $compiler->compileString('{{ badge(user) }}'));
        $this->assertSame('<?= $this->escaper->html($this->escaper->html($name)) ?>', $compiler->compileString('{{ name|e }}'));
        $this->assertSame('<?= badge($user) ?>', $compiler->compileString('{% autoescape false %}{{ badge(user) }}{% endautoescape %}'));
    }

    public function testFilters(): void
    {
        $compiler = $this->compiler();
        $compiler->addFilter('money', 'App\Money::format');
        $this->assertSame('<?= App\Money::format($total) ?>', $compiler->compileString('{{ total|money }}'));
        $this->assertSame("<?= App\\Money::format(\$total, 'USD') ?>", $compiler->compileString('{{ total|money("USD") }}'));

        $seen     = [];
        $compiler = $this->compiler();
        $compiler->addFilter('money', function (string $resolvedArgs, ?array $exprArgs) use (&$seen): string {
            $seen[] = [$resolvedArgs, $exprArgs === null];

            return '\App\Money::format(' . $resolvedArgs . ')';
        });
        $compiler->compileString('{{ total|money("USD") }}{{ total|money }}');
        $this->assertSame([["\$total, 'USD'", false], ['$total', true]], $seen);
    }

    public function testTests(): void
    {
        $compiler = $this->compiler();

        $this->assertSame('<?php if ($user == $premium) { ?>x<?php } ?>', $compiler->compileString('{% if user is premium %}x{% endif %}'));
        $this->assertSame('<?php if ($value == null) { ?>x<?php } ?>', $compiler->compileString('{% if value is null %}x{% endif %}'));
        $this->assertSame('<?php if (!isset($a)) { ?>x<?php } ?>', $compiler->compileString('{% if a is not defined %}x{% endif %}'));
    }

    public function testExtensionHooks(): void
    {
        $extension = new class () {
            public ?Compiler $compiler = null;

            public function initialize(Compiler $compiler): void
            {
                $this->compiler = $compiler;
            }

            public function resolveExpression(array $expr)
            {
                if ($expr['type'] === 311
                    && $expr['right']['type'] === 265
                    && $expr['right']['value'] === 'premium') {
                    return '\App\Users::isPremium(' . $this->compiler->expression($expr['left']) . ')';
                }

                return null;
            }
        };

        $compiler = $this->compiler();
        $compiler->addExtension($extension);

        $this->assertSame($compiler, $extension->compiler);
        $this->assertSame('<?php if (\App\Users::isPremium($user)) { ?>x<?php } ?>', $compiler->compileString('{% if user is premium %}x{% endif %}'));
    }

    public function testFirstExtensionReturningAStringWins(): void
    {
        $compiler = $this->compiler();
        $compiler->addExtension(new class () {
            public function compileFunction(string $name, string $args, ?array $exprArgs)
            {
                return $name === 'x' ? '"first"' : null;
            }
        });
        $compiler->addExtension(new class () {
            public function compileFunction(string $name, string $args, ?array $exprArgs)
            {
                return '"second"';
            }
        });

        $this->assertSame('<?= "first" ?>', $compiler->compileString('{{ x() }}'));
        $this->assertSame('<?= "second" ?>', $compiler->compileString('{{ y() }}'));
    }

    public function testNodeReference(): void
    {
        $compiler = $this->compiler();
        $expr     = static fn (string $source): array => $compiler->parse($source)[0]['expr'];

        $this->assertSame([258, 259, 260, 261, 262, 263, 265], [
            $expr('{{ 1 }}')['type'], $expr('{{ 1.5 }}')['type'], $expr('{{ "s" }}')['type'],
            $expr('{{ null }}')['type'], $expr('{{ false }}')['type'], $expr('{{ true }}')['type'], $expr('{{ a }}')['type'],
        ]);
        $this->assertSame([46, 124, 350, 360, 311, 273, 273], [
            $expr('{{ a.b }}')['type'], $expr('{{ a|f }}')['type'], $expr('{{ f(1) }}')['type'], $expr('{{ [1] }}')['type'],
            $expr('{{ a is b }}')['type'], $expr('{{ a != b }}')['type'], $expr('{{ a is not b }}')['type'],
        ]);
        $this->assertSame(350, $expr('{{ a|f(1) }}')['right']['type']);
        $this->assertSame('k', $expr('{{ f("k": 1) }}')['arguments'][0]['name']);
        $this->assertSame(359, $compiler->parse('{{ a }}')[0]['type']);
    }

    /**
     * Caching table: a changed function definition is not picked up.
     */
    public function testChangedDefinitionsAreNotRecompiled(): void
    {
        $this->views(['page' => '{{ label() }}']);
        $define = static fn (string $code): callable => static function (Volt $volt) use ($code): void {
            $volt->getCompiler()->addFunction('label', static fn (): string => $code);
        };

        $this->assertSame('v1', $this->render('page', [], [], $define('"v1"')));
        $this->assertSame('v1', $this->render('page', [], [], $define('"v2"')));
        $this->assertSame('v2', $this->render('page', [], ['always' => true], $define('"v2"')));
    }

    public function testCompileStringForTests(): void
    {
        $compiler = new Compiler();
        $compiler->addFunction('money', 'App\Money::format');

        $this->assertSame('<?= App\Money::format(1) ?>', $compiler->compileString('{{ money(1) }}'));
    }
}
