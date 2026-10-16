<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Compiler;

/**
 * Output of FindCompiler: the Dialect definition, the SQL the dialect produced from it, the bind
 * data for the Pdo adapter, and how to hydrate (into the model, or into Row objects when the
 * caller picked columns, exactly like PHQL does today).
 */
final class CompiledQuery
{
    /**
     * @param array<string, mixed>     $definition what Phalcon\Db\Dialect::select() consumed
     * @param array<int|string, mixed> $bind
     * @param array<int|string, int>   $bindTypes
     */
    public function __construct(
        public readonly string $modelClass,
        public readonly array $definition,
        public readonly string $sql,
        public readonly array $bind,
        public readonly array $bindTypes,
        public readonly bool $hydrateRows,
    ) {
    }
}
