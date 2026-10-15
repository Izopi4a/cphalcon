<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

/** Collection property with adder/remover only (no setter): the PropertyAccessor must diff. */
final class Post
{
    /** @var list<string> method calls, e.g. "addTag(php)" */
    public array $calls = [];

    /** @param array<int|string, string> $tags */
    public function __construct(private array $tags = [])
    {
    }

    public function getTags(): array
    {
        return $this->tags;
    }

    public function addTag(string $tag): void
    {
        $this->calls[] = "addTag($tag)";
        $this->tags[]  = $tag;
    }

    public function removeTag(string $tag): void
    {
        $this->calls[] = "removeTag($tag)";
        $this->tags    = array_filter($this->tags, static fn (string $t): bool => $t !== $tag);
    }
}
