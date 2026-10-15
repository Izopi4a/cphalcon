<?php
declare(strict_types=1);

namespace Phalcon\Form;

use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\TypeExtensionInterface;
use Phalcon\Form\Type\TypeInterface;
use Phalcon\Form\View\FormView;

/**
 * A type with its parent chain and type extensions resolved, plus its options resolver.
 */
interface ResolvedTypeInterface
{
    public function getBlockPrefix(): string;

    public function getParent(): ?self;

    public function getInnerType(): TypeInterface;

    /** @return list<TypeExtensionInterface> */
    public function getTypeExtensions(): array;

    public function createBuilder(FormFactoryInterface $factory, string $name, array $options = []): FormBuilderInterface;

    public function createView(FormInterface $form, ?FormView $parent = null): FormView;

    public function buildForm(FormBuilderInterface $builder, array $options): void;

    public function buildView(FormView $view, FormInterface $form, array $options): void;

    public function finishView(FormView $view, FormInterface $form, array $options): void;

    public function getOptionsResolver(): OptionsResolver;
}
