<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests\Fixtures;

use Phalcon\Mvc\Model;
use Phalcon\NativeSql\NativeFinder;

class Orders extends Model
{
    use NativeFinder;

    public ?int $id = null;
    public ?int $user_id = null;
    public ?float $total = null;
    public ?string $created_at = null;

    public function initialize(): void
    {
        $this->setSource('orders');
        $this->belongsTo('user_id', Users::class, 'id', ['alias' => 'user']);
    }
}
