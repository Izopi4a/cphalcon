<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * Model transformer for NumberType with input "string": numeric string <-> float.
 */
final class StringToFloatTransformer implements DataTransformerInterface
{
    public function __construct(private readonly ?int $scale = null)
    {
    }

    public function transform(mixed $value): ?float
    {
        if (null === $value) {
            return null;
        }
        if (!is_string($value) || !is_numeric($value)) {
            throw new TransformationFailedException('Expected a numeric string.');
        }

        return (float) $value;
    }

    public function reverseTransform(mixed $value): ?string
    {
        if (null === $value) {
            return null;
        }
        if (!is_int($value) && !is_float($value)) {
            throw new TransformationFailedException('Expected a numeric.');
        }
        if (null !== $this->scale) {
            return number_format((float) $value, $this->scale, '.', '');
        }

        return (string) $value;
    }
}
