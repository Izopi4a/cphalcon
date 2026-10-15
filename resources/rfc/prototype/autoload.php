<?php
/**
 * Prototype autoloader: Phalcon\Form\* and Phalcon\Support\PropertyAccess\* from ./src.
 * Design-validation code only, see ../17106-forms-rfc.md. Not part of the extension.
 */
declare(strict_types=1);

spl_autoload_register(static function (string $class): void {
    $prefixes = [
        // longest prefix first
        'Phalcon\\Form\\Tests\\'            => __DIR__ . '/tests/',
        'Phalcon\\Support\\PropertyAccess\\' => __DIR__ . '/src/PropertyAccess/',
        'Phalcon\\Form\\'                   => __DIR__ . '/src/Form/',
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
