<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\Type\Core\CollectionType;
use Phalcon\Form\Type\Core\TextType;

/** Entry type of the #17106 "messages" collection; itself contains a "notes" collection. */
final class MessageType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->add('message', TextType::class)
            ->add('notes', CollectionType::class, [
                'entry_type' => NoteType::class,
                'allow_add'  => true,
            ]);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefault('data_class', Message::class);
    }
}
