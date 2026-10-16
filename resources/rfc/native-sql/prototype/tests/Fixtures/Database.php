<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests\Fixtures;

use Phalcon\Db\Adapter\Pdo\Sqlite;
use Phalcon\Di\Di;
use Phalcon\Di\FactoryDefault;
use Phalcon\Events\Manager as EventsManager;
use Phalcon\Mvc\Model\Manager as ModelsManager;
use Phalcon\Mvc\Model\MetaData\Memory as MemoryMetaData;

/**
 * In-memory SQLite + FactoryDefault DI (db, modelsManager, modelsMetadata), seeded fixtures and a
 * log of every SQL statement sent to the connection ("db:beforeQuery").
 *
 * Phalcon models find their DI through Di::getDefault(); FactoryDefault registers itself as the
 * default on construction. Call Di::reset() when done.
 *
 * Seed:
 *   users:     1 Ana/BG/active, 2 Ben/SE/active, 3 Cleo/BG/inactive, 4 Dan/JP/active
 *   orders:    1 Ana 10.5, 2 Ana 99.0, 3 Ben 5.0, 4 Dan 42.0
 *   customers: 1 Acme, 2 Globex
 */
final class Database
{
    /** @var list<string> */
    public array $log = [];

    public readonly FactoryDefault $di;
    public readonly Sqlite $db;

    public function __construct()
    {
        Di::reset();

        $this->di = new FactoryDefault();
        $this->db = new Sqlite(['dbname' => ':memory:']);

        $this->db->execute('CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, email TEXT, country TEXT, active INTEGER NOT NULL DEFAULT 1, created_at TEXT)');
        $this->db->execute('CREATE TABLE orders (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, total REAL NOT NULL, created_at TEXT)');
        $this->db->execute('CREATE TABLE customers (cst_id INTEGER PRIMARY KEY AUTOINCREMENT, cst_name TEXT NOT NULL, cst_created TEXT)');

        $this->db->execute("INSERT INTO users (name, email, country, active, created_at) VALUES
            ('Ana',  'ana@example.com',  'BG', 1, datetime('now', '-2 days')),
            ('Ben',  'ben@example.com',  'SE', 1, datetime('now', '-30 days')),
            ('Cleo', 'cleo@example.com', 'BG', 0, datetime('now', '-1 days')),
            ('Dan',  'dan@example.com',  'JP', 1, datetime('now', '-400 days'))");
        $this->db->execute("INSERT INTO orders (user_id, total, created_at) VALUES
            (1, 10.5, datetime('now', '-1 days')), (1, 99.0, datetime('now')), (2, 5.0, datetime('now', '-3 days')), (4, 42.0, datetime('now'))");
        $this->db->execute("INSERT INTO customers (cst_name, cst_created) VALUES ('Acme', datetime('now')), ('Globex', datetime('now', '-10 days'))");

        $events = new EventsManager();
        $events->attach('db:beforeQuery', function ($event, Sqlite $connection): void {
            $this->log[] = $connection->getSQLStatement();
        });
        $this->db->setEventsManager($events);

        $this->di->setShared('db', $this->db);
        $this->di->setShared('modelsManager', new ModelsManager());
        $this->di->setShared('modelsMetadata', new MemoryMetaData());
    }

    /**
     * Statements that fetch rows: drops metadata introspection (sqlite_master, PRAGMA) and the
     * "numrows" COUNT(*) wrappers issued on SQLite, both Phalcon's (PdoResult::numRows) and the
     * prototype's (CountedResult).
     *
     * @return list<string>
     */
    public function selects(): array
    {
        return array_values(array_filter(
            $this->log,
            static fn (string $sql): bool => !str_contains($sql, 'sqlite_master')
                && !str_starts_with($sql, 'PRAGMA')
                && !str_starts_with($sql, 'SELECT COUNT(*) "numrows"')
                && !str_starts_with($sql, 'SELECT COUNT(*) AS "numrows"')
        ));
    }

    public function resetLog(): void
    {
        $this->log = [];
    }
}
