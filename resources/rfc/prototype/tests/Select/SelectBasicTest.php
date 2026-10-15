<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Tests\Fixtures\Profile;
use Phalcon\Form\Type\Core\ChoiceType;
use Phalcon\Form\Type\Core\FormType;
use PHPUnit\Framework\TestCase;

/**
 * Collapsed single <select>: values, defaults, empty submits, disabled.
 */
final class SelectBasicTest extends TestCase
{
    private const COLORS = ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'];

    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testStringValuesRoundTrip(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS]);

        self::assertSame('g', $form->getData());
        self::assertSame('g', $form->getViewData(), 'view data is the string value');

        $view = $form->createView();
        self::assertSame('g', $view->vars['value']);
        self::assertSame(['r', 'g', 'b'], array_map(static fn (ChoiceView $c) => $c->value, $view->vars['choices']));
        self::assertSame(['Red', 'Green', 'Blue'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']));
        self::assertTrue($view->vars['is_selected']('g', $view->vars['value']));
        self::assertFalse($view->vars['is_selected']('r', $view->vars['value']));

        $form->submit('b');
        self::assertTrue($form->isSynchronized());
        self::assertSame('b', $form->getData());
        self::assertTrue($form->createView()->vars['is_selected']('b', 'b'));
    }

    public function testIntValuesKeepTheirTypeInTheModel(): void
    {
        $form = $this->factory->createNamed('n', ChoiceType::class, 2, ['choices' => ['One' => 1, 'Two' => 2, 'Three' => 3]]);

        self::assertSame('2', $form->getViewData(), 'HTML value is a string');

        $form->submit('3');
        self::assertSame(3, $form->getData(), 'the model gets the int back, not the string');
    }

    public function testZeroStringEmptyStringAndOneAreDistinctValues(): void
    {
        // "" is a legitimate choice here: it is NOT the "nothing selected" placeholder
        $choices = ['Nothing' => '', 'Zero' => '0', 'One' => '1'];

        $form = $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => $choices, 'required' => false]);
        $view = $form->createView();
        self::assertSame(['', '0', '1'], array_map(static fn (ChoiceView $c) => $c->value, $view->vars['choices']));
        self::assertTrue($view->vars['placeholder_in_choices'], 'the "" choice doubles as the placeholder...');
        self::assertNull($view->vars['placeholder'], '...so no extra placeholder option is rendered');

        self::assertSame('0', $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => $choices])->submit('0')->getData());
        self::assertSame('1', $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => $choices])->submit('1')->getData());

        $form = $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => $choices])->submit('');
        self::assertSame('', $form->getData(), 'submitting "" selects the "" choice (not null)');
        self::assertTrue($form->isSynchronized());

        $form = $this->factory->createNamed('n', ChoiceType::class, '0', ['choices' => $choices]);
        self::assertTrue($form->createView()->vars['is_selected']('0', $form->createView()->vars['value']));
        self::assertFalse($form->createView()->vars['is_selected']('', $form->createView()->vars['value']));
    }

    public function testIntZeroAndStringZeroCannotShareAListAndFallBackToIndexValues(): void
    {
        // Same string form "0" twice: the list is not "castable to string" and uses 0-based indices
        $form = $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => ['Int zero' => 0, 'String zero' => '0']]);

        self::assertSame(['0', '1'], array_map(static fn (ChoiceView $c) => $c->value, $form->createView()->vars['choices']));
        self::assertSame(0, $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => ['Int zero' => 0, 'String zero' => '0']])->submit('0')->getData());
        self::assertSame('0', $this->factory->createNamed('n', ChoiceType::class, null, ['choices' => ['Int zero' => 0, 'String zero' => '0']])->submit('1')->getData());
    }

    public function testIntZeroAloneIsTheValueZero(): void
    {
        $form = $this->factory->createNamed('n', ChoiceType::class, 0, ['choices' => ['Zero' => 0, 'One' => 1]]);

        self::assertSame('0', $form->getViewData());
        self::assertTrue($form->createView()->vars['is_selected']('0', $form->createView()->vars['value']), '0 is a selection, not "empty"');

        $form->submit('0');
        self::assertSame(0, $form->getData());
        self::assertFalse($form->isEmpty(), '0 is not an empty submission');
    }

    public function testBoolValues(): void
    {
        $form = $this->factory->createNamed('b', ChoiceType::class, false, ['choices' => ['Yes' => true, 'No' => false]]);

        self::assertSame('0', $form->getViewData(), 'false is "0" so that it stays distinct from ""');
        self::assertSame(['1', '0'], array_map(static fn (ChoiceView $c) => $c->value, $form->createView()->vars['choices']));

        self::assertTrue($this->factory->createNamed('b', ChoiceType::class, null, ['choices' => ['Yes' => true, 'No' => false]])->submit('1')->getData());
        self::assertFalse($this->factory->createNamed('b', ChoiceType::class, null, ['choices' => ['Yes' => true, 'No' => false]])->submit('0')->getData());
    }

    public function testNullChoiceSwitchesTheListToIndexValues(): void
    {
        // Symfony: null is not castable, so every value becomes an index; "" stays "no selection"
        $form = $this->factory->createNamed('b', ChoiceType::class, null, ['choices' => ['Yes' => true, 'No' => false, 'Unknown' => null], 'required' => false]);

        self::assertSame(['0', '1', '2'], array_map(static fn (ChoiceView $c) => $c->value, $form->createView()->vars['choices']));
        self::assertSame('2', $form->getViewData(), 'null data IS the "Unknown" choice here (identity match)');
        self::assertNull($this->factory->createNamed('b', ChoiceType::class, null, ['choices' => ['Yes' => true, 'Unknown' => null]])->submit('1')->getData());
        self::assertNull($this->factory->createNamed('b', ChoiceType::class, null, ['choices' => ['Yes' => true, 'Unknown' => null]])->submit('')->getData());
    }

    public function testDefaultFromDataOptionIsLocked(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'data' => 'b']);

        self::assertSame('b', $form->getData());
        $form->setData('r');
        self::assertSame('b', $form->getData(), 'the "data" option locks the default, setData() is ignored');
        self::assertSame('b', $form->createView()->vars['value']);
    }

    public function testDefaultFromEntityProperty(): void
    {
        $profile          = new Profile();
        $profile->country = 'de';

        $form = $this->factory->createNamedBuilder('profile', FormType::class, $profile)
            ->add('country', ChoiceType::class, ['choices' => ['Germany' => 'de', 'France' => 'fr']])
            ->getForm();

        self::assertSame('de', $form->get('country')->getViewData());
        $view = $form->createView();
        self::assertSame('de', $view['country']->vars['value']);
        self::assertSame('profile[country]', $view['country']->vars['full_name']);

        $form->submit(['country' => 'fr']);
        self::assertSame('fr', $profile->country, 'written back to the entity');
    }

    public function testEmptyDataOnEmptySubmit(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS])->submit('');
        self::assertNull($form->getData(), 'default empty_data "" reverse-transforms to null');
        self::assertTrue($form->isSynchronized());
        self::assertTrue($form->isEmpty());

        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'empty_data' => 'g'])->submit('');
        self::assertSame('g', $form->getData(), 'empty_data is a view value, reverse-transformed to the choice');

        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS])->submit(null);
        self::assertNull($form->getData(), 'null submitted behaves like ""');
    }

    public function testPreselectedValueNotInChoices(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'purple', ['choices' => self::COLORS]);

        // Symfony: scalar lists cast the data to its string value even when it is unknown...
        self::assertSame('purple', $form->getViewData());
        $view = $form->createView();
        foreach ($view->vars['choices'] as $choice) {
            self::assertFalse($view->vars['is_selected']($choice->value, $view->vars['value']), '...so no option is selected');
        }

        // ...and submitting the form unchanged fails
        $form->submit('purple');
        self::assertFalse($form->isSynchronized());
        self::assertNull($form->getData());
        self::assertSame('purple', $form->getViewData(), 'the view keeps the raw value for re-display');
    }

    public function testPreselectedObjectNotInChoicesHasNoValue(): void
    {
        $a    = new \stdClass();
        $b    = new \stdClass();
        $form = $this->factory->createNamed('o', ChoiceType::class, new \stdClass(), ['choices' => ['A' => $a, 'B' => $b]]);

        self::assertSame('', $form->getViewData(), 'object lists compare by identity: unknown object has no value');
    }

    public function testEmptySubmitWithAndWithoutPlaceholder(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS, 'required' => false]);
        self::assertSame('', $form->createView()->vars['placeholder']);
        $form->submit('');
        self::assertNull($form->getData(), 'placeholder submitted -> null model data');
        self::assertTrue($form->isValid());

        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS, 'required' => true, 'placeholder' => 'Pick a color']);
        self::assertSame('Pick a color', $form->createView()->vars['placeholder']);
        $form->submit('');
        self::assertNull($form->getData());
        self::assertTrue($form->isSynchronized());
        // TODO(M2 validation bridge): a required select submitted with "" must become invalid
        // (Symfony: NotBlank/NotNull from the validator, "required" alone is only HTML5 here).
        self::assertTrue($form->isValid(), 'prototype: "required" is not validated server side yet');
    }

    public function testDisabledSelectIgnoresSubmission(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::COLORS, 'disabled' => true])->submit('b');

        self::assertTrue($form->isSubmitted());
        self::assertSame('g', $form->getData(), 'data unchanged');
        self::assertTrue($form->isValid());
        self::assertTrue($form->createView()->vars['disabled']);

        $profile          = new Profile();
        $profile->country = 'de';
        $form             = $this->factory->createNamedBuilder('profile', FormType::class, $profile)
            ->add('country', ChoiceType::class, ['choices' => ['Germany' => 'de', 'France' => 'fr'], 'disabled' => true])
            ->getForm()
            ->submit(['country' => 'fr']);
        self::assertSame('de', $profile->country, 'a disabled child is never written back');
        self::assertTrue($form->isValid());
    }

    public function testArraySubmittedToSingleSelectIsRejected(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS])->submit(['r', 'g']);

        self::assertFalse($form->isSynchronized(), 'name="color[]" posted to a single select');
        self::assertNull($form->getData());
    }

    public function testChoicesMayBeTraversable(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => new \ArrayIterator(self::COLORS)])->submit('g');

        self::assertSame('g', $form->getData());
        self::assertCount(3, $form->createView()->vars['choices']);
    }

    public function testViewVarsForTheRenderer(): void
    {
        $view = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::COLORS, 'required' => false])->createView();

        self::assertSame(['form', 'choice', '_color'], $view->vars['block_prefixes']);
        self::assertFalse($view->vars['multiple']);
        self::assertFalse($view->vars['expanded']);
        self::assertFalse($view->vars['compound']);
        self::assertSame([], $view->vars['preferred_choices']);
        self::assertSame('-------------------', $view->vars['separator']);
        self::assertFalse($view->vars['placeholder_in_choices']);
        self::assertSame('', $view->vars['placeholder']);
        self::assertSame([], $view->vars['placeholder_attr']);
        self::assertSame('', $view->vars['value'], 'null data -> "" -> the placeholder is the selected option');
        self::assertTrue($view->vars['is_selected']('', $view->vars['value']));
    }
}
