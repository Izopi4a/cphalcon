<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Today;

use Phalcon\Mvc\View\Engine\Volt;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;

/**
 * Template inheritance on the stock build (Phalcon 5.23.0, upstream master).
 * Every assertion here is a limitation the NFR removes; the same templates
 * render in tests/Prototype/InheritanceTest.
 */
final class InheritanceTodayTest extends TemplateTestCase
{
    protected string $engine = Volt::class;

    /**
     * #17145 (2013): a block inside a block is refused by the parser, even
     * in a template that extends nothing.
     */
    public function testNestedBlocksAreRefused(): void
    {
        $this->views([
            'layout' => '{% block outer %}[{% block inner %}parent{% endblock %}]{% endblock %}',
            'child'  => '{% extends "layout.volt" %}{% block inner %}child{% endblock %}',
            'page'   => 'A{% block outer %}B{% block inner %}C{% endblock %}D{% endblock %}E',
        ]);

        $this->assertThrowsMessage('Embedding blocks into other blocks is not supported', fn () => $this->render('child'));
        $this->assertThrowsMessage('Embedding blocks into other blocks is not supported', fn () => $this->render('page'));
    }

    /**
     * if/for/switch use the same counter in base.c, so the message is the
     * same, although no block is nested.
     */
    public function testBlockInsideIfOrForIsRefusedWithTheNestingMessage(): void
    {
        $this->views([
            'if'  => '{% if show %}{% block x %}x{% endblock %}{% endif %}',
            'for' => '{% for i in [1, 2] %}{% block row %}r{% endblock %}{% endfor %}',
        ]);

        $this->assertThrowsMessage('Embedding blocks into other blocks is not supported', fn () => $this->render('if', ['show' => true]));
        $this->assertThrowsMessage('Embedding blocks into other blocks is not supported', fn () => $this->render('for'));
    }

    /**
     * Printing a block twice (<title> and <h1>) has no syntax: "block" is a
     * keyword everywhere.
     */
    public function testBlockFunctionIsASyntaxError(): void
    {
        $this->views([
            'layout' => '<title>{% block title %}T{% endblock %}</title><h1>{{ block("title") }}</h1>',
        ]);

        $this->assertThrowsMessage('Syntax error, unexpected token BLOCK', fn () => $this->render('layout'));
    }

    /**
     * #17271: the grammar accepts an expression, the compiler reads it as a
     * file name.
     */
    public function testExtendsFromAVariableUsesTheVariableNameAsFileName(): void
    {
        $this->views([
            'a' => 'A:{% block x %}a{% endblock %}',
            'c' => '{% extends layoutName %}{% block x %}c{% endblock %}',
        ]);

        $this->assertThrowsMessage($this->dir . 'layoutName does not exist', fn () => $this->render('c', ['layoutName' => 'a.volt']));
    }

    /**
     * What works today and must keep working: multi-level inheritance with
     * super() (#17294).
     */
    public function testMultiLevelSuperChainWorks(): void
    {
        $this->views([
            'a' => '{% block x %}A{% endblock %}',
            'b' => '{% extends "a.volt" %}{% block x %}B({{ super() }}){% endblock %}',
            'c' => '{% extends "b.volt" %}{% block x %}C({{ super() }}){% endblock %}',
        ]);

        $this->assertSame('C(B(A))', $this->render('c'));
    }

    /**
     * No embed, no set capture: syntax errors.
     */
    public function testEmbedAndSetCaptureDoNotParse(): void
    {
        $this->assertThrowsMessage('Syntax error', fn () => $this->compile('{% embed "card.volt" %}{% block body %}x{% endblock %}{% endembed %}'));
        $this->assertThrowsMessage('Syntax error', fn () => $this->compile('{% set x %}captured{% endset %}'));
    }

    /**
     * include ... with switches to a runtime partial: the included template
     * no longer sees the includer's local variables.
     */
    public function testIncludeWithParametersLosesLocalVariables(): void
    {
        $this->views([
            'part'  => '[{{ local is defined ? local : "undef" }}|{{ p }}]',
            'plain' => '{% set local = "L" %}{% set p = "P" %}{% include "part.volt" %}',
            'with'  => '{% set local = "L" %}{% include "part" with ["p": "P"] %}',
        ]);

        $this->assertSame('[L|P]', $this->render('plain'));
        $this->assertSame('[undef|P]', $this->render('with'));
    }
}
