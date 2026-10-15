<?php
declare(strict_types=1);

namespace Phalcon\Form\Config;

use Phalcon\Events\Manager as EventsManager;
use Phalcon\Events\ManagerInterface as EventsManagerInterface;
use Phalcon\Form\Data\DataMapperInterface;
use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\InvalidArgumentException;
use Phalcon\Form\FormFactoryInterface;
use Phalcon\Form\RequestHandler\NativeRequestHandler;
use Phalcon\Form\RequestHandler\RequestHandlerInterface;
use Phalcon\Form\ResolvedTypeInterface;
use Phalcon\Form\Transformer\DataTransformerInterface;
use Phalcon\Support\PropertyAccess\PropertyPath;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

class FormConfigBuilder implements FormConfigBuilderInterface
{
    private const ALLOWED_METHODS = ['GET', 'PUT', 'POST', 'DELETE', 'PATCH'];

    private static ?RequestHandlerInterface $nativeRequestHandler = null;

    /** Room for 100k listeners per priority level before sequence numbers collide with the next level. */
    private const PRIORITY_SCALE = 100000;

    private int $listenerSequence = 0;

    protected bool $locked = false;
    private EventsManagerInterface $eventsManager;
    private string $name;
    private ?PropertyPathInterface $propertyPath = null;
    private bool $mapped = true;
    private bool $byReference = true;
    private bool $inheritData = false;
    private bool $compound = false;
    private ResolvedTypeInterface $type;
    /** @var list<DataTransformerInterface> */
    private array $viewTransformers = [];
    /** @var list<DataTransformerInterface> */
    private array $modelTransformers = [];
    private ?DataMapperInterface $dataMapper = null;
    private bool $required = true;
    private bool $disabled = false;
    private bool $errorBubbling = false;
    private mixed $emptyData = null;
    private array $attributes = [];
    private mixed $data = null;
    private ?string $dataClass;
    private bool $dataLocked = false;
    private ?FormFactoryInterface $formFactory = null;
    private string $action = '';
    private string $method = 'POST';
    private ?RequestHandlerInterface $requestHandler = null;
    private bool $autoInitialize = false;
    private ?\Closure $isEmptyCallback = null;
    private array $options;

    /**
     * @param string|null $name      null becomes "" (an unnamed root form)
     * @param string|null $dataClass FQCN the view data must be an instance of, or null for arrays/scalars
     */
    public function __construct(
        ?string $name,
        ?string $dataClass,
        ?EventsManagerInterface $eventsManager = null,
        array $options = []
    ) {
        self::validateName($name);

        if (null !== $dataClass && !class_exists($dataClass) && !interface_exists($dataClass, false)) {
            throw new InvalidArgumentException(sprintf('Class "%s" not found. Is the "data_class" form option set correctly?', $dataClass));
        }

        $this->name      = (string) $name;
        $this->dataClass = $dataClass;
        $this->options   = $options;

        if (null === $eventsManager) {
            $eventsManager = new EventsManager();
            $eventsManager->enablePriorities(true);
        }
        $this->eventsManager = $eventsManager;
    }

    public function addEventListener(string $eventName, callable $listener, int $priority = 100): static
    {
        $this->assertNotLocked();

        // Phalcon's Events\Manager keeps handlers in an SplPriorityQueue, whose order for equal
        // priorities is undefined. Forms rely on insertion order within a priority (Symfony
        // guarantees it), so fold a decreasing sequence number into the effective priority.
        // prototype: in Zephir this belongs in Events\Manager itself (stable ordering).
        $effectivePriority = $priority * self::PRIORITY_SCALE - $this->listenerSequence++;

        // Phalcon handlers are called as (Event, source, data); our listeners take the FormEvent (= data).
        $this->eventsManager->attach(
            $eventName,
            static function ($event, $source, $data) use ($listener): void {
                if ($data instanceof FormEvent) {
                    $listener($data);
                }
            },
            $effectivePriority
        );

        return $this;
    }

