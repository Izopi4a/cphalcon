<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

use Phalcon\Form\ChoiceList\ChoiceListInterface;

/**
 * Array of choices <-> array of string values (multiple ChoiceType).
 */
final class ChoicesToValuesTransformer implements DataTransformerInterface
{
    public function __construct(private readonly ChoiceListInterface $choiceList)
    {
    }

    public function transform(mixed $value): array
    {
        if (null === $value) {
            return [];
        }
        if (!is_array($value)) {
            throw new TransformationFailedException('Expected an array.');
        }

        return $this->choiceList->getValuesForChoices($value);
    }

    public function reverseTransform(mixed $value): array
    {
        if (null === $value) {
            return [];
        }
        if (!is_array($value)) {
            throw new TransformationFailedException('Expected an array.');
        }

        $choices = $this->choiceList->getChoicesForValues($value);

        if (count($choices) !== count($value)) {
            throw new TransformationFailedException('Could not find all matching choices for the given values.');
        }

        return $choices;
    }
}
