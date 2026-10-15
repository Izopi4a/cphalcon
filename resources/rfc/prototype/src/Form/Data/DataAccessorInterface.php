<?php
declare(strict_types=1);

namespace Phalcon\Form\Data;

use Phalcon\Form\FormInterface;

interface DataAccessorInterface
{
    public function getValue(object|array $viewData, FormInterface $form): mixed;

    public function setValue(object|array &$viewData, mixed $value, FormInterface $form): void;

    public function isReadable(object|array $viewData, FormInterface $form): bool;

    public function isWritable(object|array $viewData, FormInterface $form): bool;
}
