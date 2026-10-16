<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Inheritance;

use Phalcon\VoltNfr\Compiler;
use Phalcon\VoltNfr\Exception;
use Phalcon\VoltNfr\Node;

/**
 * Template inheritance resolved on the AST, before anything is compiled.
 *
 * Today Volt compiles the parent into a name => compiled-PHP map (serialized
 * into a "%%e%%" cache file) and splices the child's compiled blocks into it.
 * That model has one flat level of names and one "current block", which is
 * why blocks cannot nest (base.c refuses them) and why extends only takes a
 * string literal.
 *
 * Here the chain leaf -> ... -> root is loaded as ASTs, every level's blocks
 * are collected by name (at any depth), and the root's statements are
 * expanded: each {% block %} node is replaced by the statements of its most
 * derived definition, recursively. super() expands the next definition up the
 * chain. The result is one flat statement list (no extends/block/embed nodes)
 * that the stock statementList() compiles as before. Same output model as
 * today (one PHP file per rendered template, no runtime block dispatch).
 */
final class Resolver
{
    /**
     * Leaf first, root last.
     *
     * @var list<array{path: string, blocks: array<string, array>}>
     */
    private array $levels = [];

    /** @var array<string, true> blocks being expanded (cycle guard) */
    private array $expanding = [];

    public function __construct(private Compiler $compiler)
    {
    }

    /**
     * @return list<array> statements with no extends, block or embed nodes
     */
    public function resolve(array $ast, string $path): array
    {
        $extends = $this->findExtends($ast);

        if ($extends !== null && !$this->isLiteral($extends['path'])) {
            $override = $this->compiler->takeExtendsOverride();
            if ($override === null) {
                return $this->dynamicExtends($extends, $path);
            }
            $ast = $this->withExtendsPath($ast, $override);
        }

        return $this->resolveChain($ast, $path);
    }

    private function resolveChain(array $ast, string $path): array
    {
        $this->levels = [];
        $seen         = [$path => true];
        $current      = $ast;
        $currentPath  = $path;

        while (true) {
            $this->levels[] = ['path' => $currentPath, 'blocks' => $this->collectBlocks($current, $currentPath)];

            $extends = $this->findExtends($current);
            if ($extends === null) {
                break;
            }

            if (!$this->isLiteral($extends['path'])) {
                throw $this->error('Only the rendered template may extend a variable', $extends);
            }

            $parentPath = $this->compiler->resolveTemplatePath($extends['path']['value'], $currentPath);
            if (isset($seen[$parentPath])) {
                throw $this->error("Circular inheritance: $parentPath", $extends);
            }
            $seen[$parentPath] = true;

            $current     = $this->compiler->parseFile($parentPath);
            $currentPath = $parentPath;
        }

        return $this->expand($current, null);
    }

    /**
     * @return list<array>
     */
    private function expand(array $statements, ?array $context): array
    {
        $out = [];

        foreach ($statements as $statement) {
            $type = $statement['type'] ?? null;

            if ($type === Node::EXTENDS) {
                continue;
            }

            if ($type === Node::BLOCK) {
                array_push($out, ...$this->expandBlock($statement['name'], $statement));
                continue;
            }

            if ($type === Node::EMBED) {
                array_push($out, ...$this->expandEmbed($statement));
                continue;
            }

            if ($type === Node::ECHO && Node::isCall($statement['expr'], 'super')) {
                array_push($out, ...$this->expandSuper($context, $statement));
                continue;
            }

            if ($type === Node::ECHO && Node::isCall($statement['expr'], 'block')) {
                array_push($out, ...$this->expandBlockFunction($statement['expr']));
                continue;
            }

            foreach (Node::CONTAINERS as $key) {
                if (isset($statement[$key]) && is_array($statement[$key])) {
                    $statement[$key] = $this->expand($statement[$key], $context);
                }
            }

            $out[] = $statement;
        }

        return $out;
    }

    /**
     * A {% block %} node: the most derived definition of that name.
     */
    private function expandBlock(string $name, array $node): array
    {
        foreach ($this->levels as $index => $level) {
            if (isset($level['blocks'][$name])) {
                return $this->expandBlockAt($name, $index);
            }
        }

        throw $this->error("Block '$name' is not defined", $node);
    }

    private function expandBlockAt(string $name, int $index): array
    {
        $key = $name . '@' . $index;
        if (isset($this->expanding[$key])) {
            throw $this->error("Block '$name' renders itself", $this->levels[$index]['blocks'][$name]);
        }

        $this->expanding[$key] = true;

        try {
            return $this->expand(
                $this->levels[$index]['blocks'][$name]['block_statements'] ?? [],
                ['name' => $name, 'level' => $index]
            );
        } finally {
            unset($this->expanding[$key]);
        }
    }

