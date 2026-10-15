<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

use Phalcon\Form\Exception\InvalidArgumentException;

/**
 * Checkbox transformer: true <-> $trueValue, false <-> null (a missing checkbox is not submitted).
 * Any submitted value listed in $falseValues reverse-transforms to false, everything else to true.
 */
final class BooleanToStringTransformer implements DataTransformerInterface
{
    /** @param list<mixed> $falseValues */
    public function __construct(
        private readonly string $trueValue,
        private readonly array $falseValues = [null],
    ) {
        if (in_array($this->trueValue, $this->falseValues, true)) {
            throw new InvalidArgumentException('The specified "true" value is contained in the false-values.');
        }
    }

    public function transform(mixed $value): ?string
    {
        if (null === $value) {
            return null;
        }
        if (!is_bool($value)) {
            throw new TransformationFailedException('Expected a Boolean.');
        }

        return $value ? $this->trueValue : null;
    }

    public function reverseTransform(mixed $value): bool
    {
        if (in_array($value, $this->falseValues, true)) {
            return false;
        }
        if (!is_string($value)) {
            throw new TransformationFailedException('Expected a string.');
        }

        return true;
    }
}
