<?php

declare(strict_types=1);

use Phalcon\Mvc\Micro;

require dirname(__DIR__) . '/bootstrap.php';
require dirname(__DIR__) . '/runner.php';

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
  <nav><a href="/">Scenarios</a><a href="/playground">Playground</a></nav>
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

$app->notFound(function () {
    http_response_code(404);
    echo layout('Not found', '<h1>Not found</h1>');
});

$app->handle($_SERVER['REQUEST_URI']);
