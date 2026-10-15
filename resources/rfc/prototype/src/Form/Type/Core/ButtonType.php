<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\Type\ButtonTypeInterface;
use Phalcon\Form\View\FormView;

/**
 * Root of the button hierarchy (<button type="button">). Has no parent on purpose: FormType's
 * buildForm() would call the data-related setters a ButtonBuilder rejects. The view vars are the
 * subset of FormType's that make sense for a leaf without data (Symfony's BaseType).
 */
class ButtonType extends AbstractType implements ButtonTypeInterface
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->setDisabled($options['disabled'])
            ->setAutoInitialize($options['auto_initialize']);
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $name      = $form->getName();
        $blockName = $options['block_name'] ?? $name;

        if (null !== $view->parent) {
            $id                = sprintf('%s_%s', $view->parent->vars['id'], $name);
            $fullName          = sprintf('%s[%s]', $view->parent->vars['full_name'], $name);
            $uniqueBlockPrefix = sprintf('%s_%s', $view->parent->vars['unique_block_prefix'], $blockName);
        } else {
            $id                = ltrim($name, '_0123456789');
            $fullName          = $name;
            $uniqueBlockPrefix = '_' . $blockName;
        }

        $blockPrefixes = [];
        for ($type = $form->getConfig()->getType(); null !== $type; $type = $type->getParent()) {
            array_unshift($blockPrefixes, $type->getBlockPrefix());
        }
        if (null !== $options['block_prefix']) {
            $blockPrefixes[] = $options['block_prefix'];
        }
        $blockPrefixes[] = $uniqueBlockPrefix;

        $view->vars = array_replace($view->vars, [
            'form'                => $view,
            'id'                  => $id,
            'name'                => $name,
            'full_name'           => $fullName,
            'disabled'            => $form->isDisabled(),
            'label'               => $options['label'],
            'attr'                => $options['attr'],
            'row_attr'            => $options['row_attr'],
            'block_prefixes'      => $blockPrefixes,
            'unique_block_prefix' => $uniqueBlockPrefix,
            'priority'            => $options['priority'],
            'multipart'           => false,
        ]);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'label'           => null,
            'attr'            => [],
            'row_attr'        => [],
            'disabled'        => false,
            'block_name'      => null,
            'block_prefix'    => null,
            'priority'        => 0,
            'auto_initialize' => false,
        ]);

        $resolver->setAllowedTypes('label', ['null', 'string', 'bool']);
        $resolver->setAllowedTypes('attr', 'array');
        $resolver->setAllowedTypes('row_attr', 'array');
        $resolver->setAllowedTypes('disabled', 'bool');
        $resolver->setAllowedTypes('block_name', ['null', 'string']);
        $resolver->setAllowedTypes('block_prefix', ['null', 'string']);
        $resolver->setAllowedTypes('priority', 'int');
    }

    public function getParent(): ?string
    {
        return null;
    }

    public function getBlockPrefix(): string
    {
        return 'button';
    }
}
