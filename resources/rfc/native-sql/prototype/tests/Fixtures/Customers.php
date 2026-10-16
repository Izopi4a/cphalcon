<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests\Fixtures;

use Phalcon\Mvc\Model;
use Phalcon\NativeSql\NativeFinder;

/**
 * Model with a columnMap: PHQL conditions use the property names (id, name, createdAt) and the
 * parser-driven core rewrites them to the real columns (cst_id, cst_name, cst_created).
 */
class Customers extends Model
{
    use NativeFinder;

    public ?int $id = null;
    public ?string $name = null;
    public ?string $createdAt = null;

    public function initialize(): void
    {
        $this->setSource('customers');
    }

    public function columnMap(): array
    {
        return [
            'cst_id'      => 'id',
            'cst_name'    => 'name',
            'cst_created' => 'createdAt',
        ];
    }
}
