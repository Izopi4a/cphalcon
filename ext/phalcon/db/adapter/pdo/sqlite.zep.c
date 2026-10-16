
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
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/main.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Specific functions for the SQLite database system
 *
 * ```php
 * use Phalcon\Db\Adapter\Pdo\Sqlite;
 *
 * $connection = new Sqlite(
 *     [
 *         "dbname" => "/tmp/test.sqlite",
 *     ]
 * );
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter_Pdo_Sqlite)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Adapter\\Pdo, Sqlite, phalcon, db_adapter_pdo_sqlite, phalcon_db_adapter_pdo_abstractpdo_ce, phalcon_db_adapter_pdo_sqlite_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_adapter_pdo_sqlite_ce, SL("dialectType"), "sqlite", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_adapter_pdo_sqlite_ce, SL("type"), "sqlite", ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Constructor for Phalcon\Db\Adapter\Pdo\Sqlite
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *descriptor_param = NULL, _0$$3;
	zval descriptor;

	ZVAL_UNDEF(&descriptor);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(descriptor, descriptor_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &descriptor_param);
	ZEPHIR_OBS_COPY_OR_DUP(&descriptor, descriptor_param);
	if (zephir_array_isset_value_string(&descriptor, SL("charset"))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "SQLite does not allow the charset to be changed in the DSN.");
		ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_0$$3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_db_adapter_pdo_sqlite_ce, getThis(), "__construct", NULL, 0, &descriptor);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * This method is automatically called in Phalcon\Db\Adapter\Pdo
 * constructor. Call it when you need to restore a database connection.
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, connect)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *descriptor_param = NULL, dbname, _0$$3;
	zval descriptor;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&descriptor);
	ZVAL_UNDEF(&dbname);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("descriptor", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(descriptor, descriptor_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &descriptor_param);
	if (!descriptor_param) {
		ZEPHIR_INIT_VAR(&descriptor);
		array_init(&descriptor);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&descriptor, descriptor_param);
	}
	if (ZEPHIR_IS_EMPTY(&descriptor)) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 410, PH_NOISY_CC | PH_READONLY);
		if (UNEXPECTED(Z_TYPE_P(&_0$$3) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&_0$$3, "descriptor", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&descriptor, &_0$$3);
	}
	zephir_memory_observe(&dbname);
	if (zephir_array_isset_string_fetch(&dbname, &descriptor, SL("dbname"), 0)) {
		zephir_array_update_string(&descriptor, SL("dsn"), &dbname, PH_COPY | PH_SEPARATE);
		zephir_array_unset_string(&descriptor, SL("dbname"), PH_SEPARATE);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else if (UNEXPECTED(!(zephir_array_isset_value_string(&descriptor, SL("dsn"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The database must be specified with either 'dbname' or 'dsn'.", "phalcon/Db/Adapter/Pdo/Sqlite.zep", 82);
		return;
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_db_adapter_pdo_sqlite_ce, getThis(), "connect", NULL, 0, &descriptor);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns an array of Phalcon\Db\Column objects describing a table
 *
 * ```php
 * print_r(
 *     $connection->describeColumns("posts")
 * );
 * ```
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, describeColumns)
{
	zend_bool _44, _33$$3, _73$$29;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_36 = NULL, *_41 = NULL, *_42 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, __$true, __$false, columns, columnType, fields, field, definition, oldColumn, sizePattern, matches, matchOne, matchTwo, columnName, _0, _1, _2, *_3, _4, *_5, _43, _6$$3, _31$$3, _32$$3, _34$$3, _35$$3, _7$$4, _8$$4, _9$$5, _10$$5, _11$$5, _12$$7, _13$$7, _14$$8, _15$$9, _16$$10, _17$$11, _18$$11, _19$$12, _20$$12, _21$$13, _22$$13, _23$$14, _24$$15, _25$$16, _26$$17, _27$$18, _28$$19, _29$$21, _30$$22, _37$$28, _38$$28, _39$$28, _40$$28, _45$$29, _46$$29, _71$$29, _72$$29, _74$$29, _75$$29, _47$$30, _48$$30, _49$$31, _50$$31, _51$$31, _52$$33, _53$$33, _54$$34, _55$$35, _56$$36, _57$$37, _58$$37, _59$$38, _60$$38, _61$$39, _62$$39, _63$$40, _64$$41, _65$$42, _66$$43, _67$$44, _68$$45, _69$$47, _70$$48, _76$$54, _77$$54, _78$$54, _79$$54;
	zend_string *table = NULL, *schema = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&columnType);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&oldColumn);
	ZVAL_UNDEF(&sizePattern);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&matchOne);
	ZVAL_UNDEF(&matchTwo);
	ZVAL_UNDEF(&columnName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_43);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_31$$3);
	ZVAL_UNDEF(&_32$$3);
	ZVAL_UNDEF(&_34$$3);
	ZVAL_UNDEF(&_35$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_22$$13);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&_25$$16);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$18);
	ZVAL_UNDEF(&_28$$19);
	ZVAL_UNDEF(&_29$$21);
	ZVAL_UNDEF(&_30$$22);
	ZVAL_UNDEF(&_37$$28);
	ZVAL_UNDEF(&_38$$28);
	ZVAL_UNDEF(&_39$$28);
	ZVAL_UNDEF(&_40$$28);
	ZVAL_UNDEF(&_45$$29);
	ZVAL_UNDEF(&_46$$29);
	ZVAL_UNDEF(&_71$$29);
	ZVAL_UNDEF(&_72$$29);
	ZVAL_UNDEF(&_74$$29);
	ZVAL_UNDEF(&_75$$29);
	ZVAL_UNDEF(&_47$$30);
	ZVAL_UNDEF(&_48$$30);
	ZVAL_UNDEF(&_49$$31);
	ZVAL_UNDEF(&_50$$31);
	ZVAL_UNDEF(&_51$$31);
	ZVAL_UNDEF(&_52$$33);
	ZVAL_UNDEF(&_53$$33);
	ZVAL_UNDEF(&_54$$34);
	ZVAL_UNDEF(&_55$$35);
	ZVAL_UNDEF(&_56$$36);
	ZVAL_UNDEF(&_57$$37);
	ZVAL_UNDEF(&_58$$37);
	ZVAL_UNDEF(&_59$$38);
	ZVAL_UNDEF(&_60$$38);
	ZVAL_UNDEF(&_61$$39);
	ZVAL_UNDEF(&_62$$39);
	ZVAL_UNDEF(&_63$$40);
	ZVAL_UNDEF(&_64$$41);
	ZVAL_UNDEF(&_65$$42);
	ZVAL_UNDEF(&_66$$43);
	ZVAL_UNDEF(&_67$$44);
	ZVAL_UNDEF(&_68$$45);
	ZVAL_UNDEF(&_69$$47);
	ZVAL_UNDEF(&_70$$48);
	ZVAL_UNDEF(&_76$$54);
	ZVAL_UNDEF(&_77$$54);
	ZVAL_UNDEF(&_78$$54);
	ZVAL_UNDEF(&_79$$54);
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
	ZEPHIR_INIT_VAR(&oldColumn);
	ZVAL_NULL(&oldColumn);
	ZEPHIR_INIT_VAR(&sizePattern);
	ZVAL_STRING(&sizePattern, "#\\(([0-9]+)(?:,\\s*([0-9]+))*\\)#");
	ZEPHIR_INIT_VAR(&columns);
	array_init(&columns);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "describeColumns", NULL, 0, &table_zv, &schema_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 3);
	ZEPHIR_CALL_METHOD(&fields, this_ptr, "fetchAll", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	if (Z_TYPE_P(&fields) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4);
		zephir_string_to_char_array(&_4, &fields);
		_3 = &_4;
	} else {
		_3 = &fields;
	}
	zephir_is_iterable(_3, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 319);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _5);
			ZEPHIR_INIT_NVAR(&definition);
			zephir_create_array(&definition, 1, 0);
			add_assoc_long_ex(&definition, SL("bindType"), 2);
			ZEPHIR_OBS_NVAR(&columnType);
			zephir_array_fetch_long(&columnType, &field, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 127);
			ZEPHIR_INIT_NVAR(&_6$$3);
			zephir_fast_strtolower(&_6$$3, &columnType);
			ZEPHIR_CPY_WRT(&columnType, &_6$$3);
			if (zephir_memnstr_str(&columnType, SL("bigint"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 143)) {
				ZEPHIR_INIT_NVAR(&_7$$4);
				ZVAL_LONG(&_7$$4, 14);
				zephir_array_update_string(&definition, SL("type"), &_7$$4, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 2);
				zephir_array_update_string(&definition, SL("bindType"), &_8$$4, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("int"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 150)) {
				ZEPHIR_INIT_NVAR(&_9$$5);
				ZVAL_LONG(&_9$$5, 0);
				zephir_array_update_string(&definition, SL("type"), &_9$$5, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_10$$5);
				ZVAL_LONG(&_10$$5, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_10$$5, PH_COPY | PH_SEPARATE);
				ZEPHIR_OBS_NVAR(&_11$$5);
				zephir_array_fetch_long(&_11$$5, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 158);
				if (zephir_is_true(&_11$$5)) {
					zephir_array_update_string(&definition, SL("autoIncrement"), &__$true, PH_COPY | PH_SEPARATE);
				}
			} else if (zephir_memnstr_str(&columnType, SL("tinyint(1)"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 161)) {
				ZEPHIR_INIT_NVAR(&_12$$7);
				ZVAL_LONG(&_12$$7, 8);
				zephir_array_update_string(&definition, SL("type"), &_12$$7, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_13$$7);
				ZVAL_LONG(&_13$$7, 5);
				zephir_array_update_string(&definition, SL("bindType"), &_13$$7, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&columnType);
				ZVAL_STRING(&columnType, "boolean");
			} else if (zephir_memnstr_str(&columnType, SL("enum"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 172)) {
				ZEPHIR_INIT_NVAR(&_14$$8);
				ZVAL_LONG(&_14$$8, 5);
				zephir_array_update_string(&definition, SL("type"), &_14$$8, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("datetime"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 181)) {
				ZEPHIR_INIT_NVAR(&_15$$9);
				ZVAL_LONG(&_15$$9, 4);
				zephir_array_update_string(&definition, SL("type"), &_15$$9, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("date"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 186)) {
				ZEPHIR_INIT_NVAR(&_16$$10);
				ZVAL_LONG(&_16$$10, 1);
				zephir_array_update_string(&definition, SL("type"), &_16$$10, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("decimal"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 195)) {
				ZEPHIR_INIT_NVAR(&_17$$11);
				ZVAL_LONG(&_17$$11, 3);
				zephir_array_update_string(&definition, SL("type"), &_17$$11, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_18$$11);
				ZVAL_LONG(&_18$$11, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_18$$11, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("float"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 202)) {
				ZEPHIR_INIT_NVAR(&_19$$12);
				ZVAL_LONG(&_19$$12, 7);
				zephir_array_update_string(&definition, SL("type"), &_19$$12, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_20$$12);
				ZVAL_LONG(&_20$$12, 3);
				zephir_array_update_string(&definition, SL("bindType"), &_20$$12, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("real"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 209)) {
				ZEPHIR_INIT_NVAR(&_21$$13);
				ZVAL_LONG(&_21$$13, 7);
				zephir_array_update_string(&definition, SL("type"), &_21$$13, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_22$$13);
				ZVAL_LONG(&_22$$13, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_22$$13, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("timestamp"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 220)) {
				ZEPHIR_INIT_NVAR(&_23$$14);
				ZVAL_LONG(&_23$$14, 17);
				zephir_array_update_string(&definition, SL("type"), &_23$$14, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("varchar"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 229)) {
				ZEPHIR_INIT_NVAR(&_24$$15);
				ZVAL_LONG(&_24$$15, 2);
				zephir_array_update_string(&definition, SL("type"), &_24$$15, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("char"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 234)) {
				ZEPHIR_INIT_NVAR(&_25$$16);
				ZVAL_LONG(&_25$$16, 5);
				zephir_array_update_string(&definition, SL("type"), &_25$$16, PH_COPY | PH_SEPARATE);
			} else if (zephir_memnstr_str(&columnType, SL("text"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 239)) {
				ZEPHIR_INIT_NVAR(&_26$$17);
				ZVAL_LONG(&_26$$17, 6);
				zephir_array_update_string(&definition, SL("type"), &_26$$17, PH_COPY | PH_SEPARATE);
			} else {
				ZEPHIR_INIT_NVAR(&_27$$18);
				ZVAL_LONG(&_27$$18, 2);
				zephir_array_update_string(&definition, SL("type"), &_27$$18, PH_COPY | PH_SEPARATE);
			}
			if (zephir_memnstr_str(&columnType, SL("("), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 256)) {
				ZEPHIR_INIT_NVAR(&matches);
				ZVAL_NULL(&matches);
				ZEPHIR_INIT_NVAR(&_28$$19);
				zephir_preg_match(&_28$$19, &sizePattern, &columnType, &matches, 0, 0 , 0 );
				if (zephir_is_true(&_28$$19)) {
					ZEPHIR_OBS_NVAR(&matchOne);
					if (zephir_array_isset_long_fetch(&matchOne, &matches, 1, 0)) {
						ZEPHIR_INIT_NVAR(&_29$$21);
						ZVAL_LONG(&_29$$21, zephir_get_intval(&matchOne));
						zephir_array_update_string(&definition, SL("size"), &_29$$21, PH_COPY | PH_SEPARATE);
					}
					ZEPHIR_OBS_NVAR(&matchTwo);
					if (zephir_array_isset_long_fetch(&matchTwo, &matches, 2, 0)) {
						ZEPHIR_INIT_NVAR(&_30$$22);
						ZVAL_LONG(&_30$$22, zephir_get_intval(&matchTwo));
						zephir_array_update_string(&definition, SL("scale"), &_30$$22, PH_COPY | PH_SEPARATE);
					}
				}
			}
			if (zephir_memnstr_str(&columnType, SL("unsigned"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 272)) {
				zephir_array_update_string(&definition, SL("unsigned"), &__$true, PH_COPY | PH_SEPARATE);
			}
			if (Z_TYPE_P(&oldColumn) == IS_NULL) {
				zephir_array_update_string(&definition, SL("first"), &__$true, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_31$$3);
			zephir_array_fetch_long(&_31$$3, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 288);
			if (zephir_is_true(&_31$$3)) {
				zephir_array_update_string(&definition, SL("primary"), &__$true, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_32$$3);
			zephir_array_fetch_long(&_32$$3, &field, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 295);
			if (ZEPHIR_IS_LONG(&_32$$3, 0)) {
				zephir_array_update_string(&definition, SL("notNull"), &__$false, PH_COPY | PH_SEPARATE);
			}
			_33$$3 = !(zephir_isempty_dim_long(&field, 4));
			if (_33$$3) {
				ZEPHIR_OBS_NVAR(&_34$$3);
				zephir_array_fetch_long(&_34$$3, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 303);
				ZEPHIR_INIT_NVAR(&_6$$3);
				ZVAL_STRING(&_6$$3, "null");
				ZEPHIR_CALL_FUNCTION(&_35$$3, "strcasecmp", &_36, 38, &_34$$3, &_6$$3);
				zephir_check_call_status();
				_33$$3 = !ZEPHIR_IS_LONG_IDENTICAL(&_35$$3, 0);
			}
			if (_33$$3) {
				ZEPHIR_OBS_NVAR(&_37$$28);
				zephir_array_fetch_long(&_37$$28, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 308);
				ZEPHIR_INIT_NVAR(&_38$$28);
				ZVAL_STRING(&_38$$28, "/^'|'$/");
				ZEPHIR_INIT_NVAR(&_39$$28);
				ZVAL_STRING(&_39$$28, "");
				ZEPHIR_CALL_FUNCTION(&_40$$28, "preg_replace", &_41, 40, &_38$$28, &_39$$28, &_37$$28);
				zephir_check_call_status();
				zephir_array_update_string(&definition, SL("default"), &_40$$28, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&columnName);
			zephir_array_fetch_long(&columnName, &field, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 314);
			ZEPHIR_INIT_NVAR(&_6$$3);
			object_init_ex(&_6$$3, phalcon_db_column_ce);
			ZEPHIR_CALL_METHOD(NULL, &_6$$3, "__construct", &_42, 243, &columnName, &definition);
			zephir_check_call_status();
			zephir_array_append(&columns, &_6$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 315);
			ZEPHIR_CPY_WRT(&oldColumn, &columnName);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_44 = 1;
		while (1) {
			if (_44) {
				_44 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_43, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_43)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_45$$29);
				zephir_create_array(&_45$$29, 1, 0);
				add_assoc_long_ex(&_45$$29, SL("bindType"), 2);
				ZEPHIR_CPY_WRT(&definition, &_45$$29);
				ZEPHIR_OBS_NVAR(&columnType);
				zephir_array_fetch_long(&columnType, &field, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 127);
				ZEPHIR_INIT_NVAR(&_46$$29);
				zephir_fast_strtolower(&_46$$29, &columnType);
				ZEPHIR_CPY_WRT(&columnType, &_46$$29);
				if (zephir_memnstr_str(&columnType, SL("bigint"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 143)) {
					ZEPHIR_INIT_NVAR(&_47$$30);
					ZVAL_LONG(&_47$$30, 14);
					zephir_array_update_string(&definition, SL("type"), &_47$$30, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_48$$30);
					ZVAL_LONG(&_48$$30, 2);
					zephir_array_update_string(&definition, SL("bindType"), &_48$$30, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("int"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 150)) {
					ZEPHIR_INIT_NVAR(&_49$$31);
					ZVAL_LONG(&_49$$31, 0);
					zephir_array_update_string(&definition, SL("type"), &_49$$31, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_50$$31);
					ZVAL_LONG(&_50$$31, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_50$$31, PH_COPY | PH_SEPARATE);
					ZEPHIR_OBS_NVAR(&_51$$31);
					zephir_array_fetch_long(&_51$$31, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 158);
					if (zephir_is_true(&_51$$31)) {
						zephir_array_update_string(&definition, SL("autoIncrement"), &__$true, PH_COPY | PH_SEPARATE);
					}
				} else if (zephir_memnstr_str(&columnType, SL("tinyint(1)"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 161)) {
					ZEPHIR_INIT_NVAR(&_52$$33);
					ZVAL_LONG(&_52$$33, 8);
					zephir_array_update_string(&definition, SL("type"), &_52$$33, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_53$$33);
					ZVAL_LONG(&_53$$33, 5);
					zephir_array_update_string(&definition, SL("bindType"), &_53$$33, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&columnType);
					ZVAL_STRING(&columnType, "boolean");
				} else if (zephir_memnstr_str(&columnType, SL("enum"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 172)) {
					ZEPHIR_INIT_NVAR(&_54$$34);
					ZVAL_LONG(&_54$$34, 5);
					zephir_array_update_string(&definition, SL("type"), &_54$$34, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("datetime"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 181)) {
					ZEPHIR_INIT_NVAR(&_55$$35);
					ZVAL_LONG(&_55$$35, 4);
					zephir_array_update_string(&definition, SL("type"), &_55$$35, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("date"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 186)) {
					ZEPHIR_INIT_NVAR(&_56$$36);
					ZVAL_LONG(&_56$$36, 1);
					zephir_array_update_string(&definition, SL("type"), &_56$$36, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("decimal"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 195)) {
					ZEPHIR_INIT_NVAR(&_57$$37);
					ZVAL_LONG(&_57$$37, 3);
					zephir_array_update_string(&definition, SL("type"), &_57$$37, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_58$$37);
					ZVAL_LONG(&_58$$37, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_58$$37, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("float"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 202)) {
					ZEPHIR_INIT_NVAR(&_59$$38);
					ZVAL_LONG(&_59$$38, 7);
					zephir_array_update_string(&definition, SL("type"), &_59$$38, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_60$$38);
					ZVAL_LONG(&_60$$38, 3);
					zephir_array_update_string(&definition, SL("bindType"), &_60$$38, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("real"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 209)) {
					ZEPHIR_INIT_NVAR(&_61$$39);
					ZVAL_LONG(&_61$$39, 7);
					zephir_array_update_string(&definition, SL("type"), &_61$$39, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_62$$39);
					ZVAL_LONG(&_62$$39, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_62$$39, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("timestamp"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 220)) {
					ZEPHIR_INIT_NVAR(&_63$$40);
					ZVAL_LONG(&_63$$40, 17);
					zephir_array_update_string(&definition, SL("type"), &_63$$40, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("varchar"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 229)) {
					ZEPHIR_INIT_NVAR(&_64$$41);
					ZVAL_LONG(&_64$$41, 2);
					zephir_array_update_string(&definition, SL("type"), &_64$$41, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("char"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 234)) {
					ZEPHIR_INIT_NVAR(&_65$$42);
					ZVAL_LONG(&_65$$42, 5);
					zephir_array_update_string(&definition, SL("type"), &_65$$42, PH_COPY | PH_SEPARATE);
				} else if (zephir_memnstr_str(&columnType, SL("text"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 239)) {
					ZEPHIR_INIT_NVAR(&_66$$43);
					ZVAL_LONG(&_66$$43, 6);
					zephir_array_update_string(&definition, SL("type"), &_66$$43, PH_COPY | PH_SEPARATE);
				} else {
					ZEPHIR_INIT_NVAR(&_67$$44);
					ZVAL_LONG(&_67$$44, 2);
					zephir_array_update_string(&definition, SL("type"), &_67$$44, PH_COPY | PH_SEPARATE);
				}
				if (zephir_memnstr_str(&columnType, SL("("), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 256)) {
					ZEPHIR_INIT_NVAR(&matches);
					ZVAL_NULL(&matches);
					ZEPHIR_INIT_NVAR(&_68$$45);
					zephir_preg_match(&_68$$45, &sizePattern, &columnType, &matches, 0, 0 , 0 );
					if (zephir_is_true(&_68$$45)) {
						ZEPHIR_OBS_NVAR(&matchOne);
						if (zephir_array_isset_long_fetch(&matchOne, &matches, 1, 0)) {
							ZEPHIR_INIT_NVAR(&_69$$47);
							ZVAL_LONG(&_69$$47, zephir_get_intval(&matchOne));
							zephir_array_update_string(&definition, SL("size"), &_69$$47, PH_COPY | PH_SEPARATE);
						}
						ZEPHIR_OBS_NVAR(&matchTwo);
						if (zephir_array_isset_long_fetch(&matchTwo, &matches, 2, 0)) {
							ZEPHIR_INIT_NVAR(&_70$$48);
							ZVAL_LONG(&_70$$48, zephir_get_intval(&matchTwo));
							zephir_array_update_string(&definition, SL("scale"), &_70$$48, PH_COPY | PH_SEPARATE);
						}
					}
				}
				if (zephir_memnstr_str(&columnType, SL("unsigned"), "phalcon/Db/Adapter/Pdo/Sqlite.zep", 272)) {
					zephir_array_update_string(&definition, SL("unsigned"), &__$true, PH_COPY | PH_SEPARATE);
				}
				if (Z_TYPE_P(&oldColumn) == IS_NULL) {
					zephir_array_update_string(&definition, SL("first"), &__$true, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_71$$29);
				zephir_array_fetch_long(&_71$$29, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 288);
				if (zephir_is_true(&_71$$29)) {
					zephir_array_update_string(&definition, SL("primary"), &__$true, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_72$$29);
				zephir_array_fetch_long(&_72$$29, &field, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 295);
				if (ZEPHIR_IS_LONG(&_72$$29, 0)) {
					zephir_array_update_string(&definition, SL("notNull"), &__$false, PH_COPY | PH_SEPARATE);
				}
				_73$$29 = !(zephir_isempty_dim_long(&field, 4));
				if (_73$$29) {
					ZEPHIR_OBS_NVAR(&_74$$29);
					zephir_array_fetch_long(&_74$$29, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 303);
					ZEPHIR_INIT_NVAR(&_46$$29);
					ZVAL_STRING(&_46$$29, "null");
					ZEPHIR_CALL_FUNCTION(&_75$$29, "strcasecmp", &_36, 38, &_74$$29, &_46$$29);
					zephir_check_call_status();
					_73$$29 = !ZEPHIR_IS_LONG_IDENTICAL(&_75$$29, 0);
				}
				if (_73$$29) {
					ZEPHIR_OBS_NVAR(&_76$$54);
					zephir_array_fetch_long(&_76$$54, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 308);
					ZEPHIR_INIT_NVAR(&_77$$54);
					ZVAL_STRING(&_77$$54, "/^'|'$/");
					ZEPHIR_INIT_NVAR(&_78$$54);
					ZVAL_STRING(&_78$$54, "");
					ZEPHIR_CALL_FUNCTION(&_79$$54, "preg_replace", &_41, 40, &_77$$54, &_78$$54, &_76$$54);
					zephir_check_call_status();
					zephir_array_update_string(&definition, SL("default"), &_79$$54, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&columnName);
				zephir_array_fetch_long(&columnName, &field, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 314);
				ZEPHIR_INIT_NVAR(&_46$$29);
				object_init_ex(&_46$$29, phalcon_db_column_ce);
				ZEPHIR_CALL_METHOD(NULL, &_46$$29, "__construct", &_42, 243, &columnName, &definition);
				zephir_check_call_status();
				zephir_array_append(&columns, &_46$$29, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 315);
				ZEPHIR_CPY_WRT(&oldColumn, &columnName);
		}
	}
	ZEPHIR_INIT_NVAR(&field);
	RETURN_CCTOR(&columns);
}

/**
 * Lists table indexes
 *
 * ```php
 * print_r(
 *     $connection->describeIndexes("robots_parts")
 * );
 * ```
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, describeIndexes)
{
	zend_ulong _57;
	zend_bool _31, _18$$3, _43$$13;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_21 = NULL, *_62 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, indexes, index, keyName, indexObjects, name, columns, describeIndexes, describeIndex, indexSql, _0, _1, _2, _3, *_4, _5, *_6, _30, *_54, _55, *_56, _7$$4, _8$$3, _10$$3, _11$$3, _12$$3, *_13$$3, _14$$3, *_15$$3, _17$$3, _20$$3, _22$$3, _9$$6, _16$$7, _19$$8, _23$$9, _24$$9, _25$$9, _26$$9, _27$$10, _28$$11, _29$$12, _32$$14, _33$$13, _35$$13, _36$$13, _37$$13, *_38$$13, _39$$13, *_40$$13, _42$$13, _45$$13, _46$$13, _34$$16, _41$$17, _44$$18, _47$$19, _48$$19, _49$$19, _50$$19, _51$$20, _52$$21, _53$$22, _59$$23, _60$$23, _61$$23;
	zend_string *table = NULL, *schema = NULL, *_58;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&indexes);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&keyName);
	ZVAL_UNDEF(&indexObjects);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&describeIndexes);
	ZVAL_UNDEF(&describeIndex);
	ZVAL_UNDEF(&indexSql);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_55);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_22$$3);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_27$$10);
	ZVAL_UNDEF(&_28$$11);
	ZVAL_UNDEF(&_29$$12);
	ZVAL_UNDEF(&_32$$14);
	ZVAL_UNDEF(&_33$$13);
	ZVAL_UNDEF(&_35$$13);
	ZVAL_UNDEF(&_36$$13);
	ZVAL_UNDEF(&_37$$13);
	ZVAL_UNDEF(&_39$$13);
	ZVAL_UNDEF(&_42$$13);
	ZVAL_UNDEF(&_45$$13);
	ZVAL_UNDEF(&_46$$13);
	ZVAL_UNDEF(&_34$$16);
	ZVAL_UNDEF(&_41$$17);
	ZVAL_UNDEF(&_44$$18);
	ZVAL_UNDEF(&_47$$19);
	ZVAL_UNDEF(&_48$$19);
	ZVAL_UNDEF(&_49$$19);
	ZVAL_UNDEF(&_50$$19);
	ZVAL_UNDEF(&_51$$20);
	ZVAL_UNDEF(&_52$$21);
	ZVAL_UNDEF(&_53$$22);
	ZVAL_UNDEF(&_59$$23);
	ZVAL_UNDEF(&_60$$23);
	ZVAL_UNDEF(&_61$$23);
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
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "describeIndexes", NULL, 0, &table_zv, &schema_zv);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 2);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchAll", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &_0);
		_4 = &_5;
	} else {
		_4 = &_0;
	}
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 377);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&index);
			ZVAL_COPY(&index, _6);
			ZEPHIR_OBS_NVAR(&keyName);
			zephir_array_fetch_string(&keyName, &index, SL("name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 339);
			if (!(zephir_array_isset_value(&indexes, &keyName))) {
				ZEPHIR_INIT_NVAR(&_7$$4);
				array_init(&_7$$4);
				zephir_array_update_zval(&indexes, &keyName, &_7$$4, PH_COPY | PH_SEPARATE);
			}
			zephir_array_fetch(&_8$$3, &indexes, &keyName, PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 345);
			if (!(zephir_array_isset_value_string(&_8$$3, SL("columns")))) {
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
			} else {
				zephir_array_fetch(&_9$$6, &indexes, &keyName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 348);
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch_string(&columns, &_9$$6, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 348);
			}
			zephir_read_property_cached(&_10$$3, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_11$$3, &_10$$3, "describeIndex", NULL, 0, &keyName);
			zephir_check_call_status();
			ZVAL_LONG(&_12$$3, 2);
			ZEPHIR_CALL_METHOD(&describeIndexes, this_ptr, "fetchAll", NULL, 0, &_11$$3, &_12$$3);
			zephir_check_call_status();
			if (Z_TYPE_P(&describeIndexes) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_14$$3);
				zephir_string_to_char_array(&_14$$3, &describeIndexes);
				_13$$3 = &_14$$3;
			} else {
				_13$$3 = &describeIndexes;
			}
			zephir_is_iterable(_13$$3, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 360);
			if (Z_TYPE_P(_13$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13$$3), _15$$3)
				{
					ZEPHIR_INIT_NVAR(&describeIndex);
					ZVAL_COPY(&describeIndex, _15$$3);
					ZEPHIR_OBS_NVAR(&_16$$7);
					zephir_array_fetch_string(&_16$$7, &describeIndex, SL("name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
					zephir_array_append(&columns, &_16$$7, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _13$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_18$$3 = 1;
				while (1) {
					if (_18$$3) {
						_18$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _13$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_17$$3, _13$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_17$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&describeIndex, _13$$3, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&_19$$8);
						zephir_array_fetch_string(&_19$$8, &describeIndex, SL("name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
						zephir_array_append(&columns, &_19$$8, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
				}
			}
			ZEPHIR_INIT_NVAR(&describeIndex);
			zephir_array_update_multi(&indexes, &columns, SL("zs"), 3, &keyName, SL("columns"));
			zephir_read_property_cached(&_12$$3, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_20$$3, &_12$$3, "listIndexesSql", NULL, 0, &table_zv, &schema_zv, &keyName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&indexSql, this_ptr, "fetchColumn", &_21, 0, &_20$$3);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_22$$3);
			zephir_array_fetch_string(&_22$$3, &index, SL("unique"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 366);
			if (zephir_is_true(&_22$$3)) {
				ZEPHIR_INIT_NVAR(&_23$$9);
				ZEPHIR_INIT_NVAR(&_24$$9);
				ZVAL_STRING(&_24$$9, "# UNIQUE #i");
				ZEPHIR_INIT_NVAR(&_25$$9);
				ZEPHIR_INIT_NVAR(&_26$$9);
				ZVAL_STRING(&_26$$9, "# UNIQUE #i");
				zephir_preg_match(&_25$$9, &_26$$9, &indexSql, &_23$$9, 0, 0 , 0 );
				if (zephir_is_true(&_25$$9)) {
					ZEPHIR_INIT_NVAR(&_27$$10);
					ZVAL_STRING(&_27$$10, "UNIQUE");
					zephir_array_update_multi(&indexes, &_27$$10, SL("zs"), 3, &keyName, SL("type"));
				} else {
					ZEPHIR_INIT_NVAR(&_28$$11);
					ZVAL_STRING(&_28$$11, "PRIMARY");
					zephir_array_update_multi(&indexes, &_28$$11, SL("zs"), 3, &keyName, SL("type"));
				}
			} else {
				ZEPHIR_INIT_NVAR(&_29$$12);
				ZVAL_STRING(&_29$$12, "");
				zephir_array_update_multi(&indexes, &_29$$12, SL("zs"), 3, &keyName, SL("type"));
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_31 = 1;
		while (1) {
			if (_31) {
				_31 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_30, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_30)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&index, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&keyName);
				zephir_array_fetch_string(&keyName, &index, SL("name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 339);
				if (!(zephir_array_isset_value(&indexes, &keyName))) {
					ZEPHIR_INIT_NVAR(&_32$$14);
					array_init(&_32$$14);
					zephir_array_update_zval(&indexes, &keyName, &_32$$14, PH_COPY | PH_SEPARATE);
				}
				zephir_array_fetch(&_33$$13, &indexes, &keyName, PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 345);
				if (!(zephir_array_isset_value_string(&_33$$13, SL("columns")))) {
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
				} else {
					zephir_array_fetch(&_34$$16, &indexes, &keyName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 348);
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch_string(&columns, &_34$$16, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 348);
				}
				zephir_read_property_cached(&_35$$13, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_METHOD(&_36$$13, &_35$$13, "describeIndex", NULL, 0, &keyName);
				zephir_check_call_status();
				ZVAL_LONG(&_37$$13, 2);
				ZEPHIR_CALL_METHOD(&describeIndexes, this_ptr, "fetchAll", NULL, 0, &_36$$13, &_37$$13);
				zephir_check_call_status();
				if (Z_TYPE_P(&describeIndexes) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_39$$13);
					zephir_string_to_char_array(&_39$$13, &describeIndexes);
					_38$$13 = &_39$$13;
				} else {
					_38$$13 = &describeIndexes;
				}
				zephir_is_iterable(_38$$13, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 360);
				if (Z_TYPE_P(_38$$13) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_38$$13), _40$$13)
					{
						ZEPHIR_INIT_NVAR(&describeIndex);
						ZVAL_COPY(&describeIndex, _40$$13);
						ZEPHIR_OBS_NVAR(&_41$$17);
						zephir_array_fetch_string(&_41$$17, &describeIndex, SL("name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
						zephir_array_append(&columns, &_41$$17, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _38$$13, "rewind", NULL, 0);
					zephir_check_call_status();
					_43$$13 = 1;
					while (1) {
						if (_43$$13) {
							_43$$13 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _38$$13, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_42$$13, _38$$13, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_42$$13)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&describeIndex, _38$$13, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_OBS_NVAR(&_44$$18);
							zephir_array_fetch_string(&_44$$18, &describeIndex, SL("name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
							zephir_array_append(&columns, &_44$$18, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 357);
					}
				}
				ZEPHIR_INIT_NVAR(&describeIndex);
				zephir_array_update_multi(&indexes, &columns, SL("zs"), 3, &keyName, SL("columns"));
				zephir_read_property_cached(&_37$$13, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_METHOD(&_45$$13, &_37$$13, "listIndexesSql", NULL, 0, &table_zv, &schema_zv, &keyName);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&indexSql, this_ptr, "fetchColumn", &_21, 0, &_45$$13);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_46$$13);
				zephir_array_fetch_string(&_46$$13, &index, SL("unique"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 366);
				if (zephir_is_true(&_46$$13)) {
					ZEPHIR_INIT_NVAR(&_47$$19);
					ZEPHIR_INIT_NVAR(&_48$$19);
					ZVAL_STRING(&_48$$19, "# UNIQUE #i");
					ZEPHIR_INIT_NVAR(&_49$$19);
					ZEPHIR_INIT_NVAR(&_50$$19);
					ZVAL_STRING(&_50$$19, "# UNIQUE #i");
					zephir_preg_match(&_49$$19, &_50$$19, &indexSql, &_47$$19, 0, 0 , 0 );
					if (zephir_is_true(&_49$$19)) {
						ZEPHIR_INIT_NVAR(&_51$$20);
						ZVAL_STRING(&_51$$20, "UNIQUE");
						zephir_array_update_multi(&indexes, &_51$$20, SL("zs"), 3, &keyName, SL("type"));
					} else {
						ZEPHIR_INIT_NVAR(&_52$$21);
						ZVAL_STRING(&_52$$21, "PRIMARY");
						zephir_array_update_multi(&indexes, &_52$$21, SL("zs"), 3, &keyName, SL("type"));
					}
				} else {
					ZEPHIR_INIT_NVAR(&_53$$22);
					ZVAL_STRING(&_53$$22, "");
					zephir_array_update_multi(&indexes, &_53$$22, SL("zs"), 3, &keyName, SL("type"));
				}
		}
	}
	ZEPHIR_INIT_NVAR(&index);
	ZEPHIR_INIT_VAR(&indexObjects);
	array_init(&indexObjects);
	if (Z_TYPE_P(&indexes) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_55);
		zephir_string_to_char_array(&_55, &indexes);
		_54 = &_55;
	} else {
		_54 = &indexes;
	}
	zephir_is_iterable(_54, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 387);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_54), _57, _58, _56)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_58 != NULL) { 
			ZVAL_STR_COPY(&name, _58);
		} else {
			ZVAL_LONG(&name, _57);
		}
		ZEPHIR_INIT_NVAR(&index);
		ZVAL_COPY(&index, _56);
		ZEPHIR_INIT_NVAR(&_59$$23);
		object_init_ex(&_59$$23, phalcon_db_index_ce);
		ZEPHIR_OBS_NVAR(&_60$$23);
		zephir_array_fetch_string(&_60$$23, &index, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 382);
		ZEPHIR_OBS_NVAR(&_61$$23);
		zephir_array_fetch_string(&_61$$23, &index, SL("type"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 384);
		ZEPHIR_CALL_METHOD(NULL, &_59$$23, "__construct", &_62, 33, &name, &_60$$23, &_61$$23);
		zephir_check_call_status();
		zephir_array_update_zval(&indexObjects, &name, &_59$$23, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&index);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&indexObjects);
}

/**
 * Lists table references
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, describeReferences)
{
	zval _15$$3, _24$$6, _31$$9;
	zend_bool _17;
	zend_ulong _7, _28;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_33 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, references, reference, arrayReference, constraintName, referenceObjects, name, referencedSchema, referencedTable, columns, referencedColumns, number, _0, _1, _2, _3, *_4, _5, *_6, _16, *_25, _26, *_27, _9$$5, _10$$5, _11$$5, _12$$5, _13$$3, _14$$3, _18$$8, _19$$8, _20$$8, _21$$8, _22$$6, _23$$6, _30$$9, _32$$9;
	zend_string *table = NULL, *schema = NULL, *_8, *_29;
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
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_23$$6);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_32$$9);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_24$$6);
	ZVAL_UNDEF(&_31$$9);
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
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 411, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 427);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _7, _8, _6)
		{
			ZEPHIR_INIT_NVAR(&number);
			if (_8 != NULL) { 
				ZVAL_STR_COPY(&number, _8);
			} else {
				ZVAL_LONG(&number, _7);
			}
			ZEPHIR_INIT_NVAR(&reference);
			ZVAL_COPY(&reference, _6);
			ZEPHIR_INIT_NVAR(&constraintName);
			ZEPHIR_CONCAT_SV(&constraintName, "foreign_key_", &number);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (!(zephir_array_isset_value(&references, &constraintName))) {
				ZEPHIR_INIT_NVAR(&referencedSchema);
				ZVAL_NULL(&referencedSchema);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_long(&referencedTable, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 406);
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
				ZEPHIR_INIT_NVAR(&referencedColumns);
				array_init(&referencedColumns);
			} else {
				zephir_array_fetch(&_9$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 410);
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_string(&referencedSchema, &_9$$5, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 410);
				zephir_array_fetch(&_10$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 411);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_string(&referencedTable, &_10$$5, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 411);
				zephir_array_fetch(&_11$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 412);
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch_string(&columns, &_11$$5, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 412);
				zephir_array_fetch(&_12$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 413);
				ZEPHIR_OBS_NVAR(&referencedColumns);
				zephir_array_fetch_string(&referencedColumns, &_12$$5, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 413);
			}
			ZEPHIR_OBS_NVAR(&_13$$3);
			zephir_array_fetch_long(&_13$$3, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 416);
			zephir_array_append(&columns, &_13$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 416);
			ZEPHIR_OBS_NVAR(&_14$$3);
			zephir_array_fetch_long(&_14$$3, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 417);
			zephir_array_append(&referencedColumns, &_14$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 417);
			ZEPHIR_INIT_NVAR(&_15$$3);
			zephir_create_array(&_15$$3, 4, 0);
			zephir_array_update_string(&_15$$3, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
			zephir_array_update_zval(&references, &constraintName, &_15$$3, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_17 = 1;
		while (1) {
			if (_17) {
				_17 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_16, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_16)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&number, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&reference, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&constraintName);
				ZEPHIR_CONCAT_SV(&constraintName, "foreign_key_", &number);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (!(zephir_array_isset_value(&references, &constraintName))) {
					ZEPHIR_INIT_NVAR(&referencedSchema);
					ZVAL_NULL(&referencedSchema);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_long(&referencedTable, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 406);
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
					ZEPHIR_INIT_NVAR(&referencedColumns);
					array_init(&referencedColumns);
				} else {
					zephir_array_fetch(&_18$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 410);
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_string(&referencedSchema, &_18$$8, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 410);
					zephir_array_fetch(&_19$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 411);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_string(&referencedTable, &_19$$8, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 411);
					zephir_array_fetch(&_20$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 412);
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch_string(&columns, &_20$$8, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 412);
					zephir_array_fetch(&_21$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 413);
					ZEPHIR_OBS_NVAR(&referencedColumns);
					zephir_array_fetch_string(&referencedColumns, &_21$$8, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 413);
				}
				ZEPHIR_OBS_NVAR(&_22$$6);
				zephir_array_fetch_long(&_22$$6, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 416);
				zephir_array_append(&columns, &_22$$6, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 416);
				ZEPHIR_OBS_NVAR(&_23$$6);
				zephir_array_fetch_long(&_23$$6, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 417);
				zephir_array_append(&referencedColumns, &_23$$6, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 417);
				ZEPHIR_INIT_NVAR(&_24$$6);
				zephir_create_array(&_24$$6, 4, 0);
				zephir_array_update_string(&_24$$6, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_24$$6, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_24$$6, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_24$$6, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&references, &constraintName, &_24$$6, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&reference);
	ZEPHIR_INIT_NVAR(&number);
	ZEPHIR_INIT_VAR(&referenceObjects);
	array_init(&referenceObjects);
	if (Z_TYPE_P(&references) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_26);
		zephir_string_to_char_array(&_26, &references);
		_25 = &_26;
	} else {
		_25 = &references;
	}
	zephir_is_iterable(_25, 0, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 441);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_25), _28, _29, _27)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_29 != NULL) { 
			ZVAL_STR_COPY(&name, _29);
		} else {
			ZVAL_LONG(&name, _28);
		}
		ZEPHIR_INIT_NVAR(&arrayReference);
		ZVAL_COPY(&arrayReference, _27);
		ZEPHIR_INIT_NVAR(&_30$$9);
		object_init_ex(&_30$$9, phalcon_db_reference_ce);
		ZEPHIR_INIT_NVAR(&_31$$9);
		zephir_create_array(&_31$$9, 4, 0);
		ZEPHIR_OBS_NVAR(&_32$$9);
		zephir_array_fetch_string(&_32$$9, &arrayReference, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 433);
		zephir_array_update_string(&_31$$9, SL("referencedSchema"), &_32$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_32$$9);
		zephir_array_fetch_string(&_32$$9, &arrayReference, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 434);
		zephir_array_update_string(&_31$$9, SL("referencedTable"), &_32$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_32$$9);
		zephir_array_fetch_string(&_32$$9, &arrayReference, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 435);
		zephir_array_update_string(&_31$$9, SL("columns"), &_32$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_32$$9);
		zephir_array_fetch_string(&_32$$9, &arrayReference, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Sqlite.zep", 437);
		zephir_array_update_string(&_31$$9, SL("referencedColumns"), &_32$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, &_30$$9, "__construct", &_33, 34, &name, &_31$$9);
		zephir_check_call_status();
		zephir_array_update_zval(&referenceObjects, &name, &_30$$9, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&arrayReference);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&referenceObjects);
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
 *         $connection->getDefaultValue(),
 *     ],
 *     [
 *         "name",
 *         "year",
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, getDefaultValue)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	object_init_ex(return_value, phalcon_db_rawvalue_ce);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "NULL");
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 35, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check whether the database system requires an explicit value for identity
 * columns
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, useExplicitIdValue)
{

	RETURN_BOOL(1);
}

/**
 * SQLite does not support the DEFAULT keyword
 *
 * @deprecated Will re removed in the next version
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, supportsDefaultValue)
{

	RETURN_BOOL(0);
}

/**
 * Returns PDO adapter DSN defaults as a key-value map.
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Sqlite, getDsnDefaults)
{

	array_init(return_value);
	return;
}

