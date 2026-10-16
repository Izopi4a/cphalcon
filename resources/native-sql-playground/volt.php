<?php

/**
 * The Volt scenarios: every new Volt feature of this branch on a small
 * template, rendered through View\Simple + the Volt engine. Each scenario
 * says what happens without the change ("today", Phalcon 5.x / 7.0.x).
 */

declare(strict_types=1);

use Phalcon\Di\DiInterface;
use Phalcon\Mvc\View\Engine\Volt;
use Phalcon\Mvc\View\Engine\Volt\Runtime\AbstractExtension;
use Phalcon\Mvc\View\Engine\Volt\Runtime\VoltFilter;
use Phalcon\Mvc\View\Engine\Volt\Runtime\VoltFunction;
use Phalcon\Mvc\View\Engine\Volt\Runtime\VoltTest;
use Phalcon\Mvc\View\Simple;

/**
 * A service the templates reach through the container: [ 'money', 'format' ]
 */
final class MoneyFormatter
{
    public static int $instances = 0;

    public function __construct()
    {
        self::$instances++;
    }

    public function format(float|string $amount, string $currency = 'EUR', int $decimals = 2): string
    {
        return number_format((float) $amount, $decimals, '.', ' ') . ' ' . $currency;
    }
}

/**
 * Functions, filters and tests the shop's templates use, as one extension
 */
final class ShopExtension extends AbstractExtension
{
    public function getFunctions(): array
    {
        return [
            new VoltFunction('price', ['money', 'format']),
            new VoltFunction('stars', fn (int $n): string => '<span class="stars">' . str_repeat('★', $n) . '</span>', ['safe' => true]),
            new VoltFunction('now', fn (): string => date('H:i:s')),
        ];
    }

    public function getFilters(): array
    {
        return [
            new VoltFilter('money', [MoneyFormatter::class, 'format']),
            new VoltFilter('initials', fn (string $name): string => implode('', array_map(fn ($w) => mb_substr($w, 0, 1), explode(' ', $name)))),
        ];
    }

    public function getTests(): array
    {
        return [
            new VoltTest('local', fn ($customer): bool => $customer !== null && $customer->country === 'BG'),
            new VoltTest('shipped', fn ($order): bool => $order !== null && $order->status === 'shipped'),
        ];
    }
}

/**
 * @return list<array>
 */
