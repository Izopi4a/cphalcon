<?php
declare(strict_types=1);

namespace Phalcon\Support\PropertyAccess;

final class PropertyPath implements PropertyPathInterface
{
    /** @var list<string> */
    private array $elements = [];
    /** @var list<bool> */
    private array $isIndex = [];
    private string $pathAsString;

    public function __construct(PropertyPathInterface|string $path)
    {
        if ($path instanceof PropertyPathInterface) {
            $this->elements     = $path->getElements();
            $this->pathAsString = (string) $path;
            foreach ($this->elements as $i => $_) {
                $this->isIndex[] = $path->isIndex($i);
            }

            return;
        }

        if ('' === $path) {
            throw new InvalidPropertyPathException('The property path should not be empty.');
        }

        $this->pathAsString = $path;
        $remaining          = $path;
        $position           = 0;

        // Either ".name" / "name" (property) or "[name]" (index), repeated.
        $pattern = '/^(([^\.\[]++)|\[([^\]]++)\])(.*)/';

        while (preg_match($pattern, $remaining, $matches)) {
            if ('' !== $matches[2]) {
                $this->elements[] = $matches[2];
                $this->isIndex[]  = false;
            } else {
                $this->elements[] = $matches[3];
                $this->isIndex[]  = true;
            }

            $position += strlen($matches[1]);
            $remaining = $matches[4];

            if ('' === $remaining) {
                break;
            }
            if ('.' === $remaining[0]) {
                $remaining = substr($remaining, 1);
                ++$position;
                if ('' === $remaining || '[' === $remaining[0]) {
                    throw new InvalidPropertyPathException(sprintf('Could not parse property path "%s". Unexpected token at position %d.', $path, $position));
                }
            } elseif ('[' !== $remaining[0]) {
                throw new InvalidPropertyPathException(sprintf('Could not parse property path "%s". Unexpected token "%s" at position %d.', $path, $remaining[0], $position));
            }
        }

        if ('' !== $remaining) {
            throw new InvalidPropertyPathException(sprintf('Could not parse property path "%s". Unexpected token "%s" at position %d.', $path, $remaining[0], $position));
        }
    }

    public function __toString(): string
    {
        return $this->pathAsString;
    }

    public function count(): int
    {
        return count($this->elements);
    }

    public function getLength(): int
    {
        return count($this->elements);
    }

    public function getParent(): ?PropertyPathInterface
    {
        if (count($this->elements) <= 1) {
            return null;
        }

        $parent = clone $this;
        array_pop($parent->elements);
        array_pop($parent->isIndex);
        $parent->pathAsString = substr($this->pathAsString, 0, max(strrpos($this->pathAsString, '.') ?: 0, strrpos($this->pathAsString, '[') ?: 0));

        return $parent;
    }

    public function getElements(): array
    {
        return $this->elements;
    }

    public function getElement(int $index): string
    {
        return $this->elements[$index] ?? throw new \OutOfBoundsException(sprintf('The index %d is not within the property path', $index));
    }

    public function isProperty(int $index): bool
    {
        return !$this->isIndex($index);
    }

    public function isIndex(int $index): bool
    {
        return $this->isIndex[$index] ?? throw new \OutOfBoundsException(sprintf('The index %d is not within the property path', $index));
    }
}
