
#ifdef HAVE_CONFIG_H
#include "../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../php_ext.h"
#include "../../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/concat.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Model\MetaData\Strategy\Introspection
 *
 * Queries the table meta-data in order to introspect the model's metadata
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_MetaData_Strategy_Introspection)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\Model\\MetaData\\Strategy, Introspection, phalcon, mvc_model_metadata_strategy_introspection, phalcon_mvc_model_metadata_strategy_introspection_method_entry, 0);

	zend_class_implements(phalcon_mvc_model_metadata_strategy_introspection_ce, 1, phalcon_mvc_model_metadata_strategy_strategyinterface_ce);
	return SUCCESS;
}

/**
 * Read the model's column map, this can't be inferred
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData_Strategy_Introspection, getColumnMaps)
{
	zend_bool _6$$3;
	zend_string *_4$$3;
	zend_ulong _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *model, model_sub, *container, container_sub, orderedColumnMap, userColumnMap, reversedColumnMap, name, userName, *_0$$3, _1$$3, *_2$$3, _5$$3;

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&orderedColumnMap);
	ZVAL_UNDEF(&userColumnMap);
	ZVAL_UNDEF(&reversedColumnMap);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&userName);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &model, &container);
	ZEPHIR_INIT_VAR(&orderedColumnMap);
	ZVAL_NULL(&orderedColumnMap);
	ZEPHIR_INIT_VAR(&reversedColumnMap);
	ZVAL_NULL(&reversedColumnMap);
	if ((zephir_method_exists_ex(model, ZEND_STRL("columnmap")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(&userColumnMap, model, "columnMap", NULL, 0);
		zephir_check_call_status();
		if (UNEXPECTED(Z_TYPE_P(&userColumnMap) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "columnMap() not returned an array", "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 44);
			return;
		}
		ZEPHIR_INIT_NVAR(&reversedColumnMap);
		array_init(&reversedColumnMap);
		ZEPHIR_CPY_WRT(&orderedColumnMap, &userColumnMap);
		if (Z_TYPE_P(&userColumnMap) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_string_to_char_array(&_1$$3, &userColumnMap);
			_0$$3 = &_1$$3;
		} else {
			_0$$3 = &userColumnMap;
		}
		zephir_is_iterable(_0$$3, 0, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 53);
		if (Z_TYPE_P(_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_0$$3), _3$$3, _4$$3, _2$$3)
			{
				ZEPHIR_INIT_NVAR(&name);
				if (_4$$3 != NULL) { 
					ZVAL_STR_COPY(&name, _4$$3);
				} else {
					ZVAL_LONG(&name, _3$$3);
				}
				ZEPHIR_INIT_NVAR(&userName);
				ZVAL_COPY(&userName, _2$$3);
				zephir_array_update_zval(&reversedColumnMap, &userName, &name, PH_COPY | PH_SEPARATE);
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
				ZEPHIR_CALL_METHOD(&name, _0$$3, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&userName, _0$$3, "current", NULL, 0);
				zephir_check_call_status();
					zephir_array_update_zval(&reversedColumnMap, &userName, &name, PH_COPY | PH_SEPARATE);
			}
		}
		ZEPHIR_INIT_NVAR(&userName);
		ZEPHIR_INIT_NVAR(&name);
	}
	zephir_create_array(return_value, 2, 0);
	zephir_array_fast_append(return_value, &orderedColumnMap);
	zephir_array_fast_append(return_value, &reversedColumnMap);
	RETURN_MM();
}

/**
 * The meta-data is obtained by reading the column descriptions from the database information schema
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData_Strategy_Introspection, getMetaData)
{
	zend_bool _22, _18$$9, _29$$17;
	zval completeTable;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *model, model_sub, *container, container_sub, __$true, schema, table, readConnection, columns, attributes, primaryKeys, nonPrimaryKeys, numericTyped, notNull, fieldTypes, automaticDefault, identityField, fieldBindTypes, defaultValues, column, fieldName, defaultValue, emptyStringValues, _0, *_9, _10, *_11, _21, _1$$4, _2$$3, _3$$3, _4$$3, _5$$7, _6$$6, _7$$6, _8$$6, _12$$9, _13$$9, _14$$9, _15$$9, _16$$9, _17$$9, _19$$9, _20$$15, _23$$17, _24$$17, _25$$17, _26$$17, _27$$17, _28$$17, _30$$17, _31$$23;

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&readConnection);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&nonPrimaryKeys);
	ZVAL_UNDEF(&numericTyped);
	ZVAL_UNDEF(&notNull);
	ZVAL_UNDEF(&fieldTypes);
	ZVAL_UNDEF(&automaticDefault);
	ZVAL_UNDEF(&identityField);
	ZVAL_UNDEF(&fieldBindTypes);
	ZVAL_UNDEF(&defaultValues);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&fieldName);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&emptyStringValues);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$15);
	ZVAL_UNDEF(&_23$$17);
	ZVAL_UNDEF(&_24$$17);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_30$$17);
	ZVAL_UNDEF(&_31$$23);
	ZVAL_UNDEF(&completeTable);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &model, &container);
	ZEPHIR_CALL_METHOD(&schema, model, "getSchema", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&table, model, "getSource", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&readConnection, model, "getReadConnection", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &readConnection, "tableExists", NULL, 0, &table, &schema);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		if (zephir_is_true(&schema)) {
			ZEPHIR_INIT_VAR(&_1$$4);
			ZEPHIR_CONCAT_VSV(&_1$$4, &schema, "'.'", &table);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&completeTable, &_1$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_get_strval(&completeTable, &table);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_get_class(&_3$$3, model, 0);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SVSV(&_4$$3, "Table '", &completeTable, "' does not exist in database when dumping meta-data for ", &_3$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 32, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 92);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&columns, &readConnection, "describeColumns", NULL, 0, &table, &schema);
	zephir_check_call_status();
	if (UNEXPECTED(!(zephir_fast_count_int(&columns)))) {
		if (zephir_is_true(&schema)) {
			ZEPHIR_INIT_VAR(&_5$$7);
			ZEPHIR_CONCAT_VSV(&_5$$7, &schema, "'.'", &table);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&completeTable, &_5$$7);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_get_strval(&completeTable, &table);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_INIT_VAR(&_6$$6);
		object_init_ex(&_6$$6, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_7$$6);
		zephir_get_class(&_7$$6, model, 0);
		ZEPHIR_INIT_VAR(&_8$$6);
		ZEPHIR_CONCAT_SVSV(&_8$$6, "Cannot obtain table columns for the mapped source '", &completeTable, "' used in model ", &_7$$6);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_6$$6, "__construct", NULL, 32, &_8$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$6, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 112);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&attributes);
	array_init(&attributes);
	ZEPHIR_INIT_VAR(&primaryKeys);
	array_init(&primaryKeys);
	ZEPHIR_INIT_VAR(&nonPrimaryKeys);
	array_init(&nonPrimaryKeys);
	ZEPHIR_INIT_VAR(&numericTyped);
	array_init(&numericTyped);
	ZEPHIR_INIT_VAR(&notNull);
	array_init(&notNull);
	ZEPHIR_INIT_VAR(&fieldTypes);
	array_init(&fieldTypes);
	ZEPHIR_INIT_VAR(&fieldBindTypes);
	array_init(&fieldBindTypes);
	ZEPHIR_INIT_VAR(&automaticDefault);
	array_init(&automaticDefault);
	ZEPHIR_INIT_VAR(&identityField);
	ZVAL_BOOL(&identityField, 0);
	ZEPHIR_INIT_VAR(&defaultValues);
	array_init(&defaultValues);
	ZEPHIR_INIT_VAR(&emptyStringValues);
	array_init(&emptyStringValues);
	if (Z_TYPE_P(&columns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &columns);
		_9 = &_10;
	} else {
		_9 = &columns;
	}
	zephir_is_iterable(_9, 0, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 189);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _11);
			ZEPHIR_CALL_METHOD(&fieldName, &column, "getName", NULL, 0);
			zephir_check_call_status();
			zephir_array_append(&attributes, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 132);
			ZEPHIR_CALL_METHOD(&_12$$9, &column, "isPrimary", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_12$$9)) {
				zephir_array_append(&primaryKeys, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 138);
			} else {
				zephir_array_append(&nonPrimaryKeys, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 140);
			}
			ZEPHIR_CALL_METHOD(&_13$$9, &column, "isNumeric", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_13$$9)) {
				zephir_array_update_zval(&numericTyped, &fieldName, &__$true, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_CALL_METHOD(&_14$$9, &column, "isNotNull", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_14$$9)) {
				zephir_array_append(&notNull, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 154);
			}
			ZEPHIR_CALL_METHOD(&_15$$9, &column, "isAutoIncrement", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_15$$9)) {
				ZEPHIR_CPY_WRT(&identityField, &fieldName);
			}
			ZEPHIR_CALL_METHOD(&_16$$9, &column, "getType", NULL, 0);
			zephir_check_call_status();
			zephir_array_update_zval(&fieldTypes, &fieldName, &_16$$9, PH_COPY | PH_SEPARATE);
			ZEPHIR_CALL_METHOD(&_17$$9, &column, "getBindType", NULL, 0);
			zephir_check_call_status();
			zephir_array_update_zval(&fieldBindTypes, &fieldName, &_17$$9, PH_COPY | PH_SEPARATE);
			ZEPHIR_CALL_METHOD(&defaultValue, &column, "getDefault", NULL, 0);
			zephir_check_call_status();
			_18$$9 = Z_TYPE_P(&defaultValue) != IS_NULL;
			if (!(_18$$9)) {
				ZEPHIR_CALL_METHOD(&_19$$9, &column, "isNotNull", NULL, 0);
				zephir_check_call_status();
				_18$$9 = !zephir_is_true(&_19$$9);
			}
			if (_18$$9) {
				ZEPHIR_CALL_METHOD(&_20$$15, &column, "isAutoIncrement", NULL, 0);
				zephir_check_call_status();
				if (!(zephir_is_true(&_20$$15))) {
					zephir_array_update_zval(&defaultValues, &fieldName, &defaultValue, PH_COPY | PH_SEPARATE);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_22 = 1;
		while (1) {
			if (_22) {
				_22 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_21, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_21)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&column, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&fieldName, &column, "getName", NULL, 0);
				zephir_check_call_status();
				zephir_array_append(&attributes, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 132);
				ZEPHIR_CALL_METHOD(&_23$$17, &column, "isPrimary", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_23$$17)) {
					zephir_array_append(&primaryKeys, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 138);
				} else {
					zephir_array_append(&nonPrimaryKeys, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 140);
				}
				ZEPHIR_CALL_METHOD(&_24$$17, &column, "isNumeric", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_24$$17)) {
					zephir_array_update_zval(&numericTyped, &fieldName, &__$true, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_CALL_METHOD(&_25$$17, &column, "isNotNull", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_25$$17)) {
					zephir_array_append(&notNull, &fieldName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Introspection.zep", 154);
				}
				ZEPHIR_CALL_METHOD(&_26$$17, &column, "isAutoIncrement", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_26$$17)) {
					ZEPHIR_CPY_WRT(&identityField, &fieldName);
				}
				ZEPHIR_CALL_METHOD(&_27$$17, &column, "getType", NULL, 0);
				zephir_check_call_status();
				zephir_array_update_zval(&fieldTypes, &fieldName, &_27$$17, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&_28$$17, &column, "getBindType", NULL, 0);
				zephir_check_call_status();
				zephir_array_update_zval(&fieldBindTypes, &fieldName, &_28$$17, PH_COPY | PH_SEPARATE);
				ZEPHIR_CALL_METHOD(&defaultValue, &column, "getDefault", NULL, 0);
				zephir_check_call_status();
				_29$$17 = Z_TYPE_P(&defaultValue) != IS_NULL;
				if (!(_29$$17)) {
					ZEPHIR_CALL_METHOD(&_30$$17, &column, "isNotNull", NULL, 0);
					zephir_check_call_status();
					_29$$17 = !zephir_is_true(&_30$$17);
				}
				if (_29$$17) {
					ZEPHIR_CALL_METHOD(&_31$$23, &column, "isAutoIncrement", NULL, 0);
					zephir_check_call_status();
					if (!(zephir_is_true(&_31$$23))) {
						zephir_array_update_zval(&defaultValues, &fieldName, &defaultValue, PH_COPY | PH_SEPARATE);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	zephir_create_array(return_value, 12, 0);
	zephir_array_update_long(return_value, 0, &attributes, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 1, &primaryKeys, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 2, &nonPrimaryKeys, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 3, &notNull, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 4, &fieldTypes, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 5, &numericTyped, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 8, &identityField, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 9, &fieldBindTypes, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 10, &automaticDefault, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 11, &automaticDefault, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 12, &defaultValues, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 13, &emptyStringValues, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	RETURN_MM();
}

