<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\Button;
use Phalcon\Form\ButtonBuilder;
use Phalcon\Form\Exception\AlreadySubmittedException;
use Phalcon\Form\Exception\BadMethodCallException;
use Phalcon\Form\Exception\InvalidArgumentException;
use Phalcon\Form\FormBuilder;
use Phalcon\Form\FormError;
use Phalcon\Form\FormFactory;
use Phalcon\Form\SubmitButton;
use Phalcon\Form\SubmitButtonBuilder;
use Phalcon\Form\Type\Core\ButtonType;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\ResetType;
use Phalcon\Form\Type\Core\SubmitType;
use Phalcon\Form\Type\Core\TextType;
use PHPUnit\Framework\TestCase;

final class ButtonTest extends TestCase
{
    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testResolvedTypePicksTheButtonBuilders(): void
    {
        self::assertInstanceOf(SubmitButtonBuilder::class, $this->factory->createNamedBuilder('save', SubmitType::class));
        self::assertInstanceOf(ButtonBuilder::class, $this->factory->createNamedBuilder('b', ButtonType::class));
        self::assertNotInstanceOf(SubmitButtonBuilder::class, $this->factory->createNamedBuilder('b', ButtonType::class));
        self::assertInstanceOf(ButtonBuilder::class, $this->factory->createNamedBuilder('r', ResetType::class));
        self::assertInstanceOf(FormBuilder::class, $this->factory->createNamedBuilder('t', TextType::class));

        self::assertInstanceOf(SubmitButton::class, $this->factory->createNamed('save', SubmitType::class));
        self::assertInstanceOf(Button::class, $this->factory->createNamed('b', ButtonType::class));
        self::assertNotInstanceOf(SubmitButton::class, $this->factory->createNamed('b', ButtonType::class));
    }

    public function testClickedButtonIsRecordedOnTheRoot(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('title', TextType::class)
            ->add('save', SubmitType::class)
            ->add('saveAndAdd', SubmitType::class)
            ->getForm();

        $form->submit(['title' => 'T', 'saveAndAdd' => '']);

        self::assertTrue($form->isSubmitted());
        self::assertTrue($form->isValid());
        self::assertSame($form->get('saveAndAdd'), $form->getClickedButton());
        self::assertTrue($form->get('saveAndAdd')->isClicked());
        self::assertFalse($form->get('save')->isClicked(), 'absent key => null => not clicked');
        self::assertTrue($form->get('save')->isSubmitted(), 'clearMissing submits absent buttons with null');
        self::assertSame(['title' => 'T'], $form->getData(), 'buttons are not mapped into the data');
        self::assertSame($form->getClickedButton(), $form->get('title')->getClickedButton(), 'children see the root\'s clicked button');
    }

    public function testNestedClickedButtonBubblesUp(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('title', TextType::class)
            ->add('address', FormType::class)
            ->getForm();
        $form->get('address')->add('zip', TextType::class)->add('lookup', SubmitType::class);

        $form->submit(['title' => 'T', 'address' => ['zip' => '1000', 'lookup' => 'Lookup']]);

        $button = $form->getClickedButton();
        self::assertInstanceOf(SubmitButton::class, $button);
        self::assertSame('lookup', $button->getName());
        self::assertSame($form->get('address')->get('lookup'), $button);
        self::assertSame($form, $button->getRoot());
        self::assertSame(['title' => 'T', 'address' => ['zip' => '1000']], $form->getData());
    }

    public function testNoClickedButtonWhenNoneWasSent(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')->add('save', SubmitType::class)->getForm();
        $form->submit([]);

        self::assertNull($form->getClickedButton());
        self::assertFalse($form->get('save')->isClicked());
    }

    public function testStandaloneButtonValidityAndSubmitSemantics(): void
    {
        $button = $this->factory->createNamed('save', SubmitType::class);

        self::assertFalse($button->isSubmitted());
        self::assertFalse($button->isValid(), 'unsubmitted => not valid');
        self::assertFalse($button->isClicked());
        self::assertTrue($button->isEmpty());
        self::assertNull($button->getData());
        self::assertSame([], $button->all());
        self::assertCount(0, $button);
        self::assertFalse($button->has('x'));
        self::assertNull($button->getPropertyPath());

        $button->submit('');

        self::assertTrue($button->isSubmitted());
        self::assertTrue($button->isClicked(), 'empty string is still a value => clicked');
        self::assertTrue($button->isValid());
        self::assertSame($button, $button->getClickedButton());

        $button->addError(new FormError('nope'));
        self::assertCount(1, $button->getErrors());
        self::assertSame($button, $button->getErrors()[0]->getOrigin());
        self::assertFalse($button->isValid(), 'an error attached to the button makes it invalid');

        $this->expectException(AlreadySubmittedException::class);
        $button->submit(null);
    }

    public function testButtonErrorsCountAgainstTheParentForm(): void
    {
        $form = $this->factory->createNamedBuilder('f')->add('save', SubmitType::class)->getForm();
        $form->submit(['save' => '']);
        $form->get('save')->addError(new FormError('bad'));

        self::assertCount(1, $form->getErrors(true));
        self::assertFalse($form->isValid());
    }

    public function testUnsubmittedButtonUnderPatchDoesNotInvalidateTheForm(): void
    {
        $form = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->add('save', SubmitType::class)->getForm();
        $form->submit(['a' => '1'], false);

        self::assertFalse($form->get('save')->isSubmitted());
        self::assertTrue($form->isValid());
    }

