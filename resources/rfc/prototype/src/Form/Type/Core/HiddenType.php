<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;

final class HiddenType extends AbstractType
{
    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            // hidden fields cannot have a required attribute
            'required'        => false,
            // Pass errors to the parent
            'error_bubbling'  => true,
            'compound'        => false,
            'invalid_message' => 'The hidden field is invalid.',
        ]);
    }

    public function getBlockPrefix(): string
    {
        return 'hidden';
    }
}
