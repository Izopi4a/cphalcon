<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Compiler;

use Phalcon\Db\Column;
use Phalcon\Mvc\Model\ManagerInterface;
use Phalcon\Mvc\Model\MetaDataInterface;
use Phalcon\Mvc\ModelInterface;

/**
 * Model::find() parameters -> Phalcon\Db\Dialect::select() definition, with no PHQL string, no
 * parser and no AST.
 *
 * Today:  params -> Builder::getPhql() -> "SELECT [Model].* FROM [Model] WHERE ..." -> C parser ->
 *         AST -> Query::prepareSelect() -> IR -> Dialect::select(IR) -> SQL
 * Here:   params -> definition (built from model metadata) -> Dialect::select(definition) -> SQL
 *
 * The structured parts (FROM, the default column list, LIMIT/OFFSET, DISTINCT, FOR UPDATE) come
 * from metadata exactly like the IR does. The opaque parts (conditions, order, group, having,
 * columns) are raw SQL: FragmentRewriter fixes placeholders and columnMap names, and the Dialect
 * emits them verbatim through its existing `literal` expression type (Dialect.zep:259).
 *
 * Supported find() keys: 0/conditions, bind, bindTypes, columns, order, group, having, limit,
 * offset, distinct, for_update. Not in this prototype: cache, hydration, models/joins (that is
 * the Builder milestone), shared_lock, transaction.
 */
final class FindCompiler
{
    public function __construct(
        private readonly ManagerInterface $manager,
        private readonly MetaDataInterface $metaData,
    ) {
    }

    /**
     * @param array<string|int, mixed>|string|null $params same shape as Model::find($params)
     */
    public function compile(string $modelClass, array|string|null $params = null): CompiledQuery
    {
        $params = match (true) {
            $params === null   => [],
            is_string($params) => [$params],
            default            => $params,
        };

        /** @var ModelInterface $model */
        $model      = $this->manager->load($modelClass);
        $connection = $model->getReadConnection();
        $dialect    = $connection->getDialect();
        $source     = $model->getSource();
        $schema     = $model->getSchema() ?: null;
        $bind       = $params['bind'] ?? [];
        $bindTypes  = $params['bindTypes'] ?? [];

        $rewriter = new FragmentRewriter(
            $this->metaData->getReverseColumnMap($model),
            [$source, $modelClass, ltrim($modelClass, '\\')],
            $modelClass,
            $source,
        );
        $raw = static fn (string $sql): array => ['type' => 'literal', 'value' => $rewriter->rewrite($sql, $bind)];

        $definition = [
            'models' => [$modelClass],
            'tables' => [[$source, $schema, null]],
        ];

        // Columns: the model's own columns qualified by its table (what "[Model].*" expands to),
        // or the caller's raw list, which hydrates into Row objects like PHQL does.
        $columns     = $params['columns'] ?? null;
        $hydrateRows = $columns !== null;
        $definition['columns'] = $hydrateRows
            ? $this->columnItems(is_array($columns) ? implode(', ', $columns) : (string) $columns, $rewriter, $model, $bind)
            : array_map(static fn (string $column): array => [$column, $source], $this->metaData->getAttributes($model));

        $conditions = $params['conditions'] ?? $params[0] ?? null;
        if (is_string($conditions) && $conditions !== '') {
            $definition['where'] = $raw($conditions);
        }
        if (!empty($params['group'])) {
            $definition['group'] = [$raw(is_array($params['group']) ? implode(', ', $params['group']) : $params['group'])];
        }
        if (!empty($params['having'])) {
            $definition['having'] = $raw($params['having']);
        }
        if (!empty($params['order'])) {
            $definition['order'] = [[$raw(is_array($params['order']) ? implode(', ', $params['order']) : $params['order'])]];
        }

        // LIMIT/OFFSET become placeholders, same names and types PHQL uses (APL0/APL1, int)
        if (isset($params['limit'])) {
            $limit = ['number' => ['type' => 'placeholder', 'value' => ':APL0']];
            $bind['APL0']      = (int) $params['limit'];
            $bindTypes['APL0'] = Column::BIND_PARAM_INT;
            if (isset($params['offset'])) {
                $limit['offset']   = ['type' => 'placeholder', 'value' => ':APL1'];
                $bind['APL1']      = (int) $params['offset'];
                $bindTypes['APL1'] = Column::BIND_PARAM_INT;
            }
            $definition['limit'] = $limit;
        }
        if (!empty($params['distinct'])) {
            $definition['distinct'] = true;
        }
        if (!empty($params['for_update'])) {
            $definition['forUpdate'] = true;
        }

        // PHQL hands the Pdo adapter numeric binds as ":0", ":1" (see Query::executeSelect); same here
        $pdoBind = [];
        foreach ($bind as $key => $value) {
            $pdoBind[is_int($key) ? ':' . $key : $key] = $value;
        }

        return new CompiledQuery($modelClass, $definition, $dialect->select($definition), $pdoBind, $bindTypes, $hydrateRows);
    }

    /**
     * Splits a raw columns string on top-level commas so a bare mapped property ("name") becomes
     * "cst_name AS name", which is how PHQL names Row keys for a columnMap model.
     *
     * @return list<array<string, mixed>>
     */
    private function columnItems(string $columns, FragmentRewriter $rewriter, ModelInterface $model, array $bind): array
    {
        $map   = $this->metaData->getReverseColumnMap($model);
        $items = [];
        foreach ($this->splitTopLevel($columns) as $item) {
            $item = trim($item);
            if ($map !== null && isset($map[$item])) {
                $items[] = ['type' => 'literal', 'value' => $map[$item] . ' AS ' . $item];
                continue;
            }
            $items[] = ['type' => 'literal', 'value' => $rewriter->rewrite($item, $bind)];
        }

        return $items;
    }

    /**
     * @return list<string>
     */
    private function splitTopLevel(string $sql): array
    {
        $parts = [];
        $depth = 0;
        $quote = null;
        $buf   = '';
        foreach (str_split($sql) as $c) {
            if ($quote !== null) {
                $quote = $c === $quote ? null : $quote;
            } elseif ($c === "'" || $c === '"' || $c === '`') {
                $quote = $c;
            } elseif ($c === '(') {
                $depth++;
            } elseif ($c === ')') {
                $depth--;
            } elseif ($c === ',' && $depth === 0) {
                $parts[] = $buf;
                $buf     = '';
                continue;
            }
            $buf .= $c;
        }
        $parts[] = $buf;

        return $parts;
    }
}
