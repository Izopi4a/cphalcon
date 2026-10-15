<?php
declare(strict_types=1);

namespace Phalcon\Support\PropertyAccess;

interface PropertyAccessorInterface
{
    /**
     * @throws NoSuchPropertyException when a property element cannot be read
     * @throws UnexpectedTypeException when a non-last element is a scalar
     */
    public function getValue(object|array $objectOrArray, PropertyPathInterface|string $propertyPath): mixed;

    /**
     * Writes through the path. Intermediate arrays are written back up the chain,
     * so nested array paths work; intermediate objects are modified in place.
     */
    public function setValue(object|array &$objectOrArray, PropertyPathInterface|string $propertyPath, mixed $value): void;

    public function isReadable(object|array $objectOrArray, PropertyPathInterface|string $propertyPath): bool;

    public function isWritable(object|array $objectOrArray, PropertyPathInterface|string $propertyPath): bool;
}
