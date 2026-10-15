<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * One <option> (or one radio/checkbox) as seen by the view: the choice itself, its string value,
 * its label (false = render no label, used by expanded lists) and extra attributes.
 */
final class ChoiceView
{
    public function __construct(
        public readonly mixed $data,
        public readonly string $value,
        public readonly string|false $label,
        public readonly array $attr = [],
    ) {
    }
}
