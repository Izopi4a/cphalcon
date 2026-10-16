<?php

/**
 * Generates ../examples.md: each example runs on the stock extension (today)
 * and on the patched extension with the prototype engine (proposed), and the
 * real output is written into the document.
 *
 *   ./run.sh tools/examples.php            check: exit 1 if examples.md drifts
 *   ./run.sh tools/examples.php --write    regenerate examples.md
 *
 * The script re-runs itself once per extension (--worker=stock|nfr), because
 * one PHP process loads one phalcon.so.
 */

declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Di\FactoryDefault;
use Phalcon\Mvc\View\Engine\Volt as StockVolt;
use Phalcon\Mvc\View\Simple;
use Phalcon\VoltNfr\Runtime\AbstractExtension;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Runtime\VoltTest;
use Phalcon\VoltNfr\Volt as NfrVolt;

final class Harness
{
    public string $dir;
    public FactoryDefault $di;

    public function __construct(public string $flavor)
    {
        $this->dir = sys_get_temp_dir() . '/volt-examples-' . bin2hex(random_bytes(4)) . '/';
        mkdir($this->dir . 'cache', 0777, true);
        $this->di = new FactoryDefault();
    }

    public function views(array $files): void
    {
        foreach ($files as $name => $source) {
            $path = $this->dir . $name . '.volt';
            @mkdir(dirname($path), 0777, true);
            file_put_contents($path, $source);
            touch($path, time() - 3600);
        }
        clearstatcache();
    }

    public function edit(string $name, string $source): void
    {
        file_put_contents($this->dir . $name . '.volt', $source);
        touch($this->dir . $name . '.volt', time() + 10);
        clearstatcache();
    }

    public function render(string $view, array $params = [], array $options = [], ?callable $setup = null): string
    {
        $di     = $this->di;
        $dir    = $this->dir;
        $engine = $this->flavor === 'nfr' ? NfrVolt::class : StockVolt::class;

        $simple = new Simple();
        $simple->setDI($di);
        $simple->setViewsDir($dir);
        $simple->registerEngines([
            '.volt' => function ($view) use ($di, $dir, $engine, $options, $setup) {
                $volt = new $engine($view, $di);
                $volt->setOptions($options + ['path' => $dir . 'cache/', 'stat' => true]);
                if ($setup !== null) {
                    $setup($volt);
                }

                return $volt;
            },
        ]);

        $level = ob_get_level();
        try {
            return $simple->render($view, $params);
        } catch (Throwable $e) {
            return $this->error($e);
        } finally {
            while (ob_get_level() > $level) {
                ob_end_clean();
            }
        }
    }

    public function compile(string $source, array $options = [], ?callable $setup = null): string
    {
        $simple = new Simple();
        $simple->setViewsDir($this->dir);
        $engine = $this->flavor === 'nfr' ? NfrVolt::class : StockVolt::class;
        $volt   = new $engine($simple, $this->di);
        $volt->setOptions($options);
        if ($setup !== null) {
            $setup($volt);
        }

        try {
            return $volt->getCompiler()->compileString($source);
        } catch (Throwable $e) {
            return $this->error($e);
        }
    }

    private function error(Throwable $e): string
    {
        return 'throws ' . get_class($e) . ': ' . $this->clean($e->getMessage());
    }

    public function clean(string $text): string
    {
        $text = str_replace($this->dir, 'views/', $text);

        // directory read sizes differ per filesystem
        return (string) preg_replace('/Read of \d+ bytes/', 'Read of N bytes', $text);
    }
}

final class Prices
{
    public static int $built = 0;

    public function __construct()
    {
        self::$built++;
    }

    public function format(float $amount, string $currency = 'EUR'): string
    {
        return number_format($amount, 2) . ' ' . $currency;
    }
}

final class ShopExtension extends AbstractExtension
{
    public function getFunctions(): array
    {
        return [
            new VoltFunction('price', ['prices', 'format']),
            new VoltFunction('stars', static fn (int $n): string => str_repeat('<i class="star"></i>', $n), ['safe' => true]),
        ];
    }

    public function getTests(): array
    {
        return [new VoltTest('premium', static fn (object $user): bool => $user->plan === 'premium')];
    }
}

/**
 * Each example: templates shown in the document, optional setup code shown
 * per flavor, and run() returning labelled outputs.
 */
