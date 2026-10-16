<?php

declare(strict_types=1);

use Phalcon\Mvc\Model;

/**
 * Columns are cst_*; the application only ever sees the mapped names
 */
class Customer extends Model
{
    public ?int $id = null;
    public string $name;
    public string $email;
    public string $country;
    public ?string $createdAt = null;

    public function initialize(): void
    {
        $this->setSource('customers');
        $this->keepSnapshots(true);
        $this->useDynamicUpdate(true);
        $this->hasMany('id', Order::class, 'customerId', ['alias' => 'orders']);
    }

    public function columnMap(): array
    {
        return [
            'cst_id'         => 'id',
            'cst_name'       => 'name',
            'cst_email'      => 'email',
            'cst_country'    => 'country',
            'cst_created_at' => 'createdAt',
        ];
    }
}

class Order extends Model
{
    public ?int $id = null;
    public int $customerId;
    public string $status;
    public string $createdAt;

    public function initialize(): void
    {
        $this->setSource('orders');
        $this->belongsTo('customerId', Customer::class, 'id', ['alias' => 'customer']);
        $this->hasMany('id', OrderItem::class, 'orderId', ['alias' => 'items']);
        $this->hasManyToMany(
            'id',
            OrderItem::class,
            'orderId',
            'productId',
            Product::class,
            'id',
            ['alias' => 'products']
        );
    }

    public function columnMap(): array
    {
        return [
            'id'          => 'id',
            'customer_id' => 'customerId',
            'status'      => 'status',
            'created_at'  => 'createdAt',
        ];
    }
}

class Product extends Model
{
    public ?int $id = null;
    public string $name;
    public string $price;
    public string $attributes;

    public function initialize(): void
    {
        $this->setSource('products');
        $this->hasMany('id', OrderItem::class, 'productId', ['alias' => 'items']);
    }
}

class OrderItem extends Model
{
    public int $orderId;
    public int $productId;
    public int $quantity;
    public string $unitPrice;

    public function initialize(): void
    {
        $this->setSource('order_items');
        $this->belongsTo('orderId', Order::class, 'id', ['alias' => 'order']);
        $this->belongsTo('productId', Product::class, 'id', ['alias' => 'product']);
    }

    public function columnMap(): array
    {
        return [
            'order_id'   => 'orderId',
            'product_id' => 'productId',
            'quantity'   => 'quantity',
            'unit_price' => 'unitPrice',
        ];
    }
}
