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
    private ?ChoiceListInterface $loaded = null;

    /** @param callable(): iterable<int|string, mixed> $loader */
    public function __construct(callable $loader, ?callable $value = null)
    {
        $this->loader = $loader(...);
        $this->value  = null !== $value ? $value(...) : null;
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
