<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\ChoiceList\ChoiceGroupView;
use Phalcon\Form\Data\CheckboxListMapper;
use Phalcon\Form\Data\RadioListMapper;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Tests\Fixtures\Profile;
use Phalcon\Form\Type\Core\CheckboxType;
use Phalcon\Form\Type\Core\ChoiceType;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\RadioType;
use PHPUnit\Framework\TestCase;

/**
 * expanded: radios (single) and checkboxes name="form[color][]" (multiple).
 */
final class SelectExpandedTest extends TestCase
{
    private const COLORS = ['Red' => 'red', 'Green' => 'green', 'Blue' => 'blue'];

    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testRadiosOneChildPerChoice(): void
    {
        $form = $this->factory->createNamedBuilder('form')
            ->add('color', ChoiceType::class, ['choices' => self::COLORS, 'expanded' => true])
            ->getForm();
        $color = $form->get('color');

        self::assertTrue($color->getConfig()->getCompound());
        self::assertInstanceOf(RadioListMapper::class, $color->getConfig()->getDataMapper());
        self::assertSame([0, 1, 2], array_keys($color->all()), 'children named by index (required: no placeholder radio)');
        foreach ($color as $i => $radio) {
            self::assertSame(RadioType::class, $radio->getConfig()->getType()->getInnerType()::class);
            self::assertSame(array_values(self::COLORS)[$i], $radio->getConfig()->getOption('value'));
            self::assertSame(array_keys(self::COLORS)[$i], $radio->getConfig()->getOption('label'));
            self::assertTrue($radio->isRequired(), 'radios inherit required');
        }

        $view = $form->createView();
        self::assertTrue($view['color']->vars['expanded']);
        self::assertTrue($view['color']->vars['compound']);
        self::assertCount(3, $view['color']->children);
        foreach ($view['color'] as $childView) {
            self::assertSame('form[color]', $childView->vars['full_name'], 'all radios share the parent name');
            self::assertSame(['form', 'checkbox', 'radio', '_form_color_entry'], $childView->vars['block_prefixes'], 'block_name "entry"');
            self::assertFalse($childView->vars['checked']);
        }
        self::assertSame('form_color_1', $view['color'][1]->vars['id']);
        self::assertSame('green', $view['color'][1]->vars['value']);
        self::assertSame('Green', $view['color'][1]->vars['label']);
    }

    public function testRadiosRoundTrip(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'green', ['choices' => self::COLORS, 'expanded' => true]);

        self::assertSame('green', $form->getViewData(), 'view data of the compound is still the string value');
        self::assertFalse($form->get('0')->getData());
        self::assertTrue($form->get('1')->getData(), 'children get booleans');
        $view = $form->createView();
        self::assertSame('green', $view->vars['value']);
        self::assertTrue($view[1]->vars['checked']);
        self::assertFalse($view[0]->vars['checked']);

