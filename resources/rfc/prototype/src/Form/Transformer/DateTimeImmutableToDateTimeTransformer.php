<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * \DateTimeImmutable (model) <-> \DateTime (norm), used reversed for input "datetime_immutable".
 */
final class DateTimeImmutableToDateTimeTransformer implements DataTransformerInterface
{
    public function transform(mixed $value): ?\DateTime
    {
        if (null === $value) {
            return null;
        }
        if (!$value instanceof \DateTimeImmutable) {
            throw new TransformationFailedException('Expected a \DateTimeImmutable.');
        }

        return \DateTime::createFromImmutable($value);
    }

    public function reverseTransform(mixed $value): ?\DateTimeImmutable
    {
        if (null === $value) {
            return null;
        }
        if (!$value instanceof \DateTime) {
            throw new TransformationFailedException('Expected a \DateTime.');
        }

        return \DateTimeImmutable::createFromMutable($value);
    }
}
