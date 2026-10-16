
/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Mvc\View\Engine\Volt\Runtime;

use Closure;
use Phalcon\Di\DiInterface;
use Phalcon\Mvc\View\Engine\Volt\Exception;
use ReflectionMethod;

/**
 * Runtime functions, filters and tests. The compiler reads names and options;
 * the engine resolves the callables lazily at render time, once per name.
 */
class Registry
{
    /**
     * @var array
     */
    protected items = [
        "function": [],
        "filter":   [],
        "test":     []
    ];

    /**
     * @var array
     */
    protected resolved = [];

    /**
     * Adds a function, filter or test
     */
    public function add(<VoltCallable> item) -> <Registry>
    {
        var kind, name;

        let kind = this->kindOf(item),
            name = item->getName();

        let this->items[kind][name] = item;

        unset this->resolved[kind . ":" . name];

        return this;
    }

    /**
     * Adds everything an extension provides
     */
    public function addExtension(<ExtensionInterface> extension) -> <Registry>
    {
        var item;

        for item in extension->getFunctions() {
            this->add(item);
        }

        for item in extension->getFilters() {
            this->add(item);
        }

        for item in extension->getTests() {
            this->add(item);
        }

        return this;
    }

    /**
     * The registered item, or null
     */
    public function get(string kind, string name) -> <VoltCallable> | null
    {
        var item;

        if fetch item, this->items[kind][name] {
            return item;
        }

        return null;
    }

    /**
     * Everything the compiled output depends on; stored next to each compiled
     * template so a changed registry recompiles it
     */
    public function getSignature() -> string
    {
        var items, item;
        array parts;

        let parts = [];

        for items in this->items {
            for item in items {
                let parts[] = item->getSignature();
            }
        }

        sort(parts);

        return sha1(implode("\n", parts));
    }

    /**
     * Whether a name is registered
     */
    public function has(string kind, string name) -> bool
    {
        return isset this->items[kind][name];
    }

    /**
     * The handler as a Closure (named arguments keep working). A
     * [Service::class, "method"] pair with a non-static method gets its
     * instance from the container on first use.
     */
    public function resolve(string kind, string name, <DiInterface> container = null) -> <Closure>
    {
        var key, item, handler, closure;

        let key = kind . ":" . name;

        if fetch closure, this->resolved[key] {
            return closure;
        }

        let item = this->get(kind, name);

        if unlikely item === null {
            throw new Exception("Unknown runtime " . kind . " '" . name . "'");
        }

        let handler = item->getCallable();

        if typeof handler == "array" && count(handler) == 2 && typeof handler[0] == "string" && typeof handler[1] == "string" {
            if !this->isStatic(handler[0], handler[1]) {
                let handler[0] = this->instance(handler[0], container);
            }
        }

        let closure = Closure::fromCallable(handler);

        let this->resolved[key] = closure;

        return closure;
    }

    /**
     * An instance for [ServiceOrClass, "method"]: the container service of that
     * name, or the class built through the container, or a plain new
     */
    protected function instance(string name, <DiInterface> container = null) -> object
    {
        if container !== null && container->has(name) {
            return container->getShared(name);
        }

        if container !== null && class_exists(name) {
            return container->get(name);
        }

        if class_exists(name) {
            return create_instance(name);
        }

        throw new Exception(
            "Cannot resolve '" . name . "': not a service in the container and not a class"
        );
    }

    protected function isStatic(string className, string method) -> bool
    {
        var reflection;

        if !class_exists(className) || !method_exists(className, method) {
            return false;
        }

        let reflection = new ReflectionMethod(className, method);

        return reflection->isStatic();
    }

    protected function kindOf(<VoltCallable> item) -> string
    {
        if item instanceof VoltFilter {
            return "filter";
        }

        if item instanceof VoltTest {
            return "test";
        }

        return "function";
    }
}
