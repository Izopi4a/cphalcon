<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * Choice list whose choices come from a loader callable that is invoked at most once, on the
 * first access that really needs the choices. Lookups of empty values/choices do not load.
 *
 * prototype: stand-in for Symfony's ChoiceLoaderInterface/LazyChoiceList pair. The RFC should
 * decide whether a "choice_loader" callable suffices or a loader interface (with
 * loadChoicesForValues/loadValuesForChoices, needed by ModelType to query by primary key only)
 * is wanted.
 */
final class LazyChoiceList implements ChoiceListInterface
{
    private \Closure $loader;
    private ?\Closure $value;
    private ?\Closure $loaderForValues;
    private ?ChoiceListInterface $loaded = null;

    /**
     * @param callable(): iterable<int|string, mixed>                     $loader
     * @param callable(mixed): mixed|null                                 $value           choice => value
     * @param callable(list<string>): (iterable<int|string, mixed>|null)  $loaderForValues loads only the choices behind
     *                                                                                     some values; null result = "load everything".
     *                                                                                     Only used together with $value.
     */
    public function __construct(callable $loader, ?callable $value = null, ?callable $loaderForValues = null)
    {
        $this->loader          = $loader(...);
        $this->value           = null !== $value ? $value(...) : null;
        $this->loaderForValues = null !== $loaderForValues ? $loaderForValues(...) : null;
    }

    public function isLoaded(): bool
    {
        return null !== $this->loaded;
    }

    public function getChoices(): array
    {
        return $this->load()->getChoices();
    }

    public function getValues(): array
    {
        return $this->load()->getValues();
    }

    public function getStructuredValues(): array
    {
        return $this->load()->getStructuredValues();
    }

    public function getOriginalKeys(): array
    {
        return $this->load()->getOriginalKeys();
    }

    public function getChoicesForValues(array $values): array
    {
        // Optimisation: no value, nothing to look up (and no need to load)
        if ([] === array_filter($values, static fn (mixed $v): bool => null !== $v && '' !== $v)) {
            return [];
        }

        // Optimisation: before the list is loaded, let the loader fetch only the wanted choices
        // (ModelType: one query by primary key for a submission). The list stays unloaded; the
        // view, if ever built, loads it then.
        if (null === $this->loaded && null !== $this->loaderForValues && null !== $this->value) {
            $loaded = ($this->loaderForValues)(array_values(array_map(strval(...), array_filter($values, static fn (mixed $v): bool => null !== $v))));

            if (null !== $loaded) {
                $byValue = [];
                foreach ($loaded as $choice) {
                    $byValue[(string) ($this->value)($choice)] = $choice;
                }

                $choices = [];
                foreach ($values as $i => $givenValue) {
                    if ((null === $givenValue || is_scalar($givenValue)) && array_key_exists((string) $givenValue, $byValue)) {
                        $choices[$i] = $byValue[(string) $givenValue];
                    }
                }

                return $choices;
            }
        }

        return $this->load()->getChoicesForValues($values);
    }

    public function getValuesForChoices(array $choices): array
    {
        if ([] === array_filter($choices, static fn (mixed $c): bool => null !== $c && '' !== $c)) {
            return [];
        }

        // With a value callback the values can be computed from the choices alone: no need to load
        // (this is what lets a preselected entity render without querying the whole list)
        if (null !== $this->value) {
            return array_map(fn (mixed $choice): string => (string) ($this->value)($choice), $choices);
        }

        return $this->load()->getValuesForChoices($choices);
    }

    private function load(): ChoiceListInterface
    {
        return $this->loaded ??= new ArrayChoiceList(($this->loader)(), $this->value);
    }
}
