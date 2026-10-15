<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\EventListener\ResizeFormListener;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\Options;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;

/**
 * A compound form whose children are all of the same type (entry_type) and whose number of
 * children follows the data: one child per key. This is the #17106 feature.
 *
 *   setData([a, b, c])             -> children "0", "1", "2" with property paths [0], [1], [2]
 *   allow_add                      -> submitted keys without a child get one (prototype options)
 *   allow_delete                   -> children missing from the payload are removed, the key too
 *   delete_empty                   -> blank entries are dropped (bool, or callable($entryData))
 *   keep_as_list                   -> keys are renumbered 0..n-1 after submit
 *   prototype / prototype_name     -> an extra, unmapped "__name__" entry in the view for JS
 */
class CollectionType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $resizePrototypeOptions = null;

        if ($options['allow_add'] && $options['prototype']) {
            $resizePrototypeOptions = array_replace($options['entry_options'], $options['prototype_options']);
            $prototypeOptions       = array_replace([
                'required' => $options['required'],
                'label'    => $options['prototype_name'] . 'label__',
            ], $resizePrototypeOptions);

            if (null !== $options['prototype_data']) {
                $prototypeOptions['data'] = $options['prototype_data'];
            }

            $prototype = $builder->create($options['prototype_name'], $options['entry_type'], $prototypeOptions);
            $builder->setAttribute('prototype', $prototype->getForm());
        }

        $builder->addEventSubscriber(new ResizeFormListener(
            $options['entry_type'],
            $options['entry_options'],
            $options['allow_add'],
            $options['allow_delete'],
            $options['delete_empty'],
            $resizePrototypeOptions,
            $options['keep_as_list'],
        ));
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        $view->vars = array_replace($view->vars, [
            'allow_add'    => $options['allow_add'],
            'allow_delete' => $options['allow_delete'],
        ]);

        if ($form->getConfig()->hasAttribute('prototype')) {
            /** @var FormInterface $prototype */
            $prototype = $form->getConfig()->getAttribute('prototype');
            // The prototype must render as a child of the collection ("ticket[messages][__name__]").
            $view->vars['prototype'] = $prototype->setParent($form)->createView($view);
        }
    }

    public function finishView(FormView $view, FormInterface $form, array $options): void
    {
        // "collection_entry" goes in front of the entry type's own prefixes:
        // [form, text, _ticket_tags_entry] -> [form, collection_entry, text, _ticket_tags_entry]
        $prefixOffset = -2;
        // check if the entry type also defines a block prefix
        /** @var FormInterface $entry */
        foreach ($form as $entry) {
            if ($entry->getConfig()->getOption('block_prefix')) {
                --$prefixOffset;
            }

            break;
        }

        foreach ($view as $entryView) {
            array_splice($entryView->vars['block_prefixes'], $prefixOffset, 0, 'collection_entry');
        }

        /** @var FormInterface|null $prototype */
        if ($prototype = $form->getConfig()->getAttribute('prototype')) {
            if ($view->vars['prototype']->vars['multipart']) {
                $view->vars['multipart'] = true;
            }

            if ($prefixOffset > -3 && $prototype->getConfig()->getOption('block_prefix')) {
                --$prefixOffset;
            }

            array_splice($view->vars['prototype']->vars['block_prefixes'], $prefixOffset, 0, 'collection_entry');
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $entryOptionsNormalizer = static function (Options $options, $value) {
            $value['block_name'] = 'entry';

            return $value;
        };

        $resolver->setDefaults([
            'allow_add'         => false,
            'allow_delete'      => false,
            'prototype'         => true,
            'prototype_data'    => null,
            'prototype_name'    => '__name__',
            'entry_type'        => TextType::class,
            'entry_options'     => [],
            'prototype_options' => [],
            'delete_empty'      => false,
            'invalid_message'   => 'The collection is invalid.',
            'keep_as_list'      => false,
        ]);

        $resolver->setNormalizer('entry_options', $entryOptionsNormalizer);

        $resolver->setAllowedTypes('allow_add', 'bool');
        $resolver->setAllowedTypes('allow_delete', 'bool');
        $resolver->setAllowedTypes('prototype', 'bool');
        $resolver->setAllowedTypes('prototype_name', 'string');
        $resolver->setAllowedTypes('entry_type', 'string');
        $resolver->setAllowedTypes('entry_options', 'array');
        $resolver->setAllowedTypes('delete_empty', ['bool', 'callable']);
        $resolver->setAllowedTypes('prototype_options', 'array');
        $resolver->setAllowedTypes('keep_as_list', 'bool');
    }

    public function getBlockPrefix(): string
    {
        return 'collection';
    }
}