$examples = [
    'E1' => [
        'title' => 'Nested blocks: a region opened by a middle layout (#17145)',
        'intro' => 'The request from 2013: `leaf` extends `section` extends `base`, and the middle template opens regions that the leaf fills or extends with `super()`.',
        'files' => [
            'base'    => "<html><body>{% block body %}{% endblock %}</body></html>",
            'section' => "{% extends \"base.volt\" %}\n{% block body %}\n<main>{% block content %}{% endblock %}</main>\n<aside>{% block sidebar %}<h3>Help</h3>{% endblock %}</aside>\n{% endblock %}",
            'leaf'    => "{% extends \"section.volt\" %}\n{% block content %}Article{% endblock %}\n{% block sidebar %}{{ super() }}<p>Related</p>{% endblock %}",
        ],
        'run'   => static fn (Harness $h): array => ['render leaf' => $h->render('leaf')],
    ],
    'E2' => [
        'title' => 'A block inside if/for, and block() to print a block twice',
        'intro' => '`block_level` in base.c also counts if/for/switch, so today a block inside a condition fails with the nesting message. `block` is a keyword, so `block("title")` is a syntax error.',
        'files' => [
            'layout' => "<title>{% block title %}Shop{% endblock %}</title>\n<h1>{{ block(\"title\") }}</h1>\n{% if user %}{% block account %}Hi {{ user }}{% endblock %}{% endif %}",
            'orders' => "{% extends \"layout.volt\" %}\n{% block title %}Orders{% endblock %}\n{% block account %}{{ super() }} (3 open){% endblock %}",
        ],
        'run'   => static fn (Harness $h): array => ['render orders, user=Ada' => $h->render('orders', ['user' => 'Ada'])],
    ],
    'E3' => [
        'title' => 'Choosing the layout at render time (#17271)',
        'intro' => 'Today the variable name is used as a file name. The prototype compiles the child once per parent it is rendered with.',
        'files' => [
            'full' => "<html>{% block content %}{% endblock %}</html>",
            'ajax' => "{% block content %}{% endblock %}",
            'page' => "{% extends request_is_ajax ? \"ajax.volt\" : \"full.volt\" %}\n{% block content %}<p>{{ message }}</p>{% endblock %}",
        ],
        'run'   => static fn (Harness $h): array => [
            'render page, ajax=false' => $h->render('page', ['request_is_ajax' => false, 'message' => 'Saved']),
            'render page, ajax=true'  => $h->render('page', ['request_is_ajax' => true, 'message' => 'Saved']),
        ],
    ],
    'E4' => [
        'title' => 'Components with embed',
        'intro' => 'A card with overridable blocks, used twice with different content. Today this needs a macro per variation or a partial with HTML passed in as a string.',
        'files' => [
            'card'  => "<div class=\"card\"><h2>{% block title %}{{ title }}{% endblock %}</h2>{% block body %}{% endblock %}</div>",
            'page'  => "{% embed \"card.volt\" with [\"title\": \"Orders\"] %}\n  {% block body %}<p>{{ open }} open</p>{% endblock %}\n{% endembed %}\n{% embed \"card.volt\" with [\"title\": \"Stock\"] %}\n  {% block title %}{{ super() }} <small>low</small>{% endblock %}\n  {% block body %}<p>2 items</p>{% endblock %}\n{% endembed %}",
        ],
        'run'   => static fn (Harness $h): array => ['render page' => preg_replace('/\s+/', ' ', $h->render('page', ['open' => 3]))],
    ],
    'E5' => [
        'title' => 'Declaring a function: compile time today, run time proposed',
        'intro' => 'Today a closure passed to `addFunction()` is a code generator: it runs once, at compile time, gets the arguments as PHP source, and must return PHP source. The value it computes is frozen into the cache. The proposal keeps that API for code generators and adds callables that run at render time.',
        'files' => [],
        'setup' => [
            'stock' => "\$compiler = \$volt->getCompiler();\n\$compiler->addFunction('year', fn () => date('Y'));          // runs now, returns 2026\n\$compiler->addFunction('greeting', fn (\$args) => 'Hello ' . \$args); // returns 'Hello \$name'",
            'nfr'   => "\$volt->addFunction(new VoltFunction('year', fn () => date('Y')));\n\$volt->addFunction(new VoltFunction('greeting', fn (string \$name) => 'Hello ' . \$name));",
        ],
        'run'   => static function (Harness $h): array {
            $setup = $h->flavor === 'nfr'
                ? static function (NfrVolt $volt): void {
                    $volt->addFunction(new VoltFunction('year', static fn (): string => date('Y')));
                    $volt->addFunction(new VoltFunction('greeting', static fn (string $name): string => 'Hello ' . $name));
                }
                : static function (StockVolt $volt): void {
                    $volt->getCompiler()->addFunction('year', static fn (): string => date('Y'));
                    $volt->getCompiler()->addFunction('greeting', static fn (string $args): string => 'Hello ' . $args);
                };

            return [
                'compile {{ year() }}'           => $h->compile('{{ year() }}', [], $setup),
                'compile {{ greeting(name) }}'   => $h->compile('{{ greeting(name) }}', [], $setup),
            ];
        },
    ],
    'E6' => [
        'title' => 'Functions backed by a service, safe HTML, custom tests',
        'intro' => 'An extension class lists functions and tests; `[\'prices\', \'format\']` is resolved from the DI container the first time a template calls it. `stars()` returns HTML and is declared safe, so autoescape leaves it alone. Today: no array callables, no safe flag, no test API (an unknown test compiles to `==`).',
        'files' => [
            'product' => "{{ price(product.price) }} {{ stars(product.rating) }}\n{% if user is premium %}Free shipping{% endif %}{% if user is not premium %}Shipping: {{ price(4.9) }}{% endif %}",
        ],
        'setup' => [
            'stock' => "// no equivalent: addFunction('price', ['prices', 'format']) throws InvalidUserFunctionDefinition",
            'nfr'   => "\$di->setShared('prices', Prices::class);\n\$volt->addExtension(new ShopExtension());  // price, stars (safe), premium test",
        ],
        'run'   => static function (Harness $h): array {
            if ($h->flavor !== 'nfr') {
                return ['compile {% if user is premium %}' => $h->compile('{% if user is premium %}x{% endif %}')];
            }

            $h->di->setShared('prices', Prices::class);
            $setup   = static fn (NfrVolt $volt) => $volt->addExtension(new ShopExtension());
            $product = (object) ['price' => 19.5, 'rating' => 2];

            return [
                'render, premium user' => $h->render('product', ['product' => $product, 'user' => (object) ['plan' => 'premium']], ['autoescape' => true], $setup),
                'render, free user'    => $h->render('product', ['product' => $product, 'user' => (object) ['plan' => 'free']], ['autoescape' => true], $setup),
                'Prices instances'     => (string) Prices::$built,
                'compile {{ price(p) }}' => $h->compile('{{ price(p) }}', [], $setup),
                'typo: user is premiun'  => $h->compile('{% if user is premiun %}x{% endif %}', [], $setup),
            ];
        },
    ],
    'E7' => [
        'title' => 'Escaping that is not applied twice',
        'intro' => 'With autoescape on, today every echo is wrapped in `escaper->html()`, including escaping filters, and there is no `raw`.',
        'files' => [],
        'run'   => static fn (Harness $h): array => [
            'compile {{ name|e }}'         => $h->compile('{{ name|e }}', ['autoescape' => true]),
            'compile {{ data|escape_js }}' => $h->compile('{{ data|escape_js }}', ['autoescape' => true]),
            'compile {{ html|raw }}'       => $h->compile('{{ html|raw }}', ['autoescape' => true]),
        ],
    ],
    'E8' => [
        'title' => 'Null coalescing and null-safe access',
        'intro' => '`|default` uses `empty()`, so `0` is replaced too; a missing relation fails with "Attempt to read property on null".',
        'files' => [
            'invoice' => "{{ invoice.customer?.name ?? \"(no customer)\" }} | discount: {{ invoice.discount ?? \"none\" }} | {{ invoice.discount|default(\"none\") }}",
        ],
        'run'   => static fn (Harness $h): array => [
            'render, customer=null, discount=0' => $h->render('invoice', ['invoice' => (object) ['customer' => null, 'discount' => 0]]),
        ],
    ],
    'E9' => [
        'title' => 'Editing a layout or a partial',
        'intro' => 'Parents and static includes are inlined into the compiled child. Today only the child\'s own mtime is checked, so the edit is invisible until the cache is cleared; the prototype records what was inlined and checks it.',
        'files' => [
            'layout' => "v1 {% block content %}{% endblock %}",
            'page'   => "{% extends \"layout.volt\" %}{% block content %}page{% endblock %}",
        ],
        'run'   => static function (Harness $h): array {
            $before = $h->render('page');
            $h->edit('layout', 'v2 {% block content %}{% endblock %}');

            return ['render page' => $before, 'edit layout.volt (v2), render page' => $h->render('page')];
        },
    ],
    'E10' => [
        'title' => 'include ... with keeps the template\'s variables',
        'intro' => 'Today adding `with` turns a compiled include into `$this->partial()`, which only sees the View\'s variables.',
        'files' => [
            'row'  => "<tr><td>{{ label }}</td><td>{{ currency }} {{ amount }}</td></tr>",
            'page' => "{% set currency = \"EUR\" %}\n{% include \"row\" with [\"label\": \"Total\", \"amount\": 12] %}",
        ],
        'run'   => static fn (Harness $h): array => ['render page' => trim($h->render('page'))],
    ],
];

