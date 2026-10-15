<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\ChoiceList\LazyChoiceList;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Tests\Fixtures\Color;
use Phalcon\Form\Tests\Fixtures\Country;
use Phalcon\Form\Tests\Fixtures\Profile;
use Phalcon\Form\Type\Core\ChoiceType;
use Phalcon\Form\Type\Core\FormType;
use PHPUnit\Framework\TestCase;

/**
 * Object choices: choice_label / choice_value as property paths or callables, choice_loader.
 */
final class SelectChoiceLabelValueTest extends TestCase
{
    private FormFactory $factory;
    private Country $fr;
    private Country $se;
    private Country $jp;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
        $this->fr      = new Country(1, 'France');
        $this->se      = new Country(2, 'Sweden');
        $this->jp      = new Country(3, 'Japan', 'Asia');
    }

    /** @return list<Country> */
    private function countries(): array
    {
        return [$this->fr, $this->se, $this->jp];
    }

    public function testObjectsWithoutChoiceValueGetIndexValues(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, $this->se, ['choices' => $this->countries(), 'choice_label' => 'name']);

        self::assertSame('1', $form->getViewData(), '0-based position in the list');
        self::assertSame(['0', '1', '2'], array_map(static fn (ChoiceView $c) => $c->value, $form->createView()->vars['choices']));

        $form->submit('2');
        self::assertSame($this->jp, $form->getData(), 'the very instance from the list');
    }

    public function testChoiceLabelAsPropertyPath(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => $this->countries(), 'choice_label' => 'name'])->createView();
        self::assertSame(['France', 'Sweden', 'Japan'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']), 'getName() via the PropertyAccessor');

        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => $this->countries(), 'choice_label' => 'continent'])->createView();
        self::assertSame(['Europe', 'Europe', 'Asia'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']), 'public property');

        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => [new \ArrayObject(['name' => 'A']), new \ArrayObject(['name' => 'B'])], 'choice_label' => '[name]'])->createView();
        self::assertSame(['A', 'B'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']), 'ArrayAccess choices with an index path');
        // Note: plain arrays cannot be choices, a nested array is always an <optgroup> (see SelectGroupsTest)
    }

    public function testChoiceLabelCallableReceivesChoiceKeyAndValue(): void
    {
        $seen = [];
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'      => ['Red' => 'r', 'Green' => 'g'],
            'choice_label' => static function (string $choice, string $key, string $value) use (&$seen): string {
                $seen[] = [$choice, $key, $value];

                return strtoupper($key);
            },
        ])->createView();

        self::assertSame(['RED', 'GREEN'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']));
        self::assertSame([['r', 'Red', 'r'], ['g', 'Green', 'g']], $seen);
    }

    public function testChoiceLabelNullUsesTheKeys(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => $this->countries()])->createView();

        self::assertSame(['0', '1', '2'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']), 'a list without labels: the keys are the labels (Symfony)');
    }

    public function testChoiceValueAsPropertyPathRoundTrip(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, $this->se, ['choices' => $this->countries(), 'choice_label' => 'name', 'choice_value' => 'id']);

        self::assertSame('2', $form->getViewData(), 'getId() as the HTML value');
        $view = $form->createView();
        self::assertSame(['1', '2', '3'], array_map(static fn (ChoiceView $c) => $c->value, $view->vars['choices']));
        self::assertSame($this->se, $view->vars['choices'][1]->data);
        self::assertTrue($view->vars['is_selected']('2', $view->vars['value']));

        $form->submit('3');
        self::assertSame($this->jp, $form->getData(), 'submitting the id gives the object back');

        $form = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => $this->countries(), 'choice_value' => 'id', 'required' => false]);
        self::assertSame('', $form->getViewData(), 'null data: the path is not read on null');
        self::assertNull($form->submit('')->getData());
    }

    public function testChoiceValueCallable(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'      => $this->countries(),
            'choice_label' => 'name',
            'choice_value' => static fn (?Country $c): string => $c ? strtolower(substr($c->getName(), 0, 2)) : '',
        ]);

        self::assertSame(['fr', 'sw', 'ja'], array_map(static fn (ChoiceView $c) => $c->value, $form->createView()->vars['choices']));
        self::assertSame($this->se, $form->submit('sw')->getData());
    }

    public function testObjectPreselectedByValueNotIdentity(): void
    {
        // A different instance with the same id (e.g. loaded by another query) is still selected
        // when "choice_value" is given, because values are compared, not instances.
        $otherSweden = new Country(2, 'Sweden');
        $form        = $this->factory->createNamed('c', ChoiceType::class, $otherSweden, ['choices' => $this->countries(), 'choice_value' => 'id']);
        self::assertSame('2', $form->getViewData());

        $form = $this->factory->createNamed('c', ChoiceType::class, $otherSweden, ['choices' => $this->countries()]);
        self::assertSame('', $form->getViewData(), 'without choice_value only identity counts');
    }

    public function testObjectWrittenToAnEntityProperty(): void
    {
        $profile = new Profile();
        $profile->setHomeland($this->fr);

        $form = $this->factory->createNamedBuilder('profile', FormType::class, $profile)
            ->add('homeland', ChoiceType::class, ['choices' => $this->countries(), 'choice_label' => 'name', 'choice_value' => 'id'])
            ->getForm();

        self::assertSame('1', $form->get('homeland')->getViewData());
        $form->submit(['homeland' => '3']);
        self::assertSame($this->jp, $profile->getHomeland(), 'setHomeland() got the Country instance');
    }

    public function testEnumChoices(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, Color::Green, [
            'choices'      => Color::cases(),
            'choice_label' => static fn (Color $c): string => $c->name,
            'choice_value' => static fn (?Color $c): string => $c?->value ?? '',
        ]);

        self::assertSame('green', $form->getViewData());
        self::assertSame(['Red', 'Green', 'Blue'], array_map(static fn (ChoiceView $c) => $c->label, $form->createView()->vars['choices']));
        self::assertSame(Color::Blue, $form->submit('blue')->getData());

        $form = $this->factory->createNamed('c', ChoiceType::class, Color::Green, ['choices' => Color::cases()]);
        self::assertSame('1', $form->getViewData(), 'enums are objects: index values without choice_value');
        self::assertSame(Color::Red, $form->submit('0')->getData());
        // prototype: Symfony has EnumType (choice_value => value, choice_label => name); add it in M2
    }

    public function testChoiceAttrAsPropertyPath(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'      => [(object) ['name' => 'A', 'attr' => ['data-x' => 1]], (object) ['name' => 'B', 'attr' => []]],
            'choice_label' => 'name',
            'choice_attr'  => 'attr',
        ])->createView();

        self::assertSame(['data-x' => 1], $view->vars['choices'][0]->attr);
        self::assertSame([], $view->vars['choices'][1]->attr);
    }

    public function testChoiceLoaderIsLazyAndCalledOnce(): void
    {
        $calls  = 0;
        $loader = function () use (&$calls): array {
            ++$calls;

            return ['Red' => 'r', 'Green' => 'g'];
        };

        $form = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => ['ignored' => 'x'], 'choice_loader' => $loader]);
        self::assertInstanceOf(LazyChoiceList::class, $form->getConfig()->getAttribute('choice_list'));
        self::assertSame(0, $calls, 'creating the form with null data does not load');
        self::assertSame('', $form->getViewData());
        self::assertSame(0, $calls, 'neither does reading empty data');

        $form->submit('g');
        self::assertSame(1, $calls, 'the submit needs the list');
        self::assertSame('g', $form->getData());
        $view = $form->createView();
        self::assertSame(1, $calls, 'loaded once');
        self::assertSame(['r', 'g'], array_map(static fn (ChoiceView $c) => $c->value, $view->vars['choices']), 'the loader wins over "choices"');
    }

    public function testChoiceLoaderWithObjectsAndValuePath(): void
    {
        $form = $this->factory->createNamed('c', ChoiceType::class, $this->se, [
            'choice_loader' => fn (): array => $this->countries(),
            'choice_label'  => 'name',
            'choice_value'  => 'id',
        ]);

        self::assertSame('2', $form->getViewData(), 'the value path is applied to the data without loading the list');
        self::assertFalse($form->getConfig()->getAttribute('choice_list')->isLoaded());
        self::assertSame($this->jp, $form->submit('3')->getData());
    }

    public function testChoiceLoaderExpandedLoadsImmediately(): void
    {
        $calls = 0;
        $form  = $this->factory->createNamed('c', ChoiceType::class, null, ['choice_loader' => function () use (&$calls): array {
            ++$calls;

            return ['Red' => 'r'];
        }, 'expanded' => true]);

        self::assertSame(1, $calls, 'the children are the choices, so expanded lists cannot be lazy');
        self::assertCount(1, $form->all());
    }
}
