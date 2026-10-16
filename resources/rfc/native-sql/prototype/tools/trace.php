<?php
/**
 * Prints every stage of today's query pipeline for a few find() / Builder calls:
 *
 *   1. PHQL     Builder::getPhql()               the string find() serialises its params into
 *   2. AST      Query\Lang::parsePHQL()          what the C parser (scanner.re + parser.php.lemon) returns
 *   3. IR       Query::parse()                   AST resolved against models metadata (tables, columnMap, joins)
 *   4. SQL      Query::getSql()                  Dialect::select(IR) + bind params, without executing
 *   5. EXEC     db:beforeQuery log + result      what PDO actually received, and what came back
 *
 * and, for the find() cases, the proposed path next to it:
 *
 *   N1. DEFINITION  FindCompiler::compile()      find() params -> Dialect::select() definition,
 *                                                built from metadata; raw fragments as `literal`
 *   N2. SQL         Dialect::select(definition)  what PDO receives on the native path
 *
 * Usage: ./run.sh tools/trace.php [case-number] [--full]
 *   --full prints the complete AST/IR instead of the abbreviated form.
 */
declare(strict_types=1);

require __DIR__ . '/../autoload.php';

use Phalcon\Mvc\Model\Query\Builder;
use Phalcon\Mvc\Model\Query\Lang;
use Phalcon\NativeSql\NativeSql;
use Phalcon\NativeSql\Tests\Fixtures\Customers;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Orders;
use Phalcon\NativeSql\Tests\Fixtures\Users;

$only = null;
$full = false;
foreach (array_slice($argv, 1) as $arg) {
    $arg === '--full' ? $full = true : $only = (int) $arg;
}

$fixtures = new Database();
$manager  = $fixtures->di->getShared('modelsManager');

/**
 * Each case returns the Builder exactly as Model::find()/getPreparedQuery() would build it
 * (createBuilder(params)->from(static::class)), or a hand-written Builder. Cases with find()
 * params also show the native path for the same params.
 *
 * @var array<int, array{0: string, 1: callable(): Builder, 2?: array{0: class-string, 1: array}}>
 */
$find = static fn (string $class, array $params): array => [
    static fn () => $manager->createBuilder($params)->from($class),
    [$class, $params],
];
$cases = [
    1 => ['Users::find("created_at > datetime(\'now\', \'-7 days\')")',
        ...$find(Users::class, ["created_at > datetime('now', '-7 days')"])],
    2 => ['Users::find([conditions: country = :c:, bind, order, limit])',
        ...$find(Users::class, ['conditions' => 'country = :c:', 'bind' => ['c' => 'BG'], 'order' => 'name DESC', 'limit' => 5])],
    3 => ['Customers::find("name LIKE :n:")  (model with columnMap)',
        ...$find(Customers::class, ['conditions' => 'name LIKE :n:', 'bind' => ['n' => 'A%'], 'order' => 'createdAt'])],
    4 => ['Users::find("id IN ({ids:array})")',
        ...$find(Users::class, ['id IN ({ids:array})', 'bind' => ['ids' => [1, 2, 4]]])],
    5 => ['Builder: u.*, o.* FROM Users u JOIN Orders o  (implicit join from relation)', fn () => $manager
        ->createBuilder()->columns('u.*, o.*')->addFrom(Users::class, 'u')->join(Orders::class, null, 'o')
        ->where('o.total > :min:', ['min' => 20])],
    6 => ['Builder: COUNT(*) per country  (scalar columns, group, having)', fn () => $manager
        ->createBuilder()->columns('u.country, COUNT(*) AS n')->addFrom(Users::class, 'u')
        ->groupBy('u.country')->having('COUNT(*) > 1')],
];

foreach ($cases as $n => $case) {
    [$label, $make] = $case;
    $native = $case[2] ?? null;
    if ($only !== null && $only !== $n) {
        continue;
    }

    echo str_repeat('=', 100), "\n#{$n}  {$label}\n", str_repeat('=', 100), "\n";

    /** @var Builder $builder */
    $builder = $make();

    $phql = $builder->getPhql();
    echo "1. PHQL\n   {$phql}\n";

    $ast = Lang::parsePHQL($phql);
    echo "2. AST  (C parser)\n", indent(dump($full ? $ast : abbreviate($ast))), "\n";

    $query = $builder->getQuery();
    $ir    = $query->parse();
    echo "3. IR   (Query::parse, handed to Dialect::select)\n", indent(dump($full ? $ir : abbreviate($ir))), "\n";

    $sql = $query->getSql();
    echo "4. SQL  (Query::getSql)\n   {$sql['sql']}\n";
    if ($sql['bind'] !== []) {
        echo '   bind: ', json_encode($sql['bind']), '  types: ', json_encode($sql['bindTypes']), "\n";
    }

    $fixtures->resetLog();
    $result = $query->execute();
    $rows   = $result->toArray();
    echo "5. EXEC\n";
    foreach ($fixtures->selects() as $statement) {
        echo "   PDO <- {$statement}\n";
    }
    printf("   -> %s, %d row(s)%s\n\n", $result::class, count($rows), $rows === [] ? '' : ', first: ' . json_encode(firstRow($result)));

    if ($native !== null) {
        [$class, $params] = $native;
        $compiled = NativeSql::compiler()->compile($class, $params);
        echo "N1. DEFINITION  (FindCompiler, no PHQL / parser / AST / IR)\n", indent(dump($full ? $compiled->definition : abbreviate($compiled->definition))), "\n";
        echo "N2. SQL  (Dialect::select(definition))\n   {$compiled->sql}\n";
        if ($compiled->bind !== []) {
            echo '   bind: ', json_encode($compiled->bind), '  types: ', json_encode($compiled->bindTypes), "\n";
        }
        $nativeRows = NativeSql::execute($compiled)->toArray();
        printf("   -> %d row(s), %s\n\n", count($nativeRows), $nativeRows === $rows ? 'same rows as the PHQL path' : 'DIFFERENT rows from the PHQL path');
    }
}

\Phalcon\Di\Di::reset();

// ---------------------------------------------------------------------------------------------

function dump(mixed $value): string
{
    return json_encode($value, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE);
}

function indent(string $text): string
{
    return preg_replace('/^/m', '   ', $text);
}

/**
 * Collapses expression trees deeper than 4 levels so the shape stays readable.
 */
function abbreviate(mixed $value, int $depth = 0): mixed
{
    if (!is_array($value)) {
        return $value;
    }
    if ($depth >= 4) {
        return '…';
    }
    $out = [];
    foreach ($value as $key => $item) {
        $out[$key] = abbreviate($item, $depth + 1);
    }

    return $out;
}

function firstRow(\Phalcon\Mvc\Model\ResultsetInterface $result): mixed
{
    $row = $result->getFirst();
    if ($row instanceof \Phalcon\Mvc\ModelInterface) {
        return [$row::class => $row->toArray()];
    }
    if ($row instanceof \Phalcon\Mvc\Model\Row) {
        $out = [];
        foreach ($row->toArray() as $key => $value) {
            $out[$key] = $value instanceof \Phalcon\Mvc\ModelInterface ? [$value::class => $value->toArray()] : $value;
        }

        return $out;
    }

    return $row;
}
