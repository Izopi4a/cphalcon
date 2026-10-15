<?php
declare(strict_types=1);

namespace Phalcon\Form\Options;

/**
 * Read-only view of options being resolved. Lazy defaults receive this object and
 * may read other options through it; cycles are detected.
 *
 * @implements \ArrayAccess<string, mixed>
 */
interface Options extends \ArrayAccess, \Countable
{
}
