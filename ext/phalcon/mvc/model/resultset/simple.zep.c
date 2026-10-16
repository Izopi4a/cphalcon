
#ifdef HAVE_CONFIG_H
#include "../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../php_ext.h"
#include "../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/exception.h"
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
 * Phalcon\Mvc\Model\Resultset\Simple
 *
 * Simple resultsets only contains a complete objects
 * This class builds every complete object as it is required
 *
 * @template TKey of int
 * @template TValue of \Phalcon\Mvc\ModelInterface
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Resultset_Simple)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc\\Model\\Resultset, Simple, phalcon, mvc_model_resultset_simple, phalcon_mvc_model_resultset_ce, phalcon_mvc_model_resultset_simple_method_entry, 0);

	/**
	 * @var array|string
	 */
	zend_declare_property_null(phalcon_mvc_model_resultset_simple_ce, SL("columnMap"), ZEND_ACC_PROTECTED);
	/**
	 * @var ModelInterface|Row
	 */
	zend_declare_property_null(phalcon_mvc_model_resultset_simple_ce, SL("model"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_resultset_simple_ce, SL("keepSnapshots"), 0, ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Resultset\Simple constructor
 *
 * @param array                             columnMap
 * @param ModelInterface|Row                model
 * @param \Phalcon\Db\ResultInterface|false result
 * @param mixed|null                        cache
 * @param bool keepSnapshots                false
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool keepSnapshots;
	zval *columnMap, columnMap_sub, *model, model_sub, *result, result_sub, *cache = NULL, cache_sub, *keepSnapshots_param = NULL, __$true, __$false, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&columnMap_sub);
	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&result_sub);
	ZVAL_UNDEF(&cache_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("columnMap", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("keepSnapshots", 13, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 5)
		Z_PARAM_ZVAL(columnMap)
		Z_PARAM_ZVAL(model)
		Z_PARAM_ZVAL(result)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(cache)
		Z_PARAM_BOOL(keepSnapshots)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 2, &columnMap, &model, &result, &cache, &keepSnapshots_param);
	if (!cache) {
		cache = &cache_sub;
		cache = &__$null;
	}
	if (!keepSnapshots_param) {
		keepSnapshots = 0;
	} else {
		}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 828, model);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 829, columnMap);
	if (keepSnapshots) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 830, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 830, &__$false);
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_mvc_model_resultset_simple_ce, getThis(), "__construct", NULL, 0, result, cache);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns current row in the resultset
 * @return TValue
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, current)
{
	zend_class_entry *_8$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval __$true, __$false, row, hydrateMode, columnMap, activeRow, modelName, _0, _1$$5, _2$$5, _3$$6, _5$$6, _6$$6, _7$$6, _4$$7, _9$$9, _10$$9, _11$$9;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&hydrateMode);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&activeRow);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$9);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("activeRow", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("row", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("hydrateMode", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("columnMap", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("keepSnapshots", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 831, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&activeRow, &_0);
	if (Z_TYPE_P(&activeRow) != IS_NULL) {
		RETURN_CCTOR(&activeRow);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 832, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&row, &_0);
	if (Z_TYPE_P(&row) != IS_ARRAY) {
		if (0) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 831, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 831, &__$false);
		}
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 833, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&hydrateMode, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 829, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&columnMap, &_0);
	if (ZEPHIR_IS_LONG(&hydrateMode, 0)) { goto zephir_switch_0_clause_0; }
	goto zephir_switch_0_clause_1;
	zephir_switch_0_clause_0: ;
		ZEPHIR_INIT_VAR(&_2$$5);
		ZVAL_STRING(&_2$$5, "orm.late_state_binding");
		ZEPHIR_CALL_CE_STATIC(&_1$$5, phalcon_support_settings_ce, "get", NULL, 0, &_2$$5);
		zephir_check_call_status();
		if (zephir_is_true(&_1$$5)) {
			zephir_memory_observe(&_3$$6);
			zephir_read_property_cached(&_3$$6, this_ptr, _zephir_prop_4, 828, PH_NOISY_CC);
			if (zephir_instance_of_ev(&_3$$6, phalcon_mvc_model_ce)) {
				zephir_read_property_cached(&_4$$7, this_ptr, _zephir_prop_4, 828, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&modelName);
				zephir_get_class(&modelName, &_4$$7, 0);
			} else {
				ZEPHIR_INIT_NVAR(&modelName);
				ZVAL_STRING(&modelName, "Phalcon\\Mvc\\Model");
			}
			zephir_read_property_cached(&_5$$6, this_ptr, _zephir_prop_4, 828, PH_NOISY_CC | PH_READONLY);
			zephir_read_property_cached(&_6$$6, this_ptr, _zephir_prop_5, 830, PH_NOISY_CC | PH_READONLY);
			ZVAL_LONG(&_7$$6, 0);
			_8$$6 = zephir_fetch_class(&modelName);
			ZEPHIR_CALL_CE_STATIC(&activeRow, _8$$6, "cloneResultMap", NULL, 0, &_5$$6, &row, &columnMap, &_7$$6, &_6$$6);
			zephir_check_call_status();
		} else {
			zephir_read_property_cached(&_9$$9, this_ptr, _zephir_prop_4, 828, PH_NOISY_CC | PH_READONLY);
			zephir_read_property_cached(&_10$$9, this_ptr, _zephir_prop_5, 830, PH_NOISY_CC | PH_READONLY);
			ZVAL_LONG(&_11$$9, 0);
			ZEPHIR_CALL_CE_STATIC(&activeRow, phalcon_mvc_model_ce, "cloneResultMap", NULL, 0, &_9$$9, &row, &columnMap, &_11$$9, &_10$$9);
			zephir_check_call_status();
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
		ZEPHIR_CALL_CE_STATIC(&activeRow, phalcon_mvc_model_ce, "cloneResultMapHydrate", NULL, 0, &row, &columnMap, &hydrateMode);
		zephir_check_call_status();
		goto zephir_switch_0_end;
	zephir_switch_0_end: ;

	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 831, &activeRow);
	RETURN_CCTOR(&activeRow);
}

/**
 * Returns a complete resultset as an array, if the resultset has a big
 * number of rows it could consume more memory than currently it does.
 * Export the resultset to an array couldn't be faster with a large number
 * of records
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, toArray)
{
	zend_string *_11$$8, *_29$$19;
	zend_ulong _10$$8, _28$$19;
	zval renamedRecords, renamed;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_14 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *renameColumns_param = NULL, __$null, result, records, record, renamedKey, key, value, columnMap, _2, _0$$3, _3$$5, *_4$$7, _5$$7, *_6$$7, _23$$7, *_7$$8, _8$$8, *_9$$8, _17$$8, _12$$11, _13$$11, _15$$13, _16$$13, _19$$16, _20$$16, _21$$18, _22$$18, *_25$$19, _26$$19, *_27$$19, _34$$19, _30$$22, _31$$22, _32$$24, _33$$24, _36$$27, _37$$27, _38$$29, _39$$29;
	zend_bool renameColumns, _1, _24$$7, _18$$8, _35$$19;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&records);
	ZVAL_UNDEF(&record);
	ZVAL_UNDEF(&renamedKey);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_15$$13);
	ZVAL_UNDEF(&_16$$13);
	ZVAL_UNDEF(&_19$$16);
	ZVAL_UNDEF(&_20$$16);
	ZVAL_UNDEF(&_21$$18);
	ZVAL_UNDEF(&_22$$18);
	ZVAL_UNDEF(&_26$$19);
	ZVAL_UNDEF(&_34$$19);
	ZVAL_UNDEF(&_30$$22);
	ZVAL_UNDEF(&_31$$22);
	ZVAL_UNDEF(&_32$$24);
	ZVAL_UNDEF(&_33$$24);
	ZVAL_UNDEF(&_36$$27);
	ZVAL_UNDEF(&_37$$27);
	ZVAL_UNDEF(&_38$$29);
	ZVAL_UNDEF(&_39$$29);
	ZVAL_UNDEF(&renamedRecords);
	ZVAL_UNDEF(&renamed);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("rows", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("result", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("row", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("columnMap", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(renameColumns)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &renameColumns_param);
	if (!renameColumns_param) {
		renameColumns = 1;
	} else {
		}
	zephir_memory_observe(&records);
	zephir_read_property_cached(&records, this_ptr, _zephir_prop_0, 834, PH_NOISY_CC);
	if (Z_TYPE_P(&records) != IS_ARRAY) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_1, 835, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&result, &_0$$3);
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_2, 832, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0$$3) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, &result, "execute", NULL, 0);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&records, &result, "fetchAll", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 832, &__$null);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 834, &records);
	}
	_1 = renameColumns;
	if (_1) {
		zephir_memory_observe(&_2);
		zephir_read_property_cached(&_2, this_ptr, _zephir_prop_3, 828, PH_NOISY_CC);
		_1 = !((zephir_instance_of_ev(&_2, phalcon_mvc_model_row_ce)));
	}
	if (_1) {
		zephir_read_property_cached(&_3$$5, this_ptr, _zephir_prop_4, 829, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&columnMap, &_3$$5);
		if (Z_TYPE_P(&columnMap) != IS_ARRAY) {
			RETURN_CCTOR(&records);
		}
		ZEPHIR_INIT_VAR(&renamedRecords);
		array_init(&renamedRecords);
		if (Z_TYPE_P(&records) == IS_ARRAY) {
			if (Z_TYPE_P(&records) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_5$$7);
				zephir_string_to_char_array(&_5$$7, &records);
				_4$$7 = &_5$$7;
			} else {
				_4$$7 = &records;
			}
			zephir_is_iterable(_4$$7, 0, "phalcon/Mvc/Model/Resultset/Simple.zep", 247);
			if (Z_TYPE_P(_4$$7) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$7), _6$$7)
				{
					ZEPHIR_INIT_NVAR(&record);
					ZVAL_COPY(&record, _6$$7);
					ZEPHIR_INIT_NVAR(&renamed);
					array_init(&renamed);
					if (Z_TYPE_P(&record) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_8$$8);
						zephir_string_to_char_array(&_8$$8, &record);
						_7$$8 = &_8$$8;
					} else {
						_7$$8 = &record;
					}
					zephir_is_iterable(_7$$8, 0, "phalcon/Mvc/Model/Resultset/Simple.zep", 245);
					if (Z_TYPE_P(_7$$8) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7$$8), _10$$8, _11$$8, _9$$8)
						{
							ZEPHIR_INIT_NVAR(&key);
							if (_11$$8 != NULL) { 
								ZVAL_STR_COPY(&key, _11$$8);
							} else {
								ZVAL_LONG(&key, _10$$8);
							}
							ZEPHIR_INIT_NVAR(&value);
							ZVAL_COPY(&value, _9$$8);
							if (Z_TYPE_P(&key) == IS_STRING) {
								ZEPHIR_OBS_NVAR(&renamedKey);
								if (UNEXPECTED(!(zephir_array_isset_fetch(&renamedKey, &columnMap, &key, 0)))) {
									ZEPHIR_INIT_NVAR(&_12$$11);
									object_init_ex(&_12$$11, phalcon_mvc_model_exception_ce);
									ZEPHIR_INIT_NVAR(&_13$$11);
									ZEPHIR_CONCAT_SVS(&_13$$11, "Column '", &key, "' is not part of the column map");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									ZEPHIR_CALL_METHOD(NULL, &_12$$11, "__construct", &_14, 32, &_13$$11);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_12$$11, "phalcon/Mvc/Model/Resultset/Simple.zep", 227);
									ZEPHIR_MM_RESTORE();
									return;
								}
								if (Z_TYPE_P(&renamedKey) == IS_ARRAY) {
									ZEPHIR_OBS_NVAR(&renamedKey);
									if (UNEXPECTED(!(zephir_array_isset_long_fetch(&renamedKey, &renamedKey, 0, 0)))) {
										ZEPHIR_INIT_NVAR(&_15$$13);
										object_init_ex(&_15$$13, phalcon_mvc_model_exception_ce);
										ZEPHIR_INIT_NVAR(&_16$$13);
										ZEPHIR_CONCAT_SVS(&_16$$13, "Column '", &key, "' is not part of the column map");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										ZEPHIR_CALL_METHOD(NULL, &_15$$13, "__construct", &_14, 32, &_16$$13);
										zephir_check_call_status();
										zephir_throw_exception_debug(&_15$$13, "phalcon/Mvc/Model/Resultset/Simple.zep", 234);
										ZEPHIR_MM_RESTORE();
										return;
									}
								}
								zephir_array_update_zval(&renamed, &renamedKey, &value, PH_COPY | PH_SEPARATE);
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _7$$8, "rewind", NULL, 0);
						zephir_check_call_status();
						_18$$8 = 1;
						while (1) {
							if (_18$$8) {
								_18$$8 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _7$$8, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_17$$8, _7$$8, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_17$$8)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&key, _7$$8, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&value, _7$$8, "current", NULL, 0);
							zephir_check_call_status();
								if (Z_TYPE_P(&key) == IS_STRING) {
									ZEPHIR_OBS_NVAR(&renamedKey);
									if (UNEXPECTED(!(zephir_array_isset_fetch(&renamedKey, &columnMap, &key, 0)))) {
										ZEPHIR_INIT_NVAR(&_19$$16);
										object_init_ex(&_19$$16, phalcon_mvc_model_exception_ce);
										ZEPHIR_INIT_NVAR(&_20$$16);
										ZEPHIR_CONCAT_SVS(&_20$$16, "Column '", &key, "' is not part of the column map");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										ZEPHIR_CALL_METHOD(NULL, &_19$$16, "__construct", &_14, 32, &_20$$16);
										zephir_check_call_status();
										zephir_throw_exception_debug(&_19$$16, "phalcon/Mvc/Model/Resultset/Simple.zep", 227);
										ZEPHIR_MM_RESTORE();
										return;
									}
									if (Z_TYPE_P(&renamedKey) == IS_ARRAY) {
										ZEPHIR_OBS_NVAR(&renamedKey);
										if (UNEXPECTED(!(zephir_array_isset_long_fetch(&renamedKey, &renamedKey, 0, 0)))) {
											ZEPHIR_INIT_NVAR(&_21$$18);
											object_init_ex(&_21$$18, phalcon_mvc_model_exception_ce);
											ZEPHIR_INIT_NVAR(&_22$$18);
											ZEPHIR_CONCAT_SVS(&_22$$18, "Column '", &key, "' is not part of the column map");
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											ZEPHIR_CALL_METHOD(NULL, &_21$$18, "__construct", &_14, 32, &_22$$18);
											zephir_check_call_status();
											zephir_throw_exception_debug(&_21$$18, "phalcon/Mvc/Model/Resultset/Simple.zep", 234);
											ZEPHIR_MM_RESTORE();
											return;
										}
									}
									zephir_array_update_zval(&renamed, &renamedKey, &value, PH_COPY | PH_SEPARATE);
								}
						}
					}
					ZEPHIR_INIT_NVAR(&value);
					ZEPHIR_INIT_NVAR(&key);
					zephir_array_append(&renamedRecords, &renamed, PH_SEPARATE, "phalcon/Mvc/Model/Resultset/Simple.zep", 245);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$7, "rewind", NULL, 0);
				zephir_check_call_status();
				_24$$7 = 1;
				while (1) {
					if (_24$$7) {
						_24$$7 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_23$$7, _4$$7, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_23$$7)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&record, _4$$7, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&renamed);
						array_init(&renamed);
						if (Z_TYPE_P(&record) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_26$$19);
							zephir_string_to_char_array(&_26$$19, &record);
							_25$$19 = &_26$$19;
						} else {
							_25$$19 = &record;
						}
						zephir_is_iterable(_25$$19, 0, "phalcon/Mvc/Model/Resultset/Simple.zep", 245);
						if (Z_TYPE_P(_25$$19) == IS_ARRAY) {
							ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_25$$19), _28$$19, _29$$19, _27$$19)
							{
								ZEPHIR_INIT_NVAR(&key);
								if (_29$$19 != NULL) { 
									ZVAL_STR_COPY(&key, _29$$19);
								} else {
									ZVAL_LONG(&key, _28$$19);
								}
								ZEPHIR_INIT_NVAR(&value);
								ZVAL_COPY(&value, _27$$19);
								if (Z_TYPE_P(&key) == IS_STRING) {
									ZEPHIR_OBS_NVAR(&renamedKey);
									if (UNEXPECTED(!(zephir_array_isset_fetch(&renamedKey, &columnMap, &key, 0)))) {
										ZEPHIR_INIT_NVAR(&_30$$22);
										object_init_ex(&_30$$22, phalcon_mvc_model_exception_ce);
										ZEPHIR_INIT_NVAR(&_31$$22);
										ZEPHIR_CONCAT_SVS(&_31$$22, "Column '", &key, "' is not part of the column map");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										ZEPHIR_CALL_METHOD(NULL, &_30$$22, "__construct", &_14, 32, &_31$$22);
										zephir_check_call_status();
										zephir_throw_exception_debug(&_30$$22, "phalcon/Mvc/Model/Resultset/Simple.zep", 227);
										ZEPHIR_MM_RESTORE();
										return;
									}
									if (Z_TYPE_P(&renamedKey) == IS_ARRAY) {
										ZEPHIR_OBS_NVAR(&renamedKey);
										if (UNEXPECTED(!(zephir_array_isset_long_fetch(&renamedKey, &renamedKey, 0, 0)))) {
											ZEPHIR_INIT_NVAR(&_32$$24);
											object_init_ex(&_32$$24, phalcon_mvc_model_exception_ce);
											ZEPHIR_INIT_NVAR(&_33$$24);
											ZEPHIR_CONCAT_SVS(&_33$$24, "Column '", &key, "' is not part of the column map");
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											ZEPHIR_CALL_METHOD(NULL, &_32$$24, "__construct", &_14, 32, &_33$$24);
											zephir_check_call_status();
											zephir_throw_exception_debug(&_32$$24, "phalcon/Mvc/Model/Resultset/Simple.zep", 234);
											ZEPHIR_MM_RESTORE();
											return;
										}
									}
									zephir_array_update_zval(&renamed, &renamedKey, &value, PH_COPY | PH_SEPARATE);
								}
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$19, "rewind", NULL, 0);
							zephir_check_call_status();
							_35$$19 = 1;
							while (1) {
								if (_35$$19) {
									_35$$19 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _25$$19, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_34$$19, _25$$19, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_34$$19)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&key, _25$$19, "key", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&value, _25$$19, "current", NULL, 0);
								zephir_check_call_status();
									if (Z_TYPE_P(&key) == IS_STRING) {
										ZEPHIR_OBS_NVAR(&renamedKey);
										if (UNEXPECTED(!(zephir_array_isset_fetch(&renamedKey, &columnMap, &key, 0)))) {
											ZEPHIR_INIT_NVAR(&_36$$27);
											object_init_ex(&_36$$27, phalcon_mvc_model_exception_ce);
											ZEPHIR_INIT_NVAR(&_37$$27);
											ZEPHIR_CONCAT_SVS(&_37$$27, "Column '", &key, "' is not part of the column map");
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											ZEPHIR_CALL_METHOD(NULL, &_36$$27, "__construct", &_14, 32, &_37$$27);
											zephir_check_call_status();
											zephir_throw_exception_debug(&_36$$27, "phalcon/Mvc/Model/Resultset/Simple.zep", 227);
											ZEPHIR_MM_RESTORE();
											return;
										}
										if (Z_TYPE_P(&renamedKey) == IS_ARRAY) {
											ZEPHIR_OBS_NVAR(&renamedKey);
											if (UNEXPECTED(!(zephir_array_isset_long_fetch(&renamedKey, &renamedKey, 0, 0)))) {
												ZEPHIR_INIT_NVAR(&_38$$29);
												object_init_ex(&_38$$29, phalcon_mvc_model_exception_ce);
												ZEPHIR_INIT_NVAR(&_39$$29);
												ZEPHIR_CONCAT_SVS(&_39$$29, "Column '", &key, "' is not part of the column map");
												if (UNEXPECTED(EG(exception))) {
													ZEPHIR_MM_RESTORE();
													return;
												}
												ZEPHIR_CALL_METHOD(NULL, &_38$$29, "__construct", &_14, 32, &_39$$29);
												zephir_check_call_status();
												zephir_throw_exception_debug(&_38$$29, "phalcon/Mvc/Model/Resultset/Simple.zep", 234);
												ZEPHIR_MM_RESTORE();
												return;
											}
										}
										zephir_array_update_zval(&renamed, &renamedKey, &value, PH_COPY | PH_SEPARATE);
									}
							}
						}
						ZEPHIR_INIT_NVAR(&value);
						ZEPHIR_INIT_NVAR(&key);
						zephir_array_append(&renamedRecords, &renamed, PH_SEPARATE, "phalcon/Mvc/Model/Resultset/Simple.zep", 245);
				}
			}
			ZEPHIR_INIT_NVAR(&record);
		}
		RETURN_CTOR(&renamedRecords);
	}
	RETURN_CCTOR(&records);
}

/**
 * Serializing a resultset will dump all related rows into a big array
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, serialize)
{
	zval data;
	zval container, serializer, _0, _1, _2, _3, _4$$4, _5$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&serializer);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&data);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("columnMap", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("hydrateMode", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("keepSnapshots", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The dependency injector container is not valid", "phalcon/Mvc/Model/Resultset/Simple.zep", 267);
		return;
	}
	ZEPHIR_INIT_VAR(&data);
	zephir_create_array(&data, 6, 0);
	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 828, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("model"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 836, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("cache"), &_0, PH_COPY | PH_SEPARATE);
	ZVAL_BOOL(&_2, 0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "toArray", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_array_update_string(&data, SL("rows"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 829, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("columnMap"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 833, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("hydrateMode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 830, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("keepSnapshots"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "serializer");
	ZEPHIR_CALL_METHOD(&_1, &container, "has", NULL, 0, &_3);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		ZVAL_STRING(&_5$$4, "serializer");
		ZEPHIR_CALL_METHOD(&_4$$4, &container, "getShared", NULL, 0, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&serializer, &_4$$4);
		ZEPHIR_CALL_METHOD(NULL, &serializer, "setData", NULL, 0, &data);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_METHOD(&serializer, "serialize", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_FUNCTION("serialize", NULL, 14, &data);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Unserializing a resultset will allow to only works on the rows present in
 * the saved state
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, unserialize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data, data_sub, resultset, keepSnapshots, container, serializer, _0, _1, _4, _5, _6, _7, _8, _9, _10, _2$$4, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&resultset);
	ZVAL_UNDEF(&keepSnapshots);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&serializer);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("rows", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("count", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("columnMap", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("hydrateMode", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("keepSnapshots", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data);
	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The dependency injector container is not valid", "phalcon/Mvc/Model/Resultset/Simple.zep", 304);
		return;
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "serializer");
	ZEPHIR_CALL_METHOD(&_0, &container, "has", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "serializer");
		ZEPHIR_CALL_METHOD(&_2$$4, &container, "getShared", NULL, 0, &_3$$4);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&serializer, &_2$$4);
		ZEPHIR_CALL_METHOD(NULL, &serializer, "unserialize", NULL, 0, data);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&resultset, &serializer, "getData", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_FUNCTION(&resultset, "unserialize", NULL, 15, data);
		zephir_check_call_status();
	}
	if (UNEXPECTED(Z_TYPE_P(&resultset) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Invalid serialization data", "phalcon/Mvc/Model/Resultset/Simple.zep", 317);
		return;
	}
	zephir_memory_observe(&_4);
	zephir_array_fetch_string(&_4, &resultset, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Simple.zep", 320);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 828, &_4);
	zephir_memory_observe(&_5);
	zephir_array_fetch_string(&_5, &resultset, SL("rows"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Simple.zep", 321);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 834, &_5);
	zephir_memory_observe(&_6);
	zephir_array_fetch_string(&_6, &resultset, SL("rows"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Simple.zep", 322);
	ZVAL_UNDEF(&_7);
	ZVAL_LONG(&_7, zephir_fast_count_int(&_6));
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 837, &_7);
	zephir_memory_observe(&_8);
	zephir_array_fetch_string(&_8, &resultset, SL("cache"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Simple.zep", 323);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 836, &_8);
	zephir_memory_observe(&_9);
	zephir_array_fetch_string(&_9, &resultset, SL("columnMap"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Simple.zep", 324);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 829, &_9);
	zephir_memory_observe(&_10);
	zephir_array_fetch_string(&_10, &resultset, SL("hydrateMode"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Simple.zep", 325);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 833, &_10);
	zephir_memory_observe(&keepSnapshots);
	if (zephir_array_isset_string_fetch(&keepSnapshots, &resultset, SL("keepSnapshots"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 830, &keepSnapshots);
	}
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, __serialize)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("columnMap", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("hydrateMode", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("keepSnapshots", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 6, 0);
	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 828, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("model"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 836, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cache"), &_0, PH_COPY | PH_SEPARATE);
	ZVAL_BOOL(&_2, 0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "toArray", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("rows"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 829, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("columnMap"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 833, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("hydrateMode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 830, PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("keepSnapshots"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Phalcon_Mvc_Model_Resultset_Simple, __unserialize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *data_param = NULL, keepSnapshots, _0, _1, _2, _3, _4, _5, _6;
	zval data;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&keepSnapshots);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("model", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("rows", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("count", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("columnMap", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("hydrateMode", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("keepSnapshots", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data_param);
	zephir_get_arrval(&data, data_param);
	zephir_array_fetch_string(&_0, &data, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Simple.zep", 348);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 828, &_0);
	zephir_array_fetch_string(&_1, &data, SL("rows"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Simple.zep", 349);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 834, &_1);
	zephir_array_fetch_string(&_2, &data, SL("rows"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Simple.zep", 350);
	ZVAL_UNDEF(&_3);
	ZVAL_LONG(&_3, zephir_fast_count_int(&_2));
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 837, &_3);
	zephir_array_fetch_string(&_4, &data, SL("cache"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Simple.zep", 351);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 836, &_4);
	zephir_array_fetch_string(&_5, &data, SL("columnMap"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Simple.zep", 352);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 829, &_5);
	zephir_array_fetch_string(&_6, &data, SL("hydrateMode"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Simple.zep", 353);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 833, &_6);
	zephir_memory_observe(&keepSnapshots);
	if (zephir_array_isset_string_fetch(&keepSnapshots, &data, SL("keepSnapshots"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 830, &keepSnapshots);
	}
	ZEPHIR_MM_RESTORE();
}

