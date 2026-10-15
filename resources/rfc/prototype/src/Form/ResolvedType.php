<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Exception\InvalidArgumentException;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\TypeExtensionInterface;
use Phalcon\Form\Type\TypeInterface;
use Phalcon\Form\View\FormView;

class ResolvedType implements ResolvedTypeInterface
{
    private ?OptionsResolver $optionsResolver = null;

    /** @param list<TypeExtensionInterface> $typeExtensions */
    public function __construct(
        private readonly TypeInterface $innerType,
        private readonly array $typeExtensions = [],
        private readonly ?ResolvedTypeInterface $parent = null,
    ) {
        foreach ($typeExtensions as $extension) {
            if (!$extension instanceof TypeExtensionInterface) {
                throw new InvalidArgumentException(sprintf('Type extensions must implement "%s".', TypeExtensionInterface::class));
            }
        }
    }

    public function getBlockPrefix(): string
    {
        return $this->innerType->getBlockPrefix();
    }

    public function getParent(): ?ResolvedTypeInterface
    {
        return $this->parent;
    }

    public function getInnerType(): TypeInterface
    {
        return $this->innerType;
    }

    public function getTypeExtensions(): array
    {
        return $this->typeExtensions;
    }

    public function createBuilder(FormFactoryInterface $factory, string $name, array $options = []): FormBuilderInterface
    {
        try {
            $options = $this->getOptionsResolver()->resolve($options);
        } catch (\Phalcon\Form\Exception\ExceptionInterface $e) {
            throw new $e(sprintf('An error has occurred resolving the options of the form "%s": ', get_debug_type($this->innerType)) . $e->getMessage(), 0, $e);
        }

        $builder = new FormBuilder($name, $options['data_class'] ?? null, null, $factory, $options);
        $builder->setType($this);

        $this->buildForm($builder, $options);

        return $builder;
    }

    public function createView(FormInterface $form, ?FormView $parent = null): FormView
    {
        return new FormView($parent);
    }

    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $this->parent?->buildForm($builder, $options);
        $this->innerType->buildForm($builder, $options);
        foreach ($this->typeExtensions as $extension) {
            $extension->buildForm($builder, $options);
        }
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $this->parent?->buildView($view, $form, $options);
        $this->innerType->buildView($view, $form, $options);
        foreach ($this->typeExtensions as $extension) {
            $extension->buildView($view, $form, $options);
        }
    }

    public function finishView(FormView $view, FormInterface $form, array $options): void
    {
        $this->parent?->finishView($view, $form, $options);
        $this->innerType->finishView($view, $form, $options);
        foreach ($this->typeExtensions as $extension) {
            $extension->finishView($view, $form, $options);
        }
    }

    public function getOptionsResolver(): OptionsResolver
    {
        if (null === $this->optionsResolver) {
            $this->optionsResolver = null !== $this->parent
                ? clone $this->parent->getOptionsResolver()
                : new OptionsResolver();

            $this->innerType->configureOptions($this->optionsResolver);
            foreach ($this->typeExtensions as $extension) {
                $extension->configureOptions($this->optionsResolver);
            }
        }

        return $this->optionsResolver;
    }
}
