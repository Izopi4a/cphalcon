<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\View\FormView;

abstract class AbstractType implements TypeInterface
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

    public function getBlockPrefix(): string
    {
        // "Phalcon\Form\Type\Core\TextareaType" -> "textarea"
        $short = (new \ReflectionClass($this))->getShortName();
        if (str_ends_with($short, 'Type')) {
            $short = substr($short, 0, -4);
        }

        return strtolower(preg_replace('/(?<=\\w)([A-Z])/', '_$1', $short) ?? $short);
    }

    public function getParent(): ?string
    {
        return FormType::class;
    }
}