// ------------------------------------------------------------------ worker

if (preg_match('/^--worker=(stock|nfr)$/', $argv[1] ?? '', $m)) {
    $results = [];
    foreach ($examples as $id => $example) {
        $h        = new Harness($m[1]);
        $warnings = [];
        set_error_handler(static function (int $no, string $message) use (&$warnings, $h): bool {
            if (error_reporting() & $no) { // not silenced with @
                $warnings[] = $h->clean($message);
            }

            return true;
        });
        $h->views($example['files']);
        $results[$id] = $example['run']($h);
        restore_error_handler();
        if ($warnings !== []) {
            $results[$id]['PHP warnings'] = implode('; ', array_unique($warnings));
        }
    }
    echo json_encode($results, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);
    exit(0);
}

// ------------------------------------------------------------------ driver

$here    = dirname(__DIR__);
$worker  = static function (string $flavor, string $so) use ($here): array {
    $cmd = escapeshellarg(PHP_BINARY) . ' -d extension=' . escapeshellarg($so) . ' '
        . escapeshellarg(__FILE__) . ' --worker=' . $flavor;
    $out = shell_exec($cmd);

    return json_decode((string) $out, true, flags: JSON_THROW_ON_ERROR);
};

$stock = $worker('stock', $here . '/.build/stock/ext/modules/phalcon.so');
$nfr   = $worker('nfr', $here . '/.build/patched/ext/modules/phalcon.so');

