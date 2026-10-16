
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
#include "ext/json/php_json.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/main.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/iterator.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the
 * LICENSE.txt file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Model
 *
 * Phalcon\Mvc\Model connects business objects and database tables to create a
 * persistable domain model where logic and data are presented in one wrapping.
 * It‘s an implementation of the object-relational mapping (ORM).
 *
 * A model represents the information (data) of the application and the rules to
 * manipulate that data. Models are primarily used for managing the rules of
 * interaction with a corresponding database table. In most cases, each table in
 * your database will correspond to one model in your application. The bulk of
 * your application's business logic will be concentrated in the models.
 *
 * Phalcon\Mvc\Model is the first ORM written in Zephir/C languages for PHP,
 * giving to developers high performance when interacting with databases while
 * is also easy to use.
 *
 * ```php
 * $robot = new Robots();
 *
 * $robot->type = "mechanical";
 * $robot->name = "Astro Boy";
 * $robot->year = 1952;
 *
 * if ($robot->save() === false) {
 *     echo "Umh, We can store robots: ";
 *
 *     $messages = $robot->getMessages();
 *
 *     foreach ($messages as $message) {
 *         echo $message;
 *     }
 * } else {
 *     echo "Great, a new robot was saved successfully!";
 * }
 * ```
 * @template T of static
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, Model, phalcon, mvc_model, phalcon_di_abstractinjectionaware_ce, phalcon_mvc_model_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_model_ce, SL("dirtyState"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("dirtyRelated"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("errorMessages"), ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("modelsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var MetaDataInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("modelsMetaData"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("related"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_model_ce, SL("operationMade"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("oldSnapshot"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_ce, SL("skipped"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("snapshot"), ZEND_ACC_PROTECTED);
	/**
	 * @var TransactionInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("transaction"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("uniqueKey"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("uniqueParams"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_ce, SL("uniqueTypes"), ZEND_ACC_PROTECTED);
	phalcon_mvc_model_ce->create_object = zephir_init_properties_Phalcon_Mvc_Model;
	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("DIRTY_STATE_DETACHED"), 2);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("DIRTY_STATE_PERSISTENT"), 0);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("DIRTY_STATE_TRANSIENT"), 1);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_CREATE"), 1);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_DELETE"), 3);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_NONE"), 0);

	/**
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_UPDATE"), 2);

	/**
	 * @var string
	 */
	zephir_declare_class_constant_string(phalcon_mvc_model_ce, SL("TRANSACTION_INDEX"), "transaction");

	zend_class_implements(phalcon_mvc_model_ce, 1, phalcon_mvc_entityinterface_ce);
	zend_class_implements(phalcon_mvc_model_ce, 1, phalcon_mvc_modelinterface_ce);
	zend_class_implements(phalcon_mvc_model_ce, 1, phalcon_mvc_model_resultinterface_ce);
	zend_class_implements(phalcon_mvc_model_ce, 1, zend_ce_serializable);
	zend_class_implements(phalcon_mvc_model_ce, 1, php_json_serializable_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model constructor
 */
PHP_METHOD(Phalcon_Mvc_Model, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL, data_sub, *container = NULL, container_sub, *modelsManager = NULL, modelsManager_sub, __$null, _0$$4, _1$$4, _2$$4, _3$$5, _4$$5, _5$$6, _6$$6, _7$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&modelsManager_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsManager", 13, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(data)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(modelsManager, phalcon_mvc_model_managerinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &data, &container, &modelsManager);
	if (!data) {
		data = &data_sub;
		data = &__$null;
	}
	if (!container) {
		container = &container_sub;
		ZEPHIR_CPY_WRT(container, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(container);
	}
	if (!modelsManager) {
		modelsManager = &modelsManager_sub;
		ZEPHIR_CPY_WRT(modelsManager, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(modelsManager);
	}
	if (Z_TYPE_P(container) == IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(container, phalcon_di_di_ce, "getDefault", NULL, 0);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(container) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_0$$4);
		object_init_ex(&_0$$4, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$4);
		zephir_get_class(&_1$$4, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_2$$4);
		ZEPHIR_CONCAT_SVS(&_2$$4, "A dependency injection container is required to access the services related to the ODM in '", &_1$$4, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_0$$4, "__construct", NULL, 32, &_2$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$4, "phalcon/Mvc/Model.zep", 210);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 707, container);
	if (Z_TYPE_P(modelsManager) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "modelsManager");
		ZEPHIR_CALL_METHOD(&_3$$5, container, "getShared", NULL, 0, &_4$$5);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(modelsManager, &_3$$5);
		if (Z_TYPE_P(modelsManager) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$6);
			object_init_ex(&_5$$6, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_6$$6);
			zephir_get_class(&_6$$6, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_7$$6);
			ZEPHIR_CONCAT_SVS(&_7$$6, "The injected service 'modelsManager' is not valid in '", &_6$$6, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_5$$6, "__construct", NULL, 32, &_7$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_5$$6, "phalcon/Mvc/Model.zep", 223);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 708, modelsManager);
	ZEPHIR_CALL_METHOD(NULL, modelsManager, "initialize", NULL, 0, this_ptr);
	zephir_check_call_status();
	if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("onconstruct")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "onConstruct", NULL, 0, data);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(data) == IS_ARRAY) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "assign", NULL, 0, data);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Handles method calls when a method is not implemented
 *
 * @return mixed
 * @throws \Phalcon\Mvc\Model\Exception If the method does not exist
 */
PHP_METHOD(Phalcon_Mvc_Model, __call)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval arguments;
	zval method_zv, *arguments_param = NULL, modelName, status, records, _1, _2, _3;
	zend_string *method = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&records);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&arguments);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	arguments_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	zephir_get_arrval(&arguments, arguments_param);
	ZEPHIR_CALL_SELF(&records, "invokeFinder", &_0, 459, &method_zv, &arguments);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&records)) {
		RETURN_CCTOR(&records);
	}
	ZEPHIR_INIT_VAR(&modelName);
	zephir_get_class(&modelName, this_ptr, 0);
	ZEPHIR_CALL_METHOD(&records, this_ptr, "getRelatedRecords", NULL, 0, &modelName, &method_zv, &arguments);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&records)) {
		RETURN_CCTOR(&records);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&status, &_1, "missingMethod", NULL, 0, this_ptr, &method_zv, &arguments);
	zephir_check_call_status();
	if (Z_TYPE_P(&status) != IS_NULL) {
		RETURN_CCTOR(&status);
	}
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, phalcon_mvc_model_exception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SVSVS(&_3, "The method '", &method_zv, "' does not exist on model '", &modelName, "'");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 32, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "phalcon/Mvc/Model.zep", 292);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Handles method calls when a static method is not implemented
 *
 * @return mixed
 * @throws \Phalcon\Mvc\Model\Exception If the method does not exist
 */
PHP_METHOD(Phalcon_Mvc_Model, __callStatic)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval arguments;
	zval method_zv, *arguments_param = NULL, modelName, records, _1, _2;
	zend_string *method = NULL;

	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&records);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&arguments);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	arguments_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	zephir_get_arrval(&arguments, arguments_param);
	ZEPHIR_CALL_SELF(&records, "invokeFinder", &_0, 459, &method_zv, &arguments);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&records)) {
		RETURN_CCTOR(&records);
	}
	ZEPHIR_INIT_VAR(&modelName);
	zephir_get_called_class(&modelName);
	ZEPHIR_INIT_VAR(&_1);
	object_init_ex(&_1, phalcon_mvc_model_exception_ce);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_CONCAT_SVSVS(&_2, "The method '", &method_zv, "' does not exist on model '", &modelName, "'");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 32, &_2);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_1, "phalcon/Mvc/Model.zep", 318);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Magic method to get related records using the relation alias as a
 * property
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, __get)
{
	zend_bool _5$$3, _9$$5;
	zval method;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval property_zv, modelName, manager, lowerProperty, relation, _0, _14, _15, _16, _1$$3, _4$$3, _6$$3, _2$$4, _3$$4, _7$$5, _8$$5, _10$$5, _11$$5, _12$$6, _13$$6;
	zend_string *property = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&property_zv);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&lowerProperty);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&method);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyRelated", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("related", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(property)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&property_zv);
	ZVAL_STR_COPY(&property_zv, property);
	ZEPHIR_INIT_VAR(&modelName);
	zephir_get_class(&modelName, this_ptr, 0);
	ZEPHIR_CALL_METHOD(&manager, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&lowerProperty);
	zephir_fast_strtolower(&lowerProperty, &property_zv);
	ZEPHIR_CALL_METHOD(&_0, &manager, "getRelationByAlias", NULL, 0, &modelName, &lowerProperty);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&relation, &_0);
	if (Z_TYPE_P(&relation) == IS_OBJECT) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 709, PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset_value(&_1$$3, &lowerProperty)) {
			zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_0, 709, PH_NOISY_CC | PH_READONLY);
			zephir_memory_observe(&_3$$4);
			zephir_array_fetch(&_3$$4, &_2$$4, &lowerProperty, PH_NOISY, "phalcon/Mvc/Model.zep", 350);
			RETURN_CCTOR(&_3$$4);
		}
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_1, 710, PH_NOISY_CC | PH_READONLY);
		_5$$3 = zephir_array_isset_value(&_4$$3, &lowerProperty);
		if (_5$$3) {
			ZEPHIR_CALL_METHOD(&_6$$3, &relation, "isReusable", NULL, 0);
			zephir_check_call_status();
			_5$$3 = !zephir_is_true(&_6$$3);
		}
		if (_5$$3) {
			zephir_read_property_cached(&_7$$5, this_ptr, _zephir_prop_1, 710, PH_NOISY_CC | PH_READONLY);
			zephir_memory_observe(&_8$$5);
			zephir_array_fetch(&_8$$5, &_7$$5, &lowerProperty, PH_NOISY, "phalcon/Mvc/Model.zep", 361);
			_9$$5 = Z_TYPE_P(&_8$$5) == IS_OBJECT;
			if (_9$$5) {
				zephir_read_property_cached(&_10$$5, this_ptr, _zephir_prop_1, 710, PH_NOISY_CC | PH_READONLY);
				zephir_memory_observe(&_11$$5);
				zephir_array_fetch(&_11$$5, &_10$$5, &lowerProperty, PH_NOISY, "phalcon/Mvc/Model.zep", 361);
				_9$$5 = (zephir_instance_of_ev(&_11$$5, phalcon_mvc_modelinterface_ce));
			}
			if (_9$$5) {
				zephir_read_property_cached(&_12$$6, this_ptr, _zephir_prop_1, 710, PH_NOISY_CC | PH_READONLY);
				zephir_memory_observe(&_13$$6);
				zephir_array_fetch(&_13$$6, &_12$$6, &lowerProperty, PH_NOISY, "phalcon/Mvc/Model.zep", 362);
				RETURN_CCTOR(&_13$$6);
			}
		}
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getRelated", NULL, 0, &lowerProperty);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_14);
	zephir_camelize(&_14, &property_zv, NULL );
	ZEPHIR_INIT_VAR(&_15);
	ZEPHIR_CONCAT_SV(&_15, "get", &_14);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&method, &_15);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if ((zephir_method_exists(this_ptr, &method)  == SUCCESS)) {
		ZEPHIR_RETURN_CALL_METHOD_ZVAL(this_ptr, &method, NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_16);
	ZEPHIR_CONCAT_SVSV(&_16, "Access to undefined property ", &modelName, "::", &property_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_16);
	zephir_check_call_status();
	RETURN_MM_NULL();
}

/**
 * Magic method to check if a property is a valid relation
 */
PHP_METHOD(Phalcon_Mvc_Model, __isset)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval property_zv, manager, method, modelName, relation, result, _0, _1$$4;
	zend_string *property = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&property_zv);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(property)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&property_zv);
	ZVAL_STR_COPY(&property_zv, property);
	ZEPHIR_INIT_VAR(&modelName);
	zephir_get_class(&modelName, this_ptr, 0);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&_0, &manager, "getRelationByAlias", NULL, 0, &modelName, &property_zv);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&relation, &_0);
	if (Z_TYPE_P(&relation) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&result);
		ZVAL_BOOL(&result, 1);
	} else {
		ZEPHIR_INIT_VAR(&_1$$4);
		zephir_camelize(&_1$$4, &property_zv, NULL );
		ZEPHIR_INIT_VAR(&method);
		ZEPHIR_CONCAT_SV(&method, "get", &_1$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(&result);
		ZVAL_BOOL(&result, (zephir_method_exists(this_ptr, &method)  == SUCCESS));
	}
	RETURN_CCTOR(&result);
}

/**
 * Serializes a model
 */
PHP_METHOD(Phalcon_Mvc_Model, __serialize)
{
	zend_bool _3, _4, _5;
	zval attributes, manager, dirtyState, snapshot, _0, _1, _2, _6$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&dirtyState);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("snapshot", 8, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&snapshot);
	ZVAL_NULL(&snapshot);
	ZVAL_NULL(&_0);
	ZVAL_BOOL(&_1, 0);
	ZEPHIR_CALL_METHOD(&attributes, this_ptr, "toArray", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 711, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&dirtyState, &_0);
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_2);
	ZEPHIR_CALL_METHOD(&_2, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
	zephir_check_call_status();
	_3 = zephir_is_true(&_2);
	if (_3) {
		zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
		_3 = Z_TYPE_P(&_0) != IS_NULL;
	}
	_4 = _3;
	if (_4) {
		zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
		_5 = !ZEPHIR_IS_EQUAL(&attributes, &_1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		_4 = _5;
	}
	if (_4) {
		zephir_read_property_cached(&_6$$3, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&snapshot, &_6$$3);
	}
	zephir_create_array(return_value, 3, 0);
	zephir_array_update_string(return_value, SL("attributes"), &attributes, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("snapshot"), &snapshot, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("dirtyState"), &dirtyState, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Magic method to assign values to the the model
 *
 * @param mixed value
 */
PHP_METHOD(Phalcon_Mvc_Model, __set)
{
	zend_bool _0, _4$$4, _13$$10;
	zval related;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval property_zv, *value, value_sub, lowerProperty, modelName, manager, relation, referencedModel, item, dirtyState, _15, _16, _1$$3, _2$$4, _3$$4, _5$$6, _6$$7, _7$$8, _8$$9, *_9$$10, _10$$10, *_11$$10, _12$$10, _14$$17, _17$$20, _18$$21, _19$$21, _20$$21;
	zend_string *property = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&property_zv);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&lowerProperty);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&referencedModel);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&dirtyState);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_14$$17);
	ZVAL_UNDEF(&_17$$20);
	ZVAL_UNDEF(&_18$$21);
	ZVAL_UNDEF(&_19$$21);
	ZVAL_UNDEF(&_20$$21);
	ZVAL_UNDEF(&related);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(property)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	value = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&property_zv);
	ZVAL_STR_COPY(&property_zv, property);
	_0 = Z_TYPE_P(value) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(value, phalcon_mvc_modelinterface_ce);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&lowerProperty);
		zephir_fast_strtolower(&lowerProperty, &property_zv);
		ZEPHIR_INIT_VAR(&modelName);
		zephir_get_class(&modelName, this_ptr, 0);
		ZEPHIR_CALL_METHOD(&manager, this_ptr, "getModelsManager", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_1$$3, &manager, "getRelationByAlias", NULL, 0, &modelName, &lowerProperty);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&relation, &_1$$3);
		if (Z_TYPE_P(&relation) == IS_OBJECT) {
			zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_0, 711, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&dirtyState, &_2$$4);
			ZEPHIR_CALL_METHOD(&_3$$4, value, "getDirtyState", NULL, 0);
			zephir_check_call_status();
			_4$$4 = !ZEPHIR_IS_EQUAL(&_3$$4, &dirtyState);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_4$$4) {
				ZEPHIR_INIT_NVAR(&dirtyState);
				ZVAL_LONG(&dirtyState, 1);
			}
			zephir_unset_property_array(this_ptr, ZEND_STRL("related"), &lowerProperty);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_array(this_ptr, SL("dirtyRelated"), &lowerProperty, value);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 711, &dirtyState);
			RETVAL_ZVAL(value, 1, 0);
			RETURN_MM();
		}
	} else if (Z_TYPE_P(value) == IS_ARRAY) {
		ZEPHIR_INIT_NVAR(&lowerProperty);
		zephir_fast_strtolower(&lowerProperty, &property_zv);
		ZEPHIR_INIT_NVAR(&modelName);
		zephir_get_class(&modelName, this_ptr, 0);
		ZEPHIR_CALL_METHOD(&manager, this_ptr, "getModelsManager", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_5$$6, &manager, "getRelationByAlias", NULL, 0, &modelName, &lowerProperty);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&relation, &_5$$6);
		if (Z_TYPE_P(&relation) == IS_OBJECT) {
			ZEPHIR_CALL_METHOD(&_6$$7, &relation, "getType", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_LONG(&_6$$7, 0)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&_6$$7, 1)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&_6$$7, 2)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&_6$$7, 4)) { goto zephir_switch_0_clause_3; }
			goto zephir_switch_0_end;
			zephir_switch_0_clause_0: ;
			zephir_switch_0_clause_1: ;
				ZEPHIR_CALL_METHOD(&_7$$8, &relation, "getReferencedModel", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&referencedModel, &manager, "load", NULL, 0, &_7$$8);
				zephir_check_call_status();
				if (Z_TYPE_P(&referencedModel) == IS_OBJECT) {
					ZEPHIR_CALL_METHOD(NULL, &referencedModel, "assign", NULL, 0, value);
					zephir_check_call_status();
					zephir_unset_property_array(this_ptr, ZEND_STRL("related"), &lowerProperty);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_update_property_array(this_ptr, SL("dirtyRelated"), &lowerProperty, &referencedModel);
					ZVAL_UNDEF(&_8$$9);
					ZVAL_LONG(&_8$$9, 1);
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 711, &_8$$9);
					RETVAL_ZVAL(value, 1, 0);
					RETURN_MM();
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_VAR(&related);
				array_init(&related);
				if (Z_TYPE_P(value) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_10$$10);
					zephir_string_to_char_array(&_10$$10, value);
					_9$$10 = &_10$$10;
				} else {
					_9$$10 = value;
				}
				zephir_is_iterable(_9$$10, 0, "phalcon/Mvc/Model.zep", 534);
				if (Z_TYPE_P(_9$$10) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9$$10), _11$$10)
					{
						ZEPHIR_INIT_NVAR(&item);
						ZVAL_COPY(&item, _11$$10);
						if (Z_TYPE_P(&item) == IS_OBJECT) {
							if (zephir_instance_of_ev(&item, phalcon_mvc_modelinterface_ce)) {
								zephir_array_append(&related, &item, PH_SEPARATE, "phalcon/Mvc/Model.zep", 529);
							}
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _9$$10, "rewind", NULL, 0);
					zephir_check_call_status();
					_13$$10 = 1;
					while (1) {
						if (_13$$10) {
							_13$$10 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _9$$10, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_12$$10, _9$$10, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_12$$10)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&item, _9$$10, "current", NULL, 0);
						zephir_check_call_status();
							if (Z_TYPE_P(&item) == IS_OBJECT) {
								if (zephir_instance_of_ev(&item, phalcon_mvc_modelinterface_ce)) {
									zephir_array_append(&related, &item, PH_SEPARATE, "phalcon/Mvc/Model.zep", 529);
								}
							}
					}
				}
				ZEPHIR_INIT_NVAR(&item);
				zephir_unset_property_array(this_ptr, ZEND_STRL("related"), &lowerProperty);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (zephir_fast_count_int(&related) > 0) {
					zephir_update_property_array(this_ptr, SL("dirtyRelated"), &lowerProperty, &related);
					ZVAL_UNDEF(&_14$$17);
					ZVAL_LONG(&_14$$17, 1);
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 711, &_14$$17);
				} else {
					zephir_unset_property_array(this_ptr, ZEND_STRL("dirtyRelated"), &lowerProperty);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				RETVAL_ZVAL(value, 1, 0);
				RETURN_MM();
			zephir_switch_0_end: ;

		}
	}
	ZEPHIR_CALL_METHOD(&_15, this_ptr, "possibleSetter", NULL, 460, &property_zv, value);
	zephir_check_call_status();
	if (zephir_is_true(&_15)) {
		RETVAL_ZVAL(value, 1, 0);
		RETURN_MM();
	}
	ZEPHIR_CALL_FUNCTION(&_16, "property_exists", NULL, 324, this_ptr, &property_zv);
	zephir_check_call_status();
	if (zephir_is_true(&_16)) {
		ZEPHIR_CALL_METHOD(&manager, this_ptr, "getModelsManager", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_17$$20, &manager, "isVisibleModelProperty", NULL, 0, this_ptr, &property_zv);
		zephir_check_call_status();
		if (UNEXPECTED(!zephir_is_true(&_17$$20))) {
			ZEPHIR_INIT_VAR(&_18$$21);
			object_init_ex(&_18$$21, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_19$$21);
			zephir_get_class(&_19$$21, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_20$$21);
			ZEPHIR_CONCAT_SVSVS(&_20$$21, "Cannot access property '", &property_zv, "' (not public) in '", &_19$$21, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_18$$21, "__construct", NULL, 32, &_20$$21);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_18$$21, "phalcon/Mvc/Model.zep", 563);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_update_property_zval_zval(this_ptr, &property_zv, value);
	RETVAL_ZVAL(value, 1, 0);
	RETURN_MM();
}

/**
 * Unserializes an array to the model
 */
PHP_METHOD(Phalcon_Mvc_Model, __unserialize)
{
	zend_bool _15$$7;
	zend_string *_13$$7;
	zend_ulong _12$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, container, manager, key, value, snapshot, properties, dirtyState, _4, _5, _0$$3, _1$$4, _2$$4, _3$$4, _6$$5, _7$$5, _8$$5, *_9$$7, _10$$7, *_11$$7, _14$$7, _16$$13;
	zval data;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&properties);
	ZVAL_UNDEF(&dirtyState);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_16$$13);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("snapshot", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data_param);
	zephir_get_arrval(&data, data_param);
	if (!(zephir_array_isset_value_string(&data, SL("attributes")))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		zephir_array_update_string(&_0$$3, SL("attributes"), &data, PH_COPY | PH_SEPARATE);
		ZEPHIR_CPY_WRT(&data, &_0$$3);
	}
	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$4);
		object_init_ex(&_1$$4, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$4);
		zephir_get_class(&_2$$4, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_3$$4);
		ZEPHIR_CONCAT_SVS(&_3$$4, "A dependency injection container is required to access the services related to the ODM in '", &_2$$4, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", NULL, 32, &_3$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$4, "phalcon/Mvc/Model.zep", 592);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 707, &container);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "modelsManager");
	ZEPHIR_CALL_METHOD(&_4, &container, "getShared", NULL, 0, &_5);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_4);
	if (Z_TYPE_P(&manager) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_6$$5);
		object_init_ex(&_6$$5, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_7$$5);
		zephir_get_class(&_7$$5, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_8$$5);
		ZEPHIR_CONCAT_SVS(&_8$$5, "The injected service 'modelsManager' is not valid in '", &_7$$5, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_6$$5, "__construct", NULL, 32, &_8$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$5, "phalcon/Mvc/Model.zep", 607);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 708, &manager);
	ZEPHIR_CALL_METHOD(NULL, &manager, "initialize", NULL, 0, this_ptr);
	zephir_check_call_status();
	if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("onconstruct")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "onConstruct", NULL, 0);
		zephir_check_call_status();
	}
	zephir_memory_observe(&properties);
	if (zephir_array_isset_string_fetch(&properties, &data, SL("attributes"), 0)) {
		if (Z_TYPE_P(&properties) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_10$$7);
			zephir_string_to_char_array(&_10$$7, &properties);
			_9$$7 = &_10$$7;
		} else {
			_9$$7 = &properties;
		}
		zephir_is_iterable(_9$$7, 0, "phalcon/Mvc/Model.zep", 638);
		if (Z_TYPE_P(_9$$7) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9$$7), _12$$7, _13$$7, _11$$7)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_13$$7 != NULL) { 
					ZVAL_STR_COPY(&key, _13$$7);
				} else {
					ZVAL_LONG(&key, _12$$7);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _11$$7);
				zephir_update_property_zval_zval(this_ptr, &key, &value);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _9$$7, "rewind", NULL, 0);
			zephir_check_call_status();
			_15$$7 = 1;
			while (1) {
				if (_15$$7) {
					_15$$7 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _9$$7, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_14$$7, _9$$7, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_14$$7)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, _9$$7, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&value, _9$$7, "current", NULL, 0);
				zephir_check_call_status();
					zephir_update_property_zval_zval(this_ptr, &key, &value);
			}
		}
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
	} else {
		ZEPHIR_INIT_NVAR(&properties);
		array_init(&properties);
	}
	zephir_memory_observe(&dirtyState);
	if (zephir_array_isset_string_fetch(&dirtyState, &data, SL("dirtyState"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 711, &dirtyState);
	}
	ZEPHIR_CALL_METHOD(&_4, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (zephir_is_true(&_4)) {
		zephir_memory_observe(&snapshot);
		if (zephir_array_isset_string_fetch(&snapshot, &data, SL("snapshot"), 0)) {
			ZEPHIR_INIT_VAR(&_16$$13);
			if (Z_TYPE_P(&snapshot) != IS_NULL) {
				ZEPHIR_CPY_WRT(&_16$$13, &snapshot);
			} else {
				ZEPHIR_CPY_WRT(&_16$$13, &properties);
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 712, &_16$$13);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 712, &properties);
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Setups a behavior in a model
 *
 *```php
 * use Phalcon\Mvc\Model;
 * use Phalcon\Mvc\Model\Behavior\Timestampable;
 *
 * class Robots extends Model
 * {
 *     public function initialize()
 *     {
 *         $this->addBehavior(
 *             new Timestampable(
 *                 [
 *                     "beforeCreate" => [
 *                         "field"  => "created_at",
 *                         "format" => "Y-m-d",
 *                     ],
 *                 ]
 *             )
 *         );
 *
 *         $this->addBehavior(
 *             new Timestampable(
 *                 [
 *                     "beforeUpdate" => [
 *                         "field"  => "updated_at",
 *                         "format" => "Y-m-d",
 *                     ],
 *                 ]
 *             )
 *         );
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, addBehavior)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *behavior, behavior_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&behavior_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(behavior, phalcon_mvc_model_behaviorinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &behavior);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "addBehavior", NULL, 0, this_ptr, behavior);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Appends a customized message on the validation process
 *
 * ```php
 * use Phalcon\Mvc\Model;
 * use Phalcon\Messages\Message as Message;
 *
 * class Robots extends Model
 * {
 *     public function beforeSave()
 *     {
 *         if ($this->name === "Peter") {
 *             $message = new Message(
 *                 "Sorry, but a robot cannot be named Peter"
 *             );
 *
 *             $this->appendMessage($message);
 *         }
 *     }
 * }
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, appendMessage)
{
	zval *message, message_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&message_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(message, phalcon_messages_messageinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &message);
	zephir_update_property_array_append(this_ptr, SL("errorMessages"), message);
	RETURN_THISW();
}

/**
 * Assigns values to a model from an array
 *
 * ```php
 * $robot->assign(
 *     [
 *         "type" => "mechanical",
 *         "name" => "Astro Boy",
 *         "year" => 1952,
 *     ]
 * );
 *
 * // Assign by db row, column map needed
 * $robot->assign(
 *     $dbRow,
 *     [
 *         "db_type" => "type",
 *         "db_name" => "name",
 *         "db_year" => "year",
 *     ]
 * );
 *
 * // Allow assign only name and year
 * $robot->assign(
 *     $_POST,
 *     [
 *         "name",
 *         "year",
 *     ]
 * );
 *
 * // By default assign method will use setters if exist, you can disable it by using ini_set to directly use properties
 *
 * ini_set("phalcon.orm.disable_assign_setters", true);
 *
 * $robot->assign(
 *     $_POST,
 *     [
 *         "name",
 *         "year",
 *     ]
 * );
 * ```
 *
 * @param array data
 * @param mixed whiteList
 * @param mixed dataColumnMap Array to transform keys of data to another
 *
 * @return ModelInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, assign)
{
	zend_string *_3$$3;
	zend_ulong _2$$3;
	zend_bool _26, _5$$3, _10$$12, _22$$18, _27$$22, _36$$28;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_12 = NULL, *_15 = NULL, *_21 = NULL, *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *whiteList = NULL, whiteList_sub, *dataColumnMap = NULL, dataColumnMap_sub, __$null, key, keyMapped, value, attribute, attributeField, metaData, columnMap, disableAssignSetters, _0, _6, _7, *_8, *_9, _25, *_1$$3, _4$$3, _11$$12, _13$$12, _14$$13, _16$$15, _17$$15, _18$$16, _19$$16, _20$$16, _23$$18, _28$$22, _29$$22, _30$$23, _31$$25, _32$$25, _33$$26, _34$$26, _35$$26, _37$$28;
	zval data, dataMapped;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&dataMapped);
	ZVAL_UNDEF(&whiteList_sub);
	ZVAL_UNDEF(&dataColumnMap_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&keyMapped);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&disableAssignSetters);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$12);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_14$$13);
	ZVAL_UNDEF(&_16$$15);
	ZVAL_UNDEF(&_17$$15);
	ZVAL_UNDEF(&_18$$16);
	ZVAL_UNDEF(&_19$$16);
	ZVAL_UNDEF(&_20$$16);
	ZVAL_UNDEF(&_23$$18);
	ZVAL_UNDEF(&_28$$22);
	ZVAL_UNDEF(&_29$$22);
	ZVAL_UNDEF(&_30$$23);
	ZVAL_UNDEF(&_31$$25);
	ZVAL_UNDEF(&_32$$25);
	ZVAL_UNDEF(&_33$$26);
	ZVAL_UNDEF(&_34$$26);
	ZVAL_UNDEF(&_35$$26);
	ZVAL_UNDEF(&_37$$28);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(whiteList)
		Z_PARAM_ZVAL_OR_NULL(dataColumnMap)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &data_param, &whiteList, &dataColumnMap);
	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);
	if (!whiteList) {
		whiteList = &whiteList_sub;
		whiteList = &__$null;
	}
	if (!dataColumnMap) {
		dataColumnMap = &dataColumnMap_sub;
		dataColumnMap = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "orm.disable_assign_setters");
	ZEPHIR_CALL_CE_STATIC(&disableAssignSetters, phalcon_support_settings_ce, "get", NULL, 0, &_0);
	zephir_check_call_status();
	if (Z_TYPE_P(dataColumnMap) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&dataMapped);
		array_init(&dataMapped);
		zephir_is_iterable(&data, 0, "phalcon/Mvc/Model.zep", 800);
		if (Z_TYPE_P(&data) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _2$$3, _3$$3, _1$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_3$$3 != NULL) { 
					ZVAL_STR_COPY(&key, _3$$3);
				} else {
					ZVAL_LONG(&key, _2$$3);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _1$$3);
				ZEPHIR_OBS_NVAR(&keyMapped);
				if (zephir_array_isset_fetch(&keyMapped, dataColumnMap, &key, 0)) {
					zephir_array_update_zval(&dataMapped, &keyMapped, &value, PH_COPY | PH_SEPARATE);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
			zephir_check_call_status();
			_5$$3 = 1;
			while (1) {
				if (_5$$3) {
					_5$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_4$$3, &data, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_4$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, &data, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&keyMapped);
					if (zephir_array_isset_fetch(&keyMapped, dataColumnMap, &key, 0)) {
						zephir_array_update_zval(&dataMapped, &keyMapped, &value, PH_COPY | PH_SEPARATE);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
	} else {
		if (UNEXPECTED(Z_TYPE_P(&data) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&data, "dataMapped", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&dataMapped, &data);
	}
	if (zephir_fast_count_int(&dataMapped) == 0) {
		RETURN_THIS();
	}
	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "orm.column_renaming");
	ZEPHIR_CALL_CE_STATIC(&_6, phalcon_support_settings_ce, "get", NULL, 0, &_0);
	zephir_check_call_status();
	if (zephir_is_true(&_6)) {
		ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, this_ptr);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&columnMap);
		ZVAL_NULL(&columnMap);
	}
	ZEPHIR_CALL_METHOD(&_7, &metaData, "getAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (Z_TYPE_P(&_7) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_0);
		zephir_string_to_char_array(&_0, &_7);
		_8 = &_0;
	} else {
		_8 = &_7;
	}
	zephir_is_iterable(_8, 0, "phalcon/Mvc/Model.zep", 857);
	if (Z_TYPE_P(_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_8), _9)
		{
			ZEPHIR_INIT_NVAR(&attribute);
			ZVAL_COPY(&attribute, _9);
			_10$$12 = !(zephir_array_isset_value(&columnMap, &attribute));
			if (_10$$12) {
				ZEPHIR_INIT_NVAR(&_13$$12);
				ZVAL_STRING(&_13$$12, "orm.case_insensitive_column_map");
				ZEPHIR_CALL_CE_STATIC(&_11$$12, phalcon_support_settings_ce, "get", &_12, 0, &_13$$12);
				zephir_check_call_status();
				_10$$12 = zephir_is_true(&_11$$12);
			}
			if (_10$$12) {
				ZEPHIR_CALL_SELF(&_14$$13, "caseInsensitiveColumnMap", &_15, 461, &columnMap, &attribute);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&attribute, &_14$$13);
			}
			if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
				ZEPHIR_OBS_NVAR(&attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, &columnMap, &attribute, 0))) {
					ZEPHIR_INIT_NVAR(&_17$$15);
					ZVAL_STRING(&_17$$15, "orm.ignore_unknown_columns");
					ZEPHIR_CALL_CE_STATIC(&_16$$15, phalcon_support_settings_ce, "get", &_12, 0, &_17$$15);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_16$$15))) {
						ZEPHIR_INIT_NVAR(&_18$$16);
						object_init_ex(&_18$$16, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_19$$16);
						zephir_get_class(&_19$$16, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_20$$16);
						ZEPHIR_CONCAT_SVSVS(&_20$$16, "Column '", &attribute, "' does not make part of the column map in '", &_19$$16, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_18$$16, "__construct", &_21, 32, &_20$$16);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_18$$16, "phalcon/Mvc/Model.zep", 831);
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
			} else {
				ZEPHIR_CPY_WRT(&attributeField, &attribute);
			}
			ZEPHIR_OBS_NVAR(&value);
			if (zephir_array_isset_fetch(&value, &dataMapped, &attributeField, 0)) {
				if (Z_TYPE_P(whiteList) == IS_ARRAY) {
					if (!(zephir_fast_in_array(&attributeField, whiteList))) {
						continue;
					}
				}
				_22$$18 = zephir_is_true(&disableAssignSetters);
				if (!(_22$$18)) {
					ZEPHIR_CALL_METHOD(&_23$$18, this_ptr, "possibleSetter", &_24, 460, &attributeField, &value);
					zephir_check_call_status();
					_22$$18 = !zephir_is_true(&_23$$18);
				}
				if (_22$$18) {
					zephir_update_property_zval_zval(this_ptr, &attributeField, &value);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _8, "rewind", NULL, 0);
		zephir_check_call_status();
		_26 = 1;
		while (1) {
			if (_26) {
				_26 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _8, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_25, _8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_25)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&attribute, _8, "current", NULL, 0);
			zephir_check_call_status();
				_27$$22 = !(zephir_array_isset_value(&columnMap, &attribute));
				if (_27$$22) {
					ZEPHIR_INIT_NVAR(&_29$$22);
					ZVAL_STRING(&_29$$22, "orm.case_insensitive_column_map");
					ZEPHIR_CALL_CE_STATIC(&_28$$22, phalcon_support_settings_ce, "get", &_12, 0, &_29$$22);
					zephir_check_call_status();
					_27$$22 = zephir_is_true(&_28$$22);
				}
				if (_27$$22) {
					ZEPHIR_CALL_SELF(&_30$$23, "caseInsensitiveColumnMap", &_15, 461, &columnMap, &attribute);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&attribute, &_30$$23);
				}
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (!(zephir_array_isset_fetch(&attributeField, &columnMap, &attribute, 0))) {
						ZEPHIR_INIT_NVAR(&_32$$25);
						ZVAL_STRING(&_32$$25, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_31$$25, phalcon_support_settings_ce, "get", &_12, 0, &_32$$25);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_31$$25))) {
							ZEPHIR_INIT_NVAR(&_33$$26);
							object_init_ex(&_33$$26, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_34$$26);
							zephir_get_class(&_34$$26, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_35$$26);
							ZEPHIR_CONCAT_SVSVS(&_35$$26, "Column '", &attribute, "' does not make part of the column map in '", &_34$$26, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_33$$26, "__construct", &_21, 32, &_35$$26);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_33$$26, "phalcon/Mvc/Model.zep", 831);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &attribute);
				}
				ZEPHIR_OBS_NVAR(&value);
				if (zephir_array_isset_fetch(&value, &dataMapped, &attributeField, 0)) {
					if (Z_TYPE_P(whiteList) == IS_ARRAY) {
						if (!(zephir_fast_in_array(&attributeField, whiteList))) {
							continue;
						}
					}
					_36$$28 = zephir_is_true(&disableAssignSetters);
					if (!(_36$$28)) {
						ZEPHIR_CALL_METHOD(&_37$$28, this_ptr, "possibleSetter", &_24, 460, &attributeField, &value);
						zephir_check_call_status();
						_36$$28 = !zephir_is_true(&_37$$28);
					}
					if (_36$$28) {
						zephir_update_property_zval_zval(this_ptr, &attributeField, &value);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&attribute);
	RETURN_THIS();
}

/**
 * Returns the average value on a column for a result-set of rows matching
 * the specified conditions.
 *
 * Returned value will be a float for simple queries or a ResultsetInterface
 * instance for when the GROUP condition is used. The results will
 * contain the average of each group.
 *
 * ```php
 * // What's the average price of robots?
 * $average = Robots::average(
 *     [
 *         "column" => "price",
 *     ]
 * );
 *
 * echo "The average price is ", $average, "\n";
 *
 * // What's the average price of mechanical robots?
 * $average = Robots::average(
 *     [
 *         "type = 'mechanical'",
 *         "column" => "price",
 *     ]
 * );
 *
 * echo "The average price of mechanical robots is ", $average, "\n";
 * ```
 *
 * @param array parameters
 * @return float | ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, average)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters_param = NULL, result, _0, _1;
	zval parameters;

	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(parameters, parameters_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters_param);
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "AVG");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "average");
	ZEPHIR_CALL_SELF(&result, "groupResult", NULL, 0, &_0, &_1, &parameters);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) == IS_STRING) {
		RETURN_MM_DOUBLE(zephir_get_doubleval(&result));
	}
	RETURN_CCTOR(&result);
}

/**
 * Assigns values to a model from an array returning a new model
 *
 *```php
 * $robot = Phalcon\Mvc\Model::cloneResult(
 *     new Robots(),
 *     [
 *         "type" => "mechanical",
 *         "name" => "Astro Boy",
 *         "year" => 1952,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, cloneResult)
{
	zend_bool _9;
	zend_string *_3;
	zend_ulong _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long dirtyState, ZEPHIR_LAST_CALL_STATUS;
	zval data;
	zval *base, base_sub, *data_param = NULL, *dirtyState_param = NULL, instance, key, value, _0, *_1, _8, _13, _4$$4, _5$$4, _6$$4, _10$$6, _11$$6, _12$$6;

	ZVAL_UNDEF(&base_sub);
	ZVAL_UNDEF(&instance);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_OBJECT_OF_CLASS(base, phalcon_mvc_modelinterface_ce)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(dirtyState)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &base, &data_param, &dirtyState_param);
	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);
	if (!dirtyState_param) {
		dirtyState = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&instance);
	if (zephir_clone(&instance, base) == FAILURE) {
		RETURN_MM();
	}
	ZVAL_LONG(&_0, dirtyState);
	ZEPHIR_CALL_METHOD(NULL, &instance, "setDirtyState", NULL, 0, &_0);
	zephir_check_call_status();
	zephir_is_iterable(&data, 0, "phalcon/Mvc/Model.zep", 947);
	if (Z_TYPE_P(&data) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _2, _3, _1)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_3 != NULL) { 
				ZVAL_STR_COPY(&key, _3);
			} else {
				ZVAL_LONG(&key, _2);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			if (UNEXPECTED(Z_TYPE_P(&key) != IS_STRING)) {
				ZEPHIR_INIT_NVAR(&_4$$4);
				object_init_ex(&_4$$4, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_NVAR(&_5$$4);
				zephir_get_class(&_5$$4, base, 0);
				ZEPHIR_INIT_NVAR(&_6$$4);
				ZEPHIR_CONCAT_SVS(&_6$$4, "Invalid key in array data provided to dumpResult() in '", &_5$$4, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", &_7, 32, &_6$$4);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_4$$4, "phalcon/Mvc/Model.zep", 937);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_zval(&instance, &key, &value);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
		zephir_check_call_status();
		_9 = 1;
		while (1) {
			if (_9) {
				_9 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_8, &data, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &data, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&key) != IS_STRING)) {
					ZEPHIR_INIT_NVAR(&_10$$6);
					object_init_ex(&_10$$6, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_11$$6);
					zephir_get_class(&_11$$6, base, 0);
					ZEPHIR_INIT_NVAR(&_12$$6);
					ZEPHIR_CONCAT_SVS(&_12$$6, "Invalid key in array data provided to dumpResult() in '", &_11$$6, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_10$$6, "__construct", &_7, 32, &_12$$6);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_10$$6, "phalcon/Mvc/Model.zep", 937);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_update_property_zval_zval(&instance, &key, &value);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_INIT_VAR(&_13);
	ZVAL_STRING(&_13, "afterFetch");
	ZEPHIR_CALL_METHOD(NULL, &instance, "fireEvent", NULL, 0, &_13);
	zephir_check_call_status();
	RETURN_CCTOR(&instance);
}

/**
 * Assigns values to a model from an array, returning a new model.
 *
 *```php
 * $robot = \Phalcon\Mvc\Model::cloneResultMap(
 *     new Robots(),
 *     [
 *         "type" => "mechanical",
 *         "name" => "Astro Boy",
 *         "year" => 1952,
 *     ]
 * );
 *```
 *
 * @param ModelInterface|\Phalcon\Mvc\Model\Row base
 * @param mixed columnMap
 * @param int dirtyState
 * @param bool keepSnapshots
 *
 * @return ModelInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, cloneResultMap)
{
	zend_string *_5;
	zend_ulong _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL, *_16 = NULL, *_27 = NULL;
	zend_bool keepSnapshots, disableSetters = 0, _32, _6$$5, _24$$5, _8$$9, _9$$11, _23$$19, _30$$29, _33$$31, _49$$31, _35$$35, _36$$37, _48$$45, _54$$55;
	zend_long dirtyState, ZEPHIR_LAST_CALL_STATUS;
	zval data, localMethods;
	zval *base, base_sub, *data_param = NULL, *columnMap, columnMap_sub, *dirtyState_param = NULL, *keepSnapshots_param = NULL, instance, attribute, key, value, castValue, attributeName, metaData, reverseMap, notNullAttributes, setter, _0, _1, _2, *_3, _31, _7$$9, _10$$14, _12$$14, _13$$15, _14$$15, _15$$15, _17$$16, _18$$16, _19$$17, _20$$17, _21$$17, _22$$19, _25$$21, _26$$22, _28$$26, _29$$29, _34$$35, _37$$40, _38$$40, _39$$41, _40$$41, _41$$41, _42$$42, _43$$42, _44$$43, _45$$43, _46$$43, _47$$45, _50$$47, _51$$48, _52$$52, _53$$55, _55$$58;

	ZVAL_UNDEF(&base_sub);
	ZVAL_UNDEF(&columnMap_sub);
	ZVAL_UNDEF(&instance);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&castValue);
	ZVAL_UNDEF(&attributeName);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&reverseMap);
	ZVAL_UNDEF(&notNullAttributes);
	ZVAL_UNDEF(&setter);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_10$$14);
	ZVAL_UNDEF(&_12$$14);
	ZVAL_UNDEF(&_13$$15);
	ZVAL_UNDEF(&_14$$15);
	ZVAL_UNDEF(&_15$$15);
	ZVAL_UNDEF(&_17$$16);
	ZVAL_UNDEF(&_18$$16);
	ZVAL_UNDEF(&_19$$17);
	ZVAL_UNDEF(&_20$$17);
	ZVAL_UNDEF(&_21$$17);
	ZVAL_UNDEF(&_22$$19);
	ZVAL_UNDEF(&_25$$21);
	ZVAL_UNDEF(&_26$$22);
	ZVAL_UNDEF(&_28$$26);
	ZVAL_UNDEF(&_29$$29);
	ZVAL_UNDEF(&_34$$35);
	ZVAL_UNDEF(&_37$$40);
	ZVAL_UNDEF(&_38$$40);
	ZVAL_UNDEF(&_39$$41);
	ZVAL_UNDEF(&_40$$41);
	ZVAL_UNDEF(&_41$$41);
	ZVAL_UNDEF(&_42$$42);
	ZVAL_UNDEF(&_43$$42);
	ZVAL_UNDEF(&_44$$43);
	ZVAL_UNDEF(&_45$$43);
	ZVAL_UNDEF(&_46$$43);
	ZVAL_UNDEF(&_47$$45);
	ZVAL_UNDEF(&_50$$47);
	ZVAL_UNDEF(&_51$$48);
	ZVAL_UNDEF(&_52$$52);
	ZVAL_UNDEF(&_53$$55);
	ZVAL_UNDEF(&_55$$58);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&localMethods);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_ZVAL(base)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
		Z_PARAM_ZVAL(columnMap)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(dirtyState)
		Z_PARAM_BOOL_OR_NULL(keepSnapshots, is_null_true)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 2, &base, &data_param, &columnMap, &dirtyState_param, &keepSnapshots_param);
	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);
	if (!dirtyState_param) {
		dirtyState = 0;
	} else {
		}
	if (!keepSnapshots_param) {
		keepSnapshots = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&instance);
	if (zephir_clone(&instance, base) == FAILURE) {
		RETURN_MM();
	}
	if (zephir_instance_of_ev(&instance, phalcon_mvc_model_ce)) {
		ZEPHIR_CALL_METHOD(&metaData, &instance, "getModelsMetaData", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&notNullAttributes, &metaData, "getNotNullAttributes", NULL, 0, &instance);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&metaData);
		ZVAL_NULL(&metaData);
		ZEPHIR_INIT_NVAR(&notNullAttributes);
		array_init(&notNullAttributes);
	}
	ZVAL_LONG(&_0, dirtyState);
	ZEPHIR_CALL_METHOD(NULL, &instance, "setDirtyState", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "orm.disable_assign_setters");
	ZEPHIR_CALL_CE_STATIC(&_1, phalcon_support_settings_ce, "get", NULL, 0, &_2);
	zephir_check_call_status();
	disableSetters = zephir_get_boolval(&_1);
	ZEPHIR_INIT_VAR(&localMethods);
	zephir_create_array(&localMethods, 10, 0);
	add_assoc_long_ex(&localMethods, SL("setConnectionService"), 1);
	add_assoc_long_ex(&localMethods, SL("setDirtyState"), 1);
	add_assoc_long_ex(&localMethods, SL("setEventsManager"), 1);
	add_assoc_long_ex(&localMethods, SL("setReadConnectionService"), 1);
	add_assoc_long_ex(&localMethods, SL("setOldSnapshotData"), 1);
	add_assoc_long_ex(&localMethods, SL("setSchema"), 1);
	add_assoc_long_ex(&localMethods, SL("setSnapshotData"), 1);
	add_assoc_long_ex(&localMethods, SL("setSource"), 1);
	add_assoc_long_ex(&localMethods, SL("setTransaction"), 1);
	add_assoc_long_ex(&localMethods, SL("setWriteConnectionService"), 1);
	zephir_is_iterable(&data, 1, "phalcon/Mvc/Model.zep", 1135);
	if (Z_TYPE_P(&data) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&key, _5);
			} else {
				ZVAL_LONG(&key, _4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			if (Z_TYPE_P(&key) != IS_STRING) {
				continue;
			}
			_6$$5 = Z_TYPE_P(&value) == IS_NULL;
			if (_6$$5) {
				_6$$5 = zephir_fast_in_array(&key, &notNullAttributes);
			}
			if (_6$$5) {
				continue;
			}
			if (Z_TYPE_P(columnMap) != IS_ARRAY) {
				if (!(disableSetters)) {
					ZEPHIR_INIT_NVAR(&_7$$9);
					zephir_camelize(&_7$$9, &key, NULL );
					ZEPHIR_INIT_NVAR(&setter);
					ZEPHIR_CONCAT_SV(&setter, "set", &_7$$9);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					_8$$9 = (zephir_method_exists(&instance, &setter)  == SUCCESS);
					if (_8$$9) {
						_8$$9 = !(zephir_array_isset_value(&localMethods, &setter));
					}
					if (_8$$9) {
						ZEPHIR_CALL_METHOD_ZVAL(NULL, &instance, &setter, NULL, 0, &value);
						zephir_check_call_status();
						continue;
					}
				}
				zephir_update_property_zval_zval(&instance, &key, &value);
				continue;
			}
			ZEPHIR_OBS_NVAR(&attribute);
			if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
				_9$$11 = Z_TYPE_P(columnMap) == IS_ARRAY;
				if (_9$$11) {
					_9$$11 = !(ZEPHIR_IS_EMPTY(columnMap));
				}
				if (_9$$11) {
					if (Z_TYPE_P(&metaData) == IS_NULL) {
						ZEPHIR_CALL_METHOD(&metaData, &instance, "getModelsMetaData", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&reverseMap, &metaData, "getReverseColumnMap", NULL, 0, &instance);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&attribute);
					if (!(zephir_array_isset_fetch(&attribute, &reverseMap, &key, 0))) {
						ZEPHIR_INIT_NVAR(&_12$$14);
						ZVAL_STRING(&_12$$14, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_10$$14, phalcon_support_settings_ce, "get", &_11, 0, &_12$$14);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_10$$14))) {
							ZEPHIR_INIT_NVAR(&_13$$15);
							object_init_ex(&_13$$15, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_14$$15);
							zephir_get_class(&_14$$15, base, 0);
							ZEPHIR_INIT_NVAR(&_15$$15);
							ZEPHIR_CONCAT_SVSVS(&_15$$15, "Column '", &key, "' does not make part of the column map in '", &_14$$15, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_13$$15, "__construct", &_16, 32, &_15$$15);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_13$$15, "phalcon/Mvc/Model.zep", 1045);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				} else {
					ZEPHIR_INIT_NVAR(&_18$$16);
					ZVAL_STRING(&_18$$16, "orm.ignore_unknown_columns");
					ZEPHIR_CALL_CE_STATIC(&_17$$16, phalcon_support_settings_ce, "get", &_11, 0, &_18$$16);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_17$$16))) {
						ZEPHIR_INIT_NVAR(&_19$$17);
						object_init_ex(&_19$$17, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_20$$17);
						zephir_get_class(&_20$$17, base, 0);
						ZEPHIR_INIT_NVAR(&_21$$17);
						ZEPHIR_CONCAT_SVSVS(&_21$$17, "Column '", &key, "' does not make part of the column map in '", &_20$$17, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_19$$17, "__construct", &_16, 32, &_21$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_19$$17, "phalcon/Mvc/Model.zep", 1054);
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
			}
			if (Z_TYPE_P(&attribute) != IS_ARRAY) {
				if (!(disableSetters)) {
					ZEPHIR_INIT_NVAR(&_22$$19);
					zephir_camelize(&_22$$19, &attribute, NULL );
					ZEPHIR_INIT_NVAR(&setter);
					ZEPHIR_CONCAT_SV(&setter, "set", &_22$$19);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					_23$$19 = (zephir_method_exists(&instance, &setter)  == SUCCESS);
					if (_23$$19) {
						_23$$19 = !(zephir_array_isset_value(&localMethods, &setter));
					}
					if (_23$$19) {
						ZEPHIR_CALL_METHOD_ZVAL(NULL, &instance, &setter, NULL, 0, &value);
						zephir_check_call_status();
						continue;
					}
				}
				zephir_update_property_zval_zval(&instance, &attribute, &value);
				continue;
			}
			_24$$5 = !ZEPHIR_IS_STRING(&value, "");
			if (_24$$5) {
				_24$$5 = Z_TYPE_P(&value) != IS_NULL;
			}
			if (_24$$5) {
				ZEPHIR_OBS_NVAR(&_25$$21);
				zephir_array_fetch_long(&_25$$21, &attribute, 1, PH_NOISY, "phalcon/Mvc/Model.zep", 1076);
				if (ZEPHIR_IS_LONG(&_25$$21, 0)) { goto zephir_switch_0_clause_0; }
				if (ZEPHIR_IS_LONG(&_25$$21, 21)) { goto zephir_switch_0_clause_1; }
				if (ZEPHIR_IS_LONG(&_25$$21, 22)) { goto zephir_switch_0_clause_2; }
				if (ZEPHIR_IS_LONG(&_25$$21, 26)) { goto zephir_switch_0_clause_3; }
				if (ZEPHIR_IS_LONG(&_25$$21, 3)) { goto zephir_switch_0_clause_4; }
				if (ZEPHIR_IS_LONG(&_25$$21, 9)) { goto zephir_switch_0_clause_5; }
				if (ZEPHIR_IS_LONG(&_25$$21, 7)) { goto zephir_switch_0_clause_6; }
				if (ZEPHIR_IS_LONG(&_25$$21, 8)) { goto zephir_switch_0_clause_7; }
				goto zephir_switch_0_clause_8;
				zephir_switch_0_clause_0: ;
				zephir_switch_0_clause_1: ;
				zephir_switch_0_clause_2: ;
				zephir_switch_0_clause_3: ;
					ZVAL_LONG(&_26$$22, 10);
					ZEPHIR_CALL_FUNCTION(&castValue, "intval", &_27, 41, &value, &_26$$22);
					zephir_check_call_status();
					goto zephir_switch_0_end;
				zephir_switch_0_clause_4: ;
				zephir_switch_0_clause_5: ;
				zephir_switch_0_clause_6: ;
					ZEPHIR_INIT_NVAR(&castValue);
					ZVAL_DOUBLE(&castValue, zephir_get_doubleval(&value));
					goto zephir_switch_0_end;
				zephir_switch_0_clause_7: ;
					ZEPHIR_INIT_NVAR(&castValue);
					ZVAL_BOOL(&castValue, zephir_get_boolval(&value));
					goto zephir_switch_0_end;
				zephir_switch_0_clause_8: ;
					ZEPHIR_CPY_WRT(&castValue, &value);
					goto zephir_switch_0_end;
				zephir_switch_0_end: ;

			} else {
				ZEPHIR_OBS_NVAR(&_28$$26);
				zephir_array_fetch_long(&_28$$26, &attribute, 1, PH_NOISY, "phalcon/Mvc/Model.zep", 1099);
				if (ZEPHIR_IS_LONG(&_28$$26, 14)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&_28$$26, 8)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&_28$$26, 3)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&_28$$26, 9)) { goto zephir_switch_1_clause_3; }
				if (ZEPHIR_IS_LONG(&_28$$26, 7)) { goto zephir_switch_1_clause_4; }
				if (ZEPHIR_IS_LONG(&_28$$26, 0)) { goto zephir_switch_1_clause_5; }
				if (ZEPHIR_IS_LONG(&_28$$26, 21)) { goto zephir_switch_1_clause_6; }
				if (ZEPHIR_IS_LONG(&_28$$26, 22)) { goto zephir_switch_1_clause_7; }
				if (ZEPHIR_IS_LONG(&_28$$26, 26)) { goto zephir_switch_1_clause_8; }
				goto zephir_switch_1_clause_9;
				zephir_switch_1_clause_0: ;
				zephir_switch_1_clause_1: ;
				zephir_switch_1_clause_2: ;
				zephir_switch_1_clause_3: ;
				zephir_switch_1_clause_4: ;
				zephir_switch_1_clause_5: ;
				zephir_switch_1_clause_6: ;
				zephir_switch_1_clause_7: ;
				zephir_switch_1_clause_8: ;
					ZEPHIR_INIT_NVAR(&castValue);
					ZVAL_NULL(&castValue);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_9: ;
					ZEPHIR_CPY_WRT(&castValue, &value);
					goto zephir_switch_1_end;
				zephir_switch_1_end: ;

			}
			ZEPHIR_OBS_NVAR(&attributeName);
			zephir_array_fetch_long(&attributeName, &attribute, 0, PH_NOISY, "phalcon/Mvc/Model.zep", 1118);
			zephir_array_update_zval(&data, &key, &castValue, PH_COPY | PH_SEPARATE);
			if (!(disableSetters)) {
				ZEPHIR_INIT_NVAR(&_29$$29);
				zephir_camelize(&_29$$29, &attributeName, NULL );
				ZEPHIR_INIT_NVAR(&setter);
				ZEPHIR_CONCAT_SV(&setter, "set", &_29$$29);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				_30$$29 = (zephir_method_exists(&instance, &setter)  == SUCCESS);
				if (_30$$29) {
					_30$$29 = !(zephir_array_isset_value(&localMethods, &setter));
				}
				if (_30$$29) {
					ZEPHIR_CALL_METHOD_ZVAL(NULL, &instance, &setter, NULL, 0, &castValue);
					zephir_check_call_status();
					continue;
				}
			}
			zephir_update_property_zval_zval(&instance, &attributeName, &castValue);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
		zephir_check_call_status();
		_32 = 1;
		while (1) {
			if (_32) {
				_32 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_31, &data, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_31)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &data, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&key) != IS_STRING) {
					continue;
				}
				_33$$31 = Z_TYPE_P(&value) == IS_NULL;
				if (_33$$31) {
					_33$$31 = zephir_fast_in_array(&key, &notNullAttributes);
				}
				if (_33$$31) {
					continue;
				}
				if (Z_TYPE_P(columnMap) != IS_ARRAY) {
					if (!(disableSetters)) {
						ZEPHIR_INIT_NVAR(&_34$$35);
						zephir_camelize(&_34$$35, &key, NULL );
						ZEPHIR_INIT_NVAR(&setter);
						ZEPHIR_CONCAT_SV(&setter, "set", &_34$$35);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						_35$$35 = (zephir_method_exists(&instance, &setter)  == SUCCESS);
						if (_35$$35) {
							_35$$35 = !(zephir_array_isset_value(&localMethods, &setter));
						}
						if (_35$$35) {
							ZEPHIR_CALL_METHOD_ZVAL(NULL, &instance, &setter, NULL, 0, &value);
							zephir_check_call_status();
							continue;
						}
					}
					zephir_update_property_zval_zval(&instance, &key, &value);
					continue;
				}
				ZEPHIR_OBS_NVAR(&attribute);
				if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
					_36$$37 = Z_TYPE_P(columnMap) == IS_ARRAY;
					if (_36$$37) {
						_36$$37 = !(ZEPHIR_IS_EMPTY(columnMap));
					}
					if (_36$$37) {
						if (Z_TYPE_P(&metaData) == IS_NULL) {
							ZEPHIR_CALL_METHOD(&metaData, &instance, "getModelsMetaData", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&reverseMap, &metaData, "getReverseColumnMap", NULL, 0, &instance);
						zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&attribute);
						if (!(zephir_array_isset_fetch(&attribute, &reverseMap, &key, 0))) {
							ZEPHIR_INIT_NVAR(&_38$$40);
							ZVAL_STRING(&_38$$40, "orm.ignore_unknown_columns");
							ZEPHIR_CALL_CE_STATIC(&_37$$40, phalcon_support_settings_ce, "get", &_11, 0, &_38$$40);
							zephir_check_call_status();
							if (UNEXPECTED(!zephir_is_true(&_37$$40))) {
								ZEPHIR_INIT_NVAR(&_39$$41);
								object_init_ex(&_39$$41, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_40$$41);
								zephir_get_class(&_40$$41, base, 0);
								ZEPHIR_INIT_NVAR(&_41$$41);
								ZEPHIR_CONCAT_SVSVS(&_41$$41, "Column '", &key, "' does not make part of the column map in '", &_40$$41, "'");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_39$$41, "__construct", &_16, 32, &_41$$41);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_39$$41, "phalcon/Mvc/Model.zep", 1045);
								ZEPHIR_MM_RESTORE();
								return;
							}
							continue;
						}
					} else {
						ZEPHIR_INIT_NVAR(&_43$$42);
						ZVAL_STRING(&_43$$42, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_42$$42, phalcon_support_settings_ce, "get", &_11, 0, &_43$$42);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_42$$42))) {
							ZEPHIR_INIT_NVAR(&_44$$43);
							object_init_ex(&_44$$43, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_45$$43);
							zephir_get_class(&_45$$43, base, 0);
							ZEPHIR_INIT_NVAR(&_46$$43);
							ZEPHIR_CONCAT_SVSVS(&_46$$43, "Column '", &key, "' does not make part of the column map in '", &_45$$43, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_44$$43, "__construct", &_16, 32, &_46$$43);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_44$$43, "phalcon/Mvc/Model.zep", 1054);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				}
				if (Z_TYPE_P(&attribute) != IS_ARRAY) {
					if (!(disableSetters)) {
						ZEPHIR_INIT_NVAR(&_47$$45);
						zephir_camelize(&_47$$45, &attribute, NULL );
						ZEPHIR_INIT_NVAR(&setter);
						ZEPHIR_CONCAT_SV(&setter, "set", &_47$$45);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						_48$$45 = (zephir_method_exists(&instance, &setter)  == SUCCESS);
						if (_48$$45) {
							_48$$45 = !(zephir_array_isset_value(&localMethods, &setter));
						}
						if (_48$$45) {
							ZEPHIR_CALL_METHOD_ZVAL(NULL, &instance, &setter, NULL, 0, &value);
							zephir_check_call_status();
							continue;
						}
					}
					zephir_update_property_zval_zval(&instance, &attribute, &value);
					continue;
				}
				_49$$31 = !ZEPHIR_IS_STRING(&value, "");
				if (_49$$31) {
					_49$$31 = Z_TYPE_P(&value) != IS_NULL;
				}
				if (_49$$31) {
					ZEPHIR_OBS_NVAR(&_50$$47);
					zephir_array_fetch_long(&_50$$47, &attribute, 1, PH_NOISY, "phalcon/Mvc/Model.zep", 1076);
					if (ZEPHIR_IS_LONG(&_50$$47, 0)) { goto zephir_switch_2_clause_0; }
					if (ZEPHIR_IS_LONG(&_50$$47, 21)) { goto zephir_switch_2_clause_1; }
					if (ZEPHIR_IS_LONG(&_50$$47, 22)) { goto zephir_switch_2_clause_2; }
					if (ZEPHIR_IS_LONG(&_50$$47, 26)) { goto zephir_switch_2_clause_3; }
					if (ZEPHIR_IS_LONG(&_50$$47, 3)) { goto zephir_switch_2_clause_4; }
					if (ZEPHIR_IS_LONG(&_50$$47, 9)) { goto zephir_switch_2_clause_5; }
					if (ZEPHIR_IS_LONG(&_50$$47, 7)) { goto zephir_switch_2_clause_6; }
					if (ZEPHIR_IS_LONG(&_50$$47, 8)) { goto zephir_switch_2_clause_7; }
					goto zephir_switch_2_clause_8;
					zephir_switch_2_clause_0: ;
					zephir_switch_2_clause_1: ;
					zephir_switch_2_clause_2: ;
					zephir_switch_2_clause_3: ;
						ZVAL_LONG(&_51$$48, 10);
						ZEPHIR_CALL_FUNCTION(&castValue, "intval", &_27, 41, &value, &_51$$48);
						zephir_check_call_status();
						goto zephir_switch_2_end;
					zephir_switch_2_clause_4: ;
					zephir_switch_2_clause_5: ;
					zephir_switch_2_clause_6: ;
						ZEPHIR_INIT_NVAR(&castValue);
						ZVAL_DOUBLE(&castValue, zephir_get_doubleval(&value));
						goto zephir_switch_2_end;
					zephir_switch_2_clause_7: ;
						ZEPHIR_INIT_NVAR(&castValue);
						ZVAL_BOOL(&castValue, zephir_get_boolval(&value));
						goto zephir_switch_2_end;
					zephir_switch_2_clause_8: ;
						ZEPHIR_CPY_WRT(&castValue, &value);
						goto zephir_switch_2_end;
					zephir_switch_2_end: ;

				} else {
					ZEPHIR_OBS_NVAR(&_52$$52);
					zephir_array_fetch_long(&_52$$52, &attribute, 1, PH_NOISY, "phalcon/Mvc/Model.zep", 1099);
					if (ZEPHIR_IS_LONG(&_52$$52, 14)) { goto zephir_switch_3_clause_0; }
					if (ZEPHIR_IS_LONG(&_52$$52, 8)) { goto zephir_switch_3_clause_1; }
					if (ZEPHIR_IS_LONG(&_52$$52, 3)) { goto zephir_switch_3_clause_2; }
					if (ZEPHIR_IS_LONG(&_52$$52, 9)) { goto zephir_switch_3_clause_3; }
					if (ZEPHIR_IS_LONG(&_52$$52, 7)) { goto zephir_switch_3_clause_4; }
					if (ZEPHIR_IS_LONG(&_52$$52, 0)) { goto zephir_switch_3_clause_5; }
					if (ZEPHIR_IS_LONG(&_52$$52, 21)) { goto zephir_switch_3_clause_6; }
					if (ZEPHIR_IS_LONG(&_52$$52, 22)) { goto zephir_switch_3_clause_7; }
					if (ZEPHIR_IS_LONG(&_52$$52, 26)) { goto zephir_switch_3_clause_8; }
					goto zephir_switch_3_clause_9;
					zephir_switch_3_clause_0: ;
					zephir_switch_3_clause_1: ;
					zephir_switch_3_clause_2: ;
					zephir_switch_3_clause_3: ;
					zephir_switch_3_clause_4: ;
					zephir_switch_3_clause_5: ;
					zephir_switch_3_clause_6: ;
					zephir_switch_3_clause_7: ;
					zephir_switch_3_clause_8: ;
						ZEPHIR_INIT_NVAR(&castValue);
						ZVAL_NULL(&castValue);
						goto zephir_switch_3_end;
					zephir_switch_3_clause_9: ;
						ZEPHIR_CPY_WRT(&castValue, &value);
						goto zephir_switch_3_end;
					zephir_switch_3_end: ;

				}
				ZEPHIR_OBS_NVAR(&attributeName);
				zephir_array_fetch_long(&attributeName, &attribute, 0, PH_NOISY, "phalcon/Mvc/Model.zep", 1118);
				zephir_array_update_zval(&data, &key, &castValue, PH_COPY | PH_SEPARATE);
				if (!(disableSetters)) {
					ZEPHIR_INIT_NVAR(&_53$$55);
					zephir_camelize(&_53$$55, &attributeName, NULL );
					ZEPHIR_INIT_NVAR(&setter);
					ZEPHIR_CONCAT_SV(&setter, "set", &_53$$55);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					_54$$55 = (zephir_method_exists(&instance, &setter)  == SUCCESS);
					if (_54$$55) {
						_54$$55 = !(zephir_array_isset_value(&localMethods, &setter));
					}
					if (_54$$55) {
						ZEPHIR_CALL_METHOD_ZVAL(NULL, &instance, &setter, NULL, 0, &castValue);
						zephir_check_call_status();
						continue;
					}
				}
				zephir_update_property_zval_zval(&instance, &attributeName, &castValue);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	if (keepSnapshots) {
		ZEPHIR_CALL_METHOD(NULL, &instance, "setSnapshotData", NULL, 0, &data, columnMap);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &instance, "setOldSnapshotData", NULL, 0, &data, columnMap);
		zephir_check_call_status();
	}
	if ((zephir_method_exists_ex(&instance, ZEND_STRL("fireevent")) == SUCCESS)) {
		ZEPHIR_INIT_VAR(&_55$$58);
		ZVAL_STRING(&_55$$58, "afterFetch");
		ZEPHIR_CALL_METHOD(NULL, &instance, "fireEvent", NULL, 0, &_55$$58);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&instance);
}

/**
 * Returns an hydrated result based on the data and the column map
 *
 * @param array data
 * @param mixed columnMap
 * @param int hydrationMode
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, cloneResultMapHydrate)
{
	zend_bool _15, _3$$7, _16$$16;
	zend_string *_2;
	zend_ulong _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_8 = NULL, *_13 = NULL;
	zend_long hydrationMode, ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *columnMap, columnMap_sub, *hydrationMode_param = NULL, key, value, attribute, attributeName, *_0, _14, _4$$7, _6$$7, _7$$8, _9$$9, _10$$9, _11$$10, _12$$10, _17$$16, _18$$16, _19$$17, _20$$18, _21$$18, _22$$19, _23$$19, _24$$23;
	zval data, hydrateArray;

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&hydrateArray);
	ZVAL_UNDEF(&columnMap_sub);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&attributeName);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_17$$16);
	ZVAL_UNDEF(&_18$$16);
	ZVAL_UNDEF(&_19$$17);
	ZVAL_UNDEF(&_20$$18);
	ZVAL_UNDEF(&_21$$18);
	ZVAL_UNDEF(&_22$$19);
	ZVAL_UNDEF(&_23$$19);
	ZVAL_UNDEF(&_24$$23);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
		Z_PARAM_ZVAL(columnMap)
		Z_PARAM_LONG(hydrationMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &data_param, &columnMap, &hydrationMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);
	if (Z_TYPE_P(columnMap) != IS_ARRAY) {
		if (hydrationMode == 1) {
			RETURN_CTOR(&data);
		}
	}
	ZEPHIR_INIT_VAR(&hydrateArray);
	array_init(&hydrateArray);
	zephir_is_iterable(&data, 0, "phalcon/Mvc/Model.zep", 1222);
	if (Z_TYPE_P(&data) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _1, _2, _0)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_2 != NULL) { 
				ZVAL_STR_COPY(&key, _2);
			} else {
				ZVAL_LONG(&key, _1);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _0);
			if (Z_TYPE_P(&key) != IS_STRING) {
				continue;
			}
			if (Z_TYPE_P(columnMap) == IS_ARRAY) {
				_3$$7 = !(zephir_array_isset_value(columnMap, &key));
				if (_3$$7) {
					ZEPHIR_INIT_NVAR(&_6$$7);
					ZVAL_STRING(&_6$$7, "orm.case_insensitive_column_map");
					ZEPHIR_CALL_CE_STATIC(&_4$$7, phalcon_support_settings_ce, "get", &_5, 0, &_6$$7);
					zephir_check_call_status();
					_3$$7 = zephir_is_true(&_4$$7);
				}
				if (_3$$7) {
					ZEPHIR_CALL_SELF(&_7$$8, "caseInsensitiveColumnMap", &_8, 461, columnMap, &key);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&key, &_7$$8);
				}
				ZEPHIR_OBS_NVAR(&attribute);
				if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
					ZEPHIR_INIT_NVAR(&_10$$9);
					ZVAL_STRING(&_10$$9, "orm.ignore_unknown_columns");
					ZEPHIR_CALL_CE_STATIC(&_9$$9, phalcon_support_settings_ce, "get", &_5, 0, &_10$$9);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_9$$9))) {
						ZEPHIR_INIT_NVAR(&_11$$10);
						object_init_ex(&_11$$10, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_12$$10);
						ZEPHIR_CONCAT_SVS(&_12$$10, "Column '", &key, "' does not make part of the column map");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_11$$10, "__construct", &_13, 32, &_12$$10);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_11$$10, "phalcon/Mvc/Model.zep", 1201);
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
				if (Z_TYPE_P(&attribute) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeName);
					zephir_array_fetch_long(&attributeName, &attribute, 0, PH_NOISY, "phalcon/Mvc/Model.zep", 1211);
				} else {
					ZEPHIR_CPY_WRT(&attributeName, &attribute);
				}
				zephir_array_update_zval(&hydrateArray, &attributeName, &value, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&hydrateArray, &key, &value, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
		zephir_check_call_status();
		_15 = 1;
		while (1) {
			if (_15) {
				_15 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_14, &data, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_14)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &data, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&key) != IS_STRING) {
					continue;
				}
				if (Z_TYPE_P(columnMap) == IS_ARRAY) {
					_16$$16 = !(zephir_array_isset_value(columnMap, &key));
					if (_16$$16) {
						ZEPHIR_INIT_NVAR(&_18$$16);
						ZVAL_STRING(&_18$$16, "orm.case_insensitive_column_map");
						ZEPHIR_CALL_CE_STATIC(&_17$$16, phalcon_support_settings_ce, "get", &_5, 0, &_18$$16);
						zephir_check_call_status();
						_16$$16 = zephir_is_true(&_17$$16);
					}
					if (_16$$16) {
						ZEPHIR_CALL_SELF(&_19$$17, "caseInsensitiveColumnMap", &_8, 461, columnMap, &key);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&key, &_19$$17);
					}
					ZEPHIR_OBS_NVAR(&attribute);
					if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
						ZEPHIR_INIT_NVAR(&_21$$18);
						ZVAL_STRING(&_21$$18, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_20$$18, phalcon_support_settings_ce, "get", &_5, 0, &_21$$18);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_20$$18))) {
							ZEPHIR_INIT_NVAR(&_22$$19);
							object_init_ex(&_22$$19, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_23$$19);
							ZEPHIR_CONCAT_SVS(&_23$$19, "Column '", &key, "' does not make part of the column map");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_22$$19, "__construct", &_13, 32, &_23$$19);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_22$$19, "phalcon/Mvc/Model.zep", 1201);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
					if (Z_TYPE_P(&attribute) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attributeName);
						zephir_array_fetch_long(&attributeName, &attribute, 0, PH_NOISY, "phalcon/Mvc/Model.zep", 1211);
					} else {
						ZEPHIR_CPY_WRT(&attributeName, &attribute);
					}
					zephir_array_update_zval(&hydrateArray, &attributeName, &value, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&hydrateArray, &key, &value, PH_COPY | PH_SEPARATE);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	if (hydrationMode != 1) {
		ZEPHIR_CPY_WRT(&_24$$23, &hydrateArray);
		zephir_convert_to_object(&_24$$23);
		RETURN_CCTOR(&_24$$23);
	}
	RETURN_CTOR(&hydrateArray);
}

/**
 * Collects previously queried (belongs-to, has-one and has-one-through)
 * related records along with freshly added one
 *
 * @return array Related records that should be saved
 */
PHP_METHOD(Phalcon_Mvc_Model, collectRelatedToSave)
{
	zend_bool _5$$3;
	zend_string *_4;
	zend_ulong _3;
	zval related, dirtyRelated;
	zval name, record, _0, _1, *_2, _6$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&record);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&related);
	ZVAL_UNDEF(&dirtyRelated);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("related", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("dirtyRelated", 12, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 710, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(Z_TYPE_P(&_0) != IS_ARRAY)) {
		zephir_throw_variable_type_error(&_0, "related", "array");
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&related, &_0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 709, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(Z_TYPE_P(&_1) != IS_ARRAY)) {
		zephir_throw_variable_type_error(&_1, "dirtyRelated", "array");
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&dirtyRelated, &_1);
	zephir_is_iterable(&related, 0, "phalcon/Mvc/Model.zep", 1263);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&related), _3, _4, _2)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_4 != NULL) { 
			ZVAL_STR_COPY(&name, _4);
		} else {
			ZVAL_LONG(&name, _3);
		}
		ZEPHIR_INIT_NVAR(&record);
		ZVAL_COPY(&record, _2);
		if (zephir_array_isset_value(&dirtyRelated, &name)) {
			continue;
		}
		_5$$3 = Z_TYPE_P(&record) != IS_OBJECT;
		if (!(_5$$3)) {
			_5$$3 = !((zephir_instance_of_ev(&record, phalcon_mvc_modelinterface_ce)));
		}
		if (_5$$3) {
			continue;
		}
		ZVAL_LONG(&_6$$3, 1);
		ZEPHIR_CALL_METHOD(NULL, &record, "setDirtyState", NULL, 0, &_6$$3);
		zephir_check_call_status();
		zephir_array_update_zval(&dirtyRelated, &name, &record, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&record);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CTOR(&dirtyRelated);
}

/**
 * Counts how many records match the specified conditions.
 *
 * Returns an integer for simple queries or a ResultsetInterface
 * instance for when the GROUP condition is used. The results will
 * contain the count of each group.
 *
 * ```php
 * // How many robots are there?
 * $number = Robots::count();
 *
 * echo "There are ", $number, "\n";
 *
 * // How many mechanical robots are there?
 * $number = Robots::count("type = 'mechanical'");
 *
 * echo "There are ", $number, " mechanical robots\n";
 * ```
 *
 * @param array|string|null parameters
 */
PHP_METHOD(Phalcon_Mvc_Model, count)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, parameters_sub, __$null, result, _0, _1;

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters);
	if (!parameters) {
		parameters = &parameters_sub;
		ZEPHIR_CPY_WRT(parameters, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(parameters);
	}
	if (zephir_array_isset_value_string(parameters, SL("order"))) {
		zephir_array_unset_string(parameters, SL("order"), PH_SEPARATE);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "COUNT");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "rowcount");
	ZEPHIR_CALL_SELF(&result, "groupResult", NULL, 0, &_0, &_1, parameters);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) == IS_STRING) {
		RETURN_MM_LONG(zephir_get_intval(&result));
	}
	RETURN_CCTOR(&result);
}

/**
 * Inserts a model instance. If the instance already exists in the
 * persistence it will throw an exception
 * Returning true on success or false otherwise.
 *
 *```php
 * // Creating a new robot
 * $robot = new Robots();
 *
 * $robot->type = "mechanical";
 * $robot->name = "Astro Boy";
 * $robot->year = 1952;
 *
 * $robot->create();
 *
 * // Passing an array to create
 * $robot = new Robots();
 *
 * $robot->assign(
 *     [
 *         "type" => "mechanical",
 *         "name" => "Astro Boy",
 *         "year" => 1952,
 *     ]
 * );
 *
 * $robot->create();
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, create)
{
	zval _2$$3, _4$$3;
	zval metaData, _0, _1, _3$$3, _5$$3, _6$$3, _7$$3, _8$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("errorMessages", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getWriteConnection", NULL, 462);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "has", NULL, 0, &metaData, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_create_array(&_2$$3, 1, 0);
		ZEPHIR_INIT_VAR(&_3$$3);
		object_init_ex(&_3$$3, phalcon_messages_message_ce);
		ZEPHIR_INIT_VAR(&_4$$3);
		zephir_create_array(&_4$$3, 1, 0);
		ZEPHIR_INIT_VAR(&_5$$3);
		zephir_get_class(&_5$$3, this_ptr, 0);
		zephir_array_update_string(&_4$$3, SL("model"), &_5$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "Record cannot be created because it already exists");
		ZVAL_NULL(&_6$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "InvalidCreateAttempt");
		ZVAL_LONG(&_8$$3, 0);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "__construct", NULL, 6, &_5$$3, &_6$$3, &_7$$3, &_8$$3, &_4$$3);
		zephir_check_call_status();
		zephir_array_fast_append(&_2$$3, &_3$$3);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 713, &_2$$3);
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "save", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Deletes a model instance. Returning true on success or false otherwise.
 *
 * ```php
 * $robot = Robots::findFirst("id=100");
 *
 * $robot->delete();
 *
 * $robots = Robots::find("type = 'mechanical'");
 *
 * foreach ($robots as $robot) {
 *     $robot->delete();
 * }
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, delete)
{
	zend_bool _24;
	zval values, bindTypes, conditions;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, __$false, metaData, writeConnection, primaryKeys, bindDataTypes, columnMap, attributeField, primaryKey, bindType, value, schema, source, table, success, _0, _1, _2, _3, _5, *_9, *_10, _23, _37, _38, _42, _43, _45, _4$$3, _6$$7, _7$$7, _8$$7, _11$$9, _12$$9, _13$$9, _14$$11, _15$$11, _16$$11, _17$$13, _18$$13, _19$$13, _20$$8, _22$$8, _25$$15, _26$$15, _27$$15, _28$$17, _29$$17, _30$$17, _31$$19, _32$$19, _33$$19, _34$$14, _36$$14, _39$$20, _40$$20, _41$$20, _44$$25, _46$$28, _47$$29, _48$$29, _49$$29;
	zephir_fcall_cache_entry *_21 = NULL, *_35 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&writeConnection);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&bindDataTypes);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&primaryKey);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&success);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_42);
	ZVAL_UNDEF(&_43);
	ZVAL_UNDEF(&_45);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$13);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_25$$15);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_27$$15);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_29$$17);
	ZVAL_UNDEF(&_30$$17);
	ZVAL_UNDEF(&_31$$19);
	ZVAL_UNDEF(&_32$$19);
	ZVAL_UNDEF(&_33$$19);
	ZVAL_UNDEF(&_34$$14);
	ZVAL_UNDEF(&_36$$14);
	ZVAL_UNDEF(&_39$$20);
	ZVAL_UNDEF(&_40$$20);
	ZVAL_UNDEF(&_41$$20);
	ZVAL_UNDEF(&_44$$25);
	ZVAL_UNDEF(&_46$$28);
	ZVAL_UNDEF(&_47$$29);
	ZVAL_UNDEF(&_48$$29);
	ZVAL_UNDEF(&_49$$29);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&conditions);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("operationMade", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("errorMessages", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("skipped", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("related", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("dirtyRelated", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("dirtyState", 10, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&writeConnection, this_ptr, "getWriteConnection", NULL, 462);
	zephir_check_call_status();
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 3);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 714, &_0);
	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 713, &_1);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "orm.virtual_foreign_keys");
	ZEPHIR_CALL_CE_STATIC(&_2, phalcon_support_settings_ce, "get", NULL, 0, &_3);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "checkForeignKeysReverseRestrict", NULL, 463);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_4$$3)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_VAR(&values);
	array_init(&values);
	ZEPHIR_INIT_VAR(&bindTypes);
	array_init(&bindTypes);
	ZEPHIR_INIT_VAR(&conditions);
	array_init(&conditions);
	ZEPHIR_CALL_METHOD(&primaryKeys, &metaData, "getPrimaryKeyAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&bindDataTypes, &metaData, "getBindTypes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "orm.column_renaming");
	ZEPHIR_CALL_CE_STATIC(&_5, phalcon_support_settings_ce, "get", NULL, 0, &_3);
	zephir_check_call_status();
	if (zephir_is_true(&_5)) {
		ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, this_ptr);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&columnMap);
		ZVAL_NULL(&columnMap);
	}
	if (UNEXPECTED(!(zephir_fast_count_int(&primaryKeys)))) {
		ZEPHIR_INIT_VAR(&_6$$7);
		object_init_ex(&_6$$7, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_7$$7);
		zephir_get_class(&_7$$7, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_8$$7);
		ZEPHIR_CONCAT_SVS(&_8$$7, "A primary key must be defined in the model in order to perform the operation in '", &_7$$7, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_6$$7, "__construct", NULL, 32, &_8$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$7, "phalcon/Mvc/Model.zep", 1427);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (Z_TYPE_P(&primaryKeys) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_3);
		zephir_string_to_char_array(&_3, &primaryKeys);
		_9 = &_3;
	} else {
		_9 = &primaryKeys;
	}
	zephir_is_iterable(_9, 0, "phalcon/Mvc/Model.zep", 1476);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _10)
		{
			ZEPHIR_INIT_NVAR(&primaryKey);
			ZVAL_COPY(&primaryKey, _10);
			ZEPHIR_OBS_NVAR(&bindType);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &primaryKey, 0)))) {
				ZEPHIR_INIT_NVAR(&_11$$9);
				object_init_ex(&_11$$9, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_NVAR(&_12$$9);
				zephir_get_class(&_12$$9, this_ptr, 0);
				ZEPHIR_INIT_NVAR(&_13$$9);
				ZEPHIR_CONCAT_SVSVS(&_13$$9, "Column '", &primaryKey, "' have not defined a bind data type in '", &_12$$9, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_11$$9, "__construct", NULL, 32, &_13$$9);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_11$$9, "phalcon/Mvc/Model.zep", 1441);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
				ZEPHIR_OBS_NVAR(&attributeField);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &primaryKey, 0)))) {
					ZEPHIR_INIT_NVAR(&_14$$11);
					object_init_ex(&_14$$11, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_15$$11);
					zephir_get_class(&_15$$11, this_ptr, 0);
					ZEPHIR_INIT_NVAR(&_16$$11);
					ZEPHIR_CONCAT_SVSVS(&_16$$11, "Column '", &primaryKey, "' isn't part of the column map in '", &_15$$11, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_14$$11, "__construct", NULL, 32, &_16$$11);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_14$$11, "phalcon/Mvc/Model.zep", 1451);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&attributeField, &primaryKey);
			}
			ZEPHIR_OBS_NVAR(&value);
			if (UNEXPECTED(!(zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)))) {
				ZEPHIR_INIT_NVAR(&_17$$13);
				object_init_ex(&_17$$13, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_NVAR(&_18$$13);
				zephir_get_class(&_18$$13, this_ptr, 0);
				ZEPHIR_INIT_NVAR(&_19$$13);
				ZEPHIR_CONCAT_SVSVS(&_19$$13, "Cannot delete the record because the primary key attribute: '", &attributeField, "' was not set in '", &_18$$13, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_17$$13, "__construct", NULL, 32, &_19$$13);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_17$$13, "phalcon/Mvc/Model.zep", 1465);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1471);
			ZEPHIR_CALL_METHOD(&_20$$8, &writeConnection, "escapeIdentifier", &_21, 0, &primaryKey);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_22$$8);
			ZEPHIR_CONCAT_VS(&_22$$8, &_20$$8, " = ?");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&conditions, &_22$$8, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1472);
			zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1473);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_24 = 1;
		while (1) {
			if (_24) {
				_24 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_23, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_23)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&primaryKey, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&bindType);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &primaryKey, 0)))) {
					ZEPHIR_INIT_NVAR(&_25$$15);
					object_init_ex(&_25$$15, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_26$$15);
					zephir_get_class(&_26$$15, this_ptr, 0);
					ZEPHIR_INIT_NVAR(&_27$$15);
					ZEPHIR_CONCAT_SVSVS(&_27$$15, "Column '", &primaryKey, "' have not defined a bind data type in '", &_26$$15, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_25$$15, "__construct", NULL, 32, &_27$$15);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_25$$15, "phalcon/Mvc/Model.zep", 1441);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &primaryKey, 0)))) {
						ZEPHIR_INIT_NVAR(&_28$$17);
						object_init_ex(&_28$$17, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_29$$17);
						zephir_get_class(&_29$$17, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_30$$17);
						ZEPHIR_CONCAT_SVSVS(&_30$$17, "Column '", &primaryKey, "' isn't part of the column map in '", &_29$$17, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_28$$17, "__construct", NULL, 32, &_30$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_28$$17, "phalcon/Mvc/Model.zep", 1451);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &primaryKey);
				}
				ZEPHIR_OBS_NVAR(&value);
				if (UNEXPECTED(!(zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)))) {
					ZEPHIR_INIT_NVAR(&_31$$19);
					object_init_ex(&_31$$19, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_32$$19);
					zephir_get_class(&_32$$19, this_ptr, 0);
					ZEPHIR_INIT_NVAR(&_33$$19);
					ZEPHIR_CONCAT_SVSVS(&_33$$19, "Cannot delete the record because the primary key attribute: '", &attributeField, "' was not set in '", &_32$$19, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_31$$19, "__construct", NULL, 32, &_33$$19);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_31$$19, "phalcon/Mvc/Model.zep", 1465);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1471);
				ZEPHIR_CALL_METHOD(&_34$$14, &writeConnection, "escapeIdentifier", &_35, 0, &primaryKey);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_36$$14);
				ZEPHIR_CONCAT_VS(&_36$$14, &_34$$14, " = ?");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&conditions, &_36$$14, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1472);
				zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1473);
		}
	}
	ZEPHIR_INIT_NVAR(&primaryKey);
	ZEPHIR_INIT_VAR(&_38);
	ZVAL_STRING(&_38, "orm.events");
	ZEPHIR_CALL_CE_STATIC(&_37, phalcon_support_settings_ce, "get", NULL, 0, &_38);
	zephir_check_call_status();
	if (zephir_is_true(&_37)) {
		if (0) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 715, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 715, &__$false);
		}
		ZEPHIR_INIT_VAR(&_40$$20);
		ZVAL_STRING(&_40$$20, "beforeDelete");
		ZEPHIR_CALL_METHOD(&_39$$20, this_ptr, "fireEventCancel", NULL, 0, &_40$$20);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_39$$20)) {
			RETURN_MM_BOOL(0);
		}
		zephir_read_property_cached(&_41$$20, this_ptr, _zephir_prop_2, 715, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_41$$20)) {
			RETURN_MM_BOOL(1);
		}
	}
	ZEPHIR_CALL_METHOD(&schema, this_ptr, "getSchema", NULL, 464);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, this_ptr, "getSource", NULL, 465);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		ZEPHIR_INIT_VAR(&table);
		zephir_create_array(&table, 2, 0);
		zephir_array_fast_append(&table, &schema);
		zephir_array_fast_append(&table, &source);
	} else {
		ZEPHIR_CPY_WRT(&table, &source);
	}
	ZEPHIR_INIT_NVAR(&_38);
	zephir_fast_join_str(&_38, SL(" AND "), &conditions);
	ZEPHIR_CALL_METHOD(&success, &writeConnection, "delete", NULL, 0, &table, &_38, &values, &bindTypes);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_43);
	ZVAL_STRING(&_43, "orm.virtual_foreign_keys");
	ZEPHIR_CALL_CE_STATIC(&_42, phalcon_support_settings_ce, "get", NULL, 0, &_43);
	zephir_check_call_status();
	if (zephir_is_true(&_42)) {
		ZEPHIR_CALL_METHOD(&_44$$25, this_ptr, "checkForeignKeysReverseCascade", NULL, 466);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_44$$25)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_NVAR(&_43);
	ZVAL_STRING(&_43, "orm.events");
	ZEPHIR_CALL_CE_STATIC(&_45, phalcon_support_settings_ce, "get", NULL, 0, &_43);
	zephir_check_call_status();
	if (zephir_is_true(&_45)) {
		if (zephir_is_true(&success)) {
			ZEPHIR_INIT_VAR(&_46$$28);
			ZVAL_STRING(&_46$$28, "afterDelete");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_46$$28);
			zephir_check_call_status();
		}
	}
	if (zephir_is_true(&success)) {
		ZEPHIR_INIT_VAR(&_47$$29);
		array_init(&_47$$29);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 710, &_47$$29);
		ZEPHIR_INIT_VAR(&_48$$29);
		array_init(&_48$$29);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 709, &_48$$29);
		zephir_read_property_cached(&_49$$29, this_ptr, _zephir_prop_5, 708, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_49$$29, "clearReusableObjects", NULL, 0);
		zephir_check_call_status();
	}
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 2);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 711, &_0);
	RETURN_CCTOR(&success);
}

/**
 * Returns a simple representation of the object that can be used with
 * `var_dump()`
 *
 *```php
 * var_dump(
 *     $robot->dump()
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, dump)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_FUNCTION("get_object_vars", NULL, 467, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Query for a set of records that match the specified conditions
 *
 * ```php
 * // How many robots are there?
 * $robots = Robots::find();
 *
 * echo "There are ", count($robots), "\n";
 *
 * // How many mechanical robots are there?
 * $robots = Robots::find(
 *     "type = 'mechanical'"
 * );
 *
 * echo "There are ", count($robots), "\n";
 *
 * // Get and print virtual robots ordered by name
 * $robots = Robots::find(
 *     [
 *         "type = 'virtual'",
 *         "order" => "name",
 *     ]
 * );
 *
 * foreach ($robots as $robot) {
 *     echo $robot->name, "\n";
 * }
 *
 * // Get first 100 virtual robots ordered by name
 * $robots = Robots::find(
 *     [
 *         "type = 'virtual'",
 *         "order" => "name",
 *         "limit" => 100,
 *     ]
 * );
 *
 * foreach ($robots as $robot) {
 *     echo $robot->name, "\n";
 * }
 *
 * // encapsulate find it into an running transaction esp. useful for application unit-tests
 * // or complex business logic where we wanna control which transactions are used.
 *
 * $myTransaction = new Transaction(\Phalcon\Di\Di::getDefault());
 * $myTransaction->begin();
 *
 * $newRobot = new Robot();
 * $newRobot->setTransaction($myTransaction);
 *
 * $newRobot->assign(
 *     [
 *         'name' => 'test',
 *         'type' => 'mechanical',
 *         'year' => 1944,
 *     ]
 * );
 *
 * $newRobot->save();
 *
 * $resultInsideTransaction = Robot::find(
 *     [
 *         'name' => 'test',
 *         Model::TRANSACTION_INDEX => $myTransaction,
 *     ]
 * );
 *
 * $resultOutsideTransaction = Robot::find(['name' => 'test']);
 *
 * foreach ($setInsideTransaction as $robot) {
 *     echo $robot->name, "\n";
 * }
 *
 * foreach ($setOutsideTransaction as $robot) {
 *     echo $robot->name, "\n";
 * }
 *
 * // reverts all not commited changes
 * $myTransaction->rollback();
 *
 * // creating two different transactions
 * $myTransaction1 = new Transaction(\Phalcon\Di\Di::getDefault());
 * $myTransaction1->begin();
 * $myTransaction2 = new Transaction(\Phalcon\Di\Di::getDefault());
 * $myTransaction2->begin();
 *
 *  // add a new robots
 * $firstNewRobot = new Robot();
 * $firstNewRobot->setTransaction($myTransaction1);
 * $firstNewRobot->assign(
 *     [
 *         'name' => 'first-transaction-robot',
 *         'type' => 'mechanical',
 *         'year' => 1944,
 *     ]
 * );
 * $firstNewRobot->save();
 *
 * $secondNewRobot = new Robot();
 * $secondNewRobot->setTransaction($myTransaction2);
 * $secondNewRobot->assign(
 *     [
 *         'name' => 'second-transaction-robot',
 *         'type' => 'fictional',
 *         'year' => 1984,
 *     ]
 * );
 * $secondNewRobot->save();
 *
 * // this transaction will find the robot.
 * $resultInFirstTransaction = Robot::find(
 *     [
 *         'name'                   => 'first-transaction-robot',
 *         Model::TRANSACTION_INDEX => $myTransaction1,
 *     ]
 * );
 *
 * // this transaction won't find the robot.
 * $resultInSecondTransaction = Robot::find(
 *     [
 *         'name'                   => 'first-transaction-robot',
 *         Model::TRANSACTION_INDEX => $myTransaction2,
 *     ]
 * );
 *
 * // this transaction won't find the robot.
 * $resultOutsideAnyExplicitTransaction = Robot::find(
 *     [
 *         'name' => 'first-transaction-robot',
 *     ]
 * );
 *
 * // this transaction won't find the robot.
 * $resultInFirstTransaction = Robot::find(
 *     [
 *         'name'                   => 'second-transaction-robot',
 *         Model::TRANSACTION_INDEX => $myTransaction2,
 *     ]
 * );
 *
 * // this transaction will find the robot.
 * $resultInSecondTransaction = Robot::find(
 *     [
 *         'name'                   => 'second-transaction-robot',
 *         Model::TRANSACTION_INDEX => $myTransaction1,
 *     ]
 * );
 *
 * // this transaction won't find the robot.
 * $resultOutsideAnyExplicitTransaction = Robot::find(
 *     [
 *         'name' => 'second-transaction-robot',
 *     ]
 * );
 *
 * $transaction1->rollback();
 * $transaction2->rollback();
 * ```
 *
 * @param array|string|int|null parameters = [
 *     'conditions' => '',
 *     'columns' => '',
 *     'bind' => [],
 *     'bindTypes' => [],
 *     'order' => '',
 *     'limit' => 10,
 *     'offset' => 5,
 *     'group' => 'name, status',
 *     'for_update' => false,
 *     'shared_lock' => false,
 *     'cache' => [
 *         'lifetime' => 3600,
 *         'key' => 'my-find-key'
 *     ],
 *     'hydration' => null
 * ]
 * @return T[]|\Phalcon\Mvc\Model\Resultset<int, T>
 */
PHP_METHOD(Phalcon_Mvc_Model, find)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *parameters = NULL, parameters_sub, __$null, params, query, resultset, hydration;

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&resultset);
	ZVAL_UNDEF(&hydration);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
		if (Z_TYPE_P(parameters) != IS_NULL) {
			zephir_array_append(&params, parameters, PH_SEPARATE, "phalcon/Mvc/Model.zep", 1748);
		}
	} else {
		ZEPHIR_CPY_WRT(&params, parameters);
	}
	ZEPHIR_CALL_STATIC(&query, "getPreparedQuery", &_0, 468, &params);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&resultset, &query, "execute", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&resultset) == IS_OBJECT) {
		zephir_memory_observe(&hydration);
		if (zephir_array_isset_string_fetch(&hydration, &params, SL("hydration"), 0)) {
			ZEPHIR_CALL_METHOD(NULL, &resultset, "setHydrateMode", NULL, 0, &hydration);
			zephir_check_call_status();
		}
	}
	RETURN_CCTOR(&resultset);
}

/**
 * Query the first record that matches the specified conditions
 *
 * ```php
 * // What's the first robot in robots table?
 * $robot = Robots::findFirst();
 *
 * echo "The robot name is ", $robot->name;
 *
 * // What's the first mechanical robot in robots table?
 * $robot = Robots::findFirst(
 *     "type = 'mechanical'"
 * );
 *
 * echo "The first mechanical robot name is ", $robot->name;
 *
 * // Get first virtual robot ordered by name
 * $robot = Robots::findFirst(
 *     [
 *         "type = 'virtual'",
 *         "order" => "name",
 *     ]
 * );
 *
 * echo "The first virtual robot name is ", $robot->name;
 *
 * // behaviour with transaction
 * $myTransaction = new Transaction(\Phalcon\Di\Di::getDefault());
 * $myTransaction->begin();
 *
 * $newRobot = new Robot();
 * $newRobot->setTransaction($myTransaction);
 * $newRobot->assign(
 *     [
 *         'name' => 'test',
 *         'type' => 'mechanical',
 *         'year' => 1944,
 *     ]
 * );
 * $newRobot->save();
 *
 * $findsARobot = Robot::findFirst(
 *     [
 *         'name'                   => 'test',
 *         Model::TRANSACTION_INDEX => $myTransaction,
 *     ]
 * );
 *
 * $doesNotFindARobot = Robot::findFirst(
 *     [
 *         'name' => 'test',
 *     ]
 * );
 *
 * var_dump($findARobot);
 * var_dump($doesNotFindARobot);
 *
 * $transaction->commit();
 *
 * $doesFindTheRobotNow = Robot::findFirst(
 *     [
 *         'name' => 'test',
 *     ]
 * );
 * ```
 *
 * @param array|string|int|null parameters = [
 *     'conditions' => '',
 *     'columns' => '',
 *     'bind' => [],
 *     'bindTypes' => [],
 *     'order' => '',
 *     'limit' => 10,
 *     'offset' => 5,
 *     'group' => 'name, status',
 *     'for_update' => false,
 *     'shared_lock' => false,
 *     'cache' => [
 *         'lifetime' => 3600,
 *         'key' => 'my-find-key'
 *     ],
 *     'hydration' => null
 * ]
 *
 * @return T|\Phalcon\Mvc\ModelInterface|\Phalcon\Mvc\Model\Row|null
 */
PHP_METHOD(Phalcon_Mvc_Model, findFirst)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, parameters_sub, __$null, params, query, _6, _1$$5, _2$$6, _3$$6, _4$$6;

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	ZEPHIR_INIT_VAR(&params);
	if (Z_TYPE_P(parameters) == IS_NULL) {
		ZEPHIR_INIT_NVAR(&params);
		array_init(&params);
	} else if (Z_TYPE_P(parameters) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&params, parameters);
	} else {
		_0 = Z_TYPE_P(parameters) == IS_STRING;
		if (!(_0)) {
			_0 = zephir_is_numeric(parameters);
		}
		if (_0) {
			ZEPHIR_INIT_VAR(&_1$$5);
			zephir_create_array(&_1$$5, 1, 0);
			zephir_array_fast_append(&_1$$5, parameters);
			ZEPHIR_CPY_WRT(&params, &_1$$5);
		} else {
			ZEPHIR_INIT_VAR(&_2$$6);
			object_init_ex(&_2$$6, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_3$$6);
			zephir_get_called_class(&_3$$6);
			ZEPHIR_INIT_VAR(&_4$$6);
			ZEPHIR_CONCAT_SVS(&_4$$6, "Parameters passed must be of type array, string, numeric or null in '", &_3$$6, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_2$$6, "__construct", NULL, 32, &_4$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$6, "phalcon/Mvc/Model.zep", 1872);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZVAL_LONG(&_6, 1);
	ZEPHIR_CALL_STATIC(&query, "getPreparedQuery", &_5, 468, &params, &_6);
	zephir_check_call_status();
	ZVAL_BOOL(&_6, 1);
	ZEPHIR_CALL_METHOD(NULL, &query, "setUniqueRow", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&query, "execute", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Runs a native SQL statement and hydrates every row into this model.
 *
 * The statement goes to the database as written: CTEs, UNION, window
 * functions, database specific syntax. Placeholders are the PDO ones
 * (`:name` or `?`). The statement must return the model's real column
 * names; the column map, snapshots and the resultset class apply as they
 * do for find().
 *
 * ```php
 * $robots = Robots::findBySql(
 *     "WITH recent AS (SELECT * FROM robots WHERE year > :year)
 *      SELECT * FROM recent ORDER BY name",
 *     [
 *         "year" => 2000,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, findBySql)
{
	zend_ulong _17$$9;
	zend_bool keepSnapshots = 0, _10$$6, _22$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes, _7$$7, _11$$8, _19$$10, _23$$11, _32$$13;
	zval sql_zv, *bindParams_param = NULL, *bindTypes_param = NULL, __$null, container, manager, metaData, model, connection, result, columnMap, typesColumnMap, attribute, column, resultsetClassName, _0, _1, _2, _25, _33, _34, _3$$6, *_4$$6, _5$$6, *_6$$6, _9$$6, _8$$7, _12$$8, _13$$9, *_14$$9, _15$$9, *_16$$9, _21$$9, _20$$10, _24$$11, _26$$14, _27$$14, _28$$13, _29$$13, _30$$15, _31$$15;
	zend_string *sql = NULL, *_18$$9;

	ZVAL_UNDEF(&sql_zv);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&connection);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&typesColumnMap);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&resultsetClassName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_20$$10);
	ZVAL_UNDEF(&_24$$11);
	ZVAL_UNDEF(&_26$$14);
	ZVAL_UNDEF(&_27$$14);
	ZVAL_UNDEF(&_28$$13);
	ZVAL_UNDEF(&_29$$13);
	ZVAL_UNDEF(&_30$$15);
	ZVAL_UNDEF(&_31$$15);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_23$$11);
	ZVAL_UNDEF(&_32$$13);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(sql)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		bindParams_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		bindTypes_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&sql_zv);
	ZVAL_STR_COPY(&sql_zv, sql);
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
	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "modelsManager");
	ZEPHIR_CALL_METHOD(&_0, &container, "getShared", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "modelsMetadata");
	ZEPHIR_CALL_METHOD(&_0, &container, "getShared", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&metaData, &_0);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_get_called_class(&_1);
	ZEPHIR_CALL_METHOD(&model, &manager, "load", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&connection, &model, "getReadConnection", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&result, &connection, "query", NULL, 0, &sql_zv, &bindParams, &bindTypes);
	zephir_check_call_status();
	if (Z_TYPE_P(&result) != IS_OBJECT) {
		ZEPHIR_INIT_NVAR(&result);
		ZVAL_NULL(&result);
	}
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "orm.cast_on_hydrate");
	ZEPHIR_CALL_CE_STATIC(&_0, phalcon_support_settings_ce, "get", NULL, 0, &_2);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, &model);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&typesColumnMap, &metaData, "getDataTypes", NULL, 0, &model);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&column, &metaData, "getColumnMap", NULL, 0, &model);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&columnMap);
		if (Z_TYPE_P(&column) == IS_NULL) {
			array_init(&columnMap);
			ZEPHIR_CALL_METHOD(&_3$$6, &metaData, "getAttributes", NULL, 0, &model);
			zephir_check_call_status();
			if (Z_TYPE_P(&_3$$6) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_5$$6);
				zephir_string_to_char_array(&_5$$6, &_3$$6);
				_4$$6 = &_5$$6;
			} else {
				_4$$6 = &_3$$6;
			}
			zephir_is_iterable(_4$$6, 0, "phalcon/Mvc/Model.zep", 1943);
			if (Z_TYPE_P(_4$$6) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$6), _6$$6)
				{
					ZEPHIR_INIT_NVAR(&attribute);
					ZVAL_COPY(&attribute, _6$$6);
					ZEPHIR_INIT_NVAR(&_7$$7);
					zephir_create_array(&_7$$7, 2, 0);
					zephir_array_fast_append(&_7$$7, &attribute);
					ZEPHIR_OBS_NVAR(&_8$$7);
					zephir_array_fetch(&_8$$7, &typesColumnMap, &attribute, PH_NOISY, "phalcon/Mvc/Model.zep", 1941);
					zephir_array_fast_append(&_7$$7, &_8$$7);
					zephir_array_update_zval(&columnMap, &attribute, &_7$$7, PH_COPY | PH_SEPARATE);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$6, "rewind", NULL, 0);
				zephir_check_call_status();
				_10$$6 = 1;
				while (1) {
					if (_10$$6) {
						_10$$6 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$6, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_9$$6, _4$$6, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$6)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&attribute, _4$$6, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$8);
						zephir_create_array(&_11$$8, 2, 0);
						zephir_array_fast_append(&_11$$8, &attribute);
						ZEPHIR_OBS_NVAR(&_12$$8);
						zephir_array_fetch(&_12$$8, &typesColumnMap, &attribute, PH_NOISY, "phalcon/Mvc/Model.zep", 1941);
						zephir_array_fast_append(&_11$$8, &_12$$8);
						zephir_array_update_zval(&columnMap, &attribute, &_11$$8, PH_COPY | PH_SEPARATE);
				}
			}
			ZEPHIR_INIT_NVAR(&attribute);
		} else {
			array_init(&columnMap);
			ZEPHIR_CALL_METHOD(&_13$$9, &metaData, "getColumnMap", NULL, 0, &model);
			zephir_check_call_status();
			if (Z_TYPE_P(&_13$$9) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_15$$9);
				zephir_string_to_char_array(&_15$$9, &_13$$9);
				_14$$9 = &_15$$9;
			} else {
				_14$$9 = &_13$$9;
			}
			zephir_is_iterable(_14$$9, 0, "phalcon/Mvc/Model.zep", 1952);
			if (Z_TYPE_P(_14$$9) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_14$$9), _17$$9, _18$$9, _16$$9)
				{
					ZEPHIR_INIT_NVAR(&column);
					if (_18$$9 != NULL) { 
						ZVAL_STR_COPY(&column, _18$$9);
					} else {
						ZVAL_LONG(&column, _17$$9);
					}
					ZEPHIR_INIT_NVAR(&attribute);
					ZVAL_COPY(&attribute, _16$$9);
					ZEPHIR_INIT_NVAR(&_19$$10);
					zephir_create_array(&_19$$10, 2, 0);
					zephir_array_fast_append(&_19$$10, &attribute);
					ZEPHIR_OBS_NVAR(&_20$$10);
					zephir_array_fetch(&_20$$10, &typesColumnMap, &column, PH_NOISY, "phalcon/Mvc/Model.zep", 1950);
					zephir_array_fast_append(&_19$$10, &_20$$10);
					zephir_array_update_zval(&columnMap, &column, &_19$$10, PH_COPY | PH_SEPARATE);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _14$$9, "rewind", NULL, 0);
				zephir_check_call_status();
				_22$$9 = 1;
				while (1) {
					if (_22$$9) {
						_22$$9 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _14$$9, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_21$$9, _14$$9, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_21$$9)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&column, _14$$9, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&attribute, _14$$9, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_23$$11);
						zephir_create_array(&_23$$11, 2, 0);
						zephir_array_fast_append(&_23$$11, &attribute);
						ZEPHIR_OBS_NVAR(&_24$$11);
						zephir_array_fetch(&_24$$11, &typesColumnMap, &column, PH_NOISY, "phalcon/Mvc/Model.zep", 1950);
						zephir_array_fast_append(&_23$$11, &_24$$11);
						zephir_array_update_zval(&columnMap, &column, &_23$$11, PH_COPY | PH_SEPARATE);
				}
			}
			ZEPHIR_INIT_NVAR(&attribute);
			ZEPHIR_INIT_NVAR(&column);
		}
	}
	ZEPHIR_CALL_METHOD(&_25, &manager, "isKeepingSnapshots", NULL, 0, &model);
	zephir_check_call_status();
	keepSnapshots = zephir_get_boolval(&_25);
	if ((zephir_method_exists_ex(&model, ZEND_STRL("getresultsetclass")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(&resultsetClassName, &model, "getResultsetClass", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&resultsetClassName)) {
			if (UNEXPECTED(!(zephir_class_exists(&resultsetClassName, 1)))) {
				ZEPHIR_INIT_VAR(&_26$$14);
				object_init_ex(&_26$$14, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_VAR(&_27$$14);
				ZEPHIR_CONCAT_SVS(&_27$$14, "Resultset class \"", &resultsetClassName, "\" not found");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_26$$14, "__construct", NULL, 32, &_27$$14);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_26$$14, "phalcon/Mvc/Model.zep", 1964);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_VAR(&_28$$13);
			ZVAL_STRING(&_28$$13, "Phalcon\\Mvc\\Model\\ResultsetInterface");
			ZEPHIR_CALL_FUNCTION(&_29$$13, "is_subclass_of", NULL, 469, &resultsetClassName, &_28$$13);
			zephir_check_call_status();
			if (UNEXPECTED(!zephir_is_true(&_29$$13))) {
				ZEPHIR_INIT_VAR(&_30$$15);
				object_init_ex(&_30$$15, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_VAR(&_31$$15);
				ZEPHIR_CONCAT_SVS(&_31$$15, "Resultset class \"", &resultsetClassName, "\" must be an implementation of Phalcon\\Mvc\\Model\\ResultsetInterface");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_30$$15, "__construct", NULL, 32, &_31$$15);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_30$$15, "phalcon/Mvc/Model.zep", 1970);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_VAR(&_32$$13);
			zephir_create_array(&_32$$13, 5, 0);
			zephir_array_fast_append(&_32$$13, &columnMap);
			zephir_array_fast_append(&_32$$13, &model);
			zephir_array_fast_append(&_32$$13, &result);
			zephir_array_fast_append(&_32$$13, &__$null);
			ZEPHIR_INIT_NVAR(&_28$$13);
			ZVAL_BOOL(&_28$$13, keepSnapshots);
			zephir_array_fast_append(&_32$$13, &_28$$13);
			ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(return_value, &resultsetClassName, &_32$$13);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	object_init_ex(return_value, phalcon_mvc_model_resultset_simple_ce);
	ZVAL_NULL(&_33);
	if (keepSnapshots) {
		ZVAL_BOOL(&_34, 1);
	} else {
		ZVAL_BOOL(&_34, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 470, &columnMap, &model, &result, &_33, &_34);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Runs a native SQL statement and returns the first row as this model,
 * or null when there is none
 *
 * ```php
 * $robot = Robots::findFirstBySql(
 *     "SELECT * FROM robots WHERE name ILIKE :name LIMIT 1",
 *     [
 *         "name" => "astro%",
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, findFirstBySql)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes;
	zval sql_zv, *bindParams_param = NULL, *bindTypes_param = NULL, first, _0;
	zend_string *sql = NULL;

	ZVAL_UNDEF(&sql_zv);
	ZVAL_UNDEF(&first);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(sql)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		bindParams_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		bindTypes_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&sql_zv);
	ZVAL_STR_COPY(&sql_zv, sql);
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
	ZEPHIR_CALL_STATIC(&_0, "findBySql", NULL, 0, &sql_zv, &bindParams, &bindTypes);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&first, &_0, "getFirst", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&first) != IS_OBJECT) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&first);
}

/**
 * Fires an event, implicitly calls behaviors and listeners in the events
 * manager are notified
 */
PHP_METHOD(Phalcon_Mvc_Model, fireEvent)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval eventName_zv, _0;
	zend_string *eventName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventName_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(eventName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&eventName_zv);
	ZVAL_STR_COPY(&eventName_zv, eventName);
	if ((zephir_method_exists(this_ptr, &eventName_zv)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &eventName_zv, NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "notifyEvent", NULL, 0, &eventName_zv, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Fires an event, implicitly calls behaviors and listeners in the events
 * manager are notified
 * This method stops if one of the callbacks/listeners returns bool false
 */
PHP_METHOD(Phalcon_Mvc_Model, fireEventCancel)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval eventName_zv, _0$$3, _1;
	zend_string *eventName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventName_zv);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(eventName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&eventName_zv);
	ZVAL_STR_COPY(&eventName_zv, eventName);
	if ((zephir_method_exists(this_ptr, &eventName_zv)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD_ZVAL(&_0$$3, this_ptr, &eventName_zv, NULL, 0);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_0$$3)) {
			RETURN_MM_BOOL(0);
		}
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_1, "notifyEvent", NULL, 0, &eventName_zv, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns a list of changed values.
 *
 * ```php
 * $robots = Robots::findFirst();
 * print_r($robots->getChangedFields()); // []
 *
 * $robots->deleted = 'Y';
 *
 * $robots->getChangedFields();
 * print_r($robots->getChangedFields()); // ["deleted"]
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, getChangedFields)
{
	zend_bool _12;
	zend_string *_9;
	zend_ulong _8;
	zval changed;
	zval metaData, name, snapshot, columnMap, allAttributes, value, _0, *_4, _5, _6, *_7, _11, _1$$3, _2$$3, _3$$3, _10$$6, _13$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&allAttributes);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&changed);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("snapshot", 8, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 712, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&snapshot, &_0);
	if (UNEXPECTED(Z_TYPE_P(&snapshot) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_get_class(&_2$$3, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SVS(&_3$$3, "The 'keepSnapshots' option must be enabled to track changes in '", &_2$$3, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model.zep", 2091);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getReverseColumnMap", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (Z_TYPE_P(&columnMap) != IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&allAttributes, &metaData, "getDataTypes", NULL, 0, this_ptr);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&allAttributes, &columnMap);
	}
	ZEPHIR_INIT_VAR(&changed);
	array_init(&changed);
	if (Z_TYPE_P(&allAttributes) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &allAttributes);
		_4 = &_5;
	} else {
		_4 = &allAttributes;
	}
	ZEPHIR_INIT_VAR(&_6);
	zephir_is_iterable(_4, 0, "phalcon/Mvc/Model.zep", 2149);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _8, _9, _7)
		{
			ZEPHIR_INIT_NVAR(&name);
			if (_9 != NULL) { 
				ZVAL_STR_COPY(&name, _9);
			} else {
				ZVAL_LONG(&name, _8);
			}
			ZEPHIR_INIT_NVAR(&_6);
			ZVAL_COPY(&_6, _7);
			if (!(zephir_array_isset_value(&snapshot, &name))) {
				zephir_array_append(&changed, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2124);
				continue;
			}
			ZEPHIR_OBS_NVAR(&value);
			if (!(zephir_fetch_property_zval(&value, this_ptr, &name, PH_SILENT_CC))) {
				zephir_array_append(&changed, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2134);
				continue;
			}
			ZEPHIR_OBS_NVAR(&_10$$6);
			zephir_array_fetch(&_10$$6, &snapshot, &name, PH_NOISY, "phalcon/Mvc/Model.zep", 2142);
			if (!ZEPHIR_IS_IDENTICAL(&value, &_10$$6)) {
				zephir_array_append(&changed, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2143);
				continue;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&name, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_6, _4, "current", NULL, 0);
			zephir_check_call_status();
				if (!(zephir_array_isset_value(&snapshot, &name))) {
					zephir_array_append(&changed, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2124);
					continue;
				}
				ZEPHIR_OBS_NVAR(&value);
				if (!(zephir_fetch_property_zval(&value, this_ptr, &name, PH_SILENT_CC))) {
					zephir_array_append(&changed, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2134);
					continue;
				}
				ZEPHIR_OBS_NVAR(&_13$$10);
				zephir_array_fetch(&_13$$10, &snapshot, &name, PH_NOISY, "phalcon/Mvc/Model.zep", 2142);
				if (!ZEPHIR_IS_IDENTICAL(&value, &_13$$10)) {
					zephir_array_append(&changed, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2143);
					continue;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&_6);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CTOR(&changed);
}

/**
 * Returns one of the DIRTY_STATE_* constants telling if the record exists
 * in the database or not
 */
PHP_METHOD(Phalcon_Mvc_Model, getDirtyState)
{

	RETURN_MEMBER_TYPED(getThis(), "dirtyState", IS_LONG);
}

/**
 * Returns the custom events manager or null if there is no custom events manager
 */
PHP_METHOD(Phalcon_Mvc_Model, getEventsManager)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getCustomEventsManager", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns array of validation messages
 *
 *```php
 * $robot = new Robots();
 *
 * $robot->type = "mechanical";
 * $robot->name = "Astro Boy";
 * $robot->year = 1952;
 *
 * if ($robot->save() === false) {
 *     echo "Umh, We can't store robots right now ";
 *
 *     $messages = $robot->getMessages();
 *
 *     foreach ($messages as $message) {
 *         echo $message;
 *     }
 * } else {
 *     echo "Great, a new robot was saved successfully!";
 * }
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, getMessages)
{
	zend_bool _0, _1, _9$$3;
	zval filtered;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *filter = NULL, filter_sub, __$null, message, _2$$4, _3$$3, *_4$$3, _5$$3, *_6$$3, _8$$3, _7$$5, _10$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&filter_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&filtered);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("errorMessages", 13, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(filter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &filter);
	if (!filter) {
		filter = &filter_sub;
		ZEPHIR_CPY_WRT(filter, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(filter);
	}
	_0 = Z_TYPE_P(filter) == IS_STRING;
	if (!(_0)) {
		_0 = Z_TYPE_P(filter) == IS_ARRAY;
	}
	_1 = _0;
	if (_1) {
		_1 = !(ZEPHIR_IS_EMPTY(filter));
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&filtered);
		array_init(&filtered);
		if (Z_TYPE_P(filter) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_2$$4);
			zephir_create_array(&_2$$4, 1, 0);
			zephir_array_fast_append(&_2$$4, filter);
			ZEPHIR_CPY_WRT(filter, &_2$$4);
		}
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 713, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_3$$3) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_5$$3);
			zephir_string_to_char_array(&_5$$3, &_3$$3);
			_4$$3 = &_5$$3;
		} else {
			_4$$3 = &_3$$3;
		}
		zephir_is_iterable(_4$$3, 0, "phalcon/Mvc/Model.zep", 2213);
		if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
			{
				ZEPHIR_INIT_NVAR(&message);
				ZVAL_COPY(&message, _6$$3);
				ZEPHIR_CALL_METHOD(&_7$$5, &message, "getField", NULL, 0);
				zephir_check_call_status();
				if (zephir_fast_in_array(&_7$$5, filter)) {
					zephir_array_append(&filtered, &message, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2209);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_9$$3 = 1;
			while (1) {
				if (_9$$3) {
					_9$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_8$$3, _4$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_8$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&message, _4$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_10$$7, &message, "getField", NULL, 0);
					zephir_check_call_status();
					if (zephir_fast_in_array(&_10$$7, filter)) {
						zephir_array_append(&filtered, &message, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2209);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&message);
		RETURN_CTOR(&filtered);
	}
	RETURN_MM_MEMBER_TYPED(getThis(), "errorMessages", IS_ARRAY);
}

/**
 * Returns the models manager related to the entity instance
 */
PHP_METHOD(Phalcon_Mvc_Model, getModelsManager)
{

	RETURN_MEMBER(getThis(), "modelsManager");
}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Phalcon_Mvc_Model, getModelsMetaData)
{
	zval metaData, container, _0$$3, _1$$3, _2$$3, _3$$4, _4$$4, _5$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsMetaData", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("container", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&metaData);
	zephir_read_property_cached(&metaData, this_ptr, _zephir_prop_0, 716, PH_NOISY_CC);
	if (Z_TYPE_P(&metaData) == IS_NULL) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_1, 707, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&container, &_0$$3);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "modelsMetadata");
		ZEPHIR_CALL_METHOD(&_1$$3, &container, "getShared", NULL, 0, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&metaData, &_1$$3);
		if (UNEXPECTED(Z_TYPE_P(&metaData) != IS_OBJECT)) {
			ZEPHIR_INIT_VAR(&_3$$4);
			object_init_ex(&_3$$4, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_4$$4);
			zephir_get_class(&_4$$4, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_5$$4);
			ZEPHIR_CONCAT_SVS(&_5$$4, "The injected service 'modelsMetadata' is not valid in '", &_4$$4, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_3$$4, "__construct", NULL, 32, &_5$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_3$$4, "phalcon/Mvc/Model.zep", 2247);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 716, &metaData);
	}
	RETURN_CCTOR(&metaData);
}

/**
 * Returns the type of the latest operation performed by the ORM
 * Returns one of the OP_* class constants
 */
PHP_METHOD(Phalcon_Mvc_Model, getOperationMade)
{

	RETURN_MEMBER_TYPED(getThis(), "operationMade", IS_LONG);
}

/**
 * Returns the internal old snapshot data
 */
PHP_METHOD(Phalcon_Mvc_Model, getOldSnapshotData)
{

	RETURN_MEMBER_TYPED(getThis(), "oldSnapshot", IS_ARRAY);
}

/**
 * Gets the connection used to read data for the model
 */
PHP_METHOD(Phalcon_Mvc_Model, getReadConnection)
{
	zval _0, _2, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transaction", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 717, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) != IS_NULL) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 717, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_RETURN_CALL_METHOD(&_1$$3, "getConnection", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_2, "getReadConnection", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the DependencyInjection connection service name used to read data
 * related the model
 */
PHP_METHOD(Phalcon_Mvc_Model, getReadConnectionService)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getReadConnectionService", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns related records based on defined relations
 *
 * @param array arguments
 * @return \Phalcon\Mvc\Model\Resultset\Simple|false
 */
PHP_METHOD(Phalcon_Mvc_Model, getRelated)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval alias_zv, *arguments = NULL, arguments_sub, __$null, relation, className, manager, result, lowerAlias, _0, _1, _2$$3, _3$$3, _4$$4, _7$$4, _5$$5, _6$$5, _8$$6, _9$$6;
	zend_string *alias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&arguments_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&lowerAlias);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("dirtyRelated", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("related", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(alias)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(arguments)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		arguments = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	if (!arguments) {
		arguments = &arguments_sub;
		arguments = &__$null;
	}
	ZEPHIR_INIT_VAR(&className);
	zephir_get_class(&className, this_ptr, 0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_INIT_VAR(&lowerAlias);
	zephir_fast_strtolower(&lowerAlias, &alias_zv);
	ZEPHIR_CALL_METHOD(&_1, &manager, "getRelationByAlias", NULL, 0, &className, &lowerAlias);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&relation, &_1);
	if (UNEXPECTED(Z_TYPE_P(&relation) != IS_OBJECT)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SVSVS(&_3$$3, "There is no defined relations for the model '", &className, "' using alias '", &alias_zv, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Mvc/Model.zep", 2323);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (Z_TYPE_P(arguments) == IS_NULL) {
		zephir_read_property_cached(&_4$$4, this_ptr, _zephir_prop_1, 709, PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset_value(&_4$$4, &lowerAlias)) {
			zephir_read_property_cached(&_5$$5, this_ptr, _zephir_prop_1, 709, PH_NOISY_CC | PH_READONLY);
			zephir_memory_observe(&_6$$5);
			zephir_array_fetch(&_6$$5, &_5$$5, &lowerAlias, PH_NOISY, "phalcon/Mvc/Model.zep", 2348);
			RETURN_CCTOR(&_6$$5);
		}
		zephir_read_property_cached(&_7$$4, this_ptr, _zephir_prop_2, 710, PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset_value(&_7$$4, &lowerAlias)) {
			zephir_read_property_cached(&_8$$6, this_ptr, _zephir_prop_2, 710, PH_NOISY_CC | PH_READONLY);
			zephir_memory_observe(&_9$$6);
			zephir_array_fetch(&_9$$6, &_8$$6, &lowerAlias, PH_NOISY, "phalcon/Mvc/Model.zep", 2351);
			RETURN_CCTOR(&_9$$6);
		}
		ZEPHIR_CALL_METHOD(&result, &manager, "getRelationRecords", NULL, 0, &relation, this_ptr, arguments);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("related"), &lowerAlias, &result);
	} else {
		ZEPHIR_CALL_METHOD(&result, &manager, "getRelationRecords", NULL, 0, &relation, this_ptr, arguments);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&result);
}

/**
 * Checks if saved related records have already been loaded.
 *
 * Only returns true if the records were previously fetched
 * through the model without any additional parameters.
 *
 * ```php
 * $robot = Robots::findFirst();
 * var_dump($robot->isRelationshipLoaded('robotsParts')); // false
 *
 * $robotsParts = $robot->getRobotsParts(['id > 0']);
 * var_dump($robot->isRelationshipLoaded('robotsParts')); // false
 *
 * $robotsParts = $robot->getRobotsParts(); // or $robot->robotsParts
 * var_dump($robot->isRelationshipLoaded('robotsParts')); // true
 *
 * $robot->robotsParts = [new RobotsParts()];
 * var_dump($robot->isRelationshipLoaded('robotsParts')); // false
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, isRelationshipLoaded)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval relationshipAlias_zv, _0, _1;
	zend_string *relationshipAlias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&relationshipAlias_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("related", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(relationshipAlias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&relationshipAlias_zv);
	ZVAL_STR_COPY(&relationshipAlias_zv, relationshipAlias);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 710, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_strtolower(&_1, &relationshipAlias_zv);
	RETURN_MM_BOOL(zephir_array_isset_value(&_0, &_1));
}

/**
 * Returns schema name where the mapped table is located
 */
PHP_METHOD(Phalcon_Mvc_Model, getSchema)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getModelSchema", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the internal snapshot data
 */
PHP_METHOD(Phalcon_Mvc_Model, getSnapshotData)
{

	RETURN_MEMBER_TYPED(getThis(), "snapshot", IS_ARRAY);
}

/**
 * Returns the table name mapped in the model
 */
PHP_METHOD(Phalcon_Mvc_Model, getSource)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getModelSource", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns a list of updated values.
 *
 * ```php
 * $robots = Robots::findFirst();
 * print_r($robots->getChangedFields()); // []
 *
 * $robots->deleted = 'Y';
 *
 * $robots->getChangedFields();
 * print_r($robots->getChangedFields()); // ["deleted"]
 * $robots->save();
 * print_r($robots->getChangedFields()); // []
 * print_r($robots->getUpdatedFields()); // ["deleted"]
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, getUpdatedFields)
{
	zend_bool _16, _13$$6, _17$$8;
	zend_string *_12;
	zend_ulong _11;
	zval updated;
	zval name, snapshot, oldSnapshot, value, _0, _1, _2, *_9, *_10, _15, _3$$3, _4$$3, _5$$3, _6$$5, _7$$5, _8$$5, _14$$6, _18$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&oldSnapshot);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&updated);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("snapshot", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("oldSnapshot", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dirtyState", 10, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 712, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&snapshot, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 718, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&oldSnapshot, &_0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "orm.update_snapshot_on_save");
	ZEPHIR_CALL_CE_STATIC(&_1, phalcon_support_settings_ce, "get", NULL, 0, &_2);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_1))) {
		ZEPHIR_INIT_VAR(&_3$$3);
		object_init_ex(&_3$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_4$$3);
		zephir_get_class(&_4$$3, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_SVS(&_5$$3, "The 'updateSnapshotOnSave' option must be enabled for this method to work properly in '", &_4$$3, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "__construct", NULL, 32, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$3, "phalcon/Mvc/Model.zep", 2454);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(Z_TYPE_P(&snapshot) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The 'keepSnapshots' option must be enabled to track changes", "phalcon/Mvc/Model.zep", 2460);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 711, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_LONG(&_0, 0))) {
		ZEPHIR_INIT_VAR(&_6$$5);
		object_init_ex(&_6$$5, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_7$$5);
		zephir_get_class(&_7$$5, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_8$$5);
		ZEPHIR_CONCAT_SVS(&_8$$5, "Change checking cannot be performed because the object has not been persisted or is deleted in '", &_7$$5, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_6$$5, "__construct", NULL, 32, &_8$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$5, "phalcon/Mvc/Model.zep", 2469);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&updated);
	array_init(&updated);
	if (Z_TYPE_P(&snapshot) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_2);
		zephir_string_to_char_array(&_2, &snapshot);
		_9 = &_2;
	} else {
		_9 = &snapshot;
	}
	zephir_is_iterable(_9, 0, "phalcon/Mvc/Model.zep", 2484);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _11, _12, _10)
		{
			ZEPHIR_INIT_NVAR(&name);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&name, _12);
			} else {
				ZVAL_LONG(&name, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _10);
			_13$$6 = !(zephir_array_isset_value(&oldSnapshot, &name));
			if (!(_13$$6)) {
				ZEPHIR_OBS_NVAR(&_14$$6);
				zephir_array_fetch(&_14$$6, &oldSnapshot, &name, PH_NOISY, "phalcon/Mvc/Model.zep", 2479);
				_13$$6 = !ZEPHIR_IS_IDENTICAL(&value, &_14$$6);
			}
			if (_13$$6) {
				zephir_array_append(&updated, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2480);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&name, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _9, "current", NULL, 0);
			zephir_check_call_status();
				_17$$8 = !(zephir_array_isset_value(&oldSnapshot, &name));
				if (!(_17$$8)) {
					ZEPHIR_OBS_NVAR(&_18$$8);
					zephir_array_fetch(&_18$$8, &oldSnapshot, &name, PH_NOISY, "phalcon/Mvc/Model.zep", 2479);
					_17$$8 = !ZEPHIR_IS_IDENTICAL(&value, &_18$$8);
				}
				if (_17$$8) {
					zephir_array_append(&updated, &name, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2480);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CTOR(&updated);
}

/**
 * Gets the connection used to write data to the model
 */
PHP_METHOD(Phalcon_Mvc_Model, getWriteConnection)
{
	zval _0, _2, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("transaction", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 717, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) != IS_NULL) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 717, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_RETURN_CALL_METHOD(&_1$$3, "getConnection", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_2, "getWriteConnection", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the DependencyInjection connection service name used to write
 * data related to the model
 */
PHP_METHOD(Phalcon_Mvc_Model, getWriteConnectionService)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "getWriteConnectionService", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check if a specific attribute has changed
 * This only works if the model is keeping data snapshots
 *
 *```php
 * $robot = new Robots();
 *
 * $robot->type = "mechanical";
 * $robot->name = "Astro Boy";
 * $robot->year = 1952;
 *
 * $robot->create();
 *
 * $robot->type = "hydraulic";
 *
 * $hasChanged = $robot->hasChanged("type"); // returns true
 * $hasChanged = $robot->hasChanged(["type", "name"]); // returns true
 * $hasChanged = $robot->hasChanged(["type", "name"], true); // returns false
 *```
 *
 * @param string|array fieldName
 * @param boolean allFields
 */
PHP_METHOD(Phalcon_Mvc_Model, hasChanged)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool allFields, _0$$5;
	zval *fieldName = NULL, fieldName_sub, *allFields_param = NULL, __$null, changedFields, intersect;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fieldName_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&changedFields);
	ZVAL_UNDEF(&intersect);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(fieldName)
		Z_PARAM_BOOL(allFields)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &fieldName, &allFields_param);
	if (!fieldName) {
		fieldName = &fieldName_sub;
		fieldName = &__$null;
	}
	if (!allFields_param) {
		allFields = 0;
	} else {
		}
	ZEPHIR_CALL_METHOD(&changedFields, this_ptr, "getChangedFields", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(fieldName) == IS_STRING) {
		RETURN_MM_BOOL(zephir_fast_in_array(fieldName, &changedFields));
	}
	if (Z_TYPE_P(fieldName) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&intersect, "array_intersect", NULL, 471, fieldName, &changedFields);
		zephir_check_call_status();
		if (allFields) {
			_0$$5 = ZEPHIR_IS_EQUAL(&intersect, fieldName);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM_BOOL(_0$$5);
		}
		RETURN_MM_BOOL(zephir_fast_count_int(&intersect) > 0);
	}
	RETURN_MM_BOOL(zephir_fast_count_int(&changedFields) > 0);
}

/**
 * Checks if the object has internal snapshot data
 */
PHP_METHOD(Phalcon_Mvc_Model, hasSnapshotData)
{
	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("snapshot", 8, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 712, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(!(ZEPHIR_IS_EMPTY(&_0)));
}

/**
 * Check if a specific attribute was updated
 * This only works if the model is keeping data snapshots
 *
 * @param string|array fieldName
 */
PHP_METHOD(Phalcon_Mvc_Model, hasUpdated)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool allFields, _0$$5;
	zval *fieldName = NULL, fieldName_sub, *allFields_param = NULL, __$null, updatedFields, intersect;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fieldName_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&updatedFields);
	ZVAL_UNDEF(&intersect);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(fieldName)
		Z_PARAM_BOOL(allFields)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &fieldName, &allFields_param);
	if (!fieldName) {
		fieldName = &fieldName_sub;
		fieldName = &__$null;
	}
	if (!allFields_param) {
		allFields = 0;
	} else {
		}
	ZEPHIR_CALL_METHOD(&updatedFields, this_ptr, "getUpdatedFields", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(fieldName) == IS_STRING) {
		RETURN_MM_BOOL(zephir_fast_in_array(fieldName, &updatedFields));
	}
	if (Z_TYPE_P(fieldName) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&intersect, "array_intersect", NULL, 471, fieldName, &updatedFields);
		zephir_check_call_status();
		if (allFields) {
			_0$$5 = ZEPHIR_IS_EQUAL(&intersect, fieldName);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM_BOOL(_0$$5);
		}
		RETURN_MM_BOOL(zephir_fast_count_int(&intersect) > 0);
	}
	RETURN_MM_BOOL(zephir_fast_count_int(&updatedFields) > 0);
}

/**
 * Serializes the object for json_encode
 *
 *```php
 * echo json_encode($robot);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, jsonSerialize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "toArray", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the maximum value of a column for a result-set of rows that match
 * the specified conditions
 *
 * ```php
 * // What is the maximum robot id?
 * $id = Robots::maximum(
 *     [
 *         "column" => "id",
 *     ]
 * );
 *
 * echo "The maximum robot id is: ", $id, "\n";
 *
 * // What is the maximum id of mechanical robots?
 * $sum = Robots::maximum(
 *     [
 *         "type = 'mechanical'",
 *         "column" => "id",
 *     ]
 * );
 *
 * echo "The maximum robot id of mechanical robots is ", $id, "\n";
 * ```
 *
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, maximum)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, parameters_sub, __$null, _0, _1;

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "MAX");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "maximum");
	ZEPHIR_RETURN_CALL_SELF("groupResult", NULL, 0, &_0, &_1, parameters);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the minimum value of a column for a result-set of rows that match
 * the specified conditions
 *
 * ```php
 * // What is the minimum robot id?
 * $id = Robots::minimum(
 *     [
 *         "column" => "id",
 *     ]
 * );
 *
 * echo "The minimum robot id is: ", $id;
 *
 * // What is the minimum id of mechanical robots?
 * $sum = Robots::minimum(
 *     [
 *         "type = 'mechanical'",
 *         "column" => "id",
 *     ]
 * );
 *
 * echo "The minimum robot id of mechanical robots is ", $id;
 * ```
 *
 * @param array parameters
 */
PHP_METHOD(Phalcon_Mvc_Model, minimum)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, parameters_sub, __$null, _0, _1;

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "MIN");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "minimum");
	ZEPHIR_RETURN_CALL_SELF("groupResult", NULL, 0, &_0, &_1, parameters);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Create a criteria for a specific model
 */
PHP_METHOD(Phalcon_Mvc_Model, query)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container = NULL, container_sub, __$null, criteria, _2, _0$$4, _1$$4;

	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&criteria);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &container);
	if (!container) {
		container = &container_sub;
		ZEPHIR_CPY_WRT(container, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(container);
	}
	if (Z_TYPE_P(container) != IS_OBJECT) {
		ZEPHIR_CALL_CE_STATIC(container, phalcon_di_di_ce, "getDefault", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&criteria);
	if (zephir_instance_of_ev(container, phalcon_di_diinterface_ce)) {
		ZEPHIR_INIT_VAR(&_1$$4);
		ZVAL_STRING(&_1$$4, "Phalcon\\Mvc\\Model\\Criteria");
		ZEPHIR_CALL_METHOD(&_0$$4, container, "get", NULL, 0, &_1$$4);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&criteria, &_0$$4);
	} else {
		object_init_ex(&criteria, phalcon_mvc_model_criteria_ce);
		if (zephir_has_constructor(&criteria)) {
			ZEPHIR_CALL_METHOD(NULL, &criteria, "__construct", NULL, 0);
			zephir_check_call_status();
		}

		ZEPHIR_CALL_METHOD(NULL, &criteria, "setDI", NULL, 472, container);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_2);
	zephir_get_called_class(&_2);
	ZEPHIR_CALL_METHOD(NULL, &criteria, "setModelName", NULL, 473, &_2);
	zephir_check_call_status();
	RETURN_CCTOR(&criteria);
}

/**
 * Reads an attribute value by its name
 *
 * ```php
 * echo $robot->readAttribute("name");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model, readAttribute)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval attribute_zv, _0;
	zend_string *attribute = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attribute_zv);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(attribute)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&attribute_zv);
	ZVAL_STR_COPY(&attribute_zv, attribute);
	if (!(zephir_isset_property_value_zval(this_ptr, &attribute_zv))) {
		RETURN_MM_NULL();
	}
	zephir_memory_observe(&_0);
	zephir_read_property_zval(&_0, this_ptr, &attribute_zv, PH_NOISY_CC);
	RETURN_CCTOR(&_0);
}

/**
 * Refreshes the model attributes re-querying the record from the database
 */
PHP_METHOD(Phalcon_Mvc_Model, refresh)
{
	zend_bool _19;
	zval fields, _21, _17$$9, _20$$10;
	zval metaData, readConnection, schema, source, table, uniqueKey, tables, uniqueParams, dialect, row, attribute, manager, columnMap, _0, _4, _13, *_14, _15, *_16, _18, _22, _23, _26, _1$$3, _2$$3, _3$$3, _5$$6, _9$$6, _6$$7, _7$$7, _8$$7, _10$$8, _11$$8, _12$$8, _24$$11, _25$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&readConnection);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&uniqueKey);
	ZVAL_UNDEF(&tables);
	ZVAL_UNDEF(&uniqueParams);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_24$$11);
	ZVAL_UNDEF(&_25$$11);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_20$$10);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("uniqueKey", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("uniqueParams", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("uniqueTypes", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 711, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_LONG(&_0, 0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_get_class(&_2$$3, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SVS(&_3$$3, "The record cannot be refreshed because it does not exist or is deleted in '", &_2$$3, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model.zep", 2735);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&readConnection, this_ptr, "getReadConnection", NULL, 474);
	zephir_check_call_status();
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_1, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_4);
	ZEPHIR_CALL_METHOD(&schema, this_ptr, "getSchema", NULL, 464);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, this_ptr, "getSource", NULL, 465);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		ZEPHIR_INIT_VAR(&table);
		zephir_create_array(&table, 2, 0);
		zephir_array_fast_append(&table, &schema);
		zephir_array_fast_append(&table, &source);
	} else {
		ZEPHIR_CPY_WRT(&table, &source);
	}
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_2, 719, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&uniqueKey, &_4);
	if (!(zephir_is_true(&uniqueKey))) {
		ZEPHIR_CALL_METHOD(&_5$$6, this_ptr, "has", NULL, 0, &metaData, &readConnection);
		zephir_check_call_status();
		if (UNEXPECTED(!zephir_is_true(&_5$$6))) {
			ZEPHIR_INIT_VAR(&_6$$7);
			object_init_ex(&_6$$7, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_7$$7);
			zephir_get_class(&_7$$7, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_8$$7);
			ZEPHIR_CONCAT_SVS(&_8$$7, "The record cannot be refreshed because it does not exist or is deleted in '", &_7$$7, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_6$$7, "__construct", NULL, 32, &_8$$7);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_6$$7, "phalcon/Mvc/Model.zep", 2760);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_9$$6, this_ptr, _zephir_prop_2, 719, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&uniqueKey, &_9$$6);
	}
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_3, 720, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&uniqueParams, &_4);
	if (UNEXPECTED(Z_TYPE_P(&uniqueParams) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(&_10$$8);
		object_init_ex(&_10$$8, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_11$$8);
		zephir_get_class(&_11$$8, this_ptr, 0);
		ZEPHIR_INIT_VAR(&_12$$8);
		ZEPHIR_CONCAT_SVS(&_12$$8, "The record cannot be refreshed because it does not exist or is deleted in '", &_11$$8, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_10$$8, "__construct", NULL, 32, &_12$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_10$$8, "phalcon/Mvc/Model.zep", 2771);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&fields);
	array_init(&fields);
	ZEPHIR_CALL_METHOD(&_13, &metaData, "getAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (Z_TYPE_P(&_13) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_15);
		zephir_string_to_char_array(&_15, &_13);
		_14 = &_15;
	} else {
		_14 = &_13;
	}
	zephir_is_iterable(_14, 0, "phalcon/Mvc/Model.zep", 2786);
	if (Z_TYPE_P(_14) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_14), _16)
		{
			ZEPHIR_INIT_NVAR(&attribute);
			ZVAL_COPY(&attribute, _16);
			ZEPHIR_INIT_NVAR(&_17$$9);
			zephir_create_array(&_17$$9, 1, 0);
			zephir_array_fast_append(&_17$$9, &attribute);
			zephir_array_append(&fields, &_17$$9, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2780);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _14, "rewind", NULL, 0);
		zephir_check_call_status();
		_19 = 1;
		while (1) {
			if (_19) {
				_19 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _14, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_18, _14, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_18)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&attribute, _14, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_20$$10);
				zephir_create_array(&_20$$10, 1, 0);
				zephir_array_fast_append(&_20$$10, &attribute);
				zephir_array_append(&fields, &_20$$10, PH_SEPARATE, "phalcon/Mvc/Model.zep", 2780);
		}
	}
	ZEPHIR_INIT_NVAR(&attribute);
	ZEPHIR_CALL_METHOD(&dialect, &readConnection, "getDialect", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_21);
	zephir_create_array(&_21, 3, 0);
	zephir_array_update_string(&_21, SL("columns"), &fields, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_22, &readConnection, "escapeIdentifier", NULL, 0, &table);
	zephir_check_call_status();
	zephir_array_update_string(&_21, SL("tables"), &_22, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_21, SL("where"), &uniqueKey, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&tables, &dialect, "select", NULL, 0, &_21);
	zephir_check_call_status();
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_4, 721, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_23, 2);
	ZEPHIR_CALL_METHOD(&row, &readConnection, "fetchOne", NULL, 0, &tables, &_23, &uniqueParams, &_4);
	zephir_check_call_status();
	if (Z_TYPE_P(&row) == IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, this_ptr);
		zephir_check_call_status();
		ZVAL_NULL(&_24$$11);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "assign", NULL, 0, &row, &_24$$11, &columnMap);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_25$$11, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
		zephir_check_call_status();
		if (zephir_is_true(&_25$$11)) {
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setSnapshotData", NULL, 0, &row, &columnMap);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setOldSnapshotData", NULL, 0, &row, &columnMap);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_VAR(&_26);
	ZVAL_STRING(&_26, "afterFetch");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_26);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Inserts or updates a model instance. Returning true on success or false
 * otherwise.
 *
 *```php
 * // Creating a new robot
 * $robot = new Robots();
 *
 * $robot->type = "mechanical";
 * $robot->name = "Astro Boy";
 * $robot->year = 1952;
 *
 * $robot->save();
 *
 * // Updating a robot name
 * $robot = Robots::findFirst("id = 100");
 *
 * $robot->name = "Biomass";
 *
 * $robot->save();
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, save)
{
	zval visited;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&visited);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&visited);
	object_init_ex(&visited, phalcon_support_collection_ce);
	ZEPHIR_CALL_METHOD(NULL, &visited, "__construct", NULL, 22);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "doSave", NULL, 0, &visited);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Inserted or updates model instance, expects a visited list of objects.
 *
 * @param CollectionInterface $visited
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model, doSave)
{
	zend_bool hasRelatedToSave = 0, _12, _20$$21;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *visited, visited_sub, metaData, schema, writeConnection, readConnection, source, table, identityField, exists, success, relatedToSave, objId, manager, savedSnapshot, savedOldSnapshot, _0, _1, _5, _11, _13, _14, _17, _2$$4, _3$$8, _4$$9, _6$$11, _7$$10, _8$$10, _9$$12, _10$$12, _15$$16, _16$$18, _18$$20, _19$$21, _21$$21, _22$$21, _23$$24, _24$$23, _25$$23;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&visited_sub);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&writeConnection);
	ZVAL_UNDEF(&readConnection);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&identityField);
	ZVAL_UNDEF(&exists);
	ZVAL_UNDEF(&success);
	ZVAL_UNDEF(&relatedToSave);
	ZVAL_UNDEF(&objId);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&savedSnapshot);
	ZVAL_UNDEF(&savedOldSnapshot);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$8);
	ZVAL_UNDEF(&_4$$9);
	ZVAL_UNDEF(&_6$$11);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_8$$10);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_10$$12);
	ZVAL_UNDEF(&_15$$16);
	ZVAL_UNDEF(&_16$$18);
	ZVAL_UNDEF(&_18$$20);
	ZVAL_UNDEF(&_19$$21);
	ZVAL_UNDEF(&_21$$21);
	ZVAL_UNDEF(&_22$$21);
	ZVAL_UNDEF(&_23$$24);
	ZVAL_UNDEF(&_24$$23);
	ZVAL_UNDEF(&_25$$23);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("operationMade", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("errorMessages", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("snapshot", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("oldSnapshot", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("dirtyRelated", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("related", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(visited, phalcon_support_collection_collectioninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &visited);
	ZEPHIR_INIT_VAR(&savedSnapshot);
	ZEPHIR_INIT_VAR(&savedOldSnapshot);
	ZEPHIR_CALL_FUNCTION(&objId, "spl_object_id", NULL, 475, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, visited, "has", NULL, 0, &objId);
	zephir_check_call_status();
	if (ZEPHIR_IS_TRUE_IDENTICAL(&_0)) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_CALL_METHOD(NULL, visited, "set", NULL, 0, &objId, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&writeConnection, this_ptr, "getWriteConnection", NULL, 462);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "prepareSave");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&relatedToSave, this_ptr, "collectRelatedToSave", NULL, 0);
	zephir_check_call_status();
	hasRelatedToSave = zephir_fast_count_int(&relatedToSave) > 0;
	if (hasRelatedToSave) {
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "preSaveRelatedRecords", NULL, 0, &writeConnection, &relatedToSave, visited);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_2$$4)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_METHOD(&schema, this_ptr, "getSchema", NULL, 464);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, this_ptr, "getSource", NULL, 465);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		ZEPHIR_INIT_VAR(&table);
		zephir_create_array(&table, 2, 0);
		zephir_array_fast_append(&table, &schema);
		zephir_array_fast_append(&table, &source);
	} else {
		ZEPHIR_CPY_WRT(&table, &source);
	}
	ZEPHIR_CALL_METHOD(&readConnection, this_ptr, "getReadConnection", NULL, 474);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&exists, this_ptr, "has", NULL, 0, &metaData, &readConnection);
	zephir_check_call_status();
	if (zephir_is_true(&exists)) {
		ZVAL_UNDEF(&_3$$8);
		ZVAL_LONG(&_3$$8, 2);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 714, &_3$$8);
	} else {
		ZVAL_UNDEF(&_4$$9);
		ZVAL_LONG(&_4$$9, 1);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 714, &_4$$9);
	}
	ZEPHIR_INIT_NVAR(&_1);
	array_init(&_1);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 713, &_1);
	ZEPHIR_CALL_METHOD(&identityField, &metaData, "getIdentityField", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "preSave", NULL, 0, &metaData, &exists, &identityField);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_5)) {
		if (hasRelatedToSave) {
			ZVAL_BOOL(&_6$$11, 0);
			ZEPHIR_CALL_METHOD(NULL, &writeConnection, "rollback", NULL, 0, &_6$$11);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(&_8$$10);
		ZVAL_STRING(&_8$$10, "orm.exception_on_failed_save");
		ZEPHIR_CALL_CE_STATIC(&_7$$10, phalcon_support_settings_ce, "get", NULL, 0, &_8$$10);
		zephir_check_call_status();
		if (UNEXPECTED(zephir_is_true(&_7$$10))) {
			ZEPHIR_INIT_VAR(&_9$$12);
			object_init_ex(&_9$$12, phalcon_mvc_model_validationfailed_ce);
			ZEPHIR_CALL_METHOD(&_10$$12, this_ptr, "getMessages", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_9$$12, "__construct", NULL, 476, this_ptr, &_10$$12);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_9$$12, "phalcon/Mvc/Model.zep", 2961);
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&manager, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_11, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
	zephir_check_call_status();
	_12 = zephir_is_true(&_11);
	if (_12) {
		ZEPHIR_INIT_VAR(&_14);
		ZVAL_STRING(&_14, "orm.update_snapshot_on_save");
		ZEPHIR_CALL_CE_STATIC(&_13, phalcon_support_settings_ce, "get", NULL, 0, &_14);
		zephir_check_call_status();
		_12 = zephir_is_true(&_13);
	}
	if (_12) {
		ZEPHIR_OBS_NVAR(&savedSnapshot);
		zephir_read_property_cached(&savedSnapshot, this_ptr, _zephir_prop_2, 712, PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(&savedOldSnapshot);
		zephir_read_property_cached(&savedOldSnapshot, this_ptr, _zephir_prop_3, 718, PH_NOISY_CC);
	}
	if (zephir_is_true(&exists)) {
		ZEPHIR_CALL_METHOD(&success, this_ptr, "doLowUpdate", NULL, 0, &metaData, &writeConnection, &table);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&success, this_ptr, "doLowInsert", NULL, 0, &metaData, &writeConnection, &table, &identityField);
		zephir_check_call_status();
	}
	if (ZEPHIR_IS_TRUE_IDENTICAL(&success)) {
		ZVAL_UNDEF(&_15$$16);
		ZVAL_LONG(&_15$$16, 0);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 711, &_15$$16);
	}
	if (hasRelatedToSave) {
		if (ZEPHIR_IS_FALSE_IDENTICAL(&success)) {
			ZVAL_BOOL(&_16$$18, 0);
			ZEPHIR_CALL_METHOD(NULL, &writeConnection, "rollback", NULL, 0, &_16$$18);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&success, this_ptr, "postSaveRelatedRecords", NULL, 0, &writeConnection, &relatedToSave, visited);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&_14);
	ZVAL_STRING(&_14, "orm.events");
	ZEPHIR_CALL_CE_STATIC(&_17, phalcon_support_settings_ce, "get", NULL, 0, &_14);
	zephir_check_call_status();
	if (zephir_is_true(&_17)) {
		ZEPHIR_CALL_METHOD(&_18$$20, this_ptr, "postSave", NULL, 0, &success, &exists);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&success, &_18$$20);
	}
	if (ZEPHIR_IS_FALSE_IDENTICAL(&success)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "cancelOperation", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_19$$21, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
		zephir_check_call_status();
		_20$$21 = zephir_is_true(&_19$$21);
		if (_20$$21) {
			ZEPHIR_INIT_VAR(&_22$$21);
			ZVAL_STRING(&_22$$21, "orm.update_snapshot_on_save");
			ZEPHIR_CALL_CE_STATIC(&_21$$21, phalcon_support_settings_ce, "get", NULL, 0, &_22$$21);
			zephir_check_call_status();
			_20$$21 = zephir_is_true(&_21$$21);
		}
		if (_20$$21) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 712, &savedSnapshot);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 718, &savedOldSnapshot);
		}
	} else {
		if (hasRelatedToSave) {
			ZEPHIR_INIT_VAR(&_23$$24);
			array_init(&_23$$24);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 709, &_23$$24);
		}
		ZEPHIR_INIT_VAR(&_24$$23);
		array_init(&_24$$23);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 710, &_24$$23);
		ZEPHIR_INIT_VAR(&_25$$23);
		ZVAL_STRING(&_25$$23, "afterSave");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_25$$23);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&success);
}

/**
 * Serializes the object ignoring connections, services, related objects or
 * static properties
 */
PHP_METHOD(Phalcon_Mvc_Model, serialize)
{
	zval _7;
	zend_bool _3, _4, _5;
	zval attributes, manager, dirtyState, snapshot, _0, _1, _2, _6$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&dirtyState);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("snapshot", 8, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&snapshot);
	ZVAL_NULL(&snapshot);
	ZVAL_NULL(&_0);
	ZVAL_BOOL(&_1, 0);
	ZEPHIR_CALL_METHOD(&attributes, this_ptr, "toArray", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 711, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&dirtyState, &_0);
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_2);
	ZEPHIR_CALL_METHOD(&_2, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
	zephir_check_call_status();
	_3 = zephir_is_true(&_2);
	if (_3) {
		zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
		_3 = Z_TYPE_P(&_0) != IS_NULL;
	}
	_4 = _3;
	if (_4) {
		zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
		_5 = !ZEPHIR_IS_EQUAL(&attributes, &_1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		_4 = _5;
	}
	if (_4) {
		zephir_read_property_cached(&_6$$3, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&snapshot, &_6$$3);
	}
	ZEPHIR_INIT_VAR(&_7);
	zephir_create_array(&_7, 3, 0);
	zephir_array_update_string(&_7, SL("attributes"), &attributes, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_7, SL("snapshot"), &snapshot, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_7, SL("dirtyState"), &dirtyState, PH_COPY | PH_SEPARATE);
	ZEPHIR_RETURN_CALL_FUNCTION("serialize", NULL, 14, &_7);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Unserializes the object from a serialized string
 */
PHP_METHOD(Phalcon_Mvc_Model, unserialize)
{
	zend_bool _17$$8;
	zend_ulong _12$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval data_zv, attributes, container, manager, key, value, snapshot, properties, dirtyState, _0$$4, _1$$5, _2$$5, _3$$5, _4$$3, _5$$3, _6$$6, _7$$6, _8$$6, *_9$$8, _10$$8, *_11$$8, _16$$8, _14$$9, _15$$9, _18$$13, _19$$13, _20$$20;
	zend_string *data = NULL, *_13$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_zv);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&properties);
	ZVAL_UNDEF(&dirtyState);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$13);
	ZVAL_UNDEF(&_20$$20);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("snapshot", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&data_zv);
	ZVAL_STR_COPY(&data_zv, data);
	ZEPHIR_CALL_FUNCTION(&attributes, "unserialize", NULL, 15, &data_zv);
	zephir_check_call_status();
	if (Z_TYPE_P(&attributes) == IS_ARRAY) {
		if (!(zephir_array_isset_value_string(&attributes, SL("attributes")))) {
			ZEPHIR_INIT_VAR(&_0$$4);
			zephir_create_array(&_0$$4, 1, 0);
			zephir_array_update_string(&_0$$4, SL("attributes"), &attributes, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&attributes, &_0$$4);
		}
		ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&container) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$5);
			object_init_ex(&_1$$5, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_2$$5);
			zephir_get_class(&_2$$5, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_3$$5);
			ZEPHIR_CONCAT_SVS(&_3$$5, "A dependency injection container is required to access the services related to the ODM in '", &_2$$5, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_1$$5, "__construct", NULL, 32, &_3$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_1$$5, "phalcon/Mvc/Model.zep", 3102);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 707, &container);
		ZEPHIR_INIT_VAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "modelsManager");
		ZEPHIR_CALL_METHOD(&_4$$3, &container, "getShared", NULL, 0, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&manager, &_4$$3);
		if (UNEXPECTED(Z_TYPE_P(&manager) != IS_OBJECT)) {
			ZEPHIR_INIT_VAR(&_6$$6);
			object_init_ex(&_6$$6, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_7$$6);
			zephir_get_class(&_7$$6, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_8$$6);
			ZEPHIR_CONCAT_SVS(&_8$$6, "The injected service 'modelsManager' is not valid in '", &_7$$6, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_6$$6, "__construct", NULL, 32, &_8$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_6$$6, "phalcon/Mvc/Model.zep", 3118);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 708, &manager);
		ZEPHIR_CALL_METHOD(NULL, &manager, "initialize", NULL, 0, this_ptr);
		zephir_check_call_status();
		if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("onconstruct")) == SUCCESS)) {
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "onConstruct", NULL, 0);
			zephir_check_call_status();
		}
		zephir_memory_observe(&properties);
		if (zephir_array_isset_string_fetch(&properties, &attributes, SL("attributes"), 0)) {
			if (Z_TYPE_P(&properties) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_10$$8);
				zephir_string_to_char_array(&_10$$8, &properties);
				_9$$8 = &_10$$8;
			} else {
				_9$$8 = &properties;
			}
			zephir_is_iterable(_9$$8, 0, "phalcon/Mvc/Model.zep", 3157);
			if (Z_TYPE_P(_9$$8) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9$$8), _12$$8, _13$$8, _11$$8)
				{
					ZEPHIR_INIT_NVAR(&key);
					if (_13$$8 != NULL) { 
						ZVAL_STR_COPY(&key, _13$$8);
					} else {
						ZVAL_LONG(&key, _12$$8);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _11$$8);

					/* try_start_1: */

						zephir_update_property_zval_zval(this_ptr, &key, &value);

					try_end_1:

					if (EG(exception)) {
						ZEPHIR_INIT_NVAR(&_14$$9);
						ZVAL_OBJ(&_14$$9, EG(exception));
						Z_ADDREF_P(&_14$$9);
						ZEPHIR_INIT_NVAR(&_15$$9);
						if (zephir_is_instance_of(&_14$$9, SL("TypeError"))) {
							zend_clear_exception();
							ZEPHIR_CPY_WRT(&_15$$9, &_14$$9);
						} else {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9$$8, "rewind", NULL, 0);
				zephir_check_call_status();
				_17$$8 = 1;
				while (1) {
					if (_17$$8) {
						_17$$8 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _9$$8, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_16$$8, _9$$8, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_16$$8)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&key, _9$$8, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, _9$$8, "current", NULL, 0);
					zephir_check_call_status();

						/* try_start_2: */

							zephir_update_property_zval_zval(this_ptr, &key, &value);

						try_end_2:

						if (EG(exception)) {
							ZEPHIR_INIT_NVAR(&_18$$13);
							ZVAL_OBJ(&_18$$13, EG(exception));
							Z_ADDREF_P(&_18$$13);
							ZEPHIR_INIT_NVAR(&_19$$13);
							if (zephir_is_instance_of(&_18$$13, SL("TypeError"))) {
								zend_clear_exception();
								ZEPHIR_CPY_WRT(&_19$$13, &_18$$13);
							} else {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&key);
		} else {
			ZEPHIR_INIT_NVAR(&properties);
			array_init(&properties);
		}
		zephir_memory_observe(&dirtyState);
		if (zephir_array_isset_string_fetch(&dirtyState, &attributes, SL("dirtyState"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 711, &dirtyState);
		}
		ZEPHIR_CALL_METHOD(&_4$$3, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
		zephir_check_call_status();
		if (zephir_is_true(&_4$$3)) {
			zephir_memory_observe(&snapshot);
			if (zephir_array_isset_string_fetch(&snapshot, &attributes, SL("snapshot"), 0)) {
				ZEPHIR_INIT_VAR(&_20$$20);
				if (Z_TYPE_P(&snapshot) != IS_NULL) {
					ZEPHIR_CPY_WRT(&_20$$20, &snapshot);
				} else {
					ZEPHIR_CPY_WRT(&_20$$20, &properties);
				}
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 712, &_20$$20);
			} else {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 712, &properties);
			}
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the DependencyInjection connection service name
 */
PHP_METHOD(Phalcon_Mvc_Model, setConnectionService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval connectionService_zv, _0;
	zend_string *connectionService = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&connectionService_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(connectionService)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&connectionService_zv);
	ZVAL_STR_COPY(&connectionService_zv, connectionService);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setConnectionService", NULL, 0, this_ptr, &connectionService_zv);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the dirty state of the object using one of the DIRTY_STATE_* constants
 */
PHP_METHOD(Phalcon_Mvc_Model, setDirtyState)
{
	zval *dirtyState_param = NULL, _0;
	zend_long dirtyState;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(dirtyState)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &dirtyState_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, dirtyState);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 711, &_0);
	RETURN_THISW();
}

/**
 * Sets a custom events manager
 */
PHP_METHOD(Phalcon_Mvc_Model, setEventsManager)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *eventsManager, eventsManager_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventsManager_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(eventsManager, phalcon_events_managerinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &eventsManager);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setCustomEventsManager", NULL, 0, this_ptr, eventsManager);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the DependencyInjection connection service name used to read data
 */
PHP_METHOD(Phalcon_Mvc_Model, setReadConnectionService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval connectionService_zv, _0;
	zend_string *connectionService = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&connectionService_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(connectionService)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&connectionService_zv);
	ZVAL_STR_COPY(&connectionService_zv, connectionService);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setReadConnectionService", NULL, 0, this_ptr, &connectionService_zv);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the record's old snapshot data.
 * This method is used internally to set old snapshot data when the model
 * was set up to keep snapshot data
 *
 * @param array data
 * @param array columnMap
 */
PHP_METHOD(Phalcon_Mvc_Model, setOldSnapshotData)
{
	zend_bool _16$$3;
	zend_string *_2$$3;
	zend_ulong _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *columnMap = NULL, columnMap_sub, __$null, key, value, attribute, *_0$$3, _15$$3, _3$$6, _5$$6, _6$$7, _7$$7, _8$$7, _10$$9, _11$$9, _12$$10, _13$$10, _14$$10, _17$$13, _18$$13, _19$$14, _20$$14, _21$$14, _22$$16, _23$$16, _24$$17, _25$$17, _26$$17;
	zval data, snapshot;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&columnMap_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_22$$16);
	ZVAL_UNDEF(&_23$$16);
	ZVAL_UNDEF(&_24$$17);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$17);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("oldSnapshot", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(columnMap)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &data_param, &columnMap);
	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);
	if (!columnMap) {
		columnMap = &columnMap_sub;
		columnMap = &__$null;
	}
	if (Z_TYPE_P(columnMap) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&snapshot);
		array_init(&snapshot);
		zephir_is_iterable(&data, 0, "phalcon/Mvc/Model.zep", 3277);
		if (Z_TYPE_P(&data) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _1$$3, _2$$3, _0$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_2$$3 != NULL) { 
					ZVAL_STR_COPY(&key, _2$$3);
				} else {
					ZVAL_LONG(&key, _1$$3);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _0$$3);
				if (Z_TYPE_P(&key) != IS_STRING) {
					continue;
				}
				ZEPHIR_OBS_NVAR(&attribute);
				if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
					ZEPHIR_INIT_NVAR(&_5$$6);
					ZVAL_STRING(&_5$$6, "orm.ignore_unknown_columns");
					ZEPHIR_CALL_CE_STATIC(&_3$$6, phalcon_support_settings_ce, "get", &_4, 0, &_5$$6);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_3$$6))) {
						ZEPHIR_INIT_NVAR(&_6$$7);
						object_init_ex(&_6$$7, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_7$$7);
						zephir_get_class(&_7$$7, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_8$$7);
						ZEPHIR_CONCAT_SVSVS(&_8$$7, "Column '", &key, "' does not make part of the column map in '", &_7$$7, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_6$$7, "__construct", &_9, 32, &_8$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_6$$7, "phalcon/Mvc/Model.zep", 3257);
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
				if (Z_TYPE_P(&attribute) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attribute);
					if (!(zephir_array_isset_long_fetch(&attribute, &attribute, 0, 0))) {
						ZEPHIR_INIT_NVAR(&_11$$9);
						ZVAL_STRING(&_11$$9, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_10$$9, phalcon_support_settings_ce, "get", &_4, 0, &_11$$9);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_10$$9))) {
							ZEPHIR_INIT_NVAR(&_12$$10);
							object_init_ex(&_12$$10, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_13$$10);
							zephir_get_class(&_13$$10, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_14$$10);
							ZEPHIR_CONCAT_SVSVS(&_14$$10, "Column '", &key, "' does not make part of the column map in '", &_13$$10, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_12$$10, "__construct", &_9, 32, &_14$$10);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_12$$10, "phalcon/Mvc/Model.zep", 3268);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				}
				zephir_array_update_zval(&snapshot, &attribute, &value, PH_COPY | PH_SEPARATE);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
			zephir_check_call_status();
			_16$$3 = 1;
			while (1) {
				if (_16$$3) {
					_16$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_15$$3, &data, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_15$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, &data, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&key) != IS_STRING) {
						continue;
					}
					ZEPHIR_OBS_NVAR(&attribute);
					if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
						ZEPHIR_INIT_NVAR(&_18$$13);
						ZVAL_STRING(&_18$$13, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_17$$13, phalcon_support_settings_ce, "get", &_4, 0, &_18$$13);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_17$$13))) {
							ZEPHIR_INIT_NVAR(&_19$$14);
							object_init_ex(&_19$$14, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_20$$14);
							zephir_get_class(&_20$$14, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_21$$14);
							ZEPHIR_CONCAT_SVSVS(&_21$$14, "Column '", &key, "' does not make part of the column map in '", &_20$$14, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_19$$14, "__construct", &_9, 32, &_21$$14);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_19$$14, "phalcon/Mvc/Model.zep", 3257);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
					if (Z_TYPE_P(&attribute) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attribute);
						if (!(zephir_array_isset_long_fetch(&attribute, &attribute, 0, 0))) {
							ZEPHIR_INIT_NVAR(&_23$$16);
							ZVAL_STRING(&_23$$16, "orm.ignore_unknown_columns");
							ZEPHIR_CALL_CE_STATIC(&_22$$16, phalcon_support_settings_ce, "get", &_4, 0, &_23$$16);
							zephir_check_call_status();
							if (UNEXPECTED(!zephir_is_true(&_22$$16))) {
								ZEPHIR_INIT_NVAR(&_24$$17);
								object_init_ex(&_24$$17, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_25$$17);
								zephir_get_class(&_25$$17, this_ptr, 0);
								ZEPHIR_INIT_NVAR(&_26$$17);
								ZEPHIR_CONCAT_SVSVS(&_26$$17, "Column '", &key, "' does not make part of the column map in '", &_25$$17, "'");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_24$$17, "__construct", &_9, 32, &_26$$17);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_24$$17, "phalcon/Mvc/Model.zep", 3268);
								ZEPHIR_MM_RESTORE();
								return;
							}
							continue;
						}
					}
					zephir_array_update_zval(&snapshot, &attribute, &value, PH_COPY | PH_SEPARATE);
			}
		}
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
	} else {
		if (UNEXPECTED(Z_TYPE_P(&data) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&data, "snapshot", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&snapshot, &data);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 718, &snapshot);
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the record's snapshot data.
 * This method is used internally to set snapshot data when the model was
 * set up to keep snapshot data
 *
 * @param array columnMap
 */
PHP_METHOD(Phalcon_Mvc_Model, setSnapshotData)
{
	zend_bool _21$$3, _3$$4, _22$$12;
	zend_string *_2$$3;
	zend_ulong _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_8 = NULL, *_14 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *columnMap = NULL, columnMap_sub, __$null, key, value, attribute, *_0$$3, _20$$3, _4$$4, _6$$4, _7$$6, _9$$7, _10$$7, _11$$8, _12$$8, _13$$8, _15$$10, _16$$10, _17$$11, _18$$11, _19$$11, _23$$12, _24$$12, _25$$14, _26$$15, _27$$15, _28$$16, _29$$16, _30$$16, _31$$18, _32$$18, _33$$19, _34$$19, _35$$19;
	zval data, snapshot;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&columnMap_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_19$$11);
	ZVAL_UNDEF(&_23$$12);
	ZVAL_UNDEF(&_24$$12);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_27$$15);
	ZVAL_UNDEF(&_28$$16);
	ZVAL_UNDEF(&_29$$16);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_31$$18);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_33$$19);
	ZVAL_UNDEF(&_34$$19);
	ZVAL_UNDEF(&_35$$19);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("snapshot", 8, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(columnMap)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &data_param, &columnMap);
	ZEPHIR_OBS_COPY_OR_DUP(&data, data_param);
	if (!columnMap) {
		columnMap = &columnMap_sub;
		columnMap = &__$null;
	}
	if (Z_TYPE_P(columnMap) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&snapshot);
		array_init(&snapshot);
		zephir_is_iterable(&data, 0, "phalcon/Mvc/Model.zep", 3342);
		if (Z_TYPE_P(&data) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&data), _1$$3, _2$$3, _0$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_2$$3 != NULL) { 
					ZVAL_STR_COPY(&key, _2$$3);
				} else {
					ZVAL_LONG(&key, _1$$3);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _0$$3);
				if (Z_TYPE_P(&key) != IS_STRING) {
					continue;
				}
				_3$$4 = !(zephir_array_isset_value(columnMap, &key));
				if (_3$$4) {
					ZEPHIR_INIT_NVAR(&_6$$4);
					ZVAL_STRING(&_6$$4, "orm.case_insensitive_column_map");
					ZEPHIR_CALL_CE_STATIC(&_4$$4, phalcon_support_settings_ce, "get", &_5, 0, &_6$$4);
					zephir_check_call_status();
					_3$$4 = zephir_is_true(&_4$$4);
				}
				if (_3$$4) {
					ZEPHIR_CALL_SELF(&_7$$6, "caseInsensitiveColumnMap", &_8, 461, columnMap, &key);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&key, &_7$$6);
				}
				ZEPHIR_OBS_NVAR(&attribute);
				if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
					ZEPHIR_INIT_NVAR(&_10$$7);
					ZVAL_STRING(&_10$$7, "orm.ignore_unknown_columns");
					ZEPHIR_CALL_CE_STATIC(&_9$$7, phalcon_support_settings_ce, "get", &_5, 0, &_10$$7);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_9$$7))) {
						ZEPHIR_INIT_NVAR(&_11$$8);
						object_init_ex(&_11$$8, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_12$$8);
						zephir_get_class(&_12$$8, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_13$$8);
						ZEPHIR_CONCAT_SVSVS(&_13$$8, "Column '", &key, "' does not make part of the column map in '", &_12$$8, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_11$$8, "__construct", &_14, 32, &_13$$8);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_11$$8, "phalcon/Mvc/Model.zep", 3322);
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
				if (Z_TYPE_P(&attribute) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attribute);
					if (!(zephir_array_isset_long_fetch(&attribute, &attribute, 0, 0))) {
						ZEPHIR_INIT_NVAR(&_16$$10);
						ZVAL_STRING(&_16$$10, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_15$$10, phalcon_support_settings_ce, "get", &_5, 0, &_16$$10);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_15$$10))) {
							ZEPHIR_INIT_NVAR(&_17$$11);
							object_init_ex(&_17$$11, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_18$$11);
							zephir_get_class(&_18$$11, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_19$$11);
							ZEPHIR_CONCAT_SVSVS(&_19$$11, "Column '", &key, "' does not make part of the column map in '", &_18$$11, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_17$$11, "__construct", &_14, 32, &_19$$11);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_17$$11, "phalcon/Mvc/Model.zep", 3333);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				}
				zephir_array_update_zval(&snapshot, &attribute, &value, PH_COPY | PH_SEPARATE);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &data, "rewind", NULL, 0);
			zephir_check_call_status();
			_21$$3 = 1;
			while (1) {
				if (_21$$3) {
					_21$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, &data, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_20$$3, &data, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_20$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, &data, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&value, &data, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&key) != IS_STRING) {
						continue;
					}
					_22$$12 = !(zephir_array_isset_value(columnMap, &key));
					if (_22$$12) {
						ZEPHIR_INIT_NVAR(&_24$$12);
						ZVAL_STRING(&_24$$12, "orm.case_insensitive_column_map");
						ZEPHIR_CALL_CE_STATIC(&_23$$12, phalcon_support_settings_ce, "get", &_5, 0, &_24$$12);
						zephir_check_call_status();
						_22$$12 = zephir_is_true(&_23$$12);
					}
					if (_22$$12) {
						ZEPHIR_CALL_SELF(&_25$$14, "caseInsensitiveColumnMap", &_8, 461, columnMap, &key);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&key, &_25$$14);
					}
					ZEPHIR_OBS_NVAR(&attribute);
					if (!(zephir_array_isset_fetch(&attribute, columnMap, &key, 0))) {
						ZEPHIR_INIT_NVAR(&_27$$15);
						ZVAL_STRING(&_27$$15, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_26$$15, phalcon_support_settings_ce, "get", &_5, 0, &_27$$15);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_26$$15))) {
							ZEPHIR_INIT_NVAR(&_28$$16);
							object_init_ex(&_28$$16, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_29$$16);
							zephir_get_class(&_29$$16, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_30$$16);
							ZEPHIR_CONCAT_SVSVS(&_30$$16, "Column '", &key, "' does not make part of the column map in '", &_29$$16, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_28$$16, "__construct", &_14, 32, &_30$$16);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_28$$16, "phalcon/Mvc/Model.zep", 3322);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
					if (Z_TYPE_P(&attribute) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attribute);
						if (!(zephir_array_isset_long_fetch(&attribute, &attribute, 0, 0))) {
							ZEPHIR_INIT_NVAR(&_32$$18);
							ZVAL_STRING(&_32$$18, "orm.ignore_unknown_columns");
							ZEPHIR_CALL_CE_STATIC(&_31$$18, phalcon_support_settings_ce, "get", &_5, 0, &_32$$18);
							zephir_check_call_status();
							if (UNEXPECTED(!zephir_is_true(&_31$$18))) {
								ZEPHIR_INIT_NVAR(&_33$$19);
								object_init_ex(&_33$$19, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_34$$19);
								zephir_get_class(&_34$$19, this_ptr, 0);
								ZEPHIR_INIT_NVAR(&_35$$19);
								ZEPHIR_CONCAT_SVSVS(&_35$$19, "Column '", &key, "' does not make part of the column map in '", &_34$$19, "'");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_33$$19, "__construct", &_14, 32, &_35$$19);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_33$$19, "phalcon/Mvc/Model.zep", 3333);
								ZEPHIR_MM_RESTORE();
								return;
							}
							continue;
						}
					}
					zephir_array_update_zval(&snapshot, &attribute, &value, PH_COPY | PH_SEPARATE);
			}
		}
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
	} else {
		if (UNEXPECTED(Z_TYPE_P(&data) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&data, "snapshot", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&snapshot, &data);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 712, &snapshot);
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets a transaction related to the Model instance
 *
 *```php
 * use Phalcon\Mvc\Model\Transaction\Manager as TxManager;
 * use Phalcon\Mvc\Model\Transaction\Failed as TxFailed;
 *
 * try {
 *     $txManager = new TxManager();
 *
 *     $transaction = $txManager->get();
 *
 *     $robot = new Robots();
 *
 *     $robot->setTransaction($transaction);
 *
 *     $robot->name       = "WALL·E";
 *     $robot->created_at = date("Y-m-d");
 *
 *     if ($robot->save() === false) {
 *         $transaction->rollback("Can't save robot");
 *     }
 *
 *     $robotPart = new RobotParts();
 *
 *     $robotPart->setTransaction($transaction);
 *
 *     $robotPart->type = "head";
 *
 *     if ($robotPart->save() === false) {
 *         $transaction->rollback("Robot part cannot be saved");
 *     }
 *
 *     $transaction->commit();
 * } catch (TxFailed $e) {
 *     echo "Failed, reason: ", $e->getMessage();
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, setTransaction)
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 717, transaction);
	RETURN_THISW();
}

PHP_METHOD(Phalcon_Mvc_Model, getTransaction)
{

	RETURN_MEMBER(getThis(), "transaction");
}

/**
 * Enables/disables options in the ORM
 */
PHP_METHOD(Phalcon_Mvc_Model, setup)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *options_param = NULL, disableEvents, columnRenaming, notNullValidations, exceptionOnFailedSave, exceptionOnFailedMetaDataSave, phqlLiterals, virtualForeignKeys, lateStateBinding, castOnHydrate, ignoreUnknownColumns, updateSnapshotOnSave, disableAssignSetters, caseInsensitiveColumnMap, prefetchRecords, lastInsertId, nativeCompiler, _0$$3, _1$$4, _2$$5, _3$$6, _4$$7, _5$$8, _6$$9, _7$$10, _8$$11, _9$$12, _10$$13, _11$$14, _12$$15, _13$$16, _14$$17, _15$$18;
	zval options;

	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&disableEvents);
	ZVAL_UNDEF(&columnRenaming);
	ZVAL_UNDEF(&notNullValidations);
	ZVAL_UNDEF(&exceptionOnFailedSave);
	ZVAL_UNDEF(&exceptionOnFailedMetaDataSave);
	ZVAL_UNDEF(&phqlLiterals);
	ZVAL_UNDEF(&virtualForeignKeys);
	ZVAL_UNDEF(&lateStateBinding);
	ZVAL_UNDEF(&castOnHydrate);
	ZVAL_UNDEF(&ignoreUnknownColumns);
	ZVAL_UNDEF(&updateSnapshotOnSave);
	ZVAL_UNDEF(&disableAssignSetters);
	ZVAL_UNDEF(&caseInsensitiveColumnMap);
	ZVAL_UNDEF(&prefetchRecords);
	ZVAL_UNDEF(&lastInsertId);
	ZVAL_UNDEF(&nativeCompiler);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_10$$13);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_12$$15);
	ZVAL_UNDEF(&_13$$16);
	ZVAL_UNDEF(&_14$$17);
	ZVAL_UNDEF(&_15$$18);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &options_param);
	ZEPHIR_OBS_COPY_OR_DUP(&options, options_param);
	zephir_memory_observe(&disableEvents);
	if (zephir_array_isset_string_fetch(&disableEvents, &options, SL("events"), 0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "orm.events");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_0$$3, &disableEvents);
		zephir_check_call_status();
	}
	zephir_memory_observe(&virtualForeignKeys);
	if (zephir_array_isset_string_fetch(&virtualForeignKeys, &options, SL("virtualForeignKeys"), 0)) {
		ZEPHIR_INIT_VAR(&_1$$4);
		ZVAL_STRING(&_1$$4, "orm.virtual_foreign_keys");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_1$$4, &virtualForeignKeys);
		zephir_check_call_status();
	}
	zephir_memory_observe(&columnRenaming);
	if (zephir_array_isset_string_fetch(&columnRenaming, &options, SL("columnRenaming"), 0)) {
		ZEPHIR_INIT_VAR(&_2$$5);
		ZVAL_STRING(&_2$$5, "orm.column_renaming");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_2$$5, &columnRenaming);
		zephir_check_call_status();
	}
	zephir_memory_observe(&notNullValidations);
	if (zephir_array_isset_string_fetch(&notNullValidations, &options, SL("notNullValidations"), 0)) {
		ZEPHIR_INIT_VAR(&_3$$6);
		ZVAL_STRING(&_3$$6, "orm.not_null_validations");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_3$$6, &notNullValidations);
		zephir_check_call_status();
	}
	zephir_memory_observe(&exceptionOnFailedSave);
	if (zephir_array_isset_string_fetch(&exceptionOnFailedSave, &options, SL("exceptionOnFailedSave"), 0)) {
		ZEPHIR_INIT_VAR(&_4$$7);
		ZVAL_STRING(&_4$$7, "orm.exception_on_failed_save");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_4$$7, &exceptionOnFailedSave);
		zephir_check_call_status();
	}
	zephir_memory_observe(&exceptionOnFailedMetaDataSave);
	if (zephir_array_isset_string_fetch(&exceptionOnFailedMetaDataSave, &options, SL("exceptionOnFailedMetaDataSave"), 0)) {
		ZEPHIR_INIT_VAR(&_5$$8);
		ZVAL_STRING(&_5$$8, "orm.exception_on_failed_metadata_save");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_5$$8, &exceptionOnFailedMetaDataSave);
		zephir_check_call_status();
	}
	zephir_memory_observe(&phqlLiterals);
	if (zephir_array_isset_string_fetch(&phqlLiterals, &options, SL("phqlLiterals"), 0)) {
		ZEPHIR_INIT_VAR(&_6$$9);
		ZVAL_STRING(&_6$$9, "orm.enable_literals");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_6$$9, &phqlLiterals);
		zephir_check_call_status();
	}
	zephir_memory_observe(&nativeCompiler);
	if (zephir_array_isset_string_fetch(&nativeCompiler, &options, SL("nativeCompiler"), 0)) {
		ZEPHIR_INIT_VAR(&_7$$10);
		ZVAL_STRING(&_7$$10, "orm.native_compiler");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_7$$10, &nativeCompiler);
		zephir_check_call_status();
	}
	zephir_memory_observe(&lateStateBinding);
	if (zephir_array_isset_string_fetch(&lateStateBinding, &options, SL("lateStateBinding"), 0)) {
		ZEPHIR_INIT_VAR(&_8$$11);
		ZVAL_STRING(&_8$$11, "orm.late_state_binding");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_8$$11, &lateStateBinding);
		zephir_check_call_status();
	}
	zephir_memory_observe(&castOnHydrate);
	if (zephir_array_isset_string_fetch(&castOnHydrate, &options, SL("castOnHydrate"), 0)) {
		ZEPHIR_INIT_VAR(&_9$$12);
		ZVAL_STRING(&_9$$12, "orm.cast_on_hydrate");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_9$$12, &castOnHydrate);
		zephir_check_call_status();
	}
	zephir_memory_observe(&ignoreUnknownColumns);
	if (zephir_array_isset_string_fetch(&ignoreUnknownColumns, &options, SL("ignoreUnknownColumns"), 0)) {
		ZEPHIR_INIT_VAR(&_10$$13);
		ZVAL_STRING(&_10$$13, "orm.ignore_unknown_columns");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_10$$13, &ignoreUnknownColumns);
		zephir_check_call_status();
	}
	zephir_memory_observe(&caseInsensitiveColumnMap);
	if (zephir_array_isset_string_fetch(&caseInsensitiveColumnMap, &options, SL("caseInsensitiveColumnMap"), 0)) {
		ZEPHIR_INIT_VAR(&_11$$14);
		ZVAL_STRING(&_11$$14, "orm.case_insensitive_column_map");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_11$$14, &caseInsensitiveColumnMap);
		zephir_check_call_status();
	}
	zephir_memory_observe(&updateSnapshotOnSave);
	if (zephir_array_isset_string_fetch(&updateSnapshotOnSave, &options, SL("updateSnapshotOnSave"), 0)) {
		ZEPHIR_INIT_VAR(&_12$$15);
		ZVAL_STRING(&_12$$15, "orm.update_snapshot_on_save");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_12$$15, &updateSnapshotOnSave);
		zephir_check_call_status();
	}
	zephir_memory_observe(&disableAssignSetters);
	if (zephir_array_isset_string_fetch(&disableAssignSetters, &options, SL("disableAssignSetters"), 0)) {
		ZEPHIR_INIT_VAR(&_13$$16);
		ZVAL_STRING(&_13$$16, "orm.disable_assign_setters");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_13$$16, &disableAssignSetters);
		zephir_check_call_status();
	}
	zephir_memory_observe(&prefetchRecords);
	if (zephir_array_isset_string_fetch(&prefetchRecords, &options, SL("prefetchRecords"), 0)) {
		ZEPHIR_INIT_VAR(&_14$$17);
		ZVAL_STRING(&_14$$17, "orm.resultset_prefetch_records");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_14$$17, &prefetchRecords);
		zephir_check_call_status();
	}
	zephir_memory_observe(&lastInsertId);
	if (zephir_array_isset_string_fetch(&lastInsertId, &options, SL("castLastInsertIdToInt"), 0)) {
		ZEPHIR_INIT_VAR(&_15$$18);
		ZVAL_STRING(&_15$$18, "orm.cast_last_insert_id_to_int");
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_support_settings_ce, "set", NULL, 0, &_15$$18, &lastInsertId);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the DependencyInjection connection service name used to write data
 */
PHP_METHOD(Phalcon_Mvc_Model, setWriteConnectionService)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval connectionService_zv, _0;
	zend_string *connectionService = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&connectionService_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(connectionService)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&connectionService_zv);
	ZVAL_STR_COPY(&connectionService_zv, connectionService);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setWriteConnectionService", NULL, 0, this_ptr, &connectionService_zv);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Skips the current operation forcing a success state
 */
PHP_METHOD(Phalcon_Mvc_Model, skipOperation)
{
	zval *skip_param = NULL, __$true, __$false;
	zend_bool skip;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("skipped", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(skip)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &skip_param);
	if (skip) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 715, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 715, &__$false);
	}
}

/**
 * Calculates the sum on a column for a result-set of rows that match the
 * specified conditions
 *
 * ```php
 * // How much are all robots?
 * $sum = Robots::sum(
 *     [
 *         "column" => "price",
 *     ]
 * );
 *
 * echo "The total price of robots is ", $sum, "\n";
 *
 * // How much are mechanical robots?
 * $sum = Robots::sum(
 *     [
 *         "type = 'mechanical'",
 *         "column" => "price",
 *     ]
 * );
 *
 * echo "The total price of mechanical robots is  ", $sum, "\n";
 * ```
 *
 * @param array parameters
 * @return double | ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, sum)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, parameters_sub, __$null, _0, _1;

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &parameters);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "SUM");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "sumatory");
	ZEPHIR_RETURN_CALL_SELF("groupResult", NULL, 0, &_0, &_1, parameters);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the instance as an array representation
 *
 *```php
 * print_r(
 *     $robot->toArray()
 * );
 *```
 *
 * @param array $columns
 */
PHP_METHOD(Phalcon_Mvc_Model, toArray)
{
	zend_bool _25, _4$$4, _17$$3, _19$$3, _26$$18, _36$$17, _38$$17;
	zval data;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_9 = NULL, *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *columns = NULL, columns_sub, *useGetter = NULL, useGetter_sub, __$null, __$true, attribute, attributeField, columnMap, metaData, method, _0, *_1, _2, *_3, _24, _5$$4, _7$$4, _8$$5, _10$$6, _11$$6, _12$$7, _13$$7, _14$$7, _16$$3, _18$$3, _20$$12, _21$$11, _22$$11, _23$$15, _27$$18, _28$$18, _29$$19, _30$$20, _31$$20, _32$$21, _33$$21, _34$$21, _35$$17, _37$$17, _39$$26, _40$$25, _41$$25, _42$$29;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&columns_sub);
	ZVAL_UNDEF(&useGetter_sub);
	ZVAL_NULL(&__$null);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_18$$3);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$11);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_27$$18);
	ZVAL_UNDEF(&_28$$18);
	ZVAL_UNDEF(&_29$$19);
	ZVAL_UNDEF(&_30$$20);
	ZVAL_UNDEF(&_31$$20);
	ZVAL_UNDEF(&_32$$21);
	ZVAL_UNDEF(&_33$$21);
	ZVAL_UNDEF(&_34$$21);
	ZVAL_UNDEF(&_35$$17);
	ZVAL_UNDEF(&_37$$17);
	ZVAL_UNDEF(&_39$$26);
	ZVAL_UNDEF(&_40$$25);
	ZVAL_UNDEF(&_41$$25);
	ZVAL_UNDEF(&_42$$29);
	ZVAL_UNDEF(&data);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(columns)
		Z_PARAM_ZVAL(useGetter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &columns, &useGetter);
	if (!columns) {
		columns = &columns_sub;
		columns = &__$null;
	}
	if (!useGetter) {
		useGetter = &useGetter_sub;
		useGetter = &__$true;
	}
	ZEPHIR_INIT_VAR(&data);
	array_init(&data);
	ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &metaData, "getAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model.zep", 3649);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&attribute);
			ZVAL_COPY(&attribute, _3);
			if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
				_4$$4 = !(zephir_array_isset_value(&columnMap, &attribute));
				if (_4$$4) {
					ZEPHIR_INIT_NVAR(&_7$$4);
					ZVAL_STRING(&_7$$4, "orm.case_insensitive_column_map");
					ZEPHIR_CALL_CE_STATIC(&_5$$4, phalcon_support_settings_ce, "get", &_6, 0, &_7$$4);
					zephir_check_call_status();
					_4$$4 = zephir_is_true(&_5$$4);
				}
				if (_4$$4) {
					ZEPHIR_CALL_SELF(&_8$$5, "caseInsensitiveColumnMap", &_9, 461, &columnMap, &attribute);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&attribute, &_8$$5);
				}
				ZEPHIR_OBS_NVAR(&attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, &columnMap, &attribute, 0))) {
					ZEPHIR_INIT_NVAR(&_11$$6);
					ZVAL_STRING(&_11$$6, "orm.ignore_unknown_columns");
					ZEPHIR_CALL_CE_STATIC(&_10$$6, phalcon_support_settings_ce, "get", &_6, 0, &_11$$6);
					zephir_check_call_status();
					if (UNEXPECTED(!zephir_is_true(&_10$$6))) {
						ZEPHIR_INIT_NVAR(&_12$$7);
						object_init_ex(&_12$$7, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_13$$7);
						zephir_get_class(&_13$$7, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_14$$7);
						ZEPHIR_CONCAT_SVSVS(&_14$$7, "Column '", &attribute, "' does not make part of the column map in '", &_13$$7, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_12$$7, "__construct", &_15, 32, &_14$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_12$$7, "phalcon/Mvc/Model.zep", 3607);
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
			} else {
				ZEPHIR_CPY_WRT(&attributeField, &attribute);
			}
			if (Z_TYPE_P(columns) == IS_ARRAY) {
				if (!(zephir_fast_in_array(&attributeField, columns))) {
					continue;
				}
			}
			ZEPHIR_INIT_NVAR(&_16$$3);
			zephir_camelize(&_16$$3, &attributeField, NULL );
			ZEPHIR_INIT_NVAR(&method);
			ZEPHIR_CONCAT_SV(&method, "get", &_16$$3);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			_17$$3 = ZEPHIR_IS_TRUE_IDENTICAL(useGetter);
			if (_17$$3) {
				ZEPHIR_INIT_NVAR(&_18$$3);
				ZVAL_STRING(&_18$$3, "getSource");
				_17$$3 = !ZEPHIR_IS_IDENTICAL(&_18$$3, &method);
			}
			_19$$3 = _17$$3;
			if (_19$$3) {
				_19$$3 = (zephir_method_exists(this_ptr, &method)  == SUCCESS);
			}
			if (_19$$3) {

				/* try_start_1: */

					ZEPHIR_CALL_METHOD_ZVAL(&_20$$12, this_ptr, &method, NULL, 0);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_array_update_zval(&data, &attributeField, &_20$$12, PH_COPY | PH_SEPARATE);

				try_end_1:

				if (EG(exception)) {
					ZEPHIR_INIT_NVAR(&_21$$11);
					ZVAL_OBJ(&_21$$11, EG(exception));
					Z_ADDREF_P(&_21$$11);
					ZEPHIR_INIT_NVAR(&_22$$11);
					if (zephir_is_instance_of(&_21$$11, SL("Error"))) {
						zend_clear_exception();
						ZEPHIR_CPY_WRT(&_22$$11, &_21$$11);
						zephir_array_update_zval(&data, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
					} else {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			} else if (zephir_isset_property_value_zval(this_ptr, &attributeField)) {
				ZEPHIR_OBS_NVAR(&_23$$15);
				zephir_read_property_zval(&_23$$15, this_ptr, &attributeField, PH_NOISY_CC);
				zephir_array_update_zval(&data, &attributeField, &_23$$15, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&data, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_25 = 1;
		while (1) {
			if (_25) {
				_25 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_24, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_24)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&attribute, _1, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					_26$$18 = !(zephir_array_isset_value(&columnMap, &attribute));
					if (_26$$18) {
						ZEPHIR_INIT_NVAR(&_28$$18);
						ZVAL_STRING(&_28$$18, "orm.case_insensitive_column_map");
						ZEPHIR_CALL_CE_STATIC(&_27$$18, phalcon_support_settings_ce, "get", &_6, 0, &_28$$18);
						zephir_check_call_status();
						_26$$18 = zephir_is_true(&_27$$18);
					}
					if (_26$$18) {
						ZEPHIR_CALL_SELF(&_29$$19, "caseInsensitiveColumnMap", &_9, 461, &columnMap, &attribute);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&attribute, &_29$$19);
					}
					ZEPHIR_OBS_NVAR(&attributeField);
					if (!(zephir_array_isset_fetch(&attributeField, &columnMap, &attribute, 0))) {
						ZEPHIR_INIT_NVAR(&_31$$20);
						ZVAL_STRING(&_31$$20, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_30$$20, phalcon_support_settings_ce, "get", &_6, 0, &_31$$20);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_30$$20))) {
							ZEPHIR_INIT_NVAR(&_32$$21);
							object_init_ex(&_32$$21, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_33$$21);
							zephir_get_class(&_33$$21, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_34$$21);
							ZEPHIR_CONCAT_SVSVS(&_34$$21, "Column '", &attribute, "' does not make part of the column map in '", &_33$$21, "'");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_32$$21, "__construct", &_15, 32, &_34$$21);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_32$$21, "phalcon/Mvc/Model.zep", 3607);
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &attribute);
				}
				if (Z_TYPE_P(columns) == IS_ARRAY) {
					if (!(zephir_fast_in_array(&attributeField, columns))) {
						continue;
					}
				}
				ZEPHIR_INIT_NVAR(&_35$$17);
				zephir_camelize(&_35$$17, &attributeField, NULL );
				ZEPHIR_INIT_NVAR(&method);
				ZEPHIR_CONCAT_SV(&method, "get", &_35$$17);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				_36$$17 = ZEPHIR_IS_TRUE_IDENTICAL(useGetter);
				if (_36$$17) {
					ZEPHIR_INIT_NVAR(&_37$$17);
					ZVAL_STRING(&_37$$17, "getSource");
					_36$$17 = !ZEPHIR_IS_IDENTICAL(&_37$$17, &method);
				}
				_38$$17 = _36$$17;
				if (_38$$17) {
					_38$$17 = (zephir_method_exists(this_ptr, &method)  == SUCCESS);
				}
				if (_38$$17) {

					/* try_start_2: */

						ZEPHIR_CALL_METHOD_ZVAL(&_39$$26, this_ptr, &method, NULL, 0);
						zephir_check_call_status_or_jump(try_end_2);
						zephir_array_update_zval(&data, &attributeField, &_39$$26, PH_COPY | PH_SEPARATE);

					try_end_2:

					if (EG(exception)) {
						ZEPHIR_INIT_NVAR(&_40$$25);
						ZVAL_OBJ(&_40$$25, EG(exception));
						Z_ADDREF_P(&_40$$25);
						ZEPHIR_INIT_NVAR(&_41$$25);
						if (zephir_is_instance_of(&_40$$25, SL("Error"))) {
							zend_clear_exception();
							ZEPHIR_CPY_WRT(&_41$$25, &_40$$25);
							zephir_array_update_zval(&data, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
						} else {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} else if (zephir_isset_property_value_zval(this_ptr, &attributeField)) {
					ZEPHIR_OBS_NVAR(&_42$$29);
					zephir_read_property_zval(&_42$$29, this_ptr, &attributeField, PH_NOISY_CC);
					zephir_array_update_zval(&data, &attributeField, &_42$$29, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&data, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&attribute);
	RETURN_CTOR(&data);
}

/**
 * Updates a model instance. If the instance does not exist in the
 * persistence it will throw an exception. Returning `true` on success or
 * `false` otherwise.
 *
 * ```php
 * <?php
 *
 * use MyApp\Models\Invoices;
 *
 * $invoice = Invoices::findFirst('inv_id = 4');
 *
 * $invoice->inv_total = 120;
 *
 * $invoice->update();
 * ```
 *
 * !!! warning "NOTE"
 *
 *     When retrieving the record with `findFirst()`, you need to get the full
 *     object back (no `columns` definition) but also retrieve it using the
 *     primary key. If not, the ORM will issue an `INSERT` instead of `UPDATE`.
 */
PHP_METHOD(Phalcon_Mvc_Model, update)
{
	zval _3$$4, _5$$4;
	zval metaData, _0, _1$$3, _2$$3, _4$$4, _6$$4, _7$$4, _8$$4, _9$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("errorMessages", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 711, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(&metaData, this_ptr, "getModelsMetaData", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "getReadConnection", NULL, 474);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "has", NULL, 0, &metaData, &_2$$3);
		zephir_check_call_status();
		if (!(zephir_is_true(&_1$$3))) {
			ZEPHIR_INIT_VAR(&_3$$4);
			zephir_create_array(&_3$$4, 1, 0);
			ZEPHIR_INIT_VAR(&_4$$4);
			object_init_ex(&_4$$4, phalcon_messages_message_ce);
			ZEPHIR_INIT_VAR(&_5$$4);
			zephir_create_array(&_5$$4, 1, 0);
			ZEPHIR_INIT_VAR(&_6$$4);
			zephir_get_class(&_6$$4, this_ptr, 0);
			zephir_array_update_string(&_5$$4, SL("model"), &_6$$4, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZVAL_STRING(&_6$$4, "Record cannot be updated because it does not exist");
			ZVAL_NULL(&_7$$4);
			ZEPHIR_INIT_VAR(&_8$$4);
			ZVAL_STRING(&_8$$4, "InvalidUpdateAttempt");
			ZVAL_LONG(&_9$$4, 0);
			ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 6, &_6$$4, &_7$$4, &_8$$4, &_9$$4, &_5$$4);
			zephir_check_call_status();
			zephir_array_fast_append(&_3$$4, &_4$$4);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 713, &_3$$4);
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "save", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Writes an attribute value by its name
 *
 *```php
 * $robot->writeAttribute("name", "Rosey");
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, writeAttribute)
{
	zval attribute_zv, *value, value_sub;
	zend_string *attribute = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attribute_zv);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(attribute)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	value = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&attribute_zv, attribute);
	zephir_update_property_zval_zval(this_ptr, &attribute_zv, value);
}

/**
 * Reads "belongs to" relations and check the virtual foreign keys when
 * inserting or updating records to verify that inserted/updated values are
 * present in the related entity
 */
PHP_METHOD(Phalcon_Mvc_Model, checkForeignKeysRestrict)
{
	zend_string *_11$$7, *_40$$26;
	zend_ulong _10$$7, _39$$26;
	zend_bool error = 0, validateWithNulls = 0, _32, _19$$3, _15$$7, _48$$22, _44$$26;
	zval conditions, _21$$3, _25$$18, _50$$22, _54$$37;
	zval manager, belongsTo, foreignKey, relation, position, bindParams, extraConditions, message, fields, referencedFields, field, referencedModel, value, allowNulls, _0, *_1, _2, *_3, _31, _4$$5, _5$$3, _20$$3, _22$$3, *_7$$7, _8$$7, *_9$$7, _14$$7, _12$$8, _13$$8, _16$$10, _17$$10, _18$$12, _23$$20, _24$$18, _26$$18, _27$$18, _28$$18, _33$$24, _34$$22, _49$$22, _51$$22, *_36$$26, _37$$26, *_38$$26, _43$$26, _41$$27, _42$$27, _45$$29, _46$$29, _47$$31, _52$$39, _53$$37, _55$$37, _56$$37, _57$$37, _58$$41, _59$$41, _60$$42;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_29 = NULL, *_30 = NULL, *_35 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, action = 0, numberNull = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&belongsTo);
	ZVAL_UNDEF(&foreignKey);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&extraConditions);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&referencedFields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&referencedModel);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&allowNulls);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_22$$3);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_23$$20);
	ZVAL_UNDEF(&_24$$18);
	ZVAL_UNDEF(&_26$$18);
	ZVAL_UNDEF(&_27$$18);
	ZVAL_UNDEF(&_28$$18);
	ZVAL_UNDEF(&_33$$24);
	ZVAL_UNDEF(&_34$$22);
	ZVAL_UNDEF(&_49$$22);
	ZVAL_UNDEF(&_51$$22);
	ZVAL_UNDEF(&_37$$26);
	ZVAL_UNDEF(&_43$$26);
	ZVAL_UNDEF(&_41$$27);
	ZVAL_UNDEF(&_42$$27);
	ZVAL_UNDEF(&_45$$29);
	ZVAL_UNDEF(&_46$$29);
	ZVAL_UNDEF(&_47$$31);
	ZVAL_UNDEF(&_52$$39);
	ZVAL_UNDEF(&_53$$37);
	ZVAL_UNDEF(&_55$$37);
	ZVAL_UNDEF(&_56$$37);
	ZVAL_UNDEF(&_57$$37);
	ZVAL_UNDEF(&_58$$41);
	ZVAL_UNDEF(&_59$$41);
	ZVAL_UNDEF(&_60$$42);
	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_25$$18);
	ZVAL_UNDEF(&_50$$22);
	ZVAL_UNDEF(&_54$$37);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&belongsTo, &manager, "getBelongsTo", NULL, 0, this_ptr);
	zephir_check_call_status();
	error = 0;
	if (Z_TYPE_P(&belongsTo) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &belongsTo);
		_1 = &_2;
	} else {
		_1 = &belongsTo;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model.zep", 3878);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&relation);
			ZVAL_COPY(&relation, _3);
			validateWithNulls = 0;
			ZEPHIR_CALL_METHOD(&foreignKey, &relation, "getForeignKey", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&foreignKey)) {
				continue;
			}
			action = 1;
			if (zephir_array_isset_value_string(&foreignKey, SL("action"))) {
				ZEPHIR_OBS_NVAR(&_4$$5);
				zephir_array_fetch_string(&_4$$5, &foreignKey, SL("action"), PH_NOISY, "phalcon/Mvc/Model.zep", 3764);
				action = zephir_get_intval(&_4$$5);
			}
			if (action != 1) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&_5$$3, &relation, "getReferencedModel", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&referencedModel, &manager, "load", &_6, 0, &_5$$3);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&conditions);
			array_init(&conditions);
			ZEPHIR_INIT_NVAR(&bindParams);
			array_init(&bindParams);
			numberNull = 0;
			ZEPHIR_CALL_METHOD(&fields, &relation, "getFields", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&fields) == IS_ARRAY) {
				if (Z_TYPE_P(&fields) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_8$$7);
					zephir_string_to_char_array(&_8$$7, &fields);
					_7$$7 = &_8$$7;
				} else {
					_7$$7 = &fields;
				}
				zephir_is_iterable(_7$$7, 0, "phalcon/Mvc/Model.zep", 3807);
				if (Z_TYPE_P(_7$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7$$7), _10$$7, _11$$7, _9$$7)
					{
						ZEPHIR_INIT_NVAR(&position);
						if (_11$$7 != NULL) { 
							ZVAL_STR_COPY(&position, _11$$7);
						} else {
							ZVAL_LONG(&position, _10$$7);
						}
						ZEPHIR_INIT_NVAR(&field);
						ZVAL_COPY(&field, _9$$7);
						ZEPHIR_OBS_NVAR(&value);
						zephir_fetch_property_zval(&value, this_ptr, &field, PH_SILENT_CC);
						ZEPHIR_OBS_NVAR(&_12$$8);
						zephir_array_fetch(&_12$$8, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model.zep", 3799);
						ZEPHIR_INIT_NVAR(&_13$$8);
						ZEPHIR_CONCAT_SVSV(&_13$$8, "[", &_12$$8, "] = ?", &position);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&conditions, &_13$$8, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3799);
						zephir_array_append(&bindParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3800);
						if (Z_TYPE_P(&value) == IS_NULL) {
							numberNull++;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _7$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_15$$7 = 1;
					while (1) {
						if (_15$$7) {
							_15$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _7$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_14$$7, _7$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_14$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&position, _7$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&field, _7$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_OBS_NVAR(&value);
							zephir_fetch_property_zval(&value, this_ptr, &field, PH_SILENT_CC);
							ZEPHIR_OBS_NVAR(&_16$$10);
							zephir_array_fetch(&_16$$10, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model.zep", 3799);
							ZEPHIR_INIT_NVAR(&_17$$10);
							ZEPHIR_CONCAT_SVSV(&_17$$10, "[", &_16$$10, "] = ?", &position);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&conditions, &_17$$10, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3799);
							zephir_array_append(&bindParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3800);
							if (Z_TYPE_P(&value) == IS_NULL) {
								numberNull++;
							}
					}
				}
				ZEPHIR_INIT_NVAR(&field);
				ZEPHIR_INIT_NVAR(&position);
				validateWithNulls = numberNull == zephir_fast_count_int(&fields);
			} else {
				ZEPHIR_OBS_NVAR(&value);
				zephir_fetch_property_zval(&value, this_ptr, &fields, PH_SILENT_CC);
				ZEPHIR_INIT_NVAR(&_18$$12);
				ZEPHIR_CONCAT_SVS(&_18$$12, "[", &referencedFields, "] = ?0");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&conditions, &_18$$12, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3811);
				zephir_array_append(&bindParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3812);
				if (Z_TYPE_P(&value) == IS_NULL) {
					validateWithNulls = 1;
				}
			}
			ZEPHIR_OBS_NVAR(&extraConditions);
			if (zephir_array_isset_string_fetch(&extraConditions, &foreignKey, SL("conditions"), 0)) {
				zephir_array_append(&conditions, &extraConditions, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3823);
			}
			if (validateWithNulls) {
				ZEPHIR_OBS_NVAR(&allowNulls);
				if (zephir_array_isset_string_fetch(&allowNulls, &foreignKey, SL("allowNulls"), 0)) {
					validateWithNulls = zephir_get_boolval(&allowNulls);
				} else {
					validateWithNulls = 0;
				}
			}
			_19$$3 = !validateWithNulls;
			if (_19$$3) {
				ZEPHIR_INIT_NVAR(&_21$$3);
				zephir_create_array(&_21$$3, 2, 0);
				ZEPHIR_INIT_NVAR(&_22$$3);
				zephir_fast_join_str(&_22$$3, SL(" AND "), &conditions);
				zephir_array_fast_append(&_21$$3, &_22$$3);
				zephir_array_update_string(&_21$$3, SL("bind"), &bindParams, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_20$$3, &referencedModel, "count", NULL, 0, &_21$$3);
				zephir_check_call_status();
				_19$$3 = !zephir_is_true(&_20$$3);
			}
			if (_19$$3) {
				ZEPHIR_OBS_NVAR(&message);
				if (!(zephir_array_isset_string_fetch(&message, &foreignKey, SL("message"), 0))) {
					ZEPHIR_INIT_NVAR(&message);
					if (Z_TYPE_P(&fields) == IS_ARRAY) {
						ZEPHIR_INIT_NVAR(&_23$$20);
						zephir_fast_join_str(&_23$$20, SL(", "), &fields);
						ZEPHIR_CONCAT_SVS(&message, "Value of fields \"", &_23$$20, "\" does not exist on referenced table");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CONCAT_SVS(&message, "Value of field \"", &fields, "\" does not exist on referenced table");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
				ZEPHIR_INIT_NVAR(&_24$$18);
				object_init_ex(&_24$$18, phalcon_messages_message_ce);
				ZEPHIR_INIT_NVAR(&_25$$18);
				zephir_create_array(&_25$$18, 2, 0);
				ZEPHIR_INIT_NVAR(&_26$$18);
				zephir_get_class(&_26$$18, this_ptr, 0);
				zephir_array_update_string(&_25$$18, SL("model"), &_26$$18, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_27$$18, &relation, "getReferencedModel", NULL, 0);
				zephir_check_call_status();
				zephir_array_update_string(&_25$$18, SL("referenceModel"), &_27$$18, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_26$$18);
				ZVAL_STRING(&_26$$18, "ConstraintViolation");
				ZVAL_LONG(&_28$$18, 0);
				ZEPHIR_CALL_METHOD(NULL, &_24$$18, "__construct", &_29, 6, &message, &fields, &_26$$18, &_28$$18, &_25$$18);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_30, 0, &_24$$18);
				zephir_check_call_status();
				error = 1;
				break;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_32 = 1;
		while (1) {
			if (_32) {
				_32 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_31, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_31)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&relation, _1, "current", NULL, 0);
			zephir_check_call_status();
				validateWithNulls = 0;
				ZEPHIR_CALL_METHOD(&foreignKey, &relation, "getForeignKey", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&foreignKey)) {
					continue;
				}
				action = 1;
				if (zephir_array_isset_value_string(&foreignKey, SL("action"))) {
					ZEPHIR_OBS_NVAR(&_33$$24);
					zephir_array_fetch_string(&_33$$24, &foreignKey, SL("action"), PH_NOISY, "phalcon/Mvc/Model.zep", 3764);
					action = zephir_get_intval(&_33$$24);
				}
				if (action != 1) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&_34$$22, &relation, "getReferencedModel", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&referencedModel, &manager, "load", &_35, 0, &_34$$22);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&conditions);
				array_init(&conditions);
				ZEPHIR_INIT_NVAR(&bindParams);
				array_init(&bindParams);
				numberNull = 0;
				ZEPHIR_CALL_METHOD(&fields, &relation, "getFields", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&fields) == IS_ARRAY) {
					if (Z_TYPE_P(&fields) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_37$$26);
						zephir_string_to_char_array(&_37$$26, &fields);
						_36$$26 = &_37$$26;
					} else {
						_36$$26 = &fields;
					}
					zephir_is_iterable(_36$$26, 0, "phalcon/Mvc/Model.zep", 3807);
					if (Z_TYPE_P(_36$$26) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_36$$26), _39$$26, _40$$26, _38$$26)
						{
							ZEPHIR_INIT_NVAR(&position);
							if (_40$$26 != NULL) { 
								ZVAL_STR_COPY(&position, _40$$26);
							} else {
								ZVAL_LONG(&position, _39$$26);
							}
							ZEPHIR_INIT_NVAR(&field);
							ZVAL_COPY(&field, _38$$26);
							ZEPHIR_OBS_NVAR(&value);
							zephir_fetch_property_zval(&value, this_ptr, &field, PH_SILENT_CC);
							ZEPHIR_OBS_NVAR(&_41$$27);
							zephir_array_fetch(&_41$$27, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model.zep", 3799);
							ZEPHIR_INIT_NVAR(&_42$$27);
							ZEPHIR_CONCAT_SVSV(&_42$$27, "[", &_41$$27, "] = ?", &position);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&conditions, &_42$$27, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3799);
							zephir_array_append(&bindParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3800);
							if (Z_TYPE_P(&value) == IS_NULL) {
								numberNull++;
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _36$$26, "rewind", NULL, 0);
						zephir_check_call_status();
						_44$$26 = 1;
						while (1) {
							if (_44$$26) {
								_44$$26 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _36$$26, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_43$$26, _36$$26, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_43$$26)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&position, _36$$26, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&field, _36$$26, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_OBS_NVAR(&value);
								zephir_fetch_property_zval(&value, this_ptr, &field, PH_SILENT_CC);
								ZEPHIR_OBS_NVAR(&_45$$29);
								zephir_array_fetch(&_45$$29, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model.zep", 3799);
								ZEPHIR_INIT_NVAR(&_46$$29);
								ZEPHIR_CONCAT_SVSV(&_46$$29, "[", &_45$$29, "] = ?", &position);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_append(&conditions, &_46$$29, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3799);
								zephir_array_append(&bindParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3800);
								if (Z_TYPE_P(&value) == IS_NULL) {
									numberNull++;
								}
						}
					}
					ZEPHIR_INIT_NVAR(&field);
					ZEPHIR_INIT_NVAR(&position);
					validateWithNulls = numberNull == zephir_fast_count_int(&fields);
				} else {
					ZEPHIR_OBS_NVAR(&value);
					zephir_fetch_property_zval(&value, this_ptr, &fields, PH_SILENT_CC);
					ZEPHIR_INIT_NVAR(&_47$$31);
					ZEPHIR_CONCAT_SVS(&_47$$31, "[", &referencedFields, "] = ?0");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&conditions, &_47$$31, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3811);
					zephir_array_append(&bindParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3812);
					if (Z_TYPE_P(&value) == IS_NULL) {
						validateWithNulls = 1;
					}
				}
				ZEPHIR_OBS_NVAR(&extraConditions);
				if (zephir_array_isset_string_fetch(&extraConditions, &foreignKey, SL("conditions"), 0)) {
					zephir_array_append(&conditions, &extraConditions, PH_SEPARATE, "phalcon/Mvc/Model.zep", 3823);
				}
				if (validateWithNulls) {
					ZEPHIR_OBS_NVAR(&allowNulls);
					if (zephir_array_isset_string_fetch(&allowNulls, &foreignKey, SL("allowNulls"), 0)) {
						validateWithNulls = zephir_get_boolval(&allowNulls);
					} else {
						validateWithNulls = 0;
					}
				}
				_48$$22 = !validateWithNulls;
				if (_48$$22) {
					ZEPHIR_INIT_NVAR(&_50$$22);
					zephir_create_array(&_50$$22, 2, 0);
					ZEPHIR_INIT_NVAR(&_51$$22);
					zephir_fast_join_str(&_51$$22, SL(" AND "), &conditions);
					zephir_array_fast_append(&_50$$22, &_51$$22);
					zephir_array_update_string(&_50$$22, SL("bind"), &bindParams, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(&_49$$22, &referencedModel, "count", NULL, 0, &_50$$22);
					zephir_check_call_status();
					_48$$22 = !zephir_is_true(&_49$$22);
				}
				if (_48$$22) {
					ZEPHIR_OBS_NVAR(&message);
					if (!(zephir_array_isset_string_fetch(&message, &foreignKey, SL("message"), 0))) {
						ZEPHIR_INIT_NVAR(&message);
						if (Z_TYPE_P(&fields) == IS_ARRAY) {
							ZEPHIR_INIT_NVAR(&_52$$39);
							zephir_fast_join_str(&_52$$39, SL(", "), &fields);
							ZEPHIR_CONCAT_SVS(&message, "Value of fields \"", &_52$$39, "\" does not exist on referenced table");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZEPHIR_CONCAT_SVS(&message, "Value of field \"", &fields, "\" does not exist on referenced table");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
					ZEPHIR_INIT_NVAR(&_53$$37);
					object_init_ex(&_53$$37, phalcon_messages_message_ce);
					ZEPHIR_INIT_NVAR(&_54$$37);
					zephir_create_array(&_54$$37, 2, 0);
					ZEPHIR_INIT_NVAR(&_55$$37);
					zephir_get_class(&_55$$37, this_ptr, 0);
					zephir_array_update_string(&_54$$37, SL("model"), &_55$$37, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(&_56$$37, &relation, "getReferencedModel", NULL, 0);
					zephir_check_call_status();
					zephir_array_update_string(&_54$$37, SL("referenceModel"), &_56$$37, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_55$$37);
					ZVAL_STRING(&_55$$37, "ConstraintViolation");
					ZVAL_LONG(&_57$$37, 0);
					ZEPHIR_CALL_METHOD(NULL, &_53$$37, "__construct", &_29, 6, &message, &fields, &_55$$37, &_57$$37, &_54$$37);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_30, 0, &_53$$37);
					zephir_check_call_status();
					error = 1;
					break;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&relation);
	if (error) {
		ZEPHIR_INIT_VAR(&_59$$41);
		ZVAL_STRING(&_59$$41, "orm.events");
		ZEPHIR_CALL_CE_STATIC(&_58$$41, phalcon_support_settings_ce, "get", NULL, 0, &_59$$41);
		zephir_check_call_status();
		if (zephir_is_true(&_58$$41)) {
			ZEPHIR_INIT_VAR(&_60$$42);
			ZVAL_STRING(&_60$$42, "onValidationFails");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_60$$42);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "cancelOperation", NULL, 0);
			zephir_check_call_status();
		}
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);
}

/**
 * Reads both "hasMany" and "hasOne" relations and checks the virtual
 * foreign keys (cascade) when deleting records
 */
PHP_METHOD(Phalcon_Mvc_Model, checkForeignKeysReverseCascade)
{
	zend_bool _9, _4$$3, _10$$9;
	zval manager, relations, relation, foreignKey, related, _0, *_1, _2, *_3, _8, _5$$5, _7$$7, _11$$11, _13$$13;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, action = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&relations);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&foreignKey);
	ZVAL_UNDEF(&related);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_13$$13);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&relations, &manager, "getHasOneAndHasMany", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (Z_TYPE_P(&relations) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &relations);
		_1 = &_2;
	} else {
		_1 = &relations;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model.zep", 3954);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&relation);
			ZVAL_COPY(&relation, _3);
			ZEPHIR_CALL_METHOD(&foreignKey, &relation, "getForeignKey", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&foreignKey)) {
				continue;
			}
			action = 0;
			_4$$3 = Z_TYPE_P(&foreignKey) == IS_ARRAY;
			if (_4$$3) {
				_4$$3 = zephir_array_isset_value_string(&foreignKey, SL("action"));
			}
			if (_4$$3) {
				ZEPHIR_OBS_NVAR(&_5$$5);
				zephir_array_fetch_string(&_5$$5, &foreignKey, SL("action"), PH_NOISY, "phalcon/Mvc/Model.zep", 3928);
				action = zephir_get_intval(&_5$$5);
			}
			if (action != 2) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&related, &manager, "getRelationRecords", &_6, 0, &relation, this_ptr);
			zephir_check_call_status();
			if (zephir_is_true(&related)) {
				ZEPHIR_CALL_METHOD(&_7$$7, &related, "delete", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_7$$7)) {
					RETURN_MM_BOOL(0);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_9 = 1;
		while (1) {
			if (_9) {
				_9 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_8, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&relation, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&foreignKey, &relation, "getForeignKey", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&foreignKey)) {
					continue;
				}
				action = 0;
				_10$$9 = Z_TYPE_P(&foreignKey) == IS_ARRAY;
				if (_10$$9) {
					_10$$9 = zephir_array_isset_value_string(&foreignKey, SL("action"));
				}
				if (_10$$9) {
					ZEPHIR_OBS_NVAR(&_11$$11);
					zephir_array_fetch_string(&_11$$11, &foreignKey, SL("action"), PH_NOISY, "phalcon/Mvc/Model.zep", 3928);
					action = zephir_get_intval(&_11$$11);
				}
				if (action != 2) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&related, &manager, "getRelationRecords", &_12, 0, &relation, this_ptr);
				zephir_check_call_status();
				if (zephir_is_true(&related)) {
					ZEPHIR_CALL_METHOD(&_13$$13, &related, "delete", NULL, 0);
					zephir_check_call_status();
					if (ZEPHIR_IS_FALSE_IDENTICAL(&_13$$13)) {
						RETURN_MM_BOOL(0);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&relation);
	RETURN_MM_BOOL(1);
}

/**
 * Reads both "hasMany" and "hasOne" relations and checks the virtual
 * foreign keys (restrict) when deleting records
 */
PHP_METHOD(Phalcon_Mvc_Model, checkForeignKeysReverseRestrict)
{
	zval _11$$7, _25$$13;
	zval manager, relations, foreignKey, relation, relationClass, fields, message, _0, *_1, _2, *_3, _16, _6$$3, _7$$3, _8$$3, _5$$5, _10$$7, _12$$7, _13$$7, _20$$9, _21$$9, _22$$9, _19$$11, _24$$13, _26$$13, _27$$13, _28$$15, _29$$15, _30$$16;
	zend_bool error = 0, _17, _4$$3, _18$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_14 = NULL, *_15 = NULL, *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, action = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&relations);
	ZVAL_UNDEF(&foreignKey);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&relationClass);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_19$$11);
	ZVAL_UNDEF(&_24$$13);
	ZVAL_UNDEF(&_26$$13);
	ZVAL_UNDEF(&_27$$13);
	ZVAL_UNDEF(&_28$$15);
	ZVAL_UNDEF(&_29$$15);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_25$$13);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&relations, &manager, "getHasOneAndHasMany", NULL, 0, this_ptr);
	zephir_check_call_status();
	error = 0;
	if (Z_TYPE_P(&relations) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &relations);
		_1 = &_2;
	} else {
		_1 = &relations;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model.zep", 4045);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&relation);
			ZVAL_COPY(&relation, _3);
			ZEPHIR_CALL_METHOD(&foreignKey, &relation, "getForeignKey", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&foreignKey)) {
				continue;
			}
			action = 1;
			_4$$3 = Z_TYPE_P(&foreignKey) == IS_ARRAY;
			if (_4$$3) {
				_4$$3 = zephir_array_isset_value_string(&foreignKey, SL("action"));
			}
			if (_4$$3) {
				ZEPHIR_OBS_NVAR(&_5$$5);
				zephir_array_fetch_string(&_5$$5, &foreignKey, SL("action"), PH_NOISY, "phalcon/Mvc/Model.zep", 3999);
				action = zephir_get_intval(&_5$$5);
			}
			if (action != 1) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&relationClass, &relation, "getReferencedModel", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&fields, &relation, "getFields", NULL, 0);
			zephir_check_call_status();
			ZVAL_NULL(&_7$$3);
			ZEPHIR_INIT_NVAR(&_8$$3);
			ZVAL_STRING(&_8$$3, "count");
			ZEPHIR_CALL_METHOD(&_6$$3, &manager, "getRelationRecords", &_9, 0, &relation, this_ptr, &_7$$3, &_8$$3);
			zephir_check_call_status();
			if (zephir_is_true(&_6$$3)) {
				ZEPHIR_OBS_NVAR(&message);
				if (!(zephir_array_isset_string_fetch(&message, &foreignKey, SL("message"), 0))) {
					ZEPHIR_INIT_NVAR(&message);
					ZEPHIR_CONCAT_SV(&message, "Record is referenced by model ", &relationClass);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_INIT_NVAR(&_10$$7);
				object_init_ex(&_10$$7, phalcon_messages_message_ce);
				ZEPHIR_INIT_NVAR(&_11$$7);
				zephir_create_array(&_11$$7, 2, 0);
				ZEPHIR_INIT_NVAR(&_12$$7);
				zephir_get_class(&_12$$7, this_ptr, 0);
				zephir_array_update_string(&_11$$7, SL("model"), &_12$$7, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_11$$7, SL("referenceModel"), &relationClass, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_12$$7);
				ZVAL_STRING(&_12$$7, "ConstraintViolation");
				ZVAL_LONG(&_13$$7, 0);
				ZEPHIR_CALL_METHOD(NULL, &_10$$7, "__construct", &_14, 6, &message, &fields, &_12$$7, &_13$$7, &_11$$7);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_15, 0, &_10$$7);
				zephir_check_call_status();
				error = 1;
				break;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_17 = 1;
		while (1) {
			if (_17) {
				_17 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_16, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_16)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&relation, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&foreignKey, &relation, "getForeignKey", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&foreignKey)) {
					continue;
				}
				action = 1;
				_18$$9 = Z_TYPE_P(&foreignKey) == IS_ARRAY;
				if (_18$$9) {
					_18$$9 = zephir_array_isset_value_string(&foreignKey, SL("action"));
				}
				if (_18$$9) {
					ZEPHIR_OBS_NVAR(&_19$$11);
					zephir_array_fetch_string(&_19$$11, &foreignKey, SL("action"), PH_NOISY, "phalcon/Mvc/Model.zep", 3999);
					action = zephir_get_intval(&_19$$11);
				}
				if (action != 1) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&relationClass, &relation, "getReferencedModel", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&fields, &relation, "getFields", NULL, 0);
				zephir_check_call_status();
				ZVAL_NULL(&_21$$9);
				ZEPHIR_INIT_NVAR(&_22$$9);
				ZVAL_STRING(&_22$$9, "count");
				ZEPHIR_CALL_METHOD(&_20$$9, &manager, "getRelationRecords", &_23, 0, &relation, this_ptr, &_21$$9, &_22$$9);
				zephir_check_call_status();
				if (zephir_is_true(&_20$$9)) {
					ZEPHIR_OBS_NVAR(&message);
					if (!(zephir_array_isset_string_fetch(&message, &foreignKey, SL("message"), 0))) {
						ZEPHIR_INIT_NVAR(&message);
						ZEPHIR_CONCAT_SV(&message, "Record is referenced by model ", &relationClass);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					ZEPHIR_INIT_NVAR(&_24$$13);
					object_init_ex(&_24$$13, phalcon_messages_message_ce);
					ZEPHIR_INIT_NVAR(&_25$$13);
					zephir_create_array(&_25$$13, 2, 0);
					ZEPHIR_INIT_NVAR(&_26$$13);
					zephir_get_class(&_26$$13, this_ptr, 0);
					zephir_array_update_string(&_25$$13, SL("model"), &_26$$13, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_25$$13, SL("referenceModel"), &relationClass, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_26$$13);
					ZVAL_STRING(&_26$$13, "ConstraintViolation");
					ZVAL_LONG(&_27$$13, 0);
					ZEPHIR_CALL_METHOD(NULL, &_24$$13, "__construct", &_14, 6, &message, &fields, &_26$$13, &_27$$13, &_25$$13);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_15, 0, &_24$$13);
					zephir_check_call_status();
					error = 1;
					break;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&relation);
	if (error) {
		ZEPHIR_INIT_VAR(&_29$$15);
		ZVAL_STRING(&_29$$15, "orm.events");
		ZEPHIR_CALL_CE_STATIC(&_28$$15, phalcon_support_settings_ce, "get", NULL, 0, &_29$$15);
		zephir_check_call_status();
		if (zephir_is_true(&_28$$15)) {
			ZEPHIR_INIT_VAR(&_30$$16);
			ZVAL_STRING(&_30$$16, "onValidationFails");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_30$$16);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "cancelOperation", NULL, 0);
			zephir_check_call_status();
		}
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);
}

/**
 * Sends a pre-build INSERT SQL statement to the relational database system
 *
 * @param string|array table
 * @param bool|string identityField
 */
PHP_METHOD(Phalcon_Mvc_Model, doLowInsert)
{
	zend_string *_68$$58;
	zend_ulong _67$$58;
	zend_bool useExplicitIdentity = 0, _26, _57, _9$$9, _10$$11, _30$$24, _31$$26, _50$$40, _59$$49, _70$$58;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_14 = NULL, *_15 = NULL, *_22 = NULL, *_24 = NULL, *_35 = NULL, *_36 = NULL, *_43 = NULL, *_45 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *metaData, metaData_sub, *connection, connection_sub, *table = NULL, table_sub, *identityField, identityField_sub, __$null, attributeField, attributes, automaticAttributes, bindDataTypes, bindSkip, bindType, bindTypes, columnMap, defaultValue, defaultValues, field, fields, lastInsertedId, manager, sequenceName, schema, snapshot, source, success, unsetDefaultValues, value, values, _0, _1, _2, *_3, *_4, _25, _5$$7, _6$$7, _7$$7, _11$$12, _12$$12, _13$$12, _16$$15, _17$$15, _18$$15, _19$$17, _20$$17, _21$$17, _23$$17, _27$$22, _28$$22, _29$$22, _32$$27, _33$$27, _34$$27, _37$$30, _38$$30, _39$$30, _40$$32, _41$$32, _42$$32, _44$$32, _46$$35, _47$$38, _48$$38, _49$$38, _51$$45, _52$$45, _53$$45, _54$$48, _55$$48, _56$$48, _58$$49, _60$$49, _61$$49, _62$$57, _63$$57, *_64$$58, _65$$58, *_66$$58, _69$$58, _71$$58, _72$$58;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData_sub);
	ZVAL_UNDEF(&connection_sub);
	ZVAL_UNDEF(&table_sub);
	ZVAL_UNDEF(&identityField_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&automaticAttributes);
	ZVAL_UNDEF(&bindDataTypes);
	ZVAL_UNDEF(&bindSkip);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&defaultValues);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&lastInsertedId);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&sequenceName);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&success);
	ZVAL_UNDEF(&unsetDefaultValues);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_11$$12);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_16$$15);
	ZVAL_UNDEF(&_17$$15);
	ZVAL_UNDEF(&_18$$15);
	ZVAL_UNDEF(&_19$$17);
	ZVAL_UNDEF(&_20$$17);
	ZVAL_UNDEF(&_21$$17);
	ZVAL_UNDEF(&_23$$17);
	ZVAL_UNDEF(&_27$$22);
	ZVAL_UNDEF(&_28$$22);
	ZVAL_UNDEF(&_29$$22);
	ZVAL_UNDEF(&_32$$27);
	ZVAL_UNDEF(&_33$$27);
	ZVAL_UNDEF(&_34$$27);
	ZVAL_UNDEF(&_37$$30);
	ZVAL_UNDEF(&_38$$30);
	ZVAL_UNDEF(&_39$$30);
	ZVAL_UNDEF(&_40$$32);
	ZVAL_UNDEF(&_41$$32);
	ZVAL_UNDEF(&_42$$32);
	ZVAL_UNDEF(&_44$$32);
	ZVAL_UNDEF(&_46$$35);
	ZVAL_UNDEF(&_47$$38);
	ZVAL_UNDEF(&_48$$38);
	ZVAL_UNDEF(&_49$$38);
	ZVAL_UNDEF(&_51$$45);
	ZVAL_UNDEF(&_52$$45);
	ZVAL_UNDEF(&_53$$45);
	ZVAL_UNDEF(&_54$$48);
	ZVAL_UNDEF(&_55$$48);
	ZVAL_UNDEF(&_56$$48);
	ZVAL_UNDEF(&_58$$49);
	ZVAL_UNDEF(&_60$$49);
	ZVAL_UNDEF(&_61$$49);
	ZVAL_UNDEF(&_62$$57);
	ZVAL_UNDEF(&_63$$57);
	ZVAL_UNDEF(&_65$$58);
	ZVAL_UNDEF(&_69$$58);
	ZVAL_UNDEF(&_71$$58);
	ZVAL_UNDEF(&_72$$58);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("uniqueKey", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("uniqueParams", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("snapshot", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(metaData, phalcon_mvc_model_metadatainterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(connection, phalcon_db_adapter_adapterinterface_ce)
		Z_PARAM_ZVAL(table)
		Z_PARAM_ZVAL(identityField)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &metaData, &connection, &table, &identityField);
	ZEPHIR_SEPARATE_PARAM(table);
	ZEPHIR_INIT_VAR(&attributeField);
	ZEPHIR_INIT_VAR(&bindSkip);
	ZVAL_LONG(&bindSkip, 1024);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_INIT_VAR(&fields);
	array_init(&fields);
	ZEPHIR_INIT_VAR(&values);
	array_init(&values);
	ZEPHIR_INIT_VAR(&snapshot);
	array_init(&snapshot);
	ZEPHIR_INIT_VAR(&bindTypes);
	array_init(&bindTypes);
	ZEPHIR_INIT_VAR(&unsetDefaultValues);
	array_init(&unsetDefaultValues);
	ZEPHIR_CALL_METHOD(&attributes, metaData, "getAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&bindDataTypes, metaData, "getBindTypes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&automaticAttributes, metaData, "getAutomaticCreateAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&defaultValues, metaData, "getDefaultValues", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "orm.column_renaming");
	ZEPHIR_CALL_CE_STATIC(&_1, phalcon_support_settings_ce, "get", NULL, 0, &_2);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_CALL_METHOD(&columnMap, metaData, "getColumnMap", NULL, 0, this_ptr);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&columnMap);
		ZVAL_NULL(&columnMap);
	}
	if (Z_TYPE_P(&attributes) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_2);
		zephir_string_to_char_array(&_2, &attributes);
		_3 = &_2;
	} else {
		_3 = &attributes;
	}
	zephir_is_iterable(_3, 0, "phalcon/Mvc/Model.zep", 4167);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _4)
		{
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _4);
			if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
				ZEPHIR_OBS_NVAR(&attributeField);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
					ZEPHIR_INIT_NVAR(&_5$$7);
					object_init_ex(&_5$$7, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_6$$7);
					zephir_get_class(&_6$$7, this_ptr, 0);
					ZEPHIR_INIT_NVAR(&_7$$7);
					ZEPHIR_CONCAT_SVSVS(&_7$$7, "Column '", &field, "' in '", &_6$$7, "' isn't part of the column map");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_5$$7, "__construct", &_8, 32, &_7$$7);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_5$$7, "phalcon/Mvc/Model.zep", 4101);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&attributeField, &field);
			}
			if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
				_9$$9 = !ZEPHIR_IS_EQUAL(&field, identityField);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (_9$$9) {
					ZEPHIR_OBS_NVAR(&value);
					if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
						_10$$11 = Z_TYPE_P(&value) == IS_NULL;
						if (_10$$11) {
							_10$$11 = zephir_array_isset_value(&defaultValues, &field);
						}
						if (_10$$11) {
							ZEPHIR_OBS_NVAR(&_11$$12);
							zephir_array_fetch(&_11$$12, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4118);
							zephir_array_update_zval(&snapshot, &attributeField, &_11$$12, PH_COPY | PH_SEPARATE);
							ZEPHIR_OBS_NVAR(&_12$$12);
							zephir_array_fetch(&_12$$12, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4119);
							zephir_array_update_zval(&unsetDefaultValues, &attributeField, &_12$$12, PH_COPY | PH_SEPARATE);
							ZEPHIR_CALL_METHOD(&_13$$12, connection, "supportsDefaultValue", &_14, 0);
							zephir_check_call_status();
							if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&_13$$12))) {
								continue;
							}
							ZEPHIR_CALL_METHOD(&value, connection, "getDefaultValue", &_15, 0);
							zephir_check_call_status();
						} else {
							zephir_array_update_zval(&snapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
						}
						ZEPHIR_OBS_NVAR(&bindType);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_16$$15);
							object_init_ex(&_16$$15, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_17$$15);
							zephir_get_class(&_17$$15, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_18$$15);
							ZEPHIR_CONCAT_SVSVS(&_18$$15, "Column '", &field, "' in '", &_17$$15, "' have not defined a bind data type");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_16$$15, "__construct", &_8, 32, &_18$$15);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_16$$15, "phalcon/Mvc/Model.zep", 4136);
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4139);
						zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4140);
						zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4141);
					} else {
						if (zephir_array_isset_value(&defaultValues, &field)) {
							ZEPHIR_OBS_NVAR(&_19$$17);
							zephir_array_fetch(&_19$$17, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4144);
							zephir_array_update_zval(&snapshot, &attributeField, &_19$$17, PH_COPY | PH_SEPARATE);
							ZEPHIR_OBS_NVAR(&_20$$17);
							zephir_array_fetch(&_20$$17, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4145);
							zephir_array_update_zval(&unsetDefaultValues, &attributeField, &_20$$17, PH_COPY | PH_SEPARATE);
							ZEPHIR_CALL_METHOD(&_21$$17, connection, "supportsDefaultValue", &_22, 0);
							zephir_check_call_status();
							if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&_21$$17))) {
								continue;
							}
							ZEPHIR_CALL_METHOD(&_23$$17, connection, "getDefaultValue", &_24, 0);
							zephir_check_call_status();
							zephir_array_append(&values, &_23$$17, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4151);
						} else {
							zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4153);
							zephir_array_update_zval(&snapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
						}
						zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4157);
						zephir_array_append(&bindTypes, &bindSkip, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4158);
					}
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_26 = 1;
		while (1) {
			if (_26) {
				_26 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_25, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_25)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _3, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_27$$22);
						object_init_ex(&_27$$22, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_28$$22);
						zephir_get_class(&_28$$22, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_29$$22);
						ZEPHIR_CONCAT_SVSVS(&_29$$22, "Column '", &field, "' in '", &_28$$22, "' isn't part of the column map");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_27$$22, "__construct", &_8, 32, &_29$$22);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_27$$22, "phalcon/Mvc/Model.zep", 4101);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &field);
				}
				if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
					_30$$24 = !ZEPHIR_IS_EQUAL(&field, identityField);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (_30$$24) {
						ZEPHIR_OBS_NVAR(&value);
						if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
							_31$$26 = Z_TYPE_P(&value) == IS_NULL;
							if (_31$$26) {
								_31$$26 = zephir_array_isset_value(&defaultValues, &field);
							}
							if (_31$$26) {
								ZEPHIR_OBS_NVAR(&_32$$27);
								zephir_array_fetch(&_32$$27, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4118);
								zephir_array_update_zval(&snapshot, &attributeField, &_32$$27, PH_COPY | PH_SEPARATE);
								ZEPHIR_OBS_NVAR(&_33$$27);
								zephir_array_fetch(&_33$$27, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4119);
								zephir_array_update_zval(&unsetDefaultValues, &attributeField, &_33$$27, PH_COPY | PH_SEPARATE);
								ZEPHIR_CALL_METHOD(&_34$$27, connection, "supportsDefaultValue", &_35, 0);
								zephir_check_call_status();
								if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&_34$$27))) {
									continue;
								}
								ZEPHIR_CALL_METHOD(&value, connection, "getDefaultValue", &_36, 0);
								zephir_check_call_status();
							} else {
								zephir_array_update_zval(&snapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
							}
							ZEPHIR_OBS_NVAR(&bindType);
							if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &field, 0)))) {
								ZEPHIR_INIT_NVAR(&_37$$30);
								object_init_ex(&_37$$30, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_38$$30);
								zephir_get_class(&_38$$30, this_ptr, 0);
								ZEPHIR_INIT_NVAR(&_39$$30);
								ZEPHIR_CONCAT_SVSVS(&_39$$30, "Column '", &field, "' in '", &_38$$30, "' have not defined a bind data type");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_37$$30, "__construct", &_8, 32, &_39$$30);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_37$$30, "phalcon/Mvc/Model.zep", 4136);
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4139);
							zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4140);
							zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4141);
						} else {
							if (zephir_array_isset_value(&defaultValues, &field)) {
								ZEPHIR_OBS_NVAR(&_40$$32);
								zephir_array_fetch(&_40$$32, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4144);
								zephir_array_update_zval(&snapshot, &attributeField, &_40$$32, PH_COPY | PH_SEPARATE);
								ZEPHIR_OBS_NVAR(&_41$$32);
								zephir_array_fetch(&_41$$32, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 4145);
								zephir_array_update_zval(&unsetDefaultValues, &attributeField, &_41$$32, PH_COPY | PH_SEPARATE);
								ZEPHIR_CALL_METHOD(&_42$$32, connection, "supportsDefaultValue", &_43, 0);
								zephir_check_call_status();
								if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&_42$$32))) {
									continue;
								}
								ZEPHIR_CALL_METHOD(&_44$$32, connection, "getDefaultValue", &_45, 0);
								zephir_check_call_status();
								zephir_array_append(&values, &_44$$32, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4151);
							} else {
								zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4153);
								zephir_array_update_zval(&snapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
							}
							zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4157);
							zephir_array_append(&bindTypes, &bindSkip, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4158);
						}
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&field);
	if (!ZEPHIR_IS_FALSE_IDENTICAL(identityField)) {
		ZEPHIR_CALL_METHOD(&defaultValue, connection, "getDefaultIdValue", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_46$$35, connection, "useExplicitIdValue", NULL, 0);
		zephir_check_call_status();
		useExplicitIdentity = zephir_get_boolval(&_46$$35);
		if (useExplicitIdentity) {
			zephir_array_append(&fields, identityField, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4177);
		}
		if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
			ZEPHIR_OBS_NVAR(&attributeField);
			if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, identityField, 0)))) {
				ZEPHIR_INIT_VAR(&_47$$38);
				object_init_ex(&_47$$38, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_VAR(&_48$$38);
				zephir_get_class(&_48$$38, this_ptr, 0);
				ZEPHIR_INIT_VAR(&_49$$38);
				ZEPHIR_CONCAT_SVSVS(&_49$$38, "Identity column '", identityField, "' isn't part of the column map in '", &_48$$38, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_47$$38, "__construct", &_8, 32, &_49$$38);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_47$$38, "phalcon/Mvc/Model.zep", 4187);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(&attributeField, identityField);
		}
		ZEPHIR_OBS_NVAR(&value);
		if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
			_50$$40 = Z_TYPE_P(&value) == IS_NULL;
			if (!(_50$$40)) {
				_50$$40 = ZEPHIR_IS_STRING_IDENTICAL(&value, "");
			}
			if (_50$$40) {
				if (useExplicitIdentity) {
					zephir_array_append(&values, &defaultValue, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4199);
					zephir_array_append(&bindTypes, &bindSkip, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4199);
				}
			} else {
				if (!(useExplicitIdentity)) {
					zephir_array_append(&fields, identityField, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4207);
				}
				ZEPHIR_OBS_NVAR(&bindType);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, identityField, 0)))) {
					ZEPHIR_INIT_VAR(&_51$$45);
					object_init_ex(&_51$$45, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_VAR(&_52$$45);
					zephir_get_class(&_52$$45, this_ptr, 0);
					ZEPHIR_INIT_VAR(&_53$$45);
					ZEPHIR_CONCAT_SVSVS(&_53$$45, "Identity column '", identityField, "' isn\'t part of the table columns in '", &_52$$45, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_51$$45, "__construct", &_8, 32, &_53$$45);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_51$$45, "phalcon/Mvc/Model.zep", 4216);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4219);
				zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4220);
			}
		} else {
			if (useExplicitIdentity) {
				zephir_array_append(&values, &defaultValue, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4224);
				zephir_array_append(&bindTypes, &bindSkip, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4225);
			}
		}
	}
	if (Z_TYPE_P(table) == IS_ARRAY) {
		zephir_memory_observe(&_54$$48);
		zephir_array_fetch_long(&_54$$48, table, 0, PH_NOISY, "phalcon/Mvc/Model.zep", 4234);
		zephir_memory_observe(&_55$$48);
		zephir_array_fetch_long(&_55$$48, table, 1, PH_NOISY, "phalcon/Mvc/Model.zep", 4234);
		ZEPHIR_INIT_VAR(&_56$$48);
		ZEPHIR_CONCAT_VSV(&_56$$48, &_54$$48, ".", &_55$$48);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(table, &_56$$48);
	}
	ZEPHIR_CALL_METHOD(&success, connection, "insert", NULL, 0, table, &values, &fields, &bindTypes);
	zephir_check_call_status();
	_57 = zephir_is_true(&success);
	if (_57) {
		_57 = !ZEPHIR_IS_FALSE_IDENTICAL(identityField);
	}
	if (_57) {
		ZEPHIR_INIT_VAR(&sequenceName);
		ZVAL_NULL(&sequenceName);
		ZEPHIR_CALL_METHOD(&_58$$49, connection, "supportSequences", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&_58$$49)) {
			if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("getsequencename")) == SUCCESS)) {
				ZEPHIR_CALL_METHOD(&sequenceName, this_ptr, "getSequenceName", NULL, 0);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(&source, this_ptr, "getSource", NULL, 465);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&schema, this_ptr, "getSchema", NULL, 464);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&sequenceName);
				if (ZEPHIR_IS_EMPTY(&schema)) {
					ZEPHIR_CONCAT_VSVS(&sequenceName, &source, "_", identityField, "_seq");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CONCAT_VSVSVS(&sequenceName, &schema, ".", &source, "_", identityField, "_seq");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			}
		}
		ZEPHIR_OBS_NVAR(&value);
		zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC);
		_59$$49 = Z_TYPE_P(&value) != IS_NULL;
		if (_59$$49) {
			_59$$49 = !ZEPHIR_IS_STRING_IDENTICAL(&value, "");
		}
		if (_59$$49) {
			ZEPHIR_CPY_WRT(&lastInsertedId, &value);
		} else {
			ZEPHIR_CALL_METHOD(&lastInsertedId, connection, "lastInsertId", NULL, 0, &sequenceName);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(&_61$$49);
		ZVAL_STRING(&_61$$49, "orm.cast_last_insert_id_to_int");
		ZEPHIR_CALL_CE_STATIC(&_60$$49, phalcon_support_settings_ce, "get", NULL, 0, &_61$$49);
		zephir_check_call_status();
		if (UNEXPECTED(zephir_is_true(&_60$$49))) {
			ZVAL_LONG(&_62$$57, 10);
			ZEPHIR_CALL_FUNCTION(&_63$$57, "intval", NULL, 41, &lastInsertedId, &_62$$57);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&lastInsertedId, &_63$$57);
		}
		zephir_update_property_zval_zval(this_ptr, &attributeField, &lastInsertedId);
		zephir_array_update_zval(&snapshot, &attributeField, &lastInsertedId, PH_COPY | PH_SEPARATE);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 719, &__$null);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 720, &__$null);
	}
	if (zephir_is_true(&success)) {
		if (Z_TYPE_P(&unsetDefaultValues) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_65$$58);
			zephir_string_to_char_array(&_65$$58, &unsetDefaultValues);
			_64$$58 = &_65$$58;
		} else {
			_64$$58 = &unsetDefaultValues;
		}
		zephir_is_iterable(_64$$58, 0, "phalcon/Mvc/Model.zep", 4307);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_64$$58), _67$$58, _68$$58, _66$$58)
		{
			ZEPHIR_INIT_NVAR(&attributeField);
			if (_68$$58 != NULL) { 
				ZVAL_STR_COPY(&attributeField, _68$$58);
			} else {
				ZVAL_LONG(&attributeField, _67$$58);
			}
			ZEPHIR_INIT_NVAR(&defaultValue);
			ZVAL_COPY(&defaultValue, _66$$58);
			zephir_update_property_zval_zval(this_ptr, &attributeField, &defaultValue);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&defaultValue);
		ZEPHIR_INIT_NVAR(&attributeField);
		ZEPHIR_CALL_METHOD(&_69$$58, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
		zephir_check_call_status();
		_70$$58 = zephir_is_true(&_69$$58);
		if (_70$$58) {
			ZEPHIR_INIT_VAR(&_72$$58);
			ZVAL_STRING(&_72$$58, "orm.update_snapshot_on_save");
			ZEPHIR_CALL_CE_STATIC(&_71$$58, phalcon_support_settings_ce, "get", NULL, 0, &_72$$58);
			zephir_check_call_status();
			_70$$58 = zephir_is_true(&_71$$58);
		}
		if (_70$$58) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 712, &snapshot);
		}
	}
	RETURN_CCTOR(&success);
}

/**
 * Sends a pre-build UPDATE SQL statement to the relational database system
 *
 * @param string|array table
 */
PHP_METHOD(Phalcon_Mvc_Model, doLowUpdate)
{
	zval _26$$25, _27$$25, _47$$48, _48$$48;
	zval _88;
	zend_bool changed = 0, useDynamicUpdate = 0, _3, _90, _92, _30$$5, _20$$19, _22$$19, _28$$26, _42$$42, _44$$42, _49$$49, _62$$53, _81$$73;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_13 = NULL, *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *metaData, metaData_sub, *connection, connection_sub, *table = NULL, table_sub, __$null, automaticAttributes, attributeField, bindSkip, bindDataTypes, bindType, bindTypes, columnMap, dataType, dataTypes, field, fields, manager, nonPrimary, newSnapshot, success, primaryKeys, snapshot, snapshotValue, uniqueKey, uniqueParams, value, values, updateValue, _0, _1, _2, _89, _91, _93, *_4$$5, _5$$5, *_6$$5, _29$$5, _7$$8, _9$$8, _10$$9, _11$$9, _12$$9, _14$$12, _15$$12, _16$$12, _17$$20, _18$$20, _19$$20, _21$$21, _23$$24, _25$$24, _31$$31, _32$$31, _33$$32, _34$$32, _35$$32, _36$$35, _37$$35, _38$$35, _39$$43, _40$$43, _41$$43, _43$$44, _45$$47, _46$$47, *_50$$53, _51$$53, *_52$$53, _61$$53, _53$$56, _54$$56, _55$$57, _56$$57, _57$$57, _58$$60, _59$$60, _60$$60, _63$$65, _64$$65, _65$$66, _66$$66, _67$$66, _68$$69, _69$$69, _70$$69, _71$$74, _72$$74, _73$$74, *_74$$73, _75$$73, *_76$$73, _80$$73, _77$$77, _78$$77, _79$$77, _82$$83, _83$$83, _84$$83, _85$$87, _86$$87, _87$$87, _94$$89, _95$$90;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData_sub);
	ZVAL_UNDEF(&connection_sub);
	ZVAL_UNDEF(&table_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&automaticAttributes);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&bindSkip);
	ZVAL_UNDEF(&bindDataTypes);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&dataType);
	ZVAL_UNDEF(&dataTypes);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&nonPrimary);
	ZVAL_UNDEF(&newSnapshot);
	ZVAL_UNDEF(&success);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&snapshot);
	ZVAL_UNDEF(&snapshotValue);
	ZVAL_UNDEF(&uniqueKey);
	ZVAL_UNDEF(&uniqueParams);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&updateValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_89);
	ZVAL_UNDEF(&_91);
	ZVAL_UNDEF(&_93);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_29$$5);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_14$$12);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$20);
	ZVAL_UNDEF(&_18$$20);
	ZVAL_UNDEF(&_19$$20);
	ZVAL_UNDEF(&_21$$21);
	ZVAL_UNDEF(&_23$$24);
	ZVAL_UNDEF(&_25$$24);
	ZVAL_UNDEF(&_31$$31);
	ZVAL_UNDEF(&_32$$31);
	ZVAL_UNDEF(&_33$$32);
	ZVAL_UNDEF(&_34$$32);
	ZVAL_UNDEF(&_35$$32);
	ZVAL_UNDEF(&_36$$35);
	ZVAL_UNDEF(&_37$$35);
	ZVAL_UNDEF(&_38$$35);
	ZVAL_UNDEF(&_39$$43);
	ZVAL_UNDEF(&_40$$43);
	ZVAL_UNDEF(&_41$$43);
	ZVAL_UNDEF(&_43$$44);
	ZVAL_UNDEF(&_45$$47);
	ZVAL_UNDEF(&_46$$47);
	ZVAL_UNDEF(&_51$$53);
	ZVAL_UNDEF(&_61$$53);
	ZVAL_UNDEF(&_53$$56);
	ZVAL_UNDEF(&_54$$56);
	ZVAL_UNDEF(&_55$$57);
	ZVAL_UNDEF(&_56$$57);
	ZVAL_UNDEF(&_57$$57);
	ZVAL_UNDEF(&_58$$60);
	ZVAL_UNDEF(&_59$$60);
	ZVAL_UNDEF(&_60$$60);
	ZVAL_UNDEF(&_63$$65);
	ZVAL_UNDEF(&_64$$65);
	ZVAL_UNDEF(&_65$$66);
	ZVAL_UNDEF(&_66$$66);
	ZVAL_UNDEF(&_67$$66);
	ZVAL_UNDEF(&_68$$69);
	ZVAL_UNDEF(&_69$$69);
	ZVAL_UNDEF(&_70$$69);
	ZVAL_UNDEF(&_71$$74);
	ZVAL_UNDEF(&_72$$74);
	ZVAL_UNDEF(&_73$$74);
	ZVAL_UNDEF(&_75$$73);
	ZVAL_UNDEF(&_80$$73);
	ZVAL_UNDEF(&_77$$77);
	ZVAL_UNDEF(&_78$$77);
	ZVAL_UNDEF(&_79$$77);
	ZVAL_UNDEF(&_82$$83);
	ZVAL_UNDEF(&_83$$83);
	ZVAL_UNDEF(&_84$$83);
	ZVAL_UNDEF(&_85$$87);
	ZVAL_UNDEF(&_86$$87);
	ZVAL_UNDEF(&_87$$87);
	ZVAL_UNDEF(&_94$$89);
	ZVAL_UNDEF(&_95$$90);
	ZVAL_UNDEF(&_88);
	ZVAL_UNDEF(&_26$$25);
	ZVAL_UNDEF(&_27$$25);
	ZVAL_UNDEF(&_47$$48);
	ZVAL_UNDEF(&_48$$48);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("snapshot", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("oldSnapshot", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("uniqueKey", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("uniqueParams", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("uniqueTypes", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(metaData, phalcon_mvc_model_metadatainterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(connection, phalcon_db_adapter_adapterinterface_ce)
		Z_PARAM_ZVAL(table)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &metaData, &connection, &table);
	ZEPHIR_SEPARATE_PARAM(table);
	ZEPHIR_INIT_VAR(&bindSkip);
	ZVAL_LONG(&bindSkip, 1024);
	ZEPHIR_INIT_VAR(&fields);
	array_init(&fields);
	ZEPHIR_INIT_VAR(&values);
	array_init(&values);
	ZEPHIR_INIT_VAR(&bindTypes);
	array_init(&bindTypes);
	ZEPHIR_INIT_VAR(&newSnapshot);
	array_init(&newSnapshot);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&_1, &manager, "isUsingDynamicUpdate", NULL, 0, this_ptr);
	zephir_check_call_status();
	useDynamicUpdate = zephir_get_boolval(&_1);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 712, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&snapshot, &_0);
	ZEPHIR_CALL_METHOD(&dataTypes, metaData, "getDataTypes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&bindDataTypes, metaData, "getBindTypes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&nonPrimary, metaData, "getNonPrimaryKeyAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&automaticAttributes, metaData, "getAutomaticUpdateAttributes", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "orm.column_renaming");
	ZEPHIR_CALL_CE_STATIC(&_1, phalcon_support_settings_ce, "get", NULL, 0, &_2);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_CALL_METHOD(&columnMap, metaData, "getColumnMap", NULL, 0, this_ptr);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&columnMap);
		ZVAL_NULL(&columnMap);
	}
	_3 = useDynamicUpdate;
	if (_3) {
		_3 = Z_TYPE_P(&snapshot) == IS_ARRAY;
	}
	if (EXPECTED(_3)) {
		if (Z_TYPE_P(&nonPrimary) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_5$$5);
			zephir_string_to_char_array(&_5$$5, &nonPrimary);
			_4$$5 = &_5$$5;
		} else {
			_4$$5 = &nonPrimary;
		}
		zephir_is_iterable(_4$$5, 0, "phalcon/Mvc/Model.zep", 4467);
		if (Z_TYPE_P(_4$$5) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$5), _6$$5)
			{
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _6$$5);
				changed = 0;
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_9$$8);
						ZVAL_STRING(&_9$$8, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_7$$8, phalcon_support_settings_ce, "get", &_8, 0, &_9$$8);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_7$$8))) {
							ZEPHIR_INIT_NVAR(&_10$$9);
							object_init_ex(&_10$$9, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_11$$9);
							zephir_get_class(&_11$$9, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_12$$9);
							ZEPHIR_CONCAT_SVSVS(&_12$$9, "Column '", &field, "' in '", &_11$$9, "' isn't part of the column map");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_10$$9, "__construct", &_13, 32, &_12$$9);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_10$$9, "phalcon/Mvc/Model.zep", 4361);
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &field);
				}
				if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
					ZEPHIR_OBS_NVAR(&bindType);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_14$$12);
						object_init_ex(&_14$$12, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_15$$12);
						zephir_get_class(&_15$$12, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_16$$12);
						ZEPHIR_CONCAT_SVSVS(&_16$$12, "Column '", &field, "' in '", &_15$$12, "' have not defined a bind data type");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_14$$12, "__construct", &_13, 32, &_16$$12);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_14$$12, "phalcon/Mvc/Model.zep", 4374);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&value);
					if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
						ZEPHIR_OBS_NVAR(&snapshotValue);
						if (!(zephir_array_isset_fetch(&snapshotValue, &snapshot, &attributeField, 0))) {
							changed = 1;
						} else {
							if (Z_TYPE_P(&value) == IS_NULL) {
								changed = Z_TYPE_P(&snapshotValue) != IS_NULL;
							} else {
								if (Z_TYPE_P(&snapshotValue) == IS_NULL) {
									changed = 1;
								} else {
									ZEPHIR_OBS_NVAR(&dataType);
									if (UNEXPECTED(!(zephir_array_isset_fetch(&dataType, &dataTypes, &field, 0)))) {
										ZEPHIR_INIT_NVAR(&_17$$20);
										object_init_ex(&_17$$20, phalcon_mvc_model_exception_ce);
										ZEPHIR_INIT_NVAR(&_18$$20);
										zephir_get_class(&_18$$20, this_ptr, 0);
										ZEPHIR_INIT_NVAR(&_19$$20);
										ZEPHIR_CONCAT_SVSVS(&_19$$20, "Column '", &field, "' in '", &_18$$20, "' have not defined a data type");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										ZEPHIR_CALL_METHOD(NULL, &_17$$20, "__construct", &_13, 32, &_19$$20);
										zephir_check_call_status();
										zephir_throw_exception_debug(&_17$$20, "phalcon/Mvc/Model.zep", 4404);
										ZEPHIR_MM_RESTORE();
										return;
									}
									_20$$19 = Z_TYPE_P(&snapshotValue) == IS_OBJECT;
									if (_20$$19) {
										_20$$19 = zephir_instance_of_ev(&snapshotValue, phalcon_db_rawvalue_ce);
									}
									if (_20$$19) {
										ZEPHIR_CALL_METHOD(&_21$$21, &snapshotValue, "getValue", NULL, 0);
										zephir_check_call_status();
										ZEPHIR_CPY_WRT(&snapshotValue, &_21$$21);
									}
									ZEPHIR_CPY_WRT(&updateValue, &value);
									_22$$19 = Z_TYPE_P(&value) == IS_OBJECT;
									if (_22$$19) {
										_22$$19 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
									}
									if (_22$$19) {
										ZEPHIR_CALL_METHOD(&updateValue, &value, "getValue", NULL, 0);
										zephir_check_call_status();
									}
									if (ZEPHIR_IS_LONG(&dataType, 8)) { goto zephir_switch_0_clause_0; }
									if (ZEPHIR_IS_LONG(&dataType, 3)) { goto zephir_switch_0_clause_1; }
									if (ZEPHIR_IS_LONG(&dataType, 7)) { goto zephir_switch_0_clause_2; }
									if (ZEPHIR_IS_LONG(&dataType, 0)) { goto zephir_switch_0_clause_3; }
									if (ZEPHIR_IS_LONG(&dataType, 1)) { goto zephir_switch_0_clause_4; }
									if (ZEPHIR_IS_LONG(&dataType, 2)) { goto zephir_switch_0_clause_5; }
									if (ZEPHIR_IS_LONG(&dataType, 4)) { goto zephir_switch_0_clause_6; }
									if (ZEPHIR_IS_LONG(&dataType, 5)) { goto zephir_switch_0_clause_7; }
									if (ZEPHIR_IS_LONG(&dataType, 6)) { goto zephir_switch_0_clause_8; }
									if (ZEPHIR_IS_LONG(&dataType, 2)) { goto zephir_switch_0_clause_9; }
									if (ZEPHIR_IS_LONG(&dataType, 14)) { goto zephir_switch_0_clause_10; }
									goto zephir_switch_0_clause_11;
									zephir_switch_0_clause_0: ;
										changed = zephir_get_boolval(&snapshotValue) != zephir_get_boolval(&updateValue);
										goto zephir_switch_0_end;
									zephir_switch_0_clause_1: ;
									zephir_switch_0_clause_2: ;
										ZEPHIR_CALL_FUNCTION(&_23$$24, "floatval", &_24, 17, &snapshotValue);
										zephir_check_call_status();
										ZEPHIR_CALL_FUNCTION(&_25$$24, "floatval", &_24, 17, &updateValue);
										zephir_check_call_status();
										changed = !ZEPHIR_IS_IDENTICAL(&_23$$24, &_25$$24);
										goto zephir_switch_0_end;
									zephir_switch_0_clause_3: ;
									zephir_switch_0_clause_4: ;
									zephir_switch_0_clause_5: ;
									zephir_switch_0_clause_6: ;
									zephir_switch_0_clause_7: ;
									zephir_switch_0_clause_8: ;
									zephir_switch_0_clause_9: ;
									zephir_switch_0_clause_10: ;
										zephir_cast_to_string(&_26$$25, &snapshotValue);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										zephir_cast_to_string(&_27$$25, &updateValue);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										changed = !ZEPHIR_IS_IDENTICAL(&_26$$25, &_27$$25);
										goto zephir_switch_0_end;
									zephir_switch_0_clause_11: ;
										_28$$26 = !ZEPHIR_IS_EQUAL(&updateValue, &snapshotValue);
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										changed = _28$$26;
									zephir_switch_0_end: ;

								}
							}
						}
						if (changed) {
							zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4454);
							zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4455);
							zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4456);
						}
						zephir_array_update_zval(&newSnapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
					} else {
						zephir_array_update_zval(&newSnapshot, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _4$$5, "rewind", NULL, 0);
			zephir_check_call_status();
			_30$$5 = 1;
			while (1) {
				if (_30$$5) {
					_30$$5 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _4$$5, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_29$$5, _4$$5, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_29$$5)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _4$$5, "current", NULL, 0);
				zephir_check_call_status();
					changed = 0;
					if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attributeField);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_32$$31);
							ZVAL_STRING(&_32$$31, "orm.ignore_unknown_columns");
							ZEPHIR_CALL_CE_STATIC(&_31$$31, phalcon_support_settings_ce, "get", &_8, 0, &_32$$31);
							zephir_check_call_status();
							if (UNEXPECTED(!zephir_is_true(&_31$$31))) {
								ZEPHIR_INIT_NVAR(&_33$$32);
								object_init_ex(&_33$$32, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_34$$32);
								zephir_get_class(&_34$$32, this_ptr, 0);
								ZEPHIR_INIT_NVAR(&_35$$32);
								ZEPHIR_CONCAT_SVSVS(&_35$$32, "Column '", &field, "' in '", &_34$$32, "' isn't part of the column map");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_33$$32, "__construct", &_13, 32, &_35$$32);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_33$$32, "phalcon/Mvc/Model.zep", 4361);
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					} else {
						ZEPHIR_CPY_WRT(&attributeField, &field);
					}
					if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
						ZEPHIR_OBS_NVAR(&bindType);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_36$$35);
							object_init_ex(&_36$$35, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_37$$35);
							zephir_get_class(&_37$$35, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_38$$35);
							ZEPHIR_CONCAT_SVSVS(&_38$$35, "Column '", &field, "' in '", &_37$$35, "' have not defined a bind data type");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_36$$35, "__construct", &_13, 32, &_38$$35);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_36$$35, "phalcon/Mvc/Model.zep", 4374);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_OBS_NVAR(&value);
						if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
							ZEPHIR_OBS_NVAR(&snapshotValue);
							if (!(zephir_array_isset_fetch(&snapshotValue, &snapshot, &attributeField, 0))) {
								changed = 1;
							} else {
								if (Z_TYPE_P(&value) == IS_NULL) {
									changed = Z_TYPE_P(&snapshotValue) != IS_NULL;
								} else {
									if (Z_TYPE_P(&snapshotValue) == IS_NULL) {
										changed = 1;
									} else {
										ZEPHIR_OBS_NVAR(&dataType);
										if (UNEXPECTED(!(zephir_array_isset_fetch(&dataType, &dataTypes, &field, 0)))) {
											ZEPHIR_INIT_NVAR(&_39$$43);
											object_init_ex(&_39$$43, phalcon_mvc_model_exception_ce);
											ZEPHIR_INIT_NVAR(&_40$$43);
											zephir_get_class(&_40$$43, this_ptr, 0);
											ZEPHIR_INIT_NVAR(&_41$$43);
											ZEPHIR_CONCAT_SVSVS(&_41$$43, "Column '", &field, "' in '", &_40$$43, "' have not defined a data type");
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											ZEPHIR_CALL_METHOD(NULL, &_39$$43, "__construct", &_13, 32, &_41$$43);
											zephir_check_call_status();
											zephir_throw_exception_debug(&_39$$43, "phalcon/Mvc/Model.zep", 4404);
											ZEPHIR_MM_RESTORE();
											return;
										}
										_42$$42 = Z_TYPE_P(&snapshotValue) == IS_OBJECT;
										if (_42$$42) {
											_42$$42 = zephir_instance_of_ev(&snapshotValue, phalcon_db_rawvalue_ce);
										}
										if (_42$$42) {
											ZEPHIR_CALL_METHOD(&_43$$44, &snapshotValue, "getValue", NULL, 0);
											zephir_check_call_status();
											ZEPHIR_CPY_WRT(&snapshotValue, &_43$$44);
										}
										ZEPHIR_CPY_WRT(&updateValue, &value);
										_44$$42 = Z_TYPE_P(&value) == IS_OBJECT;
										if (_44$$42) {
											_44$$42 = zephir_instance_of_ev(&value, phalcon_db_rawvalue_ce);
										}
										if (_44$$42) {
											ZEPHIR_CALL_METHOD(&updateValue, &value, "getValue", NULL, 0);
											zephir_check_call_status();
										}
										if (ZEPHIR_IS_LONG(&dataType, 8)) { goto zephir_switch_1_clause_0; }
										if (ZEPHIR_IS_LONG(&dataType, 3)) { goto zephir_switch_1_clause_1; }
										if (ZEPHIR_IS_LONG(&dataType, 7)) { goto zephir_switch_1_clause_2; }
										if (ZEPHIR_IS_LONG(&dataType, 0)) { goto zephir_switch_1_clause_3; }
										if (ZEPHIR_IS_LONG(&dataType, 1)) { goto zephir_switch_1_clause_4; }
										if (ZEPHIR_IS_LONG(&dataType, 2)) { goto zephir_switch_1_clause_5; }
										if (ZEPHIR_IS_LONG(&dataType, 4)) { goto zephir_switch_1_clause_6; }
										if (ZEPHIR_IS_LONG(&dataType, 5)) { goto zephir_switch_1_clause_7; }
										if (ZEPHIR_IS_LONG(&dataType, 6)) { goto zephir_switch_1_clause_8; }
										if (ZEPHIR_IS_LONG(&dataType, 2)) { goto zephir_switch_1_clause_9; }
										if (ZEPHIR_IS_LONG(&dataType, 14)) { goto zephir_switch_1_clause_10; }
										goto zephir_switch_1_clause_11;
										zephir_switch_1_clause_0: ;
											changed = zephir_get_boolval(&snapshotValue) != zephir_get_boolval(&updateValue);
											goto zephir_switch_1_end;
										zephir_switch_1_clause_1: ;
										zephir_switch_1_clause_2: ;
											ZEPHIR_CALL_FUNCTION(&_45$$47, "floatval", &_24, 17, &snapshotValue);
											zephir_check_call_status();
											ZEPHIR_CALL_FUNCTION(&_46$$47, "floatval", &_24, 17, &updateValue);
											zephir_check_call_status();
											changed = !ZEPHIR_IS_IDENTICAL(&_45$$47, &_46$$47);
											goto zephir_switch_1_end;
										zephir_switch_1_clause_3: ;
										zephir_switch_1_clause_4: ;
										zephir_switch_1_clause_5: ;
										zephir_switch_1_clause_6: ;
										zephir_switch_1_clause_7: ;
										zephir_switch_1_clause_8: ;
										zephir_switch_1_clause_9: ;
										zephir_switch_1_clause_10: ;
											zephir_cast_to_string(&_47$$48, &snapshotValue);
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											zephir_cast_to_string(&_48$$48, &updateValue);
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											changed = !ZEPHIR_IS_IDENTICAL(&_47$$48, &_48$$48);
											goto zephir_switch_1_end;
										zephir_switch_1_clause_11: ;
											_49$$49 = !ZEPHIR_IS_EQUAL(&updateValue, &snapshotValue);
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											changed = _49$$49;
										zephir_switch_1_end: ;

									}
								}
							}
							if (changed) {
								zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4454);
								zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4455);
								zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4456);
							}
							zephir_array_update_zval(&newSnapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
						} else {
							zephir_array_update_zval(&newSnapshot, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
						}
					}
			}
		}
		ZEPHIR_INIT_NVAR(&field);
		if (!(zephir_fast_count_int(&fields))) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 718, &snapshot);
			RETURN_MM_BOOL(1);
		}
	} else {
		if (Z_TYPE_P(&nonPrimary) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_51$$53);
			zephir_string_to_char_array(&_51$$53, &nonPrimary);
			_50$$53 = &_51$$53;
		} else {
			_50$$53 = &nonPrimary;
		}
		zephir_is_iterable(_50$$53, 0, "phalcon/Mvc/Model.zep", 4522);
		if (Z_TYPE_P(_50$$53) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_50$$53), _52$$53)
			{
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _52$$53);
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_54$$56);
						ZVAL_STRING(&_54$$56, "orm.ignore_unknown_columns");
						ZEPHIR_CALL_CE_STATIC(&_53$$56, phalcon_support_settings_ce, "get", &_8, 0, &_54$$56);
						zephir_check_call_status();
						if (UNEXPECTED(!zephir_is_true(&_53$$56))) {
							ZEPHIR_INIT_NVAR(&_55$$57);
							object_init_ex(&_55$$57, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_56$$57);
							zephir_get_class(&_56$$57, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_57$$57);
							ZEPHIR_CONCAT_SVSVS(&_57$$57, "Column '", &field, "' in '", &_56$$57, "' isn't part of the column map");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_55$$57, "__construct", &_13, 32, &_57$$57);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_55$$57, "phalcon/Mvc/Model.zep", 4485);
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &field);
				}
				if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
					ZEPHIR_OBS_NVAR(&bindType);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_58$$60);
						object_init_ex(&_58$$60, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_59$$60);
						zephir_get_class(&_59$$60, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_60$$60);
						ZEPHIR_CONCAT_SVSVS(&_60$$60, "Column '", &field, "' in '", &_59$$60, "' have not defined a bind data type");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_58$$60, "__construct", &_13, 32, &_60$$60);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_58$$60, "phalcon/Mvc/Model.zep", 4499);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&value);
					if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
						zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4510);
						zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4511);
						zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4512);
						zephir_array_update_zval(&newSnapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
					} else {
						zephir_array_update_zval(&newSnapshot, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
						zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4516);
						zephir_array_append(&values, &__$null, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4517);
						zephir_array_append(&bindTypes, &bindSkip, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4518);
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _50$$53, "rewind", NULL, 0);
			zephir_check_call_status();
			_62$$53 = 1;
			while (1) {
				if (_62$$53) {
					_62$$53 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _50$$53, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_61$$53, _50$$53, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_61$$53)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _50$$53, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attributeField);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_64$$65);
							ZVAL_STRING(&_64$$65, "orm.ignore_unknown_columns");
							ZEPHIR_CALL_CE_STATIC(&_63$$65, phalcon_support_settings_ce, "get", &_8, 0, &_64$$65);
							zephir_check_call_status();
							if (UNEXPECTED(!zephir_is_true(&_63$$65))) {
								ZEPHIR_INIT_NVAR(&_65$$66);
								object_init_ex(&_65$$66, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_66$$66);
								zephir_get_class(&_66$$66, this_ptr, 0);
								ZEPHIR_INIT_NVAR(&_67$$66);
								ZEPHIR_CONCAT_SVSVS(&_67$$66, "Column '", &field, "' in '", &_66$$66, "' isn't part of the column map");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_65$$66, "__construct", &_13, 32, &_67$$66);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_65$$66, "phalcon/Mvc/Model.zep", 4485);
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					} else {
						ZEPHIR_CPY_WRT(&attributeField, &field);
					}
					if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
						ZEPHIR_OBS_NVAR(&bindType);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&bindType, &bindDataTypes, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_68$$69);
							object_init_ex(&_68$$69, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_69$$69);
							zephir_get_class(&_69$$69, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_70$$69);
							ZEPHIR_CONCAT_SVSVS(&_70$$69, "Column '", &field, "' in '", &_69$$69, "' have not defined a bind data type");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_68$$69, "__construct", &_13, 32, &_70$$69);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_68$$69, "phalcon/Mvc/Model.zep", 4499);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_OBS_NVAR(&value);
						if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
							zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4510);
							zephir_array_append(&values, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4511);
							zephir_array_append(&bindTypes, &bindType, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4512);
							zephir_array_update_zval(&newSnapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
						} else {
							zephir_array_update_zval(&newSnapshot, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
							zephir_array_append(&fields, &field, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4516);
							zephir_array_append(&values, &__$null, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4517);
							zephir_array_append(&bindTypes, &bindSkip, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4518);
						}
					}
			}
		}
		ZEPHIR_INIT_NVAR(&field);
	}
	if (!(zephir_fast_count_int(&fields))) {
		RETURN_MM_BOOL(1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 719, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&uniqueKey, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 720, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&uniqueParams, &_0);
	if (Z_TYPE_P(&uniqueParams) != IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&primaryKeys, metaData, "getPrimaryKeyAttributes", NULL, 0, this_ptr);
		zephir_check_call_status();
		if (UNEXPECTED(!(zephir_fast_count_int(&primaryKeys)))) {
			ZEPHIR_INIT_VAR(&_71$$74);
			object_init_ex(&_71$$74, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(&_72$$74);
			zephir_get_class(&_72$$74, this_ptr, 0);
			ZEPHIR_INIT_VAR(&_73$$74);
			ZEPHIR_CONCAT_SVS(&_73$$74, "A primary key must be defined in the model in order to perform the operation in '", &_72$$74, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_71$$74, "__construct", &_13, 32, &_73$$74);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_71$$74, "phalcon/Mvc/Model.zep", 4545);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(&uniqueParams);
		array_init(&uniqueParams);
		if (Z_TYPE_P(&primaryKeys) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_75$$73);
			zephir_string_to_char_array(&_75$$73, &primaryKeys);
			_74$$73 = &_75$$73;
		} else {
			_74$$73 = &primaryKeys;
		}
		zephir_is_iterable(_74$$73, 0, "phalcon/Mvc/Model.zep", 4572);
		if (Z_TYPE_P(_74$$73) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_74$$73), _76$$73)
			{
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _76$$73);
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_77$$77);
						object_init_ex(&_77$$77, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_78$$77);
						zephir_get_class(&_78$$77, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_79$$77);
						ZEPHIR_CONCAT_SVSVS(&_79$$77, "Column '", &field, "' in '", &_78$$77, "' isn't part of the column map");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_77$$77, "__construct", &_13, 32, &_79$$77);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_77$$77, "phalcon/Mvc/Model.zep", 4558);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &field);
				}
				ZEPHIR_OBS_NVAR(&value);
				if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
					zephir_array_update_zval(&newSnapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
					zephir_array_append(&uniqueParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4566);
				} else {
					zephir_array_update_zval(&newSnapshot, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
					zephir_array_append(&uniqueParams, &__$null, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4569);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _74$$73, "rewind", NULL, 0);
			zephir_check_call_status();
			_81$$73 = 1;
			while (1) {
				if (_81$$73) {
					_81$$73 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _74$$73, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_80$$73, _74$$73, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_80$$73)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _74$$73, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attributeField);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_82$$83);
							object_init_ex(&_82$$83, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_83$$83);
							zephir_get_class(&_83$$83, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_84$$83);
							ZEPHIR_CONCAT_SVSVS(&_84$$83, "Column '", &field, "' in '", &_83$$83, "' isn't part of the column map");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_82$$83, "__construct", &_13, 32, &_84$$83);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_82$$83, "phalcon/Mvc/Model.zep", 4558);
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CPY_WRT(&attributeField, &field);
					}
					ZEPHIR_OBS_NVAR(&value);
					if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
						zephir_array_update_zval(&newSnapshot, &attributeField, &value, PH_COPY | PH_SEPARATE);
						zephir_array_append(&uniqueParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4566);
					} else {
						zephir_array_update_zval(&newSnapshot, &attributeField, &__$null, PH_COPY | PH_SEPARATE);
						zephir_array_append(&uniqueParams, &__$null, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4569);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&field);
	}
	if (Z_TYPE_P(table) == IS_ARRAY) {
		zephir_memory_observe(&_85$$87);
		zephir_array_fetch_long(&_85$$87, table, 0, PH_NOISY, "phalcon/Mvc/Model.zep", 4578);
		zephir_memory_observe(&_86$$87);
		zephir_array_fetch_long(&_86$$87, table, 1, PH_NOISY, "phalcon/Mvc/Model.zep", 4578);
		ZEPHIR_INIT_VAR(&_87$$87);
		ZEPHIR_CONCAT_VSV(&_87$$87, &_85$$87, ".", &_86$$87);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(table, &_87$$87);
	}
	ZEPHIR_INIT_VAR(&_88);
	zephir_create_array(&_88, 3, 0);
	zephir_array_update_string(&_88, SL("conditions"), &uniqueKey, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_88, SL("bind"), &uniqueParams, PH_COPY | PH_SEPARATE);
	zephir_memory_observe(&_89);
	zephir_read_property_cached(&_89, this_ptr, _zephir_prop_5, 721, PH_NOISY_CC);
	zephir_array_update_string(&_88, SL("bindTypes"), &_89, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&success, connection, "update", NULL, 0, table, &fields, &values, &_88, &bindTypes);
	zephir_check_call_status();
	_90 = zephir_is_true(&success);
	if (_90) {
		ZEPHIR_CALL_METHOD(&_91, &manager, "isKeepingSnapshots", NULL, 0, this_ptr);
		zephir_check_call_status();
		_90 = zephir_is_true(&_91);
	}
	_92 = _90;
	if (_92) {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_STRING(&_2, "orm.update_snapshot_on_save");
		ZEPHIR_CALL_CE_STATIC(&_93, phalcon_support_settings_ce, "get", &_8, 0, &_2);
		zephir_check_call_status();
		_92 = zephir_is_true(&_93);
	}
	if (_92) {
		if (Z_TYPE_P(&snapshot) == IS_ARRAY) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 718, &snapshot);
			ZEPHIR_INIT_VAR(&_94$$89);
			zephir_fast_array_merge(&_94$$89, &snapshot, &newSnapshot);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 712, &_94$$89);
		} else {
			ZEPHIR_INIT_VAR(&_95$$90);
			array_init(&_95$$90);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 718, &_95$$90);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 712, &newSnapshot);
		}
	}
	RETURN_CCTOR(&success);
}

/**
 * Checks whether the current record already exists
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model, has)
{
	zend_bool _17$$3, _9$$11, _21$$19;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_14 = NULL, *_26 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, numberEmpty = 0, numberPrimary = 0;
	zval *metaData, metaData_sub, *connection, connection_sub, __$null, attributeField, bindDataTypes, columnMap, field, joinWhere, num, primaryKeys, schema, source, table, type, uniqueKey, uniqueParams, uniqueTypes, value, wherePk, _0, _31, _32, _33, _34, _1$$3, _2$$3, *_3$$3, *_4$$3, _16$$3, _5$$9, _6$$9, _7$$9, _10$$14, _11$$14, _12$$14, _13$$7, _15$$7, _18$$17, _19$$17, _20$$17, _22$$22, _23$$22, _24$$22, _25$$15, _27$$15, _28$$25, _29$$26, _30$$27, _35$$30, _36$$31;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData_sub);
	ZVAL_UNDEF(&connection_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&bindDataTypes);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&joinWhere);
	ZVAL_UNDEF(&num);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&uniqueKey);
	ZVAL_UNDEF(&uniqueParams);
	ZVAL_UNDEF(&uniqueTypes);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&wherePk);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_5$$9);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_10$$14);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_12$$14);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_18$$17);
	ZVAL_UNDEF(&_19$$17);
	ZVAL_UNDEF(&_20$$17);
	ZVAL_UNDEF(&_22$$22);
	ZVAL_UNDEF(&_23$$22);
	ZVAL_UNDEF(&_24$$22);
	ZVAL_UNDEF(&_25$$15);
	ZVAL_UNDEF(&_27$$15);
	ZVAL_UNDEF(&_28$$25);
	ZVAL_UNDEF(&_29$$26);
	ZVAL_UNDEF(&_30$$27);
	ZVAL_UNDEF(&_35$$30);
	ZVAL_UNDEF(&_36$$31);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uniqueKey", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("uniqueParams", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("uniqueTypes", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("dirtyState", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(metaData, phalcon_mvc_model_metadatainterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(connection, phalcon_db_adapter_adapterinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &metaData, &connection);
	ZEPHIR_INIT_VAR(&uniqueParams);
	ZVAL_NULL(&uniqueParams);
	ZEPHIR_INIT_VAR(&uniqueTypes);
	ZVAL_NULL(&uniqueTypes);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 719, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&uniqueKey, &_0);
	if (Z_TYPE_P(&uniqueKey) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&primaryKeys, metaData, "getPrimaryKeyAttributes", NULL, 0, this_ptr);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&bindDataTypes, metaData, "getBindTypes", NULL, 0, this_ptr);
		zephir_check_call_status();
		numberPrimary = zephir_fast_count_int(&primaryKeys);
		if (!(numberPrimary)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "orm.column_renaming");
		ZEPHIR_CALL_CE_STATIC(&_1$$3, phalcon_support_settings_ce, "get", NULL, 0, &_2$$3);
		zephir_check_call_status();
		if (zephir_is_true(&_1$$3)) {
			ZEPHIR_CALL_METHOD(&columnMap, metaData, "getColumnMap", NULL, 0, this_ptr);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&columnMap);
			ZVAL_NULL(&columnMap);
		}
		numberEmpty = 0;
		ZEPHIR_INIT_VAR(&wherePk);
		array_init(&wherePk);
		ZEPHIR_INIT_NVAR(&uniqueParams);
		array_init(&uniqueParams);
		ZEPHIR_INIT_NVAR(&uniqueTypes);
		array_init(&uniqueTypes);
		if (Z_TYPE_P(&primaryKeys) == IS_STRING) {
			ZEPHIR_INIT_NVAR(&_2$$3);
			zephir_string_to_char_array(&_2$$3, &primaryKeys);
			_3$$3 = &_2$$3;
		} else {
			_3$$3 = &primaryKeys;
		}
		zephir_is_iterable(_3$$3, 0, "phalcon/Mvc/Model.zep", 4702);
		if (Z_TYPE_P(_3$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3$$3), _4$$3)
			{
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _4$$3);
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_5$$9);
						object_init_ex(&_5$$9, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_6$$9);
						zephir_get_class(&_6$$9, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_7$$9);
						ZEPHIR_CONCAT_SVSVS(&_7$$9, "Column '", &field, "' in '", &_6$$9, "' isn't part of the column map");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_5$$9, "__construct", &_8, 32, &_7$$9);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_5$$9, "phalcon/Mvc/Model.zep", 4661);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &field);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_NULL(&value);
				ZEPHIR_OBS_NVAR(&value);
				if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
					_9$$11 = Z_TYPE_P(&value) == IS_NULL;
					if (!(_9$$11)) {
						_9$$11 = ZEPHIR_IS_STRING_IDENTICAL(&value, "");
					}
					if (_9$$11) {
						numberEmpty++;
					}
					zephir_array_append(&uniqueParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4682);
				} else {
					zephir_array_append(&uniqueParams, &__$null, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4684);
					numberEmpty++;
				}
				ZEPHIR_OBS_NVAR(&type);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&type, &bindDataTypes, &field, 0)))) {
					ZEPHIR_INIT_NVAR(&_10$$14);
					object_init_ex(&_10$$14, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_11$$14);
					zephir_get_class(&_11$$14, this_ptr, 0);
					ZEPHIR_INIT_NVAR(&_12$$14);
					ZEPHIR_CONCAT_SVSVS(&_12$$14, "Column '", &field, "' in '", &_11$$14, "' isn't part of the table columns");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_10$$14, "__construct", &_8, 32, &_12$$14);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_10$$14, "phalcon/Mvc/Model.zep", 4691);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&uniqueTypes, &type, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4694);
				ZEPHIR_CALL_METHOD(&_13$$7, connection, "escapeIdentifier", &_14, 0, &field);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$7);
				ZEPHIR_CONCAT_VS(&_15$$7, &_13$$7, " = ?");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&wherePk, &_15$$7, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4695);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _3$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_17$$3 = 1;
			while (1) {
				if (_17$$3) {
					_17$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _3$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_16$$3, _3$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_16$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&field, _3$$3, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attributeField);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_18$$17);
							object_init_ex(&_18$$17, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_19$$17);
							zephir_get_class(&_19$$17, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_20$$17);
							ZEPHIR_CONCAT_SVSVS(&_20$$17, "Column '", &field, "' in '", &_19$$17, "' isn't part of the column map");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_18$$17, "__construct", &_8, 32, &_20$$17);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_18$$17, "phalcon/Mvc/Model.zep", 4661);
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CPY_WRT(&attributeField, &field);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_NULL(&value);
					ZEPHIR_OBS_NVAR(&value);
					if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
						_21$$19 = Z_TYPE_P(&value) == IS_NULL;
						if (!(_21$$19)) {
							_21$$19 = ZEPHIR_IS_STRING_IDENTICAL(&value, "");
						}
						if (_21$$19) {
							numberEmpty++;
						}
						zephir_array_append(&uniqueParams, &value, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4682);
					} else {
						zephir_array_append(&uniqueParams, &__$null, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4684);
						numberEmpty++;
					}
					ZEPHIR_OBS_NVAR(&type);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&type, &bindDataTypes, &field, 0)))) {
						ZEPHIR_INIT_NVAR(&_22$$22);
						object_init_ex(&_22$$22, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_23$$22);
						zephir_get_class(&_23$$22, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_24$$22);
						ZEPHIR_CONCAT_SVSVS(&_24$$22, "Column '", &field, "' in '", &_23$$22, "' isn't part of the table columns");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_22$$22, "__construct", &_8, 32, &_24$$22);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_22$$22, "phalcon/Mvc/Model.zep", 4691);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&uniqueTypes, &type, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4694);
					ZEPHIR_CALL_METHOD(&_25$$15, connection, "escapeIdentifier", &_26, 0, &field);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_27$$15);
					ZEPHIR_CONCAT_VS(&_27$$15, &_25$$15, " = ?");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&wherePk, &_27$$15, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4695);
			}
		}
		ZEPHIR_INIT_NVAR(&field);
		if (numberPrimary == numberEmpty) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_VAR(&joinWhere);
		zephir_fast_join_str(&joinWhere, SL(" AND "), &wherePk);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 719, &joinWhere);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 720, &uniqueParams);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 721, &uniqueTypes);
		ZEPHIR_CPY_WRT(&uniqueKey, &joinWhere);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 711, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(1);
	}
	if (Z_TYPE_P(&uniqueKey) == IS_NULL) {
		zephir_read_property_cached(&_28$$25, this_ptr, _zephir_prop_0, 719, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&uniqueKey, &_28$$25);
	}
	if (Z_TYPE_P(&uniqueParams) == IS_NULL) {
		zephir_read_property_cached(&_29$$26, this_ptr, _zephir_prop_1, 720, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&uniqueParams, &_29$$26);
	}
	if (Z_TYPE_P(&uniqueTypes) == IS_NULL) {
		zephir_read_property_cached(&_30$$27, this_ptr, _zephir_prop_2, 721, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&uniqueTypes, &_30$$27);
	}
	ZEPHIR_CALL_METHOD(&schema, this_ptr, "getSchema", NULL, 464);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, this_ptr, "getSource", NULL, 465);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		ZEPHIR_INIT_VAR(&table);
		zephir_create_array(&table, 2, 0);
		zephir_array_fast_append(&table, &schema);
		zephir_array_fast_append(&table, &source);
	} else {
		ZEPHIR_CPY_WRT(&table, &source);
	}
	ZEPHIR_CALL_METHOD(&_31, connection, "escapeIdentifier", NULL, 0, &table);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_32);
	ZEPHIR_CONCAT_SVSV(&_32, "SELECT COUNT(*) \"rowcount\" FROM ", &_31, " WHERE ", &uniqueKey);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_NULL(&_33);
	ZEPHIR_CALL_METHOD(&num, connection, "fetchOne", NULL, 0, &_32, &_33, &uniqueParams, &uniqueTypes);
	zephir_check_call_status();
	zephir_memory_observe(&_34);
	zephir_array_fetch_string(&_34, &num, SL("rowcount"), PH_NOISY, "phalcon/Mvc/Model.zep", 4756);
	if (zephir_is_true(&_34)) {
		ZVAL_UNDEF(&_35$$30);
		ZVAL_LONG(&_35$$30, 0);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 711, &_35$$30);
		RETURN_MM_BOOL(1);
	} else {
		ZVAL_UNDEF(&_36$$31);
		ZVAL_LONG(&_36$$31, 1);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 711, &_36$$31);
	}
	RETURN_MM_BOOL(0);
}

/**
 * Returns related records defined relations depending on the method name.
 * Returns false if the relation is non-existent.
 *
 * @param string modelName
 * @param string method
 * @param array  arguments
 *
 * @return ResultsetInterface|ModelInterface|bool|null
 */
PHP_METHOD(Phalcon_Mvc_Model, getRelatedRecords)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval arguments;
	zval modelName_zv, method_zv, *arguments_param = NULL, manager, relation, queryMethod, extraArgs, alias, _0, _1$$3, _2$$3, _3$$5, _4$$5, _5$$5;
	zend_string *modelName = NULL, *method = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&modelName_zv);
	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&queryMethod);
	ZVAL_UNDEF(&extraArgs);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&arguments);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(modelName)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	arguments_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&modelName_zv);
	ZVAL_STR_COPY(&modelName_zv, modelName);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	ZEPHIR_OBS_COPY_OR_DUP(&arguments, arguments_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_INIT_VAR(&relation);
	ZVAL_BOOL(&relation, 0);
	ZEPHIR_INIT_VAR(&queryMethod);
	ZVAL_NULL(&queryMethod);
	zephir_memory_observe(&extraArgs);
	zephir_array_isset_long_fetch(&extraArgs, &arguments, 0, 0);
	if (zephir_start_with_str(&method_zv, SL("get"))) {
		ZVAL_LONG(&_1$$3, 3);
		ZEPHIR_INIT_VAR(&alias);
		zephir_substr(&alias, &method_zv, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_CALL_METHOD(&_2$$3, &manager, "getRelationByAlias", NULL, 0, &modelName_zv, &alias);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&relation, &_2$$3);
		if (Z_TYPE_P(&relation) != IS_OBJECT) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getRelated", NULL, 0, &alias, &extraArgs);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(&method_zv, SL("count"))) {
		ZEPHIR_INIT_NVAR(&queryMethod);
		ZVAL_STRING(&queryMethod, "count");
		ZVAL_LONG(&_4$$5, 5);
		ZEPHIR_INIT_VAR(&_5$$5);
		zephir_substr(&_5$$5, &method_zv, 5 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_CALL_METHOD(&_3$$5, &manager, "getRelationByAlias", NULL, 0, &modelName_zv, &_5$$5);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&relation, &_3$$5);
		if (Z_TYPE_P(&relation) != IS_OBJECT) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_RETURN_CALL_METHOD(&manager, "getRelationRecords", NULL, 0, &relation, this_ptr, &extraArgs, &queryMethod);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);
}

/**
 * Generate a PHQL SELECT statement for an aggregate
 *
 * @param string functionName
 * @param string alias
 * @param array|string|null parameters
 *
 * @return ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, groupResult)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval functionName_zv, alias_zv, *parameters = NULL, parameters_sub, __$null, params, distinctColumn, groupColumn, columns, resultset, cache, firstRow, groupColumns, builder, query, container, manager, transaction, bindParams, bindTypes, _0, _1, _2;
	zend_string *functionName = NULL, *alias = NULL;

	ZVAL_UNDEF(&functionName_zv);
	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&parameters_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&distinctColumn);
	ZVAL_UNDEF(&groupColumn);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&resultset);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&firstRow);
	ZVAL_UNDEF(&groupColumns);
	ZVAL_UNDEF(&builder);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&transaction);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(functionName)
		Z_PARAM_STR(alias)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(parameters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		parameters = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&functionName_zv);
	ZVAL_STR_COPY(&functionName_zv, functionName);
	zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	if (!parameters) {
		parameters = &parameters_sub;
		parameters = &__$null;
	}
	ZEPHIR_INIT_VAR(&bindParams);
	array_init(&bindParams);
	ZEPHIR_INIT_VAR(&bindTypes);
	array_init(&bindTypes);
	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "modelsManager");
	ZEPHIR_CALL_METHOD(&_0, &container, "getShared", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_0);
	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
		if (Z_TYPE_P(parameters) != IS_NULL) {
			zephir_array_append(&params, parameters, PH_SEPARATE, "phalcon/Mvc/Model.zep", 4861);
		}
	} else {
		ZEPHIR_CPY_WRT(&params, parameters);
	}
	zephir_memory_observe(&groupColumn);
	if (!(zephir_array_isset_string_fetch(&groupColumn, &params, SL("column"), 0))) {
		ZEPHIR_INIT_NVAR(&groupColumn);
		ZVAL_STRING(&groupColumn, "*");
	}
	zephir_memory_observe(&distinctColumn);
	if (zephir_array_isset_string_fetch(&distinctColumn, &params, SL("distinct"), 0)) {
		ZEPHIR_INIT_VAR(&columns);
		ZEPHIR_CONCAT_VSVSV(&columns, &functionName_zv, "(DISTINCT ", &distinctColumn, ") AS ", &alias_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		zephir_memory_observe(&groupColumns);
		ZEPHIR_INIT_NVAR(&columns);
		if (zephir_array_isset_string_fetch(&groupColumns, &params, SL("group"), 0)) {
			ZEPHIR_CONCAT_VSVSVSV(&columns, &groupColumns, ", ", &functionName_zv, "(", &groupColumn, ") AS ", &alias_zv);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CONCAT_VSVSV(&columns, &functionName_zv, "(", &groupColumn, ") AS ", &alias_zv);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(&_0, &manager, "createBuilder", NULL, 0, &params);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&builder, &_0);
	ZEPHIR_CALL_METHOD(NULL, &builder, "columns", NULL, 0, &columns);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	zephir_get_called_class(&_1);
	ZEPHIR_CALL_METHOD(NULL, &builder, "from", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &builder, "getQuery", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&query, &_0);
	zephir_memory_observe(&transaction);
	if (zephir_array_isset_string_fetch(&transaction, &params, SL("transaction"), 0)) {
		if (zephir_instance_of_ev(&transaction, phalcon_mvc_model_transactioninterface_ce)) {
			ZEPHIR_CALL_METHOD(NULL, &query, "setTransaction", NULL, 0, &transaction);
			zephir_check_call_status();
		}
	}
	if (zephir_array_isset_value_string(&params, SL("bind"))) {
		ZEPHIR_OBS_NVAR(&bindParams);
		zephir_array_fetch_string(&bindParams, &params, SL("bind"), PH_NOISY, "phalcon/Mvc/Model.zep", 4904);
		if (zephir_array_isset_value_string(&params, SL("bindTypes"))) {
			ZEPHIR_OBS_NVAR(&bindTypes);
			zephir_array_fetch_string(&bindTypes, &params, SL("bindTypes"), PH_NOISY, "phalcon/Mvc/Model.zep", 4907);
		}
	}
	zephir_memory_observe(&cache);
	if (zephir_array_isset_string_fetch(&cache, &params, SL("cache"), 0)) {
		ZEPHIR_CALL_METHOD(NULL, &query, "cache", NULL, 0, &cache);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&resultset, &query, "execute", NULL, 0, &bindParams, &bindTypes);
	zephir_check_call_status();
	if (zephir_array_isset_value_string(&params, SL("group"))) {
		RETURN_CCTOR(&resultset);
	}
	ZEPHIR_CALL_METHOD(&firstRow, &resultset, "getFirst", NULL, 0);
	zephir_check_call_status();
	zephir_memory_observe(&_2);
	zephir_read_property_zval(&_2, &firstRow, &alias_zv, PH_NOISY_CC);
	RETURN_CCTOR(&_2);
}

/**
 * Try to check if the query must invoke a finder
 *
 * @return ModelInterface[]|ModelInterface|bool
 */
PHP_METHOD(Phalcon_Mvc_Model, invokeFinder)
{
	zend_class_entry *_16;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval arguments, _12$$14;
	zval method_zv, *arguments_param = NULL, extraMethod, type, modelName, value, model, attributes, field, extraMethodFirst, metaData, params, _3, _15, _0$$3, _1$$4, _2$$5, _4$$7, _5$$7, _6$$7, _7$$13, _8$$13, _9$$13, _10$$14, _11$$14, _13$$15, _14$$15;
	zend_string *method = NULL;

	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&extraMethod);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&extraMethodFirst);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$13);
	ZVAL_UNDEF(&_8$$13);
	ZVAL_UNDEF(&_9$$13);
	ZVAL_UNDEF(&_10$$14);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_13$$15);
	ZVAL_UNDEF(&_14$$15);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&_12$$14);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	arguments_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	zephir_get_arrval(&arguments, arguments_param);
	ZEPHIR_INIT_VAR(&extraMethod);
	ZVAL_NULL(&extraMethod);
	if (zephir_start_with_str(&method_zv, SL("findFirstBy"))) {
		ZEPHIR_INIT_VAR(&type);
		ZVAL_STRING(&type, "findFirst");
		ZVAL_LONG(&_0$$3, 11);
		ZEPHIR_INIT_NVAR(&extraMethod);
		zephir_substr(&extraMethod, &method_zv, 11 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	} else if (zephir_start_with_str(&method_zv, SL("findBy"))) {
		ZEPHIR_INIT_NVAR(&type);
		ZVAL_STRING(&type, "find");
		ZVAL_LONG(&_1$$4, 6);
		ZEPHIR_INIT_NVAR(&extraMethod);
		zephir_substr(&extraMethod, &method_zv, 6 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	} else if (zephir_start_with_str(&method_zv, SL("countBy"))) {
		ZEPHIR_INIT_NVAR(&type);
		ZVAL_STRING(&type, "count");
		ZVAL_LONG(&_2$$5, 7);
		ZEPHIR_INIT_NVAR(&extraMethod);
		zephir_substr(&extraMethod, &method_zv, 7 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	}
	ZEPHIR_INIT_VAR(&modelName);
	zephir_get_called_class(&modelName);
	if (!(zephir_is_true(&extraMethod))) {
		RETURN_MM_BOOL(0);
	}
	ZVAL_LONG(&_3, 0);
	if (UNEXPECTED(!(zephir_array_key_exists(&arguments, &_3)))) {
		ZEPHIR_INIT_VAR(&_4$$7);
		object_init_ex(&_4$$7, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_5$$7);
		zephir_get_called_class(&_5$$7);
		ZEPHIR_INIT_VAR(&_6$$7);
		ZEPHIR_CONCAT_SVSVS(&_6$$7, "The static method '", &method_zv, "' in '", &_5$$7, "' requires one argument");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_4$$7, "__construct", NULL, 32, &_6$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$7, "phalcon/Mvc/Model.zep", 4986);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&model);
	ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(&model, &modelName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&metaData, &model, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&attributes, &metaData, "getReverseColumnMap", NULL, 0, &model);
	zephir_check_call_status();
	if (Z_TYPE_P(&attributes) != IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&attributes, &metaData, "getDataTypes", NULL, 0, &model);
		zephir_check_call_status();
	}
	if (zephir_array_isset_value(&attributes, &extraMethod)) {
		ZEPHIR_CPY_WRT(&field, &extraMethod);
	} else {
		ZEPHIR_CALL_FUNCTION(&extraMethodFirst, "lcfirst", NULL, 86, &extraMethod);
		zephir_check_call_status();
		if (zephir_array_isset_value(&attributes, &extraMethodFirst)) {
			ZEPHIR_CPY_WRT(&field, &extraMethodFirst);
		} else {
			ZEPHIR_INIT_NVAR(&field);
			zephir_uncamelize(&field, &extraMethod, NULL );
			if (UNEXPECTED(!(zephir_array_isset_value(&attributes, &field)))) {
				ZEPHIR_INIT_VAR(&_7$$13);
				object_init_ex(&_7$$13, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_VAR(&_8$$13);
				zephir_get_called_class(&_8$$13);
				ZEPHIR_INIT_VAR(&_9$$13);
				ZEPHIR_CONCAT_SVSVS(&_9$$13, "Cannot resolve attribute '", &extraMethod, "' in the model '", &_8$$13, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_7$$13, "__construct", NULL, 32, &_9$$13);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_7$$13, "phalcon/Mvc/Model.zep", 5023);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_memory_observe(&value);
	zephir_array_isset_long_fetch(&value, &arguments, 0, 0);
	ZEPHIR_INIT_VAR(&params);
	if (Z_TYPE_P(&value) != IS_NULL) {
		ZEPHIR_INIT_VAR(&_10$$14);
		zephir_create_array(&_10$$14, 2, 0);
		ZEPHIR_INIT_VAR(&_11$$14);
		ZEPHIR_CONCAT_SVS(&_11$$14, "[", &field, "] = ?0");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_update_string(&_10$$14, SL("conditions"), &_11$$14, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_12$$14);
		zephir_create_array(&_12$$14, 1, 0);
		zephir_array_fast_append(&_12$$14, &value);
		zephir_array_update_string(&_10$$14, SL("bind"), &_12$$14, PH_COPY | PH_SEPARATE);
		ZEPHIR_CPY_WRT(&params, &_10$$14);
	} else {
		ZEPHIR_INIT_VAR(&_13$$15);
		zephir_create_array(&_13$$15, 1, 0);
		ZEPHIR_INIT_VAR(&_14$$15);
		ZEPHIR_CONCAT_SVS(&_14$$15, "[", &field, "] IS NULL");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_update_string(&_13$$15, SL("conditions"), &_14$$15, PH_COPY | PH_SEPARATE);
		ZEPHIR_CPY_WRT(&params, &_13$$15);
	}
	zephir_array_unset_long(&arguments, 0, PH_SEPARATE);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_array_unset_string(&arguments, SL("conditions"), PH_SEPARATE);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_array_unset_string(&arguments, SL("bind"), PH_SEPARATE);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_15);
	zephir_fast_array_merge(&_15, &params, &arguments);
	ZEPHIR_CPY_WRT(&params, &_15);
	_16 = zephir_fetch_class(&modelName);
	ZEPHIR_RETURN_CALL_CE_STATIC_ZVAL(_16, type, NULL, 0, &params);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check for, and attempt to use, possible setter.
 */
PHP_METHOD(Phalcon_Mvc_Model, possibleSetter)
{
	zval localMethods;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval property_zv, *value, value_sub, possibleSetter, _0;
	zend_string *property = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&property_zv);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&possibleSetter);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&localMethods);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(property)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	value = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&property_zv);
	ZVAL_STR_COPY(&property_zv, property);
	ZEPHIR_INIT_VAR(&localMethods);
	zephir_create_array(&localMethods, 10, 0);
	add_assoc_long_ex(&localMethods, SL("setConnectionService"), 1);
	add_assoc_long_ex(&localMethods, SL("setDirtyState"), 1);
	add_assoc_long_ex(&localMethods, SL("setEventsManager"), 1);
	add_assoc_long_ex(&localMethods, SL("setReadConnectionService"), 1);
	add_assoc_long_ex(&localMethods, SL("setOldSnapshotData"), 1);
	add_assoc_long_ex(&localMethods, SL("setSchema"), 1);
	add_assoc_long_ex(&localMethods, SL("setSnapshotData"), 1);
	add_assoc_long_ex(&localMethods, SL("setSource"), 1);
	add_assoc_long_ex(&localMethods, SL("setTransaction"), 1);
	add_assoc_long_ex(&localMethods, SL("setWriteConnectionService"), 1);
	ZEPHIR_INIT_VAR(&_0);
	zephir_camelize(&_0, &property_zv, NULL );
	ZEPHIR_INIT_VAR(&possibleSetter);
	ZEPHIR_CONCAT_SV(&possibleSetter, "set", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (!((zephir_method_exists(this_ptr, &possibleSetter)  == SUCCESS))) {
		RETURN_MM_BOOL(0);
	}
	if (!(zephir_array_isset_value(&localMethods, &possibleSetter))) {
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &possibleSetter, NULL, 0, value);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(1);
}

/**
 * Executes internal hooks before save a record
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model, preSave)
{
	zval _26$$32, _44$$52;
	zval eventName;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_13 = NULL, *_18 = NULL, *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool exists, error = 0, isNull = 0, _31$$11, _19$$27, _20$$27, _21$$27, _23$$33, _37$$47, _38$$47, _39$$47, _41$$53;
	zval *metaData, metaData_sub, *exists_param = NULL, *identityField, identityField_sub, __$true, __$false, notNull, columnMap, dataTypeNumeric, automaticAttributes, defaultValues, field, attributeField, value, emptyStringValues, _0, _1, _5, _7, _50, _54, _2$$3, _3$$3, _4$$3, _6$$8, _8$$11, _9$$11, *_10$$11, *_11$$11, _30$$11, _12$$18, _14$$18, _15$$19, _16$$19, _17$$19, _22$$27, _24$$32, _25$$32, _27$$32, _28$$32, _32$$38, _33$$38, _34$$39, _35$$39, _36$$39, _40$$47, _42$$52, _43$$52, _45$$52, _46$$52, _47$$56, _48$$56, _49$$57, _51$$58, _52$$58, _53$$59, _55$$60, _56$$60, _57$$60, _58$$60, _59$$60, _60$$60;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&metaData_sub);
	ZVAL_UNDEF(&identityField_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&notNull);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&dataTypeNumeric);
	ZVAL_UNDEF(&automaticAttributes);
	ZVAL_UNDEF(&defaultValues);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&emptyStringValues);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_50);
	ZVAL_UNDEF(&_54);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_30$$11);
	ZVAL_UNDEF(&_12$$18);
	ZVAL_UNDEF(&_14$$18);
	ZVAL_UNDEF(&_15$$19);
	ZVAL_UNDEF(&_16$$19);
	ZVAL_UNDEF(&_17$$19);
	ZVAL_UNDEF(&_22$$27);
	ZVAL_UNDEF(&_24$$32);
	ZVAL_UNDEF(&_25$$32);
	ZVAL_UNDEF(&_27$$32);
	ZVAL_UNDEF(&_28$$32);
	ZVAL_UNDEF(&_32$$38);
	ZVAL_UNDEF(&_33$$38);
	ZVAL_UNDEF(&_34$$39);
	ZVAL_UNDEF(&_35$$39);
	ZVAL_UNDEF(&_36$$39);
	ZVAL_UNDEF(&_40$$47);
	ZVAL_UNDEF(&_42$$52);
	ZVAL_UNDEF(&_43$$52);
	ZVAL_UNDEF(&_45$$52);
	ZVAL_UNDEF(&_46$$52);
	ZVAL_UNDEF(&_47$$56);
	ZVAL_UNDEF(&_48$$56);
	ZVAL_UNDEF(&_49$$57);
	ZVAL_UNDEF(&_51$$58);
	ZVAL_UNDEF(&_52$$58);
	ZVAL_UNDEF(&_53$$59);
	ZVAL_UNDEF(&_55$$60);
	ZVAL_UNDEF(&_56$$60);
	ZVAL_UNDEF(&_57$$60);
	ZVAL_UNDEF(&_58$$60);
	ZVAL_UNDEF(&_59$$60);
	ZVAL_UNDEF(&_60$$60);
	ZVAL_UNDEF(&eventName);
	ZVAL_UNDEF(&_26$$32);
	ZVAL_UNDEF(&_44$$52);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("skipped", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(metaData, phalcon_mvc_model_metadatainterface_ce)
		Z_PARAM_BOOL(exists)
		Z_PARAM_ZVAL(identityField)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &metaData, &exists_param, &identityField);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "orm.events");
	ZEPHIR_CALL_CE_STATIC(&_0, phalcon_support_settings_ce, "get", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "beforeValidation");
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "fireEventCancel", NULL, 0, &_3$$3);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_2$$3)) {
			RETURN_MM_BOOL(0);
		}
		if (exists) {
			ZEPHIR_INIT_VAR(&eventName);
			ZVAL_STRING(&eventName, "beforeValidationOnUpdate");
		} else {
			ZEPHIR_INIT_NVAR(&eventName);
			ZVAL_STRING(&eventName, "beforeValidationOnCreate");
		}
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "fireEventCancel", NULL, 0, &eventName);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_4$$3)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "orm.virtual_foreign_keys");
	ZEPHIR_CALL_CE_STATIC(&_5, phalcon_support_settings_ce, "get", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_5)) {
		ZEPHIR_CALL_METHOD(&_6$$8, this_ptr, "checkForeignKeysRestrict", NULL, 477);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_6$$8)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "orm.not_null_validations");
	ZEPHIR_CALL_CE_STATIC(&_7, phalcon_support_settings_ce, "get", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_7)) {
		ZEPHIR_CALL_METHOD(&notNull, metaData, "getNotNullAttributes", NULL, 0, this_ptr);
		zephir_check_call_status();
		if (Z_TYPE_P(&notNull) == IS_ARRAY) {
			ZEPHIR_CALL_METHOD(&dataTypeNumeric, metaData, "getDataTypesNumeric", NULL, 0, this_ptr);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_9$$11);
			ZVAL_STRING(&_9$$11, "orm.column_renaming");
			ZEPHIR_CALL_CE_STATIC(&_8$$11, phalcon_support_settings_ce, "get", NULL, 0, &_9$$11);
			zephir_check_call_status();
			if (zephir_is_true(&_8$$11)) {
				ZEPHIR_CALL_METHOD(&columnMap, metaData, "getColumnMap", NULL, 0, this_ptr);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&columnMap);
				ZVAL_NULL(&columnMap);
			}
			if (exists) {
				ZEPHIR_CALL_METHOD(&automaticAttributes, metaData, "getAutomaticUpdateAttributes", NULL, 0, this_ptr);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(&automaticAttributes, metaData, "getAutomaticCreateAttributes", NULL, 0, this_ptr);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&defaultValues, metaData, "getDefaultValues", NULL, 0, this_ptr);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&emptyStringValues, metaData, "getEmptyStringAttributes", NULL, 0, this_ptr);
			zephir_check_call_status();
			error = 0;
			if (Z_TYPE_P(&notNull) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_9$$11);
				zephir_string_to_char_array(&_9$$11, &notNull);
				_10$$11 = &_9$$11;
			} else {
				_10$$11 = &notNull;
			}
			zephir_is_iterable(_10$$11, 0, "phalcon/Mvc/Model.zep", 5265);
			if (Z_TYPE_P(_10$$11) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_10$$11), _11$$11)
				{
					ZEPHIR_INIT_NVAR(&field);
					ZVAL_COPY(&field, _11$$11);
					if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&attributeField);
						if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
							ZEPHIR_INIT_NVAR(&_14$$18);
							ZVAL_STRING(&_14$$18, "orm.ignore_unknown_columns");
							ZEPHIR_CALL_CE_STATIC(&_12$$18, phalcon_support_settings_ce, "get", &_13, 0, &_14$$18);
							zephir_check_call_status();
							if (UNEXPECTED(!zephir_is_true(&_12$$18))) {
								ZEPHIR_INIT_NVAR(&_15$$19);
								object_init_ex(&_15$$19, phalcon_mvc_model_exception_ce);
								ZEPHIR_INIT_NVAR(&_16$$19);
								zephir_get_class(&_16$$19, this_ptr, 0);
								ZEPHIR_INIT_NVAR(&_17$$19);
								ZEPHIR_CONCAT_SVSVS(&_17$$19, "Column '", &field, "' in '", &_16$$19, "' isn't part of the column map");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_15$$19, "__construct", &_18, 32, &_17$$19);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_15$$19, "phalcon/Mvc/Model.zep", 5184);
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					} else {
						ZEPHIR_CPY_WRT(&attributeField, &field);
					}
					if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
						isNull = 0;
						ZEPHIR_OBS_NVAR(&value);
						if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
							if (Z_TYPE_P(&value) != IS_OBJECT) {
								if (!(zephir_array_isset_value(&dataTypeNumeric, &field))) {
									if (zephir_array_isset_value(&emptyStringValues, &field)) {
										if (Z_TYPE_P(&value) == IS_NULL) {
											isNull = 1;
										}
									} else {
										_19$$27 = Z_TYPE_P(&value) == IS_NULL;
										if (!(_19$$27)) {
											_20$$27 = ZEPHIR_IS_STRING_IDENTICAL(&value, "");
											if (_20$$27) {
												_20$$27 = zephir_array_isset_value(&defaultValues, &field);
											}
											_21$$27 = _20$$27;
											if (_21$$27) {
												ZEPHIR_OBS_NVAR(&_22$$27);
												zephir_array_fetch(&_22$$27, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 5215);
												_21$$27 = !ZEPHIR_IS_STRING_IDENTICAL(&_22$$27, "");
											}
											_19$$27 = _21$$27;
										}
										if (_19$$27) {
											isNull = 1;
										}
									}
								} else {
									if (!(zephir_is_numeric(&value))) {
										isNull = 1;
									}
								}
							}
						} else {
							isNull = 1;
						}
						if (isNull) {
							if (!(exists)) {
								_23$$33 = ZEPHIR_IS_EQUAL(&field, identityField);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								if (_23$$33) {
									continue;
								}
								if (zephir_array_isset_value(&defaultValues, &field)) {
									continue;
								}
							}
							ZEPHIR_INIT_NVAR(&_24$$32);
							object_init_ex(&_24$$32, phalcon_messages_message_ce);
							ZEPHIR_INIT_NVAR(&_25$$32);
							ZEPHIR_CONCAT_VS(&_25$$32, &attributeField, " is required");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_INIT_NVAR(&_26$$32);
							zephir_create_array(&_26$$32, 1, 0);
							ZEPHIR_INIT_NVAR(&_27$$32);
							zephir_get_class(&_27$$32, this_ptr, 0);
							zephir_array_update_string(&_26$$32, SL("model"), &_27$$32, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_27$$32);
							ZVAL_STRING(&_27$$32, "PresenceOf");
							ZVAL_LONG(&_28$$32, 0);
							ZEPHIR_CALL_METHOD(NULL, &_24$$32, "__construct", &_29, 6, &_25$$32, &attributeField, &_27$$32, &_28$$32, &_26$$32);
							zephir_check_call_status();
							zephir_update_property_array_append(this_ptr, SL("errorMessages"), &_24$$32);
							error = 1;
						}
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _10$$11, "rewind", NULL, 0);
				zephir_check_call_status();
				_31$$11 = 1;
				while (1) {
					if (_31$$11) {
						_31$$11 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _10$$11, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_30$$11, _10$$11, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_30$$11)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&field, _10$$11, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
							ZEPHIR_OBS_NVAR(&attributeField);
							if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &field, 0)))) {
								ZEPHIR_INIT_NVAR(&_33$$38);
								ZVAL_STRING(&_33$$38, "orm.ignore_unknown_columns");
								ZEPHIR_CALL_CE_STATIC(&_32$$38, phalcon_support_settings_ce, "get", &_13, 0, &_33$$38);
								zephir_check_call_status();
								if (UNEXPECTED(!zephir_is_true(&_32$$38))) {
									ZEPHIR_INIT_NVAR(&_34$$39);
									object_init_ex(&_34$$39, phalcon_mvc_model_exception_ce);
									ZEPHIR_INIT_NVAR(&_35$$39);
									zephir_get_class(&_35$$39, this_ptr, 0);
									ZEPHIR_INIT_NVAR(&_36$$39);
									ZEPHIR_CONCAT_SVSVS(&_36$$39, "Column '", &field, "' in '", &_35$$39, "' isn't part of the column map");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_34$$39, "__construct", &_18, 32, &_36$$39);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_34$$39, "phalcon/Mvc/Model.zep", 5184);
									ZEPHIR_MM_RESTORE();
									return;
								}
							}
						} else {
							ZEPHIR_CPY_WRT(&attributeField, &field);
						}
						if (!(zephir_array_isset_value(&automaticAttributes, &attributeField))) {
							isNull = 0;
							ZEPHIR_OBS_NVAR(&value);
							if (zephir_fetch_property_zval(&value, this_ptr, &attributeField, PH_SILENT_CC)) {
								if (Z_TYPE_P(&value) != IS_OBJECT) {
									if (!(zephir_array_isset_value(&dataTypeNumeric, &field))) {
										if (zephir_array_isset_value(&emptyStringValues, &field)) {
											if (Z_TYPE_P(&value) == IS_NULL) {
												isNull = 1;
											}
										} else {
											_37$$47 = Z_TYPE_P(&value) == IS_NULL;
											if (!(_37$$47)) {
												_38$$47 = ZEPHIR_IS_STRING_IDENTICAL(&value, "");
												if (_38$$47) {
													_38$$47 = zephir_array_isset_value(&defaultValues, &field);
												}
												_39$$47 = _38$$47;
												if (_39$$47) {
													ZEPHIR_OBS_NVAR(&_40$$47);
													zephir_array_fetch(&_40$$47, &defaultValues, &field, PH_NOISY, "phalcon/Mvc/Model.zep", 5215);
													_39$$47 = !ZEPHIR_IS_STRING_IDENTICAL(&_40$$47, "");
												}
												_37$$47 = _39$$47;
											}
											if (_37$$47) {
												isNull = 1;
											}
										}
									} else {
										if (!(zephir_is_numeric(&value))) {
											isNull = 1;
										}
									}
								}
							} else {
								isNull = 1;
							}
							if (isNull) {
								if (!(exists)) {
									_41$$53 = ZEPHIR_IS_EQUAL(&field, identityField);
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									if (_41$$53) {
										continue;
									}
									if (zephir_array_isset_value(&defaultValues, &field)) {
										continue;
									}
								}
								ZEPHIR_INIT_NVAR(&_42$$52);
								object_init_ex(&_42$$52, phalcon_messages_message_ce);
								ZEPHIR_INIT_NVAR(&_43$$52);
								ZEPHIR_CONCAT_VS(&_43$$52, &attributeField, " is required");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_INIT_NVAR(&_44$$52);
								zephir_create_array(&_44$$52, 1, 0);
								ZEPHIR_INIT_NVAR(&_45$$52);
								zephir_get_class(&_45$$52, this_ptr, 0);
								zephir_array_update_string(&_44$$52, SL("model"), &_45$$52, PH_COPY | PH_SEPARATE);
								ZEPHIR_INIT_NVAR(&_45$$52);
								ZVAL_STRING(&_45$$52, "PresenceOf");
								ZVAL_LONG(&_46$$52, 0);
								ZEPHIR_CALL_METHOD(NULL, &_42$$52, "__construct", &_29, 6, &_43$$52, &attributeField, &_45$$52, &_46$$52, &_44$$52);
								zephir_check_call_status();
								zephir_update_property_array_append(this_ptr, SL("errorMessages"), &_42$$52);
								error = 1;
							}
						}
				}
			}
			ZEPHIR_INIT_NVAR(&field);
			if (error) {
				ZEPHIR_INIT_VAR(&_48$$56);
				ZVAL_STRING(&_48$$56, "orm.events");
				ZEPHIR_CALL_CE_STATIC(&_47$$56, phalcon_support_settings_ce, "get", &_13, 0, &_48$$56);
				zephir_check_call_status();
				if (zephir_is_true(&_47$$56)) {
					ZEPHIR_INIT_VAR(&_49$$57);
					ZVAL_STRING(&_49$$57, "onValidationFails");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_49$$57);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "cancelOperation", NULL, 0);
					zephir_check_call_status();
				}
				RETURN_MM_BOOL(0);
			}
		}
	}
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "validation");
	ZEPHIR_CALL_METHOD(&_50, this_ptr, "fireEventCancel", NULL, 0, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_50)) {
		ZEPHIR_INIT_VAR(&_52$$58);
		ZVAL_STRING(&_52$$58, "orm.events");
		ZEPHIR_CALL_CE_STATIC(&_51$$58, phalcon_support_settings_ce, "get", &_13, 0, &_52$$58);
		zephir_check_call_status();
		if (zephir_is_true(&_51$$58)) {
			ZEPHIR_INIT_VAR(&_53$$59);
			ZVAL_STRING(&_53$$59, "onValidationFails");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_53$$59);
			zephir_check_call_status();
		}
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "orm.events");
	ZEPHIR_CALL_CE_STATIC(&_54, phalcon_support_settings_ce, "get", &_13, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_54)) {
		if (exists) {
			ZEPHIR_INIT_NVAR(&eventName);
			ZVAL_STRING(&eventName, "afterValidationOnUpdate");
		} else {
			ZEPHIR_INIT_NVAR(&eventName);
			ZVAL_STRING(&eventName, "afterValidationOnCreate");
		}
		ZEPHIR_CALL_METHOD(&_55$$60, this_ptr, "fireEventCancel", NULL, 0, &eventName);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_55$$60)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_VAR(&_57$$60);
		ZVAL_STRING(&_57$$60, "afterValidation");
		ZEPHIR_CALL_METHOD(&_56$$60, this_ptr, "fireEventCancel", NULL, 0, &_57$$60);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_56$$60)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_NVAR(&_57$$60);
		ZVAL_STRING(&_57$$60, "beforeSave");
		ZEPHIR_CALL_METHOD(&_58$$60, this_ptr, "fireEventCancel", NULL, 0, &_57$$60);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_58$$60)) {
			RETURN_MM_BOOL(0);
		}
		if (0) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 715, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 715, &__$false);
		}
		if (exists) {
			ZEPHIR_INIT_NVAR(&eventName);
			ZVAL_STRING(&eventName, "beforeUpdate");
		} else {
			ZEPHIR_INIT_NVAR(&eventName);
			ZVAL_STRING(&eventName, "beforeCreate");
		}
		ZEPHIR_CALL_METHOD(&_59$$60, this_ptr, "fireEventCancel", NULL, 0, &eventName);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_59$$60)) {
			RETURN_MM_BOOL(0);
		}
		zephir_read_property_cached(&_60$$60, this_ptr, _zephir_prop_0, 715, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_60$$60)) {
			RETURN_MM_BOOL(1);
		}
	}
	RETURN_MM_BOOL(1);
}

/**
 * Saves related records that must be stored prior to save the master record
 *
 * @param ModelInterface[] related
 * @param CollectionInterface visited
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model, preSaveRelatedRecords)
{
	zend_string *_6;
	zend_ulong _5;
	zend_bool nesting = 0, _28, _21$$5, _42$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL, *_14 = NULL, *_16 = NULL, *_23 = NULL, *_25 = NULL, *_30 = NULL, *_32 = NULL, *_37 = NULL, *_45 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *connection, connection_sub, *related, related_sub, *visited, visited_sub, className, manager, type, relation, columns, referencedFields, name, record, _0, _1, *_2, _3, *_4, _27, _7$$3, _9$$6, _11$$6, _12$$6, _13$$6, _15$$7, _17$$7, _18$$7, _19$$7, _20$$5, _22$$5, _26$$5, _24$$8, _29$$9, _31$$12, _33$$12, _34$$12, _35$$12, _36$$13, _38$$13, _39$$13, _40$$13, _41$$11, _43$$11, _46$$11, _44$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&connection_sub);
	ZVAL_UNDEF(&related_sub);
	ZVAL_UNDEF(&visited_sub);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&referencedFields);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&record);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_26$$5);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_31$$12);
	ZVAL_UNDEF(&_33$$12);
	ZVAL_UNDEF(&_34$$12);
	ZVAL_UNDEF(&_35$$12);
	ZVAL_UNDEF(&_36$$13);
	ZVAL_UNDEF(&_38$$13);
	ZVAL_UNDEF(&_39$$13);
	ZVAL_UNDEF(&_40$$13);
	ZVAL_UNDEF(&_41$$11);
	ZVAL_UNDEF(&_43$$11);
	ZVAL_UNDEF(&_46$$11);
	ZVAL_UNDEF(&_44$$14);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dirtyState", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(connection, phalcon_db_adapter_adapterinterface_ce)
		Z_PARAM_ZVAL(related)
		Z_PARAM_OBJECT_OF_CLASS(visited, phalcon_support_collection_collectioninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &connection, &related, &visited);
	nesting = 0;
	if (nesting) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, connection, "begin", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&className);
	zephir_get_class(&className, this_ptr, 0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_1);
	if (Z_TYPE_P(related) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, related);
		_2 = &_3;
	} else {
		_2 = related;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/Model.zep", 5429);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_2), _5, _6, _4)
		{
			ZEPHIR_INIT_NVAR(&name);
			if (_6 != NULL) { 
				ZVAL_STR_COPY(&name, _6);
			} else {
				ZVAL_LONG(&name, _5);
			}
			ZEPHIR_INIT_NVAR(&record);
			ZVAL_COPY(&record, _4);
			ZEPHIR_CALL_METHOD(&_7$$3, &manager, "getRelationByAlias", &_8, 0, &className, &name);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&relation, &_7$$3);
			if (Z_TYPE_P(&relation) == IS_OBJECT) {
				ZEPHIR_CALL_METHOD(&type, &relation, "getType", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_LONG(&type, 0)) {
					if (UNEXPECTED(Z_TYPE_P(&record) != IS_OBJECT)) {
						if (nesting) {
							ZVAL_BOOL(&_9$$6, 1);
						} else {
							ZVAL_BOOL(&_9$$6, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_10, 0, &_9$$6);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						object_init_ex(&_11$$6, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_12$$6);
						zephir_get_class(&_12$$6, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_13$$6);
						ZEPHIR_CONCAT_SVSV(&_13$$6, "Only objects can be stored as part of belongs-to relations in '", &_12$$6, "' Relation ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_11$$6, "__construct", &_14, 32, &_13$$6);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_11$$6, "phalcon/Mvc/Model.zep", 5387);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&columns, &relation, "getFields", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
					zephir_check_call_status();
					if (UNEXPECTED(Z_TYPE_P(&columns) == IS_ARRAY)) {
						if (nesting) {
							ZVAL_BOOL(&_15$$7, 1);
						} else {
							ZVAL_BOOL(&_15$$7, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_16, 0, &_15$$7);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$7);
						object_init_ex(&_17$$7, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_18$$7);
						zephir_get_class(&_18$$7, this_ptr, 0);
						ZEPHIR_INIT_NVAR(&_19$$7);
						ZEPHIR_CONCAT_SVSV(&_19$$7, "Not implemented in '", &_18$$7, "' Relation ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_17$$7, "__construct", &_14, 32, &_19$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_17$$7, "phalcon/Mvc/Model.zep", 5398);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_read_property_cached(&_20$$5, &record, _zephir_prop_0, 0, PH_NOISY_CC | PH_READONLY);
					_21$$5 = !ZEPHIR_IS_LONG_IDENTICAL(&_20$$5, 0);
					if (_21$$5) {
						ZEPHIR_CALL_METHOD(&_22$$5, &record, "doSave", NULL, 0, visited);
						zephir_check_call_status();
						_21$$5 = !zephir_is_true(&_22$$5);
					}
					if (_21$$5) {
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_23, 0, &record);
						zephir_check_call_status();
						if (nesting) {
							ZVAL_BOOL(&_24$$8, 1);
						} else {
							ZVAL_BOOL(&_24$$8, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_25, 0, &_24$$8);
						zephir_check_call_status();
						RETURN_MM_BOOL(0);
					}
					ZEPHIR_CALL_METHOD(&_26$$5, &record, "readAttribute", NULL, 0, &referencedFields);
					zephir_check_call_status();
					zephir_update_property_zval_zval(this_ptr, &columns, &_26$$5);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_28 = 1;
		while (1) {
			if (_28) {
				_28 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_27, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_27)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&name, _2, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&record, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_29$$9, &manager, "getRelationByAlias", &_30, 0, &className, &name);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&relation, &_29$$9);
				if (Z_TYPE_P(&relation) == IS_OBJECT) {
					ZEPHIR_CALL_METHOD(&type, &relation, "getType", NULL, 0);
					zephir_check_call_status();
					if (ZEPHIR_IS_LONG(&type, 0)) {
						if (UNEXPECTED(Z_TYPE_P(&record) != IS_OBJECT)) {
							if (nesting) {
								ZVAL_BOOL(&_31$$12, 1);
							} else {
								ZVAL_BOOL(&_31$$12, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_32, 0, &_31$$12);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_33$$12);
							object_init_ex(&_33$$12, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_34$$12);
							zephir_get_class(&_34$$12, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_35$$12);
							ZEPHIR_CONCAT_SVSV(&_35$$12, "Only objects can be stored as part of belongs-to relations in '", &_34$$12, "' Relation ", &name);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_33$$12, "__construct", &_14, 32, &_35$$12);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_33$$12, "phalcon/Mvc/Model.zep", 5387);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&columns, &relation, "getFields", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
						zephir_check_call_status();
						if (UNEXPECTED(Z_TYPE_P(&columns) == IS_ARRAY)) {
							if (nesting) {
								ZVAL_BOOL(&_36$$13, 1);
							} else {
								ZVAL_BOOL(&_36$$13, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_37, 0, &_36$$13);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_38$$13);
							object_init_ex(&_38$$13, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_39$$13);
							zephir_get_class(&_39$$13, this_ptr, 0);
							ZEPHIR_INIT_NVAR(&_40$$13);
							ZEPHIR_CONCAT_SVSV(&_40$$13, "Not implemented in '", &_39$$13, "' Relation ", &name);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_38$$13, "__construct", &_14, 32, &_40$$13);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_38$$13, "phalcon/Mvc/Model.zep", 5398);
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_read_property_cached(&_41$$11, &record, _zephir_prop_0, 0, PH_NOISY_CC | PH_READONLY);
						_42$$11 = !ZEPHIR_IS_LONG_IDENTICAL(&_41$$11, 0);
						if (_42$$11) {
							ZEPHIR_CALL_METHOD(&_43$$11, &record, "doSave", NULL, 0, visited);
							zephir_check_call_status();
							_42$$11 = !zephir_is_true(&_43$$11);
						}
						if (_42$$11) {
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_23, 0, &record);
							zephir_check_call_status();
							if (nesting) {
								ZVAL_BOOL(&_44$$14, 1);
							} else {
								ZVAL_BOOL(&_44$$14, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_45, 0, &_44$$14);
							zephir_check_call_status();
							RETURN_MM_BOOL(0);
						}
						ZEPHIR_CALL_METHOD(&_46$$11, &record, "readAttribute", NULL, 0, &referencedFields);
						zephir_check_call_status();
						zephir_update_property_zval_zval(this_ptr, &columns, &_46$$11);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&record);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_MM_BOOL(1);
}

/**
 * Executes internal events after save a record
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model, postSave)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *success_param = NULL, *exists_param = NULL, _0$$4, _1$$5;
	zend_bool success, exists;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$5);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_BOOL(success)
		Z_PARAM_BOOL(exists)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &success_param, &exists_param);
	if (success) {
		if (exists) {
			ZEPHIR_INIT_VAR(&_0$$4);
			ZVAL_STRING(&_0$$4, "afterUpdate");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_0$$4);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_VAR(&_1$$5);
			ZVAL_STRING(&_1$$5, "afterCreate");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_1$$5);
			zephir_check_call_status();
		}
	}
	RETURN_MM_BOOL(success);
}

/**
 * Save the related records assigned in the has-one/has-many relations
 *
 * @param ModelInterface[] related
 * @param CollectionInterface visited
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_Model, postSaveRelatedRecords)
{
	zval _34$$14, _36$$14, _48$$19, _50$$19, _98$$40, _100$$40, _112$$45, _114$$45;
	zend_string *_5;
	zend_ulong _4;
	zend_bool nesting = 0, isThrough = 0, _70, _9$$4, _41$$11, _61$$22, _74$$30, _105$$37, _125$$48;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_11 = NULL, *_14 = NULL, *_16 = NULL, *_20 = NULL, *_28 = NULL, *_30 = NULL, *_32 = NULL, *_33 = NULL, *_39 = NULL, *_44 = NULL, *_46 = NULL, *_47 = NULL, *_53 = NULL, *_59 = NULL, *_64 = NULL, *_66 = NULL, *_72 = NULL, *_76 = NULL, *_80 = NULL, *_85 = NULL, *_94 = NULL, *_96 = NULL, *_97 = NULL, *_103 = NULL, *_108 = NULL, *_110 = NULL, *_111 = NULL, *_117 = NULL, *_123 = NULL, *_128 = NULL, *_130 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *connection, connection_sub, *related, related_sub, *visited, visited_sub, className, manager, relation, name, record, columns, referencedModel, referencedFields, relatedRecords, value, recordAfter, intermediateModel, intermediateFields, intermediateValue, intermediateModelName, intermediateReferencedFields, existingIntermediateModel, _0, *_1, _2, *_3, _69, _133, _6$$3, _8$$4, _23$$4, _10$$6, _12$$6, _13$$6, _15$$7, _17$$7, _18$$7, _19$$10, _21$$10, _22$$10, *_24$$11, _25$$11, *_26$$11, _40$$11, _27$$12, _31$$12, _37$$12, _29$$13, _35$$14, _38$$16, _42$$17, _45$$17, _51$$17, _43$$18, _49$$19, _52$$21, *_54$$22, _55$$22, *_56$$22, _60$$22, _57$$23, _58$$24, _62$$25, _63$$26, _65$$28, _67$$28, _68$$28, _71$$29, _73$$30, _88$$30, _75$$32, _77$$32, _78$$32, _79$$33, _81$$33, _82$$33, _83$$34, _84$$36, _86$$36, _87$$36, *_89$$37, _90$$37, *_91$$37, _104$$37, _92$$38, _95$$38, _101$$38, _93$$39, _99$$40, _102$$42, _106$$43, _109$$43, _115$$43, _107$$44, _113$$45, _116$$47, *_118$$48, _119$$48, *_120$$48, _124$$48, _121$$49, _122$$50, _126$$51, _127$$52, _129$$54, _131$$54, _132$$54;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&connection_sub);
	ZVAL_UNDEF(&related_sub);
	ZVAL_UNDEF(&visited_sub);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&record);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&referencedModel);
	ZVAL_UNDEF(&referencedFields);
	ZVAL_UNDEF(&relatedRecords);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&recordAfter);
	ZVAL_UNDEF(&intermediateModel);
	ZVAL_UNDEF(&intermediateFields);
	ZVAL_UNDEF(&intermediateValue);
	ZVAL_UNDEF(&intermediateModelName);
	ZVAL_UNDEF(&intermediateReferencedFields);
	ZVAL_UNDEF(&existingIntermediateModel);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_69);
	ZVAL_UNDEF(&_133);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_23$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_21$$10);
	ZVAL_UNDEF(&_22$$10);
	ZVAL_UNDEF(&_25$$11);
	ZVAL_UNDEF(&_40$$11);
	ZVAL_UNDEF(&_27$$12);
	ZVAL_UNDEF(&_31$$12);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_29$$13);
	ZVAL_UNDEF(&_35$$14);
	ZVAL_UNDEF(&_38$$16);
	ZVAL_UNDEF(&_42$$17);
	ZVAL_UNDEF(&_45$$17);
	ZVAL_UNDEF(&_51$$17);
	ZVAL_UNDEF(&_43$$18);
	ZVAL_UNDEF(&_49$$19);
	ZVAL_UNDEF(&_52$$21);
	ZVAL_UNDEF(&_55$$22);
	ZVAL_UNDEF(&_60$$22);
	ZVAL_UNDEF(&_57$$23);
	ZVAL_UNDEF(&_58$$24);
	ZVAL_UNDEF(&_62$$25);
	ZVAL_UNDEF(&_63$$26);
	ZVAL_UNDEF(&_65$$28);
	ZVAL_UNDEF(&_67$$28);
	ZVAL_UNDEF(&_68$$28);
	ZVAL_UNDEF(&_71$$29);
	ZVAL_UNDEF(&_73$$30);
	ZVAL_UNDEF(&_88$$30);
	ZVAL_UNDEF(&_75$$32);
	ZVAL_UNDEF(&_77$$32);
	ZVAL_UNDEF(&_78$$32);
	ZVAL_UNDEF(&_79$$33);
	ZVAL_UNDEF(&_81$$33);
	ZVAL_UNDEF(&_82$$33);
	ZVAL_UNDEF(&_83$$34);
	ZVAL_UNDEF(&_84$$36);
	ZVAL_UNDEF(&_86$$36);
	ZVAL_UNDEF(&_87$$36);
	ZVAL_UNDEF(&_90$$37);
	ZVAL_UNDEF(&_104$$37);
	ZVAL_UNDEF(&_92$$38);
	ZVAL_UNDEF(&_95$$38);
	ZVAL_UNDEF(&_101$$38);
	ZVAL_UNDEF(&_93$$39);
	ZVAL_UNDEF(&_99$$40);
	ZVAL_UNDEF(&_102$$42);
	ZVAL_UNDEF(&_106$$43);
	ZVAL_UNDEF(&_109$$43);
	ZVAL_UNDEF(&_115$$43);
	ZVAL_UNDEF(&_107$$44);
	ZVAL_UNDEF(&_113$$45);
	ZVAL_UNDEF(&_116$$47);
	ZVAL_UNDEF(&_119$$48);
	ZVAL_UNDEF(&_124$$48);
	ZVAL_UNDEF(&_121$$49);
	ZVAL_UNDEF(&_122$$50);
	ZVAL_UNDEF(&_126$$51);
	ZVAL_UNDEF(&_127$$52);
	ZVAL_UNDEF(&_129$$54);
	ZVAL_UNDEF(&_131$$54);
	ZVAL_UNDEF(&_132$$54);
	ZVAL_UNDEF(&_34$$14);
	ZVAL_UNDEF(&_36$$14);
	ZVAL_UNDEF(&_48$$19);
	ZVAL_UNDEF(&_50$$19);
	ZVAL_UNDEF(&_98$$40);
	ZVAL_UNDEF(&_100$$40);
	ZVAL_UNDEF(&_112$$45);
	ZVAL_UNDEF(&_114$$45);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(connection, phalcon_db_adapter_adapterinterface_ce)
		Z_PARAM_ZVAL(related)
		Z_PARAM_OBJECT_OF_CLASS(visited, phalcon_support_collection_collectioninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &connection, &related, &visited);
	nesting = 0;
	ZEPHIR_INIT_VAR(&className);
	zephir_get_class(&className, this_ptr, 0);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getModelsManager", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_0);
	if (Z_TYPE_P(related) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, related);
		_1 = &_2;
	} else {
		_1 = related;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model.zep", 5657);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&name);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&name, _5);
			} else {
				ZVAL_LONG(&name, _4);
			}
			ZEPHIR_INIT_NVAR(&record);
			ZVAL_COPY(&record, _3);
			ZEPHIR_CALL_METHOD(&_6$$3, &manager, "getRelationByAlias", &_7, 0, &className, &name);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&relation, &_6$$3);
			if (Z_TYPE_P(&relation) == IS_OBJECT) {
				ZEPHIR_CALL_METHOD(&_8$$4, &relation, "getType", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_LONG(&_8$$4, 0)) {
					continue;
				}
				_9$$4 = Z_TYPE_P(&record) != IS_OBJECT;
				if (_9$$4) {
					_9$$4 = Z_TYPE_P(&record) != IS_ARRAY;
				}
				if (UNEXPECTED(_9$$4)) {
					if (nesting) {
						ZVAL_BOOL(&_10$$6, 1);
					} else {
						ZVAL_BOOL(&_10$$6, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_11, 0, &_10$$6);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_12$$6);
					object_init_ex(&_12$$6, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_13$$6);
					ZEPHIR_CONCAT_SVSV(&_13$$6, "Only objects/arrays can be stored as part of has-many/has-one/has-one-through/has-many-to-many relations on model ", &className, " on Relation ", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_12$$6, "__construct", &_14, 32, &_13$$6);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_12$$6, "phalcon/Mvc/Model.zep", 5492);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&columns, &relation, "getFields", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&referencedModel, &relation, "getReferencedModel", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
				zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&columns) == IS_ARRAY)) {
					if (nesting) {
						ZVAL_BOOL(&_15$$7, 1);
					} else {
						ZVAL_BOOL(&_15$$7, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_16, 0, &_15$$7);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_17$$7);
					object_init_ex(&_17$$7, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_18$$7);
					ZEPHIR_CONCAT_SVSV(&_18$$7, "Not implemented in '", &className, "' on Relation ", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_17$$7, "__construct", &_14, 32, &_18$$7);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_17$$7, "phalcon/Mvc/Model.zep", 5502);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (Z_TYPE_P(&record) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&relatedRecords);
					zephir_create_array(&relatedRecords, 1, 0);
					zephir_array_fast_append(&relatedRecords, &record);
				} else {
					ZEPHIR_CPY_WRT(&relatedRecords, &record);
				}
				ZEPHIR_OBS_NVAR(&value);
				if (UNEXPECTED(!(zephir_fetch_property_zval(&value, this_ptr, &columns, PH_SILENT_CC)))) {
					if (nesting) {
						ZVAL_BOOL(&_19$$10, 1);
					} else {
						ZVAL_BOOL(&_19$$10, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_20, 0, &_19$$10);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_21$$10);
					object_init_ex(&_21$$10, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_22$$10);
					ZEPHIR_CONCAT_SVSVS(&_22$$10, "The column '", &columns, "' needs to be present in the model '", &className, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_21$$10, "__construct", &_14, 32, &_22$$10);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_21$$10, "phalcon/Mvc/Model.zep", 5519);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_23$$4, &relation, "isThrough", NULL, 0);
				zephir_check_call_status();
				isThrough = zephir_get_boolval(&_23$$4);
				if (isThrough) {
					ZEPHIR_CALL_METHOD(&intermediateModelName, &relation, "getIntermediateModel", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&intermediateFields, &relation, "getIntermediateFields", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&intermediateReferencedFields, &relation, "getIntermediateReferencedFields", NULL, 0);
					zephir_check_call_status();
					if (Z_TYPE_P(&relatedRecords) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_25$$11);
						zephir_string_to_char_array(&_25$$11, &relatedRecords);
						_24$$11 = &_25$$11;
					} else {
						_24$$11 = &relatedRecords;
					}
					zephir_is_iterable(_24$$11, 0, "phalcon/Mvc/Model.zep", 5618);
					if (Z_TYPE_P(_24$$11) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_24$$11), _26$$11)
						{
							ZEPHIR_INIT_NVAR(&recordAfter);
							ZVAL_COPY(&recordAfter, _26$$11);
							ZEPHIR_CALL_METHOD(&_27$$12, &recordAfter, "doSave", NULL, 0, visited);
							zephir_check_call_status();
							if (!(zephir_is_true(&_27$$12))) {
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
								zephir_check_call_status();
								if (nesting) {
									ZVAL_BOOL(&_29$$13, 1);
								} else {
									ZVAL_BOOL(&_29$$13, 0);
								}
								ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_30, 0, &_29$$13);
								zephir_check_call_status();
								RETURN_MM_BOOL(0);
							}
							ZEPHIR_CALL_METHOD(&_31$$12, &manager, "load", &_32, 0, &intermediateModelName);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&intermediateModel, &_31$$12);
							ZEPHIR_CALL_METHOD(&_31$$12, &relation, "getType", &_33, 0);
							zephir_check_call_status();
							if (ZEPHIR_IS_LONG(&_31$$12, 3)) {
								ZEPHIR_INIT_NVAR(&_34$$14);
								zephir_create_array(&_34$$14, 2, 0);
								ZEPHIR_INIT_NVAR(&_35$$14);
								ZEPHIR_CONCAT_SVS(&_35$$14, "[", &intermediateFields, "] = ?0");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_fast_append(&_34$$14, &_35$$14);
								ZEPHIR_INIT_NVAR(&_36$$14);
								zephir_create_array(&_36$$14, 1, 0);
								zephir_array_fast_append(&_36$$14, &value);
								zephir_array_update_string(&_34$$14, SL("bind"), &_36$$14, PH_COPY | PH_SEPARATE);
								ZEPHIR_CALL_METHOD(&existingIntermediateModel, &intermediateModel, "findFirst", NULL, 0, &_34$$14);
								zephir_check_call_status();
								if (zephir_is_true(&existingIntermediateModel)) {
									ZEPHIR_CPY_WRT(&intermediateModel, &existingIntermediateModel);
								}
							}
							ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateFields, &value);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&intermediateValue, &recordAfter, "readAttribute", NULL, 0, &referencedFields);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateReferencedFields, &intermediateValue);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_37$$12, &intermediateModel, "doSave", NULL, 0, visited);
							zephir_check_call_status();
							if (!(zephir_is_true(&_37$$12))) {
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &intermediateModel);
								zephir_check_call_status();
								if (nesting) {
									ZVAL_BOOL(&_38$$16, 1);
								} else {
									ZVAL_BOOL(&_38$$16, 0);
								}
								ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_39, 0, &_38$$16);
								zephir_check_call_status();
								RETURN_MM_BOOL(0);
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _24$$11, "rewind", NULL, 0);
						zephir_check_call_status();
						_41$$11 = 1;
						while (1) {
							if (_41$$11) {
								_41$$11 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _24$$11, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_40$$11, _24$$11, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_40$$11)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&recordAfter, _24$$11, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&_42$$17, &recordAfter, "doSave", NULL, 0, visited);
								zephir_check_call_status();
								if (!(zephir_is_true(&_42$$17))) {
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
									zephir_check_call_status();
									if (nesting) {
										ZVAL_BOOL(&_43$$18, 1);
									} else {
										ZVAL_BOOL(&_43$$18, 0);
									}
									ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_44, 0, &_43$$18);
									zephir_check_call_status();
									RETURN_MM_BOOL(0);
								}
								ZEPHIR_CALL_METHOD(&_45$$17, &manager, "load", &_46, 0, &intermediateModelName);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&intermediateModel, &_45$$17);
								ZEPHIR_CALL_METHOD(&_45$$17, &relation, "getType", &_47, 0);
								zephir_check_call_status();
								if (ZEPHIR_IS_LONG(&_45$$17, 3)) {
									ZEPHIR_INIT_NVAR(&_48$$19);
									zephir_create_array(&_48$$19, 2, 0);
									ZEPHIR_INIT_NVAR(&_49$$19);
									ZEPHIR_CONCAT_SVS(&_49$$19, "[", &intermediateFields, "] = ?0");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_fast_append(&_48$$19, &_49$$19);
									ZEPHIR_INIT_NVAR(&_50$$19);
									zephir_create_array(&_50$$19, 1, 0);
									zephir_array_fast_append(&_50$$19, &value);
									zephir_array_update_string(&_48$$19, SL("bind"), &_50$$19, PH_COPY | PH_SEPARATE);
									ZEPHIR_CALL_METHOD(&existingIntermediateModel, &intermediateModel, "findFirst", NULL, 0, &_48$$19);
									zephir_check_call_status();
									if (zephir_is_true(&existingIntermediateModel)) {
										ZEPHIR_CPY_WRT(&intermediateModel, &existingIntermediateModel);
									}
								}
								ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateFields, &value);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&intermediateValue, &recordAfter, "readAttribute", NULL, 0, &referencedFields);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateReferencedFields, &intermediateValue);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&_51$$17, &intermediateModel, "doSave", NULL, 0, visited);
								zephir_check_call_status();
								if (!(zephir_is_true(&_51$$17))) {
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &intermediateModel);
									zephir_check_call_status();
									if (nesting) {
										ZVAL_BOOL(&_52$$21, 1);
									} else {
										ZVAL_BOOL(&_52$$21, 0);
									}
									ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_53, 0, &_52$$21);
									zephir_check_call_status();
									RETURN_MM_BOOL(0);
								}
						}
					}
					ZEPHIR_INIT_NVAR(&recordAfter);
				} else {
					if (Z_TYPE_P(&relatedRecords) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_55$$22);
						zephir_string_to_char_array(&_55$$22, &relatedRecords);
						_54$$22 = &_55$$22;
					} else {
						_54$$22 = &relatedRecords;
					}
					zephir_is_iterable(_54$$22, 0, "phalcon/Mvc/Model.zep", 5642);
					if (Z_TYPE_P(_54$$22) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_54$$22), _56$$22)
						{
							ZEPHIR_INIT_NVAR(&recordAfter);
							ZVAL_COPY(&recordAfter, _56$$22);
							ZEPHIR_CALL_METHOD(NULL, &recordAfter, "writeAttribute", NULL, 0, &referencedFields, &value);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_57$$23, &recordAfter, "doSave", NULL, 0, visited);
							zephir_check_call_status();
							if (!(zephir_is_true(&_57$$23))) {
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
								zephir_check_call_status();
								if (nesting) {
									ZVAL_BOOL(&_58$$24, 1);
								} else {
									ZVAL_BOOL(&_58$$24, 0);
								}
								ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_59, 0, &_58$$24);
								zephir_check_call_status();
								RETURN_MM_BOOL(0);
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _54$$22, "rewind", NULL, 0);
						zephir_check_call_status();
						_61$$22 = 1;
						while (1) {
							if (_61$$22) {
								_61$$22 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _54$$22, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_60$$22, _54$$22, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_60$$22)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&recordAfter, _54$$22, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_CALL_METHOD(NULL, &recordAfter, "writeAttribute", NULL, 0, &referencedFields, &value);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&_62$$25, &recordAfter, "doSave", NULL, 0, visited);
								zephir_check_call_status();
								if (!(zephir_is_true(&_62$$25))) {
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
									zephir_check_call_status();
									if (nesting) {
										ZVAL_BOOL(&_63$$26, 1);
									} else {
										ZVAL_BOOL(&_63$$26, 0);
									}
									ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_64, 0, &_63$$26);
									zephir_check_call_status();
									RETURN_MM_BOOL(0);
								}
						}
					}
					ZEPHIR_INIT_NVAR(&recordAfter);
				}
			} else {
				if (UNEXPECTED(Z_TYPE_P(&record) != IS_ARRAY)) {
					if (nesting) {
						ZVAL_BOOL(&_65$$28, 1);
					} else {
						ZVAL_BOOL(&_65$$28, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_66, 0, &_65$$28);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_67$$28);
					object_init_ex(&_67$$28, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_68$$28);
					ZEPHIR_CONCAT_SVSVS(&_68$$28, "There are no defined relations for the model '", &className, "' using alias '", &name, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_67$$28, "__construct", &_14, 32, &_68$$28);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_67$$28, "phalcon/Mvc/Model.zep", 5649);
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_70 = 1;
		while (1) {
			if (_70) {
				_70 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_69, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_69)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&name, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&record, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_71$$29, &manager, "getRelationByAlias", &_72, 0, &className, &name);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&relation, &_71$$29);
				if (Z_TYPE_P(&relation) == IS_OBJECT) {
					ZEPHIR_CALL_METHOD(&_73$$30, &relation, "getType", NULL, 0);
					zephir_check_call_status();
					if (ZEPHIR_IS_LONG(&_73$$30, 0)) {
						continue;
					}
					_74$$30 = Z_TYPE_P(&record) != IS_OBJECT;
					if (_74$$30) {
						_74$$30 = Z_TYPE_P(&record) != IS_ARRAY;
					}
					if (UNEXPECTED(_74$$30)) {
						if (nesting) {
							ZVAL_BOOL(&_75$$32, 1);
						} else {
							ZVAL_BOOL(&_75$$32, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_76, 0, &_75$$32);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_77$$32);
						object_init_ex(&_77$$32, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_78$$32);
						ZEPHIR_CONCAT_SVSV(&_78$$32, "Only objects/arrays can be stored as part of has-many/has-one/has-one-through/has-many-to-many relations on model ", &className, " on Relation ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_77$$32, "__construct", &_14, 32, &_78$$32);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_77$$32, "phalcon/Mvc/Model.zep", 5492);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&columns, &relation, "getFields", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&referencedModel, &relation, "getReferencedModel", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
					zephir_check_call_status();
					if (UNEXPECTED(Z_TYPE_P(&columns) == IS_ARRAY)) {
						if (nesting) {
							ZVAL_BOOL(&_79$$33, 1);
						} else {
							ZVAL_BOOL(&_79$$33, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_80, 0, &_79$$33);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_81$$33);
						object_init_ex(&_81$$33, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_82$$33);
						ZEPHIR_CONCAT_SVSV(&_82$$33, "Not implemented in '", &className, "' on Relation ", &name);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_81$$33, "__construct", &_14, 32, &_82$$33);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_81$$33, "phalcon/Mvc/Model.zep", 5502);
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (Z_TYPE_P(&record) == IS_OBJECT) {
						ZEPHIR_INIT_NVAR(&_83$$34);
						zephir_create_array(&_83$$34, 1, 0);
						zephir_array_fast_append(&_83$$34, &record);
						ZEPHIR_CPY_WRT(&relatedRecords, &_83$$34);
					} else {
						ZEPHIR_CPY_WRT(&relatedRecords, &record);
					}
					ZEPHIR_OBS_NVAR(&value);
					if (UNEXPECTED(!(zephir_fetch_property_zval(&value, this_ptr, &columns, PH_SILENT_CC)))) {
						if (nesting) {
							ZVAL_BOOL(&_84$$36, 1);
						} else {
							ZVAL_BOOL(&_84$$36, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_85, 0, &_84$$36);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_86$$36);
						object_init_ex(&_86$$36, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_87$$36);
						ZEPHIR_CONCAT_SVSVS(&_87$$36, "The column '", &columns, "' needs to be present in the model '", &className, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_86$$36, "__construct", &_14, 32, &_87$$36);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_86$$36, "phalcon/Mvc/Model.zep", 5519);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_88$$30, &relation, "isThrough", NULL, 0);
					zephir_check_call_status();
					isThrough = zephir_get_boolval(&_88$$30);
					if (isThrough) {
						ZEPHIR_CALL_METHOD(&intermediateModelName, &relation, "getIntermediateModel", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&intermediateFields, &relation, "getIntermediateFields", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&intermediateReferencedFields, &relation, "getIntermediateReferencedFields", NULL, 0);
						zephir_check_call_status();
						if (Z_TYPE_P(&relatedRecords) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_90$$37);
							zephir_string_to_char_array(&_90$$37, &relatedRecords);
							_89$$37 = &_90$$37;
						} else {
							_89$$37 = &relatedRecords;
						}
						zephir_is_iterable(_89$$37, 0, "phalcon/Mvc/Model.zep", 5618);
						if (Z_TYPE_P(_89$$37) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_89$$37), _91$$37)
							{
								ZEPHIR_INIT_NVAR(&recordAfter);
								ZVAL_COPY(&recordAfter, _91$$37);
								ZEPHIR_CALL_METHOD(&_92$$38, &recordAfter, "doSave", NULL, 0, visited);
								zephir_check_call_status();
								if (!(zephir_is_true(&_92$$38))) {
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
									zephir_check_call_status();
									if (nesting) {
										ZVAL_BOOL(&_93$$39, 1);
									} else {
										ZVAL_BOOL(&_93$$39, 0);
									}
									ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_94, 0, &_93$$39);
									zephir_check_call_status();
									RETURN_MM_BOOL(0);
								}
								ZEPHIR_CALL_METHOD(&_95$$38, &manager, "load", &_96, 0, &intermediateModelName);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&intermediateModel, &_95$$38);
								ZEPHIR_CALL_METHOD(&_95$$38, &relation, "getType", &_97, 0);
								zephir_check_call_status();
								if (ZEPHIR_IS_LONG(&_95$$38, 3)) {
									ZEPHIR_INIT_NVAR(&_98$$40);
									zephir_create_array(&_98$$40, 2, 0);
									ZEPHIR_INIT_NVAR(&_99$$40);
									ZEPHIR_CONCAT_SVS(&_99$$40, "[", &intermediateFields, "] = ?0");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_fast_append(&_98$$40, &_99$$40);
									ZEPHIR_INIT_NVAR(&_100$$40);
									zephir_create_array(&_100$$40, 1, 0);
									zephir_array_fast_append(&_100$$40, &value);
									zephir_array_update_string(&_98$$40, SL("bind"), &_100$$40, PH_COPY | PH_SEPARATE);
									ZEPHIR_CALL_METHOD(&existingIntermediateModel, &intermediateModel, "findFirst", NULL, 0, &_98$$40);
									zephir_check_call_status();
									if (zephir_is_true(&existingIntermediateModel)) {
										ZEPHIR_CPY_WRT(&intermediateModel, &existingIntermediateModel);
									}
								}
								ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateFields, &value);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&intermediateValue, &recordAfter, "readAttribute", NULL, 0, &referencedFields);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateReferencedFields, &intermediateValue);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&_101$$38, &intermediateModel, "doSave", NULL, 0, visited);
								zephir_check_call_status();
								if (!(zephir_is_true(&_101$$38))) {
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &intermediateModel);
									zephir_check_call_status();
									if (nesting) {
										ZVAL_BOOL(&_102$$42, 1);
									} else {
										ZVAL_BOOL(&_102$$42, 0);
									}
									ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_103, 0, &_102$$42);
									zephir_check_call_status();
									RETURN_MM_BOOL(0);
								}
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _89$$37, "rewind", NULL, 0);
							zephir_check_call_status();
							_105$$37 = 1;
							while (1) {
								if (_105$$37) {
									_105$$37 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _89$$37, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_104$$37, _89$$37, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_104$$37)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&recordAfter, _89$$37, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&_106$$43, &recordAfter, "doSave", NULL, 0, visited);
									zephir_check_call_status();
									if (!(zephir_is_true(&_106$$43))) {
										ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
										zephir_check_call_status();
										if (nesting) {
											ZVAL_BOOL(&_107$$44, 1);
										} else {
											ZVAL_BOOL(&_107$$44, 0);
										}
										ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_108, 0, &_107$$44);
										zephir_check_call_status();
										RETURN_MM_BOOL(0);
									}
									ZEPHIR_CALL_METHOD(&_109$$43, &manager, "load", &_110, 0, &intermediateModelName);
									zephir_check_call_status();
									ZEPHIR_CPY_WRT(&intermediateModel, &_109$$43);
									ZEPHIR_CALL_METHOD(&_109$$43, &relation, "getType", &_111, 0);
									zephir_check_call_status();
									if (ZEPHIR_IS_LONG(&_109$$43, 3)) {
										ZEPHIR_INIT_NVAR(&_112$$45);
										zephir_create_array(&_112$$45, 2, 0);
										ZEPHIR_INIT_NVAR(&_113$$45);
										ZEPHIR_CONCAT_SVS(&_113$$45, "[", &intermediateFields, "] = ?0");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										zephir_array_fast_append(&_112$$45, &_113$$45);
										ZEPHIR_INIT_NVAR(&_114$$45);
										zephir_create_array(&_114$$45, 1, 0);
										zephir_array_fast_append(&_114$$45, &value);
										zephir_array_update_string(&_112$$45, SL("bind"), &_114$$45, PH_COPY | PH_SEPARATE);
										ZEPHIR_CALL_METHOD(&existingIntermediateModel, &intermediateModel, "findFirst", NULL, 0, &_112$$45);
										zephir_check_call_status();
										if (zephir_is_true(&existingIntermediateModel)) {
											ZEPHIR_CPY_WRT(&intermediateModel, &existingIntermediateModel);
										}
									}
									ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateFields, &value);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&intermediateValue, &recordAfter, "readAttribute", NULL, 0, &referencedFields);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(NULL, &intermediateModel, "writeAttribute", NULL, 0, &intermediateReferencedFields, &intermediateValue);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&_115$$43, &intermediateModel, "doSave", NULL, 0, visited);
									zephir_check_call_status();
									if (!(zephir_is_true(&_115$$43))) {
										ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &intermediateModel);
										zephir_check_call_status();
										if (nesting) {
											ZVAL_BOOL(&_116$$47, 1);
										} else {
											ZVAL_BOOL(&_116$$47, 0);
										}
										ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_117, 0, &_116$$47);
										zephir_check_call_status();
										RETURN_MM_BOOL(0);
									}
							}
						}
						ZEPHIR_INIT_NVAR(&recordAfter);
					} else {
						if (Z_TYPE_P(&relatedRecords) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_119$$48);
							zephir_string_to_char_array(&_119$$48, &relatedRecords);
							_118$$48 = &_119$$48;
						} else {
							_118$$48 = &relatedRecords;
						}
						zephir_is_iterable(_118$$48, 0, "phalcon/Mvc/Model.zep", 5642);
						if (Z_TYPE_P(_118$$48) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_118$$48), _120$$48)
							{
								ZEPHIR_INIT_NVAR(&recordAfter);
								ZVAL_COPY(&recordAfter, _120$$48);
								ZEPHIR_CALL_METHOD(NULL, &recordAfter, "writeAttribute", NULL, 0, &referencedFields, &value);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&_121$$49, &recordAfter, "doSave", NULL, 0, visited);
								zephir_check_call_status();
								if (!(zephir_is_true(&_121$$49))) {
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
									zephir_check_call_status();
									if (nesting) {
										ZVAL_BOOL(&_122$$50, 1);
									} else {
										ZVAL_BOOL(&_122$$50, 0);
									}
									ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_123, 0, &_122$$50);
									zephir_check_call_status();
									RETURN_MM_BOOL(0);
								}
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _118$$48, "rewind", NULL, 0);
							zephir_check_call_status();
							_125$$48 = 1;
							while (1) {
								if (_125$$48) {
									_125$$48 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _118$$48, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_124$$48, _118$$48, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_124$$48)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&recordAfter, _118$$48, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_CALL_METHOD(NULL, &recordAfter, "writeAttribute", NULL, 0, &referencedFields, &value);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&_126$$51, &recordAfter, "doSave", NULL, 0, visited);
									zephir_check_call_status();
									if (!(zephir_is_true(&_126$$51))) {
										ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessagesFrom", &_28, 0, &recordAfter);
										zephir_check_call_status();
										if (nesting) {
											ZVAL_BOOL(&_127$$52, 1);
										} else {
											ZVAL_BOOL(&_127$$52, 0);
										}
										ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_128, 0, &_127$$52);
										zephir_check_call_status();
										RETURN_MM_BOOL(0);
									}
							}
						}
						ZEPHIR_INIT_NVAR(&recordAfter);
					}
				} else {
					if (UNEXPECTED(Z_TYPE_P(&record) != IS_ARRAY)) {
						if (nesting) {
							ZVAL_BOOL(&_129$$54, 1);
						} else {
							ZVAL_BOOL(&_129$$54, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, connection, "rollback", &_130, 0, &_129$$54);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_131$$54);
						object_init_ex(&_131$$54, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_132$$54);
						ZEPHIR_CONCAT_SVSVS(&_132$$54, "There are no defined relations for the model '", &className, "' using alias '", &name, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_131$$54, "__construct", &_14, 32, &_132$$54);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_131$$54, "phalcon/Mvc/Model.zep", 5649);
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&record);
	ZEPHIR_INIT_NVAR(&name);
	if (nesting) {
		ZVAL_BOOL(&_133, 1);
	} else {
		ZVAL_BOOL(&_133, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, connection, "commit", NULL, 0, &_133);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);
}

/**
 * Sets a list of attributes that must be skipped from the
 * generated UPDATE statement
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->allowEmptyStringValues(
 *             [
 *                 "name",
 *             ]
 *         );
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, allowEmptyStringValues)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *attributes_param = NULL, __$true, keysAttributes, attribute, *_0, _1, _3;
	zval attributes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&keysAttributes);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &attributes_param);
	ZEPHIR_OBS_COPY_OR_DUP(&attributes, attributes_param);
	ZEPHIR_INIT_VAR(&keysAttributes);
	array_init(&keysAttributes);
	zephir_is_iterable(&attributes, 0, "phalcon/Mvc/Model.zep", 5690);
	if (Z_TYPE_P(&attributes) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&attributes), _0)
		{
			ZEPHIR_INIT_NVAR(&attribute);
			ZVAL_COPY(&attribute, _0);
			zephir_array_update_zval(&keysAttributes, &attribute, &__$true, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &attributes, "rewind", NULL, 0);
		zephir_check_call_status();
		_2 = 1;
		while (1) {
			if (_2) {
				_2 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &attributes, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_1, &attributes, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_1)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&attribute, &attributes, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_update_zval(&keysAttributes, &attribute, &__$true, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&attribute);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_3, "setEmptyStringAttributes", NULL, 0, this_ptr, &keysAttributes);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Cancel the current operation
 */
PHP_METHOD(Phalcon_Mvc_Model, cancelOperation)
{
	zval _0, _1$$3, _2$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("operationMade", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 714, PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_LONG(&_0, 3)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "notDeleted");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_1$$3);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(&_2$$4);
		ZVAL_STRING(&_2$$4, "notSaved");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireEvent", NULL, 0, &_2$$4);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Setup a reverse 1-1 or n-1 relation between two models
 *
 *```php
 * class RobotsParts extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->belongsTo(
 *             "robots_id",
 *             Robots::class,
 *             "id"
 *         );
 *     }
 * }
 *```
 *
 * @param array $options = [
 *     'reusable' => false,
 *     'alias' => 'someAlias',
 *     'foreignKey' => [
 *         'message' => null,
 *         'allowNulls' => false,
 *         'action' => null
 *     ],
 *     'params' => [
 *         'conditions' => '',
 *         'columns' => '',
 *         'bind' => [],
 *         'bindTypes' => [],
 *         'order' => '',
 *         'limit' => 10,
 *         'offset' => 5,
 *         'group' => 'name, status',
 *         'for_update' => false,
 *         'shared_lock' => false,
 *         'cache' => [
 *             'lifetime' => 3600,
 *             'key' => 'my-find-key'
 *         ],
 *         'hydration' => null
 *     ]
 * ]
 */
PHP_METHOD(Phalcon_Mvc_Model, belongsTo)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval options;
	zend_string *referenceModel = NULL;
	zval *fields, fields_sub, referenceModel_zv, *referencedFields, referencedFields_sub, *options_param = NULL, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&referenceModel_zv);
	ZVAL_UNDEF(&referencedFields_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_ZVAL(fields)
		Z_PARAM_STR(referenceModel)
		Z_PARAM_ZVAL(referencedFields)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	fields = ZEND_CALL_ARG(execute_data, 1);
	referencedFields = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		options_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&referenceModel_zv);
	ZVAL_STR_COPY(&referenceModel_zv, referenceModel);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "addBelongsTo", NULL, 0, this_ptr, fields, &referenceModel_zv, referencedFields, &options);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * shared prepare query logic for find and findFirst method
 */
PHP_METHOD(Phalcon_Mvc_Model, getPreparedQuery)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *params, params_sub, *limit = NULL, limit_sub, __$null, builder, bindParams, bindTypes, transaction, cache, manager, query, container, _0, _1, _2$$5, _3$$7;

	ZVAL_UNDEF(&params_sub);
	ZVAL_UNDEF(&limit_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&builder);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&transaction);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$7);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(params)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(limit)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &params, &limit);
	if (!limit) {
		limit = &limit_sub;
		limit = &__$null;
	}
	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "modelsManager");
	ZEPHIR_CALL_METHOD(&_0, &container, "getShared", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_0);
	ZEPHIR_CALL_METHOD(&_0, &manager, "createBuilder", NULL, 0, params);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&builder, &_0);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_get_called_class(&_1);
	ZEPHIR_CALL_METHOD(NULL, &builder, "from", NULL, 0, &_1);
	zephir_check_call_status();
	if (Z_TYPE_P(limit) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, &builder, "limit", NULL, 0, limit);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_0, &builder, "getQuery", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&query, &_0);
	zephir_memory_observe(&bindParams);
	if (zephir_array_isset_string_fetch(&bindParams, params, SL("bind"), 0)) {
		if (Z_TYPE_P(&bindParams) == IS_ARRAY) {
			ZVAL_BOOL(&_2$$5, 1);
			ZEPHIR_CALL_METHOD(NULL, &query, "setBindParams", NULL, 0, &bindParams, &_2$$5);
			zephir_check_call_status();
		}
		zephir_memory_observe(&bindTypes);
		if (zephir_array_isset_string_fetch(&bindTypes, params, SL("bindTypes"), 0)) {
			if (Z_TYPE_P(&bindTypes) == IS_ARRAY) {
				ZVAL_BOOL(&_3$$7, 1);
				ZEPHIR_CALL_METHOD(NULL, &query, "setBindTypes", NULL, 0, &bindTypes, &_3$$7);
				zephir_check_call_status();
			}
		}
	}
	zephir_memory_observe(&transaction);
	if (zephir_array_isset_string_fetch(&transaction, params, SL("transaction"), 0)) {
		if (zephir_instance_of_ev(&transaction, phalcon_mvc_model_transactioninterface_ce)) {
			ZEPHIR_CALL_METHOD(NULL, &query, "setTransaction", NULL, 0, &transaction);
			zephir_check_call_status();
		}
	}
	zephir_memory_observe(&cache);
	if (zephir_array_isset_string_fetch(&cache, params, SL("cache"), 0)) {
		ZEPHIR_CALL_METHOD(NULL, &query, "cache", NULL, 0, &cache);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&query);
}

/**
 * Setup a 1-n relation between two models
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->hasMany(
 *             "id",
 *             RobotsParts::class,
 *             "robots_id"
 *         );
 *     }
 * }
 *```
 *
 * @param array $options = [
 *     'reusable' => false,
 *     'alias' => 'someAlias',
 *     'foreignKey' => [
 *         'message' => null,
 *         'allowNulls' => false,
 *         'action' => null
 *     ],
 *     'params' => [
 *         'conditions' => '',
 *         'columns' => '',
 *         'bind' => [],
 *         'bindTypes' => [],
 *         'order' => '',
 *         'limit' => 10,
 *         'offset' => 5,
 *         'group' => 'name, status',
 *         'for_update' => false,
 *         'shared_lock' => false,
 *         'cache' => [
 *             'lifetime' => 3600,
 *             'key' => 'my-find-key'
 *         ],
 *         'hydration' => null
 *     ]
 * ]
 */
PHP_METHOD(Phalcon_Mvc_Model, hasMany)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval options;
	zend_string *referenceModel = NULL;
	zval *fields, fields_sub, referenceModel_zv, *referencedFields, referencedFields_sub, *options_param = NULL, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&referenceModel_zv);
	ZVAL_UNDEF(&referencedFields_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_ZVAL(fields)
		Z_PARAM_STR(referenceModel)
		Z_PARAM_ZVAL(referencedFields)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	fields = ZEND_CALL_ARG(execute_data, 1);
	referencedFields = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		options_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&referenceModel_zv);
	ZVAL_STR_COPY(&referenceModel_zv, referenceModel);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "addHasMany", NULL, 0, this_ptr, fields, &referenceModel_zv, referencedFields, &options);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Setup an n-n relation between two models, through an intermediate
 * relation
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         // Setup a many-to-many relation to Parts through RobotsParts
 *         $this->hasManyToMany(
 *             "id",
 *             RobotsParts::class,
 *             "robots_id",
 *             "parts_id",
 *             Parts::class,
 *             "id",
 *         );
 *     }
 * }
 *```
 *
 * @param string|array fields
 * @param string intermediateModel
 * @param string|array intermediateFields
 * @param string|array intermediateReferencedFields
 * @param string referenceModel
 * @param string|array referencedFields
 * @param array $options = [
 *     'reusable' => false,
 *     'alias' => 'someAlias',
 *     'foreignKey' => [
 *         'message' => null,
 *         'allowNulls' => false,
 *         'action' => null
 *     ],
 *     'params' => [
 *         'conditions' => '',
 *         'columns' => '',
 *         'bind' => [],
 *         'bindTypes' => [],
 *         'order' => '',
 *         'limit' => 10,
 *         'offset' => 5,
 *         'group' => 'name, status',
 *         'for_update' => false,
 *         'shared_lock' => false,
 *         'cache' => [
 *             'lifetime' => 3600,
 *             'key' => 'my-find-key'
 *         ],
 *         'hydration' => null
 *     ]
 * ]
 */
PHP_METHOD(Phalcon_Mvc_Model, hasManyToMany)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval options;
	zend_string *intermediateModel = NULL, *referenceModel = NULL;
	zval *fields, fields_sub, intermediateModel_zv, *intermediateFields, intermediateFields_sub, *intermediateReferencedFields, intermediateReferencedFields_sub, referenceModel_zv, *referencedFields, referencedFields_sub, *options_param = NULL, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&intermediateModel_zv);
	ZVAL_UNDEF(&intermediateFields_sub);
	ZVAL_UNDEF(&intermediateReferencedFields_sub);
	ZVAL_UNDEF(&referenceModel_zv);
	ZVAL_UNDEF(&referencedFields_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(6, 7)
		Z_PARAM_ZVAL(fields)
		Z_PARAM_STR(intermediateModel)
		Z_PARAM_ZVAL(intermediateFields)
		Z_PARAM_ZVAL(intermediateReferencedFields)
		Z_PARAM_STR(referenceModel)
		Z_PARAM_ZVAL(referencedFields)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	fields = ZEND_CALL_ARG(execute_data, 1);
	intermediateFields = ZEND_CALL_ARG(execute_data, 3);
	intermediateReferencedFields = ZEND_CALL_ARG(execute_data, 4);
	referencedFields = ZEND_CALL_ARG(execute_data, 6);
	if (ZEND_NUM_ARGS() > 6) {
		options_param = ZEND_CALL_ARG(execute_data, 7);
	}
	zephir_memory_observe(&intermediateModel_zv);
	ZVAL_STR_COPY(&intermediateModel_zv, intermediateModel);
	zephir_memory_observe(&referenceModel_zv);
	ZVAL_STR_COPY(&referenceModel_zv, referenceModel);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "addHasManyToMany", NULL, 0, this_ptr, fields, &intermediateModel_zv, intermediateFields, intermediateReferencedFields, &referenceModel_zv, referencedFields, &options);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Setup a 1-1 relation between two models
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->hasOne(
 *             "id",
 *             RobotsDescription::class,
 *             "robots_id"
 *         );
 *     }
 * }
 *```
 *
 * @param array $options = [
 *     'reusable' => false,
 *     'alias' => 'someAlias',
 *     'foreignKey' => [
 *         'message' => null,
 *         'allowNulls' => false,
 *         'action' => null
 *     ],
 *     'params' => [
 *         'conditions' => '',
 *         'columns' => '',
 *         'bind' => [],
 *         'bindTypes' => [],
 *         'order' => '',
 *         'limit' => 10,
 *         'offset' => 5,
 *         'group' => 'name, status',
 *         'for_update' => false,
 *         'shared_lock' => false,
 *         'cache' => [
 *             'lifetime' => 3600,
 *             'key' => 'my-find-key'
 *         ],
 *         'hydration' => null
 *     ]
 * ]
 */
PHP_METHOD(Phalcon_Mvc_Model, hasOne)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval options;
	zend_string *referenceModel = NULL;
	zval *fields, fields_sub, referenceModel_zv, *referencedFields, referencedFields_sub, *options_param = NULL, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&referenceModel_zv);
	ZVAL_UNDEF(&referencedFields_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_ZVAL(fields)
		Z_PARAM_STR(referenceModel)
		Z_PARAM_ZVAL(referencedFields)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	fields = ZEND_CALL_ARG(execute_data, 1);
	referencedFields = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		options_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&referenceModel_zv);
	ZVAL_STR_COPY(&referenceModel_zv, referenceModel);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "addHasOne", NULL, 0, this_ptr, fields, &referenceModel_zv, referencedFields, &options);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Setup a 1-1 relation between two models, through an intermediate
 * relation
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         // Setup a 1-1 relation to one item from Parts through RobotsParts
 *         $this->hasOneThrough(
 *             "id",
 *             RobotsParts::class,
 *             "robots_id",
 *             "parts_id",
 *             Parts::class,
 *             "id",
 *         );
 *     }
 * }
 *```
 *
 * @param    string|array $fields
 * @param    string|array $intermediateFields
 * @param    string|array $intermediateReferencedFields
 * @param    string|array $referencedFields
 * @param    array $options
 */
PHP_METHOD(Phalcon_Mvc_Model, hasOneThrough)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval options;
	zend_string *intermediateModel = NULL, *referenceModel = NULL;
	zval *fields, fields_sub, intermediateModel_zv, *intermediateFields, intermediateFields_sub, *intermediateReferencedFields, intermediateReferencedFields_sub, referenceModel_zv, *referencedFields, referencedFields_sub, *options_param = NULL, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&intermediateModel_zv);
	ZVAL_UNDEF(&intermediateFields_sub);
	ZVAL_UNDEF(&intermediateReferencedFields_sub);
	ZVAL_UNDEF(&referenceModel_zv);
	ZVAL_UNDEF(&referencedFields_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(6, 7)
		Z_PARAM_ZVAL(fields)
		Z_PARAM_STR(intermediateModel)
		Z_PARAM_ZVAL(intermediateFields)
		Z_PARAM_ZVAL(intermediateReferencedFields)
		Z_PARAM_STR(referenceModel)
		Z_PARAM_ZVAL(referencedFields)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	fields = ZEND_CALL_ARG(execute_data, 1);
	intermediateFields = ZEND_CALL_ARG(execute_data, 3);
	intermediateReferencedFields = ZEND_CALL_ARG(execute_data, 4);
	referencedFields = ZEND_CALL_ARG(execute_data, 6);
	if (ZEND_NUM_ARGS() > 6) {
		options_param = ZEND_CALL_ARG(execute_data, 7);
	}
	zephir_memory_observe(&intermediateModel_zv);
	ZVAL_STR_COPY(&intermediateModel_zv, intermediateModel);
	zephir_memory_observe(&referenceModel_zv);
	ZVAL_STR_COPY(&referenceModel_zv, referenceModel);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "addHasOneThrough", NULL, 0, this_ptr, fields, &intermediateModel_zv, intermediateFields, intermediateReferencedFields, &referenceModel_zv, referencedFields, &options);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Sets if the model must keep the original record snapshot in memory
 *
 *```php
 * use Phalcon\Mvc\Model;
 *
 * class Robots extends Model
 * {
 *     public function initialize()
 *     {
 *         $this->keepSnapshots(true);
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, keepSnapshots)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *keepSnapshot_param = NULL, _0, _1;
	zend_bool keepSnapshot;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(keepSnapshot)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &keepSnapshot_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	if (keepSnapshot) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "keepSnapshots", NULL, 0, this_ptr, &_1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets schema name where the mapped table is located
 */
PHP_METHOD(Phalcon_Mvc_Model, setSchema)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval schema_zv, _0;
	zend_string *schema = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(schema)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&schema_zv);
	ZVAL_STR_COPY(&schema_zv, schema);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setModelSchema", NULL, 0, this_ptr, &schema_zv);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets the table name to which model should be mapped
 */
PHP_METHOD(Phalcon_Mvc_Model, setSource)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval source_zv, _0;
	zend_string *source = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&source_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(source)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&source_zv);
	ZVAL_STR_COPY(&source_zv, source);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setModelSource", NULL, 0, this_ptr, &source_zv);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sets a list of attributes that must be skipped from the
 * generated INSERT/UPDATE statement
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->skipAttributes(
 *             [
 *                 "price",
 *             ]
 *         );
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, skipAttributes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *attributes_param = NULL;
	zval attributes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &attributes_param);
	ZEPHIR_OBS_COPY_OR_DUP(&attributes, attributes_param);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "skipAttributesOnCreate", NULL, 0, &attributes);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "skipAttributesOnUpdate", NULL, 0, &attributes);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets a list of attributes that must be skipped from the
 * generated INSERT statement
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->skipAttributesOnCreate(
 *             [
 *                 "created_at",
 *             ]
 *         );
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, skipAttributesOnCreate)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *attributes_param = NULL, __$null, attribute, *_0, _1, _3;
	zval attributes, keysAttributes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&keysAttributes);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &attributes_param);
	ZEPHIR_OBS_COPY_OR_DUP(&attributes, attributes_param);
	ZEPHIR_INIT_VAR(&keysAttributes);
	array_init(&keysAttributes);
	zephir_is_iterable(&attributes, 0, "phalcon/Mvc/Model.zep", 6149);
	if (Z_TYPE_P(&attributes) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&attributes), _0)
		{
			ZEPHIR_INIT_NVAR(&attribute);
			ZVAL_COPY(&attribute, _0);
			zephir_array_update_zval(&keysAttributes, &attribute, &__$null, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &attributes, "rewind", NULL, 0);
		zephir_check_call_status();
		_2 = 1;
		while (1) {
			if (_2) {
				_2 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &attributes, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_1, &attributes, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_1)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&attribute, &attributes, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_update_zval(&keysAttributes, &attribute, &__$null, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&attribute);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_3, "setAutomaticCreateAttributes", NULL, 0, this_ptr, &keysAttributes);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets a list of attributes that must be skipped from the
 * generated UPDATE statement
 *
 *```php
 * class Robots extends \Phalcon\Mvc\Model
 * {
 *     public function initialize()
 *     {
 *         $this->skipAttributesOnUpdate(
 *             [
 *                 "modified_in",
 *             ]
 *         );
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, skipAttributesOnUpdate)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *attributes_param = NULL, __$null, attribute, *_0, _1, _3;
	zval attributes, keysAttributes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&keysAttributes);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &attributes_param);
	ZEPHIR_OBS_COPY_OR_DUP(&attributes, attributes_param);
	ZEPHIR_INIT_VAR(&keysAttributes);
	array_init(&keysAttributes);
	zephir_is_iterable(&attributes, 0, "phalcon/Mvc/Model.zep", 6184);
	if (Z_TYPE_P(&attributes) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&attributes), _0)
		{
			ZEPHIR_INIT_NVAR(&attribute);
			ZVAL_COPY(&attribute, _0);
			zephir_array_update_zval(&keysAttributes, &attribute, &__$null, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &attributes, "rewind", NULL, 0);
		zephir_check_call_status();
		_2 = 1;
		while (1) {
			if (_2) {
				_2 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &attributes, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_1, &attributes, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_1)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&attribute, &attributes, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_update_zval(&keysAttributes, &attribute, &__$null, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&attribute);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getModelsMetaData", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_3, "setAutomaticUpdateAttributes", NULL, 0, this_ptr, &keysAttributes);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets if a model must use dynamic update instead of the all-field update
 *
 *```php
 * use Phalcon\Mvc\Model;
 *
 * class Robots extends Model
 * {
 *     public function initialize()
 *     {
 *         $this->useDynamicUpdate(true);
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, useDynamicUpdate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *dynamicUpdate_param = NULL, _0, _1;
	zend_bool dynamicUpdate;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(dynamicUpdate)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &dynamicUpdate_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 708, PH_NOISY_CC | PH_READONLY);
	if (dynamicUpdate) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "useDynamicUpdate", NULL, 0, this_ptr, &_1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Executes validators on every validation call
 *
 *```php
 * use Phalcon\Mvc\Model;
 * use Phalcon\Filter\Validation;
 * use Phalcon\Filter\Validation\Validator\ExclusionIn;
 *
 * class Subscriptors extends Model
 * {
 *     public function validation()
 *     {
 *         $validator = new Validation();
 *
 *         $validator->add(
 *             "status",
 *             new ExclusionIn(
 *                 [
 *                     "domain" => [
 *                         "A",
 *                         "I",
 *                     ],
 *                 ]
 *             )
 *         );
 *
 *         return $this->validate($validator);
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, validate)
{
	zend_object_iterator *_1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *validator, validator_sub, messages, message, _0, _2$$4, _3$$4, _4$$4, _5$$4, _6$$4, _7$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&validator_sub);
	ZVAL_UNDEF(&messages);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(validator, phalcon_filter_validation_validationinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &validator);
	ZVAL_NULL(&_0);
	ZEPHIR_CALL_METHOD(&messages, validator, "validate", NULL, 0, &_0, this_ptr);
	zephir_check_call_status();
	if (((Z_TYPE_P(&messages) == IS_TRUE || Z_TYPE_P(&messages) == IS_FALSE) == 1)) {
		RETURN_CCTOR(&messages);
	}
	_1 = zephir_get_iterator(&messages);
	if (EXPECTED(_1 != NULL)) {
		_1->funcs->rewind(_1);
		for (;_1->funcs->valid(_1) == SUCCESS && !EG(exception); _1->funcs->move_forward(_1)) {
		{
			ZEPHIR_ITERATOR_COPY(&message, _1);
		}
		ZEPHIR_INIT_NVAR(&_2$$4);
		object_init_ex(&_2$$4, phalcon_messages_message_ce);
		ZEPHIR_CALL_METHOD(&_3$$4, &message, "getMessage", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$4, &message, "getField", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_5$$4, &message, "getType", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_6$$4, &message, "getCode", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_7$$4, &message, "getMetaData", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", &_8, 6, &_3$$4, &_4$$4, &_5$$4, &_6$$4, &_7$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_9, 0, &_2$$4);
		zephir_check_call_status();
	}
	zend_iterator_dtor(_1);
	}
	RETURN_MM_BOOL(!(zephir_fast_count_int(&messages)));
}

/**
 * Check whether validation process has generated any messages
 *
 *```php
 * use Phalcon\Mvc\Model;
 * use Phalcon\Filter\Validation;
 * use Phalcon\Filter\Validation\Validator\ExclusionIn;
 *
 * class Subscriptors extends Model
 * {
 *     public function validation()
 *     {
 *         $validator = new Validation();
 *
 *         $validator->validate(
 *             "status",
 *             new ExclusionIn(
 *                 [
 *                     "domain" => [
 *                         "A",
 *                         "I",
 *                     ],
 *                 ]
 *             )
 *         );
 *
 *         return $this->validate($validator);
 *     }
 * }
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model, validationHasFailed)
{
	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("errorMessages", 13, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 713, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_fast_count_int(&_0) > 0);
}

/**
 * Attempts to find key case-insensitively
 */
PHP_METHOD(Phalcon_Mvc_Model, caseInsensitiveColumnMap)
{
	zend_bool _6$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *columnMap, columnMap_sub, *key, key_sub, cmKey, _0, *_1, _2, *_3, _4$$3, _5$$3;

	ZVAL_UNDEF(&columnMap_sub);
	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&cmKey);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(columnMap)
		Z_PARAM_ZVAL(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &columnMap, &key);
	ZEPHIR_INIT_VAR(&_0);
	zephir_array_keys(&_0, columnMap);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model.zep", 6321);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
	{
		ZEPHIR_INIT_NVAR(&cmKey);
		ZVAL_COPY(&cmKey, _3);
		ZEPHIR_INIT_NVAR(&_4$$3);
		zephir_fast_strtolower(&_4$$3, &cmKey);
		ZEPHIR_INIT_NVAR(&_5$$3);
		zephir_fast_strtolower(&_5$$3, key);
		_6$$3 = ZEPHIR_IS_EQUAL(&_4$$3, &_5$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (_6$$3) {
			RETURN_CCTOR(&cmKey);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&cmKey);
	RETVAL_ZVAL(key, 1, 0);
	RETURN_MM();
}

/***
 * Append messages to this model from another Model.
 */
PHP_METHOD(Phalcon_Mvc_Model, appendMessagesFrom)
{
	zval _3$$5, _7$$7;
	zend_bool _6$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *model, model_sub, messages, message, *_0$$3, _1$$3, *_2$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&messages);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_7$$7);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(model)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &model);
	ZEPHIR_CALL_METHOD(&messages, model, "getMessages", NULL, 0);
	zephir_check_call_status();
	if (0 == ZEPHIR_IS_EMPTY(&messages)) {
		if (Z_TYPE_P(&messages) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_string_to_char_array(&_1$$3, &messages);
			_0$$3 = &_1$$3;
		} else {
			_0$$3 = &messages;
		}
		zephir_is_iterable(_0$$3, 0, "phalcon/Mvc/Model.zep", 6345);
		if (Z_TYPE_P(_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$3), _2$$3)
			{
				ZEPHIR_INIT_NVAR(&message);
				ZVAL_COPY(&message, _2$$3);
				if (Z_TYPE_P(&message) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_3$$5);
					zephir_create_array(&_3$$5, 1, 0);
					zephir_array_update_string(&_3$$5, SL("model"), model, PH_COPY | PH_SEPARATE);
					ZEPHIR_CALL_METHOD(NULL, &message, "setMetaData", NULL, 0, &_3$$5);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_4, 0, &message);
				zephir_check_call_status();
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _0$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_6$$3 = 1;
			while (1) {
				if (_6$$3) {
					_6$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _0$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_5$$3, _0$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_5$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&message, _0$$3, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&message) == IS_OBJECT) {
						ZEPHIR_INIT_NVAR(&_7$$7);
						zephir_create_array(&_7$$7, 1, 0);
						zephir_array_update_string(&_7$$7, SL("model"), model, PH_COPY | PH_SEPARATE);
						ZEPHIR_CALL_METHOD(NULL, &message, "setMetaData", NULL, 0, &_7$$7);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendMessage", &_4, 0, &message);
					zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&message);
	}
	ZEPHIR_MM_RESTORE();
}

zend_object *zephir_init_properties_Phalcon_Mvc_Model(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _12, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("uniqueTypes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("uniqueTypes"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("uniqueParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("uniqueParams"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("snapshot"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("snapshot"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("oldSnapshot"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("oldSnapshot"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("related"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("related"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("errorMessages"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("errorMessages"), &_11$$8);
		}
		zephir_read_property_ex(&_12, this_ptr, ZEND_STRL("dirtyRelated"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("dirtyRelated"), &_13$$9);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

