<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\Exception\UnexpectedTypeException;

/**
 * Default mapper: reads a child when the data is non-empty, the child is mapped and readable;
 * writes a child when it is mapped, submitted, synchronized, enabled and writable.
 */
final class DataMapper implements DataMapperInterface
{
    private readonly DataAccessorInterface $accessor;

    public function __construct(?DataAccessorInterface $accessor = null)
    {
        $this->accessor = $accessor ?? new ChainAccessor([new CallbackAccessor(), new PropertyPathAccessor()]);
    }

    public function mapDataToForms(mixed $viewData, iterable $forms): void
    {
        $empty = null === $viewData || [] === $viewData;

        if (!$empty && !is_array($viewData) && !is_object($viewData)) {
            throw new UnexpectedTypeException($viewData, 'object, array or empty');
        }

        foreach ($forms as $form) {
            $config = $form->getConfig();

            if (!$empty && $config->getMapped() && $this->accessor->isReadable($viewData, $form)) {
                $form->setData($this->accessor->getValue($viewData, $form));
            } else {
                $form->setData($config->getData());
            }
        }
    }

    public function mapFormsToData(iterable $forms, mixed &$viewData): void
    {
        if (null === $viewData) {
            return;
        }
        if (!is_array($viewData) && !is_object($viewData)) {
            throw new UnexpectedTypeException($viewData, 'object, array or empty');
        }

        foreach ($forms as $form) {
            $config = $form->getConfig();

            if ($config->getMapped()
                && $form->isSubmitted()
                && $form->isSynchronized()
                && !$form->isDisabled()
                && $this->accessor->isWritable($viewData, $form)
            ) {
                $this->accessor->setValue($viewData, $form->getData(), $form);
            }
        }
    }
}
