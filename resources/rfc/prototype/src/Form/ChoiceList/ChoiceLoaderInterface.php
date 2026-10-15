<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * Loads choices on demand for a LazyChoiceList. Besides the full list a loader may know how to
 * fetch only the choices behind some values (a ModelType submission: one query by primary key
 * instead of the whole table).
 *
 * prototype: a plain "choice_loader" callable is still accepted everywhere (it is the full-list
 * loader alone); this interface is the shape Symfony's ChoiceLoaderInterface has, minus
 * loadValuesForChoices() which the "choice_value" callable already covers.
 */
interface ChoiceLoaderInterface
{
    /** @return iterable<int|string, mixed> the choices (label => choice, or a list) */
    public function loadChoices(): iterable;

    /**
     * Loads only the choices behind the given string values. Returns null when it cannot do
     * better than loading the whole list; the LazyChoiceList then falls back to loadChoices().
     *
     * @param list<string> $values
     *
     * @return iterable<int|string, mixed>|null the matching choices (any keys, matched by their value)
     */
    public function loadChoicesForValues(array $values): ?iterable;
}
