<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormError;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;

final class ColorType extends AbstractType
{
    private const HTML5_PATTERN = '/^#[0-9a-f]{6}$/i';

    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        if (!$options['html5']) {
            return;
        }

        $builder->addEventListener(FormEvents::PRE_SUBMIT, static function (FormEvent $event): void {
            $value = $event->getData();
            if (null === $value || '' === $value || (is_string($value) && preg_match(self::HTML5_PATTERN, $value))) {
                return;
            }

            $template   = 'This value is not a valid HTML5 color.';
            $parameters = ['{{ value }}' => is_scalar($value) ? (string) $value : get_debug_type($value)];
            $event->getForm()->addError(new FormError(strtr($template, $parameters), $template, $parameters, null, 'INVALID_COLOR_ERROR'));
        });
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefault('html5', false);
        $resolver->setAllowedTypes('html5', 'bool');
    }

    public function getParent(): ?string
    {
        return TextType::class;
    }

    public function getBlockPrefix(): string
    {
        return 'color';
    }
}
