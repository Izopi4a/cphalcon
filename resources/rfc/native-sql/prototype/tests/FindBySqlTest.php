<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests;

use Phalcon\Db\Column;
use Phalcon\Di\Di;
use Phalcon\Mvc\Model\Resultset\Simple;
use Phalcon\Mvc\Model\Row;
use Phalcon\NativeSql\NativeSql;
use Phalcon\NativeSql\Tests\Fixtures\Customers;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Users;
use PHPUnit\Framework\TestCase;

/**
 * Whole statements PHQL cannot express (CTE, UNION ALL, window functions, derived tables),
 * hydrated into models or rows with the same resultset classes find() returns.
 */
final class FindBySqlTest extends TestCase
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

    public function testCteIntoModels(): void
    {
        $users = Users::findBySql(
            'WITH big AS (SELECT user_id FROM orders WHERE total > :min)
             SELECT u.* FROM users u WHERE u.id IN (SELECT user_id FROM big) ORDER BY u.id',
            ['min' => 40],
        );

        self::assertInstanceOf(Simple::class, $users);
        self::assertInstanceOf(Users::class, $users->getFirst());
        self::assertSame(['Ana', 'Dan'], array_column($users->toArray(), 'name'));
    }

    public function testColumnMapAppliedOnHydration(): void
    {
        // raw SQL returns real column names; the model gets its properties
        $customers = Customers::findBySql('SELECT * FROM customers WHERE cst_id IN (SELECT 1 UNION ALL SELECT 2) ORDER BY cst_id DESC');

        self::assertSame(
            [['id' => 2, 'name' => 'Globex'], ['id' => 1, 'name' => 'Acme']],
            array_map(static fn (array $c): array => ['id' => $c['id'], 'name' => $c['name']], $customers->toArray()),
        );
    }

    public function testModelsFromRawSqlKeepSnapshotsAndSave(): void
    {
        $this->fixtures->di->getShared('modelsManager')->keepSnapshots(new Users(), true);

        $ana = Users::findBySql("SELECT * FROM users WHERE name = 'Ana'")->getFirst();
        self::assertTrue($ana->hasSnapshotData());

        $ana->country = 'GR';
        self::assertSame(['country'], $ana->getChangedFields());
        self::assertTrue($ana->save());
        self::assertSame('GR', Users::findFirst(1)->country);
    }

    public function testWindowFunctionIntoRows(): void
    {
        $rows = NativeSql::rows(
            'SELECT u.name, SUM(o.total) AS spent, RANK() OVER (ORDER BY SUM(o.total) DESC) AS place
             FROM users u JOIN orders o ON o.user_id = u.id GROUP BY u.id ORDER BY place',
        );

        self::assertInstanceOf(Row::class, $rows->getFirst());
        self::assertSame(
            [['name' => 'Ana', 'spent' => 109.5, 'place' => 1], ['name' => 'Dan', 'spent' => 42.0, 'place' => 2], ['name' => 'Ben', 'spent' => 5.0, 'place' => 3]],
            $rows->toArray(),
        );
    }

    public function testDerivedTableIntoRows(): void
    {
        // int bind type matters: on SQLite COUNT(*) > '1' (text) is always false
        $rows = NativeSql::rows(
            'SELECT t.country, t.n FROM (SELECT country, COUNT(*) AS n FROM users GROUP BY country) t WHERE t.n > :n',
            ['n' => 1],
            ['n' => Column::BIND_PARAM_INT],
        );

        self::assertSame([['country' => 'BG', 'n' => 2]], $rows->toArray());
    }

    public function testEmptyResult(): void
    {
        $users = Users::findBySql('SELECT * FROM users WHERE 1 = 0');

        self::assertCount(0, $users);
        self::assertNull($users->getFirst());
    }
}
