<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\View\FormView;

interface TypeInterface
{
    /** Configures the builder (children, transformers, listeners, config flags). */
    public function buildForm(FormBuilderInterface $builder, array $options): void;

    /** Sets view vars; runs top-down, before child views exist. */
    public function buildView(FormView $view, FormInterface $form, array $options): void;

    /** Runs bottom-up, after child views exist. */
    public function finishView(FormView $view, FormInterface $form, array $options): void;

    public function configureOptions(OptionsResolver $resolver): void;

    /** Short name used for theme block lookup, e.g. "text". */
    public function getBlockPrefix(): string;

    /** FQCN of the parent type, or null for a root type. */
    public function getParent(): ?string;
}
