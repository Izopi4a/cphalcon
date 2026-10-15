<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\ChoiceList\ChoiceGroupView;
use Phalcon\Form\ChoiceList\ChoiceListFactory;
use Phalcon\Form\ChoiceList\ChoiceListInterface;
use Phalcon\Form\ChoiceList\ChoiceListView;
use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\Data\CheckboxListMapper;
use Phalcon\Form\Data\RadioListMapper;
use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\EventListener\MergeCollectionListener;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\FormError;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Options\Options;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Transformer\ChoicesToValuesTransformer;
use Phalcon\Form\Transformer\ChoiceToValueTransformer;
use Phalcon\Form\Transformer\TransformationFailedException;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\View\FormView;
use Phalcon\Support\PropertyAccess\PropertyPathInterface;

/**
 * A choice among a list: <select> (single/multiple), radios (expanded) or checkboxes
 * (expanded + multiple). Choices are given as label => choice, optionally nested as
 * group label => [label => choice] for <optgroup>s.
 *
 *   expanded multiple  renders              compound  empty_data  view data
 *   false    false     <select>             false     ''          string value ("" = none)
 *   false    true      <select multiple>    false     []          list of string values, full_name "[]"
 *   true     false     radios               true      null        string value
 *   true     true      checkboxes           true      []          list of string values, children full_name "[]"
 *
 * The model data is the choice itself (string, int, object...), never its HTML value. Same
 * semantics as Symfony's ChoiceType; translation-related options are left out.
 *
 * prototype: "choice_loader" is a callable returning the choices (Symfony: ChoiceLoaderInterface);
 * "choice_name"/"choice_filter"/"choice_translation_*" are not implemented.
 */
final class ChoiceType extends AbstractType
{
    private readonly ChoiceListFactory $choiceListFactory;

    public function __construct(?ChoiceListFactory $choiceListFactory = null)
    {
        $this->choiceListFactory = $choiceListFactory ?? new ChoiceListFactory();
    }

    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $unknownValues = [];
        $choiceList    = $this->createChoiceList($options);
        $builder->setAttribute('choice_list', $choiceList);

        if ($options['expanded']) {
            $builder->setDataMapper($options['multiple'] ? new CheckboxListMapper() : new RadioListMapper());

            // The children are the choices: build the view structure now and keep it for buildView()
            $choiceListView = $this->createChoiceListView($choiceList, $options);
            $builder->setAttribute('choice_list_view', $choiceListView);

            // Only add the placeholder radio when the choices do not already contain the "" value
            if (null !== $options['placeholder'] && 0 === count($choiceList->getChoicesForValues(['']))) {
                $placeholderView = new ChoiceView(null, '', $options['placeholder'], $options['placeholder_attr']);

                // "placeholder" is a reserved child name
                $this->addSubForm($builder, 'placeholder', $placeholderView, $options);
            }

            $this->addSubForms($builder, $choiceListView->preferredChoices, $options);
            $this->addSubForms($builder, $choiceListView->choices, $options);
        }

