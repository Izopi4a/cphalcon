<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures;

final class Address
{
    public ?string $street = null;
    private ?string $zip = null;

    public function getZip(): ?string
    {
        return $this->zip;
    }

    public function setZip(?string $zip): void
    {
        $this->zip = $zip;
    }
}
