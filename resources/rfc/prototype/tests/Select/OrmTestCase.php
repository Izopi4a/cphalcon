<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Db\Adapter\Pdo\Sqlite;
use Phalcon\Di\Di;
use Phalcon\Di\FactoryDefault;
use Phalcon\Events\Manager as EventsManager;
use Phalcon\Form\FormFactory;
use Phalcon\Mvc\Model\Manager as ModelsManager;
use Phalcon\Mvc\Model\MetaData\Memory as MemoryMetaData;
use PHPUnit\Framework\TestCase;

/**
 * In-memory SQLite + FactoryDefault DI (db, modelsManager, modelsMetadata) with the Orm fixtures'
 * tables seeded, and a query log on the connection's events manager ("db:beforeQuery").
 *
 * Phalcon models find their DI through Di::getDefault(); FactoryDefault registers itself as the
 * default on construction and tearDown() resets it.
 *
 * Seed (insertion order):
 *   countries: 1 France/Europe, 2 Sweden/Europe, 3 Japan/Asia, 4 Brazil/South America
 *   cities:    1 Paris/1, 2 Tokyo/3, 3 Stockholm/2
 *   translations: (en, greeting) Hello, (fr, greeting) Bonjour, (en, farewell) Bye
 */
abstract class OrmTestCase extends TestCase
{
    protected FormFactory $factory;
    protected FactoryDefault $di;
    protected Sqlite $db;
    /** @var list<string> every SQL statement sent to the connection, in order */
    protected array $queryLog = [];

    protected function setUp(): void
    {
        Di::reset();

        $this->factory = new FormFactory();
        $this->di      = new FactoryDefault();
        $this->db      = new Sqlite(['dbname' => ':memory:']);

        $events = new EventsManager();
        $events->attach('db:beforeQuery', function ($event, Sqlite $connection): void {
            $this->queryLog[] = $connection->getSQLStatement();
        });
        $this->db->setEventsManager($events);

        $this->di->setShared('db', $this->db);
        $this->di->setShared('modelsManager', new ModelsManager());
        $this->di->setShared('modelsMetadata', new MemoryMetaData());

        $this->db->execute('CREATE TABLE countries (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, continent TEXT)');
        $this->db->execute('CREATE TABLE cities (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, country_id INTEGER)');
        $this->db->execute('CREATE TABLE translations (locale TEXT NOT NULL, key_name TEXT NOT NULL, text TEXT, PRIMARY KEY (locale, key_name))');
        $this->db->execute("INSERT INTO countries (name, continent) VALUES ('France', 'Europe'), ('Sweden', 'Europe'), ('Japan', 'Asia'), ('Brazil', 'South America')");
        $this->db->execute("INSERT INTO cities (name, country_id) VALUES ('Paris', 1), ('Tokyo', 3), ('Stockholm', 2)");
        $this->db->execute("INSERT INTO translations (locale, key_name, text) VALUES ('en', 'greeting', 'Hello'), ('fr', 'greeting', 'Bonjour'), ('en', 'farewell', 'Bye')");

        $this->queryLog = [];
    }

    protected function tearDown(): void
    {
        Di::reset();
    }

    /**
     * The row-fetching SELECTs since the last reset: Phalcon's metadata introspection
     * (sqlite_master, PRAGMA) and the COUNT(*) "numrows" wrapper a Simple resultset issues on
     * SQLite are left out, so one find() = one entry.
     *
     * @return list<string>
     */
    protected function selectQueries(): array
    {
        return array_values(array_filter($this->queryLog, static fn (string $sql): bool => str_starts_with($sql, 'SELECT "')));
    }

    protected function resetQueryLog(): void
    {
        $this->queryLog = [];
    }
}
