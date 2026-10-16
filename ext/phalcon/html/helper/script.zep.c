
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
#include "kernel/fcall.h"
#include "kernel/object.h"
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
 * Class Script
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_Script)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper, Script, phalcon, html_helper_script, phalcon_html_helper_abstractseries_ce, phalcon_html_helper_script_method_entry, 0);

	return SUCCESS;
}

/**
 * Add an element to the list
 *
 * @param string $url
 * @param array  $attributes
 *
 * @return $this
 * @throws Exception
 */
PHP_METHOD(Phalcon_Html_Helper_Script, add)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes, _0, _2;
	zval url_zv, *attributes_param = NULL, _1, _3;
	zend_string *url = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&url_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(url)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		attributes_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&url_zv);
	ZVAL_STR_COPY(&url_zv, url);
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "renderFullElement");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 3, 0);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getTag", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(&_2, &_3);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "");
	zephir_array_fast_append(&_2, &_1);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getAttributes", NULL, 0, &url_zv, &attributes);
	zephir_check_call_status();
	zephir_array_fast_append(&_2, &_3);
	zephir_array_fast_append(&_0, &_2);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "indent", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(&_0, &_3);
	zephir_update_property_array_append(this_ptr, SL("store"), &_0);
	RETURN_THIS();
}

/**
 * Returns the necessary attributes
 *
 * @param string $url
 * @param array  $attributes
 *
 * @return array
 */
PHP_METHOD(Phalcon_Html_Helper_Script, getAttributes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval attributes, required;
	zval url_zv, *attributes_param = NULL;
	zend_string *url = NULL;

	ZVAL_UNDEF(&url_zv);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&required);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(url)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	attributes_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&url_zv);
	ZVAL_STR_COPY(&url_zv, url);
	zephir_get_arrval(&attributes, attributes_param);
	ZEPHIR_INIT_VAR(&required);
	zephir_create_array(&required, 2, 0);
	zephir_array_update_string(&required, SL("src"), &url_zv, PH_COPY | PH_SEPARATE);
	add_assoc_stringl_ex(&required, SL("type"), SL("application/javascript"));
	zephir_array_unset_string(&attributes, SL("src"), PH_SEPARATE);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_fast_array_merge(return_value, &required, &attributes);
	RETURN_MM();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_Script, getTag)
{

	RETURN_STRING("script");
}