function voltScenarios(): array
{
    return [
        [
            'group' => 'Inheritance on the AST',
            'title' => 'Nested blocks across three levels, super() at every level',
            'today' => 'Parser error: "Embedding blocks into other blocks is not supported" (#17145, open since 2013).',
            'files' => [
                'base'   => "<title>{% block title %}Shop{% endblock %}</title>\n{% block body %}<header>Shop</header>\n<main>{% block content %}{% endblock %}</main>{% endblock %}",
                'layout' => "{% extends \"base.volt\" %}\n{% block content %}<aside>{% block sidebar %}categories{% endblock %}</aside>\n<section>{% block main %}{% endblock %}</section>{% endblock %}",
                'page'   => "{% extends \"layout.volt\" %}\n{% block title %}Orders · {{ super() }}{% endblock %}\n{% block sidebar %}{{ super() }} + filters{% endblock %}\n{% block main %}{{ orders }} orders{% endblock %}",
            ],
            'vars'  => fn () => ['orders' => Order::count()],
        ],
        [
            'group' => 'Inheritance on the AST',
            'title' => '{{ block("title") }}: print a block twice',
            'today' => 'Syntax error: block is a reserved word, so block("title") does not parse.',
            'files' => [
                'page' => "<title>{% block title %}Order #{{ order.id }}{% endblock %}</title>\n<h1>{{ block(\"title\") }}</h1>",
            ],
            'vars'  => fn () => ['order' => Order::findFirst(['order' => 'id'])],
        ],
        [
            'group' => 'Inheritance on the AST',
            'title' => 'A block inside if/for, overridden by the child',
            'today' => 'Parser error: blocks are only accepted at the top level of a template.',
            'files' => [
                'base' => "{% for c in customers %}\n<li>{% block line %}{{ c.name }}{% endblock %}</li>{% endfor %}",
                'page' => "{% extends \"base.volt\" %}\n{% block line %}{{ c.name }} ({{ c.country }}){% endblock %}",
            ],
            'vars'  => fn () => ['customers' => Customer::find(['order' => 'id', 'limit' => 3])],
        ],
        [
            'group' => 'Inheritance on the AST',
            'title' => '{% embed %}: a component with overridable parts',
            'today' => 'Unknown tag. The usual workaround is a partial with HTML passed in variables.',
            'files' => [
                'card' => "<div class=\"card\"><h3>{% block head %}{{ title }}{% endblock %}</h3>\n<div>{% block body %}{% endblock %}</div></div>",
                'page' => "{% embed \"card.volt\" with [\"title\": \"Latest order\"] %}\n{% block body %}#{{ order.id }} · {{ order.status }} · {{ order.customer.name }}{% endblock %}\n{% endembed %}",
            ],
            'vars'  => fn () => ['order' => Order::findFirst(['order' => 'createdAt DESC'])],
        ],
        [
            'group' => 'Inheritance on the AST',
            'title' => '{% extends layoutName %}: the parent chosen at render time',
            'today' => 'The variable name is used as a file name ("layoutName" not found, #17271).',
            'files' => [
                'admin'  => "<div class=\"admin\">{% block content %}{% endblock %}</div>",
                'public' => "<div class=\"public\">{% block content %}{% endblock %}</div>",
                'page'   => "{% extends layoutName %}\n{% block content %}Hello from the same child{% endblock %}",
            ],
            'renders' => [
                ['layoutName' => 'admin.volt'],
                ['layoutName' => 'public.volt'],
            ],
        ],
        [
            'group' => 'Runtime functions, filters and tests',
            'title' => 'A function backed by a DI service, a safe one returning HTML, one evaluated per render',
            'today' => 'addFunction() closures run once at compile time and must return PHP source: now() would be frozen into the cache, and HTML from a function is escaped by autoescape.',
            'files' => [
                'page' => "{{ price(1234.5, \"BGN\") }} · {{ stars(4) }} · rendered at {{ now() }}",
            ],
            'options' => ['autoescape' => true],
        ],
        [
            'group' => 'Runtime functions, filters and tests',
            'title' => "Filters with named arguments ('name': value), any callable",
            'today' => "'name': value arguments produce invalid PHP for functions; filters receive PHP source strings.",
            'files' => [
                'page' => "{% for c in customers %}{{ c.name|initials }}: {{ 1500|money('currency': 'BGN', 'decimals': 0) }} · {% endfor %}",
            ],
            'vars'  => fn () => ['customers' => Customer::find(['order' => 'id', 'limit' => 3])],
        ],
        [
            'group' => 'Runtime functions, filters and tests',
            'title' => 'Tests: is local / is not shipped, plus the built-in is null',
            'today' => 'An unknown test silently compiles to ==, and "is not" is lexed as !=, so negating a test breaks.',
            'files' => [
                'page' => "{% for o in orders %}#{{ o.id }} {{ o.customer.name }}{% if o.customer is local %} (BG){% endif %}{% if o is not shipped %} · not shipped yet{% endif %}<br>\n{% endfor %}{{ missing is null ? 'missing is null' : '' }}",
            ],
            'vars'  => fn () => ['orders' => Order::find(['order' => 'id', 'limit' => 4]), 'missing' => null],
        ],
        [
            'group' => 'Runtime functions, filters and tests',
            'title' => 'Strict tests: an unknown test name is a compile error',
            'today' => '{% if order is paid %} compiles to $order == $paid, which is quietly false.',
            'files' => [
                'page' => "{% if order is paid %}paid{% endif %}",
            ],
            'vars'  => fn () => ['order' => Order::findFirst()],
        ],
        [
            'group' => 'New syntax',
            'title' => '?? keeps 0, ?. walks nullable relations',
            'today' => 'Both are syntax errors. |default uses empty(), so a discount of 0 is replaced.',
            'files' => [
                'page' => "discount: {{ discount ?? 'none' }} vs |default: {{ discount|default('none') }}\n· customer: {{ order?.customer?.name }} · missing: {{ missing?.customer?.name ?? 'nobody' }}",
            ],
            'vars'  => fn () => ['discount' => 0, 'order' => Order::findFirst(), 'missing' => null],
        ],
        [
            'group' => 'New syntax',
            'title' => '{% set name %}...{% endset %}: capture rendered output',
            'today' => 'Unknown tag.',
            'files' => [
                'page' => "{% set badge %}<b>{{ customer.name }}</b> ({{ customer.country }}){% endset %}\n{{ badge|raw }} … again: {{ badge|raw }}",
            ],
            'vars'  => fn () => ['customer' => Customer::findFirst(1)],
        ],
        [
            'group' => 'New syntax',
            'title' => 'include ... with [...]: still compiled, sees the includer\'s variables',
            'today' => 'With "with", include switches to a runtime partial that no longer sees the template\'s variables (shop is undefined).',
            'files' => [
                '_line' => "{{ label }}: {{ value }} (shop {{ shop }})",
                'page'  => "{% set shop = 'Plovdiv' %}\n{% include \"_line\" with [\"label\": \"Orders\", \"value\": orders] %}",
            ],
            'vars'  => fn () => ['orders' => Order::count()],
        ],
        [
            'group' => 'Fixed along the way',
            'title' => '{% call %} with caller()',
            'today' => 'The whole {% call %} block compiles to an empty string: the content disappears without an error.',
            'files' => [
                'page' => "{% macro panel(title) %}<section><h4>{{ title }}</h4>{{ caller() }}</section>{% endmacro %}\n{% call panel(\"Top customer\") %}{{ customer.name }} from {{ customer.country }}{% endcall %}",
            ],
            'vars'  => fn () => ['customer' => Customer::findFirst(1)],
        ],
        [
            'group' => 'Fixed along the way',
            'title' => '// is floor division',
            'today' => '{{ 7 // 2 }} prints 1: the grammar builds a modulo node.',
            'files' => [
                'page' => "7 // 2 = {{ 7 // 2 }} · 7 % 2 = {{ 7 % 2 }} · orders per customer: {{ orders // 40 }}",
            ],
            'vars'  => fn () => ['orders' => Order::count()],
        ],
        [
            'group' => 'Fixed along the way',
            'title' => 'Autoescape no longer escapes twice',
            'today' => '{{ name|e }} becomes html(html($name)) (&amp;amp;), content() and partial() output is escaped, there is no raw.',
            'files' => [
                'page' => "{{ name }} · {{ name|e }} · {{ '<b>bold</b>'|raw }} · {{ stars(2) }}",
            ],
            'vars'    => fn () => ['name' => 'Tom & "Jerry"'],
            'options' => ['autoescape' => true],
        ],
        [
            'group' => 'Cache',
            'title' => 'Dependency sidecar: editing a parent recompiles the child',
            'today' => 'stat only compares the child\'s own mtime: edits to a layout or an include are ignored until the cache is cleared.',
            'files' => [
                'base' => "<b>{% block content %}{% endblock %}</b>",
                'page' => "{% extends \"base.volt\" %}{% block content %}child{% endblock %}",
            ],
            'showDeps' => true,
        ],
    ];
}

