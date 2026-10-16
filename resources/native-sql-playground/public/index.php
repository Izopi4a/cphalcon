<?php

declare(strict_types=1);

use Phalcon\Mvc\Micro;

require dirname(__DIR__) . '/bootstrap.php';
require dirname(__DIR__) . '/runner.php';
require dirname(__DIR__) . '/volt.php';

// php -S: let the built-in server hand out static files
if (PHP_SAPI === 'cli-server' && is_file(__DIR__ . parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH))) {
    return false;
}

function e(mixed $value): string
{
    return htmlspecialchars((string) $value, ENT_QUOTES);
}

function json(mixed $value): string
{
    return e(json_encode($value, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES));
}

function sqlBlock(array $run): string
{
    $html = '';
    foreach ($run['sql'] as $q) {
        $bind  = $q['bind'] ? '<div class="bind">' . e(json_encode($q['bind'], JSON_UNESCAPED_UNICODE)) . '</div>' : '';
        $html .= '<pre class="sql">' . e(preg_replace('/\s+/', ' ', trim($q['sql']))) . '</pre>' . $bind;
    }
    return $html;
}

function runPanel(?array $run, string $label): string
{
    if ($run === null) {
        return '<div class="panel muted"><h4>' . e($label) . '</h4><p>Not compiled by either path: the statement goes to PDO as written.</p></div>';
    }
    $status = $run['ok']
        ? '<span class="ok">ok</span>'
        : '<span class="err">failed</span>';
    $body = $run['ok']
        ? '<details open><summary>result</summary><pre class="result">' . json($run['result']) . '</pre></details>'
        : '<pre class="error">' . e($run['error']) . '</pre>';

    return sprintf(
        '<div class="panel"><h4>%s %s <small>%.1f ms</small></h4>%s%s</div>',
        e($label),
        $status,
        $run['ms'],
        sqlBlock($run),
        $body
    );
}

function layout(string $title, string $body): string
{
    return <<<HTML
<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{$title}</title>
<link rel="stylesheet" href="/style.css">
</head>
<body>
<header>
  <strong>native-sql-spin</strong>
  <nav><a href="/">SQL scenarios</a><a href="/playground">SQL playground</a><a href="/volt">Volt</a><a href="/volt/try">Volt playground</a></nav>
</header>
<main>{$body}</main>
</body>
</html>
HTML;
}

$app = new Micro(spinDi());

$app->get('/', function () use ($app) {
    warmMetadata();
    $results = runAll($app->getDI());

    $labels = [
        'same'        => 'same result on both paths',
        'native-only' => 'PHQL fails, native works',
        'api'         => 'new native SQL API',
        'differs'     => 'results differ',
        'REGRESSION'  => 'native fails, PHQL works',
        'both-fail'   => 'both fail',
    ];
    $tally = array_count_values(array_column($results, 'verdict'));
    $chips = '';
    foreach ($tally as $verdict => $n) {
        $chips .= sprintf('<span class="chip v-%s">%d %s</span>', e($verdict), $n, e($labels[$verdict]));
    }

    $body  = '<h1>PHQL vs native compiler</h1>';
    $body .= '<p class="lead">Every scenario runs twice in one request: with <code>orm.native_compiler</code> off (today\'s PHQL parser) and on (straight to SQL). Database: PostgreSQL, <code>phalcon_spin</code>.</p>';
    $body .= '<div class="chips">' . $chips . '</div>';

    $group = null;
    foreach ($results as $s) {
        if ($s['group'] !== $group) {
            $group = $s['group'];
            $body .= '<h2>' . e($group) . '</h2>';
        }
        $body .= sprintf(
            '<section class="card"><div class="card-head"><span class="num">#%d</span><h3>%s</h3><span class="chip v-%s">%s</span></div><pre class="code">%s</pre><div class="cols">%s%s</div></section>',
            $s['index'],
            e($s['title']),
            e($s['verdict']),
            e($labels[$s['verdict']]),
            e($s['source']),
            runPanel($s['phql'], 'PHQL'),
            runPanel($s['native'], 'native')
        );
    }

    echo layout('PHQL vs native', $body);
});

