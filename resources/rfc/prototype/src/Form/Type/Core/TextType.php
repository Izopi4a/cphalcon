<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\DataTransformerInterface;
use Phalcon\Form\Type\AbstractType;

class TextType extends AbstractType implements DataTransformerInterface
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        // When empty_data is explicitly set to an empty string, a string should always be returned
        // when NULL was submitted; otherwise "" reverse-transforms to null (closes #17338 by default).
        if ('' === $options['empty_data']) {
            $builder->addViewTransformer($this);
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefault('compound', false);
    }

    public function getBlockPrefix(): string
    {
        return 'text';
    }

    public function transform(mixed $value): mixed
    {
        return null === $value ? '' : (string) $value;
    }

    public function reverseTransform(mixed $value): mixed
    {
        return null !== $value ? $value : '';
    }
}
