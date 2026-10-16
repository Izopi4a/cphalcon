
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
#include "kernel/fcall.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Class AbstractFormatter
 */
ZEPHIR_INIT_CLASS(Phalcon_Logger_Formatter_AbstractFormatter)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Logger\\Formatter, AbstractFormatter, phalcon, logger_formatter_abstractformatter, phalcon_support_helper_str_abstractstr_ce, phalcon_logger_formatter_abstractformatter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Default date format
	 *
	 * @var string
	 */
	zend_declare_property_string(phalcon_logger_formatter_abstractformatter_ce, SL("dateFormat"), "c", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_logger_formatter_abstractformatter_ce, SL("interpolatorLeft"), "%", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_logger_formatter_abstractformatter_ce, SL("interpolatorRight"), "%", ZEND_ACC_PROTECTED);
	zend_class_implements(phalcon_logger_formatter_abstractformatter_ce, 1, phalcon_logger_formatter_formatterinterface_ce);
	return SUCCESS;
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Logger_Formatter_AbstractFormatter, getDateFormat)
{

	RETURN_MEMBER_TYPED(getThis(), "dateFormat", IS_STRING);
}

/**
 * @param string $format
 */
PHP_METHOD(Phalcon_Logger_Formatter_AbstractFormatter, setDateFormat)
{
	zval format_zv;
	zend_string *format = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&format_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dateFormat", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(format)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&format_zv, format);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 174, &format_zv);
}

/**
 * Returns the date formatted for the logger.
 *
 * @param Item $item
 *
 * @return string
 */
PHP_METHOD(Phalcon_Logger_Formatter_AbstractFormatter, getFormattedDate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *item, item_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dateFormat", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(item, phalcon_logger_item_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &item);
	ZEPHIR_CALL_METHOD(&_0, item, "getDateTime", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 174, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "format", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param Item   $item
 * @param string $message
 *
 * @return string
 */
PHP_METHOD(Phalcon_Logger_Formatter_AbstractFormatter, getInterpolatedMessage)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *message = NULL;
	zval *item, item_sub, message_zv, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item_sub);
	ZVAL_UNDEF(&message_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("interpolatorLeft", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("interpolatorRight", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(item, phalcon_logger_item_ce)
		Z_PARAM_STR(message)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	item = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&message_zv);
	ZVAL_STR_COPY(&message_zv, message);
	ZEPHIR_CALL_METHOD(&_0, item, "getContext", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 175, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 176, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "toInterpolate", NULL, 0, &message_zv, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

