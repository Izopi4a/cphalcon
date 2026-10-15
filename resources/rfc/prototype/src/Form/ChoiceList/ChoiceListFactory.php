<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

use Phalcon\Support\PropertyAccess\PropertyAccessor;
use Phalcon\Support\PropertyAccess\PropertyAccessorInterface;
use Phalcon\Support\PropertyAccess\PropertyPath;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;
use Phalcon\Support\PropertyAccess\UnexpectedTypeException;

/**
 * Builds choice lists and their view structure. Merges Symfony's DefaultChoiceListFactory and
 * PropertyAccessDecorator: every callable option may also be given as a property path string,
 * which is read on each choice with the PropertyAccessor.
 *
 * prototype: no CachingFactoryDecorator (lists are rebuilt per form).
 */
final class ChoiceListFactory
{
    public function __construct(private readonly PropertyAccessorInterface $accessor = new PropertyAccessor())
    {
    }

    /** @param iterable<int|string, mixed> $choices */
    public function createListFromChoices(iterable $choices, callable|string|PropertyPathInterface|null $value = null): ChoiceListInterface
    {
        return new ArrayChoiceList($choices, $this->valueCallable($value));
    }

    /** @param callable(): iterable<int|string, mixed> $loader */
    public function createListFromLoader(callable $loader, callable|string|PropertyPathInterface|null $value = null): ChoiceListInterface
    {
        return new LazyChoiceList($loader, $this->valueCallable($value));
    }

    /**
     * @param array|callable|string|PropertyPathInterface|null $preferredChoices array of choices or callable(choice, key, value): bool|int
     * @param callable|string|PropertyPathInterface|bool|null  $label            null: original key; false: no label; callable(choice, key, value)
     * @param callable|string|PropertyPathInterface|null       $groupBy          callable(choice, key, value): string|list<string>|null
     * @param array|callable|string|PropertyPathInterface|null $attr             attr by original key, or callable(choice, key, value): array
     */
    public function createView(
        ChoiceListInterface $list,
        array|callable|string|PropertyPathInterface|null $preferredChoices = null,
        callable|string|PropertyPathInterface|bool|null $label = null,
        callable|string|PropertyPathInterface|null $groupBy = null,
        array|callable|string|PropertyPathInterface|null $attr = null,
        bool $duplicatePreferredChoices = true,
    ): ChoiceListView {
        $accessor = $this->accessor;

        if (is_string($label) || $label instanceof PropertyPathInterface) {
            $path  = self::path($label);
            $label = static fn (mixed $choice): mixed => $accessor->getValue($choice, $path);
        }
        if (is_string($preferredChoices) || $preferredChoices instanceof PropertyPathInterface) {
            $path             = self::path($preferredChoices);
            $preferredChoices = static function (mixed $choice) use ($accessor, $path): mixed {
                try {
                    return $accessor->getValue($choice, $path);
                } catch (UnexpectedTypeException) {
                    return false; // not preferred when not readable
                }
            };
        }
        if (is_string($groupBy) || $groupBy instanceof PropertyPathInterface) {
            $path    = self::path($groupBy);
            $groupBy = static function (mixed $choice) use ($accessor, $path): mixed {
                try {
                    return $accessor->getValue($choice, $path);
                } catch (UnexpectedTypeException) {
                    return null; // not grouped when not readable
                }
            };
        }
        if (is_string($attr) || $attr instanceof PropertyPathInterface) {
            $path = self::path($attr);
            $attr = static fn (mixed $choice): mixed => $accessor->getValue($choice, $path);
        }

        // arrays are always lists of preferred choices, even when they happen to look callable
        if (!is_callable($preferredChoices) || is_array($preferredChoices)) {
            if (null === $preferredChoices || [] === $preferredChoices) {
                $preferredChoices = null;
            } else {
                $preferredList    = array_values($preferredChoices);
                $preferredChoices = static fn (mixed $choice): int|false => array_search($choice, $preferredList, true);
            }
        }

        $preferredViews      = [];
        $preferredViewsOrder = [];
        $otherViews          = [];
        $choices             = $list->getChoices();
        $keys                = $list->getOriginalKeys();
        $index               = 0;

        if (null !== $groupBy) {
            foreach ($choices as $value => $choice) {
                $this->addChoiceViewsGroupedByCallable($groupBy, $choice, (string) $value, $label, $keys, $index, $attr, $preferredChoices, $preferredViews, $preferredViewsOrder, $otherViews, $duplicatePreferredChoices);
            }

            // Remove empty group views that may have been created by addChoiceViewsGroupedByCallable()
            foreach ($preferredViews as $key => $view) {
                if ($view instanceof ChoiceGroupView && 0 === count($view->choices)) {
                    unset($preferredViews[$key]);
                }
            }
            foreach ($otherViews as $key => $view) {
                if ($view instanceof ChoiceGroupView && 0 === count($view->choices)) {
                    unset($otherViews[$key]);
                }
            }
            foreach ($preferredViewsOrder as $key => $groupViewsOrder) {
                if (is_array($groupViewsOrder)) {
                    if ([] !== $groupViewsOrder) {
                        $preferredViewsOrder[$key] = min($groupViewsOrder);
                    } else {
                        unset($preferredViewsOrder[$key]);
                    }
                }
            }
        } else {
            // Otherwise use the original structure of the choices
            $this->addChoiceViewsFromStructuredValues($list->getStructuredValues(), $label, $choices, $keys, $index, $attr, $preferredChoices, $preferredViews, $preferredViewsOrder, $otherViews, $duplicatePreferredChoices);
        }

        uksort($preferredViews, static fn ($a, $b): int => isset($preferredViewsOrder[$a], $preferredViewsOrder[$b])
            ? $preferredViewsOrder[$a] <=> $preferredViewsOrder[$b]
            : 0);

        return new ChoiceListView($otherViews, $preferredViews);
    }

