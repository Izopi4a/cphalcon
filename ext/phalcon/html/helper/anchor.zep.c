
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Class Anchor
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_Anchor)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper, Anchor, phalcon, html_helper_anchor, phalcon_html_helper_abstracthelper_ce, phalcon_html_helper_anchor_method_entry, 0);

	return SUCCESS;
}

/**
 * Produce a <a> tag
 *
 * @param string $href
 * @param string $text
 * @param array  $attributes
 * @param bool   $raw
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Html_Helper_Anchor, __invoke)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool raw;
	zval attributes;
	zval href_zv, text_zv, *attributes_param = NULL, *raw_param = NULL, overrides, _0, _1;
	zend_string *href = NULL, *text = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&href_zv);
	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&overrides);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(href)
		Z_PARAM_STR(text)
		Z_PARAM_OPTIONAL
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
	zephir_memory_observe(&href_zv);
	ZVAL_STR_COPY(&href_zv, href);
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
	ZEPHIR_CALL_METHOD(&overrides, this_ptr, "processAttributes", NULL, 0, &href_zv, &attributes);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "a");
	if (raw) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "renderFullElement", NULL, 0, &_0, &text_zv, &overrides, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param string $href
 * @param array  $attributes
 *
 * @return array
 */
PHP_METHOD(Phalcon_Html_Helper_Anchor, processAttributes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval attributes;
	zval href_zv, *attributes_param = NULL, overrides;
	zend_string *href = NULL;

	ZVAL_UNDEF(&href_zv);
	ZVAL_UNDEF(&overrides);
	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(href)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	attributes_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&href_zv);
	ZVAL_STR_COPY(&href_zv, href);
	zephir_get_arrval(&attributes, attributes_param);
	ZEPHIR_INIT_VAR(&overrides);
	zephir_create_array(&overrides, 1, 0);
	zephir_array_update_string(&overrides, SL("href"), &href_zv, PH_COPY | PH_SEPARATE);
	zephir_array_unset_string(&attributes, SL("href"), PH_SEPARATE);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_fast_array_merge(return_value, &overrides, &attributes);
	RETURN_MM();
}

