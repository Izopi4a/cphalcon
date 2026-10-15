<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * One <optgroup>: a label and its ChoiceView (or nested ChoiceGroupView) children.
 */
final class ChoiceGroupView implements \IteratorAggregate
{
    /** @param array<int|string, ChoiceView|ChoiceGroupView> $choices */
    public function __construct(
        public readonly string $label,
        public array $choices = [],
    ) {
    }

    /** @return \ArrayIterator<int|string, ChoiceView|ChoiceGroupView> */
    public function getIterator(): \ArrayIterator
    {
        return new \ArrayIterator($this->choices);
    }
}
