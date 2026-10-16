
#ifdef HAVE_CONFIG_H
#include "../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../php_ext.h"
#include "../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/main.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/string.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Class Select
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_Input_Select)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper\\Input, Select, phalcon, html_helper_input_select, phalcon_html_helper_abstractlist_ce, phalcon_html_helper_input_select_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_html_helper_input_select_ce, SL("elementTag"), "option", ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_html_helper_input_select_ce, SL("inOptGroup"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_html_helper_input_select_ce, SL("selected"), "", ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Add an element to the list
 *
 * @param string      $text
 * @param string|null $value
 * @param array       $attributes
 * @param bool        $raw
 *
 * @return Select
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, add)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool raw;
	zval attributes, _1, _3;
	zval text_zv, value_zv, *attributes_param = NULL, *raw_param = NULL, _0, _2, _4, _5;
	zend_string *text = NULL, *value = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&value_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("elementTag", 10, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(text)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(value)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_BOOL(raw)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		attributes_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		raw_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&text_zv);
	ZVAL_STR_COPY(&text_zv, text);
	if (!value) {
		ZEPHIR_INIT_VAR(&value_zv);
	} else {
		zephir_memory_observe(&value_zv);
	ZVAL_STR_COPY(&value_zv, value);
	}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	if (!raw_param) {
		raw = 0;
	} else {
		}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "processValue", NULL, 365, &attributes, &value_zv);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&_0) != IS_ARRAY)) {
		zephir_throw_variable_type_error(&_0, "attributes", "array");
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&attributes, &_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 3, 0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "renderFullElement");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 4, 0);
	zephir_memory_observe(&_4);
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_0, 566, PH_NOISY_CC);
	zephir_array_fast_append(&_3, &_4);
	zephir_array_fast_append(&_3, &text_zv);
	zephir_array_fast_append(&_3, &attributes);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_BOOL(&_2, raw);
	zephir_array_fast_append(&_3, &_2);
	zephir_array_fast_append(&_1, &_3);
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "indent", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(&_1, &_5);
	zephir_update_property_array_append(this_ptr, SL("store"), &_1);
	RETURN_THIS();
}

