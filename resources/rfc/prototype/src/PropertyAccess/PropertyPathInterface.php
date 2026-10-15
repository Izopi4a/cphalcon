<?php
declare(strict_types=1);

namespace Phalcon\Support\PropertyAccess;

/**
 * A parsed path such as "address.lines[0].text": dots address properties, brackets address indices.
 */
interface PropertyPathInterface extends \Stringable, \Countable
{
    public function getLength(): int;

    /** Path without the last element, or null for a single-element path. */
    public function getParent(): ?self;

    /** @return list<string> */
    public function getElements(): array;

    public function getElement(int $index): string;

    public function isProperty(int $index): bool;

    public function isIndex(int $index): bool;
}
