<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Config\FormConfigInterface;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\Exception\AlreadySubmittedException;
use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\Exception\OutOfBoundsException;
use Phalcon\Form\Exception\RuntimeException;
use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\Transformer\TransformationFailedException;
use Phalcon\Form\Type\Core\TextType;
use Phalcon\Form\Util\FormUtil;
use Phalcon\Form\Util\InheritDataAwareIterator;
use Phalcon\Form\Util\OrderedHashMap;
use Phalcon\Form\View\FormView;
use Phalcon\Support\PropertyAccess\PropertyPath;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * Form tree node. Life cycle (same as Symfony Forms):
 *
 *   setData(model):  preSetData -> model transformers -> view transformers -> mapper (data -> children) -> postSetData
 *   submit(input):   preSubmit -> children submit -> empty_data -> mapper (children -> data)
 *                    -> view transformers (reverse) -> submit -> model transformers (reverse) -> postSubmit
 */
class Form implements FormInterface, ClearableErrorsInterface
{
    private ?FormInterface $parent = null;
    /** @var OrderedHashMap<FormInterface> */
    private OrderedHashMap $children;
    /** @var list<FormError> */
    private array $errors = [];
    private bool $submitted = false;
    private ?ClickableInterface $clickedButton = null;
    private mixed $modelData = null;
    private mixed $normData = null;
    private mixed $viewData = null;
    /** @var array<string, mixed> */
    private array $extraData = [];
    private ?TransformationFailedException $transformationFailure = null;
    private bool $defaultDataSet = false;
    private bool $lockSetData = false;
    private ?PropertyPathInterface $propertyPath = null;

    public function __construct(private readonly FormConfigInterface $config)
    {
        if ($config->getCompound() && null === $config->getDataMapper()) {
            throw new LogicException('Compound forms need a data mapper.');
        }

        // Forms that inherit their parent's data never set data themselves.
        if ($config->getInheritData()) {
            $this->defaultDataSet = true;
        }

        $this->children = new OrderedHashMap();
    }

    public function __clone(): void
    {
        $this->children = clone $this->children;
        foreach ($this->children as $key => $child) {
            $this->children[$key] = clone $child;
        }
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
        if (null !== $this->propertyPath) {
            return $this->propertyPath;
        }
        if (null !== $this->config->getPropertyPath()) {
            return $this->propertyPath = $this->config->getPropertyPath();
        }
        if ('' === $this->getName()) {
            return null;
        }

        $parent = $this->parent;
        while (null !== $parent && $parent->getConfig()->getInheritData()) {
            $parent = $parent->getParent();
        }

        if (null !== $parent && null === $parent->getConfig()->getDataClass()) {
            return $this->propertyPath = new PropertyPath('[' . $this->getName() . ']');
        }

        return $this->propertyPath = new PropertyPath($this->getName());
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

    public function setParent(?FormInterface $parent): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('You cannot set the parent of a submitted form.');
        }
        if (null !== $parent && '' === $this->getName()) {
            throw new LogicException('A form with an empty name cannot have a parent form.');
        }

        $this->parent       = $parent;
        $this->propertyPath = null;

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

