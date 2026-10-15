<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\FormInterface;
use Phalcon\Support\PropertyAccess\AccessException;
use Phalcon\Support\PropertyAccess\PropertyAccessor;
use Phalcon\Support\PropertyAccess\PropertyAccessorInterface;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

final class PropertyPathAccessor implements DataAccessorInterface
{
    public function __construct(private readonly PropertyAccessorInterface $propertyAccessor = new PropertyAccessor())
    {
    }

    public function getValue(object|array $viewData, FormInterface $form): mixed
    {
        $path = $this->getPropertyPath($form);

        return $this->propertyAccessor->getValue($viewData, $path);
    }

    public function setValue(object|array &$viewData, mixed $value, FormInterface $form): void
    {
        $path = $this->getPropertyPath($form);

        // Keep identity: if the current value is the very same object reference and the form is
        // by_reference, the object was already modified in place by the children.
        if (is_object($viewData) && $form->getConfig()->getByReference()) {
            $current = $this->propertyAccessor->getValue($viewData, $path);
            if (is_object($current) && $current === $value) {
                return;
            }
            if ($current instanceof \DateTimeInterface && $value instanceof \DateTimeInterface && $current == $value) {
                return;
            }
        }

        $this->propertyAccessor->setValue($viewData, $path, $value);
    }

    public function isReadable(object|array $viewData, FormInterface $form): bool
    {
        return null !== $form->getPropertyPath() && $this->propertyAccessor->isReadable($viewData, $form->getPropertyPath());
    }

    public function isWritable(object|array $viewData, FormInterface $form): bool
    {
        return null !== $form->getPropertyPath() && $this->propertyAccessor->isWritable($viewData, $form->getPropertyPath());
    }

    private function getPropertyPath(FormInterface $form): PropertyPathInterface
    {
        return $form->getPropertyPath() ?? throw new LogicException(sprintf('Unable to map a form without a property path (form "%s").', $form->getName()));
    }
}