/**
 * Renders one scenario: [renders => [[vars, output|error]], compiled, deps]
 */
function renderVoltScenario(array $scenario, DiInterface $di): array
{
    if (!$di->has('money')) {
        $di->setShared('money', MoneyFormatter::class);
    }

    $dir = sys_get_temp_dir() . '/native-sql-playground-volt/' . sha1(json_encode($scenario['files'])) . '/';
    @mkdir($dir . 'cache', 0777, true);

    foreach ($scenario['files'] as $name => $source) {
        file_put_contents($dir . $name . '.volt', $source);
    }

    $options = ($scenario['options'] ?? []) + ['path' => $dir . 'cache/', 'always' => true];
    $result  = ['renders' => [], 'compiled' => null, 'deps' => null];
    $sets    = $scenario['renders'] ?? [[]];
    $volt    = null;

    foreach ($sets as $extra) {
        $vars  = (isset($scenario['vars']) ? ($scenario['vars'])() : []) + $extra;
        $view  = new Simple();
        $view->setDI($di);
        $view->setViewsDir($dir);
        $view->registerEngines([
            '.volt' => function ($view) use ($di, $options, &$volt) {
                $volt = new Volt($view, $di);
                $volt->setOptions($options);
                $volt->addExtension(new ShopExtension());

                return $volt;
            },
        ]);

        $level = ob_get_level();
        try {
            $output = $view->render('page', $vars);
            $result['renders'][] = ['vars' => $extra, 'output' => $output, 'error' => null];
        } catch (Throwable $e) {
            $result['renders'][] = ['vars' => $extra, 'output' => null, 'error' => (new ReflectionClass($e))->getShortName() . ': ' . $e->getMessage()];
        } finally {
            while (ob_get_level() > $level) {
                ob_end_clean();
            }
        }
    }

    // the compiled page, and its dependency sidecar
    try {
        $compiler = $volt?->getCompiler();
        if ($compiler !== null) {
            $compiler->compile($dir . 'page.volt');
            $compiled           = $compiler->getCompiledTemplatePath();
            $result['compiled'] = (string) file_get_contents($compiled);
            if (!empty($scenario['showDeps']) && is_file($compiled . '.deps.php')) {
                $deps           = include $compiled . '.deps.php';
                $result['deps'] = [
                    'files'     => array_map(fn ($m) => date('H:i:s', $m), array_combine(
                        array_map('basename', array_keys($deps['files'])),
                        array_values($deps['files'])
                    )),
                    'signature' => substr($deps['signature'], 0, 60) . '…',
                ];
            }
        }
    } catch (Throwable $e) {
        $result['compiled'] = (new ReflectionClass($e))->getShortName() . ': ' . $e->getMessage();
    }

    return $result;
}
