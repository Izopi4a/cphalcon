<?php
declare(strict_types=1);

namespace Phalcon\Form\ChoiceList;

/**
 * One <option> as seen by the view: the choice itself, its string value, its label and extra attributes.
 */
final class ChoiceView
{
    public function __construct(
        public readonly mixed $data,
        public readonly string $value,
        public readonly string $label,
        public readonly array $attr = [],
    ) {
    }
}
