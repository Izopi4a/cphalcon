<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\Data\DataMapper;
use Phalcon\Form\EventListener\TrimListener;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\Options;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * Root of the type hierarchy: a compound form with a data mapper. Symfony's BaseType + FormType.
 */
class FormType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $isDataOptionSet = array_key_exists('data', $options);

        $builder
            ->setRequired($options['required'])
            ->setDisabled($options['disabled'])
            ->setAutoInitialize($options['auto_initialize'])
            ->setErrorBubbling($options['error_bubbling'])
            ->setEmptyData($options['empty_data'])
            ->setPropertyPath($options['property_path'])
            ->setMapped($options['mapped'])
            ->setByReference($options['by_reference'])
            ->setInheritData($options['inherit_data'])
            ->setCompound($options['compound'])
            ->setData($isDataOptionSet ? $options['data'] : null)
            ->setDataLocked($isDataOptionSet)
            ->setDataMapper($options['compound'] ? new DataMapper() : null)
            ->setMethod($options['method'])
            ->setAction($options['action'])
            ->setIsEmptyCallback($options['is_empty_callback']);

        if ($options['trim']) {
            $builder->addEventSubscriber(new TrimListener());
        }
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $name      = $form->getName();
        $blockName = $options['block_name'] ?? ($name ?: 'form');

        if (null !== $view->parent) {
            $id                = sprintf('%s_%s', $view->parent->vars['id'], $name);
            $fullName          = sprintf('%s[%s]', $view->parent->vars['full_name'], $name);
            $uniqueBlockPrefix = sprintf('%s_%s', $view->parent->vars['unique_block_prefix'], $blockName);
        } else {
            $id                = $name;
            $fullName          = $name;
            $uniqueBlockPrefix = '_' . $blockName;

            // Strip leading underscores and digits. These are allowed in
            // form names, but not in HTML4 ID attributes.
            $id = ltrim($id, '_0123456789');
        }

        $blockPrefixes = [];
        for ($type = $form->getConfig()->getType(); null !== $type; $type = $type->getParent()) {
            array_unshift($blockPrefixes, $type->getBlockPrefix());
        }
        if (null !== $options['block_prefix']) {
            $blockPrefixes[] = $options['block_prefix'];
        }
        $blockPrefixes[] = $uniqueBlockPrefix;

        $config = $form->getConfig();

        $view->vars = array_replace($view->vars, [
            'form'                => $view,
            'id'                  => $id,
            'name'                => $name,
            'full_name'           => $fullName,
            'disabled'            => $form->isDisabled(),
            'label'               => $options['label'],
            'label_attr'          => $options['label_attr'],
            'help'                => $options['help'],
            'attr'                => $options['attr'],
            'row_attr'            => $options['row_attr'],
            'block_prefixes'      => $blockPrefixes,
            'unique_block_prefix' => $uniqueBlockPrefix,
            'priority'            => $options['priority'],
            'multipart'           => false,
            'errors'              => $form->getErrors(),
            'valid'               => $form->isSubmitted() ? $form->isValid() : true,
            'value'               => $form->getViewData(),
            'data'                => $form->getNormData(),
            'required'            => $form->isRequired(),
            'compound'            => $config->getCompound(),
            'method'              => $config->getMethod(),
            'action'              => $config->getAction(),
            'submitted'           => $form->isSubmitted(),
        ]);
    }

    public function finishView(FormView $view, FormInterface $form, array $options): void
    {
        $multipart = false;
        foreach ($view->children as $child) {
            if ($child->vars['multipart'] ?? false) {
                $multipart = true;
                break;
            }
        }
        $view->vars['multipart'] = $view->vars['multipart'] || $multipart;
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        // Derive "data_class" option from passed "data" object
        $dataClass = static fn (Options $options) => isset($options['data']) && is_object($options['data']) ? $options['data']::class : null;

        // Derive "empty_data" closure from "data_class" option
        $emptyData = static function (Options $options) {
            $class = $options['data_class'];

            if (null !== $class) {
                return static fn (FormInterface $form) => $form->isEmpty() && !$form->isRequired() ? null : new $class();
            }

            return static fn (FormInterface $form) => $form->getConfig()->getCompound() ? [] : '';
        };

        // Wrap "post_max_size_message" in a closure to translate it lazily
        $errorBubbling = static fn (Options $options) => $options['compound'] && !$options['inherit_data'];

        $resolver->setDefaults([
            'data_class'                 => $dataClass,
            'empty_data'                 => $emptyData,
            'trim'                       => true,
            'required'                   => true,
            'property_path'              => null,
            'mapped'                     => true,
            'by_reference'               => true,
            'error_bubbling'             => $errorBubbling,
            'label'                      => null,
            'label_attr'                 => [],
            'help'                       => null,
            'inherit_data'               => false,
            'compound'                   => true,
            'method'                     => 'POST',
            'action'                     => '',
            'attr'                       => [],
            'row_attr'                   => [],
            'block_name'                 => null,
            'block_prefix'               => null,
            'priority'                   => 0,
            'disabled'                   => false,
            'auto_initialize'            => true,
            'allow_file_upload'          => false,
            'invalid_message'            => 'This value is not valid.',
            'invalid_message_parameters' => [],
            'is_empty_callback'          => null,
            'getter'                     => null,
            'setter'                     => null,
        ]);

        $resolver->setDefined(['data']);

        $resolver->setAllowedTypes('data_class', ['null', 'string']);
        $resolver->setAllowedTypes('property_path', ['null', 'string', PropertyPathInterface::class]);
        $resolver->setAllowedTypes('label', ['null', 'string', 'bool']);
        $resolver->setAllowedTypes('attr', 'array');
        $resolver->setAllowedTypes('row_attr', 'array');
        $resolver->setAllowedTypes('label_attr', 'array');
        $resolver->setAllowedTypes('is_empty_callback', ['null', 'callable']);
        $resolver->setAllowedTypes('getter', ['null', 'callable']);
        $resolver->setAllowedTypes('setter', ['null', 'callable']);
        $resolver->setAllowedTypes('priority', 'int');
    }

    public function getParent(): ?string
    {
        return null;
    }

    public function getBlockPrefix(): string
    {
        return 'form';
    }
}
