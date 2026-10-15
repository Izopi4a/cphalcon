<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * Choice list over an array of label => choice. Values are the stringified choices when all
 * choices are scalars with distinct string forms, otherwise their 0-based index; a "choice_value"
 * callable overrides both.
 *
 * prototype: flat lists only, no choice groups.
 */
final class ArrayChoiceList implements ChoiceListInterface
{
    /** @var array<string, mixed> value => choice */
    private array $choices = [];
    /** @var array<string, int|string> value => original key */
    private array $originalKeys = [];
    /** @var array<int|string, string> original key => value */
    private array $structuredValues = [];
    private ?\Closure $valueCallback = null;

    /** @param iterable<int|string, mixed> $choices */
    public function __construct(iterable $choices, ?callable $value = null)
    {
        $choices = is_array($choices) ? $choices : iterator_to_array($choices);

        if (null === $value && self::castableToString($choices)) {
            $value = static fn (mixed $choice): string => false === $choice ? '0' : (string) $choice;
        }
        if (null !== $value) {
            $this->valueCallback = $value(...);
        }

        $index = 0;
        foreach ($choices as $key => $choice) {
            $stringValue = null !== $value ? (string) $value($choice) : (string) $index++;

            $this->choices[$stringValue]     = $choice;
            $this->originalKeys[$stringValue] = $key;
            $this->structuredValues[$key]    = $stringValue;
        }
    }

    public function getChoices(): array
    {
        return $this->choices;
    }

    public function getValues(): array
    {
        return array_map(strval(...), array_keys($this->choices));
    }

    public function getStructuredValues(): array
    {
        return $this->structuredValues;
    }

    public function getOriginalKeys(): array
    {
        return $this->originalKeys;
    }

    public function getChoicesForValues(array $values): array
    {
        $choices = [];
        foreach ($values as $i => $givenValue) {
            if ((null === $givenValue || is_scalar($givenValue)) && array_key_exists((string) $givenValue, $this->choices)) {
                $choices[$i] = $this->choices[(string) $givenValue];
            }
        }

        return $choices;
    }

    public function getValuesForChoices(array $choices): array
    {
        $values = [];

        if (null !== $this->valueCallback) {
            foreach ($choices as $i => $givenChoice) {
                $values[$i] = (string) ($this->valueCallback)($givenChoice);
            }

            return $values;
        }

        // No callback: compare by identity.
        foreach ($choices as $i => $givenChoice) {
            foreach ($this->choices as $value => $choice) {
                if ($choice === $givenChoice) {
                    $values[$i] = (string) $value;
                    break;
                }
            }
        }

        return $values;
    }

    private static function castableToString(array $choices): bool
    {
        $seen = [];
        foreach ($choices as $choice) {
            if (!is_scalar($choice) && null !== $choice) {
                return false;
            }
            $string = false === $choice ? '0' : (string) $choice;
            if (isset($seen[$string])) {
                return false;
            }
            $seen[$string] = true;
        }

        return true;
    }
}
