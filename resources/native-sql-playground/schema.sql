-- native-sql-spin: a small shop on PostgreSQL
DROP TABLE IF EXISTS order_items, orders, products, customers CASCADE;

-- prefixed columns on purpose: the model maps them (columnMap)
CREATE TABLE customers (
    cst_id         serial PRIMARY KEY,
    cst_name       text        NOT NULL,
    cst_email      text        NOT NULL UNIQUE,
    cst_country    char(2)     NOT NULL,
    cst_created_at timestamptz NOT NULL DEFAULT now()
);

CREATE TABLE products (
    id         serial PRIMARY KEY,
    name       text          NOT NULL,
    price      numeric(10,2) NOT NULL,
    attributes jsonb         NOT NULL DEFAULT '{}'
);

CREATE TABLE orders (
    id          serial PRIMARY KEY,
    customer_id int         NOT NULL REFERENCES customers (cst_id),
    status      text        NOT NULL,
    created_at  timestamptz NOT NULL
);

CREATE TABLE order_items (
    order_id   int           NOT NULL REFERENCES orders (id),
    product_id int           NOT NULL REFERENCES products (id),
    quantity   int           NOT NULL,
    unit_price numeric(10,2) NOT NULL,
    PRIMARY KEY (order_id, product_id)
);

CREATE INDEX orders_customer_idx ON orders (customer_id);
CREATE INDEX orders_created_idx ON orders (created_at);
