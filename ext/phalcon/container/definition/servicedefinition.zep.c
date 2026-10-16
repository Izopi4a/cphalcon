
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
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 *
 * Implementation of this file has been heavily influenced by CapsulePHP.
 * Additionally, there are implementations from ioc-interop, service-interop
 * and resolver-interop. These have been copied and implemented here since
 * PHP extensions cannot have more than one namespace.
 *
 * @link    https://github.com/capsulephp/di
 * @license https://github.com/capsulephp/di/blob/3.x/LICENSE.md
 *
 * @link    https://github.com/ioc-interop/interface
 * @license https://github.com/ioc-interop/interface/blob/1.x/LICENSE.md
 *
 * @link    https://github.com/service-interop/interface
 * @license https://github.com/service-interop/interface/blob/1.x/LICENSE.md
 *
 * @link    https://github.com/resolver-interop/interface/tree/1.x
 * @license https://github.com/resolver-interop/interface/blob/1.x/LICENSE.md
 */
ZEPHIR_INIT_CLASS(Phalcon_Container_Definition_ServiceDefinition)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Container\\Definition, ServiceDefinition, phalcon, container_definition_servicedefinition, phalcon_container_definition_servicedefinition_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("arguments"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("className"), ZEND_ACC_PROTECTED);
	/**
	 * @var object|null
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("container"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("constructorArgs"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("extenders"), ZEND_ACC_PROTECTED);
	/**
	 * @var callable|null
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("factory"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_container_definition_servicedefinition_ce, SL("frozen"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_container_definition_servicedefinition_ce, SL("isCacheable"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("lifetime"), ZEND_ACC_PROTECTED);
	/**
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("raw"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("serviceName"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("tags"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_container_definition_servicedefinition_ce, SL("type"), ZEND_ACC_PROTECTED);
	phalcon_container_definition_servicedefinition_ce->create_object = zephir_init_properties_Phalcon_Container_Definition_ServiceDefinition;

	return SUCCESS;
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval serviceName_zv, type_zv, *raw = NULL, raw_sub, __$null, _0;
	zend_string *serviceName = NULL, *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&serviceName_zv);
	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&raw_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("serviceName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("raw", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("lifetime", 8, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(serviceName)
		Z_PARAM_STR(type)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(raw)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		raw = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&serviceName_zv);
	ZVAL_STR_COPY(&serviceName_zv, serviceName);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	if (!raw) {
		raw = &raw_sub;
		raw = &__$null;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 350, &serviceName_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 351, &type_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 352, raw);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "SCOPED");
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 353, &_0);
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, addExtender)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *extender, extender_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extender_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(extender)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extender);
	if (UNEXPECTED(!(zephir_is_callable(extender)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'extender' must be callable", "phalcon/Container/Definition/ServiceDefinition.zep", 101);
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array_append(this_ptr, SL("extenders"), extender);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, addTag)
{
	zend_bool _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tag_zv, __$true, _0, _1, _2, _4, _5$$4, _6$$4;
	zend_string *tag = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tag_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("tags", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("serviceName", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(tag)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tag_zv);
	ZVAL_STR_COPY(&tag_zv, tag);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 354, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_1, "in_array", NULL, 209, &tag_zv, &_0, &__$true);
	zephir_check_call_status();
	if (!(zephir_is_true(&_1))) {
		zephir_update_property_array_append(this_ptr, SL("tags"), &tag_zv);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 355, PH_NOISY_CC | PH_READONLY);
	_3 = Z_TYPE_P(&_2) != IS_NULL;
	if (_3) {
		zephir_read_property_cached(&_4, this_ptr, _zephir_prop_1, 355, PH_NOISY_CC | PH_READONLY);
		_3 = (zephir_method_exists_ex(&_4, ZEND_STRL("settag")) == SUCCESS);
	}
	if (_3) {
		zephir_read_property_cached(&_5$$4, this_ptr, _zephir_prop_1, 355, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_6$$4, this_ptr, _zephir_prop_2, 350, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "setTag", NULL, 0, &tag_zv, &_6$$4);
		zephir_check_call_status();
	}
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, buildService)
{
	zend_bool _10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, args, classValue, extender, factory, instance, reflection, _0, _4, *_5, _6, *_7, _9, _1$$3, _2$$4, _3$$4, _8$$5, _11$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&args);
	ZVAL_UNDEF(&classValue);
	ZVAL_UNDEF(&extender);
	ZVAL_UNDEF(&factory);
	ZVAL_UNDEF(&instance);
	ZVAL_UNDEF(&reflection);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_11$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("factory", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("className", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("serviceName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("constructorArgs", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("extenders", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT(container)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &container);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "hasFactory", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 356, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&factory, &_1$$3);
		ZEPHIR_CALL_ZVAL_FUNCTION(&instance, &factory, NULL, 0, container);
		zephir_check_call_status();
	} else {
		zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_1, 357, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2$$4) != IS_NULL) {
			zephir_memory_observe(&classValue);
			zephir_read_property_cached(&classValue, this_ptr, _zephir_prop_1, 357, PH_NOISY_CC);
		} else {
			ZEPHIR_OBS_NVAR(&classValue);
			zephir_read_property_cached(&classValue, this_ptr, _zephir_prop_2, 350, PH_NOISY_CC);
		}
		zephir_read_property_cached(&_3$$4, this_ptr, _zephir_prop_3, 358, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&args, this_ptr, "resolveArgs", NULL, 214, container, &_3$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&reflection);
		object_init_ex(&reflection, zephir_get_internal_ce(SL("reflectionclass")));
		ZEPHIR_CALL_METHOD(NULL, &reflection, "__construct", NULL, 157, &classValue);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&instance, &reflection, "newInstanceArgs", NULL, 215, &args);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_4, 359, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_4) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_6);
		zephir_string_to_char_array(&_6, &_4);
		_5 = &_6;
	} else {
		_5 = &_4;
	}
	zephir_is_iterable(_5, 0, "phalcon/Container/Definition/ServiceDefinition.zep", 143);
	if (Z_TYPE_P(_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5), _7)
		{
			ZEPHIR_INIT_NVAR(&extender);
			ZVAL_COPY(&extender, _7);
			ZEPHIR_CALL_ZVAL_FUNCTION(&_8$$5, &extender, NULL, 0, &instance, container);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&instance, &_8$$5);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _5, "rewind", NULL, 0);
		zephir_check_call_status();
		_10 = 1;
		while (1) {
			if (_10) {
				_10 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _5, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_9, _5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&extender, _5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_ZVAL_FUNCTION(&_11$$6, &extender, NULL, 0, &instance, container);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&instance, &_11$$6);
		}
	}
	ZEPHIR_INIT_NVAR(&extender);
	RETURN_CCTOR(&instance);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, freeze)
{
	zend_bool _2, _3, _6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, __$true, __$false, classValue, reflection, constructor, params, _0, _1, _4, _5, _7, _8$$4, _9$$5, _10$$5, _11$$5, _12$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&classValue);
	ZVAL_UNDEF(&reflection);
	ZVAL_UNDEF(&constructor);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("frozen", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("arguments", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("className", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("serviceName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("constructorArgs", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT(container)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &container);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 360, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 351, PH_NOISY_CC | PH_READONLY);
	_2 = ZEPHIR_IS_STRING_IDENTICAL(&_1, "string");
	if (_2) {
		_2 = (zephir_method_exists_ex(container, ZEND_STRL("isautowireenabled")) == SUCCESS);
	}
	_3 = _2;
	if (_3) {
		ZEPHIR_CALL_METHOD(&_4, container, "isAutowireEnabled", NULL, 0);
		zephir_check_call_status();
		_3 = zephir_is_true(&_4);
	}
	if (_3) {
		zephir_read_property_cached(&_8$$4, this_ptr, _zephir_prop_3, 357, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8$$4) != IS_NULL) {
			zephir_memory_observe(&classValue);
			zephir_read_property_cached(&classValue, this_ptr, _zephir_prop_3, 357, PH_NOISY_CC);
		} else {
			ZEPHIR_OBS_NVAR(&classValue);
			zephir_read_property_cached(&classValue, this_ptr, _zephir_prop_4, 350, PH_NOISY_CC);
		}
		ZEPHIR_INIT_VAR(&reflection);
		object_init_ex(&reflection, zephir_get_internal_ce(SL("reflectionclass")));
		ZEPHIR_CALL_METHOD(NULL, &reflection, "__construct", NULL, 157, &classValue);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&constructor, &reflection, "getConstructor", NULL, 216);
		zephir_check_call_status();
		if (Z_TYPE_P(&constructor) != IS_NULL) {
			ZEPHIR_CALL_METHOD(&params, &constructor, "getParameters", NULL, 0);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&params);
			array_init(&params);
		}
		if ((zephir_method_exists_ex(container, ZEND_STRL("getresolver")) == SUCCESS)) {
			ZEPHIR_CALL_METHOD(&_9$$5, container, "getResolver", NULL, 0);
			zephir_check_call_status();
			zephir_read_property_cached(&_11$$5, this_ptr, _zephir_prop_2, 361, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_10$$5, &_9$$5, "resolveParameters", NULL, 0, container, &params, &_11$$5);
			zephir_check_call_status();
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 358, &_10$$5);
		}
	} else {
		zephir_read_property_cached(&_5, this_ptr, _zephir_prop_1, 351, PH_NOISY_CC | PH_READONLY);
		_6 = ZEPHIR_IS_STRING_IDENTICAL(&_5, "string");
		if (_6) {
			zephir_memory_observe(&_7);
			zephir_read_property_cached(&_7, this_ptr, _zephir_prop_2, 361, PH_NOISY_CC);
			_6 = !(ZEPHIR_IS_EMPTY(&_7));
		}
		if (_6) {
			zephir_read_property_cached(&_12$$6, this_ptr, _zephir_prop_2, 361, PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 358, &_12$$6);
		}
	}
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 360, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 360, &__$false);
	}
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getArguments)
{

	RETURN_MEMBER_TYPED(getThis(), "arguments", IS_ARRAY);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getClass)
{
	zval _0, _1$$3, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("className", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("serviceName", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 357, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 350, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, phalcon_container_exception_invalid_ce, "noClassSet", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Container/Definition/ServiceDefinition.zep", 185);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_MEMBER_TYPED(getThis(), "className", IS_STRING);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getConstructorArgs)
{

	RETURN_MEMBER_TYPED(getThis(), "constructorArgs", IS_ARRAY);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getExtenders)
{

	RETURN_MEMBER_TYPED(getThis(), "extenders", IS_ARRAY);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getFactory)
{
	zval _0, _1$$3, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("factory", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("serviceName", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 356, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 350, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, phalcon_container_exception_invalid_ce, "noFactorySet", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Container/Definition/ServiceDefinition.zep", 204);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_MEMBER(getThis(), "factory");
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getLifetime)
{

	RETURN_MEMBER_TYPED(getThis(), "lifetime", IS_STRING);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getServiceName)
{

	RETURN_MEMBER_TYPED(getThis(), "serviceName", IS_STRING);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getTags)
{

	RETURN_MEMBER_TYPED(getThis(), "tags", IS_ARRAY);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, getType)
{

	RETURN_MEMBER_TYPED(getThis(), "type", IS_STRING);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, hasClass)
{
	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("className", 9, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 357, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(Z_TYPE_P(&_0) != IS_NULL);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, hasExtenders)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extenders", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 359, PH_NOISY_CC);
	RETURN_MM_BOOL(!(ZEPHIR_IS_EMPTY(&_0)));
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, hasFactory)
{
	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("factory", 7, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 356, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(Z_TYPE_P(&_0) != IS_NULL);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, isCacheable)
{
	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("isCacheable", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("frozen", 6, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 362, PH_NOISY_CC | PH_READONLY);
	_1 = zephir_is_true(&_0);
	if (_1) {
		zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 360, PH_NOISY_CC | PH_READONLY);
		_1 = zephir_is_true(&_2);
	}
	RETURN_BOOL(_1);
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, isFrozen)
{

	RETURN_MEMBER(getThis(), "frozen");
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setArgument)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *param, param_sub, *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(param)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &param, &value);
	_0 = Z_TYPE_P(param) != IS_LONG;
	if (_0) {
		_0 = Z_TYPE_P(param) != IS_STRING;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'param' must be int or string", "phalcon/Container/Definition/ServiceDefinition.zep", 258);
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("arguments"), param, value);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setClass)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval classValue_zv;
	zend_string *classValue = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&classValue_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("className", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(classValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&classValue_zv);
	ZVAL_STR_COPY(&classValue_zv, classValue);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 357, &classValue_zv);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setContainer)
{
	zend_bool _0;
	zval *container, container_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(container)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &container);
	_0 = Z_TYPE_P(container) != IS_OBJECT;
	if (_0) {
		_0 = Z_TYPE_P(container) != IS_NULL;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(zend_ce_type_error, "Argument 'container' must be object or null", "phalcon/Container/Definition/ServiceDefinition.zep", 278);
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 355, container);
	RETURN_THISW();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setExtenders)
{
	zend_bool _7;
	zend_string *_2;
	zend_ulong _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *extenders_param = NULL, key, extender, *_0, _6, _3$$4, _5$$4, _8$$6, _9$$6;
	zval extenders;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extenders);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&extender);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("serviceName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("extenders", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(extenders, extenders_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extenders_param);
	zephir_get_arrval(&extenders, extenders_param);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&extenders, 0, "phalcon/Container/Definition/ServiceDefinition.zep", 298);
	if (Z_TYPE_P(&extenders) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&extenders), _1, _2, _0)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_2 != NULL) { 
				ZVAL_STR_COPY(&key, _2);
			} else {
				ZVAL_LONG(&key, _1);
			}
			ZEPHIR_INIT_NVAR(&extender);
			ZVAL_COPY(&extender, _0);
			if (!(zephir_is_callable(&extender))) {
				zephir_read_property_cached(&_5$$4, this_ptr, _zephir_prop_0, 350, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_CE_STATIC(&_3$$4, phalcon_container_exception_invalid_ce, "invalidExtender", &_4, 0, &_5$$4, &key);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_3$$4, "phalcon/Container/Definition/ServiceDefinition.zep", 294);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &extenders, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &extenders, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, &extenders, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &extenders, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&extender, &extenders, "current", NULL, 0);
			zephir_check_call_status();
				if (!(zephir_is_callable(&extender))) {
					zephir_read_property_cached(&_9$$6, this_ptr, _zephir_prop_0, 350, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CALL_CE_STATIC(&_8$$6, phalcon_container_exception_invalid_ce, "invalidExtender", &_4, 0, &_9$$6, &key);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_8$$6, "phalcon/Container/Definition/ServiceDefinition.zep", 294);
					ZEPHIR_MM_RESTORE();
					return;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&extender);
	ZEPHIR_INIT_NVAR(&key);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 359, &extenders);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setFactory)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *factory, factory_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&factory_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("factory", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(factory)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &factory);
	if (UNEXPECTED(!(zephir_is_callable(factory)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'factory' must be callable", "phalcon/Container/Definition/ServiceDefinition.zep", 306);
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 356, factory);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setIsCacheable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *isCacheable_param = NULL, __$true, __$false;
	zend_bool isCacheable;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("isCacheable", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(isCacheable)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &isCacheable_param);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	if (isCacheable) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 362, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 362, &__$false);
	}
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, setLifetime)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval lifetime_zv;
	zend_string *lifetime = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&lifetime_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("lifetime", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(lifetime)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&lifetime_zv);
	ZVAL_STR_COPY(&lifetime_zv, lifetime);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 353, &lifetime_zv);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, unsetClass)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("className", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 357, &__$null);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, unsetExtenders)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extenders", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 359, &_0);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, unsetFactory)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("factory", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkFrozen", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 356, &__$null);
	RETURN_THIS();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, checkFrozen)
{
	zval _0, _1$$3, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("frozen", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("serviceName", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 360, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 350, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_1$$3, phalcon_container_exception_invalid_ce, "frozenDefinition", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Container/Definition/ServiceDefinition.zep", 358);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Container_Definition_ServiceDefinition, resolveArgs)
{
	zend_bool _6, _3$$3, _7$$6;
	zend_string *_2;
	zend_ulong _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval args;
	zval *container, container_sub, *args_param = NULL, key, arg, resolved, *_0, _5, _4$$4, _8$$7;

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&arg);
	ZVAL_UNDEF(&resolved);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&args);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT(container)
		ZEPHIR_Z_PARAM_ARRAY(args, args_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &container, &args_param);
	zephir_get_arrval(&args, args_param);
	ZEPHIR_INIT_VAR(&resolved);
	array_init(&resolved);
	zephir_is_iterable(&args, 0, "phalcon/Container/Definition/ServiceDefinition.zep", 376);
	if (Z_TYPE_P(&args) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&args), _1, _2, _0)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_2 != NULL) { 
				ZVAL_STR_COPY(&key, _2);
			} else {
				ZVAL_LONG(&key, _1);
			}
			ZEPHIR_INIT_NVAR(&arg);
			ZVAL_COPY(&arg, _0);
			_3$$3 = Z_TYPE_P(&arg) == IS_OBJECT;
			if (_3$$3) {
				_3$$3 = (zephir_method_exists_ex(&arg, ZEND_STRL("resolve")) == SUCCESS);
			}
			if (_3$$3) {
				ZEPHIR_CALL_METHOD(&_4$$4, &arg, "resolve", NULL, 0, container);
				zephir_check_call_status();
				zephir_array_update_zval(&resolved, &key, &_4$$4, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&resolved, &key, &arg, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &args, "rewind", NULL, 0);
		zephir_check_call_status();
		_6 = 1;
		while (1) {
			if (_6) {
				_6 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &args, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_5, &args, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &args, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&arg, &args, "current", NULL, 0);
			zephir_check_call_status();
				_7$$6 = Z_TYPE_P(&arg) == IS_OBJECT;
				if (_7$$6) {
					_7$$6 = (zephir_method_exists_ex(&arg, ZEND_STRL("resolve")) == SUCCESS);
				}
				if (_7$$6) {
					ZEPHIR_CALL_METHOD(&_8$$7, &arg, "resolve", NULL, 0, container);
					zephir_check_call_status();
					zephir_array_update_zval(&resolved, &key, &_8$$7, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&resolved, &key, &arg, PH_COPY | PH_SEPARATE);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&arg);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CCTOR(&resolved);
}

zend_object *zephir_init_properties_Phalcon_Container_Definition_ServiceDefinition(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _1$$3, _3$$4, _5$$5, _7$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("tags"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("tags"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("extenders"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("extenders"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("constructorArgs"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("constructorArgs"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("arguments"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("arguments"), &_7$$6);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

