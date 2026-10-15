<?php
declare(strict_types=1);

namespace Phalcon\Support\PropertyAccess;

/**
 * Reduced property accessor: array indices, ArrayAccess, get/is/has getters, set setters,
 * add/remove pairs for iterables, public properties. No magic __call, wildcards or caching.
 * Missing array indices read as null (they are not an error for forms).
 */
final class PropertyAccessor implements PropertyAccessorInterface
{
    public function __construct(private readonly bool $allowMagicGetSet = true)
    {
    }

    public function getValue(object|array $objectOrArray, PropertyPathInterface|string $propertyPath): mixed
    {
        $path    = $propertyPath instanceof PropertyPathInterface ? $propertyPath : new PropertyPath($propertyPath);
        $current = $objectOrArray;
        $length  = $path->getLength();

        for ($i = 0; $i < $length; ++$i) {
            if (null === $current) {
                // Symfony: a null intermediate is an error (no null-safe operator in the reduced version).
                throw new UnexpectedTypeException(sprintf('Cannot read "%s" on null (path "%s").', $path->getElement($i), (string) $path));
            }
            if (!is_object($current) && !is_array($current)) {
                throw new UnexpectedTypeException(sprintf('Cannot read "%s" on a value of type "%s" (path "%s").', $path->getElement($i), get_debug_type($current), (string) $path));
            }
            $current = $path->isIndex($i)
                ? $this->readIndex($current, $path->getElement($i))
                : $this->readProperty($current, $path->getElement($i));
        }

        return $current;
    }

    public function setValue(object|array &$objectOrArray, PropertyPathInterface|string $propertyPath, mixed $value): void
    {
        $path = $propertyPath instanceof PropertyPathInterface ? $propertyPath : new PropertyPath($propertyPath);
        $this->write($objectOrArray, $path, 0, $value);
    }

    public function isReadable(object|array $objectOrArray, PropertyPathInterface|string $propertyPath): bool
    {
        try {
            $this->getValue($objectOrArray, $propertyPath);

            return true;
        } catch (Exception) {
            return false;
        }
    }

    public function isWritable(object|array $objectOrArray, PropertyPathInterface|string $propertyPath): bool
    {
        $path = $propertyPath instanceof PropertyPathInterface ? $propertyPath : new PropertyPath($propertyPath);

        try {
            $parent  = $path->getParent();
            $target  = null === $parent ? $objectOrArray : $this->getValue($objectOrArray, $parent);
            $last    = $path->getLength() - 1;
            $element = $path->getElement($last);

            if (null === $target) {
                // Only a null reached through an index is auto-created as an array (see write()).
                return null !== $parent && $parent->isIndex($parent->getLength() - 1) && $path->isIndex($last);
            }
            if ($path->isIndex($last)) {
                return is_array($target) || $target instanceof \ArrayAccess;
            }
            if (!is_object($target)) {
                return false;
            }

            return $this->findWriteStrategy($target, $element, null, false) !== null;
        } catch (Exception) {
            return false;
        }
    }

    // --- reading

    private function readIndex(object|array $target, string $index): mixed
    {
        if (is_array($target)) {
            return array_key_exists($index, $target) ? $target[$index] : null;
        }
        if ($target instanceof \ArrayAccess) {
            return $target->offsetExists($index) ? $target[$index] : null;
        }
        throw new NoSuchIndexException(sprintf('Cannot read index "%s" from object of type "%s" because it doesn\'t implement \ArrayAccess.', $index, get_debug_type($target)));
    }

    private function readProperty(object|array $target, string $property): mixed
    {
        if (is_array($target)) {
            // Lenient: a property element on an array behaves like an index (forms default to "[name]" anyway).
            return array_key_exists($property, $target) ? $target[$property] : null;
        }

        $camel = self::camelize($property);
        foreach (['get' . $camel, 'is' . $camel, 'has' . $camel] as $getter) {
            if (method_exists($target, $getter) && (new \ReflectionMethod($target, $getter))->isPublic()) {
                return $target->$getter();
            }
        }
        if (property_exists($target, $property) && (new \ReflectionProperty($target, $property))->isPublic()) {
            return $target->$property ?? null;
        }
        if ($this->allowMagicGetSet && method_exists($target, '__get')) {
            return $target->$property;
        }

        throw new NoSuchPropertyException(sprintf('Can\'t get a way to read the property "%s" in class "%s".', $property, $target::class));
    }

    // --- writing

