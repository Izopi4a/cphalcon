<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

use Phalcon\Form\ChoiceList\ChoiceListInterface;

/**
 * Single choice <-> its string value in the choice list (collapsed, non-multiple ChoiceType).
 */
final class ChoiceToValueTransformer implements DataTransformerInterface
{
    public function __construct(private readonly ChoiceListInterface $choiceList)
    {
    }

    public function transform(mixed $value): string
    {
        return (string) current($this->choiceList->getValuesForChoices([$value]));
    }

    public function reverseTransform(mixed $value): mixed
    {
        if (null !== $value && !is_string($value)) {
            throw new TransformationFailedException('Expected a string or null.');
        }

        $choices = $this->choiceList->getChoicesForValues([(string) $value]);

        if (1 !== count($choices)) {
            if (null === $value || '' === $value) {
                return null;
            }

            throw new TransformationFailedException(sprintf('The choice "%s" does not exist or is not unique.', $value));
        }

        return current($choices);
    }
}
