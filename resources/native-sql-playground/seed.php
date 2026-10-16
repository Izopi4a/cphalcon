<?php

/**
 * (Re)creates the schema and fills it with deterministic data:
 * 40 customers, 12 products, ~250 orders over the last 120 days.
 */

declare(strict_types=1);

require __DIR__ . '/bootstrap.php';

$di = spinDi();
$db = $di->getShared('db');
SqlLog::$enabled = false;

$db->execute(file_get_contents(__DIR__ . '/schema.sql'));

mt_srand(17);

$first     = ['Ana', 'Boris', 'Cleo', 'Dimitar', 'Elena', 'Filip', 'Gergana', 'Hristo', 'Iva', 'Kalin', 'Lora', 'Martin', 'Nina', 'Ognyan', 'Petya', 'Radoslav', 'Sofia', 'Todor', 'Vera', 'Yana'];
$last      = ['Ivanova', 'Petrov', 'Georgieva', 'Dimitrov', 'Koleva', 'Stoyanov', 'Nikolova', 'Angelov'];
$countries = ['BG', 'BG', 'BG', 'DE', 'DE', 'US', 'FR', 'GR'];

for ($i = 1; $i <= 40; $i++) {
    $name = $first[($i - 1) % count($first)] . ' ' . $last[mt_rand(0, count($last) - 1)];
    $db->execute(
        'INSERT INTO customers (cst_name, cst_email, cst_country, cst_created_at) VALUES (?, ?, ?, now() - make_interval(days => ?))',
        [$name, 'customer' . $i . '@example.com', $countries[mt_rand(0, count($countries) - 1)], mt_rand(10, 400)]
    );
}

$products = [
    ['Espresso machine', 389.00, ['color' => 'black', 'brand' => 'Rancilio', 'warranty' => 2]],
    ['Grinder', 179.50, ['color' => 'silver', 'brand' => 'Eureka', 'warranty' => 1]],
    ['Milk jug', 18.90, ['color' => 'silver', 'size' => '600ml']],
    ['Tamper', 29.00, ['color' => 'black', 'size' => '58mm']],
    ['Scale', 54.00, ['color' => 'black', 'brand' => 'Timemore']],
    ['Beans Ethiopia 1kg', 32.00, ['origin' => 'Ethiopia', 'roast' => 'light']],
    ['Beans Brazil 1kg', 24.00, ['origin' => 'Brazil', 'roast' => 'medium']],
    ['Beans Colombia 1kg', 27.00, ['origin' => 'Colombia', 'roast' => 'medium']],
    ['Cups (set of 6)', 36.00, ['color' => 'white']],
    ['Descaler', 12.50, []],
    ['Knock box', 22.00, ['color' => 'black']],
    ['Kettle', 89.00, ['color' => 'white', 'brand' => 'Fellow', 'warranty' => 1]],
];
foreach ($products as [$name, $price, $attributes]) {
    $db->execute(
        'INSERT INTO products (name, price, attributes) VALUES (?, ?, ?::jsonb)',
        [$name, $price, json_encode($attributes)]
    );
}

$statuses = ['paid', 'paid', 'paid', 'shipped', 'shipped', 'pending', 'cancelled'];
for ($o = 1; $o <= 250; $o++) {
    $db->execute(
        "INSERT INTO orders (customer_id, status, created_at) VALUES (?, ?, now() - make_interval(days => ?, hours => ?))",
        [mt_rand(1, 40), $statuses[mt_rand(0, count($statuses) - 1)], mt_rand(0, 120), mt_rand(0, 23)]
    );
    $picked = array_rand(range(1, count($products)), mt_rand(1, 4));
    foreach ((array) $picked as $index) {
        $productId = $index + 1;
        $db->execute(
            'INSERT INTO order_items (order_id, product_id, quantity, unit_price) VALUES (?, ?, ?, ?)',
            [$o, $productId, mt_rand(1, 3), $products[$index][1]]
        );
    }
}

foreach (['customers', 'products', 'orders', 'order_items'] as $table) {
    printf("%-12s %d rows\n", $table, $db->fetchColumn("SELECT COUNT(*) FROM $table"));
}
