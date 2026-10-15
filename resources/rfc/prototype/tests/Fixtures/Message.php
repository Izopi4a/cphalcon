<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

final class Message
{
    public ?string $message = null;
    /** @var list<Note> */
    public array $notes = [];
}
