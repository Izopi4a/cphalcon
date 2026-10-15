<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests;

use Phalcon\Form\Exception\UnexpectedTypeException;
use Phalcon\Form\FormFactory;
use Phalcon\Form\FormInterface;
use Phalcon\Form\Tests\Fixtures\Message;
use Phalcon\Form\Tests\Fixtures\MessageType;
use Phalcon\Form\Tests\Fixtures\Note;
use Phalcon\Form\Tests\Fixtures\NoteType;
use Phalcon\Form\Tests\Fixtures\Ticket17106;
use Phalcon\Form\Type\Core\CollectionType;
use Phalcon\Form\Type\Core\FormType;
use Phalcon\Form\Type\Core\TextType;
use PHPUnit\Framework\TestCase;

final class CollectionTypeTest extends TestCase
{
    private FormFactory $factory;

    protected function setUp(): void
    {
        $this->factory = new FormFactory();
    }

    /** @param array<string, mixed> $options */
    private function collection(array $options = []): FormInterface
    {
        return $this->factory->createNamed('tags', CollectionType::class, null, $options);
    }

    // (a)
    public function testSetDataCreatesOneChildPerEntry(): void
    {
        $form = $this->collection();
        $form->setData(['a', 'b', 'c']);

        self::assertCount(3, $form);
        self::assertSame([0, 1, 2], array_keys($form->all()));
        foreach (['0' => 'a', '1' => 'b', '2' => 'c'] as $name => $value) {
            self::assertSame('[' . $name . ']', (string) $form->get((string) $name)->getPropertyPath());
            self::assertSame($value, $form->get((string) $name)->getViewData());
            self::assertSame('entry', $form->get((string) $name)->getConfig()->getOption('block_name'));
        }

        $form->setData(['x']);
        self::assertSame([0], array_keys($form->all()), 'resizing drops the old rows');
        self::assertSame('x', $form->get('0')->getViewData());
    }

    public function testSetDataAcceptsTraversableArrayAccess(): void
    {
        $data = new \ArrayObject(['a', 'b']);
        $form = $this->collection(['allow_add' => true]);
        $form->setData($data);
        self::assertCount(2, $form);

        $form->submit([0 => 'x', 1 => 'y', 2 => 'z']);

        self::assertSame($data, $form->getData(), 'the ArrayAccess object is written in place');
        self::assertSame(['x', 'y', 'z'], $data->getArrayCopy());
    }

    public function testSetDataRejectsScalars(): void
    {
        $this->expectException(UnexpectedTypeException::class);
        $this->collection()->setData('not a collection');
    }

    // (b)
    public function testWithoutAllowAddExtraEntriesAreIgnored(): void
    {
        $form = $this->collection();
        $form->setData(['a', 'b']);

        $form->submit([0 => 'x', 1 => 'y', 2 => 'z']);

        self::assertCount(2, $form, 'no child was created for key 2');
        self::assertSame(['x', 'y'], $form->getData(), 'the extra entry is not mapped');
        self::assertSame([2 => 'z'], $form->getExtraData(), 'same as Symfony: unmatched keys end up in extraData');
        self::assertTrue($form->isValid(), 'extra fields are a validator concern (allow_extra_fields), not a core one');
    }

    // (c)
    public function testAllowAddAddsEntries(): void
    {
        $form = $this->collection(['allow_add' => true]);
        $form->setData(['a']);

        $form->submit([0 => 'x', 1 => 'y', 2 => 'z']);

        self::assertSame([0, 1, 2], array_keys($form->all()));
        self::assertSame('[2]', (string) $form->get('2')->getPropertyPath());
        self::assertSame(['x', 'y', 'z'], $form->getData());
        self::assertSame([], $form->getExtraData());
    }

    public function testAllowAddFromNullData(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('tags', CollectionType::class, ['allow_add' => true])
            ->getForm();

        $form->submit(['tags' => ['x', 'y']]);

        self::assertSame(['tags' => ['x', 'y']], $form->getData(), 'empty_data [] of the compound collection is filled');
    }

