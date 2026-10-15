<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\IntegerToStringTransformer;
use Phalcon\Form\Type\AbstractType;

final class IntegerType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder->addViewTransformer(new IntegerToStringTransformer($options['grouping']));
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        // Like Symfony: no "scale" (always 0) and no "html5"; "rounding_mode" dropped (non-Intl, decimals rejected).
        $resolver->setDefaults([
            'grouping'        => false,
            'compound'        => false,
            'invalid_message' => 'Please enter an integer.',
        ]);
        $resolver->setAllowedTypes('grouping', 'bool');
    }

    public function getBlockPrefix(): string
    {
        return 'integer';
    }
}