$app->map('/playground', function () use ($app) {
    $request = $app->request;
    $models  = ['Customer', 'Order', 'Product', 'OrderItem'];

    $model  = in_array($request->get('model'), $models, true) ? $request->get('model') : 'Order';
    $method = in_array($request->get('method'), ['find', 'findFirst', 'count'], true) ? $request->get('method') : 'find';
    $params = $request->get('params') ?? json_encode([
        'conditions' => "createdAt > NOW() - INTERVAL '7 days' AND status <> :status:",
        'bind'       => ['status' => 'cancelled'],
        'order'      => 'createdAt DESC',
        'limit'      => 5,
    ], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);
    $sql = $request->get('sql') ?? "SELECT cst_country AS country, COUNT(*) AS customers\n  FROM customers\n GROUP BY cst_country\n ORDER BY customers DESC";
    $sqlTarget = $request->get('target') === 'findBySql' ? 'findBySql' : 'nativeQuery';

    $output = '';
    if ($request->isPost()) {
        warmMetadata();
        if ($request->getPost('run') === 'find') {
            $decoded = json_decode($params, true);
            if (!is_array($decoded) && !is_string($decoded)) {
                $output = '<pre class="error">params must be a JSON object or string: ' . e(json_last_error_msg()) . '</pre>';
            } else {
                $scenario = ['run' => fn () => $model::$method($decoded)];
                $output   = '<div class="cols">' . runPanel(runScenario($scenario, $app->getDI(), false), 'PHQL')
                    . runPanel(runScenario($scenario, $app->getDI(), true), 'native') . '</div>';
            }
        } else {
            $scenario = ['run' => fn ($di) => $sqlTarget === 'findBySql'
                ? $model::findBySql($sql)
                : $di->getShared('modelsManager')->nativeQuery($sql)];
            $output = '<div class="cols single">' . runPanel(runScenario($scenario, $app->getDI(), true), $sqlTarget) . '</div>';
        }
    }

    $options = fn (array $list, string $selected) => implode('', array_map(
        fn ($v) => sprintf('<option%s>%s</option>', $v === $selected ? ' selected' : '', e($v)),
        $list
    ));

    $body = '<h1>Playground</h1>
<p class="lead">Each statement runs inside a transaction that is committed; scenarios that write are yours to undo. Reset everything with <code>./spin seed.php</code>.</p>
<form method="post" class="play">
  <fieldset>
    <legend>Model::find() family, both paths</legend>
    <div class="row">
      <label>Model <select name="model">' . $options($models, $model) . '</select></label>
      <label>Method <select name="method">' . $options(['find', 'findFirst', 'count'], $method) . '</select></label>
    </div>
    <label>Parameters (JSON: the array you would pass, or a string)<textarea name="params" rows="8" spellcheck="false">' . e($params) . '</textarea></label>
    <button name="run" value="find">Run on PHQL and native</button>
  </fieldset>
  <fieldset>
    <legend>Native SQL</legend>
    <div class="row">
      <label>Through <select name="target">' . $options(['nativeQuery', 'findBySql'], $sqlTarget) . '</select></label>
      <span class="hint">findBySql hydrates the model picked above; select its real columns</span>
    </div>
    <label>SQL<textarea name="sql" rows="6" spellcheck="false">' . e($sql) . '</textarea></label>
    <button name="run" value="sql">Run</button>
  </fieldset>
</form>' . $output;

    echo layout('Playground', $body);
})->via(['GET', 'POST']);

