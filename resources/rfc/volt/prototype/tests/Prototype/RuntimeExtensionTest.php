<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\VoltNfr\Runtime\VoltFilter;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Runtime\VoltTest;
use Phalcon\VoltNfr\Tests\Fixtures\Money;
use Phalcon\VoltNfr\Tests\Fixtures\PriceFormatter;
use Phalcon\VoltNfr\Tests\Fixtures\ShopExtension;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;
use Phalcon\VoltNfr\Volt;

/**
 * Runtime functions, filters and tests: a PHP callable that runs at render
 * time with the evaluated arguments. Compare tests/Today/ExtensionApiTodayTest.
 */
final class RuntimeExtensionTest extends TemplateTestCase
{
    protected function setUp(): void
    {
        parent::setUp();
        PriceFormatter::$instances = 0;
    }

    public function testStaticCallableCompilesToADirectCall(): void
    {
        $code = $this->compile('{{ money(total, "EUR") }}', [], static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('money', [Money::class, 'format']));
        });

        $this->assertSame('<?= \Phalcon\VoltNfr\Tests\Fixtures\Money::format($total, \'EUR\') ?>', $code);
    }

    /**
     * The year() trap from tests/Today: a closure is called at render time,
     * every time, instead of being frozen into the compiled file.
     */
    public function testClosureRunsAtRenderTimeEveryTime(): void
    {
        $calls = 0;
        $setup = static function (Volt $volt) use (&$calls): void {
            $volt->addFunction(new VoltFunction('counter', static function () use (&$calls): int {
                return ++$calls;
            }));
        };

        $this->views(['page' => '{{ counter() }},{{ counter() }}']);

        $this->assertSame('1,2', $this->render('page', [], [], $setup));
        $this->assertSame('3,4', $this->render('page', [], [], $setup));
        $this->assertSame('<?= ($this->runtime[\'function:counter\'] ??= $this->getRuntimeFunction(\'counter\'))() ?>', $this->compile('{{ counter() }}', [], $setup));
    }

    public function testFirstClassCallableAndInvokableObject(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('upper', strtoupper(...)));
            $volt->addFunction(new VoltFunction('wrap', new class () {
                public function __invoke(string $s): string
                {
                    return "[$s]";
                }
            }));
        };

        $this->views(['page' => '{{ upper(name) }} {{ wrap(name) }}']);

        $this->assertSame('ADA [ada]', $this->render('page', ['name' => 'ada'], [], $setup));
    }

    /**
     * [service, method] with a non-static method: the instance comes from
     * the container on first call, never at compile time.
     */
    public function testServiceCallableIsResolvedLazilyFromTheContainer(): void
    {
        $this->di->setShared('prices', fn () => new PriceFormatter('de'));
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('price', ['prices', 'format']));
        };

        $code = $this->compile('{{ price(total) }}', [], $setup);
        $this->assertSame('<?= ($this->runtime[\'function:price\'] ??= $this->getRuntimeFunction(\'price\'))($total) ?>', $code);
        $this->assertSame(0, PriceFormatter::$instances);

        $this->views(['page' => '{{ price(total) }}|{{ price(total, "USD") }}']);
        $this->assertSame('de:9.50 EUR|de:9.50 USD', $this->render('page', ['total' => 9.5], [], $setup));
        $this->assertSame(1, PriceFormatter::$instances);
    }

    public function testClassNameCallableIsBuiltThroughTheContainer(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('price', [PriceFormatter::class, 'format']));
        };

        $this->views(['page' => '{{ price(3) }}']);

        $this->assertSame('en:3.00 EUR', $this->render('page', [], [], $setup));
    }

    public function testNamedArguments(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('money', [Money::class, 'format']));
        };

        $this->assertSame(
            '<?= \Phalcon\VoltNfr\Tests\Fixtures\Money::format(currency: \'USD\', amount: $total) ?>',
            $this->compile('{{ money("currency": "USD", "amount": total) }}', [], $setup)
        );

        $this->views(['page' => '{{ money("currency": "USD", "amount": total) }}']);
        $this->assertSame('1.50 USD', $this->render('page', ['total' => 1.5], [], $setup));
    }

    public function testNeedsContextPassesTheTemplateVariables(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction(
                'greet',
                static fn (array $context, string $greeting): string => $greeting . ' ' . $context['user'],
                ['needsContext' => true]
            ));
        };

        $this->views(['page' => '{% set user = "Ada" %}{{ greet("Hi") }}']);

        $this->assertSame('Hi Ada', $this->render('page', [], [], $setup));
    }

    public function testFilterWithArguments(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFilter(new VoltFilter('money', Money::format(...)));
        };

        $this->views(['page' => '{{ total|money }} / {{ total|money("GBP") }}']);

        $this->assertSame('2.00 EUR / 2.00 GBP', $this->render('page', ['total' => 2], [], $setup));
    }

    public function testCustomTestAndItsNegation(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addTest(new VoltTest('premium', static fn (object $u): bool => $u->premium));
            $volt->addTest(new VoltTest('older_than', static fn (object $u, int $age): bool => $u->age > $age));
        };

        $this->views(['page' => '{% for u in users %}{{ u.name }}:{% if u is premium %}P{% endif %}{% if u is not premium %}F{% endif %}{% if u is older_than(30) %}+{% endif %} {% endfor %}']);

        $users = [
            (object) ['name' => 'ada', 'premium' => true, 'age' => 36],
            (object) ['name' => 'bob', 'premium' => false, 'age' => 20],
        ];
        $this->assertSame('ada:P+ bob:F ', $this->render('page', ['users' => $users], [], $setup));
    }

    public function testExtensionBundle(): void
    {
        $this->di->setShared('prices', fn () => new PriceFormatter('fr'));
        $setup = static function (Volt $volt): void {
            $volt->addExtension(new ShopExtension());
        };

        $this->views(['page' => '{{ price(1) }}|{{ 2|price("USD") }}|{{ badge("<new>") }}|{% if user is premium %}vip{% endif %}']);

        $this->assertSame(
            'fr:1.00 EUR|fr:2.00 USD|<span class="badge">&lt;new&gt;</span>|vip',
            $this->render('page', ['user' => (object) ['premium' => true]], ['autoescape' => true], $setup)
        );
        $this->assertSame(1, PriceFormatter::$instances);
    }

    // ---------------------------------------------------------------- tests

    public function testNullAndNoneTests(): void
    {
        $this->views(['page' => '{{ a is null ? "y" : "n" }}{{ b is none ? "y" : "n" }}{{ c is not null ? "y" : "n" }}']);

        $this->assertSame('yny', $this->render('page', ['a' => null, 'b' => 0, 'c' => '']));
    }

    public function testBuiltinTestsStillCompileAsToday(): void
    {
        $this->assertSame('<?= ((($a) % (3)) == 0) ?>', $this->compile('{{ a is divisibleby(3) }}'));
        $this->assertSame('<?= !(((($a) % (3)) == 0)) ?>', $this->compile('{{ a is not divisibleby(3) }}'));
        $this->assertSame('<?= !isset($a) ?>', $this->compile('{{ a is not defined }}'));
        $this->assertSame('<?= $a != $b ?>', $this->compile('{{ a != b }}'));
    }

    public function testUnknownTestIsACompileError(): void
    {
        $this->assertThrowsMessage('Unknown test "premiumm" in eval code on line 1', fn () => $this->compile('{% if u is premiumm %}x{% endif %}'));
    }

    public function testStrictTestsCanBeTurnedOff(): void
    {
        $this->assertSame('<?= $a == $b ?>', $this->compile('{{ a is b }}', ['strictTests' => false]));
        $this->assertSame('<?= !($a == $b) ?>', $this->compile('{{ a is not b }}', ['strictTests' => false]));
    }

    /**
     * The compile-time API keeps working next to the runtime one.
     */
    public function testCompileTimeFunctionsStillWork(): void
    {
        $code = $this->compile('{{ upper(name) }}', [], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('upper', 'strtoupper');
        });

        $this->assertSame('<?= strtoupper($name) ?>', $code);
    }
}