/**
 * Add a placeholder to the element
 *
 * @param string $text
 * @param string $value
 * @param array  $attributes
 * @param bool   $raw
 *
 * @return Select
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, addPlaceholder)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool raw;
	zval attributes, _1, _3;
	zval text_zv, *value = NULL, value_sub, *attributes_param = NULL, *raw_param = NULL, __$null, _2, _4, _5;
	zend_string *text = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&value_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("elementTag", 10, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(text)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(value)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_BOOL(raw)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		value = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		attributes_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		raw_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&text_zv);
	ZVAL_STR_COPY(&text_zv, text);
	if (!value) {
		value = &value_sub;
		value = &__$null;
	}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	if (!raw_param) {
		raw = 0;
	} else {
		}
	if (Z_TYPE_P(value) != IS_NULL) {
		zephir_cast_to_string(&_0$$3, value);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_update_string(&attributes, SL("value"), &_0$$3, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 3, 0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "renderFullElement");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 4, 0);
	zephir_memory_observe(&_4);
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_0, 566, PH_NOISY_CC);
	zephir_array_fast_append(&_3, &_4);
	zephir_array_fast_append(&_3, &text_zv);
	zephir_array_fast_append(&_3, &attributes);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_BOOL(&_2, raw);
	zephir_array_fast_append(&_3, &_2);
	zephir_array_fast_append(&_1, &_3);
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "indent", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(&_1, &_5);
	zephir_update_property_array_append(this_ptr, SL("store"), &_1);
	RETURN_THIS();
}

/**
 * Populates the select from a data provider.
 *
 * Flat entries: key = option value, value = label string.
 * Optgroup entries: key = group label, value = [value => label] array.
 *
 * @param SelectDataInterface data
 *
 * @return Select
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, fromData)
{
	zval _6$$4, _20$$4, _13$$5, _14$$5, _18$$6, _19$$6, _21$$7, _22$$7, _25$$9, _37$$9, _31$$10, _32$$10, _35$$11, _36$$11, _38$$12, _39$$12;
	zend_bool _24, _17$$4, _34$$9;
	zend_string *_5, *_12$$4, *_30$$9;
	zend_ulong _4, _11$$4, _29$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data, data_sub, key, subKey, subValue, value, _0, *_1, _2, *_3, _23, *_8$$4, _9$$4, *_10$$4, _16$$4, *_26$$9, _27$$9, *_28$$9, _33$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&subKey);
	ZVAL_UNDEF(&subValue);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_33$$9);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_37$$9);
	ZVAL_UNDEF(&_31$$10);
	ZVAL_UNDEF(&_32$$10);
	ZVAL_UNDEF(&_35$$11);
	ZVAL_UNDEF(&_36$$11);
	ZVAL_UNDEF(&_38$$12);
	ZVAL_UNDEF(&_39$$12);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(data, phalcon_html_helper_input_select_selectdatainterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data);
	ZEPHIR_CALL_METHOD(&_0, data, "getOptions", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Html/Helper/Input/Select.zep", 130);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&key, _5);
			} else {
				ZVAL_LONG(&key, _4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			if (Z_TYPE_P(&value) == IS_ARRAY) {
				zephir_cast_to_string(&_6$$4, &key);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "optGroup", &_7, 0, &_6$$4);
				zephir_check_call_status();
				if (Z_TYPE_P(&value) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_9$$4);
					zephir_string_to_char_array(&_9$$4, &value);
					_8$$4 = &_9$$4;
				} else {
					_8$$4 = &value;
				}
				zephir_is_iterable(_8$$4, 0, "phalcon/Html/Helper/Input/Select.zep", 124);
				if (Z_TYPE_P(_8$$4) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_8$$4), _11$$4, _12$$4, _10$$4)
					{
						ZEPHIR_INIT_NVAR(&subKey);
						if (_12$$4 != NULL) { 
							ZVAL_STR_COPY(&subKey, _12$$4);
						} else {
							ZVAL_LONG(&subKey, _11$$4);
						}
						ZEPHIR_INIT_NVAR(&subValue);
						ZVAL_COPY(&subValue, _10$$4);
						zephir_cast_to_string(&_13$$5, &subValue);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_cast_to_string(&_14$$5, &subKey);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_15, 0, &_13$$5, &_14$$5);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _8$$4, "rewind", NULL, 0);
					zephir_check_call_status();
					_17$$4 = 1;
					while (1) {
						if (_17$$4) {
							_17$$4 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _8$$4, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_16$$4, _8$$4, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_16$$4)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&subKey, _8$$4, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&subValue, _8$$4, "current", NULL, 0);
						zephir_check_call_status();
							zephir_cast_to_string(&_18$$6, &subValue);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_cast_to_string(&_19$$6, &subKey);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_15, 0, &_18$$6, &_19$$6);
							zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&subValue);
				ZEPHIR_INIT_NVAR(&subKey);
				zephir_cast_to_string(&_20$$4, &key);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "optGroup", &_7, 0, &_20$$4);
				zephir_check_call_status();
			} else {
				zephir_cast_to_string(&_21$$7, &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_cast_to_string(&_22$$7, &key);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_15, 0, &_21$$7, &_22$$7);
				zephir_check_call_status();
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_24 = 1;
		while (1) {
			if (_24) {
				_24 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_23, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_23)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _1, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&value) == IS_ARRAY) {
					zephir_cast_to_string(&_25$$9, &key);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "optGroup", &_7, 0, &_25$$9);
					zephir_check_call_status();
					if (Z_TYPE_P(&value) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_27$$9);
						zephir_string_to_char_array(&_27$$9, &value);
						_26$$9 = &_27$$9;
					} else {
						_26$$9 = &value;
					}
					zephir_is_iterable(_26$$9, 0, "phalcon/Html/Helper/Input/Select.zep", 124);
					if (Z_TYPE_P(_26$$9) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_26$$9), _29$$9, _30$$9, _28$$9)
						{
							ZEPHIR_INIT_NVAR(&subKey);
							if (_30$$9 != NULL) { 
								ZVAL_STR_COPY(&subKey, _30$$9);
							} else {
								ZVAL_LONG(&subKey, _29$$9);
							}
							ZEPHIR_INIT_NVAR(&subValue);
							ZVAL_COPY(&subValue, _28$$9);
							zephir_cast_to_string(&_31$$10, &subValue);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_cast_to_string(&_32$$10, &subKey);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_15, 0, &_31$$10, &_32$$10);
							zephir_check_call_status();
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _26$$9, "rewind", NULL, 0);
						zephir_check_call_status();
						_34$$9 = 1;
						while (1) {
							if (_34$$9) {
								_34$$9 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _26$$9, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_33$$9, _26$$9, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_33$$9)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&subKey, _26$$9, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&subValue, _26$$9, "current", NULL, 0);
							zephir_check_call_status();
								zephir_cast_to_string(&_35$$11, &subValue);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_cast_to_string(&_36$$11, &subKey);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_15, 0, &_35$$11, &_36$$11);
								zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&subValue);
					ZEPHIR_INIT_NVAR(&subKey);
					zephir_cast_to_string(&_37$$9, &key);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "optGroup", &_7, 0, &_37$$9);
					zephir_check_call_status();
				} else {
					zephir_cast_to_string(&_38$$12, &value);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_cast_to_string(&_39$$12, &key);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_15, 0, &_38$$12, &_39$$12);
					zephir_check_call_status();
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_THIS();
}

/**
 * Creates an option group
 *
 * @param string $label
 * @param array  $attributes
 *
 * @return Select
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, optGroup)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes, _1$$3, _3$$3, _11$$4;
	zval label_zv, *attributes_param = NULL, __$true, __$false, _0, _14, _2$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$4, _9$$4, _10$$4, _12$$4, _13$$4;
	zend_string *label = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&label_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_11$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("inOptGroup", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("indentLevel", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(label)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		attributes_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (!label) {
		ZEPHIR_INIT_VAR(&label_zv);
	} else {
		zephir_memory_observe(&label_zv);
	ZVAL_STR_COPY(&label_zv, label);
	}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 567, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 3, 0);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "optGroupStart");
		zephir_array_fast_append(&_1$$3, &_2$$3);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_create_array(&_3$$3, 2, 0);
		zephir_array_fast_append(&_3$$3, &label_zv);
		zephir_array_fast_append(&_3$$3, &attributes);
		zephir_array_fast_append(&_1$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "indent", NULL, 0);
		zephir_check_call_status();
		zephir_array_fast_append(&_1$$3, &_4$$3);
		zephir_update_property_array_append(this_ptr, SL("store"), &_1$$3);
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_1, 568, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_LONG(&_6$$3, 1);
		ZEPHIR_INIT_VAR(&_7$$3);
		zephir_add_function(&_7$$3, &_5$$3, &_6$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 568, &_7$$3);
	} else {
		zephir_read_property_cached(&_8$$4, this_ptr, _zephir_prop_1, 568, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_9$$4);
		ZVAL_LONG(&_9$$4, 1);
		ZEPHIR_INIT_VAR(&_10$$4);
		zephir_sub_function(&_10$$4, &_8$$4, &_9$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 568, &_10$$4);
		ZEPHIR_INIT_VAR(&_11$$4);
		zephir_create_array(&_11$$4, 3, 0);
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "optGroupEnd");
		zephir_array_fast_append(&_11$$4, &_12$$4);
		ZEPHIR_INIT_NVAR(&_12$$4);
		array_init(&_12$$4);
		zephir_array_fast_append(&_11$$4, &_12$$4);
		ZEPHIR_CALL_METHOD(&_13$$4, this_ptr, "indent", NULL, 0);
		zephir_check_call_status();
		zephir_array_fast_append(&_11$$4, &_13$$4);
		zephir_update_property_array_append(this_ptr, SL("store"), &_11$$4);
	}
	zephir_memory_observe(&_14);
	zephir_read_property_cached(&_14, this_ptr, _zephir_prop_0, 567, PH_NOISY_CC);
	if (!zephir_is_true(&_14)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 567, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 567, &__$false);
	}
	RETURN_THIS();
}

/**
 * @param string $selected
 *
 * @return Select
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, selected)
{
	zval selected_zv;
	zend_string *selected = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&selected_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("selected", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(selected)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&selected_zv, selected);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 569, &selected_zv);
	RETURN_THISW();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, getTag)
{

	RETURN_STRING("select");
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, optGroupEnd)
{

	RETURN_STRING("</optgroup>");
}

/**
 * @param string $label
 * @param array  $attributes
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, optGroupStart)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes;
	zval label_zv, *attributes_param = NULL, _0;
	zend_string *label = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&label_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(label)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	attributes_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&label_zv);
	ZVAL_STR_COPY(&label_zv, label);
	zephir_get_arrval(&attributes, attributes_param);
	zephir_array_update_string(&attributes, SL("label"), &label_zv, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "optgroup");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "renderTag", NULL, 0, &_0, &attributes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Checks if the value has been passed and if it is the same as the
 * value stored in the object
 *
 * @param array  $attributes
 * @param string $value
 *
 * @return array
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Select, processValue)
{
	zend_bool _0, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *attributes_param = NULL, *value = NULL, value_sub, __$null, _1$$3, _3$$3, _4$$4;
	zval attributes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&value_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("selected", 8, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &attributes_param, &value);
	zephir_get_arrval(&attributes, attributes_param);
	if (!value) {
		value = &value_sub;
		value = &__$null;
	}
	_0 = zephir_is_numeric(value);
	if (!(_0)) {
		_0 = !(ZEPHIR_IS_EMPTY(value));
	}
	if (_0) {
		zephir_array_update_string(&attributes, SL("value"), value, PH_COPY | PH_SEPARATE);
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 569, PH_NOISY_CC | PH_READONLY);
		_2$$3 = !(ZEPHIR_IS_EMPTY(&_1$$3));
		if (_2$$3) {
			zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 569, PH_NOISY_CC | PH_READONLY);
			_2$$3 = ZEPHIR_IS_IDENTICAL(value, &_3$$3);
		}
		if (_2$$3) {
			ZEPHIR_INIT_VAR(&_4$$4);
			ZVAL_STRING(&_4$$4, "selected");
			zephir_array_update_string(&attributes, SL("selected"), &_4$$4, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CTOR(&attributes);
}

