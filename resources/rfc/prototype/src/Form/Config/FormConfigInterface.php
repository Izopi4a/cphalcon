<?php
declare(strict_types=1);

namespace Phalcon\Form\Config;

use Phalcon\Events\ManagerInterface as EventsManagerInterface;
use Phalcon\Form\Data\DataMapperInterface;
use Phalcon\Form\FormFactoryInterface;
use Phalcon\Form\RequestHandler\RequestHandlerInterface;
use Phalcon\Form\ResolvedTypeInterface;
use Phalcon\Form\Transformer\DataTransformerInterface;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * Immutable configuration of a form, frozen when the builder produces the form.
 */
interface FormConfigInterface
{
    public function getEventsManager(): EventsManagerInterface;

    public function getName(): string;

    public function getPropertyPath(): ?PropertyPathInterface;

    public function getMapped(): bool;

    public function getByReference(): bool;

    public function getInheritData(): bool;

    public function getCompound(): bool;

    public function getType(): ResolvedTypeInterface;

    /** @return list<DataTransformerInterface> */
    public function getViewTransformers(): array;

    /** @return list<DataTransformerInterface> */
    public function getModelTransformers(): array;

    public function getDataMapper(): ?DataMapperInterface;

    public function getRequired(): bool;

    public function getDisabled(): bool;

    public function getErrorBubbling(): bool;

    public function getEmptyData(): mixed;

    /** @return array<string, mixed> */
    public function getAttributes(): array;

    public function hasAttribute(string $name): bool;

    public function getAttribute(string $name, mixed $default = null): mixed;

    public function getData(): mixed;

    public function getDataClass(): ?string;

    public function getDataLocked(): bool;

    public function getFormFactory(): FormFactoryInterface;

    public function getAction(): string;

    public function getMethod(): string;

    public function getRequestHandler(): RequestHandlerInterface;

    public function getAutoInitialize(): bool;

    public function getIsEmptyCallback(): ?\Closure;

    /** @return array<string, mixed> */
    public function getOptions(): array;

    public function hasOption(string $name): bool;

    public function getOption(string $name, mixed $default = null): mixed;
}
