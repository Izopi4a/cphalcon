<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Config\FormConfigInterface;
use Phalcon\Form\Exception\AlreadySubmittedException;
use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Transformer\TransformationFailedException;
use Phalcon\Form\View\FormView;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * A button in the form tree. It is a leaf that holds no data: the data accessors return
 * null/[] and the mutators are no-ops or throw, like Symfony's Button. Submitting it records
 * whether it was clicked (the browser only sends the button's name when it was pressed).
 */
class Button implements FormInterface, ClickableInterface
{
    private ?FormInterface $parent = null;
    private bool $submitted = false;
    private bool $clicked = false;
    /** @var list<FormError> */
    private array $errors = [];

    public function __construct(private readonly FormConfigInterface $config)
    {
    }

    public function offsetExists(mixed $offset): bool
    {
        return false;
    }

    public function offsetGet(mixed $offset): FormInterface
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function offsetSet(mixed $offset, mixed $value): void
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function offsetUnset(mixed $offset): void
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function setParent(?FormInterface $parent): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('You cannot set the parent of a submitted button.');
        }

        $this->parent = $parent;

        return $this;
    }

    public function getParent(): ?FormInterface
    {
        return $this->parent;
    }

    public function getRoot(): FormInterface
    {
        return $this->parent?->getRoot() ?? $this;
    }

    public function isRoot(): bool
    {
        return null === $this->parent;
    }

    public function add(FormInterface|string $child, ?string $type = null, array $options = []): static
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function get(string $name): FormInterface
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function has(string $name): bool
    {
        return false;
    }

    public function remove(string $name): static
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function all(): array
    {
        return [];
    }

    public function getErrors(bool $deep = false): array
    {
        return $this->errors;
    }

    public function addError(FormError $error): static
    {
        if (null === $error->getOrigin()) {
            $error->setOrigin($this);
        }

        $this->errors[] = $error;

        return $this;
    }

    public function clearErrors(bool $deep = false): static
    {
        $this->errors = [];

        return $this;
    }

    /** Buttons hold no data; this is a no-op, kept so a data mapper can treat buttons like any child. */
    public function setData(mixed $modelData): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('You cannot change the data of a submitted button.');
        }

        return $this;
    }

    public function getData(): mixed
    {
        return null;
    }

    public function getNormData(): mixed
    {
        return null;
    }

    public function getViewData(): mixed
    {
        return null;
    }

    public function getExtraData(): array
    {
        return [];
    }

    public function getConfig(): FormConfigInterface
    {
        return $this->config;
    }

    public function getName(): string
    {
        return $this->config->getName();
    }

    public function getPropertyPath(): ?PropertyPathInterface
    {
        return null;
    }

    public function isRequired(): bool
    {
        if (null === $this->parent || $this->parent->isRequired()) {
            return $this->config->getRequired();
        }

        return false;
    }

    public function isDisabled(): bool
    {
        if (null === $this->parent || !$this->parent->isDisabled()) {
            return $this->config->getDisabled();
        }

        return true;
    }

    public function isEmpty(): bool
    {
        return true;
    }

    public function isSubmitted(): bool
    {
        return $this->submitted;
    }

    public function isSynchronized(): bool
    {
        return true;
    }

    public function getTransformationFailure(): ?TransformationFailedException
    {
        return null;
    }

    /** A button is valid once it was submitted and nothing attached an error to it. */
    public function isValid(): bool
    {
        return $this->submitted && [] === $this->errors;
    }

    public function isClicked(): bool
    {
        return $this->clicked;
    }

    public function getClickedButton(): ?ClickableInterface
    {
        if ($this->clicked) {
            return $this;
        }

        return null !== $this->parent && method_exists($this->parent, 'getClickedButton') ? $this->parent->getClickedButton() : null;
    }

    public function initialize(): static
    {
        throw new BadMethodCallException('Buttons cannot be initialized. Call initialize() on the root form instead.');
    }

    public function handleRequest(mixed $request = null): static
    {
        throw new BadMethodCallException('Buttons cannot handle requests. Call handleRequest() on the root form instead.');
    }

    /**
     * Browsers only send a button's name/value pair when that button was pressed, so a non-null
     * payload means "clicked". Buttons are leaves: $clearMissing is irrelevant.
     */
    public function submit(mixed $submittedData, bool $clearMissing = true): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('A form can only be submitted once.');
        }

        $this->submitted = true;
        $this->clicked   = null !== $submittedData;

        return $this;
    }

    public function createView(?FormView $parent = null): FormView
    {
        if (null === $parent && null !== $this->parent) {
            $parent = $this->parent->createView();
        }

        $type    = $this->config->getType();
        $options = $this->config->getOptions();

        $view = $type->createView($this, $parent);

        $type->buildView($view, $this, $options);
        $type->finishView($view, $this, $options);

        return $view;
    }

    public function getIterator(): \Traversable
    {
        return new \EmptyIterator();
    }

    public function count(): int
    {
        return 0;
    }
}
