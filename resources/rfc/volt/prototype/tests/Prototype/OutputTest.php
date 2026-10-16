<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\VoltNfr\Runtime\VoltFilter;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;
use Phalcon\VoltNfr\Volt;

/**
 * Escaping and the new expressions. Compare tests/Today/OutputTodayTest.
 */
final class OutputTest extends TemplateTestCase
{
    private const AUTOESCAPE = ['autoescape' => true];

    public function testEscapingFiltersAreNotEscapedTwice(): void
    {
        $this->assertSame('<?= $this->escaper->html($x) ?>', $this->compile('{{ x|e }}', self::AUTOESCAPE));
        $this->assertSame('<?= $this->escaper->js($x) ?>', $this->compile('{{ x|escape_js }}', self::AUTOESCAPE));
        $this->assertSame('<?= $this->escaper->html($x) ?>', $this->compile('{{ x }}', self::AUTOESCAPE));
    }

    public function testRawFilter(): void
    {
        $this->views(['page' => '{{ html }}|{{ html|raw }}']);

        $this->assertSame('&lt;b&gt;|<b>', $this->render('page', ['html' => '<b>'], self::AUTOESCAPE));
    }

    public function testSafeFunctionsAndFiltersAreNotEscaped(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('icon', static fn (string $n): string => "<i class=\"$n\"></i>", ['safe' => true]));
            $volt->addFunction(new VoltFunction('label', static fn (string $n): string => "<b>$n</b>"));
            $volt->addFilter(new VoltFilter('markdown', static fn (string $s): string => "<p>$s</p>", ['safe' => true]));
        };

        $this->views(['page' => '{{ icon("star") }}|{{ label("x") }}|{{ text|markdown }}']);

        $this->assertSame(
            '<i class="star"></i>|&lt;b&gt;x&lt;/b&gt;|<p>hi</p>',
            $this->render('page', ['text' => 'hi'], self::AUTOESCAPE, $setup)
        );
    }

    /**
     * A safe call inside a larger expression is escaped as a whole: only a
     * bare safe call skips escaping.
     */
    public function testSafeCallInsideAConcatenationIsEscaped(): void
    {
        $setup = static function (Volt $volt): void {
            $volt->addFunction(new VoltFunction('icon', static fn (): string => '<i></i>', ['safe' => true]));
        };

        $this->views(['page' => '{{ "<" ~ icon() }}']);

        $this->assertSame('&lt;&lt;i&gt;&lt;/i&gt;', $this->render('page', [], self::AUTOESCAPE, $setup));
    }

    public function testNullCoalescing(): void
    {
        $this->views(['page' => '{{ missing ?? "a" }}|{{ nothing ?? "b" }}|{{ zero ?? "c" }}|{{ zero|default("d") }}|{{ user.nick ?? user.name }}']);

        $this->assertSame('a|b|0|d|Ada', $this->render('page', [
            'nothing' => null,
            'zero'    => 0,
            'user'    => (object) ['name' => 'Ada'],
        ]));
    }

    public function testNullSafeNavigation(): void
    {
        $order = new class () {
            public ?object $customer = null;

            public function total(): int
            {
                return 7;
            }
        };

        $this->views(['page' => '[{{ order?.customer?.name }}]{{ order?.total() }}{{ missing?.total() ?? "-" }}']);

        $this->assertSame('[]7-', $this->render('page', ['order' => $order, 'missing' => null]));

        $order->customer = (object) ['name' => 'Ada'];
        $this->assertSame('[Ada]7-', $this->render('page', ['order' => $order, 'missing' => null]));
    }

    /**
     * The capture holds rendered output: "Hello &lt;Ada&gt;!" (18 bytes).
     */
    public function testSetCapture(): void
    {
        $this->views(['page' => '{% set greeting %}Hello {{ name }}!{% endset %}<h1>{{ greeting|raw }}</h1>{{ greeting|length }}']);

        $this->assertSame('<h1>Hello &lt;Ada&gt;!</h1>18', $this->render('page', ['name' => '<Ada>'], self::AUTOESCAPE));
    }
}
