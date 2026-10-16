<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests;

use Phalcon\NativeSql\Compiler\FragmentRewriter;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

/**
 * The rewriter is the whole replacement for the grammar on the find() path, so its contract is
 * spelled out case by case: what it rewrites, and everything it must leave alone.
 */
final class FragmentRewriterTest extends TestCase
{
    private const MODEL = 'App\\Models\\Customers';

    /**
     * @return iterable<string, array{0: string, 1: string, 2?: array<string, mixed>}>
     */
    public static function cases(): iterable
    {
        // placeholders
        yield ':name:'               => ['a = :a:', 'a = :a'];
        yield '?0 ?1'                => ['a = ?0 OR b = ?1', 'a = :0 OR b = :1'];
        yield '{name}'               => ['a = {a}', 'a = :a'];
        yield '{name:int}'           => ['a = {a:int}', 'a = :a'];
        yield '{name:array}'         => ['ref IN ({ids:array})', 'ref IN (:ids0, :ids1, :ids2)', ['ids' => [1, 2, 3]]];
        yield 'PDO :name untouched'  => ['a = :a', 'a = :a'];

        // columnMap
        yield 'bare property'        => ['name = :n:', 'cst_name = :n'];
        yield 'two properties'       => ['name = :n: AND createdAt > 0', 'cst_name = :n AND cst_created > 0'];
        yield 'table.property'       => ['customers.name = 1', 'customers.cst_name = 1'];
        yield '[Model].property'     => ['[App\\Models\\Customers].name = 1', 'customers.cst_name = 1'];
        yield 'other domain kept'    => ['o.name = 1', 'o.name = 1'];
        yield 'function name kept'   => ['name(1) = 1', 'name(1) = 1'];
        yield 'AS alias kept'        => ['COUNT(*) AS name', 'COUNT(*) AS name'];
        yield 'unmapped identifier'  => ['email = 1', 'email = 1'];
        yield 'keywords untouched'   => ['name IS NOT NULL ORDER', 'cst_name IS NOT NULL ORDER'];

        // must never be touched
        yield 'string literal'       => ["name = 'name :x: ?0 {y}'", "cst_name = 'name :x: ?0 {y}'"];
        yield 'escaped quote'        => ["name = 'it''s name'", "cst_name = 'it''s name'"];
        yield 'quoted identifier'    => ['"name" = 1', '"name" = 1'];
        yield 'backtick identifier'  => ['`name` = 1', '`name` = 1'];
        yield 'pg :: cast'           => ['id::text = :v:', 'cst_id::text = :v'];
        yield 'json operators'       => ["meta ->> '$.a' = 1", "meta ->> '$.a' = 1"];
        yield 'window clause'        => ['ROW_NUMBER() OVER (PARTITION BY name ORDER BY id)', 'ROW_NUMBER() OVER (PARTITION BY cst_name ORDER BY cst_id)'];
        yield 'union'                => ['id IN (SELECT 1 UNION ALL SELECT 2)', 'cst_id IN (SELECT 1 UNION ALL SELECT 2)'];
    }

    #[DataProvider('cases')]
    public function testRewrite(string $in, string $expected, array $bind = []): void
    {
        $rewriter = new FragmentRewriter(
            ['id' => 'cst_id', 'name' => 'cst_name', 'createdAt' => 'cst_created'],
            ['customers', self::MODEL],
            self::MODEL,
            'customers',
        );

        self::assertSame($expected, $rewriter->rewrite($in, $bind));
    }

    public function testWithoutColumnMapOnlyPlaceholdersChange(): void
    {
        $rewriter = new FragmentRewriter(null, ['users'], 'App\\Users', 'users');

        self::assertSame('name = :n AND id IN (:i0, :i1)', $rewriter->rewrite('name = :n: AND id IN ({i:array})', ['i' => [1, 2]]));
    }

    public function testEmptyArrayBindIsRejected(): void
    {
        $this->expectException(\InvalidArgumentException::class);
        (new FragmentRewriter(null, [], 'X', 'x'))->rewrite('id IN ({ids:array})', ['ids' => []]);
    }

    public function testUnterminatedStringIsRejected(): void
    {
        $this->expectException(\InvalidArgumentException::class);
        (new FragmentRewriter(null, [], 'X', 'x'))->rewrite("name = 'oops");
    }
}
