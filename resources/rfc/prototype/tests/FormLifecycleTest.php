<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\Event\FormEvent;
use Phalcon\Form\Event\FormEvents;
use Phalcon\Form\Exception\AlreadySubmittedException;
use Phalcon\Form\FormError;
use Phalcon\Form\FormFactory;
use Phalcon\Form\Tests\Fixtures\Address;
use Phalcon\Form\Tests\Fixtures\Ticket;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\TextType;
use PHPUnit\Framework\TestCase;

final class FormLifecycleTest extends TestCase
{
    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    public function testNestedArrayDataRoundTrip(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('title', TextType::class)
            ->add('address', FormType::class)
            ->getForm();
        $form->get('address')->add('street', TextType::class)->add('zip', TextType::class);

        $form->setData(['title' => 'Old', 'address' => ['street' => 'Main', 'zip' => '1000']]);
        self::assertSame('Old', $form->get('title')->getViewData());
        self::assertSame('1000', $form->get('address')->get('zip')->getViewData());

        $form->submit(['title' => ' New ', 'address' => ['street' => '', 'zip' => '2000'], 'extra' => 'x']);

        self::assertTrue($form->isSubmitted());
        self::assertTrue($form->isValid());
        self::assertSame(['extra' => 'x'], $form->getExtraData());
        self::assertSame(
            ['title' => 'New', 'address' => ['street' => null, 'zip' => '2000']],
            $form->getData(),
            'trim applied, "" became null (#17338), nested array mapped back'
        );
    }

    public function testObjectGraphRoundTripWithSetterAndPublicProperty(): void
    {
        $ticket          = new Ticket();
        $ticket->title   = 'Old';
        $ticket->address = new Address();
        $ticket->address->setZip('1000');

        $form = $this->factory->createNamedBuilder('ticket', FormType::class, $ticket, ['data_class' => Ticket::class])
            ->add('title', TextType::class)
            ->add('address', FormType::class, ['data_class' => Address::class])
            ->getForm();
        $form->get('address')->add('street', TextType::class)->add('zip', TextType::class);

        self::assertSame('1000', $form->get('address')->get('zip')->getViewData(), 'getter used for reading');

        $form->submit(['title' => 'New', 'address' => ['street' => 'Side', 'zip' => '2000']]);

        self::assertSame($ticket, $form->getData(), 'by_reference keeps identity');
        self::assertSame('New', $ticket->title);
        self::assertSame('Side', $ticket->address->street, 'public property written');
        self::assertSame('2000', $ticket->address->getZip(), 'setter used for writing');
    }

    public function testEmptyDataCreatesObjectForNestedForm(): void
    {
        $form = $this->factory->createNamedBuilder('ticket', FormType::class, null, ['data_class' => Ticket::class])
            ->add('title', TextType::class)
            ->add('address', FormType::class, ['data_class' => Address::class])
            ->getForm();
        $form->get('address')->add('zip', TextType::class);

        $form->submit(['title' => 'T', 'address' => ['zip' => '9']]);

        $ticket = $form->getData();
        self::assertInstanceOf(Ticket::class, $ticket);
        self::assertInstanceOf(Address::class, $ticket->address);
        self::assertSame('9', $ticket->address->getZip());
    }

    public function testEventOrderOnSetDataAndSubmit(): void
    {
        $log     = [];
        $builder = $this->factory->createNamedBuilder('f')->add('a', TextType::class);
        foreach ([FormEvents::PRE_SET_DATA, FormEvents::POST_SET_DATA, FormEvents::PRE_SUBMIT, FormEvents::SUBMIT, FormEvents::POST_SUBMIT] as $name) {
            $builder->addEventListener($name, static function (FormEvent $e) use (&$log, $name): void {
                $log[] = $name;
            });
        }
        $builder->get('a')->addEventListener(FormEvents::POST_SUBMIT, static function (FormEvent $e) use (&$log): void {
            $log[] = 'child:' . FormEvents::POST_SUBMIT;
        });

        $form = $builder->getForm();   // auto_initialize fires the *SetData events
        $form->submit(['a' => '1']);

        self::assertSame([
            'form:preSetData', 'form:postSetData',
            'form:preSubmit', 'child:form:postSubmit', 'form:submit', 'form:postSubmit',
        ], $log, 'children finish before the parent transforms');
    }

    public function testPreSubmitListenerCanReplaceDataAndPriorityIsHonoured(): void
    {
        $builder = $this->factory->createNamedBuilder('f')->add('a', TextType::class);
        $builder->addEventListener(FormEvents::PRE_SUBMIT, static fn (FormEvent $e) => $e->setData(['a' => $e->getData()['a'] . '-low']), 10);
        $builder->addEventListener(FormEvents::PRE_SUBMIT, static fn (FormEvent $e) => $e->setData(['a' => $e->getData()['a'] . '-high']), 200);
        $form = $builder->getForm();

        $form->submit(['a' => 'x']);

        self::assertSame(['a' => 'x-high-low'], $form->getData(), 'higher priority runs first');
    }

