<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

/** Model behind a select: a scalar property (collapsed single) and an array one (multiple). */
final class Profile
{
    public ?string $country = null;
    /** @var list<string> */
    public array $colors = [];
    private ?Country $homeland = null;

    public function getHomeland(): ?Country
    {
        return $this->homeland;
    }

    public function setHomeland(?Country $homeland): void
    {
        $this->homeland = $homeland;
    }
}
