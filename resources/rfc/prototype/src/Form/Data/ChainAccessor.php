<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\FormInterface;

final class ChainAccessor implements DataAccessorInterface
{
    /** @param iterable<DataAccessorInterface> $accessors */
    public function __construct(private readonly iterable $accessors)
    {
    }

    public function getValue(object|array $viewData, FormInterface $form): mixed
    {
        foreach ($this->accessors as $accessor) {
            if ($accessor->isReadable($viewData, $form)) {
                return $accessor->getValue($viewData, $form);
            }
        }
        throw new LogicException(sprintf('Unable to read from the given form data (form "%s").', $form->getName()));
    }

    public function setValue(object|array &$viewData, mixed $value, FormInterface $form): void
    {
        foreach ($this->accessors as $accessor) {
            if ($accessor->isWritable($viewData, $form)) {
                $accessor->setValue($viewData, $value, $form);

                return;
            }
        }
        throw new LogicException(sprintf('Unable to write the given value to the form data (form "%s").', $form->getName()));
    }

    public function isReadable(object|array $viewData, FormInterface $form): bool
    {
        foreach ($this->accessors as $accessor) {
            if ($accessor->isReadable($viewData, $form)) {
                return true;
            }
        }

        return false;
    }

    public function isWritable(object|array $viewData, FormInterface $form): bool
    {
        foreach ($this->accessors as $accessor) {
            if ($accessor->isWritable($viewData, $form)) {
                return true;
            }
        }

        return false;
    }
}
