<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\Exception\UnexpectedTypeException;

/**
 * Maps an array of choice values to a list of CheckboxType children and back
 * (expanded + multiple ChoiceType). Each child's "value" option is its choice value.
 */
final class CheckboxListMapper implements DataMapperInterface
{
    public function mapDataToForms(mixed $viewData, iterable $forms): void
    {
        $choices = $viewData ?? [];

        if (!is_array($choices)) {
            throw new UnexpectedTypeException($choices, 'array');
        }

        foreach ($forms as $checkbox) {
            $value = $checkbox->getConfig()->getOption('value');
            $checkbox->setData(in_array($value, $choices, true));
        }
    }

    public function mapFormsToData(iterable $forms, mixed &$viewData): void
    {
        if (!is_array($viewData)) {
            throw new UnexpectedTypeException($viewData, 'array');
        }

        $values = [];

        foreach ($forms as $checkbox) {
            if ($checkbox->getData()) {
                // construct an array of choice values
                $values[] = $checkbox->getConfig()->getOption('value');
            }
        }

        $viewData = $values;
    }
}
