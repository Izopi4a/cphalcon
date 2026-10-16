<?php

declare(strict_types=1);

use Phalcon\Db\Adapter\Pdo\Postgresql;
use Phalcon\Di\FactoryDefault;
use Phalcon\Events\Manager as EventsManager;

if (!extension_loaded('phalcon')) {
    fwrite(STDERR, "The phalcon extension is not loaded, start through ./run.sh or ./spin\n");
    exit(1);
}

require __DIR__ . '/models.php';

/**
 * Every SQL statement the adapter runs, for showing what the ORM produced
 */
final class SqlLog
{
    /** @var list<array{sql: string, bind: array}> */
    public static array $entries = [];
    public static bool $enabled  = true;

    public static function reset(): void
    {
        self::$entries = [];
    }
}

function spinDi(): FactoryDefault
{
    $env = parse_ini_file(__DIR__ . '/.env');
    $di  = new FactoryDefault();

    $di->setShared('db', function () use ($env) {
        $db = new Postgresql([
            'host'     => $env['DB_HOST'],
            'port'     => (int) $env['DB_PORT'],
            'dbname'   => $env['DB_NAME'],
            'username' => $env['DB_USER'],
            'password' => $env['DB_PASS'],
        ]);

        $events = new EventsManager();
        $events->attach('db:beforeQuery', function ($event, $connection) {
            if (SqlLog::$enabled) {
                SqlLog::$entries[] = [
                    'sql'  => $connection->getSQLStatement(),
                    'bind' => $connection->getSqlVariables() ?? [],
                ];
            }
        });
        $db->setEventsManager($events);

        return $db;
    });

    return $di;
}

/**
 * Loads model metadata once, so the SQL log only shows the queries a
 * scenario runs
 */
function warmMetadata(): void
{
    SqlLog::$enabled = false;
    foreach ([Customer::class, Order::class, Product::class, OrderItem::class] as $class) {
        (new $class())->getModelsMetaData()->getAttributes(new $class());
    }
    SqlLog::$enabled = true;
}

/**
 * Anything a scenario returns, as plain data for display
 */
function plain(mixed $value, int $maxRows = 6): mixed
{
    if ($value instanceof Phalcon\Mvc\Model\ResultsetInterface) {
        $rows = [];
        $all  = count($value);
        foreach ($value as $i => $row) {
            if ($i >= $maxRows) {
                break;
            }
            $rows[] = plain($row);
        }
        return ['rows' => $rows, 'count' => $all, 'class' => (new ReflectionClass($value))->getShortName()];
    }

    if ($value instanceof Phalcon\Mvc\Model\Row) {
        $out = [];
        foreach (get_object_vars($value) as $k => $v) {
            $out[$k] = plain($v);
        }
        return $out;
    }

    if ($value instanceof Phalcon\Mvc\ModelInterface) {
        return [get_class($value) => $value->toArray()];
    }

    if ($value instanceof Phalcon\Paginator\RepositoryInterface) {
        return [
            'page'  => $value->getCurrent() . ' / ' . $value->getLast(),
            'total' => $value->getTotalItems(),
            'items' => plain($value->getItems(), 3),
        ];
    }

    if (is_array($value)) {
        return array_map(fn ($v) => plain($v, $maxRows), $value);
    }

    return $value;
}
