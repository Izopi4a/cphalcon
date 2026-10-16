<?php

declare(strict_types=1);

namespace Phalcon\VoltNfr\Cache;

/**
 * Every compiled template gets a sidecar "<compiled>.deps.php" listing the
 * files that were inlined into it (parents, embeds, static includes) with
 * their mtimes, plus a signature of the compiler configuration (runtime
 * registry, autoescape). With stat on, a compiled template is stale when any
 * dependency changed, not only the template itself.
 *
 * The sidecar is a PHP file returning an array, so opcache serves it.
 */
final class Dependencies
{
    /**
     * @param array<string, int> $files path => mtime at compile time
     */
    public static function write(string $compiledPath, array $files, string $signature): void
    {
        $data = ['files' => $files, 'signature' => $signature];
        $code = '<?php return ' . var_export($data, true) . ';' . PHP_EOL;

        file_put_contents($compiledPath . '.deps.php', $code, LOCK_EX);
    }

    /**
     * @return array{files: array<string, int>, signature: string}|null
     */
    public static function read(string $compiledPath): ?array
    {
        $file = $compiledPath . '.deps.php';
        if (!is_file($file)) {
            return null;
        }

        $data = include $file;

        return is_array($data) ? $data : null;
    }

    /**
     * Why the compiled template must be rebuilt, or null when it is fresh.
     */
    public static function staleReason(string $compiledPath, string $signature): ?string
    {
        $data = self::read($compiledPath);
        if ($data === null) {
            return 'no dependency data';
        }

        if ($data['signature'] !== $signature) {
            return 'compiler configuration changed';
        }

        foreach ($data['files'] as $file => $mtime) {
            clearstatcache(true, $file);
            if (!is_file($file) || filemtime($file) !== $mtime) {
                return 'dependency changed: ' . $file;
            }
        }

        return null;
    }
}
