<?php
declare(strict_types=1);

namespace Phalcon\Form\Util;

/**
 * Insertion-ordered map that tolerates adding/removing entries while iterating.
 * Iteration works on a snapshot of the keys and skips keys removed meanwhile.
 *
 * @template T
 * @implements \ArrayAccess<string, T>
 * @implements \IteratorAggregate<string, T>
 */
final class OrderedHashMap implements \ArrayAccess, \IteratorAggregate, \Countable
{
    /** @var array<string, T> */
    private array $elements = [];

    public function offsetExists(mixed $offset): bool
    {
        return isset($this->elements[(string) $offset]);
    }

    public function offsetGet(mixed $offset): mixed
    {
        $key = (string) $offset;
        if (!isset($this->elements[$key])) {
            throw new \OutOfBoundsException(sprintf('The offset "%s" does not exist.', $key));
        }

        return $this->elements[$key];
    }

    public function offsetSet(mixed $offset, mixed $value): void
    {
        if (null === $offset) {
            $offset = count($this->elements) > 0 ? max(array_map('intval', array_keys($this->elements))) + 1 : 0;
        }
        $this->elements[(string) $offset] = $value;
    }

    public function offsetUnset(mixed $offset): void
    {
        unset($this->elements[(string) $offset]);
    }

    public function count(): int
    {
        return count($this->elements);
    }

    public function getIterator(): \Generator
    {
        foreach (array_keys($this->elements) as $key) {
            if (array_key_exists($key, $this->elements)) {
                yield $key => $this->elements[$key];
            }
        }
    }

    /** @return array<string, T> */
    public function toArray(): array
    {
        return $this->elements;
    }

    /** @return list<string> */
    public function keys(): array
    {
        return array_map('strval', array_keys($this->elements));
    }
}