        $form->submit('blue');
        self::assertTrue($form->isSynchronized());
        self::assertSame('blue', $form->getData());
        self::assertTrue($form->get('2')->getData());
        self::assertFalse($form->get('1')->getData());
        self::assertSame(['0' => null, '1' => null, '2' => 'blue'], array_map(static fn ($c) => $c->getViewData(), $form->all()), 'the PRE_SUBMIT listener dispatched the value to the right child');
    }

    public function testRadiosEmptySubmitWhenRequired(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'green', ['choices' => self::COLORS, 'expanded' => true])->submit(null);

        self::assertTrue($form->isSynchronized());
        self::assertNull($form->getData(), 'empty_data for radios is null');
        self::assertTrue($form->isEmpty());
        // TODO(M2 validation bridge): required radios with nothing checked must be invalid
        self::assertTrue($form->isValid());
    }

    public function testRadiosWithPlaceholder(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'required' => false]);

        self::assertSame(['placeholder', 0, 1, 2], array_keys($form->all()), 'the "None" radio comes first');
        self::assertTrue($form->get('placeholder')->getData(), 'null data: the placeholder radio is checked');
        $view = $form->createView();
        self::assertTrue($view['placeholder']->vars['checked']);
        self::assertSame('', $view['placeholder']->vars['value']);
        self::assertSame('None', $view['placeholder']->vars['label']);
        self::assertSame('color', $view['placeholder']->vars['full_name']);
        self::assertSame('None', $view->vars['placeholder']);
        self::assertFalse($view->vars['placeholder_in_choices']);

        $form->submit('');
        self::assertNull($form->getData(), 'placeholder radio submitted -> null');
        self::assertTrue($form->get('placeholder')->getData());

        $form = $this->factory->createNamed('color', ChoiceType::class, 'red', ['choices' => self::COLORS, 'expanded' => true, 'required' => false])->submit(null);
        self::assertNull($form->getData(), 'nothing posted -> null too');
    }

    public function testRadiosWithARealEmptyChoiceGetNoPlaceholderChild(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => ['Any' => '', 'Red' => 'red'], 'expanded' => true, 'required' => false]);

        self::assertFalse($form->has('placeholder'));
        self::assertSame('', $form->submit('')->getData(), '"" is the real choice');
    }

    public function testRadiosUnknownValue(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'green', ['choices' => self::COLORS, 'expanded' => true])->submit('purple');

        self::assertFalse($form->isSynchronized());
        self::assertNull($form->getData());
        self::assertSame('purple', $form->getViewData());
        self::assertStringContainsString('"purple"', $form->getTransformationFailure()->getMessage());
    }

    public function testRadiosWithIntAndZeroValues(): void
    {
        $form = $this->factory->createNamed('n', ChoiceType::class, 0, ['choices' => ['Zero' => 0, 'One' => 1], 'expanded' => true]);

        self::assertTrue($form->get('0')->getData(), '0 is checked');
        self::assertSame(0, $form->submit('0')->getData());
        self::assertSame(1, $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => ['Zero' => 0, 'One' => 1], 'expanded' => true])->submit('1')->getData());
    }

    public function testCheckboxesOneChildPerChoice(): void
    {
        $form = $this->factory->createNamedBuilder('form')
            ->add('color', ChoiceType::class, ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])
            ->getForm();
        $color = $form->get('color');

        self::assertInstanceOf(CheckboxListMapper::class, $color->getConfig()->getDataMapper());
        self::assertSame([0, 1, 2], array_keys($color->all()), 'never a placeholder for checkboxes');
        foreach ($color as $checkbox) {
            self::assertSame(CheckboxType::class, $checkbox->getConfig()->getType()->getInnerType()::class);
            self::assertFalse($checkbox->isRequired(), 'a checkbox of a list is never required');
        }

        $view = $form->createView();
        self::assertTrue($view['color']->vars['multiple']);
        foreach ($view['color'] as $childView) {
            self::assertSame('form[color][]', $childView->vars['full_name'], 'name="form[color][]" on every checkbox');
            self::assertSame(['form', 'checkbox', '_form_color_entry'], $childView->vars['block_prefixes']);
        }
        self::assertSame('form_color_2', $view['color'][2]->vars['id']);
        self::assertSame('blue', $view['color'][2]->vars['value']);
        self::assertSame('form[color]', $view['color']->vars['full_name'], 'the parent name itself has no [] (unlike <select multiple>)');
    }

    public function testCheckboxesRoundTrip(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, ['green'], ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true]);

        self::assertSame(['green'], $form->getViewData());
        self::assertTrue($form->get('1')->getData());
        self::assertTrue($form->createView()[1]->vars['checked']);

        $form->submit(['red', 'blue']);
        self::assertTrue($form->isSynchronized());
        self::assertSame(['red', 'blue'], $form->getData());
        self::assertTrue($form->get('0')->getData());
        self::assertFalse($form->get('1')->getData());
        self::assertTrue($form->get('2')->getData());
        self::assertSame(['red', 'blue'], $form->createView()->vars['value']);
    }

    public function testCheckboxesNoneCheckedIsAnEmptyArray(): void
    {
        self::assertSame([], $this->factory->createNamed('c', ChoiceType::class, ['green'], ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])->submit(null)->getData(), 'browsers post nothing when no box is checked');
        self::assertSame([], $this->factory->createNamed('c', ChoiceType::class, ['green'], ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])->submit([])->getData());
    }

    public function testCheckboxesUnknownValueIsAnErrorOnTheParent(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])->submit(['red', 'purple']);

        self::assertTrue($form->isSynchronized());
        self::assertSame(['red'], $form->getData(), 'known values kept');
        self::assertFalse($form->isValid());
        self::assertCount(1, $form->getErrors());
        self::assertSame(['{{ value }}' => 'purple'], $form->getErrors()[0]->getMessageParameters());
        self::assertSame($form, $form->getErrors()[0]->getOrigin());
        foreach ($form as $checkbox) {
            self::assertTrue($checkbox->isValid());
        }
    }

    public function testCheckboxesScalarSubmitIsNotSynchronized(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])->submit('red');

        self::assertFalse($form->isSynchronized(), 'name="color" without [] posted to a checkbox list');
        self::assertSame('Expected an array.', $form->getTransformationFailure()->getMessage());
    }

    public function testCheckboxesPreselectedFromEntityAndWrittenBack(): void
    {
        $profile         = new Profile();
        $profile->colors = ['blue'];

        $form = $this->factory->createNamedBuilder('profile', FormType::class, $profile)
            ->add('colors', ChoiceType::class, ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true])
            ->getForm();

        self::assertTrue($form->get('colors')->get('2')->getData());
        $view = $form->createView();
        self::assertTrue($view['colors'][2]->vars['checked']);
        self::assertSame('profile[colors][]', $view['colors'][2]->vars['full_name']);

        $form->submit(['colors' => ['red', 'green']]);
        self::assertSame(['red', 'green'], $profile->colors);
    }

    public function testRadiosPreselectedFromEntityAndWrittenBack(): void
    {
        $profile          = new Profile();
        $profile->country = 'fr';

        $form = $this->factory->createNamedBuilder('profile', FormType::class, $profile)
            ->add('country', ChoiceType::class, ['choices' => ['Germany' => 'de', 'France' => 'fr'], 'expanded' => true])
            ->getForm();

        self::assertTrue($form->get('country')->get('1')->getData());
        self::assertSame('profile[country]', $form->createView()['country'][1]->vars['full_name']);

        $form->submit(['country' => 'de']);
        self::assertSame('de', $profile->country);
    }

    public function testDisabledExpandedIgnoresSubmission(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, ['green'], ['choices' => self::COLORS, 'expanded' => true, 'multiple' => true, 'disabled' => true])->submit(['red']);
        self::assertSame(['green'], $form->getData());
        self::assertTrue($form->get('0')->isDisabled(), 'children inherit disabled through the parent');

        $form = $this->factory->createNamed('color', ChoiceType::class, 'green', ['choices' => self::COLORS, 'expanded' => true, 'disabled' => true])->submit('red');
        self::assertSame('green', $form->getData());
    }

    public function testChoiceAttrPerCheckbox(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, [
            'choices'     => self::COLORS,
            'expanded'    => true,
            'multiple'    => true,
            'choice_attr' => static fn (string $choice): array => ['data-color' => $choice, 'class' => 'swatch'],
        ]);

        self::assertSame(['data-color' => 'green', 'class' => 'swatch'], $form->get('1')->getConfig()->getOption('attr'));
        self::assertSame(['data-color' => 'green', 'class' => 'swatch'], $form->createView()[1]->vars['attr']);
    }

    public function testChoiceLabelFalseGivesChildrenNoLabel(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'choice_label' => false]);

        self::assertFalse($form->get('0')->getConfig()->getOption('label'));
        self::assertFalse($form->createView()[0]->vars['label']);
    }

    public function testGroupedChoicesExpanded(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, [
            'choices'  => ['Warm' => ['Red' => 'red'], 'Cold' => ['Blue' => 'blue', 'Green' => 'green']],
            'expanded' => true,
            'multiple' => true,
        ]);

        // The children are flat (one checkbox per option, named by global index)...
        self::assertSame([0, 1, 2], array_keys($form->all()));
        self::assertSame(['red', 'blue', 'green'], array_map(static fn ($c) => $c->getConfig()->getOption('value'), array_values($form->all())));

        // ...while the "choices" view var keeps the groups, so a theme can render fieldsets by
        // looking up form.children[choice_view_index]. Symfony's themes render expanded lists
        // flat; grouping them is left to the Volt theme (RFC decision).
        $view = $form->createView();
        self::assertContainsOnlyInstancesOf(ChoiceGroupView::class, $view->vars['choices']);
        self::assertSame([1, 2], array_keys($view->vars['choices']['Cold']->choices), 'option index = child name');
        self::assertSame('blue', $view[1]->vars['value']);

        $form->submit(['green', 'red']);
        self::assertSame(['red', 'green'], $form->getData(), 'in choice order (the mapper walks the children)');
    }

    public function testPreferredChoicesExpandedKeepsOneChildPerChoice(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'preferred_choices' => ['blue']]);

        self::assertCount(3, $form->all(), 'the preferred child is not duplicated');
        self::assertSame([2, 0, 1], array_keys($form->all()), 'preferred first');
    }
}
