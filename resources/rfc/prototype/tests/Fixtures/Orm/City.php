<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures\Orm;

use Phalcon\Mvc\Model;

/**
 * cities(id, name, country_id), belongsTo Country as "country". No __toString on purpose
 * (ModelType must then require "choice_label").
 *
 * The relation is reached only through Phalcon's magic: `$city->country` goes through
 * Model::__get() (a query, or the dirty related record), `$city->country = $c` through
 * Model::__set() (stored as dirty related, saved with the city). There is no getCountry()/
 * setCountry() method, method_exists() is false for them.
 */
final class City extends Model
{
    public ?int $id = null;
    public ?string $name = null;
    public ?int $country_id = null;

    public function initialize(): void
    {
        $this->setSource('cities');
        $this->belongsTo('country_id', Country::class, 'id', ['alias' => 'country']);
    }
}
