
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Router
 *
 * Phalcon\Mvc\Router is the standard framework router. Routing is the
 * process of taking a URI endpoint (that part of the URI which comes after the
 * base URL) and decomposing it into parameters to determine which module,
 * controller, and action of that controller should receive the request
 *
 * ```php
 * use Phalcon\Mvc\Router;
 *
 * $router = new Router();
 *
 * $router->add(
 *     "/documentation/{chapter}/{name}\.{type:[a-z]+}",
 *     [
 *         "controller" => "documentation",
 *         "action"     => "show",
 *     ]
 * );
 *
 * $router->handle(
 *     "/documentation/1/examples.html"
 * );
 *
 * echo $router->getControllerName();
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Router)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, Router, phalcon, mvc_router, phalcon_di_abstractinjectionaware_ce, phalcon_mvc_router_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("action"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("controller"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("defaultAction"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("defaultController"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("defaultModule"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("defaultNamespace"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("defaultParams"), ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("keyRouteNames"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("keyRouteIds"), ZEND_ACC_PROTECTED);
	/**
	 * @var RouteInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("matchedRoute"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("matches"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("module"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_ce, SL("namespaceName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var array|string|null
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("notFoundPaths"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("params"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_router_ce, SL("removeExtraSlashes"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_ce, SL("routes"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_router_ce, SL("uriSource"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_router_ce, SL("wasMatched"), 0, ZEND_ACC_PROTECTED);
	phalcon_mvc_router_ce->create_object = zephir_init_properties_Phalcon_Mvc_Router;
	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_router_ce, SL("POSITION_FIRST"), 0);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_router_ce, SL("POSITION_LAST"), 1);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_router_ce, SL("URI_SOURCE_GET_URL"), 0);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_router_ce, SL("URI_SOURCE_SERVER_REQUEST_URI"), 1);

	zend_class_implements(phalcon_mvc_router_ce, 1, phalcon_mvc_routerinterface_ce);
	zend_class_implements(phalcon_mvc_router_ce, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Router constructor
 *
 * @param bool defaultRoutes
 */
PHP_METHOD(Phalcon_Mvc_Router, __construct)
{
	zval routes, _1$$3, _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *defaultRoutes_param = NULL, _0$$3, _2$$3, _4$$3;
	zend_bool defaultRoutes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&routes);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("routes", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(defaultRoutes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &defaultRoutes_param);
	if (!defaultRoutes_param) {
		defaultRoutes = 1;
	} else {
	if (UNEXPECTED(Z_TYPE_P(defaultRoutes_param) != IS_TRUE && Z_TYPE_P(defaultRoutes_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'defaultRoutes' must be of the type bool"));
		RETURN_MM_NULL();
	}
	defaultRoutes = (Z_TYPE_P(defaultRoutes_param) == IS_TRUE);
	}
	ZEPHIR_INIT_VAR(&routes);
	array_init(&routes);
	if (defaultRoutes) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_router_route_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 1, 0);
		add_assoc_long_ex(&_1$$3, SL("controller"), 1);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "#^/([\\w0-9\\_\\-]+)[/]{0,1}$#u");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 110, &_2$$3, &_1$$3);
		zephir_check_call_status();
		zephir_array_append(&routes, &_0$$3, PH_SEPARATE, "phalcon/Mvc/Router.zep", 190);
		ZEPHIR_INIT_NVAR(&_2$$3);
		object_init_ex(&_2$$3, phalcon_mvc_router_route_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_create_array(&_3$$3, 3, 0);
		add_assoc_long_ex(&_3$$3, SL("controller"), 1);
		add_assoc_long_ex(&_3$$3, SL("action"), 2);
		add_assoc_long_ex(&_3$$3, SL("params"), 3);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "#^/([\\w0-9\\_\\-]+)/([\\w0-9\\.\\_]+)(/.*)*$#u");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 110, &_4$$3, &_3$$3);
		zephir_check_call_status();
		zephir_array_append(&routes, &_2$$3, PH_SEPARATE, "phalcon/Mvc/Router.zep", 199);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 204, &routes);
	ZEPHIR_MM_RESTORE();
}

/**
 * Adds a route to the router without any HTTP constraint
 *
 *```php
 * use Phalcon\Mvc\Router;
 *
 * $router->add("/about", "About::index");
 *
 * $router->add(
 *     "/about",
 *     "About::index",
 *     ["GET", "POST"]
 * );
 *
 * $router->add(
 *     "/about",
 *     "About::index",
 *     ["GET", "POST"],
 *     Router::POSITION_FIRST
 * );
 *```
 *
 * @param string            $pattern
 * @param array|string|null $paths = [
 *                                 'module => '',
 *                                 'controller' => '',
 *                                 'action' => '',
 *                                 'namespace' => ''
 *                                 ]
 * @param array|string|null $httpMethods
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, add)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *httpMethods = NULL, httpMethods_sub, *position_param = NULL, __$null, route, _0;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_UNDEF(&httpMethods_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_ZVAL_OR_NULL(httpMethods)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		httpMethods = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		position_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!httpMethods) {
		httpMethods = &httpMethods_sub;
		httpMethods = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&route);
	object_init_ex(&route, phalcon_mvc_router_route_ce);
	ZEPHIR_CALL_METHOD(NULL, &route, "__construct", NULL, 110, &pattern_zv, paths, httpMethods);
	zephir_check_call_status();
	ZVAL_LONG(&_0, position);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "attach", NULL, 0, &route, &_0);
	zephir_check_call_status();
	RETURN_CCTOR(&route);
}

/**
 * Adds a route to the router that only match if the HTTP method is CONNECT
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addConnect)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "CONNECT");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is DELETE
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addDelete)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "DELETE");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is GET
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addGet)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "GET");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is HEAD
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addHead)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "HEAD");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Add a route to the router that only match if the HTTP method is OPTIONS
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "OPTIONS");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is PATCH
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addPatch)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "PATCH");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is POST
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addPost)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "POST");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is PURGE
 * (Squid and Varnish support)
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addPurge)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "PURGE");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is PUT
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addPut)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "PUT");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a route to the router that only match if the HTTP method is TRACE
 *
 * @param string            $pattern
 * @param array|string|null $paths  = [
 *                                  'module => '',
 *                                  'controller' => '',
 *                                  'action' => '',
 *                                  'namespace' => ''
 *                                  ]
 * @param int               $position
 *
 * @return RouteInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, addTrace)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position, ZEPHIR_LAST_CALL_STATUS;
	zval pattern_zv, *paths = NULL, paths_sub, *position_param = NULL, __$null, _0, _1;
	zend_string *pattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern_zv);
	ZVAL_UNDEF(&paths_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(pattern)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(paths)
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		paths = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		position_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&pattern_zv);
	ZVAL_STR_COPY(&pattern_zv, pattern);
	if (!paths) {
		paths = &paths_sub;
		paths = &__$null;
	}
	if (!position_param) {
		position = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "TRACE");
	ZVAL_LONG(&_1, position);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, &pattern_zv, paths, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Attach Route object to the routes stack.
 *
 * ```php
 * use Phalcon\Mvc\Router;
 * use Phalcon\Mvc\Router\Route;
 *
 * class CustomRoute extends Route {
 *      // ...
 * }
 *
 * $router = new Router();
 *
 * $router->attach(
 *     new CustomRoute("/about", "About::index", ["GET", "HEAD"]),
 *     Router::POSITION_FIRST
 * );
 * ```
 *
 * @param RouteInterface $route
 * @param int            $position
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, attach)
{
	zval _1$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long position;
	zval *route, route_sub, *position_param = NULL, _0$$4, _2$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_1$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("routes", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_OBJECT_OF_CLASS(route, phalcon_mvc_router_routeinterface_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(position)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &route, &position_param);
	if (!position_param) {
		position = 1;
	} else {
		}
	if (position == 1) { goto zephir_switch_0_clause_0; }
	if (position == 0) { goto zephir_switch_0_clause_1; }
	goto zephir_switch_0_clause_2;
	zephir_switch_0_clause_0: ;
		zephir_update_property_array_append(this_ptr, SL("routes"), route);
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
		ZEPHIR_INIT_VAR(&_0$$4);
		ZEPHIR_INIT_VAR(&_1$$4);
		zephir_create_array(&_1$$4, 1, 0);
		zephir_array_fast_append(&_1$$4, route);
		zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_0, 204, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_0$$4, &_1$$4, &_2$$4);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 204, &_0$$4);
		goto zephir_switch_0_end;
	zephir_switch_0_clause_2: ;
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "Invalid route position", "phalcon/Mvc/Router.zep", 514);
		return;
	zephir_switch_0_end: ;

	RETURN_THIS();
}

/**
 * Removes all the pre-defined routes
 */
PHP_METHOD(Phalcon_Mvc_Router, clear)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("routes", 6, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 204, &_0);
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Mvc_Router, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Returns the processed action name
 */
PHP_METHOD(Phalcon_Mvc_Router, getActionName)
{

	RETURN_MEMBER_TYPED(getThis(), "action", IS_STRING);
}

/**
 * Returns the processed controller name
 */
PHP_METHOD(Phalcon_Mvc_Router, getControllerName)
{

	RETURN_MEMBER_TYPED(getThis(), "controller", IS_STRING);
}

/**
 * Returns an array of default parameters
 */
PHP_METHOD(Phalcon_Mvc_Router, getDefaults)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultNamespace", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("defaultModule", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("defaultController", 17, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("defaultAction", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("defaultParams", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 5, 0);
	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 205, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("namespace"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 206, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("module"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 207, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("controller"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 208, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("action"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 209, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("params"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Router, getKeyRouteNames)
{

	RETURN_MEMBER_TYPED(getThis(), "keyRouteNames", IS_ARRAY);
}

/**
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Router, getKeyRouteIds)
{

	RETURN_MEMBER_TYPED(getThis(), "keyRouteIds", IS_ARRAY);
}

/**
 * Returns the route that matches the handled URI
 */
PHP_METHOD(Phalcon_Mvc_Router, getMatchedRoute)
{

	RETURN_MEMBER(getThis(), "matchedRoute");
}

/**
 * Returns the sub expressions in the regular expression matched
 */
PHP_METHOD(Phalcon_Mvc_Router, getMatches)
{

	RETURN_MEMBER_TYPED(getThis(), "matches", IS_ARRAY);
}

/**
 * Returns the processed module name
 */
PHP_METHOD(Phalcon_Mvc_Router, getModuleName)
{

	RETURN_MEMBER_TYPED(getThis(), "module", IS_STRING);
}

/**
 * Returns the processed namespace name
 */
PHP_METHOD(Phalcon_Mvc_Router, getNamespaceName)
{

	RETURN_MEMBER_TYPED(getThis(), "namespaceName", IS_STRING);
}

/**
 * Returns the processed parameters
 */
PHP_METHOD(Phalcon_Mvc_Router, getParams)
{

	RETURN_MEMBER_TYPED(getThis(), "params", IS_ARRAY);
}

/**
 * Get rewrite info. This info is read from $_GET["_url"].
 * This returns '/' if the rewrite information cannot be read
 */
PHP_METHOD(Phalcon_Mvc_Router, getRewriteUri)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval _GET, _SERVER, url, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_GET);
	ZVAL_UNDEF(&_SERVER);
	ZVAL_UNDEF(&url);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uriSource", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_get_global(&_SERVER, SL("_SERVER"));
	zephir_get_global(&_GET, SL("_GET"));

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 210, PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_LONG_IDENTICAL(&_0, 0)) {
		zephir_memory_observe(&url);
		if (zephir_array_isset_string_fetch(&url, &_GET, SL("_url"), 0)) {
			if (!(ZEPHIR_IS_EMPTY(&url))) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "extractRealUri", NULL, 0, &url);
				zephir_check_call_status();
				RETURN_MM();
			}
		}
	} else {
		ZEPHIR_OBS_NVAR(&url);
		if (zephir_array_isset_string_fetch(&url, &_SERVER, SL("REQUEST_URI"), 0)) {
			if (!(ZEPHIR_IS_EMPTY(&url))) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "extractRealUri", NULL, 0, &url);
				zephir_check_call_status();
				RETURN_MM();
			}
		}
	}
	RETURN_MM_STRING("/");
}

PHP_METHOD(Phalcon_Mvc_Router, extractRealUri)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval uri_zv, urlParts, realUri, _0;
	zend_string *uri = NULL;

	ZVAL_UNDEF(&uri_zv);
	ZVAL_UNDEF(&urlParts);
	ZVAL_UNDEF(&realUri);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&uri_zv);
	ZVAL_STR_COPY(&uri_zv, uri);
	ZVAL_LONG(&_0, 2);
	ZEPHIR_INIT_VAR(&urlParts);
	zephir_fast_explode_str(&urlParts, SL("?"), &uri_zv, &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&realUri);
	zephir_array_fetch_long(&realUri, &urlParts, 0, PH_NOISY, "phalcon/Mvc/Router.zep", 658);
	RETURN_CCTOR(&realUri);
}

/**
 * Returns a route object by its id
 *
 * @param mixed id
 *
 * @return RouteInterface|bool
 */
PHP_METHOD(Phalcon_Mvc_Router, getRouteById)
{
	zend_bool _11, _9$$4, _12$$6;
	zend_string *_8;
	zend_ulong _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *id, id_sub, route, routeId, key, _0, _3, *_4, _5, *_6, _10, _1$$3, _2$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id_sub);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&routeId);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("keyRouteIds", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("routes", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &id);
	zephir_memory_observe(&key);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 211, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_fetch(&key, &_0, id, 0)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 204, PH_NOISY_CC | PH_READONLY);
		zephir_memory_observe(&_2$$3);
		zephir_array_fetch(&_2$$3, &_1$$3, &key, PH_NOISY, "phalcon/Mvc/Router.zep", 675);
		RETURN_CCTOR(&_2$$3);
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 204, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_3) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &_3);
		_4 = &_5;
	} else {
		_4 = &_3;
	}
	zephir_is_iterable(_4, 0, "phalcon/Mvc/Router.zep", 687);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _7, _8, _6)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_8 != NULL) { 
				ZVAL_STR_COPY(&key, _8);
			} else {
				ZVAL_LONG(&key, _7);
			}
			ZEPHIR_INIT_NVAR(&route);
			ZVAL_COPY(&route, _6);
			ZEPHIR_CALL_METHOD(&routeId, &route, "getRouteId", NULL, 0);
			zephir_check_call_status();
			zephir_update_property_array(this_ptr, SL("keyRouteIds"), &routeId, &key);
			_9$$4 = ZEPHIR_IS_EQUAL(&routeId, id);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_9$$4) {
				RETURN_CCTOR(&route);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_11 = 1;
		while (1) {
			if (_11) {
				_11 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_10, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&route, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&routeId, &route, "getRouteId", NULL, 0);
				zephir_check_call_status();
				zephir_update_property_array(this_ptr, SL("keyRouteIds"), &routeId, &key);
				_12$$6 = ZEPHIR_IS_EQUAL(&routeId, id);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (_12$$6) {
					RETURN_CCTOR(&route);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_MM_BOOL(0);
}

/**
 * Returns a route object by its name
 *
 * @param string name
 *
 * @return RouteInterface|bool
 */
PHP_METHOD(Phalcon_Mvc_Router, getRouteByName)
{
	zend_bool _11, _9$$5, _12$$8;
	zend_ulong _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, route, routeName, key, _0, _3, *_4, _5, *_6, _10, _1$$3, _2$$3;
	zend_string *name = NULL, *_8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&routeName);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("keyRouteNames", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("routes", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_memory_observe(&key);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 212, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_fetch(&key, &_0, &name_zv, 0)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 204, PH_NOISY_CC | PH_READONLY);
		zephir_memory_observe(&_2$$3);
		zephir_array_fetch(&_2$$3, &_1$$3, &key, PH_NOISY, "phalcon/Mvc/Router.zep", 702);
		RETURN_CCTOR(&_2$$3);
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 204, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_3) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &_3);
		_4 = &_5;
	} else {
		_4 = &_3;
	}
	zephir_is_iterable(_4, 0, "phalcon/Mvc/Router.zep", 717);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _7, _8, _6)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_8 != NULL) { 
				ZVAL_STR_COPY(&key, _8);
			} else {
				ZVAL_LONG(&key, _7);
			}
			ZEPHIR_INIT_NVAR(&route);
			ZVAL_COPY(&route, _6);
			ZEPHIR_CALL_METHOD(&routeName, &route, "getName", NULL, 0);
			zephir_check_call_status();
			if (!(ZEPHIR_IS_EMPTY(&routeName))) {
				zephir_update_property_array(this_ptr, SL("keyRouteNames"), &routeName, &key);
				_9$$5 = ZEPHIR_IS_EQUAL(&routeName, &name_zv);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (_9$$5) {
					RETURN_CCTOR(&route);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_11 = 1;
		while (1) {
			if (_11) {
				_11 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_10, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&route, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&routeName, &route, "getName", NULL, 0);
				zephir_check_call_status();
				if (!(ZEPHIR_IS_EMPTY(&routeName))) {
					zephir_update_property_array(this_ptr, SL("keyRouteNames"), &routeName, &key);
					_12$$8 = ZEPHIR_IS_EQUAL(&routeName, &name_zv);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (_12$$8) {
						RETURN_CCTOR(&route);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_MM_BOOL(0);
}

/**
 * Returns all the routes defined in the router
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Router, getRoutes)
{

	RETURN_MEMBER_TYPED(getThis(), "routes", IS_ARRAY);
}

/**
 * Handles routing information received from the rewrite engine
 *
 *```php
 * // Passing a URL
 * $router->handle("/posts/edit/1");
 *```
 *
 * @param string uri
 *
 * @return void
 */
PHP_METHOD(Phalcon_Mvc_Router, handle)
{
	zend_ulong _26$$32, _64$$77;
	zval _20$$27, _33$$38, _35$$41, _42$$49, _44$$52, _58$$72, _70$$83, _72$$86, _79$$94, _81$$97;
	zend_bool _1, _46, _14$$20, _17$$24, _37$$32, _31$$33, _40$$44, _52$$65, _55$$69, _74$$77, _68$$78, _77$$89;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL, *_12 = NULL, *_16 = NULL, *_19 = NULL, *_22 = NULL, *_30 = NULL, *_49 = NULL, *_50 = NULL, *_54 = NULL, *_57 = NULL, *_60 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri_zv, __$true, __$false, __$null, action, beforeMatch, container, controller, converter, converters, currentHostName, eventsManager, handledUri, hostname, matched, matches, matchPosition, methods, module, notFoundPaths, params, paramsStr, part, parts, paths, pattern, position, realUri, regexHostName, request, route, routeFound, strParams, vnamespace, _0, _3, _5, _6, *_7, *_8, _45, _83, _84, _85, _86, _87, _2$$5, _4$$8, _9$$11, _10$$11, _13$$16, _15$$22, _18$$26, _21$$30, *_23$$32, _24$$32, *_25$$32, _36$$32, _28$$34, _29$$34, _32$$38, _34$$41, _38$$45, _39$$45, _41$$49, _43$$52, _47$$56, _48$$56, _51$$61, _53$$67, _56$$71, _59$$75, *_61$$77, _62$$77, *_63$$77, _73$$77, _66$$79, _67$$79, _69$$83, _71$$86, _75$$90, _76$$90, _78$$94, _80$$97, _82$$102, _88$$110, _89$$112, _90$$114;
	zend_string *uri = NULL, *_27$$32, *_65$$77;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&beforeMatch);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&controller);
	ZVAL_UNDEF(&converter);
	ZVAL_UNDEF(&converters);
	ZVAL_UNDEF(&currentHostName);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&handledUri);
	ZVAL_UNDEF(&hostname);
	ZVAL_UNDEF(&matched);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&matchPosition);
	ZVAL_UNDEF(&methods);
	ZVAL_UNDEF(&module);
	ZVAL_UNDEF(&notFoundPaths);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&paramsStr);
	ZVAL_UNDEF(&part);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&paths);
	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&realUri);
	ZVAL_UNDEF(&regexHostName);
	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&routeFound);
	ZVAL_UNDEF(&strParams);
	ZVAL_UNDEF(&vnamespace);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_45);
	ZVAL_UNDEF(&_83);
	ZVAL_UNDEF(&_84);
	ZVAL_UNDEF(&_85);
	ZVAL_UNDEF(&_86);
	ZVAL_UNDEF(&_87);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_4$$8);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_13$$16);
	ZVAL_UNDEF(&_15$$22);
	ZVAL_UNDEF(&_18$$26);
	ZVAL_UNDEF(&_21$$30);
	ZVAL_UNDEF(&_24$$32);
	ZVAL_UNDEF(&_36$$32);
	ZVAL_UNDEF(&_28$$34);
	ZVAL_UNDEF(&_29$$34);
	ZVAL_UNDEF(&_32$$38);
	ZVAL_UNDEF(&_34$$41);
	ZVAL_UNDEF(&_38$$45);
	ZVAL_UNDEF(&_39$$45);
	ZVAL_UNDEF(&_41$$49);
	ZVAL_UNDEF(&_43$$52);
	ZVAL_UNDEF(&_47$$56);
	ZVAL_UNDEF(&_48$$56);
	ZVAL_UNDEF(&_51$$61);
	ZVAL_UNDEF(&_53$$67);
	ZVAL_UNDEF(&_56$$71);
	ZVAL_UNDEF(&_59$$75);
	ZVAL_UNDEF(&_62$$77);
	ZVAL_UNDEF(&_73$$77);
	ZVAL_UNDEF(&_66$$79);
	ZVAL_UNDEF(&_67$$79);
	ZVAL_UNDEF(&_69$$83);
	ZVAL_UNDEF(&_71$$86);
	ZVAL_UNDEF(&_75$$90);
	ZVAL_UNDEF(&_76$$90);
	ZVAL_UNDEF(&_78$$94);
	ZVAL_UNDEF(&_80$$97);
	ZVAL_UNDEF(&_82$$102);
	ZVAL_UNDEF(&_88$$110);
	ZVAL_UNDEF(&_89$$112);
	ZVAL_UNDEF(&_90$$114);
	ZVAL_UNDEF(&_20$$27);
	ZVAL_UNDEF(&_33$$38);
	ZVAL_UNDEF(&_35$$41);
	ZVAL_UNDEF(&_42$$49);
	ZVAL_UNDEF(&_44$$52);
	ZVAL_UNDEF(&_58$$72);
	ZVAL_UNDEF(&_70$$83);
	ZVAL_UNDEF(&_72$$86);
	ZVAL_UNDEF(&_79$$94);
	ZVAL_UNDEF(&_81$$97);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	static zend_string *_zephir_prop_9 = NULL;
	static zend_string *_zephir_prop_10 = NULL;
	static zend_string *_zephir_prop_11 = NULL;
	static zend_string *_zephir_prop_12 = NULL;
	static zend_string *_zephir_prop_13 = NULL;
	static zend_string *_zephir_prop_14 = NULL;
	static zend_string *_zephir_prop_15 = NULL;
	static zend_string *_zephir_prop_16 = NULL;
	static zend_string *_zephir_prop_17 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("removeExtraSlashes", 18, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("wasMatched", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("matchedRoute", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("routes", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("matches", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("notFoundPaths", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("defaultNamespace", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("namespaceName", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("defaultModule", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("module", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_12)) {
		_zephir_prop_12 = zend_string_init("defaultController", 17, 1);
	}
	if (UNEXPECTED(!_zephir_prop_13)) {
		_zephir_prop_13 = zend_string_init("controller", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_14)) {
		_zephir_prop_14 = zend_string_init("defaultAction", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_15)) {
		_zephir_prop_15 = zend_string_init("action", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_16)) {
		_zephir_prop_16 = zend_string_init("defaultParams", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_17)) {
		_zephir_prop_17 = zend_string_init("params", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&uri_zv);
	ZVAL_STR_COPY(&uri_zv, uri);
	if (!(!(ZEPHIR_IS_EMPTY(&uri_zv)))) {
		ZEPHIR_CALL_METHOD(&realUri, this_ptr, "getRewriteUri", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&realUri, this_ptr, "extractRealUri", NULL, 0, &uri_zv);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 213, PH_NOISY_CC | PH_READONLY);
	_1 = zephir_is_true(&_0);
	if (_1) {
		_1 = !ZEPHIR_IS_STRING_IDENTICAL(&realUri, "/");
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_2$$5);
		ZVAL_STRING(&_2$$5, "/");
		ZEPHIR_INIT_VAR(&handledUri);
		zephir_fast_trim(&handledUri, &realUri, &_2$$5, ZEPHIR_TRIM_RIGHT);
	} else {
		ZEPHIR_CPY_WRT(&handledUri, &realUri);
	}
	if (ZEPHIR_IS_EMPTY(&handledUri)) {
		ZEPHIR_INIT_NVAR(&handledUri);
		ZVAL_STRING(&handledUri, "/");
	}
	ZEPHIR_INIT_VAR(&currentHostName);
	ZVAL_NULL(&currentHostName);
	ZEPHIR_INIT_VAR(&routeFound);
	ZVAL_BOOL(&routeFound, 0);
	ZEPHIR_INIT_VAR(&parts);
	array_init(&parts);
	ZEPHIR_INIT_VAR(&params);
	array_init(&params);
	ZEPHIR_INIT_VAR(&matches);
	ZVAL_NULL(&matches);
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 214, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 214, &__$false);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 215, &__$null);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_3, 216, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_3);
	if (Z_TYPE_P(&eventsManager) != IS_NULL) {
		ZEPHIR_INIT_VAR(&_4$$8);
		ZVAL_STRING(&_4$$8, "router:beforeCheckRoutes");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_4$$8, this_ptr);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_4, 217, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_3);
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "A dependency injection container is required to access the 'request' service", "phalcon/Mvc/Router.zep", 792);
		return;
	}
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "request");
	ZEPHIR_CALL_METHOD(&_5, &container, "get", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&request, &_5);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_5, 204, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_3) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_6);
		zephir_string_to_char_array(&_6, &_3);
		_7 = &_6;
	} else {
		_7 = &_3;
	}
	zephir_is_iterable(_7, 0, "phalcon/Mvc/Router.zep", 998);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_REVERSE_FOREACH_VAL(Z_ARRVAL_P(_7), _8)
		{
			ZEPHIR_INIT_NVAR(&route);
			ZVAL_COPY(&route, _8);
			ZEPHIR_INIT_NVAR(&params);
			array_init(&params);
			ZEPHIR_INIT_NVAR(&matches);
			ZVAL_NULL(&matches);
			ZEPHIR_CALL_METHOD(&methods, &route, "getHttpMethods", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&methods) != IS_NULL) {
				ZVAL_BOOL(&_10$$11, 1);
				ZEPHIR_CALL_METHOD(&_9$$11, &request, "isMethod", &_11, 0, &methods, &_10$$11);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_9$$11)) {
					continue;
				}
			}
			ZEPHIR_CALL_METHOD(&hostname, &route, "getHostName", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&hostname) != IS_NULL) {
				if (Z_TYPE_P(&currentHostName) == IS_NULL) {
					ZEPHIR_CALL_METHOD(&currentHostName, &request, "getHttpHost", &_12, 0);
					zephir_check_call_status();
				}
				if (!(zephir_is_true(&currentHostName))) {
					continue;
				}
				if (zephir_memnstr_str(&hostname, SL("("), "phalcon/Mvc/Router.zep", 840)) {
					if (!(zephir_memnstr_str(&hostname, SL("#"), "phalcon/Mvc/Router.zep", 841))) {
						ZEPHIR_INIT_NVAR(&regexHostName);
						ZEPHIR_CONCAT_SV(&regexHostName, "#^", &hostname);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if (!(zephir_memnstr_str(&hostname, SL(":"), "phalcon/Mvc/Router.zep", 844))) {
							zephir_concat_self_str(&regexHostName, SL("(:[[:digit:]]+)?"));
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
						zephir_concat_self_str(&regexHostName, SL("$#i"));
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CPY_WRT(&regexHostName, &hostname);
					}
					ZEPHIR_INIT_NVAR(&_13$$16);
					ZEPHIR_INIT_NVAR(&matched);
					zephir_preg_match(&matched, &regexHostName, &currentHostName, &_13$$16, 0, 0 , 0 );
				} else {
					_14$$20 = ZEPHIR_IS_EQUAL(&currentHostName, &hostname);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&matched);
					ZVAL_BOOL(&matched, _14$$20);
				}
				if (!(zephir_is_true(&matched))) {
					continue;
				}
			}
			if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
				ZEPHIR_INIT_NVAR(&_15$$22);
				ZVAL_STRING(&_15$$22, "router:beforeCheckRoute");
				ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_16, 0, &_15$$22, this_ptr, &route);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&pattern, &route, "getCompiledPattern", NULL, 0);
			zephir_check_call_status();
			if (zephir_memnstr_str(&pattern, SL("^"), "phalcon/Mvc/Router.zep", 872)) {
				ZEPHIR_INIT_NVAR(&routeFound);
				zephir_preg_match(&routeFound, &pattern, &handledUri, &matches, 0, 0 , 0 );
			} else {
				_17$$24 = ZEPHIR_IS_EQUAL(&pattern, &handledUri);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&routeFound);
				ZVAL_BOOL(&routeFound, _17$$24);
			}
			if (zephir_is_true(&routeFound)) {
				if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_18$$26);
					ZVAL_STRING(&_18$$26, "router:matchedRoute");
					ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_19, 0, &_18$$26, this_ptr, &route);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&beforeMatch, &route, "getBeforeMatch", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&beforeMatch) != IS_NULL) {
					if (UNEXPECTED(!(zephir_is_callable(&beforeMatch)))) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "Before-Match callback is not callable in matched route", "phalcon/Mvc/Router.zep", 894);
						return;
					}
					ZEPHIR_INIT_NVAR(&_20$$27);
					zephir_create_array(&_20$$27, 3, 0);
					zephir_array_fast_append(&_20$$27, &handledUri);
					zephir_array_fast_append(&_20$$27, &route);
					zephir_array_fast_append(&_20$$27, this_ptr);
					ZEPHIR_INIT_NVAR(&routeFound);
					ZEPHIR_CALL_USER_FUNC_ARRAY(&routeFound, &beforeMatch, &_20$$27);
					zephir_check_call_status();
				}
			} else {
				if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_21$$30);
					ZVAL_STRING(&_21$$30, "router:notMatchedRoute");
					ZEPHIR_CALL_METHOD(&routeFound, &eventsManager, "fire", &_22, 0, &_21$$30, this_ptr, &route);
					zephir_check_call_status();
				}
			}
			if (zephir_is_true(&routeFound)) {
				ZEPHIR_CALL_METHOD(&paths, &route, "getPaths", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&parts, &paths);
				if (Z_TYPE_P(&matches) == IS_ARRAY) {
					ZEPHIR_CALL_METHOD(&converters, &route, "getConverters", NULL, 0);
					zephir_check_call_status();
					if (Z_TYPE_P(&paths) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_24$$32);
						zephir_string_to_char_array(&_24$$32, &paths);
						_23$$32 = &_24$$32;
					} else {
						_23$$32 = &paths;
					}
					zephir_is_iterable(_23$$32, 0, "phalcon/Mvc/Router.zep", 986);
					if (Z_TYPE_P(_23$$32) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_23$$32), _26$$32, _27$$32, _25$$32)
						{
							ZEPHIR_INIT_NVAR(&part);
							if (_27$$32 != NULL) { 
								ZVAL_STR_COPY(&part, _27$$32);
							} else {
								ZVAL_LONG(&part, _26$$32);
							}
							ZEPHIR_INIT_NVAR(&position);
							ZVAL_COPY(&position, _25$$32);
							if (UNEXPECTED(Z_TYPE_P(&part) != IS_STRING)) {
								ZEPHIR_INIT_NVAR(&_28$$34);
								object_init_ex(&_28$$34, phalcon_mvc_router_exception_ce);
								ZEPHIR_INIT_NVAR(&_29$$34);
								ZEPHIR_CONCAT_SV(&_29$$34, "Wrong key in paths: ", &part);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_28$$34, "__construct", &_30, 32, &_29$$34);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_28$$34, "phalcon/Mvc/Router.zep", 934);
								ZEPHIR_MM_RESTORE();
								return;
							}
							_31$$33 = Z_TYPE_P(&position) != IS_STRING;
							if (_31$$33) {
								_31$$33 = Z_TYPE_P(&position) != IS_LONG;
							}
							if (_31$$33) {
								continue;
							}
							ZEPHIR_OBS_NVAR(&matchPosition);
							if (zephir_array_isset_fetch(&matchPosition, &matches, &position, 0)) {
								if (Z_TYPE_P(&converters) == IS_ARRAY) {
									ZEPHIR_OBS_NVAR(&converter);
									if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
										ZEPHIR_INIT_NVAR(&_32$$38);
										ZEPHIR_INIT_NVAR(&_33$$38);
										zephir_create_array(&_33$$38, 1, 0);
										zephir_array_fast_append(&_33$$38, &matchPosition);
										ZEPHIR_CALL_USER_FUNC_ARRAY(&_32$$38, &converter, &_33$$38);
										zephir_check_call_status();
										zephir_array_update_zval(&parts, &part, &_32$$38, PH_COPY | PH_SEPARATE);
										continue;
									}
								}
								zephir_array_update_zval(&parts, &part, &matchPosition, PH_COPY | PH_SEPARATE);
							} else {
								if (Z_TYPE_P(&converters) == IS_ARRAY) {
									ZEPHIR_OBS_NVAR(&converter);
									if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
										ZEPHIR_INIT_NVAR(&_34$$41);
										ZEPHIR_INIT_NVAR(&_35$$41);
										zephir_create_array(&_35$$41, 1, 0);
										zephir_array_fast_append(&_35$$41, &position);
										ZEPHIR_CALL_USER_FUNC_ARRAY(&_34$$41, &converter, &_35$$41);
										zephir_check_call_status();
										zephir_array_update_zval(&parts, &part, &_34$$41, PH_COPY | PH_SEPARATE);
									}
								} else {
									if (Z_TYPE_P(&position) == IS_LONG) {
										zephir_array_unset(&parts, &part, PH_SEPARATE);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
									}
								}
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _23$$32, "rewind", NULL, 0);
						zephir_check_call_status();
						_37$$32 = 1;
						while (1) {
							if (_37$$32) {
								_37$$32 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _23$$32, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_36$$32, _23$$32, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_36$$32)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&part, _23$$32, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&position, _23$$32, "current", NULL, 0);
							zephir_check_call_status();
								if (UNEXPECTED(Z_TYPE_P(&part) != IS_STRING)) {
									ZEPHIR_INIT_NVAR(&_38$$45);
									object_init_ex(&_38$$45, phalcon_mvc_router_exception_ce);
									ZEPHIR_INIT_NVAR(&_39$$45);
									ZEPHIR_CONCAT_SV(&_39$$45, "Wrong key in paths: ", &part);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_38$$45, "__construct", &_30, 32, &_39$$45);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_38$$45, "phalcon/Mvc/Router.zep", 934);
									ZEPHIR_MM_RESTORE();
									return;
								}
								_40$$44 = Z_TYPE_P(&position) != IS_STRING;
								if (_40$$44) {
									_40$$44 = Z_TYPE_P(&position) != IS_LONG;
								}
								if (_40$$44) {
									continue;
								}
								ZEPHIR_OBS_NVAR(&matchPosition);
								if (zephir_array_isset_fetch(&matchPosition, &matches, &position, 0)) {
									if (Z_TYPE_P(&converters) == IS_ARRAY) {
										ZEPHIR_OBS_NVAR(&converter);
										if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
											ZEPHIR_INIT_NVAR(&_41$$49);
											ZEPHIR_INIT_NVAR(&_42$$49);
											zephir_create_array(&_42$$49, 1, 0);
											zephir_array_fast_append(&_42$$49, &matchPosition);
											ZEPHIR_CALL_USER_FUNC_ARRAY(&_41$$49, &converter, &_42$$49);
											zephir_check_call_status();
											zephir_array_update_zval(&parts, &part, &_41$$49, PH_COPY | PH_SEPARATE);
											continue;
										}
									}
									zephir_array_update_zval(&parts, &part, &matchPosition, PH_COPY | PH_SEPARATE);
								} else {
									if (Z_TYPE_P(&converters) == IS_ARRAY) {
										ZEPHIR_OBS_NVAR(&converter);
										if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
											ZEPHIR_INIT_NVAR(&_43$$52);
											ZEPHIR_INIT_NVAR(&_44$$52);
											zephir_create_array(&_44$$52, 1, 0);
											zephir_array_fast_append(&_44$$52, &position);
											ZEPHIR_CALL_USER_FUNC_ARRAY(&_43$$52, &converter, &_44$$52);
											zephir_check_call_status();
											zephir_array_update_zval(&parts, &part, &_43$$52, PH_COPY | PH_SEPARATE);
										}
									} else {
										if (Z_TYPE_P(&position) == IS_LONG) {
											zephir_array_unset(&parts, &part, PH_SEPARATE);
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
										}
									}
								}
						}
					}
					ZEPHIR_INIT_NVAR(&position);
					ZEPHIR_INIT_NVAR(&part);
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 218, &matches);
				}
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 215, &route);
				break;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_46 = 1;
		while (1) {
			if (_46) {
				_46 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_45, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_45)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&route, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&params);
				array_init(&params);
				ZEPHIR_INIT_NVAR(&matches);
				ZVAL_NULL(&matches);
				ZEPHIR_CALL_METHOD(&methods, &route, "getHttpMethods", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&methods) != IS_NULL) {
					ZVAL_BOOL(&_48$$56, 1);
					ZEPHIR_CALL_METHOD(&_47$$56, &request, "isMethod", &_49, 0, &methods, &_48$$56);
					zephir_check_call_status();
					if (ZEPHIR_IS_FALSE_IDENTICAL(&_47$$56)) {
						continue;
					}
				}
				ZEPHIR_CALL_METHOD(&hostname, &route, "getHostName", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&hostname) != IS_NULL) {
					if (Z_TYPE_P(&currentHostName) == IS_NULL) {
						ZEPHIR_CALL_METHOD(&currentHostName, &request, "getHttpHost", &_50, 0);
						zephir_check_call_status();
					}
					if (!(zephir_is_true(&currentHostName))) {
						continue;
					}
					if (zephir_memnstr_str(&hostname, SL("("), "phalcon/Mvc/Router.zep", 840)) {
						if (!(zephir_memnstr_str(&hostname, SL("#"), "phalcon/Mvc/Router.zep", 841))) {
							ZEPHIR_INIT_NVAR(&regexHostName);
							ZEPHIR_CONCAT_SV(&regexHostName, "#^", &hostname);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if (!(zephir_memnstr_str(&hostname, SL(":"), "phalcon/Mvc/Router.zep", 844))) {
								zephir_concat_self_str(&regexHostName, SL("(:[[:digit:]]+)?"));
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
							}
							zephir_concat_self_str(&regexHostName, SL("$#i"));
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZEPHIR_CPY_WRT(&regexHostName, &hostname);
						}
						ZEPHIR_INIT_NVAR(&_51$$61);
						ZEPHIR_INIT_NVAR(&matched);
						zephir_preg_match(&matched, &regexHostName, &currentHostName, &_51$$61, 0, 0 , 0 );
					} else {
						_52$$65 = ZEPHIR_IS_EQUAL(&currentHostName, &hostname);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_INIT_NVAR(&matched);
						ZVAL_BOOL(&matched, _52$$65);
					}
					if (!(zephir_is_true(&matched))) {
						continue;
					}
				}
				if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_53$$67);
					ZVAL_STRING(&_53$$67, "router:beforeCheckRoute");
					ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_54, 0, &_53$$67, this_ptr, &route);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&pattern, &route, "getCompiledPattern", NULL, 0);
				zephir_check_call_status();
				if (zephir_memnstr_str(&pattern, SL("^"), "phalcon/Mvc/Router.zep", 872)) {
					ZEPHIR_INIT_NVAR(&routeFound);
					zephir_preg_match(&routeFound, &pattern, &handledUri, &matches, 0, 0 , 0 );
				} else {
					_55$$69 = ZEPHIR_IS_EQUAL(&pattern, &handledUri);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&routeFound);
					ZVAL_BOOL(&routeFound, _55$$69);
				}
				if (zephir_is_true(&routeFound)) {
					if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
						ZEPHIR_INIT_NVAR(&_56$$71);
						ZVAL_STRING(&_56$$71, "router:matchedRoute");
						ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_57, 0, &_56$$71, this_ptr, &route);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&beforeMatch, &route, "getBeforeMatch", NULL, 0);
					zephir_check_call_status();
					if (Z_TYPE_P(&beforeMatch) != IS_NULL) {
						if (UNEXPECTED(!(zephir_is_callable(&beforeMatch)))) {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "Before-Match callback is not callable in matched route", "phalcon/Mvc/Router.zep", 894);
							return;
						}
						ZEPHIR_INIT_NVAR(&_58$$72);
						zephir_create_array(&_58$$72, 3, 0);
						zephir_array_fast_append(&_58$$72, &handledUri);
						zephir_array_fast_append(&_58$$72, &route);
						zephir_array_fast_append(&_58$$72, this_ptr);
						ZEPHIR_INIT_NVAR(&routeFound);
						ZEPHIR_CALL_USER_FUNC_ARRAY(&routeFound, &beforeMatch, &_58$$72);
						zephir_check_call_status();
					}
				} else {
					if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
						ZEPHIR_INIT_NVAR(&_59$$75);
						ZVAL_STRING(&_59$$75, "router:notMatchedRoute");
						ZEPHIR_CALL_METHOD(&routeFound, &eventsManager, "fire", &_60, 0, &_59$$75, this_ptr, &route);
						zephir_check_call_status();
					}
				}
				if (zephir_is_true(&routeFound)) {
					ZEPHIR_CALL_METHOD(&paths, &route, "getPaths", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&parts, &paths);
					if (Z_TYPE_P(&matches) == IS_ARRAY) {
						ZEPHIR_CALL_METHOD(&converters, &route, "getConverters", NULL, 0);
						zephir_check_call_status();
						if (Z_TYPE_P(&paths) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_62$$77);
							zephir_string_to_char_array(&_62$$77, &paths);
							_61$$77 = &_62$$77;
						} else {
							_61$$77 = &paths;
						}
						zephir_is_iterable(_61$$77, 0, "phalcon/Mvc/Router.zep", 986);
						if (Z_TYPE_P(_61$$77) == IS_ARRAY) {
							ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_61$$77), _64$$77, _65$$77, _63$$77)
							{
								ZEPHIR_INIT_NVAR(&part);
								if (_65$$77 != NULL) { 
									ZVAL_STR_COPY(&part, _65$$77);
								} else {
									ZVAL_LONG(&part, _64$$77);
								}
								ZEPHIR_INIT_NVAR(&position);
								ZVAL_COPY(&position, _63$$77);
								if (UNEXPECTED(Z_TYPE_P(&part) != IS_STRING)) {
									ZEPHIR_INIT_NVAR(&_66$$79);
									object_init_ex(&_66$$79, phalcon_mvc_router_exception_ce);
									ZEPHIR_INIT_NVAR(&_67$$79);
									ZEPHIR_CONCAT_SV(&_67$$79, "Wrong key in paths: ", &part);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_66$$79, "__construct", &_30, 32, &_67$$79);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_66$$79, "phalcon/Mvc/Router.zep", 934);
									ZEPHIR_MM_RESTORE();
									return;
								}
								_68$$78 = Z_TYPE_P(&position) != IS_STRING;
								if (_68$$78) {
									_68$$78 = Z_TYPE_P(&position) != IS_LONG;
								}
								if (_68$$78) {
									continue;
								}
								ZEPHIR_OBS_NVAR(&matchPosition);
								if (zephir_array_isset_fetch(&matchPosition, &matches, &position, 0)) {
									if (Z_TYPE_P(&converters) == IS_ARRAY) {
										ZEPHIR_OBS_NVAR(&converter);
										if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
											ZEPHIR_INIT_NVAR(&_69$$83);
											ZEPHIR_INIT_NVAR(&_70$$83);
											zephir_create_array(&_70$$83, 1, 0);
											zephir_array_fast_append(&_70$$83, &matchPosition);
											ZEPHIR_CALL_USER_FUNC_ARRAY(&_69$$83, &converter, &_70$$83);
											zephir_check_call_status();
											zephir_array_update_zval(&parts, &part, &_69$$83, PH_COPY | PH_SEPARATE);
											continue;
										}
									}
									zephir_array_update_zval(&parts, &part, &matchPosition, PH_COPY | PH_SEPARATE);
								} else {
									if (Z_TYPE_P(&converters) == IS_ARRAY) {
										ZEPHIR_OBS_NVAR(&converter);
										if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
											ZEPHIR_INIT_NVAR(&_71$$86);
											ZEPHIR_INIT_NVAR(&_72$$86);
											zephir_create_array(&_72$$86, 1, 0);
											zephir_array_fast_append(&_72$$86, &position);
											ZEPHIR_CALL_USER_FUNC_ARRAY(&_71$$86, &converter, &_72$$86);
											zephir_check_call_status();
											zephir_array_update_zval(&parts, &part, &_71$$86, PH_COPY | PH_SEPARATE);
										}
									} else {
										if (Z_TYPE_P(&position) == IS_LONG) {
											zephir_array_unset(&parts, &part, PH_SEPARATE);
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
										}
									}
								}
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _61$$77, "rewind", NULL, 0);
							zephir_check_call_status();
							_74$$77 = 1;
							while (1) {
								if (_74$$77) {
									_74$$77 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _61$$77, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_73$$77, _61$$77, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_73$$77)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&part, _61$$77, "key", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&position, _61$$77, "current", NULL, 0);
								zephir_check_call_status();
									if (UNEXPECTED(Z_TYPE_P(&part) != IS_STRING)) {
										ZEPHIR_INIT_NVAR(&_75$$90);
										object_init_ex(&_75$$90, phalcon_mvc_router_exception_ce);
										ZEPHIR_INIT_NVAR(&_76$$90);
										ZEPHIR_CONCAT_SV(&_76$$90, "Wrong key in paths: ", &part);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										ZEPHIR_CALL_METHOD(NULL, &_75$$90, "__construct", &_30, 32, &_76$$90);
										zephir_check_call_status();
										zephir_throw_exception_debug(&_75$$90, "phalcon/Mvc/Router.zep", 934);
										ZEPHIR_MM_RESTORE();
										return;
									}
									_77$$89 = Z_TYPE_P(&position) != IS_STRING;
									if (_77$$89) {
										_77$$89 = Z_TYPE_P(&position) != IS_LONG;
									}
									if (_77$$89) {
										continue;
									}
									ZEPHIR_OBS_NVAR(&matchPosition);
									if (zephir_array_isset_fetch(&matchPosition, &matches, &position, 0)) {
										if (Z_TYPE_P(&converters) == IS_ARRAY) {
											ZEPHIR_OBS_NVAR(&converter);
											if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
												ZEPHIR_INIT_NVAR(&_78$$94);
												ZEPHIR_INIT_NVAR(&_79$$94);
												zephir_create_array(&_79$$94, 1, 0);
												zephir_array_fast_append(&_79$$94, &matchPosition);
												ZEPHIR_CALL_USER_FUNC_ARRAY(&_78$$94, &converter, &_79$$94);
												zephir_check_call_status();
												zephir_array_update_zval(&parts, &part, &_78$$94, PH_COPY | PH_SEPARATE);
												continue;
											}
										}
										zephir_array_update_zval(&parts, &part, &matchPosition, PH_COPY | PH_SEPARATE);
									} else {
										if (Z_TYPE_P(&converters) == IS_ARRAY) {
											ZEPHIR_OBS_NVAR(&converter);
											if (zephir_array_isset_fetch(&converter, &converters, &part, 0)) {
												ZEPHIR_INIT_NVAR(&_80$$97);
												ZEPHIR_INIT_NVAR(&_81$$97);
												zephir_create_array(&_81$$97, 1, 0);
												zephir_array_fast_append(&_81$$97, &position);
												ZEPHIR_CALL_USER_FUNC_ARRAY(&_80$$97, &converter, &_81$$97);
												zephir_check_call_status();
												zephir_array_update_zval(&parts, &part, &_80$$97, PH_COPY | PH_SEPARATE);
											}
										} else {
											if (Z_TYPE_P(&position) == IS_LONG) {
												zephir_array_unset(&parts, &part, PH_SEPARATE);
												if (UNEXPECTED(EG(exception))) {
													ZEPHIR_MM_RESTORE();
													return;
												}
											}
										}
									}
							}
						}
						ZEPHIR_INIT_NVAR(&position);
						ZEPHIR_INIT_NVAR(&part);
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 218, &matches);
					}
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 215, &route);
					break;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&route);
	if (zephir_is_true(&routeFound)) {
		if (1) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 214, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 214, &__$false);
		}
	} else {
		if (0) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 214, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 214, &__$false);
		}
	}
	if (!(zephir_is_true(&routeFound))) {
		zephir_read_property_cached(&_82$$102, this_ptr, _zephir_prop_7, 219, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&notFoundPaths, &_82$$102);
		if (Z_TYPE_P(&notFoundPaths) != IS_NULL) {
			ZEPHIR_CALL_CE_STATIC(&parts, phalcon_mvc_router_route_ce, "getRoutePaths", NULL, 0, &notFoundPaths);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&routeFound);
			ZVAL_BOOL(&routeFound, 1);
		}
	}
	zephir_read_property_cached(&_83, this_ptr, _zephir_prop_8, 205, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 220, &_83);
	zephir_read_property_cached(&_84, this_ptr, _zephir_prop_10, 206, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_11, 221, &_84);
	zephir_read_property_cached(&_85, this_ptr, _zephir_prop_12, 207, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_13, 222, &_85);
	zephir_read_property_cached(&_86, this_ptr, _zephir_prop_14, 208, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_15, 223, &_86);
	zephir_read_property_cached(&_87, this_ptr, _zephir_prop_16, 209, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_17, 224, &_87);
	if (zephir_is_true(&routeFound)) {
		zephir_memory_observe(&vnamespace);
		if (zephir_array_isset_string_fetch(&vnamespace, &parts, SL("namespace"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 220, &vnamespace);
			zephir_array_unset_string(&parts, SL("namespace"), PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_memory_observe(&module);
		if (zephir_array_isset_string_fetch(&module, &parts, SL("module"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_11, 221, &module);
			zephir_array_unset_string(&parts, SL("module"), PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_memory_observe(&controller);
		if (zephir_array_isset_string_fetch(&controller, &parts, SL("controller"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_13, 222, &controller);
			zephir_array_unset_string(&parts, SL("controller"), PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_memory_observe(&action);
		if (zephir_array_isset_string_fetch(&action, &parts, SL("action"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_15, 223, &action);
			zephir_array_unset_string(&parts, SL("action"), PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_memory_observe(&paramsStr);
		if (zephir_array_isset_string_fetch(&paramsStr, &parts, SL("params"), 0)) {
			if (Z_TYPE_P(&paramsStr) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_88$$110);
				ZVAL_STRING(&_88$$110, "/");
				ZEPHIR_INIT_VAR(&strParams);
				zephir_fast_trim(&strParams, &paramsStr, &_88$$110, ZEPHIR_TRIM_BOTH);
				if (!ZEPHIR_IS_STRING_IDENTICAL(&strParams, "")) {
					ZEPHIR_INIT_NVAR(&params);
					zephir_fast_explode_str(&params, SL("/"), &strParams, NULL);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			}
			zephir_array_unset_string(&parts, SL("params"), PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		if (zephir_fast_count_int(&params)) {
			ZEPHIR_INIT_VAR(&_89$$112);
			zephir_fast_array_merge(&_89$$112, &params, &parts);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_17, 224, &_89$$112);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_17, 224, &parts);
		}
	}
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_90$$114);
		ZVAL_STRING(&_90$$114, "router:afterCheckRoutes");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_90$$114, this_ptr);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns whether controller name should not be mangled
 */
PHP_METHOD(Phalcon_Mvc_Router, isExactControllerName)
{

	RETURN_BOOL(1);
}

/**
 * Mounts a group of routes in the router
 *
 * @param GroupInterface group
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, mount)
{
	zend_bool _6$$5, _11$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *group, group_sub, groupRoutes, beforeMatch, hostname, routes, route, eventsManager, _0, _12, _1$$3, *_2$$5, _3$$5, *_4$$5, _5$$5, *_7$$8, _8$$8, *_9$$8, _10$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&group_sub);
	ZVAL_UNDEF(&groupRoutes);
	ZVAL_UNDEF(&beforeMatch);
	ZVAL_UNDEF(&hostname);
	ZVAL_UNDEF(&routes);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_10$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("routes", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(group, phalcon_mvc_router_groupinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &group);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 216, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "router:beforeMount");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_1$$3, this_ptr, group);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&groupRoutes, group, "getRoutes", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!(zephir_fast_count_int(&groupRoutes)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "The group of routes does not contain any routes", "phalcon/Mvc/Router.zep", 1119);
		return;
	}
	ZEPHIR_CALL_METHOD(&beforeMatch, group, "getBeforeMatch", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&beforeMatch) != IS_NULL) {
		if (Z_TYPE_P(&groupRoutes) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_3$$5);
			zephir_string_to_char_array(&_3$$5, &groupRoutes);
			_2$$5 = &_3$$5;
		} else {
			_2$$5 = &groupRoutes;
		}
		zephir_is_iterable(_2$$5, 0, "phalcon/Mvc/Router.zep", 1131);
		if (Z_TYPE_P(_2$$5) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2$$5), _4$$5)
			{
				ZEPHIR_INIT_NVAR(&route);
				ZVAL_COPY(&route, _4$$5);
				ZEPHIR_CALL_METHOD(NULL, &route, "beforeMatch", NULL, 0, &beforeMatch);
				zephir_check_call_status();
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _2$$5, "rewind", NULL, 0);
			zephir_check_call_status();
			_6$$5 = 1;
			while (1) {
				if (_6$$5) {
					_6$$5 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _2$$5, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_5$$5, _2$$5, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_5$$5)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&route, _2$$5, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &route, "beforeMatch", NULL, 0, &beforeMatch);
					zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&route);
	}
	ZEPHIR_CALL_METHOD(&hostname, group, "getHostName", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&hostname) != IS_NULL) {
		if (Z_TYPE_P(&groupRoutes) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_8$$8);
			zephir_string_to_char_array(&_8$$8, &groupRoutes);
			_7$$8 = &_8$$8;
		} else {
			_7$$8 = &groupRoutes;
		}
		zephir_is_iterable(_7$$8, 0, "phalcon/Mvc/Router.zep", 1140);
		if (Z_TYPE_P(_7$$8) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_7$$8), _9$$8)
			{
				ZEPHIR_INIT_NVAR(&route);
				ZVAL_COPY(&route, _9$$8);
				ZEPHIR_CALL_METHOD(NULL, &route, "setHostName", NULL, 0, &hostname);
				zephir_check_call_status();
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _7$$8, "rewind", NULL, 0);
			zephir_check_call_status();
			_11$$8 = 1;
			while (1) {
				if (_11$$8) {
					_11$$8 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _7$$8, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_10$$8, _7$$8, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_10$$8)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&route, _7$$8, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &route, "setHostName", NULL, 0, &hostname);
					zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&route);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 204, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&routes, &_0);
	ZEPHIR_INIT_VAR(&_12);
	zephir_fast_array_merge(&_12, &routes, &groupRoutes);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 204, &_12);
	RETURN_THIS();
}

/**
 * Set a group of paths to be returned when none of the defined routes are
 * matched
 *
 * @param array|string|null paths
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, notFound)
{
	zend_bool _0;
	zval *paths, paths_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&paths_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("notFoundPaths", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(paths)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &paths);
	_0 = Z_TYPE_P(paths) != IS_ARRAY;
	if (_0) {
		_0 = Z_TYPE_P(paths) != IS_STRING;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_mvc_router_exception_ce, "The not-found paths must be an array or string", "phalcon/Mvc/Router.zep", 1162);
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 219, paths);
	RETURN_THISW();
}

/**
 * Set whether router must remove the extra slashes in the handled routes
 *
 * @param bool remove
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, removeExtraSlashes)
{
	zval *remove_param = NULL, __$true, __$false;
	zend_bool remove;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("removeExtraSlashes", 18, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(remove)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &remove_param);
	if (UNEXPECTED(Z_TYPE_P(remove_param) != IS_TRUE && Z_TYPE_P(remove_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'remove' must be of the type bool"));
		RETURN_NULL();
	}
	remove = (Z_TYPE_P(remove_param) == IS_TRUE);
	if (remove) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 213, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 213, &__$false);
	}
	RETURN_THISW();
}

/**
 * Sets the default action name
 *
 * @param string actionName
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, setDefaultAction)
{
	zval actionName_zv;
	zend_string *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&actionName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultAction", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(actionName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&actionName_zv, actionName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 208, &actionName_zv);
	RETURN_THISW();
}

/**
 * Sets the default controller name
 *
 * @param string controllerName
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, setDefaultController)
{
	zval controllerName_zv;
	zend_string *controllerName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultController", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(controllerName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&controllerName_zv, controllerName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 207, &controllerName_zv);
	RETURN_THISW();
}

/**
 * Sets the name of the default module
 *
 * @param string moduleName
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, setDefaultModule)
{
	zval moduleName_zv;
	zend_string *moduleName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&moduleName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultModule", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(moduleName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&moduleName_zv, moduleName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 206, &moduleName_zv);
	RETURN_THISW();
}

/**
 * Sets the name of the default namespace
 *
 * @parma string namespaceName
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, setDefaultNamespace)
{
	zval namespaceName_zv;
	zend_string *namespaceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&namespaceName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultNamespace", 16, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(namespaceName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&namespaceName_zv, namespaceName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 205, &namespaceName_zv);
	RETURN_THISW();
}

/**
 * Sets an array of default paths. If a route is missing a path the router
 * will use the defined here. This method must not be used to set a 404
 * route
 *
 *```php
 * $router->setDefaults(
 *     [
 *         "module" => "common",
 *         "action" => "index",
 *     ]
 * );
 *```
 *
 * @param array defaults
 *
 * @return RouterInterface
 */
PHP_METHOD(Phalcon_Mvc_Router, setDefaults)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *defaults_param = NULL, namespaceName, module, controller, action, params;
	zval defaults;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&namespaceName);
	ZVAL_UNDEF(&module);
	ZVAL_UNDEF(&controller);
	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultNamespace", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("defaultModule", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("defaultController", 17, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("defaultAction", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("defaultParams", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(defaults, defaults_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &defaults_param);
	ZEPHIR_OBS_COPY_OR_DUP(&defaults, defaults_param);
	zephir_memory_observe(&namespaceName);
	if (zephir_array_isset_string_fetch(&namespaceName, &defaults, SL("namespace"), 0)) {
		zephir_cast_to_string(&_0$$3, &namespaceName);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 205, &_0$$3);
	}
	zephir_memory_observe(&module);
	if (zephir_array_isset_string_fetch(&module, &defaults, SL("module"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 206, &module);
	}
	zephir_memory_observe(&controller);
	if (zephir_array_isset_string_fetch(&controller, &defaults, SL("controller"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 207, &controller);
	}
	zephir_memory_observe(&action);
	if (zephir_array_isset_string_fetch(&action, &defaults, SL("action"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 208, &action);
	}
	zephir_memory_observe(&params);
	if (zephir_array_isset_string_fetch(&params, &defaults, SL("params"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 209, &params);
	}
	RETURN_THIS();
}

/**
 * Sets the events manager
 *
 * @param ManagerInterface eventsManager
 *
 * @return void
 */
PHP_METHOD(Phalcon_Mvc_Router, setEventsManager)
{
	zval *eventsManager, eventsManager_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventsManager_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("eventsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(eventsManager, phalcon_events_managerinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &eventsManager);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 216, eventsManager);
}

/**
 * @param array $routeNames
 *
 * @return Router
 */
PHP_METHOD(Phalcon_Mvc_Router, setKeyRouteNames)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *routeNames_param = NULL;
	zval routeNames;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routeNames);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("keyRouteNames", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(routeNames, routeNames_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &routeNames_param);
	zephir_get_arrval(&routeNames, routeNames_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 212, &routeNames);
	RETURN_THIS();
}

/**
 * @param array $routeIds
 *
 * @return Router
 */
PHP_METHOD(Phalcon_Mvc_Router, setKeyRouteIds)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *routeIds_param = NULL;
	zval routeIds;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routeIds);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("keyRouteIds", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(routeIds, routeIds_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &routeIds_param);
	zephir_get_arrval(&routeIds, routeIds_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 211, &routeIds);
	RETURN_THIS();
}

/**
 * Sets the URI source. One of the URI_SOURCE_* constants
 *
 * ```php
 * $router->setUriSource(
 *     Router::URI_SOURCE_SERVER_REQUEST_URI
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Router, setUriSource)
{
	zval *uriSource_param = NULL, _0;
	zend_long uriSource;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uriSource", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(uriSource)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &uriSource_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, uriSource);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 210, &_0);
	RETURN_THISW();
}

/**
 * Checks if the router matches any of the defined routes
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Router, wasMatched)
{

	RETURN_MEMBER(getThis(), "wasMatched");
}

zend_object *zephir_init_properties_Phalcon_Mvc_Router(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("routes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("routes"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("params"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("params"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("matches"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("matches"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("keyRouteIds"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("keyRouteIds"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("keyRouteNames"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("keyRouteNames"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("defaultParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("defaultParams"), &_11$$8);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