    private function addChoiceView(mixed $choice, string $value, callable|false|null $label, array $keys, int &$index, array|callable|null $attr, ?callable $isPreferred, array &$preferredViews, array &$preferredViewsOrder, array &$otherViews, bool $duplicatePreferredChoices): void
    {
        $key       = $keys[$value];
        $nextIndex = $index++;

        if (null === $label) {
            // If the labels are null, use the original choice key by default
            $label = (string) $key;
        } elseif (false !== $label) {
            // "choice_label" false (no label) is passed on to expanded children
            $dynamicLabel = $label($choice, $key, $value);
            $label        = false === $dynamicLabel ? false : (string) $dynamicLabel;
        }

        $view = new ChoiceView(
            $choice,
            $value,
            $label,
            // The attributes may be a callable or a mapping from choice keys to nested arrays
            is_callable($attr) && !is_array($attr) ? (array) $attr($choice, $key, $value) : ($attr[$key] ?? []),
        );

        // $isPreferred may be null if no choices are preferred
        if (null !== $isPreferred && false !== $preferredKey = $isPreferred($choice, $key, $value)) {
            $preferredViews[$nextIndex]      = $view;
            $preferredViewsOrder[$nextIndex] = $preferredKey;

            if ($duplicatePreferredChoices) {
                $otherViews[$nextIndex] = $view;
            }
        } else {
            $otherViews[$nextIndex] = $view;
        }
    }

    private function addChoiceViewsFromStructuredValues(array $values, callable|false|null $label, array $choices, array $keys, int &$index, array|callable|null $attr, ?callable $isPreferred, array &$preferredViews, array &$preferredViewsOrder, array &$otherViews, bool $duplicatePreferredChoices): void
    {
        foreach ($values as $key => $value) {
            if (null === $value) {
                continue;
            }

            // Add the contents of groups to new ChoiceGroupView instances
            if (is_array($value)) {
                $preferredViewsForGroup = [];
                $otherViewsForGroup     = [];

                $this->addChoiceViewsFromStructuredValues($value, $label, $choices, $keys, $index, $attr, $isPreferred, $preferredViewsForGroup, $preferredViewsOrder, $otherViewsForGroup, $duplicatePreferredChoices);

                if (count($preferredViewsForGroup) > 0) {
                    $preferredViews[$key] = new ChoiceGroupView((string) $key, $preferredViewsForGroup);
                }
                if (count($otherViewsForGroup) > 0) {
                    $otherViews[$key] = new ChoiceGroupView((string) $key, $otherViewsForGroup);
                }

                continue;
            }

            // Add ungrouped items directly
            $this->addChoiceView($choices[$value], (string) $value, $label, $keys, $index, $attr, $isPreferred, $preferredViews, $preferredViewsOrder, $otherViews, $duplicatePreferredChoices);
        }
    }

    private function addChoiceViewsGroupedByCallable(callable $groupBy, mixed $choice, string $value, callable|false|null $label, array $keys, int &$index, array|callable|null $attr, ?callable $isPreferred, array &$preferredViews, array &$preferredViewsOrder, array &$otherViews, bool $duplicatePreferredChoices): void
    {
        $groupLabels = $groupBy($choice, $keys[$value], $value);

        if (null === $groupLabels) {
            // If the callable returns null, don't group the choice
            $this->addChoiceView($choice, $value, $label, $keys, $index, $attr, $isPreferred, $preferredViews, $preferredViewsOrder, $otherViews, $duplicatePreferredChoices);

            return;
        }

        $groupLabels = is_array($groupLabels) ? array_map(strval(...), $groupLabels) : [(string) $groupLabels];

        foreach ($groupLabels as $groupLabel) {
            // Initialize the group views if necessary. Unnecessarily built group views are
            // cleaned up at the end of createView()
            if (!isset($preferredViews[$groupLabel])) {
                $preferredViews[$groupLabel] = new ChoiceGroupView($groupLabel);
                $otherViews[$groupLabel]     = new ChoiceGroupView($groupLabel);
            }
            if (!isset($preferredViewsOrder[$groupLabel])) {
                $preferredViewsOrder[$groupLabel] = [];
            }

            $this->addChoiceView($choice, $value, $label, $keys, $index, $attr, $isPreferred, $preferredViews[$groupLabel]->choices, $preferredViewsOrder[$groupLabel], $otherViews[$groupLabel]->choices, $duplicatePreferredChoices);
        }
    }

    private function valueCallable(callable|string|PropertyPathInterface|null $value): ?callable
    {
        if (is_string($value) || $value instanceof PropertyPathInterface) {
            $accessor = $this->accessor;
            $path     = self::path($value);

            // The callable may be invoked with a non-object/array value when such values are
            // passed to getValuesForChoices() (e.g. null data). Handle this case so that the call
            // to getValue() doesn't break.
            return static fn (mixed $choice): mixed => is_object($choice) || is_array($choice) ? $accessor->getValue($choice, $path) : null;
        }

        return $value;
    }

    private static function path(string|PropertyPathInterface $path): PropertyPathInterface
    {
        return $path instanceof PropertyPathInterface ? $path : new PropertyPath($path);
    }
}
