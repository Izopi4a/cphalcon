<?php
declare(strict_types=1);

namespace Phalcon\Form\Type\Core;

use Phalcon\Form\Type\AbstractType;
use Phalcon\Form\Type\ButtonTypeInterface;

/** <button type="reset">. Never sent by browsers, so it is never clicked server side. */
class ResetType extends AbstractType implements ButtonTypeInterface
{
    public function getParent(): ?string
    {
        return ButtonType::class;
    }

    public function getBlockPrefix(): string
    {
        return 'reset';
    }
}