    public function setData(mixed $modelData): static
    {
        // If the form is submitted while disabled, it is set to submitted, but the data is not
        // changed. In such cases (i.e. when the form is not initialized yet) don't
        // abort this method.
        if ($this->submitted && $this->defaultDataSet) {
            throw new AlreadySubmittedException('You cannot change the data of a submitted form.');
        }
        if ($this->config->getInheritData()) {
            throw new RuntimeException('You cannot change the data of a form inheriting its parent data.');
        }
        // Don't allow modifications of the configured data if the data is locked
        if ($this->config->getDataLocked() && $modelData !== $this->config->getData()) {
            return $this;
        }
        if (is_object($modelData) && !$this->config->getByReference()) {
            $modelData = clone $modelData;
        }
        if ($this->lockSetData) {
            throw new RuntimeException('A cycle was detected. Listeners to the PRE_SET_DATA event must not call setData(). You should call setData() on the FormEvent object instead.');
        }

        $this->lockSetData = true;
        $eventsManager     = $this->config->getEventsManager();

        try {
            $event = new FormEvent($this, $modelData);
            $eventsManager->fire(FormEvents::PRE_SET_DATA, $this, $event);
            $modelData = $event->getData();

            // Treat data as strings unless a transformer exists
            if (is_scalar($modelData) && [] === $this->config->getViewTransformers() && [] === $this->config->getModelTransformers()) {
                $modelData = (string) $modelData;
            }

            // Synchronize representations - must not change the content!
            $normData = $this->modelToNorm($modelData);
            $viewData = $this->normToView($normData);

            // Validate if view data matches data class (unless empty)
            if (!FormUtil::isEmpty($viewData)) {
                $dataClass = $this->config->getDataClass();

                if (null !== $dataClass && !$viewData instanceof $dataClass) {
                    throw new LogicException(sprintf(
                        'The form\'s view data is expected to be an instance of class "%s", but is %s. You can avoid this error by setting the "data_class" option to null or by adding a view transformer that transforms %s to an instance of "%s".',
                        $dataClass,
                        is_object($viewData) ? 'an instance of class ' . $viewData::class : 'a(n) ' . get_debug_type($viewData),
                        is_object($viewData) ? 'an instance of class ' . $viewData::class : 'a(n) ' . get_debug_type($viewData),
                        $dataClass
                    ));
                }
            }

            $this->modelData      = $modelData;
            $this->normData       = $normData;
            $this->viewData       = $viewData;
            $this->defaultDataSet = true;
        } finally {
            $this->lockSetData = false;
        }

        // Compound forms don't need to invoke this method if they don't have children
        if (count($this->children) > 0) {
            // Update child forms from the data (unless their config data is locked)
            $this->config->getDataMapper()->mapDataToForms(
                $viewData,
                new \RecursiveIteratorIterator(new InheritDataAwareIterator($this->children))
            );
        }

        $eventsManager->fire(FormEvents::POST_SET_DATA, $this, new FormEvent($this, $modelData, false));

        return $this;
    }

    public function getData(): mixed
    {
        if ($this->config->getInheritData()) {
            if (null === $this->parent) {
                throw new RuntimeException('The form is configured to inherit its parent\'s data, but does not have a parent.');
            }

            return $this->parent->getData();
        }

        if (!$this->defaultDataSet) {
            $this->lazyInitialize();
        }

        return $this->modelData;
    }

    public function getNormData(): mixed
    {
        if ($this->config->getInheritData()) {
            if (null === $this->parent) {
                throw new RuntimeException('The form is configured to inherit its parent\'s data, but does not have a parent.');
            }

            return $this->parent->getNormData();
        }

        if (!$this->defaultDataSet) {
            $this->lazyInitialize();
        }

        return $this->normData;
    }

    public function getViewData(): mixed
    {
        if ($this->config->getInheritData()) {
            if (null === $this->parent) {
                throw new RuntimeException('The form is configured to inherit its parent\'s data, but does not have a parent.');
            }

            return $this->parent->getViewData();
        }

        if (!$this->defaultDataSet) {
            $this->lazyInitialize();
        }

        return $this->viewData;
    }

    public function getExtraData(): array
    {
        return $this->extraData;
    }

    public function initialize(): static
    {
        if (null !== $this->parent) {
            throw new RuntimeException('Only root forms should be initialized.');
        }

        // Guarantee that the *_SET_DATA events have been triggered once the
        // form is initialized. This makes sure that dynamically added or
        // removed fields are already visible after initialization.
        if (!$this->defaultDataSet) {
            $this->setData($this->config->getData());
        }

        return $this;
    }

    public function handleRequest(mixed $request = null): static
    {
        $this->config->getRequestHandler()->handleRequest($this, $request);

        return $this;
    }

