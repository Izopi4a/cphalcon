
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "Zend/zend_closures.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/concat.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the
 * LICENSE.txt file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Model\Binder
 *
 * This is an class for binding models into params for handler
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Binder)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\Model, Binder, phalcon, mvc_model_binder, phalcon_mvc_model_binder_method_entry, 0);

	/**
	 * Array for storing active bound models
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_binder_ce, SL("boundModels"), ZEND_ACC_PROTECTED);
	/**
	 * Cache object used for caching parameters for model binding
	 *
	 * @var AdapterInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_binder_ce, SL("cache"), ZEND_ACC_PROTECTED);
	/**
	 * Internal cache for caching parameters for model binding during request
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_binder_ce, SL("internalCache"), ZEND_ACC_PROTECTED);
	/**
	 * Array for original values
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_binder_ce, SL("originalValues"), ZEND_ACC_PROTECTED);
	phalcon_mvc_model_binder_ce->create_object = zephir_init_properties_Phalcon_Mvc_Model_Binder;

	zend_class_implements(phalcon_mvc_model_binder_ce, 1, phalcon_mvc_model_binderinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Binder constructor
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, __construct)
{
	zval *cache = NULL, cache_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cache_sub);
	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("cache", 5, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(cache, phalcon_cache_adapter_adapterinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &cache);
	if (!cache) {
		cache = &cache_sub;
		cache = &__$null;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 718, cache);
}

/**
 * Bind models into params in proper handler
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, bindToHandler)
{
	zend_ulong _6$$4;
	zend_bool _1, _10$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *cacheKey = NULL, *methodName = NULL, *_7$$4;
	zval params;
	zval *handler, handler_sub, *params_param = NULL, cacheKey_zv, methodName_zv, paramKey, className, boundModel, paramsCache, paramValue, _0, _2, *_3$$4, _4$$4, *_5$$4, _9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&cacheKey_zv);
	ZVAL_UNDEF(&methodName_zv);
	ZVAL_UNDEF(&paramKey);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&boundModel);
	ZVAL_UNDEF(&paramsCache);
	ZVAL_UNDEF(&paramValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&params);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("originalValues", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("boundModels", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_OBJECT(handler)
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
		Z_PARAM_STR(cacheKey)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(methodName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 1);
	params_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_get_arrval(&params, params_param);
	zephir_memory_observe(&cacheKey_zv);
	ZVAL_STR_COPY(&cacheKey_zv, cacheKey);
	if (!methodName) {
		ZEPHIR_INIT_VAR(&methodName_zv);
	} else {
	zephir_memory_observe(&methodName_zv);
	ZVAL_STR_COPY(&methodName_zv, methodName);
	}
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 719, &_0);
	_1 = !((zephir_is_instance_of(handler, SL("Closure"))));
	if (_1) {
		_1 = ZEPHIR_IS_NULL(&methodName_zv);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "You must specify methodName for handler or pass Closure as handler", "phalcon/Mvc/Model/Binder.zep", 76);
		return;
	}
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 720, &_2);
	ZEPHIR_CALL_METHOD(&paramsCache, this_ptr, "getParamsFromCache", NULL, 0, &cacheKey_zv);
	zephir_check_call_status();
	if (Z_TYPE_P(&paramsCache) == IS_ARRAY) {
		if (Z_TYPE_P(&paramsCache) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_4$$4);
			zephir_string_to_char_array(&_4$$4, &paramsCache);
			_3$$4 = &_4$$4;
		} else {
			_3$$4 = &paramsCache;
		}
		zephir_is_iterable(_3$$4, 0, "phalcon/Mvc/Model/Binder.zep", 91);
		if (Z_TYPE_P(_3$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_3$$4), _6$$4, _7$$4, _5$$4)
			{
				ZEPHIR_INIT_NVAR(&paramKey);
				if (_7$$4 != NULL) { 
					ZVAL_STR_COPY(&paramKey, _7$$4);
				} else {
					ZVAL_LONG(&paramKey, _6$$4);
				}
				ZEPHIR_INIT_NVAR(&className);
				ZVAL_COPY(&className, _5$$4);
				ZEPHIR_OBS_NVAR(&paramValue);
				zephir_array_fetch(&paramValue, &params, &paramKey, PH_NOISY, "phalcon/Mvc/Model/Binder.zep", 84);
				ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_8, 0, &paramValue, &className);
				zephir_check_call_status();
				zephir_update_property_array(this_ptr, SL("originalValues"), &paramKey, &paramValue);
				zephir_array_update_zval(&params, &paramKey, &boundModel, PH_COPY | PH_SEPARATE);
				zephir_update_property_array(this_ptr, SL("boundModels"), &paramKey, &boundModel);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _3$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_10$$4 = 1;
			while (1) {
				if (_10$$4) {
					_10$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _3$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_9$$4, _3$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_9$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&paramKey, _3$$4, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&className, _3$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&paramValue);
					zephir_array_fetch(&paramValue, &params, &paramKey, PH_NOISY, "phalcon/Mvc/Model/Binder.zep", 84);
					ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_8, 0, &paramValue, &className);
					zephir_check_call_status();
					zephir_update_property_array(this_ptr, SL("originalValues"), &paramKey, &paramValue);
					zephir_array_update_zval(&params, &paramKey, &boundModel, PH_COPY | PH_SEPARATE);
					zephir_update_property_array(this_ptr, SL("boundModels"), &paramKey, &boundModel);
			}
		}
		ZEPHIR_INIT_NVAR(&className);
		ZEPHIR_INIT_NVAR(&paramKey);
		RETURN_CTOR(&params);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getParamsFromReflection", NULL, 0, handler, &params, &cacheKey_zv, &methodName_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Find the model by param value.
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, findBoundModel)
{
	zend_class_entry *_0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *className = NULL;
	zval *paramValue, paramValue_sub, className_zv;

	ZVAL_UNDEF(&paramValue_sub);
	ZVAL_UNDEF(&className_zv);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(paramValue)
		Z_PARAM_STR(className)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	paramValue = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&className_zv);
	ZVAL_STR_COPY(&className_zv, className);
	_0 = zephir_fetch_class(&className_zv);
	ZEPHIR_RETURN_CALL_CE_STATIC(_0, "findFirst", NULL, 0, paramValue);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the active bound models
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, getBoundModels)
{

	RETURN_MEMBER_TYPED(getThis(), "boundModels", IS_ARRAY);
}

/**
 * Return the array for original values
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, getOriginalValues)
{

	RETURN_MEMBER_TYPED(getThis(), "originalValues", IS_ARRAY);
}

/**
 * Sets cache instance
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, getCache)
{

	RETURN_MEMBER(getThis(), "cache");
}

/**
 * Get params classes from cache by key
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, getParamsFromCache)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval cacheKey_zv, cache, internalParams, _0, _1, _3;
	zend_string *cacheKey = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cacheKey_zv);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&internalParams);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("internalCache", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("cache", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(cacheKey)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&cacheKey_zv);
	ZVAL_STR_COPY(&cacheKey_zv, cacheKey);
	zephir_memory_observe(&internalParams);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 721, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_fetch(&internalParams, &_0, &cacheKey_zv, 0)) {
		RETURN_CCTOR(&internalParams);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 718, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&cache, &_1);
	_2 = Z_TYPE_P(&cache) == IS_NULL;
	if (!(_2)) {
		ZEPHIR_CALL_METHOD(&_3, &cache, "has", NULL, 0, &cacheKey_zv);
		zephir_check_call_status();
		_2 = !zephir_is_true(&_3);
	}
	if (_2) {
		RETURN_MM_NULL();
	}
	ZEPHIR_CALL_METHOD(&internalParams, &cache, "get", NULL, 0, &cacheKey_zv);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("internalCache"), &cacheKey_zv, &internalParams);
	RETURN_CCTOR(&internalParams);
}

/**
 * Get modified params for handler using reflection
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, getParamsFromReflection)
{
	zend_class_entry *_11$$10, *_22$$24;
	zend_bool _17, _6$$5, _18$$19;
	zend_ulong _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_14 = NULL, *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *cacheKey = NULL, *methodName = NULL, *_5;
	zval params, paramsCache;
	zval *handler, handler_sub, *params_param = NULL, cacheKey_zv, methodName_zv, methodParams, reflection, paramKey, methodParam, className, realClasses, boundModel, cache, handlerClass, reflectionClass, paramsKeys, paramValue, _0, *_1, _2, *_3, _16, _8$$5, _9$$5, _7$$7, _12$$14, _13$$14, _20$$19, _21$$19, _19$$21, _23$$28, _24$$28;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&cacheKey_zv);
	ZVAL_UNDEF(&methodName_zv);
	ZVAL_UNDEF(&methodParams);
	ZVAL_UNDEF(&reflection);
	ZVAL_UNDEF(&paramKey);
	ZVAL_UNDEF(&methodParam);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&realClasses);
	ZVAL_UNDEF(&boundModel);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&handlerClass);
	ZVAL_UNDEF(&reflectionClass);
	ZVAL_UNDEF(&paramsKeys);
	ZVAL_UNDEF(&paramValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_12$$14);
	ZVAL_UNDEF(&_13$$14);
	ZVAL_UNDEF(&_20$$19);
	ZVAL_UNDEF(&_21$$19);
	ZVAL_UNDEF(&_19$$21);
	ZVAL_UNDEF(&_23$$28);
	ZVAL_UNDEF(&_24$$28);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&paramsCache);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("cache", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT(handler)
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
		Z_PARAM_STR(cacheKey)
		Z_PARAM_STR(methodName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 1);
	params_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_get_arrval(&params, params_param);
	zephir_memory_observe(&cacheKey_zv);
	ZVAL_STR_COPY(&cacheKey_zv, cacheKey);
	zephir_memory_observe(&methodName_zv);
	ZVAL_STR_COPY(&methodName_zv, methodName);
	ZEPHIR_INIT_VAR(&realClasses);
	ZVAL_NULL(&realClasses);
	ZEPHIR_INIT_VAR(&paramsCache);
	array_init(&paramsCache);
	ZEPHIR_INIT_VAR(&reflection);
	if (!ZEPHIR_IS_NULL(&methodName_zv)) {
		object_init_ex(&reflection, zephir_get_internal_ce(SL("reflectionmethod")));
		ZEPHIR_CALL_METHOD(NULL, &reflection, "__construct", NULL, 475, handler, &methodName_zv);
		zephir_check_call_status();
	} else {
		object_init_ex(&reflection, zephir_get_internal_ce(SL("reflectionfunction")));
		ZEPHIR_CALL_METHOD(NULL, &reflection, "__construct", NULL, 154, handler);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 718, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&cache, &_0);
	ZEPHIR_CALL_METHOD(&methodParams, &reflection, "getParameters", NULL, 155);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&paramsKeys);
	zephir_array_keys(&paramsKeys, &params);
	if (Z_TYPE_P(&methodParams) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &methodParams);
		_1 = &_2;
	} else {
		_1 = &methodParams;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Binder.zep", 244);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&paramKey);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&paramKey, _5);
			} else {
				ZVAL_LONG(&paramKey, _4);
			}
			ZEPHIR_INIT_NVAR(&methodParam);
			ZVAL_COPY(&methodParam, _3);
			ZEPHIR_CALL_METHOD(&reflectionClass, &methodParam, "getType", NULL, 0);
			zephir_check_call_status();
			_6$$5 = !zephir_is_true(&reflectionClass);
			if (!(_6$$5)) {
				_6$$5 = !((zephir_is_instance_of(&reflectionClass, SL("ReflectionNamedType"))));
			}
			if (_6$$5) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&className, &reflectionClass, "getName", NULL, 0);
			zephir_check_call_status();
			if (!(zephir_array_isset_value(&params, &paramKey))) {
				ZEPHIR_OBS_NVAR(&_7$$7);
				zephir_array_fetch(&_7$$7, &paramsKeys, &paramKey, PH_NOISY, "phalcon/Mvc/Model/Binder.zep", 196);
				ZEPHIR_CPY_WRT(&paramKey, &_7$$7);
			}
			ZEPHIR_INIT_NVAR(&boundModel);
			ZVAL_NULL(&boundModel);
			ZEPHIR_OBS_NVAR(&paramValue);
			zephir_array_fetch(&paramValue, &params, &paramKey, PH_NOISY, "phalcon/Mvc/Model/Binder.zep", 200);
			if (ZEPHIR_IS_STRING(&className, "Phalcon\\Mvc\\Model")) {
				if (Z_TYPE_P(&realClasses) == IS_NULL) {
					if (zephir_instance_of_ev(handler, phalcon_mvc_controller_bindmodelinterface_ce)) {
						ZEPHIR_INIT_NVAR(&handlerClass);
						zephir_get_class(&handlerClass, handler, 0);
						_11$$10 = zephir_fetch_class(&handlerClass);
						ZEPHIR_CALL_CE_STATIC(&realClasses, _11$$10, "getModelName", NULL, 0);
						zephir_check_call_status();
					} else if (zephir_instance_of_ev(handler, phalcon_mvc_model_binder_bindableinterface_ce)) {
						ZEPHIR_CALL_METHOD(&realClasses, handler, "getModelName", NULL, 0);
						zephir_check_call_status();
					} else {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Handler must implement Phalcon\\Mvc\\Model\\Binder\\BindableInterface in order to use Phalcon\\Mvc\\Model as parameter", "phalcon/Mvc/Model/Binder.zep", 212);
						return;
					}
				}
				if (Z_TYPE_P(&realClasses) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&className);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&className, &realClasses, &paramKey, 0)))) {
						ZEPHIR_INIT_NVAR(&_12$$14);
						object_init_ex(&_12$$14, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_13$$14);
						ZEPHIR_CONCAT_SVS(&_13$$14, "You should provide model class name for ", &paramKey, " parameter");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_12$$14, "__construct", &_14, 32, &_13$$14);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_12$$14, "phalcon/Mvc/Model/Binder.zep", 220);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_15, 0, &paramValue, &className);
					zephir_check_call_status();
				} else if (Z_TYPE_P(&realClasses) == IS_STRING) {
					ZEPHIR_CPY_WRT(&className, &realClasses);
					ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_15, 0, &paramValue, &className);
					zephir_check_call_status();
				} else {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "getModelName should return array or string", "phalcon/Mvc/Model/Binder.zep", 230);
					return;
				}
			} else {
				ZEPHIR_INIT_NVAR(&_8$$5);
				ZVAL_STRING(&_8$$5, "Phalcon\\Mvc\\Model");
				ZEPHIR_CALL_FUNCTION(&_9$$5, "is_subclass_of", &_10, 476, &className, &_8$$5);
				zephir_check_call_status();
				if (zephir_is_true(&_9$$5)) {
					ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_15, 0, &paramValue, &className);
					zephir_check_call_status();
				}
			}
			if (Z_TYPE_P(&boundModel) != IS_NULL) {
				zephir_update_property_array(this_ptr, SL("originalValues"), &paramKey, &paramValue);
				zephir_array_update_zval(&params, &paramKey, &boundModel, PH_COPY | PH_SEPARATE);
				zephir_update_property_array(this_ptr, SL("boundModels"), &paramKey, &boundModel);
				zephir_array_update_zval(&paramsCache, &paramKey, &className, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_17 = 1;
		while (1) {
			if (_17) {
				_17 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_16, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_16)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&paramKey, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&methodParam, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&reflectionClass, &methodParam, "getType", NULL, 0);
				zephir_check_call_status();
				_18$$19 = !zephir_is_true(&reflectionClass);
				if (!(_18$$19)) {
					_18$$19 = !((zephir_is_instance_of(&reflectionClass, SL("ReflectionNamedType"))));
				}
				if (_18$$19) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&className, &reflectionClass, "getName", NULL, 0);
				zephir_check_call_status();
				if (!(zephir_array_isset_value(&params, &paramKey))) {
					ZEPHIR_OBS_NVAR(&_19$$21);
					zephir_array_fetch(&_19$$21, &paramsKeys, &paramKey, PH_NOISY, "phalcon/Mvc/Model/Binder.zep", 196);
					ZEPHIR_CPY_WRT(&paramKey, &_19$$21);
				}
				ZEPHIR_INIT_NVAR(&boundModel);
				ZVAL_NULL(&boundModel);
				ZEPHIR_OBS_NVAR(&paramValue);
				zephir_array_fetch(&paramValue, &params, &paramKey, PH_NOISY, "phalcon/Mvc/Model/Binder.zep", 200);
				if (ZEPHIR_IS_STRING(&className, "Phalcon\\Mvc\\Model")) {
					if (Z_TYPE_P(&realClasses) == IS_NULL) {
						if (zephir_instance_of_ev(handler, phalcon_mvc_controller_bindmodelinterface_ce)) {
							ZEPHIR_INIT_NVAR(&handlerClass);
							zephir_get_class(&handlerClass, handler, 0);
							_22$$24 = zephir_fetch_class(&handlerClass);
							ZEPHIR_CALL_CE_STATIC(&realClasses, _22$$24, "getModelName", NULL, 0);
							zephir_check_call_status();
						} else if (zephir_instance_of_ev(handler, phalcon_mvc_model_binder_bindableinterface_ce)) {
							ZEPHIR_CALL_METHOD(&realClasses, handler, "getModelName", NULL, 0);
							zephir_check_call_status();
						} else {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Handler must implement Phalcon\\Mvc\\Model\\Binder\\BindableInterface in order to use Phalcon\\Mvc\\Model as parameter", "phalcon/Mvc/Model/Binder.zep", 212);
							return;
						}
					}
					if (Z_TYPE_P(&realClasses) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&className);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&className, &realClasses, &paramKey, 0)))) {
							ZEPHIR_INIT_NVAR(&_23$$28);
							object_init_ex(&_23$$28, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_24$$28);
							ZEPHIR_CONCAT_SVS(&_24$$28, "You should provide model class name for ", &paramKey, " parameter");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_23$$28, "__construct", &_14, 32, &_24$$28);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_23$$28, "phalcon/Mvc/Model/Binder.zep", 220);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_15, 0, &paramValue, &className);
						zephir_check_call_status();
					} else if (Z_TYPE_P(&realClasses) == IS_STRING) {
						ZEPHIR_CPY_WRT(&className, &realClasses);
						ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_15, 0, &paramValue, &className);
						zephir_check_call_status();
					} else {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "getModelName should return array or string", "phalcon/Mvc/Model/Binder.zep", 230);
						return;
					}
				} else {
					ZEPHIR_INIT_NVAR(&_20$$19);
					ZVAL_STRING(&_20$$19, "Phalcon\\Mvc\\Model");
					ZEPHIR_CALL_FUNCTION(&_21$$19, "is_subclass_of", &_10, 476, &className, &_20$$19);
					zephir_check_call_status();
					if (zephir_is_true(&_21$$19)) {
						ZEPHIR_CALL_METHOD(&boundModel, this_ptr, "findBoundModel", &_15, 0, &paramValue, &className);
						zephir_check_call_status();
					}
				}
				if (Z_TYPE_P(&boundModel) != IS_NULL) {
					zephir_update_property_array(this_ptr, SL("originalValues"), &paramKey, &paramValue);
					zephir_array_update_zval(&params, &paramKey, &boundModel, PH_COPY | PH_SEPARATE);
					zephir_update_property_array(this_ptr, SL("boundModels"), &paramKey, &boundModel);
					zephir_array_update_zval(&paramsCache, &paramKey, &className, PH_COPY | PH_SEPARATE);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&methodParam);
	ZEPHIR_INIT_NVAR(&paramKey);
	if (Z_TYPE_P(&cache) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, &cache, "set", NULL, 0, &cacheKey_zv, &paramsCache);
		zephir_check_call_status();
	}
	zephir_update_property_array(this_ptr, SL("internalCache"), &cacheKey_zv, &paramsCache);
	RETURN_CTOR(&params);
}

/**
 * Gets cache instance
 */
PHP_METHOD(Phalcon_Mvc_Model_Binder, setCache)
{
	zval *cache, cache_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cache_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("cache", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(cache, phalcon_cache_adapter_adapterinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &cache);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 718, cache);
	RETURN_THISW();
}

zend_object *zephir_init_properties_Phalcon_Mvc_Model_Binder(zend_class_entry *class_type)
{
		zval _0, _2, _4, _1$$3, _3$$4, _5$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("originalValues"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("originalValues"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("internalCache"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("internalCache"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("boundModels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("boundModels"), &_5$$5);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

