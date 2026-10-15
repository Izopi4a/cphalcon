<?php
declare(strict_types=1);

namespace Phalcon\Form\View;

use Phalcon\Form\Exception\BadMethodCallException;

/**
 * Snapshot of a form for rendering. Mirrors the form tree; vars are filled by the types'
 * buildView()/finishView(). Create it after submit so errors/values are current.
 *
 * @implements \ArrayAccess<string, FormView>
 * @implements \IteratorAggregate<string, FormView>
 */
class FormView implements \ArrayAccess, \IteratorAggregate, \Countable
{
    /** @var array<string, mixed> */
    public array $vars = ['value' => null, 'attr' => []];

    /** @var array<string, FormView> */
    public array $children = [];

    private bool $rendered = false;
    private bool $methodRendered = false;

    public function __construct(public readonly ?FormView $parent = null)
    {
    }

    /** True once this view, or all of its children, have been rendered. */
    public function isRendered(): bool
    {
        if ($this->rendered || [] === $this->children) {
            return $this->rendered;
        }
        foreach ($this->children as $child) {
            if (!$child->isRendered()) {
                return false;
            }
        }

        return $this->rendered = true;
    }

    public function setRendered(): static
    {
        $this->rendered = true;

        return $this;
    }

    public function isMethodRendered(): bool
    {
        return $this->methodRendered;
    }

    public function setMethodRendered(): void
    {
        $this->methodRendered = true;
    }

    public function offsetGet(mixed $offset): FormView
    {
        return $this->children[$offset] ?? throw new \OutOfBoundsException(sprintf('Child "%s" does not exist.', $offset));
    }

    public function offsetExists(mixed $offset): bool
    {
        return isset($this->children[$offset]);
    }

    public function offsetSet(mixed $offset, mixed $value): void
    {
        throw new BadMethodCallException('Not supported.');
    }

    public function offsetUnset(mixed $offset): void
    {
        unset($this->children[$offset]);
    }

    public function getIterator(): \ArrayIterator
    {
        return new \ArrayIterator($this->children);
    }

    public function count(): int
    {
        return count($this->children);
    }
}
