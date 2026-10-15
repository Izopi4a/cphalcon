<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Config\FormConfigInterface;
use Phalcon\Form\Transformer\TransformationFailedException;
use Phalcon\Form\View\FormView;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * A node of the form tree.
 *
 * @extends \ArrayAccess<string, FormInterface>
 * @extends \IteratorAggregate<string, FormInterface>
 */
interface FormInterface extends \ArrayAccess, \IteratorAggregate, \Countable
{
    public function setParent(?FormInterface $parent): static;

    public function getParent(): ?FormInterface;

    public function getRoot(): FormInterface;

    public function isRoot(): bool;

    /** Adds a child form, or creates one from a type class name. */
    public function add(FormInterface|string $child, ?string $type = null, array $options = []): static;

    public function get(string $name): FormInterface;

    public function has(string $name): bool;

    public function remove(string $name): static;

    /** @return array<string, FormInterface> */
    public function all(): array;

    /** @return list<FormError> errors of this form; with $deep also of all descendants */
    public function getErrors(bool $deep = false): array;

    public function addError(FormError $error): static;

    public function clearErrors(bool $deep = false): static;

    /** Sets the model data (also runs the preSetData/postSetData events). */
    public function setData(mixed $modelData): static;

    public function getData(): mixed;

    public function getNormData(): mixed;

    public function getViewData(): mixed;

    /** @return array<string, mixed> submitted keys that matched no child */
    public function getExtraData(): array;

    public function getConfig(): FormConfigInterface;

    public function getName(): string;

    public function getPropertyPath(): ?PropertyPathInterface;

    public function isRequired(): bool;

    public function isDisabled(): bool;

    public function isEmpty(): bool;

    public function isSubmitted(): bool;

    /** False when a transformer failed on submit; the view data then holds the raw input. */
    public function isSynchronized(): bool;

    public function getTransformationFailure(): ?TransformationFailedException;

    public function isValid(): bool;

    public function getClickedButton(): ?ClickableInterface;

    /** Initializes a root form by setting its default data. */
    public function initialize(): static;

    /** Lets the configured request handler submit the form if the request contains it. */
    public function handleRequest(mixed $request = null): static;

    public function submit(mixed $submittedData, bool $clearMissing = true): static;

    public function createView(?FormView $parent = null): FormView;
}
