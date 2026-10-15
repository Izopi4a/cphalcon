<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Events\ManagerInterface as EventsManagerInterface;
use Phalcon\Form\Config\FormConfigBuilder;
use Phalcon\Form\Config\FormConfigInterface;
use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\InvalidArgumentException;
use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\Type\Core\TextType;

class FormBuilder extends FormConfigBuilder implements FormBuilderInterface
{
    /** @var array<string, FormBuilderInterface> */
    private array $children = [];
    /** @var array<string, array{0: string, 1: array}> name => [type, options] */
    private array $unresolvedChildren = [];

    public function __construct(
        ?string $name,
        ?string $dataClass,
        ?EventsManagerInterface $eventsManager,
        FormFactoryInterface $factory,
        array $options = []
    ) {
        parent::__construct($name, $dataClass, $eventsManager, $options);
        $this->setFormFactory($factory);
    }

    public function add(FormBuilderInterface|string $child, ?string $type = null, array $options = []): static
    {
        $this->assertNotLocked();

        if ($child instanceof FormBuilderInterface) {
            $this->children[$child->getName()] = $child;
            unset($this->unresolvedChildren[$child->getName()]);

            return $this;
        }

        if ('' === $child) {
            throw new UnexpectedTypeException($child, 'non-empty string');
        }
        if (null !== $type && !is_string($type)) {
            throw new UnexpectedTypeException($type, 'string or null');
        }

        // Add to "children" to maintain order
        $this->children[$child]           = null;
        $this->unresolvedChildren[$child] = [$type, $options];

        return $this;
    }

    public function create(string $name, ?string $type = null, array $options = []): FormBuilderInterface
    {
        $this->assertNotLocked();

        return $this->getFormFactory()->createNamedBuilder($name, $type ?? TextType::class, null, $options);
    }

    public function get(string $name): FormBuilderInterface
    {
        $this->assertNotLocked();

        if (isset($this->unresolvedChildren[$name])) {
            return $this->resolveChild($name);
        }
        if (isset($this->children[$name])) {
            return $this->children[$name];
        }

        throw new InvalidArgumentException(sprintf('The child with the name "%s" does not exist.', $name));
    }

    public function remove(string $name): static
    {
        $this->assertNotLocked();
        unset($this->unresolvedChildren[$name], $this->children[$name]);

        return $this;
    }

    public function has(string $name): bool
    {
        $this->assertNotLocked();

        return isset($this->unresolvedChildren[$name]) || isset($this->children[$name]);
    }

    public function all(): array
    {
        $this->assertNotLocked();
        $this->resolveChildren();

        return $this->children;
    }

    public function count(): int
    {
        $this->assertNotLocked();

        return count($this->children);
    }

    public function getFormConfig(): FormConfigInterface
    {
        /** @var self $config */
        $config = parent::getFormConfig();

        $config->children           = [];
        $config->unresolvedChildren = [];

        return $config;
    }

    public function getForm(): FormInterface
    {
        $this->assertNotLocked();
        $this->resolveChildren();

        $form = new Form($this->getFormConfig());

        foreach ($this->children as $child) {
            // Automatic initialization is only supported on root forms
            $form->add($child->setAutoInitialize(false)->getForm());
        }

        if ($this->getAutoInitialize()) {
            // Automatically initialize the form if it is configured so
            $form->initialize();
        }

        return $form;
    }

    public function getIterator(): \Traversable
    {
        return new \ArrayIterator($this->all());
    }

    private function resolveChild(string $name): FormBuilderInterface
    {
        [$type, $options] = $this->unresolvedChildren[$name];
        unset($this->unresolvedChildren[$name]);

        return $this->children[$name] = $this->create($name, $type, $options);
    }

    private function resolveChildren(): void
    {
        foreach ($this->unresolvedChildren as $name => [$type, $options]) {
            // PHP turns numeric string keys ("0", child names of expanded ChoiceType) into ints
            $this->children[$name] = $this->create((string) $name, $type, $options);
        }
        $this->unresolvedChildren = [];
    }
}