    /**
     * {{ super() }}: the definition of the current block one level up.
     */
    private function expandSuper(?array $context, array $node): array
    {
        if ($context === null) {
            throw $this->error('super() can only be used inside a block', $node);
        }

        for ($index = $context['level'] + 1, $count = count($this->levels); $index < $count; $index++) {
            if (isset($this->levels[$index]['blocks'][$context['name']])) {
                return $this->expandBlockAt($context['name'], $index);
            }
        }

        throw $this->error("super() in block '{$context['name']}': no parent template defines it", $node);
    }

    /**
     * {{ block("name") }}: render a block again elsewhere (e.g. <title> and <h1>).
     */
    private function expandBlockFunction(array $call): array
    {
        $arguments = $call['arguments'] ?? [];
        if (count($arguments) !== 1 || !$this->isLiteral($arguments[0]['expr'])) {
            throw $this->error('block() takes one string literal: {{ block("name") }}', $call);
        }

        return $this->expandBlock($arguments[0]['expr']['value'], $call);
    }

    /**
     * {% embed "card.volt" with [...] %}{% block body %}...{% endblock %}{% endembed %}
     *
     * The embed body is an anonymous child template of "card.volt", resolved
     * on its own, inlined here, and run in a scope of its own.
     */
    private function expandEmbed(array $node): array
    {
        if (!$this->isLiteral($node['path'])) {
            throw $this->error('embed needs a string literal template name', $node);
        }

        $child = [
            ['type' => Node::EXTENDS, 'path' => $node['path'], 'file' => $node['file'], 'line' => $node['line']],
            ...($node['block_statements'] ?? []),
        ];

        $statements = (new self($this->compiler))->resolveChain($child, $this->levels[0]['path']);
        $params     = isset($node['params']) ? $this->compiler->expression($node['params']) : '[]';

        return [
            Node::php('<?php (function (array $__volt_scope) { extract($__volt_scope); ?>'),
            ...$statements,
            Node::php('<?php })(array_merge(get_defined_vars(), ' . $params . ')); ?>'),
        ];
    }

    /**
     * {% extends layoutVar %}: the parent is only known at render time. The
     * template compiles to a call that compiles (once per parent) and runs
     * the child against that parent.
     */
    private function dynamicExtends(array $extends, string $path): array
    {
        return [Node::php(
            '<?php $this->renderDynamicExtends(' . $this->compiler->expression($extends['path'])
            . ', ' . var_export($path, true) . ', get_defined_vars()); ?>'
        )];
    }

    /**
     * All blocks of one template, at any depth (inside blocks, if, for...),
     * except those inside an embed body: those belong to the embedded template.
     *
     * @return array<string, array>
     */
    private function collectBlocks(array $statements, string $path, array &$blocks = []): array
    {
        foreach ($statements as $statement) {
            $type = $statement['type'] ?? null;

            if ($type === Node::EMBED) {
                continue;
            }

            if ($type === Node::BLOCK) {
                $name = $statement['name'];
                if (isset($blocks[$name])) {
                    throw $this->error(sprintf(
                        "Block '%s' is defined twice in %s (lines %d and %d)",
                        $name,
                        $path,
                        $blocks[$name]['line'],
                        $statement['line']
                    ), $statement);
                }
                $blocks[$name] = $statement;
            }

            foreach (Node::CONTAINERS as $key) {
                if (isset($statement[$key]) && is_array($statement[$key])) {
                    $this->collectBlocks($statement[$key], $path, $blocks);
                }
            }
        }

        return $blocks;
    }

    private function findExtends(array $statements): ?array
    {
        foreach ($statements as $statement) {
            if (($statement['type'] ?? null) === Node::EXTENDS) {
                return $statement;
            }
        }

        return null;
    }

    private function withExtendsPath(array $statements, string $path): array
    {
        foreach ($statements as $i => $statement) {
            if (($statement['type'] ?? null) === Node::EXTENDS) {
                $statements[$i]['path'] = ['type' => Node::STRING, 'value' => $path];
                break;
            }
        }

        return $statements;
    }

    private function isLiteral(array $expr): bool
    {
        return ($expr['type'] ?? null) === Node::STRING;
    }

    private function error(string $message, array $node): Exception
    {
        return new Exception(sprintf('%s in %s on line %d', $message, $node['file'] ?? '?', $node['line'] ?? 0));
    }
}
