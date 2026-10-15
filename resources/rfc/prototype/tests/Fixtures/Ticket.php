<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

final class Ticket
{
    public ?string $title = null;
    public ?Address $address = null;
    /** @var list<string> */
    private array $tags = [];

    public function getTags(): array
    {
        return $this->tags;
    }

    public function addTag(string $tag): void
    {
        $this->tags[] = $tag;
    }

    public function removeTag(string $tag): void
    {
        $this->tags = array_values(array_filter($this->tags, static fn ($t) => $t !== $tag));
    }
}
