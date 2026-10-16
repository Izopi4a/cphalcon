
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
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "Zend/zend_closures.h"
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
 * Phalcon\Mvc\Micro
 *
 * With Phalcon you can create "Micro-Framework like" applications. By doing
 * this, you only need to write a minimal amount of code to create a PHP
 * application. Micro applications are suitable to small applications, APIs and
 * prototypes in a practical way.
 *
 *```php
 * $app = new \Phalcon\Mvc\Micro();
 *
 * $app->get(
 *     "/say/welcome/{name}",
 *     function ($name) {
 *         echo "<h1>Welcome $name!</h1>";
 *     }
 * );
 *
 * $app->handle("/say/welcome/Phalcon");
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Micro)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, Micro, phalcon, mvc_micro, phalcon_di_injectable_ce, phalcon_mvc_micro_method_entry, 0);

	/**
	 * @var callable|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("activeHandler"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("afterBindingHandlers"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("afterHandlers"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("beforeHandlers"), ZEND_ACC_PROTECTED);
	/**
	 * @var DiInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("container"), ZEND_ACC_PROTECTED);
	/**
	 * @var callable|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("errorHandler"), ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("finishHandlers"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("handlers"), ZEND_ACC_PROTECTED);
	/**
	 * @var BinderInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("modelBinder"), ZEND_ACC_PROTECTED);
	/**
	 * @var callable|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("notFoundHandler"), ZEND_ACC_PROTECTED);
	/**
	 * @var callable|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("responseHandler"), ZEND_ACC_PROTECTED);
	/**
	 * @var mixed|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("returnedValue"), ZEND_ACC_PROTECTED);
	/**
	 * @var RouterInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_micro_ce, SL("router"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_micro_ce, SL("stopped"), 0, ZEND_ACC_PROTECTED);
	phalcon_mvc_micro_ce->create_object = zephir_init_properties_Phalcon_Mvc_Micro;

	zend_class_implements(phalcon_mvc_micro_ce, 1, zend_ce_arrayaccess);
	zend_class_implements(phalcon_mvc_micro_ce, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Micro constructor
 */
PHP_METHOD(Phalcon_Mvc_Micro, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container = NULL, container_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &container);
	if (!container) {
		container = &container_sub;
		container = &__$null;
	}
	if (Z_TYPE_P(container) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setDi", NULL, 0, container);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Appends an 'after' middleware to be called after execute the route
 *
 * @param callable|MiddlewareInterface handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, after)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_array_append(this_ptr, SL("afterHandlers"), handler);
	RETURN_THISW();
}

/**
 * Appends a afterBinding middleware to be called after model binding
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, afterBinding)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_array_append(this_ptr, SL("afterBindingHandlers"), handler);
	RETURN_THISW();
}

/**
 * Appends a before middleware to be called before execute the route
 *
 * @param callable|MiddlewareInterface handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, before)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_array_append(this_ptr, SL("beforeHandlers"), handler);
	RETURN_THISW();
}

/**
 * Maps a route to a handler that only matches if the HTTP method is DELETE
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, delete)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addDelete", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Sets a handler that will be called when an exception is thrown handling
 * the route
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, error)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("errorHandler", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 683, handler);
	RETURN_THISW();
}

/**
 * Appends a 'finish' middleware to be called when the request is finished
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, finish)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_array_append(this_ptr, SL("finishHandlers"), handler);
	RETURN_THISW();
}

/**
 * Maps a route to a handler that only matches if the HTTP method is GET
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, get)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addGet", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Return the handler that will be called for the matched route
 *
 * @return callable
 */
PHP_METHOD(Phalcon_Mvc_Micro, getActiveHandler)
{

	RETURN_MEMBER(getThis(), "activeHandler");
}

/**
 * Returns bound models from binder instance
 */
PHP_METHOD(Phalcon_Mvc_Micro, getBoundModels)
{
	zval modelBinder, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&modelBinder);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelBinder", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 684, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&modelBinder, &_0);
	if (Z_TYPE_P(&modelBinder) == IS_NULL) {
		array_init(return_value);
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(&modelBinder, "getBoundModels", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Mvc_Micro, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Sets the events manager
 */
PHP_METHOD(Phalcon_Mvc_Micro, setEventsManager)
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 685, eventsManager);
}

/**
 * Returns the internal handlers attached to the application
 */
PHP_METHOD(Phalcon_Mvc_Micro, getHandlers)
{

	RETURN_MEMBER_TYPED(getThis(), "handlers", IS_ARRAY);
}

/**
 * Gets model binder
 */
PHP_METHOD(Phalcon_Mvc_Micro, getModelBinder)
{

	RETURN_MEMBER(getThis(), "modelBinder");
}

/**
 * Returns the value returned by the executed handler
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Micro, getReturnedValue)
{

	RETURN_MEMBER(getThis(), "returnedValue");
}

/**
 * Returns the internal router used by the application
 */
PHP_METHOD(Phalcon_Mvc_Micro, getRouter)
{
	zval _0, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("router", 6, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 686, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "router");
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "getSharedService", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 686, &_1$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 686, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "clear", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_0, 686, PH_NOISY_CC | PH_READONLY);
		ZVAL_BOOL(&_5$$3, 1);
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "removeExtraSlashes", NULL, 0, &_5$$3);
		zephir_check_call_status();
	}
	RETURN_MM_MEMBER(getThis(), "router");
}

/**
 * Obtains a service from the DI
 *
 * @return object
 */
PHP_METHOD(Phalcon_Mvc_Micro, getService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval serviceName_zv, _0, _2, _1$$3;
	zend_string *serviceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&serviceName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(serviceName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&serviceName_zv);
	ZVAL_STR_COPY(&serviceName_zv, serviceName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_di_factorydefault_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 454);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 687, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_2, "get", NULL, 0, &serviceName_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Obtains a shared service from the DI
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Micro, getSharedService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval serviceName_zv, _0, _2, _1$$3;
	zend_string *serviceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&serviceName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(serviceName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&serviceName_zv);
	ZVAL_STR_COPY(&serviceName_zv, serviceName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_di_factorydefault_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 454);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 687, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_2, "getShared", NULL, 0, &serviceName_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Handle the whole request
 *
 * @param string uri
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Micro, handle)
{
	zval _90$$59, _97$$64, _106$$69;
	zend_class_entry *_31$$21;
	zend_bool _93$$4, _24$$7, _29$$7, _40$$7, _53$$7, _69$$7, _19$$11, _25$$16, _36$$25, _48$$31, _54$$36, _64$$42, _70$$47, _87$$57, _94$$62, _111$$80, _112$$80;
	zval bindCacheKey;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri_zv, __$true, __$false, container, status, router, matchedRoute, handler, beforeHandlers, params, returnedValue, e, afterHandlers, notFoundHandler, finishHandlers, finish, before, after, response, modelBinder, routeName, realHandler, methodName, lazyReturned, afterBindingHandlers, afterBinding, _0, _99, _1$$4, _5$$4, _6$$4, _81$$4, _84$$4, *_85$$4, *_86$$4, _92$$4, _2$$5, _3$$5, _4$$5, _7$$7, _8$$7, _11$$7, _15$$7, *_16$$7, _17$$7, *_18$$7, _23$$7, _44$$7, *_45$$7, _46$$7, *_47$$7, _52$$7, _60$$7, *_61$$7, _62$$7, *_63$$7, _68$$7, _9$$8, _10$$8, _12$$9, _13$$9, _14$$9, _22$$11, _20$$14, _21$$14, _28$$16, _26$$19, _27$$19, _30$$21, _32$$23, _33$$24, _34$$24, _35$$22, _37$$26, _38$$26, _39$$26, _41$$29, _42$$29, _43$$29, _51$$31, _49$$34, _50$$34, _57$$36, _55$$39, _56$$39, _58$$41, _59$$41, _67$$42, _65$$45, _66$$45, _73$$47, _71$$50, _72$$50, _74$$52, _78$$52, _75$$53, _76$$53, _77$$53, _79$$55, _80$$55, _82$$56, _83$$56, _91$$57, _88$$60, _89$$60, _98$$62, _95$$65, _96$$65, _100$$67, _103$$67, _101$$68, _102$$68, _104$$69, _105$$69, _107$$78, _108$$78, _109$$81, _110$$81, _113$$80;
	zend_string *uri = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&matchedRoute);
	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&beforeHandlers);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&returnedValue);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&afterHandlers);
	ZVAL_UNDEF(&notFoundHandler);
	ZVAL_UNDEF(&finishHandlers);
	ZVAL_UNDEF(&finish);
	ZVAL_UNDEF(&before);
	ZVAL_UNDEF(&after);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&modelBinder);
	ZVAL_UNDEF(&routeName);
	ZVAL_UNDEF(&realHandler);
	ZVAL_UNDEF(&methodName);
	ZVAL_UNDEF(&lazyReturned);
	ZVAL_UNDEF(&afterBindingHandlers);
	ZVAL_UNDEF(&afterBinding);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_99);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_81$$4);
	ZVAL_UNDEF(&_84$$4);
	ZVAL_UNDEF(&_92$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_44$$7);
	ZVAL_UNDEF(&_46$$7);
	ZVAL_UNDEF(&_52$$7);
	ZVAL_UNDEF(&_60$$7);
	ZVAL_UNDEF(&_62$$7);
	ZVAL_UNDEF(&_68$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_28$$16);
	ZVAL_UNDEF(&_26$$19);
	ZVAL_UNDEF(&_27$$19);
	ZVAL_UNDEF(&_30$$21);
	ZVAL_UNDEF(&_32$$23);
	ZVAL_UNDEF(&_33$$24);
	ZVAL_UNDEF(&_34$$24);
	ZVAL_UNDEF(&_35$$22);
	ZVAL_UNDEF(&_37$$26);
	ZVAL_UNDEF(&_38$$26);
	ZVAL_UNDEF(&_39$$26);
	ZVAL_UNDEF(&_41$$29);
	ZVAL_UNDEF(&_42$$29);
	ZVAL_UNDEF(&_43$$29);
	ZVAL_UNDEF(&_51$$31);
	ZVAL_UNDEF(&_49$$34);
	ZVAL_UNDEF(&_50$$34);
	ZVAL_UNDEF(&_57$$36);
	ZVAL_UNDEF(&_55$$39);
	ZVAL_UNDEF(&_56$$39);
	ZVAL_UNDEF(&_58$$41);
	ZVAL_UNDEF(&_59$$41);
	ZVAL_UNDEF(&_67$$42);
	ZVAL_UNDEF(&_65$$45);
	ZVAL_UNDEF(&_66$$45);
	ZVAL_UNDEF(&_73$$47);
	ZVAL_UNDEF(&_71$$50);
	ZVAL_UNDEF(&_72$$50);
	ZVAL_UNDEF(&_74$$52);
	ZVAL_UNDEF(&_78$$52);
	ZVAL_UNDEF(&_75$$53);
	ZVAL_UNDEF(&_76$$53);
	ZVAL_UNDEF(&_77$$53);
	ZVAL_UNDEF(&_79$$55);
	ZVAL_UNDEF(&_80$$55);
	ZVAL_UNDEF(&_82$$56);
	ZVAL_UNDEF(&_83$$56);
	ZVAL_UNDEF(&_91$$57);
	ZVAL_UNDEF(&_88$$60);
	ZVAL_UNDEF(&_89$$60);
	ZVAL_UNDEF(&_98$$62);
	ZVAL_UNDEF(&_95$$65);
	ZVAL_UNDEF(&_96$$65);
	ZVAL_UNDEF(&_100$$67);
	ZVAL_UNDEF(&_103$$67);
	ZVAL_UNDEF(&_101$$68);
	ZVAL_UNDEF(&_102$$68);
	ZVAL_UNDEF(&_104$$69);
	ZVAL_UNDEF(&_105$$69);
	ZVAL_UNDEF(&_107$$78);
	ZVAL_UNDEF(&_108$$78);
	ZVAL_UNDEF(&_109$$81);
	ZVAL_UNDEF(&_110$$81);
	ZVAL_UNDEF(&_113$$80);
	ZVAL_UNDEF(&bindCacheKey);
	ZVAL_UNDEF(&_90$$59);
	ZVAL_UNDEF(&_97$$64);
	ZVAL_UNDEF(&_106$$69);
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
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("handlers", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("activeHandler", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("beforeHandlers", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("stopped", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("modelBinder", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("afterBindingHandlers", 20, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("returnedValue", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("afterHandlers", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("notFoundHandler", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("finishHandlers", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_12)) {
		_zephir_prop_12 = zend_string_init("errorHandler", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_13)) {
		_zephir_prop_13 = zend_string_init("responseHandler", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&uri_zv);
	ZVAL_STR_COPY(&uri_zv, uri);
	ZEPHIR_INIT_VAR(&status);
	ZVAL_NULL(&status);
	ZEPHIR_INIT_VAR(&returnedValue);
	ZEPHIR_INIT_VAR(&realHandler);
	ZVAL_NULL(&realHandler);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "A dependency injection container is required to access micro services", "phalcon/Mvc/Micro.zep", 398);
		return;
	}

	/* try_start_1: */

		ZEPHIR_INIT_NVAR(&returnedValue);
		ZVAL_NULL(&returnedValue);
		zephir_read_property_cached(&_1$$4, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_1$$4) != IS_NULL) {
			zephir_read_property_cached(&_2$$5, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "micro:beforeHandleRoute");
			ZEPHIR_CALL_METHOD(&_3$$5, &_2$$5, "fire", NULL, 0, &_4$$5, this_ptr);
			zephir_check_call_status_or_jump(try_end_1);
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_3$$5)) {
				RETURN_MM_BOOL(0);
			}
		}
		ZEPHIR_INIT_VAR(&_6$$4);
		ZVAL_STRING(&_6$$4, "router");
		ZEPHIR_CALL_METHOD(&_5$$4, &container, "getShared", NULL, 0, &_6$$4);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CPY_WRT(&router, &_5$$4);
		ZEPHIR_CALL_METHOD(NULL, &router, "handle", NULL, 0, &uri_zv);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&matchedRoute, &router, "getMatchedRoute", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		if (Z_TYPE_P(&matchedRoute) != IS_NULL) {
			zephir_memory_observe(&handler);
			zephir_read_property_cached(&_7$$7, this_ptr, _zephir_prop_2, 688, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_8$$7, &matchedRoute, "getRouteId", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&handler, &_7$$7, &_8$$7, 0)))) {
				ZEPHIR_INIT_VAR(&_9$$8);
				object_init_ex(&_9$$8, phalcon_mvc_micro_exception_ce);
				ZEPHIR_INIT_VAR(&_10$$8);
				ZVAL_STRING(&_10$$8, "Matched route does not have an associated handler");
				ZEPHIR_CALL_METHOD(NULL, &_9$$8, "__construct", NULL, 32, &_10$$8);
				zephir_check_call_status_or_jump(try_end_1);
				zephir_throw_exception_debug(&_9$$8, "phalcon/Mvc/Micro.zep", 432);
				goto try_end_1;

			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 689, &handler);
			zephir_read_property_cached(&_11$$7, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			if (Z_TYPE_P(&_11$$7) != IS_NULL) {
				zephir_read_property_cached(&_12$$9, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_14$$9);
				ZVAL_STRING(&_14$$9, "micro:beforeExecuteRoute");
				ZEPHIR_CALL_METHOD(&_13$$9, &_12$$9, "fire", NULL, 0, &_14$$9, this_ptr);
				zephir_check_call_status_or_jump(try_end_1);
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_13$$9)) {
					RETURN_MM_BOOL(0);
				}
				ZEPHIR_OBS_NVAR(&handler);
				zephir_read_property_cached(&handler, this_ptr, _zephir_prop_3, 689, PH_NOISY_CC);
			}
			zephir_read_property_cached(&_15$$7, this_ptr, _zephir_prop_4, 690, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&beforeHandlers, &_15$$7);
			if (0) {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$true);
			} else {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$false);
			}
			if (Z_TYPE_P(&beforeHandlers) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_17$$7);
				zephir_string_to_char_array(&_17$$7, &beforeHandlers);
				_16$$7 = &_17$$7;
			} else {
				_16$$7 = &beforeHandlers;
			}
			zephir_is_iterable(_16$$7, 0, "phalcon/Mvc/Micro.zep", 484);
			if (Z_TYPE_P(_16$$7) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_16$$7), _18$$7)
				{
					ZEPHIR_INIT_NVAR(&before);
					ZVAL_COPY(&before, _18$$7);
					_19$$11 = Z_TYPE_P(&before) == IS_OBJECT;
					if (_19$$11) {
						_19$$11 = zephir_instance_of_ev(&before, phalcon_mvc_micro_middlewareinterface_ce);
					}
					if (_19$$11) {
						ZEPHIR_CALL_METHOD(&status, &before, "call", NULL, 0, this_ptr);
						zephir_check_call_status_or_jump(try_end_1);
					} else {
						if (UNEXPECTED(!(zephir_is_callable(&before)))) {
							ZEPHIR_INIT_NVAR(&_20$$14);
							object_init_ex(&_20$$14, phalcon_mvc_micro_exception_ce);
							ZEPHIR_INIT_NVAR(&_21$$14);
							ZVAL_STRING(&_21$$14, "'before' handler is not callable");
							ZEPHIR_CALL_METHOD(NULL, &_20$$14, "__construct", NULL, 32, &_21$$14);
							zephir_check_call_status_or_jump(try_end_1);
							zephir_throw_exception_debug(&_20$$14, "phalcon/Mvc/Micro.zep", 467);
							goto try_end_1;

						}
						ZEPHIR_INIT_NVAR(&status);
						ZEPHIR_CALL_USER_FUNC(&status, &before);
						zephir_check_call_status_or_jump(try_end_1);
					}
					zephir_read_property_cached(&_22$$11, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
					if (zephir_is_true(&_22$$11)) {
						RETURN_CCTOR(&status);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _16$$7, "rewind", NULL, 0);
				zephir_check_call_status();
				_24$$7 = 1;
				while (1) {
					if (_24$$7) {
						_24$$7 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _16$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_23$$7, _16$$7, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_23$$7)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&before, _16$$7, "current", NULL, 0);
					zephir_check_call_status();
						_25$$16 = Z_TYPE_P(&before) == IS_OBJECT;
						if (_25$$16) {
							_25$$16 = zephir_instance_of_ev(&before, phalcon_mvc_micro_middlewareinterface_ce);
						}
						if (_25$$16) {
							ZEPHIR_CALL_METHOD(&status, &before, "call", NULL, 0, this_ptr);
							zephir_check_call_status_or_jump(try_end_1);
						} else {
							if (UNEXPECTED(!(zephir_is_callable(&before)))) {
								ZEPHIR_INIT_NVAR(&_26$$19);
								object_init_ex(&_26$$19, phalcon_mvc_micro_exception_ce);
								ZEPHIR_INIT_NVAR(&_27$$19);
								ZVAL_STRING(&_27$$19, "'before' handler is not callable");
								ZEPHIR_CALL_METHOD(NULL, &_26$$19, "__construct", NULL, 32, &_27$$19);
								zephir_check_call_status_or_jump(try_end_1);
								zephir_throw_exception_debug(&_26$$19, "phalcon/Mvc/Micro.zep", 467);
								goto try_end_1;

							}
							ZEPHIR_INIT_NVAR(&status);
							ZEPHIR_CALL_USER_FUNC(&status, &before);
							zephir_check_call_status_or_jump(try_end_1);
						}
						zephir_read_property_cached(&_28$$16, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
						if (zephir_is_true(&_28$$16)) {
							RETURN_CCTOR(&status);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&before);
			ZEPHIR_CALL_METHOD(&params, &router, "getParams", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_read_property_cached(&_15$$7, this_ptr, _zephir_prop_6, 684, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&modelBinder, &_15$$7);
			_29$$7 = Z_TYPE_P(&handler) == IS_OBJECT;
			if (_29$$7) {
				_29$$7 = zephir_is_instance_of(&handler, SL("Closure"));
			}
			if (_29$$7) {
				_31$$21 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
				ZEPHIR_CALL_CE_STATIC(&_30$$21, _31$$21, "bind", NULL, 0, &handler, this_ptr);
				zephir_check_call_status_or_jump(try_end_1);
				ZEPHIR_CPY_WRT(&handler, &_30$$21);
				if (Z_TYPE_P(&modelBinder) != IS_NULL) {
					ZEPHIR_CALL_METHOD(&routeName, &matchedRoute, "getName", NULL, 0);
					zephir_check_call_status_or_jump(try_end_1);
					if (Z_TYPE_P(&routeName) != IS_NULL) {
						ZEPHIR_INIT_VAR(&_32$$23);
						ZEPHIR_CONCAT_SV(&_32$$23, "_PHMB_", &routeName);
						if (UNEXPECTED(EG(exception))) {
							goto try_end_1;
						}
						zephir_get_strval(&bindCacheKey, &_32$$23);
						if (UNEXPECTED(EG(exception))) {
							goto try_end_1;
						}
					} else {
						ZEPHIR_CALL_METHOD(&_33$$24, &matchedRoute, "getPattern", NULL, 0);
						zephir_check_call_status_or_jump(try_end_1);
						ZEPHIR_INIT_VAR(&_34$$24);
						ZEPHIR_CONCAT_SV(&_34$$24, "_PHMB_", &_33$$24);
						if (UNEXPECTED(EG(exception))) {
							goto try_end_1;
						}
						zephir_get_strval(&bindCacheKey, &_34$$24);
						if (UNEXPECTED(EG(exception))) {
							goto try_end_1;
						}
					}
					ZEPHIR_CALL_METHOD(&_35$$22, &modelBinder, "bindToHandler", NULL, 0, &handler, &params, &bindCacheKey);
					zephir_check_call_status_or_jump(try_end_1);
					ZEPHIR_CPY_WRT(&params, &_35$$22);
				}
			}
			if (Z_TYPE_P(&handler) == IS_ARRAY) {
				ZEPHIR_OBS_NVAR(&realHandler);
				zephir_array_fetch_long(&realHandler, &handler, 0, PH_NOISY, "phalcon/Mvc/Micro.zep", 515);
				_36$$25 = zephir_instance_of_ev(&realHandler, phalcon_mvc_controller_ce);
				if (_36$$25) {
					_36$$25 = Z_TYPE_P(&modelBinder) != IS_NULL;
				}
				if (_36$$25) {
					zephir_memory_observe(&methodName);
					zephir_array_fetch_long(&methodName, &handler, 1, PH_NOISY, "phalcon/Mvc/Micro.zep", 518);
					ZEPHIR_INIT_VAR(&_37$$26);
					zephir_get_class(&_37$$26, &realHandler, 0);
					ZEPHIR_INIT_VAR(&_38$$26);
					ZEPHIR_CONCAT_SVSV(&_38$$26, "_PHMB_", &_37$$26, "_", &methodName);
					if (UNEXPECTED(EG(exception))) {
						goto try_end_1;
					}
					zephir_get_strval(&bindCacheKey, &_38$$26);
					if (UNEXPECTED(EG(exception))) {
						goto try_end_1;
					}
					ZEPHIR_CALL_METHOD(&_39$$26, &modelBinder, "bindToHandler", NULL, 0, &realHandler, &params, &bindCacheKey, &methodName);
					zephir_check_call_status_or_jump(try_end_1);
					ZEPHIR_CPY_WRT(&params, &_39$$26);
				}
			}
			_40$$7 = Z_TYPE_P(&realHandler) != IS_NULL;
			if (_40$$7) {
				_40$$7 = zephir_instance_of_ev(&realHandler, phalcon_mvc_micro_lazyloader_ce);
			}
			if (_40$$7) {
				ZEPHIR_OBS_NVAR(&methodName);
				zephir_array_fetch_long(&methodName, &handler, 1, PH_NOISY, "phalcon/Mvc/Micro.zep", 535);
				ZEPHIR_CALL_METHOD(&lazyReturned, &realHandler, "callMethod", NULL, 0, &methodName, &params, &modelBinder);
				zephir_check_call_status_or_jump(try_end_1);
			} else {
				ZEPHIR_INIT_NVAR(&lazyReturned);
				ZEPHIR_CALL_USER_FUNC_ARRAY(&lazyReturned, &handler, &params);
				zephir_check_call_status_or_jump(try_end_1);
			}
			ZEPHIR_CPY_WRT(&returnedValue, &lazyReturned);
			zephir_read_property_cached(&_15$$7, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			if (Z_TYPE_P(&_15$$7) != IS_NULL) {
				zephir_read_property_cached(&_41$$29, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_43$$29);
				ZVAL_STRING(&_43$$29, "micro:afterBinding");
				ZEPHIR_CALL_METHOD(&_42$$29, &_41$$29, "fire", NULL, 0, &_43$$29, this_ptr);
				zephir_check_call_status_or_jump(try_end_1);
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_42$$29)) {
					RETURN_MM_BOOL(0);
				}
			}
			zephir_read_property_cached(&_44$$7, this_ptr, _zephir_prop_7, 692, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&afterBindingHandlers, &_44$$7);
			if (0) {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$true);
			} else {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$false);
			}
			if (Z_TYPE_P(&afterBindingHandlers) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_46$$7);
				zephir_string_to_char_array(&_46$$7, &afterBindingHandlers);
				_45$$7 = &_46$$7;
			} else {
				_45$$7 = &afterBindingHandlers;
			}
			zephir_is_iterable(_45$$7, 0, "phalcon/Mvc/Micro.zep", 598);
			if (Z_TYPE_P(_45$$7) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_45$$7), _47$$7)
				{
					ZEPHIR_INIT_NVAR(&afterBinding);
					ZVAL_COPY(&afterBinding, _47$$7);
					_48$$31 = Z_TYPE_P(&afterBinding) == IS_OBJECT;
					if (_48$$31) {
						_48$$31 = zephir_instance_of_ev(&afterBinding, phalcon_mvc_micro_middlewareinterface_ce);
					}
					if (_48$$31) {
						ZEPHIR_CALL_METHOD(&status, &afterBinding, "call", NULL, 0, this_ptr);
						zephir_check_call_status_or_jump(try_end_1);
					} else {
						if (UNEXPECTED(!(zephir_is_callable(&afterBinding)))) {
							ZEPHIR_INIT_NVAR(&_49$$34);
							object_init_ex(&_49$$34, phalcon_mvc_micro_exception_ce);
							ZEPHIR_INIT_NVAR(&_50$$34);
							ZVAL_STRING(&_50$$34, "'afterBinding' handler is not callable");
							ZEPHIR_CALL_METHOD(NULL, &_49$$34, "__construct", NULL, 32, &_50$$34);
							zephir_check_call_status_or_jump(try_end_1);
							zephir_throw_exception_debug(&_49$$34, "phalcon/Mvc/Micro.zep", 578);
							goto try_end_1;

						}
						ZEPHIR_INIT_NVAR(&status);
						ZEPHIR_CALL_USER_FUNC(&status, &afterBinding);
						zephir_check_call_status_or_jump(try_end_1);
					}
					zephir_read_property_cached(&_51$$31, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
					if (zephir_is_true(&_51$$31)) {
						RETURN_CCTOR(&status);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _45$$7, "rewind", NULL, 0);
				zephir_check_call_status();
				_53$$7 = 1;
				while (1) {
					if (_53$$7) {
						_53$$7 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _45$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_52$$7, _45$$7, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_52$$7)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&afterBinding, _45$$7, "current", NULL, 0);
					zephir_check_call_status();
						_54$$36 = Z_TYPE_P(&afterBinding) == IS_OBJECT;
						if (_54$$36) {
							_54$$36 = zephir_instance_of_ev(&afterBinding, phalcon_mvc_micro_middlewareinterface_ce);
						}
						if (_54$$36) {
							ZEPHIR_CALL_METHOD(&status, &afterBinding, "call", NULL, 0, this_ptr);
							zephir_check_call_status_or_jump(try_end_1);
						} else {
							if (UNEXPECTED(!(zephir_is_callable(&afterBinding)))) {
								ZEPHIR_INIT_NVAR(&_55$$39);
								object_init_ex(&_55$$39, phalcon_mvc_micro_exception_ce);
								ZEPHIR_INIT_NVAR(&_56$$39);
								ZVAL_STRING(&_56$$39, "'afterBinding' handler is not callable");
								ZEPHIR_CALL_METHOD(NULL, &_55$$39, "__construct", NULL, 32, &_56$$39);
								zephir_check_call_status_or_jump(try_end_1);
								zephir_throw_exception_debug(&_55$$39, "phalcon/Mvc/Micro.zep", 578);
								goto try_end_1;

							}
							ZEPHIR_INIT_NVAR(&status);
							ZEPHIR_CALL_USER_FUNC(&status, &afterBinding);
							zephir_check_call_status_or_jump(try_end_1);
						}
						zephir_read_property_cached(&_57$$36, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
						if (zephir_is_true(&_57$$36)) {
							RETURN_CCTOR(&status);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&afterBinding);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 693, &returnedValue);
			zephir_read_property_cached(&_44$$7, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			if (Z_TYPE_P(&_44$$7) != IS_NULL) {
				zephir_read_property_cached(&_58$$41, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_59$$41);
				ZVAL_STRING(&_59$$41, "micro:afterExecuteRoute");
				ZEPHIR_CALL_METHOD(NULL, &_58$$41, "fire", NULL, 0, &_59$$41, this_ptr);
				zephir_check_call_status_or_jump(try_end_1);
			}
			zephir_read_property_cached(&_60$$7, this_ptr, _zephir_prop_9, 694, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&afterHandlers, &_60$$7);
			if (0) {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$true);
			} else {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$false);
			}
			if (Z_TYPE_P(&afterHandlers) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_62$$7);
				zephir_string_to_char_array(&_62$$7, &afterHandlers);
				_61$$7 = &_62$$7;
			} else {
				_61$$7 = &afterHandlers;
			}
			zephir_is_iterable(_61$$7, 0, "phalcon/Mvc/Micro.zep", 637);
			if (Z_TYPE_P(_61$$7) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_61$$7), _63$$7)
				{
					ZEPHIR_INIT_NVAR(&after);
					ZVAL_COPY(&after, _63$$7);
					_64$$42 = Z_TYPE_P(&after) == IS_OBJECT;
					if (_64$$42) {
						_64$$42 = zephir_instance_of_ev(&after, phalcon_mvc_micro_middlewareinterface_ce);
					}
					if (_64$$42) {
						ZEPHIR_CALL_METHOD(&status, &after, "call", NULL, 0, this_ptr);
						zephir_check_call_status_or_jump(try_end_1);
					} else {
						if (UNEXPECTED(!(zephir_is_callable(&after)))) {
							ZEPHIR_INIT_NVAR(&_65$$45);
							object_init_ex(&_65$$45, phalcon_mvc_micro_exception_ce);
							ZEPHIR_INIT_NVAR(&_66$$45);
							ZVAL_STRING(&_66$$45, "One of the 'after' handlers is not callable");
							ZEPHIR_CALL_METHOD(NULL, &_65$$45, "__construct", NULL, 32, &_66$$45);
							zephir_check_call_status_or_jump(try_end_1);
							zephir_throw_exception_debug(&_65$$45, "phalcon/Mvc/Micro.zep", 624);
							goto try_end_1;

						}
						ZEPHIR_INIT_NVAR(&status);
						ZEPHIR_CALL_USER_FUNC(&status, &after);
						zephir_check_call_status_or_jump(try_end_1);
					}
					zephir_read_property_cached(&_67$$42, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
					if (zephir_is_true(&_67$$42)) {
						break;
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _61$$7, "rewind", NULL, 0);
				zephir_check_call_status();
				_69$$7 = 1;
				while (1) {
					if (_69$$7) {
						_69$$7 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _61$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_68$$7, _61$$7, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_68$$7)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&after, _61$$7, "current", NULL, 0);
					zephir_check_call_status();
						_70$$47 = Z_TYPE_P(&after) == IS_OBJECT;
						if (_70$$47) {
							_70$$47 = zephir_instance_of_ev(&after, phalcon_mvc_micro_middlewareinterface_ce);
						}
						if (_70$$47) {
							ZEPHIR_CALL_METHOD(&status, &after, "call", NULL, 0, this_ptr);
							zephir_check_call_status_or_jump(try_end_1);
						} else {
							if (UNEXPECTED(!(zephir_is_callable(&after)))) {
								ZEPHIR_INIT_NVAR(&_71$$50);
								object_init_ex(&_71$$50, phalcon_mvc_micro_exception_ce);
								ZEPHIR_INIT_NVAR(&_72$$50);
								ZVAL_STRING(&_72$$50, "One of the 'after' handlers is not callable");
								ZEPHIR_CALL_METHOD(NULL, &_71$$50, "__construct", NULL, 32, &_72$$50);
								zephir_check_call_status_or_jump(try_end_1);
								zephir_throw_exception_debug(&_71$$50, "phalcon/Mvc/Micro.zep", 624);
								goto try_end_1;

							}
							ZEPHIR_INIT_NVAR(&status);
							ZEPHIR_CALL_USER_FUNC(&status, &after);
							zephir_check_call_status_or_jump(try_end_1);
						}
						zephir_read_property_cached(&_73$$47, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
						if (zephir_is_true(&_73$$47)) {
							break;
						}
				}
			}
			ZEPHIR_INIT_NVAR(&after);
		} else {
			zephir_read_property_cached(&_74$$52, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			if (Z_TYPE_P(&_74$$52) != IS_NULL) {
				zephir_read_property_cached(&_75$$53, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_77$$53);
				ZVAL_STRING(&_77$$53, "micro:beforeNotFound");
				ZEPHIR_CALL_METHOD(&_76$$53, &_75$$53, "fire", NULL, 0, &_77$$53, this_ptr);
				zephir_check_call_status_or_jump(try_end_1);
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_76$$53)) {
					RETURN_MM_BOOL(0);
				}
			}
			zephir_read_property_cached(&_78$$52, this_ptr, _zephir_prop_10, 695, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&notFoundHandler, &_78$$52);
			if (UNEXPECTED(!(zephir_is_callable(&notFoundHandler)))) {
				ZEPHIR_INIT_VAR(&_79$$55);
				object_init_ex(&_79$$55, phalcon_mvc_micro_exception_ce);
				ZEPHIR_INIT_VAR(&_80$$55);
				ZVAL_STRING(&_80$$55, "Not-Found handler is not callable or is not defined");
				ZEPHIR_CALL_METHOD(NULL, &_79$$55, "__construct", NULL, 32, &_80$$55);
				zephir_check_call_status_or_jump(try_end_1);
				zephir_throw_exception_debug(&_79$$55, "phalcon/Mvc/Micro.zep", 655);
				goto try_end_1;

			}
			ZEPHIR_INIT_NVAR(&returnedValue);
			ZEPHIR_CALL_USER_FUNC(&returnedValue, &notFoundHandler);
			zephir_check_call_status_or_jump(try_end_1);
		}
		zephir_read_property_cached(&_81$$4, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_81$$4) != IS_NULL) {
			zephir_read_property_cached(&_82$$56, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_83$$56);
			ZVAL_STRING(&_83$$56, "micro:afterHandleRoute");
			ZEPHIR_CALL_METHOD(NULL, &_82$$56, "fire", NULL, 0, &_83$$56, this_ptr, &returnedValue);
			zephir_check_call_status_or_jump(try_end_1);
		}
		zephir_read_property_cached(&_84$$4, this_ptr, _zephir_prop_11, 696, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&finishHandlers, &_84$$4);
		if (0) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 691, &__$false);
		}
		if (Z_TYPE_P(&finishHandlers) == IS_STRING) {
			ZEPHIR_INIT_NVAR(&_6$$4);
			zephir_string_to_char_array(&_6$$4, &finishHandlers);
			_85$$4 = &_6$$4;
		} else {
			_85$$4 = &finishHandlers;
		}
		zephir_is_iterable(_85$$4, 0, "phalcon/Mvc/Micro.zep", 709);
		if (Z_TYPE_P(_85$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_85$$4), _86$$4)
			{
				ZEPHIR_INIT_NVAR(&finish);
				ZVAL_COPY(&finish, _86$$4);
				_87$$57 = Z_TYPE_P(&finish) == IS_OBJECT;
				if (_87$$57) {
					_87$$57 = zephir_instance_of_ev(&finish, phalcon_mvc_micro_middlewareinterface_ce);
				}
				if (_87$$57) {
					ZEPHIR_CALL_METHOD(&status, &finish, "call", NULL, 0, this_ptr);
					zephir_check_call_status_or_jump(try_end_1);
				} else {
					if (UNEXPECTED(!(zephir_is_callable(&finish)))) {
						ZEPHIR_INIT_NVAR(&_88$$60);
						object_init_ex(&_88$$60, phalcon_mvc_micro_exception_ce);
						ZEPHIR_INIT_NVAR(&_89$$60);
						ZVAL_STRING(&_89$$60, "One of the 'finish' handlers is not callable");
						ZEPHIR_CALL_METHOD(NULL, &_88$$60, "__construct", NULL, 32, &_89$$60);
						zephir_check_call_status_or_jump(try_end_1);
						zephir_throw_exception_debug(&_88$$60, "phalcon/Mvc/Micro.zep", 690);
						goto try_end_1;

					}
					ZEPHIR_INIT_NVAR(&_90$$59);
					zephir_create_array(&_90$$59, 1, 0);
					zephir_array_fast_append(&_90$$59, this_ptr);
					ZEPHIR_INIT_NVAR(&status);
					ZEPHIR_CALL_USER_FUNC_ARRAY(&status, &finish, &_90$$59);
					zephir_check_call_status_or_jump(try_end_1);
				}
				zephir_read_property_cached(&_91$$57, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
				if (zephir_is_true(&_91$$57)) {
					break;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _85$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_93$$4 = 1;
			while (1) {
				if (_93$$4) {
					_93$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _85$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_92$$4, _85$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_92$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&finish, _85$$4, "current", NULL, 0);
				zephir_check_call_status();
					_94$$62 = Z_TYPE_P(&finish) == IS_OBJECT;
					if (_94$$62) {
						_94$$62 = zephir_instance_of_ev(&finish, phalcon_mvc_micro_middlewareinterface_ce);
					}
					if (_94$$62) {
						ZEPHIR_CALL_METHOD(&status, &finish, "call", NULL, 0, this_ptr);
						zephir_check_call_status_or_jump(try_end_1);
					} else {
						if (UNEXPECTED(!(zephir_is_callable(&finish)))) {
							ZEPHIR_INIT_NVAR(&_95$$65);
							object_init_ex(&_95$$65, phalcon_mvc_micro_exception_ce);
							ZEPHIR_INIT_NVAR(&_96$$65);
							ZVAL_STRING(&_96$$65, "One of the 'finish' handlers is not callable");
							ZEPHIR_CALL_METHOD(NULL, &_95$$65, "__construct", NULL, 32, &_96$$65);
							zephir_check_call_status_or_jump(try_end_1);
							zephir_throw_exception_debug(&_95$$65, "phalcon/Mvc/Micro.zep", 690);
							goto try_end_1;

						}
						ZEPHIR_INIT_NVAR(&_97$$64);
						zephir_create_array(&_97$$64, 1, 0);
						zephir_array_fast_append(&_97$$64, this_ptr);
						ZEPHIR_INIT_NVAR(&status);
						ZEPHIR_CALL_USER_FUNC_ARRAY(&status, &finish, &_97$$64);
						zephir_check_call_status_or_jump(try_end_1);
					}
					zephir_read_property_cached(&_98$$62, this_ptr, _zephir_prop_5, 691, PH_NOISY_CC | PH_READONLY);
					if (zephir_is_true(&_98$$62)) {
						break;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&finish);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_99);
		ZVAL_OBJ(&_99, EG(exception));
		Z_ADDREF_P(&_99);
		if (zephir_is_instance_of(&_99, SL("Throwable"))) {
			zend_clear_exception();
			ZEPHIR_CPY_WRT(&e, &_99);
			zephir_read_property_cached(&_100$$67, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
			if (Z_TYPE_P(&_100$$67) != IS_NULL) {
				zephir_read_property_cached(&_101$$68, this_ptr, _zephir_prop_1, 685, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_102$$68);
				ZVAL_STRING(&_102$$68, "micro:beforeException");
				ZEPHIR_CALL_METHOD(&returnedValue, &_101$$68, "fire", NULL, 0, &_102$$68, this_ptr, &e);
				zephir_check_call_status();
			}
			zephir_read_property_cached(&_103$$67, this_ptr, _zephir_prop_12, 683, PH_NOISY_CC | PH_READONLY);
			if (Z_TYPE_P(&_103$$67) != IS_NULL) {
				zephir_read_property_cached(&_104$$69, this_ptr, _zephir_prop_12, 683, PH_NOISY_CC | PH_READONLY);
				if (UNEXPECTED(!(zephir_is_callable(&_104$$69)))) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "Error handler is not callable", "phalcon/Mvc/Micro.zep", 726);
					return;
				}
				zephir_read_property_cached(&_105$$69, this_ptr, _zephir_prop_12, 683, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_106$$69);
				zephir_create_array(&_106$$69, 1, 0);
				zephir_array_fast_append(&_106$$69, &e);
				ZEPHIR_INIT_NVAR(&returnedValue);
				ZEPHIR_CALL_USER_FUNC_ARRAY(&returnedValue, &_105$$69, &_106$$69);
				zephir_check_call_status();
				if (Z_TYPE_P(&returnedValue) == IS_OBJECT) {
					if (!(zephir_instance_of_ev(&returnedValue, phalcon_http_responseinterface_ce))) {
						zephir_throw_exception_debug(&e, "phalcon/Mvc/Micro.zep", 739);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					if (!ZEPHIR_IS_FALSE_IDENTICAL(&returnedValue)) {
						zephir_throw_exception_debug(&e, "phalcon/Mvc/Micro.zep", 743);
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			} else {
				if (!ZEPHIR_IS_FALSE_IDENTICAL(&returnedValue)) {
					zephir_throw_exception_debug(&e, "phalcon/Mvc/Micro.zep", 748);
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		} else {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_13, 697, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		zephir_read_property_cached(&_107$$78, this_ptr, _zephir_prop_13, 697, PH_NOISY_CC | PH_READONLY);
		if (UNEXPECTED(!(zephir_is_callable(&_107$$78)))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "Response handler is not callable or is not defined", "phalcon/Mvc/Micro.zep", 761);
			return;
		}
		zephir_read_property_cached(&_108$$78, this_ptr, _zephir_prop_13, 697, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&returnedValue);
		ZEPHIR_CALL_USER_FUNC(&returnedValue, &_108$$78);
		zephir_check_call_status();
	} else {
		if (Z_TYPE_P(&returnedValue) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_110$$81);
			ZVAL_STRING(&_110$$81, "response");
			ZEPHIR_CALL_METHOD(&_109$$81, &container, "getShared", NULL, 0, &_110$$81);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&response, &_109$$81);
			ZEPHIR_CALL_METHOD(&_109$$81, &response, "isSent", NULL, 0);
			zephir_check_call_status();
			if (!(zephir_is_true(&_109$$81))) {
				ZEPHIR_CALL_METHOD(NULL, &response, "setContent", NULL, 0, &returnedValue);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &response, "send", NULL, 0);
				zephir_check_call_status();
			}
		}
		_111$$80 = Z_TYPE_P(&returnedValue) == IS_OBJECT;
		if (_111$$80) {
			_111$$80 = zephir_instance_of_ev(&returnedValue, phalcon_http_responseinterface_ce);
		}
		_112$$80 = _111$$80;
		if (_112$$80) {
			ZEPHIR_CALL_METHOD(&_113$$80, &returnedValue, "isSent", NULL, 0);
			zephir_check_call_status();
			_112$$80 = !zephir_is_true(&_113$$80);
		}
		if (_112$$80) {
			ZEPHIR_CALL_METHOD(NULL, &returnedValue, "send", NULL, 0);
			zephir_check_call_status();
		}
	}
	RETURN_CCTOR(&returnedValue);
}

/**
 * Checks if a service is registered in the DI
 */
PHP_METHOD(Phalcon_Mvc_Micro, hasService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval serviceName_zv, _0, _2, _1$$3;
	zend_string *serviceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&serviceName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(serviceName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&serviceName_zv);
	ZVAL_STR_COPY(&serviceName_zv, serviceName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_di_factorydefault_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 454);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 687, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_2, "has", NULL, 0, &serviceName_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Maps a route to a handler that only matches if the HTTP method is HEAD
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, head)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addHead", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Maps a route to a handler without any HTTP method constraint
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, map)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "add", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Mounts a collection of handlers
 */
PHP_METHOD(Phalcon_Mvc_Micro, mount)
{
	zend_bool _8, _5$$7, _6$$7, _10$$15, _11$$15;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collection, collection_sub, mainHandler, handlers, lazyHandler, prefix, methods, pattern, subHandler, realHandler, prefixedPattern, route, handler, name, _0, *_1, _2, *_3, _7, _9$$15;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&mainHandler);
	ZVAL_UNDEF(&handlers);
	ZVAL_UNDEF(&lazyHandler);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&methods);
	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&subHandler);
	ZVAL_UNDEF(&realHandler);
	ZVAL_UNDEF(&prefixedPattern);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9$$15);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(collection, phalcon_mvc_micro_collectioninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &collection);
	ZEPHIR_CALL_METHOD(&mainHandler, collection, "getHandler", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(ZEPHIR_IS_EMPTY(&mainHandler))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "Collection requires a main handler", "phalcon/Mvc/Micro.zep", 876);
		return;
	}
	ZEPHIR_CALL_METHOD(&handlers, collection, "getHandlers", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!(zephir_fast_count_int(&handlers)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "There are no handlers to mount", "phalcon/Mvc/Micro.zep", 882);
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, collection, "isLazy", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&lazyHandler);
		object_init_ex(&lazyHandler, phalcon_mvc_micro_lazyloader_ce);
		ZEPHIR_CALL_METHOD(NULL, &lazyHandler, "__construct", NULL, 455, &mainHandler);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&lazyHandler, &mainHandler);
	}
	ZEPHIR_CALL_METHOD(&prefix, collection, "getPrefix", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&handlers) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &handlers);
		_1 = &_2;
	} else {
		_1 = &handlers;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Micro.zep", 940);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&handler);
			ZVAL_COPY(&handler, _3);
			if (UNEXPECTED(Z_TYPE_P(&handler) != IS_ARRAY)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "One of the registered handlers is invalid", "phalcon/Mvc/Micro.zep", 903);
				return;
			}
			ZEPHIR_OBS_NVAR(&methods);
			zephir_array_fetch_long(&methods, &handler, 0, PH_NOISY, "phalcon/Mvc/Micro.zep", 906);
			ZEPHIR_OBS_NVAR(&pattern);
			zephir_array_fetch_long(&pattern, &handler, 1, PH_NOISY, "phalcon/Mvc/Micro.zep", 907);
			ZEPHIR_OBS_NVAR(&subHandler);
			zephir_array_fetch_long(&subHandler, &handler, 2, PH_NOISY, "phalcon/Mvc/Micro.zep", 908);
			ZEPHIR_OBS_NVAR(&name);
			zephir_array_fetch_long(&name, &handler, 3, PH_NOISY, "phalcon/Mvc/Micro.zep", 909);
			ZEPHIR_INIT_NVAR(&realHandler);
			zephir_create_array(&realHandler, 2, 0);
			zephir_array_fast_append(&realHandler, &lazyHandler);
			zephir_array_fast_append(&realHandler, &subHandler);
			if (!(ZEPHIR_IS_EMPTY(&prefix))) {
				if (ZEPHIR_IS_STRING_IDENTICAL(&pattern, "/")) {
					ZEPHIR_CPY_WRT(&prefixedPattern, &prefix);
				} else {
					ZEPHIR_INIT_NVAR(&prefixedPattern);
					ZEPHIR_CONCAT_VV(&prefixedPattern, &prefix, &pattern);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			} else {
				ZEPHIR_CPY_WRT(&prefixedPattern, &pattern);
			}
			ZEPHIR_CALL_METHOD(&route, this_ptr, "map", &_4, 0, &prefixedPattern, &realHandler);
			zephir_check_call_status();
			_5$$7 = Z_TYPE_P(&methods) == IS_STRING;
			if (_5$$7) {
				_5$$7 = !ZEPHIR_IS_STRING_IDENTICAL(&methods, "");
			}
			_6$$7 = _5$$7;
			if (!(_6$$7)) {
				_6$$7 = Z_TYPE_P(&methods) == IS_ARRAY;
			}
			if (_6$$7) {
				ZEPHIR_CALL_METHOD(NULL, &route, "via", NULL, 0, &methods);
				zephir_check_call_status();
			}
			if (Z_TYPE_P(&name) == IS_STRING) {
				ZEPHIR_CALL_METHOD(NULL, &route, "setName", NULL, 0, &name);
				zephir_check_call_status();
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&handler, _1, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&handler) != IS_ARRAY)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_micro_exception_ce, "One of the registered handlers is invalid", "phalcon/Mvc/Micro.zep", 903);
					return;
				}
				ZEPHIR_OBS_NVAR(&methods);
				zephir_array_fetch_long(&methods, &handler, 0, PH_NOISY, "phalcon/Mvc/Micro.zep", 906);
				ZEPHIR_OBS_NVAR(&pattern);
				zephir_array_fetch_long(&pattern, &handler, 1, PH_NOISY, "phalcon/Mvc/Micro.zep", 907);
				ZEPHIR_OBS_NVAR(&subHandler);
				zephir_array_fetch_long(&subHandler, &handler, 2, PH_NOISY, "phalcon/Mvc/Micro.zep", 908);
				ZEPHIR_OBS_NVAR(&name);
				zephir_array_fetch_long(&name, &handler, 3, PH_NOISY, "phalcon/Mvc/Micro.zep", 909);
				ZEPHIR_INIT_NVAR(&_9$$15);
				zephir_create_array(&_9$$15, 2, 0);
				zephir_array_fast_append(&_9$$15, &lazyHandler);
				zephir_array_fast_append(&_9$$15, &subHandler);
				ZEPHIR_CPY_WRT(&realHandler, &_9$$15);
				if (!(ZEPHIR_IS_EMPTY(&prefix))) {
					if (ZEPHIR_IS_STRING_IDENTICAL(&pattern, "/")) {
						ZEPHIR_CPY_WRT(&prefixedPattern, &prefix);
					} else {
						ZEPHIR_INIT_NVAR(&prefixedPattern);
						ZEPHIR_CONCAT_VV(&prefixedPattern, &prefix, &pattern);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} else {
					ZEPHIR_CPY_WRT(&prefixedPattern, &pattern);
				}
				ZEPHIR_CALL_METHOD(&route, this_ptr, "map", &_4, 0, &prefixedPattern, &realHandler);
				zephir_check_call_status();
				_10$$15 = Z_TYPE_P(&methods) == IS_STRING;
				if (_10$$15) {
					_10$$15 = !ZEPHIR_IS_STRING_IDENTICAL(&methods, "");
				}
				_11$$15 = _10$$15;
				if (!(_11$$15)) {
					_11$$15 = Z_TYPE_P(&methods) == IS_ARRAY;
				}
				if (_11$$15) {
					ZEPHIR_CALL_METHOD(NULL, &route, "via", NULL, 0, &methods);
					zephir_check_call_status();
				}
				if (Z_TYPE_P(&name) == IS_STRING) {
					ZEPHIR_CALL_METHOD(NULL, &route, "setName", NULL, 0, &name);
					zephir_check_call_status();
				}
		}
	}
	ZEPHIR_INIT_NVAR(&handler);
	RETURN_THIS();
}

/**
 * Sets a handler that will be called when the router does not match any of
 * the defined routes
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, notFound)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("notFoundHandler", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 695, handler);
	RETURN_THISW();
}

/**
 * Check if a service is registered in the internal services container using
 * the array syntax
 *
 * @param mixed offset
 */
PHP_METHOD(Phalcon_Mvc_Micro, offsetExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval offset_sub;
	zval *offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&offset_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &offset);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "hasService", NULL, 0, offset);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Allows to obtain a shared service in the internal services container
 * using the array syntax
 *
 *```php
 * var_dump(
 *     $app["request"]
 * );
 *```
 *
 * @param mixed offset
 */
PHP_METHOD(Phalcon_Mvc_Micro, offsetGet)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval offset_sub;
	zval *offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&offset_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &offset);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getService", NULL, 0, offset);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Allows to register a shared service in the internal services container
 * using the array syntax
 *
 *```php
 *    $app["request"] = new \Phalcon\Http\Request();
 *```
 */
PHP_METHOD(Phalcon_Mvc_Micro, offsetSet)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval offset_sub, value_sub;
	zval *offset, *value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&offset_sub);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(offset)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &offset, &value);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setService", NULL, 0, offset, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Removes a service from the internal services container using the array
 * syntax
 */
PHP_METHOD(Phalcon_Mvc_Micro, offsetUnset)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval offset_sub, _0, _2, _1$$3;
	zval *offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&offset_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &offset);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_di_factorydefault_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 454);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 687, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_2, "remove", NULL, 0, offset);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Maps a route to a handler that only matches if the HTTP method is OPTIONS
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, options)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addOptions", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Maps a route to a handler that only matches if the HTTP method is PATCH
 *
 * @param callable $handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, patch)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addPatch", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Maps a route to a handler that only matches if the HTTP method is POST
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, post)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addPost", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Maps a route to a handler that only matches if the HTTP method is PUT
 *
 * @param callable $handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, put)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval routePattern_zv, *handler, handler_sub, router, route, _0;
	zend_string *routePattern = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routePattern_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(routePattern)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&routePattern_zv);
	ZVAL_STR_COPY(&routePattern_zv, routePattern);
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getRouter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, &router, "addPut", NULL, 0, &routePattern_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &route, "getRouteId", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("handlers"), &_0, handler);
	RETURN_CCTOR(&route);
}

/**
 * Sets externally the handler that must be called by the matched route
 *
 * @param callable activeHandler
 */
PHP_METHOD(Phalcon_Mvc_Micro, setActiveHandler)
{
	zval *activeHandler, activeHandler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&activeHandler_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("activeHandler", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(activeHandler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &activeHandler);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 689, activeHandler);
}

/**
 * Sets the DependencyInjector container
 */
PHP_METHOD(Phalcon_Mvc_Micro, setDI)
{
	zval *container, container_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &container);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 687, container);
}

/**
 * Sets model binder
 *
 * ```php
 * $micro = new Micro($di);
 *
 * $micro->setModelBinder(
 *     new Binder(),
 *     'cache'
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Micro, setModelBinder)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *modelBinder, modelBinder_sub, *cache = NULL, cache_sub, __$null, _0$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&modelBinder_sub);
	ZVAL_UNDEF(&cache_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelBinder", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_OBJECT_OF_CLASS(modelBinder, phalcon_mvc_model_binderinterface_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(cache)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &modelBinder, &cache);
	if (!cache) {
		cache = &cache_sub;
		ZEPHIR_CPY_WRT(cache, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(cache);
	}
	if (Z_TYPE_P(cache) == IS_STRING) {
		ZEPHIR_CALL_METHOD(&_0$$3, this_ptr, "getService", NULL, 0, cache);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(cache, &_0$$3);
	}
	if (Z_TYPE_P(cache) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, modelBinder, "setCache", NULL, 0, cache);
		zephir_check_call_status();
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 684, modelBinder);
	RETURN_THIS();
}

