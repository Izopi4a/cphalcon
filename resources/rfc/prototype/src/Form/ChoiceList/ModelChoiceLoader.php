<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

use Phalcon\Mvc\ModelInterface;

/**
 * Loads the choices of a ModelType: Model::find($parameters) for the whole list, and a
 * find() restricted to the submitted keys when the list has not been loaded yet (Symfony's
 * DoctrineChoiceLoader optimisation: a <select> submission costs one row, not the table).
 *
 * The restricted query keeps the "parameters" conditions (a key outside the configured subset
 * must stay invalid) and is skipped when the parameters contain limit/offset/columns/group
 * or when the choice value is an arbitrary callable: then the whole list is loaded.
 *
 * prototype: "parameters" is whatever Model::find() takes (array or conditions string), or a
 * Closure/invokable object returning it, evaluated on first load so conditions can depend on
 * request state. A string callable is treated as a conditions string.
 */
final class ModelChoiceLoader implements ChoiceLoaderInterface
{
    /**
     * @param class-string<ModelInterface>     $class
     * @param array|string|callable|null       $parameters     the Model::find() argument, or a callable returning it
     * @param ModelIdReader|string|null        $valueAttribute how choice values map to attributes: the id reader
     *                                                         (primary key), one attribute name, or null (no query by value possible)
     */
    public function __construct(
        private readonly string $class,
        private readonly mixed $parameters,
        private readonly ModelIdReader|string|null $valueAttribute,
    ) {
    }

    public function __invoke(): iterable
    {
        return $this->loadChoices();
    }

    public function loadChoices(): iterable
    {
        return ($this->class)::find($this->resolveParameters());
    }

    public function loadChoicesForValues(array $values): ?iterable
    {
        if (null === $this->valueAttribute) {
            return null;
        }

        $parameters = $this->resolveParameters();
        if (is_string($parameters)) {
            $parameters = ['conditions' => $parameters];
        }
        if (null !== $parameters && !is_array($parameters)) {
            return null; // e.g. an integer primary key as find() argument: no idea how to combine
        }
        $parameters ??= [];

        foreach (['limit', 'offset', 'columns', 'group', 'having'] as $unsupported) {
            if (isset($parameters[$unsupported])) {
                return null;
            }
        }

        $clauses = [];
        $bind    = [];
        foreach (array_values($values) as $i => $value) {
            $attributes = $this->valueAttribute instanceof ModelIdReader
                ? $this->valueAttribute->parse((string) $value)
                : [$this->valueAttribute => (string) $value];

            if (null === $attributes) {
                continue; // not the shape of a key: cannot match anything
            }

            $parts = [];
            $j     = 0;
            foreach ($attributes as $attribute => $part) {
                $placeholder        = sprintf('mt_%d_%d', $i, $j++);
                $parts[]            = sprintf('%s = :%s:', $attribute, $placeholder);
                $bind[$placeholder] = $part;
            }
            $clauses[] = '(' . implode(' AND ', $parts) . ')';
        }

        if ([] === $clauses) {
            return [];
        }

        $byValue = implode(' OR ', $clauses);

        $parameters['conditions'] = isset($parameters['conditions']) && '' !== $parameters['conditions']
            ? sprintf('(%s) AND (%s)', $parameters['conditions'], $byValue)
            : $byValue;
        $parameters['bind'] = ($parameters['bind'] ?? []) + $bind;

        return ($this->class)::find($parameters);
    }

    private function resolveParameters(): mixed
    {
        $parameters = $this->parameters;

        if ($parameters instanceof \Closure || (is_object($parameters) && is_callable($parameters))) {
            return $parameters();
        }

        return $parameters;
    }
}
