<?php
declare(strict_types=1);

namespace Phalcon\Form\Type;

use Phalcon\Form\EventListener\TransformationFailureListener;
use Phalcon\Form\FormBuilderInterface;
use Phalcon\Form\Type\Core\FormType;

/**
 * Registers the TransformationFailureListener on every form that has no "constraints" option,
 * i.e. whenever the validation bridge is not responsible for reporting the failure.
 */
final class TransformationFailureExtension extends AbstractTypeExtension
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        if (!isset($options['constraints']) || !$options['constraints']) {
            $builder->addEventSubscriber(new TransformationFailureListener());
        }
    }

    public static function getExtendedTypes(): iterable
    {
        return [FormType::class];
    }
}
