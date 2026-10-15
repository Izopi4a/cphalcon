<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

/** Enum choices: objects, so the list falls back to index values unless "choice_value" is given. */
enum Color: string
{
    case Red   = 'red';
    case Green = 'green';
    case Blue  = 'blue';
}