$md   = [];
$md[] = '# Volt NFR: examples, today vs proposed';
$md[] = '';
$md[] = 'Generated by `prototype/tools/examples.php`; every output below was produced by running the';
$md[] = 'template. "Today" is the stock extension built from upstream master (5.23.0). "Proposed" is the';
$md[] = 'patched parser (`prototype/patches/volt-parser.patch`) with the prototype engine';
$md[] = '(`Phalcon\\VoltNfr\\Volt`). Regenerate with `./run.sh tools/examples.php --write`.';

foreach ($examples as $id => $example) {
    $md[] = '';
    $md[] = "## $id. {$example['title']}";
    $md[] = '';
    $md[] = $example['intro'];
    foreach ($example['files'] as $name => $source) {
        $md[] = '';
        $md[] = "`$name.volt`";
        $md[] = '```twig';
        $md[] = $source;
        $md[] = '```';
    }
    foreach (['stock' => 'Setup today', 'nfr' => 'Setup proposed'] as $flavor => $label) {
        if (isset($example['setup'][$flavor])) {
            $md[] = '';
            $md[] = "$label:";
            $md[] = '```php';
            $md[] = $example['setup'][$flavor];
            $md[] = '```';
        }
    }
    foreach (['Today' => $stock[$id], 'Proposed' => $nfr[$id]] as $label => $outputs) {
        $md[] = '';
        $md[] = "**$label**";
        $md[] = '```text';
        foreach ($outputs as $what => $output) {
            $md[] = $what . ' → ' . $output;
        }
        $md[] = '```';
    }
}

$document = implode("\n", $md) . "\n";
$target   = dirname($here) . '/examples.md';

if (in_array('--write', $argv, true)) {
    file_put_contents($target, $document);
    echo "wrote $target\n";
    exit(0);
}

if (!is_file($target) || file_get_contents($target) !== $document) {
    echo "examples.md drifted from the real output; run with --write and review the diff\n";
    exit(1);
}

echo "examples.md matches the real output\n";
