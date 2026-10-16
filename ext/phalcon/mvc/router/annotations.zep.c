
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/operators.h"
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
 * Phalcon\Mvc\Router\Annotations
 *
 * A router that reads routes annotations from classes/resources
 *
 * ```php
 * use Phalcon\Mvc\Router\Annotations;
 *
 * $di->setShared(
 *     "router",
 *     function() {
 *         // Use the annotations router
 *         $router = new Annotations(false);
 *
 *         // This will do the same as above but only if the handled uri starts with /robots
 *         $router->addResource("Robots", "/robots");
 *
 *         return $router;
 *     }
 * );
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Router_Annotations)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc\\Router, Annotations, phalcon, mvc_router_annotations, phalcon_mvc_router_ce, phalcon_mvc_router_annotations_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_annotations_ce, SL("actionSuffix"), "Action", ZEND_ACC_PROTECTED);
	/**
	 * @var callable|string|null
	 */
	zend_declare_property_null(phalcon_mvc_router_annotations_ce, SL("actionPreformatCallback"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_annotations_ce, SL("controllerSuffix"), "Controller", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_router_annotations_ce, SL("handlers"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_router_annotations_ce, SL("routePrefix"), "", ZEND_ACC_PROTECTED);
	phalcon_mvc_router_annotations_ce->create_object = zephir_init_properties_Phalcon_Mvc_Router_Annotations;

	return SUCCESS;
}

/**
 * Adds a resource to the annotations handler
 * A resource is a class that contains routing annotations
 * The class is located in a module
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, addModuleResource)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval module_zv, handler_zv, prefix_zv;
	zend_string *module = NULL, *handler = NULL, *prefix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&module_zv);
	ZVAL_UNDEF(&handler_zv);
	ZVAL_UNDEF(&prefix_zv);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(module)
		Z_PARAM_STR(handler)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(prefix)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&module_zv);
	ZVAL_STR_COPY(&module_zv, module);
	zephir_memory_observe(&handler_zv);
	ZVAL_STR_COPY(&handler_zv, handler);
	if (!prefix) {
		ZEPHIR_INIT_VAR(&prefix_zv);
	} else {
	zephir_memory_observe(&prefix_zv);
	ZVAL_STR_COPY(&prefix_zv, prefix);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0);
	zephir_array_fast_append(&_0, &prefix_zv);
	zephir_array_fast_append(&_0, &handler_zv);
	zephir_array_fast_append(&_0, &module_zv);
	zephir_update_property_array_append(this_ptr, SL("handlers"), &_0);
	RETURN_THIS();
}

/**
 * Adds a resource to the annotations handler
 * A resource is a class that contains routing annotations
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, addResource)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval handler_zv, prefix_zv;
	zend_string *handler = NULL, *prefix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_zv);
	ZVAL_UNDEF(&prefix_zv);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(handler)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(prefix)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&handler_zv);
	ZVAL_STR_COPY(&handler_zv, handler);
	if (!prefix) {
		ZEPHIR_INIT_VAR(&prefix_zv);
	} else {
	zephir_memory_observe(&prefix_zv);
	ZVAL_STR_COPY(&prefix_zv, prefix);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0);
	zephir_array_fast_append(&_0, &prefix_zv);
	zephir_array_fast_append(&_0, &handler_zv);
	zephir_update_property_array_append(this_ptr, SL("handlers"), &_0);
	RETURN_THIS();
}

/**
 * Return the registered resources
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, getResources)
{

	RETURN_MEMBER_TYPED(getThis(), "handlers", IS_ARRAY);
}

/**
 * Produce the routing parameters from the rewrite information
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, handle)
{
	zend_ulong _23$$18, _58$$41;
	zend_bool _41, _19$$15, _33$$18, _31$$19, _39$$23, _54$$38, _67$$41, _65$$42, _73$$46;
	zval sufixed;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL, *_13 = NULL, *_17 = NULL, *_29 = NULL, *_49 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri_zv, __$null, annotationsService, handlers, controllerSuffix, scope, prefix, route, compiledPattern, container, handler, controllerName, lowerControllerName, namespaceName, moduleName, handlerAnnotations, classAnnotations, annotations, annotation, methodAnnotations, method, collection, _0, _1, *_2, *_3, _40, _5$$6, _7$$6, _8$$6, _9$$7, _10$$7, _11$$4, _12$$12, *_14$$15, _15$$15, *_16$$15, _18$$15, *_20$$18, _21$$18, *_22$$18, _32$$18, _25$$19, *_26$$19, _27$$19, *_28$$19, _30$$19, _34$$23, *_35$$23, _36$$23, *_37$$23, _38$$23, _42$$29, _43$$29, _44$$29, _45$$30, _46$$30, _47$$27, _48$$35, *_50$$38, _51$$38, *_52$$38, _53$$38, *_55$$41, _56$$41, *_57$$41, _66$$41, _60$$42, *_61$$42, _62$$42, *_63$$42, _64$$42, _68$$46, *_69$$46, _70$$46, *_71$$46, _72$$46;
	zend_string *uri = NULL, *_24$$18, *_59$$41;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_zv);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&annotationsService);
	ZVAL_UNDEF(&handlers);
	ZVAL_UNDEF(&controllerSuffix);
	ZVAL_UNDEF(&scope);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&compiledPattern);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&lowerControllerName);
	ZVAL_UNDEF(&namespaceName);
	ZVAL_UNDEF(&moduleName);
	ZVAL_UNDEF(&handlerAnnotations);
	ZVAL_UNDEF(&classAnnotations);
	ZVAL_UNDEF(&annotations);
	ZVAL_UNDEF(&annotation);
	ZVAL_UNDEF(&methodAnnotations);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_15$$15);
	ZVAL_UNDEF(&_18$$15);
	ZVAL_UNDEF(&_21$$18);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_25$$19);
	ZVAL_UNDEF(&_27$$19);
	ZVAL_UNDEF(&_30$$19);
	ZVAL_UNDEF(&_34$$23);
	ZVAL_UNDEF(&_36$$23);
	ZVAL_UNDEF(&_38$$23);
	ZVAL_UNDEF(&_42$$29);
	ZVAL_UNDEF(&_43$$29);
	ZVAL_UNDEF(&_44$$29);
	ZVAL_UNDEF(&_45$$30);
	ZVAL_UNDEF(&_46$$30);
	ZVAL_UNDEF(&_47$$27);
	ZVAL_UNDEF(&_48$$35);
	ZVAL_UNDEF(&_51$$38);
	ZVAL_UNDEF(&_53$$38);
	ZVAL_UNDEF(&_56$$41);
	ZVAL_UNDEF(&_66$$41);
	ZVAL_UNDEF(&_60$$42);
	ZVAL_UNDEF(&_62$$42);
	ZVAL_UNDEF(&_64$$42);
	ZVAL_UNDEF(&_68$$46);
	ZVAL_UNDEF(&_70$$46);
	ZVAL_UNDEF(&_72$$46);
	ZVAL_UNDEF(&sufixed);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("handlers", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("controllerSuffix", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("routePrefix", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&uri_zv);
	ZVAL_STR_COPY(&uri_zv, uri);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 851, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (UNEXPECTED(Z_TYPE_P(&container) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "A dependency injection container is required to access the 'annotations' service", "phalcon/Mvc/Router/Annotations.zep", 114);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 852, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&handlers, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 853, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&controllerSuffix, &_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "annotations");
	ZEPHIR_CALL_METHOD(&annotationsService, &container, "getShared", NULL, 0, &_1);
	zephir_check_call_status();
	if (Z_TYPE_P(&handlers) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_1);
		zephir_string_to_char_array(&_1, &handlers);
		_2 = &_1;
	} else {
		_2 = &handlers;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/Router/Annotations.zep", 250);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _3)
		{
			ZEPHIR_INIT_NVAR(&scope);
			ZVAL_COPY(&scope, _3);
			if (Z_TYPE_P(&scope) != IS_ARRAY) {
				continue;
			}
			ZEPHIR_OBS_NVAR(&prefix);
			zephir_array_fetch_long(&prefix, &scope, 0, PH_NOISY, "phalcon/Mvc/Router/Annotations.zep", 129);
			if (!(ZEPHIR_IS_EMPTY(&prefix))) {
				ZEPHIR_INIT_NVAR(&route);
				object_init_ex(&route, phalcon_mvc_router_route_ce);
				ZEPHIR_CALL_METHOD(NULL, &route, "__construct", &_4, 110, &prefix);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_5$$6, &route, "getCompiledPattern", &_6, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_7$$6);
				ZVAL_STRING(&_7$$6, "$#");
				ZEPHIR_INIT_NVAR(&_8$$6);
				ZVAL_STRING(&_8$$6, "#");
				ZEPHIR_INIT_NVAR(&compiledPattern);
				zephir_fast_str_replace(&compiledPattern, &_7$$6, &_8$$6, &_5$$6);
				if (zephir_memnstr_str(&compiledPattern, SL("^"), "phalcon/Mvc/Router/Annotations.zep", 146)) {
					ZEPHIR_INIT_NVAR(&_9$$7);
					ZEPHIR_INIT_NVAR(&_10$$7);
					zephir_preg_match(&_10$$7, &compiledPattern, &uri_zv, &_9$$7, 0, 0 , 0 );
					if (!(zephir_is_true(&_10$$7))) {
						continue;
					}
				} else if (!(zephir_start_with(&uri_zv, &prefix, NULL))) {
					continue;
				}
			}
			ZEPHIR_OBS_NVAR(&handler);
			zephir_array_fetch_long(&handler, &scope, 1, PH_NOISY, "phalcon/Mvc/Router/Annotations.zep", 161);
			if (zephir_memnstr_str(&handler, SL("\\"), "phalcon/Mvc/Router/Annotations.zep", 163)) {
				ZEPHIR_INIT_NVAR(&controllerName);
				zephir_get_class_ns(&controllerName, &handler, 0);
				ZEPHIR_INIT_NVAR(&namespaceName);
				zephir_get_ns_class(&namespaceName, &handler, 0);
			} else {
				ZEPHIR_CPY_WRT(&controllerName, &handler);
				ZEPHIR_OBS_NVAR(&namespaceName);
				zephir_fetch_property(&namespaceName, this_ptr, SL("defaultNamespace"), PH_SILENT_CC);
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 854, &__$null);
			ZEPHIR_OBS_NVAR(&moduleName);
			zephir_array_isset_long_fetch(&moduleName, &scope, 2, 0);
			ZEPHIR_INIT_NVAR(&_11$$4);
			if (Z_TYPE_P(&moduleName) != IS_NULL) {
				ZEPHIR_CPY_WRT(&_11$$4, &moduleName);
			} else {
				ZEPHIR_INIT_NVAR(&_11$$4);
				ZVAL_STRING(&_11$$4, "");
			}
			ZEPHIR_CPY_WRT(&moduleName, &_11$$4);
			ZEPHIR_INIT_NVAR(&_11$$4);
			ZEPHIR_CONCAT_VV(&_11$$4, &controllerName, &controllerSuffix);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&sufixed, &_11$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (Z_TYPE_P(&namespaceName) != IS_NULL) {
				ZEPHIR_INIT_NVAR(&_12$$12);
				ZEPHIR_CONCAT_VSV(&_12$$12, &namespaceName, "\\", &sufixed);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_get_strval(&sufixed, &_12$$12);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_CALL_METHOD(&handlerAnnotations, &annotationsService, "get", &_13, 0, &sufixed);
			zephir_check_call_status();
			if (Z_TYPE_P(&handlerAnnotations) != IS_OBJECT) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&classAnnotations, &handlerAnnotations, "getClassAnnotations", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&classAnnotations) == IS_OBJECT) {
				ZEPHIR_CALL_METHOD(&annotations, &classAnnotations, "getAnnotations", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&annotations) == IS_ARRAY) {
					if (Z_TYPE_P(&annotations) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_15$$15);
						zephir_string_to_char_array(&_15$$15, &annotations);
						_14$$15 = &_15$$15;
					} else {
						_14$$15 = &annotations;
					}
					zephir_is_iterable(_14$$15, 0, "phalcon/Mvc/Router/Annotations.zep", 218);
					if (Z_TYPE_P(_14$$15) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_14$$15), _16$$15)
						{
							ZEPHIR_INIT_NVAR(&annotation);
							ZVAL_COPY(&annotation, _16$$15);
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "processControllerAnnotation", &_17, 0, &controllerName, &annotation);
							zephir_check_call_status();
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _14$$15, "rewind", NULL, 0);
						zephir_check_call_status();
						_19$$15 = 1;
						while (1) {
							if (_19$$15) {
								_19$$15 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _14$$15, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_18$$15, _14$$15, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_18$$15)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&annotation, _14$$15, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "processControllerAnnotation", &_17, 0, &controllerName, &annotation);
								zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&annotation);
				}
			}
			ZEPHIR_CALL_METHOD(&methodAnnotations, &handlerAnnotations, "getMethodsAnnotations", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&methodAnnotations) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(&lowerControllerName);
				zephir_uncamelize(&lowerControllerName, &controllerName, NULL );
				if (Z_TYPE_P(&methodAnnotations) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_21$$18);
					zephir_string_to_char_array(&_21$$18, &methodAnnotations);
					_20$$18 = &_21$$18;
				} else {
					_20$$18 = &methodAnnotations;
				}
				zephir_is_iterable(_20$$18, 0, "phalcon/Mvc/Router/Annotations.zep", 244);
				if (Z_TYPE_P(_20$$18) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_20$$18), _23$$18, _24$$18, _22$$18)
					{
						ZEPHIR_INIT_NVAR(&method);
						if (_24$$18 != NULL) { 
							ZVAL_STR_COPY(&method, _24$$18);
						} else {
							ZVAL_LONG(&method, _23$$18);
						}
						ZEPHIR_INIT_NVAR(&collection);
						ZVAL_COPY(&collection, _22$$18);
						if (Z_TYPE_P(&collection) != IS_OBJECT) {
							continue;
						}
						ZEPHIR_CALL_METHOD(&_25$$19, &collection, "getAnnotations", NULL, 0);
						zephir_check_call_status();
						if (Z_TYPE_P(&_25$$19) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_27$$19);
							zephir_string_to_char_array(&_27$$19, &_25$$19);
							_26$$19 = &_27$$19;
						} else {
							_26$$19 = &_25$$19;
						}
						zephir_is_iterable(_26$$19, 0, "phalcon/Mvc/Router/Annotations.zep", 243);
						if (Z_TYPE_P(_26$$19) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_26$$19), _28$$19)
							{
								ZEPHIR_INIT_NVAR(&annotation);
								ZVAL_COPY(&annotation, _28$$19);
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
								zephir_check_call_status();
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _26$$19, "rewind", NULL, 0);
							zephir_check_call_status();
							_31$$19 = 1;
							while (1) {
								if (_31$$19) {
									_31$$19 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _26$$19, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_30$$19, _26$$19, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_30$$19)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&annotation, _26$$19, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
									zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&annotation);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _20$$18, "rewind", NULL, 0);
					zephir_check_call_status();
					_33$$18 = 1;
					while (1) {
						if (_33$$18) {
							_33$$18 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _20$$18, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_32$$18, _20$$18, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_32$$18)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&method, _20$$18, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&collection, _20$$18, "current", NULL, 0);
						zephir_check_call_status();
							if (Z_TYPE_P(&collection) != IS_OBJECT) {
								continue;
							}
							ZEPHIR_CALL_METHOD(&_34$$23, &collection, "getAnnotations", NULL, 0);
							zephir_check_call_status();
							if (Z_TYPE_P(&_34$$23) == IS_STRING) {
								ZEPHIR_INIT_NVAR(&_36$$23);
								zephir_string_to_char_array(&_36$$23, &_34$$23);
								_35$$23 = &_36$$23;
							} else {
								_35$$23 = &_34$$23;
							}
							zephir_is_iterable(_35$$23, 0, "phalcon/Mvc/Router/Annotations.zep", 243);
							if (Z_TYPE_P(_35$$23) == IS_ARRAY) {
								ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_35$$23), _37$$23)
								{
									ZEPHIR_INIT_NVAR(&annotation);
									ZVAL_COPY(&annotation, _37$$23);
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
									zephir_check_call_status();
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, _35$$23, "rewind", NULL, 0);
								zephir_check_call_status();
								_39$$23 = 1;
								while (1) {
									if (_39$$23) {
										_39$$23 = 0;
									} else {
										ZEPHIR_CALL_METHOD(NULL, _35$$23, "next", NULL, 0);
										zephir_check_call_status();
									}
									ZEPHIR_CALL_METHOD(&_38$$23, _35$$23, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_38$$23)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&annotation, _35$$23, "current", NULL, 0);
									zephir_check_call_status();
										ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
										zephir_check_call_status();
								}
							}
							ZEPHIR_INIT_NVAR(&annotation);
					}
				}
				ZEPHIR_INIT_NVAR(&collection);
				ZEPHIR_INIT_NVAR(&method);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_41 = 1;
		while (1) {
			if (_41) {
				_41 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_40, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_40)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&scope, _2, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&scope) != IS_ARRAY) {
					continue;
				}
				ZEPHIR_OBS_NVAR(&prefix);
				zephir_array_fetch_long(&prefix, &scope, 0, PH_NOISY, "phalcon/Mvc/Router/Annotations.zep", 129);
				if (!(ZEPHIR_IS_EMPTY(&prefix))) {
					ZEPHIR_INIT_NVAR(&route);
					object_init_ex(&route, phalcon_mvc_router_route_ce);
					ZEPHIR_CALL_METHOD(NULL, &route, "__construct", &_4, 110, &prefix);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_42$$29, &route, "getCompiledPattern", &_6, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_43$$29);
					ZVAL_STRING(&_43$$29, "$#");
					ZEPHIR_INIT_NVAR(&_44$$29);
					ZVAL_STRING(&_44$$29, "#");
					ZEPHIR_INIT_NVAR(&compiledPattern);
					zephir_fast_str_replace(&compiledPattern, &_43$$29, &_44$$29, &_42$$29);
					if (zephir_memnstr_str(&compiledPattern, SL("^"), "phalcon/Mvc/Router/Annotations.zep", 146)) {
						ZEPHIR_INIT_NVAR(&_45$$30);
						ZEPHIR_INIT_NVAR(&_46$$30);
						zephir_preg_match(&_46$$30, &compiledPattern, &uri_zv, &_45$$30, 0, 0 , 0 );
						if (!(zephir_is_true(&_46$$30))) {
							continue;
						}
					} else if (!(zephir_start_with(&uri_zv, &prefix, NULL))) {
						continue;
					}
				}
				ZEPHIR_OBS_NVAR(&handler);
				zephir_array_fetch_long(&handler, &scope, 1, PH_NOISY, "phalcon/Mvc/Router/Annotations.zep", 161);
				if (zephir_memnstr_str(&handler, SL("\\"), "phalcon/Mvc/Router/Annotations.zep", 163)) {
					ZEPHIR_INIT_NVAR(&controllerName);
					zephir_get_class_ns(&controllerName, &handler, 0);
					ZEPHIR_INIT_NVAR(&namespaceName);
					zephir_get_ns_class(&namespaceName, &handler, 0);
				} else {
					ZEPHIR_CPY_WRT(&controllerName, &handler);
					ZEPHIR_OBS_NVAR(&namespaceName);
					zephir_fetch_property(&namespaceName, this_ptr, SL("defaultNamespace"), PH_SILENT_CC);
				}
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 854, &__$null);
				ZEPHIR_OBS_NVAR(&moduleName);
				zephir_array_isset_long_fetch(&moduleName, &scope, 2, 0);
				ZEPHIR_INIT_NVAR(&_47$$27);
				if (Z_TYPE_P(&moduleName) != IS_NULL) {
					ZEPHIR_CPY_WRT(&_47$$27, &moduleName);
				} else {
					ZEPHIR_INIT_NVAR(&_47$$27);
					ZVAL_STRING(&_47$$27, "");
				}
				ZEPHIR_CPY_WRT(&moduleName, &_47$$27);
				ZEPHIR_INIT_NVAR(&_47$$27);
				ZEPHIR_CONCAT_VV(&_47$$27, &controllerName, &controllerSuffix);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_get_strval(&sufixed, &_47$$27);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (Z_TYPE_P(&namespaceName) != IS_NULL) {
					ZEPHIR_INIT_NVAR(&_48$$35);
					ZEPHIR_CONCAT_VSV(&_48$$35, &namespaceName, "\\", &sufixed);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_get_strval(&sufixed, &_48$$35);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&handlerAnnotations, &annotationsService, "get", &_49, 0, &sufixed);
				zephir_check_call_status();
				if (Z_TYPE_P(&handlerAnnotations) != IS_OBJECT) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&classAnnotations, &handlerAnnotations, "getClassAnnotations", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&classAnnotations) == IS_OBJECT) {
					ZEPHIR_CALL_METHOD(&annotations, &classAnnotations, "getAnnotations", NULL, 0);
					zephir_check_call_status();
					if (Z_TYPE_P(&annotations) == IS_ARRAY) {
						if (Z_TYPE_P(&annotations) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_51$$38);
							zephir_string_to_char_array(&_51$$38, &annotations);
							_50$$38 = &_51$$38;
						} else {
							_50$$38 = &annotations;
						}
						zephir_is_iterable(_50$$38, 0, "phalcon/Mvc/Router/Annotations.zep", 218);
						if (Z_TYPE_P(_50$$38) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_50$$38), _52$$38)
							{
								ZEPHIR_INIT_NVAR(&annotation);
								ZVAL_COPY(&annotation, _52$$38);
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "processControllerAnnotation", &_17, 0, &controllerName, &annotation);
								zephir_check_call_status();
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _50$$38, "rewind", NULL, 0);
							zephir_check_call_status();
							_54$$38 = 1;
							while (1) {
								if (_54$$38) {
									_54$$38 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _50$$38, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_53$$38, _50$$38, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_53$$38)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&annotation, _50$$38, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "processControllerAnnotation", &_17, 0, &controllerName, &annotation);
									zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&annotation);
					}
				}
				ZEPHIR_CALL_METHOD(&methodAnnotations, &handlerAnnotations, "getMethodsAnnotations", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&methodAnnotations) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&lowerControllerName);
					zephir_uncamelize(&lowerControllerName, &controllerName, NULL );
					if (Z_TYPE_P(&methodAnnotations) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_56$$41);
						zephir_string_to_char_array(&_56$$41, &methodAnnotations);
						_55$$41 = &_56$$41;
					} else {
						_55$$41 = &methodAnnotations;
					}
					zephir_is_iterable(_55$$41, 0, "phalcon/Mvc/Router/Annotations.zep", 244);
					if (Z_TYPE_P(_55$$41) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_55$$41), _58$$41, _59$$41, _57$$41)
						{
							ZEPHIR_INIT_NVAR(&method);
							if (_59$$41 != NULL) { 
								ZVAL_STR_COPY(&method, _59$$41);
							} else {
								ZVAL_LONG(&method, _58$$41);
							}
							ZEPHIR_INIT_NVAR(&collection);
							ZVAL_COPY(&collection, _57$$41);
							if (Z_TYPE_P(&collection) != IS_OBJECT) {
								continue;
							}
							ZEPHIR_CALL_METHOD(&_60$$42, &collection, "getAnnotations", NULL, 0);
							zephir_check_call_status();
							if (Z_TYPE_P(&_60$$42) == IS_STRING) {
								ZEPHIR_INIT_NVAR(&_62$$42);
								zephir_string_to_char_array(&_62$$42, &_60$$42);
								_61$$42 = &_62$$42;
							} else {
								_61$$42 = &_60$$42;
							}
							zephir_is_iterable(_61$$42, 0, "phalcon/Mvc/Router/Annotations.zep", 243);
							if (Z_TYPE_P(_61$$42) == IS_ARRAY) {
								ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_61$$42), _63$$42)
								{
									ZEPHIR_INIT_NVAR(&annotation);
									ZVAL_COPY(&annotation, _63$$42);
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
									zephir_check_call_status();
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, _61$$42, "rewind", NULL, 0);
								zephir_check_call_status();
								_65$$42 = 1;
								while (1) {
									if (_65$$42) {
										_65$$42 = 0;
									} else {
										ZEPHIR_CALL_METHOD(NULL, _61$$42, "next", NULL, 0);
										zephir_check_call_status();
									}
									ZEPHIR_CALL_METHOD(&_64$$42, _61$$42, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_64$$42)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&annotation, _61$$42, "current", NULL, 0);
									zephir_check_call_status();
										ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
										zephir_check_call_status();
								}
							}
							ZEPHIR_INIT_NVAR(&annotation);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _55$$41, "rewind", NULL, 0);
						zephir_check_call_status();
						_67$$41 = 1;
						while (1) {
							if (_67$$41) {
								_67$$41 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _55$$41, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_66$$41, _55$$41, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_66$$41)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&method, _55$$41, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&collection, _55$$41, "current", NULL, 0);
							zephir_check_call_status();
								if (Z_TYPE_P(&collection) != IS_OBJECT) {
									continue;
								}
								ZEPHIR_CALL_METHOD(&_68$$46, &collection, "getAnnotations", NULL, 0);
								zephir_check_call_status();
								if (Z_TYPE_P(&_68$$46) == IS_STRING) {
									ZEPHIR_INIT_NVAR(&_70$$46);
									zephir_string_to_char_array(&_70$$46, &_68$$46);
									_69$$46 = &_70$$46;
								} else {
									_69$$46 = &_68$$46;
								}
								zephir_is_iterable(_69$$46, 0, "phalcon/Mvc/Router/Annotations.zep", 243);
								if (Z_TYPE_P(_69$$46) == IS_ARRAY) {
									ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_69$$46), _71$$46)
									{
										ZEPHIR_INIT_NVAR(&annotation);
										ZVAL_COPY(&annotation, _71$$46);
										ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
										zephir_check_call_status();
									} ZEND_HASH_FOREACH_END();
								} else {
									ZEPHIR_CALL_METHOD(NULL, _69$$46, "rewind", NULL, 0);
									zephir_check_call_status();
									_73$$46 = 1;
									while (1) {
										if (_73$$46) {
											_73$$46 = 0;
										} else {
											ZEPHIR_CALL_METHOD(NULL, _69$$46, "next", NULL, 0);
											zephir_check_call_status();
										}
										ZEPHIR_CALL_METHOD(&_72$$46, _69$$46, "valid", NULL, 0);
										zephir_check_call_status();
										if (!zend_is_true(&_72$$46)) {
											break;
										}
										ZEPHIR_CALL_METHOD(&annotation, _69$$46, "current", NULL, 0);
										zephir_check_call_status();
											ZEPHIR_CALL_METHOD(NULL, this_ptr, "processActionAnnotation", &_29, 0, &moduleName, &namespaceName, &lowerControllerName, &method, &annotation);
											zephir_check_call_status();
									}
								}
								ZEPHIR_INIT_NVAR(&annotation);
						}
					}
					ZEPHIR_INIT_NVAR(&collection);
					ZEPHIR_INIT_NVAR(&method);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&scope);
	ZEPHIR_CALL_PARENT(NULL, phalcon_mvc_router_annotations_ce, getThis(), "handle", NULL, 0, &uri_zv);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Checks for annotations in the public methods of the controller
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, processActionAnnotation)
{
	zend_ulong _12$$18, _21$$21;
	zend_bool isRoute = 0, _8, _27, _16$$18, _25$$21;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_14 = NULL, *_17 = NULL, *_23 = NULL, *_26 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval module_zv, namespaceName_zv, controller_zv, action_zv, *annotation, annotation_sub, name, proxyActionName, actionName, routePrefix, paths, value, uri, route, methods, converts, param, convert, converterParam, routeName, beforeMatch, _0, _1, _2, _5, _6, _3$$6, _4$$6, _7$$16, *_9$$18, _10$$18, *_11$$18, _15$$18, *_18$$21, _19$$21, *_20$$21, _24$$21;
	zend_string *module = NULL, *namespaceName = NULL, *controller = NULL, *action = NULL, *_13$$18, *_22$$21;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&module_zv);
	ZVAL_UNDEF(&namespaceName_zv);
	ZVAL_UNDEF(&controller_zv);
	ZVAL_UNDEF(&action_zv);
	ZVAL_UNDEF(&annotation_sub);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&proxyActionName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&routePrefix);
	ZVAL_UNDEF(&paths);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&methods);
	ZVAL_UNDEF(&converts);
	ZVAL_UNDEF(&param);
	ZVAL_UNDEF(&convert);
	ZVAL_UNDEF(&converterParam);
	ZVAL_UNDEF(&routeName);
	ZVAL_UNDEF(&beforeMatch);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_7$$16);
	ZVAL_UNDEF(&_10$$18);
	ZVAL_UNDEF(&_15$$18);
	ZVAL_UNDEF(&_19$$21);
	ZVAL_UNDEF(&_24$$21);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("actionSuffix", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("routePrefix", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("actionPreformatCallback", 23, 1);
	}

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(module)
		Z_PARAM_STR(namespaceName)
		Z_PARAM_STR(controller)
		Z_PARAM_STR(action)
		Z_PARAM_OBJECT_OF_CLASS(annotation, phalcon_annotations_annotation_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	annotation = ZEND_CALL_ARG(execute_data, 5);
	zephir_memory_observe(&module_zv);
	ZVAL_STR_COPY(&module_zv, module);
	zephir_memory_observe(&namespaceName_zv);
	ZVAL_STR_COPY(&namespaceName_zv, namespaceName);
	zephir_memory_observe(&controller_zv);
	ZVAL_STR_COPY(&controller_zv, controller);
	zephir_memory_observe(&action_zv);
	ZVAL_STR_COPY(&action_zv, action);
	isRoute = 0;
	ZEPHIR_INIT_VAR(&methods);
	ZVAL_NULL(&methods);
	ZEPHIR_CALL_METHOD(&name, annotation, "getName", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(&name, "Route")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&name, "Get")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&name, "Post")) { goto zephir_switch_0_clause_2; }
	if (ZEPHIR_IS_STRING(&name, "Put")) { goto zephir_switch_0_clause_3; }
	if (ZEPHIR_IS_STRING(&name, "Patch")) { goto zephir_switch_0_clause_4; }
	if (ZEPHIR_IS_STRING(&name, "Delete")) { goto zephir_switch_0_clause_5; }
	if (ZEPHIR_IS_STRING(&name, "Options")) { goto zephir_switch_0_clause_6; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		isRoute = 1;
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
	zephir_switch_0_clause_3: ;
	zephir_switch_0_clause_4: ;
	zephir_switch_0_clause_5: ;
	zephir_switch_0_clause_6: ;
		isRoute = 1;
		ZEPHIR_INIT_NVAR(&methods);
		zephir_fast_strtoupper(&methods, &name);
		goto zephir_switch_0_end;
	zephir_switch_0_end: ;

	if (!(isRoute)) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 855, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "");
	ZEPHIR_INIT_VAR(&proxyActionName);
	zephir_fast_str_replace(&proxyActionName, &_0, &_1, &action_zv);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 854, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&routePrefix, &_2);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_2, 856, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_2) != IS_NULL) {
		zephir_read_property_cached(&_3$$6, this_ptr, _zephir_prop_2, 856, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(&_4$$6, "call_user_func", NULL, 191, &_3$$6, &proxyActionName);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&proxyActionName, &_4$$6);
	}
	ZEPHIR_INIT_VAR(&actionName);
	zephir_fast_strtolower(&actionName, &proxyActionName);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "paths");
	ZEPHIR_CALL_METHOD(&paths, annotation, "getNamedArgument", NULL, 0, &_5);
	zephir_check_call_status();
	if (Z_TYPE_P(&paths) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(&paths);
		array_init(&paths);
	}
	if (!(ZEPHIR_IS_EMPTY(&module_zv))) {
		zephir_array_update_string(&paths, SL("module"), &module_zv, PH_COPY | PH_SEPARATE);
	}
	if (!(ZEPHIR_IS_EMPTY(&namespaceName_zv))) {
		zephir_array_update_string(&paths, SL("namespace"), &namespaceName_zv, PH_COPY | PH_SEPARATE);
	}
	zephir_array_update_string(&paths, SL("controller"), &controller_zv, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&paths, SL("action"), &actionName, PH_COPY | PH_SEPARATE);
	ZVAL_LONG(&_6, 0);
	ZEPHIR_CALL_METHOD(&value, annotation, "getArgument", NULL, 0, &_6);
	zephir_check_call_status();
	if (Z_TYPE_P(&value) != IS_NULL) {
		if (!ZEPHIR_IS_STRING(&value, "/")) {
			ZEPHIR_INIT_VAR(&uri);
			ZEPHIR_CONCAT_VV(&uri, &routePrefix, &value);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			if (Z_TYPE_P(&routePrefix) != IS_NULL) {
				ZEPHIR_CPY_WRT(&uri, &routePrefix);
			} else {
				ZEPHIR_CPY_WRT(&uri, &value);
			}
		}
	} else {
		ZEPHIR_INIT_NVAR(&uri);
		ZEPHIR_CONCAT_VV(&uri, &routePrefix, &actionName);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&route, this_ptr, "add", NULL, 0, &uri, &paths);
	zephir_check_call_status();
	if (Z_TYPE_P(&methods) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_7$$16);
		ZVAL_STRING(&_7$$16, "methods");
		ZEPHIR_CALL_METHOD(&methods, annotation, "getNamedArgument", NULL, 0, &_7$$16);
		zephir_check_call_status();
	}
	_8 = Z_TYPE_P(&methods) == IS_ARRAY;
	if (!(_8)) {
		_8 = Z_TYPE_P(&methods) == IS_STRING;
	}
	if (_8) {
		ZEPHIR_CALL_METHOD(NULL, &route, "via", NULL, 0, &methods);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "converts");
	ZEPHIR_CALL_METHOD(&converts, annotation, "getNamedArgument", NULL, 0, &_5);
	zephir_check_call_status();
	if (Z_TYPE_P(&converts) == IS_ARRAY) {
		if (Z_TYPE_P(&converts) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_10$$18);
			zephir_string_to_char_array(&_10$$18, &converts);
			_9$$18 = &_10$$18;
		} else {
			_9$$18 = &converts;
		}
		zephir_is_iterable(_9$$18, 0, "phalcon/Mvc/Router/Annotations.zep", 373);
		if (Z_TYPE_P(_9$$18) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9$$18), _12$$18, _13$$18, _11$$18)
			{
				ZEPHIR_INIT_NVAR(&param);
				if (_13$$18 != NULL) { 
					ZVAL_STR_COPY(&param, _13$$18);
				} else {
					ZVAL_LONG(&param, _12$$18);
				}
				ZEPHIR_INIT_NVAR(&convert);
				ZVAL_COPY(&convert, _11$$18);
				ZEPHIR_CALL_METHOD(NULL, &route, "convert", &_14, 0, &param, &convert);
				zephir_check_call_status();
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _9$$18, "rewind", NULL, 0);
			zephir_check_call_status();
			_16$$18 = 1;
			while (1) {
				if (_16$$18) {
					_16$$18 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _9$$18, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_15$$18, _9$$18, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_15$$18)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&param, _9$$18, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&convert, _9$$18, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &route, "convert", &_17, 0, &param, &convert);
					zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&convert);
		ZEPHIR_INIT_NVAR(&param);
	}
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "converters");
	ZEPHIR_CALL_METHOD(&converts, annotation, "getNamedArgument", NULL, 0, &_5);
	zephir_check_call_status();
	if (Z_TYPE_P(&converts) == IS_ARRAY) {
		if (Z_TYPE_P(&converts) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_19$$21);
			zephir_string_to_char_array(&_19$$21, &converts);
			_18$$21 = &_19$$21;
		} else {
			_18$$21 = &converts;
		}
		zephir_is_iterable(_18$$21, 0, "phalcon/Mvc/Router/Annotations.zep", 384);
		if (Z_TYPE_P(_18$$21) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_18$$21), _21$$21, _22$$21, _20$$21)
			{
				ZEPHIR_INIT_NVAR(&converterParam);
				if (_22$$21 != NULL) { 
					ZVAL_STR_COPY(&converterParam, _22$$21);
				} else {
					ZVAL_LONG(&converterParam, _21$$21);
				}
				ZEPHIR_INIT_NVAR(&convert);
				ZVAL_COPY(&convert, _20$$21);
				ZEPHIR_CALL_METHOD(NULL, &route, "convert", &_23, 0, &converterParam, &convert);
				zephir_check_call_status();
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _18$$21, "rewind", NULL, 0);
			zephir_check_call_status();
			_25$$21 = 1;
			while (1) {
				if (_25$$21) {
					_25$$21 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _18$$21, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_24$$21, _18$$21, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_24$$21)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&converterParam, _18$$21, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&convert, _18$$21, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &route, "convert", &_26, 0, &converterParam, &convert);
					zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&convert);
		ZEPHIR_INIT_NVAR(&converterParam);
	}
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "beforeMatch");
	ZEPHIR_CALL_METHOD(&beforeMatch, annotation, "getNamedArgument", NULL, 0, &_5);
	zephir_check_call_status();
	_27 = Z_TYPE_P(&beforeMatch) == IS_ARRAY;
	if (!(_27)) {
		_27 = Z_TYPE_P(&beforeMatch) == IS_STRING;
	}
	if (_27) {
		ZEPHIR_CALL_METHOD(NULL, &route, "beforeMatch", NULL, 0, &beforeMatch);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "name");
	ZEPHIR_CALL_METHOD(&routeName, annotation, "getNamedArgument", NULL, 0, &_5);
	zephir_check_call_status();
	if (Z_TYPE_P(&routeName) == IS_STRING) {
		ZEPHIR_CALL_METHOD(NULL, &route, "setName", NULL, 0, &routeName);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Checks for annotations in the controller docblock
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, processControllerAnnotation)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval handler_zv, *annotation, annotation_sub, _0, _1$$3, _2$$3;
	zend_string *handler = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_zv);
	ZVAL_UNDEF(&annotation_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("routePrefix", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(handler)
		Z_PARAM_OBJECT_OF_CLASS(annotation, phalcon_annotations_annotation_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	annotation = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&handler_zv);
	ZVAL_STR_COPY(&handler_zv, handler);
	ZEPHIR_CALL_METHOD(&_0, annotation, "getName", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(&_0, "RoutePrefix")) {
		ZVAL_LONG(&_2$$3, 0);
		ZEPHIR_CALL_METHOD(&_1$$3, annotation, "getArgument", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 854, &_1$$3);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Changes the action method suffix
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, setActionSuffix)
{
	zval actionSuffix_zv;
	zend_string *actionSuffix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&actionSuffix_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("actionSuffix", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(actionSuffix)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&actionSuffix_zv, actionSuffix);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 855, &actionSuffix_zv);
}

/**
 * Sets the action preformat callback
 * $action here already without suffix 'Action'
 *
 * ```php
 * // Array as callback
 * $annotationRouter->setActionPreformatCallback(
 *      [
 *          new Uncamelize(),
 *          '__invoke'
 *      ]
 *  );
 *
 * // Function as callback
 * $annotationRouter->setActionPreformatCallback(
 *     function ($action) {
 *         return $action;
 *     }
 * );
 *
 * // String as callback
 * $annotationRouter->setActionPreformatCallback('strtolower');
 *
 * // If empty method constructor called [null], sets uncamelize with - delimiter
 * $annotationRouter->setActionPreformatCallback();
 * ```
 *
 * @param callable|string|null $callback
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, setActionPreformatCallback)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *callback = NULL, callback_sub, __$null, _0$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("actionPreformatCallback", 23, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &callback);
	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}
	if (EXPECTED(zephir_is_callable(callback))) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 856, callback);
	} else if (Z_TYPE_P(callback) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_0$$4);
		ZEPHIR_INIT_NVAR(&_0$$4);
		zephir_create_closure_ex(&_0$$4, NULL, phalcon_13__closure_ce, SL("__invoke"));
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 856, &_0$$4);
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_router_exception_ce, "The 'callback' parameter must be either a callable or NULL.", "phalcon/Mvc/Router/Annotations.zep", 463);
		return;
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * @return callable|string|null
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, getActionPreformatCallback)
{

	RETURN_MEMBER(getThis(), "actionPreformatCallback");
}

/**
 * Changes the controller class suffix
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, setControllerSuffix)
{
	zval controllerSuffix_zv;
	zend_string *controllerSuffix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerSuffix_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("controllerSuffix", 16, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(controllerSuffix)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&controllerSuffix_zv, controllerSuffix);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 853, &controllerSuffix_zv);
}

zend_object *zephir_init_properties_Phalcon_Mvc_Router_Annotations(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _12, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	

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
		zephir_read_property_ex(&_12, this_ptr, ZEND_STRL("handlers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("handlers"), &_13$$9);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

