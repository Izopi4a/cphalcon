<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\DateTimeImmutableToDateTimeTransformer;
use Phalcon\Form\Transformer\DateTimeToStringTransformer;
use Phalcon\Form\Transformer\DateTimeToTimestampTransformer;
use Phalcon\Form\Transformer\ReversedTransformer;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;

/**
 * Shared by DateType, DateTimeType and TimeType.
 *
 * prototype: only widget "single_text" (one <input>) is supported, so the types are never compound;
 * "format" and "input_format" are PHP date() formats, not ICU patterns.
 */
abstract class AbstractDateTimeType extends AbstractType
{
    /** Default of the "format" option (view representation). */
    abstract protected function defaultFormat(): string;

    /** Default of the "input_format" option (model representation when input = "string"). */
    abstract protected function defaultInputFormat(): string;

    /** HTML5 input type ("date", "datetime-local", "time"). */
    abstract protected function html5Type(): string;

    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $modelTimezone = $options['model_timezone'];

        $builder->addViewTransformer(new DateTimeToStringTransformer($modelTimezone, $options['view_timezone'], $options['format']));

        match ($options['input']) {
            'string'             => $builder->addModelTransformer(new ReversedTransformer(new DateTimeToStringTransformer($modelTimezone, $modelTimezone, $options['input_format']))),
            'timestamp'          => $builder->addModelTransformer(new ReversedTransformer(new DateTimeToTimestampTransformer($modelTimezone, $modelTimezone))),
            'datetime_immutable' => $builder->addModelTransformer(new DateTimeImmutableToDateTimeTransformer()),
            default              => null, // 'datetime': the norm data already is a \DateTime
        };
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $view->vars['widget'] = $options['widget'];
        $view->vars['type']   = $this->html5Type();
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'widget'         => 'single_text',
            'input'          => 'datetime',
            'format'         => $this->defaultFormat(),
            'input_format'   => $this->defaultInputFormat(),
            'model_timezone' => null,
            'view_timezone'  => null,
            'compound'       => false,
            // The view data is always a string, never the \DateTime object
            'data_class'     => null,
            'invalid_message' => 'Please enter a valid date.',
        ]);

        $resolver->setAllowedValues('widget', ['single_text']);
        $resolver->setAllowedValues('input', ['datetime', 'datetime_immutable', 'string', 'timestamp']);
        $resolver->setAllowedTypes('format', 'string');
        $resolver->setAllowedTypes('input_format', 'string');
        $resolver->setAllowedTypes('model_timezone', ['null', 'string']);
        $resolver->setAllowedTypes('view_timezone', ['null', 'string']);
    }
}