    private function write(mixed &$target, PropertyPathInterface $path, int $i, mixed $value): void
    {
        $element = $path->getElement($i);
        $isLast  = $i === $path->getLength() - 1;

        if (null === $target) {
            if (!$path->isIndex($i)) {
                // Symfony auto-creates arrays for missing indices only; a null object property is an error.
                throw new UnexpectedTypeException(sprintf('Cannot write property "%s" on null (path "%s").', $element, (string) $path));
            }
            $target = [];
        }
        if (!is_object($target) && !is_array($target)) {
            throw new UnexpectedTypeException(sprintf('Cannot write "%s" on a value of type "%s" (path "%s").', $element, get_debug_type($target), (string) $path));
        }

        if ($isLast) {
            if ($path->isIndex($i) || is_array($target)) {
                $this->writeIndex($target, $element, $value);
            } else {
                $this->writeProperty($target, $element, $value);
            }

            return;
        }

        $child = $path->isIndex($i) ? $this->readIndex($target, $element) : $this->readProperty($target, $element);
        $this->write($child, $path, $i + 1, $value);

        // Arrays have value semantics: write the modified copy back. Objects were modified in place.
        if (is_array($child) || null === $child) {
            if ($path->isIndex($i) || is_array($target)) {
                $this->writeIndex($target, $element, $child);
            } else {
                $this->writeProperty($target, $element, $child);
            }
        }
    }

    private function writeIndex(mixed &$target, string $index, mixed $value): void
    {
        if (is_array($target)) {
            $target[$index] = $value;

            return;
        }
        if ($target instanceof \ArrayAccess) {
            $target[$index] = $value;

            return;
        }
        throw new NoSuchIndexException(sprintf('Cannot write index "%s" to object of type "%s" because it doesn\'t implement \ArrayAccess.', $index, get_debug_type($target)));
    }

    private function writeProperty(object $target, string $property, mixed $value): void
    {
        $strategy = $this->findWriteStrategy($target, $property, $value, true);
        if (null === $strategy) {
            throw new NoSuchPropertyException(sprintf('Could not determine access type for property "%s" in class "%s".', $property, $target::class));
        }
        $strategy($value);
    }

    /**
     * @return \Closure(mixed): void|null
     */
    private function findWriteStrategy(object $target, string $property, mixed $value, bool $forWrite): ?\Closure
    {
        $camel  = self::camelize($property);
        $setter = 'set' . $camel;

        // Symfony prefers an adder/remover pair over a setter when writing an iterable.
        if (is_iterable($value) || !$forWrite) {
            foreach (self::singulars($camel) as $singular) {
                $adder   = 'add' . $singular;
                $remover = 'remove' . $singular;
                if (method_exists($target, $adder) && method_exists($target, $remover)) {
                    return function (mixed $v) use ($target, $property, $adder, $remover): void {
                        $this->writeCollection($target, $property, $v, $adder, $remover);
                    };
                }
            }
        }

        if (method_exists($target, $setter) && (new \ReflectionMethod($target, $setter))->isPublic()) {
            return static fn (mixed $v) => $target->$setter($v);
        }

        if (property_exists($target, $property) && (new \ReflectionProperty($target, $property))->isPublic()) {
            return static function (mixed $v) use ($target, $property): void {
                $target->$property = $v;
            };
        }

        if ($this->allowMagicGetSet && method_exists($target, '__set')) {
            return static function (mixed $v) use ($target, $property): void {
                $target->$property = $v;
            };
        }

        return null;
    }

    private function writeCollection(object $target, string $property, iterable $collection, string $adder, string $remover): void
    {
        $previous = [];
        try {
            $current = $this->readProperty($target, $property);
            if (is_iterable($current)) {
                foreach ($current as $item) {
                    $previous[] = $item;
                }
            }
        } catch (NoSuchPropertyException) {
            // nothing to diff against
        }

        $new = [];
        foreach ($collection as $item) {
            $new[] = $item;
        }

        foreach ($previous as $item) {
            if (!in_array($item, $new, true)) {
                $target->$remover($item);
            }
        }
        foreach ($new as $item) {
            if (!in_array($item, $previous, true)) {
                $target->$adder($item);
            }
        }
    }

    // --- helpers

    private static function camelize(string $string): string
    {
        return str_replace(' ', '', ucwords(str_replace('_', ' ', $string)));
    }

    /** @return list<string> candidate singular forms, best first */
    private static function singulars(string $plural): array
    {
        $lower = strtolower($plural);
        $out   = [];
        if (str_ends_with($lower, 'ies')) {
            $out[] = substr($plural, 0, -3) . 'y';
        }
        if (str_ends_with($lower, 'ses') || str_ends_with($lower, 'xes') || str_ends_with($lower, 'ches') || str_ends_with($lower, 'shes')) {
            $out[] = substr($plural, 0, -2);
        }
        if (str_ends_with($lower, 's')) {
            $out[] = substr($plural, 0, -1);
        }
        $out[] = $plural;

        return array_values(array_unique($out));
    }
}