$app->get('/volt', function () use ($app) {
    warmMetadata();

    $body  = '<h1>Volt on this branch</h1>';
    $body .= '<p class="lead">Every card renders its templates through View\Simple and the Volt engine on this request, shows the compiled PHP, and says what happens without the change. Variables come from the same shop database as the SQL scenarios.</p>';

    $group = null;
    foreach (voltScenarios() as $index => $scenario) {
        if ($scenario['group'] !== $group) {
            $group = $scenario['group'];
            $body .= '<h2>' . e($group) . '</h2>';
        }

        $result = renderVoltScenario($scenario, $app->getDI());
        $ok     = !in_array(false, array_map(fn ($r) => $r['error'] === null, $result['renders']), true);
        $files  = '';
        foreach ($scenario['files'] as $name => $source) {
            $files .= '<div class="file"><div class="file-name">' . e($name) . '.volt</div><pre class="code">' . e($source) . '</pre></div>';
        }

        $outputs = '';
        foreach ($result['renders'] as $render) {
            $label = $render['vars'] ? '<div class="file-name">' . e(json_encode($render['vars'], JSON_UNESCAPED_SLASHES)) . '</div>' : '';
            $outputs .= $label . ($render['error'] !== null
                ? '<pre class="error">' . e($render['error']) . '</pre>'
                : '<div class="rendered">' . $render['output'] . '</div><pre class="html">' . e(trim($render['output'])) . '</pre>');
        }

        $deps = $result['deps'] ? '<details><summary>dependency sidecar (.deps.php)</summary><pre class="result">' . json($result['deps']) . '</pre></details>' : '';

        $body .= sprintf(
            '<section class="card"><div class="card-head"><span class="num">#%d</span><h3>%s</h3><span class="chip %s">%s</span></div>'
            . '<p class="today"><b>Today:</b> %s</p>'
            . '<div class="cols"><div class="panel"><h4>templates</h4>%s</div><div class="panel"><h4>rendered</h4>%s'
            . '<details><summary>compiled PHP</summary><pre class="sql">%s</pre></details>%s</div></div></section>',
            $index + 1,
            e($scenario['title']),
            $ok ? 'v-same' : 'v-api',
            $ok ? 'works' : 'compile error (by design)',
            e($scenario['today']),
            $files,
            $outputs,
            e((string) $result['compiled']),
            $deps
        );
    }

    echo layout('Volt', $body);
});

$app->map('/volt/try', function () use ($app) {
    $request  = $app->request;
    $template = $request->get('template') ?? "{# runtime functions: price(), stars(), now(); filters: money, initials; tests: local, shipped #}\n"
        . "{% set shown = customers|length %}\n"
        . "<h3>{% block title %}Customers{% endblock %}</h3>\n"
        . "{% for c in customers %}\n"
        . "  <p>{{ c.name|initials }} · {{ c.name }}{% if c is local %} {{ stars(3) }}{% endif %} · {{ c.orders?.count() ?? 0 }} orders</p>\n"
        . "{% endfor %}\n"
        . "<p>{{ shown }} shown · {{ 1999.5|money('currency': 'BGN') }} · {{ 9 // 2 }} · {{ block(\"title\") }} again</p>";
    $autoescape = $request->isPost() ? (bool) $request->getPost('autoescape') : true;

    $output = '';
    if ($request->isPost()) {
        warmMetadata();
        $scenario = [
            'files'   => ['page' => $template],
            'vars'    => fn () => ['customers' => Customer::find(['order' => 'id', 'limit' => 5]), 'orders' => Order::count()],
            'options' => ['autoescape' => $autoescape],
        ];
        $result = renderVoltScenario($scenario, $app->getDI());
        $render = $result['renders'][0];
        $output = '<div class="cols"><div class="panel"><h4>rendered</h4>'
            . ($render['error'] !== null ? '<pre class="error">' . e($render['error']) . '</pre>' : '<div class="rendered">' . $render['output'] . '</div><pre class="html">' . e(trim($render['output'])) . '</pre>')
            . '</div><div class="panel"><h4>compiled PHP</h4><pre class="sql">' . e((string) $result['compiled']) . '</pre></div></div>';
    }

    $body = '<h1>Volt playground</h1>
<p class="lead">Variables: <code>customers</code> (5 Customer models, with the <code>orders</code> relation) and <code>orders</code> (a count). The ShopExtension is registered: functions <code>price()</code>, <code>stars()</code> (safe), <code>now()</code>; filters <code>money</code>, <code>initials</code>; tests <code>local</code>, <code>shipped</code>.</p>
<form method="post" class="play">
  <fieldset>
    <legend>Template</legend>
    <label><input type="checkbox" name="autoescape" value="1"' . ($autoescape ? ' checked' : '') . '> autoescape</label>
    <textarea name="template" rows="12" spellcheck="false">' . e($template) . '</textarea>
    <button>Render</button>
  </fieldset>
</form>' . $output;

    echo layout('Volt playground', $body);
})->via(['GET', 'POST']);

$app->notFound(function () {
    http_response_code(404);
    echo layout('Not found', '<h1>Not found</h1>');
});

$app->handle($_SERVER['REQUEST_URI']);