    public function submit(mixed $submittedData, bool $clearMissing = true): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('A form can only be submitted once.');
        }

        // Initialize errors in the very beginning so we're sure
        // they are collectable during submission only
        $this->errors = [];

        // Obviously, a disabled form should not change its data upon submission.
        if ($this->isDisabled()) {
            $this->submitted = true;

            return $this;
        }

        // The data must be initialized if it was not initialized yet.
        // This is necessary to guarantee that the *_SET_DATA listeners
        // are always invoked before submit() takes place.
        if (!$this->defaultDataSet) {
            $this->setData($this->config->getData());
        }

        // Treat false as NULL to support binding false to checkboxes.
        // Don't convert NULL to a string here in order to determine later
        // whether an empty value has been submitted or whether no value has
        // been submitted at all. This is important for processing checkboxes
        // and radio buttons with empty values.
        if (false === $submittedData) {
            $submittedData = null;
        } elseif (is_scalar($submittedData)) {
            $submittedData = (string) $submittedData;
        } elseif ($this->config->getRequestHandler()->isFileUpload($submittedData)) {
            if (!$this->config->getOption('allow_file_upload')) {
                $submittedData                = null;
                $this->transformationFailure = new TransformationFailedException('Submitted data was expected to be text or number, file upload given.');
            }
        } elseif (is_array($submittedData) && !$this->config->getCompound() && !$this->config->getOption('multiple', false)) {
            $submittedData               = null;
            $this->transformationFailure = new TransformationFailedException('Submitted data was expected to be text or number, array given.');
        }

        $eventsManager = $this->config->getEventsManager();
        $modelData     = null;
        $normData      = null;
        $viewData      = null;

        try {
            if (null !== $this->transformationFailure) {
                throw $this->transformationFailure;
            }

            // Hook to change content of the data submitted by the browser
            $event = new FormEvent($this, $submittedData);
            $eventsManager->fire(FormEvents::PRE_SUBMIT, $this, $event);
            $submittedData = $event->getData();

            // Check whether the form is compound.
            // This check is preferable over checking the number of children,
            // since forms without children may also be compound.
            // (think of empty collection forms)
            if ($this->config->getCompound()) {
                if (null === $submittedData) {
                    $submittedData = [];
                }
                if (!is_array($submittedData)) {
                    throw new TransformationFailedException('Compound forms expect an array or NULL on submission.');
                }

                foreach ($this->children as $name => $child) {
                    $isSubmitted = array_key_exists($name, $submittedData);

                    if ($isSubmitted || $clearMissing) {
                        $child->submit($isSubmitted ? $submittedData[$name] : null, $clearMissing);
                        unset($submittedData[$name]);

                        if (null !== $this->clickedButton) {
                            continue;
                        }
                        if ($child instanceof ClickableInterface && $child->isClicked()) {
                            $this->clickedButton = $child;
                            continue;
                        }
                        if (method_exists($child, 'getClickedButton') && null !== $child->getClickedButton()) {
                            $this->clickedButton = $child->getClickedButton();
                        }
                    }
                }

                $this->extraData = $submittedData;
            }

            // Forms that inherit their parents' data also are not processed,
            // because then it would be too difficult to merge the changes in
            // the child and the parent form. Instead, the parent form also takes
            // changes in the grandchildren (i.e. children of the form that inherits
            // its parent's data) into account.
            // (see InheritDataAwareIterator below)
            if (!$this->config->getInheritData()) {
                // If the form is compound, the view data is merged with the data
                // of the children using the data mapper.
                // If the form is not compound, the view data is assigned to the submitted data.
                $viewData = $this->config->getCompound() ? $this->viewData : $submittedData;

                if (FormUtil::isEmpty($viewData)) {
                    $emptyData = $this->config->getEmptyData();

                    if ($emptyData instanceof \Closure) {
                        $emptyData = $emptyData($this, $viewData);
                    }

                    $viewData = $emptyData;
                }

                // Merge form data from children into existing view data
                // It is not necessary to invoke this method if the form has no children,
                // even if it is compound.
                if (count($this->children) > 0) {
                    // Use InheritDataAwareIterator to process children of
                    // descendants that inherit this form's data.
                    // These descendants will not be submitted normally (see the check
                    // for $this->config->getInheritData() above)
                    $this->config->getDataMapper()->mapFormsToData(
                        new \RecursiveIteratorIterator(new InheritDataAwareIterator($this->children)),
                        $viewData
                    );
                }

                // Normalize data to unified representation
                $normData = $this->viewToNorm($viewData);

                // Hook to change content of the data in the normalized
                // representation
                $event = new FormEvent($this, $normData);
                $eventsManager->fire(FormEvents::SUBMIT, $this, $event);
                $normData = $event->getData();

                // Synchronize representations - must not change the content!
                $modelData = $this->normToModel($normData);
                $viewData  = $this->normToView($normData);
            }
        } catch (TransformationFailedException $e) {
            $this->transformationFailure = $e;

            // If $viewData was not yet set, set it to $submittedData so that
            // the erroneous data is accessible on the form.
            // Forms that inherit data never set any data, because the getters
            // forward to the parent form's getters anyway.
            if (null === $viewData && !$this->config->getInheritData()) {
                $viewData = $submittedData;
            }
        }

        $this->submitted = true;
        $this->modelData = $modelData;
        $this->normData  = $normData;
        $this->viewData  = $viewData;

        $eventsManager->fire(FormEvents::POST_SUBMIT, $this, new FormEvent($this, $viewData, false));

        return $this;
    }

    public function addError(FormError $error): static
    {
        if (null === $error->getOrigin()) {
            $error->setOrigin($this);
        }

        if (null !== $this->parent && $this->config->getErrorBubbling()) {
            $this->parent->addError($error);
        } else {
            $this->errors[] = $error;
        }

        return $this;
    }

    public function isSubmitted(): bool
    {
        return $this->submitted;
    }

    public function isSynchronized(): bool
    {
        return null === $this->transformationFailure;
    }

    public function getTransformationFailure(): ?TransformationFailedException
    {
        return $this->transformationFailure;
    }

    public function isEmpty(): bool
    {
        foreach ($this->children as $child) {
            if (!$child->isEmpty()) {
                return false;
            }
        }

        if (null !== $this->config->getIsEmptyCallback()) {
            return ($this->config->getIsEmptyCallback())($this->modelData);
        }

        return FormUtil::isEmpty($this->modelData)
            || false === $this->modelData
            // arrays, countables
            || ((is_array($this->modelData) || $this->modelData instanceof \Countable) && 0 === count($this->modelData));
    }

    public function isValid(): bool
    {
        if (!$this->submitted) {
            throw new LogicException('Cannot check if an unsubmitted form is valid. Call Form::isSubmitted() and ensure that it\'s true before calling Form::isValid().');
        }

        if ($this->isDisabled()) {
            return true;
        }

        return 0 === count($this->getErrors(true));
    }

    public function getClickedButton(): ?ClickableInterface
    {
        if (null !== $this->clickedButton) {
            return $this->clickedButton;
        }

        return null !== $this->parent && method_exists($this->parent, 'getClickedButton') ? $this->parent->getClickedButton() : null;
    }

    public function getErrors(bool $deep = false): array
    {
        $errors = $this->errors;

        if ($deep) {
            foreach ($this->children as $child) {
                if ($child->isSubmitted() && $child->isValid()) {
                    continue;
                }
                foreach ($child->getErrors(true) as $error) {
                    $errors[] = $error;
                }
            }
        }

        return $errors;
    }

    public function clearErrors(bool $deep = false): static
    {
        $this->errors = [];

        if ($deep) {
            foreach ($this->children as $child) {
                if ($child instanceof ClearableErrorsInterface) {
                    $child->clearErrors(true);
                }
            }
        }

        return $this;
    }

    public function all(): array
    {
        return $this->children->toArray();
    }

    public function add(FormInterface|string $child, ?string $type = null, array $options = []): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('You cannot add children to a submitted form.');
        }
        if (!$this->config->getCompound()) {
            throw new LogicException('You cannot add children to a simple form. Maybe you should set the option "compound" to true?');
        }

        if (!$child instanceof FormInterface) {
            if ('' === $child) {
                throw new UnexpectedTypeException($child, 'non-empty string');
            }
            $options += ['auto_initialize' => false];
            $child = $this->config->getFormFactory()->createNamed($child, $type ?? TextType::class, null, $options);
        } elseif ($child->getConfig()->getAutoInitialize()) {
            throw new RuntimeException(sprintf('Automatic initialization is only supported on root forms. You should set the "auto_initialize" option to false on the field "%s".', $child->getName()));
        }

        $this->children[$child->getName()] = $child;
        $child->setParent($this);

        // If setData() is currently being called, there is no need to call
        // mapDataToForms() here, as mapDataToForms() is called at the end
        // of setData() anyway. Not doing this check leads to an endless
        // recursion when initializing the form lazily and an event listener
        // (such as ResizeFormListener) adds fields depending on the data:
        if (!$this->lockSetData && $this->defaultDataSet && !$this->config->getInheritData()) {
            $viewData = $this->getViewData();
            $iterator = new InheritDataAwareIterator(new \ArrayIterator([$child->getName() => $child]));
            $this->config->getDataMapper()->mapDataToForms($viewData, new \RecursiveIteratorIterator($iterator));
        }

        return $this;
    }

    public function remove(string $name): static
    {
        if ($this->submitted) {
            throw new AlreadySubmittedException('You cannot remove children from a submitted form.');
        }

        if (isset($this->children[$name])) {
            if (!$this->children[$name]->isSubmitted()) {
                $this->children[$name]->setParent(null);
            }
            unset($this->children[$name]);
        }

        return $this;
    }

    public function has(string $name): bool
    {
        return isset($this->children[$name]);
    }

    public function get(string $name): FormInterface
    {
        if (isset($this->children[$name])) {
            return $this->children[$name];
        }

        throw new OutOfBoundsException(sprintf('Child "%s" does not exist.', $name));
    }

    public function offsetExists(mixed $offset): bool
    {
        return $this->has((string) $offset);
    }

    public function offsetGet(mixed $offset): FormInterface
    {
        return $this->get((string) $offset);
    }

    public function offsetSet(mixed $offset, mixed $value): void
    {
        $this->add($value);
    }

    public function offsetUnset(mixed $offset): void
    {
        $this->remove((string) $offset);
    }

    public function getIterator(): \Traversable
    {
        return $this->children->getIterator();
    }

    public function count(): int
    {
        return count($this->children);
    }

    public function createView(?FormView $parent = null): FormView
    {
        if (null === $parent && null !== $this->parent) {
            $parent = $this->parent->createView();
        }

        $type    = $this->config->getType();
        $options = $this->config->getOptions();

        // The methods createView(), buildView() and finishView() are called
        // explicitly here in order to be able to override either of them
        // in a custom resolved form type.
        $view = $type->createView($this, $parent);

        $type->buildView($view, $this, $options);

        foreach ($this->children as $name => $child) {
            $view->children[$name] = $child->createView($view);
        }

        $this->sort($view->children);

        $type->finishView($view, $this, $options);

        return $view;
    }

    /** Stable sort of child views by their "priority" var, highest first. */
    private function sort(array &$children): void
    {
        $c = [];
        $i = 0;
        $needsSorting = false;
        foreach ($children as $name => $child) {
            $c[$name] = ['p' => $child->vars['priority'] ?? 0, 'i' => $i++];
            if (0 !== $c[$name]['p']) {
                $needsSorting = true;
            }
        }
        if (!$needsSorting) {
            return;
        }
        uksort($children, static fn ($a, $b) => [$c[$b]['p'], $c[$a]['i']] <=> [$c[$a]['p'], $c[$b]['i']]);
    }

    private function lazyInitialize(): void
    {
        if ($this->lockSetData) {
            throw new RuntimeException('A cycle was detected. Listeners to the PRE_SET_DATA event must not call getData(), getNormData() or getViewData(). You should call getData() on the FormEvent object instead.');
        }
        $this->setData($this->config->getData());
    }

    /** Model -> norm: model transformers, forward, in order. */
    private function modelToNorm(mixed $value): mixed
    {
        try {
            foreach ($this->config->getModelTransformers() as $transformer) {
                $value = $transformer->transform($value);
            }
        } catch (TransformationFailedException $e) {
            throw new TransformationFailedException(sprintf('Unable to transform data for property path "%s": %s', $this->getPropertyPath(), $e->getMessage()), $e->getCode(), $e, $e->getInvalidMessage(), $e->getInvalidMessageParameters());
        }

        return $value;
    }

    /** Norm -> model: model transformers, reverse, in reverse order. */
    private function normToModel(mixed $value): mixed
    {
        try {
            $transformers = $this->config->getModelTransformers();
            for ($i = count($transformers) - 1; $i >= 0; --$i) {
                $value = $transformers[$i]->reverseTransform($value);
            }
        } catch (TransformationFailedException $e) {
            throw new TransformationFailedException(sprintf('Unable to reverse value for property path "%s": %s', $this->getPropertyPath(), $e->getMessage()), $e->getCode(), $e, $e->getInvalidMessage(), $e->getInvalidMessageParameters());
        }

        return $value;
    }

    /** Norm -> view: view transformers, forward. Without transformers scalars become strings. */
    private function normToView(mixed $value): mixed
    {
        // Scalar values should be converted to strings to
        // facilitate differentiation between empty ("") and zero (0).
        // Only do this for simple forms, as the resulting value in
        // compound forms is passed to the data mapper and thus should
        // not be converted to a string before.
        if ([] === $this->config->getViewTransformers() && !$this->config->getCompound()) {
            return null === $value || is_scalar($value) ? (string) $value : $value;
        }

        try {
            foreach ($this->config->getViewTransformers() as $transformer) {
                $value = $transformer->transform($value);
            }
        } catch (TransformationFailedException $e) {
            throw new TransformationFailedException(sprintf('Unable to transform value for property path "%s": %s', $this->getPropertyPath(), $e->getMessage()), $e->getCode(), $e, $e->getInvalidMessage(), $e->getInvalidMessageParameters());
        }

        return $value;
    }

    /** View -> norm: view transformers, reverse, in reverse order. Without transformers "" becomes null. */
    private function viewToNorm(mixed $value): mixed
    {
        if ([] === $this->config->getViewTransformers()) {
            return '' === $value ? null : $value;
        }

        try {
            $transformers = $this->config->getViewTransformers();
            for ($i = count($transformers) - 1; $i >= 0; --$i) {
                $value = $transformers[$i]->reverseTransform($value);
            }
        } catch (TransformationFailedException $e) {
            throw new TransformationFailedException(sprintf('Unable to reverse value for property path "%s": %s', $this->getPropertyPath(), $e->getMessage()), $e->getCode(), $e, $e->getInvalidMessage(), $e->getInvalidMessageParameters());
        }

        return $value;
    }
}
