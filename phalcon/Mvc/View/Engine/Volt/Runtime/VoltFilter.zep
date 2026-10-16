
/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Mvc\View\Engine\Volt\Runtime;

/**
 * A template filter that runs at render time: {{ value|name(args) }}
 *
 *```php
 * $volt->addFilter(new VoltFilter("name", $callable, ["safe" => false]));
 *```
 */
final class VoltFilter extends VoltCallable
{
}
