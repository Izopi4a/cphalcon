<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\FormFactory;
use Phalcon\Form\Type\Core\ChoiceType;
use PHPUnit\Framework\TestCase;

/**
 * The "placeholder" option: defaults per required/multiple/expanded, placeholder_in_choices, attrs.
 */
final class SelectPlaceholderTest extends TestCase
{
    private const COLORS = ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'];

    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    private function placeholder(array $options): ?string
    {
        return $this->factory->createNamed('c', ChoiceType::class, null, $options + ['choices' => self::COLORS])->createView()->vars['placeholder'];
    }

    public function testDefaultDependsOnRequired(): void
    {
        self::assertNull($this->placeholder([]), 'required (default): no placeholder');
        self::assertNull($this->placeholder(['required' => true]));
        self::assertSame('', $this->placeholder(['required' => false]), 'optional: an empty "" option');
    }

    public function testExplicitStringIsKeptEvenWhenRequired(): void
    {
        self::assertSame('Choose...', $this->placeholder(['placeholder' => 'Choose...']));
        self::assertSame('Choose...', $this->placeholder(['placeholder' => 'Choose...', 'required' => false]));
    }

    public function testFalseDisablesIt(): void
    {
        self::assertNull($this->placeholder(['placeholder' => false, 'required' => false]));
        self::assertNull($this->placeholder(['placeholder' => false, 'required' => true]));
    }

    public function testNeverForMultiple(): void
    {
        self::assertNull($this->placeholder(['multiple' => true]));
        self::assertNull($this->placeholder(['multiple' => true, 'required' => false]));
        self::assertNull($this->placeholder(['multiple' => true, 'placeholder' => 'Pick']), 'explicit string ignored for <select multiple>');
        self::assertNull($this->placeholder(['multiple' => true, 'expanded' => true, 'placeholder' => 'Pick']), 'and for checkboxes');
    }

    public function testExpandedSingleRadios(): void
    {
        self::assertNull($this->placeholder(['expanded' => true]), 'required radios: no "none" radio');
        self::assertNull($this->placeholder(['expanded' => true, 'placeholder' => 'Pick']), 'required radios ignore an explicit placeholder');
        self::assertSame('None', $this->placeholder(['expanded' => true, 'required' => false]), 'optional radios: "" becomes the "None" label');
        self::assertSame('None', $this->placeholder(['expanded' => true, 'required' => false, 'placeholder' => '']));
        self::assertSame('Nothing', $this->placeholder(['expanded' => true, 'required' => false, 'placeholder' => 'Nothing']));
        self::assertNull($this->placeholder(['expanded' => true, 'required' => false, 'placeholder' => false]));
    }

    public function testRequiredListBoxHasNoPlaceholder(): void
    {
        self::assertNull($this->placeholder(['required' => true, 'placeholder' => 'Pick', 'attr' => ['size' => 5]]), 'size > 1 and required: no placeholder');
        self::assertSame('Pick', $this->placeholder(['required' => false, 'placeholder' => 'Pick', 'attr' => ['size' => 5]]));
        self::assertSame('Pick', $this->placeholder(['required' => true, 'placeholder' => 'Pick', 'attr' => ['size' => 1]]));
    }

    public function testPlaceholderIsSelectedWhenValueIsNull(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'required' => false])->createView();

        self::assertSame('', $view->vars['value']);
        self::assertTrue($view->vars['is_selected']('', $view->vars['value']));
        self::assertFalse($view->vars['is_selected']('r', $view->vars['value']));

        $view = $this->factory->createNamed('c', ChoiceType::class, 'r', ['choices' => self::COLORS, 'required' => false])->createView();
        self::assertFalse($view->vars['is_selected']('', $view->vars['value']));
    }

    public function testRealEmptyChoiceFirstReplacesThePlaceholder(): void
    {
        $choices = ['Any' => '', 'Red' => 'r'];
        $view    = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => $choices, 'required' => false, 'placeholder' => 'Pick'])->createView();

        self::assertTrue($view->vars['placeholder_in_choices']);
        self::assertNull($view->vars['placeholder'], 'no second "" option');
        self::assertSame([], $view->vars['placeholder_attr']);
        self::assertSame('Any', $view->vars['choices'][0]->label);

        // Submitting "" selects the real choice, the model gets "" not null
        self::assertSame('', $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => $choices])->submit('')->getData());
    }

    public function testRealEmptyChoiceNotFirstStillGetsAPlaceholder(): void
    {
        // Symfony only looks at the FIRST option (ChoiceListView::hasPlaceholder); a "" choice in
        // the middle leads to two "" options. Documented here as current behaviour.
        // prototype: the RFC may want "any choice with value ''" instead.
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => ['Red' => 'r', 'Any' => ''], 'required' => false])->createView();

        self::assertFalse($view->vars['placeholder_in_choices']);
        self::assertSame('', $view->vars['placeholder']);
    }

    public function testPreferredEmptyChoiceCountsAsPlaceholder(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'           => ['Red' => 'r', 'Any' => ''],
            'preferred_choices' => [''],
            'required'          => false,
        ])->createView();

        self::assertTrue($view->vars['placeholder_in_choices'], 'the first preferred option is ""');
        self::assertNull($view->vars['placeholder']);
    }

    public function testPlaceholderAttr(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'placeholder' => 'Pick', 'placeholder_attr' => ['disabled' => true, 'class' => 'muted']])->createView();
        self::assertSame(['disabled' => true, 'class' => 'muted'], $view->vars['placeholder_attr']);

        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'placeholder' => false, 'placeholder_attr' => ['disabled' => true]])->createView();
        self::assertSame([], $view->vars['placeholder_attr'], 'no placeholder: attrs are not exposed');
    }

    public function testPlaceholderRadioChildCarriesTheAttr(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::COLORS, 'expanded' => true, 'required' => false, 'placeholder_attr' => ['class' => 'none']]);

        self::assertTrue($form->has('placeholder'));
        self::assertSame('None', $form->get('placeholder')->getConfig()->getOption('label'));
        self::assertSame(['class' => 'none'], $form->get('placeholder')->getConfig()->getOption('attr'));
        self::assertSame('', $form->get('placeholder')->getConfig()->getOption('value'));
    }
}
