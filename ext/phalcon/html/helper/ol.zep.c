
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
#include "kernel/fcall.h"
#include "kernel/operators.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Class Ol
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_Ol)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper, Ol, phalcon, html_helper_ol, phalcon_html_helper_abstractlist_ce, phalcon_html_helper_ol_method_entry, 0);

	return SUCCESS;
}

/**
 * Add an element to the list
 *
 * @param string $text
 * @param array  $attributes
 * @param bool   $raw
 *
 * @return AbstractList
 */
PHP_METHOD(Phalcon_Html_Helper_Ol, add)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool raw;
	zval attributes, _0, _2;
	zval text_zv, *attributes_param = NULL, *raw_param = NULL, _1, _3, _4;
	zend_string *text = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("elementTag", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(text)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_BOOL(raw)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		attributes_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		raw_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&text_zv);
	ZVAL_STR_COPY(&text_zv, text);
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
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "renderFullElement");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 4, 0);
	zephir_memory_observe(&_3);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 198, PH_NOISY_CC);
	zephir_array_fast_append(&_2, &_3);
	zephir_array_fast_append(&_2, &text_zv);
	zephir_array_fast_append(&_2, &attributes);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_BOOL(&_1, raw);
	zephir_array_fast_append(&_2, &_1);
	zephir_array_fast_append(&_0, &_2);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "indent", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(&_0, &_4);
	zephir_update_property_array_append(this_ptr, SL("store"), &_0);
	RETURN_THIS();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_Ol, getTag)
{

	RETURN_STRING("ol");
}

