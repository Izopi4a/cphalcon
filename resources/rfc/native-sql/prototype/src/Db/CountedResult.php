<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Db;

use Phalcon\Db\Adapter\AdapterInterface;
use Phalcon\Db\Result\PdoResult;

/**
 * A PdoResult whose row count is known up front.
 *
 * Why it exists: Resultset::__construct() calls numRows() immediately. On drivers without a
 * reliable rowCount() (everything except mysql/pgsql, i.e. SQLite) PdoResult::numRows()
 * (PdoResult.zep:278-337) emulates it with preg_match("/^SELECT\s+(.*)/i") and re-runs
 * "SELECT COUNT(*) FROM (SELECT <match>)". That regex has no /s flag and requires a leading
 * SELECT, so a multi-line statement is truncated at the first newline (the COUNT query fails)
 * and a statement starting with WITH is counted as 0 rows (the resultset looks empty).
 *
 * The prototype counts by wrapping the whole statement instead, which also covers CTEs,
 * comments and newlines. The RFC proposes the same change inside PdoResult::numRows().
 */
final class CountedResult extends PdoResult
{
    /**
     * @param array<int|string, mixed> $bind
     * @param array<int|string, int>   $bindTypes
     */
    public static function query(AdapterInterface $connection, string $sql, array $bind = [], array $bindTypes = []): ?PdoResult
    {
        $result = $connection->query($sql, $bind, $bindTypes);
        if (!$result instanceof PdoResult) {
            return null;
        }
        if (in_array($connection->getType(), ['mysql', 'pgsql'], true)) {
            return $result;
        }

        // same binds AND types as the real statement (fetchColumn() takes no types, and on SQLite
        // an int-vs-text bind changes the result of a comparison)
        $counted = $connection->query('SELECT COUNT(*) AS "numrows" FROM (' . rtrim(trim($sql), ';') . "\n)", $bind, $bindTypes);
        $counted->setFetchMode(\Phalcon\Db\Enum::FETCH_ASSOC);
        $count = (int) ($counted->fetch()['numrows'] ?? 0);

        return new self($connection, $result->getInternalResult(), $sql, $bind, $bindTypes, $count);
    }

    /**
     * @param array<int|string, mixed> $bind
     * @param array<int|string, int>   $bindTypes
     */
    public function __construct(AdapterInterface $connection, \PDOStatement $statement, string $sql, array $bind, array $bindTypes, int $count)
    {
        parent::__construct($connection, $statement, $sql, $bind, $bindTypes);
        $this->rowCount = $count;
    }
}
