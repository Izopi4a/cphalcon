
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
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/string.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view
 * the LICENSE file that was distributed with this source code.
 */
/**
 * Base class for Phalcon\Db\Adapter adapters.
 *
 * This class and its related classes provide a simple SQL database interface
 * for Phalcon Framework. The Phalcon\Db is the basic class you use to connect
 * your PHP application to an RDBMS. There is a different adapter class for each
 * brand of RDBMS.
 *
 * This component is intended to lower level database operations. If you want to
 * interact with databases using higher level of abstraction use
 * Phalcon\Mvc\Model.
 *
 * Phalcon\Db\AbstractDb is an abstract class. You only can use it with a
 * database adapter like Phalcon\Db\Adapter\Pdo
 *
 *```php
 * use Phalcon\Db;
 * use Phalcon\Db\Exception;
 * use Phalcon\Db\Adapter\Pdo\Mysql as MysqlConnection;
 *
 * try {
 *     $connection = new MysqlConnection(
 *         [
 *             "host"     => "192.168.0.11",
 *             "username" => "sigma",
 *             "password" => "secret",
 *             "dbname"   => "blog",
 *             "port"     => "3306",
 *         ]
 *     );
 *
 *     $result = $connection->query(
 *         "SELECT * FROM co_invoices LIMIT 5"
 *     );
 *
 *     $result->setFetchMode(Enum::FETCH_NUM);
 *
 *     while ($invoice = $result->fetch()) {
 *         print_r($invoice);
 *     }
 * } catch (Exception $e) {
 *     echo $e->getMessage(), PHP_EOL;
 * }
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter_AbstractAdapter)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Db\\Adapter, AbstractAdapter, phalcon, db_adapter_abstractadapter, phalcon_db_adapter_abstractadapter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Connection ID
	 *
	 * @var int
	 */
	zend_declare_property_long(phalcon_db_adapter_abstractadapter_ce, SL("connectionConsecutive"), 0, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC);
	/**
	 * Active connection ID
	 *
	 * @var int
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("connectionId"), ZEND_ACC_PROTECTED);
	/**
	 * Descriptor used to connect to a database
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("descriptor"), ZEND_ACC_PROTECTED);
	/**
	 * Dialect instance
	 *
	 * @var object
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("dialect"), ZEND_ACC_PROTECTED);
	/**
	 * Name of the dialect used
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("dialectType"), ZEND_ACC_PROTECTED);
	/**
	 * Event Manager
	 *
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * The real SQL statement - what was executed
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("realSqlStatement"), ZEND_ACC_PROTECTED);
	/**
	 * Active SQL Bind Types
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("sqlBindTypes"), ZEND_ACC_PROTECTED);
	/**
	 * Active SQL Statement
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("sqlStatement"), ZEND_ACC_PROTECTED);
	/**
	 * Active SQL bound parameter variables
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("sqlVariables"), ZEND_ACC_PROTECTED);
	/**
	 * Current transaction level
	 *
	 * @var int
	 */
	zend_declare_property_long(phalcon_db_adapter_abstractadapter_ce, SL("transactionLevel"), 0, ZEND_ACC_PROTECTED);
	/**
	 * Whether the database supports transactions with save points
	 *
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_db_adapter_abstractadapter_ce, SL("transactionsWithSavepoints"), 0, ZEND_ACC_PROTECTED);
	/**
	 * Type of database system the adapter is used for
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_abstractadapter_ce, SL("type"), ZEND_ACC_PROTECTED);
	phalcon_db_adapter_abstractadapter_ce->create_object = zephir_init_properties_Phalcon_Db_Adapter_AbstractAdapter;

	zend_class_implements(phalcon_db_adapter_abstractadapter_ce, 1, phalcon_db_adapter_adapterinterface_ce);
	zend_class_implements(phalcon_db_adapter_abstractadapter_ce, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Db\Adapter constructor
 *
 * @param array descriptor = [
 *     'host' => 'localhost',
 *     'port' => '3306',
 *     'dbname' => 'blog',
 *     'username' => 'sigma'
 *     'password' => 'secret',
 *     'dialectClass' => null,
 *     'options' => [],
 *     'dsn' => null,
 *     'charset' => 'utf8mb4'
 * ]
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, __construct)
{
	zend_bool _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *descriptor_param = NULL, dialectClass, connectionId, _0, _1, _5, _2$$3, _3$$4, _6$$6;
	zval descriptor;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&descriptor);
	ZVAL_UNDEF(&dialectClass);
	ZVAL_UNDEF(&connectionId);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_6$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("connectionId", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("dialectType", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dialect", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("descriptor", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(descriptor, descriptor_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &descriptor_param);
	ZEPHIR_OBS_COPY_OR_DUP(&descriptor, descriptor_param);
	zephir_memory_observe(&connectionId);
	zephir_read_static_property_ce(&connectionId, phalcon_db_adapter_abstractadapter_ce, SL("connectionConsecutive"), PH_NOISY_CC);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 55, &connectionId);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, 1);
	ZEPHIR_INIT_VAR(&_1);
	zephir_add_function(&_1, &connectionId, &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_static_property_ce(phalcon_db_adapter_abstractadapter_ce, ZEND_STRL("connectionConsecutive"), &_1);
	zephir_memory_observe(&dialectClass);
	if (!(zephir_array_isset_string_fetch(&dialectClass, &descriptor, SL("dialectClass"), 0))) {
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 56, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&dialectClass);
		ZEPHIR_CONCAT_SV(&dialectClass, "phalcon\\db\\dialect\\", &_2$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(&dialectClass) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3$$4);
		ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(&_3$$4, &dialectClass);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 57, &_3$$4);
	} else if (Z_TYPE_P(&dialectClass) == IS_OBJECT) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 57, &dialectClass);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 58, &descriptor);
	_4 = zephir_array_isset_value_string(&descriptor, SL("options"));
	if (_4) {
		zephir_memory_observe(&_5);
		zephir_array_fetch_string(&_5, &descriptor, SL("options"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 205);
		_4 = Z_TYPE_P(&_5) == IS_ARRAY;
	}
	if (_4) {
		zephir_array_fetch_string(&_6$$6, &descriptor, SL("options"), PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 206);
		ZEPHIR_CALL_SELF(NULL, "setup", NULL, 0, &_6$$6);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Adds a column to a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, addColumn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	column = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "addColumn", NULL, 0, &tableName_zv, &schemaName_zv, column);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a foreign key to a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, addForeignKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *reference, reference_sub, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&reference_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_OBJECT_OF_CLASS(reference, phalcon_db_referenceinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	reference = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "addForeignKey", NULL, 0, &tableName_zv, &schemaName_zv, reference);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds an index to a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, addIndex)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *index, index_sub, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_OBJECT_OF_CLASS(index, phalcon_db_indexinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	index = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "addIndex", NULL, 0, &tableName_zv, &schemaName_zv, index);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a primary key to a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, addPrimaryKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *index, index_sub, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_OBJECT_OF_CLASS(index, phalcon_db_indexinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	index = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "addPrimaryKey", NULL, 0, &tableName_zv, &schemaName_zv, index);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Creates a new savepoint
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, createSavepoint)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, dialect, _0, _1, _2;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&dialect, &_0);
	ZEPHIR_CALL_METHOD(&_1, &dialect, "supportsSavePoints", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter.", "phalcon/Db/Adapter/AbstractAdapter.zep", 278);
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, &dialect, "createSavepoint", NULL, 0, &name_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Creates a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, createTable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval definition;
	zval tableName_zv, schemaName_zv, *definition_param = NULL, columns, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&definition);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		ZEPHIR_Z_PARAM_ARRAY(definition, definition_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	definition_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	ZEPHIR_OBS_COPY_OR_DUP(&definition, definition_param);
	zephir_memory_observe(&columns);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&columns, &definition, SL("columns"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The table must contain at least one column", "phalcon/Db/Adapter/AbstractAdapter.zep", 294);
		return;
	}
	if (UNEXPECTED(!(zephir_fast_count_int(&columns)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The table must contain at least one column", "phalcon/Db/Adapter/AbstractAdapter.zep", 298);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "createTable", NULL, 0, &tableName_zv, &schemaName_zv, &definition);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Creates a view
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, createView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval definition;
	zval viewName_zv, *definition_param = NULL, schemaName_zv, _0, _1;
	zend_string *viewName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&definition);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(viewName)
		ZEPHIR_Z_PARAM_ARRAY(definition, definition_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	definition_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&viewName_zv);
	ZVAL_STR_COPY(&viewName_zv, viewName);
	ZEPHIR_OBS_COPY_OR_DUP(&definition, definition_param);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
		zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	if (UNEXPECTED(!(zephir_array_isset_value_string(&definition, SL("sql"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The table must contain at least one column", "phalcon/Db/Adapter/AbstractAdapter.zep", 316);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "createView", NULL, 0, &viewName_zv, &definition, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Deletes data from a table using custom RBDM SQL syntax
 *
 * ```php
 * // Deleting existing robot
 * $success = $connection->delete(
 *     "robots",
 *     "id = 101"
 * );
 *
 * // Next SQL sentence is generated
 * DELETE FROM `robots` WHERE `id` = 101
 * ```
 *
 * @param array|string table
 * @param string|null whereCondition
 * @param array placeholders
 * @param array dataTypes
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, delete)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval placeholders, dataTypes;
	zend_string *whereCondition = NULL;
	zval *table, table_sub, whereCondition_zv, *placeholders_param = NULL, *dataTypes_param = NULL, sql, escapedTable;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_sub);
	ZVAL_UNDEF(&whereCondition_zv);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&escapedTable);
	ZVAL_UNDEF(&placeholders);
	ZVAL_UNDEF(&dataTypes);
	ZVAL_UNDEF(&_0$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_ZVAL(table)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(whereCondition)
		ZEPHIR_Z_PARAM_ARRAY(placeholders, placeholders_param)
		ZEPHIR_Z_PARAM_ARRAY(dataTypes, dataTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	table = ZEND_CALL_ARG(execute_data, 1);
	if (ZEND_NUM_ARGS() > 2) {
		placeholders_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		dataTypes_param = ZEND_CALL_ARG(execute_data, 4);
	}
	if (!whereCondition) {
		ZEPHIR_INIT_VAR(&whereCondition_zv);
	} else {
		zephir_memory_observe(&whereCondition_zv);
	ZVAL_STR_COPY(&whereCondition_zv, whereCondition);
	}
	if (!placeholders_param) {
		ZEPHIR_INIT_VAR(&placeholders);
		array_init(&placeholders);
	} else {
		zephir_get_arrval(&placeholders, placeholders_param);
	}
	if (!dataTypes_param) {
		ZEPHIR_INIT_VAR(&dataTypes);
		array_init(&dataTypes);
	} else {
		zephir_get_arrval(&dataTypes, dataTypes_param);
	}
	ZEPHIR_CALL_METHOD(&escapedTable, this_ptr, "escapeIdentifier", NULL, 0, table);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&sql);
	ZEPHIR_CONCAT_SV(&sql, "DELETE FROM ", &escapedTable);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (!(ZEPHIR_IS_EMPTY(&whereCondition_zv))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SV(&_0$$3, " WHERE ", &whereCondition_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &sql, &placeholders, &dataTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Lists table indexes
 *
 *```php
 * print_r(
 *     $connection->describeIndexes("robots_parts")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, describeIndexes)
{
	zend_ulong _14;
	zend_bool _9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_17 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, indexes, index, keyName, indexObjects, name, indexColumns, columns, _0, _1, _2, _3, *_4, _5, *_6, _8, *_11, _12, *_13, _7$$3, _10$$6, _16$$9;
	zend_string *table = NULL, *schema = NULL, *_15;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&indexes);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&keyName);
	ZVAL_UNDEF(&indexObjects);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&indexColumns);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_16$$9);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(table)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schema)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!schema) {
		ZEPHIR_INIT_VAR(&schema_zv);
	} else {
		zephir_memory_observe(&schema_zv);
	ZVAL_STR_COPY(&schema_zv, schema);
	}
	ZEPHIR_INIT_VAR(&indexes);
	array_init(&indexes);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "describeIndexes", NULL, 0, &table_zv, &schema_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchAll", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &_0);
		_4 = &_5;
	} else {
		_4 = &_0;
	}
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 395);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&index);
			ZVAL_COPY(&index, _6);
			ZEPHIR_OBS_NVAR(&keyName);
			zephir_array_fetch_long(&keyName, &index, 2, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 383);
			if (!(zephir_array_isset_value(&indexes, &keyName))) {
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
			} else {
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch(&columns, &indexes, &keyName, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 388);
			}
			ZEPHIR_OBS_NVAR(&_7$$3);
			zephir_array_fetch_long(&_7$$3, &index, 4, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 391);
			zephir_array_append(&columns, &_7$$3, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 391);
			zephir_array_update_zval(&indexes, &keyName, &columns, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_9 = 1;
		while (1) {
			if (_9) {
				_9 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_8, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&index, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&keyName);
				zephir_array_fetch_long(&keyName, &index, 2, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 383);
				if (!(zephir_array_isset_value(&indexes, &keyName))) {
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
				} else {
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch(&columns, &indexes, &keyName, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 388);
				}
				ZEPHIR_OBS_NVAR(&_10$$6);
				zephir_array_fetch_long(&_10$$6, &index, 4, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 391);
				zephir_array_append(&columns, &_10$$6, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 391);
				zephir_array_update_zval(&indexes, &keyName, &columns, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&index);
	ZEPHIR_INIT_VAR(&indexObjects);
	array_init(&indexObjects);
	if (Z_TYPE_P(&indexes) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_12);
		zephir_string_to_char_array(&_12, &indexes);
		_11 = &_12;
	} else {
		_11 = &indexes;
	}
	zephir_is_iterable(_11, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 404);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_11), _14, _15, _13)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_15 != NULL) { 
			ZVAL_STR_COPY(&name, _15);
		} else {
			ZVAL_LONG(&name, _14);
		}
		ZEPHIR_INIT_NVAR(&indexColumns);
		ZVAL_COPY(&indexColumns, _13);
		ZEPHIR_INIT_NVAR(&_16$$9);
		object_init_ex(&_16$$9, phalcon_db_index_ce);
		ZEPHIR_CALL_METHOD(NULL, &_16$$9, "__construct", &_17, 33, &name, &indexColumns);
		zephir_check_call_status();
		zephir_array_update_zval(&indexObjects, &name, &_16$$9, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&indexColumns);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&indexObjects);
}

/**
 * Lists table references
 *
 *```php
 * print_r(
 *     $connection->describeReferences("robots_parts")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, describeReferences)
{
	zval _13$$3, _22$$6, _29$$9;
	zend_ulong _26;
	zend_bool _15;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_31 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, references, reference, arrayReference, constraintName, referenceObjects, name, referencedSchema, referencedTable, columns, referencedColumns, _0, _1, _2, _3, *_4, _5, *_6, _14, *_23, _24, *_25, _7$$5, _8$$5, _9$$5, _10$$5, _11$$3, _12$$3, _16$$8, _17$$8, _18$$8, _19$$8, _20$$6, _21$$6, _28$$9, _30$$9;
	zend_string *table = NULL, *schema = NULL, *_27;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&references);
	ZVAL_UNDEF(&reference);
	ZVAL_UNDEF(&arrayReference);
	ZVAL_UNDEF(&constraintName);
	ZVAL_UNDEF(&referenceObjects);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&referencedSchema);
	ZVAL_UNDEF(&referencedTable);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&referencedColumns);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_29$$9);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(table)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schema)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!schema) {
		ZEPHIR_INIT_VAR(&schema_zv);
	} else {
	zephir_memory_observe(&schema_zv);
	ZVAL_STR_COPY(&schema_zv, schema);
	}
	ZEPHIR_INIT_VAR(&references);
	array_init(&references);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "describeReferences", NULL, 0, &table_zv, &schema_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchAll", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &_0);
		_4 = &_5;
	} else {
		_4 = &_0;
	}
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 450);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&reference);
			ZVAL_COPY(&reference, _6);
			ZEPHIR_OBS_NVAR(&constraintName);
			zephir_array_fetch_long(&constraintName, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 425);
			if (!(zephir_array_isset_value(&references, &constraintName))) {
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_long(&referencedSchema, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 428);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_long(&referencedTable, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 429);
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
				ZEPHIR_INIT_NVAR(&referencedColumns);
				array_init(&referencedColumns);
			} else {
				zephir_array_fetch(&_7$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 433);
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_string(&referencedSchema, &_7$$5, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 433);
				zephir_array_fetch(&_8$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 434);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_string(&referencedTable, &_8$$5, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 434);
				zephir_array_fetch(&_9$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 435);
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch_string(&columns, &_9$$5, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 435);
				zephir_array_fetch(&_10$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 436);
				ZEPHIR_OBS_NVAR(&referencedColumns);
				zephir_array_fetch_string(&referencedColumns, &_10$$5, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 436);
			}
			ZEPHIR_OBS_NVAR(&_11$$3);
			zephir_array_fetch_long(&_11$$3, &reference, 1, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 439);
			zephir_array_append(&columns, &_11$$3, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 439);
			ZEPHIR_OBS_NVAR(&_12$$3);
			zephir_array_fetch_long(&_12$$3, &reference, 5, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 440);
			zephir_array_append(&referencedColumns, &_12$$3, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 440);
			ZEPHIR_INIT_NVAR(&_13$$3);
			zephir_create_array(&_13$$3, 4, 0);
			zephir_array_update_string(&_13$$3, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_13$$3, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_13$$3, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_13$$3, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
			zephir_array_update_zval(&references, &constraintName, &_13$$3, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_15 = 1;
		while (1) {
			if (_15) {
				_15 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_14, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_14)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&reference, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&constraintName);
				zephir_array_fetch_long(&constraintName, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 425);
				if (!(zephir_array_isset_value(&references, &constraintName))) {
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_long(&referencedSchema, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 428);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_long(&referencedTable, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 429);
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
					ZEPHIR_INIT_NVAR(&referencedColumns);
					array_init(&referencedColumns);
				} else {
					zephir_array_fetch(&_16$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 433);
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_string(&referencedSchema, &_16$$8, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 433);
					zephir_array_fetch(&_17$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 434);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_string(&referencedTable, &_17$$8, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 434);
					zephir_array_fetch(&_18$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 435);
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch_string(&columns, &_18$$8, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 435);
					zephir_array_fetch(&_19$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/AbstractAdapter.zep", 436);
					ZEPHIR_OBS_NVAR(&referencedColumns);
					zephir_array_fetch_string(&referencedColumns, &_19$$8, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 436);
				}
				ZEPHIR_OBS_NVAR(&_20$$6);
				zephir_array_fetch_long(&_20$$6, &reference, 1, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 439);
				zephir_array_append(&columns, &_20$$6, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 439);
				ZEPHIR_OBS_NVAR(&_21$$6);
				zephir_array_fetch_long(&_21$$6, &reference, 5, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 440);
				zephir_array_append(&referencedColumns, &_21$$6, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 440);
				ZEPHIR_INIT_NVAR(&_22$$6);
				zephir_create_array(&_22$$6, 4, 0);
				zephir_array_update_string(&_22$$6, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_22$$6, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_22$$6, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_22$$6, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&references, &constraintName, &_22$$6, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&reference);
	ZEPHIR_INIT_VAR(&referenceObjects);
	array_init(&referenceObjects);
	if (Z_TYPE_P(&references) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_24);
		zephir_string_to_char_array(&_24, &references);
		_23 = &_24;
	} else {
		_23 = &references;
	}
	zephir_is_iterable(_23, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 464);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_23), _26, _27, _25)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_27 != NULL) { 
			ZVAL_STR_COPY(&name, _27);
		} else {
			ZVAL_LONG(&name, _26);
		}
		ZEPHIR_INIT_NVAR(&arrayReference);
		ZVAL_COPY(&arrayReference, _25);
		ZEPHIR_INIT_NVAR(&_28$$9);
		object_init_ex(&_28$$9, phalcon_db_reference_ce);
		ZEPHIR_INIT_NVAR(&_29$$9);
		zephir_create_array(&_29$$9, 4, 0);
		ZEPHIR_OBS_NVAR(&_30$$9);
		zephir_array_fetch_string(&_30$$9, &arrayReference, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 456);
		zephir_array_update_string(&_29$$9, SL("referencedSchema"), &_30$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_30$$9);
		zephir_array_fetch_string(&_30$$9, &arrayReference, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 457);
		zephir_array_update_string(&_29$$9, SL("referencedTable"), &_30$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_30$$9);
		zephir_array_fetch_string(&_30$$9, &arrayReference, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 458);
		zephir_array_update_string(&_29$$9, SL("columns"), &_30$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_30$$9);
		zephir_array_fetch_string(&_30$$9, &arrayReference, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 460);
		zephir_array_update_string(&_29$$9, SL("referencedColumns"), &_30$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, &_28$$9, "__construct", &_31, 34, &name, &_29$$9);
		zephir_check_call_status();
		zephir_array_update_zval(&referenceObjects, &name, &_28$$9, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&arrayReference);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&referenceObjects);
}

/**
 * Drops a column from a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, dropColumn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, columnName_zv, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL, *columnName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&columnName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_STR(columnName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_memory_observe(&columnName_zv);
	ZVAL_STR_COPY(&columnName_zv, columnName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "dropColumn", NULL, 0, &tableName_zv, &schemaName_zv, &columnName_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Drops a foreign key from a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, dropForeignKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, referenceName_zv, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL, *referenceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&referenceName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_STR(referenceName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_memory_observe(&referenceName_zv);
	ZVAL_STR_COPY(&referenceName_zv, referenceName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "dropForeignKey", NULL, 0, &tableName_zv, &schemaName_zv, &referenceName_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Drop an index from a table
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, dropIndex)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *indexName, indexName_sub, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&indexName_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_ZVAL(indexName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	indexName = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "dropIndex", NULL, 0, &tableName_zv, &schemaName_zv, indexName);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Drops a table's primary key
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, dropPrimaryKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "dropPrimaryKey", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Drops a table from a schema/database
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, dropTable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool ifExists;
	zval tableName_zv, schemaName_zv, *ifExists_param = NULL, _0, _1, _2;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
		Z_PARAM_BOOL(ifExists)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		ifExists_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	if (!ifExists_param) {
		ifExists = 1;
	} else {
		}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	if (ifExists) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	ZEPHIR_CALL_METHOD(&_1, &_0, "dropTable", NULL, 0, &tableName_zv, &schemaName_zv, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Drops a view
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, dropView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool ifExists;
	zval viewName_zv, schemaName_zv, *ifExists_param = NULL, _0, _1, _2;
	zend_string *viewName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(viewName)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
		Z_PARAM_BOOL(ifExists)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		ifExists_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&viewName_zv);
	ZVAL_STR_COPY(&viewName_zv, viewName);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	if (!ifExists_param) {
		ifExists = 1;
	} else {
		}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	if (ifExists) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	ZEPHIR_CALL_METHOD(&_1, &_0, "dropView", NULL, 0, &viewName_zv, &schemaName_zv, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Escapes a column/table/schema name
 *
 *```php
 * $escapedTable = $connection->escapeIdentifier(
 *     "robots"
 * );
 *
 * $escapedTable = $connection->escapeIdentifier(
 *     [
 *         "store",
 *         "robots",
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, escapeIdentifier)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *identifier, identifier_sub, _0$$3, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&identifier_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(identifier)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &identifier);
	if (Z_TYPE_P(identifier) == IS_ARRAY) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
		zephir_memory_observe(&_2$$3);
		zephir_array_fetch_long(&_2$$3, identifier, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 569);
		ZEPHIR_CALL_METHOD(&_1$$3, &_0$$3, "escape", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
		zephir_memory_observe(&_5$$3);
		zephir_array_fetch_long(&_5$$3, identifier, 1, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 569);
		ZEPHIR_CALL_METHOD(&_4$$3, &_3$$3, "escape", NULL, 0, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VSV(return_value, &_1$$3, ".", &_4$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_6, "escape", NULL, 0, identifier);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Dumps the complete result of a query into an array
 *
 *```php
 * // Getting all robots with associative indexes only
 * $robots = $connection->fetchAll(
 *     "SELECT * FROM robots",
 *     \Phalcon\Db\Enum::FETCH_ASSOC
 * );
 *
 * foreach ($robots as $robot) {
 *     print_r($robot);
 * }
 *
 *  // Getting all robots that contains word "robot" withing the name
 * $robots = $connection->fetchAll(
 *     "SELECT * FROM robots WHERE name LIKE :name",
 *     \Phalcon\Db\Enum::FETCH_ASSOC,
 *     [
 *         "name" => "%robot%",
 *     ]
 * );
 * foreach($robots as $robot) {
 *     print_r($robot);
 * }
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, fetchAll)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval bindParams, bindTypes;
	zend_long fetchMode, ZEPHIR_LAST_CALL_STATUS;
	zval sqlQuery_zv, *fetchMode_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, result, _1, _0$$4;
	zend_string *sqlQuery = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlQuery_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(sqlQuery)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(fetchMode)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		fetchMode_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		bindParams_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		bindTypes_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&sqlQuery_zv);
	ZVAL_STR_COPY(&sqlQuery_zv, sqlQuery);
	if (!fetchMode_param) {
		fetchMode = 2;
	} else {
		}
	if (!bindParams_param) {
		ZEPHIR_INIT_VAR(&bindParams);
		array_init(&bindParams);
	} else {
		zephir_get_arrval(&bindParams, bindParams_param);
	}
	if (!bindTypes_param) {
		ZEPHIR_INIT_VAR(&bindTypes);
		array_init(&bindTypes);
	} else {
		zephir_get_arrval(&bindTypes, bindTypes_param);
	}
	ZEPHIR_CALL_METHOD(&result, this_ptr, "query", NULL, 0, &sqlQuery_zv, &bindParams, &bindTypes);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) != IS_OBJECT) {
		array_init(return_value);
		RETURN_MM();
	}
	if (UNEXPECTED(fetchMode == 7)) {
		ZVAL_LONG(&_0$$4, 7);
		ZEPHIR_RETURN_CALL_METHOD(&result, "fetchAll", NULL, 0, &_0$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZVAL_LONG(&_1, fetchMode);
	ZEPHIR_CALL_METHOD(NULL, &result, "setFetchMode", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&result, "fetchAll", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the n'th field of first row in a SQL query result
 *
 *```php
 * // Getting count of robots
 * $robotsCount = $connection->fetchColumn("SELECT count(*) FROM robots");
 * print_r($robotsCount);
 *
 * // Getting name of last edited robot
 * $robot = $connection->fetchColumn(
 *     "SELECT id, name FROM robots ORDER BY modified DESC",
 *     1
 * );
 * print_r($robot);
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, fetchColumn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval placeholders;
	zval sqlQuery_zv, *placeholders_param = NULL, *column = NULL, column_sub, row, columnValue, _0;
	zend_string *sqlQuery = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlQuery_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&columnValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&placeholders);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(sqlQuery)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(placeholders, placeholders_param)
		Z_PARAM_ZVAL(column)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		placeholders_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		column = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&sqlQuery_zv);
	ZVAL_STR_COPY(&sqlQuery_zv, sqlQuery);
	if (!placeholders_param) {
		ZEPHIR_INIT_VAR(&placeholders);
		array_init(&placeholders);
	} else {
		zephir_get_arrval(&placeholders, placeholders_param);
	}
	if (!column) {
		column = &column_sub;
		ZEPHIR_INIT_VAR(column);
		ZVAL_LONG(column, 0);
	}
	ZVAL_LONG(&_0, 4);
	ZEPHIR_CALL_METHOD(&row, this_ptr, "fetchOne", NULL, 0, &sqlQuery_zv, &_0, &placeholders);
	zephir_check_call_status();
	zephir_memory_observe(&columnValue);
	if (!(zephir_array_isset_fetch(&columnValue, &row, column, 0))) {
		RETURN_MM_BOOL(0);
	}
	RETURN_CCTOR(&columnValue);
}

/**
 * Returns the first row in a SQL query result
 *
 *```php
 * // Getting first robot
 * $robot = $connection->fetchOne("SELECT * FROM robots");
 * print_r($robot);
 *
 * // Getting first robot with associative indexes only
 * $robot = $connection->fetchOne(
 *     "SELECT * FROM robots",
 *     \Phalcon\Db\Enum::FETCH_ASSOC
 * );
 * print_r($robot);
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, fetchOne)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes;
	zval sqlQuery_zv, *fetchMode = NULL, fetchMode_sub, *bindParams_param = NULL, *bindTypes_param = NULL, result;
	zend_string *sqlQuery = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlQuery_zv);
	ZVAL_UNDEF(&fetchMode_sub);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(sqlQuery)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(fetchMode)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		fetchMode = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		bindParams_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		bindTypes_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&sqlQuery_zv);
	ZVAL_STR_COPY(&sqlQuery_zv, sqlQuery);
	if (!fetchMode) {
		fetchMode = &fetchMode_sub;
		ZEPHIR_INIT_VAR(fetchMode);
		ZVAL_LONG(fetchMode, 2);
	}
	if (!bindParams_param) {
		ZEPHIR_INIT_VAR(&bindParams);
		array_init(&bindParams);
	} else {
		zephir_get_arrval(&bindParams, bindParams_param);
	}
	if (!bindTypes_param) {
		ZEPHIR_INIT_VAR(&bindTypes);
		array_init(&bindTypes);
	} else {
		zephir_get_arrval(&bindTypes, bindTypes_param);
	}
	ZEPHIR_CALL_METHOD(&result, this_ptr, "query", NULL, 0, &sqlQuery_zv, &bindParams, &bindTypes);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) != IS_OBJECT) {
		array_init(return_value);
		RETURN_MM();
	}
	if (Z_TYPE_P(fetchMode) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, &result, "setFetchMode", NULL, 0, fetchMode);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(&result, "fetch", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns a SQL modified with a FOR UPDATE clause
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, forUpdate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval sqlQuery_zv, _0;
	zend_string *sqlQuery = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlQuery_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sqlQuery)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&sqlQuery_zv);
	ZVAL_STR_COPY(&sqlQuery_zv, sqlQuery);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "forUpdate", NULL, 0, &sqlQuery_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the SQL column definition from a column
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getColumnDefinition)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column, column_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &column);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getColumnDefinition", NULL, 0, column);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets a list of columns
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getColumnList)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *columnList, columnList_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&columnList_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(columnList)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &columnList);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getColumnList", NULL, 0, columnList);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets the active connection unique identifier
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getConnectionId)
{

	RETURN_MEMBER_TYPED(getThis(), "connectionId", IS_LONG);
}

/**
 * Returns the default identity value to be inserted in an identity column
 *
 *```php
 * // Inserting a new robot with a valid default value for the column 'id'
 * $success = $connection->insert(
 *     "robots",
 *     [
 *         $connection->getDefaultIdValue(),
 *         "Astro Boy",
 *         1952,
 *     ],
 *     [
 *         "id",
 *         "name",
 *         "year",
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getDefaultIdValue)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	object_init_ex(return_value, phalcon_db_rawvalue_ce);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "null");
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 35, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the default value to make the RBDM use the default value declared
 * in the table definition
 *
 *```php
 * // Inserting a new robot with a valid default value for the column 'year'
 * $success = $connection->insert(
 *     "robots",
 *     [
 *         "Astro Boy",
 *         $connection->getDefaultValue()
 *     ],
 *     [
 *         "name",
 *         "year",
 *     ]
 * );
 *```
 *
 * @todo Return NULL if this is not supported by the adapter
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getDefaultValue)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	object_init_ex(return_value, phalcon_db_rawvalue_ce);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "DEFAULT");
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 35, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return descriptor used to connect to the active database
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getDescriptor)
{

	RETURN_MEMBER_TYPED(getThis(), "descriptor", IS_ARRAY);
}

/**
 * Returns internal dialect instance
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getDialect)
{

	RETURN_MEMBER(getThis(), "dialect");
}

/**
 * Name of the dialect used
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getDialectType)
{

	RETURN_MEMBER_TYPED(getThis(), "dialectType", IS_STRING);
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Returns the savepoint name to use for nested transactions
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getNestedTransactionSavepointName)
{
	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transactionLevel", 16, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 59, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CONCAT_SV(return_value, "PHALCON_SAVEPOINT_", &_0);
	if (UNEXPECTED(EG(exception))) {
		return;
	}
	return;
}

/**
 * Active SQL statement in the object without replace bound parameters
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getRealSQLStatement)
{

	RETURN_MEMBER_TYPED(getThis(), "realSqlStatement", IS_STRING);
}

/**
 * Active SQL statement in the object
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getSQLBindTypes)
{

	RETURN_MEMBER_TYPED(getThis(), "sqlBindTypes", IS_ARRAY);
}

/**
 * Active SQL statement in the object
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getSQLStatement)
{

	RETURN_MEMBER_TYPED(getThis(), "sqlStatement", IS_STRING);
}

/**
 * Active SQL variables in the object
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getSQLVariables)
{

	RETURN_MEMBER_TYPED(getThis(), "sqlVariables", IS_ARRAY);
}

/**
 * Type of database system the adapter is used for
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, getType)
{

	RETURN_MEMBER_TYPED(getThis(), "type", IS_STRING);
}

/**
 * Inserts data into a table using custom RDBMS SQL syntax
 *
 * ```php
 * // Inserting a new robot
 * $success = $connection->insert(
 *     "robots",
 *     ["Astro Boy", 1952],
 *     ["name", "year"]
 * );
 *
 * // Next SQL sentence is sent to the database system
 * INSERT INTO `robots` (`name`, `year`) VALUES ("Astro boy", 1952);
 * ```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, insert)
{
	zval _1$$3, _6$$5, _7$$7, _13$$13, _14$$15;
	zend_bool _11, _5$$4, _12$$12, _24$$22;
	zend_ulong _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval values;
	zval table_zv, *values_param = NULL, *fields = NULL, fields_sub, *dataTypes = NULL, dataTypes_sub, __$null, bindDataTypes, bindType, escapedTable, escapedFields, field, insertSql, insertValues, joinedValues, placeholders, position, tableName, value, *_2, _10, _17, _18, _0$$3, _8$$8, _9$$9, _15$$16, _16$$17, *_19$$22, _20$$22, *_21$$22, _23$$22, _26$$22, _22$$23, _25$$24;
	zend_string *table = NULL, *_4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&dataTypes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&bindDataTypes);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&escapedTable);
	ZVAL_UNDEF(&escapedFields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&insertSql);
	ZVAL_UNDEF(&insertValues);
	ZVAL_UNDEF(&joinedValues);
	ZVAL_UNDEF(&placeholders);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&tableName);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_15$$16);
	ZVAL_UNDEF(&_16$$17);
	ZVAL_UNDEF(&_20$$22);
	ZVAL_UNDEF(&_23$$22);
	ZVAL_UNDEF(&_26$$22);
	ZVAL_UNDEF(&_22$$23);
	ZVAL_UNDEF(&_25$$24);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_13$$13);
	ZVAL_UNDEF(&_14$$15);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(table)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(fields)
		Z_PARAM_ZVAL_OR_NULL(dataTypes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		fields = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		dataTypes = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	if (!fields) {
		fields = &fields_sub;
		fields = &__$null;
	}
	if (!dataTypes) {
		dataTypes = &dataTypes_sub;
		dataTypes = &__$null;
	}
	if (UNEXPECTED(!(zephir_fast_count_int(&values)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_db_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SVS(&_1$$3, "Unable to insert into ", &table_zv, " without data");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 32, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Db/Adapter/AbstractAdapter.zep", 873);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&placeholders);
	array_init(&placeholders);
	ZEPHIR_INIT_VAR(&insertValues);
	array_init(&insertValues);
	ZEPHIR_INIT_VAR(&bindDataTypes);
	array_init(&bindDataTypes);
	zephir_is_iterable(&values, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 911);
	if (Z_TYPE_P(&values) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&values), _3, _4, _2)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_4 != NULL) { 
				ZVAL_STR_COPY(&position, _4);
			} else {
				ZVAL_LONG(&position, _3);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _2);
			_5$$4 = Z_TYPE_P(&value) == IS_OBJECT;
			if (_5$$4) {
				_5$$4 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
			}
			if (_5$$4) {
				zephir_cast_to_string(&_6$$5, &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&placeholders, &_6$$5, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 886);
			} else {
				if (Z_TYPE_P(&value) == IS_OBJECT) {
					zephir_cast_to_string(&_7$$7, &value);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CPY_WRT(&value, &_7$$7);
				}
				if (Z_TYPE_P(&value) == IS_NULL) {
					ZEPHIR_INIT_NVAR(&_8$$8);
					ZVAL_STRING(&_8$$8, "null");
					zephir_array_append(&placeholders, &_8$$8, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 893);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$9);
					ZVAL_STRING(&_9$$9, "?");
					zephir_array_append(&placeholders, &_9$$9, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 895);
					zephir_array_append(&insertValues, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 896);
					if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&bindType);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, dataTypes, &position, 0)))) {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Incomplete number of bind types", "phalcon/Db/Adapter/AbstractAdapter.zep", 902);
							return;
						}
						zephir_array_append(&bindDataTypes, &bindType, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 905);
					}
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &values, "rewind", NULL, 0);
		zephir_check_call_status();
		_11 = 1;
		while (1) {
			if (_11) {
				_11 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &values, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_10, &values, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&position, &values, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &values, "current", NULL, 0);
			zephir_check_call_status();
				_12$$12 = Z_TYPE_P(&value) == IS_OBJECT;
				if (_12$$12) {
					_12$$12 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
				}
				if (_12$$12) {
					zephir_cast_to_string(&_13$$13, &value);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&placeholders, &_13$$13, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 886);
				} else {
					if (Z_TYPE_P(&value) == IS_OBJECT) {
						zephir_cast_to_string(&_14$$15, &value);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CPY_WRT(&value, &_14$$15);
					}
					if (Z_TYPE_P(&value) == IS_NULL) {
						ZEPHIR_INIT_NVAR(&_15$$16);
						ZVAL_STRING(&_15$$16, "null");
						zephir_array_append(&placeholders, &_15$$16, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 893);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$17);
						ZVAL_STRING(&_16$$17, "?");
						zephir_array_append(&placeholders, &_16$$17, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 895);
						zephir_array_append(&insertValues, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 896);
						if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
							ZEPHIR_OBS_NVAR(&bindType);
							if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, dataTypes, &position, 0)))) {
								ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Incomplete number of bind types", "phalcon/Db/Adapter/AbstractAdapter.zep", 902);
								return;
							}
							zephir_array_append(&bindDataTypes, &bindType, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 905);
						}
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&position);
	ZEPHIR_INIT_VAR(&_17);
	ZVAL_STRING(&_17, ".");
	ZEPHIR_INIT_VAR(&_18);
	zephir_fast_strpos(&_18, &table_zv, &_17, 0 );
	if (ZEPHIR_GT_LONG(&_18, 0)) {
		ZEPHIR_INIT_VAR(&tableName);
		zephir_fast_explode_str(&tableName, SL("."), &table_zv, NULL);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CPY_WRT(&tableName, &table_zv);
	}
	ZEPHIR_CALL_METHOD(&escapedTable, this_ptr, "escapeIdentifier", NULL, 0, &tableName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&joinedValues);
	zephir_fast_join_str(&joinedValues, SL(", "), &placeholders);
	ZEPHIR_INIT_VAR(&insertSql);
	if (Z_TYPE_P(fields) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&escapedFields);
		array_init(&escapedFields);
		if (Z_TYPE_P(fields) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_20$$22);
			zephir_string_to_char_array(&_20$$22, fields);
			_19$$22 = &_20$$22;
		} else {
			_19$$22 = fields;
		}
		zephir_is_iterable(_19$$22, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 931);
		if (Z_TYPE_P(_19$$22) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_19$$22), _21$$22)
			{
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _21$$22);
				ZEPHIR_CALL_METHOD(&_22$$23, this_ptr, "escapeIdentifier", NULL, 0, &field);
				zephir_check_call_status();
				zephir_array_append(&escapedFields, &_22$$23, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 928);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _19$$22, "rewind", NULL, 0);
			zephir_check_call_status();
			_24$$22 = 1;
			while (1) {
				if (_24$$22) {
					_24$$22 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _19$$22, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_23$$22, _19$$22, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_23$$22)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _19$$22, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_25$$24, this_ptr, "escapeIdentifier", NULL, 0, &field);
					zephir_check_call_status();
					zephir_array_append(&escapedFields, &_25$$24, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 928);
			}
		}
		ZEPHIR_INIT_NVAR(&field);
		ZEPHIR_INIT_VAR(&_26$$22);
		zephir_fast_join_str(&_26$$22, SL(", "), &escapedFields);
		ZEPHIR_CONCAT_SVSVSVS(&insertSql, "INSERT INTO ", &escapedTable, " (", &_26$$22, ") VALUES (", &joinedValues, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CONCAT_SVSVS(&insertSql, "INSERT INTO ", &escapedTable, " VALUES (", &joinedValues, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (!(zephir_fast_count_int(&bindDataTypes))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &insertSql, &insertValues);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &insertSql, &insertValues, &bindDataTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Inserts data into a table using custom RBDM SQL syntax
 *
 * ```php
 * // Inserting a new robot
 * $success = $connection->insertAsDict(
 *     "robots",
 *     [
 *         "name" => "Astro Boy",
 *         "year" => 1952,
 *     ]
 * );
 *
 * // Next SQL sentence is sent to the database system
 * INSERT INTO `robots` (`name`, `year`) VALUES ("Astro boy", 1952);
 * ```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, insertAsDict)
{
	zend_ulong _4;
	zend_bool _0, _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, *data, data_sub, *dataTypes = NULL, dataTypes_sub, __$null, values, fields, field, value, *_1, _2, *_3, _6;
	zend_string *table = NULL, *_5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&dataTypes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(table)
		Z_PARAM_ZVAL(data)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(dataTypes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	data = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		dataTypes = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!dataTypes) {
		dataTypes = &dataTypes_sub;
		dataTypes = &__$null;
	}
	ZEPHIR_INIT_VAR(&values);
	array_init(&values);
	ZEPHIR_INIT_VAR(&fields);
	array_init(&fields);
	_0 = Z_TYPE_P(data) != IS_ARRAY;
	if (!(_0)) {
		_0 = ZEPHIR_IS_EMPTY(data);
	}
	if (_0) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(data) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, data);
		_1 = &_2;
	} else {
		_1 = data;
	}
	zephir_is_iterable(_1, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 977);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&field);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&field, _5);
			} else {
				ZVAL_LONG(&field, _4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 973);
			zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 974);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _1, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 973);
				zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 974);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&field);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "insert", NULL, 0, &table_zv, &values, &fields, dataTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns if nested transactions should use savepoints
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, isNestedTransactionsWithSavepoints)
{

	RETURN_MEMBER(getThis(), "transactionsWithSavepoints");
}

/**
 * Appends a LIMIT clause to $sqlQuery argument
 *
 * ```php
 * echo $connection->limit("SELECT * FROM robots", 5);
 * ```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, limit)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long number, ZEPHIR_LAST_CALL_STATUS;
	zval sqlQuery_zv, *number_param = NULL, _0, _1;
	zend_string *sqlQuery = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlQuery_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(sqlQuery)
		Z_PARAM_LONG(number)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	number_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&sqlQuery_zv);
	ZVAL_STR_COPY(&sqlQuery_zv, sqlQuery);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, number);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "limit", NULL, 0, &sqlQuery_zv, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * List all tables on a database
 *
 *```php
 * print_r(
 *     $connection->listTables("blog")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, listTables)
{
	zend_bool _8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval schemaName_zv, tables, table, allTables, _0, _1, _2, *_3, _4, *_5, _7, _6$$3, _9$$4;
	zend_string *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&allTables);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_9$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	ZEPHIR_INIT_VAR(&allTables);
	array_init(&allTables);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "listTables", NULL, 0, &schemaName_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 3);
	ZEPHIR_CALL_METHOD(&tables, this_ptr, "fetchAll", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	if (Z_TYPE_P(&tables) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4);
		zephir_string_to_char_array(&_4, &tables);
		_3 = &_4;
	} else {
		_3 = &tables;
	}
	zephir_is_iterable(_3, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 1024);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&table);
			ZVAL_COPY(&table, _5);
			ZEPHIR_OBS_NVAR(&_6$$3);
			zephir_array_fetch_long(&_6$$3, &table, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1021);
			zephir_array_append(&allTables, &_6$$3, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1021);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&table, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_9$$4);
				zephir_array_fetch_long(&_9$$4, &table, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1021);
				zephir_array_append(&allTables, &_9$$4, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1021);
		}
	}
	ZEPHIR_INIT_NVAR(&table);
	RETURN_CCTOR(&allTables);
}

/**
 * List all views on a database
 *
 *```php
 * print_r(
 *     $connection->listViews("blog")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, listViews)
{
	zend_bool _8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval schemaName_zv, tables, table, allTables, _0, _1, _2, *_3, _4, *_5, _7, _6$$3, _9$$4;
	zend_string *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&allTables);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_9$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	ZEPHIR_INIT_VAR(&allTables);
	array_init(&allTables);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "listViews", NULL, 0, &schemaName_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 3);
	ZEPHIR_CALL_METHOD(&tables, this_ptr, "fetchAll", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	if (Z_TYPE_P(&tables) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4);
		zephir_string_to_char_array(&_4, &tables);
		_3 = &_4;
	} else {
		_3 = &tables;
	}
	zephir_is_iterable(_3, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 1051);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&table);
			ZVAL_COPY(&table, _5);
			ZEPHIR_OBS_NVAR(&_6$$3);
			zephir_array_fetch_long(&_6$$3, &table, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1048);
			zephir_array_append(&allTables, &_6$$3, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1048);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&table, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_9$$4);
				zephir_array_fetch_long(&_9$$4, &table, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1048);
				zephir_array_append(&allTables, &_9$$4, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1048);
		}
	}
	ZEPHIR_INIT_NVAR(&table);
	RETURN_CCTOR(&allTables);
}

/**
 * Modifies a table column based on a definition
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, modifyColumn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, *currentColumn = NULL, currentColumn_sub, __$null, _0, _1;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&currentColumn_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(currentColumn, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	column = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		currentColumn = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	if (!currentColumn) {
		currentColumn = &currentColumn_sub;
		currentColumn = &__$null;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "modifyColumn", NULL, 0, &tableName_zv, &schemaName_zv, column, currentColumn);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Releases given savepoint
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, releaseSavepoint)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, dialect, _0, _1, _2, _3;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&dialect, &_0);
	ZEPHIR_CALL_METHOD(&_1, &dialect, "supportsSavePoints", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter", "phalcon/Db/Adapter/AbstractAdapter.zep", 1081);
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, &dialect, "supportsReleaseSavePoints", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_2))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&_3, &dialect, "releaseSavepoint", NULL, 0, &name_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Rollbacks given savepoint
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, rollbackSavepoint)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, dialect, _0, _1, _2;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&dialect, &_0);
	ZEPHIR_CALL_METHOD(&_1, &dialect, "supportsSavePoints", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter", "phalcon/Db/Adapter/AbstractAdapter.zep", 1105);
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, &dialect, "rollbackSavepoint", NULL, 0, &name_zv);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Sets the event manager
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, setEventsManager)
{
	zval *eventsManager, eventsManager_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventsManager_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("eventsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(eventsManager, phalcon_events_managerinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &eventsManager);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 60, eventsManager);
}

/**
 * Sets the dialect used to produce the SQL
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, setDialect)
{
	zval *dialect, dialect_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&dialect_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(dialect, phalcon_db_dialectinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &dialect);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 57, dialect);
}

/**
 * Set if nested transactions should use savepoints
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, setNestedTransactionsWithSavepoints)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *nestedTransactionsWithSavepoints_param = NULL, __$true, __$false, _0, _1, _2;
	zend_bool nestedTransactionsWithSavepoints;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transactionLevel", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("dialect", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("transactionsWithSavepoints", 26, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(nestedTransactionsWithSavepoints)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &nestedTransactionsWithSavepoints_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 59, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(ZEPHIR_GT_LONG(&_0, 0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Nested transaction with savepoints behavior cannot be changed while a transaction is open", "phalcon/Db/Adapter/AbstractAdapter.zep", 1137);
		return;
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "supportsSavePoints", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_2))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter", "phalcon/Db/Adapter/AbstractAdapter.zep", 1143);
		return;
	}
	if (nestedTransactionsWithSavepoints) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 61, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 61, &__$false);
	}
	RETURN_THIS();
}

/**
 * Enables/disables options in the Database component
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, setup)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *options_param = NULL, escapeIdentifiers, forceCasting, _0$$3, _1$$4;
	zval options;

	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&escapeIdentifiers);
	ZVAL_UNDEF(&forceCasting);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &options_param);
	ZEPHIR_OBS_COPY_OR_DUP(&options, options_param);
	zephir_memory_observe(&escapeIdentifiers);
	if (zephir_array_isset_string_fetch(&escapeIdentifiers, &options, SL("escapeSqlIdentifiers"), 0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "db.escape_identifiers");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_0$$3, &escapeIdentifiers);
		zephir_check_call_status();
	}
	zephir_memory_observe(&forceCasting);
	if (zephir_array_isset_string_fetch(&forceCasting, &options, SL("forceCasting"), 0)) {
		ZEPHIR_INIT_VAR(&_1$$4);
		ZVAL_STRING(&_1$$4, "db.force_casting");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_1$$4, &forceCasting);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns a SQL modified with a LOCK IN SHARE MODE clause
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, sharedLock)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval sqlQuery_zv, _0;
	zend_string *sqlQuery = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlQuery_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sqlQuery)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&sqlQuery_zv);
	ZVAL_STR_COPY(&sqlQuery_zv, sqlQuery);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "sharedLock", NULL, 0, &sqlQuery_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check whether the database system requires a sequence to produce
 * auto-numeric values
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, supportSequences)
{

	RETURN_BOOL(0);
}

/**
 * Generates SQL checking for the existence of a schema.table
 *
 *```php
 * var_dump(
 *     $connection->tableExists("blog", "posts")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, tableExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, _0, _1, _2, _3, _4;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(tableName)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "tableExists", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchOne", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	zephir_memory_observe(&_4);
	zephir_array_fetch_long(&_4, &_0, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1201);
	RETURN_MM_BOOL(ZEPHIR_GT_LONG(&_4, 0));
}

/**
 * Gets creation options from a table
 *
 *```php
 * print_r(
 *     $connection->tableOptions("robots")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, tableOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, sql, _0, _1, _2, _3;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(tableName)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
		zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&sql, &_0, "tableOptions", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	if (!(zephir_is_true(&sql))) {
		array_init(return_value);
		RETURN_MM();
	}
	ZVAL_LONG(&_2, 2);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "fetchAll", NULL, 0, &sql, &_2);
	zephir_check_call_status();
	zephir_memory_observe(&_3);
	zephir_array_fetch_long(&_3, &_1, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1223);
	RETURN_CCTOR(&_3);
}

/**
 * Updates data on a table using custom RBDM SQL syntax
 *
 * ```php
 * // Updating existing robot
 * $success = $connection->update(
 *     "robots",
 *     ["name"],
 *     ["New Astro Boy"],
 *     "id = 101"
 * );
 *
 * // Next SQL sentence is sent to the database system
 * UPDATE `robots` SET `name` = "Astro boy" WHERE id = 101
 *
 * // Updating existing robot with array condition and $dataTypes
 * $success = $connection->update(
 *     "robots",
 *     ["name"],
 *     ["New Astro Boy"],
 *     [
 *         "conditions" => "id = ?",
 *         "bind"       => [$some_unsafe_id],
 *         "bindTypes"  => [PDO::PARAM_INT], // use only if you use $dataTypes param
 *     ],
 *     [
 *         PDO::PARAM_STR
 *     ]
 * );
 *
 * ```
 *
 * Warning! If $whereCondition is string it not escaped.
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, update)
{
	zval _7$$5, _9$$7, _15$$14, _17$$16;
	zend_bool _13, _6$$3, _14$$12;
	zend_ulong _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, *fields, fields_sub, *values, values_sub, *whereCondition = NULL, whereCondition_sub, *dataTypes = NULL, dataTypes_sub, __$null, bindDataTypes, bindType, conditions, escapedField, escapedTable, field, placeholders, position, setClause, tableName, updateSql, updateValues, value, whereBind, whereTypes, *_0, _1, *_2, _12, _20, _21, _8$$5, _10$$8, _11$$9, _16$$14, _18$$17, _19$$18;
	zend_string *table = NULL, *_4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&values_sub);
	ZVAL_UNDEF(&whereCondition_sub);
	ZVAL_UNDEF(&dataTypes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&bindDataTypes);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&escapedField);
	ZVAL_UNDEF(&escapedTable);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&placeholders);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&setClause);
	ZVAL_UNDEF(&tableName);
	ZVAL_UNDEF(&updateSql);
	ZVAL_UNDEF(&updateValues);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&whereBind);
	ZVAL_UNDEF(&whereTypes);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_16$$14);
	ZVAL_UNDEF(&_18$$17);
	ZVAL_UNDEF(&_19$$18);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_15$$14);
	ZVAL_UNDEF(&_17$$16);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_STR(table)
		Z_PARAM_ZVAL(fields)
		Z_PARAM_ZVAL(values)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(whereCondition)
		Z_PARAM_ZVAL_OR_NULL(dataTypes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	fields = ZEND_CALL_ARG(execute_data, 2);
	values = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		whereCondition = ZEND_CALL_ARG(execute_data, 4);
	}
	if (ZEND_NUM_ARGS() > 4) {
		dataTypes = ZEND_CALL_ARG(execute_data, 5);
	}
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!whereCondition) {
		whereCondition = &whereCondition_sub;
		whereCondition = &__$null;
	}
	if (!dataTypes) {
		dataTypes = &dataTypes_sub;
		dataTypes = &__$null;
	}
	ZEPHIR_INIT_VAR(&placeholders);
	array_init(&placeholders);
	ZEPHIR_INIT_VAR(&updateValues);
	array_init(&updateValues);
	ZEPHIR_INIT_VAR(&bindDataTypes);
	array_init(&bindDataTypes);
	if (Z_TYPE_P(values) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_1);
		zephir_string_to_char_array(&_1, values);
		_0 = &_1;
	} else {
		_0 = values;
	}
	zephir_is_iterable(_0, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 1313);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_0), _3, _4, _2)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_4 != NULL) { 
				ZVAL_STR_COPY(&position, _4);
			} else {
				ZVAL_LONG(&position, _3);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _2);
			ZEPHIR_OBS_NVAR(&field);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&field, fields, &position, 0)))) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The number of values in the update is not the same as fields", "phalcon/Db/Adapter/AbstractAdapter.zep", 1278);
				return;
			}
			ZEPHIR_CALL_METHOD(&escapedField, this_ptr, "escapeIdentifier", &_5, 0, &field);
			zephir_check_call_status();
			_6$$3 = Z_TYPE_P(&value) == IS_OBJECT;
			if (_6$$3) {
				_6$$3 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
			}
			if (_6$$3) {
				zephir_cast_to_string(&_7$$5, &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_8$$5);
				ZEPHIR_CONCAT_VSV(&_8$$5, &escapedField, " = ", &_7$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&placeholders, &_8$$5, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1284);
			} else {
				if (Z_TYPE_P(&value) == IS_OBJECT) {
					zephir_cast_to_string(&_9$$7, &value);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CPY_WRT(&value, &_9$$7);
				}
				if (Z_TYPE_P(&value) == IS_NULL) {
					ZEPHIR_INIT_NVAR(&_10$$8);
					ZEPHIR_CONCAT_VS(&_10$$8, &escapedField, " = null");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&placeholders, &_10$$8, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1291);
				} else {
					zephir_array_append(&updateValues, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1293);
					if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&bindType);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, dataTypes, &position, 0)))) {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Incomplete number of bind types", "phalcon/Db/Adapter/AbstractAdapter.zep", 1299);
							return;
						}
						zephir_array_append(&bindDataTypes, &bindType, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1302);
					}
					ZEPHIR_INIT_NVAR(&_11$$9);
					ZEPHIR_CONCAT_VS(&_11$$9, &escapedField, " = ?");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&placeholders, &_11$$9, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1305);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _0, "rewind", NULL, 0);
		zephir_check_call_status();
		_13 = 1;
		while (1) {
			if (_13) {
				_13 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_12, _0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_12)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&position, _0, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&field);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&field, fields, &position, 0)))) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The number of values in the update is not the same as fields", "phalcon/Db/Adapter/AbstractAdapter.zep", 1278);
					return;
				}
				ZEPHIR_CALL_METHOD(&escapedField, this_ptr, "escapeIdentifier", &_5, 0, &field);
				zephir_check_call_status();
				_14$$12 = Z_TYPE_P(&value) == IS_OBJECT;
				if (_14$$12) {
					_14$$12 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
				}
				if (_14$$12) {
					zephir_cast_to_string(&_15$$14, &value);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_16$$14);
					ZEPHIR_CONCAT_VSV(&_16$$14, &escapedField, " = ", &_15$$14);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&placeholders, &_16$$14, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1284);
				} else {
					if (Z_TYPE_P(&value) == IS_OBJECT) {
						zephir_cast_to_string(&_17$$16, &value);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CPY_WRT(&value, &_17$$16);
					}
					if (Z_TYPE_P(&value) == IS_NULL) {
						ZEPHIR_INIT_NVAR(&_18$$17);
						ZEPHIR_CONCAT_VS(&_18$$17, &escapedField, " = null");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&placeholders, &_18$$17, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1291);
					} else {
						zephir_array_append(&updateValues, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1293);
						if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
							ZEPHIR_OBS_NVAR(&bindType);
							if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, dataTypes, &position, 0)))) {
								ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Incomplete number of bind types", "phalcon/Db/Adapter/AbstractAdapter.zep", 1299);
								return;
							}
							zephir_array_append(&bindDataTypes, &bindType, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1302);
						}
						ZEPHIR_INIT_NVAR(&_19$$18);
						ZEPHIR_CONCAT_VS(&_19$$18, &escapedField, " = ?");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&placeholders, &_19$$18, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1305);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&position);
	ZEPHIR_INIT_VAR(&_20);
	ZVAL_STRING(&_20, ".");
	ZEPHIR_INIT_VAR(&_21);
	zephir_fast_strpos(&_21, &table_zv, &_20, 0 );
	if (ZEPHIR_GT_LONG(&_21, 0)) {
		ZEPHIR_INIT_VAR(&tableName);
		zephir_fast_explode_str(&tableName, SL("."), &table_zv, NULL);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CPY_WRT(&tableName, &table_zv);
	}
	ZEPHIR_CALL_METHOD(&escapedTable, this_ptr, "escapeIdentifier", &_5, 0, &tableName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&setClause);
	zephir_fast_join_str(&setClause, SL(", "), &placeholders);
	ZEPHIR_INIT_VAR(&updateSql);
	if (Z_TYPE_P(whereCondition) != IS_NULL) {
		ZEPHIR_CONCAT_SVSVS(&updateSql, "UPDATE ", &escapedTable, " SET ", &setClause, " WHERE ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (Z_TYPE_P(whereCondition) == IS_STRING) {
			zephir_concat_self(&updateSql, whereCondition);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			if (UNEXPECTED(Z_TYPE_P(whereCondition) != IS_ARRAY)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Invalid WHERE clause conditions", "phalcon/Db/Adapter/AbstractAdapter.zep", 1336);
				return;
			}
			zephir_memory_observe(&conditions);
			if (zephir_array_isset_string_fetch(&conditions, whereCondition, SL("conditions"), 0)) {
				zephir_concat_self(&updateSql, &conditions);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			zephir_memory_observe(&whereBind);
			if (zephir_array_isset_string_fetch(&whereBind, whereCondition, SL("bind"), 0)) {
				zephir_merge_append(&updateValues, &whereBind);
			}
			zephir_memory_observe(&whereTypes);
			if (zephir_array_isset_string_fetch(&whereTypes, whereCondition, SL("bindTypes"), 0)) {
				zephir_merge_append(&bindDataTypes, &whereTypes);
			}
		}
	} else {
		ZEPHIR_CONCAT_SVSV(&updateSql, "UPDATE ", &escapedTable, " SET ", &setClause);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (!(zephir_fast_count_int(&bindDataTypes))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &updateSql, &updateValues);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &updateSql, &updateValues, &bindDataTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Updates data on a table using custom RBDM SQL syntax
 * Another, more convenient syntax
 *
 * ```php
 * // Updating existing robot
 * $success = $connection->updateAsDict(
 *     "robots",
 *     [
 *         "name" => "New Astro Boy",
 *     ],
 *     "id = 101"
 * );
 *
 * // Next SQL sentence is sent to the database system
 * UPDATE `robots` SET `name` = "Astro boy" WHERE id = 101
 * ```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, updateAsDict)
{
	zend_ulong _4;
	zend_bool _0, _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, *data, data_sub, *whereCondition = NULL, whereCondition_sub, *dataTypes = NULL, dataTypes_sub, __$null, values, fields, field, value, *_1, _2, *_3, _6;
	zend_string *table = NULL, *_5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&whereCondition_sub);
	ZVAL_UNDEF(&dataTypes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(table)
		Z_PARAM_ZVAL(data)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(whereCondition)
		Z_PARAM_ZVAL_OR_NULL(dataTypes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	data = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		whereCondition = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		dataTypes = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!whereCondition) {
		whereCondition = &whereCondition_sub;
		whereCondition = &__$null;
	}
	if (!dataTypes) {
		dataTypes = &dataTypes_sub;
		dataTypes = &__$null;
	}
	ZEPHIR_INIT_VAR(&values);
	array_init(&values);
	ZEPHIR_INIT_VAR(&fields);
	array_init(&fields);
	_0 = Z_TYPE_P(data) != IS_ARRAY;
	if (!(_0)) {
		_0 = ZEPHIR_IS_EMPTY(data);
	}
	if (_0) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(data) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, data);
		_1 = &_2;
	} else {
		_1 = data;
	}
	zephir_is_iterable(_1, 0, "phalcon/Db/Adapter/AbstractAdapter.zep", 1409);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&field);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&field, _5);
			} else {
				ZVAL_LONG(&field, _4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1405);
			zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1406);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _1, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1405);
				zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Db/Adapter/AbstractAdapter.zep", 1406);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&field);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "update", NULL, 0, &table_zv, &fields, &values, whereCondition, dataTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check whether the database system requires an explicit value for identity
 * columns
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, useExplicitIdValue)
{

	RETURN_BOOL(0);
}

/**
 * Check whether the database system support the DEFAULT
 * keyword (SQLite does not support it)
 *
 * @deprecated Will re removed in the next version
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, supportsDefaultValue)
{

	RETURN_BOOL(1);
}

/**
 * Generates SQL checking for the existence of a schema.view
 *
 *```php
 * var_dump(
 *     $connection->viewExists("active_users", "posts")
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_AbstractAdapter, viewExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval viewName_zv, schemaName_zv, _0, _1, _2, _3, _4;
	zend_string *viewName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(viewName)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(schemaName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&viewName_zv);
	ZVAL_STR_COPY(&viewName_zv, viewName);
	if (!schemaName) {
		ZEPHIR_INIT_VAR(&schemaName_zv);
	} else {
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 57, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "viewExists", NULL, 0, &viewName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchOne", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	zephir_memory_observe(&_4);
	zephir_array_fetch_long(&_4, &_0, 0, PH_NOISY, "phalcon/Db/Adapter/AbstractAdapter.zep", 1442);
	RETURN_MM_BOOL(ZEPHIR_GT_LONG(&_4, 0));
}

zend_object *zephir_init_properties_Phalcon_Db_Adapter_AbstractAdapter(zend_class_entry *class_type)
{
		zval _0, _2, _4, _1$$3, _3$$4, _5$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("sqlVariables"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlVariables"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("sqlBindTypes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlBindTypes"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("descriptor"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("descriptor"), &_5$$5);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

