<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\Exception\UnexpectedTypeException;

/**
 * Maps one choice value (string, "" for none) to a list of RadioType children and back
 * (expanded single ChoiceType). The child named "placeholder" stands for "no choice" (null).
 */
final class RadioListMapper implements DataMapperInterface
{
    public function mapDataToForms(mixed $viewData, iterable $forms): void
    {
        if (!is_string($viewData)) {
            throw new UnexpectedTypeException($viewData, 'string');
        }

        foreach ($forms as $radio) {
            $value = $radio->getConfig()->getOption('value');
            $radio->setData($viewData === $value);
        }
    }

    public function mapFormsToData(iterable $forms, mixed &$viewData): void
    {
        if (null !== $viewData && !is_string($viewData)) {
            throw new UnexpectedTypeException($viewData, 'null or string');
        }

        $viewData = null;

        foreach ($forms as $radio) {
            if ($radio->getData()) {
                if ('placeholder' === $radio->getName()) {
                    return;
                }

                $viewData = $radio->getConfig()->getOption('value');

                return;
            }
        }
    }
}
