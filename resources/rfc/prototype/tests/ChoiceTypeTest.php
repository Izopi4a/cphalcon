<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\ChoiceList\ChoiceView;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Options\InvalidOptionsException;
use Phalcon\Form\Type\Core\ChoiceType;
use PHPUnit\Framework\TestCase;

final class ChoiceTypeTest extends TestCase
{
    private const CHOICES = ['Red' => 'r', 'Green' => 'g', 'Blue' => 'b'];

    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testSingleSelect(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, 'g', ['choices' => self::CHOICES]);
        self::assertSame('g', $form->getViewData());

        $form->submit('b');
        self::assertSame('b', $form->getData());

        $view = $form->createView();
        self::assertSame('color', $view->vars['full_name']);
        self::assertFalse($view->vars['multiple']);
        self::assertNull($view->vars['placeholder'], 'required: no placeholder');
        self::assertCount(3, $view->vars['choices']);
        self::assertContainsOnlyInstancesOf(ChoiceView::class, $view->vars['choices']);
        self::assertSame(['Red', 'r', 'r'], [$view->vars['choices'][0]->label, $view->vars['choices'][0]->value, $view->vars['choices'][0]->data]);
        self::assertTrue($view->vars['is_selected']('b', $view->vars['value']));
        self::assertFalse($view->vars['is_selected']('r', $view->vars['value']));
    }

    public function testUnknownChoiceIsNotSynchronized(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::CHOICES])->submit('x');

        self::assertFalse($form->isSynchronized());
        self::assertNull($form->getData());
        self::assertSame('x', $form->getViewData());
    }

    public function testEmptySubmitAndPlaceholder(): void
    {
        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::CHOICES, 'required' => false])->submit('');

        self::assertTrue($form->isSynchronized());
        self::assertNull($form->getData());
        self::assertSame('', $form->createView()->vars['placeholder'], 'optional: empty placeholder');

        $form = $this->factory->createNamed('color', ChoiceType::class, null, ['choices' => self::CHOICES, 'placeholder' => 'Pick one'])->submit('r');
        self::assertSame('Pick one', $form->createView()->vars['placeholder']);
    }

    public function testMultipleSelect(): void
    {
        $form = $this->factory->createNamedBuilder('f')
            ->add('colors', ChoiceType::class, ['choices' => self::CHOICES, 'multiple' => true, 'placeholder' => 'ignored'])
            ->getForm();

        $form->submit(['colors' => ['r', 'b']]);
        self::assertSame(['colors' => ['r', 'b']], $form->getData());

        $view = $form->createView();
        self::assertSame('f[colors][]', $view['colors']->vars['full_name']);
        self::assertTrue($view['colors']->vars['multiple']);
        self::assertNull($view['colors']->vars['placeholder'], 'no placeholder for multiple');
        self::assertSame(['r', 'b'], $view['colors']->vars['value']);
        self::assertTrue($view['colors']->vars['is_selected']('b', $view['colors']->vars['value']));

        $form = $this->factory->createNamed('f', ChoiceType::class, null, ['choices' => self::CHOICES, 'multiple' => true])->submit(null);
        self::assertSame([], $form->getData(), 'nothing selected is an empty array');

        $form = $this->factory->createNamed('f', ChoiceType::class, null, ['choices' => self::CHOICES, 'multiple' => true])->submit(['r', 'nope']);
        self::assertTrue($form->isSynchronized(), 'multiple: unknown values do not fail the submit (Symfony)...');
        self::assertSame(['r'], $form->getData(), '...the known ones are kept...');
        self::assertCount(1, $form->getErrors(), '...and the form gets one error');
    }

    public function testObjectChoicesWithCallbacksAndPreferred(): void
    {
        $red   = new \ArrayObject(['id' => 10, 'name' => 'red']);
        $green = new \ArrayObject(['id' => 20, 'name' => 'green']);
        $form  = $this->factory->createNamed('f', ChoiceType::class, $green, [
            'choices'           => [$red, $green],
            'choice_value'      => static fn (?\ArrayObject $o): string => $o ? (string) $o['id'] : '',
            'choice_label'      => static fn (\ArrayObject $o): string => ucfirst($o['name']),
            'choice_attr'       => static fn (\ArrayObject $o): array => ['data-id' => $o['id']],
            'preferred_choices' => [$green],
        ]);

        self::assertSame('20', $form->getViewData());

        $form->submit('10');
        self::assertSame($red, $form->getData(), 'model data is the object, not the value');

        $view = $form->createView();
        self::assertSame(['Red', 'Green'], array_map(static fn (ChoiceView $c) => $c->label, $view->vars['choices']));
        self::assertSame(['data-id' => 10], $view->vars['choices'][0]->attr);
        self::assertCount(1, $view->vars['preferred_choices']);
        self::assertSame($green, reset($view->vars['preferred_choices'])->data, 'preferred views are keyed by choice index');
    }

    public function testExpandedBuildsOneChildPerChoice(): void
    {
        $form = $this->factory->createNamed('f', ChoiceType::class, 'g', ['choices' => self::CHOICES, 'expanded' => true]);

        self::assertSame([0, 1, 2], array_keys($form->all()), 'children are named by index (PHP int keys), required: no placeholder radio');
        self::assertTrue($form->get('1')->getData());
        self::assertSame('g', $form->submit('g')->getData());

        $this->expectException(InvalidOptionsException::class);
        $this->factory->createNamed('f', ChoiceType::class, null, ['choices' => self::CHOICES, 'expanded' => 'yes']);
    }
}
