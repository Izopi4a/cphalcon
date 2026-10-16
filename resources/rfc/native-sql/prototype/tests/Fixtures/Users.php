<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests\Fixtures;

use Phalcon\Mvc\Model;
use Phalcon\NativeSql\NativeFinder;

/**
 * Plain model: property names equal column names.
 */
class Users extends Model
{
    use NativeFinder;

    public ?int $id = null;
    public ?string $name = null;
    public ?string $email = null;
    public ?string $country = null;
    public ?int $active = null;
    public ?string $created_at = null;

    public function initialize(): void
    {
        $this->setSource('users');
        $this->hasMany('id', Orders::class, 'user_id', ['alias' => 'orders']);
    }
}
