<?php
declare(strict_types=1);

namespace Phalcon\Form\Config;

use Phalcon\Form\Data\DataMapperInterface;
use Phalcon\Form\Event\EventSubscriberInterface;
use Phalcon\Form\FormFactoryInterface;
use Phalcon\Form\RequestHandler\RequestHandlerInterface;
use Phalcon\Form\ResolvedTypeInterface;
use Phalcon\Form\Transformer\DataTransformerInterface;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * Mutable configuration, used while a type builds the form. Every setter throws once
 * getFormConfig() has frozen the configuration.
 */
interface FormConfigBuilderInterface extends FormConfigInterface
{
    /** @param callable(\Phalcon\Form\Event\FormEvent): void $listener */
    public function addEventListener(string $eventName, callable $listener, int $priority = 100): static;

    public function addEventSubscriber(EventSubscriberInterface $subscriber): static;

    public function addViewTransformer(DataTransformerInterface $transformer, bool $forcePrepend = false): static;

    public function resetViewTransformers(): static;

    public function addModelTransformer(DataTransformerInterface $transformer, bool $forceAppend = false): static;

    public function resetModelTransformers(): static;

    public function setAttribute(string $name, mixed $value): static;

    public function setAttributes(array $attributes): static;

    public function setDataMapper(?DataMapperInterface $dataMapper): static;

    public function setDisabled(bool $disabled): static;

    public function setEmptyData(mixed $emptyData): static;

    public function setErrorBubbling(bool $errorBubbling): static;

    public function setRequired(bool $required): static;

    public function setPropertyPath(PropertyPathInterface|string|null $propertyPath): static;

    public function setMapped(bool $mapped): static;

    public function setByReference(bool $byReference): static;

    public function setInheritData(bool $inheritData): static;

    public function setCompound(bool $compound): static;

    public function setType(ResolvedTypeInterface $type): static;

    public function setData(mixed $data): static;

    public function setDataLocked(bool $locked): static;

    public function setFormFactory(FormFactoryInterface $formFactory): static;

    public function setAction(string $action): static;

    public function setMethod(string $method): static;

    public function setRequestHandler(RequestHandlerInterface $requestHandler): static;

    public function setAutoInitialize(bool $initialize): static;

    public function setIsEmptyCallback(?\Closure $isEmptyCallback): static;

    /** Returns a frozen copy of this configuration. */
    public function getFormConfig(): FormConfigInterface;
}
