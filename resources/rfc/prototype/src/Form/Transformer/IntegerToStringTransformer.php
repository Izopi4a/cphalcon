<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * Integer <-> string. Decimals are rejected on the way back ("1.5" is not an integer).
 */
final class IntegerToStringTransformer extends NumberToStringTransformer
{
    public function __construct(bool $grouping = false)
    {
        parent::__construct(0, $grouping);
    }

    public function reverseTransform(mixed $value): ?int
    {
        if (is_string($value) && str_contains($value, '.')) {
            throw new TransformationFailedException(sprintf('The value "%s" is not a valid integer.', $value));
        }
        // prototype: without grouping "," reads as a decimal comma, which an integer must not have
        if (is_string($value) && !$this->grouping && str_contains($value, ',')) {
            throw new TransformationFailedException(sprintf('The value "%s" is not a valid integer.', $value));
        }

        $result = parent::reverseTransform($value);

        if (null === $result) {
            return null;
        }
        if ($result > PHP_INT_MAX || $result < PHP_INT_MIN) {
            throw new TransformationFailedException(sprintf('The value "%s" is out of the integer range.', $value));
        }

        return (int) $result;
    }
}
