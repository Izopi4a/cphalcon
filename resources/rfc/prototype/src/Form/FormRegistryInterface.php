<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Type\ExtensionInterface;

interface FormRegistryInterface
{
    /** @param class-string<\Phalcon\Form\Type\TypeInterface> $class */
    public function getType(string $class): ResolvedTypeInterface;

    public function hasType(string $class): bool;

    /** @return list<ExtensionInterface> */
    public function getExtensions(): array;
}
