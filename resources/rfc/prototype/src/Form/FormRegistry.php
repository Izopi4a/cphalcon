<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Exception\InvalidArgumentException;
use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\Type\ExtensionInterface;
use Phalcon\Form\Type\TypeInterface;

class FormRegistry implements FormRegistryInterface
{
    /** @var array<class-string, ResolvedTypeInterface> */
    private array $types = [];
    /** @var array<class-string, true> */
    private array $checkedTypes = [];

    /** @param list<ExtensionInterface> $extensions */
    public function __construct(private readonly array $extensions = [])
    {
        foreach ($extensions as $extension) {
            if (!$extension instanceof ExtensionInterface) {
                throw new InvalidArgumentException(sprintf('Extensions must implement "%s".', ExtensionInterface::class));
            }
        }
    }

    public function getType(string $class): ResolvedTypeInterface
    {
        if (!isset($this->types[$class])) {
            $type = null;
            foreach ($this->extensions as $extension) {
                if ($extension->hasType($class)) {
                    $type = $extension->getType($class);
                    break;
                }
            }

            if (null === $type) {
                if (!class_exists($class)) {
                    throw new InvalidArgumentException(sprintf('Could not load type "%s": class does not exist.', $class));
                }
                if (!is_subclass_of($class, TypeInterface::class)) {
                    throw new InvalidArgumentException(sprintf('Could not load type "%s": class does not implement "%s".', $class, TypeInterface::class));
                }
                // Types without dependencies need no registration, like in Symfony.
                $type = new $class();
            }

            $this->types[$class] = $this->resolveType($type);
        }

        return $this->types[$class];
    }

    public function hasType(string $class): bool
    {
        if (isset($this->types[$class])) {
            return true;
        }
        try {
            $this->getType($class);
        } catch (InvalidArgumentException) {
            return false;
        }

        return true;
    }

    public function getExtensions(): array
    {
        return $this->extensions;
    }

    private function resolveType(TypeInterface $type): ResolvedTypeInterface
    {
        $class = $type::class;

        if (isset($this->checkedTypes[$class])) {
            throw new LogicException(sprintf('Circular reference detected for form type "%s" (%s).', $class, implode(' > ', array_keys($this->checkedTypes))));
        }
        $this->checkedTypes[$class] = true;

        try {
            $typeExtensions = [];
            foreach ($this->extensions as $extension) {
                $typeExtensions = array_merge($typeExtensions, $extension->getTypeExtensions($class));
            }

            $parentClass = $type->getParent();
            $parent      = null !== $parentClass ? $this->getType($parentClass) : null;

            return new ResolvedType($type, $typeExtensions, $parent);
        } finally {
            unset($this->checkedTypes[$class]);
        }
    }
}
