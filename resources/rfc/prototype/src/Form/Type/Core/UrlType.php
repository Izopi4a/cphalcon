<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\EventListener\FixUrlProtocolListener;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;

final class UrlType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        if ($options['default_protocol']) {
            $builder->addEventSubscriber(new FixUrlProtocolListener($options['default_protocol']));
        }
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        if ($options['default_protocol']) {
            // Browsers would reject "example.com" in <input type="url">; the listener completes it instead.
            $view->vars['type'] = 'text';
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefault('default_protocol', 'http');
        $resolver->setAllowedTypes('default_protocol', ['null', 'string']);
    }

    public function getParent(): ?string
    {
        return TextType::class;
    }

    public function getBlockPrefix(): string
    {
        return 'url';
    }
}
