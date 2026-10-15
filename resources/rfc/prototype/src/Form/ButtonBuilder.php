<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Events\Manager as EventsManager;
use Phalcon\Events\ManagerInterface as EventsManagerInterface;
use Phalcon\Form\Config\FormConfigBuilder;
use Phalcon\Form\Config\FormConfigInterface;
use Phalcon\Form\Data\DataMapperInterface;
use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\InvalidArgumentException;
use Phalcon\Form\RequestHandler\RequestHandlerInterface;
use Phalcon\Form\Transformer\DataTransformerInterface;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * Builder for {@see Button}. It is also the button's (frozen) config: only name, type, disabled,
 * attributes, options and auto_initialize carry meaning; children, data, transformers, events and
 * request handling are unsupported and throw BadMethodCallException, like Symfony's ButtonBuilder.
 */
class ButtonBuilder implements FormBuilderInterface
{
    protected bool $locked = false;
    private bool $disabled = false;
    private ResolvedTypeInterface $type;
    private string $name;
    /** @var array<string, mixed> */
    private array $attributes = [];
    /** @var array<string, mixed> */
    private array $options;
    private ?EventsManagerInterface $eventsManager = null;

    /** @throws InvalidArgumentException if the name is empty or invalid */
    public function __construct(?string $name, array $options = [])
    {
        if (null === $name || '' === $name) {
            throw new InvalidArgumentException('Buttons cannot have empty names.');
        }
        FormConfigBuilder::validateName($name);

        $this->name    = $name;
        $this->options = $options;
    }

    // ----- children: unsupported -----

    public function add(FormBuilderInterface|string $child, ?string $type = null, array $options = []): static
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function create(string $name, ?string $type = null, array $options = []): FormBuilderInterface
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function get(string $name): FormBuilderInterface
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function remove(string $name): static
    {
        throw new BadMethodCallException('Buttons cannot have children.');
    }

    public function has(string $name): bool
    {
        return false;
    }

    public function all(): array
    {
        return [];
    }

    public function count(): int
    {
        return 0;
    }

    public function getIterator(): \Traversable
    {
        return new \EmptyIterator();
    }

    // ----- building -----

    public function getForm(): FormInterface
    {
        return new Button($this->getFormConfig());
    }

    public function getFormConfig(): FormConfigInterface
    {
        $this->assertNotLocked();

        $config         = clone $this;
        $config->locked = true;

        return $config;
    }

    // ----- supported config setters -----

    public function setAttribute(string $name, mixed $value): static
    {
        $this->assertNotLocked();
        $this->attributes[$name] = $value;

        return $this;
    }

    public function setAttributes(array $attributes): static
    {
        $this->assertNotLocked();
        $this->attributes = $attributes;

        return $this;
    }

    public function setDisabled(bool $disabled): static
    {
        $this->assertNotLocked();
        $this->disabled = $disabled;

        return $this;
    }

    public function setType(ResolvedTypeInterface $type): static
    {
        $this->assertNotLocked();
        $this->type = $type;

        return $this;
    }

    /** Only false is accepted: buttons hold no data to initialize. */
    public function setAutoInitialize(bool $initialize): static
    {
        $this->assertNotLocked();
        if ($initialize) {
            throw new BadMethodCallException('Buttons do not support automatic initialization.');
        }

        return $this;
    }

    // ----- unsupported config setters -----

    public function addEventListener(string $eventName, callable $listener, int $priority = 100): static
    {
        throw new BadMethodCallException('Buttons do not support event listeners.');
    }

    public function addEventSubscriber(EventSubscriberInterface $subscriber): static
    {
        throw new BadMethodCallException('Buttons do not support event subscribers.');
    }

    public function addViewTransformer(DataTransformerInterface $transformer, bool $forcePrepend = false): static
    {
        throw new BadMethodCallException('Buttons do not support data transformers.');
    }

    public function resetViewTransformers(): static
    {
        throw new BadMethodCallException('Buttons do not support data transformers.');
    }

    public function addModelTransformer(DataTransformerInterface $transformer, bool $forceAppend = false): static
    {
        throw new BadMethodCallException('Buttons do not support data transformers.');
    }

    public function resetModelTransformers(): static
    {
        throw new BadMethodCallException('Buttons do not support data transformers.');
    }

    public function setDataMapper(?DataMapperInterface $dataMapper): static
    {
        throw new BadMethodCallException('Buttons do not support data mappers.');
    }

    public function setEmptyData(mixed $emptyData): static
    {
        throw new BadMethodCallException('Buttons do not support empty data.');
    }