    // (d)
    public function testAllowDeleteRemovesMissingEntriesAndTheirKeys(): void
    {
        $form = $this->collection(['allow_delete' => true]);
        $form->setData(['a', 'b', 'c']);

        $form->submit([0 => 'x', 2 => 'z']);

        self::assertFalse($form->has('1'));
        self::assertSame([0, 2], array_keys($form->all()));
        self::assertSame([0 => 'x', 2 => 'z'], $form->getData(), 'key 1 is gone, the remaining keys are untouched');
    }

    public function testWithoutAllowDeleteMissingEntriesAreNulled(): void
    {
        $form = $this->collection();
        $form->setData(['a', 'b']);

        $form->submit([0 => 'x']);

        self::assertCount(2, $form);
        self::assertSame([0 => 'x', 1 => null], $form->getData(), 'clearMissing submits null to the child, which stays');
    }

    // (e)
    public function testDeleteEmptyDropsBlankNewEntries(): void
    {
        $form = $this->collection(['allow_add' => true, 'delete_empty' => true]);
        $form->setData([]);

        $form->submit([0 => 'x', 1 => '', 2 => 'y']);

        self::assertSame([0, 2], array_keys($form->all()));
        self::assertSame([0 => 'x', 2 => 'y'], $form->getData());
    }

    public function testDeleteEmptyOnExistingEntriesNeedsAllowDelete(): void
    {
        $form = $this->collection(['delete_empty' => true]);
        $form->setData(['a', 'b']);
        $form->submit([0 => '', 1 => 'b']);
        self::assertSame([0 => null, 1 => 'b'], $form->getData(), 'existing entries are kept without allow_delete');

        $form = $this->collection(['delete_empty' => true, 'allow_delete' => true]);
        $form->setData(['a', 'b']);
        $form->submit([0 => '', 1 => 'b']);
        self::assertSame([1 => 'b'], $form->getData());
        self::assertSame([1], array_keys($form->all()));
    }

    public function testDeleteEmptyAcceptsACallable(): void
    {
        $form = $this->collection([
            'allow_add'    => true,
            'delete_empty' => static fn (?string $entry) => null === $entry || str_starts_with($entry, '-'),
        ]);
        $form->setData([]);

        $form->submit([0 => 'keep', 1 => '-drop', 2 => '']);

        self::assertSame([0 => 'keep'], $form->getData());
    }

    // (f)
    public function testKeepAsListRenumbersEntries(): void
    {
        $form = $this->collection(['allow_add' => true, 'allow_delete' => true, 'keep_as_list' => true]);
        $form->setData(['a', 'b', 'c', 'd']);

        $form->submit([0 => 'w', 2 => 'y', 5 => 'z']);

        self::assertSame(['w', 'y', 'z'], $form->getData(), 'a list again');
        self::assertSame([0, 1, 2], array_keys($form->all()), 'children renumbered with the data');
        self::assertSame('[2]', (string) $form->get('2')->getPropertyPath());
    }

    public function testKeepAsListWithDeleteEmpty(): void
    {
        $form = $this->collection(['allow_add' => true, 'delete_empty' => true, 'keep_as_list' => true]);
        $form->setData([]);

        $form->submit(['x', '', 'y']);

        self::assertSame(['x', 'y'], $form->getData());
    }

