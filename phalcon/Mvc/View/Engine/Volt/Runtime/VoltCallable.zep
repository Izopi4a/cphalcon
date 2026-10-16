
/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Mvc\View\Engine\Volt\Runtime;

use ReflectionMethod;

/**
 * A template function, filter or test backed by a PHP handler that runs at
 * RENDER time with the evaluated argument values. The counterpart of
 * Compiler::addFunction(), whose definition runs at COMPILE time and returns
 * PHP source.
 *
 * Accepted callables:
 * - any Closure, including first-class callables (Money::format(...))
 * - "strlen", "App\\Money::format", [Money::class, "format"] (static)
 * - [$object, "method"] and invokable objects
 * - [ServiceOrClass::class, "method"] with a non-static method: the instance
 *   comes from the DI container the first time a template calls it
 *
 * Options:
 * - safe:         the result is HTML, autoescape leaves it alone
 * - needsContext: the template variables are passed as the first argument
 */
abstract class VoltCallable
{
    /**
     * @var mixed
     */
    protected handler;

    /**
     * @var string
     */
    protected name;

    /**
     * @var array
     */
    protected options = [];

    /**
     * Phalcon\Mvc\View\Engine\Volt\Runtime\VoltCallable constructor
     *
     * @param array options = [
     *     'safe'         => false,
     *     'needsContext' => false
     * ]
     */
    public function __construct(string name, var handler, array options = [])
    {
        let this->name     = name,
            this->handler = handler,
            this->options  = options;
    }

    /**
     * @return mixed
     */
    public function getCallable() -> var
    {
        return this->handler;
    }

    public function getName() -> string
    {
        return this->name;
    }

    public function getOptions() -> array
    {
        return this->options;
    }

    /**
     * Part of the cache signature: what the compiled code depends on
     */
    public function getSignature() -> string
    {
        var code;

        let code = this->getStaticCallCode();

        if code === null {
            let code = "runtime";
        }

        return get_class(this) . ":" . this->name . ":" . code . ":" . json_encode(this->options);
    }

    /**
     * PHP code that calls the handler directly, when it can be written into
     * the compiled template as is: a function name or a public static method.
     * Null means "resolve it at render time" (closures, objects, services).
     */
    public function getStaticCallCode() -> string | null
    {
        var handler, method;

        let handler = this->handler;

        if typeof handler == "string" && !memstr(handler, "::") {
            if function_exists(handler) {
                return "\\" . ltrim(handler, "\\");
            }

            return null;
        }

        if typeof handler == "string" {
            let handler = explode("::", handler, 2);
        }

        if typeof handler == "array" && count(handler) == 2 && typeof handler[0] == "string" && typeof handler[1] == "string" {
            if !class_exists(handler[0]) || !method_exists(handler[0], handler[1]) {
                return null;
            }

            let method = new ReflectionMethod(handler[0], handler[1]);

            if method->isStatic() && method->isPublic() {
                return "\\" . ltrim(handler[0], "\\") . "::" . handler[1];
            }
        }

        return null;
    }

    /**
     * Whether the result is HTML that autoescape must not escape again
     */
    public function isSafe() -> bool
    {
        var safe;

        if fetch safe, this->options["safe"] {
            return (bool) safe;
        }

        return false;
    }

    /**
     * Whether the template variables are passed as the first argument
     */
    public function needsContext() -> bool
    {
        var needsContext;

        if fetch needsContext, this->options["needsContext"] {
            return (bool) needsContext;
        }

        return false;
    }
}
