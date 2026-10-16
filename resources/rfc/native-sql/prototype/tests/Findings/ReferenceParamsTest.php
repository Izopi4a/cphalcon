<?php
declare(strict_types=1);

namespace Phalcon\NativeSql\Tests\Findings;

use Phalcon\Di\Di;
use Phalcon\NativeSql\Tests\Fixtures\Database;
use Phalcon\NativeSql\Tests\Fixtures\Users;
use PHPUnit\Framework\TestCase;

/**
 * Side finding while building the prototype (2026-10-16), not part of the NFR itself.
 *
 * On 7.0.x, find()/findFirst()/Builder silently ignore a `conditions` or `bind` entry whose value
 * is a PHP reference: `Users::find([0 => &$cond])` runs with no WHERE and returns every row.
 *
 * Cause: the Zephir kernel used by 7.0.x (composer `phalcon/zephir: dev-development`, locked)
 * copies the hash entry in zephir_array_isset_*_fetch() without ZVAL_DEREF (ext/kernel/array.c,
 * e.g. lines 219-226), so `fetch x, params[0]` yields an IS_REFERENCE zval and every
 * `typeof x == "string"/"array"` check in Builder::__construct / Model::getPreparedQuery fails.
 * upstream/master is fixed: its ext refresh of 2026-09-08 (2e00fe0c69, Zephir ^1.5.0) adds the
 * ZVAL_DEREF. A referenced element is common: any `foreach ($params as &$v)` leaves one behind,
 * and PHPUnit passes nested data-provider arrays this way.
 *
 * These tests assert the CURRENT (buggy) behaviour so they flip red once 7.0.x picks up the
 * kernel fix; then invert them and drop the detach() calls in the other tests.
 */
final class ReferenceParamsTest extends TestCase
{
    protected function setUp(): void
    {
        new Database();
    }

    protected function tearDown(): void
    {
        Di::reset();
    }

    public function testReferencedConditionIsDroppedAndEveryRowReturned(): void
    {
        $cond = 'active = 0';

        self::assertCount(1, Users::find([$cond]), 'plain value: only Cleo is inactive');
        self::assertCount(4, Users::find([0 => &$cond]), '7.0.x bug: WHERE dropped, all users returned');
    }

    public function testReferencedBindIsDropped(): void
    {
        $bind = ['c' => 'BG'];

        self::assertCount(2, Users::find(['country = :c:', 'bind' => ['c' => 'BG']]));
        self::assertCount(0, Users::find(['country = :c:', 'bind' => &$bind]), '7.0.x bug: :c sent unbound (NULL)');
    }

    public function testForeachByReferenceLeavesTheTrap(): void
    {
        $params = ['active = 0', 'order' => 'name'];
        foreach ($params as &$value) {
            $value = trim($value);
        }
        unset($value);

        self::assertCount(4, Users::find($params), '7.0.x bug: the trimmed condition is a reference -> ignored');
    }

    public function testNativePathIsUnaffectedBecauseItIsPlainPhp(): void
    {
        $cond = 'active = 0';

        // Plain PHP dereferences automatically. A Zephir port of the compiler would hit the same
        // kernel bug, so this is about the kernel, not about PHQL vs native.
        self::assertCount(1, Users::findNative([0 => &$cond]));
    }
}
