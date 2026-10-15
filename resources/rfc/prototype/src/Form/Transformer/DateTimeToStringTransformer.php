<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * \DateTimeInterface <-> string in a PHP date() format. $inputTimezone is the model side,
 * $outputTimezone the view side; both default to the PHP default timezone.
 */
final class DateTimeToStringTransformer implements DataTransformerInterface
{
    private readonly string $inputTimezone;
    private readonly string $outputTimezone;
    private readonly string $parseFormat;

    public function __construct(
        ?string $inputTimezone = null,
        ?string $outputTimezone = null,
        private readonly string $format = 'Y-m-d H:i:s',
    ) {
        $this->inputTimezone  = $inputTimezone ?: date_default_timezone_get();
        $this->outputTimezone = $outputTimezone ?: date_default_timezone_get();

        // "|" resets the fields the format does not mention to 1970-01-01 00:00:00 instead of "now".
        $this->parseFormat = str_contains($format, '|') ? $format : $format . '|';
    }

    public function transform(mixed $value): string
    {
        if (null === $value) {
            return '';
        }
        if (!$value instanceof \DateTimeInterface) {
            throw new TransformationFailedException('Expected a \DateTimeInterface.');
        }

        $dateTime = \DateTimeImmutable::createFromInterface($value)->setTimezone(new \DateTimeZone($this->outputTimezone));

        return $dateTime->format($this->format);
    }

    public function reverseTransform(mixed $value): ?\DateTime
    {
        if (null === $value || '' === $value) {
            return null;
        }
        if (!is_string($value)) {
            throw new TransformationFailedException('Expected a string.');
        }

        $dateTime = \DateTime::createFromFormat($this->parseFormat, $value, new \DateTimeZone($this->outputTimezone));
        $errors   = \DateTime::getLastErrors() ?: ['error_count' => 0, 'warning_count' => 0, 'errors' => [], 'warnings' => []];

        if (false === $dateTime || 0 < $errors['error_count'] || 0 < $errors['warning_count']) {
            throw new TransformationFailedException(
                sprintf('The date "%s" does not match the format "%s": %s', $value, $this->format, implode(', ', [...$errors['warnings'], ...$errors['errors']])),
                0,
                null,
                'Please enter a valid date.',
                ['{{ value }}' => $value]
            );
        }

        if ($this->inputTimezone !== $this->outputTimezone) {
            $dateTime->setTimezone(new \DateTimeZone($this->inputTimezone));
        }

        return $dateTime;
    }
}
