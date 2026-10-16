
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/filter.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Html\Escaper
 *
 * Escapes different kinds of text securing them. By using this component you
 * may prevent XSS attacks.
 *
 * This component only works with UTF-8. The PREG extension needs to be compiled
 * with UTF-8 support.
 *
 *```php
 * $escaper = new \Phalcon\Html\Escaper();
 *
 * $escaped = $escaper->escapeCss("font-family: <Verdana>");
 *
 * echo $escaped; // font\2D family\3A \20 \3C Verdana\3E
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Escaper)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Html, Escaper, phalcon, html_escaper, phalcon_html_escaper_method_entry, 0);

	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_html_escaper_ce, SL("doubleEncode"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_html_escaper_ce, SL("encoding"), "utf-8", ZEND_ACC_PROTECTED);
	/**
	 * ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML401
	 *
	 * @var int
	 */
	zend_declare_property_long(phalcon_html_escaper_ce, SL("flags"), 11, ZEND_ACC_PROTECTED);
	zend_class_implements(phalcon_html_escaper_ce, 1, phalcon_html_escaper_escaperinterface_ce);
	return SUCCESS;
}

/**
 * Escapes a HTML attribute string or array
 *
 * If the input is an array, the keys are the attribute names and the
 * values are attribute values. If a value is boolean (true/false) then
 * the attribute will have no value:
 * `['disabled' => true]` -> `'disabled``
 *
 * The resulting string will have attribute pairs separated by a space.
 *
 * @param array|string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, attributes)
{
	zval _0$$3, _10$$4, _12$$7, _20$$8, _22$$11;
	zend_bool _15, _6$$4, _16$$8;
	zend_string *_5;
	zend_ulong _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input, input_sub, key, result, value, *_1, _2, *_3, _14, _7$$4, _9$$4, _8$$6, _11$$7, _13$$7, _17$$8, _19$$8, _18$$10, _21$$11, _23$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_sub);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_21$$11);
	ZVAL_UNDEF(&_23$$11);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_22$$11);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &input);
	if (EXPECTED((Z_TYPE_P(input) != IS_ARRAY))) {
		zephir_cast_to_string(&_0$$3, input);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "phpHtmlSpecialChars", NULL, 0, &_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	if (Z_TYPE_P(input) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, input);
		_1 = &_2;
	} else {
		_1 = input;
	}
	zephir_is_iterable(_1, 0, "phalcon/Html/Escaper.zep", 96);
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
			_6$$4 = Z_TYPE_P(&value) == IS_NULL;
			if (!(_6$$4)) {
				_6$$4 = ZEPHIR_IS_FALSE_IDENTICAL(&value);
			}
			if (_6$$4) {
				continue;
			}
			ZEPHIR_INIT_NVAR(&_7$$4);
			zephir_fast_trim(&_7$$4, &key, NULL , ZEPHIR_TRIM_BOTH);
			ZEPHIR_CPY_WRT(&key, &_7$$4);
			if (Z_TYPE_P(&value) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(&_8$$6);
				zephir_fast_join_str(&_8$$6, SL(" "), &value);
				ZEPHIR_CPY_WRT(&value, &_8$$6);
			}
			zephir_cast_to_string(&_10$$4, &key);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_9$$4, this_ptr, "phpHtmlSpecialChars", NULL, 0, &_10$$4);
			zephir_check_call_status();
			zephir_concat_self(&result, &_9$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (!ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
				zephir_cast_to_string(&_12$$7, &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_11$$7, this_ptr, "phpHtmlSpecialChars", NULL, 0, &_12$$7);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_13$$7);
				ZEPHIR_CONCAT_SVS(&_13$$7, "=\"", &_11$$7, "\"");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&result, &_13$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			zephir_concat_self_str(&result, SL(" "));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_15 = 1;
		while (1) {
			if (_15) {
				_15 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_14, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_14)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _1, "current", NULL, 0);
			zephir_check_call_status();
				_16$$8 = Z_TYPE_P(&value) == IS_NULL;
				if (!(_16$$8)) {
					_16$$8 = ZEPHIR_IS_FALSE_IDENTICAL(&value);
				}
				if (_16$$8) {
					continue;
				}
				ZEPHIR_INIT_NVAR(&_17$$8);
				zephir_fast_trim(&_17$$8, &key, NULL , ZEPHIR_TRIM_BOTH);
				ZEPHIR_CPY_WRT(&key, &_17$$8);
				if (Z_TYPE_P(&value) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&_18$$10);
					zephir_fast_join_str(&_18$$10, SL(" "), &value);
					ZEPHIR_CPY_WRT(&value, &_18$$10);
				}
				zephir_cast_to_string(&_20$$8, &key);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_19$$8, this_ptr, "phpHtmlSpecialChars", NULL, 0, &_20$$8);
				zephir_check_call_status();
				zephir_concat_self(&result, &_19$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (!ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
					zephir_cast_to_string(&_22$$11, &value);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_21$$11, this_ptr, "phpHtmlSpecialChars", NULL, 0, &_22$$11);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_23$$11);
					ZEPHIR_CONCAT_SVS(&_23$$11, "=\"", &_21$$11, "\"");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&result, &_23$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				zephir_concat_self_str(&result, SL(" "));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	zephir_fast_trim(return_value, &result, NULL , ZEPHIR_TRIM_RIGHT);
	RETURN_MM();
}

