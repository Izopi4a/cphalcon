<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Select;

use Phalcon\Form\ChoiceList\ArrayChoiceList;
use Phalcon\Form\ChoiceList\ChoiceGroupView;
use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Tests\Fixtures\Country;
use Phalcon\Form\Type\Core\ChoiceType;
use PHPUnit\Framework\TestCase;

/**
 * <optgroup>s (nested choices, group_by), preferred choices, per-option attributes.
 */
final class SelectGroupsTest extends TestCase
{
    private const GROUPED = [
        'Warm' => ['Red' => 'r', 'Orange' => 'o'],
        'Cold' => ['Blue' => 'b', 'Green' => 'g'],
    ];

    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    /** @return list<string> "label:value" of a flat list of ChoiceView */
    private static function flat(array $views): array
    {
        return array_values(array_map(static fn (ChoiceView $v): string => $v->label . ':' . $v->value, $views));
    }

    public function testNestedChoicesBecomeOptgroups(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'b', ['choices' => self::GROUPED]);
        $view = $form->createView();

        self::assertCount(2, $view->vars['choices']);
        self::assertContainsOnlyInstancesOf(ChoiceGroupView::class, $view->vars['choices']);
        self::assertSame(['Warm', 'Cold'], array_keys($view->vars['choices']), 'groups are keyed by their label');
        self::assertSame('Warm', $view->vars['choices']['Warm']->label);
        self::assertSame(['Red:r', 'Orange:o'], self::flat($view->vars['choices']['Warm']->choices));
        self::assertSame(['Blue:b', 'Green:g'], self::flat($view->vars['choices']['Cold']->choices));
        self::assertSame([2, 3], array_keys($view->vars['choices']['Cold']->choices), 'option views keep their global index');
        self::assertTrue($view->vars['is_selected']('b', $view->vars['value']));