    public function testDisabledButtonFollowsParentAndOption(): void
    {
        $form = $this->factory->createNamedBuilder('f', FormType::class, null, ['disabled' => true])->add('save', SubmitType::class)->getForm();
        self::assertTrue($form->get('save')->isDisabled(), 'inherited from parent');

        $button = $this->factory->createNamed('save', SubmitType::class, null, ['disabled' => true]);
        self::assertTrue($button->isDisabled());
        self::assertTrue($button->getConfig()->getDisabled());
        self::assertFalse($this->factory->createNamed('save', SubmitType::class)->isDisabled());
    }

    public function testButtonRejectsDataAndChildrenOperations(): void
    {
        $button = $this->factory->createNamed('save', SubmitType::class);

        self::assertSame($button, $button->setData('ignored'), 'setData is a no-op before submit');
        self::assertNull($button->getData());

        foreach ([
            static fn (Button $b) => $b->add('x'),
            static fn (Button $b) => $b->get('x'),
            static fn (Button $b) => $b->remove('x'),
            static fn (Button $b) => $b['x'],
            static fn (Button $b) => $b->initialize(),
            static fn (Button $b) => $b->handleRequest(),
        ] as $i => $call) {
            try {
                $call($button);
                self::fail("call #$i should throw");
            } catch (BadMethodCallException) {
                $this->addToAssertionCount(1);
            }
        }
    }

    public function testButtonBuilderRestrictions(): void
    {
        $builder = $this->factory->createNamedBuilder('save', SubmitType::class, null, ['attr' => ['class' => 'btn']]);

        // Supported
        $builder->setAttribute('k', 'v')->setDisabled(true)->setAutoInitialize(false);
        self::assertSame('v', $builder->getAttribute('k'));
        self::assertTrue($builder->getDisabled());
        self::assertSame(['class' => 'btn'], $builder->getOption('attr'));
        self::assertFalse($builder->getMapped());
        self::assertFalse($builder->getCompound());
        self::assertFalse($builder->getRequired());
        self::assertFalse($builder->getAutoInitialize());
        self::assertSame([], $builder->all());
        self::assertFalse($builder->has('x'));
        self::assertCount(0, $builder);
        self::assertSame([], iterator_to_array($builder));
        self::assertInstanceOf(\Phalcon\Events\ManagerInterface::class, $builder->getEventsManager());

        // Unsupported
        foreach ([
            static fn (ButtonBuilder $b) => $b->add('x'),
            static fn (ButtonBuilder $b) => $b->create('x'),
            static fn (ButtonBuilder $b) => $b->get('x'),
            static fn (ButtonBuilder $b) => $b->remove('x'),
            static fn (ButtonBuilder $b) => $b->setAutoInitialize(true),
            static fn (ButtonBuilder $b) => $b->setData('x'),
            static fn (ButtonBuilder $b) => $b->setCompound(true),
            static fn (ButtonBuilder $b) => $b->setRequired(true),
            static fn (ButtonBuilder $b) => $b->setMapped(true),
            static fn (ButtonBuilder $b) => $b->setMethod('GET'),
            static fn (ButtonBuilder $b) => $b->addEventListener('x', static fn () => null),
            static fn (ButtonBuilder $b) => $b->getFormFactory(),
            static fn (ButtonBuilder $b) => $b->getRequestHandler(),
        ] as $i => $call) {
            try {
                $call($builder);
                self::fail("call #$i should throw");
            } catch (BadMethodCallException) {
                $this->addToAssertionCount(1);
            }
        }

        // Frozen after getForm()
        $button = $builder->getForm();
        self::assertTrue($button->getConfig()->getDisabled());
        self::assertSame('v', $button->getConfig()->getAttribute('k'));
        $builder->setDisabled(false);
        self::assertTrue($button->getConfig()->getDisabled(), 'the button holds a frozen clone, the builder stays usable');
        $frozen = $button->getConfig();
        self::assertInstanceOf(ButtonBuilder::class, $frozen);
        $this->expectException(BadMethodCallException::class);
        $frozen->setDisabled(false);
    }

    public function testButtonsCannotHaveEmptyNames(): void
    {
        $this->expectException(InvalidArgumentException::class);
        new ButtonBuilder('');
    }

    public function testButtonViewVars(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('title', TextType::class)
            ->add('save', SubmitType::class, ['label' => 'Save it', 'attr' => ['class' => 'primary'], 'priority' => -1])
            ->add('reset', ResetType::class)
            ->getForm();
        $form->submit(['title' => 'x', 'save' => '']);

        $view = $form->createView();
        $save = $view['save'];

        self::assertSame('ticket_save', $save->vars['id']);
        self::assertSame('save', $save->vars['name']);
        self::assertSame('ticket[save]', $save->vars['full_name']);
        self::assertSame('Save it', $save->vars['label']);
        self::assertSame(['class' => 'primary'], $save->vars['attr']);
        self::assertSame(['button', 'submit', '_ticket_save'], $save->vars['block_prefixes']);
        self::assertSame('_ticket_save', $save->vars['unique_block_prefix']);
        self::assertFalse($save->vars['disabled']);
        self::assertTrue($save->vars['clicked']);
        self::assertFalse($save->vars['multipart']);
        self::assertSame(['button', 'reset', '_ticket_reset'], $view['reset']->vars['block_prefixes']);
        self::assertArrayNotHasKey('clicked', $view['reset']->vars);
        self::assertSame(['title', 'reset', 'save'], array_keys($view->children), 'priority -1 sorts the button last');

        $standalone = $this->factory->createNamed('_9go', SubmitType::class)->createView();
        self::assertSame('go', $standalone->vars['id'], 'leading underscores/digits stripped from a root id');
        self::assertSame('_9go', $standalone->vars['full_name']);
        self::assertFalse($standalone->vars['clicked']);
    }
}