    public function setErrorBubbling(bool $errorBubbling): static
    {
        throw new BadMethodCallException('Buttons do not support error bubbling.');
    }

    public function setRequired(bool $required): static
    {
        throw new BadMethodCallException('Buttons cannot be required.');
    }

    public function setPropertyPath(PropertyPathInterface|string|null $propertyPath): static
    {
        throw new BadMethodCallException('Buttons do not support property paths.');
    }

    public function setMapped(bool $mapped): static
    {
        throw new BadMethodCallException('Buttons do not support data mapping.');
    }

    public function setByReference(bool $byReference): static
    {
        throw new BadMethodCallException('Buttons do not support data mapping.');
    }

    public function setInheritData(bool $inheritData): static
    {
        throw new BadMethodCallException('Buttons do not support data inheritance.');
    }

    public function setCompound(bool $compound): static
    {
        throw new BadMethodCallException('Buttons cannot be compound.');
    }

    public function setData(mixed $data): static
    {
        throw new BadMethodCallException('Buttons do not support data.');
    }

    public function setDataLocked(bool $locked): static
    {
        throw new BadMethodCallException('Buttons do not support data locking.');
    }

    public function setFormFactory(FormFactoryInterface $formFactory): static
    {
        throw new BadMethodCallException('Buttons do not support form factories.');
    }

    public function setAction(string $action): static
    {
        throw new BadMethodCallException('Buttons do not support actions.');
    }

    public function setMethod(string $method): static
    {
        throw new BadMethodCallException('Buttons do not support methods.');
    }

    public function setRequestHandler(RequestHandlerInterface $requestHandler): static
    {
        throw new BadMethodCallException('Buttons do not support request handlers.');
    }

    public function setIsEmptyCallback(?\Closure $isEmptyCallback): static
    {
        throw new BadMethodCallException('Buttons do not support "is empty" callbacks.');
    }

    // ----- config getters -----

    /** Nothing fires events on a button; a fresh manager is returned so callers need no null checks. */
    public function getEventsManager(): EventsManagerInterface
    {
        return $this->eventsManager ??= new EventsManager();
    }

    public function getName(): string
    {
        return $this->name;
    }

    public function getPropertyPath(): ?PropertyPathInterface
    {
        return null;
    }

    public function getMapped(): bool
    {
        return false;
    }

    public function getByReference(): bool
    {
        return false;
    }

    public function getInheritData(): bool
    {
        return false;
    }

    public function getCompound(): bool
    {
        return false;
    }

    public function getType(): ResolvedTypeInterface
    {
        return $this->type;
    }

    public function getViewTransformers(): array
    {
        return [];
    }

    public function getModelTransformers(): array
    {
        return [];
    }

    public function getDataMapper(): ?DataMapperInterface
    {
        return null;
    }

    public function getRequired(): bool
    {
        return false;
    }

    public function getDisabled(): bool
    {
        return $this->disabled;
    }

    public function getErrorBubbling(): bool
    {
        return false;
    }

    public function getEmptyData(): mixed
    {
        return null;
    }

    public function getAttributes(): array
    {
        return $this->attributes;
    }

    public function hasAttribute(string $name): bool
    {
        return array_key_exists($name, $this->attributes);
    }

    public function getAttribute(string $name, mixed $default = null): mixed
    {
        return array_key_exists($name, $this->attributes) ? $this->attributes[$name] : $default;
    }

    public function getData(): mixed
    {
        return null;
    }

    public function getDataClass(): ?string
    {
        return null;
    }

    public function getDataLocked(): bool
    {
        return false;
    }

    public function getFormFactory(): FormFactoryInterface
    {
        throw new BadMethodCallException('Buttons do not support adding children.');
    }

    public function getAction(): string
    {
        return '';
    }

    public function getMethod(): string
    {
        return 'POST';
    }

    public function getRequestHandler(): RequestHandlerInterface
    {
        throw new BadMethodCallException('Buttons do not support request handlers.');
    }

    public function getAutoInitialize(): bool
    {
        return false;
    }

    public function getIsEmptyCallback(): ?\Closure
    {
        return null;
    }

    public function getOptions(): array
    {
        return $this->options;
    }

    public function hasOption(string $name): bool
    {
        return array_key_exists($name, $this->options);
    }

    public function getOption(string $name, mixed $default = null): mixed
    {
        return array_key_exists($name, $this->options) ? $this->options[$name] : $default;
    }

    protected function assertNotLocked(): void
    {
        if ($this->locked) {
            throw new BadMethodCallException('ButtonBuilder methods cannot be accessed anymore once the builder is turned into a FormConfigInterface instance.');
        }
    }
}