        if ($options['expanded'] || $options['multiple']) {
            // Make sure that scalar, submitted values are converted to arrays which can be
            // submitted to the checkboxes/radio buttons; record unknown values on the way.
            $builder->addEventListener(FormEvents::PRE_SUBMIT, static function (FormEvent $event) use ($choiceList, $options, &$unknownValues): void {
                $form = $event->getForm();
                $data = $event->getData();

                // Since the type always uses a mapper an empty array will not be considered as
                // empty in Form::submit(), so evaluate empty data here so its value is submitted
                // to the children
                if (null === $data) {
                    $emptyData = $form->getConfig()->getEmptyData();
                    $data      = $emptyData instanceof \Closure ? $emptyData($form, $data) : $emptyData;
                }

                // Convert the submitted data to a string, if scalar, before casting it to an array
                if (!is_array($data)) {
                    if ($options['multiple']) {
                        throw new TransformationFailedException('Expected an array.');
                    }

                    $data = (array) (string) $data;
                }

                // A map from submitted values to integers (null entries cannot be flipped and are
                // never a choice value: they are dropped here; the "clearMissing" path of
                // Form::submit() still submits null to every child)
                $valueMap = array_flip(array_filter($data, static fn (mixed $v): bool => null !== $v));

                // Make a copy of the value map to determine whether any unknown values were submitted
                $unknownValues = $valueMap;

                // Reconstruct the data as mapping from child names to values
                $knownValues = [];

                if ($options['expanded']) {
                    /** @var FormInterface $child */
                    foreach ($form as $child) {
                        $value = $child->getConfig()->getOption('value');

                        // Add the value to $data with the child's name as key
                        if (isset($valueMap[$value])) {
                            $knownValues[$child->getName()] = $value;
                            unset($unknownValues[$value]);
                        } else {
                            $knownValues[$child->getName()] = null;
                        }
                    }
                } else {
                    foreach ($data as $value) {
                        if (null !== $value && [] !== $choiceList->getChoicesForValues([$value])) {
                            $knownValues[] = $value;
                            unset($unknownValues[$value]);
                        }
                    }
                }

                // The empty value is always known, independent of whether a field exists for it or not
                unset($unknownValues['']);

                // Throw exception if unknown values were submitted (multiple choices are turned
                // into a FormError by the POST_SUBMIT listener below)
                if (count($unknownValues) > 0 && !$options['multiple']) {
                    throw new TransformationFailedException(sprintf('The choices "%s" do not exist in the choice list.', implode('", "', array_keys($unknownValues))));
                }

                $event->setData($knownValues);
            });
        }

        if ($options['multiple']) {
            $messageTemplate = $options['invalid_message'] ?? 'The value {{ value }} is not valid.';

            $builder->addEventListener(FormEvents::POST_SUBMIT, static function (FormEvent $event) use (&$unknownValues, $messageTemplate): void {
                // Unknown values among the submitted ones: the known ones are kept (the form stays
                // synchronized) and the form gets one error naming the unknown ones
                if (count($unknownValues) > 0) {
                    $form     = $event->getForm();
                    $viewData = $form->getViewData();

                    $clientDataAsString = is_scalar($viewData)
                        ? (string) $viewData
                        : (is_array($viewData) ? implode('", "', array_keys($unknownValues)) : get_debug_type($viewData));

                    // prototype: no translator; the message is the template with {{ value }} replaced
                    $message = strtr($messageTemplate, ['{{ value }}' => $clientDataAsString]);

                    $form->addError(new FormError(
                        $message,
                        $messageTemplate,
                        ['{{ value }}' => $clientDataAsString],
                        new TransformationFailedException(sprintf('The choices "%s" do not exist in the choice list.', $clientDataAsString))
                    ));
                }
            });

            // <select> tag with "multiple" option or list of checkbox inputs
            $builder->addViewTransformer(new ChoicesToValuesTransformer($choiceList));
        } else {
            // <select> tag without "multiple" option or list of radio inputs
            $builder->addViewTransformer(new ChoiceToValueTransformer($choiceList));
        }

        if ($options['multiple'] && $options['by_reference']) {
            // Make sure the collection created during the view->norm transformation is merged
            // back into the original collection
            $builder->addEventSubscriber(new MergeCollectionListener(true, true));
        }

