<?php
declare(strict_types=1);

namespace Phalcon\NativeSql;

use Phalcon\Mvc\Model\ResultsetInterface;
use Phalcon\Mvc\ModelInterface;

/**
 * What the API looks like on a model. In v7 these would be Model::find()/findFirst() themselves
 * (same signature, new backend) plus a new Model::findBySql(); here they sit next to the
 * existing methods so tests can compare both paths on the same fixtures.
 */
trait NativeFinder
{
    /**
     * @param array<string|int, mixed>|string|null $params
     */
    public static function findNative(array|string|null $params = null): ResultsetInterface
    {
        return NativeSql::find(static::class, $params);
    }

    /**
     * @param array<string|int, mixed>|string|null $params
     */
    public static function findFirstNative(array|string|null $params = null): ?ModelInterface
    {
        return NativeSql::findFirst(static::class, $params);
    }

    /**
     * @param array<int|string, mixed> $bind
     * @param array<int|string, int>   $bindTypes
     */
    public static function findBySql(string $sql, array $bind = [], array $bindTypes = []): ResultsetInterface
    {
        return NativeSql::findBySql(static::class, $sql, $bind, $bindTypes);
    }
}