    public function addEventSubscriber(EventSubscriberInterface $subscriber): static
    {
        $this->assertNotLocked();

        foreach ($subscriber::getSubscribedEvents() as $eventName => $params) {
            if (is_string($params)) {
                $this->addEventListener($eventName, $subscriber->$params(...));
            } else {
                $this->addEventListener($eventName, $subscriber->{$params[0]}(...), $params[1] ?? 100);
            }
        }

        return $this;
    }

    public function addViewTransformer(DataTransformerInterface $transformer, bool $forcePrepend = false): static
    {
        $this->assertNotLocked();
        if ($forcePrepend) {
            array_unshift($this->viewTransformers, $transformer);
        } else {
            $this->viewTransformers[] = $transformer;
        }

        return $this;
    }

    public function resetViewTransformers(): static
    {
        $this->assertNotLocked();
        $this->viewTransformers = [];

        return $this;
    }

    public function addModelTransformer(DataTransformerInterface $transformer, bool $forceAppend = false): static
    {
        $this->assertNotLocked();
        if ($forceAppend) {
            $this->modelTransformers[] = $transformer;
        } else {
            array_unshift($this->modelTransformers, $transformer);
        }

        return $this;
    }

    public function resetModelTransformers(): static
    {
        $this->assertNotLocked();
        $this->modelTransformers = [];

        return $this;
    }

    public function getEventsManager(): EventsManagerInterface
    {
        return $this->eventsManager;
    }

    public function getName(): string
    {
        return $this->name;
    }

    public function getPropertyPath(): ?PropertyPathInterface
    {
        return $this->propertyPath;
    }

    public function getMapped(): bool
    {
        return $this->mapped;
    }

    public function getByReference(): bool
    {
        return $this->byReference;
    }

    public function getInheritData(): bool
    {
        return $this->inheritData;
    }

    public function getCompound(): bool
    {
        return $this->compound;
    }

    public function getType(): ResolvedTypeInterface
    {
        return $this->type;
    }

    public function getViewTransformers(): array
    {
        return $this->viewTransformers;
    }

    public function getModelTransformers(): array
    {
        return $this->modelTransformers;
    }

    public function getDataMapper(): ?DataMapperInterface
    {
        return $this->dataMapper;
    }

    public function getRequired(): bool
    {
        return $this->required;
    }

    public function getDisabled(): bool
    {
        return $this->disabled;
    }

    public function getErrorBubbling(): bool
    {
        return $this->errorBubbling;
    }

    public function getEmptyData(): mixed
    {
        return $this->emptyData;
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
        return $this->data;
    }

    public function getDataClass(): ?string
    {
        return $this->dataClass;
    }

    public function getDataLocked(): bool
    {
        return $this->dataLocked;
    }

    public function getFormFactory(): FormFactoryInterface
    {
        if (null === $this->formFactory) {
            throw new BadMethodCallException('The form factory must be set before retrieving it.');
        }

        return $this->formFactory;
    }

    public function getAction(): string
    {
        return $this->action;
    }

    public function getMethod(): string
    {
        return $this->method;
    }

    public function getRequestHandler(): RequestHandlerInterface
    {
        return $this->requestHandler ??= (self::$nativeRequestHandler ??= new NativeRequestHandler());
    }

    public function getAutoInitialize(): bool
    {
        return $this->autoInitialize;
    }

