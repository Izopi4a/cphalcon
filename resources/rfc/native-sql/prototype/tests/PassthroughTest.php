<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests;

use Phalcon\Di\Di;
use Phalcon\Mvc\Model\Exception as ModelException;
use Phalcon\Mvc\Model\Row;
use Phalcon\NativeSql\Tests\Fixtures\Customers;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Users;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

/**
 * The other half of the claim: the same find() call, with SQL the database understands but the
 * PHQL grammar does not, throws today and works on the native path.
 *
 * Each case asserts both: PHQL refuses it (so the test documents the current limit and will
 * flag it if 7.0.x grows the grammar), and the native path returns the expected ids.
 */
final class PassthroughTest extends TestCase
{
    protected function setUp(): void
    {
        new Database();
    }

    protected function tearDown(): void
    {
        Di::reset();
    }

    /**
     * Seed: users 1 Ana/BG/active, 2 Ben/SE/active, 3 Cleo/BG/inactive, 4 Dan/JP/active;
     * orders: Ana 10.5 + 99.0, Ben 5.0, Dan 42.0.
     *
     * @return iterable<string, array{0: array<string|int, mixed>, 1: list<int>}>
     */
    public static function refusedByPhql(): iterable
    {
        yield 'UNION inside IN (...)' => [
            ['id IN (SELECT user_id FROM orders WHERE total > 40 UNION SELECT 3)', 'order' => 'id'],
            [1, 3, 4],
        ];
        yield 'searched CASE in ORDER BY' => [
            ['order' => "CASE WHEN country = 'BG' THEN 0 ELSE 1 END, id"],
            [1, 3, 2, 4],
        ];
        yield 'LIKE ... ESCAPE' => [
            ["name LIKE 'A!%' ESCAPE '!' OR name LIKE 'B%'"],
            [2],
        ];
        yield 'string concat ||' => [
            ["name || '@' || country = :tag:", 'bind' => ['tag' => 'Dan@JP']],
            [4],
        ];
        yield 'JSON ->> operator' => [
            ["json_object('c', country) ->> '$.c' = 'SE'"],
            [2],
        ];
        yield 'NULLS LAST' => [
            ['order' => 'email DESC NULLS LAST, id'],
            [4, 3, 2, 1],
        ];
        yield 'row-value IN' => [
            ["(country, active) IN (VALUES ('BG', 0), ('JP', 1))", 'order' => 'id'],
            [3, 4],
        ];
    }

    #[DataProvider('refusedByPhql')]
    public function testPhqlRefusesAndNativePassesThrough(array $params, array $expectedIds): void
    {
        $params = FindParityTest::detach($params);

        $this->expectPhqlSyntaxError(static fn () => Users::find($params));

        self::assertSame($expectedIds, array_column(Users::findNative($params)->toArray(), 'id'));
    }

    public function testWindowFunctionInColumnsHydratesRows(): void
    {
        $params = ['columns' => 'id, ROW_NUMBER() OVER (PARTITION BY country ORDER BY id DESC) AS rn', 'order' => 'id'];

        $this->expectPhqlSyntaxError(static fn () => Users::find($params));

        $rows = Users::findNative($params);
        self::assertInstanceOf(Row::class, $rows->getFirst());
        self::assertSame(
            [['id' => 1, 'rn' => 2], ['id' => 2, 'rn' => 1], ['id' => 3, 'rn' => 1], ['id' => 4, 'rn' => 1]],
            $rows->toArray(),
        );
    }

    public function testColumnMapStillAppliesInsidePassthroughSql(): void
    {
        // "name" and "createdAt" are properties; the DB only knows cst_name / cst_created.
        $params = ["CASE WHEN name LIKE 'A%' THEN 1 ELSE 0 END = 1 AND createdAt IS NOT NULL"];

        $this->expectPhqlSyntaxError(static fn () => Customers::find($params));

        self::assertSame(['Acme'], array_column(Customers::findNative($params)->toArray(), 'name'));
    }

    /**
     * The parser (Lemon: "Syntax error, ...") or the scanner (re2c: "Scanner: Unknown opcode ...",
     * e.g. for ||) rejects the statement before anything reaches the database.
     */
    private function expectPhqlSyntaxError(callable $call): void
    {
        try {
            $call();
            self::fail('PHQL accepted this; the case no longer documents a limit, move it to FindParityTest');
        } catch (ModelException $e) {
            self::assertMatchesRegularExpression('/^(Syntax error|Scanner: )/', $e->getMessage());
        }
    }
}