    // (g)
    public function testViewHasPrototypeAndCollectionEntryBlockPrefix(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('messages', CollectionType::class, ['allow_add' => true, 'prototype_data' => 'dflt'])
            ->getForm();
        $form->setData(['messages' => ['m0', 'm1']]);

        $view     = $form->createView();
        $messages = $view['messages'];

        self::assertTrue($messages->vars['allow_add']);
        self::assertFalse($messages->vars['allow_delete']);
        self::assertSame(['form', 'collection', '_ticket_messages'], $messages->vars['block_prefixes']);
        self::assertSame('ticket[messages]', $messages->vars['full_name']);

        self::assertCount(2, $messages);
        self::assertSame('ticket[messages][0]', $messages['0']->vars['full_name']);
        self::assertSame('ticket_messages_1', $messages['1']->vars['id']);
        self::assertSame('m1', $messages['1']->vars['value']);
        self::assertSame(
            ['form', 'collection_entry', 'text', '_ticket_messages_entry'],
            $messages['0']->vars['block_prefixes'],
            'Symfony inserts collection_entry in front of the entry type prefixes (offset -2)'
        );

        $prototype = $messages->vars['prototype'];
        self::assertSame('ticket[messages][__name__]', $prototype->vars['full_name']);
        self::assertSame('ticket_messages___name__', $prototype->vars['id']);
        self::assertSame('__name__label__', $prototype->vars['label']);
        self::assertSame('dflt', $prototype->vars['value'], 'prototype_data is the prototype value');
        self::assertSame($messages, $prototype->parent);
        self::assertSame(['form', 'collection_entry', 'text', '_ticket_messages_entry'], $prototype->vars['block_prefixes']);
        self::assertSame($form->get('messages'), $form->get('messages')->getConfig()->getAttribute('prototype')->getParent());
    }

    public function testNoPrototypeWithoutAllowAddOrWhenDisabled(): void
    {
        $view = $this->collection()->createView();
        self::assertArrayNotHasKey('prototype', $view->vars);
        self::assertFalse($this->collection()->getConfig()->hasAttribute('prototype'));

        $view = $this->collection(['allow_add' => true, 'prototype' => false])->createView();
        self::assertArrayNotHasKey('prototype', $view->vars);

        $form = $this->collection(['allow_add' => true, 'prototype_name' => '__tag__']);
        self::assertSame('tags[__tag__]', $form->createView()->vars['prototype']->vars['full_name']);
    }

    public function testEntryOptionsAndPrototypeOptions(): void
    {
        $form = $this->collection([
            'allow_add'         => true,
            'entry_options'     => ['attr' => ['class' => 'tag'], 'required' => false],
            'prototype_options' => ['attr' => ['class' => 'tag new']],
        ]);
        $form->setData(['a']);
        $form->submit([0 => 'a', 1 => 'b']);
        $view = $form->createView();

        self::assertSame(['class' => 'tag'], $view['0']->vars['attr'], 'existing entry: entry_options');
        self::assertSame(['class' => 'tag new'], $view['1']->vars['attr'], 'entry added on submit: prototype_options over entry_options');
        self::assertFalse($view['1']->vars['required'], 'entry_options still apply to added entries');
        self::assertSame(['class' => 'tag new'], $view->vars['prototype']->vars['attr']);
    }

    // (h) the exact scenario from GitHub issue #17106
    public function testIssue17106TicketWithMessagesAndNotes(): void
    {
        $form = $this->factory->createNamedBuilder('ticket', FormType::class, null, ['data_class' => Ticket17106::class])
            ->add('title', TextType::class)
            ->add('messages', CollectionType::class, [
                'entry_type' => MessageType::class,
                'allow_add'  => true,
            ])
            ->getForm();

        $form->submit([
            'title'    => 'T',
            'messages' => [
                0 => ['message' => 'm0', 'notes' => [0 => ['note' => 'n0']]],
            ],
        ]);

        self::assertTrue($form->isValid());
        $ticket = $form->getData();
        self::assertInstanceOf(Ticket17106::class, $ticket);
        self::assertSame('T', $ticket->title);
        self::assertCount(1, $ticket->messages);
        self::assertInstanceOf(Message::class, $ticket->messages[0]);
        self::assertSame('m0', $ticket->messages[0]->message);
        self::assertCount(1, $ticket->messages[0]->notes);
        self::assertInstanceOf(Note::class, $ticket->messages[0]->notes[0]);
        self::assertSame('n0', $ticket->messages[0]->notes[0]->note);

        $view = $form->createView();
        self::assertSame('ticket[title]', $view['title']->vars['full_name']);
        self::assertSame('ticket[messages][0][message]', $view['messages']['0']['message']->vars['full_name']);
        self::assertSame('ticket[messages][0][notes][0][note]', $view['messages']['0']['notes']['0']['note']->vars['full_name']);
        self::assertSame('n0', $view['messages']['0']['notes']['0']['note']->vars['value']);
        self::assertSame(
            ['form', 'collection_entry', 'message', '_ticket_messages_entry'],
            $view['messages']['0']->vars['block_prefixes']
        );
        self::assertSame(
            'ticket[messages][__name__][notes][__name__][note]',
            $view['messages']->vars['prototype']['notes']->vars['prototype']['note']->vars['full_name'],
            'nested prototypes for the JavaScript side'
        );
    }

