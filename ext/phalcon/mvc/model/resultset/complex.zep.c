
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/exception.h"
#include "kernel/array.h"
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
 * Phalcon\Mvc\Model\Resultset\Complex
 *
 * Complex resultsets may include complete objects and scalar values.
 * This class builds every complex row as it is required
 *
 * @template TKey of int
 * @template TValue of mixed
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Resultset_Complex)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc\\Model\\Resultset, Complex, phalcon, mvc_model_resultset_complex, phalcon_mvc_model_resultset_ce, phalcon_mvc_model_resultset_complex_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_resultset_complex_ce, SL("columnTypes"), ZEND_ACC_PROTECTED);
	/**
	 * Unserialised result-set hydrated all rows already. unserialise() sets
	 * disableHydration to true
	 *
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_resultset_complex_ce, SL("disableHydration"), 0, ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Resultset\Complex constructor
 *
 * @param array                $columnTypes
 * @param ResultInterface|null $result
 * @param mixed|null           $cache
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *columnTypes, columnTypes_sub, *result = NULL, result_sub, *cache = NULL, cache_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&columnTypes_sub);
	ZVAL_UNDEF(&result_sub);
	ZVAL_UNDEF(&cache_sub);
	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("columnTypes", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(columnTypes)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(result, phalcon_db_resultinterface_ce)
		Z_PARAM_ZVAL_OR_NULL(cache)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &columnTypes, &result, &cache);
	if (!result) {
		result = &result_sub;
		result = &__$null;
	}
	if (!cache) {
		cache = &cache_sub;
		cache = &__$null;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 806, columnTypes);
	ZEPHIR_CALL_PARENT(NULL, phalcon_mvc_model_resultset_complex_ce, getThis(), "__construct", NULL, 0, result, cache);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns current row in the resultset
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, current)
{
	zend_class_entry *_24$$20, *_49$$44;
	zend_string *_6;
	zend_ulong _5;
	zend_bool allNull = 0, _32, _12$$11, _38$$35;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_18 = NULL, *_25 = NULL, *_28 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, dirtyState = 0;
	zval __$true, __$false, row, hydrateMode, eager, alias, activeRow, type, column, columnValue, value, attribute, source, attributes, columnMap, rowModel, keepSnapshots, sqlAlias, modelName, _0, _1, *_2, _3, *_4, _31, *_7$$11, _8$$11, *_9$$11, _11$$11, *_14$$11, _15$$11, *_16$$11, _10$$12, _13$$13, _17$$18, _19$$18, _20$$20, _22$$20, _23$$20, _21$$21, _26$$23, _27$$23, _29$$29, _30$$29, *_33$$35, _34$$35, *_35$$35, _37$$35, *_40$$35, _41$$35, *_42$$35, _36$$36, _39$$37, _43$$42, _44$$42, _45$$44, _47$$44, _48$$44, _46$$45, _50$$47, _51$$47, _52$$53, _53$$53;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&hydrateMode);
	ZVAL_UNDEF(&eager);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&activeRow);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&columnValue);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&attribute);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&rowModel);
	ZVAL_UNDEF(&keepSnapshots);
	ZVAL_UNDEF(&sqlAlias);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_10$$12);
	ZVAL_UNDEF(&_13$$13);
	ZVAL_UNDEF(&_17$$18);
	ZVAL_UNDEF(&_19$$18);
	ZVAL_UNDEF(&_20$$20);
	ZVAL_UNDEF(&_22$$20);
	ZVAL_UNDEF(&_23$$20);
	ZVAL_UNDEF(&_21$$21);
	ZVAL_UNDEF(&_26$$23);
	ZVAL_UNDEF(&_27$$23);
	ZVAL_UNDEF(&_29$$29);
	ZVAL_UNDEF(&_30$$29);
	ZVAL_UNDEF(&_34$$35);
	ZVAL_UNDEF(&_37$$35);
	ZVAL_UNDEF(&_41$$35);
	ZVAL_UNDEF(&_36$$36);
	ZVAL_UNDEF(&_39$$37);
	ZVAL_UNDEF(&_43$$42);
	ZVAL_UNDEF(&_44$$42);
	ZVAL_UNDEF(&_45$$44);
	ZVAL_UNDEF(&_47$$44);
	ZVAL_UNDEF(&_48$$44);
	ZVAL_UNDEF(&_46$$45);
	ZVAL_UNDEF(&_50$$47);
	ZVAL_UNDEF(&_51$$47);
	ZVAL_UNDEF(&_52$$53);
	ZVAL_UNDEF(&_53$$53);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("activeRow", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("row", 3, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("disableHydration", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("hydrateMode", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("columnTypes", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 807, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&activeRow, &_0);
	if (Z_TYPE_P(&activeRow) != IS_NULL) {
		RETURN_CCTOR(&activeRow);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 808, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&row, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 809, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 807, &row);
		RETURN_CCTOR(&row);
	}
	if (Z_TYPE_P(&row) != IS_ARRAY) {
		if (0) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 807, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 807, &__$false);
		}
		RETURN_MM_BOOL(0);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_3, 810, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&hydrateMode, &_1);
	if (ZEPHIR_IS_LONG(&hydrateMode, 0)) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_LONG(&hydrateMode, 1)) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_LONG(&hydrateMode, 2)) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_clause_3;
	zephir_switch_0_clause_0: ;
		ZEPHIR_INIT_NVAR(&activeRow);
		object_init_ex(&activeRow, phalcon_mvc_model_row_ce);
		if (zephir_has_constructor(&activeRow)) {
			ZEPHIR_CALL_METHOD(NULL, &activeRow, "__construct", NULL, 0);
			zephir_check_call_status();
		}

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
		ZEPHIR_INIT_NVAR(&activeRow);
		array_init(&activeRow);
		goto zephir_switch_0_end;
	zephir_switch_0_clause_2: ;
	zephir_switch_0_clause_3: ;
		ZEPHIR_INIT_NVAR(&activeRow);
		object_init(&activeRow);
		goto zephir_switch_0_end;
	zephir_switch_0_end: ;

	dirtyState = 0;
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_4, 806, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_1) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &_1);
		_2 = &_3;
	} else {
		_2 = &_1;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/Model/Resultset/Complex.zep", 279);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_2), _5, _6, _4)
		{
			ZEPHIR_INIT_NVAR(&alias);
			if (_6 != NULL) { 
				ZVAL_STR_COPY(&alias, _6);
			} else {
				ZVAL_LONG(&alias, _5);
			}
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _4);
			if (UNEXPECTED(Z_TYPE_P(&column) != IS_ARRAY)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Column type is corrupt", "phalcon/Mvc/Model/Resultset/Complex.zep", 143);
				return;
			}
			ZEPHIR_OBS_NVAR(&type);
			zephir_array_fetch_string(&type, &column, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 146);
			if (ZEPHIR_IS_STRING(&type, "object")) {
				ZEPHIR_OBS_NVAR(&source);
				zephir_array_fetch_string(&source, &column, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 152);
				ZEPHIR_OBS_NVAR(&attributes);
				zephir_array_fetch_string(&attributes, &column, SL("attributes"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 153);
				ZEPHIR_OBS_NVAR(&columnMap);
				zephir_array_fetch_string(&columnMap, &column, SL("columnMap"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 154);
				ZEPHIR_INIT_NVAR(&rowModel);
				array_init(&rowModel);
				if (Z_TYPE_P(&attributes) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_8$$11);
					zephir_string_to_char_array(&_8$$11, &attributes);
					_7$$11 = &_8$$11;
				} else {
					_7$$11 = &attributes;
				}
				zephir_is_iterable(_7$$11, 0, "phalcon/Mvc/Model/Resultset/Complex.zep", 172);
				if (Z_TYPE_P(_7$$11) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_7$$11), _9$$11)
					{
						ZEPHIR_INIT_NVAR(&attribute);
						ZVAL_COPY(&attribute, _9$$11);
						ZEPHIR_OBS_NVAR(&columnValue);
						ZEPHIR_INIT_NVAR(&_10$$12);
						ZEPHIR_CONCAT_SVSV(&_10$$12, "_", &source, "_", &attribute);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_fetch(&columnValue, &row, &_10$$12, PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 165);
						zephir_array_update_zval(&rowModel, &attribute, &columnValue, PH_COPY | PH_SEPARATE);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _7$$11, "rewind", NULL, 0);
					zephir_check_call_status();
					_12$$11 = 1;
					while (1) {
						if (_12$$11) {
							_12$$11 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _7$$11, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_11$$11, _7$$11, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_11$$11)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&attribute, _7$$11, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_OBS_NVAR(&columnValue);
							ZEPHIR_INIT_NVAR(&_13$$13);
							ZEPHIR_CONCAT_SVSV(&_13$$13, "_", &source, "_", &attribute);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_fetch(&columnValue, &row, &_13$$13, PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 165);
							zephir_array_update_zval(&rowModel, &attribute, &columnValue, PH_COPY | PH_SEPARATE);
					}
				}
				ZEPHIR_INIT_NVAR(&attribute);
				allNull = 1;
				if (Z_TYPE_P(&rowModel) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_15$$11);
					zephir_string_to_char_array(&_15$$11, &rowModel);
					_14$$11 = &_15$$11;
				} else {
					_14$$11 = &rowModel;
				}
				zephir_is_iterable(_14$$11, 0, "phalcon/Mvc/Model/Resultset/Complex.zep", 180);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_14$$11), _16$$11)
				{
					ZEPHIR_INIT_NVAR(&columnValue);
					ZVAL_COPY(&columnValue, _16$$11);
					if (Z_TYPE_P(&columnValue) != IS_NULL) {
						allNull = 0;
						break;
					}
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&columnValue);
				if (allNull) {
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_NULL(&value);
				} else {
					if (ZEPHIR_IS_LONG(&hydrateMode, 0)) { goto zephir_switch_1_clause_0; }
					goto zephir_switch_1_clause_1;
					zephir_switch_1_clause_0: ;
						ZEPHIR_OBS_NVAR(&keepSnapshots);
						if (!(zephir_array_isset_string_fetch(&keepSnapshots, &column, SL("keepSnapshots"), 0))) {
							ZEPHIR_INIT_NVAR(&keepSnapshots);
							ZVAL_BOOL(&keepSnapshots, 0);
						}
						ZEPHIR_INIT_NVAR(&_19$$18);
						ZVAL_STRING(&_19$$18, "orm.late_state_binding");
						ZEPHIR_CALL_CE_STATIC(&_17$$18, phalcon_support_settings_ce, "get", &_18, 0, &_19$$18);
						zephir_check_call_status();
						if (zephir_is_true(&_17$$18)) {
							ZEPHIR_OBS_NVAR(&_20$$20);
							zephir_array_fetch_string(&_20$$20, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 194);
							if (zephir_instance_of_ev(&_20$$20, phalcon_mvc_model_ce)) {
								ZEPHIR_OBS_NVAR(&_21$$21);
								zephir_array_fetch_string(&_21$$21, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 195);
								ZEPHIR_INIT_NVAR(&modelName);
								zephir_get_class(&modelName, &_21$$21, 0);
							} else {
								ZEPHIR_INIT_NVAR(&modelName);
								ZVAL_STRING(&modelName, "Phalcon\\Mvc\\Model");
							}
							ZEPHIR_OBS_NVAR(&_22$$20);
							zephir_array_fetch_string(&_22$$20, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 201);
							ZVAL_LONG(&_23$$20, dirtyState);
							_24$$20 = zephir_fetch_class(&modelName);
							ZEPHIR_CALL_CE_STATIC(&value, _24$$20, "cloneResultMap", NULL, 0, &_22$$20, &rowModel, &columnMap, &_23$$20, &keepSnapshots);
							zephir_check_call_status();
						} else {
							ZEPHIR_OBS_NVAR(&_26$$23);
							zephir_array_fetch_string(&_26$$23, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 213);
							ZVAL_LONG(&_27$$23, dirtyState);
							ZEPHIR_CALL_CE_STATIC(&value, phalcon_mvc_model_ce, "cloneResultMap", &_25, 0, &_26$$23, &rowModel, &columnMap, &_27$$23, &keepSnapshots);
							zephir_check_call_status();
						}
						goto zephir_switch_1_end;
					zephir_switch_1_clause_1: ;
						ZEPHIR_CALL_CE_STATIC(&value, phalcon_mvc_model_ce, "cloneResultMapHydrate", &_28, 0, &rowModel, &columnMap, &hydrateMode);
						zephir_check_call_status();
						goto zephir_switch_1_end;
					zephir_switch_1_end: ;

				}
				ZEPHIR_OBS_NVAR(&attribute);
				zephir_array_fetch_string(&attribute, &column, SL("balias"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 238);
			} else {
				ZEPHIR_OBS_NVAR(&sqlAlias);
				if (zephir_array_isset_string_fetch(&sqlAlias, &column, SL("sqlAlias"), 0)) {
					ZEPHIR_OBS_NVAR(&value);
					zephir_array_fetch(&value, &row, &sqlAlias, PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 244);
				} else {
					ZEPHIR_OBS_NVAR(&value);
					zephir_array_isset_fetch(&value, &row, &alias, 0);
				}
				if (zephir_array_isset_value_string(&column, SL("balias"))) {
					ZEPHIR_CPY_WRT(&attribute, &alias);
				} else {
					ZEPHIR_INIT_NVAR(&_29$$29);
					ZVAL_STRING(&_29$$29, "_");
					ZEPHIR_INIT_NVAR(&_30$$29);
					ZVAL_STRING(&_30$$29, "");
					ZEPHIR_INIT_NVAR(&attribute);
					zephir_fast_str_replace(&attribute, &_29$$29, &_30$$29, &alias);
				}
			}
			ZEPHIR_OBS_NVAR(&eager);
			if (!(zephir_array_isset_string_fetch(&eager, &column, SL("eager"), 0))) {
				if (ZEPHIR_IS_LONG(&hydrateMode, 1)) { goto zephir_switch_2_clause_0; }
				goto zephir_switch_2_clause_1;
				zephir_switch_2_clause_0: ;
					zephir_array_update_zval(&activeRow, &attribute, &value, PH_COPY | PH_SEPARATE);
					goto zephir_switch_2_end;
				zephir_switch_2_clause_1: ;
					zephir_update_property_zval_zval(&activeRow, &attribute, &value);
					goto zephir_switch_2_end;
				zephir_switch_2_end: ;

			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_32 = 1;
		while (1) {
			if (_32) {
				_32 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_31, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_31)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&alias, _2, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&column, _2, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&column) != IS_ARRAY)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Column type is corrupt", "phalcon/Mvc/Model/Resultset/Complex.zep", 143);
					return;
				}
				ZEPHIR_OBS_NVAR(&type);
				zephir_array_fetch_string(&type, &column, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 146);
				if (ZEPHIR_IS_STRING(&type, "object")) {
					ZEPHIR_OBS_NVAR(&source);
					zephir_array_fetch_string(&source, &column, SL("column"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 152);
					ZEPHIR_OBS_NVAR(&attributes);
					zephir_array_fetch_string(&attributes, &column, SL("attributes"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 153);
					ZEPHIR_OBS_NVAR(&columnMap);
					zephir_array_fetch_string(&columnMap, &column, SL("columnMap"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 154);
					ZEPHIR_INIT_NVAR(&rowModel);
					array_init(&rowModel);
					if (Z_TYPE_P(&attributes) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_34$$35);
						zephir_string_to_char_array(&_34$$35, &attributes);
						_33$$35 = &_34$$35;
					} else {
						_33$$35 = &attributes;
					}
					zephir_is_iterable(_33$$35, 0, "phalcon/Mvc/Model/Resultset/Complex.zep", 172);
					if (Z_TYPE_P(_33$$35) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_33$$35), _35$$35)
						{
							ZEPHIR_INIT_NVAR(&attribute);
							ZVAL_COPY(&attribute, _35$$35);
							ZEPHIR_OBS_NVAR(&columnValue);
							ZEPHIR_INIT_NVAR(&_36$$36);
							ZEPHIR_CONCAT_SVSV(&_36$$36, "_", &source, "_", &attribute);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_fetch(&columnValue, &row, &_36$$36, PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 165);
							zephir_array_update_zval(&rowModel, &attribute, &columnValue, PH_COPY | PH_SEPARATE);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _33$$35, "rewind", NULL, 0);
						zephir_check_call_status();
						_38$$35 = 1;
						while (1) {
							if (_38$$35) {
								_38$$35 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _33$$35, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_37$$35, _33$$35, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_37$$35)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&attribute, _33$$35, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_OBS_NVAR(&columnValue);
								ZEPHIR_INIT_NVAR(&_39$$37);
								ZEPHIR_CONCAT_SVSV(&_39$$37, "_", &source, "_", &attribute);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_fetch(&columnValue, &row, &_39$$37, PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 165);
								zephir_array_update_zval(&rowModel, &attribute, &columnValue, PH_COPY | PH_SEPARATE);
						}
					}
					ZEPHIR_INIT_NVAR(&attribute);
					allNull = 1;
					if (Z_TYPE_P(&rowModel) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_41$$35);
						zephir_string_to_char_array(&_41$$35, &rowModel);
						_40$$35 = &_41$$35;
					} else {
						_40$$35 = &rowModel;
					}
					zephir_is_iterable(_40$$35, 0, "phalcon/Mvc/Model/Resultset/Complex.zep", 180);
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_40$$35), _42$$35)
					{
						ZEPHIR_INIT_NVAR(&columnValue);
						ZVAL_COPY(&columnValue, _42$$35);
						if (Z_TYPE_P(&columnValue) != IS_NULL) {
							allNull = 0;
							break;
						}
					} ZEND_HASH_FOREACH_END();
					ZEPHIR_INIT_NVAR(&columnValue);
					if (allNull) {
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_NULL(&value);
					} else {
						if (ZEPHIR_IS_LONG(&hydrateMode, 0)) { goto zephir_switch_3_clause_0; }
						goto zephir_switch_3_clause_1;
						zephir_switch_3_clause_0: ;
							ZEPHIR_OBS_NVAR(&keepSnapshots);
							if (!(zephir_array_isset_string_fetch(&keepSnapshots, &column, SL("keepSnapshots"), 0))) {
								ZEPHIR_INIT_NVAR(&keepSnapshots);
								ZVAL_BOOL(&keepSnapshots, 0);
							}
							ZEPHIR_INIT_NVAR(&_44$$42);
							ZVAL_STRING(&_44$$42, "orm.late_state_binding");
							ZEPHIR_CALL_CE_STATIC(&_43$$42, phalcon_support_settings_ce, "get", &_18, 0, &_44$$42);
							zephir_check_call_status();
							if (zephir_is_true(&_43$$42)) {
								ZEPHIR_OBS_NVAR(&_45$$44);
								zephir_array_fetch_string(&_45$$44, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 194);
								if (zephir_instance_of_ev(&_45$$44, phalcon_mvc_model_ce)) {
									ZEPHIR_OBS_NVAR(&_46$$45);
									zephir_array_fetch_string(&_46$$45, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 195);
									ZEPHIR_INIT_NVAR(&modelName);
									zephir_get_class(&modelName, &_46$$45, 0);
								} else {
									ZEPHIR_INIT_NVAR(&modelName);
									ZVAL_STRING(&modelName, "Phalcon\\Mvc\\Model");
								}
								ZEPHIR_OBS_NVAR(&_47$$44);
								zephir_array_fetch_string(&_47$$44, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 201);
								ZVAL_LONG(&_48$$44, dirtyState);
								_49$$44 = zephir_fetch_class(&modelName);
								ZEPHIR_CALL_CE_STATIC(&value, _49$$44, "cloneResultMap", NULL, 0, &_47$$44, &rowModel, &columnMap, &_48$$44, &keepSnapshots);
								zephir_check_call_status();
							} else {
								ZEPHIR_OBS_NVAR(&_50$$47);
								zephir_array_fetch_string(&_50$$47, &column, SL("instance"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 213);
								ZVAL_LONG(&_51$$47, dirtyState);
								ZEPHIR_CALL_CE_STATIC(&value, phalcon_mvc_model_ce, "cloneResultMap", &_25, 0, &_50$$47, &rowModel, &columnMap, &_51$$47, &keepSnapshots);
								zephir_check_call_status();
							}
							goto zephir_switch_3_end;
						zephir_switch_3_clause_1: ;
							ZEPHIR_CALL_CE_STATIC(&value, phalcon_mvc_model_ce, "cloneResultMapHydrate", &_28, 0, &rowModel, &columnMap, &hydrateMode);
							zephir_check_call_status();
							goto zephir_switch_3_end;
						zephir_switch_3_end: ;

					}
					ZEPHIR_OBS_NVAR(&attribute);
					zephir_array_fetch_string(&attribute, &column, SL("balias"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 238);
				} else {
					ZEPHIR_OBS_NVAR(&sqlAlias);
					if (zephir_array_isset_string_fetch(&sqlAlias, &column, SL("sqlAlias"), 0)) {
						ZEPHIR_OBS_NVAR(&value);
						zephir_array_fetch(&value, &row, &sqlAlias, PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 244);
					} else {
						ZEPHIR_OBS_NVAR(&value);
						zephir_array_isset_fetch(&value, &row, &alias, 0);
					}
					if (zephir_array_isset_value_string(&column, SL("balias"))) {
						ZEPHIR_CPY_WRT(&attribute, &alias);
					} else {
						ZEPHIR_INIT_NVAR(&_52$$53);
						ZVAL_STRING(&_52$$53, "_");
						ZEPHIR_INIT_NVAR(&_53$$53);
						ZVAL_STRING(&_53$$53, "");
						ZEPHIR_INIT_NVAR(&attribute);
						zephir_fast_str_replace(&attribute, &_52$$53, &_53$$53, &alias);
					}
				}
				ZEPHIR_OBS_NVAR(&eager);
				if (!(zephir_array_isset_string_fetch(&eager, &column, SL("eager"), 0))) {
					if (ZEPHIR_IS_LONG(&hydrateMode, 1)) { goto zephir_switch_4_clause_0; }
					goto zephir_switch_4_clause_1;
					zephir_switch_4_clause_0: ;
						zephir_array_update_zval(&activeRow, &attribute, &value, PH_COPY | PH_SEPARATE);
						goto zephir_switch_4_end;
					zephir_switch_4_clause_1: ;
						zephir_update_property_zval_zval(&activeRow, &attribute, &value);
						goto zephir_switch_4_end;
					zephir_switch_4_end: ;

				}
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	ZEPHIR_INIT_NVAR(&alias);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 807, &activeRow);
	RETURN_CCTOR(&activeRow);
}

/**
 * Returns a complete resultset as an array, if the resultset has a big
 * number of rows it could consume more memory than currently it does.
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, toArray)
{
	zval records;
	zval current, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_1 = NULL, *_2 = NULL, *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&current);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&records);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&records);
	array_init(&records);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "rewind", NULL, 100);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "valid", &_1, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&_0))) {
			break;
		}
		ZEPHIR_CALL_METHOD(&current, this_ptr, "current", &_2, 0);
		zephir_check_call_status();
		zephir_array_append(&records, &current, PH_SEPARATE, "phalcon/Mvc/Model/Resultset/Complex.zep", 299);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "next", &_3, 0);
		zephir_check_call_status();
	}
	RETURN_CTOR(&records);
}

/**
 * Serializing a resultset will dump all related rows into a big array,
 * serialize it and return the resulting string
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, serialize)
{
	zval data;
	zval container, serializer, _0, _1, _2, _3$$4, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&serializer);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&data);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("columnTypes", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("hydrateMode", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The dependency injector container is not valid", "phalcon/Mvc/Model/Resultset/Complex.zep", 320);
		return;
	}
	ZEPHIR_INIT_VAR(&data);
	zephir_create_array(&data, 4, 0);
	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 811, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("cache"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "toArray", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&data, SL("rows"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 806, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("columnTypes"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 810, PH_NOISY_CC);
	zephir_array_update_string(&data, SL("hydrateMode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "serializer");
	ZEPHIR_CALL_METHOD(&_1, &container, "has", NULL, 0, &_2);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_INIT_VAR(&_4$$4);
		ZVAL_STRING(&_4$$4, "serializer");
		ZEPHIR_CALL_METHOD(&_3$$4, &container, "getShared", NULL, 0, &_4$$4);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&serializer, &_3$$4);
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
 * Unserializing a resultset will allow to only works on the rows present in the saved state
 */
PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, unserialize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data, data_sub, __$true, __$false, resultset, container, serializer, _0, _1, _4, _5, _6, _7, _8, _9, _2$$4, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&resultset);
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
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("disableHydration", 16, 1);
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
		_zephir_prop_4 = zend_string_init("columnTypes", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("hydrateMode", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data);
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 809, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 809, &__$false);
	}
	ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The dependency injector container is not valid", "phalcon/Mvc/Model/Resultset/Complex.zep", 356);
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
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Invalid serialization data", "phalcon/Mvc/Model/Resultset/Complex.zep", 369);
		return;
	}
	zephir_memory_observe(&_4);
	zephir_array_fetch_string(&_4, &resultset, SL("rows"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 372);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 812, &_4);
	zephir_memory_observe(&_5);
	zephir_array_fetch_string(&_5, &resultset, SL("rows"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 373);
	ZVAL_UNDEF(&_6);
	ZVAL_LONG(&_6, zephir_fast_count_int(&_5));
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 813, &_6);
	zephir_memory_observe(&_7);
	zephir_array_fetch_string(&_7, &resultset, SL("cache"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 374);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 811, &_7);
	zephir_memory_observe(&_8);
	zephir_array_fetch_string(&_8, &resultset, SL("columnTypes"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 375);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 806, &_8);
	zephir_memory_observe(&_9);
	zephir_array_fetch_string(&_9, &resultset, SL("hydrateMode"), PH_NOISY, "phalcon/Mvc/Model/Resultset/Complex.zep", 376);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 810, &_9);
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, __serialize)
{
	zval records, cache, columnTypes, hydrateMode, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&records);
	ZVAL_UNDEF(&cache);
	ZVAL_UNDEF(&columnTypes);
	ZVAL_UNDEF(&hydrateMode);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("cache", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("columnTypes", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("hydrateMode", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&records, this_ptr, "toArray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 811, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&cache, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 806, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&columnTypes, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 810, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&hydrateMode, &_0);
	zephir_create_array(return_value, 4, 0);
	zephir_array_update_string(return_value, SL("cache"), &cache, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("rows"), &records, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("columnTypes"), &columnTypes, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("hydrateMode"), &hydrateMode, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Phalcon_Mvc_Model_Resultset_Complex, __unserialize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *data_param = NULL, __$true, __$false, _0, _1, _2, _3, _4, _5;
	zval data;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("disableHydration", 16, 1);
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
		_zephir_prop_4 = zend_string_init("columnTypes", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("hydrateMode", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(data, data_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &data_param);
	zephir_get_arrval(&data, data_param);
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 809, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 809, &__$false);
	}
	zephir_array_fetch_string(&_0, &data, SL("rows"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Complex.zep", 407);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 812, &_0);
	zephir_array_fetch_string(&_1, &data, SL("rows"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Complex.zep", 408);
	ZVAL_UNDEF(&_2);
	ZVAL_LONG(&_2, zephir_fast_count_int(&_1));
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 813, &_2);
	zephir_array_fetch_string(&_3, &data, SL("cache"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Complex.zep", 409);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 811, &_3);
	zephir_array_fetch_string(&_4, &data, SL("columnTypes"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Complex.zep", 410);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 806, &_4);
	zephir_array_fetch_string(&_5, &data, SL("hydrateMode"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Resultset/Complex.zep", 411);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 810, &_5);
	ZEPHIR_MM_RESTORE();
}

