<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Today;

use Phalcon\Mvc\View\Engine\Volt;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;

/**
 * Escaping, expressions and caching on the stock build.
 */
final class OutputTodayTest extends TemplateTestCase
{
    protected string $engine = Volt::class;

    /**
     * Autoescape wraps the whole echo, including escaping filters.
     */
    public function testAutoescapeEscapesEscapingFiltersAgain(): void
    {
        $options = ['autoescape' => true];

        $this->assertSame('<?= $this->escaper->html($this->escaper->html($x)) ?>', $this->compile('{{ x|e }}', $options));
        $this->assertSame('<?= $this->escaper->html($this->escaper->js($x)) ?>', $this->compile('{{ x|escape_js }}', $options));
    }

    /**
     * No raw filter and no way to mark a function's output as HTML.
     */
    public function testNoRawFilterAndFunctionHtmlIsEscaped(): void
    {
        $this->assertThrowsMessage('Unknown filter "raw"', fn () => $this->compile('{{ html|raw }}'));

        $code = $this->compile('{{ badge(user) }}', ['autoescape' => true], static function (Volt $volt): void {
            $volt->getCompiler()->addFunction('badge', 'badge');
        });
        $this->assertSame('<?= $this->escaper->html(badge($user)) ?>', $code);
    }

    /**
     * The rendered view inserted by content() is escaped again, and a
     * property named like a keyword cannot be read (#12846).
     */
    public function testContentIsEscapedAndKeywordPropertiesFail(): void
    {
        $this->assertSame('<?= $this->escaper->html($this->getContent()) ?>', $this->compile('{{ content() }}', ['autoescape' => true]));
        $this->assertThrowsMessage('unexpected token BLOCK', fn () => $this->compile('{{ article.block }}'));
    }

    /**
     * |default uses empty(): 0, "0" and false are replaced as well.
     */
    public function testNoNullCoalescingAndDefaultUsesEmpty(): void
    {
        $this->assertThrowsMessage('Syntax error', fn () => $this->compile('{{ a ?? "x" }}'));
        $this->assertThrowsMessage('Syntax error', fn () => $this->compile('{{ a?.b }}'));

        $this->views(['d' => '{{ count|default("none") }}']);
        $this->assertSame('none', $this->render('d', ['count' => 0]));
    }

    /**
     * Grammar quirks: "//" is parsed as modulo, {% call %} drops its body,
     * {% cache %} still parses but the compiler removed it.
     */
    public function testGrammarCompilerDrift(): void
    {
        $this->assertSame('<?= 7 % 2 ?>', $this->compile('{{ 7 // 2 }}'));
        $this->assertSame('', $this->compile('{% call m(1) %}BODY{% endcall %}'));
        $this->assertThrowsMessage('Unknown statement 314', fn () => $this->compile('{% cache "k" 60 %}x{% endcache %}'));
    }

    /**
     * With stat on, only the rendered template's own mtime is checked:
     * parents and static includes are inlined, so editing them changes
     * nothing until the cache is cleared.
     */
    public function testEditingAParentOrAnIncludeLeavesTheChildStale(): void
    {
        $this->views([
            'layout' => 'L1 {% block x %}{% endblock %}',
            'child'  => '{% extends "layout.volt" %}{% block x %}child{% endblock %}',
            'inc'    => 'I1',
            'page'   => 'page {% include "inc.volt" %}',
        ]);
        $this->assertSame('L1 child', $this->render('child'));
        $this->assertSame('page I1', $this->render('page'));

        $this->edit('layout', 'L2 {% block x %}{% endblock %}');
        $this->edit('inc', 'I2');

        $this->assertSame('L1 child', $this->render('child'));
        $this->assertSame('page I1', $this->render('page'));
    }
}
