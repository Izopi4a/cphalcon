<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures\Orm;

/**
 * Plain object holding a collection of Country models through an adder/remover pair (no
 * setter): the target of a ModelType multiple with by_reference false.
 */
final class Trip
{
    /** @var list<string> method calls, e.g. "addCountry(2)" */
    public array $calls = [];

    /** @param list<Country> $countries */
    public function __construct(private array $countries = [])
    {
    }

    /** @return list<Country> */
    public function getCountries(): array
    {
        return $this->countries;
    }

    public function addCountry(Country $country): void
    {
        $this->calls[]     = sprintf('addCountry(%d)', $country->id);
        $this->countries[] = $country;
    }

    public function removeCountry(Country $country): void
    {
        $this->calls[]   = sprintf('removeCountry(%d)', $country->id);
        $this->countries = array_values(array_filter($this->countries, static fn (Country $c): bool => $c->id !== $country->id));
    }
}
