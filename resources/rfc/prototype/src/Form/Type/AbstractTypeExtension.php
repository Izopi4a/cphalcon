<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\View\FormView;

abstract class AbstractTypeExtension implements TypeExtensionInterface
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
    }

    public function finishView(FormView $view, FormInterface $form, array $options): void
    {
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
    }
}
