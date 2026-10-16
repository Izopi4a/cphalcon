
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
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/fcall.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * @property array $attributes
 * @property array $store
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_AbstractSeries)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper, AbstractSeries, phalcon, html_helper_abstractseries, phalcon_html_helper_abstracthelper_ce, phalcon_html_helper_abstractseries_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_html_helper_abstractseries_ce, SL("attributes"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_html_helper_abstractseries_ce, SL("store"), ZEND_ACC_PROTECTED);
	phalcon_html_helper_abstractseries_ce->create_object = zephir_init_properties_Phalcon_Html_Helper_AbstractSeries;

	return SUCCESS;
}

/**
 * @param string $indent
 * @param string $delimiter
 *
 * @return AbstractSeries
 */
PHP_METHOD(Phalcon_Html_Helper_AbstractSeries, __invoke)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval indent_zv, delimiter_zv, _0;
	zend_string *indent = NULL, *delimiter = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&indent_zv);
	ZVAL_UNDEF(&delimiter_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("delimiter", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("indent", 6, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(indent)
		Z_PARAM_STR_OR_NULL(delimiter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!indent) {
		indent = zend_string_init(ZEND_STRL("    "), 0);
		zephir_memory_observe(&indent_zv);
		ZVAL_STR(&indent_zv, indent);
	} else {
		zephir_memory_observe(&indent_zv);
	ZVAL_STR_COPY(&indent_zv, indent);
	}
	if (!delimiter) {
		ZEPHIR_INIT_VAR(&delimiter_zv);
	} else {
		zephir_memory_observe(&delimiter_zv);
	ZVAL_STR_COPY(&delimiter_zv, delimiter);
	}
	ZEPHIR_INIT_VAR(&_0);
	if (Z_TYPE_P(&delimiter_zv) == IS_NULL) {
		ZEPHIR_INIT_NVAR(&_0);
		ZEPHIR_GET_CONSTANT(&_0, "PHP_EOL");
	} else {
		ZEPHIR_CPY_WRT(&_0, &delimiter_zv);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 63, &_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 64, &indent_zv);
	RETURN_THIS();
}

/**
 * Generates and returns the HTML for the list.
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_AbstractSeries, __toString)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("store", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("delimiter", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 65, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 63, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "renderArrayElements", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Resets the internal store.
 */
PHP_METHOD(Phalcon_Html_Helper_AbstractSeries, reset)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("store", 5, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 65, &_0);
	RETURN_THIS();
}

/**
 * Returns the tag name.
 *
 * @return string
 */
PHP_METHOD(Phalcon_Html_Helper_AbstractSeries, getTag)
{
}

zend_object *zephir_init_properties_Phalcon_Html_Helper_AbstractSeries(zend_class_entry *class_type)
{
		zval _0, _2, _1$$3, _3$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("store"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("store"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("attributes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("attributes"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

