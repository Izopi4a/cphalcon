
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
 * A bundle of runtime functions, filters and tests, registered with
 * Volt::addExtension(). Only names and options are read at compile time; the
 * callables run at render time.
 */
interface ExtensionInterface
{
    /**
     * @return VoltFilter[]
     */
    public function getFilters() -> array;

    /**
     * @return VoltFunction[]
     */
    public function getFunctions() -> array;

    /**
     * @return VoltTest[]
     */
    public function getTests() -> array;
}
