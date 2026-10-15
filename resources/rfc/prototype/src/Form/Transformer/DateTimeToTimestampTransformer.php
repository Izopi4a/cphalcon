<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * \DateTimeInterface <-> Unix timestamp (int).
 */
final class DateTimeToTimestampTransformer implements DataTransformerInterface
{
    private readonly string $inputTimezone;
    private readonly string $outputTimezone;

    public function __construct(?string $inputTimezone = null, ?string $outputTimezone = null)
    {
        $this->inputTimezone  = $inputTimezone ?: date_default_timezone_get();
        $this->outputTimezone = $outputTimezone ?: date_default_timezone_get();
    }

    public function transform(mixed $value): ?int
    {
        if (null === $value) {
            return null;
        }
        if (!$value instanceof \DateTimeInterface) {
            throw new TransformationFailedException('Expected a \DateTimeInterface.');
        }

        return $value->getTimestamp();
    }

    public function reverseTransform(mixed $value): ?\DateTime
    {
        if (null === $value || '' === $value) {
            return null;
        }
        if (!is_numeric($value) || (string) (int) $value !== (string) $value) {
            throw new TransformationFailedException('Expected a numeric.', 0, null, 'Please enter a valid date.', ['{{ value }}' => is_scalar($value) ? (string) $value : get_debug_type($value)]);
        }

        $dateTime = new \DateTime('now', new \DateTimeZone($this->outputTimezone));
        $dateTime->setTimestamp((int) $value);

        if ($this->inputTimezone !== $this->outputTimezone) {
            $dateTime->setTimezone(new \DateTimeZone($this->inputTimezone));
        }

        return $dateTime;
    }
}
