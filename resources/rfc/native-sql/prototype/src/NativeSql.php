<?php
declare(strict_types=1);

namespace Phalcon\NativeSql;

use Phalcon\Di\Di;
use Phalcon\Mvc\Model\ManagerInterface;
use Phalcon\Mvc\Model\MetaDataInterface;
use Phalcon\Mvc\Model\Resultset\Simple;
use Phalcon\Mvc\Model\ResultsetInterface;
use Phalcon\Mvc\Model\Row;
use Phalcon\Mvc\ModelInterface;
use Phalcon\NativeSql\Compiler\CompiledQuery;
use Phalcon\NativeSql\Compiler\FindCompiler;
use Phalcon\NativeSql\Db\CountedResult;

/**
 * The two entry points the RFC proposes, as plain functions over today's 7.0.x classes:
 *
 *   find($class, $params)        Model::find() semantics, compiled straight to the Dialect
 *   findBySql($class, $sql, ...) any SQL the database accepts, hydrated into the model
 *   rows($sql, ...)              any SQL, hydrated into Phalcon\Mvc\Model\Row
 *
 * Hydration is the code path Query::executeSelect() uses for a single-model query
 * (Query.zep:1295-1400): Resultset\Simple with the model's columnMap and the manager's
 * keepSnapshots flag. Nothing here touches the PHQL parser. Results go through CountedResult so
 * multi-line and WITH statements are counted correctly on SQLite (see that class).
 */
final class NativeSql
{
    /**
     * @param array<string|int, mixed>|string|null $params
     */
    public static function find(string $modelClass, array|string|null $params = null): ResultsetInterface
    {
        return self::execute(self::compiler()->compile($modelClass, $params));
    }

    /**
     * @param array<string|int, mixed>|string|null $params
     */
    public static function findFirst(string $modelClass, array|string|null $params = null): ?ModelInterface
    {
        $params = is_string($params) ? [$params] : ($params ?? []);
        $first  = self::find($modelClass, ['limit' => 1] + $params)->getFirst();

        return $first instanceof ModelInterface ? $first : null;
    }

    /**
     * Raw SQL -> models. The statement must return the model's real column names (e.g.
     * "SELECT u.* FROM users u ..."); the columnMap is applied on hydration.
     *
     * @param array<int|string, mixed> $bind
     * @param array<int|string, int>   $bindTypes
     */
    public static function findBySql(string $modelClass, string $sql, array $bind = [], array $bindTypes = []): ResultsetInterface
    {
        $manager = self::manager();
        $model   = $manager->load($modelClass);
        $result  = CountedResult::query($model->getReadConnection(), $sql, $bind, $bindTypes);

        return new Simple(
            self::metaData()->getColumnMap($model),
            $model,
            $result,
            null,
            (bool) $manager->isKeepingSnapshots($model),
        );
    }

    /**
     * Raw SQL -> Row objects (scalars, aggregates, window functions, anything).
     *
     * @param array<int|string, mixed> $bind
     * @param array<int|string, int>   $bindTypes
     */
    public static function rows(string $sql, array $bind = [], array $bindTypes = [], string $connectionService = 'db'): ResultsetInterface
    {
        $result = CountedResult::query(Di::getDefault()->getShared($connectionService), $sql, $bind, $bindTypes);

        return new Simple(null, new Row(), $result, null, false);
    }

    public static function execute(CompiledQuery $compiled): ResultsetInterface
    {
        if ($compiled->hydrateRows) {
            $model  = self::manager()->load($compiled->modelClass);
            $result = CountedResult::query($model->getReadConnection(), $compiled->sql, $compiled->bind, $compiled->bindTypes);

            return new Simple(null, new Row(), $result, null, false);
        }

        return self::findBySql($compiled->modelClass, $compiled->sql, $compiled->bind, $compiled->bindTypes);
    }

    public static function compiler(): FindCompiler
    {
        return new FindCompiler(self::manager(), self::metaData());
    }

    private static function manager(): ManagerInterface
    {
        return Di::getDefault()->getShared('modelsManager');
    }

    private static function metaData(): MetaDataInterface
    {
        return Di::getDefault()->getShared('modelsMetadata');
    }
}
