
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
 * A template test that runs at render time: {% if value is name %}
 *
 *```php
 * $volt->addTest(new VoltTest("name", $callable, ["safe" => false]));
 *```
 */
final class VoltTest extends VoltCallable
{
}
