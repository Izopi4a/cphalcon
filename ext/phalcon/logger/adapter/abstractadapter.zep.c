
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
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/string.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Class AbstractAdapter
 *
 * @property string             $defaultFormatter
 * @property FormatterInterface $formatter
 * @property bool               $inTransaction
 * @property array              $queue
 */
ZEPHIR_INIT_CLASS(Phalcon_Logger_Adapter_AbstractAdapter)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Logger\\Adapter, AbstractAdapter, phalcon, logger_adapter_abstractadapter, phalcon_logger_adapter_abstractadapter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Name of the default formatter class
	 *
	 * @var string
	 */
	zend_declare_property_string(phalcon_logger_adapter_abstractadapter_ce, SL("defaultFormatter"), "Phalcon\\Logger\\Formatter\\Line", ZEND_ACC_PROTECTED);
	/**
	 * Formatter
	 *
	 * @var FormatterInterface|null
	 */
	zend_declare_property_null(phalcon_logger_adapter_abstractadapter_ce, SL("formatter"), ZEND_ACC_PROTECTED);
	/**
	 * Tells if there is an active transaction or not
	 *
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_logger_adapter_abstractadapter_ce, SL("inTransaction"), 0, ZEND_ACC_PROTECTED);
	/**
	 * Array with messages queued in the transaction
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_logger_adapter_abstractadapter_ce, SL("queue"), ZEND_ACC_PROTECTED);
	phalcon_logger_adapter_abstractadapter_ce->create_object = zephir_init_properties_Phalcon_Logger_Adapter_AbstractAdapter;

	zend_class_implements(phalcon_logger_adapter_abstractadapter_ce, 1, phalcon_logger_adapter_adapterinterface_ce);
	return SUCCESS;
}

/**
 * Destructor cleanup
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, __destruct)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("inTransaction", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 86, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_logger_exception_ce, "There is an active transaction", "phalcon/Logger/Adapter/AbstractAdapter.zep", 64);
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "close", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Prevent serialization
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, __serialize)
{

	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_logger_exception_ce, "This object cannot be serialized", "phalcon/Logger/Adapter/AbstractAdapter.zep", 75);
	return;
}

/**
 * Prevent unserialization
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, __unserialize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *data_param = NULL;
	zval data;

	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data_param);
	zephir_get_arrval(&data, data_param);
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_logger_exception_ce, "This object cannot be unserialized", "phalcon/Logger/Adapter/AbstractAdapter.zep", 83);
	return;
}

/**
 * Adds a message to the queue
 *
 * @param Item $item
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, add)
{
	zval *item, item_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(item, phalcon_logger_item_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &item);
	zephir_update_property_array_append(this_ptr, SL("queue"), item);
	RETURN_THISW();
}

/**
 * Starts a transaction
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, begin)
{
	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("inTransaction", 13, 1);
	}
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 86, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 86, &__$false);
	}
	RETURN_THISW();
}

/**
 * Commits the internal transaction
 *
 * @return AdapterInterface
 * @throws Exception
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, commit)
{
	zend_bool _6;
	zval item, queue, _0, *_1, _2, *_3, _5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&queue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("queue", 5, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkTransaction", NULL, 67);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 87, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&queue, &_0);
	if (Z_TYPE_P(&queue) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &queue);
		_1 = &_2;
	} else {
		_1 = &queue;
	}
	zephir_is_iterable(_1, 0, "phalcon/Logger/Adapter/AbstractAdapter.zep", 132);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&item);
			ZVAL_COPY(&item, _3);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "process", &_4, 0, &item);
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
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "process", &_4, 0, &item);
				zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "resetTransaction", NULL, 68);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * @return FormatterInterface
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, getFormatter)
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
		_zephir_prop_0 = zend_string_init("formatter", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("defaultFormatter", 16, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 88, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 89, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(&_1$$3, &_2$$3);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 88, &_1$$3);
	}
	RETURN_MM_MEMBER(getThis(), "formatter");
}

/**
 * Returns the whether the logger is currently in an active transaction or
 * not
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, inTransaction)
{

	RETURN_MEMBER(getThis(), "inTransaction");
}

/**
 * Processes the message in the adapter
 *
 * @param Item $item
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, process)
{
}

/**
 * Rollbacks the internal transaction
 *
 * @return AdapterInterface
 * @throws Exception
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, rollback)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkTransaction", NULL, 67);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "resetTransaction", NULL, 68);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets the message formatter
 *
 * @param FormatterInterface $formatter
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, setFormatter)
{
	zval *formatter, formatter_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&formatter_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("formatter", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(formatter, phalcon_logger_formatter_formatterinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &formatter);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 88, formatter);
	RETURN_THISW();
}

/**
 * Returns the formatted item
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, getFormattedItem)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *item, item_sub, formatter;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item_sub);
	ZVAL_UNDEF(&formatter);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(item, phalcon_logger_item_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &item);
	ZEPHIR_CALL_METHOD(&formatter, this_ptr, "getFormatter", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&formatter, "format", NULL, 0, item);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Checks if the transaction is active
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, checkTransaction)
{
	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("inTransaction", 13, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 86, PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_TRUE_IDENTICAL(&_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_logger_exception_ce, "There is no active transaction", "phalcon/Logger/Adapter/AbstractAdapter.zep", 213);
		return;
	}
}

/**
 * Resets the transaction flag and queue array
 */
PHP_METHOD(Phalcon_Logger_Adapter_AbstractAdapter, resetTransaction)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, __$false, _0;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("queue", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("inTransaction", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 87, &_0);
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 86, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 86, &__$false);
	}
	ZEPHIR_MM_RESTORE();
}

zend_object *zephir_init_properties_Phalcon_Logger_Adapter_AbstractAdapter(zend_class_entry *class_type)
{
		zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("queue"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("queue"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

