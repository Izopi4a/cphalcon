<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\Transformer\CallbackTransformer;
use Phalcon\Form\Type\AbstractType;

final class TextareaType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        // Browsers submit "\r\n" line endings; store "\n". Keeps TextType's ""/null semantics.
        $builder->addViewTransformer(new CallbackTransformer(
            static fn (mixed $value): mixed => null === $value ? '' : $value,
            static fn (mixed $value): mixed => match (true) {
                '' === $value      => null,
                is_string($value)  => str_replace(["\r\n", "\r"], "\n", $value),
                default            => $value,
            },
        ));
    }

    public function getParent(): ?string
    {
        return TextType::class;
    }

    public function getBlockPrefix(): string
    {
        return 'textarea';
    }
}