/**
 * Appends a custom 'response' handler to be called instead of the default
 * response handler
 *
 * @param callable handler
 */
PHP_METHOD(Phalcon_Mvc_Micro, setResponseHandler)
{
	zval *handler, handler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("responseHandler", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handler)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handler);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 697, handler);
	RETURN_THISW();
}

/**
 * Sets a service from the DI
 */
PHP_METHOD(Phalcon_Mvc_Micro, setService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool shared;
	zval serviceName_zv, *definition, definition_sub, *shared_param = NULL, _0, _2, _3, _1$$3;
	zend_string *serviceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&serviceName_zv);
	ZVAL_UNDEF(&definition_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(serviceName)
		Z_PARAM_ZVAL(definition)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(shared)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	definition = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		shared_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&serviceName_zv);
	ZVAL_STR_COPY(&serviceName_zv, serviceName);
	if (!shared_param) {
		shared = 0;
	} else {
		}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_di_factorydefault_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 454);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 687, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 687, PH_NOISY_CC | PH_READONLY);
	if (shared) {
		ZVAL_BOOL(&_3, 1);
	} else {
		ZVAL_BOOL(&_3, 0);
	}
	ZEPHIR_RETURN_CALL_METHOD(&_2, "set", NULL, 0, &serviceName_zv, definition, &_3);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Stops the middleware execution avoiding than other middlewares be
 * executed
 */
PHP_METHOD(Phalcon_Mvc_Micro, stop)
{
	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("stopped", 7, 1);
	}
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 691, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 691, &__$false);
	}
}

zend_object *zephir_init_properties_Phalcon_Mvc_Micro(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("handlers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("handlers"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("finishHandlers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("finishHandlers"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("beforeHandlers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("beforeHandlers"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("afterHandlers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("afterHandlers"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("afterBindingHandlers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("afterBindingHandlers"), &_9$$7);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

