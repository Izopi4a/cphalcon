<?php

/**
 * Prints every stage a child template goes through, today and in the
 * prototype, for walkthrough.md.
 *
 *   ./run.sh tools/trace.php
 */

declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Di\FactoryDefault;
use Phalcon\Mvc\View\Engine\Volt\Compiler as StockCompiler;
use Phalcon\Mvc\View\Simple;
use Phalcon\VoltNfr\Compiler as NfrCompiler;
use Phalcon\VoltNfr\Inheritance\Resolver;
use Phalcon\VoltNfr\Runtime\VoltFunction;
use Phalcon\VoltNfr\Volt;

$dir = sys_get_temp_dir() . '/volt-trace-' . getmypid() . '/';
@mkdir($dir . 'stock', 0777, true);
@mkdir($dir . 'nfr', 0777, true);

$files = [
    'layout.volt' => '<h1>{% block title %}Shop{% endblock %}</h1>{% block content %}{% endblock %}',
    'page.volt'   => '{% extends "layout.volt" %}{% block title %}Orders{% endblock %}{% block content %}{{ count }} open{% endblock %}',
];
foreach ($files as $name => $source) {
    file_put_contents($dir . $name, $source);
}

$compact = static function (array $node) use (&$compact): array {
    unset($node['file'], $node['line']);
    foreach ($node as $key => $value) {
        if (is_array($value)) {
            $node[$key] = $compact($value);
        }
    }

    return $node;
};
$show = static fn (string $title, string $body) => print("### $title\n\n```\n" . rtrim(str_replace($dir, '/views/', $body)) . "\n```\n\n");

foreach ($files as $name => $source) {
    $show("source: $name", $source);
}

$view = new Simple();
$view->setViewsDir($dir);

// --- today ------------------------------------------------------------------
$stock = new StockCompiler($view);
$show('1. parse(page.volt): the AST, an array (file/line keys removed)', json_encode($compact($stock->parse($files['page.volt'])), JSON_PRETTY_PRINT));

$stock->setOptions(['path' => $dir . 'stock/', 'always' => true]);
$stock->compile($dir . 'page.volt');
foreach (glob($dir . 'stock/*') as $compiled) {
    $show('2. today, cache file ' . basename($compiled), file_get_contents($compiled));
}

// --- prototype ----------------------------------------------------------------
$nfr = new NfrCompiler($view);
$nfr->setOptions(['path' => $dir . 'nfr/', 'always' => true]);
$resolved = (new Resolver($nfr))->resolve($nfr->parseSource($files['page.volt'], $dir . 'page.volt'), $dir . 'page.volt');
$show('3. prototype, Resolver::resolve(): the flat AST handed to statementList()', json_encode($compact($resolved), JSON_PRETTY_PRINT));

$nfr->compile($dir . 'page.volt');
foreach (glob($dir . 'nfr/*') as $compiled) {
    $show('4. prototype, cache file ' . basename($compiled), file_get_contents($compiled));
}

// --- runtime function -----------------------------------------------------------
$volt = new Volt($view, new FactoryDefault());
$volt->addFunction(new VoltFunction('money', ['prices', 'format']));
$volt->addFunction(new VoltFunction('ucwords', 'ucwords'));
$show(
    '5. prototype, runtime functions: a callable is compiled to a direct call or a registry lookup',
    $volt->getCompiler()->compileString('{{ ucwords(name) }} {{ money(total, "EUR") }}')
);
