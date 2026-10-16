<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;

/**
 * {% embed %} (a component with overridable blocks) and include ... with,
 * both compiled inline with a scope of their own.
 */
final class EmbedAndIncludeTest extends TemplateTestCase
{
    private const CARD = '<div class="card"><h2>{% block title %}{{ title ?? "Untitled" }}{% endblock %}</h2>'
        . '<div>{% block body %}{% endblock %}</div>{% block footer %}{% endblock %}</div>';

    public function testEmbedOverridesBlocksOfTheEmbeddedTemplate(): void
    {
        $this->views([
            'card' => self::CARD,
            'page' => '{% embed "card.volt" %}{% block body %}Hello {{ name }}{% endblock %}{% endembed %}',
        ]);

        $this->assertSame(
            '<div class="card"><h2>Untitled</h2><div>Hello Ada</div></div>',
            $this->render('page', ['name' => 'Ada'])
        );
    }

    public function testEmbedWithParametersAndSuper(): void
    {
        $this->views([
            'card' => self::CARD,
            'page' => '{% embed "card.volt" with ["title": "Orders"] %}'
                . '{% block title %}{{ super() }} ({{ count }}){% endblock %}'
                . '{% block body %}{{ count }} open{% endblock %}'
                . '{% endembed %}',
        ]);

        $this->assertSame(
            '<div class="card"><h2>Orders (3)</h2><div>3 open</div></div>',
            $this->render('page', ['count' => 3])
        );
    }

    public function testEmbedVariablesDoNotLeak(): void
    {
        $this->views([
            'box'  => '[{% block content %}{% endblock %}]',
            'page' => '{% set x = "outer" %}{% embed "box.volt" with ["x": "inner"] %}{% block content %}{{ x }}{% set y = 1 %}{% endblock %}{% endembed %}{{ x }}{{ y is defined ? "leak" : "" }}',
        ]);

        $this->assertSame('[inner]outer', $this->render('page'));
    }

    public function testEmbedInsideAChildBlockAndTwiceWithDifferentBlocks(): void
    {
        $this->views([
            'box'    => '[{% block content %}{% endblock %}]',
            'layout' => '<{% block main %}{% endblock %}>',
            'page'   => '{% extends "layout.volt" %}{% block main %}'
                . '{% embed "box.volt" %}{% block content %}one{% endblock %}{% endembed %}'
                . '{% embed "box.volt" %}{% block content %}two{% endblock %}{% endembed %}'
                . '{% endblock %}',
        ]);

        $this->assertSame('<[one][two]>', $this->render('page'));
    }

    /**
     * The embed's blocks belong to the embedded template; a block with the
     * same name in the page is unrelated.
     */
    public function testEmbedBlocksAreScopedToTheEmbed(): void
    {
        $this->views([
            'box'  => '[{% block content %}box{% endblock %}]',
            'page' => '{% block content %}page{% endblock %}{% embed "box.volt" %}{% block content %}embed{% endblock %}{% endembed %}',
        ]);

        $this->assertSame('page[embed]', $this->render('page'));
    }

    public function testEmbeddedTemplateMayItselfExtend(): void
    {
        $this->views([
            'base-card' => '<card>{% block body %}{% endblock %}</card>',
            'alert'     => '{% extends "base-card.volt" %}{% block body %}!{% block message %}{% endblock %}{% endblock %}',
            'page'      => '{% embed "alert.volt" %}{% block message %}Saved{% endblock %}{% endembed %}',
        ]);

        $this->assertSame('<card>!Saved</card>', $this->render('page'));
    }

    /**
     * Compare tests/Today/InheritanceTodayTest::testIncludeWithParametersLosesLocalVariables.
     */
    public function testIncludeWithParametersKeepsLocalVariables(): void
    {
        $this->views([
            'part' => '[{{ local is defined ? local : "undef" }}|{{ p }}]',
            'with' => '{% set local = "L" %}{% include "part" with ["p": "P"] %}{{ p is defined ? "leak" : "" }}',
        ]);

        $this->assertSame('[L|P]', $this->render('with'));
    }

    /**
     * #17368: the same name resolves with or without ".volt".
     */
    public function testIncludeResolvesTheVoltExtension(): void
    {
        $this->views([
            'part' => 'part',
            'page' => '{% include "part" %} {% include "part.volt" %} {% include "part" with [] %}',
        ]);

        $this->assertSame('part part part', $this->render('page'));
    }
}
