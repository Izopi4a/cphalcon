<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\ChoiceList\ArrayChoiceList;
use Phalcon\Form\ChoiceList\ChoiceListInterface;
use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\Options;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\ChoicesToValuesTransformer;
use Phalcon\Form\Transformer\ChoiceToValueTransformer;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;

/**
 * <select> (single or multiple). Choices are given as label => choice.
 *
 * prototype: collapsed only ("expanded" must stay false), no choice loaders, groups or
 * MergeCollectionListener (a multiple submit replaces the model array).
 */
final class ChoiceType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $choiceList = new ArrayChoiceList($options['choices'], $options['choice_value']);
        $builder->setAttribute('choice_list', $choiceList);

        if ($options['multiple']) {
            $builder->addViewTransformer(new ChoicesToValuesTransformer($choiceList));
        } else {
            $builder->addViewTransformer(new ChoiceToValueTransformer($choiceList));
        }
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        /** @var ChoiceListInterface $choiceList */
        $choiceList = $form->getConfig()->getAttribute('choice_list');
        $choices    = $this->createChoiceViews($choiceList, $options);
        $preferred  = $this->filterPreferred($choices, $options['preferred_choices']);

        $view->vars = array_replace($view->vars, [
            'multiple'          => $options['multiple'],
            'expanded'          => false,
            'preferred_choices' => $preferred,
            'choices'           => $choices,
            'placeholder'       => null,
            'placeholder_attr'  => [],
        ]);

        // Optimised per form: no type check inside the closure that templates call per option.
        $view->vars['is_selected'] = $options['multiple']
            ? static fn (string $choice, array $values): bool => in_array($choice, $values, true)
            : static fn (string $choice, mixed $value): bool => $choice === $value;

        // Only add the placeholder when the list itself has no "" option
        $view->vars['placeholder_in_choices'] = [] !== array_filter($choices, static fn (ChoiceView $c): bool => '' === $c->value);
        if (null !== $options['placeholder'] && !$view->vars['placeholder_in_choices']) {
            $view->vars['placeholder']      = $options['placeholder'];
            $view->vars['placeholder_attr'] = $options['placeholder_attr'];
        }

        if ($options['multiple']) {
            // Otherwise only one of the selected options is sent in the request
            $view->vars['full_name'] .= '[]';
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'multiple'          => false,
            'expanded'          => false,
            'choices'           => [],
            'choice_label'      => null,
            'choice_value'      => null,
            'choice_attr'       => null,
            'preferred_choices' => [],
            'empty_data'        => static fn (Options $options): mixed => $options['multiple'] ? [] : '',
            'placeholder'       => static fn (Options $options): ?string => $options['required'] ? null : '',
            'placeholder_attr'  => [],
            'error_bubbling'    => false,
            'compound'          => false,
            // The view data is always a string or an array of strings, even when "data" is an object
            'data_class'        => null,
            'trim'              => false,
            'invalid_message'   => 'The selected choice is invalid.',
        ]);

        $resolver->setAllowedTypes('multiple', 'bool');
        $resolver->setAllowedValues('expanded', [false]);
        $resolver->setAllowedTypes('choices', ['array', \Traversable::class]);
        $resolver->setAllowedTypes('choice_label', ['null', 'callable']);
        $resolver->setAllowedTypes('choice_value', ['null', 'callable']);
        $resolver->setAllowedTypes('choice_attr', ['null', 'array', 'callable']);
        $resolver->setAllowedTypes('preferred_choices', ['array', 'callable']);
        $resolver->setAllowedTypes('placeholder', ['null', 'string', 'bool']);
        $resolver->setAllowedTypes('placeholder_attr', 'array');

        $resolver->setNormalizer('placeholder', static function (Options $options, mixed $placeholder): ?string {
            if ($options['multiple'] || false === $placeholder) {
                // never a placeholder for <select multiple>, or when the user opted out
                return null;
            }
            if ($options['required'] && ($options['attr']['size'] ?? 1) > 1) {
                // a placeholder in a required list box makes no sense
                return null;
            }

            return true === $placeholder ? '' : $placeholder;
        });
    }

    public function getBlockPrefix(): string
    {
        return 'choice';
    }

    /** @return list<ChoiceView> */
    private function createChoiceViews(ChoiceListInterface $choiceList, array $options): array
    {
        $views = [];
        $keys  = $choiceList->getOriginalKeys();

        foreach ($choiceList->getChoices() as $value => $choice) {
            $value = (string) $value;
            $key   = $keys[$value];
            $label = null !== $options['choice_label'] ? $options['choice_label']($choice, $key, $value) : $key;
            $attr  = match (true) {
                null === $options['choice_attr']  => [],
                is_array($options['choice_attr']) => $options['choice_attr'][$key] ?? [],
                default                           => $options['choice_attr']($choice, $key, $value),
            };

            $views[] = new ChoiceView($choice, $value, (string) $label, $attr);
        }

        return $views;
    }

    /** @return list<ChoiceView> */
    private function filterPreferred(array $views, array|callable $preferred): array
    {
        if ([] === $preferred) {
            return [];
        }

        // arrays are always lists of choices, even when they happen to look callable
        return array_values(array_filter($views, static fn (ChoiceView $view): bool => is_array($preferred)
            ? in_array($view->data, $preferred, true)
            : (bool) $preferred($view->data, $view->label, $view->value)));
    }
}
