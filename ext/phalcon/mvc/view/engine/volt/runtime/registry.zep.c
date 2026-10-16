
#ifdef HAVE_CONFIG_H
#include "../../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../../php_ext.h"
#include "../../../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/operators.h"
#include "kernel/exception.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Runtime functions, filters and tests. The compiler reads names and options;
 * the engine resolves the callables lazily at render time, once per name.
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime, Registry, phalcon, mvc_view_engine_volt_runtime_registry, phalcon_mvc_view_engine_volt_runtime_registry_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_runtime_registry_ce, SL("items"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_runtime_registry_ce, SL("resolved"), ZEND_ACC_PROTECTED);
	phalcon_mvc_view_engine_volt_runtime_registry_ce->create_object = zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Runtime_Registry;

	return SUCCESS;
}

/**
 * Adds a function, filter or test
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, add)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *item, item_sub, kind, name, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item_sub);
	ZVAL_UNDEF(&kind);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(item, phalcon_mvc_view_engine_volt_runtime_voltcallable_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &item);
	ZEPHIR_CALL_METHOD(&kind, this_ptr, "kindOf", NULL, 0, item);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&name, item, "getName", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array_multi(this_ptr, SL("items"), item, SL("zz"), 2, &kind, &name);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_VSV(&_0, &kind, ":", &name);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_unset_property_array(this_ptr, ZEND_STRL("resolved"), &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();
}

/**
 * Adds everything an extension provides
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, addExtension)
{
	zend_bool _6, _12, _18;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *extension, extension_sub, item, _0, *_1, _2, *_3, _5, _7, *_8, _9, *_10, _11, _13, *_14, _15, *_16, _17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extension_sub);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_17);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(extension, phalcon_mvc_view_engine_volt_runtime_extensioninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extension);
	ZEPHIR_CALL_METHOD(&_0, extension, "getFunctions", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 66);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&item);
			ZVAL_COPY(&item, _3);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_4, 0, &item);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_6 = 1;
		while (1) {
			if (_6) {
				_6 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_5, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&item, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_4, 0, &item);
				zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_CALL_METHOD(&_7, extension, "getFilters", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_7) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_9);
		zephir_string_to_char_array(&_9, &_7);
		_8 = &_9;
	} else {
		_8 = &_7;
	}
	zephir_is_iterable(_8, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 70);
	if (Z_TYPE_P(_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_8), _10)
		{
			ZEPHIR_INIT_NVAR(&item);
			ZVAL_COPY(&item, _10);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_4, 0, &item);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _8, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _8, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&item, _8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_4, 0, &item);
				zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_CALL_METHOD(&_13, extension, "getTests", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_13) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_15);
		zephir_string_to_char_array(&_15, &_13);
		_14 = &_15;
	} else {
		_14 = &_13;
	}
	zephir_is_iterable(_14, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 74);
	if (Z_TYPE_P(_14) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_14), _16)
		{
			ZEPHIR_INIT_NVAR(&item);
			ZVAL_COPY(&item, _16);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_4, 0, &item);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _14, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _14, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _14, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&item, _14, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_4, 0, &item);
				zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&item);
	RETURN_THIS();
}

/**
 * The registered item, or null
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, get)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval kind_zv, name_zv, item, _0, _1;
	zend_string *kind = NULL, *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kind_zv);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("items", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(kind)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&kind_zv);
	ZVAL_STR_COPY(&kind_zv, kind);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_memory_observe(&item);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 941, PH_NOISY_CC | PH_READONLY);
	zephir_memory_observe(&_1);
	zephir_array_fetch(&_1, &_0, &kind_zv, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 84);
	if (zephir_array_isset_fetch(&item, &_1, &name_zv, 0)) {
		RETURN_CCTOR(&item);
	}
	RETURN_MM_NULL();
}

/**
 * Everything the compiled output depends on; stored next to each compiled
 * template so a changed registry recompiles it
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, getSignature)
{
	zend_bool _12, _9$$3, _18$$6;
	zval parts;
	zval items, item, _0, *_1, _2, *_3, _11, _20, *_4$$3, _5$$3, *_6$$3, _8$$3, _7$$4, _10$$5, *_13$$6, _14$$6, *_15$$6, _17$$6, _16$$7, _19$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&items);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&parts);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("items", 5, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&parts);
	array_init(&parts);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 941, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 108);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&items);
			ZVAL_COPY(&items, _3);
			if (Z_TYPE_P(&items) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &items);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &items;
			}
			zephir_is_iterable(_4$$3, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 106);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&item);
					ZVAL_COPY(&item, _6$$3);
					ZEPHIR_CALL_METHOD(&_7$$4, &item, "getSignature", NULL, 0);
					zephir_check_call_status();
					zephir_array_append(&parts, &_7$$4, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 104);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_9$$3 = 1;
				while (1) {
					if (_9$$3) {
						_9$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_8$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_8$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&item, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_10$$5, &item, "getSignature", NULL, 0);
						zephir_check_call_status();
						zephir_array_append(&parts, &_10$$5, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 104);
				}
			}
			ZEPHIR_INIT_NVAR(&item);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&items, _1, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&items) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_14$$6);
					zephir_string_to_char_array(&_14$$6, &items);
					_13$$6 = &_14$$6;
				} else {
					_13$$6 = &items;
				}
				zephir_is_iterable(_13$$6, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 106);
				if (Z_TYPE_P(_13$$6) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13$$6), _15$$6)
					{
						ZEPHIR_INIT_NVAR(&item);
						ZVAL_COPY(&item, _15$$6);
						ZEPHIR_CALL_METHOD(&_16$$7, &item, "getSignature", NULL, 0);
						zephir_check_call_status();
						zephir_array_append(&parts, &_16$$7, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 104);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _13$$6, "rewind", NULL, 0);
					zephir_check_call_status();
					_18$$6 = 1;
					while (1) {
						if (_18$$6) {
							_18$$6 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _13$$6, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_17$$6, _13$$6, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_17$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&item, _13$$6, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_19$$8, &item, "getSignature", NULL, 0);
							zephir_check_call_status();
							zephir_array_append(&parts, &_19$$8, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 104);
					}
				}
				ZEPHIR_INIT_NVAR(&item);
		}
	}
	ZEPHIR_INIT_NVAR(&items);
	ZEPHIR_MAKE_REF(&parts);
	ZEPHIR_CALL_FUNCTION(NULL, "sort", NULL, 0, &parts);
	ZEPHIR_UNREF(&parts);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_20);
	zephir_fast_join_str(&_20, SL("\n"), &parts);
	ZEPHIR_RETURN_CALL_FUNCTION("sha1", NULL, 0, &_20);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Whether a name is registered
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, has)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval kind_zv, name_zv, _0, _1;
	zend_string *kind = NULL, *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kind_zv);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("items", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(kind)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&kind_zv);
	ZVAL_STR_COPY(&kind_zv, kind);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 941, PH_NOISY_CC | PH_READONLY);
	zephir_memory_observe(&_1);
	zephir_array_fetch(&_1, &_0, &kind_zv, 0, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 118);
	RETURN_MM_BOOL(zephir_array_isset_value(&_1, &name_zv));
}

/**
 * The handler as a Closure (named arguments keep working). A
 * [Service::class, "method"] pair with a non-static method gets its
 * instance from the container on first use.
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, resolve)
{
	zend_class_entry *_14;
	zend_bool _4, _5, _7;
	zval _0, _3$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval kind_zv, name_zv, *container = NULL, container_sub, __$null, key, item, handler, closure, _1, _6, _8, _2$$4, _9$$5, _10$$5, _11$$5, _12$$6, _13$$6;
	zend_string *kind = NULL, *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kind_zv);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&closure);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("resolved", 8, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(kind)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		container = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&kind_zv);
	ZVAL_STR_COPY(&kind_zv, kind);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	if (!container) {
		container = &container_sub;
		container = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_VSV(&_0, &kind_zv, ":", &name_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&key, &_0);
	zephir_memory_observe(&closure);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 942, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_fetch(&closure, &_1, &key, 0)) {
		RETURN_CCTOR(&closure);
	}
	ZEPHIR_CALL_METHOD(&item, this_ptr, "get", NULL, 0, &kind_zv, &name_zv);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&item) == IS_NULL)) {
		ZEPHIR_INIT_VAR(&_2$$4);
		object_init_ex(&_2$$4, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_3$$4);
		ZEPHIR_CONCAT_SVSVS(&_3$$4, "Unknown runtime ", &kind_zv, " '", &name_zv, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 0, &_3$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$4, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 139);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&handler, &item, "getCallable", NULL, 0);
	zephir_check_call_status();
	_4 = Z_TYPE_P(&handler) == IS_ARRAY;
	if (_4) {
		_4 = zephir_fast_count_int(&handler) == 2;
	}
	_5 = _4;
	if (_5) {
		zephir_memory_observe(&_6);
		zephir_array_fetch_long(&_6, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 144);
		_5 = Z_TYPE_P(&_6) == IS_STRING;
	}
	_7 = _5;
	if (_7) {
		zephir_memory_observe(&_8);
		zephir_array_fetch_long(&_8, &handler, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 144);
		_7 = Z_TYPE_P(&_8) == IS_STRING;
	}
	if (_7) {
		zephir_memory_observe(&_10$$5);
		zephir_array_fetch_long(&_10$$5, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 145);
		zephir_memory_observe(&_11$$5);
		zephir_array_fetch_long(&_11$$5, &handler, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 145);
		ZEPHIR_CALL_METHOD(&_9$$5, this_ptr, "isStatic", NULL, 0, &_10$$5, &_11$$5);
		zephir_check_call_status();
		if (!(zephir_is_true(&_9$$5))) {
			zephir_memory_observe(&_13$$6);
			zephir_array_fetch_long(&_13$$6, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 146);
			ZEPHIR_CALL_METHOD(&_12$$6, this_ptr, "instance", NULL, 0, &_13$$6, container);
			zephir_check_call_status();
			zephir_array_update_long(&handler, 0, &_12$$6, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		}
	}
	_14 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
	ZEPHIR_CALL_CE_STATIC(&closure, _14, "fromCallable", NULL, 0, &handler);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("resolved"), &key, &closure);
	RETURN_CCTOR(&closure);
}

/**
 * An instance for [ServiceOrClass, "method"]: the container service of that
 * name, or the class built through the container, or a plain new
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, instance)
{
	zval _4;
	zend_bool _0, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, *container = NULL, container_sub, __$null, _1, _3;
	zend_string *name = NULL;

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		container = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	if (!container) {
		container = &container_sub;
		container = &__$null;
	}
	_0 = Z_TYPE_P(container) != IS_NULL;
	if (_0) {
		ZEPHIR_CALL_METHOD(&_1, container, "has", NULL, 0, &name_zv);
		zephir_check_call_status();
		_0 = zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_RETURN_CALL_METHOD(container, "getShared", NULL, 0, &name_zv);
		zephir_check_call_status();
		RETURN_MM();
	}
	_2 = Z_TYPE_P(container) != IS_NULL;
	if (_2) {
		_2 = zephir_class_exists(&name_zv, 1);
	}
	if (_2) {
		ZEPHIR_RETURN_CALL_METHOD(container, "get", NULL, 0, &name_zv);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_class_exists(&name_zv, 1)) {
		ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(return_value, &name_zv);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, phalcon_mvc_view_engine_volt_exception_ce);
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_SVS(&_4, "Cannot resolve '", &name_zv, "': not a service in the container and not a class");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 0, &_4);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "phalcon/Mvc/View/Engine/Volt/Runtime/Registry.zep", 177);
	ZEPHIR_MM_RESTORE();
	return;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, isStatic)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval className_zv, method_zv, reflection;
	zend_string *className = NULL, *method = NULL;

	ZVAL_UNDEF(&className_zv);
	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&reflection);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(className)
		Z_PARAM_STR(method)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&className_zv);
	ZVAL_STR_COPY(&className_zv, className);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	_0 = !(zephir_class_exists(&className_zv, 1));
	if (!(_0)) {
		_0 = !((zephir_method_exists(&className_zv, &method_zv)  == SUCCESS));
	}
	if (_0) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(&reflection);
	object_init_ex(&reflection, zephir_get_internal_ce(SL("reflectionmethod")));
	ZEPHIR_CALL_METHOD(NULL, &reflection, "__construct", NULL, 69, &className_zv, &method_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&reflection, "isStatic", NULL, 70);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, kindOf)
{
	zval *item, item_sub;

	ZVAL_UNDEF(&item_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(item, phalcon_mvc_view_engine_volt_runtime_voltcallable_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &item);
	if (zephir_instance_of_ev(item, phalcon_mvc_view_engine_volt_runtime_voltfilter_ce)) {
		RETURN_STRING("filter");
	}
	if (zephir_instance_of_ev(item, phalcon_mvc_view_engine_volt_runtime_volttest_ce)) {
		RETURN_STRING("test");
	}
	RETURN_STRING("function");
}

zend_object *zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Runtime_Registry(zend_class_entry *class_type)
{
		zval _3$$4;
	zval _0, _2, _1$$3, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_3$$4);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("resolved"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("resolved"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("items"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			zephir_create_array(&_3$$4, 3, 0);
			ZEPHIR_INIT_VAR(&_4$$4);
			array_init(&_4$$4);
			zephir_array_update_string(&_3$$4, SL("function"), &_4$$4, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_4$$4);
			array_init(&_4$$4);
			zephir_array_update_string(&_3$$4, SL("filter"), &_4$$4, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_4$$4);
			array_init(&_4$$4);
			zephir_array_update_string(&_3$$4, SL("test"), &_4$$4, PH_COPY | PH_SEPARATE);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("items"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