    public function getIsEmptyCallback(): ?\Closure
    {
        return $this->isEmptyCallback;
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

    public function setDataMapper(?DataMapperInterface $dataMapper): static
    {
        $this->assertNotLocked();
        $this->dataMapper = $dataMapper;

        return $this;
    }

    public function setDisabled(bool $disabled): static
    {
        $this->assertNotLocked();
        $this->disabled = $disabled;

        return $this;
    }

    public function setEmptyData(mixed $emptyData): static
    {
        $this->assertNotLocked();
        $this->emptyData = $emptyData;

        return $this;
    }

    public function setErrorBubbling(bool $errorBubbling): static
    {
        $this->assertNotLocked();
        $this->errorBubbling = $errorBubbling;

        return $this;
    }

    public function setRequired(bool $required): static
    {
        $this->assertNotLocked();
        $this->required = $required;

        return $this;
    }

    public function setPropertyPath(PropertyPathInterface|string|null $propertyPath): static
    {
        $this->assertNotLocked();
        if (is_string($propertyPath)) {
            $propertyPath = new PropertyPath($propertyPath);
        }
        $this->propertyPath = $propertyPath;

        return $this;
    }

    public function setMapped(bool $mapped): static
    {
        $this->assertNotLocked();
        $this->mapped = $mapped;

        return $this;
    }

    public function setByReference(bool $byReference): static
    {
        $this->assertNotLocked();
        $this->byReference = $byReference;

        return $this;
    }

    public function setInheritData(bool $inheritData): static
    {
        $this->assertNotLocked();
        $this->inheritData = $inheritData;

        return $this;
    }

    public function setCompound(bool $compound): static
    {
        $this->assertNotLocked();
        $this->compound = $compound;

        return $this;
    }

    public function setType(ResolvedTypeInterface $type): static
    {
        $this->assertNotLocked();
        $this->type = $type;

        return $this;
    }

    public function setData(mixed $data): static
    {
        $this->assertNotLocked();
        $this->data = $data;

        return $this;
    }

    public function setDataLocked(bool $locked): static
    {
        $this->assertNotLocked();
        $this->dataLocked = $locked;

        return $this;
    }

    public function setFormFactory(FormFactoryInterface $formFactory): static
    {
        $this->assertNotLocked();
        $this->formFactory = $formFactory;

        return $this;
    }

    public function setAction(string $action): static
    {
        $this->assertNotLocked();
        $this->action = $action;

        return $this;
    }

    public function setMethod(string $method): static
    {
        $this->assertNotLocked();
        $upper = strtoupper($method);
        if (!in_array($upper, self::ALLOWED_METHODS, true)) {
            throw new InvalidArgumentException(sprintf('The form method is "%s", but should be one of "%s".', $method, implode('", "', self::ALLOWED_METHODS)));
        }
        $this->method = $upper;

        return $this;
    }

    public function setRequestHandler(RequestHandlerInterface $requestHandler): static
    {
        $this->assertNotLocked();
        $this->requestHandler = $requestHandler;

        return $this;
    }

    public function setAutoInitialize(bool $initialize): static
    {
        $this->assertNotLocked();
        $this->autoInitialize = $initialize;

        return $this;
    }

    public function setIsEmptyCallback(?\Closure $isEmptyCallback): static
    {
        $this->assertNotLocked();
        $this->isEmptyCallback = $isEmptyCallback;

        return $this;
    }

    public function getFormConfig(): FormConfigInterface
    {
        $this->assertNotLocked();

        $config         = clone $this;
        $config->locked = true;

        return $config;
    }

    /**
     * Child names: letters, digits, underscore, then also "-" and ":". Empty is allowed (root only).
     */
    public static function validateName(?string $name): void
    {
        if (null !== $name && '' !== $name && !preg_match('/^[a-zA-Z0-9_][a-zA-Z0-9_\-:]*$/D', $name)) {
            throw new InvalidArgumentException(sprintf(
                'The name "%s" contains illegal characters. Names should start with a letter, digit or underscore and only contain letters, digits, numbers, underscores ("_"), hyphens ("-") and colons (":").',
                $name
            ));
        }
    }

    protected function assertNotLocked(): void
    {
        if ($this->locked) {
            throw new BadMethodCallException('FormConfigBuilder methods cannot be accessed anymore once the builder is turned into a FormConfigInterface instance.');
        }
    }
}
