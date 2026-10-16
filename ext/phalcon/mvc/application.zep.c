
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "Zend/zend_closures.h"
#include "kernel/array.h"
#include "kernel/file.h"
#include "kernel/concat.h"
#include "kernel/require.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Application
 *
 * This component encapsulates all the complex operations behind instantiating
 * every component needed and integrating it with the rest to allow the MVC
 * pattern to operate as desired.
 *
 *```php
 * use Phalcon\Mvc\Application;
 *
 * class MyApp extends Application
 * {
 *     /**
 *      * Register the services here to make them general or register
 *      * in the ModuleDefinition to make them module-specific
 *      *\/
 *     protected function registerServices()
 *     {
 *
 *     }
 *
 *     /**
 *      * This method registers all the modules in the application
 *      *\/
 *     public function main()
 *     {
 *         $this->registerModules(
 *             [
 *                 "frontend" => [
 *                     "className" => "Multiple\\Frontend\\Module",
 *                     "path"      => "../apps/frontend/Module.php",
 *                 ],
 *                 "backend" => [
 *                     "className" => "Multiple\\Backend\\Module",
 *                     "path"      => "../apps/backend/Module.php",
 *                 ],
 *             ]
 *         );
 *     }
 * }
 *
 * $application = new MyApp();
 *
 * $application->main();
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Application)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, Application, phalcon, mvc_application, phalcon_application_abstractapplication_ce, phalcon_mvc_application_method_entry, 0);

	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_application_ce, SL("implicitView"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_application_ce, SL("sendCookies"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_application_ce, SL("sendHeaders"), 1, ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Handles a MVC request
 */
PHP_METHOD(Phalcon_Mvc_Application, handle)
{
	zval _17$$20;
	zend_class_entry *_6$$7;
	zend_bool returnedResponse = 0, _1, _10$$6, _13$$11, _31$$30, _33$$30;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri_zv, __$false, container, eventsManager, router, dispatcher, response, view, module, moduleObject, moduleName, className, path, implicitView, controller, possibleResponse, renderStatus, matchedRoute, match, _0, _2, _3, _4, _21, _22, _23, _24, _41, _5$$7, _7$$6, _8$$8, _9$$8, _11$$12, _12$$12, _14$$18, _15$$18, _16$$15, _18$$22, _19$$23, _20$$23, _25$$25, _26$$25, _27$$27, _28$$27, _29$$29, _30$$29, _32$$31, _34$$34, _35$$35, _36$$35, _37$$38, _38$$38, _39$$39, _40$$40;
	zend_string *uri = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_zv);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&dispatcher);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&module);
	ZVAL_UNDEF(&moduleObject);
	ZVAL_UNDEF(&moduleName);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&implicitView);
	ZVAL_UNDEF(&controller);
	ZVAL_UNDEF(&possibleResponse);
	ZVAL_UNDEF(&renderStatus);
	ZVAL_UNDEF(&matchedRoute);
	ZVAL_UNDEF(&match);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_11$$12);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_14$$18);
	ZVAL_UNDEF(&_15$$18);
	ZVAL_UNDEF(&_16$$15);
	ZVAL_UNDEF(&_18$$22);
	ZVAL_UNDEF(&_19$$23);
	ZVAL_UNDEF(&_20$$23);
	ZVAL_UNDEF(&_25$$25);
	ZVAL_UNDEF(&_26$$25);
	ZVAL_UNDEF(&_27$$27);
	ZVAL_UNDEF(&_28$$27);
	ZVAL_UNDEF(&_29$$29);
	ZVAL_UNDEF(&_30$$29);
	ZVAL_UNDEF(&_32$$31);
	ZVAL_UNDEF(&_34$$34);
	ZVAL_UNDEF(&_35$$35);
	ZVAL_UNDEF(&_36$$35);
	ZVAL_UNDEF(&_37$$38);
	ZVAL_UNDEF(&_38$$38);
	ZVAL_UNDEF(&_39$$39);
	ZVAL_UNDEF(&_40$$40);
	ZVAL_UNDEF(&_17$$20);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("defaultModule", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("implicitView", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("sendHeaders", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("sendCookies", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&uri_zv);
	ZVAL_STR_COPY(&uri_zv, uri);
	ZEPHIR_INIT_VAR(&view);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 671, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_application_exception_ce, "A dependency injection container is required to access internal services", "phalcon/Mvc/Application.zep", 100);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 672, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	_1 = Z_TYPE_P(&eventsManager) != IS_NULL;
	if (_1) {
		ZEPHIR_INIT_VAR(&_3);
		ZVAL_STRING(&_3, "application:boot");
		ZEPHIR_CALL_METHOD(&_2, &eventsManager, "fire", NULL, 0, &_3, this_ptr);
		zephir_check_call_status();
		_1 = ZEPHIR_IS_FALSE_IDENTICAL(&_2);
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "router");
	ZEPHIR_CALL_METHOD(&_4, &container, "getShared", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&router, &_4);
	ZEPHIR_CALL_METHOD(NULL, &router, "handle", NULL, 0, &uri_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&matchedRoute, &router, "getMatchedRoute", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&matchedRoute) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(&match, &matchedRoute, "getMatch", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&match) != IS_NULL) {
			if (zephir_is_instance_of(&match, SL("Closure"))) {
				_6$$7 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
				ZEPHIR_CALL_CE_STATIC(&_5$$7, _6$$7, "bind", NULL, 0, &match, &container);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&match, &_5$$7);
			}
			ZEPHIR_CALL_METHOD(&_7$$6, &router, "getParams", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&possibleResponse);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&possibleResponse, &match, &_7$$6);
			zephir_check_call_status();
			if (Z_TYPE_P(&possibleResponse) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_9$$8);
				ZVAL_STRING(&_9$$8, "response");
				ZEPHIR_CALL_METHOD(&_8$$8, &container, "getShared", NULL, 0, &_9$$8);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&response, &_8$$8);
				ZEPHIR_CALL_METHOD(NULL, &response, "setContent", NULL, 0, &possibleResponse);
				zephir_check_call_status();
				RETURN_CCTOR(&response);
			}
			_10$$6 = Z_TYPE_P(&possibleResponse) == IS_OBJECT;
			if (_10$$6) {
				_10$$6 = zephir_instance_of_ev(&possibleResponse, phalcon_http_responseinterface_ce);
			}
			if (_10$$6) {
				ZEPHIR_CALL_METHOD(NULL, &possibleResponse, "sendHeaders", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &possibleResponse, "sendCookies", NULL, 0);
				zephir_check_call_status();
				RETURN_CCTOR(&possibleResponse);
			}
		}
	}
	ZEPHIR_CALL_METHOD(&moduleName, &router, "getModuleName", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&moduleName))) {
		ZEPHIR_OBS_NVAR(&moduleName);
		zephir_read_property_cached(&moduleName, this_ptr, _zephir_prop_2, 673, PH_NOISY_CC);
	}
	ZEPHIR_INIT_VAR(&moduleObject);
	ZVAL_NULL(&moduleObject);
	if (zephir_is_true(&moduleName)) {
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_12$$12);
			ZVAL_STRING(&_12$$12, "application:beforeStartModule");
			ZEPHIR_CALL_METHOD(&_11$$12, &eventsManager, "fire", NULL, 0, &_12$$12, this_ptr, &moduleName);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_11$$12)) {
				RETURN_MM_BOOL(0);
			}
		}
		ZEPHIR_CALL_METHOD(&module, this_ptr, "getModule", NULL, 0, &moduleName);
		zephir_check_call_status();
		_13$$11 = Z_TYPE_P(&module) != IS_ARRAY;
		if (_13$$11) {
			_13$$11 = Z_TYPE_P(&module) != IS_OBJECT;
		}
		if (UNEXPECTED(_13$$11)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_application_exception_ce, "Invalid module definition", "phalcon/Mvc/Application.zep", 196);
			return;
		}
		if (Z_TYPE_P(&module) == IS_ARRAY) {
			zephir_memory_observe(&className);
			if (!(zephir_array_isset_string_fetch(&className, &module, SL("className"), 0))) {
				ZEPHIR_INIT_NVAR(&className);
				ZVAL_STRING(&className, "Module");
			}
			zephir_memory_observe(&path);
			if (zephir_array_isset_string_fetch(&path, &module, SL("path"), 0)) {
				if (UNEXPECTED(!((zephir_file_exists(&path) == SUCCESS)))) {
					ZEPHIR_INIT_VAR(&_14$$18);
					object_init_ex(&_14$$18, phalcon_mvc_application_exception_ce);
					ZEPHIR_INIT_VAR(&_15$$18);
					ZEPHIR_CONCAT_SVS(&_15$$18, "Module definition path '", &path, "' does not exist");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_14$$18, "__construct", NULL, 32, &_15$$18);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_14$$18, "phalcon/Mvc/Application.zep", 218);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (!(zephir_class_exists(&className, zephir_is_true(&__$false) ))) {
					if (zephir_require_once_zval(&path) == FAILURE) {
						RETURN_MM_NULL();
					}
				}
			}
			ZEPHIR_CALL_METHOD(&_16$$15, &container, "get", NULL, 0, &className);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&moduleObject, &_16$$15);
			ZEPHIR_CALL_METHOD(NULL, &moduleObject, "registerAutoloaders", NULL, 0, &container);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &moduleObject, "registerServices", NULL, 0, &container);
			zephir_check_call_status();
		} else {
			if (UNEXPECTED(!((zephir_is_instance_of(&module, SL("Closure")))))) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_application_exception_ce, "Invalid module definition", "phalcon/Mvc/Application.zep", 239);
				return;
			}
			ZEPHIR_INIT_VAR(&_17$$20);
			zephir_create_array(&_17$$20, 1, 0);
			zephir_array_fast_append(&_17$$20, &container);
			ZEPHIR_INIT_NVAR(&moduleObject);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&moduleObject, &module, &_17$$20);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_18$$22);
			ZVAL_STRING(&_18$$22, "application:afterStartModule");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_18$$22, this_ptr, &moduleObject);
			zephir_check_call_status();
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 674, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&implicitView, &_0);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&implicitView)) {
		ZEPHIR_INIT_VAR(&_20$$23);
		ZVAL_STRING(&_20$$23, "view");
		ZEPHIR_CALL_METHOD(&_19$$23, &container, "getShared", NULL, 0, &_20$$23);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&view, &_19$$23);
	}
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "dispatcher");
	ZEPHIR_CALL_METHOD(&_4, &container, "getShared", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&dispatcher, &_4);
	ZEPHIR_CALL_METHOD(&_4, &router, "getModuleName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setModuleName", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_21, &router, "getNamespaceName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setNamespaceName", NULL, 0, &_21);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_22, &router, "getControllerName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setControllerName", NULL, 0, &_22);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_23, &router, "getActionName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setActionName", NULL, 0, &_23);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_24, &router, "getParams", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setParams", NULL, 0, &_24);
	zephir_check_call_status();
	if (ZEPHIR_IS_TRUE_IDENTICAL(&implicitView)) {
		ZEPHIR_CALL_METHOD(NULL, &view, "start", NULL, 0);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_26$$25);
		ZVAL_STRING(&_26$$25, "application:beforeHandleRequest");
		ZEPHIR_CALL_METHOD(&_25$$25, &eventsManager, "fire", NULL, 0, &_26$$25, this_ptr, &dispatcher);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_25$$25)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_METHOD(&controller, &dispatcher, "dispatch", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&possibleResponse, &dispatcher, "getReturnedValue", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&possibleResponse)) {
		ZEPHIR_INIT_VAR(&_28$$27);
		ZVAL_STRING(&_28$$27, "response");
		ZEPHIR_CALL_METHOD(&_27$$27, &container, "getShared", NULL, 0, &_28$$27);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&response, &_27$$27);
	} else {
		if (Z_TYPE_P(&possibleResponse) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_30$$29);
			ZVAL_STRING(&_30$$29, "response");
			ZEPHIR_CALL_METHOD(&_29$$29, &container, "getShared", NULL, 0, &_30$$29);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&response, &_29$$29);
			ZEPHIR_CALL_METHOD(NULL, &response, "setContent", NULL, 0, &possibleResponse);
			zephir_check_call_status();
		} else {
			_31$$30 = (Z_TYPE_P(&possibleResponse) == IS_OBJECT);
			if (_31$$30) {
				_31$$30 = (zephir_instance_of_ev(&possibleResponse, phalcon_http_responseinterface_ce));
			}
			returnedResponse = _31$$30;
			if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
				ZEPHIR_INIT_VAR(&_32$$31);
				ZVAL_STRING(&_32$$31, "application:afterHandleRequest");
				ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_32$$31, this_ptr, &controller);
				zephir_check_call_status();
			}
			_33$$30 = returnedResponse == 0;
			if (_33$$30) {
				_33$$30 = ZEPHIR_IS_TRUE_IDENTICAL(&implicitView);
			}
			if (_33$$30) {
				if (Z_TYPE_P(&controller) == IS_OBJECT) {
					ZEPHIR_INIT_VAR(&renderStatus);
					ZVAL_BOOL(&renderStatus, 1);
					if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
						ZEPHIR_INIT_VAR(&_34$$34);
						ZVAL_STRING(&_34$$34, "application:viewRender");
						ZEPHIR_CALL_METHOD(&renderStatus, &eventsManager, "fire", NULL, 0, &_34$$34, this_ptr, &view);
						zephir_check_call_status();
					}
					if (!ZEPHIR_IS_FALSE_IDENTICAL(&renderStatus)) {
						ZEPHIR_CALL_METHOD(&_35$$35, &dispatcher, "getControllerName", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_36$$35, &dispatcher, "getActionName", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(NULL, &view, "render", NULL, 0, &_35$$35, &_36$$35);
						zephir_check_call_status();
					}
				}
			}
			if (ZEPHIR_IS_TRUE_IDENTICAL(&implicitView)) {
				ZEPHIR_CALL_METHOD(NULL, &view, "finish", NULL, 0);
				zephir_check_call_status();
			}
			if (returnedResponse == 1) {
				ZEPHIR_CPY_WRT(&response, &possibleResponse);
			} else {
				ZEPHIR_INIT_VAR(&_38$$38);
				ZVAL_STRING(&_38$$38, "response");
				ZEPHIR_CALL_METHOD(&_37$$38, &container, "getShared", NULL, 0, &_38$$38);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&response, &_37$$38);
				if (ZEPHIR_IS_TRUE_IDENTICAL(&implicitView)) {
					ZEPHIR_CALL_METHOD(&_39$$39, &view, "getContent", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &response, "setContent", NULL, 0, &_39$$39);
					zephir_check_call_status();
				}
			}
		}
	}
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_40$$40);
		ZVAL_STRING(&_40$$40, "application:beforeSendResponse");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_40$$40, this_ptr, &response);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 675, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(NULL, &response, "sendHeaders", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_41, this_ptr, _zephir_prop_5, 676, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_41)) {
		ZEPHIR_CALL_METHOD(NULL, &response, "sendCookies", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&response);
}

/**
 * Enables or disables sending cookies by each request handling
 */
PHP_METHOD(Phalcon_Mvc_Application, sendCookiesOnHandleRequest)
{
	zval *sendCookies_param = NULL, __$true, __$false;
	zend_bool sendCookies;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("sendCookies", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(sendCookies)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &sendCookies_param);
	if (sendCookies) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 676, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 676, &__$false);
	}
	RETURN_THISW();
}

/**
 * Enables or disables sending headers by each request handling
 */
PHP_METHOD(Phalcon_Mvc_Application, sendHeadersOnHandleRequest)
{
	zval *sendHeaders_param = NULL, __$true, __$false;
	zend_bool sendHeaders;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("sendHeaders", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(sendHeaders)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &sendHeaders_param);
	if (sendHeaders) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 675, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 675, &__$false);
	}
	RETURN_THISW();
}

/**
 * By default. The view is implicitly buffering all the output
 * You can full disable the view component using this method
 */
PHP_METHOD(Phalcon_Mvc_Application, useImplicitView)
{
	zval *implicitView_param = NULL, __$true, __$false;
	zend_bool implicitView;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("implicitView", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(implicitView)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &implicitView_param);
	if (implicitView) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 674, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 674, &__$false);
	}
	RETURN_THISW();
}

