<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;

/**
 * Inheritance resolved on the AST (src/Inheritance/Resolver.php) with the
 * patched parser. The first tests render the templates that fail in
 * tests/Today/InheritanceTodayTest.
 */
final class InheritanceTest extends TemplateTestCase
{
    private const LAYOUT = '<{% block outer %}[O {% block inner %}parent-inner{% endblock %} /O]{% endblock %}>';

    public function testChildOverridesTheInnerBlockOnly(): void
    {
        $this->views([
            'layout' => self::LAYOUT,
            'child'  => '{% extends "layout.volt" %}{% block inner %}child-inner{% endblock %}',
        ]);

        $this->assertSame('<[O child-inner /O]>', $this->render('child'));
    }

    public function testChildOverridesTheOuterBlockAndDropsTheInnerOne(): void
    {
        $this->views([
            'layout' => self::LAYOUT,
            'child'  => '{% extends "layout.volt" %}{% block outer %}child-outer{% endblock %}',
        ]);

        $this->assertSame('<child-outer>', $this->render('child'));
    }

    public function testNoOverrideRendersTheNestedDefaults(): void
    {
        $this->views([
            'layout' => self::LAYOUT,
            'child'  => '{% extends "layout.volt" %}',
        ]);

        $this->assertSame('<[O parent-inner /O]>', $this->render('child'));
    }

    public function testSuperInsideANestedBlock(): void
    {
        $this->views([
            'layout' => self::LAYOUT,
            'child'  => '{% extends "layout.volt" %}{% block inner %}{{ super() }}+child{% endblock %}',
        ]);

        $this->assertSame('<[O parent-inner+child /O]>', $this->render('child'));
    }

    public function testOverridingOuterKeepsAnInnerBlockThatTheChildRedeclares(): void
    {
        $this->views([
            'layout' => self::LAYOUT,
            'mid'    => '{% extends "layout.volt" %}{% block outer %}mid({% block inner %}mid-inner{% endblock %}){% endblock %}',
            'leaf'   => '{% extends "mid.volt" %}{% block inner %}leaf-inner+{{ super() }}{% endblock %}',
        ]);

        $this->assertSame('<mid(mid-inner)>', $this->render('mid'));
        $this->assertSame('<mid(leaf-inner+mid-inner)>', $this->render('leaf'));
    }

    /**
     * The case from #17145: a.volt extends b.volt extends c.volt, the middle
     * template opens a region that the leaf fills.
     */
    public function testThreeLevelsWithARegionOpenedInTheMiddle(): void
    {
        $this->views([
            'base' => '<html>{% block body %}base{% endblock %}</html>',
            'mid'  => '{% extends "base.volt" %}{% block body %}<main>{% block content %}{% endblock %}</main><aside>{% block sidebar %}default{% endblock %}</aside>{% endblock %}',
            'leaf' => '{% extends "mid.volt" %}{% block content %}article{% endblock %}{% block sidebar %}{{ super() }}+tags{% endblock %}',
        ]);

        $this->assertSame('<html><main>article</main><aside>default+tags</aside></html>', $this->render('leaf'));
    }

    public function testStandaloneTemplateWithNestedBlocks(): void
    {
        $this->views(['page' => 'A{% block outer %}B{% block inner %}C{% endblock %}D{% endblock %}E']);

        $this->assertSame('ABCDE', $this->render('page'));
    }

    public function testBlocksInsideIfAndFor(): void
    {
        $this->views([
            'layout' => '{% if show %}{% block banner %}parent{% endblock %}{% endif %}|{% for i in [1, 2] %}{% block row %}r{{ i }}{% endblock %}{% endfor %}',
            'child'  => '{% extends "layout.volt" %}{% block banner %}child{% endblock %}{% block row %}c{{ i }}{% endblock %}',
        ]);

        $this->assertSame('child|c1c2', $this->render('child', ['show' => true]));
        $this->assertSame('|c1c2', $this->render('child', ['show' => false]));
    }

    public function testBlockFunctionPrintsTheResolvedBlockAgain(): void
    {
        $this->views([
            'layout' => '<title>{% block title %}Site{% endblock %}</title><h1>{{ block("title") }}</h1>',
            'child'  => '{% extends "layout.volt" %}{% block title %}Orders{% endblock %}',
        ]);

        $this->assertSame('<title>Site</title><h1>Site</h1>', $this->render('layout'));
        $this->assertSame('<title>Orders</title><h1>Orders</h1>', $this->render('child'));
    }

