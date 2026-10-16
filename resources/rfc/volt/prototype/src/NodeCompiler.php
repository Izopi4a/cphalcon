<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr;

use Phalcon\VoltNfr\Runtime\Registry;
use Phalcon\VoltNfr\Runtime\VoltCallable;

/**
 * A regular Volt compiler extension (the addExtension() hooks) that compiles
 * what the NFR adds. The stock expression() and statementList() are final, so
 * the prototype goes through the hooks; Compiler.zep would get plain cases.
 */
final class NodeCompiler
{
    private const BUILTIN_TESTS = [
        Node::IDENTIFIER => ['empty', 'even', 'odd', 'numeric', 'scalar', 'iterable'],
        Node::FCALL      => ['divisibleby', 'sameas', 'type'],
    ];

    public function __construct(
        private Compiler $compiler,
        private Registry $registry
    ) {
    }

    /**
     * {{ name(args) }} for a runtime function.
     */
    public function compileFunction(string $name, string $arguments, mixed $exprArgs): ?string
    {
        $function = $this->registry->get('function', $name);
        if ($function === null) {
            return null;
        }

        return $this->call('function', $function, $this->arguments($exprArgs));
    }

    /**
     * {{ value|name(args) }} for a runtime filter, and |raw.
     * $arguments already holds "value, args".
     */
    public function compileFilter(string $name, string $arguments, mixed $exprArgs): ?string
    {
        if ($name === 'raw') {
            return $arguments;
        }

        $filter = $this->registry->get('filter', $name);
        if ($filter === null) {
            return null;
        }

        return $this->call('filter', $filter, [$arguments]);
    }

    public function resolveExpression(array $expr): ?string
    {
        return match ($expr['type'] ?? null) {
            Node::COALESCE => '(' . $this->compiler->expression($expr['left'])
                . ' ?? ' . $this->compiler->expression($expr['right']) . ')',
            Node::NULLSAFE => $this->nullsafe($expr),
            Node::IS       => $this->test($expr, false),
            Node::ISNOT    => $this->test($expr, true),
            default        => null,
        };
    }

    public function compileStatement(array $statement): ?string
    {
        return match ($statement['type'] ?? null) {
            Node::PHP         => $statement['code'],
            Node::SET_CAPTURE => '<?php ob_start(); ?>'
                . $this->compiler->compileStatements($statement['block_statements'] ?? [])
                . '<?php $' . $statement['name'] . ' = ob_get_clean(); ?>',
            default           => null,
        };
    }

    // --------------------------------------------------------------- private

    /**
     * a?.b  ->  $a?->b ;  a?.b(1)  ->  $a?->b(1) (the call wraps this node)
     */
    private function nullsafe(array $expr): string
    {
        $right = $expr['right'];
        if (($right['type'] ?? null) !== Node::IDENTIFIER) {
            throw new Exception(sprintf(
                'Only a property or method name can follow "?." in %s on line %d',
                $expr['file'] ?? '',
                $expr['line'] ?? 0
            ));
        }

        return $this->compiler->expression($expr['left']) . '?->' . $right['value'];
    }

    /**
     * value is name / value is name(args) / value is not ...
     */
    private function test(array $expr, bool $negate): ?string
    {
        $right = $expr['right'];
        $type  = $right['type'] ?? null;
        $name  = match ($type) {
            Node::IDENTIFIER => $right['value'],
            Node::FCALL      => $right['name']['value'] ?? null,
            Node::NULL       => 'null', // "null" is a keyword: a NULL literal node
            default          => null,
        };

        $left = $this->compiler->expression($expr['left']);

        if ($name !== null && ($test = $this->registry->get('test', $name)) !== null) {
            $code = $this->call('test', $test, [$left, ...$this->arguments($right['arguments'] ?? null)]);
        } elseif ($name === 'null' || $name === 'none') {
            $code = '(' . $left . ' === null)';
        } elseif ($name !== null && in_array($name, self::BUILTIN_TESTS[$type] ?? [], true)) {
            if (!$negate) {
                return null; // the stock resolveTest()
            }
            $code = $this->compiler->resolveTest($right, $left);
        } elseif ($this->compiler->isStrictTests()) {
            throw new Exception(sprintf(
                'Unknown test "%s" in %s on line %d',
                $name ?? 'expression',
                $expr['file'] ?? '',
                $expr['line'] ?? 0
            ));
        } else {
            if (!$negate) {
                return null; // today's fallback: "=="
            }
            $code = $left . ' == ' . $this->compiler->expression($right);
        }

        return $negate ? '!(' . $code . ')' : $code;
    }

    /**
     * Compiled arguments; 'name': value becomes a PHP named argument.
     *
     * @return list<string>
     */
    private function arguments(mixed $exprArgs): array
    {
        $arguments = [];
        foreach (is_array($exprArgs) ? $exprArgs : [] as $argument) {
            $code = $this->compiler->expression($argument['expr']);
            if (isset($argument['name'])) {
                if (!preg_match('/^[A-Za-z_][A-Za-z0-9_]*$/', $argument['name'])) {
                    throw new Exception("Invalid argument name '{$argument['name']}'");
                }
                $code = $argument['name'] . ': ' . $code;
            }
            $arguments[] = $code;
        }

        return $arguments;
    }

    /**
     * A direct call for functions and static methods, else a lookup in the
     * engine's registry at render time.
     *
     * @param list<string> $arguments
     */
    private function call(string $kind, VoltCallable $callable, array $arguments): string
    {
        if ($callable->needsContext()) {
            array_unshift($arguments, 'get_defined_vars()');
        }

        $list   = implode(', ', $arguments);
        $static = $callable->getStaticCallCode();
        if ($static !== null) {
            return $static . '(' . $list . ')';
        }

        $method = match ($kind) {
            'function' => 'getRuntimeFunction',
            'filter'   => 'getRuntimeFilter',
            'test'     => 'getRuntimeTest',
        };

        // memoized on the engine: one array read per call after the first
        $name = var_export($callable->getName(), true);
        $key  = var_export($kind . ':' . $callable->getName(), true);

        return '($this->runtime[' . $key . '] ??= $this->' . $method . '(' . $name . '))(' . $list . ')';
    }
}
