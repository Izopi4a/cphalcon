
/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Mvc\View\Engine\Volt;

/**
 * Every compiled template gets a sidecar "<compiled>.deps.php" listing the
 * files inlined into it (parents, embeds, static includes) with their mtimes,
 * plus a signature of the compiler configuration (runtime registry,
 * autoescape, strict tests). With "stat" on, a compiled template is stale when
 * any of them changed, not only the template itself.
 *
 * The sidecar is a PHP file returning an array, so opcache serves it.
 */
class Dependencies
{
    /**
     * @return array|null ["files" => [path => mtime], "signature" => string]
     */
    public static function read(string compiledPath) -> array | null
    {
        var file, data;

        let file = compiledPath . ".deps.php";

        if !is_file(file) {
            return null;
        }

        let data = require file;

        if typeof data != "array" {
            return null;
        }

        return data;
    }

    /**
     * Why the compiled template must be rebuilt, or null when it is fresh
     */
    public static function staleReason(string compiledPath, string signature) -> string | null
    {
        var data, files, file, mtime, storedSignature;

        let data = self::read(compiledPath);

        if data === null {
            return "no dependency data";
        }

        if !fetch storedSignature, data["signature"] || storedSignature !== signature {
            return "compiler configuration changed";
        }

        if !fetch files, data["files"] || typeof files != "array" {
            return "no dependency data";
        }

        for file, mtime in files {
            clearstatcache(true, file);

            if !is_file(file) || filemtime(file) !== mtime {
                return "dependency changed: " . file;
            }
        }

        return null;
    }

    /**
     * @param array files path => mtime at compile time
     */
    public static function write(string compiledPath, array files, string signature) -> void
    {
        file_put_contents(
            compiledPath . ".deps.php",
            "<?php return " . var_export(["files": files, "signature": signature], true) . ";" . PHP_EOL,
            LOCK_EX
        );
    }
}