    public function testMultiLevelSuperChainStillWorks(): void
    {
        $this->views([
            'a' => '{% block x %}A{% endblock %}',
            'b' => '{% extends "a.volt" %}{% block x %}B({{ super() }}){% endblock %}',
            'c' => '{% extends "b.volt" %}{% block x %}C({{ super() }}){% endblock %}',
        ]);

        $this->assertSame('C(B(A))', $this->render('c'));
    }

    public function testRelativeExtends(): void
    {
        $this->views([
            'layouts/base'  => '[{% block x %}base{% endblock %}]',
            'pages/one'     => '{% extends "../layouts/base.volt" %}{% block x %}one{% endblock %}',
        ]);

        $this->assertSame('[one]', $this->render('pages/one'));
    }

    // ------------------------------------------------------ dynamic extends

    /**
     * #17271: {% extends layoutName %}. One compiled file per (child, parent).
     */
    public function testExtendsFromAVariable(): void
    {
        $this->views([
            'full'  => '<full>{% block content %}{% endblock %}</full>',
            'ajax'  => '<ajax>{% block content %}{% endblock %}</ajax>',
            'page'  => '{% extends layout %}{% block content %}{{ title }}{% endblock %}',
        ]);

        $this->assertSame('<full>Orders</full>', $this->render('page', ['layout' => 'full.volt', 'title' => 'Orders']));
        $this->assertSame('<ajax>Orders</ajax>', $this->render('page', ['layout' => 'ajax.volt', 'title' => 'Orders']));
        $variants = array_filter(glob($this->dir . 'cache/variant%%*.php'), static fn ($f) => !str_ends_with($f, '.deps.php'));
        $this->assertCount(2, $variants);
    }

    public function testExtendsFromAConditionalExpression(): void
    {
        $this->views([
            'full' => 'F:{% block c %}{% endblock %}',
            'ajax' => 'A:{% block c %}{% endblock %}',
            'page' => '{% extends isAjax ? "ajax.volt" : "full.volt" %}{% block c %}x{% endblock %}',
        ]);

        $this->assertSame('A:x', $this->render('page', ['isAjax' => true]));
        $this->assertSame('F:x', $this->render('page', ['isAjax' => false]));
    }

    // --------------------------------------------------------------- errors

    public function testSuperOutsideABlock(): void
    {
        $this->views(['page' => 'x {{ super() }}']);

        $this->assertThrowsMessage('super() can only be used inside a block', fn () => $this->render('page'));
    }

    public function testSuperWithoutAParentDefinition(): void
    {
        $this->views([
            'layout' => '{% block a %}A{% endblock %}',
            'child'  => '{% extends "layout.volt" %}{% block a %}{% block b %}{{ super() }}{% endblock %}{% endblock %}',
        ]);

        $this->assertThrowsMessage("super() in block 'b': no parent template defines it", fn () => $this->render('child'));
    }

    public function testBlockFunctionForAnUndefinedBlock(): void
    {
        $this->views(['page' => '{{ block("nope") }}']);

        $this->assertThrowsMessage("Block 'nope' is not defined", fn () => $this->render('page'));
    }

    public function testBlockThatRendersItself(): void
    {
        $this->views(['page' => '{% block a %}{{ block("a") }}{% endblock %}']);

        $this->assertThrowsMessage("Block 'a' renders itself", fn () => $this->render('page'));
    }

    public function testDuplicateBlockNames(): void
    {
        $this->views(['page' => "{% block a %}1{% endblock %}\n{% block a %}2{% endblock %}"]);

        $this->assertThrowsMessage("Block 'a' is defined twice", fn () => $this->render('page'));
    }

    public function testCircularInheritance(): void
    {
        $this->views([
            'a' => '{% extends "b.volt" %}{% block x %}a{% endblock %}',
            'b' => '{% extends "a.volt" %}{% block x %}b{% endblock %}',
        ]);

        $this->assertThrowsMessage('Circular inheritance', fn () => $this->render('a'));
    }

    public function testErrorsNameTheTemplateFile(): void
    {
        $this->views(['broken' => "line one\n{{ 1 + * 2 }}\nline three"]);

        $this->assertThrowsMessage($this->dir . 'broken.volt on line 2', fn () => $this->render('broken'));
    }
}
