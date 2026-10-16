
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
 * Base class for runtime extensions: override what you provide
 */
abstract class AbstractExtension implements ExtensionInterface
{
    public function getFilters() -> array
    {
        return [];
    }

    public function getFunctions() -> array
    {
        return [];
    }

    public function getTests() -> array
    {
        return [];
    }
}
