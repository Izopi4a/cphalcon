<?php
declare(strict_types=1);

namespace Phalcon\Form;

interface ClearableErrorsInterface
{
    public function clearErrors(bool $deep = false): static;
}
