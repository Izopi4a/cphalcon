<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests;

use Phalcon\Di\Di;
use Phalcon\Mvc\Model\Row;
use Phalcon\NativeSql\Tests\Fixtures\Customers;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Users;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\TestCase;

/**
 * The claim to prove: Model::find() keeps its exact behaviour when its parameters compile
 * straight to the Dialect definition instead of going through PHQL.
 *
 * Every case runs both paths on the same database and compares the hydrated result (classes and
 * values), not the SQL text: the two SQL strings legitimately differ (PHQL quotes and qualifies
 * every column, the native path passes the user's fragment through).
 */
final class FindParityTest extends TestCase
{
    private Database $fixtures;

    protected function setUp(): void
    {
        $this->fixtures = new Database();
    }

    protected function tearDown(): void
    {
        Di::reset();
    }

    /**
     * @return iterable<string, array{0: class-string, 1: array<string|int, mixed>|string|null}>
     */
    public static function findParams(): iterable
    {
        yield 'no params'                         => [Users::class, null];
        yield 'string condition with a function'  => [Users::class, "created_at > datetime('now', '-7 days')"];
        yield 'named bind :c:'                    => [Users::class, ['conditions' => 'country = :c:', 'bind' => ['c' => 'BG']]];
        yield 'conditions as key 0'               => [Users::class, ['active = :a:', 'bind' => ['a' => 1]]];
        yield 'positional bind ?0 ?1'             => [Users::class, ['id = ?0 OR id = ?1', 'bind' => [1, 2]]];
        yield '{ids:array}'                       => [Users::class, ['id IN ({ids:array})', 'bind' => ['ids' => [1, 4]]]];
        yield '{name} brace placeholder'          => [Users::class, ['name = {name}', 'bind' => ['name' => 'Ben']]];
        yield 'order + limit'                     => [Users::class, ['order' => 'name DESC', 'limit' => 2]];
        yield 'limit + offset'                    => [Users::class, ['order' => 'id', 'limit' => 2, 'offset' => 1]];
        yield 'distinct'                          => [Users::class, ['distinct' => true, 'order' => 'id']];
        yield 'bracketed model name in condition' => [Users::class, ['[' . Users::class . '].active = 1']];
        yield 'columns -> Row'                    => [Users::class, ['columns' => 'id, name', 'order' => 'id']];
        yield 'aggregate + group + having'        => [Users::class, ['columns' => 'country, COUNT(*) AS n', 'group' => 'country', 'having' => 'COUNT(*) > 1']];
        yield 'columnMap: condition on property'  => [Customers::class, ['name LIKE :n:', 'bind' => ['n' => 'A%']]];
        yield 'columnMap: order on property'      => [Customers::class, ['order' => 'createdAt DESC']];
        yield 'columnMap: columns -> Row'         => [Customers::class, ['columns' => 'id, name', 'order' => 'id']];
        yield 'columnMap: bracketed model'        => [Customers::class, ['[' . Customers::class . '].id > 1']];
    }

    #[DataProvider('findParams')]
    public function testNativeFindMatchesPhqlFind(string $class, array|string|null $params): void
    {
        // PHPUnit hands nested provider arrays over as PHP references, and on 7.0.x the Zephir
        // kernel drops referenced find() params (see Findings/ReferenceParamsTest). Compare the two
        // paths, not that bug.
        $params = self::detach($params);

        $viaPhql   = $class::find($params);
        $viaNative = $class::findNative($params);

        self::assertSame($this->shape($viaPhql), $this->shape($viaNative));
        self::assertNotEmpty($viaNative->toArray(), 'fixture should produce rows for a meaningful comparison');
    }

    public function testFindFirstMatches(): void
    {
        $phql   = Users::findFirst(['country = :c:', 'bind' => ['c' => 'SE']]);
        $native = Users::findFirstNative(['country = :c:', 'bind' => ['c' => 'SE']]);

        self::assertInstanceOf(Users::class, $native);
        self::assertSame($phql->toArray(), $native->toArray());
    }

    public function testNativeFindIssuesOneStatementAndNoParserWork(): void
    {
        // warm the metadata so only the row query is left in the log
        Users::findNative(['id = 1']);
        $this->fixtures->resetLog();

        Users::findNative(['country = :c:', 'bind' => ['c' => 'BG'], 'order' => 'name', 'limit' => 5]);

        self::assertSame(
            ['SELECT "users"."id", "users"."name", "users"."email", "users"."country", "users"."active", "users"."created_at" FROM "users" WHERE country = :c ORDER BY name LIMIT :APL0'],
            $this->fixtures->selects(),
        );
    }

    public function testHydratedModelsAreFullModels(): void
    {
        $customer = Customers::findFirstNative(['name = :n:', 'bind' => ['n' => 'Acme']]);

        self::assertInstanceOf(Customers::class, $customer);
        self::assertSame('Acme', $customer->name);

        $customer->name = 'Acme Ltd';
        self::assertTrue($customer->save(), implode(', ', array_map('strval', $customer->getMessages())));
        self::assertSame('Acme Ltd', Customers::findFirst(1)->name);
    }

    /**
     * A copy of the value with every PHP reference replaced by its value.
     */
    public static function detach(mixed $value): mixed
    {
        return is_array($value) ? array_map(self::detach(...), $value) : $value;
    }

    /**
     * Resultset class, element classes and values, in order.
     *
     * @return list<array{0: class-string, 1: array<string, mixed>}>
     */
    private function shape(iterable $resultset): array
    {
        $out = [];
        foreach ($resultset as $row) {
            $out[] = [$row::class, $row->toArray()];
        }

        return $out;
    }
}