        $form->submit('g');
        self::assertSame('g', $form->getData(), 'values inside groups submit normally');
    }

    public function testTheListItselfIsFlat(): void
    {
        $list = new ArrayChoiceList(self::GROUPED);

        self::assertSame(['r' => 'r', 'o' => 'o', 'b' => 'b', 'g' => 'g'], $list->getChoices());
        self::assertSame(['r' => 'Red', 'o' => 'Orange', 'b' => 'Blue', 'g' => 'Green'], $list->getOriginalKeys());
        self::assertSame(['Warm' => ['Red' => 'r', 'Orange' => 'o'], 'Cold' => ['Blue' => 'b', 'Green' => 'g']], $list->getStructuredValues(), 'only the structure remembers the groups');
        self::assertSame([1 => 'b'], $list->getChoicesForValues(['x', 'b']));
    }

    public function testMixedGroupedAndUngroupedChoices(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => ['None' => 'n'] + self::GROUPED + ['Other' => 'x']])->createView();

        self::assertInstanceOf(ChoiceView::class, $view->vars['choices'][0]);
        self::assertInstanceOf(ChoiceGroupView::class, $view->vars['choices']['Warm']);
        self::assertInstanceOf(ChoiceGroupView::class, $view->vars['choices']['Cold']);
        self::assertInstanceOf(ChoiceView::class, $view->vars['choices'][5]);
        self::assertSame(['None', 'Warm', 'Cold', 'Other'], array_map(static fn ($v) => $v->label, array_values($view->vars['choices'])));
    }

    public function testNestedGroupsAreAllowed(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => ['Europe' => ['West' => ['France' => 'fr'], 'North' => ['Sweden' => 'se']]]])->createView();

        $europe = $view->vars['choices']['Europe'];
        self::assertInstanceOf(ChoiceGroupView::class, $europe);
        self::assertInstanceOf(ChoiceGroupView::class, $europe->choices['West']);
        self::assertSame('fr', $europe->choices['West']->choices[0]->value);
        // HTML only allows one <optgroup> level: the renderer has to flatten or label "Europe / West"
    }

    public function testGroupByCallable(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'  => ['Red' => 'r', 'Blue' => 'b', 'Orange' => 'o', 'Any' => 'a'],
            'group_by' => static fn (string $choice, string $key, string $value): ?string => match ($choice) {
                'r', 'o' => 'Warm',
                'b'      => 'Cold',
                default  => null, // ungrouped
            },
        ])->createView();

        self::assertSame(['Warm', 'Cold', 3], array_keys($view->vars['choices']));
        self::assertSame(['Red:r', 'Orange:o'], self::flat($view->vars['choices']['Warm']->choices));
        self::assertSame(['Blue:b'], self::flat($view->vars['choices']['Cold']->choices));
        self::assertSame('Any', $view->vars['choices'][3]->label, 'null from group_by: not grouped');
    }

    public function testGroupByCallableReturningSeveralGroups(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'  => ['Red' => 'r', 'Blue' => 'b'],
            'group_by' => static fn (string $choice): array => 'r' === $choice ? ['Warm', 'Primary'] : ['Cold', 'Primary'],
        ])->createView();

        self::assertSame(['Warm', 'Primary', 'Cold'], array_keys($view->vars['choices']));
        self::assertSame(['Red:r', 'Blue:b'], self::flat($view->vars['choices']['Primary']->choices), 'a choice may appear in several groups');
    }

    public function testGroupByPropertyPathOnObjects(): void
    {
        $fr   = new Country(1, 'France');
        $se   = new Country(2, 'Sweden');
        $jp   = new Country(3, 'Japan', 'Asia');
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'      => [$fr, $se, $jp],
            'choice_label' => 'name',
            'choice_value' => 'id',
            'group_by'     => 'continent',
        ])->createView();

        self::assertSame(['Europe', 'Asia'], array_keys($view->vars['choices']));
        self::assertSame(['France:1', 'Sweden:2'], self::flat($view->vars['choices']['Europe']->choices));
        self::assertSame(['Japan:3'], self::flat($view->vars['choices']['Asia']->choices));
    }

    public function testPreferredChoicesAreRenderedFirstAndKeptInTheList(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'], 'preferred_choices' => ['b', 'r']])->createView();

        self::assertSame(['Blue:b', 'Red:r'], self::flat($view->vars['preferred_choices']), 'in the order of the preferred_choices option');
        self::assertSame([2, 0], array_keys($view->vars['preferred_choices']), 'keyed by their index in the full list');
        self::assertSame(['Red:r', 'Green:g', 'Blue:b'], self::flat($view->vars['choices']), 'duplicate_preferred_choices (default true): still in the main list');
    }

    public function testDuplicatePreferredChoicesFalse(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'], 'preferred_choices' => ['b'], 'duplicate_preferred_choices' => false])->createView();

        self::assertSame(['Blue:b'], self::flat($view->vars['preferred_choices']));
        self::assertSame(['Red:r', 'Green:g'], self::flat($view->vars['choices']), 'moved, not copied');
    }

    public function testPreferredChoicesCallableAndPropertyPath(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'           => ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'],
            'preferred_choices' => static fn (string $choice, string $key, string $value): bool => 'g' === $choice,
        ])->createView();
        self::assertSame(['Green:g'], self::flat($view->vars['preferred_choices']));

        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'           => [new Country(1, 'France'), new Country(2, 'Sweden', featured: true)],
            'choice_label'      => 'name',
            'choice_value'      => 'id',
            'preferred_choices' => 'featured',
        ])->createView();
        self::assertSame(['Sweden:2'], self::flat($view->vars['preferred_choices']));
    }

    public function testPreferredChoicesWithinGroups(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, ['choices' => self::GROUPED, 'preferred_choices' => ['g', 'r']])->createView();

        // Symfony: with nested choices the preferred groups keep the source order (only group_by
        // sorts groups by their best preferred choice); the options inside follow the list order.
        self::assertSame(['Warm', 'Cold'], array_keys($view->vars['preferred_choices']));
        self::assertContainsOnlyInstancesOf(ChoiceGroupView::class, $view->vars['preferred_choices']);
        self::assertSame(['Green:g'], self::flat($view->vars['preferred_choices']['Cold']->choices), 'only the preferred option inside the group');
        self::assertSame(['Red:r'], self::flat($view->vars['preferred_choices']['Warm']->choices));
        self::assertSame(['Red:r', 'Orange:o'], self::flat($view->vars['choices']['Warm']->choices), 'the full group is untouched');
    }

    public function testPreferredChoicesWithGroupBy(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'                     => ['Red' => 'r', 'Blue' => 'b', 'Orange' => 'o'],
            'group_by'                    => static fn (string $c): string => 'b' === $c ? 'Cold' : 'Warm',
            'preferred_choices'           => ['o'],
            'duplicate_preferred_choices' => false,
        ])->createView();

        self::assertSame(['Warm'], array_keys($view->vars['preferred_choices']), 'empty preferred groups are dropped');
        self::assertSame(['Orange:o'], self::flat($view->vars['preferred_choices']['Warm']->choices));
        self::assertSame(['Red:r'], self::flat($view->vars['choices']['Warm']->choices));
    }

    public function testChoiceAttrArrayAndCallable(): void
    {
        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'     => self::GROUPED,
            'choice_attr' => ['Orange' => ['disabled' => true], 'Blue' => ['data-hex' => '#00f']],
        ])->createView();
        self::assertSame(['disabled' => true], $view->vars['choices']['Warm']->choices[1]->attr, 'keyed by the label (original key)');
        self::assertSame([], $view->vars['choices']['Warm']->choices[0]->attr);
        self::assertSame(['data-hex' => '#00f'], $view->vars['choices']['Cold']->choices[2]->attr);

        $view = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'     => ['Red' => 'r'],
            'choice_attr' => static fn (string $choice, string $key, string $value): array => ['data-key' => $key, 'data-value' => $value, 'data-choice' => $choice],
        ])->createView();
        self::assertSame(['data-key' => 'Red', 'data-value' => 'r', 'data-choice' => 'r'], $view->vars['choices'][0]->attr);
    }

    public function testDisabledOptionIsStillAcceptedServerSide(): void
    {
        // "disabled" in choice_attr is an HTML attribute only. Symfony accepts the value when it
        // is posted anyway (a tampered request); rejecting it is the job of a validation constraint.
        // Documented as current behaviour; the RFC may decide to reject disabled options.
        $form = $this->factory->createNamed('c', ChoiceType::class, null, [
            'choices'     => ['Red' => 'r', 'Orange' => 'o'],
            'choice_attr' => ['Orange' => ['disabled' => true]],
        ])->submit('o');

        self::assertTrue($form->isSynchronized());
        self::assertSame('o', $form->getData());
        self::assertTrue($form->isValid());
    }
}
