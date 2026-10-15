<?php
declare(strict_types=1);

namespace Phalcon\Form\Transformer;

/**
 * Number <-> string without ext-intl: "." is the decimal separator, "," the (optional) thousands
 * separator. Without grouping a submitted "1,5" is read as a decimal comma, i.e. 1.5.
 */
class NumberToStringTransformer implements DataTransformerInterface
{
    public function __construct(
        protected readonly ?int $scale = null,
        protected readonly bool $grouping = false,
    ) {
    }

    public function transform(mixed $value): string
    {
        if (null === $value) {
            return '';
        }
        if (!is_numeric($value)) {
            throw new TransformationFailedException('Expected a numeric.');
        }

        $decimals = $this->scale ?? self::countDecimals($value);

        return number_format((float) $value, $decimals, '.', $this->grouping ? ',' : '');
    }

    public function reverseTransform(mixed $value): int|float|null
    {
        if (null === $value || '' === $value) {
            return null;
        }
        if (!is_string($value)) {
            throw new TransformationFailedException('Expected a string.');
        }

        $normalized = $this->grouping ? str_replace(',', '', $value) : str_replace(',', '.', $value);
        $normalized = trim($normalized);

        if (!is_numeric($normalized) || !preg_match('/^[+-]?(\d+\.?\d*|\.\d+)([eE][+-]?\d+)?$/', $normalized)) {
            throw new TransformationFailedException(sprintf('The number "%s" could not be parsed.', $value));
        }

        $result = (float) $normalized;

        if (is_infinite($result) || is_nan($result)) {
            throw new TransformationFailedException(sprintf('The number "%s" is out of range.', $value));
        }

        return null !== $this->scale ? round($result, $this->scale) : $result;
    }

    private static function countDecimals(int|float|string $value): int
    {
        if (is_int($value)) {
            return 0;
        }

        $string = rtrim(rtrim(sprintf('%.14F', (float) $value), '0'), '.');
        $dot    = strpos($string, '.');

        return false === $dot ? 0 : strlen($string) - $dot - 1;
    }
}
