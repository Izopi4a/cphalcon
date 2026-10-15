<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\BooleanToStringTransformer;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;

class CheckboxType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        // Unlike other types the default data is a Boolean, not null: setData(null) is not
        // acceptable for checkboxes. Not done through the "data" option since that locks the data.
        $builder->setData($options['data'] ?? false);
        $builder->addViewTransformer(new BooleanToStringTransformer($options['value'], $options['false_values']));
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $view->vars = array_replace($view->vars, [
            'value'   => $options['value'],
            'checked' => null !== $form->getViewData(),
        ]);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'value'             => '1',
            // null submitted stays null; the view transformer turns it into false
            'empty_data'        => static fn (FormInterface $form, mixed $viewData): mixed => $viewData,
            'compound'          => false,
            'false_values'      => [null],
            'invalid_message'   => 'The checkbox has an invalid value.',
            'is_empty_callback' => static fn (mixed $modelData): bool => false === $modelData,
        ]);

        $resolver->setAllowedTypes('false_values', 'array');
    }

    public function getBlockPrefix(): string
    {
        return 'checkbox';
    }
}