/**
 * Escape CSS strings by replacing non-alphanumeric chars by their
 * hexadecimal escaped representation
 *
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, css)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, result, _0;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	if (UNEXPECTED(ZEPHIR_IS_EMPTY(&input_zv))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "normalizeEncoding", NULL, 356, &input_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&result, this_ptr, "doEscapeCss", NULL, 357, &_0);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) != IS_STRING) {
		RETURN_MM_STRING("");
	}
	RETURN_CCTOR(&result);
}

/**
 * Detect the character encoding of a string to be handled by an encoder.
 * Special-handling for chr(172) and chr(128) to chr(159) which fail to be
 * detected by mb_detect_encoding()
 *
 * @param string $input
 *
 * @return string|null
 */
PHP_METHOD(Phalcon_Html_Escaper, detectEncoding)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, __$true, charset, _1, *_2, _3$$5;
	zend_string *input = NULL;

	ZVAL_UNDEF(&input_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&charset);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	ZEPHIR_INIT_VAR(&charset);
	zephir_is_basic_charset(&charset, &input_zv);
	if (Z_TYPE_P(&charset) == IS_STRING) {
		RETURN_CCTOR(&charset);
	}
	if (!((zephir_function_exists_ex(ZEND_STRL("mb_detect_encoding")) == SUCCESS))) {
		RETURN_MM_NULL();
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "UTF-32");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "UTF-8");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "ISO-8859-1");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "ASCII");
	zephir_array_fast_append(&_0, &_1);
	zephir_is_iterable(&_0, 0, "phalcon/Html/Escaper.zep", 170);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _2)
	{
		ZEPHIR_INIT_NVAR(&charset);
		ZVAL_COPY(&charset, _2);
		ZEPHIR_CALL_FUNCTION(&_3$$5, "mb_detect_encoding", &_4, 358, &input_zv, &charset, &__$true);
		zephir_check_call_status();
		if (!ZEPHIR_IS_FALSE_IDENTICAL(&_3$$5)) {
			RETURN_CCTOR(&charset);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&charset);
	ZEPHIR_RETURN_CALL_FUNCTION("mb_detect_encoding", &_4, 358, &input_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escape CSS strings by replacing non-alphanumeric chars by their
 * hexadecimal escaped representation
 *
 * @param string $input
 *
 * @return string
 * @deprecated
 */
PHP_METHOD(Phalcon_Html_Escaper, escapeCss)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "css", NULL, 0, &input_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escape JavaScript strings by replacing non-alphanumeric chars by their
 * hexadecimal escaped representation
 *
 * @param string $input
 *
 * @return string
 * @deprecated
 */
PHP_METHOD(Phalcon_Html_Escaper, escapeJs)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "js", NULL, 0, &input_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escapes a HTML string. Internally uses htmlspecialchars
 *
 * @param string|null $input
 *
 * @return string
 * @deprecated
 */
PHP_METHOD(Phalcon_Html_Escaper, escapeHtml)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!input) {
		ZEPHIR_INIT_VAR(&input_zv);
	} else {
		zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	}
	zephir_cast_to_string(&_0, &input_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "html", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escapes a HTML attribute string
 *
 * @param string|null $input
 *
 * @return string
 * @deprecated
 */
PHP_METHOD(Phalcon_Html_Escaper, escapeHtmlAttr)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!input) {
		ZEPHIR_INIT_VAR(&input_zv);
	} else {
		zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	}
	zephir_cast_to_string(&_0, &input_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "attributes", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escapes a URL. Internally uses rawurlencode
 *
 * @param string $input
 *
 * @return string
 * @deprecated
 */
PHP_METHOD(Phalcon_Html_Escaper, escapeUrl)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "url", NULL, 0, &input_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, getEncoding)
{

	RETURN_MEMBER_TYPED(getThis(), "encoding", IS_STRING);
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Html_Escaper, getFlags)
{

	RETURN_MEMBER_TYPED(getThis(), "flags", IS_LONG);
}

/**
 * Escapes a HTML string. Internally uses htmlspecialchars
 *
 * @param string|null $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, html)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, _0, _1, _2;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("flags", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("encoding", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("doubleEncode", 12, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!input) {
		ZEPHIR_INIT_VAR(&input_zv);
	} else {
		zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	}
	if (Z_TYPE_P(&input_zv) == IS_NULL) {
		RETURN_MM_STRING("");
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 551, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 552, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_2, 553, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("htmlspecialchars", NULL, 320, &input_zv, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escape javascript strings by replacing non-alphanumeric chars by their
 * hexadecimal escaped representation
 *
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, js)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, result, _0;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	if (UNEXPECTED(ZEPHIR_IS_EMPTY(&input_zv))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "normalizeEncoding", NULL, 356, &input_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&result, this_ptr, "doEscapeJs", NULL, 359, &_0);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) != IS_STRING) {
		RETURN_MM_STRING("");
	}
	RETURN_CCTOR(&result);
}

/**
 * Utility to normalize a string's encoding to UTF-32.
 *
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, normalizeEncoding)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, _0, _1;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "detectEncoding", NULL, 360, &input_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "UTF-32");
	ZEPHIR_RETURN_CALL_FUNCTION("mb_convert_encoding", NULL, 361, &input_zv, &_1, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Sets the double_encode to be used by the escaper
 *
 *```php
 * $escaper->setDoubleEncode(false);
 *```
 *
 * @param bool $doubleEncode
 */
PHP_METHOD(Phalcon_Html_Escaper, setDoubleEncode)
{
	zval *doubleEncode_param = NULL, __$true, __$false;
	zend_bool doubleEncode;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("doubleEncode", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(doubleEncode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &doubleEncode_param);
	if (doubleEncode) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 553, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 553, &__$false);
	}
	RETURN_THISW();
}

