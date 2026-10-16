<?php

/**
 * Prototype autoloader: Phalcon\VoltNfr\* from ./src and ./tests.
 * Design-validation code only, see ../volt-rfc.md. Not part of the extension.
 */

declare(strict_types=1);

spl_autoload_register(static function (string $class): void {
    $prefixes = [
        // longest prefix first
        'Phalcon\\VoltNfr\\Tests\\' => __DIR__ . '/tests/',
        'Phalcon\\VoltNfr\\'        => __DIR__ . '/src/',
    ];
    foreach ($prefixes as $prefix => $dir) {
        if (str_starts_with($class, $prefix)) {
            $file = $dir . str_replace('\\', '/', substr($class, strlen($prefix))) . '.php';
            if (is_file($file)) {
                require $file;
            }

            return;
        }
    }
});