    public function testIssue17106EditingAnExistingTicket(): void
    {
        $note          = new Note();
        $note->note    = 'old note';
        $msg           = new Message();
        $msg->message  = 'old';
        $msg->notes    = [$note];
        $ticket        = new Ticket17106();
        $ticket->title = 'T';
        $ticket->messages = [$msg];

        $form = $this->factory->createNamedBuilder('ticket', FormType::class, $ticket, ['data_class' => Ticket17106::class])
            ->add('title', TextType::class)
            ->add('messages', CollectionType::class, [
                'entry_type'   => MessageType::class,
                'allow_add'    => true,
                'allow_delete' => true,
            ])
            ->getForm();

        self::assertSame('old note', $form->get('messages')->get('0')->get('notes')->get('0')->get('note')->getViewData());

        $form->submit([
            'title'    => 'T2',
            'messages' => [
                0 => ['message' => 'edited', 'notes' => [0 => ['note' => 'edited note'], 1 => ['note' => 'added note']]],
                1 => ['message' => 'second', 'notes' => []],
            ],
        ]);

        self::assertSame($ticket, $form->getData());
        self::assertSame($msg, $ticket->messages[0], 'existing message kept by reference');
        self::assertSame('edited', $msg->message);
        self::assertSame($note, $msg->notes[0]);
        self::assertSame('edited note', $note->note);
        self::assertSame('added note', $msg->notes[1]->note);
        self::assertSame('second', $ticket->messages[1]->message);
        self::assertSame([], $ticket->messages[1]->notes);

        // Second round: a message is removed.
        $form = $this->factory->createNamedBuilder('ticket', FormType::class, $ticket, ['data_class' => Ticket17106::class])
            ->add('messages', CollectionType::class, ['entry_type' => MessageType::class, 'allow_delete' => true])
            ->getForm();
        $form->submit(['messages' => [1 => ['message' => 'second', 'notes' => []]]]);

        self::assertSame([1], array_keys($ticket->messages));
    }

    // (i)
    public function testCompoundEntriesWithoutDataClassRoundTripAsArrays(): void
    {
        $form = $this->factory->createNamedBuilder('ticket')
            ->add('notes', CollectionType::class, [
                'entry_type'    => NoteType::class,
                'entry_options' => ['data_class' => null],
                'allow_add'     => true,
                'allow_delete'  => true,
            ])
            ->getForm();
        $form->setData(['notes' => [['note' => 'a'], ['note' => 'b'], ['note' => 'c']]]);

        self::assertSame('b', $form->get('notes')->get('1')->get('note')->getViewData());
        self::assertSame('[note]', (string) $form->get('notes')->get('1')->get('note')->getPropertyPath());

        $form->submit(['notes' => [0 => ['note' => 'A'], 2 => ['note' => 'C'], 3 => ['note' => 'D']]]);

        self::assertTrue($form->isValid());
        self::assertSame(
            ['notes' => [0 => ['note' => 'A'], 2 => ['note' => 'C'], 3 => ['note' => 'D']]],
            $form->getData()
        );
        self::assertSame('ticket[notes][3][note]', $form->createView()['notes']['3']['note']->vars['full_name']);
    }
}
