<?php

/**
 * The scenarios: each one is a closure, run once on the PHQL path and once
 * on the native compiler (orm.native_compiler). "api" scenarios use the new
 * native SQL API, which does not depend on the switch.
 */

declare(strict_types=1);

use Phalcon\Paginator\Adapter\QueryBuilder as QueryBuilderPaginator;

return [
    // ------------------------------------------------------------------ both
    [
        'group' => 'Works on both paths',
        'title' => 'find() with a bound condition, order and limit (columnMap model)',
        'run'   => fn ($di) => Customer::find([
            'country = :country:',
            'bind'  => ['country' => 'BG'],
            'order' => 'name',
            'limit' => 5,
        ]),
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'findFirst() by primary key, magic findFirstBy*()',
        'run'   => fn ($di) => [
            'findFirst(7)'           => Customer::findFirst(7),
            'findFirstByEmail(...)'  => Customer::findFirstByEmail('customer3@example.com'),
        ],
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'Array placeholder {statuses:array}',
        'run'   => fn ($di) => Order::find([
            'status IN ({statuses:array})',
            'bind'  => ['statuses' => ['pending', 'cancelled']],
            'order' => 'id DESC',
            'limit' => 5,
        ]),
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'Aggregates: count(), count() grouped, sum()',
        'run'   => fn ($di) => [
            'count()'         => Order::count(),
            'count(group)'    => Order::count(['group' => 'status', 'order' => 'rowcount DESC']),
            'sum(quantity)'   => OrderItem::sum(['column' => 'quantity']),
        ],
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'ILIKE',
        'run'   => fn ($di) => Customer::find([
            'name ILIKE :q:',
            'bind'  => ['q' => 'an%'],
            'order' => 'id',
        ]),
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'Relations: hasMany, count, many-to-many',
        'run'   => function ($di) {
            $customer = Customer::findFirst(5);
            $order    = Order::findFirst(['order' => 'id']);

            return [
                'customer'          => $customer->name,
                'countOrders()'     => $customer->countOrders(),
                'orders (statuses)' => array_column($customer->getOrders(['order' => 'id'])->toArray(), 'status'),
                'order 1 products'  => array_column($order->getProducts(['order' => 'name'])->toArray(), 'name'),
            ];
        },
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'Builder: explicit joins, multi-model result (c.*, o.*)',
        'run'   => function ($di) {
            $rows = $di->getShared('modelsManager')->createBuilder()
                ->columns('c.*, o.*')
                ->from(['c' => Customer::class])
                ->join(Order::class, 'o.customerId = c.id', 'o')
                ->where('c.id = :id:', ['id' => 3])
                ->orderBy('o.id')
                ->getQuery()
                ->execute();

            $out = [];
            foreach ($rows as $row) {
                $out[] = $row->c->name . ' / order #' . $row->o->id . ' ' . $row->o->status;
            }

            return $out;
        },
    ],
    [
        'group' => 'Works on both paths',
        'title' => 'Paginator\Adapter\QueryBuilder, page 2',
        'run'   => fn ($di) => (new QueryBuilderPaginator([
            'builder' => $di->getShared('modelsManager')->createBuilder()
                ->from(Order::class)
                ->where('status = :s:', ['s' => 'paid'])
                ->orderBy('id'),
            'limit'   => 5,
            'page'    => 2,
        ]))->paginate(),
    ],

    // --------------------------------------------------------------- refused
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => "INTERVAL arithmetic",
        'run'   => fn ($di) => Order::find([
            "createdAt > NOW() - INTERVAL '3 days'",
            'order' => 'createdAt DESC',
        ]),
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => 'PostgreSQL cast ::text',
        'run'   => fn ($di) => Customer::find([
            "id::text LIKE '1%'",
            'order' => 'id',
        ]),
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => 'JSONB ->> and @> with a bound value',
        'run'   => fn ($di) => [
            "attributes->>'color'" => Product::find([
                "attributes->>'color' = :color:",
                'bind'  => ['color' => 'black'],
                'order' => 'price DESC',
            ]),
            'attributes @> CAST(:attr: AS jsonb)' => Product::find([
                'attributes @> CAST(:attr: AS jsonb)',
                'bind' => ['attr' => '{"roast": "medium"}'],
            ]),
        ],
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => 'Searched CASE in ORDER BY',
        'run'   => fn ($di) => Customer::find([
            'order' => "CASE WHEN country = 'BG' THEN 0 ELSE 1 END, name",
            'limit' => 6,
        ]),
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => 'Window function in columns (rows, mapped names)',
        'run'   => fn ($di) => Order::find([
            'columns'    => 'id, customerId, status, ROW_NUMBER() OVER (PARTITION BY customer_id ORDER BY created_at DESC) AS nth',
            'conditions' => 'customerId <= 2',
            'order'      => 'customerId, nth',
        ]),
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => 'UNION inside a subquery',
        'run'   => fn ($di) => Customer::find([
            'id IN (SELECT customer_id FROM orders WHERE status = :status: UNION SELECT :vip:)',
            'bind'  => ['status' => 'cancelled', 'vip' => 1],
            'order' => 'id',
        ]),
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => "date_trunc() in columns and GROUP BY",
        'run'   => fn ($di) => Order::find([
            'columns' => "date_trunc('week', created_at)::date AS week, COUNT(*) AS orders",
            'group'   => "date_trunc('week', created_at)",
            'order'   => 'week DESC',
            'limit'   => 4,
        ]),
    ],
    [
        'group' => 'PHQL refuses or miscompiles, native passes it through',
        'title' => 'Builder: implicit join through a joined model (Customer -> Order -> OrderItem)',
        'run'   => fn ($di) => $di->getShared('modelsManager')->createBuilder()
            ->columns('[Customer].country, SUM([OrderItem].quantity * [OrderItem].unitPrice) AS revenue')
            ->from(Customer::class)
            ->join(Order::class)
            ->join(OrderItem::class)
            ->groupBy('[Customer].country')
            ->orderBy('revenue DESC')
            ->getQuery()
            ->execute(),
    ],

    // ------------------------------------------------------------ native API
    [
        'group' => 'New native SQL API',
        'api'   => true,
        'title' => 'Model::findBySql(): DISTINCT ON, best customer per country, as models',
        'run'   => fn ($di) => Customer::findBySql(
            'SELECT DISTINCT ON (c.cst_country) c.*
               FROM customers c
               JOIN orders o      ON o.customer_id = c.cst_id
               JOIN order_items i ON i.order_id = o.id
              WHERE o.status <> :cancelled
              GROUP BY c.cst_id
              ORDER BY c.cst_country, SUM(i.quantity * i.unit_price) DESC',
            ['cancelled' => 'cancelled']
        ),
    ],
    [
        'group' => 'New native SQL API',
        'api'   => true,
        'title' => 'findFirstBySql() then save(): snapshots and dynamic update still work',
        'run'   => function ($di) {
            $customer = Customer::findFirstBySql(
                'SELECT * FROM customers WHERE cst_email = :email',
                ['email' => 'customer2@example.com']
            );
            $original       = $customer->name;
            $customer->name = $original . ' (edited)';
            $changed        = $customer->getChangedFields();
            $customer->save();
            $saved          = Customer::findFirst($customer->id)->name;
            $customer->name = $original;
            $customer->save();

            return ['changed fields' => $changed, 'saved name' => $saved, 'restored' => $original];
        },
    ],
    [
        'group' => 'New native SQL API',
        'api'   => true,
        'title' => 'Manager::nativeQuery(): daily revenue for 14 days, generate_series keeps empty days',
        'run'   => fn ($di) => $di->getShared('modelsManager')->nativeQuery(
            "WITH days AS (
                SELECT generate_series(current_date - 13, current_date, interval '1 day')::date AS day
             )
             SELECT d.day, COUNT(DISTINCT o.id) AS orders, COALESCE(SUM(i.quantity * i.unit_price), 0) AS revenue
               FROM days d
               LEFT JOIN orders o      ON o.created_at::date = d.day AND o.status <> 'cancelled'
               LEFT JOIN order_items i ON i.order_id = o.id
              GROUP BY d.day
              ORDER BY d.day DESC"
        ),
    ],
    [
        'group' => 'New native SQL API',
        'api'   => true,
        'title' => 'nativeQuery(): RANK() and json_agg() per customer',
        'run'   => fn ($di) => $di->getShared('modelsManager')->nativeQuery(
            'SELECT c.cst_name AS name,
                    SUM(i.quantity * i.unit_price) AS lifetime,
                    RANK() OVER (ORDER BY SUM(i.quantity * i.unit_price) DESC) AS rank,
                    json_agg(DISTINCT o.status) AS statuses
               FROM customers c
               JOIN orders o      ON o.customer_id = c.cst_id
               JOIN order_items i ON i.order_id = o.id
              GROUP BY c.cst_id
              ORDER BY rank
              LIMIT :top',
            ['top' => 5]
        ),
    ],
    [
        'group' => 'New native SQL API',
        'api'   => true,
        'title' => 'nativeQuery(): LATERAL, the latest order of each German customer',
        'run'   => fn ($di) => $di->getShared('modelsManager')->nativeQuery(
            "SELECT c.cst_name AS name, last.id AS order_id, last.status, last.created_at::date AS day
               FROM customers c
               CROSS JOIN LATERAL (
                    SELECT o.* FROM orders o WHERE o.customer_id = c.cst_id ORDER BY o.created_at DESC LIMIT 1
               ) last
              WHERE c.cst_country = 'DE'
              ORDER BY last.created_at DESC"
        ),
    ],
    [
        'group' => 'New native SQL API',
        'api'   => true,
        'title' => 'nativeQuery(): upsert with RETURNING',
        'run'   => fn ($di) => $di->getShared('modelsManager')->nativeQuery(
            'INSERT INTO order_items (order_id, product_id, quantity, unit_price)
             VALUES (:order, :product, 1, 389.00)
             ON CONFLICT (order_id, product_id) DO UPDATE SET quantity = order_items.quantity
             RETURNING order_id, product_id, quantity, (xmax = 0) AS inserted',
            ['order' => 1, 'product' => 1]
        ),
    ],
];
