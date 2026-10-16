<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Today;

use Phalcon\Mvc\View\Engine\Volt;
use Phalcon\Mvc\View\Engine\Volt\Exceptions\InvalidUserFunctionDefinition;
use Phalcon\VoltNfr\Tests\Fixtures\Html;
use Phalcon\VoltNfr\Tests\Fixtures\Money;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;

/**
 * Declaring functions, filters and tests on the stock build. A user function
 * is a compile-time code generator: the closure runs once, receives the
 * arguments as compiled PHP source, and must return PHP source.
 */
final class ExtensionApiTodayTest extends TemplateTestCase
{
    protected string $engine = Volt::class;

    public function testStringDefinitionIsPastedAsAFunctionName(): void
    {
        $code = $this->compile('{{ money(total, "EUR") }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('money', Money::class . '::format');
        });

        $this->assertSame('<?= Phalcon\VoltNfr\Tests\Fixtures\Money::format($total, \'EUR\') ?>', $code);
    }

    /**
     * The closure receives "$total, 'EUR'" (PHP source) and the AST.
     */
    public function testClosureReceivesCompiledSourceAndMustReturnSource(): void
    {
        $seen = [];
        $code = $this->compile('{{ money(total, "EUR") }}', [], static function (Volt $volt) use (&$seen): void {
            $volt->getCompiler()->addFunction('money', static function (string $resolvedArgs, array $exprArgs) use (&$seen): string {
                $seen = [$resolvedArgs, $exprArgs[0]['expr']['type'], $exprArgs[1]['expr']['type']];

                return '\\' . Money::class . '::format(' . $resolvedArgs . ')';
            });
        });

        $this->assertSame(['$total, \'EUR\'', 265, 260], $seen);
        $this->assertSame('<?= \Phalcon\VoltNfr\Tests\Fixtures\Money::format($total, \'EUR\') ?>', $code);
    }

    /**
     * The common mistake: computing a value instead of returning code. The
     * value is frozen into the compiled file.
     */
    public function testClosureValueIsBakedIntoTheCompiledTemplate(): void
    {
        $code = $this->compile('{{ year() }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('year', static fn (): string => date('Y'));
        });

        $this->assertSame('<?= ' . date('Y') . ' ?>', $code);
    }

    /**
     * Returning something that is not PHP compiles fine and breaks later,
     * when the compiled file is required.
     */
    public function testNonPhpReturnValueCompilesToInvalidCode(): void
    {
        $code = $this->compile('{{ greeting(name) }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('greeting', static fn (string $args): string => 'Hello ' . $args);
        });

        $this->assertSame('<?= Hello $name ?>', $code);
    }

    public function testArrayCallableIsRejected(): void
    {
        $this->expectException(InvalidUserFunctionDefinition::class);

        $this->compile('{{ money(1) }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('money', [Money::class, 'format']);
        });
    }

    /**
     * A first-class callable is a Closure, so it is called as a code
     * generator, at compile time, with PHP source as its argument.
     */
    public function testFirstClassCallableIsCalledAsACodeGenerator(): void
    {
        $code = $this->compile('{{ bold(name) }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('bold', Html::bold(...));
        });

        $this->assertSame('<?= <b>$name</b> ?>', $code);
    }

    public function testUnknownFunctionCompilesToARuntimeMacroCall(): void
    {
        $this->assertSame('<?= $this->callMacro(\'mony\', [$total]) ?>', $this->compile('{{ mony(total) }}'));
    }

    /**
     * Named arguments become a PHP array literal inside a function call.
     */
    public function testNamedArgumentsCompileToInvalidCodeForFunctions(): void
    {
        $code = $this->compile('{{ money("currency": "EUR", "amount": total) }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('money', Money::class . '::format');
        });

        $this->assertSame('<?= Phalcon\VoltNfr\Tests\Fixtures\Money::format(\'currency\' => \'EUR\', \'amount\' => $total) ?>', $code);
    }

    /**
     * There is no test API; an unknown test name silently becomes "==".
     */
    public function testUnknownTestsCompileToLooseEquality(): void
    {
        $this->assertSame('<?php if ($user == $premium) { ?>P<?php } ?>', $this->compile('{% if user is premium %}P{% endif %}'));
        $this->assertSame('<?= $a == null ?>', $this->compile('{{ a is null }}'));
    }

    /**
     * "is not" is lexed as "!=", so negating a function test breaks.
     */
    public function testIsNotWithAFunctionTestBecomesInequality(): void
    {
        $this->assertSame('<?= ((($a) % (3)) == 0) ?>', $this->compile('{{ a is divisibleby(3) }}'));
        $this->assertSame('<?= $a != $this->callMacro(\'divisibleby\', [3]) ?>', $this->compile('{{ a is not divisibleby(3) }}'));
    }
}
