
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
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/pdo/php_pdo_driver.h"
#include "kernel/string.h"
#include "phalcon/mvc/model/orm.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Model\Query
 *
 * This class takes a PHQL intermediate representation and executes it.
 *
 *```php
 * $phql = "SELECT c.price*0.16 AS taxes, c.* FROM Cars AS c JOIN Brands AS b
 *          WHERE b.name = :name: ORDER BY c.name";
 *
 * $result = $manager->executeQuery(
 *     $phql,
 *     [
 *         "name" => "Lamborghini",
 *     ]
 * );
 *
 * foreach ($result as $row) {
 *     echo "Name: ",  $row->cars->name, "\n";
 *     echo "Price: ", $row->cars->price, "\n";
 *     echo "Taxes: ", $row->taxes, "\n";
 * }
 *
 * // with transaction
 * use Phalcon\Mvc\Model\Query;
 * use Phalcon\Mvc\Model\Transaction;
 *
 * // $di needs to have the service "db" registered for this to work
 * $di = Phalcon\Di\FactoryDefault::getDefault();
 *
 * $phql = 'SELECT * FROM robot';
 *
 * $myTransaction = new Transaction($di);
 * $myTransaction->begin();
 *
 * $newRobot = new Robot();
 * $newRobot->setTransaction($myTransaction);
 * $newRobot->type = "mechanical";
 * $newRobot->name = "Astro Boy";
 * $newRobot->year = 1952;
 * $newRobot->save();
 *
 * $queryWithTransaction = new Query($phql, $di);
 * $queryWithTransaction->setTransaction($myTransaction);
 *
 * $resultWithEntries = $queryWithTransaction->execute();
 *
 * $queryWithOutTransaction = new Query($phql, $di);
 * $resultWithOutEntries = $queryWithTransaction->execute();
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Query)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\Model, Query, phalcon, mvc_model_query, phalcon_mvc_model_query_method_entry, 0);

	/**
	 * @var array
	 * TODO: Add default value, instead of null, also remove type check
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("ast"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("bindParams"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("bindTypes"), ZEND_ACC_PROTECTED);
	/**
	 * @var mixed|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("cache"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("cacheOptions"), ZEND_ACC_PROTECTED);
	/**
	 * @var DiInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("container"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("enableImplicitJoins"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("intermediate"), ZEND_ACC_PROTECTED);
	/**
	 * @var \Phalcon\Mvc\Model\ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("manager"), ZEND_ACC_PROTECTED);
	/**
	 * @var \Phalcon\Mvc\Model\MetaDataInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("metaData"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("models"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("modelsInstances"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_model_query_ce, SL("nestingLevel"), -1, ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("phql"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_query_ce, SL("sharedLock"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("sqlAliases"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("sqlAliasesModels"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("sqlAliasesModelsInstances"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("sqlColumnAliases"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("sqlModelsAliases"), ZEND_ACC_PROTECTED);
	/**
	 * @var int|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("type"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_query_ce, SL("uniqueRow"), 0, ZEND_ACC_PROTECTED);
	/**
	 * TransactionInterface so that the query can wrap a transaction
	 * around batch updates and intermediate selects within the transaction.
	 * however if a model got a transaction set inside it will use the local
	 * transaction instead of this one
	 *
	 * @var TransactionInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("transaction"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_ce, SL("internalPhqlCache"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC);
	phalcon_mvc_model_query_ce->create_object = zephir_init_properties_Phalcon_Mvc_Model_Query;
	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_query_ce, SL("TYPE_DELETE"), 303);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_query_ce, SL("TYPE_INSERT"), 306);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_query_ce, SL("TYPE_SELECT"), 309);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_query_ce, SL("TYPE_UPDATE"), 300);

	zend_class_implements(phalcon_mvc_model_query_ce, 1, phalcon_mvc_model_queryinterface_ce);
	zend_class_implements(phalcon_mvc_model_query_ce, 1, phalcon_di_injectionawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Query constructor
 *
 * @param string|null phql
 * @param DiInterface|null container
 * @param array options
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval options;
	zval phql_zv, *container = NULL, container_sub, *options_param = NULL, __$true, __$false, __$null, enableImplicitJoins, _2, _3, _0$$5, _1$$5;
	zend_string *phql = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&phql_zv);
	ZVAL_UNDEF(&container_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&enableImplicitJoins);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("phql", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("enableImplicitJoins", 19, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("bindTypes", 9, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(phql)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		container = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		options_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (!phql) {
		ZEPHIR_INIT_VAR(&phql_zv);
	} else {
		zephir_memory_observe(&phql_zv);
	ZVAL_STR_COPY(&phql_zv, phql);
	}
	if (!container) {
		container = &container_sub;
		container = &__$null;
	}
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 761, &phql_zv);
	if (Z_TYPE_P(container) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setDI", NULL, 0, container);
		zephir_check_call_status();
	}
	zephir_memory_observe(&enableImplicitJoins);
	if (zephir_array_isset_string_fetch(&enableImplicitJoins, &options, SL("enable_implicit_joins"), 0)) {
		if (ZEPHIR_IS_TRUE(&enableImplicitJoins)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 762, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 762, &__$false);
		}
	} else {
		ZEPHIR_INIT_VAR(&_1$$5);
		ZVAL_STRING(&_1$$5, "orm.enable_implicit_joins");
		ZEPHIR_CALL_CE_STATIC(&_0$$5, phalcon_support_settings_ce, "get", NULL, 0, &_1$$5);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 762, &_0$$5);
	}
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 763, &_2);
	ZEPHIR_INIT_VAR(&_3);
	array_init(&_3);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 764, &_3);
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the cache parameters of the query
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, cache)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *cacheOptions_param = NULL;
	zval cacheOptions;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&cacheOptions);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("cacheOptions", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(cacheOptions, cacheOptions_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &cacheOptions_param);
	zephir_get_arrval(&cacheOptions, cacheOptions_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 765, &cacheOptions);
	RETURN_THIS();
}

/**
 * Destroys the internal PHQL cache
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, clean)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_static_property_ce(phalcon_mvc_model_query_ce, ZEND_STRL("internalPhqlCache"), &_0);
	ZEPHIR_MM_RESTORE();
}

/**
 * Executes a parsed PHQL statement
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, execute)
{
	zval _5$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *bindParams_param = NULL, *bindTypes_param = NULL, adapter, cache, cacheLifetime, cacheOptions, cacheService, defaultBindParams, defaultBindTypes, intermediate, key, lifetime, mergedParams, mergedTypes, preparedResult, result, type, uniqueRow, _0, _1$$3, _2$$3, _3$$3, _6$$3, _4$$7, _7$$10, _8$$20, _9$$20;
	zval bindParams, bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&adapter);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&cacheLifetime);
	ZVAL_UNDEF(&cacheOptions);
	ZVAL_UNDEF(&cacheService);
	ZVAL_UNDEF(&defaultBindParams);
	ZVAL_UNDEF(&defaultBindTypes);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&lifetime);
	ZVAL_UNDEF(&mergedParams);
	ZVAL_UNDEF(&mergedTypes);
	ZVAL_UNDEF(&preparedResult);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&uniqueRow);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_8$$20);
	ZVAL_UNDEF(&_9$$20);
	ZVAL_UNDEF(&_5$$7);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uniqueRow", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("cacheOptions", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("bindTypes", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("type", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &bindParams_param, &bindTypes_param);
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
	ZEPHIR_INIT_VAR(&cache);
	ZEPHIR_INIT_VAR(&key);
	ZEPHIR_INIT_VAR(&lifetime);
	ZEPHIR_INIT_VAR(&result);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 766, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&uniqueRow, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 765, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&cacheOptions, &_0);
	if (Z_TYPE_P(&cacheOptions) != IS_NULL) {
		if (UNEXPECTED(Z_TYPE_P(&cacheOptions) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Invalid caching options", "phalcon/Mvc/Model/Query.zep", 287);
			return;
		}
		ZEPHIR_OBS_NVAR(&key);
		if (UNEXPECTED(!(zephir_array_isset_string_fetch(&key, &cacheOptions, SL("key"), 0)))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "A cache key must be provided to identify the cached resultset in the cache backend", "phalcon/Mvc/Model/Query.zep", 296);
			return;
		}
		zephir_memory_observe(&cacheService);
		if (!(zephir_array_isset_string_fetch(&cacheService, &cacheOptions, SL("service"), 0))) {
			ZEPHIR_INIT_NVAR(&cacheService);
			ZVAL_STRING(&cacheService, "modelsCache");
		}
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_2, 767, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&cache, &_1$$3, "getShared", NULL, 0, &cacheService);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Phalcon\\Cache\\CacheInterface");
		ZEPHIR_CALL_FUNCTION(&_3$$3, "is_a", NULL, 98, &cache, &_2$$3);
		zephir_check_call_status();
		if (UNEXPECTED(!ZEPHIR_IS_TRUE_IDENTICAL(&_3$$3))) {
			ZEPHIR_INIT_VAR(&_4$$7);
			object_init_ex(&_4$$7, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_5$$7);
			ZEPHIR_CONCAT_SS(&_5$$7, "Cache service must be an object implementing ", "Phalcon\\Cache\\CacheInterface");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_4$$7, "__construct", NULL, 32, &_5$$7);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_4$$7, "phalcon/Mvc/Model/Query.zep", 309);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&adapter, &cache, "getAdapter", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&cacheLifetime, &adapter, "getLifetime", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_OBS_NVAR(&lifetime);
		if (!(zephir_array_isset_string_fetch(&lifetime, &cacheOptions, SL("lifetime"), 0))) {
			ZEPHIR_CPY_WRT(&lifetime, &cacheLifetime);
		}
		ZEPHIR_INIT_NVAR(&result);
		ZVAL_BOOL(&result, 0);
		ZEPHIR_CALL_METHOD(&_6$$3, &cache, "has", NULL, 0, &key);
		zephir_check_call_status();
		if (zephir_is_true(&_6$$3)) {
			ZEPHIR_CALL_METHOD(&result, &cache, "get", NULL, 0, &key);
			zephir_check_call_status();
		}
		if (!(ZEPHIR_IS_EMPTY(&result))) {
			if (UNEXPECTED(Z_TYPE_P(&result) != IS_OBJECT)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Cache didn't return a valid resultset", "phalcon/Mvc/Model/Query.zep", 332);
				return;
			}
			ZVAL_BOOL(&_7$$10, 0);
			ZEPHIR_CALL_METHOD(NULL, &result, "setIsFresh", NULL, 0, &_7$$10);
			zephir_check_call_status();
			if (zephir_is_true(&uniqueRow)) {
				ZEPHIR_CALL_METHOD(&preparedResult, &result, "getFirst", NULL, 0);
				zephir_check_call_status();
			} else {
				ZEPHIR_CPY_WRT(&preparedResult, &result);
			}
			RETURN_CCTOR(&preparedResult);
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 768, &cache);
	}
	ZEPHIR_CALL_METHOD(&intermediate, this_ptr, "parse", NULL, 0);
	zephir_check_call_status();
	zephir_memory_observe(&defaultBindParams);
	zephir_read_property_cached(&defaultBindParams, this_ptr, _zephir_prop_4, 763, PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&mergedParams);
	zephir_add_function(&mergedParams, &defaultBindParams, &bindParams);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&defaultBindTypes);
	zephir_read_property_cached(&defaultBindTypes, this_ptr, _zephir_prop_5, 764, PH_NOISY_CC);
	if (Z_TYPE_P(&defaultBindTypes) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&mergedTypes);
		zephir_add_function(&mergedTypes, &defaultBindTypes, &bindTypes);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CPY_WRT(&mergedTypes, &bindTypes);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_6, 769, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&type, &_0);
	if (ZEPHIR_IS_LONG(&type, 309)) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_LONG(&type, 306)) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_LONG(&type, 300)) { goto zephir_switch_0_clause_2; }
	if (ZEPHIR_IS_LONG(&type, 303)) { goto zephir_switch_0_clause_3; }
	goto zephir_switch_0_clause_4;
	zephir_switch_0_clause_0: ;
		ZEPHIR_CALL_METHOD(&result, this_ptr, "executeSelect", NULL, 487, &intermediate, &mergedParams, &mergedTypes);
		zephir_check_call_status();
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
		ZEPHIR_CALL_METHOD(&result, this_ptr, "executeInsert", NULL, 488, &intermediate, &mergedParams, &mergedTypes);
		zephir_check_call_status();
		goto zephir_switch_0_end;
	zephir_switch_0_clause_2: ;
		ZEPHIR_CALL_METHOD(&result, this_ptr, "executeUpdate", NULL, 489, &intermediate, &mergedParams, &mergedTypes);
		zephir_check_call_status();
		goto zephir_switch_0_end;
	zephir_switch_0_clause_3: ;
		ZEPHIR_CALL_METHOD(&result, this_ptr, "executeDelete", NULL, 490, &intermediate, &mergedParams, &mergedTypes);
		zephir_check_call_status();
		goto zephir_switch_0_end;
	zephir_switch_0_clause_4: ;
		ZEPHIR_INIT_VAR(&_8$$20);
		object_init_ex(&_8$$20, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_9$$20);
		ZEPHIR_CONCAT_SV(&_9$$20, "Unknown statement ", &type);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_8$$20, "__construct", NULL, 32, &_9$$20);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_8$$20, "phalcon/Mvc/Model/Query.zep", 415);
		ZEPHIR_MM_RESTORE();
		return;
	zephir_switch_0_end: ;

	if (Z_TYPE_P(&cacheOptions) != IS_NULL) {
		if (!ZEPHIR_IS_LONG(&type, 309)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Only PHQL statements that return resultsets can be cached", "phalcon/Mvc/Model/Query.zep", 428);
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &cache, "set", NULL, 0, &key, &result, &lifetime);
		zephir_check_call_status();
	}
	if (zephir_is_true(&uniqueRow)) {
		ZEPHIR_CALL_METHOD(&preparedResult, &result, "getFirst", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&preparedResult, &result);
	}
	RETURN_CCTOR(&preparedResult);
}

/**
 * Returns the current cache backend instance
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getCache)
{

	RETURN_MEMBER(getThis(), "cache");
}

/**
 * Returns the current cache options
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getCacheOptions)
{

	RETURN_MEMBER_TYPED(getThis(), "cacheOptions", IS_ARRAY);
}

/**
 * Returns default bind params
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getBindParams)
{

	RETURN_MEMBER_TYPED(getThis(), "bindParams", IS_ARRAY);
}

/**
 * Returns default bind types
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getBindTypes)
{

	RETURN_MEMBER_TYPED(getThis(), "bindTypes", IS_ARRAY);
}

/**
 * Returns the dependency injection container
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getDI)
{

	RETURN_MEMBER(getThis(), "container");
}

/**
 * Returns the intermediate representation of the PHQL statement
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getIntermediate)
{

	RETURN_MEMBER_TYPED(getThis(), "intermediate", IS_ARRAY);
}

/**
 * Executes the query returning the first result
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getSingleResult)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *bindParams_param = NULL, *bindTypes_param = NULL, _0, _1;
	zval bindParams, bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uniqueRow", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &bindParams_param, &bindTypes_param);
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
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 766, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &bindParams, &bindTypes);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "execute", NULL, 0, &bindParams, &bindTypes);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_1, "getFirst", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns an associative array with the SQL to be generated by the internal PHQL,
 * and arrays with bound parameters and their types (only works in SELECT statements).
 *
 *```php
 * [
 *     'sql' => 'SELECT * FROM parts WHERE robot = :robot',
 *     'bind' => ['robot' => 123],
 *     'bindTypes => ['robot' => 1] // 1 corresponds to int
 * ]
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getSql)
{
	zval intermediate, _0, _1$$3, _2$$3, _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindTypes", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&intermediate, this_ptr, "parse", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 769, PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_LONG(&_0, 309)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 763, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_2, 764, PH_NOISY_CC | PH_READONLY);
		ZVAL_BOOL(&_3$$3, 1);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "executeSelect", NULL, 487, &intermediate, &_1$$3, &_2$$3, &_3$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "This type of statement generates multiple SQL statements", "phalcon/Mvc/Model/Query.zep", 542);
	return;
}

/**
 * Gets the type of PHQL statement executed
 *
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getType)
{

	RETURN_MEMBER_TYPED(getThis(), "type", IS_LONG);
}

/**
 * Check if the query is programmed to get only the first row in the
 * resultset
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getUniqueRow)
{

	RETURN_MEMBER(getThis(), "uniqueRow");
}

/**
 * @return TransactionInterface|null
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getTransaction)
{

	RETURN_MEMBER(getThis(), "transaction");
}

/**
 * Parses the intermediate code produced by Phalcon\Mvc\Model\Query\Lang
 * generating another intermediate representation that could be executed by
 * Phalcon\Mvc\Model\Query
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, parse)
{
	zval intermediate, phql, ast, irPhql, uniqueId, type, _0, _1$$5, _2$$7, _3$$13, _4$$13;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&phql);
	ZVAL_UNDEF(&ast);
	ZVAL_UNDEF(&irPhql);
	ZVAL_UNDEF(&uniqueId);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$7);
	ZVAL_UNDEF(&_3$$13);
	ZVAL_UNDEF(&_4$$13);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("intermediate", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("phql", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("ast", 3, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 770, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&intermediate, &_0);
	if (Z_TYPE_P(&intermediate) == IS_ARRAY) {
		RETURN_CCTOR(&intermediate);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 761, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&phql, &_0);
	ZEPHIR_CALL_CE_STATIC(&ast, phalcon_mvc_model_query_lang_ce, "parsePHQL", NULL, 0, &phql);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&irPhql);
	ZVAL_NULL(&irPhql);
	ZEPHIR_INIT_VAR(&uniqueId);
	ZVAL_NULL(&uniqueId);
	if (Z_TYPE_P(&ast) == IS_ARRAY) {
		ZEPHIR_OBS_NVAR(&uniqueId);
		if (zephir_array_isset_string_fetch(&uniqueId, &ast, SL("id"), 0)) {
			ZEPHIR_OBS_NVAR(&irPhql);
			zephir_read_static_property_ce(&_1$$5, phalcon_mvc_model_query_ce, SL("internalPhqlCache"), PH_NOISY_CC | PH_READONLY);
			if (zephir_array_isset_fetch(&irPhql, &_1$$5, &uniqueId, 0)) {
				if (Z_TYPE_P(&irPhql) == IS_ARRAY) {
					zephir_memory_observe(&_2$$7);
					zephir_array_fetch_string(&_2$$7, &ast, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 607);
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 769, &_2$$7);
					RETURN_CCTOR(&irPhql);
				}
			}
		}
		zephir_memory_observe(&type);
		if (zephir_array_isset_string_fetch(&type, &ast, SL("type"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 771, &ast);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 769, &type);
			if (ZEPHIR_IS_LONG(&type, 309)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&type, 306)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&type, 300)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&type, 303)) { goto zephir_switch_0_clause_3; }
			goto zephir_switch_0_clause_4;
			zephir_switch_0_clause_0: ;
				ZEPHIR_CALL_METHOD(&irPhql, this_ptr, "_prepareSelect", NULL, 491);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				ZEPHIR_CALL_METHOD(&irPhql, this_ptr, "_prepareInsert", NULL, 492);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
				ZEPHIR_CALL_METHOD(&irPhql, this_ptr, "_prepareUpdate", NULL, 493);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_CALL_METHOD(&irPhql, this_ptr, "_prepareDelete", NULL, 494);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_INIT_VAR(&_3$$13);
				object_init_ex(&_3$$13, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_VAR(&_4$$13);
				ZEPHIR_CONCAT_SVSV(&_4$$13, "Unknown statement ", &type, ", when preparing: ", &phql);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_3$$13, "__construct", NULL, 32, &_4$$13);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_3$$13, "phalcon/Mvc/Model/Query.zep", 641);
				ZEPHIR_MM_RESTORE();
				return;
			zephir_switch_0_end: ;

		}
	}
	if (UNEXPECTED(Z_TYPE_P(&irPhql) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted AST", "phalcon/Mvc/Model/Query.zep", 647);
		return;
	}
	if (Z_TYPE_P(&uniqueId) == IS_LONG) {
		zephir_update_static_property_array_multi_ce(phalcon_mvc_model_query_ce, SL("internalPhqlCache"), &irPhql, SL("z"), 1, &uniqueId);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 770, &irPhql);
	RETURN_CCTOR(&irPhql);
}

/**
 * Set default bind parameters
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setBindParams)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool merge;
	zval *bindParams_param = NULL, *merge_param = NULL, currentBindParams, _0$$3;
	zval bindParams;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&currentBindParams);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("bindParams", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &bindParams_param, &merge_param);
	ZEPHIR_OBS_COPY_OR_DUP(&bindParams, bindParams_param);
	if (!merge_param) {
		merge = 0;
	} else {
		}
	if (merge) {
		zephir_memory_observe(&currentBindParams);
		zephir_read_property_cached(&currentBindParams, this_ptr, _zephir_prop_0, 763, PH_NOISY_CC);
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_add_function(&_0$$3, &currentBindParams, &bindParams);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 763, &_0$$3);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 763, &bindParams);
	}
	RETURN_THIS();
}

/**
 * Set default bind parameters
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setBindTypes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool merge;
	zval *bindTypes_param = NULL, *merge_param = NULL, currentBindTypes, _0$$4;
	zval bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&currentBindTypes);
	ZVAL_UNDEF(&_0$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("bindTypes", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &bindTypes_param, &merge_param);
	ZEPHIR_OBS_COPY_OR_DUP(&bindTypes, bindTypes_param);
	if (!merge_param) {
		merge = 0;
	} else {
		}
	if (UNEXPECTED(merge)) {
		zephir_memory_observe(&currentBindTypes);
		zephir_read_property_cached(&currentBindTypes, this_ptr, _zephir_prop_0, 764, PH_NOISY_CC);
		if (Z_TYPE_P(&currentBindTypes) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_0$$4);
			zephir_add_function(&_0$$4, &currentBindTypes, &bindTypes);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 764, &_0$$4);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 764, &bindTypes);
		}
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 764, &bindTypes);
	}
	RETURN_THIS();
}

/**
 * Sets the dependency injection container
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setDI)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, manager, metaData, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("metaData", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &container);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "modelsManager");
	ZEPHIR_CALL_METHOD(&manager, container, "getShared", NULL, 0, &_0);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&manager) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Injected service 'modelsManager' is invalid", "phalcon/Mvc/Model/Query.zep", 711);
		return;
	}
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "modelsMetadata");
	ZEPHIR_CALL_METHOD(&metaData, container, "getShared", NULL, 0, &_0);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&metaData) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Injected service 'modelsMetaData' is invalid", "phalcon/Mvc/Model/Query.zep", 717);
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 772, &manager);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 773, &metaData);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 767, container);
	ZEPHIR_MM_RESTORE();
}

/**
 * Allows to set the IR to be executed
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setIntermediate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *intermediate_param = NULL;
	zval intermediate;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("intermediate", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(intermediate, intermediate_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &intermediate_param);
	ZEPHIR_OBS_COPY_OR_DUP(&intermediate, intermediate_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 770, &intermediate);
	RETURN_THIS();
}

/**
 * Set SHARED LOCK clause
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setSharedLock)
{
	zval *sharedLock_param = NULL, __$true, __$false;
	zend_bool sharedLock;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("sharedLock", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(sharedLock)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &sharedLock_param);
	if (!sharedLock_param) {
		sharedLock = 0;
	} else {
		}
	if (sharedLock) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 774, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 774, &__$false);
	}
	RETURN_THISW();
}

/**
 * allows to wrap a transaction around all queries
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setTransaction)
{
	zval *transaction, transaction_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&transaction_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transaction", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(transaction, phalcon_mvc_model_transactioninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &transaction);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 775, transaction);
	RETURN_THISW();
}

/**
 * Sets the type of PHQL statement to be executed
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setType)
{
	zval *type_param = NULL, _0;
	zend_long type;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("type", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &type_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, type);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 769, &_0);
	RETURN_THISW();
}

/**
 * Tells to the query if only the first row in the resultset must be
 * returned
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, setUniqueRow)
{
	zval *uniqueRow_param = NULL, __$true, __$false;
	zend_bool uniqueRow;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uniqueRow", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(uniqueRow)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &uniqueRow_param);
	if (uniqueRow) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 766, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 766, &__$false);
	}
	RETURN_THISW();
}

/**
 * Executes the DELETE intermediate representation producing a
 * Phalcon\Mvc\Model\Query\Status
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, executeDelete)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL, *_8 = NULL, *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, models, modelName, model, records, connection, record, exception, _0, _3, _11, _1$$4, _2$$5, _5$$7, _7$$8, _9$$6;
	zval intermediate, bindParams, bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&records);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&record);
	ZVAL_UNDEF(&exception);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_9$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &intermediate_param, &bindParams_param, &bindTypes_param);
	zephir_get_arrval(&intermediate, intermediate_param);
	zephir_get_arrval(&bindParams, bindParams_param);
	zephir_get_arrval(&bindTypes, bindTypes_param);
	zephir_memory_observe(&models);
	zephir_array_fetch_string(&models, &intermediate, SL("models"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 785);
	if (UNEXPECTED(zephir_array_isset_value_long(&models, 1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Delete from several models at the same time is still not supported", "phalcon/Mvc/Model/Query.zep", 790);
		return;
	}
	zephir_memory_observe(&modelName);
	zephir_array_fetch_long(&modelName, &models, 0, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 793);
	zephir_memory_observe(&model);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 776, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&model, &_0, &modelName, 0))) {
		zephir_read_property_cached(&_1$$4, this_ptr, _zephir_prop_1, 772, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&model, &_1$$4, "load", NULL, 0, &modelName);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&records, this_ptr, "getRelatedRecords", NULL, 495, &model, &intermediate, &bindParams, &bindTypes);
	zephir_check_call_status();
	if (!(zephir_fast_count_int(&records))) {
		object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
		ZVAL_BOOL(&_2$$5, 1);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_2$$5);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&connection, this_ptr, "getWriteConnection", NULL, 0, &model, &intermediate, &bindParams, &bindTypes);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &connection, "begin", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &records, "rewind", NULL, 0);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_CALL_METHOD(&_3, &records, "valid", NULL, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_3))) {
			break;
		}

		/* try_start_1: */

			ZEPHIR_CALL_METHOD(&record, &records, "current", &_4, 0);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_METHOD(&_5$$7, &record, "delete", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			if (!(zephir_is_true(&_5$$7))) {
				ZEPHIR_CALL_METHOD(NULL, &connection, "rollback", &_6, 0);
				zephir_check_call_status_or_jump(try_end_1);
				object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
				ZVAL_BOOL(&_7$$8, 0);
				ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_7$$8, &record);
				zephir_check_call_status_or_jump(try_end_1);
				RETURN_MM();
			}
			ZEPHIR_CALL_METHOD(NULL, &records, "next", &_8, 0);
			zephir_check_call_status_or_jump(try_end_1);

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_NVAR(&_9$$6);
			ZVAL_OBJ(&_9$$6, EG(exception));
			Z_ADDREF_P(&_9$$6);
			if (zephir_is_instance_of(&_9$$6, SL("PDOException"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&exception, &_9$$6);
				ZEPHIR_CALL_METHOD(NULL, &connection, "rollback", &_10, 0);
				zephir_check_call_status();
				zephir_throw_exception_debug(&exception, "phalcon/Mvc/Model/Query.zep", 852);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &connection, "commit", NULL, 0);
	zephir_check_call_status();
	object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
	ZVAL_BOOL(&_11, 1);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_11);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Executes the INSERT intermediate representation producing a
 * Phalcon\Mvc\Model\Query\Status
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, executeInsert)
{
	zend_string *_8;
	zend_ulong _7;
	zend_bool automaticFields = 0, _25, _21$$8, _36$$17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_12 = NULL, *_17 = NULL, *_19 = NULL, *_20 = NULL, *_27 = NULL, *_29 = NULL, *_35 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, modelName, manager, connection, metaData, attributes, fields, columnMap, dialect, insertValues, number, value, model, values, exprValue, insertValue, wildcard, fieldName, attributeName, insertModel, _0, _1, *_4, _5, *_6, _24, _39, _2$$4, _3$$4, _9$$8, _11$$11, _13$$11, _14$$11, _15$$12, _16$$12, _18$$13, _22$$15, _23$$15, _26$$17, _28$$20, _30$$20, _31$$20, _32$$21, _33$$21, _34$$22, _37$$24, _38$$24;
	zval intermediate, bindParams, bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&insertValues);
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&exprValue);
	ZVAL_UNDEF(&insertValue);
	ZVAL_UNDEF(&wildcard);
	ZVAL_UNDEF(&fieldName);
	ZVAL_UNDEF(&attributeName);
	ZVAL_UNDEF(&insertModel);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_22$$15);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_28$$20);
	ZVAL_UNDEF(&_30$$20);
	ZVAL_UNDEF(&_31$$20);
	ZVAL_UNDEF(&_32$$21);
	ZVAL_UNDEF(&_33$$21);
	ZVAL_UNDEF(&_34$$22);
	ZVAL_UNDEF(&_37$$24);
	ZVAL_UNDEF(&_38$$24);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("metaData", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &intermediate_param, &bindParams_param, &bindTypes_param);
	zephir_get_arrval(&intermediate, intermediate_param);
	zephir_get_arrval(&bindParams, bindParams_param);
	zephir_get_arrval(&bindTypes, bindTypes_param);
	ZEPHIR_INIT_VAR(&columnMap);
	zephir_memory_observe(&modelName);
	zephir_array_fetch_string(&modelName, &intermediate, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 880);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	zephir_memory_observe(&model);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 776, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&model, &_0, &modelName, 0))) {
		ZEPHIR_CALL_METHOD(&model, &manager, "load", NULL, 0, &modelName);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&connection, this_ptr, "getWriteConnection", NULL, 0, &model, &intermediate, &bindParams, &bindTypes);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_2, 773, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&metaData, &_1);
	ZEPHIR_CALL_METHOD(&attributes, &metaData, "getAttributes", NULL, 0, &model);
	zephir_check_call_status();
	automaticFields = 0;
	zephir_memory_observe(&fields);
	if (!(zephir_array_isset_string_fetch(&fields, &intermediate, SL("fields"), 0))) {
		automaticFields = 1;
		ZEPHIR_CPY_WRT(&fields, &attributes);
		ZEPHIR_INIT_VAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "orm.column_renaming");
		ZEPHIR_CALL_CE_STATIC(&_2$$4, phalcon_support_settings_ce, "get", NULL, 0, &_3$$4);
		zephir_check_call_status();
		if (zephir_is_true(&_2$$4)) {
			ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, &model);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&columnMap);
			ZVAL_NULL(&columnMap);
		}
	}
	zephir_memory_observe(&values);
	zephir_array_fetch_string(&values, &intermediate, SL("values"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 915);
	if (UNEXPECTED(zephir_fast_count_int(&fields) != zephir_fast_count_int(&values))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The column count does not match the values count", "phalcon/Mvc/Model/Query.zep", 924);
		return;
	}
	ZEPHIR_CALL_METHOD(&dialect, &connection, "getDialect", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&insertValues);
	array_init(&insertValues);
	if (Z_TYPE_P(&values) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &values);
		_4 = &_5;
	} else {
		_4 = &values;
	}
	zephir_is_iterable(_4, 0, "phalcon/Mvc/Model/Query.zep", 995);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _7, _8, _6)
		{
			ZEPHIR_INIT_NVAR(&number);
			if (_8 != NULL) { 
				ZVAL_STR_COPY(&number, _8);
			} else {
				ZVAL_LONG(&number, _7);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_OBS_NVAR(&exprValue);
			zephir_array_fetch_string(&exprValue, &value, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 934);
			ZEPHIR_OBS_NVAR(&_9$$8);
			zephir_array_fetch_string(&_9$$8, &value, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 936);
			if (ZEPHIR_IS_LONG(&_9$$8, 260)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&_9$$8, 258)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&_9$$8, 259)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&_9$$8, 322)) { goto zephir_switch_0_clause_3; }
			if (ZEPHIR_IS_LONG(&_9$$8, 273)) { goto zephir_switch_0_clause_4; }
			if (ZEPHIR_IS_LONG(&_9$$8, 274)) { goto zephir_switch_0_clause_5; }
			if (ZEPHIR_IS_LONG(&_9$$8, 277)) { goto zephir_switch_0_clause_6; }
			goto zephir_switch_0_clause_7;
			zephir_switch_0_clause_0: ;
			zephir_switch_0_clause_1: ;
			zephir_switch_0_clause_2: ;
				ZEPHIR_CALL_METHOD(&insertValue, &dialect, "getSqlExpression", &_10, 0, &exprValue);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_NVAR(&insertValue);
				ZVAL_NULL(&insertValue);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
			zephir_switch_0_clause_5: ;
			zephir_switch_0_clause_6: ;
				ZEPHIR_CALL_METHOD(&_11$$11, &dialect, "getSqlExpression", &_12, 0, &exprValue);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_13$$11);
				ZVAL_STRING(&_13$$11, ":");
				ZEPHIR_INIT_NVAR(&_14$$11);
				ZVAL_STRING(&_14$$11, "");
				ZEPHIR_INIT_NVAR(&wildcard);
				zephir_fast_str_replace(&wildcard, &_13$$11, &_14$$11, &_11$$11);
				ZEPHIR_OBS_NVAR(&insertValue);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&insertValue, &bindParams, &wildcard, 0)))) {
					ZEPHIR_INIT_NVAR(&_15$$12);
					object_init_ex(&_15$$12, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_16$$12);
					ZEPHIR_CONCAT_SVS(&_16$$12, "Bound parameter '", &wildcard, "' cannot be replaced because it isn't in the placeholders list");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_15$$12, "__construct", &_17, 32, &_16$$12);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_15$$12, "phalcon/Mvc/Model/Query.zep", 960);
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_7: ;
				ZEPHIR_INIT_NVAR(&insertValue);
				object_init_ex(&insertValue, phalcon_db_rawvalue_ce);
				ZEPHIR_CALL_METHOD(&_18$$13, &dialect, "getSqlExpression", &_19, 0, &exprValue);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &insertValue, "__construct", &_20, 35, &_18$$13);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_end: ;

			ZEPHIR_OBS_NVAR(&fieldName);
			zephir_array_fetch(&fieldName, &fields, &number, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 973);
			_21$$8 = automaticFields;
			if (_21$$8) {
				_21$$8 = Z_TYPE_P(&columnMap) == IS_ARRAY;
			}
			if (_21$$8) {
				ZEPHIR_OBS_NVAR(&attributeName);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeName, &columnMap, &fieldName, 0)))) {
					ZEPHIR_INIT_NVAR(&_22$$15);
					object_init_ex(&_22$$15, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_23$$15);
					ZEPHIR_CONCAT_SVS(&_23$$15, "Column '", &fieldName, "' isn't part of the column map");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_22$$15, "__construct", &_17, 32, &_23$$15);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_22$$15, "phalcon/Mvc/Model/Query.zep", 983);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&attributeName, &fieldName);
			}
			zephir_array_update_zval(&insertValues, &attributeName, &insertValue, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_25 = 1;
		while (1) {
			if (_25) {
				_25 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_24, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_24)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&number, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&exprValue);
				zephir_array_fetch_string(&exprValue, &value, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 934);
				ZEPHIR_OBS_NVAR(&_26$$17);
				zephir_array_fetch_string(&_26$$17, &value, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 936);
				if (ZEPHIR_IS_LONG(&_26$$17, 260)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&_26$$17, 258)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&_26$$17, 259)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&_26$$17, 322)) { goto zephir_switch_1_clause_3; }
				if (ZEPHIR_IS_LONG(&_26$$17, 273)) { goto zephir_switch_1_clause_4; }
				if (ZEPHIR_IS_LONG(&_26$$17, 274)) { goto zephir_switch_1_clause_5; }
				if (ZEPHIR_IS_LONG(&_26$$17, 277)) { goto zephir_switch_1_clause_6; }
				goto zephir_switch_1_clause_7;
				zephir_switch_1_clause_0: ;
				zephir_switch_1_clause_1: ;
				zephir_switch_1_clause_2: ;
					ZEPHIR_CALL_METHOD(&insertValue, &dialect, "getSqlExpression", &_27, 0, &exprValue);
					zephir_check_call_status();
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_NVAR(&insertValue);
					ZVAL_NULL(&insertValue);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
				zephir_switch_1_clause_5: ;
				zephir_switch_1_clause_6: ;
					ZEPHIR_CALL_METHOD(&_28$$20, &dialect, "getSqlExpression", &_29, 0, &exprValue);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_30$$20);
					ZVAL_STRING(&_30$$20, ":");
					ZEPHIR_INIT_NVAR(&_31$$20);
					ZVAL_STRING(&_31$$20, "");
					ZEPHIR_INIT_NVAR(&wildcard);
					zephir_fast_str_replace(&wildcard, &_30$$20, &_31$$20, &_28$$20);
					ZEPHIR_OBS_NVAR(&insertValue);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&insertValue, &bindParams, &wildcard, 0)))) {
						ZEPHIR_INIT_NVAR(&_32$$21);
						object_init_ex(&_32$$21, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_33$$21);
						ZEPHIR_CONCAT_SVS(&_33$$21, "Bound parameter '", &wildcard, "' cannot be replaced because it isn't in the placeholders list");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_32$$21, "__construct", &_17, 32, &_33$$21);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_32$$21, "phalcon/Mvc/Model/Query.zep", 960);
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_7: ;
					ZEPHIR_INIT_NVAR(&insertValue);
					object_init_ex(&insertValue, phalcon_db_rawvalue_ce);
					ZEPHIR_CALL_METHOD(&_34$$22, &dialect, "getSqlExpression", &_35, 0, &exprValue);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &insertValue, "__construct", &_20, 35, &_34$$22);
					zephir_check_call_status();
					goto zephir_switch_1_end;
				zephir_switch_1_end: ;

				ZEPHIR_OBS_NVAR(&fieldName);
				zephir_array_fetch(&fieldName, &fields, &number, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 973);
				_36$$17 = automaticFields;
				if (_36$$17) {
					_36$$17 = Z_TYPE_P(&columnMap) == IS_ARRAY;
				}
				if (_36$$17) {
					ZEPHIR_OBS_NVAR(&attributeName);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeName, &columnMap, &fieldName, 0)))) {
						ZEPHIR_INIT_NVAR(&_37$$24);
						object_init_ex(&_37$$24, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_38$$24);
						ZEPHIR_CONCAT_SVS(&_38$$24, "Column '", &fieldName, "' isn't part of the column map");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_37$$24, "__construct", &_17, 32, &_38$$24);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_37$$24, "phalcon/Mvc/Model/Query.zep", 983);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeName, &fieldName);
				}
				zephir_array_update_zval(&insertValues, &attributeName, &insertValue, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&number);
	ZEPHIR_CALL_METHOD(&insertModel, &manager, "load", NULL, 0, &modelName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &insertModel, "assign", NULL, 0, &insertValues);
	zephir_check_call_status();
	object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
	ZEPHIR_CALL_METHOD(&_39, &insertModel, "create", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_39, &insertModel);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Executes the SELECT intermediate representation producing a
 * Phalcon\Mvc\Model\Resultset
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, executeSelect)
{
	zval _114$$86, _117$$87;
	zend_string *_29, *_91, *_98, *_108, *_135$$101;
	zend_ulong _28, _90, _97, _107, _134$$101;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_8 = NULL, *_9 = NULL, *_14 = NULL, *_32 = NULL, *_33 = NULL, *_35 = NULL, *_37 = NULL, *_47 = NULL, *_63 = NULL, *_64 = NULL, *_67 = NULL, *_77 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, numberObjects = 0;
	zend_bool simulate, haveObjects = 0, haveScalars = 0, isComplex = 0, isSimpleStd = 0, isKeepingSnapshots = 0, _12, _23, _60, _94, _101, _6$$3, _15$$9, _58$$32, _43$$35, _54$$41, _88$$50, _73$$53, _84$$59, _109$$84, _128$$98, _139$$101, _143$$91;
	zval *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, *simulate_param = NULL, __$true, __$null, manager, modelName, models, model, connection, connectionTypes, columns, column, selectColumns, simpleColumnMap, metaData, aliasCopy, sqlColumn, attributes, instance, columnMap, attribute, columnAlias, sqlAlias, dialect, sqlSelect, bindCounts, processed, wildcard, value, processedTypes, typeWildcard, result, resultData, cache, resultObject, columns1, typesColumnMap, wildcardValue, resultsetClassName, _0, *_1, _2, *_3, _11, *_18, _19, *_20, _22, *_25, _26, *_27, _59, *_89, _93, *_96, _100, *_104, _105, *_106, _118, _4$$3, _7$$3, _10$$7, _13$$9, _16$$9, _17$$13, _21$$15, _24$$20, _30$$32, _31$$33, _34$$35, _36$$35, *_38$$35, *_39$$35, _42$$35, _46$$35, _41$$38, _45$$39, _48$$40, *_49$$41, _50$$41, *_51$$41, _53$$41, _56$$45, _57$$46, _61$$50, _62$$51, _65$$53, _66$$53, *_68$$53, *_69$$53, _72$$53, _76$$53, _71$$56, _75$$57, _78$$58, *_79$$59, _80$$59, *_81$$59, _83$$59, _86$$63, _87$$64, _92$$71, _95$$75, _99$$77, _102$$80, _103$$83, _110$$85, _111$$85, _112$$85, _113$$86, _115$$87, _116$$87, _119$$93, _120$$93, _142$$93, _121$$98, *_122$$98, _123$$98, *_124$$98, _127$$98, _126$$99, _130$$100, *_131$$101, _132$$101, *_133$$101, _138$$101, _137$$102, _141$$103, _151$$91, _144$$106, _145$$106, _146$$105, _147$$105, _148$$107, _149$$107;
	zval intermediate, bindParams, bindTypes, _40$$38, _44$$39, _52$$42, _55$$43, _70$$56, _74$$57, _82$$60, _85$$61, _125$$99, _129$$100, _136$$102, _140$$103, _150$$105;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&_40$$38);
	ZVAL_UNDEF(&_44$$39);
	ZVAL_UNDEF(&_52$$42);
	ZVAL_UNDEF(&_55$$43);
	ZVAL_UNDEF(&_70$$56);
	ZVAL_UNDEF(&_74$$57);
	ZVAL_UNDEF(&_82$$60);
	ZVAL_UNDEF(&_85$$61);
	ZVAL_UNDEF(&_125$$99);
	ZVAL_UNDEF(&_129$$100);
	ZVAL_UNDEF(&_136$$102);
	ZVAL_UNDEF(&_140$$103);
	ZVAL_UNDEF(&_150$$105);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&connectionTypes);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&selectColumns);
	ZVAL_UNDEF(&simpleColumnMap);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&aliasCopy);
	ZVAL_UNDEF(&sqlColumn);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&instance);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&columnAlias);
	ZVAL_UNDEF(&sqlAlias);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&sqlSelect);
	ZVAL_UNDEF(&bindCounts);
	ZVAL_UNDEF(&processed);
	ZVAL_UNDEF(&wildcard);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&processedTypes);
	ZVAL_UNDEF(&typeWildcard);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&resultData);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&resultObject);
	ZVAL_UNDEF(&columns1);
	ZVAL_UNDEF(&typesColumnMap);
	ZVAL_UNDEF(&wildcardValue);
	ZVAL_UNDEF(&resultsetClassName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_59);
	ZVAL_UNDEF(&_93);
	ZVAL_UNDEF(&_100);
	ZVAL_UNDEF(&_105);
	ZVAL_UNDEF(&_118);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_24$$20);
	ZVAL_UNDEF(&_30$$32);
	ZVAL_UNDEF(&_31$$33);
	ZVAL_UNDEF(&_34$$35);
	ZVAL_UNDEF(&_36$$35);
	ZVAL_UNDEF(&_42$$35);
	ZVAL_UNDEF(&_46$$35);
	ZVAL_UNDEF(&_41$$38);
	ZVAL_UNDEF(&_45$$39);
	ZVAL_UNDEF(&_48$$40);
	ZVAL_UNDEF(&_50$$41);
	ZVAL_UNDEF(&_53$$41);
	ZVAL_UNDEF(&_56$$45);
	ZVAL_UNDEF(&_57$$46);
	ZVAL_UNDEF(&_61$$50);
	ZVAL_UNDEF(&_62$$51);
	ZVAL_UNDEF(&_65$$53);
	ZVAL_UNDEF(&_66$$53);
	ZVAL_UNDEF(&_72$$53);
	ZVAL_UNDEF(&_76$$53);
	ZVAL_UNDEF(&_71$$56);
	ZVAL_UNDEF(&_75$$57);
	ZVAL_UNDEF(&_78$$58);
	ZVAL_UNDEF(&_80$$59);
	ZVAL_UNDEF(&_83$$59);
	ZVAL_UNDEF(&_86$$63);
	ZVAL_UNDEF(&_87$$64);
	ZVAL_UNDEF(&_92$$71);
	ZVAL_UNDEF(&_95$$75);
	ZVAL_UNDEF(&_99$$77);
	ZVAL_UNDEF(&_102$$80);
	ZVAL_UNDEF(&_103$$83);
	ZVAL_UNDEF(&_110$$85);
	ZVAL_UNDEF(&_111$$85);
	ZVAL_UNDEF(&_112$$85);
	ZVAL_UNDEF(&_113$$86);
	ZVAL_UNDEF(&_115$$87);
	ZVAL_UNDEF(&_116$$87);
	ZVAL_UNDEF(&_119$$93);
	ZVAL_UNDEF(&_120$$93);
	ZVAL_UNDEF(&_142$$93);
	ZVAL_UNDEF(&_121$$98);
	ZVAL_UNDEF(&_123$$98);
	ZVAL_UNDEF(&_127$$98);
	ZVAL_UNDEF(&_126$$99);
	ZVAL_UNDEF(&_130$$100);
	ZVAL_UNDEF(&_132$$101);
	ZVAL_UNDEF(&_138$$101);
	ZVAL_UNDEF(&_137$$102);
	ZVAL_UNDEF(&_141$$103);
	ZVAL_UNDEF(&_151$$91);
	ZVAL_UNDEF(&_144$$106);
	ZVAL_UNDEF(&_145$$106);
	ZVAL_UNDEF(&_146$$105);
	ZVAL_UNDEF(&_147$$105);
	ZVAL_UNDEF(&_148$$107);
	ZVAL_UNDEF(&_149$$107);
	ZVAL_UNDEF(&_114$$86);
	ZVAL_UNDEF(&_117$$87);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("metaData", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("sharedLock", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("cache", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		ZEPHIR_Z_PARAM_ARRAY(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(simulate)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 1, &intermediate_param, &bindParams_param, &bindTypes_param, &simulate_param);
	zephir_get_arrval(&intermediate, intermediate_param);
	zephir_get_arrval(&bindParams, bindParams_param);
	zephir_get_arrval(&bindTypes, bindTypes_param);
	if (!simulate_param) {
		simulate = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&model);
	ZEPHIR_INIT_VAR(&connection);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_INIT_VAR(&connectionTypes);
	array_init(&connectionTypes);
	zephir_memory_observe(&models);
	zephir_array_fetch_string(&models, &intermediate, SL("models"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1032);
	if (Z_TYPE_P(&models) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &models);
		_1 = &_2;
	} else {
		_1 = &models;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query.zep", 1069);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&modelName);
			ZVAL_COPY(&modelName, _3);
			ZEPHIR_OBS_NVAR(&model);
			zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_1, 776, PH_NOISY_CC | PH_READONLY);
			if (!(zephir_array_isset_fetch(&model, &_4$$3, &modelName, 0))) {
				ZEPHIR_CALL_METHOD(&model, &manager, "load", &_5, 0, &modelName);
				zephir_check_call_status();
				zephir_update_property_array(this_ptr, SL("modelsInstances"), &modelName, &model);
			}
			_6$$3 = zephir_array_isset_value_string(&intermediate, SL("forUpdate"));
			if (_6$$3) {
				ZEPHIR_OBS_NVAR(&_7$$3);
				zephir_array_fetch_string(&_7$$3, &intermediate, SL("forUpdate"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1041);
				_6$$3 = zephir_is_true(&_7$$3);
			}
			if (_6$$3) {
				ZEPHIR_CALL_METHOD(&connection, this_ptr, "getWriteConnection", &_8, 0, &model, &intermediate, &bindParams, &bindTypes);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(&connection, this_ptr, "getReadConnection", &_9, 0, &model, &intermediate, &bindParams, &bindTypes);
				zephir_check_call_status();
			}
			if (Z_TYPE_P(&connection) == IS_OBJECT) {
				ZEPHIR_CALL_METHOD(&_10$$7, &connection, "getType", NULL, 0);
				zephir_check_call_status();
				zephir_array_update_zval(&connectionTypes, &_10$$7, &__$true, PH_COPY | PH_SEPARATE);
				if (UNEXPECTED(zephir_fast_count_int(&connectionTypes) == 2)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Cannot use models of different database systems in the same query", "phalcon/Mvc/Model/Query.zep", 1064);
					return;
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&modelName, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&model);
				zephir_read_property_cached(&_13$$9, this_ptr, _zephir_prop_1, 776, PH_NOISY_CC | PH_READONLY);
				if (!(zephir_array_isset_fetch(&model, &_13$$9, &modelName, 0))) {
					ZEPHIR_CALL_METHOD(&model, &manager, "load", &_14, 0, &modelName);
					zephir_check_call_status();
					zephir_update_property_array(this_ptr, SL("modelsInstances"), &modelName, &model);
				}
				_15$$9 = zephir_array_isset_value_string(&intermediate, SL("forUpdate"));
				if (_15$$9) {
					ZEPHIR_OBS_NVAR(&_16$$9);
					zephir_array_fetch_string(&_16$$9, &intermediate, SL("forUpdate"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1041);
					_15$$9 = zephir_is_true(&_16$$9);
				}
				if (_15$$9) {
					ZEPHIR_CALL_METHOD(&connection, this_ptr, "getWriteConnection", &_8, 0, &model, &intermediate, &bindParams, &bindTypes);
					zephir_check_call_status();
				} else {
					ZEPHIR_CALL_METHOD(&connection, this_ptr, "getReadConnection", &_9, 0, &model, &intermediate, &bindParams, &bindTypes);
					zephir_check_call_status();
				}
				if (Z_TYPE_P(&connection) == IS_OBJECT) {
					ZEPHIR_CALL_METHOD(&_17$$13, &connection, "getType", NULL, 0);
					zephir_check_call_status();
					zephir_array_update_zval(&connectionTypes, &_17$$13, &__$true, PH_COPY | PH_SEPARATE);
					if (UNEXPECTED(zephir_fast_count_int(&connectionTypes) == 2)) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Cannot use models of different database systems in the same query", "phalcon/Mvc/Model/Query.zep", 1064);
						return;
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&modelName);
	zephir_memory_observe(&columns);
	zephir_array_fetch_string(&columns, &intermediate, SL("columns"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1069);
	haveObjects = 0;
	haveScalars = 0;
	isComplex = 0;
	numberObjects = 0;
	ZEPHIR_CPY_WRT(&columns1, &columns);
	if (Z_TYPE_P(&columns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_19);
		zephir_string_to_char_array(&_19, &columns);
		_18 = &_19;
	} else {
		_18 = &columns;
	}
	zephir_is_iterable(_18, 0, "phalcon/Mvc/Model/Query.zep", 1097);
	if (Z_TYPE_P(_18) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_18), _20)
		{
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _20);
			if (UNEXPECTED(Z_TYPE_P(&column) != IS_ARRAY)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Invalid column definition", "phalcon/Mvc/Model/Query.zep", 1081);
				return;
			}
			ZEPHIR_OBS_NVAR(&_21$$15);
			zephir_array_fetch_string(&_21$$15, &column, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1084);
			if (ZEPHIR_IS_STRING(&_21$$15, "scalar")) {
				if (!(zephir_array_isset_value_string(&column, SL("balias")))) {
					isComplex = 1;
				}
				haveScalars = 1;
			} else {
				haveObjects = 1;
				numberObjects++;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _18, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _18, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _18, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&column, _18, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&column) != IS_ARRAY)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Invalid column definition", "phalcon/Mvc/Model/Query.zep", 1081);
					return;
				}
				ZEPHIR_OBS_NVAR(&_24$$20);
				zephir_array_fetch_string(&_24$$20, &column, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1084);
				if (ZEPHIR_IS_STRING(&_24$$20, "scalar")) {
					if (!(zephir_array_isset_value_string(&column, SL("balias")))) {
						isComplex = 1;
					}
					haveScalars = 1;
				} else {
					haveObjects = 1;
					numberObjects++;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	if (!(isComplex)) {
		if (haveObjects) {
			if (haveScalars) {
				isComplex = 1;
			} else {
				if (numberObjects == 1) {
					isSimpleStd = 0;
				} else {
					isComplex = 1;
				}
			}
		} else {
			isSimpleStd = 1;
		}
	}
	ZEPHIR_INIT_VAR(&instance);
	ZVAL_NULL(&instance);
	ZEPHIR_INIT_VAR(&selectColumns);
	array_init(&selectColumns);
	ZEPHIR_INIT_VAR(&simpleColumnMap);
	array_init(&simpleColumnMap);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 773, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&metaData, &_0);
	if (Z_TYPE_P(&columns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_26);
		zephir_string_to_char_array(&_26, &columns);
		_25 = &_26;
	} else {
		_25 = &columns;
	}
	zephir_is_iterable(_25, 0, "phalcon/Mvc/Model/Query.zep", 1203);
	if (Z_TYPE_P(_25) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_25), _28, _29, _27)
		{
			ZEPHIR_INIT_NVAR(&aliasCopy);
			if (_29 != NULL) { 
				ZVAL_STR_COPY(&aliasCopy, _29);
			} else {
				ZVAL_LONG(&aliasCopy, _28);
			}
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _27);
			ZEPHIR_OBS_NVAR(&sqlColumn);
			zephir_array_fetch_string(&sqlColumn, &column, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1120);
			ZEPHIR_OBS_NVAR(&_30$$32);
			zephir_array_fetch_string(&_30$$32, &column, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1123);
			if (ZEPHIR_IS_STRING(&_30$$32, "object")) {
				ZEPHIR_OBS_NVAR(&modelName);
				zephir_array_fetch_string(&modelName, &column, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1124);
				ZEPHIR_OBS_NVAR(&instance);
				zephir_read_property_cached(&_31$$33, this_ptr, _zephir_prop_1, 776, PH_NOISY_CC | PH_READONLY);
				if (!(zephir_array_isset_fetch(&instance, &_31$$33, &modelName, 0))) {
					ZEPHIR_CALL_METHOD(&instance, &manager, "load", &_32, 0, &modelName);
					zephir_check_call_status();
					zephir_update_property_array(this_ptr, SL("modelsInstances"), &modelName, &instance);
				}
				ZEPHIR_CALL_METHOD(&attributes, &metaData, "getAttributes", &_33, 0, &instance);
				zephir_check_call_status();
				if (isComplex) {
					ZEPHIR_INIT_NVAR(&_36$$35);
					ZVAL_STRING(&_36$$35, "orm.column_renaming");
					ZEPHIR_CALL_CE_STATIC(&_34$$35, phalcon_support_settings_ce, "get", &_35, 0, &_36$$35);
					zephir_check_call_status();
					if (zephir_is_true(&_34$$35)) {
						ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", &_37, 0, &instance);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(&columnMap);
						ZVAL_NULL(&columnMap);
					}
					if (Z_TYPE_P(&attributes) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_36$$35);
						zephir_string_to_char_array(&_36$$35, &attributes);
						_38$$35 = &_36$$35;
					} else {
						_38$$35 = &attributes;
					}
					zephir_is_iterable(_38$$35, 0, "phalcon/Mvc/Model/Query.zep", 1160);
					if (Z_TYPE_P(_38$$35) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_38$$35), _39$$35)
						{
							ZEPHIR_INIT_NVAR(&attribute);
							ZVAL_COPY(&attribute, _39$$35);
							ZEPHIR_INIT_NVAR(&_40$$38);
							zephir_create_array(&_40$$38, 3, 0);
							zephir_array_fast_append(&_40$$38, &attribute);
							zephir_array_fast_append(&_40$$38, &sqlColumn);
							ZEPHIR_INIT_NVAR(&_41$$38);
							ZEPHIR_CONCAT_SVSV(&_41$$38, "_", &sqlColumn, "_", &attribute);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_fast_append(&_40$$38, &_41$$38);
							zephir_array_append(&selectColumns, &_40$$38, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1153);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _38$$35, "rewind", NULL, 0);
						zephir_check_call_status();
						_43$$35 = 1;
						while (1) {
							if (_43$$35) {
								_43$$35 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _38$$35, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_42$$35, _38$$35, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_42$$35)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&attribute, _38$$35, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_INIT_NVAR(&_44$$39);
								zephir_create_array(&_44$$39, 3, 0);
								zephir_array_fast_append(&_44$$39, &attribute);
								zephir_array_fast_append(&_44$$39, &sqlColumn);
								ZEPHIR_INIT_NVAR(&_45$$39);
								ZEPHIR_CONCAT_SVSV(&_45$$39, "_", &sqlColumn, "_", &attribute);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_fast_append(&_44$$39, &_45$$39);
								zephir_array_append(&selectColumns, &_44$$39, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1153);
						}
					}
					ZEPHIR_INIT_NVAR(&attribute);
					zephir_array_update_multi(&columns1, &instance, SL("zs"), 3, &aliasCopy, SL("instance"));
					zephir_array_update_multi(&columns1, &attributes, SL("zs"), 3, &aliasCopy, SL("attributes"));
					zephir_array_update_multi(&columns1, &columnMap, SL("zs"), 3, &aliasCopy, SL("columnMap"));
					ZEPHIR_CALL_METHOD(&_46$$35, &manager, "isKeepingSnapshots", &_47, 0, &instance);
					zephir_check_call_status();
					isKeepingSnapshots = zephir_get_boolval(&_46$$35);
					if (isKeepingSnapshots) {
						ZEPHIR_INIT_NVAR(&_48$$40);
						ZVAL_BOOL(&_48$$40, isKeepingSnapshots);
						zephir_array_update_multi(&columns1, &_48$$40, SL("zs"), 3, &aliasCopy, SL("keepSnapshots"));
					}
				} else {
					if (Z_TYPE_P(&attributes) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_50$$41);
						zephir_string_to_char_array(&_50$$41, &attributes);
						_49$$41 = &_50$$41;
					} else {
						_49$$41 = &attributes;
					}
					zephir_is_iterable(_49$$41, 0, "phalcon/Mvc/Model/Query.zep", 1177);
					if (Z_TYPE_P(_49$$41) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_49$$41), _51$$41)
						{
							ZEPHIR_INIT_NVAR(&attribute);
							ZVAL_COPY(&attribute, _51$$41);
							ZEPHIR_INIT_NVAR(&_52$$42);
							zephir_create_array(&_52$$42, 2, 0);
							zephir_array_fast_append(&_52$$42, &attribute);
							zephir_array_fast_append(&_52$$42, &sqlColumn);
							zephir_array_append(&selectColumns, &_52$$42, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1175);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _49$$41, "rewind", NULL, 0);
						zephir_check_call_status();
						_54$$41 = 1;
						while (1) {
							if (_54$$41) {
								_54$$41 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _49$$41, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_53$$41, _49$$41, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_53$$41)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&attribute, _49$$41, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_INIT_NVAR(&_55$$43);
								zephir_create_array(&_55$$43, 2, 0);
								zephir_array_fast_append(&_55$$43, &attribute);
								zephir_array_fast_append(&_55$$43, &sqlColumn);
								zephir_array_append(&selectColumns, &_55$$43, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1175);
						}
					}
					ZEPHIR_INIT_NVAR(&attribute);
				}
			} else {
				ZEPHIR_INIT_NVAR(&columnAlias);
				if (Z_TYPE_P(&aliasCopy) == IS_LONG) {
					ZEPHIR_INIT_NVAR(&_56$$45);
					zephir_create_array(&_56$$45, 2, 0);
					zephir_array_fast_append(&_56$$45, &sqlColumn);
					zephir_array_fast_append(&_56$$45, &__$null);
					ZEPHIR_CPY_WRT(&columnAlias, &_56$$45);
				} else {
					ZEPHIR_INIT_NVAR(&_57$$46);
					zephir_create_array(&_57$$46, 3, 0);
					zephir_array_fast_append(&_57$$46, &sqlColumn);
					zephir_array_fast_append(&_57$$46, &__$null);
					zephir_array_fast_append(&_57$$46, &aliasCopy);
					ZEPHIR_CPY_WRT(&columnAlias, &_57$$46);
				}
				zephir_array_append(&selectColumns, &columnAlias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1188);
			}
			_58$$32 = !isComplex;
			if (_58$$32) {
				_58$$32 = isSimpleStd;
			}
			if (_58$$32) {
				ZEPHIR_OBS_NVAR(&sqlAlias);
				if (zephir_array_isset_string_fetch(&sqlAlias, &column, SL("sqlAlias"), 0)) {
					zephir_array_update_zval(&simpleColumnMap, &sqlAlias, &aliasCopy, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&simpleColumnMap, &aliasCopy, &aliasCopy, PH_COPY | PH_SEPARATE);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _25, "rewind", NULL, 0);
		zephir_check_call_status();
		_60 = 1;
		while (1) {
			if (_60) {
				_60 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _25, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_59, _25, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_59)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&aliasCopy, _25, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&column, _25, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&sqlColumn);
				zephir_array_fetch_string(&sqlColumn, &column, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1120);
				ZEPHIR_OBS_NVAR(&_61$$50);
				zephir_array_fetch_string(&_61$$50, &column, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1123);
				if (ZEPHIR_IS_STRING(&_61$$50, "object")) {
					ZEPHIR_OBS_NVAR(&modelName);
					zephir_array_fetch_string(&modelName, &column, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1124);
					ZEPHIR_OBS_NVAR(&instance);
					zephir_read_property_cached(&_62$$51, this_ptr, _zephir_prop_1, 776, PH_NOISY_CC | PH_READONLY);
					if (!(zephir_array_isset_fetch(&instance, &_62$$51, &modelName, 0))) {
						ZEPHIR_CALL_METHOD(&instance, &manager, "load", &_63, 0, &modelName);
						zephir_check_call_status();
						zephir_update_property_array(this_ptr, SL("modelsInstances"), &modelName, &instance);
					}
					ZEPHIR_CALL_METHOD(&attributes, &metaData, "getAttributes", &_64, 0, &instance);
					zephir_check_call_status();
					if (isComplex) {
						ZEPHIR_INIT_NVAR(&_66$$53);
						ZVAL_STRING(&_66$$53, "orm.column_renaming");
						ZEPHIR_CALL_CE_STATIC(&_65$$53, phalcon_support_settings_ce, "get", &_35, 0, &_66$$53);
						zephir_check_call_status();
						if (zephir_is_true(&_65$$53)) {
							ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", &_67, 0, &instance);
							zephir_check_call_status();
						} else {
							ZEPHIR_INIT_NVAR(&columnMap);
							ZVAL_NULL(&columnMap);
						}
						if (Z_TYPE_P(&attributes) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_66$$53);
							zephir_string_to_char_array(&_66$$53, &attributes);
							_68$$53 = &_66$$53;
						} else {
							_68$$53 = &attributes;
						}
						zephir_is_iterable(_68$$53, 0, "phalcon/Mvc/Model/Query.zep", 1160);
						if (Z_TYPE_P(_68$$53) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_68$$53), _69$$53)
							{
								ZEPHIR_INIT_NVAR(&attribute);
								ZVAL_COPY(&attribute, _69$$53);
								ZEPHIR_INIT_NVAR(&_70$$56);
								zephir_create_array(&_70$$56, 3, 0);
								zephir_array_fast_append(&_70$$56, &attribute);
								zephir_array_fast_append(&_70$$56, &sqlColumn);
								ZEPHIR_INIT_NVAR(&_71$$56);
								ZEPHIR_CONCAT_SVSV(&_71$$56, "_", &sqlColumn, "_", &attribute);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_fast_append(&_70$$56, &_71$$56);
								zephir_array_append(&selectColumns, &_70$$56, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1153);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _68$$53, "rewind", NULL, 0);
							zephir_check_call_status();
							_73$$53 = 1;
							while (1) {
								if (_73$$53) {
									_73$$53 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _68$$53, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_72$$53, _68$$53, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_72$$53)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&attribute, _68$$53, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_INIT_NVAR(&_74$$57);
									zephir_create_array(&_74$$57, 3, 0);
									zephir_array_fast_append(&_74$$57, &attribute);
									zephir_array_fast_append(&_74$$57, &sqlColumn);
									ZEPHIR_INIT_NVAR(&_75$$57);
									ZEPHIR_CONCAT_SVSV(&_75$$57, "_", &sqlColumn, "_", &attribute);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_fast_append(&_74$$57, &_75$$57);
									zephir_array_append(&selectColumns, &_74$$57, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1153);
							}
						}
						ZEPHIR_INIT_NVAR(&attribute);
						zephir_array_update_multi(&columns1, &instance, SL("zs"), 3, &aliasCopy, SL("instance"));
						zephir_array_update_multi(&columns1, &attributes, SL("zs"), 3, &aliasCopy, SL("attributes"));
						zephir_array_update_multi(&columns1, &columnMap, SL("zs"), 3, &aliasCopy, SL("columnMap"));
						ZEPHIR_CALL_METHOD(&_76$$53, &manager, "isKeepingSnapshots", &_77, 0, &instance);
						zephir_check_call_status();
						isKeepingSnapshots = zephir_get_boolval(&_76$$53);
						if (isKeepingSnapshots) {
							ZEPHIR_INIT_NVAR(&_78$$58);
							ZVAL_BOOL(&_78$$58, isKeepingSnapshots);
							zephir_array_update_multi(&columns1, &_78$$58, SL("zs"), 3, &aliasCopy, SL("keepSnapshots"));
						}
					} else {
						if (Z_TYPE_P(&attributes) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_80$$59);
							zephir_string_to_char_array(&_80$$59, &attributes);
							_79$$59 = &_80$$59;
						} else {
							_79$$59 = &attributes;
						}
						zephir_is_iterable(_79$$59, 0, "phalcon/Mvc/Model/Query.zep", 1177);
						if (Z_TYPE_P(_79$$59) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_79$$59), _81$$59)
							{
								ZEPHIR_INIT_NVAR(&attribute);
								ZVAL_COPY(&attribute, _81$$59);
								ZEPHIR_INIT_NVAR(&_82$$60);
								zephir_create_array(&_82$$60, 2, 0);
								zephir_array_fast_append(&_82$$60, &attribute);
								zephir_array_fast_append(&_82$$60, &sqlColumn);
								zephir_array_append(&selectColumns, &_82$$60, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1175);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _79$$59, "rewind", NULL, 0);
							zephir_check_call_status();
							_84$$59 = 1;
							while (1) {
								if (_84$$59) {
									_84$$59 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _79$$59, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_83$$59, _79$$59, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_83$$59)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&attribute, _79$$59, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_INIT_NVAR(&_85$$61);
									zephir_create_array(&_85$$61, 2, 0);
									zephir_array_fast_append(&_85$$61, &attribute);
									zephir_array_fast_append(&_85$$61, &sqlColumn);
									zephir_array_append(&selectColumns, &_85$$61, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1175);
							}
						}
						ZEPHIR_INIT_NVAR(&attribute);
					}
				} else {
					if (Z_TYPE_P(&aliasCopy) == IS_LONG) {
						ZEPHIR_INIT_NVAR(&_86$$63);
						zephir_create_array(&_86$$63, 2, 0);
						zephir_array_fast_append(&_86$$63, &sqlColumn);
						zephir_array_fast_append(&_86$$63, &__$null);
						ZEPHIR_CPY_WRT(&columnAlias, &_86$$63);
					} else {
						ZEPHIR_INIT_NVAR(&_87$$64);
						zephir_create_array(&_87$$64, 3, 0);
						zephir_array_fast_append(&_87$$64, &sqlColumn);
						zephir_array_fast_append(&_87$$64, &__$null);
						zephir_array_fast_append(&_87$$64, &aliasCopy);
						ZEPHIR_CPY_WRT(&columnAlias, &_87$$64);
					}
					zephir_array_append(&selectColumns, &columnAlias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1188);
				}
				_88$$50 = !isComplex;
				if (_88$$50) {
					_88$$50 = isSimpleStd;
				}
				if (_88$$50) {
					ZEPHIR_OBS_NVAR(&sqlAlias);
					if (zephir_array_isset_string_fetch(&sqlAlias, &column, SL("sqlAlias"), 0)) {
						zephir_array_update_zval(&simpleColumnMap, &sqlAlias, &aliasCopy, PH_COPY | PH_SEPARATE);
					} else {
						zephir_array_update_zval(&simpleColumnMap, &aliasCopy, &aliasCopy, PH_COPY | PH_SEPARATE);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	ZEPHIR_INIT_NVAR(&aliasCopy);
	ZEPHIR_INIT_VAR(&processed);
	array_init(&processed);
	ZEPHIR_INIT_VAR(&bindCounts);
	array_init(&bindCounts);
	zephir_array_update_string(&intermediate, SL("columns"), &selectColumns, PH_COPY | PH_SEPARATE);
	zephir_is_iterable(&bindParams, 0, "phalcon/Mvc/Model/Query.zep", 1224);
	if (Z_TYPE_P(&bindParams) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bindParams), _90, _91, _89)
		{
			ZEPHIR_INIT_NVAR(&wildcard);
			if (_91 != NULL) { 
				ZVAL_STR_COPY(&wildcard, _91);
			} else {
				ZVAL_LONG(&wildcard, _90);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _89);
			if (Z_TYPE_P(&wildcard) == IS_LONG) {
				ZEPHIR_INIT_NVAR(&wildcardValue);
				ZEPHIR_CONCAT_SV(&wildcardValue, ":", &wildcard);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&wildcardValue, &wildcard);
			}
			zephir_array_update_zval(&processed, &wildcardValue, &value, PH_COPY | PH_SEPARATE);
			if (Z_TYPE_P(&value) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(&_92$$71);
				ZVAL_LONG(&_92$$71, zephir_fast_count_int(&value));
				zephir_array_update_zval(&bindCounts, &wildcardValue, &_92$$71, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &bindParams, "rewind", NULL, 0);
		zephir_check_call_status();
		_94 = 1;
		while (1) {
			if (_94) {
				_94 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bindParams, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_93, &bindParams, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_93)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&wildcard, &bindParams, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &bindParams, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&wildcard) == IS_LONG) {
					ZEPHIR_INIT_NVAR(&wildcardValue);
					ZEPHIR_CONCAT_SV(&wildcardValue, ":", &wildcard);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&wildcardValue, &wildcard);
				}
				zephir_array_update_zval(&processed, &wildcardValue, &value, PH_COPY | PH_SEPARATE);
				if (Z_TYPE_P(&value) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&_95$$75);
					ZVAL_LONG(&_95$$75, zephir_fast_count_int(&value));
					zephir_array_update_zval(&bindCounts, &wildcardValue, &_95$$75, PH_COPY | PH_SEPARATE);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&wildcard);
	ZEPHIR_INIT_VAR(&processedTypes);
	array_init(&processedTypes);
	zephir_is_iterable(&bindTypes, 0, "phalcon/Mvc/Model/Query.zep", 1237);
	if (Z_TYPE_P(&bindTypes) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bindTypes), _97, _98, _96)
		{
			ZEPHIR_INIT_NVAR(&typeWildcard);
			if (_98 != NULL) { 
				ZVAL_STR_COPY(&typeWildcard, _98);
			} else {
				ZVAL_LONG(&typeWildcard, _97);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _96);
			if (Z_TYPE_P(&typeWildcard) == IS_LONG) {
				ZEPHIR_INIT_NVAR(&_99$$77);
				ZEPHIR_CONCAT_SV(&_99$$77, ":", &typeWildcard);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_update_zval(&processedTypes, &_99$$77, &value, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&processedTypes, &typeWildcard, &value, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &bindTypes, "rewind", NULL, 0);
		zephir_check_call_status();
		_101 = 1;
		while (1) {
			if (_101) {
				_101 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bindTypes, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_100, &bindTypes, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_100)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&typeWildcard, &bindTypes, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &bindTypes, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&typeWildcard) == IS_LONG) {
					ZEPHIR_INIT_NVAR(&_102$$80);
					ZEPHIR_CONCAT_SV(&_102$$80, ":", &typeWildcard);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_zval(&processedTypes, &_102$$80, &value, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&processedTypes, &typeWildcard, &value, PH_COPY | PH_SEPARATE);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&typeWildcard);
	if (zephir_fast_count_int(&bindCounts)) {
		zephir_array_update_string(&intermediate, SL("bindCounts"), &bindCounts, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_CALL_METHOD(&dialect, &connection, "getDialect", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&sqlSelect, &dialect, "select", NULL, 0, &intermediate);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 774, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(&_103$$83, &dialect, "sharedLock", NULL, 0, &sqlSelect);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&sqlSelect, &_103$$83);
	}
	if (Z_TYPE_P(&processed) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_105);
		zephir_string_to_char_array(&_105, &processed);
		_104 = &_105;
	} else {
		_104 = &processed;
	}
	zephir_is_iterable(_104, 0, "phalcon/Mvc/Model/Query.zep", 1272);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_104), _107, _108, _106)
	{
		ZEPHIR_INIT_NVAR(&wildcard);
		if (_108 != NULL) { 
			ZVAL_STR_COPY(&wildcard, _108);
		} else {
			ZVAL_LONG(&wildcard, _107);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _106);
		_109$$84 = Z_TYPE_P(&value) == IS_OBJECT;
		if (_109$$84) {
			_109$$84 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
		}
		if (_109$$84) {
			ZVAL_LONG(&_110$$85, 0);
			ZVAL_LONG(&_111$$85, 1);
			ZEPHIR_INIT_NVAR(&_112$$85);
			zephir_substr(&_112$$85, &wildcard, 0 , 1 , 0);
			if (ZEPHIR_IS_STRING_IDENTICAL(&_112$$85, ":")) {
				ZEPHIR_INIT_NVAR(&_113$$86);
				zephir_cast_to_string(&_114$$86, &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_fast_str_replace(&_113$$86, &wildcard, &_114$$86, &sqlSelect);
				ZEPHIR_CPY_WRT(&sqlSelect, &_113$$86);
			} else {
				ZEPHIR_INIT_NVAR(&_115$$87);
				ZEPHIR_INIT_NVAR(&_116$$87);
				ZEPHIR_CONCAT_SV(&_116$$87, ":", &wildcard);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_cast_to_string(&_117$$87, &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_fast_str_replace(&_115$$87, &_116$$87, &_117$$87, &sqlSelect);
				ZEPHIR_CPY_WRT(&sqlSelect, &_115$$87);
			}
			zephir_array_unset(&processed, &wildcard, PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_unset(&processedTypes, &wildcard, PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&wildcard);
	if (simulate) {
		zephir_create_array(return_value, 3, 0);
		zephir_array_update_string(return_value, SL("sql"), &sqlSelect, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(return_value, SL("bind"), &processed, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(return_value, SL("bindTypes"), &processedTypes, PH_COPY | PH_SEPARATE);
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&result, &connection, "query", NULL, 0, &sqlSelect, &processed, &processedTypes);
	zephir_check_call_status();
	if (zephir_instance_of_ev(&result, phalcon_db_resultinterface_ce)) {
		ZEPHIR_CPY_WRT(&resultData, &result);
	} else {
		ZEPHIR_INIT_NVAR(&resultData);
		ZVAL_NULL(&resultData);
	}
	zephir_read_property_cached(&_118, this_ptr, _zephir_prop_4, 768, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&cache, &_118);
	if (!(isComplex)) {
		if (isSimpleStd) {
			ZEPHIR_INIT_VAR(&resultObject);
			object_init_ex(&resultObject, phalcon_mvc_model_row_ce);
			if (zephir_has_constructor(&resultObject)) {
				ZEPHIR_CALL_METHOD(NULL, &resultObject, "__construct", NULL, 0);
				zephir_check_call_status();
			}

			isKeepingSnapshots = 0;
		} else {
			if (Z_TYPE_P(&instance) == IS_OBJECT) {
				ZEPHIR_CPY_WRT(&resultObject, &instance);
			} else {
				ZEPHIR_CPY_WRT(&resultObject, &model);
			}
			ZEPHIR_INIT_VAR(&_120$$93);
			ZVAL_STRING(&_120$$93, "orm.cast_on_hydrate");
			ZEPHIR_CALL_CE_STATIC(&_119$$93, phalcon_support_settings_ce, "get", &_35, 0, &_120$$93);
			zephir_check_call_status();
			if (!(zephir_is_true(&_119$$93))) {
				ZEPHIR_CALL_METHOD(&simpleColumnMap, &metaData, "getColumnMap", NULL, 0, &resultObject);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, &resultObject);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&typesColumnMap, &metaData, "getDataTypes", NULL, 0, &resultObject);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&simpleColumnMap);
				if (Z_TYPE_P(&columnMap) == IS_NULL) {
					array_init(&simpleColumnMap);
					ZEPHIR_CALL_METHOD(&_121$$98, &metaData, "getAttributes", NULL, 0, &resultObject);
					zephir_check_call_status();
					if (Z_TYPE_P(&_121$$98) == IS_STRING) {
						ZEPHIR_INIT_VAR(&_123$$98);
						zephir_string_to_char_array(&_123$$98, &_121$$98);
						_122$$98 = &_123$$98;
					} else {
						_122$$98 = &_121$$98;
					}
					zephir_is_iterable(_122$$98, 0, "phalcon/Mvc/Model/Query.zep", 1342);
					if (Z_TYPE_P(_122$$98) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_122$$98), _124$$98)
						{
							ZEPHIR_INIT_NVAR(&attribute);
							ZVAL_COPY(&attribute, _124$$98);
							ZEPHIR_INIT_NVAR(&_125$$99);
							zephir_create_array(&_125$$99, 2, 0);
							zephir_array_fast_append(&_125$$99, &attribute);
							ZEPHIR_OBS_NVAR(&_126$$99);
							zephir_array_fetch(&_126$$99, &typesColumnMap, &attribute, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1340);
							zephir_array_fast_append(&_125$$99, &_126$$99);
							zephir_array_update_zval(&simpleColumnMap, &attribute, &_125$$99, PH_COPY | PH_SEPARATE);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _122$$98, "rewind", NULL, 0);
						zephir_check_call_status();
						_128$$98 = 1;
						while (1) {
							if (_128$$98) {
								_128$$98 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _122$$98, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_127$$98, _122$$98, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_127$$98)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&attribute, _122$$98, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_INIT_NVAR(&_129$$100);
								zephir_create_array(&_129$$100, 2, 0);
								zephir_array_fast_append(&_129$$100, &attribute);
								ZEPHIR_OBS_NVAR(&_130$$100);
								zephir_array_fetch(&_130$$100, &typesColumnMap, &attribute, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1340);
								zephir_array_fast_append(&_129$$100, &_130$$100);
								zephir_array_update_zval(&simpleColumnMap, &attribute, &_129$$100, PH_COPY | PH_SEPARATE);
						}
					}
					ZEPHIR_INIT_NVAR(&attribute);
				} else {
					array_init(&simpleColumnMap);
					if (Z_TYPE_P(&columnMap) == IS_STRING) {
						ZEPHIR_INIT_VAR(&_132$$101);
						zephir_string_to_char_array(&_132$$101, &columnMap);
						_131$$101 = &_132$$101;
					} else {
						_131$$101 = &columnMap;
					}
					zephir_is_iterable(_131$$101, 0, "phalcon/Mvc/Model/Query.zep", 1351);
					if (Z_TYPE_P(_131$$101) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_131$$101), _134$$101, _135$$101, _133$$101)
						{
							ZEPHIR_INIT_NVAR(&column);
							if (_135$$101 != NULL) { 
								ZVAL_STR_COPY(&column, _135$$101);
							} else {
								ZVAL_LONG(&column, _134$$101);
							}
							ZEPHIR_INIT_NVAR(&attribute);
							ZVAL_COPY(&attribute, _133$$101);
							ZEPHIR_INIT_NVAR(&_136$$102);
							zephir_create_array(&_136$$102, 2, 0);
							zephir_array_fast_append(&_136$$102, &attribute);
							ZEPHIR_OBS_NVAR(&_137$$102);
							zephir_array_fetch(&_137$$102, &typesColumnMap, &column, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1349);
							zephir_array_fast_append(&_136$$102, &_137$$102);
							zephir_array_update_zval(&simpleColumnMap, &column, &_136$$102, PH_COPY | PH_SEPARATE);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _131$$101, "rewind", NULL, 0);
						zephir_check_call_status();
						_139$$101 = 1;
						while (1) {
							if (_139$$101) {
								_139$$101 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _131$$101, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_138$$101, _131$$101, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_138$$101)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&column, _131$$101, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&attribute, _131$$101, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_INIT_NVAR(&_140$$103);
								zephir_create_array(&_140$$103, 2, 0);
								zephir_array_fast_append(&_140$$103, &attribute);
								ZEPHIR_OBS_NVAR(&_141$$103);
								zephir_array_fetch(&_141$$103, &typesColumnMap, &column, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1349);
								zephir_array_fast_append(&_140$$103, &_141$$103);
								zephir_array_update_zval(&simpleColumnMap, &column, &_140$$103, PH_COPY | PH_SEPARATE);
						}
					}
					ZEPHIR_INIT_NVAR(&attribute);
					ZEPHIR_INIT_NVAR(&column);
				}
			}
			ZEPHIR_CALL_METHOD(&_142$$93, &manager, "isKeepingSnapshots", NULL, 0, &resultObject);
			zephir_check_call_status();
			isKeepingSnapshots = zephir_get_boolval(&_142$$93);
		}
		_143$$91 = zephir_instance_of_ev(&resultObject, phalcon_mvc_modelinterface_ce);
		if (_143$$91) {
			_143$$91 = (zephir_method_exists_ex(&resultObject, ZEND_STRL("getresultsetclass")) == SUCCESS);
		}
		if (_143$$91) {
			ZEPHIR_CALL_METHOD(&resultsetClassName, &resultObject, "getResultsetClass", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&resultsetClassName)) {
				if (UNEXPECTED(!(zephir_class_exists(&resultsetClassName, 1)))) {
					ZEPHIR_INIT_VAR(&_144$$106);
					object_init_ex(&_144$$106, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_VAR(&_145$$106);
					ZEPHIR_CONCAT_SVS(&_145$$106, "Resultset class \"", &resultsetClassName, "\" not found");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_144$$106, "__construct", NULL, 32, &_145$$106);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_144$$106, "phalcon/Mvc/Model/Query.zep", 1367);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_VAR(&_146$$105);
				ZVAL_STRING(&_146$$105, "Phalcon\\Mvc\\Model\\ResultsetInterface");
				ZEPHIR_CALL_FUNCTION(&_147$$105, "is_subclass_of", NULL, 469, &resultsetClassName, &_146$$105);
				zephir_check_call_status();
				if (UNEXPECTED(!zephir_is_true(&_147$$105))) {
					ZEPHIR_INIT_VAR(&_148$$107);
					object_init_ex(&_148$$107, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_VAR(&_149$$107);
					ZEPHIR_CONCAT_SVS(&_149$$107, "Resultset class \"", &resultsetClassName, "\" must be an implementation of Phalcon\\Mvc\\Model\\ResultsetInterface");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_148$$107, "__construct", NULL, 32, &_149$$107);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_148$$107, "phalcon/Mvc/Model/Query.zep", 1373);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_VAR(&_150$$105);
				zephir_create_array(&_150$$105, 5, 0);
				zephir_array_fast_append(&_150$$105, &simpleColumnMap);
				zephir_array_fast_append(&_150$$105, &resultObject);
				zephir_array_fast_append(&_150$$105, &resultData);
				zephir_array_fast_append(&_150$$105, &cache);
				ZEPHIR_INIT_NVAR(&_146$$105);
				ZVAL_BOOL(&_146$$105, isKeepingSnapshots);
				zephir_array_fast_append(&_150$$105, &_146$$105);
				ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(return_value, &resultsetClassName, &_150$$105);
				zephir_check_call_status();
				RETURN_MM();
			}
		}
		object_init_ex(return_value, phalcon_mvc_model_resultset_simple_ce);
		if (isKeepingSnapshots) {
			ZVAL_BOOL(&_151$$91, 1);
		} else {
			ZVAL_BOOL(&_151$$91, 0);
		}
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 470, &simpleColumnMap, &resultObject, &resultData, &cache, &_151$$91);
		zephir_check_call_status();
		RETURN_MM();
	}
	object_init_ex(return_value, phalcon_mvc_model_resultset_complex_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 497, &columns1, &resultData, &cache);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Executes the UPDATE intermediate representation producing a
 * Phalcon\Mvc\Model\Query\Status
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, executeUpdate)
{
	zend_bool _20;
	zend_string *_6;
	zend_ulong _5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL, *_15 = NULL, *_17 = NULL, *_18 = NULL, *_22 = NULL, *_24 = NULL, *_30 = NULL, *_33 = NULL, *_35 = NULL, *_37 = NULL, *_39 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, models, modelName, model, connection, dialect, fields, values, updateValues, fieldName, value, selectBindParams, selectBindTypes, number, field, records, exprValue, updateValue, wildcard, record, exception, _0, *_2, _3, *_4, _19, _32, _40, _1$$4, _7$$5, _9$$10, _11$$10, _12$$10, _13$$11, _14$$11, _16$$13, _21$$14, _23$$19, _25$$19, _26$$19, _27$$20, _28$$20, _29$$22, _31$$23, _34$$25, _36$$26, _38$$24;
	zval intermediate, bindParams, bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&updateValues);
	ZVAL_UNDEF(&fieldName);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&selectBindParams);
	ZVAL_UNDEF(&selectBindTypes);
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&records);
	ZVAL_UNDEF(&exprValue);
	ZVAL_UNDEF(&updateValue);
	ZVAL_UNDEF(&wildcard);
	ZVAL_UNDEF(&record);
	ZVAL_UNDEF(&exception);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$10);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_16$$13);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_23$$19);
	ZVAL_UNDEF(&_25$$19);
	ZVAL_UNDEF(&_26$$19);
	ZVAL_UNDEF(&_27$$20);
	ZVAL_UNDEF(&_28$$20);
	ZVAL_UNDEF(&_29$$22);
	ZVAL_UNDEF(&_31$$23);
	ZVAL_UNDEF(&_34$$25);
	ZVAL_UNDEF(&_36$$26);
	ZVAL_UNDEF(&_38$$24);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &intermediate_param, &bindParams_param, &bindTypes_param);
	zephir_get_arrval(&intermediate, intermediate_param);
	zephir_get_arrval(&bindParams, bindParams_param);
	zephir_get_arrval(&bindTypes, bindTypes_param);
	ZEPHIR_INIT_VAR(&updateValue);
	zephir_memory_observe(&models);
	zephir_array_fetch_string(&models, &intermediate, SL("models"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1422);
	if (UNEXPECTED(zephir_array_isset_value_long(&models, 1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Updating several models at the same time is still not supported", "phalcon/Mvc/Model/Query.zep", 1427);
		return;
	}
	zephir_memory_observe(&modelName);
	zephir_array_fetch_long(&modelName, &models, 0, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1430);
	zephir_memory_observe(&model);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 776, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&model, &_0, &modelName, 0))) {
		zephir_read_property_cached(&_1$$4, this_ptr, _zephir_prop_1, 772, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&model, &_1$$4, "load", NULL, 0, &modelName);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&connection, this_ptr, "getWriteConnection", NULL, 0, &model, &intermediate, &bindParams, &bindTypes);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&dialect, &connection, "getDialect", NULL, 0);
	zephir_check_call_status();
	zephir_memory_observe(&fields);
	zephir_array_fetch_string(&fields, &intermediate, SL("fields"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1449);
	zephir_memory_observe(&values);
	zephir_array_fetch_string(&values, &intermediate, SL("values"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1450);
	ZEPHIR_INIT_VAR(&updateValues);
	array_init(&updateValues);
	ZEPHIR_CPY_WRT(&selectBindParams, &bindParams);
	ZEPHIR_CPY_WRT(&selectBindTypes, &bindTypes);
	if (Z_TYPE_P(&fields) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &fields);
		_2 = &_3;
	} else {
		_2 = &fields;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/Model/Query.zep", 1522);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_2), _5, _6, _4)
		{
			ZEPHIR_INIT_NVAR(&number);
			if (_6 != NULL) { 
				ZVAL_STR_COPY(&number, _6);
			} else {
				ZVAL_LONG(&number, _5);
			}
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _4);
			ZEPHIR_OBS_NVAR(&value);
			zephir_array_fetch(&value, &values, &number, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1465);
			ZEPHIR_OBS_NVAR(&exprValue);
			zephir_array_fetch_string(&exprValue, &value, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1466);
			if (zephir_array_isset_value_string(&field, SL("balias"))) {
				ZEPHIR_OBS_NVAR(&fieldName);
				zephir_array_fetch_string(&fieldName, &field, SL("balias"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1469);
			} else {
				ZEPHIR_OBS_NVAR(&fieldName);
				zephir_array_fetch_string(&fieldName, &field, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1471);
			}
			ZEPHIR_OBS_NVAR(&_7$$5);
			zephir_array_fetch_string(&_7$$5, &value, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1474);
			if (ZEPHIR_IS_LONG(&_7$$5, 260)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&_7$$5, 258)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&_7$$5, 259)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&_7$$5, 322)) { goto zephir_switch_0_clause_3; }
			if (ZEPHIR_IS_LONG(&_7$$5, 273)) { goto zephir_switch_0_clause_4; }
			if (ZEPHIR_IS_LONG(&_7$$5, 274)) { goto zephir_switch_0_clause_5; }
			if (ZEPHIR_IS_LONG(&_7$$5, 277)) { goto zephir_switch_0_clause_6; }
			if (ZEPHIR_IS_LONG(&_7$$5, 277)) { goto zephir_switch_0_clause_7; }
			goto zephir_switch_0_clause_8;
			zephir_switch_0_clause_0: ;
			zephir_switch_0_clause_1: ;
			zephir_switch_0_clause_2: ;
				ZEPHIR_CALL_METHOD(&updateValue, &dialect, "getSqlExpression", &_8, 0, &exprValue);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_NVAR(&updateValue);
				ZVAL_NULL(&updateValue);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
			zephir_switch_0_clause_5: ;
			zephir_switch_0_clause_6: ;
				ZEPHIR_CALL_METHOD(&_9$$10, &dialect, "getSqlExpression", &_10, 0, &exprValue);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_11$$10);
				ZVAL_STRING(&_11$$10, ":");
				ZEPHIR_INIT_NVAR(&_12$$10);
				ZVAL_STRING(&_12$$10, "");
				ZEPHIR_INIT_NVAR(&wildcard);
				zephir_fast_str_replace(&wildcard, &_11$$10, &_12$$10, &_9$$10);
				ZEPHIR_OBS_NVAR(&updateValue);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&updateValue, &bindParams, &wildcard, 0)))) {
					ZEPHIR_INIT_NVAR(&_13$$11);
					object_init_ex(&_13$$11, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_14$$11);
					ZEPHIR_CONCAT_SVS(&_14$$11, "Bound parameter '", &wildcard, "' cannot be replaced because it's not in the placeholders list");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_13$$11, "__construct", &_15, 32, &_14$$11);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_13$$11, "phalcon/Mvc/Model/Query.zep", 1497);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_unset(&selectBindParams, &wildcard, PH_SEPARATE);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_unset(&selectBindTypes, &wildcard, PH_SEPARATE);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_7: ;
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Not supported", "phalcon/Mvc/Model/Query.zep", 1506);
				return;
			zephir_switch_0_clause_8: ;
				ZEPHIR_INIT_NVAR(&updateValue);
				object_init_ex(&updateValue, phalcon_db_rawvalue_ce);
				ZEPHIR_CALL_METHOD(&_16$$13, &dialect, "getSqlExpression", &_17, 0, &exprValue);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &updateValue, "__construct", &_18, 35, &_16$$13);
				zephir_check_call_status();
				goto zephir_switch_0_end;
			zephir_switch_0_end: ;

			zephir_array_update_zval(&updateValues, &fieldName, &updateValue, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_20 = 1;
		while (1) {
			if (_20) {
				_20 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_19, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_19)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&number, _2, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&field, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&value);
				zephir_array_fetch(&value, &values, &number, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1465);
				ZEPHIR_OBS_NVAR(&exprValue);
				zephir_array_fetch_string(&exprValue, &value, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1466);
				if (zephir_array_isset_value_string(&field, SL("balias"))) {
					ZEPHIR_OBS_NVAR(&fieldName);
					zephir_array_fetch_string(&fieldName, &field, SL("balias"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1469);
				} else {
					ZEPHIR_OBS_NVAR(&fieldName);
					zephir_array_fetch_string(&fieldName, &field, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1471);
				}
				ZEPHIR_OBS_NVAR(&_21$$14);
				zephir_array_fetch_string(&_21$$14, &value, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1474);
				if (ZEPHIR_IS_LONG(&_21$$14, 260)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&_21$$14, 258)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&_21$$14, 259)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&_21$$14, 322)) { goto zephir_switch_1_clause_3; }
				if (ZEPHIR_IS_LONG(&_21$$14, 273)) { goto zephir_switch_1_clause_4; }
				if (ZEPHIR_IS_LONG(&_21$$14, 274)) { goto zephir_switch_1_clause_5; }
				if (ZEPHIR_IS_LONG(&_21$$14, 277)) { goto zephir_switch_1_clause_6; }
				if (ZEPHIR_IS_LONG(&_21$$14, 277)) { goto zephir_switch_1_clause_7; }
				goto zephir_switch_1_clause_8;
				zephir_switch_1_clause_0: ;
				zephir_switch_1_clause_1: ;
				zephir_switch_1_clause_2: ;
					ZEPHIR_CALL_METHOD(&updateValue, &dialect, "getSqlExpression", &_22, 0, &exprValue);
					zephir_check_call_status();
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_NVAR(&updateValue);
					ZVAL_NULL(&updateValue);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
				zephir_switch_1_clause_5: ;
				zephir_switch_1_clause_6: ;
					ZEPHIR_CALL_METHOD(&_23$$19, &dialect, "getSqlExpression", &_24, 0, &exprValue);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_25$$19);
					ZVAL_STRING(&_25$$19, ":");
					ZEPHIR_INIT_NVAR(&_26$$19);
					ZVAL_STRING(&_26$$19, "");
					ZEPHIR_INIT_NVAR(&wildcard);
					zephir_fast_str_replace(&wildcard, &_25$$19, &_26$$19, &_23$$19);
					ZEPHIR_OBS_NVAR(&updateValue);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&updateValue, &bindParams, &wildcard, 0)))) {
						ZEPHIR_INIT_NVAR(&_27$$20);
						object_init_ex(&_27$$20, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_28$$20);
						ZEPHIR_CONCAT_SVS(&_28$$20, "Bound parameter '", &wildcard, "' cannot be replaced because it's not in the placeholders list");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_27$$20, "__construct", &_15, 32, &_28$$20);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_27$$20, "phalcon/Mvc/Model/Query.zep", 1497);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_unset(&selectBindParams, &wildcard, PH_SEPARATE);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_unset(&selectBindTypes, &wildcard, PH_SEPARATE);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_7: ;
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Not supported", "phalcon/Mvc/Model/Query.zep", 1506);
					return;
				zephir_switch_1_clause_8: ;
					ZEPHIR_INIT_NVAR(&updateValue);
					object_init_ex(&updateValue, phalcon_db_rawvalue_ce);
					ZEPHIR_CALL_METHOD(&_29$$22, &dialect, "getSqlExpression", &_30, 0, &exprValue);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &updateValue, "__construct", &_18, 35, &_29$$22);
					zephir_check_call_status();
					goto zephir_switch_1_end;
				zephir_switch_1_end: ;

				zephir_array_update_zval(&updateValues, &fieldName, &updateValue, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&field);
	ZEPHIR_INIT_NVAR(&number);
	ZEPHIR_CALL_METHOD(&records, this_ptr, "getRelatedRecords", NULL, 495, &model, &intermediate, &selectBindParams, &selectBindTypes);
	zephir_check_call_status();
	if (!(zephir_fast_count_int(&records))) {
		object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
		ZVAL_BOOL(&_31$$23, 1);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_31$$23);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&connection, this_ptr, "getWriteConnection", NULL, 0, &model, &intermediate, &bindParams, &bindTypes);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &connection, "begin", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &records, "rewind", NULL, 0);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_CALL_METHOD(&_32, &records, "valid", NULL, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_32))) {
			break;
		}

		/* try_start_1: */

			ZEPHIR_CALL_METHOD(&record, &records, "current", &_33, 0);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_METHOD(NULL, &record, "assign", NULL, 0, &updateValues);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_METHOD(&_34$$25, &record, "update", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			if (!(zephir_is_true(&_34$$25))) {
				ZEPHIR_CALL_METHOD(NULL, &connection, "rollback", &_35, 0);
				zephir_check_call_status_or_jump(try_end_1);
				object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
				ZVAL_BOOL(&_36$$26, 0);
				ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_36$$26, &record);
				zephir_check_call_status_or_jump(try_end_1);
				RETURN_MM();
			}
			ZEPHIR_CALL_METHOD(NULL, &records, "next", &_37, 0);
			zephir_check_call_status_or_jump(try_end_1);

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_NVAR(&_38$$24);
			ZVAL_OBJ(&_38$$24, EG(exception));
			Z_ADDREF_P(&_38$$24);
			if (zephir_is_instance_of(&_38$$24, SL("PDOException"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&exception, &_38$$24);
				ZEPHIR_CALL_METHOD(NULL, &connection, "rollback", &_39, 0);
				zephir_check_call_status();
				zephir_throw_exception_debug(&exception, "phalcon/Mvc/Model/Query.zep", 1572);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &connection, "commit", NULL, 0);
	zephir_check_call_status();
	object_init_ex(return_value, phalcon_mvc_model_query_status_ce);
	ZVAL_BOOL(&_40, 1);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 496, &_40);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Resolves an expression in a single call argument
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getCallArgument)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *argument_param = NULL, _0;
	zval argument;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&argument);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(argument, argument_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &argument_param);
	ZEPHIR_OBS_COPY_OR_DUP(&argument, argument_param);
	zephir_memory_observe(&_0);
	zephir_array_fetch_string(&_0, &argument, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1589);
	if (ZEPHIR_IS_LONG(&_0, 352)) {
		zephir_create_array(return_value, 1, 0);
		add_assoc_stringl_ex(return_value, SL("type"), SL("all"));
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getExpression", NULL, 498, &argument);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Resolves an expression in a single call argument
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getCaseExpression)
{
	zend_bool _13;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *expr_param = NULL, whenClauses, whenExpr, _0, *_1, _2, *_3, _12, _21, _22, _5$$4, _6$$4, _8$$4, _10$$5, _11$$5, _15$$7, _16$$7, _17$$7, _19$$8, _20$$8;
	zval expr, _4$$4, _9$$5, _14$$7, _18$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&whenClauses);
	ZVAL_UNDEF(&whenExpr);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_20$$8);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expr_param);
	ZEPHIR_OBS_COPY_OR_DUP(&expr, expr_param);
	ZEPHIR_INIT_VAR(&whenClauses);
	array_init(&whenClauses);
	zephir_array_fetch_string(&_0, &expr, SL("right"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query.zep", 1607);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query.zep", 1622);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&whenExpr);
			ZVAL_COPY(&whenExpr, _3);
			if (zephir_array_isset_value_string(&whenExpr, SL("right"))) {
				ZEPHIR_INIT_NVAR(&_4$$4);
				zephir_create_array(&_4$$4, 3, 0);
				add_assoc_stringl_ex(&_4$$4, SL("type"), SL("when"));
				ZEPHIR_OBS_NVAR(&_6$$4);
				zephir_array_fetch_string(&_6$$4, &whenExpr, SL("left"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1611);
				ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "getExpression", &_7, 498, &_6$$4);
				zephir_check_call_status();
				zephir_array_update_string(&_4$$4, SL("expr"), &_5$$4, PH_COPY | PH_SEPARATE);
				ZEPHIR_OBS_NVAR(&_8$$4);
				zephir_array_fetch_string(&_8$$4, &whenExpr, SL("right"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1612);
				ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "getExpression", &_7, 498, &_8$$4);
				zephir_check_call_status();
				zephir_array_update_string(&_4$$4, SL("then"), &_5$$4, PH_COPY | PH_SEPARATE);
				zephir_array_append(&whenClauses, &_4$$4, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1613);
			} else {
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_create_array(&_9$$5, 2, 0);
				add_assoc_stringl_ex(&_9$$5, SL("type"), SL("else"));
				ZEPHIR_OBS_NVAR(&_11$$5);
				zephir_array_fetch_string(&_11$$5, &whenExpr, SL("left"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1617);
				ZEPHIR_CALL_METHOD(&_10$$5, this_ptr, "getExpression", &_7, 498, &_11$$5);
				zephir_check_call_status();
				zephir_array_update_string(&_9$$5, SL("expr"), &_10$$5, PH_COPY | PH_SEPARATE);
				zephir_array_append(&whenClauses, &_9$$5, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1618);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_13 = 1;
		while (1) {
			if (_13) {
				_13 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_12, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_12)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&whenExpr, _1, "current", NULL, 0);
			zephir_check_call_status();
				if (zephir_array_isset_value_string(&whenExpr, SL("right"))) {
					ZEPHIR_INIT_NVAR(&_14$$7);
					zephir_create_array(&_14$$7, 3, 0);
					add_assoc_stringl_ex(&_14$$7, SL("type"), SL("when"));
					ZEPHIR_OBS_NVAR(&_16$$7);
					zephir_array_fetch_string(&_16$$7, &whenExpr, SL("left"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1611);
					ZEPHIR_CALL_METHOD(&_15$$7, this_ptr, "getExpression", &_7, 498, &_16$$7);
					zephir_check_call_status();
					zephir_array_update_string(&_14$$7, SL("expr"), &_15$$7, PH_COPY | PH_SEPARATE);
					ZEPHIR_OBS_NVAR(&_17$$7);
					zephir_array_fetch_string(&_17$$7, &whenExpr, SL("right"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1612);
					ZEPHIR_CALL_METHOD(&_15$$7, this_ptr, "getExpression", &_7, 498, &_17$$7);
					zephir_check_call_status();
					zephir_array_update_string(&_14$$7, SL("then"), &_15$$7, PH_COPY | PH_SEPARATE);
					zephir_array_append(&whenClauses, &_14$$7, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1613);
				} else {
					ZEPHIR_INIT_NVAR(&_18$$8);
					zephir_create_array(&_18$$8, 2, 0);
					add_assoc_stringl_ex(&_18$$8, SL("type"), SL("else"));
					ZEPHIR_OBS_NVAR(&_20$$8);
					zephir_array_fetch_string(&_20$$8, &whenExpr, SL("left"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1617);
					ZEPHIR_CALL_METHOD(&_19$$8, this_ptr, "getExpression", &_7, 498, &_20$$8);
					zephir_check_call_status();
					zephir_array_update_string(&_18$$8, SL("expr"), &_19$$8, PH_COPY | PH_SEPARATE);
					zephir_array_append(&whenClauses, &_18$$8, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 1618);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&whenExpr);
	zephir_create_array(return_value, 3, 0);
	add_assoc_stringl_ex(return_value, SL("type"), SL("case"));
	zephir_array_fetch_string(&_22, &expr, SL("left"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query.zep", 1624);
	ZEPHIR_CALL_METHOD(&_21, this_ptr, "getExpression", &_7, 498, &_22);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("expr"), &_21, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("when-clauses"), &whenClauses, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Resolves an expression from its intermediate code into an array
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getExpression)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool quoting, tempNotQuoting = 0, _90$$72;
	zval *expr_param = NULL, *quoting_param = NULL, exprType, exprLeft, exprRight, left, right, listItems, exprListItem, exprReturn, value, escapedValue, exprValue, valueParts, name, bindType, bind, _0$$5, _1$$6, _2$$7, _3$$8, _4$$9, _5$$10, _6$$11, _7$$12, _8$$13, _9$$14, _10$$16, _11$$17, _12$$18, _13$$19, _14$$20, _15$$21, _16$$22, _17$$23, _18$$24, _19$$25, _20$$25, _21$$26, _22$$27, _23$$28, _24$$33, _25$$33, _26$$33, _27$$33, _28$$33, _29$$34, _30$$34, _31$$34, _32$$37, _33$$37, _34$$37, _35$$38, _36$$38, _37$$38, _38$$39, _39$$39, _40$$39, _41$$40, _42$$40, _43$$40, _44$$41, _45$$41, _46$$41, _47$$42, _48$$42, _49$$42, _50$$43, _57$$43, _58$$43, _51$$44, _52$$44, _53$$45, _54$$45, _55$$46, _56$$46, _59$$47, _60$$47, _61$$48, _62$$48, _63$$49, _64$$50, _65$$51, _66$$52, _67$$53, _68$$54, _69$$55, _70$$56, _71$$57, _72$$58, _73$$59, _74$$60, _75$$61, _76$$62, _77$$63, _78$$64, _79$$65, _80$$66, _81$$66, _82$$69, _83$$69, _84$$69, _85$$70, _86$$70, *_87$$72, _89$$72, _88$$73, _91$$74;
	zval expr;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&exprType);
	ZVAL_UNDEF(&exprLeft);
	ZVAL_UNDEF(&exprRight);
	ZVAL_UNDEF(&left);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&listItems);
	ZVAL_UNDEF(&exprListItem);
	ZVAL_UNDEF(&exprReturn);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&escapedValue);
	ZVAL_UNDEF(&exprValue);
	ZVAL_UNDEF(&valueParts);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&bind);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_2$$7);
	ZVAL_UNDEF(&_3$$8);
	ZVAL_UNDEF(&_4$$9);
	ZVAL_UNDEF(&_5$$10);
	ZVAL_UNDEF(&_6$$11);
	ZVAL_UNDEF(&_7$$12);
	ZVAL_UNDEF(&_8$$13);
	ZVAL_UNDEF(&_9$$14);
	ZVAL_UNDEF(&_10$$16);
	ZVAL_UNDEF(&_11$$17);
	ZVAL_UNDEF(&_12$$18);
	ZVAL_UNDEF(&_13$$19);
	ZVAL_UNDEF(&_14$$20);
	ZVAL_UNDEF(&_15$$21);
	ZVAL_UNDEF(&_16$$22);
	ZVAL_UNDEF(&_17$$23);
	ZVAL_UNDEF(&_18$$24);
	ZVAL_UNDEF(&_19$$25);
	ZVAL_UNDEF(&_20$$25);
	ZVAL_UNDEF(&_21$$26);
	ZVAL_UNDEF(&_22$$27);
	ZVAL_UNDEF(&_23$$28);
	ZVAL_UNDEF(&_24$$33);
	ZVAL_UNDEF(&_25$$33);
	ZVAL_UNDEF(&_26$$33);
	ZVAL_UNDEF(&_27$$33);
	ZVAL_UNDEF(&_28$$33);
	ZVAL_UNDEF(&_29$$34);
	ZVAL_UNDEF(&_30$$34);
	ZVAL_UNDEF(&_31$$34);
	ZVAL_UNDEF(&_32$$37);
	ZVAL_UNDEF(&_33$$37);
	ZVAL_UNDEF(&_34$$37);
	ZVAL_UNDEF(&_35$$38);
	ZVAL_UNDEF(&_36$$38);
	ZVAL_UNDEF(&_37$$38);
	ZVAL_UNDEF(&_38$$39);
	ZVAL_UNDEF(&_39$$39);
	ZVAL_UNDEF(&_40$$39);
	ZVAL_UNDEF(&_41$$40);
	ZVAL_UNDEF(&_42$$40);
	ZVAL_UNDEF(&_43$$40);
	ZVAL_UNDEF(&_44$$41);
	ZVAL_UNDEF(&_45$$41);
	ZVAL_UNDEF(&_46$$41);
	ZVAL_UNDEF(&_47$$42);
	ZVAL_UNDEF(&_48$$42);
	ZVAL_UNDEF(&_49$$42);
	ZVAL_UNDEF(&_50$$43);
	ZVAL_UNDEF(&_57$$43);
	ZVAL_UNDEF(&_58$$43);
	ZVAL_UNDEF(&_51$$44);
	ZVAL_UNDEF(&_52$$44);
	ZVAL_UNDEF(&_53$$45);
	ZVAL_UNDEF(&_54$$45);
	ZVAL_UNDEF(&_55$$46);
	ZVAL_UNDEF(&_56$$46);
	ZVAL_UNDEF(&_59$$47);
	ZVAL_UNDEF(&_60$$47);
	ZVAL_UNDEF(&_61$$48);
	ZVAL_UNDEF(&_62$$48);
	ZVAL_UNDEF(&_63$$49);
	ZVAL_UNDEF(&_64$$50);
	ZVAL_UNDEF(&_65$$51);
	ZVAL_UNDEF(&_66$$52);
	ZVAL_UNDEF(&_67$$53);
	ZVAL_UNDEF(&_68$$54);
	ZVAL_UNDEF(&_69$$55);
	ZVAL_UNDEF(&_70$$56);
	ZVAL_UNDEF(&_71$$57);
	ZVAL_UNDEF(&_72$$58);
	ZVAL_UNDEF(&_73$$59);
	ZVAL_UNDEF(&_74$$60);
	ZVAL_UNDEF(&_75$$61);
	ZVAL_UNDEF(&_76$$62);
	ZVAL_UNDEF(&_77$$63);
	ZVAL_UNDEF(&_78$$64);
	ZVAL_UNDEF(&_79$$65);
	ZVAL_UNDEF(&_80$$66);
	ZVAL_UNDEF(&_81$$66);
	ZVAL_UNDEF(&_82$$69);
	ZVAL_UNDEF(&_83$$69);
	ZVAL_UNDEF(&_84$$69);
	ZVAL_UNDEF(&_85$$70);
	ZVAL_UNDEF(&_86$$70);
	ZVAL_UNDEF(&_89$$72);
	ZVAL_UNDEF(&_88$$73);
	ZVAL_UNDEF(&_91$$74);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("bindParams", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(quoting)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &expr_param, &quoting_param);
	zephir_get_arrval(&expr, expr_param);
	if (!quoting_param) {
		quoting = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&left);
	ZVAL_NULL(&left);
	ZEPHIR_INIT_VAR(&right);
	ZVAL_NULL(&right);
	ZEPHIR_INIT_VAR(&exprReturn);
	zephir_memory_observe(&exprType);
	if (zephir_array_isset_string_fetch(&exprType, &expr, SL("type"), 0)) {
		tempNotQuoting = 1;
		if (!ZEPHIR_IS_LONG(&exprType, 409)) {
			zephir_memory_observe(&exprLeft);
			if (zephir_array_isset_string_fetch(&exprLeft, &expr, SL("left"), 0)) {
				if (tempNotQuoting) {
					ZVAL_BOOL(&_0$$5, 1);
				} else {
					ZVAL_BOOL(&_0$$5, 0);
				}
				ZEPHIR_CALL_METHOD(&left, this_ptr, "getExpression", NULL, 498, &exprLeft, &_0$$5);
				zephir_check_call_status();
			}
			zephir_memory_observe(&exprRight);
			if (zephir_array_isset_string_fetch(&exprRight, &expr, SL("right"), 0)) {
				if (tempNotQuoting) {
					ZVAL_BOOL(&_1$$6, 1);
				} else {
					ZVAL_BOOL(&_1$$6, 0);
				}
				ZEPHIR_CALL_METHOD(&right, this_ptr, "getExpression", NULL, 498, &exprRight, &_1$$6);
				zephir_check_call_status();
			}
		}
		if (ZEPHIR_CHAR_VALUE(&exprType) == '<') { goto zephir_switch_0_clause_0; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '=') { goto zephir_switch_0_clause_1; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '>') { goto zephir_switch_0_clause_2; }
		if (ZEPHIR_IS_LONG(&exprType, 270)) { goto zephir_switch_0_clause_3; }
		if (ZEPHIR_IS_LONG(&exprType, 271)) { goto zephir_switch_0_clause_4; }
		if (ZEPHIR_IS_LONG(&exprType, 272)) { goto zephir_switch_0_clause_5; }
		if (ZEPHIR_IS_LONG(&exprType, 266)) { goto zephir_switch_0_clause_6; }
		if (ZEPHIR_IS_LONG(&exprType, 267)) { goto zephir_switch_0_clause_7; }
		if (ZEPHIR_IS_LONG(&exprType, 355)) { goto zephir_switch_0_clause_8; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '+') { goto zephir_switch_0_clause_9; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '-') { goto zephir_switch_0_clause_10; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '*') { goto zephir_switch_0_clause_11; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '/') { goto zephir_switch_0_clause_12; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '%') { goto zephir_switch_0_clause_13; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '&') { goto zephir_switch_0_clause_14; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '|') { goto zephir_switch_0_clause_15; }
		if (ZEPHIR_IS_LONG(&exprType, 356)) { goto zephir_switch_0_clause_16; }
		if (ZEPHIR_IS_LONG(&exprType, 407)) { goto zephir_switch_0_clause_17; }
		if (ZEPHIR_IS_LONG(&exprType, 367)) { goto zephir_switch_0_clause_18; }
		if (ZEPHIR_IS_LONG(&exprType, 258)) { goto zephir_switch_0_clause_19; }
		if (ZEPHIR_IS_LONG(&exprType, 259)) { goto zephir_switch_0_clause_20; }
		if (ZEPHIR_IS_LONG(&exprType, 414)) { goto zephir_switch_0_clause_21; }
		if (ZEPHIR_IS_LONG(&exprType, 334)) { goto zephir_switch_0_clause_22; }
		if (ZEPHIR_IS_LONG(&exprType, 335)) { goto zephir_switch_0_clause_23; }
		if (ZEPHIR_IS_LONG(&exprType, 260)) { goto zephir_switch_0_clause_24; }
		if (ZEPHIR_IS_LONG(&exprType, 273)) { goto zephir_switch_0_clause_25; }
		if (ZEPHIR_IS_LONG(&exprType, 274)) { goto zephir_switch_0_clause_26; }
		if (ZEPHIR_IS_LONG(&exprType, 277)) { goto zephir_switch_0_clause_27; }
		if (ZEPHIR_IS_LONG(&exprType, 322)) { goto zephir_switch_0_clause_28; }
		if (ZEPHIR_IS_LONG(&exprType, 268)) { goto zephir_switch_0_clause_29; }
		if (ZEPHIR_IS_LONG(&exprType, 351)) { goto zephir_switch_0_clause_30; }
		if (ZEPHIR_IS_LONG(&exprType, 275)) { goto zephir_switch_0_clause_31; }
		if (ZEPHIR_IS_LONG(&exprType, 357)) { goto zephir_switch_0_clause_32; }
		if (ZEPHIR_CHAR_VALUE(&exprType) == '!') { goto zephir_switch_0_clause_33; }
		if (ZEPHIR_IS_LONG(&exprType, 365)) { goto zephir_switch_0_clause_34; }
		if (ZEPHIR_IS_LONG(&exprType, 366)) { goto zephir_switch_0_clause_35; }
		if (ZEPHIR_IS_LONG(&exprType, 315)) { goto zephir_switch_0_clause_36; }
		if (ZEPHIR_IS_LONG(&exprType, 323)) { goto zephir_switch_0_clause_37; }
		if (ZEPHIR_IS_LONG(&exprType, 408)) { goto zephir_switch_0_clause_38; }
		if (ZEPHIR_IS_LONG(&exprType, 330)) { goto zephir_switch_0_clause_39; }
		if (ZEPHIR_IS_LONG(&exprType, 332)) { goto zephir_switch_0_clause_40; }
		if (ZEPHIR_IS_LONG(&exprType, 331)) { goto zephir_switch_0_clause_41; }
		if (ZEPHIR_IS_LONG(&exprType, 276)) { goto zephir_switch_0_clause_42; }
		if (ZEPHIR_IS_LONG(&exprType, 333)) { goto zephir_switch_0_clause_43; }
		if (ZEPHIR_IS_LONG(&exprType, 336)) { goto zephir_switch_0_clause_44; }
		if (ZEPHIR_IS_LONG(&exprType, 358)) { goto zephir_switch_0_clause_45; }
		if (ZEPHIR_IS_LONG(&exprType, 350)) { goto zephir_switch_0_clause_46; }
		if (ZEPHIR_IS_LONG(&exprType, 409)) { goto zephir_switch_0_clause_47; }
		if (ZEPHIR_IS_LONG(&exprType, 309)) { goto zephir_switch_0_clause_48; }
		goto zephir_switch_0_clause_49;
		zephir_switch_0_clause_0: ;
			ZEPHIR_INIT_VAR(&_2$$7);
			zephir_create_array(&_2$$7, 4, 0);
			add_assoc_stringl_ex(&_2$$7, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_2$$7, SL("op"), SL("<"));
			zephir_array_update_string(&_2$$7, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_2$$7, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_2$$7);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_1: ;
			ZEPHIR_INIT_VAR(&_3$$8);
			zephir_create_array(&_3$$8, 4, 0);
			add_assoc_stringl_ex(&_3$$8, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_3$$8, SL("op"), SL("="));
			zephir_array_update_string(&_3$$8, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_3$$8, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_3$$8);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_2: ;
			ZEPHIR_INIT_VAR(&_4$$9);
			zephir_create_array(&_4$$9, 4, 0);
			add_assoc_stringl_ex(&_4$$9, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_4$$9, SL("op"), SL(">"));
			zephir_array_update_string(&_4$$9, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_4$$9, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_4$$9);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_3: ;
			ZEPHIR_INIT_VAR(&_5$$10);
			zephir_create_array(&_5$$10, 4, 0);
			add_assoc_stringl_ex(&_5$$10, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_5$$10, SL("op"), SL("<>"));
			zephir_array_update_string(&_5$$10, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_5$$10, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_5$$10);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_4: ;
			ZEPHIR_INIT_VAR(&_6$$11);
			zephir_create_array(&_6$$11, 4, 0);
			add_assoc_stringl_ex(&_6$$11, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_6$$11, SL("op"), SL("<="));
			zephir_array_update_string(&_6$$11, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_6$$11, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_6$$11);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_5: ;
			ZEPHIR_INIT_VAR(&_7$$12);
			zephir_create_array(&_7$$12, 4, 0);
			add_assoc_stringl_ex(&_7$$12, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_7$$12, SL("op"), SL(">="));
			zephir_array_update_string(&_7$$12, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_7$$12, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_7$$12);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_6: ;
			ZEPHIR_INIT_VAR(&_8$$13);
			zephir_create_array(&_8$$13, 4, 0);
			add_assoc_stringl_ex(&_8$$13, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_8$$13, SL("op"), SL("AND"));
			zephir_array_update_string(&_8$$13, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_8$$13, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_8$$13);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_7: ;
			ZEPHIR_INIT_VAR(&_9$$14);
			zephir_create_array(&_9$$14, 4, 0);
			add_assoc_stringl_ex(&_9$$14, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_9$$14, SL("op"), SL("OR"));
			zephir_array_update_string(&_9$$14, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_9$$14, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_9$$14);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_8: ;
			ZEPHIR_CALL_METHOD(&exprReturn, this_ptr, "getQualified", NULL, 499, &expr);
			zephir_check_call_status();
			goto zephir_switch_0_end;
		zephir_switch_0_clause_9: ;
			ZEPHIR_INIT_VAR(&_10$$16);
			zephir_create_array(&_10$$16, 4, 0);
			add_assoc_stringl_ex(&_10$$16, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_10$$16, SL("op"), SL("+"));
			zephir_array_update_string(&_10$$16, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_10$$16, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_10$$16);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_10: ;
			ZEPHIR_INIT_VAR(&_11$$17);
			zephir_create_array(&_11$$17, 4, 0);
			add_assoc_stringl_ex(&_11$$17, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_11$$17, SL("op"), SL("-"));
			zephir_array_update_string(&_11$$17, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_11$$17, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_11$$17);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_11: ;
			ZEPHIR_INIT_VAR(&_12$$18);
			zephir_create_array(&_12$$18, 4, 0);
			add_assoc_stringl_ex(&_12$$18, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_12$$18, SL("op"), SL("*"));
			zephir_array_update_string(&_12$$18, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_12$$18, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_12$$18);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_12: ;
			ZEPHIR_INIT_VAR(&_13$$19);
			zephir_create_array(&_13$$19, 4, 0);
			add_assoc_stringl_ex(&_13$$19, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_13$$19, SL("op"), SL("/"));
			zephir_array_update_string(&_13$$19, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_13$$19, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_13$$19);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_13: ;
			ZEPHIR_INIT_VAR(&_14$$20);
			zephir_create_array(&_14$$20, 4, 0);
			add_assoc_stringl_ex(&_14$$20, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_14$$20, SL("op"), SL("%"));
			zephir_array_update_string(&_14$$20, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_14$$20, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_14$$20);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_14: ;
			ZEPHIR_INIT_VAR(&_15$$21);
			zephir_create_array(&_15$$21, 4, 0);
			add_assoc_stringl_ex(&_15$$21, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_15$$21, SL("op"), SL("&"));
			zephir_array_update_string(&_15$$21, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$21, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_15$$21);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_15: ;
			ZEPHIR_INIT_VAR(&_16$$22);
			zephir_create_array(&_16$$22, 4, 0);
			add_assoc_stringl_ex(&_16$$22, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_16$$22, SL("op"), SL("|"));
			zephir_array_update_string(&_16$$22, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_16$$22, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_16$$22);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_16: ;
		zephir_switch_0_clause_17: ;
			ZEPHIR_INIT_VAR(&_17$$23);
			zephir_create_array(&_17$$23, 2, 0);
			add_assoc_stringl_ex(&_17$$23, SL("type"), SL("parentheses"));
			zephir_array_update_string(&_17$$23, SL("left"), &left, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_17$$23);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_18: ;
			ZEPHIR_INIT_VAR(&_18$$24);
			zephir_create_array(&_18$$24, 3, 0);
			add_assoc_stringl_ex(&_18$$24, SL("type"), SL("unary-op"));
			add_assoc_stringl_ex(&_18$$24, SL("op"), SL("-"));
			zephir_array_update_string(&_18$$24, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_18$$24);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_19: ;
		zephir_switch_0_clause_20: ;
		zephir_switch_0_clause_21: ;
			ZEPHIR_INIT_VAR(&_19$$25);
			zephir_create_array(&_19$$25, 2, 0);
			add_assoc_stringl_ex(&_19$$25, SL("type"), SL("literal"));
			zephir_memory_observe(&_20$$25);
			zephir_array_fetch_string(&_20$$25, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1840);
			zephir_array_update_string(&_19$$25, SL("value"), &_20$$25, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_19$$25);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_22: ;
			ZEPHIR_INIT_VAR(&_21$$26);
			zephir_create_array(&_21$$26, 2, 0);
			add_assoc_stringl_ex(&_21$$26, SL("type"), SL("literal"));
			add_assoc_stringl_ex(&_21$$26, SL("value"), SL("TRUE"));
			ZEPHIR_CPY_WRT(&exprReturn, &_21$$26);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_23: ;
			ZEPHIR_INIT_VAR(&_22$$27);
			zephir_create_array(&_22$$27, 2, 0);
			add_assoc_stringl_ex(&_22$$27, SL("type"), SL("literal"));
			add_assoc_stringl_ex(&_22$$27, SL("value"), SL("FALSE"));
			ZEPHIR_CPY_WRT(&exprReturn, &_22$$27);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_24: ;
			zephir_memory_observe(&value);
			zephir_array_fetch_string(&value, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1861);
			if (quoting) {
				if (zephir_memnstr_str(&value, SL("'"), "phalcon/Mvc/Model/Query.zep", 1868)) {
					ZEPHIR_INIT_VAR(&escapedValue);
					phalcon_orm_singlequotes(&escapedValue, &value);
				} else {
					ZEPHIR_CPY_WRT(&escapedValue, &value);
				}
				ZEPHIR_INIT_VAR(&exprValue);
				ZEPHIR_CONCAT_SVS(&exprValue, "'", &escapedValue, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&exprValue, &value);
			}
			ZEPHIR_INIT_VAR(&_23$$28);
			zephir_create_array(&_23$$28, 2, 0);
			add_assoc_stringl_ex(&_23$$28, SL("type"), SL("literal"));
			zephir_array_update_string(&_23$$28, SL("value"), &exprValue, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_23$$28);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_25: ;
			ZEPHIR_INIT_VAR(&_24$$33);
			zephir_create_array(&_24$$33, 2, 0);
			add_assoc_stringl_ex(&_24$$33, SL("type"), SL("placeholder"));
			ZEPHIR_INIT_VAR(&_25$$33);
			zephir_memory_observe(&_26$$33);
			zephir_array_fetch_string(&_26$$33, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1889);
			ZEPHIR_INIT_VAR(&_27$$33);
			ZVAL_STRING(&_27$$33, "?");
			ZEPHIR_INIT_VAR(&_28$$33);
			ZVAL_STRING(&_28$$33, ":");
			zephir_fast_str_replace(&_25$$33, &_27$$33, &_28$$33, &_26$$33);
			zephir_array_update_string(&_24$$33, SL("value"), &_25$$33, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_24$$33);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_26: ;
			ZEPHIR_INIT_VAR(&_29$$34);
			zephir_create_array(&_29$$34, 2, 0);
			add_assoc_stringl_ex(&_29$$34, SL("type"), SL("placeholder"));
			zephir_memory_observe(&_30$$34);
			zephir_array_fetch_string(&_30$$34, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1898);
			ZEPHIR_INIT_VAR(&_31$$34);
			ZEPHIR_CONCAT_SV(&_31$$34, ":", &_30$$34);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_update_string(&_29$$34, SL("value"), &_31$$34, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_29$$34);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_27: ;
			ZEPHIR_OBS_NVAR(&value);
			zephir_array_fetch_string(&value, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1903);
			if (zephir_memnstr_str(&value, SL(":"), "phalcon/Mvc/Model/Query.zep", 1905)) {
				ZEPHIR_INIT_VAR(&valueParts);
				zephir_fast_explode_str(&valueParts, SL(":"), &value, NULL);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_memory_observe(&name);
				zephir_array_fetch_long(&name, &valueParts, 0, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1907);
				zephir_memory_observe(&bindType);
				zephir_array_fetch_long(&bindType, &valueParts, 1, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 1908);
				if (ZEPHIR_IS_STRING(&bindType, "str")) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_STRING(&bindType, "int")) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_STRING(&bindType, "double")) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_STRING(&bindType, "bool")) { goto zephir_switch_1_clause_3; }
				if (ZEPHIR_IS_STRING(&bindType, "blob")) { goto zephir_switch_1_clause_4; }
				if (ZEPHIR_IS_STRING(&bindType, "null")) { goto zephir_switch_1_clause_5; }
				if (ZEPHIR_IS_STRING(&bindType, "array")) { goto zephir_switch_1_clause_6; }
				if (ZEPHIR_IS_STRING(&bindType, "array-str")) { goto zephir_switch_1_clause_7; }
				if (ZEPHIR_IS_STRING(&bindType, "array-int")) { goto zephir_switch_1_clause_8; }
				goto zephir_switch_1_clause_9;
				zephir_switch_1_clause_0: ;
					ZEPHIR_INIT_VAR(&_32$$37);
					ZVAL_LONG(&_32$$37, 2);
					zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_32$$37);
					ZEPHIR_INIT_VAR(&_33$$37);
					zephir_create_array(&_33$$37, 2, 0);
					add_assoc_stringl_ex(&_33$$37, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_34$$37);
					ZEPHIR_CONCAT_SV(&_34$$37, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_33$$37, SL("value"), &_34$$37, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&exprReturn, &_33$$37);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					ZEPHIR_INIT_VAR(&_35$$38);
					ZVAL_LONG(&_35$$38, 1);
					zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_35$$38);
					ZEPHIR_INIT_VAR(&_36$$38);
					zephir_create_array(&_36$$38, 2, 0);
					add_assoc_stringl_ex(&_36$$38, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_37$$38);
					ZEPHIR_CONCAT_SV(&_37$$38, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_36$$38, SL("value"), &_37$$38, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&exprReturn, &_36$$38);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_2: ;
					ZEPHIR_INIT_VAR(&_38$$39);
					ZVAL_LONG(&_38$$39, 32);
					zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_38$$39);
					ZEPHIR_INIT_VAR(&_39$$39);
					zephir_create_array(&_39$$39, 2, 0);
					add_assoc_stringl_ex(&_39$$39, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_40$$39);
					ZEPHIR_CONCAT_SV(&_40$$39, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_39$$39, SL("value"), &_40$$39, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&exprReturn, &_39$$39);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_VAR(&_41$$40);
					ZVAL_LONG(&_41$$40, 5);
					zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_41$$40);
					ZEPHIR_INIT_VAR(&_42$$40);
					zephir_create_array(&_42$$40, 2, 0);
					add_assoc_stringl_ex(&_42$$40, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_43$$40);
					ZEPHIR_CONCAT_SV(&_43$$40, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_42$$40, SL("value"), &_43$$40, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&exprReturn, &_42$$40);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_INIT_VAR(&_44$$41);
					ZVAL_LONG(&_44$$41, 3);
					zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_44$$41);
					ZEPHIR_INIT_VAR(&_45$$41);
					zephir_create_array(&_45$$41, 2, 0);
					add_assoc_stringl_ex(&_45$$41, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_46$$41);
					ZEPHIR_CONCAT_SV(&_46$$41, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_45$$41, SL("value"), &_46$$41, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&exprReturn, &_45$$41);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_5: ;
					ZEPHIR_INIT_VAR(&_47$$42);
					ZVAL_LONG(&_47$$42, 0);
					zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_47$$42);
					ZEPHIR_INIT_VAR(&_48$$42);
					zephir_create_array(&_48$$42, 2, 0);
					add_assoc_stringl_ex(&_48$$42, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_49$$42);
					ZEPHIR_CONCAT_SV(&_49$$42, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_48$$42, SL("value"), &_49$$42, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&exprReturn, &_48$$42);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_6: ;
				zephir_switch_1_clause_7: ;
				zephir_switch_1_clause_8: ;
					zephir_memory_observe(&bind);
					zephir_read_property_cached(&_50$$43, this_ptr, _zephir_prop_0, 763, PH_NOISY_CC | PH_READONLY);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&bind, &_50$$43, &name, 0)))) {
						ZEPHIR_INIT_VAR(&_51$$44);
						object_init_ex(&_51$$44, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_VAR(&_52$$44);
						ZEPHIR_CONCAT_SV(&_52$$44, "Bind value is required for array type placeholder: ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_51$$44, "__construct", NULL, 32, &_52$$44);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_51$$44, "phalcon/Mvc/Model/Query.zep", 1978);
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (UNEXPECTED(Z_TYPE_P(&bind) != IS_ARRAY)) {
						ZEPHIR_INIT_VAR(&_53$$45);
						object_init_ex(&_53$$45, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_VAR(&_54$$45);
						ZEPHIR_CONCAT_SV(&_54$$45, "Bind type requires an array in placeholder: ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_53$$45, "__construct", NULL, 32, &_54$$45);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_53$$45, "phalcon/Mvc/Model/Query.zep", 1984);
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (UNEXPECTED(zephir_fast_count_int(&bind) < 1)) {
						ZEPHIR_INIT_VAR(&_55$$46);
						object_init_ex(&_55$$46, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_VAR(&_56$$46);
						ZEPHIR_CONCAT_SV(&_56$$46, "At least one value must be bound in placeholder: ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_55$$46, "__construct", NULL, 32, &_56$$46);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_55$$46, "phalcon/Mvc/Model/Query.zep", 1990);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_VAR(&_57$$43);
					zephir_create_array(&_57$$43, 4, 0);
					add_assoc_stringl_ex(&_57$$43, SL("type"), SL("placeholder"));
					ZEPHIR_INIT_VAR(&_58$$43);
					ZEPHIR_CONCAT_SV(&_58$$43, ":", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_57$$43, SL("value"), &_58$$43, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_57$$43, SL("rawValue"), &name, PH_COPY | PH_SEPARATE);
					add_assoc_long_ex(&_57$$43, SL("times"), zephir_fast_count_int(&bind));
					ZEPHIR_CPY_WRT(&exprReturn, &_57$$43);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_9: ;
					ZEPHIR_INIT_VAR(&_59$$47);
					object_init_ex(&_59$$47, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_VAR(&_60$$47);
					ZEPHIR_CONCAT_SV(&_60$$47, "Unknown bind type: ", &bindType);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_59$$47, "__construct", NULL, 32, &_60$$47);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_59$$47, "phalcon/Mvc/Model/Query.zep", 2005);
					ZEPHIR_MM_RESTORE();
					return;
				zephir_switch_1_end: ;

			} else {
				ZEPHIR_INIT_VAR(&_61$$48);
				zephir_create_array(&_61$$48, 2, 0);
				add_assoc_stringl_ex(&_61$$48, SL("type"), SL("placeholder"));
				ZEPHIR_INIT_VAR(&_62$$48);
				ZEPHIR_CONCAT_SV(&_62$$48, ":", &value);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_update_string(&_61$$48, SL("value"), &_62$$48, PH_COPY | PH_SEPARATE);
				ZEPHIR_CPY_WRT(&exprReturn, &_61$$48);
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_28: ;
			ZEPHIR_INIT_VAR(&_63$$49);
			zephir_create_array(&_63$$49, 2, 0);
			add_assoc_stringl_ex(&_63$$49, SL("type"), SL("literal"));
			add_assoc_stringl_ex(&_63$$49, SL("value"), SL("NULL"));
			ZEPHIR_CPY_WRT(&exprReturn, &_63$$49);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_29: ;
			ZEPHIR_INIT_VAR(&_64$$50);
			zephir_create_array(&_64$$50, 4, 0);
			add_assoc_stringl_ex(&_64$$50, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_64$$50, SL("op"), SL("LIKE"));
			zephir_array_update_string(&_64$$50, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_64$$50, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_64$$50);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_30: ;
			ZEPHIR_INIT_VAR(&_65$$51);
			zephir_create_array(&_65$$51, 4, 0);
			add_assoc_stringl_ex(&_65$$51, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_65$$51, SL("op"), SL("NOT LIKE"));
			zephir_array_update_string(&_65$$51, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_65$$51, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_65$$51);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_31: ;
			ZEPHIR_INIT_VAR(&_66$$52);
			zephir_create_array(&_66$$52, 4, 0);
			add_assoc_stringl_ex(&_66$$52, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_66$$52, SL("op"), SL("ILIKE"));
			zephir_array_update_string(&_66$$52, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_66$$52, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_66$$52);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_32: ;
			ZEPHIR_INIT_VAR(&_67$$53);
			zephir_create_array(&_67$$53, 4, 0);
			add_assoc_stringl_ex(&_67$$53, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_67$$53, SL("op"), SL("NOT ILIKE"));
			zephir_array_update_string(&_67$$53, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_67$$53, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_67$$53);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_33: ;
			ZEPHIR_INIT_VAR(&_68$$54);
			zephir_create_array(&_68$$54, 3, 0);
			add_assoc_stringl_ex(&_68$$54, SL("type"), SL("unary-op"));
			add_assoc_stringl_ex(&_68$$54, SL("op"), SL("NOT "));
			zephir_array_update_string(&_68$$54, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_68$$54);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_34: ;
			ZEPHIR_INIT_VAR(&_69$$55);
			zephir_create_array(&_69$$55, 3, 0);
			add_assoc_stringl_ex(&_69$$55, SL("type"), SL("unary-op"));
			add_assoc_stringl_ex(&_69$$55, SL("op"), SL(" IS NULL"));
			zephir_array_update_string(&_69$$55, SL("left"), &left, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_69$$55);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_35: ;
			ZEPHIR_INIT_VAR(&_70$$56);
			zephir_create_array(&_70$$56, 3, 0);
			add_assoc_stringl_ex(&_70$$56, SL("type"), SL("unary-op"));
			add_assoc_stringl_ex(&_70$$56, SL("op"), SL(" IS NOT NULL"));
			zephir_array_update_string(&_70$$56, SL("left"), &left, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_70$$56);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_36: ;
			ZEPHIR_INIT_VAR(&_71$$57);
			zephir_create_array(&_71$$57, 4, 0);
			add_assoc_stringl_ex(&_71$$57, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_71$$57, SL("op"), SL("IN"));
			zephir_array_update_string(&_71$$57, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_71$$57, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_71$$57);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_37: ;
			ZEPHIR_INIT_VAR(&_72$$58);
			zephir_create_array(&_72$$58, 4, 0);
			add_assoc_stringl_ex(&_72$$58, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_72$$58, SL("op"), SL("NOT IN"));
			zephir_array_update_string(&_72$$58, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_72$$58, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_72$$58);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_38: ;
			ZEPHIR_INIT_VAR(&_73$$59);
			zephir_create_array(&_73$$59, 3, 0);
			add_assoc_stringl_ex(&_73$$59, SL("type"), SL("unary-op"));
			add_assoc_stringl_ex(&_73$$59, SL("op"), SL("EXISTS"));
			zephir_array_update_string(&_73$$59, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_73$$59);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_39: ;
			ZEPHIR_INIT_VAR(&_74$$60);
			zephir_create_array(&_74$$60, 3, 0);
			add_assoc_stringl_ex(&_74$$60, SL("type"), SL("unary-op"));
			add_assoc_stringl_ex(&_74$$60, SL("op"), SL("DISTINCT "));
			zephir_array_update_string(&_74$$60, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_74$$60);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_40: ;
			ZEPHIR_INIT_VAR(&_75$$61);
			zephir_create_array(&_75$$61, 4, 0);
			add_assoc_stringl_ex(&_75$$61, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_75$$61, SL("op"), SL("BETWEEN NOT"));
			zephir_array_update_string(&_75$$61, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_75$$61, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_75$$61);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_41: ;
			ZEPHIR_INIT_VAR(&_76$$62);
			zephir_create_array(&_76$$62, 4, 0);
			add_assoc_stringl_ex(&_76$$62, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_76$$62, SL("op"), SL("BETWEEN"));
			zephir_array_update_string(&_76$$62, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_76$$62, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_76$$62);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_42: ;
			ZEPHIR_INIT_VAR(&_77$$63);
			zephir_create_array(&_77$$63, 4, 0);
			add_assoc_stringl_ex(&_77$$63, SL("type"), SL("binary-op"));
			add_assoc_stringl_ex(&_77$$63, SL("op"), SL("AGAINST"));
			zephir_array_update_string(&_77$$63, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_77$$63, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_77$$63);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_43: ;
			ZEPHIR_INIT_VAR(&_78$$64);
			zephir_create_array(&_78$$64, 3, 0);
			add_assoc_stringl_ex(&_78$$64, SL("type"), SL("cast"));
			zephir_array_update_string(&_78$$64, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_78$$64, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_78$$64);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_44: ;
			ZEPHIR_INIT_VAR(&_79$$65);
			zephir_create_array(&_79$$65, 3, 0);
			add_assoc_stringl_ex(&_79$$65, SL("type"), SL("convert"));
			zephir_array_update_string(&_79$$65, SL("left"), &left, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_79$$65, SL("right"), &right, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_79$$65);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_45: ;
			ZEPHIR_INIT_VAR(&_80$$66);
			zephir_create_array(&_80$$66, 2, 0);
			add_assoc_stringl_ex(&_80$$66, SL("type"), SL("literal"));
			zephir_memory_observe(&_81$$66);
			zephir_array_fetch_string(&_81$$66, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2181);
			zephir_array_update_string(&_80$$66, SL("value"), &_81$$66, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_80$$66);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_46: ;
			ZEPHIR_CALL_METHOD(&exprReturn, this_ptr, "getFunctionCall", NULL, 500, &expr);
			zephir_check_call_status();
			goto zephir_switch_0_end;
		zephir_switch_0_clause_47: ;
			ZEPHIR_CALL_METHOD(&exprReturn, this_ptr, "getCaseExpression", NULL, 501, &expr);
			zephir_check_call_status();
			goto zephir_switch_0_end;
		zephir_switch_0_clause_48: ;
			ZEPHIR_INIT_VAR(&_82$$69);
			zephir_create_array(&_82$$69, 2, 0);
			add_assoc_stringl_ex(&_82$$69, SL("type"), SL("select"));
			ZVAL_BOOL(&_84$$69, 1);
			ZEPHIR_CALL_METHOD(&_83$$69, this_ptr, "_prepareSelect", NULL, 491, &expr, &_84$$69);
			zephir_check_call_status();
			zephir_array_update_string(&_82$$69, SL("value"), &_83$$69, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&exprReturn, &_82$$69);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_49: ;
			ZEPHIR_INIT_VAR(&_85$$70);
			object_init_ex(&_85$$70, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_86$$70);
			ZEPHIR_CONCAT_SV(&_86$$70, "Unknown expression type ", &exprType);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_85$$70, "__construct", NULL, 32, &_86$$70);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_85$$70, "phalcon/Mvc/Model/Query.zep", 2204);
			ZEPHIR_MM_RESTORE();
			return;
		zephir_switch_0_end: ;

		RETURN_CCTOR(&exprReturn);
	}
	if (zephir_array_isset_value_string(&expr, SL("domain"))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getQualified", NULL, 499, &expr);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_array_isset_value_long(&expr, 0)) {
		ZEPHIR_INIT_VAR(&listItems);
		array_init(&listItems);
		zephir_is_iterable(&expr, 0, "phalcon/Mvc/Model/Query.zep", 2227);
		if (Z_TYPE_P(&expr) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&expr), _87$$72)
			{
				ZEPHIR_INIT_NVAR(&exprListItem);
				ZVAL_COPY(&exprListItem, _87$$72);
				ZEPHIR_CALL_METHOD(&_88$$73, this_ptr, "getExpression", NULL, 498, &exprListItem);
				zephir_check_call_status();
				zephir_array_append(&listItems, &_88$$73, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2224);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &expr, "rewind", NULL, 0);
			zephir_check_call_status();
			_90$$72 = 1;
			while (1) {
				if (_90$$72) {
					_90$$72 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, &expr, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_89$$72, &expr, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_89$$72)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&exprListItem, &expr, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_91$$74, this_ptr, "getExpression", NULL, 498, &exprListItem);
					zephir_check_call_status();
					zephir_array_append(&listItems, &_91$$74, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2224);
			}
		}
		ZEPHIR_INIT_NVAR(&exprListItem);
		zephir_create_array(return_value, 2, 0);
		add_assoc_stringl_ex(return_value, SL("type"), SL("list"));
		zephir_array_fast_append(return_value, &listItems);
		RETURN_MM();
	}
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Unknown expression", "phalcon/Mvc/Model/Query.zep", 2233);
	return;
}

/**
 * Resolves an expression in a single call argument
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getFunctionCall)
{
	zend_bool _6$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, distinct = 0;
	zval *expr_param = NULL, arguments, argument, _13, *_0$$6, _1$$6, *_2$$6, _5$$6, _3$$7, _7$$8, _8$$9, _9$$9, _10$$10, _11$$10, _12$$11;
	zval expr, functionArgs;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&functionArgs);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&argument);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$11);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expr_param);
	ZEPHIR_OBS_COPY_OR_DUP(&expr, expr_param);
	zephir_memory_observe(&arguments);
	if (zephir_array_isset_string_fetch(&arguments, &expr, SL("arguments"), 0)) {
		if (zephir_array_isset_value_string(&expr, SL("distinct"))) {
			distinct = 1;
		} else {
			distinct = 0;
		}
		if (zephir_array_isset_value_long(&arguments, 0)) {
			ZEPHIR_INIT_VAR(&functionArgs);
			array_init(&functionArgs);
			if (Z_TYPE_P(&arguments) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_1$$6);
				zephir_string_to_char_array(&_1$$6, &arguments);
				_0$$6 = &_1$$6;
			} else {
				_0$$6 = &arguments;
			}
			zephir_is_iterable(_0$$6, 0, "phalcon/Mvc/Model/Query.zep", 2259);
			if (Z_TYPE_P(_0$$6) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$6), _2$$6)
				{
					ZEPHIR_INIT_NVAR(&argument);
					ZVAL_COPY(&argument, _2$$6);
					ZEPHIR_CALL_METHOD(&_3$$7, this_ptr, "getCallArgument", &_4, 502, &argument);
					zephir_check_call_status();
					zephir_array_append(&functionArgs, &_3$$7, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2257);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0$$6, "rewind", NULL, 0);
				zephir_check_call_status();
				_6$$6 = 1;
				while (1) {
					if (_6$$6) {
						_6$$6 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _0$$6, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_5$$6, _0$$6, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_5$$6)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&argument, _0$$6, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_7$$8, this_ptr, "getCallArgument", &_4, 502, &argument);
						zephir_check_call_status();
						zephir_array_append(&functionArgs, &_7$$8, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2257);
				}
			}
			ZEPHIR_INIT_NVAR(&argument);
		} else {
			ZEPHIR_INIT_VAR(&_8$$9);
			zephir_create_array(&_8$$9, 1, 0);
			ZEPHIR_CALL_METHOD(&_9$$9, this_ptr, "getCallArgument", &_4, 502, &arguments);
			zephir_check_call_status();
			zephir_array_fast_append(&_8$$9, &_9$$9);
			ZEPHIR_CPY_WRT(&functionArgs, &_8$$9);
		}
		if (distinct) {
			zephir_create_array(return_value, 4, 0);
			add_assoc_stringl_ex(return_value, SL("type"), SL("functionCall"));
			zephir_memory_observe(&_10$$10);
			zephir_array_fetch_string(&_10$$10, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2269);
			zephir_array_update_string(return_value, SL("name"), &_10$$10, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(return_value, SL("arguments"), &functionArgs, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_VAR(&_11$$10);
			ZVAL_LONG(&_11$$10, distinct);
			zephir_array_update_string(return_value, SL("distinct"), &_11$$10, PH_COPY | PH_SEPARATE);
			RETURN_MM();
		} else {
			zephir_create_array(return_value, 3, 0);
			add_assoc_stringl_ex(return_value, SL("type"), SL("functionCall"));
			zephir_memory_observe(&_12$$11);
			zephir_array_fetch_string(&_12$$11, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2276);
			zephir_array_update_string(return_value, SL("name"), &_12$$11, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(return_value, SL("arguments"), &functionArgs, PH_COPY | PH_SEPARATE);
			RETURN_MM();
		}
	}
	zephir_create_array(return_value, 2, 0);
	add_assoc_stringl_ex(return_value, SL("type"), SL("functionCall"));
	zephir_memory_observe(&_13);
	zephir_array_fetch_string(&_13, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2285);
	zephir_array_update_string(return_value, SL("name"), &_13, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Returns a processed group clause for a SELECT statement
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getGroupClause)
{
	zend_bool _4$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_2 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *group_param = NULL, groupItem, *_0$$3, _3$$3, _1$$4, _5$$5, _6$$6, _7$$6;
	zval group, groupParts;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&group);
	ZVAL_UNDEF(&groupParts);
	ZVAL_UNDEF(&groupItem);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(group, group_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &group_param);
	ZEPHIR_OBS_COPY_OR_DUP(&group, group_param);
	if (zephir_array_isset_value_long(&group, 0)) {
		ZEPHIR_INIT_VAR(&groupParts);
		array_init(&groupParts);
		zephir_is_iterable(&group, 0, "phalcon/Mvc/Model/Query.zep", 2305);
		if (Z_TYPE_P(&group) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&group), _0$$3)
			{
				ZEPHIR_INIT_NVAR(&groupItem);
				ZVAL_COPY(&groupItem, _0$$3);
				ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "getExpression", &_2, 498, &groupItem);
				zephir_check_call_status();
				zephir_array_append(&groupParts, &_1$$4, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2303);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &group, "rewind", NULL, 0);
			zephir_check_call_status();
			_4$$3 = 1;
			while (1) {
				if (_4$$3) {
					_4$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, &group, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_3$$3, &group, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_3$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&groupItem, &group, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_5$$5, this_ptr, "getExpression", &_2, 498, &groupItem);
					zephir_check_call_status();
					zephir_array_append(&groupParts, &_5$$5, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2303);
			}
		}
		ZEPHIR_INIT_NVAR(&groupItem);
	} else {
		ZEPHIR_INIT_VAR(&_6$$6);
		zephir_create_array(&_6$$6, 1, 0);
		ZEPHIR_CALL_METHOD(&_7$$6, this_ptr, "getExpression", &_2, 498, &group);
		zephir_check_call_status();
		zephir_array_fast_append(&_6$$6, &_7$$6);
		ZEPHIR_CPY_WRT(&groupParts, &_6$$6);
	}
	RETURN_CTOR(&groupParts);
}

/**
 * Returns a processed limit clause for a SELECT statement
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getLimitClause)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *limitClause_param = NULL, number, offset, _0$$3, _1$$4;
	zval limitClause, limit;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&limitClause);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&offset);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(limitClause, limitClause_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &limitClause_param);
	ZEPHIR_OBS_COPY_OR_DUP(&limitClause, limitClause_param);
	ZEPHIR_INIT_VAR(&limit);
	array_init(&limit);
	zephir_memory_observe(&number);
	if (zephir_array_isset_string_fetch(&number, &limitClause, SL("number"), 0)) {
		ZEPHIR_CALL_METHOD(&_0$$3, this_ptr, "getExpression", NULL, 498, &number);
		zephir_check_call_status();
		zephir_array_update_string(&limit, SL("number"), &_0$$3, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&offset);
	if (zephir_array_isset_string_fetch(&offset, &limitClause, SL("offset"), 0)) {
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "getExpression", NULL, 498, &offset);
		zephir_check_call_status();
		zephir_array_update_string(&limit, SL("offset"), &_1$$4, PH_COPY | PH_SEPARATE);
	}
	RETURN_CTOR(&limit);
}

/**
 * Resolves a JOIN clause checking if the associated models exist
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getJoin)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval join;
	zval *manager, manager_sub, *join_param = NULL, qualified, modelName, source, model, schema, _0$$3;

	ZVAL_UNDEF(&manager_sub);
	ZVAL_UNDEF(&qualified);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&join);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(manager, phalcon_mvc_model_managerinterface_ce)
		ZEPHIR_Z_PARAM_ARRAY(join, join_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &manager, &join_param);
	zephir_get_arrval(&join, join_param);
	zephir_memory_observe(&qualified);
	if (zephir_array_isset_string_fetch(&qualified, &join, SL("qualified"), 0)) {
		zephir_memory_observe(&_0$$3);
		zephir_array_fetch_string(&_0$$3, &qualified, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2341);
		if (ZEPHIR_IS_LONG(&_0$$3, 355)) {
			zephir_memory_observe(&modelName);
			zephir_array_fetch_string(&modelName, &qualified, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2342);
			ZEPHIR_CALL_METHOD(&model, manager, "load", NULL, 0, &modelName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
			zephir_check_call_status();
			zephir_create_array(return_value, 4, 0);
			zephir_array_update_string(return_value, SL("schema"), &schema, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(return_value, SL("source"), &source, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(return_value, SL("modelName"), &modelName, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(return_value, SL("model"), &model, PH_COPY | PH_SEPARATE);
			RETURN_MM();
		}
	}
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 2357);
	return;
}

/**
 * Resolves a JOIN type
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getJoinType)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *join_param = NULL, type, _0, _1, _2;
	zval join;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("phql", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(join, join_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &join_param);
	zephir_get_arrval(&join, join_param);
	zephir_memory_observe(&type);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&type, &join, SL("type"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 2368);
		return;
	}
	if (ZEPHIR_IS_LONG(&type, 360)) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_LONG(&type, 361)) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_LONG(&type, 362)) { goto zephir_switch_0_clause_2; }
	if (ZEPHIR_IS_LONG(&type, 363)) { goto zephir_switch_0_clause_3; }
	if (ZEPHIR_IS_LONG(&type, 364)) { goto zephir_switch_0_clause_4; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		RETURN_MM_STRING("INNER");
	zephir_switch_0_clause_1: ;
		RETURN_MM_STRING("LEFT");
	zephir_switch_0_clause_2: ;
		RETURN_MM_STRING("RIGHT");
	zephir_switch_0_clause_3: ;
		RETURN_MM_STRING("CROSS");
	zephir_switch_0_clause_4: ;
		RETURN_MM_STRING("FULL OUTER");
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_mvc_model_exception_ce);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 761, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_CONCAT_SVSV(&_2, "Unknown join type ", &type, ", when preparing: ", &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 32, &_2);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_0, "phalcon/Mvc/Model/Query.zep", 2390);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Processes the JOINs in the query returning an internal representation for
 * the database dialect
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getJoins)
{
	zend_string *_24, *_47, *_30$$19, *_50$$23, *_72$$38;
	zend_ulong _23, _46, _29$$19, _49$$23, _71$$38;
	zend_bool _14, _39, _69, _63$$32, _83$$47;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_5 = NULL, *_9 = NULL, *_26 = NULL, *_51 = NULL, *_52 = NULL, *_57 = NULL, *_58 = NULL, *_73 = NULL, *_74 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *select_param = NULL, __$true, models, sqlAliases, sqlAliasesModels, sqlModelsAliases, sqlAliasesModelsInstances, modelsInstances, fromModels, manager, selectJoins, joinItem, joins, joinData, schema, source, model, realModelName, completeSource, joinType, aliasExpr, alias, joinAliasName, joinExpr, fromModelName, joinAlias, joinModel, joinSource, preCondition, modelNameAlias, relation, relations, modelAlias, sqlJoin, sqlJoinItem, selectTables, tables, tableItem, _0, *_1, _2, *_3, _13, *_22, *_33, _34, *_35, _38, *_42, _43, _44, *_45, _68, _6$$9, _7$$9, _8$$9, _10$$11, _11$$11, _12$$11, _15$$12, _16$$14, _17$$14, _18$$14, _19$$16, _20$$16, _21$$16, _25$$18, _27$$19, *_28$$19, _36$$21, _37$$21, _40$$22, _41$$22, *_48$$23, _53$$28, _54$$28, _55$$28, _56$$29, *_59$$32, _60$$32, *_61$$32, _62$$32, _65$$36, *_70$$38, _75$$43, _76$$43, _77$$43, _78$$44, *_79$$47, _80$$47, *_81$$47, _82$$47, _85$$51;
	zval select, sqlJoins, joinModels, joinSources, joinTypes, joinPreCondition, joinPrepared, _31$$20, _32$$20, _64$$36, _66$$37, _67$$37, _84$$51, _86$$52, _87$$52;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&select);
	ZVAL_UNDEF(&sqlJoins);
	ZVAL_UNDEF(&joinModels);
	ZVAL_UNDEF(&joinSources);
	ZVAL_UNDEF(&joinTypes);
	ZVAL_UNDEF(&joinPreCondition);
	ZVAL_UNDEF(&joinPrepared);
	ZVAL_UNDEF(&_31$$20);
	ZVAL_UNDEF(&_32$$20);
	ZVAL_UNDEF(&_64$$36);
	ZVAL_UNDEF(&_66$$37);
	ZVAL_UNDEF(&_67$$37);
	ZVAL_UNDEF(&_84$$51);
	ZVAL_UNDEF(&_86$$52);
	ZVAL_UNDEF(&_87$$52);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&sqlAliases);
	ZVAL_UNDEF(&sqlAliasesModels);
	ZVAL_UNDEF(&sqlModelsAliases);
	ZVAL_UNDEF(&sqlAliasesModelsInstances);
	ZVAL_UNDEF(&modelsInstances);
	ZVAL_UNDEF(&fromModels);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&selectJoins);
	ZVAL_UNDEF(&joinItem);
	ZVAL_UNDEF(&joins);
	ZVAL_UNDEF(&joinData);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&realModelName);
	ZVAL_UNDEF(&completeSource);
	ZVAL_UNDEF(&joinType);
	ZVAL_UNDEF(&aliasExpr);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&joinAliasName);
	ZVAL_UNDEF(&joinExpr);
	ZVAL_UNDEF(&fromModelName);
	ZVAL_UNDEF(&joinAlias);
	ZVAL_UNDEF(&joinModel);
	ZVAL_UNDEF(&joinSource);
	ZVAL_UNDEF(&preCondition);
	ZVAL_UNDEF(&modelNameAlias);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&relations);
	ZVAL_UNDEF(&modelAlias);
	ZVAL_UNDEF(&sqlJoin);
	ZVAL_UNDEF(&sqlJoinItem);
	ZVAL_UNDEF(&selectTables);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&tableItem);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_43);
	ZVAL_UNDEF(&_44);
	ZVAL_UNDEF(&_68);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_16$$14);
	ZVAL_UNDEF(&_17$$14);
	ZVAL_UNDEF(&_18$$14);
	ZVAL_UNDEF(&_19$$16);
	ZVAL_UNDEF(&_20$$16);
	ZVAL_UNDEF(&_21$$16);
	ZVAL_UNDEF(&_25$$18);
	ZVAL_UNDEF(&_27$$19);
	ZVAL_UNDEF(&_36$$21);
	ZVAL_UNDEF(&_37$$21);
	ZVAL_UNDEF(&_40$$22);
	ZVAL_UNDEF(&_41$$22);
	ZVAL_UNDEF(&_53$$28);
	ZVAL_UNDEF(&_54$$28);
	ZVAL_UNDEF(&_55$$28);
	ZVAL_UNDEF(&_56$$29);
	ZVAL_UNDEF(&_60$$32);
	ZVAL_UNDEF(&_62$$32);
	ZVAL_UNDEF(&_65$$36);
	ZVAL_UNDEF(&_75$$43);
	ZVAL_UNDEF(&_76$$43);
	ZVAL_UNDEF(&_77$$43);
	ZVAL_UNDEF(&_78$$44);
	ZVAL_UNDEF(&_80$$47);
	ZVAL_UNDEF(&_82$$47);
	ZVAL_UNDEF(&_85$$51);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("sqlAliases", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("sqlAliasesModels", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("sqlModelsAliases", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("sqlAliasesModelsInstances", 25, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("phql", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("enableImplicitJoins", 19, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(select, select_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &select_param);
	zephir_get_arrval(&select, select_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 777, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&models, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 778, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&sqlAliases, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 779, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&sqlAliasesModels, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 780, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&sqlModelsAliases, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 781, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&sqlAliasesModelsInstances, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_5, 776, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&modelsInstances, &_0);
	ZEPHIR_CPY_WRT(&fromModels, &models);
	ZEPHIR_INIT_VAR(&sqlJoins);
	array_init(&sqlJoins);
	ZEPHIR_INIT_VAR(&joinModels);
	array_init(&joinModels);
	ZEPHIR_INIT_VAR(&joinSources);
	array_init(&joinSources);
	ZEPHIR_INIT_VAR(&joinTypes);
	array_init(&joinTypes);
	ZEPHIR_INIT_VAR(&joinPreCondition);
	array_init(&joinPreCondition);
	ZEPHIR_INIT_VAR(&joinPrepared);
	array_init(&joinPrepared);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_6, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	zephir_memory_observe(&tables);
	zephir_array_fetch_string(&tables, &select, SL("tables"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2426);
	if (!(zephir_array_isset_value_long(&tables, 0))) {
		ZEPHIR_INIT_VAR(&selectTables);
		zephir_create_array(&selectTables, 1, 0);
		zephir_array_fast_append(&selectTables, &tables);
	} else {
		ZEPHIR_CPY_WRT(&selectTables, &tables);
	}
	zephir_memory_observe(&joins);
	zephir_array_fetch_string(&joins, &select, SL("joins"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2434);
	if (!(zephir_array_isset_value_long(&joins, 0))) {
		ZEPHIR_INIT_VAR(&selectJoins);
		zephir_create_array(&selectJoins, 1, 0);
		zephir_array_fast_append(&selectJoins, &joins);
	} else {
		ZEPHIR_CPY_WRT(&selectJoins, &joins);
	}
	if (Z_TYPE_P(&selectJoins) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &selectJoins);
		_1 = &_2;
	} else {
		_1 = &selectJoins;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query.zep", 2585);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&joinItem);
			ZVAL_COPY(&joinItem, _3);
			ZEPHIR_CALL_METHOD(&joinData, this_ptr, "getJoin", &_4, 503, &manager, &joinItem);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&source);
			zephir_array_fetch_string(&source, &joinData, SL("source"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2448);
			ZEPHIR_OBS_NVAR(&schema);
			zephir_array_fetch_string(&schema, &joinData, SL("schema"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2449);
			ZEPHIR_OBS_NVAR(&model);
			zephir_array_fetch_string(&model, &joinData, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2450);
			ZEPHIR_OBS_NVAR(&realModelName);
			zephir_array_fetch_string(&realModelName, &joinData, SL("modelName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2451);
			ZEPHIR_INIT_NVAR(&completeSource);
			zephir_create_array(&completeSource, 2, 0);
			zephir_array_fast_append(&completeSource, &source);
			zephir_array_fast_append(&completeSource, &schema);
			ZEPHIR_CALL_METHOD(&joinType, this_ptr, "getJoinType", &_5, 504, &joinItem);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&aliasExpr);
			if (zephir_array_isset_string_fetch(&aliasExpr, &joinItem, SL("alias"), 0)) {
				ZEPHIR_OBS_NVAR(&alias);
				zephir_array_fetch_string(&alias, &aliasExpr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2463);
				if (UNEXPECTED(zephir_array_isset_value(&joinModels, &alias))) {
					ZEPHIR_INIT_NVAR(&_6$$9);
					object_init_ex(&_6$$9, phalcon_mvc_model_exception_ce);
					zephir_read_property_cached(&_7$$9, this_ptr, _zephir_prop_7, 761, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_INIT_NVAR(&_8$$9);
					ZEPHIR_CONCAT_SVSV(&_8$$9, "Cannot use '", &alias, "' as join alias because it was already used, when preparing: ", &_7$$9);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_6$$9, "__construct", &_9, 32, &_8$$9);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_6$$9, "phalcon/Mvc/Model/Query.zep", 2471);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2477);
				zephir_array_update_zval(&joinTypes, &alias, &joinType, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&joinModels, &alias, &realModelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlModelsAliases, &realModelName, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModels, &alias, &realModelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&models, &realModelName, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&joinSources, &alias, &completeSource, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&joinPrepared, &alias, &joinItem, PH_COPY | PH_SEPARATE);
			} else {
				if (UNEXPECTED(zephir_array_isset_value(&joinModels, &realModelName))) {
					ZEPHIR_INIT_NVAR(&_10$$11);
					object_init_ex(&_10$$11, phalcon_mvc_model_exception_ce);
					zephir_read_property_cached(&_11$$11, this_ptr, _zephir_prop_7, 761, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_INIT_NVAR(&_12$$11);
					ZEPHIR_CONCAT_SVSV(&_12$$11, "Cannot use '", &realModelName, "' as join alias because it was already used, when preparing: ", &_11$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_10$$11, "__construct", &_9, 32, &_12$$11);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_10$$11, "phalcon/Mvc/Model/Query.zep", 2530);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_update_zval(&joinTypes, &realModelName, &joinType, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliases, &realModelName, &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&joinModels, &realModelName, &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlModelsAliases, &realModelName, &realModelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModels, &realModelName, &realModelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &realModelName, &model, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&models, &realModelName, &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&joinSources, &realModelName, &completeSource, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&joinPrepared, &realModelName, &joinItem, PH_COPY | PH_SEPARATE);
			}
			zephir_array_update_zval(&modelsInstances, &realModelName, &model, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&joinItem, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&joinData, this_ptr, "getJoin", &_4, 503, &manager, &joinItem);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&source);
				zephir_array_fetch_string(&source, &joinData, SL("source"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2448);
				ZEPHIR_OBS_NVAR(&schema);
				zephir_array_fetch_string(&schema, &joinData, SL("schema"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2449);
				ZEPHIR_OBS_NVAR(&model);
				zephir_array_fetch_string(&model, &joinData, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2450);
				ZEPHIR_OBS_NVAR(&realModelName);
				zephir_array_fetch_string(&realModelName, &joinData, SL("modelName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2451);
				ZEPHIR_INIT_NVAR(&_15$$12);
				zephir_create_array(&_15$$12, 2, 0);
				zephir_array_fast_append(&_15$$12, &source);
				zephir_array_fast_append(&_15$$12, &schema);
				ZEPHIR_CPY_WRT(&completeSource, &_15$$12);
				ZEPHIR_CALL_METHOD(&joinType, this_ptr, "getJoinType", &_5, 504, &joinItem);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&aliasExpr);
				if (zephir_array_isset_string_fetch(&aliasExpr, &joinItem, SL("alias"), 0)) {
					ZEPHIR_OBS_NVAR(&alias);
					zephir_array_fetch_string(&alias, &aliasExpr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2463);
					if (UNEXPECTED(zephir_array_isset_value(&joinModels, &alias))) {
						ZEPHIR_INIT_NVAR(&_16$$14);
						object_init_ex(&_16$$14, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_17$$14, this_ptr, _zephir_prop_7, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_18$$14);
						ZEPHIR_CONCAT_SVSV(&_18$$14, "Cannot use '", &alias, "' as join alias because it was already used, when preparing: ", &_17$$14);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_16$$14, "__construct", &_9, 32, &_18$$14);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_16$$14, "phalcon/Mvc/Model/Query.zep", 2471);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2477);
					zephir_array_update_zval(&joinTypes, &alias, &joinType, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&joinModels, &alias, &realModelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlModelsAliases, &realModelName, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModels, &alias, &realModelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&models, &realModelName, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&joinSources, &alias, &completeSource, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&joinPrepared, &alias, &joinItem, PH_COPY | PH_SEPARATE);
				} else {
					if (UNEXPECTED(zephir_array_isset_value(&joinModels, &realModelName))) {
						ZEPHIR_INIT_NVAR(&_19$$16);
						object_init_ex(&_19$$16, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_20$$16, this_ptr, _zephir_prop_7, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_21$$16);
						ZEPHIR_CONCAT_SVSV(&_21$$16, "Cannot use '", &realModelName, "' as join alias because it was already used, when preparing: ", &_20$$16);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_19$$16, "__construct", &_9, 32, &_21$$16);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_19$$16, "phalcon/Mvc/Model/Query.zep", 2530);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_zval(&joinTypes, &realModelName, &joinType, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliases, &realModelName, &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&joinModels, &realModelName, &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlModelsAliases, &realModelName, &realModelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModels, &realModelName, &realModelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &realModelName, &model, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&models, &realModelName, &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&joinSources, &realModelName, &completeSource, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&joinPrepared, &realModelName, &joinItem, PH_COPY | PH_SEPARATE);
				}
				zephir_array_update_zval(&modelsInstances, &realModelName, &model, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&joinItem);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 777, &models);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 778, &sqlAliases);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 779, &sqlAliasesModels);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 780, &sqlModelsAliases);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 781, &sqlAliasesModelsInstances);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 776, &modelsInstances);
	zephir_is_iterable(&joinPrepared, 0, "phalcon/Mvc/Model/Query.zep", 2605);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&joinPrepared), _23, _24, _22)
	{
		ZEPHIR_INIT_NVAR(&joinAliasName);
		if (_24 != NULL) { 
			ZVAL_STR_COPY(&joinAliasName, _24);
		} else {
			ZVAL_LONG(&joinAliasName, _23);
		}
		ZEPHIR_INIT_NVAR(&joinItem);
		ZVAL_COPY(&joinItem, _22);
		ZEPHIR_OBS_NVAR(&joinExpr);
		if (zephir_array_isset_string_fetch(&joinExpr, &joinItem, SL("conditions"), 0)) {
			ZEPHIR_CALL_METHOD(&_25$$18, this_ptr, "getExpression", &_26, 498, &joinExpr);
			zephir_check_call_status();
			zephir_array_update_zval(&joinPreCondition, &joinAliasName, &_25$$18, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&joinItem);
	ZEPHIR_INIT_NVAR(&joinAliasName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_8, 762, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_27$$19);
		zephir_is_iterable(&joinPrepared, 0, "phalcon/Mvc/Model/Query.zep", 2617);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&joinPrepared), _29$$19, _30$$19, _28$$19)
		{
			ZEPHIR_INIT_NVAR(&joinAliasName);
			if (_30$$19 != NULL) { 
				ZVAL_STR_COPY(&joinAliasName, _30$$19);
			} else {
				ZVAL_LONG(&joinAliasName, _29$$19);
			}
			ZEPHIR_INIT_NVAR(&_27$$19);
			ZVAL_COPY(&_27$$19, _28$$19);
			ZEPHIR_OBS_NVAR(&joinType);
			zephir_array_fetch(&joinType, &joinTypes, &joinAliasName, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2607);
			ZEPHIR_OBS_NVAR(&joinSource);
			zephir_array_fetch(&joinSource, &joinSources, &joinAliasName, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2608);
			ZEPHIR_OBS_NVAR(&preCondition);
			zephir_array_fetch(&preCondition, &joinPreCondition, &joinAliasName, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2609);
			ZEPHIR_INIT_NVAR(&_31$$20);
			zephir_create_array(&_31$$20, 3, 0);
			zephir_array_update_string(&_31$$20, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_31$$20, SL("source"), &joinSource, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_32$$20);
			zephir_create_array(&_32$$20, 1, 0);
			zephir_array_fast_append(&_32$$20, &preCondition);
			zephir_array_update_string(&_31$$20, SL("conditions"), &_32$$20, PH_COPY | PH_SEPARATE);
			zephir_array_append(&sqlJoins, &_31$$20, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2614);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&_27$$19);
		ZEPHIR_INIT_NVAR(&joinAliasName);
		RETURN_CTOR(&sqlJoins);
	}
	ZEPHIR_INIT_NVAR(&fromModels);
	array_init(&fromModels);
	if (Z_TYPE_P(&selectTables) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_34);
		zephir_string_to_char_array(&_34, &selectTables);
		_33 = &_34;
	} else {
		_33 = &selectTables;
	}
	zephir_is_iterable(_33, 0, "phalcon/Mvc/Model/Query.zep", 2632);
	if (Z_TYPE_P(_33) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_33), _35)
		{
			ZEPHIR_INIT_NVAR(&tableItem);
			ZVAL_COPY(&tableItem, _35);
			ZEPHIR_OBS_NVAR(&_36$$21);
			zephir_array_fetch_string(&_36$$21, &tableItem, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2626);
			ZEPHIR_OBS_NVAR(&_37$$21);
			zephir_array_fetch_string(&_37$$21, &_36$$21, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2626);
			zephir_array_update_zval(&fromModels, &_37$$21, &__$true, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _33, "rewind", NULL, 0);
		zephir_check_call_status();
		_39 = 1;
		while (1) {
			if (_39) {
				_39 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _33, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_38, _33, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_38)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&tableItem, _33, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_40$$22);
				zephir_array_fetch_string(&_40$$22, &tableItem, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2626);
				ZEPHIR_OBS_NVAR(&_41$$22);
				zephir_array_fetch_string(&_41$$22, &_40$$22, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2626);
				zephir_array_update_zval(&fromModels, &_41$$22, &__$true, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&tableItem);
	if (Z_TYPE_P(&fromModels) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_43);
		zephir_string_to_char_array(&_43, &fromModels);
		_42 = &_43;
	} else {
		_42 = &fromModels;
	}
	ZEPHIR_INIT_VAR(&_44);
	zephir_is_iterable(_42, 0, "phalcon/Mvc/Model/Query.zep", 2752);
	if (Z_TYPE_P(_42) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_42), _46, _47, _45)
		{
			ZEPHIR_INIT_NVAR(&fromModelName);
			if (_47 != NULL) { 
				ZVAL_STR_COPY(&fromModelName, _47);
			} else {
				ZVAL_LONG(&fromModelName, _46);
			}
			ZEPHIR_INIT_NVAR(&_44);
			ZVAL_COPY(&_44, _45);
			zephir_is_iterable(&joinModels, 0, "phalcon/Mvc/Model/Query.zep", 2750);
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&joinModels), _49$$23, _50$$23, _48$$23)
			{
				ZEPHIR_INIT_NVAR(&joinAlias);
				if (_50$$23 != NULL) { 
					ZVAL_STR_COPY(&joinAlias, _50$$23);
				} else {
					ZVAL_LONG(&joinAlias, _49$$23);
				}
				ZEPHIR_INIT_NVAR(&joinModel);
				ZVAL_COPY(&joinModel, _48$$23);
				ZEPHIR_OBS_NVAR(&joinSource);
				zephir_array_fetch(&joinSource, &joinSources, &joinAlias, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2637);
				ZEPHIR_OBS_NVAR(&joinType);
				zephir_array_fetch(&joinType, &joinTypes, &joinAlias, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2642);
				ZEPHIR_OBS_NVAR(&preCondition);
				if (!(zephir_array_isset_fetch(&preCondition, &joinPreCondition, &joinAlias, 0))) {
					ZEPHIR_OBS_NVAR(&modelNameAlias);
					zephir_array_fetch(&modelNameAlias, &sqlAliasesModels, &joinAlias, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2651);
					ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationByAlias", &_51, 0, &fromModelName, &modelNameAlias);
					zephir_check_call_status();
					if (ZEPHIR_IS_FALSE_IDENTICAL(&relation)) {
						ZEPHIR_CALL_METHOD(&relations, &manager, "getRelationsBetween", &_52, 0, &fromModelName, &modelNameAlias);
						zephir_check_call_status();
						if (Z_TYPE_P(&relations) == IS_ARRAY) {
							if (UNEXPECTED(zephir_fast_count_int(&relations) != 1)) {
								ZEPHIR_INIT_NVAR(&_53$$28);
								object_init_ex(&_53$$28, phalcon_mvc_model_exception_ce);
								zephir_read_property_cached(&_54$$28, this_ptr, _zephir_prop_7, 761, PH_NOISY_CC | PH_READONLY);
								ZEPHIR_INIT_NVAR(&_55$$28);
								ZEPHIR_CONCAT_SVSVSV(&_55$$28, "There is more than one relation between models '", &fromModelName, "' and '", &joinModel, "', the join must be done using an alias, when preparing: ", &_54$$28);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_53$$28, "__construct", &_9, 32, &_55$$28);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_53$$28, "phalcon/Mvc/Model/Query.zep", 2677);
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_OBS_NVAR(&relation);
							zephir_array_fetch_long(&relation, &relations, 0, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2683);
						}
					}
					if (Z_TYPE_P(&relation) == IS_OBJECT) {
						ZEPHIR_OBS_NVAR(&modelAlias);
						zephir_array_fetch(&modelAlias, &sqlModelsAliases, &fromModelName, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2694);
						ZEPHIR_CALL_METHOD(&_56$$29, &relation, "isThrough", NULL, 0);
						zephir_check_call_status();
						if (!(zephir_is_true(&_56$$29))) {
							ZEPHIR_CALL_METHOD(&sqlJoin, this_ptr, "getSingleJoin", &_57, 505, &joinType, &joinSource, &modelAlias, &joinAlias, &relation);
							zephir_check_call_status();
						} else {
							ZEPHIR_CALL_METHOD(&sqlJoin, this_ptr, "getMultiJoin", &_58, 506, &joinType, &joinSource, &modelAlias, &joinAlias, &relation);
							zephir_check_call_status();
						}
						if (zephir_array_isset_value_long(&sqlJoin, 0)) {
							if (Z_TYPE_P(&sqlJoin) == IS_STRING) {
								ZEPHIR_INIT_NVAR(&_60$$32);
								zephir_string_to_char_array(&_60$$32, &sqlJoin);
								_59$$32 = &_60$$32;
							} else {
								_59$$32 = &sqlJoin;
							}
							zephir_is_iterable(_59$$32, 0, "phalcon/Mvc/Model/Query.zep", 2724);
							if (Z_TYPE_P(_59$$32) == IS_ARRAY) {
								ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_59$$32), _61$$32)
								{
									ZEPHIR_INIT_NVAR(&sqlJoinItem);
									ZVAL_COPY(&sqlJoinItem, _61$$32);
									zephir_array_append(&sqlJoins, &sqlJoinItem, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2722);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, _59$$32, "rewind", NULL, 0);
								zephir_check_call_status();
								_63$$32 = 1;
								while (1) {
									if (_63$$32) {
										_63$$32 = 0;
									} else {
										ZEPHIR_CALL_METHOD(NULL, _59$$32, "next", NULL, 0);
										zephir_check_call_status();
									}
									ZEPHIR_CALL_METHOD(&_62$$32, _59$$32, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_62$$32)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&sqlJoinItem, _59$$32, "current", NULL, 0);
									zephir_check_call_status();
										zephir_array_append(&sqlJoins, &sqlJoinItem, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2722);
								}
							}
							ZEPHIR_INIT_NVAR(&sqlJoinItem);
						} else {
							zephir_array_append(&sqlJoins, &sqlJoin, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2725);
						}
					} else {
						ZEPHIR_INIT_NVAR(&_64$$36);
						zephir_create_array(&_64$$36, 3, 0);
						zephir_array_update_string(&_64$$36, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_64$$36, SL("source"), &joinSource, PH_COPY | PH_SEPARATE);
						ZEPHIR_INIT_NVAR(&_65$$36);
						array_init(&_65$$36);
						zephir_array_update_string(&_64$$36, SL("conditions"), &_65$$36, PH_COPY | PH_SEPARATE);
						zephir_array_append(&sqlJoins, &_64$$36, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2736);
					}
				} else {
					ZEPHIR_INIT_NVAR(&_66$$37);
					zephir_create_array(&_66$$37, 3, 0);
					zephir_array_update_string(&_66$$37, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_66$$37, SL("source"), &joinSource, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_67$$37);
					zephir_create_array(&_67$$37, 1, 0);
					zephir_array_fast_append(&_67$$37, &preCondition);
					zephir_array_update_string(&_66$$37, SL("conditions"), &_67$$37, PH_COPY | PH_SEPARATE);
					zephir_array_append(&sqlJoins, &_66$$37, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2747);
				}
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&joinModel);
			ZEPHIR_INIT_NVAR(&joinAlias);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _42, "rewind", NULL, 0);
		zephir_check_call_status();
		_69 = 1;
		while (1) {
			if (_69) {
				_69 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _42, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_68, _42, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_68)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&fromModelName, _42, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_44, _42, "current", NULL, 0);
			zephir_check_call_status();
				zephir_is_iterable(&joinModels, 0, "phalcon/Mvc/Model/Query.zep", 2750);
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&joinModels), _71$$38, _72$$38, _70$$38)
				{
					ZEPHIR_INIT_NVAR(&joinAlias);
					if (_72$$38 != NULL) { 
						ZVAL_STR_COPY(&joinAlias, _72$$38);
					} else {
						ZVAL_LONG(&joinAlias, _71$$38);
					}
					ZEPHIR_INIT_NVAR(&joinModel);
					ZVAL_COPY(&joinModel, _70$$38);
					ZEPHIR_OBS_NVAR(&joinSource);
					zephir_array_fetch(&joinSource, &joinSources, &joinAlias, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2637);
					ZEPHIR_OBS_NVAR(&joinType);
					zephir_array_fetch(&joinType, &joinTypes, &joinAlias, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2642);
					ZEPHIR_OBS_NVAR(&preCondition);
					if (!(zephir_array_isset_fetch(&preCondition, &joinPreCondition, &joinAlias, 0))) {
						ZEPHIR_OBS_NVAR(&modelNameAlias);
						zephir_array_fetch(&modelNameAlias, &sqlAliasesModels, &joinAlias, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2651);
						ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationByAlias", &_73, 0, &fromModelName, &modelNameAlias);
						zephir_check_call_status();
						if (ZEPHIR_IS_FALSE_IDENTICAL(&relation)) {
							ZEPHIR_CALL_METHOD(&relations, &manager, "getRelationsBetween", &_74, 0, &fromModelName, &modelNameAlias);
							zephir_check_call_status();
							if (Z_TYPE_P(&relations) == IS_ARRAY) {
								if (UNEXPECTED(zephir_fast_count_int(&relations) != 1)) {
									ZEPHIR_INIT_NVAR(&_75$$43);
									object_init_ex(&_75$$43, phalcon_mvc_model_exception_ce);
									zephir_read_property_cached(&_76$$43, this_ptr, _zephir_prop_7, 761, PH_NOISY_CC | PH_READONLY);
									ZEPHIR_INIT_NVAR(&_77$$43);
									ZEPHIR_CONCAT_SVSVSV(&_77$$43, "There is more than one relation between models '", &fromModelName, "' and '", &joinModel, "', the join must be done using an alias, when preparing: ", &_76$$43);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_75$$43, "__construct", &_9, 32, &_77$$43);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_75$$43, "phalcon/Mvc/Model/Query.zep", 2677);
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_OBS_NVAR(&relation);
								zephir_array_fetch_long(&relation, &relations, 0, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2683);
							}
						}
						if (Z_TYPE_P(&relation) == IS_OBJECT) {
							ZEPHIR_OBS_NVAR(&modelAlias);
							zephir_array_fetch(&modelAlias, &sqlModelsAliases, &fromModelName, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2694);
							ZEPHIR_CALL_METHOD(&_78$$44, &relation, "isThrough", NULL, 0);
							zephir_check_call_status();
							if (!(zephir_is_true(&_78$$44))) {
								ZEPHIR_CALL_METHOD(&sqlJoin, this_ptr, "getSingleJoin", &_57, 505, &joinType, &joinSource, &modelAlias, &joinAlias, &relation);
								zephir_check_call_status();
							} else {
								ZEPHIR_CALL_METHOD(&sqlJoin, this_ptr, "getMultiJoin", &_58, 506, &joinType, &joinSource, &modelAlias, &joinAlias, &relation);
								zephir_check_call_status();
							}
							if (zephir_array_isset_value_long(&sqlJoin, 0)) {
								if (Z_TYPE_P(&sqlJoin) == IS_STRING) {
									ZEPHIR_INIT_NVAR(&_80$$47);
									zephir_string_to_char_array(&_80$$47, &sqlJoin);
									_79$$47 = &_80$$47;
								} else {
									_79$$47 = &sqlJoin;
								}
								zephir_is_iterable(_79$$47, 0, "phalcon/Mvc/Model/Query.zep", 2724);
								if (Z_TYPE_P(_79$$47) == IS_ARRAY) {
									ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_79$$47), _81$$47)
									{
										ZEPHIR_INIT_NVAR(&sqlJoinItem);
										ZVAL_COPY(&sqlJoinItem, _81$$47);
										zephir_array_append(&sqlJoins, &sqlJoinItem, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2722);
									} ZEND_HASH_FOREACH_END();
								} else {
									ZEPHIR_CALL_METHOD(NULL, _79$$47, "rewind", NULL, 0);
									zephir_check_call_status();
									_83$$47 = 1;
									while (1) {
										if (_83$$47) {
											_83$$47 = 0;
										} else {
											ZEPHIR_CALL_METHOD(NULL, _79$$47, "next", NULL, 0);
											zephir_check_call_status();
										}
										ZEPHIR_CALL_METHOD(&_82$$47, _79$$47, "valid", NULL, 0);
										zephir_check_call_status();
										if (!zend_is_true(&_82$$47)) {
											break;
										}
										ZEPHIR_CALL_METHOD(&sqlJoinItem, _79$$47, "current", NULL, 0);
										zephir_check_call_status();
											zephir_array_append(&sqlJoins, &sqlJoinItem, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2722);
									}
								}
								ZEPHIR_INIT_NVAR(&sqlJoinItem);
							} else {
								zephir_array_append(&sqlJoins, &sqlJoin, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2725);
							}
						} else {
							ZEPHIR_INIT_NVAR(&_84$$51);
							zephir_create_array(&_84$$51, 3, 0);
							zephir_array_update_string(&_84$$51, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_84$$51, SL("source"), &joinSource, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_85$$51);
							array_init(&_85$$51);
							zephir_array_update_string(&_84$$51, SL("conditions"), &_85$$51, PH_COPY | PH_SEPARATE);
							zephir_array_append(&sqlJoins, &_84$$51, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2736);
						}
					} else {
						ZEPHIR_INIT_NVAR(&_86$$52);
						zephir_create_array(&_86$$52, 3, 0);
						zephir_array_update_string(&_86$$52, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_86$$52, SL("source"), &joinSource, PH_COPY | PH_SEPARATE);
						ZEPHIR_INIT_NVAR(&_87$$52);
						zephir_create_array(&_87$$52, 1, 0);
						zephir_array_fast_append(&_87$$52, &preCondition);
						zephir_array_update_string(&_86$$52, SL("conditions"), &_87$$52, PH_COPY | PH_SEPARATE);
						zephir_array_append(&sqlJoins, &_86$$52, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2747);
					}
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&joinModel);
				ZEPHIR_INIT_NVAR(&joinAlias);
		}
	}
	ZEPHIR_INIT_NVAR(&_44);
	ZEPHIR_INIT_NVAR(&fromModelName);
	RETURN_CTOR(&sqlJoins);
}

/**
 * Resolves joins involving many-to-many relations
 *
 * @param string joinSource
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getMultiJoin)
{
	zend_bool _15$$3;
	zend_ulong _4$$3;
	zval sqlJoins, _11$$4, _13$$4, _21$$6, _22$$6, _24$$8, _25$$8, _26$$8, _28$$8, _29$$8, _30$$8, _31$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval joinType_zv, *joinSource, joinSource_sub, modelAlias_zv, joinAlias_zv, *relation, relation_sub, fields, referencedFields, intermediateModelName, intermediateModel, intermediateSource, intermediateSchema, intermediateFields, intermediateReferencedFields, referencedModelName, manager, field, position, intermediateField, sqlEqualsJoinCondition, _0, *_1$$3, _2$$3, *_3$$3, _14$$3, _6$$5, _7$$5, _8$$5, _10$$4, _16$$7, _17$$7, _18$$7, _19$$6, _20$$6, _23$$8, _27$$8;
	zend_string *joinType = NULL, *modelAlias = NULL, *joinAlias = NULL, *_5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&joinType_zv);
	ZVAL_UNDEF(&joinSource_sub);
	ZVAL_UNDEF(&modelAlias_zv);
	ZVAL_UNDEF(&joinAlias_zv);
	ZVAL_UNDEF(&relation_sub);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&referencedFields);
	ZVAL_UNDEF(&intermediateModelName);
	ZVAL_UNDEF(&intermediateModel);
	ZVAL_UNDEF(&intermediateSource);
	ZVAL_UNDEF(&intermediateSchema);
	ZVAL_UNDEF(&intermediateFields);
	ZVAL_UNDEF(&intermediateReferencedFields);
	ZVAL_UNDEF(&referencedModelName);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&intermediateField);
	ZVAL_UNDEF(&sqlEqualsJoinCondition);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_27$$8);
	ZVAL_UNDEF(&sqlJoins);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_29$$8);
	ZVAL_UNDEF(&_30$$8);
	ZVAL_UNDEF(&_31$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("phql", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(joinType)
		Z_PARAM_ZVAL(joinSource)
		Z_PARAM_STR(modelAlias)
		Z_PARAM_STR(joinAlias)
		Z_PARAM_OBJECT_OF_CLASS(relation, phalcon_mvc_model_relationinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	joinSource = ZEND_CALL_ARG(execute_data, 2);
	relation = ZEND_CALL_ARG(execute_data, 5);
	zephir_memory_observe(&joinType_zv);
	ZVAL_STR_COPY(&joinType_zv, joinType);
	zephir_memory_observe(&modelAlias_zv);
	ZVAL_STR_COPY(&modelAlias_zv, modelAlias);
	zephir_memory_observe(&joinAlias_zv);
	ZVAL_STR_COPY(&joinAlias_zv, joinAlias);
	ZEPHIR_INIT_VAR(&sqlJoins);
	array_init(&sqlJoins);
	ZEPHIR_CALL_METHOD(&fields, relation, "getFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&referencedFields, relation, "getReferencedFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateModelName, relation, "getIntermediateModel", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&intermediateModel, &manager, "load", NULL, 0, &intermediateModelName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateSource, &intermediateModel, "getSource", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateSchema, &intermediateModel, "getSchema", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("sqlAliases"), &intermediateModelName, &intermediateSource);
	zephir_update_property_array(this_ptr, SL("sqlAliasesModelsInstances"), &intermediateModelName, &intermediateModel);
	ZEPHIR_CALL_METHOD(&intermediateFields, relation, "getIntermediateFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateReferencedFields, relation, "getIntermediateReferencedFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&referencedModelName, relation, "getReferencedModel", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&fields) == IS_ARRAY) {
		if (Z_TYPE_P(&fields) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_2$$3);
			zephir_string_to_char_array(&_2$$3, &fields);
			_1$$3 = &_2$$3;
		} else {
			_1$$3 = &fields;
		}
		zephir_is_iterable(_1$$3, 0, "phalcon/Mvc/Model/Query.zep", 2869);
		if (Z_TYPE_P(_1$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1$$3), _4$$3, _5$$3, _3$$3)
			{
				ZEPHIR_INIT_NVAR(&field);
				if (_5$$3 != NULL) { 
					ZVAL_STR_COPY(&field, _5$$3);
				} else {
					ZVAL_LONG(&field, _4$$3);
				}
				ZEPHIR_INIT_NVAR(&position);
				ZVAL_COPY(&position, _3$$3);
				if (UNEXPECTED(!(zephir_array_isset_value(&referencedFields, &position)))) {
					ZEPHIR_INIT_NVAR(&_6$$5);
					object_init_ex(&_6$$5, phalcon_mvc_model_exception_ce);
					zephir_read_property_cached(&_7$$5, this_ptr, _zephir_prop_1, 761, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_INIT_NVAR(&_8$$5);
					ZEPHIR_CONCAT_SVSVSV(&_8$$5, "The number of fields must be equal to the number of referenced fields in join ", &modelAlias_zv, "-", &joinAlias_zv, ", when preparing: ", &_7$$5);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_6$$5, "__construct", &_9, 32, &_8$$5);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_6$$5, "phalcon/Mvc/Model/Query.zep", 2836);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_OBS_NVAR(&intermediateField);
				zephir_array_fetch(&intermediateField, &intermediateFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2842);
				ZEPHIR_INIT_NVAR(&sqlEqualsJoinCondition);
				zephir_create_array(&sqlEqualsJoinCondition, 4, 0);
				add_assoc_stringl_ex(&sqlEqualsJoinCondition, SL("type"), SL("binary-op"));
				add_assoc_stringl_ex(&sqlEqualsJoinCondition, SL("op"), SL("="));
				ZEPHIR_INIT_NVAR(&_11$$4);
				zephir_create_array(&_11$$4, 3, 0);
				add_assoc_long_ex(&_11$$4, SL("type"), 355);
				zephir_array_update_string(&_11$$4, SL("domain"), &modelAlias_zv, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_11$$4, SL("name"), &field, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_10$$4, this_ptr, "getQualified", &_12, 499, &_11$$4);
				zephir_check_call_status();
				zephir_array_update_string(&sqlEqualsJoinCondition, SL("left"), &_10$$4, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_13$$4);
				zephir_create_array(&_13$$4, 3, 0);
				add_assoc_stringl_ex(&_13$$4, SL("type"), SL("qualified"));
				zephir_array_update_string(&_13$$4, SL("domain"), &joinAlias_zv, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_13$$4, SL("name"), &referencedFields, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_10$$4, this_ptr, "getQualified", &_12, 499, &_13$$4);
				zephir_check_call_status();
				zephir_array_update_string(&sqlEqualsJoinCondition, SL("right"), &_10$$4, PH_COPY | PH_SEPARATE);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _1$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_15$$3 = 1;
			while (1) {
				if (_15$$3) {
					_15$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _1$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_14$$3, _1$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_14$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _1$$3, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&position, _1$$3, "current", NULL, 0);
				zephir_check_call_status();
					if (UNEXPECTED(!(zephir_array_isset_value(&referencedFields, &position)))) {
						ZEPHIR_INIT_NVAR(&_16$$7);
						object_init_ex(&_16$$7, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_17$$7, this_ptr, _zephir_prop_1, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_18$$7);
						ZEPHIR_CONCAT_SVSVSV(&_18$$7, "The number of fields must be equal to the number of referenced fields in join ", &modelAlias_zv, "-", &joinAlias_zv, ", when preparing: ", &_17$$7);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_16$$7, "__construct", &_9, 32, &_18$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_16$$7, "phalcon/Mvc/Model/Query.zep", 2836);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&intermediateField);
					zephir_array_fetch(&intermediateField, &intermediateFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2842);
					ZEPHIR_INIT_NVAR(&_19$$6);
					zephir_create_array(&_19$$6, 4, 0);
					add_assoc_stringl_ex(&_19$$6, SL("type"), SL("binary-op"));
					add_assoc_stringl_ex(&_19$$6, SL("op"), SL("="));
					ZEPHIR_INIT_NVAR(&_21$$6);
					zephir_create_array(&_21$$6, 3, 0);
					add_assoc_long_ex(&_21$$6, SL("type"), 355);
					zephir_array_update_string(&_21$$6, SL("domain"), &modelAlias_zv, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_21$$6, SL("name"), &field, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(&_20$$6, this_ptr, "getQualified", &_12, 499, &_21$$6);
					zephir_check_call_status();
					zephir_array_update_string(&_19$$6, SL("left"), &_20$$6, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_22$$6);
					zephir_create_array(&_22$$6, 3, 0);
					add_assoc_stringl_ex(&_22$$6, SL("type"), SL("qualified"));
					zephir_array_update_string(&_22$$6, SL("domain"), &joinAlias_zv, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_22$$6, SL("name"), &referencedFields, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(&_20$$6, this_ptr, "getQualified", &_12, 499, &_22$$6);
					zephir_check_call_status();
					zephir_array_update_string(&_19$$6, SL("right"), &_20$$6, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&sqlEqualsJoinCondition, &_19$$6);
			}
		}
		ZEPHIR_INIT_NVAR(&position);
		ZEPHIR_INIT_NVAR(&field);
	} else {
		ZEPHIR_INIT_VAR(&_23$$8);
		zephir_create_array(&_23$$8, 2, 0);
		ZEPHIR_INIT_VAR(&_24$$8);
		zephir_create_array(&_24$$8, 3, 0);
		zephir_array_update_string(&_24$$8, SL("type"), &joinType_zv, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_25$$8);
		zephir_create_array(&_25$$8, 2, 0);
		zephir_array_fast_append(&_25$$8, &intermediateSource);
		zephir_array_fast_append(&_25$$8, &intermediateSchema);
		zephir_array_update_string(&_24$$8, SL("source"), &_25$$8, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_25$$8);
		zephir_create_array(&_25$$8, 1, 0);
		ZEPHIR_INIT_VAR(&_26$$8);
		zephir_create_array(&_26$$8, 4, 0);
		add_assoc_stringl_ex(&_26$$8, SL("type"), SL("binary-op"));
		add_assoc_stringl_ex(&_26$$8, SL("op"), SL("="));
		ZEPHIR_INIT_VAR(&_28$$8);
		zephir_create_array(&_28$$8, 3, 0);
		add_assoc_long_ex(&_28$$8, SL("type"), 355);
		zephir_array_update_string(&_28$$8, SL("domain"), &modelAlias_zv, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_28$$8, SL("name"), &fields, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_27$$8, this_ptr, "getQualified", &_12, 499, &_28$$8);
		zephir_check_call_status();
		zephir_array_update_string(&_26$$8, SL("left"), &_27$$8, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_29$$8);
		zephir_create_array(&_29$$8, 3, 0);
		add_assoc_stringl_ex(&_29$$8, SL("type"), SL("qualified"));
		zephir_array_update_string(&_29$$8, SL("domain"), &intermediateModelName, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_29$$8, SL("name"), &intermediateFields, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_27$$8, this_ptr, "getQualified", &_12, 499, &_29$$8);
		zephir_check_call_status();
		zephir_array_update_string(&_26$$8, SL("right"), &_27$$8, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_25$$8, &_26$$8);
		zephir_array_update_string(&_24$$8, SL("conditions"), &_25$$8, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_23$$8, &_24$$8);
		ZEPHIR_INIT_NVAR(&_24$$8);
		zephir_create_array(&_24$$8, 3, 0);
		zephir_array_update_string(&_24$$8, SL("type"), &joinType_zv, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_24$$8, SL("source"), joinSource, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_25$$8);
		zephir_create_array(&_25$$8, 1, 0);
		ZEPHIR_INIT_NVAR(&_26$$8);
		zephir_create_array(&_26$$8, 4, 0);
		add_assoc_stringl_ex(&_26$$8, SL("type"), SL("binary-op"));
		add_assoc_stringl_ex(&_26$$8, SL("op"), SL("="));
		ZEPHIR_INIT_VAR(&_30$$8);
		zephir_create_array(&_30$$8, 3, 0);
		add_assoc_long_ex(&_30$$8, SL("type"), 355);
		zephir_array_update_string(&_30$$8, SL("domain"), &intermediateModelName, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_30$$8, SL("name"), &intermediateReferencedFields, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_27$$8, this_ptr, "getQualified", &_12, 499, &_30$$8);
		zephir_check_call_status();
		zephir_array_update_string(&_26$$8, SL("left"), &_27$$8, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_31$$8);
		zephir_create_array(&_31$$8, 3, 0);
		add_assoc_stringl_ex(&_31$$8, SL("type"), SL("qualified"));
		zephir_array_update_string(&_31$$8, SL("domain"), &referencedModelName, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_31$$8, SL("name"), &referencedFields, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_27$$8, this_ptr, "getQualified", &_12, 499, &_31$$8);
		zephir_check_call_status();
		zephir_array_update_string(&_26$$8, SL("right"), &_27$$8, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_25$$8, &_26$$8);
		zephir_array_update_string(&_24$$8, SL("conditions"), &_25$$8, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_23$$8, &_24$$8);
		ZEPHIR_CPY_WRT(&sqlJoins, &_23$$8);
	}
	RETURN_CTOR(&sqlJoins);
}

/**
 * Returns a processed order clause for a SELECT statement
 *
 * @param array|string order
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getOrderClause)
{
	zend_bool _10;
	zval orderParts, orderPartSort;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *order, order_sub, orderColumns, orderItem, orderPartExpr, orderSort, *_0, _1, *_2, _9, _3$$5, _5$$7, _6$$8, _7$$8, _8$$9, _11$$10, _12$$12, _13$$12, _14$$13, _15$$13, _16$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&order_sub);
	ZVAL_UNDEF(&orderColumns);
	ZVAL_UNDEF(&orderItem);
	ZVAL_UNDEF(&orderPartExpr);
	ZVAL_UNDEF(&orderSort);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_14$$13);
	ZVAL_UNDEF(&_15$$13);
	ZVAL_UNDEF(&_16$$14);
	ZVAL_UNDEF(&orderParts);
	ZVAL_UNDEF(&orderPartSort);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(order)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &order);
	if (!(zephir_array_isset_value_long(order, 0))) {
		ZEPHIR_INIT_VAR(&orderColumns);
		zephir_create_array(&orderColumns, 1, 0);
		zephir_array_fast_append(&orderColumns, order);
	} else {
		ZEPHIR_CPY_WRT(&orderColumns, order);
	}
	ZEPHIR_INIT_VAR(&orderParts);
	array_init(&orderParts);
	if (Z_TYPE_P(&orderColumns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_1);
		zephir_string_to_char_array(&_1, &orderColumns);
		_0 = &_1;
	} else {
		_0 = &orderColumns;
	}
	zephir_is_iterable(_0, 0, "phalcon/Mvc/Model/Query.zep", 2978);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0), _2)
		{
			ZEPHIR_INIT_NVAR(&orderItem);
			ZVAL_COPY(&orderItem, _2);
			ZEPHIR_OBS_NVAR(&_3$$5);
			zephir_array_fetch_string(&_3$$5, &orderItem, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2960);
			ZEPHIR_CALL_METHOD(&orderPartExpr, this_ptr, "getExpression", &_4, 498, &_3$$5);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&orderSort);
			if (zephir_array_isset_string_fetch(&orderSort, &orderItem, SL("sort"), 0)) {
				if (ZEPHIR_IS_LONG(&orderSort, 327)) {
					ZEPHIR_INIT_NVAR(&orderPartSort);
					zephir_create_array(&orderPartSort, 2, 0);
					zephir_array_fast_append(&orderPartSort, &orderPartExpr);
					ZEPHIR_INIT_NVAR(&_5$$7);
					ZVAL_STRING(&_5$$7, "ASC");
					zephir_array_fast_append(&orderPartSort, &_5$$7);
				} else {
					ZEPHIR_INIT_NVAR(&_6$$8);
					zephir_create_array(&_6$$8, 2, 0);
					zephir_array_fast_append(&_6$$8, &orderPartExpr);
					ZEPHIR_INIT_NVAR(&_7$$8);
					ZVAL_STRING(&_7$$8, "DESC");
					zephir_array_fast_append(&_6$$8, &_7$$8);
					ZEPHIR_CPY_WRT(&orderPartSort, &_6$$8);
				}
			} else {
				ZEPHIR_INIT_NVAR(&_8$$9);
				zephir_create_array(&_8$$9, 1, 0);
				zephir_array_fast_append(&_8$$9, &orderPartExpr);
				ZEPHIR_CPY_WRT(&orderPartSort, &_8$$9);
			}
			zephir_array_append(&orderParts, &orderPartSort, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2975);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _0, "rewind", NULL, 0);
		zephir_check_call_status();
		_10 = 1;
		while (1) {
			if (_10) {
				_10 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_9, _0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&orderItem, _0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_11$$10);
				zephir_array_fetch_string(&_11$$10, &orderItem, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2960);
				ZEPHIR_CALL_METHOD(&orderPartExpr, this_ptr, "getExpression", &_4, 498, &_11$$10);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&orderSort);
				if (zephir_array_isset_string_fetch(&orderSort, &orderItem, SL("sort"), 0)) {
					if (ZEPHIR_IS_LONG(&orderSort, 327)) {
						ZEPHIR_INIT_NVAR(&_12$$12);
						zephir_create_array(&_12$$12, 2, 0);
						zephir_array_fast_append(&_12$$12, &orderPartExpr);
						ZEPHIR_INIT_NVAR(&_13$$12);
						ZVAL_STRING(&_13$$12, "ASC");
						zephir_array_fast_append(&_12$$12, &_13$$12);
						ZEPHIR_CPY_WRT(&orderPartSort, &_12$$12);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$13);
						zephir_create_array(&_14$$13, 2, 0);
						zephir_array_fast_append(&_14$$13, &orderPartExpr);
						ZEPHIR_INIT_NVAR(&_15$$13);
						ZVAL_STRING(&_15$$13, "DESC");
						zephir_array_fast_append(&_14$$13, &_15$$13);
						ZEPHIR_CPY_WRT(&orderPartSort, &_14$$13);
					}
				} else {
					ZEPHIR_INIT_NVAR(&_16$$14);
					zephir_create_array(&_16$$14, 1, 0);
					zephir_array_fast_append(&_16$$14, &orderPartExpr);
					ZEPHIR_CPY_WRT(&orderPartSort, &_16$$14);
				}
				zephir_array_append(&orderParts, &orderPartSort, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 2975);
		}
	}
	ZEPHIR_INIT_NVAR(&orderItem);
	RETURN_CTOR(&orderParts);
}

/**
 * Replaces the model's name to its source name in a qualified-name
 * expression
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getQualified)
{
	zend_bool _3, _4, _29$$14;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_24 = NULL, *_31 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, number = 0;
	zval *expr_param = NULL, columnName, nestingLevel, sqlColumnAliases, metaData, sqlAliases, source, sqlAliasesModelsInstances, realColumnName, columnDomain, model, models, columnMap, hasModel, className, _0, _5, _1$$3, _2$$3, _6$$6, _10$$6, _11$$6, _7$$7, _8$$7, _9$$7, _12$$8, _13$$9, _14$$9, _15$$9, _16$$12, _17$$12, _18$$12, _19$$14, *_20$$14, _21$$14, *_22$$14, _28$$14, _38$$14, _42$$14, _43$$14, _23$$15, _25$$17, _26$$17, _27$$17, _30$$18, _32$$20, _33$$20, _34$$20, _35$$21, _36$$21, _37$$21, _39$$23, _40$$23, _41$$23, _44$$27, _45$$27, _46$$27;
	zval expr;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&columnName);
	ZVAL_UNDEF(&nestingLevel);
	ZVAL_UNDEF(&sqlColumnAliases);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&sqlAliases);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&sqlAliasesModelsInstances);
	ZVAL_UNDEF(&realColumnName);
	ZVAL_UNDEF(&columnDomain);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&hasModel);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_28$$14);
	ZVAL_UNDEF(&_38$$14);
	ZVAL_UNDEF(&_42$$14);
	ZVAL_UNDEF(&_43$$14);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_32$$20);
	ZVAL_UNDEF(&_33$$20);
	ZVAL_UNDEF(&_34$$20);
	ZVAL_UNDEF(&_35$$21);
	ZVAL_UNDEF(&_36$$21);
	ZVAL_UNDEF(&_37$$21);
	ZVAL_UNDEF(&_39$$23);
	ZVAL_UNDEF(&_40$$23);
	ZVAL_UNDEF(&_41$$23);
	ZVAL_UNDEF(&_44$$27);
	ZVAL_UNDEF(&_45$$27);
	ZVAL_UNDEF(&_46$$27);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("nestingLevel", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("sqlColumnAliases", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("metaData", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("sqlAliases", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("phql", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("sqlAliasesModelsInstances", 25, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("models", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expr_param);
	ZEPHIR_OBS_COPY_OR_DUP(&expr, expr_param);
	zephir_memory_observe(&columnName);
	zephir_array_fetch_string(&columnName, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 2992);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 782, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&nestingLevel, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 783, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_value(&_0, &nestingLevel)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 783, PH_NOISY_CC | PH_READONLY);
		zephir_memory_observe(&_2$$3);
		zephir_array_fetch(&_2$$3, &_1$$3, &nestingLevel, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3000);
		ZEPHIR_CPY_WRT(&sqlColumnAliases, &_2$$3);
	} else {
		ZEPHIR_INIT_NVAR(&sqlColumnAliases);
		array_init(&sqlColumnAliases);
	}
	_3 = zephir_array_isset_value(&sqlColumnAliases, &columnName);
	if (_3) {
		_4 = !(zephir_array_isset_value_string(&expr, SL("domain")));
		if (!(_4)) {
			_4 = zephir_isempty_dim_string(&expr, SL("domain"));
		}
		_3 = _4;
	}
	if (_3) {
		zephir_create_array(return_value, 2, 0);
		add_assoc_stringl_ex(return_value, SL("type"), SL("qualified"));
		zephir_array_update_string(return_value, SL("name"), &columnName, PH_COPY | PH_SEPARATE);
		RETURN_MM();
	}
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_2, 773, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&metaData, &_5);
	zephir_memory_observe(&columnDomain);
	if (zephir_array_isset_string_fetch(&columnDomain, &expr, SL("domain"), 0)) {
		zephir_read_property_cached(&_6$$6, this_ptr, _zephir_prop_3, 778, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&sqlAliases, &_6$$6);
		zephir_memory_observe(&source);
		if (UNEXPECTED(!(zephir_array_isset_fetch(&source, &sqlAliases, &columnDomain, 0)))) {
			ZEPHIR_INIT_VAR(&_7$$7);
			object_init_ex(&_7$$7, phalcon_mvc_model_exception_ce);
			zephir_read_property_cached(&_8$$7, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_9$$7);
			ZEPHIR_CONCAT_SVSV(&_9$$7, "Unknown model or alias '", &columnDomain, "' (11), when preparing: ", &_8$$7);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_7$$7, "__construct", NULL, 32, &_9$$7);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_7$$7, "phalcon/Mvc/Model/Query.zep", 3026);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_11$$6);
		ZVAL_STRING(&_11$$6, "orm.column_renaming");
		ZEPHIR_CALL_CE_STATIC(&_10$$6, phalcon_support_settings_ce, "get", NULL, 0, &_11$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_10$$6)) {
			zephir_read_property_cached(&_12$$8, this_ptr, _zephir_prop_5, 781, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&sqlAliasesModelsInstances, &_12$$8);
			zephir_memory_observe(&model);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&model, &sqlAliasesModelsInstances, &columnDomain, 0)))) {
				ZEPHIR_INIT_VAR(&_13$$9);
				object_init_ex(&_13$$9, phalcon_mvc_model_exception_ce);
				zephir_read_property_cached(&_14$$9, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_15$$9);
				ZEPHIR_CONCAT_SVSV(&_15$$9, "There is no model related to model or alias '", &columnDomain, "', when executing: ", &_14$$9);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_13$$9, "__construct", NULL, 32, &_15$$9);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_13$$9, "phalcon/Mvc/Model/Query.zep", 3045);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getReverseColumnMap", NULL, 0, &model);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&columnMap);
			ZVAL_NULL(&columnMap);
		}
		if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
			zephir_memory_observe(&realColumnName);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&realColumnName, &columnMap, &columnName, 0)))) {
				ZEPHIR_INIT_VAR(&_16$$12);
				object_init_ex(&_16$$12, phalcon_mvc_model_exception_ce);
				zephir_read_property_cached(&_17$$12, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_18$$12);
				ZEPHIR_CONCAT_SVSVSV(&_18$$12, "Column '", &columnName, "' does not belong to the model or alias '", &columnDomain, "', when executing: ", &_17$$12);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_16$$12, "__construct", NULL, 32, &_18$$12);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_16$$12, "phalcon/Mvc/Model/Query.zep", 3057);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(&realColumnName, &columnName);
		}
	} else {
		number = 0;
		ZEPHIR_INIT_VAR(&hasModel);
		ZVAL_BOOL(&hasModel, 0);
		zephir_read_property_cached(&_19$$14, this_ptr, _zephir_prop_6, 776, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_19$$14) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_21$$14);
			zephir_string_to_char_array(&_21$$14, &_19$$14);
			_20$$14 = &_21$$14;
		} else {
			_20$$14 = &_19$$14;
		}
		zephir_is_iterable(_20$$14, 0, "phalcon/Mvc/Model/Query.zep", 3091);
		if (Z_TYPE_P(_20$$14) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_20$$14), _22$$14)
			{
				ZEPHIR_INIT_NVAR(&model);
				ZVAL_COPY(&model, _22$$14);
				ZEPHIR_CALL_METHOD(&_23$$15, &metaData, "hasAttribute", &_24, 0, &model, &columnName);
				zephir_check_call_status();
				if (zephir_is_true(&_23$$15)) {
					number++;
					if (UNEXPECTED(number > 1)) {
						ZEPHIR_INIT_NVAR(&_25$$17);
						object_init_ex(&_25$$17, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_26$$17, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_27$$17);
						ZEPHIR_CONCAT_SVSV(&_27$$17, "The column '", &columnName, "' is ambiguous, when preparing: ", &_26$$17);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_25$$17, "__construct", NULL, 32, &_27$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_25$$17, "phalcon/Mvc/Model/Query.zep", 3080);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CPY_WRT(&hasModel, &model);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _20$$14, "rewind", NULL, 0);
			zephir_check_call_status();
			_29$$14 = 1;
			while (1) {
				if (_29$$14) {
					_29$$14 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _20$$14, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_28$$14, _20$$14, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_28$$14)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&model, _20$$14, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_30$$18, &metaData, "hasAttribute", &_31, 0, &model, &columnName);
					zephir_check_call_status();
					if (zephir_is_true(&_30$$18)) {
						number++;
						if (UNEXPECTED(number > 1)) {
							ZEPHIR_INIT_NVAR(&_32$$20);
							object_init_ex(&_32$$20, phalcon_mvc_model_exception_ce);
							zephir_read_property_cached(&_33$$20, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
							ZEPHIR_INIT_NVAR(&_34$$20);
							ZEPHIR_CONCAT_SVSV(&_34$$20, "The column '", &columnName, "' is ambiguous, when preparing: ", &_33$$20);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_32$$20, "__construct", NULL, 32, &_34$$20);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_32$$20, "phalcon/Mvc/Model/Query.zep", 3080);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CPY_WRT(&hasModel, &model);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&model);
		if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&hasModel))) {
			ZEPHIR_INIT_VAR(&_35$$21);
			object_init_ex(&_35$$21, phalcon_mvc_model_exception_ce);
			zephir_read_property_cached(&_36$$21, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_37$$21);
			ZEPHIR_CONCAT_SVSV(&_37$$21, "Column '", &columnName, "' does not belong to any of the selected models (1), when preparing: ", &_36$$21);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_35$$21, "__construct", NULL, 32, &_37$$21);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_35$$21, "phalcon/Mvc/Model/Query.zep", 3094);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_38$$14, this_ptr, _zephir_prop_7, 777, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&models, &_38$$14);
		if (UNEXPECTED(Z_TYPE_P(&models) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The models list was not loaded correctly", "phalcon/Mvc/Model/Query.zep", 3105);
			return;
		}
		ZEPHIR_INIT_VAR(&className);
		zephir_get_class(&className, &hasModel, 0);
		ZEPHIR_OBS_NVAR(&source);
		if (UNEXPECTED(!(zephir_array_isset_fetch(&source, &models, &className, 0)))) {
			ZEPHIR_INIT_VAR(&_39$$23);
			object_init_ex(&_39$$23, phalcon_mvc_model_exception_ce);
			zephir_read_property_cached(&_40$$23, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_41$$23);
			ZEPHIR_CONCAT_SVSV(&_41$$23, "Can't obtain model's source from models list: '", &className, "', when preparing: ", &_40$$23);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_39$$23, "__construct", NULL, 32, &_41$$23);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_39$$23, "phalcon/Mvc/Model/Query.zep", 3116);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_43$$14);
		ZVAL_STRING(&_43$$14, "orm.column_renaming");
		ZEPHIR_CALL_CE_STATIC(&_42$$14, phalcon_support_settings_ce, "get", NULL, 0, &_43$$14);
		zephir_check_call_status();
		if (zephir_is_true(&_42$$14)) {
			ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getReverseColumnMap", NULL, 0, &hasModel);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&columnMap);
			ZVAL_NULL(&columnMap);
		}
		if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
			ZEPHIR_OBS_NVAR(&realColumnName);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&realColumnName, &columnMap, &columnName, 0)))) {
				ZEPHIR_INIT_VAR(&_44$$27);
				object_init_ex(&_44$$27, phalcon_mvc_model_exception_ce);
				zephir_read_property_cached(&_45$$27, this_ptr, _zephir_prop_4, 761, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_46$$27);
				ZEPHIR_CONCAT_SVSV(&_46$$27, "Column '", &columnName, "' does not belong to any of the selected models (3), when preparing: ", &_45$$27);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_44$$27, "__construct", NULL, 32, &_46$$27);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_44$$27, "phalcon/Mvc/Model/Query.zep", 3135);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(&realColumnName, &columnName);
		}
	}
	zephir_create_array(return_value, 4, 0);
	add_assoc_stringl_ex(return_value, SL("type"), SL("qualified"));
	zephir_array_update_string(return_value, SL("domain"), &source, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("name"), &realColumnName, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("balias"), &columnName, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Gets the read connection from the model if there is no transaction set
 * inside the query object
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getReadConnection)
{
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval intermediate, bindParams, bindTypes;
	zval *model, model_sub, *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, connection, transaction, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&transaction);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transaction", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY_OR_NULL(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 3, &model, &intermediate_param, &bindParams_param, &bindTypes_param);
	if (!intermediate_param) {
		ZEPHIR_INIT_VAR(&intermediate);
	} else {
		zephir_get_arrval(&intermediate, intermediate_param);
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
	ZEPHIR_INIT_VAR(&connection);
	ZVAL_NULL(&connection);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 775, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&transaction, &_0);
	_1 = Z_TYPE_P(&transaction) == IS_OBJECT;
	if (_1) {
		_1 = zephir_instance_of_ev(&transaction, phalcon_mvc_model_transactioninterface_ce);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(&transaction, "getConnection", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	if ((zephir_method_exists_ex(model, ZEND_STRL("selectreadconnection")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(&connection, model, "selectReadConnection", NULL, 0, &intermediate, &bindParams, &bindTypes);
		zephir_check_call_status();
		if (UNEXPECTED(Z_TYPE_P(&connection) != IS_OBJECT)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "selectReadConnection did not return a connection", "phalcon/Mvc/Model/Query.zep", 3179);
			return;
		}
		RETURN_CCTOR(&connection);
	}
	ZEPHIR_RETURN_CALL_METHOD(model, "getReadConnection", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Query the records on which the UPDATE/DELETE operation will be done
 *
 * @return ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getRelatedRecords)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval intermediate, bindParams, bindTypes, _0, _1;
	zval *model, model_sub, *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, selectIr, whereConditions, limitConditions, query, _2, _3, _4, _5, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&selectIr);
	ZVAL_UNDEF(&whereConditions);
	ZVAL_UNDEF(&limitConditions);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
		ZEPHIR_Z_PARAM_ARRAY(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &model, &intermediate_param, &bindParams_param, &bindTypes_param);
	zephir_get_arrval(&intermediate, intermediate_param);
	zephir_get_arrval(&bindParams, bindParams_param);
	zephir_get_arrval(&bindTypes, bindTypes_param);
	ZEPHIR_INIT_VAR(&selectIr);
	zephir_create_array(&selectIr, 3, 0);
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 1, 0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 3, 0);
	add_assoc_stringl_ex(&_1, SL("type"), SL("object"));
	ZEPHIR_INIT_VAR(&_2);
	zephir_get_class(&_2, model, 0);
	zephir_array_update_string(&_1, SL("model"), &_2, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_3, model, "getSource", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_1, SL("column"), &_3, PH_COPY | PH_SEPARATE);
	zephir_array_fast_append(&_0, &_1);
	zephir_array_update_string(&selectIr, SL("columns"), &_0, PH_COPY | PH_SEPARATE);
	zephir_memory_observe(&_4);
	zephir_array_fetch_string(&_4, &intermediate, SL("models"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3209);
	zephir_array_update_string(&selectIr, SL("models"), &_4, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_4);
	zephir_array_fetch_string(&_4, &intermediate, SL("tables"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3211);
	zephir_array_update_string(&selectIr, SL("tables"), &_4, PH_COPY | PH_SEPARATE);
	zephir_memory_observe(&whereConditions);
	if (zephir_array_isset_string_fetch(&whereConditions, &intermediate, SL("where"), 0)) {
		zephir_array_update_string(&selectIr, SL("where"), &whereConditions, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&limitConditions);
	if (zephir_array_isset_string_fetch(&limitConditions, &intermediate, SL("limit"), 0)) {
		zephir_array_update_string(&selectIr, SL("limit"), &limitConditions, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(&query);
	object_init_ex(&query, phalcon_mvc_model_query_ce);
	ZEPHIR_CALL_METHOD(NULL, &query, "__construct", NULL, 507);
	zephir_check_call_status();
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_0, 767, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &query, "setDI", NULL, 508, &_5);
	zephir_check_call_status();
	ZVAL_LONG(&_6, 309);
	ZEPHIR_CALL_METHOD(NULL, &query, "setType", NULL, 509, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &query, "setIntermediate", NULL, 510, &selectIr);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&query, "execute", NULL, 511, &bindParams, &bindTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Resolves a column from its intermediate representation into an array
 * used to determine if the resultset produced is simple or complex
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getSelectColumn)
{
	zend_bool _12$$4, _22$$12;
	zend_string *_5$$4;
	zend_ulong _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column_param = NULL, columnType, sqlAliases, modelName, source, columnDomain, sqlColumnAlias, preparedAlias, sqlExprColumn, sqlAliasesModels, columnData, balias, eager, _29, _30, _0$$4, *_1$$4, _2$$4, *_3$$4, _11$$4, _6$$5, _7$$5, _8$$5, _10$$6, _13$$7, _14$$7, _15$$7, _16$$7, _17$$8, _18$$10, _25$$10, _19$$11, _20$$11, _21$$11, _23$$13, _24$$13, _26$$15, _27$$16, _28$$18;
	zval column, sqlColumns, sqlColumn;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&sqlColumns);
	ZVAL_UNDEF(&sqlColumn);
	ZVAL_UNDEF(&columnType);
	ZVAL_UNDEF(&sqlAliases);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&columnDomain);
	ZVAL_UNDEF(&sqlColumnAlias);
	ZVAL_UNDEF(&preparedAlias);
	ZVAL_UNDEF(&sqlExprColumn);
	ZVAL_UNDEF(&sqlAliasesModels);
	ZVAL_UNDEF(&columnData);
	ZVAL_UNDEF(&balias);
	ZVAL_UNDEF(&eager);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_25$$10);
	ZVAL_UNDEF(&_19$$11);
	ZVAL_UNDEF(&_20$$11);
	ZVAL_UNDEF(&_21$$11);
	ZVAL_UNDEF(&_23$$13);
	ZVAL_UNDEF(&_24$$13);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_27$$16);
	ZVAL_UNDEF(&_28$$18);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("sqlAliases", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("phql", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("sqlAliasesModels", 16, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(column, column_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &column_param);
	ZEPHIR_OBS_COPY_OR_DUP(&column, column_param);
	zephir_memory_observe(&columnType);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&columnType, &column, SL("type"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 3251);
		return;
	}
	ZEPHIR_INIT_VAR(&sqlColumns);
	array_init(&sqlColumns);
	zephir_memory_observe(&eager);
	zephir_array_isset_string_fetch(&eager, &column, SL("eager"), 0);
	if (ZEPHIR_IS_LONG(&columnType, 352)) {
		zephir_read_property_cached(&_0$$4, this_ptr, _zephir_prop_0, 777, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0$$4) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_2$$4);
			zephir_string_to_char_array(&_2$$4, &_0$$4);
			_1$$4 = &_2$$4;
		} else {
			_1$$4 = &_0$$4;
		}
		zephir_is_iterable(_1$$4, 0, "phalcon/Mvc/Model/Query.zep", 3281);
		if (Z_TYPE_P(_1$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1$$4), _4$$4, _5$$4, _3$$4)
			{
				ZEPHIR_INIT_NVAR(&modelName);
				if (_5$$4 != NULL) { 
					ZVAL_STR_COPY(&modelName, _5$$4);
				} else {
					ZVAL_LONG(&modelName, _4$$4);
				}
				ZEPHIR_INIT_NVAR(&source);
				ZVAL_COPY(&source, _3$$4);
				ZEPHIR_INIT_NVAR(&sqlColumn);
				zephir_create_array(&sqlColumn, 4, 0);
				add_assoc_stringl_ex(&sqlColumn, SL("type"), SL("object"));
				zephir_array_update_string(&sqlColumn, SL("model"), &modelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&sqlColumn, SL("column"), &source, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_6$$5);
				ZEPHIR_INIT_NVAR(&_7$$5);
				ZVAL_STRING(&_7$$5, "\\");
				ZEPHIR_INIT_NVAR(&_8$$5);
				zephir_fast_strpos(&_8$$5, &modelName, &_7$$5, 0 );
				if (!ZEPHIR_IS_FALSE_IDENTICAL(&_8$$5)) {
					ZEPHIR_CPY_WRT(&_6$$5, &modelName);
				} else {
					ZEPHIR_CALL_FUNCTION(&_6$$5, "lcfirst", &_9, 86, &modelName);
					zephir_check_call_status();
				}
				zephir_array_update_string(&sqlColumn, SL("balias"), &_6$$5, PH_COPY | PH_SEPARATE);
				if (Z_TYPE_P(&eager) != IS_NULL) {
					zephir_array_update_string(&sqlColumn, SL("eager"), &eager, PH_COPY | PH_SEPARATE);
					zephir_array_fetch_string(&_10$$6, &column, SL("eagerType"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query.zep", 3275);
					zephir_array_update_string(&sqlColumn, SL("eagerType"), &_10$$6, PH_COPY | PH_SEPARATE);
				}
				zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3278);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _1$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_12$$4 = 1;
			while (1) {
				if (_12$$4) {
					_12$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _1$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_11$$4, _1$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_11$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&modelName, _1$$4, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&source, _1$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_13$$7);
					zephir_create_array(&_13$$7, 4, 0);
					add_assoc_stringl_ex(&_13$$7, SL("type"), SL("object"));
					zephir_array_update_string(&_13$$7, SL("model"), &modelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_13$$7, SL("column"), &source, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_14$$7);
					ZEPHIR_INIT_NVAR(&_15$$7);
					ZVAL_STRING(&_15$$7, "\\");
					ZEPHIR_INIT_NVAR(&_16$$7);
					zephir_fast_strpos(&_16$$7, &modelName, &_15$$7, 0 );
					if (!ZEPHIR_IS_FALSE_IDENTICAL(&_16$$7)) {
						ZEPHIR_CPY_WRT(&_14$$7, &modelName);
					} else {
						ZEPHIR_CALL_FUNCTION(&_14$$7, "lcfirst", &_9, 86, &modelName);
						zephir_check_call_status();
					}
					zephir_array_update_string(&_13$$7, SL("balias"), &_14$$7, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&sqlColumn, &_13$$7);
					if (Z_TYPE_P(&eager) != IS_NULL) {
						zephir_array_update_string(&sqlColumn, SL("eager"), &eager, PH_COPY | PH_SEPARATE);
						zephir_array_fetch_string(&_17$$8, &column, SL("eagerType"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query.zep", 3275);
						zephir_array_update_string(&sqlColumn, SL("eagerType"), &_17$$8, PH_COPY | PH_SEPARATE);
					}
					zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3278);
			}
		}
		ZEPHIR_INIT_NVAR(&source);
		ZEPHIR_INIT_NVAR(&modelName);
		RETURN_CTOR(&sqlColumns);
	}
	if (UNEXPECTED(!(zephir_array_isset_value_string(&column, SL("column"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 3285);
		return;
	}
	if (ZEPHIR_IS_LONG(&columnType, 353)) {
		zephir_read_property_cached(&_18$$10, this_ptr, _zephir_prop_1, 778, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&sqlAliases, &_18$$10);
		zephir_memory_observe(&columnDomain);
		zephir_array_fetch_string(&columnDomain, &column, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3297);
		ZEPHIR_OBS_NVAR(&source);
		if (UNEXPECTED(!(zephir_array_isset_fetch(&source, &sqlAliases, &columnDomain, 0)))) {
			ZEPHIR_INIT_VAR(&_19$$11);
			object_init_ex(&_19$$11, phalcon_mvc_model_exception_ce);
			zephir_read_property_cached(&_20$$11, this_ptr, _zephir_prop_2, 761, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_21$$11);
			ZEPHIR_CONCAT_SVSV(&_21$$11, "Unknown model or alias '", &columnDomain, "' (2), when preparing: ", &_20$$11);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_19$$11, "__construct", NULL, 32, &_21$$11);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_19$$11, "phalcon/Mvc/Model/Query.zep", 3302);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&sqlColumnAlias, &source);
		zephir_memory_observe(&preparedAlias);
		zephir_array_isset_string_fetch(&preparedAlias, &column, SL("balias"), 0);
		zephir_read_property_cached(&_18$$10, this_ptr, _zephir_prop_3, 779, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&sqlAliasesModels, &_18$$10);
		ZEPHIR_OBS_NVAR(&modelName);
		zephir_array_fetch(&modelName, &sqlAliasesModels, &columnDomain, PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3316);
		if (Z_TYPE_P(&preparedAlias) != IS_STRING) {
			_22$$12 = ZEPHIR_IS_EQUAL(&columnDomain, &modelName);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_22$$12) {
				ZEPHIR_INIT_VAR(&_23$$13);
				ZVAL_STRING(&_23$$13, "\\");
				ZEPHIR_INIT_VAR(&_24$$13);
				zephir_fast_strpos(&_24$$13, &modelName, &_23$$13, 0 );
				if (!ZEPHIR_IS_FALSE_IDENTICAL(&_24$$13)) {
					ZEPHIR_CPY_WRT(&preparedAlias, &modelName);
				} else {
					ZEPHIR_CALL_FUNCTION(&preparedAlias, "lcfirst", &_9, 86, &modelName);
					zephir_check_call_status();
				}
			} else {
				ZEPHIR_CPY_WRT(&preparedAlias, &columnDomain);
			}
		}
		ZEPHIR_INIT_VAR(&_25$$10);
		zephir_create_array(&_25$$10, 4, 0);
		add_assoc_stringl_ex(&_25$$10, SL("type"), SL("object"));
		zephir_array_update_string(&_25$$10, SL("model"), &modelName, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_25$$10, SL("column"), &sqlColumnAlias, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_25$$10, SL("balias"), &preparedAlias, PH_COPY | PH_SEPARATE);
		ZEPHIR_CPY_WRT(&sqlColumn, &_25$$10);
		if (Z_TYPE_P(&eager) != IS_NULL) {
			zephir_array_update_string(&sqlColumn, SL("eager"), &eager, PH_COPY | PH_SEPARATE);
			zephir_array_fetch_string(&_26$$15, &column, SL("eagerType"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query.zep", 3338);
			zephir_array_update_string(&sqlColumn, SL("eagerType"), &_26$$15, PH_COPY | PH_SEPARATE);
		}
		zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3341);
		RETURN_CTOR(&sqlColumns);
	}
	if (ZEPHIR_IS_LONG(&columnType, 354)) {
		ZEPHIR_INIT_VAR(&_27$$16);
		zephir_create_array(&_27$$16, 1, 0);
		add_assoc_stringl_ex(&_27$$16, SL("type"), SL("scalar"));
		ZEPHIR_CPY_WRT(&sqlColumn, &_27$$16);
		zephir_memory_observe(&columnData);
		zephir_array_fetch_string(&columnData, &column, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3355);
		ZEPHIR_CALL_METHOD(&sqlExprColumn, this_ptr, "getExpression", NULL, 498, &columnData);
		zephir_check_call_status();
		zephir_memory_observe(&balias);
		if (zephir_array_isset_string_fetch(&balias, &sqlExprColumn, SL("balias"), 0)) {
			zephir_array_update_string(&sqlColumn, SL("balias"), &balias, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&sqlColumn, SL("sqlAlias"), &balias, PH_COPY | PH_SEPARATE);
		}
		if (Z_TYPE_P(&eager) != IS_NULL) {
			zephir_array_update_string(&sqlColumn, SL("eager"), &eager, PH_COPY | PH_SEPARATE);
			zephir_array_fetch_string(&_28$$18, &column, SL("eagerType"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query.zep", 3368);
			zephir_array_update_string(&sqlColumn, SL("eagerType"), &_28$$18, PH_COPY | PH_SEPARATE);
		}
		zephir_array_update_string(&sqlColumn, SL("column"), &sqlExprColumn, PH_COPY | PH_SEPARATE);
		zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3372);
		RETURN_CTOR(&sqlColumns);
	}
	ZEPHIR_INIT_VAR(&_29);
	object_init_ex(&_29, phalcon_mvc_model_exception_ce);
	ZEPHIR_INIT_VAR(&_30);
	ZEPHIR_CONCAT_SV(&_30, "Unknown type of column ", &columnType);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, &_29, "__construct", NULL, 32, &_30);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_29, "phalcon/Mvc/Model/Query.zep", 3377);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Resolves joins involving has-one/belongs-to/has-many relations
 *
 * @param string joinSource
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getSingleJoin)
{
	zend_bool _19$$4;
	zend_ulong _8$$4;
	zval _1$$3, _3$$3, _4$$3, _14$$5, _16$$5, _17$$5, _23$$7, _25$$7, _26$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval joinType_zv, *joinSource, joinSource_sub, modelAlias_zv, joinAlias_zv, *relation, relation_sub, fields, referencedFields, sqlJoinConditions, sqlJoinPartialConditions, position, field, referencedField, _0$$3, _2$$3, *_5$$4, _6$$4, *_7$$4, _18$$4, _10$$6, _11$$6, _12$$6, _15$$5, _20$$8, _21$$8, _22$$8, _24$$7;
	zend_string *joinType = NULL, *modelAlias = NULL, *joinAlias = NULL, *_9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&joinType_zv);
	ZVAL_UNDEF(&joinSource_sub);
	ZVAL_UNDEF(&modelAlias_zv);
	ZVAL_UNDEF(&joinAlias_zv);
	ZVAL_UNDEF(&relation_sub);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&referencedFields);
	ZVAL_UNDEF(&sqlJoinConditions);
	ZVAL_UNDEF(&sqlJoinPartialConditions);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&referencedField);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_18$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_26$$7);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("phql", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(joinType)
		Z_PARAM_ZVAL(joinSource)
		Z_PARAM_STR(modelAlias)
		Z_PARAM_STR(joinAlias)
		Z_PARAM_OBJECT_OF_CLASS(relation, phalcon_mvc_model_relationinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	joinSource = ZEND_CALL_ARG(execute_data, 2);
	relation = ZEND_CALL_ARG(execute_data, 5);
	zephir_memory_observe(&joinType_zv);
	ZVAL_STR_COPY(&joinType_zv, joinType);
	zephir_memory_observe(&modelAlias_zv);
	ZVAL_STR_COPY(&modelAlias_zv, modelAlias);
	zephir_memory_observe(&joinAlias_zv);
	ZVAL_STR_COPY(&joinAlias_zv, joinAlias);
	ZEPHIR_INIT_VAR(&sqlJoinConditions);
	ZVAL_NULL(&sqlJoinConditions);
	ZEPHIR_CALL_METHOD(&fields, relation, "getFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&referencedFields, relation, "getReferencedFields", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&fields) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 4, 0);
		add_assoc_stringl_ex(&_1$$3, SL("type"), SL("binary-op"));
		add_assoc_stringl_ex(&_1$$3, SL("op"), SL("="));
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_create_array(&_3$$3, 3, 0);
		add_assoc_long_ex(&_3$$3, SL("type"), 355);
		zephir_array_update_string(&_3$$3, SL("domain"), &modelAlias_zv, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_3$$3, SL("name"), &fields, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "getQualified", NULL, 499, &_3$$3);
		zephir_check_call_status();
		zephir_array_update_string(&_1$$3, SL("left"), &_2$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_4$$3);
		zephir_create_array(&_4$$3, 3, 0);
		add_assoc_stringl_ex(&_4$$3, SL("type"), SL("qualified"));
		zephir_array_update_string(&_4$$3, SL("domain"), &joinAlias_zv, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_4$$3, SL("name"), &referencedFields, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "getQualified", NULL, 499, &_4$$3);
		zephir_check_call_status();
		zephir_array_update_string(&_1$$3, SL("right"), &_2$$3, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_0$$3, &_1$$3);
		ZEPHIR_CPY_WRT(&sqlJoinConditions, &_0$$3);
	} else {
		ZEPHIR_INIT_VAR(&sqlJoinPartialConditions);
		array_init(&sqlJoinPartialConditions);
		if (Z_TYPE_P(&fields) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_6$$4);
			zephir_string_to_char_array(&_6$$4, &fields);
			_5$$4 = &_6$$4;
		} else {
			_5$$4 = &fields;
		}
		zephir_is_iterable(_5$$4, 0, "phalcon/Mvc/Model/Query.zep", 3467);
		if (Z_TYPE_P(_5$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_5$$4), _8$$4, _9$$4, _7$$4)
			{
				ZEPHIR_INIT_NVAR(&position);
				if (_9$$4 != NULL) { 
					ZVAL_STR_COPY(&position, _9$$4);
				} else {
					ZVAL_LONG(&position, _8$$4);
				}
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _7$$4);
				ZEPHIR_OBS_NVAR(&referencedField);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&referencedField, &referencedFields, &position, 0)))) {
					ZEPHIR_INIT_NVAR(&_10$$6);
					object_init_ex(&_10$$6, phalcon_mvc_model_exception_ce);
					zephir_read_property_cached(&_11$$6, this_ptr, _zephir_prop_0, 761, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_INIT_NVAR(&_12$$6);
					ZEPHIR_CONCAT_SVSVSV(&_12$$6, "The number of fields must be equal to the number of referenced fields in join ", &modelAlias_zv, "-", &joinAlias_zv, ", when preparing: ", &_11$$6);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_10$$6, "__construct", &_13, 32, &_12$$6);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_10$$6, "phalcon/Mvc/Model/Query.zep", 3439);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_create_array(&_14$$5, 4, 0);
				add_assoc_stringl_ex(&_14$$5, SL("type"), SL("binary-op"));
				add_assoc_stringl_ex(&_14$$5, SL("op"), SL("="));
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_create_array(&_16$$5, 3, 0);
				add_assoc_long_ex(&_16$$5, SL("type"), 355);
				zephir_array_update_string(&_16$$5, SL("domain"), &modelAlias_zv, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_16$$5, SL("name"), &field, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_15$$5, this_ptr, "getQualified", NULL, 499, &_16$$5);
				zephir_check_call_status();
				zephir_array_update_string(&_14$$5, SL("left"), &_15$$5, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_create_array(&_17$$5, 3, 0);
				add_assoc_stringl_ex(&_17$$5, SL("type"), SL("qualified"));
				zephir_array_update_string(&_17$$5, SL("domain"), &joinAlias_zv, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_17$$5, SL("name"), &referencedField, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_15$$5, this_ptr, "getQualified", NULL, 499, &_17$$5);
				zephir_check_call_status();
				zephir_array_update_string(&_14$$5, SL("right"), &_15$$5, PH_COPY | PH_SEPARATE);
				zephir_array_append(&sqlJoinPartialConditions, &_14$$5, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3464);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _5$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_19$$4 = 1;
			while (1) {
				if (_19$$4) {
					_19$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _5$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_18$$4, _5$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_18$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&position, _5$$4, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&field, _5$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&referencedField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&referencedField, &referencedFields, &position, 0)))) {
						ZEPHIR_INIT_NVAR(&_20$$8);
						object_init_ex(&_20$$8, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_21$$8, this_ptr, _zephir_prop_0, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_22$$8);
						ZEPHIR_CONCAT_SVSVSV(&_22$$8, "The number of fields must be equal to the number of referenced fields in join ", &modelAlias_zv, "-", &joinAlias_zv, ", when preparing: ", &_21$$8);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_20$$8, "__construct", &_13, 32, &_22$$8);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_20$$8, "phalcon/Mvc/Model/Query.zep", 3439);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_23$$7);
					zephir_create_array(&_23$$7, 4, 0);
					add_assoc_stringl_ex(&_23$$7, SL("type"), SL("binary-op"));
					add_assoc_stringl_ex(&_23$$7, SL("op"), SL("="));
					ZEPHIR_INIT_NVAR(&_25$$7);
					zephir_create_array(&_25$$7, 3, 0);
					add_assoc_long_ex(&_25$$7, SL("type"), 355);
					zephir_array_update_string(&_25$$7, SL("domain"), &modelAlias_zv, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_25$$7, SL("name"), &field, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(&_24$$7, this_ptr, "getQualified", NULL, 499, &_25$$7);
					zephir_check_call_status();
					zephir_array_update_string(&_23$$7, SL("left"), &_24$$7, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_create_array(&_26$$7, 3, 0);
					add_assoc_stringl_ex(&_26$$7, SL("type"), SL("qualified"));
					zephir_array_update_string(&_26$$7, SL("domain"), &joinAlias_zv, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_26$$7, SL("name"), &referencedField, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(&_24$$7, this_ptr, "getQualified", NULL, 499, &_26$$7);
					zephir_check_call_status();
					zephir_array_update_string(&_23$$7, SL("right"), &_24$$7, PH_COPY | PH_SEPARATE);
					zephir_array_append(&sqlJoinPartialConditions, &_23$$7, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3464);
			}
		}
		ZEPHIR_INIT_NVAR(&field);
		ZEPHIR_INIT_NVAR(&position);
	}
	zephir_create_array(return_value, 3, 0);
	zephir_array_update_string(return_value, SL("type"), &joinType_zv, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("source"), joinSource, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("conditions"), &sqlJoinConditions, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Resolves a table in a SELECT statement checking if the model exists
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getTable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval qualifiedName;
	zval *manager, manager_sub, *qualifiedName_param = NULL, modelName, model, source, schema;

	ZVAL_UNDEF(&manager_sub);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&qualifiedName);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(manager, phalcon_mvc_model_managerinterface_ce)
		ZEPHIR_Z_PARAM_ARRAY(qualifiedName, qualifiedName_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &manager, &qualifiedName_param);
	zephir_get_arrval(&qualifiedName, qualifiedName_param);
	zephir_memory_observe(&modelName);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&modelName, &qualifiedName, SL("name"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 3489);
		return;
	}
	ZEPHIR_CALL_METHOD(&model, manager, "load", NULL, 0, &modelName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		zephir_create_array(return_value, 2, 0);
		zephir_array_fast_append(return_value, &schema);
		zephir_array_fast_append(return_value, &source);
		RETURN_MM();
	}
	RETURN_CCTOR(&source);
}

/**
 * Gets the write connection from the model if there is no transaction
 * inside the query object
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, getWriteConnection)
{
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval intermediate, bindParams, bindTypes;
	zval *model, model_sub, *intermediate_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, connection, transaction, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&transaction);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transaction", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY_OR_NULL(intermediate, intermediate_param)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 3, &model, &intermediate_param, &bindParams_param, &bindTypes_param);
	if (!intermediate_param) {
		ZEPHIR_INIT_VAR(&intermediate);
	} else {
		zephir_get_arrval(&intermediate, intermediate_param);
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
	ZEPHIR_INIT_VAR(&connection);
	ZVAL_NULL(&connection);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 775, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&transaction, &_0);
	_1 = Z_TYPE_P(&transaction) == IS_OBJECT;
	if (_1) {
		_1 = zephir_instance_of_ev(&transaction, phalcon_mvc_model_transactioninterface_ce);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(&transaction, "getConnection", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	if ((zephir_method_exists_ex(model, ZEND_STRL("selectwriteconnection")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(&connection, model, "selectWriteConnection", NULL, 0, &intermediate, &bindParams, &bindTypes);
		zephir_check_call_status();
		if (UNEXPECTED(Z_TYPE_P(&connection) != IS_OBJECT)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "selectWriteConnection did not return a connection", "phalcon/Mvc/Model/Query.zep", 3527);
			return;
		}
		RETURN_CCTOR(&connection);
	}
	ZEPHIR_RETURN_CALL_METHOD(model, "getWriteConnection", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Analyzes a DELETE intermediate code and produces an array to be executed
 * later
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, _prepareDelete)
{
	zend_bool _8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null, ast, delete, tables, models, modelsInstances, sqlTables, sqlModels, sqlAliases, sqlAliasesModelsInstances, deleteTables, manager, table, qualifiedName, modelName, model, source, schema, completeSource, alias, sqlDelete, where, limit, _0, *_1, _2, *_3, _7, _5$$8, _6$$9, _10$$13, _11$$14, _12$$17, _13$$17, _14$$18;
	zephir_fcall_cache_entry *_4 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&ast);
	ZVAL_UNDEF(&delete);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&modelsInstances);
	ZVAL_UNDEF(&sqlTables);
	ZVAL_UNDEF(&sqlModels);
	ZVAL_UNDEF(&sqlAliases);
	ZVAL_UNDEF(&sqlAliasesModelsInstances);
	ZVAL_UNDEF(&deleteTables);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&qualifiedName);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&completeSource);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&sqlDelete);
	ZVAL_UNDEF(&where);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_10$$13);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_12$$17);
	ZVAL_UNDEF(&_13$$17);
	ZVAL_UNDEF(&_14$$18);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("ast", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("sqlAliases", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("sqlAliasesModelsInstances", 25, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 771, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&ast, &_0);
	zephir_memory_observe(&delete);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&delete, &ast, SL("delete"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted DELETE AST", "phalcon/Mvc/Model/Query.zep", 3549);
		return;
	}
	zephir_memory_observe(&tables);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&tables, &delete, SL("tables"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted DELETE AST", "phalcon/Mvc/Model/Query.zep", 3553);
		return;
	}
	ZEPHIR_INIT_VAR(&models);
	array_init(&models);
	ZEPHIR_INIT_VAR(&modelsInstances);
	array_init(&modelsInstances);
	ZEPHIR_INIT_VAR(&sqlTables);
	array_init(&sqlTables);
	ZEPHIR_INIT_VAR(&sqlModels);
	array_init(&sqlModels);
	ZEPHIR_INIT_VAR(&sqlAliases);
	array_init(&sqlAliases);
	ZEPHIR_INIT_VAR(&sqlAliasesModelsInstances);
	array_init(&sqlAliasesModelsInstances);
	if (!(zephir_array_isset_value_long(&tables, 0))) {
		ZEPHIR_INIT_VAR(&deleteTables);
		zephir_create_array(&deleteTables, 1, 0);
		zephir_array_fast_append(&deleteTables, &tables);
	} else {
		ZEPHIR_CPY_WRT(&deleteTables, &tables);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	if (Z_TYPE_P(&deleteTables) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &deleteTables);
		_1 = &_2;
	} else {
		_1 = &deleteTables;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query.zep", 3613);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&table);
			ZVAL_COPY(&table, _3);
			ZEPHIR_OBS_NVAR(&qualifiedName);
			zephir_array_fetch_string(&qualifiedName, &table, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3577);
			ZEPHIR_OBS_NVAR(&modelName);
			zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3578);
			ZEPHIR_CALL_METHOD(&model, &manager, "load", &_4, 0, &modelName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&completeSource);
			if (zephir_is_true(&schema)) {
				ZEPHIR_INIT_NVAR(&_5$$8);
				zephir_create_array(&_5$$8, 2, 0);
				zephir_array_fast_append(&_5$$8, &source);
				zephir_array_fast_append(&_5$$8, &schema);
				ZEPHIR_CPY_WRT(&completeSource, &_5$$8);
			} else {
				ZEPHIR_INIT_NVAR(&_6$$9);
				zephir_create_array(&_6$$9, 2, 0);
				zephir_array_fast_append(&_6$$9, &source);
				zephir_array_fast_append(&_6$$9, &__$null);
				ZEPHIR_CPY_WRT(&completeSource, &_6$$9);
			}
			ZEPHIR_OBS_NVAR(&alias);
			if (zephir_array_isset_string_fetch(&alias, &table, SL("alias"), 0)) {
				zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3595);
				zephir_array_append(&sqlTables, &completeSource, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3596);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&models, &alias, &modelName, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&sqlAliases, &modelName, &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
				zephir_array_append(&sqlTables, &source, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3602);
				zephir_array_update_zval(&models, &modelName, &source, PH_COPY | PH_SEPARATE);
			}
			zephir_array_append(&sqlModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3606);
			zephir_array_update_zval(&modelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&table, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&qualifiedName);
				zephir_array_fetch_string(&qualifiedName, &table, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3577);
				ZEPHIR_OBS_NVAR(&modelName);
				zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3578);
				ZEPHIR_CALL_METHOD(&model, &manager, "load", &_9, 0, &modelName);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&schema)) {
					ZEPHIR_INIT_NVAR(&_10$$13);
					zephir_create_array(&_10$$13, 2, 0);
					zephir_array_fast_append(&_10$$13, &source);
					zephir_array_fast_append(&_10$$13, &schema);
					ZEPHIR_CPY_WRT(&completeSource, &_10$$13);
				} else {
					ZEPHIR_INIT_NVAR(&_11$$14);
					zephir_create_array(&_11$$14, 2, 0);
					zephir_array_fast_append(&_11$$14, &source);
					zephir_array_fast_append(&_11$$14, &__$null);
					ZEPHIR_CPY_WRT(&completeSource, &_11$$14);
				}
				ZEPHIR_OBS_NVAR(&alias);
				if (zephir_array_isset_string_fetch(&alias, &table, SL("alias"), 0)) {
					zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3595);
					zephir_array_append(&sqlTables, &completeSource, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3596);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&models, &alias, &modelName, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&sqlAliases, &modelName, &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
					zephir_array_append(&sqlTables, &source, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3602);
					zephir_array_update_zval(&models, &modelName, &source, PH_COPY | PH_SEPARATE);
				}
				zephir_array_append(&sqlModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3606);
				zephir_array_update_zval(&modelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&table);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 777, &models);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 776, &modelsInstances);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 778, &sqlAliases);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 781, &sqlAliasesModelsInstances);
	ZEPHIR_INIT_VAR(&sqlDelete);
	array_init(&sqlDelete);
	zephir_array_update_string(&sqlDelete, SL("tables"), &sqlTables, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlDelete, SL("models"), &sqlModels, PH_COPY | PH_SEPARATE);
	zephir_memory_observe(&where);
	if (zephir_array_isset_string_fetch(&where, &ast, SL("where"), 0)) {
		ZVAL_BOOL(&_13$$17, 1);
		ZEPHIR_CALL_METHOD(&_12$$17, this_ptr, "getExpression", NULL, 498, &where, &_13$$17);
		zephir_check_call_status();
		zephir_array_update_string(&sqlDelete, SL("where"), &_12$$17, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&limit);
	if (zephir_array_isset_string_fetch(&limit, &ast, SL("limit"), 0)) {
		ZEPHIR_CALL_METHOD(&_14$$18, this_ptr, "getLimitClause", NULL, 0, &limit);
		zephir_check_call_status();
		zephir_array_update_string(&sqlDelete, SL("limit"), &_14$$18, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(&sqlDelete);
}

/**
 * Analyzes an INSERT intermediate code and produces an array to be executed
 * later
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, _prepareInsert)
{
	zval _6$$7, _13$$8;
	zend_bool notQuoting = 0, _12, _27$$9;
	zval ast, qualifiedName, manager, modelName, model, source, schema, exprValues, exprValue, sqlInsert, metaData, fields, sqlFields, field, name, _0, _2, *_3, _4, *_5, _11, _1$$6, _7$$7, _8$$7, _9$$7, _14$$8, _15$$8, _16$$8, *_17$$9, _18$$9, *_19$$9, _26$$9, _20$$10, _22$$11, _23$$11, _24$$11, _28$$12, _30$$13, _31$$13, _32$$13;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_21 = NULL, *_25 = NULL, *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ast);
	ZVAL_UNDEF(&qualifiedName);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&exprValues);
	ZVAL_UNDEF(&exprValue);
	ZVAL_UNDEF(&sqlInsert);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&sqlFields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_20$$10);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_23$$11);
	ZVAL_UNDEF(&_24$$11);
	ZVAL_UNDEF(&_28$$12);
	ZVAL_UNDEF(&_30$$13);
	ZVAL_UNDEF(&_31$$13);
	ZVAL_UNDEF(&_32$$13);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_13$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("ast", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("metaData", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("phql", 4, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 771, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&ast, &_0);
	if (UNEXPECTED(!(zephir_array_isset_value_string(&ast, SL("qualifiedName"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted INSERT AST", "phalcon/Mvc/Model/Query.zep", 3647);
		return;
	}
	if (UNEXPECTED(!(zephir_array_isset_value_string(&ast, SL("values"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted INSERT AST", "phalcon/Mvc/Model/Query.zep", 3651);
		return;
	}
	zephir_memory_observe(&qualifiedName);
	zephir_array_fetch_string(&qualifiedName, &ast, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3654);
	if (UNEXPECTED(!(zephir_array_isset_value_string(&qualifiedName, SL("name"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted INSERT AST", "phalcon/Mvc/Model/Query.zep", 3658);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	zephir_memory_observe(&modelName);
	zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3662);
	ZEPHIR_CALL_METHOD(&model, &manager, "load", NULL, 0, &modelName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		ZEPHIR_INIT_VAR(&_1$$6);
		zephir_create_array(&_1$$6, 2, 0);
		zephir_array_fast_append(&_1$$6, &schema);
		zephir_array_fast_append(&_1$$6, &source);
		ZEPHIR_CPY_WRT(&source, &_1$$6);
	}
	notQuoting = 0;
	ZEPHIR_INIT_VAR(&exprValues);
	array_init(&exprValues);
	zephir_memory_observe(&_2);
	zephir_array_fetch_string(&_2, &ast, SL("values"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3675);
	if (Z_TYPE_P(&_2) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4);
		zephir_string_to_char_array(&_4, &_2);
		_3 = &_4;
	} else {
		_3 = &_2;
	}
	zephir_is_iterable(_3, 0, "phalcon/Mvc/Model/Query.zep", 3683);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&exprValue);
			ZVAL_COPY(&exprValue, _5);
			ZEPHIR_INIT_NVAR(&_6$$7);
			zephir_create_array(&_6$$7, 2, 0);
			ZEPHIR_OBS_NVAR(&_7$$7);
			zephir_array_fetch_string(&_7$$7, &exprValue, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3678);
			zephir_array_update_string(&_6$$7, SL("type"), &_7$$7, PH_COPY | PH_SEPARATE);
			if (notQuoting) {
				ZVAL_BOOL(&_9$$7, 1);
			} else {
				ZVAL_BOOL(&_9$$7, 0);
			}
			ZEPHIR_CALL_METHOD(&_8$$7, this_ptr, "getExpression", &_10, 498, &exprValue, &_9$$7);
			zephir_check_call_status();
			zephir_array_update_string(&_6$$7, SL("value"), &_8$$7, PH_COPY | PH_SEPARATE);
			zephir_array_append(&exprValues, &_6$$7, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3680);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&exprValue, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_13$$8);
				zephir_create_array(&_13$$8, 2, 0);
				ZEPHIR_OBS_NVAR(&_14$$8);
				zephir_array_fetch_string(&_14$$8, &exprValue, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3678);
				zephir_array_update_string(&_13$$8, SL("type"), &_14$$8, PH_COPY | PH_SEPARATE);
				if (notQuoting) {
					ZVAL_BOOL(&_16$$8, 1);
				} else {
					ZVAL_BOOL(&_16$$8, 0);
				}
				ZEPHIR_CALL_METHOD(&_15$$8, this_ptr, "getExpression", &_10, 498, &exprValue, &_16$$8);
				zephir_check_call_status();
				zephir_array_update_string(&_13$$8, SL("value"), &_15$$8, PH_COPY | PH_SEPARATE);
				zephir_array_append(&exprValues, &_13$$8, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3680);
		}
	}
	ZEPHIR_INIT_NVAR(&exprValue);
	ZEPHIR_INIT_VAR(&sqlInsert);
	zephir_create_array(&sqlInsert, 2, 0);
	zephir_array_update_string(&sqlInsert, SL("model"), &modelName, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlInsert, SL("table"), &source, PH_COPY | PH_SEPARATE);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 773, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&metaData, &_0);
	zephir_memory_observe(&fields);
	if (zephir_array_isset_string_fetch(&fields, &ast, SL("fields"), 0)) {
		ZEPHIR_INIT_VAR(&sqlFields);
		array_init(&sqlFields);
		if (Z_TYPE_P(&fields) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_18$$9);
			zephir_string_to_char_array(&_18$$9, &fields);
			_17$$9 = &_18$$9;
		} else {
			_17$$9 = &fields;
		}
		zephir_is_iterable(_17$$9, 0, "phalcon/Mvc/Model/Query.zep", 3707);
		if (Z_TYPE_P(_17$$9) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_17$$9), _19$$9)
			{
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _19$$9);
				ZEPHIR_OBS_NVAR(&name);
				zephir_array_fetch_string(&name, &field, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3694);
				ZEPHIR_CALL_METHOD(&_20$$10, &metaData, "hasAttribute", &_21, 0, &model, &name);
				zephir_check_call_status();
				if (UNEXPECTED(!zephir_is_true(&_20$$10))) {
					ZEPHIR_INIT_NVAR(&_22$$11);
					object_init_ex(&_22$$11, phalcon_mvc_model_exception_ce);
					zephir_read_property_cached(&_23$$11, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_INIT_NVAR(&_24$$11);
					ZEPHIR_CONCAT_SVSVSV(&_24$$11, "The model '", &modelName, "' does not have the attribute '", &name, "', when preparing: ", &_23$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_22$$11, "__construct", &_25, 32, &_24$$11);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_22$$11, "phalcon/Mvc/Model/Query.zep", 3700);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&sqlFields, &name, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3704);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _17$$9, "rewind", NULL, 0);
			zephir_check_call_status();
			_27$$9 = 1;
			while (1) {
				if (_27$$9) {
					_27$$9 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _17$$9, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_26$$9, _17$$9, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_26$$9)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _17$$9, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&name);
					zephir_array_fetch_string(&name, &field, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3694);
					ZEPHIR_CALL_METHOD(&_28$$12, &metaData, "hasAttribute", &_29, 0, &model, &name);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_28$$12))) {
						ZEPHIR_INIT_NVAR(&_30$$13);
						object_init_ex(&_30$$13, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_31$$13, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_32$$13);
						ZEPHIR_CONCAT_SVSVSV(&_32$$13, "The model '", &modelName, "' does not have the attribute '", &name, "', when preparing: ", &_31$$13);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_30$$13, "__construct", &_25, 32, &_32$$13);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_30$$13, "phalcon/Mvc/Model/Query.zep", 3700);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&sqlFields, &name, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3704);
			}
		}
		ZEPHIR_INIT_NVAR(&field);
		zephir_array_update_string(&sqlInsert, SL("fields"), &sqlFields, PH_COPY | PH_SEPARATE);
	}
	zephir_array_update_string(&sqlInsert, SL("values"), &exprValues, PH_COPY | PH_SEPARATE);
	RETURN_CCTOR(&sqlInsert);
}

/**
 * Analyzes a SELECT intermediate code and produces an array to be executed later
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, _prepareSelect)
{
	zval _15$$24, _29$$28, _53$$43, _67$$47, _101$$66, _106$$73, _115$$81, _120$$88;
	zval sqlModels, sqlTables, sqlAliases, sqlColumns, sqlAliasesModels, sqlModelsAliases, sqlAliasesModelsInstances, models, modelsInstances, _23$$24, _24$$24, _25$$24, _37$$28, _38$$28, _39$$28, _61$$43, _62$$43, _63$$43, _75$$47, _76$$47, _77$$47;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_9 = NULL, *_16 = NULL, *_18 = NULL, *_30 = NULL, *_32 = NULL, *_42 = NULL, *_54 = NULL, *_56 = NULL, *_68 = NULL, *_70 = NULL, *_95 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, position = 0, number = 0;
	zend_bool merge, _41, _108, _27$$21, _65$$40, _103$$60, _117$$75;
	zval *ast = NULL, ast_sub, *merge_param = NULL, __$null, __$true, select, tables, columns, selectedModels, manager, metaData, selectedModel, qualifiedName, modelName, model, schema, source, completeSource, alias, joins, sqlJoins, selectColumns, sqlColumnAliases, column, sqlColumn, sqlSelect, distinct, having, where, groupBy, order, limit, tempModels, tempModelsInstances, tempSqlAliases, tempSqlModelsAliases, tempSqlAliasesModelsInstances, tempSqlAliasesModels, with, withs, withItem, automaticJoins, relation, joinAlias, relationModel, bestAlias, eagerType, _1, *_2, _3, *_4, _40, *_91, _92, *_93, _107, _121, _0$$3, _6$$17, _7$$17, _8$$17, _10$$19, *_11$$21, _12$$21, *_13$$21, _26$$21, _14$$24, _17$$25, _19$$27, _20$$27, _21$$27, _22$$26, _28$$28, _31$$29, _33$$31, _34$$31, _35$$31, _36$$30, _43$$33, _44$$36, _45$$36, _46$$36, _47$$38, _48$$41, *_49$$40, _50$$40, *_51$$40, _64$$40, _52$$43, _55$$44, _57$$46, _58$$46, _59$$46, _60$$45, _66$$47, _69$$48, _71$$50, _72$$50, _73$$50, _74$$49, _78$$52, _79$$52, _80$$52, _81$$52, _82$$52, _83$$52, _84$$52, _85$$52, _86$$52, _87$$52, _88$$52, _89$$52, _90$$55, _94$$60, *_96$$60, _97$$60, *_98$$60, _102$$60, _99$$65, _100$$66, _104$$72, _105$$73, _109$$75, *_110$$75, _111$$75, *_112$$75, _116$$75, _113$$80, _114$$81, _118$$87, _119$$88, _122$$92, _123$$93, _124$$94, _125$$95, _126$$96;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ast_sub);
	ZVAL_NULL(&__$null);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&select);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&selectedModels);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&selectedModel);
	ZVAL_UNDEF(&qualifiedName);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&completeSource);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&joins);
	ZVAL_UNDEF(&sqlJoins);
	ZVAL_UNDEF(&selectColumns);
	ZVAL_UNDEF(&sqlColumnAliases);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&sqlColumn);
	ZVAL_UNDEF(&sqlSelect);
	ZVAL_UNDEF(&distinct);
	ZVAL_UNDEF(&having);
	ZVAL_UNDEF(&where);
	ZVAL_UNDEF(&groupBy);
	ZVAL_UNDEF(&order);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&tempModels);
	ZVAL_UNDEF(&tempModelsInstances);
	ZVAL_UNDEF(&tempSqlAliases);
	ZVAL_UNDEF(&tempSqlModelsAliases);
	ZVAL_UNDEF(&tempSqlAliasesModelsInstances);
	ZVAL_UNDEF(&tempSqlAliasesModels);
	ZVAL_UNDEF(&with);
	ZVAL_UNDEF(&withs);
	ZVAL_UNDEF(&withItem);
	ZVAL_UNDEF(&automaticJoins);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&joinAlias);
	ZVAL_UNDEF(&relationModel);
	ZVAL_UNDEF(&bestAlias);
	ZVAL_UNDEF(&eagerType);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_92);
	ZVAL_UNDEF(&_107);
	ZVAL_UNDEF(&_121);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_6$$17);
	ZVAL_UNDEF(&_7$$17);
	ZVAL_UNDEF(&_8$$17);
	ZVAL_UNDEF(&_10$$19);
	ZVAL_UNDEF(&_12$$21);
	ZVAL_UNDEF(&_26$$21);
	ZVAL_UNDEF(&_14$$24);
	ZVAL_UNDEF(&_17$$25);
	ZVAL_UNDEF(&_19$$27);
	ZVAL_UNDEF(&_20$$27);
	ZVAL_UNDEF(&_21$$27);
	ZVAL_UNDEF(&_22$$26);
	ZVAL_UNDEF(&_28$$28);
	ZVAL_UNDEF(&_31$$29);
	ZVAL_UNDEF(&_33$$31);
	ZVAL_UNDEF(&_34$$31);
	ZVAL_UNDEF(&_35$$31);
	ZVAL_UNDEF(&_36$$30);
	ZVAL_UNDEF(&_43$$33);
	ZVAL_UNDEF(&_44$$36);
	ZVAL_UNDEF(&_45$$36);
	ZVAL_UNDEF(&_46$$36);
	ZVAL_UNDEF(&_47$$38);
	ZVAL_UNDEF(&_48$$41);
	ZVAL_UNDEF(&_50$$40);
	ZVAL_UNDEF(&_64$$40);
	ZVAL_UNDEF(&_52$$43);
	ZVAL_UNDEF(&_55$$44);
	ZVAL_UNDEF(&_57$$46);
	ZVAL_UNDEF(&_58$$46);
	ZVAL_UNDEF(&_59$$46);
	ZVAL_UNDEF(&_60$$45);
	ZVAL_UNDEF(&_66$$47);
	ZVAL_UNDEF(&_69$$48);
	ZVAL_UNDEF(&_71$$50);
	ZVAL_UNDEF(&_72$$50);
	ZVAL_UNDEF(&_73$$50);
	ZVAL_UNDEF(&_74$$49);
	ZVAL_UNDEF(&_78$$52);
	ZVAL_UNDEF(&_79$$52);
	ZVAL_UNDEF(&_80$$52);
	ZVAL_UNDEF(&_81$$52);
	ZVAL_UNDEF(&_82$$52);
	ZVAL_UNDEF(&_83$$52);
	ZVAL_UNDEF(&_84$$52);
	ZVAL_UNDEF(&_85$$52);
	ZVAL_UNDEF(&_86$$52);
	ZVAL_UNDEF(&_87$$52);
	ZVAL_UNDEF(&_88$$52);
	ZVAL_UNDEF(&_89$$52);
	ZVAL_UNDEF(&_90$$55);
	ZVAL_UNDEF(&_94$$60);
	ZVAL_UNDEF(&_97$$60);
	ZVAL_UNDEF(&_102$$60);
	ZVAL_UNDEF(&_99$$65);
	ZVAL_UNDEF(&_100$$66);
	ZVAL_UNDEF(&_104$$72);
	ZVAL_UNDEF(&_105$$73);
	ZVAL_UNDEF(&_109$$75);
	ZVAL_UNDEF(&_111$$75);
	ZVAL_UNDEF(&_116$$75);
	ZVAL_UNDEF(&_113$$80);
	ZVAL_UNDEF(&_114$$81);
	ZVAL_UNDEF(&_118$$87);
	ZVAL_UNDEF(&_119$$88);
	ZVAL_UNDEF(&_122$$92);
	ZVAL_UNDEF(&_123$$93);
	ZVAL_UNDEF(&_124$$94);
	ZVAL_UNDEF(&_125$$95);
	ZVAL_UNDEF(&_126$$96);
	ZVAL_UNDEF(&sqlModels);
	ZVAL_UNDEF(&sqlTables);
	ZVAL_UNDEF(&sqlAliases);
	ZVAL_UNDEF(&sqlColumns);
	ZVAL_UNDEF(&sqlAliasesModels);
	ZVAL_UNDEF(&sqlModelsAliases);
	ZVAL_UNDEF(&sqlAliasesModelsInstances);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&modelsInstances);
	ZVAL_UNDEF(&_23$$24);
	ZVAL_UNDEF(&_24$$24);
	ZVAL_UNDEF(&_25$$24);
	ZVAL_UNDEF(&_37$$28);
	ZVAL_UNDEF(&_38$$28);
	ZVAL_UNDEF(&_39$$28);
	ZVAL_UNDEF(&_61$$43);
	ZVAL_UNDEF(&_62$$43);
	ZVAL_UNDEF(&_63$$43);
	ZVAL_UNDEF(&_75$$47);
	ZVAL_UNDEF(&_76$$47);
	ZVAL_UNDEF(&_77$$47);
	ZVAL_UNDEF(&_15$$24);
	ZVAL_UNDEF(&_29$$28);
	ZVAL_UNDEF(&_53$$43);
	ZVAL_UNDEF(&_67$$47);
	ZVAL_UNDEF(&_101$$66);
	ZVAL_UNDEF(&_106$$73);
	ZVAL_UNDEF(&_115$$81);
	ZVAL_UNDEF(&_120$$88);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	static zend_string *_zephir_prop_9 = NULL;
	static zend_string *_zephir_prop_10 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("ast", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("metaData", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("phql", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("sqlAliases", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("sqlAliasesModels", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("sqlModelsAliases", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("sqlAliasesModelsInstances", 25, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("nestingLevel", 12, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(ast)
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &ast, &merge_param);
	if (!ast) {
		ast = &ast_sub;
		ZEPHIR_CPY_WRT(ast, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(ast);
	}
	if (!merge_param) {
		merge = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&tempModels);
	ZEPHIR_INIT_VAR(&tempModelsInstances);
	ZEPHIR_INIT_VAR(&tempSqlAliases);
	ZEPHIR_INIT_VAR(&tempSqlModelsAliases);
	ZEPHIR_INIT_VAR(&tempSqlAliasesModelsInstances);
	ZEPHIR_INIT_VAR(&tempSqlAliasesModels);
	if (ZEPHIR_IS_EMPTY(ast)) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 771, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(ast, &_0$$3);
	}
	zephir_memory_observe(&select);
	if (!(zephir_array_isset_string_fetch(&select, ast, SL("select"), 0))) {
		ZEPHIR_CPY_WRT(&select, ast);
	}
	zephir_memory_observe(&tables);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&tables, &select, SL("tables"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 3743);
		return;
	}
	zephir_memory_observe(&columns);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&columns, &select, SL("columns"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted SELECT AST", "phalcon/Mvc/Model/Query.zep", 3747);
		return;
	}
	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("nestingLevel")));
	ZEPHIR_INIT_VAR(&sqlModels);
	array_init(&sqlModels);
	ZEPHIR_INIT_VAR(&sqlTables);
	array_init(&sqlTables);
	ZEPHIR_INIT_VAR(&sqlColumns);
	array_init(&sqlColumns);
	ZEPHIR_INIT_VAR(&sqlAliases);
	array_init(&sqlAliases);
	ZEPHIR_INIT_VAR(&sqlAliasesModels);
	array_init(&sqlAliasesModels);
	ZEPHIR_INIT_VAR(&sqlModelsAliases);
	array_init(&sqlModelsAliases);
	ZEPHIR_INIT_VAR(&sqlAliasesModelsInstances);
	array_init(&sqlAliasesModelsInstances);
	ZEPHIR_INIT_VAR(&models);
	array_init(&models);
	ZEPHIR_INIT_VAR(&modelsInstances);
	array_init(&modelsInstances);
	if (!(zephir_array_isset_value_long(&tables, 0))) {
		ZEPHIR_INIT_VAR(&selectedModels);
		zephir_create_array(&selectedModels, 1, 0);
		zephir_array_fast_append(&selectedModels, &tables);
	} else {
		ZEPHIR_CPY_WRT(&selectedModels, &tables);
	}
	if (!(zephir_array_isset_value_long(&columns, 0))) {
		ZEPHIR_INIT_VAR(&selectColumns);
		zephir_create_array(&selectColumns, 1, 0);
		zephir_array_fast_append(&selectColumns, &columns);
	} else {
		ZEPHIR_CPY_WRT(&selectColumns, &columns);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_1);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_2, 773, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&metaData, &_1);
	if (UNEXPECTED(Z_TYPE_P(&manager) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "A models-manager is required to execute the query", "phalcon/Mvc/Model/Query.zep", 3814);
		return;
	}
	if (UNEXPECTED(Z_TYPE_P(&metaData) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "A meta-data is required to execute the query", "phalcon/Mvc/Model/Query.zep", 3820);
		return;
	}
	number = 0;
	ZEPHIR_INIT_VAR(&automaticJoins);
	array_init(&automaticJoins);
	if (Z_TYPE_P(&selectedModels) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &selectedModels);
		_2 = &_3;
	} else {
		_2 = &selectedModels;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/Model/Query.zep", 3950);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
		{
			ZEPHIR_INIT_NVAR(&selectedModel);
			ZVAL_COPY(&selectedModel, _4);
			ZEPHIR_OBS_NVAR(&qualifiedName);
			zephir_array_fetch_string(&qualifiedName, &selectedModel, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3828);
			ZEPHIR_OBS_NVAR(&modelName);
			zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3829);
			ZEPHIR_CALL_METHOD(&model, &manager, "load", &_5, 0, &modelName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&schema)) {
				ZEPHIR_INIT_NVAR(&completeSource);
				zephir_create_array(&completeSource, 2, 0);
				zephir_array_fast_append(&completeSource, &source);
				zephir_array_fast_append(&completeSource, &schema);
			} else {
				ZEPHIR_CPY_WRT(&completeSource, &source);
			}
			ZEPHIR_OBS_NVAR(&alias);
			if (zephir_array_isset_string_fetch(&alias, &selectedModel, SL("alias"), 0)) {
				if (UNEXPECTED(zephir_array_isset_value(&sqlAliases, &alias))) {
					ZEPHIR_INIT_NVAR(&_6$$17);
					object_init_ex(&_6$$17, phalcon_mvc_model_exception_ce);
					zephir_read_property_cached(&_7$$17, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_INIT_NVAR(&_8$$17);
					ZEPHIR_CONCAT_SVSV(&_8$$17, "Alias '", &alias, "' is used more than once, when preparing: ", &_7$$17);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_6$$17, "__construct", &_9, 32, &_8$$17);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_6$$17, "phalcon/Mvc/Model/Query.zep", 3854);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModels, &alias, &modelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlModelsAliases, &modelName, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
				if (Z_TYPE_P(&completeSource) == IS_ARRAY) {
					zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3866);
				} else {
					ZEPHIR_INIT_NVAR(&_10$$19);
					zephir_create_array(&_10$$19, 3, 0);
					zephir_array_fast_append(&_10$$19, &source);
					zephir_array_fast_append(&_10$$19, &__$null);
					zephir_array_fast_append(&_10$$19, &alias);
					ZEPHIR_CPY_WRT(&completeSource, &_10$$19);
				}
				zephir_array_update_zval(&models, &modelName, &alias, PH_COPY | PH_SEPARATE);
			} else {
				ZEPHIR_CPY_WRT(&alias, &source);
				zephir_array_update_zval(&sqlAliases, &modelName, &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModels, &modelName, &modelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlModelsAliases, &modelName, &modelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&models, &modelName, &source, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&with);
			if (zephir_array_isset_string_fetch(&with, &selectedModel, SL("with"), 0)) {
				if (!(zephir_array_isset_value_long(&with, 0))) {
					ZEPHIR_INIT_NVAR(&withs);
					zephir_create_array(&withs, 1, 0);
					zephir_array_fast_append(&withs, &with);
				} else {
					ZEPHIR_CPY_WRT(&withs, &with);
				}
				if (Z_TYPE_P(&withs) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_12$$21);
					zephir_string_to_char_array(&_12$$21, &withs);
					_11$$21 = &_12$$21;
				} else {
					_11$$21 = &withs;
				}
				zephir_is_iterable(_11$$21, 0, "phalcon/Mvc/Model/Query.zep", 3942);
				if (Z_TYPE_P(_11$$21) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_11$$21), _13$$21)
					{
						ZEPHIR_INIT_NVAR(&withItem);
						ZVAL_COPY(&withItem, _13$$21);
						ZEPHIR_INIT_NVAR(&_14$$24);
						ZVAL_LONG(&_14$$24, number);
						ZEPHIR_INIT_NVAR(&_15$$24);
						ZEPHIR_CONCAT_SV(&_15$$24, "AA", &_14$$24);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CPY_WRT(&joinAlias, &_15$$24);
						ZEPHIR_OBS_NVAR(&relationModel);
						zephir_array_fetch_string(&relationModel, &withItem, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3892);
						ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationByAlias", &_16, 0, &modelName, &relationModel);
						zephir_check_call_status();
						if (Z_TYPE_P(&relation) == IS_OBJECT) {
							ZEPHIR_INIT_NVAR(&_17$$25);
							ZVAL_STRING(&_17$$25, "alias");
							ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_17$$25);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
							zephir_check_call_status();
						} else {
							ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationsBetween", &_18, 0, &modelName, &relationModel);
							zephir_check_call_status();
							if (UNEXPECTED(Z_TYPE_P(&relation) != IS_OBJECT)) {
								ZEPHIR_INIT_NVAR(&_19$$27);
								object_init_ex(&_19$$27, phalcon_mvc_model_exception_ce);
								zephir_read_property_cached(&_20$$27, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
								ZEPHIR_INIT_NVAR(&_21$$27);
								ZEPHIR_CONCAT_SVSVSV(&_21$$27, "Can't find a relationship between '", &modelName, "' and '", &relationModel, "' when preparing: ", &_20$$27);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_19$$27, "__construct", &_9, 32, &_21$$27);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_19$$27, "phalcon/Mvc/Model/Query.zep", 3912);
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_INIT_NVAR(&_22$$26);
							ZVAL_STRING(&_22$$26, "alias");
							ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_22$$26);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_INIT_NVAR(&_23$$24);
						zephir_create_array(&_23$$24, 5, 0);
						add_assoc_long_ex(&_23$$24, SL("type"), 353);
						zephir_array_update_string(&_23$$24, SL("column"), &joinAlias, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_23$$24, SL("eager"), &alias, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_23$$24, SL("eagerType"), &eagerType, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_23$$24, SL("balias"), &bestAlias, PH_COPY | PH_SEPARATE);
						zephir_array_append(&selectColumns, &_23$$24, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3926);
						ZEPHIR_INIT_NVAR(&_24$$24);
						zephir_create_array(&_24$$24, 3, 0);
						add_assoc_long_ex(&_24$$24, SL("type"), 360);
						ZEPHIR_INIT_NVAR(&_25$$24);
						zephir_create_array(&_25$$24, 2, 0);
						add_assoc_long_ex(&_25$$24, SL("type"), 355);
						zephir_array_update_string(&_25$$24, SL("name"), &relationModel, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_24$$24, SL("qualified"), &_25$$24, PH_COPY | PH_SEPARATE);
						ZEPHIR_INIT_NVAR(&_25$$24);
						zephir_create_array(&_25$$24, 2, 0);
						add_assoc_long_ex(&_25$$24, SL("type"), 355);
						zephir_array_update_string(&_25$$24, SL("name"), &joinAlias, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_24$$24, SL("alias"), &_25$$24, PH_COPY | PH_SEPARATE);
						zephir_array_append(&automaticJoins, &_24$$24, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3938);
						number++;
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _11$$21, "rewind", NULL, 0);
					zephir_check_call_status();
					_27$$21 = 1;
					while (1) {
						if (_27$$21) {
							_27$$21 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _11$$21, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_26$$21, _11$$21, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_26$$21)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&withItem, _11$$21, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_28$$28);
							ZVAL_LONG(&_28$$28, number);
							ZEPHIR_INIT_NVAR(&_29$$28);
							ZEPHIR_CONCAT_SV(&_29$$28, "AA", &_28$$28);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CPY_WRT(&joinAlias, &_29$$28);
							ZEPHIR_OBS_NVAR(&relationModel);
							zephir_array_fetch_string(&relationModel, &withItem, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3892);
							ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationByAlias", &_30, 0, &modelName, &relationModel);
							zephir_check_call_status();
							if (Z_TYPE_P(&relation) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_31$$29);
								ZVAL_STRING(&_31$$29, "alias");
								ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_31$$29);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
								zephir_check_call_status();
							} else {
								ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationsBetween", &_32, 0, &modelName, &relationModel);
								zephir_check_call_status();
								if (UNEXPECTED(Z_TYPE_P(&relation) != IS_OBJECT)) {
									ZEPHIR_INIT_NVAR(&_33$$31);
									object_init_ex(&_33$$31, phalcon_mvc_model_exception_ce);
									zephir_read_property_cached(&_34$$31, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
									ZEPHIR_INIT_NVAR(&_35$$31);
									ZEPHIR_CONCAT_SVSVSV(&_35$$31, "Can't find a relationship between '", &modelName, "' and '", &relationModel, "' when preparing: ", &_34$$31);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_33$$31, "__construct", &_9, 32, &_35$$31);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_33$$31, "phalcon/Mvc/Model/Query.zep", 3912);
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_INIT_NVAR(&_36$$30);
								ZVAL_STRING(&_36$$30, "alias");
								ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_36$$30);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_INIT_NVAR(&_37$$28);
							zephir_create_array(&_37$$28, 5, 0);
							add_assoc_long_ex(&_37$$28, SL("type"), 353);
							zephir_array_update_string(&_37$$28, SL("column"), &joinAlias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_37$$28, SL("eager"), &alias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_37$$28, SL("eagerType"), &eagerType, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_37$$28, SL("balias"), &bestAlias, PH_COPY | PH_SEPARATE);
							zephir_array_append(&selectColumns, &_37$$28, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3926);
							ZEPHIR_INIT_NVAR(&_38$$28);
							zephir_create_array(&_38$$28, 3, 0);
							add_assoc_long_ex(&_38$$28, SL("type"), 360);
							ZEPHIR_INIT_NVAR(&_39$$28);
							zephir_create_array(&_39$$28, 2, 0);
							add_assoc_long_ex(&_39$$28, SL("type"), 355);
							zephir_array_update_string(&_39$$28, SL("name"), &relationModel, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_38$$28, SL("qualified"), &_39$$28, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_39$$28);
							zephir_create_array(&_39$$28, 2, 0);
							add_assoc_long_ex(&_39$$28, SL("type"), 355);
							zephir_array_update_string(&_39$$28, SL("name"), &joinAlias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_38$$28, SL("alias"), &_39$$28, PH_COPY | PH_SEPARATE);
							zephir_array_append(&automaticJoins, &_38$$28, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3938);
							number++;
					}
				}
				ZEPHIR_INIT_NVAR(&withItem);
			}
			zephir_array_append(&sqlModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3944);
			zephir_array_append(&sqlTables, &completeSource, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3945);
			zephir_array_update_zval(&modelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_41 = 1;
		while (1) {
			if (_41) {
				_41 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_40, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_40)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&selectedModel, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&qualifiedName);
				zephir_array_fetch_string(&qualifiedName, &selectedModel, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3828);
				ZEPHIR_OBS_NVAR(&modelName);
				zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3829);
				ZEPHIR_CALL_METHOD(&model, &manager, "load", &_42, 0, &modelName);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&schema)) {
					ZEPHIR_INIT_NVAR(&_43$$33);
					zephir_create_array(&_43$$33, 2, 0);
					zephir_array_fast_append(&_43$$33, &source);
					zephir_array_fast_append(&_43$$33, &schema);
					ZEPHIR_CPY_WRT(&completeSource, &_43$$33);
				} else {
					ZEPHIR_CPY_WRT(&completeSource, &source);
				}
				ZEPHIR_OBS_NVAR(&alias);
				if (zephir_array_isset_string_fetch(&alias, &selectedModel, SL("alias"), 0)) {
					if (UNEXPECTED(zephir_array_isset_value(&sqlAliases, &alias))) {
						ZEPHIR_INIT_NVAR(&_44$$36);
						object_init_ex(&_44$$36, phalcon_mvc_model_exception_ce);
						zephir_read_property_cached(&_45$$36, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_INIT_NVAR(&_46$$36);
						ZEPHIR_CONCAT_SVSV(&_46$$36, "Alias '", &alias, "' is used more than once, when preparing: ", &_45$$36);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_44$$36, "__construct", &_9, 32, &_46$$36);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_44$$36, "phalcon/Mvc/Model/Query.zep", 3854);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModels, &alias, &modelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlModelsAliases, &modelName, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
					if (Z_TYPE_P(&completeSource) == IS_ARRAY) {
						zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3866);
					} else {
						ZEPHIR_INIT_NVAR(&_47$$38);
						zephir_create_array(&_47$$38, 3, 0);
						zephir_array_fast_append(&_47$$38, &source);
						zephir_array_fast_append(&_47$$38, &__$null);
						zephir_array_fast_append(&_47$$38, &alias);
						ZEPHIR_CPY_WRT(&completeSource, &_47$$38);
					}
					zephir_array_update_zval(&models, &modelName, &alias, PH_COPY | PH_SEPARATE);
				} else {
					ZEPHIR_CPY_WRT(&alias, &source);
					zephir_array_update_zval(&sqlAliases, &modelName, &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModels, &modelName, &modelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlModelsAliases, &modelName, &modelName, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&models, &modelName, &source, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&with);
				if (zephir_array_isset_string_fetch(&with, &selectedModel, SL("with"), 0)) {
					if (!(zephir_array_isset_value_long(&with, 0))) {
						ZEPHIR_INIT_NVAR(&_48$$41);
						zephir_create_array(&_48$$41, 1, 0);
						zephir_array_fast_append(&_48$$41, &with);
						ZEPHIR_CPY_WRT(&withs, &_48$$41);
					} else {
						ZEPHIR_CPY_WRT(&withs, &with);
					}
					if (Z_TYPE_P(&withs) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_50$$40);
						zephir_string_to_char_array(&_50$$40, &withs);
						_49$$40 = &_50$$40;
					} else {
						_49$$40 = &withs;
					}
					zephir_is_iterable(_49$$40, 0, "phalcon/Mvc/Model/Query.zep", 3942);
					if (Z_TYPE_P(_49$$40) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_49$$40), _51$$40)
						{
							ZEPHIR_INIT_NVAR(&withItem);
							ZVAL_COPY(&withItem, _51$$40);
							ZEPHIR_INIT_NVAR(&_52$$43);
							ZVAL_LONG(&_52$$43, number);
							ZEPHIR_INIT_NVAR(&_53$$43);
							ZEPHIR_CONCAT_SV(&_53$$43, "AA", &_52$$43);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CPY_WRT(&joinAlias, &_53$$43);
							ZEPHIR_OBS_NVAR(&relationModel);
							zephir_array_fetch_string(&relationModel, &withItem, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3892);
							ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationByAlias", &_54, 0, &modelName, &relationModel);
							zephir_check_call_status();
							if (Z_TYPE_P(&relation) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_55$$44);
								ZVAL_STRING(&_55$$44, "alias");
								ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_55$$44);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
								zephir_check_call_status();
							} else {
								ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationsBetween", &_56, 0, &modelName, &relationModel);
								zephir_check_call_status();
								if (UNEXPECTED(Z_TYPE_P(&relation) != IS_OBJECT)) {
									ZEPHIR_INIT_NVAR(&_57$$46);
									object_init_ex(&_57$$46, phalcon_mvc_model_exception_ce);
									zephir_read_property_cached(&_58$$46, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
									ZEPHIR_INIT_NVAR(&_59$$46);
									ZEPHIR_CONCAT_SVSVSV(&_59$$46, "Can't find a relationship between '", &modelName, "' and '", &relationModel, "' when preparing: ", &_58$$46);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_57$$46, "__construct", &_9, 32, &_59$$46);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_57$$46, "phalcon/Mvc/Model/Query.zep", 3912);
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_INIT_NVAR(&_60$$45);
								ZVAL_STRING(&_60$$45, "alias");
								ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_60$$45);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_INIT_NVAR(&_61$$43);
							zephir_create_array(&_61$$43, 5, 0);
							add_assoc_long_ex(&_61$$43, SL("type"), 353);
							zephir_array_update_string(&_61$$43, SL("column"), &joinAlias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_61$$43, SL("eager"), &alias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_61$$43, SL("eagerType"), &eagerType, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_61$$43, SL("balias"), &bestAlias, PH_COPY | PH_SEPARATE);
							zephir_array_append(&selectColumns, &_61$$43, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3926);
							ZEPHIR_INIT_NVAR(&_62$$43);
							zephir_create_array(&_62$$43, 3, 0);
							add_assoc_long_ex(&_62$$43, SL("type"), 360);
							ZEPHIR_INIT_NVAR(&_63$$43);
							zephir_create_array(&_63$$43, 2, 0);
							add_assoc_long_ex(&_63$$43, SL("type"), 355);
							zephir_array_update_string(&_63$$43, SL("name"), &relationModel, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_62$$43, SL("qualified"), &_63$$43, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_63$$43);
							zephir_create_array(&_63$$43, 2, 0);
							add_assoc_long_ex(&_63$$43, SL("type"), 355);
							zephir_array_update_string(&_63$$43, SL("name"), &joinAlias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_62$$43, SL("alias"), &_63$$43, PH_COPY | PH_SEPARATE);
							zephir_array_append(&automaticJoins, &_62$$43, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3938);
							number++;
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _49$$40, "rewind", NULL, 0);
						zephir_check_call_status();
						_65$$40 = 1;
						while (1) {
							if (_65$$40) {
								_65$$40 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _49$$40, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_64$$40, _49$$40, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_64$$40)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&withItem, _49$$40, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_INIT_NVAR(&_66$$47);
								ZVAL_LONG(&_66$$47, number);
								ZEPHIR_INIT_NVAR(&_67$$47);
								ZEPHIR_CONCAT_SV(&_67$$47, "AA", &_66$$47);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CPY_WRT(&joinAlias, &_67$$47);
								ZEPHIR_OBS_NVAR(&relationModel);
								zephir_array_fetch_string(&relationModel, &withItem, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 3892);
								ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationByAlias", &_68, 0, &modelName, &relationModel);
								zephir_check_call_status();
								if (Z_TYPE_P(&relation) == IS_OBJECT) {
									ZEPHIR_INIT_NVAR(&_69$$48);
									ZVAL_STRING(&_69$$48, "alias");
									ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_69$$48);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
									zephir_check_call_status();
								} else {
									ZEPHIR_CALL_METHOD(&relation, &manager, "getRelationsBetween", &_70, 0, &modelName, &relationModel);
									zephir_check_call_status();
									if (UNEXPECTED(Z_TYPE_P(&relation) != IS_OBJECT)) {
										ZEPHIR_INIT_NVAR(&_71$$50);
										object_init_ex(&_71$$50, phalcon_mvc_model_exception_ce);
										zephir_read_property_cached(&_72$$50, this_ptr, _zephir_prop_3, 761, PH_NOISY_CC | PH_READONLY);
										ZEPHIR_INIT_NVAR(&_73$$50);
										ZEPHIR_CONCAT_SVSVSV(&_73$$50, "Can't find a relationship between '", &modelName, "' and '", &relationModel, "' when preparing: ", &_72$$50);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										ZEPHIR_CALL_METHOD(NULL, &_71$$50, "__construct", &_9, 32, &_73$$50);
										zephir_check_call_status();
										zephir_throw_exception_debug(&_71$$50, "phalcon/Mvc/Model/Query.zep", 3912);
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_INIT_NVAR(&_74$$49);
									ZVAL_STRING(&_74$$49, "alias");
									ZEPHIR_CALL_METHOD(&bestAlias, &relation, "getOption", NULL, 0, &_74$$49);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&relationModel, &relation, "getReferencedModel", NULL, 0);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&eagerType, &relation, "getType", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_INIT_NVAR(&_75$$47);
								zephir_create_array(&_75$$47, 5, 0);
								add_assoc_long_ex(&_75$$47, SL("type"), 353);
								zephir_array_update_string(&_75$$47, SL("column"), &joinAlias, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&_75$$47, SL("eager"), &alias, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&_75$$47, SL("eagerType"), &eagerType, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&_75$$47, SL("balias"), &bestAlias, PH_COPY | PH_SEPARATE);
								zephir_array_append(&selectColumns, &_75$$47, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3926);
								ZEPHIR_INIT_NVAR(&_76$$47);
								zephir_create_array(&_76$$47, 3, 0);
								add_assoc_long_ex(&_76$$47, SL("type"), 360);
								ZEPHIR_INIT_NVAR(&_77$$47);
								zephir_create_array(&_77$$47, 2, 0);
								add_assoc_long_ex(&_77$$47, SL("type"), 355);
								zephir_array_update_string(&_77$$47, SL("name"), &relationModel, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&_76$$47, SL("qualified"), &_77$$47, PH_COPY | PH_SEPARATE);
								ZEPHIR_INIT_NVAR(&_77$$47);
								zephir_create_array(&_77$$47, 2, 0);
								add_assoc_long_ex(&_77$$47, SL("type"), 355);
								zephir_array_update_string(&_77$$47, SL("name"), &joinAlias, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&_76$$47, SL("alias"), &_77$$47, PH_COPY | PH_SEPARATE);
								zephir_array_append(&automaticJoins, &_76$$47, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3938);
								number++;
						}
					}
					ZEPHIR_INIT_NVAR(&withItem);
				}
				zephir_array_append(&sqlModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3944);
				zephir_array_append(&sqlTables, &completeSource, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3945);
				zephir_array_update_zval(&modelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&selectedModel);
	if (!(merge)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 777, &models);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 776, &modelsInstances);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 778, &sqlAliases);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 779, &sqlAliasesModels);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 780, &sqlModelsAliases);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 781, &sqlAliasesModelsInstances);
	} else {
		ZEPHIR_OBS_NVAR(&tempModels);
		zephir_read_property_cached(&tempModels, this_ptr, _zephir_prop_4, 777, PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(&tempModelsInstances);
		zephir_read_property_cached(&tempModelsInstances, this_ptr, _zephir_prop_5, 776, PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(&tempSqlAliases);
		zephir_read_property_cached(&tempSqlAliases, this_ptr, _zephir_prop_6, 778, PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(&tempSqlAliasesModels);
		zephir_read_property_cached(&tempSqlAliasesModels, this_ptr, _zephir_prop_7, 779, PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(&tempSqlModelsAliases);
		zephir_read_property_cached(&tempSqlModelsAliases, this_ptr, _zephir_prop_8, 780, PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(&tempSqlAliasesModelsInstances);
		zephir_read_property_cached(&tempSqlAliasesModelsInstances, this_ptr, _zephir_prop_9, 781, PH_NOISY_CC);
		ZEPHIR_INIT_VAR(&_78$$52);
		zephir_read_property_cached(&_79$$52, this_ptr, _zephir_prop_4, 777, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_78$$52, &_79$$52, &models);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 777, &_78$$52);
		ZEPHIR_INIT_VAR(&_80$$52);
		zephir_read_property_cached(&_81$$52, this_ptr, _zephir_prop_5, 776, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_80$$52, &_81$$52, &modelsInstances);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 776, &_80$$52);
		ZEPHIR_INIT_VAR(&_82$$52);
		zephir_read_property_cached(&_83$$52, this_ptr, _zephir_prop_6, 778, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_82$$52, &_83$$52, &sqlAliases);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 778, &_82$$52);
		ZEPHIR_INIT_VAR(&_84$$52);
		zephir_read_property_cached(&_85$$52, this_ptr, _zephir_prop_7, 779, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_84$$52, &_85$$52, &sqlAliasesModels);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 779, &_84$$52);
		ZEPHIR_INIT_VAR(&_86$$52);
		zephir_read_property_cached(&_87$$52, this_ptr, _zephir_prop_8, 780, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_86$$52, &_87$$52, &sqlModelsAliases);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 780, &_86$$52);
		ZEPHIR_INIT_VAR(&_88$$52);
		zephir_read_property_cached(&_89$$52, this_ptr, _zephir_prop_9, 781, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_88$$52, &_89$$52, &sqlAliasesModelsInstances);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 781, &_88$$52);
	}
	zephir_memory_observe(&joins);
	zephir_array_isset_string_fetch(&joins, &select, SL("joins"), 0);
	if (zephir_fast_count_int(&joins)) {
		if (zephir_fast_count_int(&automaticJoins)) {
			if (zephir_array_isset_value_long(&joins, 0)) {
				ZEPHIR_INIT_VAR(&_90$$55);
				zephir_fast_array_merge(&_90$$55, &joins, &automaticJoins);
				zephir_array_update_string(&select, SL("joins"), &_90$$55, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_append(&automaticJoins, &joins, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 3981);
				zephir_array_update_string(&select, SL("joins"), &automaticJoins, PH_COPY | PH_SEPARATE);
			}
		}
		ZEPHIR_CALL_METHOD(&sqlJoins, this_ptr, "getJoins", NULL, 0, &select);
		zephir_check_call_status();
	} else {
		if (zephir_fast_count_int(&automaticJoins)) {
			zephir_array_update_string(&select, SL("joins"), &automaticJoins, PH_COPY | PH_SEPARATE);
			ZEPHIR_CALL_METHOD(&sqlJoins, this_ptr, "getJoins", NULL, 0, &select);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&sqlJoins);
			array_init(&sqlJoins);
		}
	}
	position = 0;
	ZEPHIR_INIT_VAR(&sqlColumnAliases);
	array_init(&sqlColumnAliases);
	if (Z_TYPE_P(&selectColumns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_92);
		zephir_string_to_char_array(&_92, &selectColumns);
		_91 = &_92;
	} else {
		_91 = &selectColumns;
	}
	zephir_is_iterable(_91, 0, "phalcon/Mvc/Model/Query.zep", 4032);
	if (Z_TYPE_P(_91) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_91), _93)
		{
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _93);
			ZEPHIR_CALL_METHOD(&_94$$60, this_ptr, "getSelectColumn", &_95, 0, &column);
			zephir_check_call_status();
			if (Z_TYPE_P(&_94$$60) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_97$$60);
				zephir_string_to_char_array(&_97$$60, &_94$$60);
				_96$$60 = &_97$$60;
			} else {
				_96$$60 = &_94$$60;
			}
			zephir_is_iterable(_96$$60, 0, "phalcon/Mvc/Model/Query.zep", 4030);
			if (Z_TYPE_P(_96$$60) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_96$$60), _98$$60)
				{
					ZEPHIR_INIT_NVAR(&sqlColumn);
					ZVAL_COPY(&sqlColumn, _98$$60);
					ZEPHIR_OBS_NVAR(&alias);
					if (zephir_array_isset_string_fetch(&alias, &column, SL("alias"), 0)) {
						zephir_array_update_string(&sqlColumn, SL("balias"), &alias, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&sqlColumn, SL("sqlAlias"), &alias, PH_COPY | PH_SEPARATE);
						zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
						zephir_array_update_zval(&sqlColumnAliases, &alias, &__$true, PH_COPY | PH_SEPARATE);
					} else {
						ZEPHIR_OBS_NVAR(&alias);
						if (zephir_array_isset_string_fetch(&alias, &sqlColumn, SL("balias"), 0)) {
							zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
						} else {
							ZEPHIR_OBS_NVAR(&_99$$65);
							zephir_array_fetch_string(&_99$$65, &sqlColumn, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4020);
							if (ZEPHIR_IS_STRING(&_99$$65, "scalar")) {
								ZEPHIR_INIT_NVAR(&_100$$66);
								ZVAL_LONG(&_100$$66, position);
								ZEPHIR_INIT_NVAR(&_101$$66);
								ZEPHIR_CONCAT_SV(&_101$$66, "_", &_100$$66);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_update_zval(&sqlColumns, &_101$$66, &sqlColumn, PH_COPY | PH_SEPARATE);
							} else {
								zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4023);
							}
						}
					}
					position++;
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _96$$60, "rewind", NULL, 0);
				zephir_check_call_status();
				_103$$60 = 1;
				while (1) {
					if (_103$$60) {
						_103$$60 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _96$$60, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_102$$60, _96$$60, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_102$$60)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&sqlColumn, _96$$60, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&alias);
						if (zephir_array_isset_string_fetch(&alias, &column, SL("alias"), 0)) {
							zephir_array_update_string(&sqlColumn, SL("balias"), &alias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&sqlColumn, SL("sqlAlias"), &alias, PH_COPY | PH_SEPARATE);
							zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
							zephir_array_update_zval(&sqlColumnAliases, &alias, &__$true, PH_COPY | PH_SEPARATE);
						} else {
							ZEPHIR_OBS_NVAR(&alias);
							if (zephir_array_isset_string_fetch(&alias, &sqlColumn, SL("balias"), 0)) {
								zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
							} else {
								ZEPHIR_OBS_NVAR(&_104$$72);
								zephir_array_fetch_string(&_104$$72, &sqlColumn, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4020);
								if (ZEPHIR_IS_STRING(&_104$$72, "scalar")) {
									ZEPHIR_INIT_NVAR(&_105$$73);
									ZVAL_LONG(&_105$$73, position);
									ZEPHIR_INIT_NVAR(&_106$$73);
									ZEPHIR_CONCAT_SV(&_106$$73, "_", &_105$$73);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_update_zval(&sqlColumns, &_106$$73, &sqlColumn, PH_COPY | PH_SEPARATE);
								} else {
									zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4023);
								}
							}
						}
						position++;
				}
			}
			ZEPHIR_INIT_NVAR(&sqlColumn);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _91, "rewind", NULL, 0);
		zephir_check_call_status();
		_108 = 1;
		while (1) {
			if (_108) {
				_108 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _91, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_107, _91, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_107)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&column, _91, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_109$$75, this_ptr, "getSelectColumn", &_95, 0, &column);
				zephir_check_call_status();
				if (Z_TYPE_P(&_109$$75) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_111$$75);
					zephir_string_to_char_array(&_111$$75, &_109$$75);
					_110$$75 = &_111$$75;
				} else {
					_110$$75 = &_109$$75;
				}
				zephir_is_iterable(_110$$75, 0, "phalcon/Mvc/Model/Query.zep", 4030);
				if (Z_TYPE_P(_110$$75) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_110$$75), _112$$75)
					{
						ZEPHIR_INIT_NVAR(&sqlColumn);
						ZVAL_COPY(&sqlColumn, _112$$75);
						ZEPHIR_OBS_NVAR(&alias);
						if (zephir_array_isset_string_fetch(&alias, &column, SL("alias"), 0)) {
							zephir_array_update_string(&sqlColumn, SL("balias"), &alias, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&sqlColumn, SL("sqlAlias"), &alias, PH_COPY | PH_SEPARATE);
							zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
							zephir_array_update_zval(&sqlColumnAliases, &alias, &__$true, PH_COPY | PH_SEPARATE);
						} else {
							ZEPHIR_OBS_NVAR(&alias);
							if (zephir_array_isset_string_fetch(&alias, &sqlColumn, SL("balias"), 0)) {
								zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
							} else {
								ZEPHIR_OBS_NVAR(&_113$$80);
								zephir_array_fetch_string(&_113$$80, &sqlColumn, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4020);
								if (ZEPHIR_IS_STRING(&_113$$80, "scalar")) {
									ZEPHIR_INIT_NVAR(&_114$$81);
									ZVAL_LONG(&_114$$81, position);
									ZEPHIR_INIT_NVAR(&_115$$81);
									ZEPHIR_CONCAT_SV(&_115$$81, "_", &_114$$81);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_update_zval(&sqlColumns, &_115$$81, &sqlColumn, PH_COPY | PH_SEPARATE);
								} else {
									zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4023);
								}
							}
						}
						position++;
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _110$$75, "rewind", NULL, 0);
					zephir_check_call_status();
					_117$$75 = 1;
					while (1) {
						if (_117$$75) {
							_117$$75 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _110$$75, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_116$$75, _110$$75, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_116$$75)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&sqlColumn, _110$$75, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_OBS_NVAR(&alias);
							if (zephir_array_isset_string_fetch(&alias, &column, SL("alias"), 0)) {
								zephir_array_update_string(&sqlColumn, SL("balias"), &alias, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&sqlColumn, SL("sqlAlias"), &alias, PH_COPY | PH_SEPARATE);
								zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
								zephir_array_update_zval(&sqlColumnAliases, &alias, &__$true, PH_COPY | PH_SEPARATE);
							} else {
								ZEPHIR_OBS_NVAR(&alias);
								if (zephir_array_isset_string_fetch(&alias, &sqlColumn, SL("balias"), 0)) {
									zephir_array_update_zval(&sqlColumns, &alias, &sqlColumn, PH_COPY | PH_SEPARATE);
								} else {
									ZEPHIR_OBS_NVAR(&_118$$87);
									zephir_array_fetch_string(&_118$$87, &sqlColumn, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4020);
									if (ZEPHIR_IS_STRING(&_118$$87, "scalar")) {
										ZEPHIR_INIT_NVAR(&_119$$88);
										ZVAL_LONG(&_119$$88, position);
										ZEPHIR_INIT_NVAR(&_120$$88);
										ZEPHIR_CONCAT_SV(&_120$$88, "_", &_119$$88);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										zephir_array_update_zval(&sqlColumns, &_120$$88, &sqlColumn, PH_COPY | PH_SEPARATE);
									} else {
										zephir_array_append(&sqlColumns, &sqlColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4023);
									}
								}
							}
							position++;
					}
				}
				ZEPHIR_INIT_NVAR(&sqlColumn);
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	zephir_memory_observe(&_121);
	zephir_read_property_cached(&_121, this_ptr, _zephir_prop_10, 782, PH_NOISY_CC);
	zephir_update_property_array(this_ptr, SL("sqlColumnAliases"), &_121, &sqlColumnAliases);
	ZEPHIR_INIT_VAR(&sqlSelect);
	zephir_create_array(&sqlSelect, 3, 0);
	zephir_array_update_string(&sqlSelect, SL("models"), &sqlModels, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlSelect, SL("tables"), &sqlTables, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlSelect, SL("columns"), &sqlColumns, PH_COPY | PH_SEPARATE);
	zephir_memory_observe(&distinct);
	if (zephir_array_isset_string_fetch(&distinct, &select, SL("distinct"), 0)) {
		zephir_array_update_string(&sqlSelect, SL("distinct"), &distinct, PH_COPY | PH_SEPARATE);
	}
	if (zephir_fast_count_int(&sqlJoins)) {
		zephir_array_update_string(&sqlSelect, SL("joins"), &sqlJoins, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&where);
	if (zephir_array_isset_string_fetch(&where, ast, SL("where"), 0)) {
		ZEPHIR_CALL_METHOD(&_122$$92, this_ptr, "getExpression", NULL, 498, &where);
		zephir_check_call_status();
		zephir_array_update_string(&sqlSelect, SL("where"), &_122$$92, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&groupBy);
	if (zephir_array_isset_string_fetch(&groupBy, ast, SL("groupBy"), 0)) {
		ZEPHIR_CALL_METHOD(&_123$$93, this_ptr, "getGroupClause", NULL, 0, &groupBy);
		zephir_check_call_status();
		zephir_array_update_string(&sqlSelect, SL("group"), &_123$$93, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&having);
	if (zephir_array_isset_string_fetch(&having, ast, SL("having"), 0)) {
		ZEPHIR_CALL_METHOD(&_124$$94, this_ptr, "getExpression", NULL, 498, &having);
		zephir_check_call_status();
		zephir_array_update_string(&sqlSelect, SL("having"), &_124$$94, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&order);
	if (zephir_array_isset_string_fetch(&order, ast, SL("orderBy"), 0)) {
		ZEPHIR_CALL_METHOD(&_125$$95, this_ptr, "getOrderClause", NULL, 0, &order);
		zephir_check_call_status();
		zephir_array_update_string(&sqlSelect, SL("order"), &_125$$95, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&limit);
	if (zephir_array_isset_string_fetch(&limit, ast, SL("limit"), 0)) {
		ZEPHIR_CALL_METHOD(&_126$$96, this_ptr, "getLimitClause", NULL, 0, &limit);
		zephir_check_call_status();
		zephir_array_update_string(&sqlSelect, SL("limit"), &_126$$96, PH_COPY | PH_SEPARATE);
	}
	if (zephir_array_isset_value_string(ast, SL("forUpdate"))) {
		zephir_array_update_string(&sqlSelect, SL("forUpdate"), &__$true, PH_COPY | PH_SEPARATE);
	}
	if (merge) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 777, &tempModels);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 776, &tempModelsInstances);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 778, &tempSqlAliases);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 779, &tempSqlAliasesModels);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 780, &tempSqlModelsAliases);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 781, &tempSqlAliasesModelsInstances);
	}
	RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("nestingLevel")));
	RETURN_CCTOR(&sqlSelect);
}

/**
 * Analyzes an UPDATE intermediate code and produces an array to be executed
 * later
 */
PHP_METHOD(Phalcon_Mvc_Model_Query, _prepareUpdate)
{
	zval _19$$20, _28$$21;
	zend_bool notQuoting = 0, _8, _24;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null, ast, update, tables, values, modelsInstances, models, sqlTables, sqlAliases, sqlAliasesModelsInstances, updateTables, completeSource, sqlModels, manager, table, qualifiedName, modelName, model, source, schema, alias, sqlFields, sqlValues, updateValues, updateValue, exprColumn, sqlUpdate, where, limit, _0, *_1, _2, *_3, _7, *_12, _13, *_14, _23, _5$$9, _6$$10, _10$$14, _11$$15, _15$$20, _16$$20, _17$$20, _20$$20, _21$$20, _22$$20, _25$$21, _26$$21, _27$$21, _29$$21, _30$$21, _31$$21, _32$$22, _33$$22, _34$$23;
	zephir_fcall_cache_entry *_4 = NULL, *_9 = NULL, *_18 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&ast);
	ZVAL_UNDEF(&update);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&modelsInstances);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&sqlTables);
	ZVAL_UNDEF(&sqlAliases);
	ZVAL_UNDEF(&sqlAliasesModelsInstances);
	ZVAL_UNDEF(&updateTables);
	ZVAL_UNDEF(&completeSource);
	ZVAL_UNDEF(&sqlModels);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&qualifiedName);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&sqlFields);
	ZVAL_UNDEF(&sqlValues);
	ZVAL_UNDEF(&updateValues);
	ZVAL_UNDEF(&updateValue);
	ZVAL_UNDEF(&exprColumn);
	ZVAL_UNDEF(&sqlUpdate);
	ZVAL_UNDEF(&where);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_5$$9);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_10$$14);
	ZVAL_UNDEF(&_11$$15);
	ZVAL_UNDEF(&_15$$20);
	ZVAL_UNDEF(&_16$$20);
	ZVAL_UNDEF(&_17$$20);
	ZVAL_UNDEF(&_20$$20);
	ZVAL_UNDEF(&_21$$20);
	ZVAL_UNDEF(&_22$$20);
	ZVAL_UNDEF(&_25$$21);
	ZVAL_UNDEF(&_26$$21);
	ZVAL_UNDEF(&_27$$21);
	ZVAL_UNDEF(&_29$$21);
	ZVAL_UNDEF(&_30$$21);
	ZVAL_UNDEF(&_31$$21);
	ZVAL_UNDEF(&_32$$22);
	ZVAL_UNDEF(&_33$$22);
	ZVAL_UNDEF(&_34$$23);
	ZVAL_UNDEF(&_19$$20);
	ZVAL_UNDEF(&_28$$21);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("ast", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("modelsInstances", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("sqlAliases", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("sqlAliasesModelsInstances", 25, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 771, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&ast, &_0);
	zephir_memory_observe(&update);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&update, &ast, SL("update"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted UPDATE AST", "phalcon/Mvc/Model/Query.zep", 4109);
		return;
	}
	zephir_memory_observe(&tables);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&tables, &update, SL("tables"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted UPDATE AST", "phalcon/Mvc/Model/Query.zep", 4113);
		return;
	}
	zephir_memory_observe(&values);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&values, &update, SL("values"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Corrupted UPDATE AST", "phalcon/Mvc/Model/Query.zep", 4117);
		return;
	}
	ZEPHIR_INIT_VAR(&models);
	array_init(&models);
	ZEPHIR_INIT_VAR(&modelsInstances);
	array_init(&modelsInstances);
	ZEPHIR_INIT_VAR(&sqlTables);
	array_init(&sqlTables);
	ZEPHIR_INIT_VAR(&sqlModels);
	array_init(&sqlModels);
	ZEPHIR_INIT_VAR(&sqlAliases);
	array_init(&sqlAliases);
	ZEPHIR_INIT_VAR(&sqlAliasesModelsInstances);
	array_init(&sqlAliasesModelsInstances);
	if (!(zephir_array_isset_value_long(&tables, 0))) {
		ZEPHIR_INIT_VAR(&updateTables);
		zephir_create_array(&updateTables, 1, 0);
		zephir_array_fast_append(&updateTables, &tables);
	} else {
		ZEPHIR_CPY_WRT(&updateTables, &tables);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 772, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	if (Z_TYPE_P(&updateTables) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &updateTables);
		_1 = &_2;
	} else {
		_1 = &updateTables;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query.zep", 4183);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&table);
			ZVAL_COPY(&table, _3);
			ZEPHIR_OBS_NVAR(&qualifiedName);
			zephir_array_fetch_string(&qualifiedName, &table, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4141);
			ZEPHIR_OBS_NVAR(&modelName);
			zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4142);
			ZEPHIR_CALL_METHOD(&model, &manager, "load", &_4, 0, &modelName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&completeSource);
			if (zephir_is_true(&schema)) {
				ZEPHIR_INIT_NVAR(&_5$$9);
				zephir_create_array(&_5$$9, 2, 0);
				zephir_array_fast_append(&_5$$9, &source);
				zephir_array_fast_append(&_5$$9, &schema);
				ZEPHIR_CPY_WRT(&completeSource, &_5$$9);
			} else {
				ZEPHIR_INIT_NVAR(&_6$$10);
				zephir_create_array(&_6$$10, 2, 0);
				zephir_array_fast_append(&_6$$10, &source);
				zephir_array_fast_append(&_6$$10, &__$null);
				ZEPHIR_CPY_WRT(&completeSource, &_6$$10);
			}
			ZEPHIR_OBS_NVAR(&alias);
			if (zephir_array_isset_string_fetch(&alias, &table, SL("alias"), 0)) {
				zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
				zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4165);
				zephir_array_append(&sqlTables, &completeSource, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4166);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&models, &alias, &modelName, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&sqlAliases, &modelName, &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&sqlAliasesModelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
				zephir_array_append(&sqlTables, &source, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4172);
				zephir_array_update_zval(&models, &modelName, &source, PH_COPY | PH_SEPARATE);
			}
			zephir_array_append(&sqlModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4176);
			zephir_array_update_zval(&modelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&table, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&qualifiedName);
				zephir_array_fetch_string(&qualifiedName, &table, SL("qualifiedName"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4141);
				ZEPHIR_OBS_NVAR(&modelName);
				zephir_array_fetch_string(&modelName, &qualifiedName, SL("name"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4142);
				ZEPHIR_CALL_METHOD(&model, &manager, "load", &_9, 0, &modelName);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&schema)) {
					ZEPHIR_INIT_NVAR(&_10$$14);
					zephir_create_array(&_10$$14, 2, 0);
					zephir_array_fast_append(&_10$$14, &source);
					zephir_array_fast_append(&_10$$14, &schema);
					ZEPHIR_CPY_WRT(&completeSource, &_10$$14);
				} else {
					ZEPHIR_INIT_NVAR(&_11$$15);
					zephir_create_array(&_11$$15, 2, 0);
					zephir_array_fast_append(&_11$$15, &source);
					zephir_array_fast_append(&_11$$15, &__$null);
					ZEPHIR_CPY_WRT(&completeSource, &_11$$15);
				}
				ZEPHIR_OBS_NVAR(&alias);
				if (zephir_array_isset_string_fetch(&alias, &table, SL("alias"), 0)) {
					zephir_array_update_zval(&sqlAliases, &alias, &alias, PH_COPY | PH_SEPARATE);
					zephir_array_append(&completeSource, &alias, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4165);
					zephir_array_append(&sqlTables, &completeSource, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4166);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &alias, &model, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&models, &alias, &modelName, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&sqlAliases, &modelName, &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&sqlAliasesModelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
					zephir_array_append(&sqlTables, &source, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4172);
					zephir_array_update_zval(&models, &modelName, &source, PH_COPY | PH_SEPARATE);
				}
				zephir_array_append(&sqlModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4176);
				zephir_array_update_zval(&modelsInstances, &modelName, &model, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&table);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 777, &models);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 776, &modelsInstances);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 778, &sqlAliases);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 781, &sqlAliasesModelsInstances);
	ZEPHIR_INIT_VAR(&sqlFields);
	array_init(&sqlFields);
	ZEPHIR_INIT_VAR(&sqlValues);
	array_init(&sqlValues);
	if (!(zephir_array_isset_value_long(&values, 0))) {
		ZEPHIR_INIT_VAR(&updateValues);
		zephir_create_array(&updateValues, 1, 0);
		zephir_array_fast_append(&updateValues, &values);
	} else {
		ZEPHIR_CPY_WRT(&updateValues, &values);
	}
	notQuoting = 0;
	if (Z_TYPE_P(&updateValues) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_13);
		zephir_string_to_char_array(&_13, &updateValues);
		_12 = &_13;
	} else {
		_12 = &updateValues;
	}
	zephir_is_iterable(_12, 0, "phalcon/Mvc/Model/Query.zep", 4207);
	if (Z_TYPE_P(_12) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_12), _14)
		{
			ZEPHIR_INIT_NVAR(&updateValue);
			ZVAL_COPY(&updateValue, _14);
			ZEPHIR_OBS_NVAR(&_16$$20);
			zephir_array_fetch_string(&_16$$20, &updateValue, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4199);
			if (notQuoting) {
				ZVAL_BOOL(&_17$$20, 1);
			} else {
				ZVAL_BOOL(&_17$$20, 0);
			}
			ZEPHIR_CALL_METHOD(&_15$$20, this_ptr, "getExpression", &_18, 498, &_16$$20, &_17$$20);
			zephir_check_call_status();
			zephir_array_append(&sqlFields, &_15$$20, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4199);
			ZEPHIR_OBS_NVAR(&exprColumn);
			zephir_array_fetch_string(&exprColumn, &updateValue, SL("expr"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4200);
			ZEPHIR_INIT_NVAR(&_19$$20);
			zephir_create_array(&_19$$20, 2, 0);
			ZEPHIR_OBS_NVAR(&_20$$20);
			zephir_array_fetch_string(&_20$$20, &exprColumn, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4202);
			zephir_array_update_string(&_19$$20, SL("type"), &_20$$20, PH_COPY | PH_SEPARATE);
			if (notQuoting) {
				ZVAL_BOOL(&_22$$20, 1);
			} else {
				ZVAL_BOOL(&_22$$20, 0);
			}
			ZEPHIR_CALL_METHOD(&_21$$20, this_ptr, "getExpression", &_18, 498, &exprColumn, &_22$$20);
			zephir_check_call_status();
			zephir_array_update_string(&_19$$20, SL("value"), &_21$$20, PH_COPY | PH_SEPARATE);
			zephir_array_append(&sqlValues, &_19$$20, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4204);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _12, "rewind", NULL, 0);
		zephir_check_call_status();
		_24 = 1;
		while (1) {
			if (_24) {
				_24 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _12, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_23, _12, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_23)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&updateValue, _12, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_26$$21);
				zephir_array_fetch_string(&_26$$21, &updateValue, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4199);
				if (notQuoting) {
					ZVAL_BOOL(&_27$$21, 1);
				} else {
					ZVAL_BOOL(&_27$$21, 0);
				}
				ZEPHIR_CALL_METHOD(&_25$$21, this_ptr, "getExpression", &_18, 498, &_26$$21, &_27$$21);
				zephir_check_call_status();
				zephir_array_append(&sqlFields, &_25$$21, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4199);
				ZEPHIR_OBS_NVAR(&exprColumn);
				zephir_array_fetch_string(&exprColumn, &updateValue, SL("expr"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4200);
				ZEPHIR_INIT_NVAR(&_28$$21);
				zephir_create_array(&_28$$21, 2, 0);
				ZEPHIR_OBS_NVAR(&_29$$21);
				zephir_array_fetch_string(&_29$$21, &exprColumn, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query.zep", 4202);
				zephir_array_update_string(&_28$$21, SL("type"), &_29$$21, PH_COPY | PH_SEPARATE);
				if (notQuoting) {
					ZVAL_BOOL(&_31$$21, 1);
				} else {
					ZVAL_BOOL(&_31$$21, 0);
				}
				ZEPHIR_CALL_METHOD(&_30$$21, this_ptr, "getExpression", &_18, 498, &exprColumn, &_31$$21);
				zephir_check_call_status();
				zephir_array_update_string(&_28$$21, SL("value"), &_30$$21, PH_COPY | PH_SEPARATE);
				zephir_array_append(&sqlValues, &_28$$21, PH_SEPARATE, "phalcon/Mvc/Model/Query.zep", 4204);
		}
	}
	ZEPHIR_INIT_NVAR(&updateValue);
	ZEPHIR_INIT_VAR(&sqlUpdate);
	zephir_create_array(&sqlUpdate, 4, 0);
	zephir_array_update_string(&sqlUpdate, SL("tables"), &sqlTables, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlUpdate, SL("models"), &sqlModels, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlUpdate, SL("fields"), &sqlFields, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&sqlUpdate, SL("values"), &sqlValues, PH_COPY | PH_SEPARATE);
	zephir_memory_observe(&where);
	if (zephir_array_isset_string_fetch(&where, &ast, SL("where"), 0)) {
		ZVAL_BOOL(&_33$$22, 1);
		ZEPHIR_CALL_METHOD(&_32$$22, this_ptr, "getExpression", &_18, 498, &where, &_33$$22);
		zephir_check_call_status();
		zephir_array_update_string(&sqlUpdate, SL("where"), &_32$$22, PH_COPY | PH_SEPARATE);
	}
	zephir_memory_observe(&limit);
	if (zephir_array_isset_string_fetch(&limit, &ast, SL("limit"), 0)) {
		ZEPHIR_CALL_METHOD(&_34$$23, this_ptr, "getLimitClause", NULL, 0, &limit);
		zephir_check_call_status();
		zephir_array_update_string(&sqlUpdate, SL("limit"), &_34$$23, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(&sqlUpdate);
}

zend_object *zephir_init_properties_Phalcon_Mvc_Model_Query(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _12, _14, _16, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9, _15$$10, _17$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_17$$11);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("sqlModelsAliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlModelsAliases"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("sqlColumnAliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlColumnAliases"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("sqlAliasesModelsInstances"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlAliasesModelsInstances"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("sqlAliasesModels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlAliasesModels"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("sqlAliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("sqlAliases"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("modelsInstances"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("modelsInstances"), &_11$$8);
		}
		zephir_read_property_ex(&_12, this_ptr, ZEND_STRL("models"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("models"), &_13$$9);
		}
		zephir_read_property_ex(&_14, this_ptr, ZEND_STRL("bindTypes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_14) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_15$$10);
			array_init(&_15$$10);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("bindTypes"), &_15$$10);
		}
		zephir_read_property_ex(&_16, this_ptr, ZEND_STRL("bindParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_16) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_17$$11);
			array_init(&_17$$11);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("bindParams"), &_17$$11);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

