<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * Maps choices (the model values) to the string "values" rendered in HTML and back.
 */
interface ChoiceListInterface
{
    /** @return array<string, mixed> value => choice */
    public function getChoices(): array;

    /** @return list<string> */
    public function getValues(): array;

    /** @return array<int|string, string> original key => value */
    public function getStructuredValues(): array;

    /** @return array<string, int|string> value => original key (the label when choices are label => value) */
    public function getOriginalKeys(): array;

    /**
     * @param list<string> $values
     * @return array<int|string, mixed> choices, keyed like the given values; unknown values are dropped
     */
    public function getChoicesForValues(array $values): array;

    /**
     * @param list<mixed> $choices
     * @return array<int|string, string> values, keyed like the given choices; unknown choices are dropped
     */
    public function getValuesForChoices(array $choices): array;
}
