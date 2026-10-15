<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

/** Entity-like choice with getters, for "choice_label"/"choice_value" property paths. */
final class Country
{
    public function __construct(
        private readonly int $id,
        private readonly string $name,
        public readonly string $continent = 'Europe',
        public readonly bool $featured = false,
    ) {
    }

    public function getId(): int
    {
        return $this->id;
    }

    public function getName(): string
    {
        return $this->name;
    }
}
