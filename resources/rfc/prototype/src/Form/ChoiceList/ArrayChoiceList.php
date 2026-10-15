<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * Choice list over an array of label => choice, optionally nested one level or more as
 * group label => [label => choice]. Values are the stringified choices when all choices are
 * scalars with distinct string forms, otherwise their 0-based index; a "choice_value" callable
 * overrides both.
 *
 * The list itself is always flat (value => choice); the grouping only survives in
 * getStructuredValues(), which the view factory uses to build ChoiceGroupView instances.
 * Same algorithm as Symfony's ArrayChoiceList.
 */
class ArrayChoiceList implements ChoiceListInterface
{
    /** @var array<string, mixed> value => choice */
    protected array $choices = [];
    /** @var array<string, int|string> value => original key */
    protected array $originalKeys = [];
    /** @var array<int|string, string|array> original key => value, nested for groups */
    protected array $structuredValues = [];
    protected ?\Closure $valueCallback = null;

    /** @param iterable<int|string, mixed> $choices */
    public function __construct(iterable $choices, ?callable $value = null)
    {
        $choices = is_array($choices) ? $choices : iterator_to_array($choices);

        if (null === $value && self::castableToString($choices)) {
            $value = static fn (mixed $choice): string => false === $choice ? '0' : (string) $choice;
        }

        if (null !== $value) {
            // A deterministic value generator: also usable for getValuesForChoices()
            $this->valueCallback = $value(...);
        } else {
            // Otherwise generate incrementing integers as values
            $i     = 0;
            $value = static function () use (&$i): int {
                return $i++;
            };
        }

        $this->flatten($choices, $value, $this->choices, $this->originalKeys, $this->structuredValues);
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

    /**
     * Flattens nested choice arrays (groups) into value => choice while recording the structure.
     *
     * @param array<int|string, mixed> $choices
     */
    protected function flatten(array $choices, callable $value, array &$choicesByValues, array &$keysByValues, array &$structuredValues): void
    {
        foreach ($choices as $key => $choice) {
            if (is_array($choice)) {
                $structuredValues[$key] = [];
                $this->flatten($choice, $value, $choicesByValues, $keysByValues, $structuredValues[$key]);

                continue;
            }

            $choiceValue                  = (string) $value($choice);
            $choicesByValues[$choiceValue] = $choice;
            $keysByValues[$choiceValue]    = $key;
            $structuredValues[$key]        = $choiceValue;
        }
    }

    /**
     * All choices (groups included) scalar, with distinct string forms. Like Symfony a null
     * choice is not castable and switches the whole list to index values.
     */
    private static function castableToString(array $choices, array &$cache = []): bool
    {
        foreach ($choices as $choice) {
            if (is_array($choice)) {
                if (!self::castableToString($choice, $cache)) {
                    return false;
                }

                continue;
            }
            if (!is_scalar($choice)) {
                return false;
            }

            // prevent false being cast to the empty string
            $string = false === $choice ? '0' : (string) $choice;
            if (isset($cache[$string])) {
                return false;
            }
            $cache[$string] = true;
        }

        return true;
    }
}
