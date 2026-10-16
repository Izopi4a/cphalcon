
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


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Class Element
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_Element)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper, Element, phalcon, html_helper_element, phalcon_html_helper_abstracthelper_ce, phalcon_html_helper_element_method_entry, 0);

	return SUCCESS;
}

/**
 * Produce a tag.
 *
 * @param string $tag
 * @param string $text
 * @param array  $attributes
 * @param bool   $raw
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Html_Helper_Element, __invoke)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool raw;
	zval attributes;
	zval tag_zv, text_zv, *attributes_param = NULL, *raw_param = NULL, _0;
	zend_string *tag = NULL, *text = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tag_zv);
	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(tag)
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
	zephir_memory_observe(&tag_zv);
	ZVAL_STR_COPY(&tag_zv, tag);
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
	if (raw) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "renderFullElement", NULL, 0, &tag_zv, &text_zv, &attributes, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