/**
 * Sets the encoding to be used by the escaper
 *
 *```php
 * $escaper->setEncoding("utf-8");
 *```
 *
 * @param string $encoding
 */
PHP_METHOD(Phalcon_Html_Escaper, setEncoding)
{
	zval encoding_zv;
	zend_string *encoding = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&encoding_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("encoding", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(encoding)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&encoding_zv, encoding);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 552, &encoding_zv);
	RETURN_THISW();
}

/**
 * Sets the HTML quoting type for htmlspecialchars
 *
 *```php
 * $escaper->setFlags(ENT_XHTML);
 *```
 *
 * @param int $flags
 */
PHP_METHOD(Phalcon_Html_Escaper, setFlags)
{
	zval *flags_param = NULL, _0;
	zend_long flags;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("flags", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &flags_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, flags);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 551, &_0);
	RETURN_THISW();
}

/**
 * Sets the HTML quoting type for htmlspecialchars
 *
 *```php
 * $escaper->setHtmlQuoteType(ENT_XHTML);
 *```
 *
 * @param int $flags
 * @deprecated
 */
PHP_METHOD(Phalcon_Html_Escaper, setHtmlQuoteType)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *flags_param = NULL, _0;
	zend_long flags, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &flags_param);
	ZVAL_LONG(&_0, flags);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "setFlags", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escapes a URL. Internally uses rawurlencode
 *
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, url)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv;
	zend_string *input = NULL;

	ZVAL_UNDEF(&input_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	ZEPHIR_RETURN_CALL_FUNCTION("rawurlencode", NULL, 362, &input_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Proxy method for testing
 *
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, phpHtmlSpecialChars)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, _0, _1, _2;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("flags", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("encoding", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("doubleEncode", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 551, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 552, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_2, 553, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("htmlspecialchars", NULL, 320, &input_zv, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, doEscapeCss)
{
	zval input_zv;
	zend_string *input = NULL;

	ZVAL_UNDEF(&input_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&input_zv, input);
	zephir_escape_css(return_value, &input_zv);
	return;
}

/**
 * @param string $input
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Escaper, doEscapeJs)
{
	zval input_zv;
	zend_string *input = NULL;

	ZVAL_UNDEF(&input_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&input_zv, input);
	zephir_escape_js(return_value, &input_zv);
	return;
}

