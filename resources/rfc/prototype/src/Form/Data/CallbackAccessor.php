<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\FormInterface;

/**
 * Uses the "getter" and "setter" options of the child form instead of property access.
 */
final class CallbackAccessor implements DataAccessorInterface
{
    public function getValue(object|array $viewData, FormInterface $form): mixed
    {
        $getter = $form->getConfig()->getOption('getter');

        return null === $getter ? null : ($getter)($viewData, $form);
    }

    public function setValue(object|array &$viewData, mixed $value, FormInterface $form): void
    {
        $setter = $form->getConfig()->getOption('setter');
        if (null !== $setter) {
            ($setter)($viewData, $form->getData(), $form);
        }
    }

    public function isReadable(object|array $viewData, FormInterface $form): bool
    {
        return null !== $form->getConfig()->getOption('getter');
    }

    public function isWritable(object|array $viewData, FormInterface $form): bool
    {
        return null !== $form->getConfig()->getOption('setter');
    }
}
