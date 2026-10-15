<?php
declare(strict_types=1);

namespace Phalcon\Form;

/** Implemented by submit buttons so the root form can report which one was clicked. */
interface ClickableInterface
{
    public function isClicked(): bool;
}