    public function testListenersWithEqualPriorityRunInInsertionOrder(): void
    {
        // Phalcon's Events\Manager (SplPriorityQueue) does not guarantee this on its own.
        $builder = $this->factory->createNamedBuilder('f')->add('a', TextType::class);
        for ($i = 1; $i <= 8; ++$i) {
            $builder->addEventListener(FormEvents::PRE_SUBMIT, static fn (FormEvent $e) => $e->setData(['a' => $e->getData()['a'] . $i]));
        }
        $form = $builder->getForm();

        $form->submit(['a' => '']);

        self::assertSame(['a' => '12345678'], $form->getData());
    }

    public function testErrorBubblingDefaults(): void
    {
        $form = $this->factory->createNamedBuilder('f')
            ->add('leaf', TextType::class)
            ->add('group', FormType::class)
            ->getForm();
        $form->get('group')->add('inner', TextType::class);
        $form->submit(['leaf' => '1', 'group' => ['inner' => '2']]);

        $form->get('leaf')->addError(new FormError('leaf error'));
        $form->get('group')->addError(new FormError('group error'));
        $form->get('group')->get('inner')->addError(new FormError('inner error'));

        self::assertCount(1, $form->get('leaf')->getErrors(), 'leaf keeps its own error');
        self::assertCount(1, $form->get('group')->get('inner')->getErrors());
        self::assertCount(1, $form->getErrors(), 'compound child bubbles to root');
        self::assertSame('group error', (string) $form->getErrors()[0]);
        self::assertCount(3, $form->getErrors(true));
        self::assertFalse($form->isValid());
        self::assertSame($form->get('leaf'), $form->get('leaf')->getErrors()[0]->getOrigin());
    }

    public function testDataOptionLocksAgainstParentData(): void
    {
        $form = $this->factory->createNamedBuilder('f')
            ->add('a', TextType::class, ['data' => 'fixed'])
            ->add('b', TextType::class)
            ->getForm();
        $form->setData(['a' => 'from-parent', 'b' => 'from-parent']);

        self::assertSame('fixed', $form->get('a')->getData());
        self::assertSame('from-parent', $form->get('b')->getData());
    }

    public function testInheritDataGroupsFieldsOfTheParentObject(): void
    {
        $ticket        = new Ticket();
        $ticket->title = 'T';

        $builder = $this->factory->createNamedBuilder('ticket', FormType::class, $ticket, ['data_class' => Ticket::class])
            ->add('meta', FormType::class, ['inherit_data' => true]);
        $builder->get('meta')->add('title', TextType::class);
        $form = $builder->getForm();

        self::assertSame('T', $form->get('meta')->get('title')->getViewData());
        $form->submit(['meta' => ['title' => 'U']]);
        self::assertSame('U', $ticket->title);
    }

    public function testClearMissingFalseKeepsUnsubmittedChildren(): void
    {
        $form = $this->factory->createNamedBuilder('f')->add('a', TextType::class)->add('b', TextType::class)->getForm();
        $form->setData(['a' => '1', 'b' => '2']);

        $form->submit(['a' => '9'], false);

        self::assertSame(['a' => '9', 'b' => '2'], $form->getData(), 'PATCH semantics');
        self::assertFalse($form->get('b')->isSubmitted());
    }

    public function testSubmitTwiceThrows(): void
    {
        $form = $this->factory->createNamed('f')->submit([]);
        $this->expectException(AlreadySubmittedException::class);
        $form->submit([]);
    }

    public function testViewTreeNamesAndBlockPrefixes(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')->add('address', FormType::class)->getForm();
        $form->get('address')->add('zip', TextType::class);
        $form->submit(['address' => ['zip' => '1']]);

        $view = $form->createView();

        self::assertSame('ticket', $view->vars['full_name']);
        self::assertSame('ticket[address]', $view['address']->vars['full_name']);
        self::assertSame('ticket[address][zip]', $view['address']['zip']->vars['full_name']);
        self::assertSame('ticket_address_zip', $view['address']['zip']->vars['id']);
        self::assertSame(['form', 'text', '_ticket_address_zip'], $view['address']['zip']->vars['block_prefixes']);
        self::assertSame('1', $view['address']['zip']->vars['value']);
        self::assertTrue($view->vars['compound']);
        self::assertFalse($view['address']['zip']->vars['compound']);
    }

    public function testAdderRemoverCollectionWriteThroughPropertyAccess(): void
    {
        $ticket = new Ticket();
        $ticket->addTag('keep');
        $ticket->addTag('drop');

        $form = $this->factory->createNamedBuilder('ticket', FormType::class, $ticket, ['data_class' => Ticket::class])
            ->add('tags', FormType::class, ['by_reference' => false])
            ->getForm();
        $form->get('tags')->add('0', TextType::class)->add('1', TextType::class);

        self::assertSame('keep', $form->get('tags')->get('0')->getViewData());
        $form->submit(['tags' => ['0' => 'keep', '1' => 'new']]);

        self::assertSame(['keep', 'new'], $ticket->getTags(), 'removeTag("drop") + addTag("new") were called');
    }
}
