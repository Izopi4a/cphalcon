<?php
declare(strict_types=1);

namespace Phalcon\Form\Util;

use Phalcon\Form\FormInterface;

/**
 * Iterates over forms and descends into those with the "inherit_data" option,
 * so a DataMapper can reach the grandchildren that actually hold the data.
 *
 * @implements \RecursiveIterator<string, FormInterface>
 */
final class InheritDataAwareIterator extends \IteratorIterator implements \RecursiveIterator
{
    /** @param iterable<string, FormInterface> $forms */
    public function __construct(iterable $forms)
    {
        parent::__construct($forms instanceof \Traversable ? $forms : new \ArrayIterator($forms));
    }

    public function getChildren(): self
    {
        return new self($this->current()->all());
    }

    public function hasChildren(): bool
    {
        return $this->current()->getConfig()->getInheritData();
    }
}
