<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * The view-side structure of a choice list: all choices (grouped or not) plus the preferred ones.
 */
final class ChoiceListView
{
    /**
     * @param array<int|string, ChoiceView|ChoiceGroupView> $choices
     * @param array<int|string, ChoiceView|ChoiceGroupView> $preferredChoices
     */
    public function __construct(
        public array $choices = [],
        public array $preferredChoices = [],
    ) {
    }

    /**
     * Whether the first rendered option already is the "" option, in which case the type does
     * not add its own placeholder option (same rule as Symfony: only the first option counts).
     */
    public function hasPlaceholder(): bool
    {
        if ([] !== $this->preferredChoices) {
            $first = reset($this->preferredChoices);

            return $first instanceof ChoiceView && '' === $first->value;
        }

        $first = reset($this->choices);

        return $first instanceof ChoiceView && '' === $first->value;
    }
}
