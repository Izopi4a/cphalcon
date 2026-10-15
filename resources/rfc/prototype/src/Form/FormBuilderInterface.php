<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Config\FormConfigBuilderInterface;

/**
 * @extends \IteratorAggregate<string, FormBuilderInterface>
 */
interface FormBuilderInterface extends \Countable, \IteratorAggregate, FormConfigBuilderInterface
{
    /** Adds a child by name (created lazily from $type) or an existing builder. */
    public function add(FormBuilderInterface|string $child, ?string $type = null, array $options = []): static;

    /** Creates a child builder without adding it. */
    public function create(string $name, ?string $type = null, array $options = []): FormBuilderInterface;

    public function get(string $name): FormBuilderInterface;

    public function remove(string $name): static;

    public function has(string $name): bool;

    /** @return array<string, FormBuilderInterface> */
    public function all(): array;

    public function getForm(): FormInterface;
}
