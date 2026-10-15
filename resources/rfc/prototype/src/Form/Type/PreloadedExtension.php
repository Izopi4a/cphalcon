<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

use Phalcon\Form\Exception\InvalidArgumentException;

final class PreloadedExtension implements ExtensionInterface
{
    /** @var array<class-string, TypeInterface> */
    private array $types = [];
    /** @var array<class-string, list<TypeExtensionInterface>> */
    private array $typeExtensions = [];

    /**
     * @param iterable<TypeInterface>          $types
     * @param iterable<TypeExtensionInterface> $typeExtensions
     */
    public function __construct(iterable $types = [], iterable $typeExtensions = [])
    {
        foreach ($types as $type) {
            $this->types[$type::class] = $type;
        }
        foreach ($typeExtensions as $extension) {
            foreach ($extension::getExtendedTypes() as $extended) {
                $this->typeExtensions[$extended][] = $extension;
            }
        }
    }

    public function hasType(string $class): bool
    {
        return isset($this->types[$class]);
    }

    public function getType(string $class): TypeInterface
    {
        return $this->types[$class] ?? throw new InvalidArgumentException(sprintf('The type "%s" cannot be loaded by this extension.', $class));
    }

    public function getTypeExtensions(string $class): array
    {
        return $this->typeExtensions[$class] ?? [];
    }

    public function hasTypeExtensions(string $class): bool
    {
        return !empty($this->typeExtensions[$class]);
    }
}
