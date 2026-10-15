<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\Options\OptionsResolver;
use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\Type\Core\TextType;

final class NoteType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder->add('note', TextType::class);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefault('data_class', Note::class);
    }
}
