<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

/**
 * A bundle of types and type extensions (what the Container provider registers).
 */
interface ExtensionInterface
{
    public function hasType(string $class): bool;

    public function getType(string $class): TypeInterface;

    /** @return list<TypeExtensionInterface> */
    public function getTypeExtensions(string $class): array;

    public function hasTypeExtensions(string $class): bool;
}
