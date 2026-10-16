<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Tests\Prototype;

use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Tests\Support\TemplateTestCase;
use Phalcon\VoltNfr\Volt;

/**
 * Dependency tracking (src/Cache/Dependencies.php). Compare
 * tests/Today/OutputTodayTest::testEditingAParentOrAnIncludeLeavesTheChildStale.
 */
final class CacheTest extends TemplateTestCase
{
    public function testEditingAParentRecompilesTheChild(): void
    {
        $this->views([
            'base'  => 'B1 {% block x %}{% endblock %}',
            'mid'   => '{% extends "base.volt" %}{% block x %}mid {% block y %}{% endblock %}{% endblock %}',
            'child' => '{% extends "mid.volt" %}{% block y %}child{% endblock %}',
        ]);
        $this->assertSame('B1 mid child', $this->render('child'));

        $this->edit('base', 'B2 {% block x %}{% endblock %}');

        $this->assertSame('B2 mid child', $this->render('child'));
    }

    public function testEditingAnIncludeOrAnEmbedRecompilesTheIncluder(): void
    {
        $this->views([
            'inc'  => 'I1',
            'box'  => '[{% block c %}{% endblock %}]',
            'page' => '{% include "inc.volt" %} {% embed "box.volt" %}{% block c %}e{% endblock %}{% endembed %}',
        ]);
        $this->assertSame('I1 [e]', $this->render('page'));

        $this->edit('inc', 'I2');
        $this->assertSame('I2 [e]', $this->render('page'));

        $this->edit('box', '({% block c %}{% endblock %})');
        $this->assertSame('I2 (e)', $this->render('page'));
    }

    public function testNestedIncludesPropagate(): void
    {
        $this->views([
            'leaf' => 'L1',
            'part' => 'part:{% include "leaf.volt" %}',
            'page' => 'page:{% include "part.volt" %}',
        ]);
        $this->assertSame('page:part:L1', $this->render('page'));

        $this->edit('leaf', 'L2');

        $this->assertSame('page:part:L2', $this->render('page'));
    }

    /**
     * The compiled output depends on the registry (a safe flag decides the
     * escaping): changing it recompiles without clearing the cache.
     */
    public function testChangingTheRegistryRecompiles(): void
    {
        $this->views(['page' => '{{ icon() }}']);
        $function = static fn (array $options): callable => static function (Volt $volt) use ($options): void {
            $volt->addFunction(new VoltFunction('icon', static fn (): string => '<i></i>', $options));
        };

        $this->assertSame('&lt;i&gt;&lt;/i&gt;', $this->render('page', [], ['autoescape' => true], $function([])));
        $this->assertSame('<i></i>', $this->render('page', [], ['autoescape' => true], $function(['safe' => true])));
    }

    /**
     * stat => false keeps today's production behaviour: no file checks.
     */
    public function testStatOffSkipsTheDependencyCheck(): void
    {
        $this->views([
            'base'  => 'B1 {% block x %}{% endblock %}',
            'child' => '{% extends "base.volt" %}{% block x %}c{% endblock %}',
        ]);
        $this->assertSame('B1 c', $this->render('child', [], ['stat' => false]));

        $this->edit('base', 'B2 {% block x %}{% endblock %}');

        $this->assertSame('B1 c', $this->render('child', [], ['stat' => false]));
        $this->assertSame('B2 c', $this->render('child'));
    }

    public function testNoSerializedBlockCacheIsWritten(): void
    {
        $this->views([
            'base'  => '{% block x %}{% endblock %}',
            'child' => '{% extends "base.volt" %}{% block x %}c{% endblock %}',
        ]);
        $this->render('child');

        $this->assertSame([], glob($this->dir . 'cache/*%%e%%*'));
    }
}
