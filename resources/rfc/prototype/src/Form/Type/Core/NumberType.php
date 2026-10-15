<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\Exception\LogicException;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\Options;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\NumberToStringTransformer;
use Phalcon\Form\Transformer\StringToFloatTransformer;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;

final class NumberType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder->addViewTransformer(new NumberToStringTransformer($options['scale'], $options['grouping']));

        if ('string' === $options['input']) {
            $builder->addModelTransformer(new StringToFloatTransformer($options['scale']));
        }
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        if ($options['html5']) {
            $view->vars['type'] = 'number';

            if (!isset($view->vars['attr']['step'])) {
                $view->vars['attr']['step'] = 'any';
            }
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'scale'           => null,
            'grouping'        => false,
            'compound'        => false,
            'input'           => 'number',
            'html5'           => false,
            'invalid_message' => 'Please enter a number.',
        ]);

        $resolver->setAllowedTypes('scale', ['null', 'int']);
        $resolver->setAllowedTypes('grouping', 'bool');
        $resolver->setAllowedTypes('html5', 'bool');
        $resolver->setAllowedValues('input', ['number', 'string']);

        $resolver->setNormalizer('grouping', static function (Options $options, bool $grouping): bool {
            if ($grouping && $options['html5']) {
                throw new LogicException('Cannot use the "grouping" option when the "html5" option is enabled.');
            }

            return $grouping;
        });
    }

    public function getBlockPrefix(): string
    {
        return 'number';
    }
}
