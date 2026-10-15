<?php
declare(strict_types=1);

namespace Phalcon\Form\Tests\Fixtures\Orm;

use Phalcon\Mvc\Model;

/**
 * countries(id, name, continent), hasMany cities. Has a __toString (the ModelType default label)
 * and a getter (getLabel) besides the public typed attributes.
 *
 * Public nullable typed properties with a null default: Phalcon hydrates them directly, the
 * metadata comes from the table (Introspection strategy), and readAttribute()/the
 * PropertyAccessor read them as public properties.
 */
final class Country extends Model
{
    public ?int $id = null;
    public ?string $name = null;
    public ?string $continent = null;

    public function initialize(): void
    {
        $this->setSource('countries');
        $this->hasMany('id', City::class, 'country_id', ['alias' => 'cities']);
    }

    public function getLabel(): string
    {
        return sprintf('%s (%s)', $this->name, $this->continent);
    }

    public function __toString(): string
    {
        return (string) $this->name;
    }
}
