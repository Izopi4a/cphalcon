<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

/** The Ticket from GitHub issue #17106: a title and a list of messages. */
final class Ticket17106
{
    public ?string $title = null;
    /** @var list<Message> */
    public array $messages = [];
}