        // To avoid issues when the submitted choices are arrays (i.e. array to string conversions),
        // ensure that all elements of the submitted choice data are NULL, strings or ints.
        $builder->addEventListener(FormEvents::PRE_SUBMIT, static function (FormEvent $event): void {
            $data = $event->getData();

            if (!is_array($data)) {
                return;
            }

            foreach ($data as $v) {
                if (null !== $v && !is_string($v) && !is_int($v)) {
                    throw new TransformationFailedException('All choices submitted must be NULL, strings or ints.');
                }
            }
        }, 256);
    }

    public function buildView(FormView $view, FormInterface $form, array $options): void
    {
        /** @var ChoiceListInterface $choiceList */
        $choiceList = $form->getConfig()->getAttribute('choice_list');

        /** @var ChoiceListView $choiceListView */
        $choiceListView = $form->getConfig()->hasAttribute('choice_list_view')
            ? $form->getConfig()->getAttribute('choice_list_view')
            : $this->createChoiceListView($choiceList, $options);

        $view->vars = array_replace($view->vars, [
            'multiple'          => $options['multiple'],
            'expanded'          => $options['expanded'],
            'preferred_choices' => $choiceListView->preferredChoices,
            'choices'           => $choiceListView->choices,
            'separator'         => '-------------------',
            'separator_html'    => false,
            'placeholder'       => null,
            'placeholder_attr'  => [],
        ]);

        // The decision, whether a choice is selected, is potentially done thousands of times
        // during the rendering of a template. Provide a closure here that is optimized for the
        // value of the form, to avoid making the type check inside the closure.
        $view->vars['is_selected'] = $options['multiple']
            ? static fn (string $choice, array $values): bool => in_array($choice, $values, true)
            : static fn (string $choice, mixed $value): bool => $choice === $value;

        // Check if the choices already contain the empty value
        $view->vars['placeholder_in_choices'] = $choiceListView->hasPlaceholder();

        // Only add the empty value option if this is not the case
        if (null !== $options['placeholder'] && !$view->vars['placeholder_in_choices']) {
            $view->vars['placeholder']      = $options['placeholder'];
            $view->vars['placeholder_attr'] = $options['placeholder_attr'];
        }

        if ($options['multiple'] && !$options['expanded']) {
            // Add "[]" to the name in case a select tag with multiple options is displayed.
            // Otherwise only one of the selected options is sent in the request.
            $view->vars['full_name'] .= '[]';
        }
    }

    public function finishView(FormView $view, FormInterface $form, array $options): void
    {
        if ($options['expanded']) {
            // Radio buttons should have the same name as the parent
            $childName = $view->vars['full_name'];

            // Checkboxes should append "[]" to allow multiple selection
            if ($options['multiple']) {
                $childName .= '[]';
            }

            foreach ($view as $childView) {
                $childView->vars['full_name'] = $childName;
            }
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $emptyData = static function (Options $options): mixed {
            if ($options['expanded'] && !$options['multiple']) {
                return null;
            }
            if ($options['multiple']) {
                return [];
            }

            return '';
        };

        $placeholderDefault = static fn (Options $options): ?string => $options['required'] ? null : '';

        $placeholderNormalizer = static function (Options $options, mixed $placeholder): ?string {
            if ($options['multiple']) {
                // never use an empty value for this case
                return null;
            }
            if ($options['required'] && ($options['expanded'] || isset($options['attr']['size']) && $options['attr']['size'] > 1)) {
                // placeholder for required radio buttons or a select with size > 1 does not make sense
                return null;
            }
            if (false === $placeholder) {
                // an empty value should be added but the user decided otherwise
                return null;
            }
            if ($options['expanded'] && '' === $placeholder) {
                // never use an empty label for radio buttons
                return 'None';
            }

            // empty value has been set explicitly
            return true === $placeholder ? '' : $placeholder;
        };

        $compound = static fn (Options $options): bool => $options['expanded'];

        $resolver->setDefaults([
            'multiple'                    => false,
            'expanded'                    => false,
            'choices'                     => [],
            'choice_loader'               => null,
            'choice_label'                => null,
            'choice_value'                => null,
            'choice_attr'                 => null,
            'preferred_choices'           => [],
            'duplicate_preferred_choices' => true,
            'group_by'                    => null,
            'empty_data'                  => $emptyData,
            'placeholder'                 => $placeholderDefault,
            'placeholder_attr'            => [],
            'error_bubbling'              => false,
            'compound'                    => $compound,
            // The view data is always a string or an array of strings, even if the "data" option
            // is manually set to an object.
            'data_class'                  => null,
            'trim'                        => false,
            'invalid_message'             => 'The selected choice is invalid.',
        ]);

        $resolver->setNormalizer('placeholder', $placeholderNormalizer);

        $resolver->setAllowedTypes('multiple', 'bool');
        $resolver->setAllowedTypes('expanded', 'bool');
        $resolver->setAllowedTypes('choices', ['null', 'array', \Traversable::class]);
        $resolver->setAllowedTypes('choice_loader', ['null', 'callable']);
        $resolver->setAllowedTypes('choice_label', ['null', 'bool', 'callable', 'string', PropertyPathInterface::class]);
        $resolver->setAllowedTypes('choice_value', ['null', 'callable', 'string', PropertyPathInterface::class]);
        $resolver->setAllowedTypes('choice_attr', ['null', 'array', 'callable', 'string', PropertyPathInterface::class]);
        $resolver->setAllowedTypes('preferred_choices', ['array', \Traversable::class, 'callable', 'string', PropertyPathInterface::class]);
        $resolver->setAllowedTypes('duplicate_preferred_choices', 'bool');
        $resolver->setAllowedTypes('group_by', ['null', 'callable', 'string', PropertyPathInterface::class]);
        $resolver->setAllowedTypes('placeholder', ['null', 'string', 'bool']);
        $resolver->setAllowedTypes('placeholder_attr', 'array');
    }

    public function getBlockPrefix(): string
    {
        return 'choice';
    }

    private function createChoiceList(array $options): ChoiceListInterface
    {
        if (null !== $options['choice_loader']) {
            return $this->choiceListFactory->createListFromLoader($options['choice_loader'], $options['choice_value']);
        }

        // Harden against NULL values (like in ModelType)
        $choices = $options['choices'] ?? [];

        return $this->choiceListFactory->createListFromChoices($choices, $options['choice_value']);
    }

    private function createChoiceListView(ChoiceListInterface $choiceList, array $options): ChoiceListView
    {
        $preferred = $options['preferred_choices'];
        if ($preferred instanceof \Traversable) {
            $preferred = iterator_to_array($preferred);
        }

        return $this->choiceListFactory->createView(
            $choiceList,
            $preferred,
            $options['choice_label'],
            $options['group_by'],
            $options['choice_attr'],
            $options['duplicate_preferred_choices'],
        );
    }

    /** @param array<int|string, ChoiceView|ChoiceGroupView> $choiceViews */
    private function addSubForms(FormBuilderInterface $builder, array $choiceViews, array $options): void
    {
        foreach ($choiceViews as $name => $choiceView) {
            // Flatten groups: the children of an expanded list are always a flat list; the view
            // keeps the grouping in its "choices" var for themes that want fieldsets.
            if ($choiceView instanceof ChoiceGroupView) {
                $this->addSubForms($builder, $choiceView->choices, $options);

                continue;
            }

            $this->addSubForm($builder, (string) $name, $choiceView, $options);
        }
    }

    private function addSubForm(FormBuilderInterface $builder, string $name, ChoiceView $choiceView, array $options): void
    {
        $choiceOpts = [
            'value'      => $choiceView->value,
            'label'      => $choiceView->label,
            'attr'       => $choiceView->attr,
            'block_name' => 'entry',
        ];

        if ($options['multiple']) {
            $choiceType = CheckboxType::class;
            // The user can check 0 or more checkboxes. If required is true, they are required to
            // check all of them, which is never wanted.
            $choiceOpts['required'] = false;
        } else {
            $choiceType = RadioType::class;
        }

        $builder->add($name, $choiceType, $choiceOpts);
    }
}
