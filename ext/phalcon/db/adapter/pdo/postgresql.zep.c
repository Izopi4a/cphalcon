
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
 * Specific functions for the PostgreSQL database system
 *
 * ```php
 * use Phalcon\Db\Adapter\Pdo\Postgresql;
 *
 * $config = [
 *     "host"     => "localhost",
 *     "dbname"   => "blog",
 *     "port"     => 5432,
 *     "username" => "postgres",
 *     "password" => "secret",
 * ];
 *
 * $connection = new Postgresql($config);
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter_Pdo_Postgresql)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Adapter\\Pdo, Postgresql, phalcon, db_adapter_pdo_postgresql, phalcon_db_adapter_pdo_abstractpdo_ce, phalcon_db_adapter_pdo_postgresql_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_adapter_pdo_postgresql_ce, SL("dialectType"), "postgresql", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_adapter_pdo_postgresql_ce, SL("type"), "pgsql", ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Constructor for Phalcon\Db\Adapter\Pdo\Postgresql
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, __construct)
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
		ZVAL_STRING(&_0$$3, "Postgres does not allow the charset to be changed in the DSN.");
		ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_0$$3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_db_adapter_pdo_postgresql_ce, getThis(), "__construct", NULL, 0, &descriptor);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * This method is automatically called in Phalcon\Db\Adapter\Pdo
 * constructor. Call it when you need to restore a database connection.
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, connect)
{
	zend_bool _2$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *descriptor_param = NULL, __$null, schema, sql, _0$$3, _1$$6, _3$$6;
	zval descriptor;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&descriptor);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_3$$6);
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
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 407, PH_NOISY_CC | PH_READONLY);
		if (UNEXPECTED(Z_TYPE_P(&_0$$3) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&_0$$3, "descriptor", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&descriptor, &_0$$3);
	}
	zephir_memory_observe(&schema);
	if (zephir_array_isset_string_fetch(&schema, &descriptor, SL("schema"), 0)) {
		zephir_array_unset_string(&descriptor, SL("schema"), PH_SEPARATE);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_NVAR(&schema);
		ZVAL_NULL(&schema);
	}
	if (zephir_array_isset_value_string(&descriptor, SL("password"))) {
		zephir_memory_observe(&_1$$6);
		zephir_array_fetch_string(&_1$$6, &descriptor, SL("password"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 85);
		_2$$6 = Z_TYPE_P(&_1$$6) == IS_STRING;
		if (_2$$6) {
			zephir_memory_observe(&_3$$6);
			zephir_array_fetch_string(&_3$$6, &descriptor, SL("password"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 85);
			_2$$6 = zephir_fast_strlen_ev(&_3$$6) == 0;
		}
		if (_2$$6) {
			zephir_array_update_string(&descriptor, SL("password"), &__$null, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_db_adapter_pdo_postgresql_ce, getThis(), "connect", NULL, 0, &descriptor);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&schema))) {
		ZEPHIR_INIT_VAR(&sql);
		ZEPHIR_CONCAT_SVS(&sql, "SET search_path TO '", &schema, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execute", NULL, 0, &sql);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Creates a table
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, createTable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval definition;
	zval tableName_zv, schemaName_zv, *definition_param = NULL, sql, queries, query, exception, columns, _0, *_1$$6, _2$$6, *_3$$6, _4$$7, _6$$5, _7$$11, _8$$11;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&queries);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&exception);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$11);
	ZVAL_UNDEF(&_8$$11);
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
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The table must contain at least one column", "phalcon/Db/Adapter/Pdo/Postgresql.zep", 107);
		return;
	}
	if (UNEXPECTED(!(zephir_fast_count_int(&columns)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The table must contain at least one column", "phalcon/Db/Adapter/Pdo/Postgresql.zep", 111);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 408, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&sql, &_0, "createTable", NULL, 0, &tableName_zv, &schemaName_zv, &definition);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&queries);
	zephir_fast_explode_str(&queries, SL(";"), &sql, NULL);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_fast_count_int(&queries) > 1) {

		/* try_start_1: */

			ZEPHIR_CALL_METHOD(NULL, this_ptr, "begin", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			if (Z_TYPE_P(&queries) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_2$$6);
				zephir_string_to_char_array(&_2$$6, &queries);
				_1$$6 = &_2$$6;
			} else {
				_1$$6 = &queries;
			}
			zephir_is_iterable(_1$$6, 0, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 130);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1$$6), _3$$6)
			{
				ZEPHIR_INIT_NVAR(&query);
				ZVAL_COPY(&query, _3$$6);
				if (ZEPHIR_IS_EMPTY(&query)) {
					continue;
				}
				ZEPHIR_INIT_NVAR(&_4$$7);
				ZEPHIR_CONCAT_VS(&_4$$7, &query, ";");
				if (UNEXPECTED(EG(exception))) {
					goto try_end_1;
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "query", &_5, 0, &_4$$7);
				zephir_check_call_status_or_jump(try_end_1);
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&query);
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "commit", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			RETURN_MM();

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_VAR(&_6$$5);
			ZVAL_OBJ(&_6$$5, EG(exception));
			Z_ADDREF_P(&_6$$5);
			if (zephir_is_instance_of(&_6$$5, SL("Throwable"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&exception, &_6$$5);
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollback", NULL, 0);
				zephir_check_call_status();
				zephir_throw_exception_debug(&exception, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 134);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	} else {
		zephir_memory_observe(&_7$$11);
		zephir_array_fetch_long(&_7$$11, &queries, 0, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 137);
		ZEPHIR_INIT_VAR(&_8$$11);
		ZEPHIR_CONCAT_VS(&_8$$11, &_7$$11, ";");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_8$$11);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(1);
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
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, describeColumns)
{
	zend_bool _65, _6$$3, _67$$41;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_56 = NULL, *_59 = NULL, *_63 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, __$true, __$false, __$null, columns, columnType, fields, field, definition, oldColumn, columnName, charSize, numericSize, numericScale, _0, _1, _2, *_3, _4, *_5, _64, _48$$3, _49$$3, _50$$3, _51$$3, _60$$3, _62$$3, _7$$4, _8$$4, _9$$5, _10$$5, _11$$6, _12$$6, _13$$7, _14$$7, _15$$8, _16$$8, _17$$9, _18$$9, _19$$10, _20$$11, _21$$12, _22$$12, _23$$13, _24$$13, _25$$14, _26$$14, _27$$15, _28$$15, _29$$16, _30$$16, _31$$17, _32$$18, _33$$19, _34$$20, _35$$21, _36$$22, _37$$23, _38$$24, _39$$25, _40$$26, _41$$27, _42$$28, _43$$29, _44$$30, _45$$31, _46$$31, _47$$32, _52$$38, _53$$38, _54$$38, _55$$38, _57$$38, _58$$38, _61$$40, _66$$41, _109$$41, _110$$41, _111$$41, _112$$41, _119$$41, _121$$41, _68$$42, _69$$42, _70$$43, _71$$43, _72$$44, _73$$44, _74$$45, _75$$45, _76$$46, _77$$46, _78$$47, _79$$47, _80$$48, _81$$49, _82$$50, _83$$50, _84$$51, _85$$51, _86$$52, _87$$52, _88$$53, _89$$53, _90$$54, _91$$54, _92$$55, _93$$56, _94$$57, _95$$58, _96$$59, _97$$60, _98$$61, _99$$62, _100$$63, _101$$64, _102$$65, _103$$66, _104$$67, _105$$68, _106$$69, _107$$69, _108$$70, _113$$76, _114$$76, _115$$76, _116$$76, _117$$76, _118$$76, _120$$78;
	zend_string *table = NULL, *schema = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&columnType);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&oldColumn);
	ZVAL_UNDEF(&columnName);
	ZVAL_UNDEF(&charSize);
	ZVAL_UNDEF(&numericSize);
	ZVAL_UNDEF(&numericScale);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_64);
	ZVAL_UNDEF(&_48$$3);
	ZVAL_UNDEF(&_49$$3);
	ZVAL_UNDEF(&_50$$3);
	ZVAL_UNDEF(&_51$$3);
	ZVAL_UNDEF(&_60$$3);
	ZVAL_UNDEF(&_62$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_20$$11);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&_22$$12);
	ZVAL_UNDEF(&_23$$13);
	ZVAL_UNDEF(&_24$$13);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_26$$14);
	ZVAL_UNDEF(&_27$$15);
	ZVAL_UNDEF(&_28$$15);
	ZVAL_UNDEF(&_29$$16);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_31$$17);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_33$$19);
	ZVAL_UNDEF(&_34$$20);
	ZVAL_UNDEF(&_35$$21);
	ZVAL_UNDEF(&_36$$22);
	ZVAL_UNDEF(&_37$$23);
	ZVAL_UNDEF(&_38$$24);
	ZVAL_UNDEF(&_39$$25);
	ZVAL_UNDEF(&_40$$26);
	ZVAL_UNDEF(&_41$$27);
	ZVAL_UNDEF(&_42$$28);
	ZVAL_UNDEF(&_43$$29);
	ZVAL_UNDEF(&_44$$30);
	ZVAL_UNDEF(&_45$$31);
	ZVAL_UNDEF(&_46$$31);
	ZVAL_UNDEF(&_47$$32);
	ZVAL_UNDEF(&_52$$38);
	ZVAL_UNDEF(&_53$$38);
	ZVAL_UNDEF(&_54$$38);
	ZVAL_UNDEF(&_55$$38);
	ZVAL_UNDEF(&_57$$38);
	ZVAL_UNDEF(&_58$$38);
	ZVAL_UNDEF(&_61$$40);
	ZVAL_UNDEF(&_66$$41);
	ZVAL_UNDEF(&_109$$41);
	ZVAL_UNDEF(&_110$$41);
	ZVAL_UNDEF(&_111$$41);
	ZVAL_UNDEF(&_112$$41);
	ZVAL_UNDEF(&_119$$41);
	ZVAL_UNDEF(&_121$$41);
	ZVAL_UNDEF(&_68$$42);
	ZVAL_UNDEF(&_69$$42);
	ZVAL_UNDEF(&_70$$43);
	ZVAL_UNDEF(&_71$$43);
	ZVAL_UNDEF(&_72$$44);
	ZVAL_UNDEF(&_73$$44);
	ZVAL_UNDEF(&_74$$45);
	ZVAL_UNDEF(&_75$$45);
	ZVAL_UNDEF(&_76$$46);
	ZVAL_UNDEF(&_77$$46);
	ZVAL_UNDEF(&_78$$47);
	ZVAL_UNDEF(&_79$$47);
	ZVAL_UNDEF(&_80$$48);
	ZVAL_UNDEF(&_81$$49);
	ZVAL_UNDEF(&_82$$50);
	ZVAL_UNDEF(&_83$$50);
	ZVAL_UNDEF(&_84$$51);
	ZVAL_UNDEF(&_85$$51);
	ZVAL_UNDEF(&_86$$52);
	ZVAL_UNDEF(&_87$$52);
	ZVAL_UNDEF(&_88$$53);
	ZVAL_UNDEF(&_89$$53);
	ZVAL_UNDEF(&_90$$54);
	ZVAL_UNDEF(&_91$$54);
	ZVAL_UNDEF(&_92$$55);
	ZVAL_UNDEF(&_93$$56);
	ZVAL_UNDEF(&_94$$57);
	ZVAL_UNDEF(&_95$$58);
	ZVAL_UNDEF(&_96$$59);
	ZVAL_UNDEF(&_97$$60);
	ZVAL_UNDEF(&_98$$61);
	ZVAL_UNDEF(&_99$$62);
	ZVAL_UNDEF(&_100$$63);
	ZVAL_UNDEF(&_101$$64);
	ZVAL_UNDEF(&_102$$65);
	ZVAL_UNDEF(&_103$$66);
	ZVAL_UNDEF(&_104$$67);
	ZVAL_UNDEF(&_105$$68);
	ZVAL_UNDEF(&_106$$69);
	ZVAL_UNDEF(&_107$$69);
	ZVAL_UNDEF(&_108$$70);
	ZVAL_UNDEF(&_113$$76);
	ZVAL_UNDEF(&_114$$76);
	ZVAL_UNDEF(&_115$$76);
	ZVAL_UNDEF(&_116$$76);
	ZVAL_UNDEF(&_117$$76);
	ZVAL_UNDEF(&_118$$76);
	ZVAL_UNDEF(&_120$$78);
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
	ZEPHIR_INIT_VAR(&columns);
	array_init(&columns);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 408, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(_3, 0, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 529);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _5);
			ZEPHIR_INIT_NVAR(&definition);
			zephir_create_array(&definition, 1, 0);
			add_assoc_long_ex(&definition, SL("bindType"), 2);
			ZEPHIR_OBS_NVAR(&columnType);
			zephir_array_fetch_long(&columnType, &field, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 182);
			ZEPHIR_OBS_NVAR(&charSize);
			zephir_array_fetch_long(&charSize, &field, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 183);
			ZEPHIR_OBS_NVAR(&numericSize);
			zephir_array_fetch_long(&numericSize, &field, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 184);
			ZEPHIR_OBS_NVAR(&numericScale);
			zephir_array_fetch_long(&numericScale, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 185);
			_6$$3 = 1;
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("boolean"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 203)) { goto zephir_switch_0_clause_0; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("bigint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 215)) { goto zephir_switch_0_clause_1; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("mediumint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 225)) { goto zephir_switch_0_clause_2; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("smallint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 235)) { goto zephir_switch_0_clause_3; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("tinyint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 245)) { goto zephir_switch_0_clause_4; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("int"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 258)) { goto zephir_switch_0_clause_5; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("bit"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 268)) { goto zephir_switch_0_clause_6; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("enum"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 277)) { goto zephir_switch_0_clause_7; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("datetime"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 285)) { goto zephir_switch_0_clause_8; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("date"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 294)) { goto zephir_switch_0_clause_9; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("decimal"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 304)) { goto zephir_switch_0_clause_10; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("numeric"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 305)) { goto zephir_switch_0_clause_11; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("double precision"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 316)) { goto zephir_switch_0_clause_12; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("float"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 327)) { goto zephir_switch_0_clause_13; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("real"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 328)) { goto zephir_switch_0_clause_14; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("mediumblob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 339)) { goto zephir_switch_0_clause_15; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("longblob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 347)) { goto zephir_switch_0_clause_16; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("tinyblob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 355)) { goto zephir_switch_0_clause_17; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("blob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 363)) { goto zephir_switch_0_clause_18; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("timestamp"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 371)) { goto zephir_switch_0_clause_19; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("time"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 379)) { goto zephir_switch_0_clause_20; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("jsonb"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 387)) { goto zephir_switch_0_clause_21; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("json"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 395)) { goto zephir_switch_0_clause_22; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("longtext"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 403)) { goto zephir_switch_0_clause_23; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("mediumtext"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 411)) { goto zephir_switch_0_clause_24; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("tinytext"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 419)) { goto zephir_switch_0_clause_25; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("text"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 427)) { goto zephir_switch_0_clause_26; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("varying"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 435)) { goto zephir_switch_0_clause_27; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("varchar"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 436)) { goto zephir_switch_0_clause_28; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("char"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 445)) { goto zephir_switch_0_clause_29; }
			if (_6$$3 == zephir_memnstr_str(&columnType, SL("uuid"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 454)) { goto zephir_switch_0_clause_30; }
			goto zephir_switch_0_clause_31;
			zephir_switch_0_clause_0: ;
				ZEPHIR_INIT_NVAR(&_7$$4);
				ZVAL_LONG(&_7$$4, 8);
				zephir_array_update_string(&definition, SL("type"), &_7$$4, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 5);
				zephir_array_update_string(&definition, SL("bindType"), &_8$$4, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				ZEPHIR_INIT_NVAR(&_9$$5);
				ZVAL_LONG(&_9$$5, 14);
				zephir_array_update_string(&definition, SL("type"), &_9$$5, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_10$$5);
				ZVAL_LONG(&_10$$5, 2);
				zephir_array_update_string(&definition, SL("bindType"), &_10$$5, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
				ZEPHIR_INIT_NVAR(&_11$$6);
				ZVAL_LONG(&_11$$6, 21);
				zephir_array_update_string(&definition, SL("type"), &_11$$6, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_12$$6);
				ZVAL_LONG(&_12$$6, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_12$$6, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_NVAR(&_13$$7);
				ZVAL_LONG(&_13$$7, 22);
				zephir_array_update_string(&definition, SL("type"), &_13$$7, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_14$$7);
				ZVAL_LONG(&_14$$7, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_14$$7, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_INIT_NVAR(&_15$$8);
				ZVAL_LONG(&_15$$8, 26);
				zephir_array_update_string(&definition, SL("type"), &_15$$8, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_16$$8);
				ZVAL_LONG(&_16$$8, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_16$$8, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_5: ;
				ZEPHIR_INIT_NVAR(&_17$$9);
				ZVAL_LONG(&_17$$9, 0);
				zephir_array_update_string(&definition, SL("type"), &_17$$9, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_18$$9);
				ZVAL_LONG(&_18$$9, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_18$$9, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_6: ;
				ZEPHIR_INIT_NVAR(&_19$$10);
				ZVAL_LONG(&_19$$10, 19);
				zephir_array_update_string(&definition, SL("type"), &_19$$10, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_7: ;
				ZEPHIR_INIT_NVAR(&_20$$11);
				ZVAL_LONG(&_20$$11, 18);
				zephir_array_update_string(&definition, SL("type"), &_20$$11, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_8: ;
				ZEPHIR_INIT_NVAR(&_21$$12);
				ZVAL_LONG(&_21$$12, 4);
				zephir_array_update_string(&definition, SL("type"), &_21$$12, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_22$$12);
				ZVAL_LONG(&_22$$12, 0);
				zephir_array_update_string(&definition, SL("size"), &_22$$12, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_9: ;
				ZEPHIR_INIT_NVAR(&_23$$13);
				ZVAL_LONG(&_23$$13, 1);
				zephir_array_update_string(&definition, SL("type"), &_23$$13, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_24$$13);
				ZVAL_LONG(&_24$$13, 0);
				zephir_array_update_string(&definition, SL("size"), &_24$$13, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_10: ;
			zephir_switch_0_clause_11: ;
				ZEPHIR_INIT_NVAR(&_25$$14);
				ZVAL_LONG(&_25$$14, 3);
				zephir_array_update_string(&definition, SL("type"), &_25$$14, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_26$$14);
				ZVAL_LONG(&_26$$14, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_26$$14, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_12: ;
				ZEPHIR_INIT_NVAR(&_27$$15);
				ZVAL_LONG(&_27$$15, 9);
				zephir_array_update_string(&definition, SL("type"), &_27$$15, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_28$$15);
				ZVAL_LONG(&_28$$15, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_28$$15, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_13: ;
			zephir_switch_0_clause_14: ;
				ZEPHIR_INIT_NVAR(&_29$$16);
				ZVAL_LONG(&_29$$16, 7);
				zephir_array_update_string(&definition, SL("type"), &_29$$16, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_30$$16);
				ZVAL_LONG(&_30$$16, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_30$$16, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_15: ;
				ZEPHIR_INIT_NVAR(&_31$$17);
				ZVAL_LONG(&_31$$17, 6);
				zephir_array_update_string(&definition, SL("type"), &_31$$17, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_16: ;
				ZEPHIR_INIT_NVAR(&_32$$18);
				ZVAL_LONG(&_32$$18, 13);
				zephir_array_update_string(&definition, SL("type"), &_32$$18, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_17: ;
				ZEPHIR_INIT_NVAR(&_33$$19);
				ZVAL_LONG(&_33$$19, 10);
				zephir_array_update_string(&definition, SL("type"), &_33$$19, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_18: ;
				ZEPHIR_INIT_NVAR(&_34$$20);
				ZVAL_LONG(&_34$$20, 11);
				zephir_array_update_string(&definition, SL("type"), &_34$$20, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_19: ;
				ZEPHIR_INIT_NVAR(&_35$$21);
				ZVAL_LONG(&_35$$21, 17);
				zephir_array_update_string(&definition, SL("type"), &_35$$21, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_20: ;
				ZEPHIR_INIT_NVAR(&_36$$22);
				ZVAL_LONG(&_36$$22, 20);
				zephir_array_update_string(&definition, SL("type"), &_36$$22, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_21: ;
				ZEPHIR_INIT_NVAR(&_37$$23);
				ZVAL_LONG(&_37$$23, 16);
				zephir_array_update_string(&definition, SL("type"), &_37$$23, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_22: ;
				ZEPHIR_INIT_NVAR(&_38$$24);
				ZVAL_LONG(&_38$$24, 15);
				zephir_array_update_string(&definition, SL("type"), &_38$$24, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_23: ;
				ZEPHIR_INIT_NVAR(&_39$$25);
				ZVAL_LONG(&_39$$25, 24);
				zephir_array_update_string(&definition, SL("type"), &_39$$25, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_24: ;
				ZEPHIR_INIT_NVAR(&_40$$26);
				ZVAL_LONG(&_40$$26, 23);
				zephir_array_update_string(&definition, SL("type"), &_40$$26, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_25: ;
				ZEPHIR_INIT_NVAR(&_41$$27);
				ZVAL_LONG(&_41$$27, 25);
				zephir_array_update_string(&definition, SL("type"), &_41$$27, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_26: ;
				ZEPHIR_INIT_NVAR(&_42$$28);
				ZVAL_LONG(&_42$$28, 6);
				zephir_array_update_string(&definition, SL("type"), &_42$$28, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_27: ;
			zephir_switch_0_clause_28: ;
				ZEPHIR_INIT_NVAR(&_43$$29);
				ZVAL_LONG(&_43$$29, 2);
				zephir_array_update_string(&definition, SL("type"), &_43$$29, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("size"), &charSize, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_29: ;
				ZEPHIR_INIT_NVAR(&_44$$30);
				ZVAL_LONG(&_44$$30, 5);
				zephir_array_update_string(&definition, SL("type"), &_44$$30, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("size"), &charSize, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_30: ;
				ZEPHIR_INIT_NVAR(&_45$$31);
				ZVAL_LONG(&_45$$31, 5);
				zephir_array_update_string(&definition, SL("type"), &_45$$31, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_46$$31);
				ZVAL_LONG(&_46$$31, 36);
				zephir_array_update_string(&definition, SL("size"), &_46$$31, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_31: ;
				ZEPHIR_INIT_NVAR(&_47$$32);
				ZVAL_LONG(&_47$$32, 2);
				zephir_array_update_string(&definition, SL("type"), &_47$$32, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_end: ;

			if (Z_TYPE_P(&oldColumn) == IS_NULL) {
				zephir_array_update_string(&definition, SL("first"), &__$true, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_48$$3);
			zephir_array_fetch_long(&_48$$3, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 481);
			if (ZEPHIR_IS_STRING(&_48$$3, "PRI")) {
				zephir_array_update_string(&definition, SL("primary"), &__$true, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_49$$3);
			zephir_array_fetch_long(&_49$$3, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 488);
			if (ZEPHIR_IS_STRING(&_49$$3, "YES")) {
				zephir_array_update_string(&definition, SL("notNull"), &__$false, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_50$$3);
			zephir_array_fetch_long(&_50$$3, &field, 7, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 495);
			if (ZEPHIR_IS_STRING(&_50$$3, "auto_increment")) {
				zephir_array_update_string(&definition, SL("autoIncrement"), &__$true, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_51$$3);
			zephir_array_fetch_long(&_51$$3, &field, 9, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 502);
			if (Z_TYPE_P(&_51$$3) != IS_NULL) {
				ZEPHIR_OBS_NVAR(&_52$$38);
				zephir_array_fetch_long(&_52$$38, &field, 9, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 507);
				ZEPHIR_INIT_NVAR(&_53$$38);
				ZVAL_STRING(&_53$$38, "/^'|'?::[[:alnum:][:space:]]+$/");
				ZEPHIR_INIT_NVAR(&_54$$38);
				ZVAL_STRING(&_54$$38, "");
				ZEPHIR_CALL_FUNCTION(&_55$$38, "preg_replace", &_56, 40, &_53$$38, &_54$$38, &_52$$38);
				zephir_check_call_status();
				zephir_array_update_string(&definition, SL("default"), &_55$$38, PH_COPY | PH_SEPARATE);
				zephir_array_fetch_string(&_57$$38, &definition, SL("default"), PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 509);
				ZEPHIR_INIT_NVAR(&_53$$38);
				ZVAL_STRING(&_53$$38, "null");
				ZEPHIR_CALL_FUNCTION(&_58$$38, "strcasecmp", &_59, 38, &_57$$38, &_53$$38);
				zephir_check_call_status();
				if (ZEPHIR_IS_LONG(&_58$$38, 0)) {
					zephir_array_update_string(&definition, SL("default"), &__$null, PH_COPY | PH_SEPARATE);
				}
			}
			ZEPHIR_OBS_NVAR(&_60$$3);
			zephir_array_fetch_long(&_60$$3, &field, 10, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 517);
			if (Z_TYPE_P(&_60$$3) != IS_NULL) {
				ZEPHIR_OBS_NVAR(&_61$$40);
				zephir_array_fetch_long(&_61$$40, &field, 10, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 518);
				zephir_array_update_string(&definition, SL("comment"), &_61$$40, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&columnName);
			zephir_array_fetch_long(&columnName, &field, 0, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 524);
			ZEPHIR_INIT_NVAR(&_62$$3);
			object_init_ex(&_62$$3, phalcon_db_column_ce);
			ZEPHIR_CALL_METHOD(NULL, &_62$$3, "__construct", &_63, 243, &columnName, &definition);
			zephir_check_call_status();
			zephir_array_append(&columns, &_62$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 525);
			ZEPHIR_CPY_WRT(&oldColumn, &columnName);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_65 = 1;
		while (1) {
			if (_65) {
				_65 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_64, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_64)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_66$$41);
				zephir_create_array(&_66$$41, 1, 0);
				add_assoc_long_ex(&_66$$41, SL("bindType"), 2);
				ZEPHIR_CPY_WRT(&definition, &_66$$41);
				ZEPHIR_OBS_NVAR(&columnType);
				zephir_array_fetch_long(&columnType, &field, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 182);
				ZEPHIR_OBS_NVAR(&charSize);
				zephir_array_fetch_long(&charSize, &field, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 183);
				ZEPHIR_OBS_NVAR(&numericSize);
				zephir_array_fetch_long(&numericSize, &field, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 184);
				ZEPHIR_OBS_NVAR(&numericScale);
				zephir_array_fetch_long(&numericScale, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 185);
				_67$$41 = 1;
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("boolean"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 203)) { goto zephir_switch_1_clause_0; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("bigint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 215)) { goto zephir_switch_1_clause_1; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("mediumint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 225)) { goto zephir_switch_1_clause_2; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("smallint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 235)) { goto zephir_switch_1_clause_3; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("tinyint"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 245)) { goto zephir_switch_1_clause_4; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("int"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 258)) { goto zephir_switch_1_clause_5; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("bit"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 268)) { goto zephir_switch_1_clause_6; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("enum"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 277)) { goto zephir_switch_1_clause_7; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("datetime"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 285)) { goto zephir_switch_1_clause_8; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("date"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 294)) { goto zephir_switch_1_clause_9; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("decimal"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 304)) { goto zephir_switch_1_clause_10; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("numeric"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 305)) { goto zephir_switch_1_clause_11; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("double precision"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 316)) { goto zephir_switch_1_clause_12; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("float"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 327)) { goto zephir_switch_1_clause_13; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("real"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 328)) { goto zephir_switch_1_clause_14; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("mediumblob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 339)) { goto zephir_switch_1_clause_15; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("longblob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 347)) { goto zephir_switch_1_clause_16; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("tinyblob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 355)) { goto zephir_switch_1_clause_17; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("blob"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 363)) { goto zephir_switch_1_clause_18; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("timestamp"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 371)) { goto zephir_switch_1_clause_19; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("time"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 379)) { goto zephir_switch_1_clause_20; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("jsonb"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 387)) { goto zephir_switch_1_clause_21; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("json"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 395)) { goto zephir_switch_1_clause_22; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("longtext"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 403)) { goto zephir_switch_1_clause_23; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("mediumtext"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 411)) { goto zephir_switch_1_clause_24; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("tinytext"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 419)) { goto zephir_switch_1_clause_25; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("text"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 427)) { goto zephir_switch_1_clause_26; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("varying"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 435)) { goto zephir_switch_1_clause_27; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("varchar"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 436)) { goto zephir_switch_1_clause_28; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("char"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 445)) { goto zephir_switch_1_clause_29; }
				if (_67$$41 == zephir_memnstr_str(&columnType, SL("uuid"), "phalcon/Db/Adapter/Pdo/Postgresql.zep", 454)) { goto zephir_switch_1_clause_30; }
				goto zephir_switch_1_clause_31;
				zephir_switch_1_clause_0: ;
					ZEPHIR_INIT_NVAR(&_68$$42);
					ZVAL_LONG(&_68$$42, 8);
					zephir_array_update_string(&definition, SL("type"), &_68$$42, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_69$$42);
					ZVAL_LONG(&_69$$42, 5);
					zephir_array_update_string(&definition, SL("bindType"), &_69$$42, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					ZEPHIR_INIT_NVAR(&_70$$43);
					ZVAL_LONG(&_70$$43, 14);
					zephir_array_update_string(&definition, SL("type"), &_70$$43, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_71$$43);
					ZVAL_LONG(&_71$$43, 2);
					zephir_array_update_string(&definition, SL("bindType"), &_71$$43, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_2: ;
					ZEPHIR_INIT_NVAR(&_72$$44);
					ZVAL_LONG(&_72$$44, 21);
					zephir_array_update_string(&definition, SL("type"), &_72$$44, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_73$$44);
					ZVAL_LONG(&_73$$44, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_73$$44, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_NVAR(&_74$$45);
					ZVAL_LONG(&_74$$45, 22);
					zephir_array_update_string(&definition, SL("type"), &_74$$45, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_75$$45);
					ZVAL_LONG(&_75$$45, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_75$$45, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_INIT_NVAR(&_76$$46);
					ZVAL_LONG(&_76$$46, 26);
					zephir_array_update_string(&definition, SL("type"), &_76$$46, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_77$$46);
					ZVAL_LONG(&_77$$46, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_77$$46, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_5: ;
					ZEPHIR_INIT_NVAR(&_78$$47);
					ZVAL_LONG(&_78$$47, 0);
					zephir_array_update_string(&definition, SL("type"), &_78$$47, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_79$$47);
					ZVAL_LONG(&_79$$47, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_79$$47, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_6: ;
					ZEPHIR_INIT_NVAR(&_80$$48);
					ZVAL_LONG(&_80$$48, 19);
					zephir_array_update_string(&definition, SL("type"), &_80$$48, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_7: ;
					ZEPHIR_INIT_NVAR(&_81$$49);
					ZVAL_LONG(&_81$$49, 18);
					zephir_array_update_string(&definition, SL("type"), &_81$$49, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_8: ;
					ZEPHIR_INIT_NVAR(&_82$$50);
					ZVAL_LONG(&_82$$50, 4);
					zephir_array_update_string(&definition, SL("type"), &_82$$50, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_83$$50);
					ZVAL_LONG(&_83$$50, 0);
					zephir_array_update_string(&definition, SL("size"), &_83$$50, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_9: ;
					ZEPHIR_INIT_NVAR(&_84$$51);
					ZVAL_LONG(&_84$$51, 1);
					zephir_array_update_string(&definition, SL("type"), &_84$$51, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_85$$51);
					ZVAL_LONG(&_85$$51, 0);
					zephir_array_update_string(&definition, SL("size"), &_85$$51, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_10: ;
				zephir_switch_1_clause_11: ;
					ZEPHIR_INIT_NVAR(&_86$$52);
					ZVAL_LONG(&_86$$52, 3);
					zephir_array_update_string(&definition, SL("type"), &_86$$52, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_87$$52);
					ZVAL_LONG(&_87$$52, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_87$$52, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_12: ;
					ZEPHIR_INIT_NVAR(&_88$$53);
					ZVAL_LONG(&_88$$53, 9);
					zephir_array_update_string(&definition, SL("type"), &_88$$53, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_89$$53);
					ZVAL_LONG(&_89$$53, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_89$$53, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_13: ;
				zephir_switch_1_clause_14: ;
					ZEPHIR_INIT_NVAR(&_90$$54);
					ZVAL_LONG(&_90$$54, 7);
					zephir_array_update_string(&definition, SL("type"), &_90$$54, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("size"), &numericSize, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_91$$54);
					ZVAL_LONG(&_91$$54, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_91$$54, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_15: ;
					ZEPHIR_INIT_NVAR(&_92$$55);
					ZVAL_LONG(&_92$$55, 6);
					zephir_array_update_string(&definition, SL("type"), &_92$$55, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_16: ;
					ZEPHIR_INIT_NVAR(&_93$$56);
					ZVAL_LONG(&_93$$56, 13);
					zephir_array_update_string(&definition, SL("type"), &_93$$56, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_17: ;
					ZEPHIR_INIT_NVAR(&_94$$57);
					ZVAL_LONG(&_94$$57, 10);
					zephir_array_update_string(&definition, SL("type"), &_94$$57, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_18: ;
					ZEPHIR_INIT_NVAR(&_95$$58);
					ZVAL_LONG(&_95$$58, 11);
					zephir_array_update_string(&definition, SL("type"), &_95$$58, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_19: ;
					ZEPHIR_INIT_NVAR(&_96$$59);
					ZVAL_LONG(&_96$$59, 17);
					zephir_array_update_string(&definition, SL("type"), &_96$$59, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_20: ;
					ZEPHIR_INIT_NVAR(&_97$$60);
					ZVAL_LONG(&_97$$60, 20);
					zephir_array_update_string(&definition, SL("type"), &_97$$60, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_21: ;
					ZEPHIR_INIT_NVAR(&_98$$61);
					ZVAL_LONG(&_98$$61, 16);
					zephir_array_update_string(&definition, SL("type"), &_98$$61, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_22: ;
					ZEPHIR_INIT_NVAR(&_99$$62);
					ZVAL_LONG(&_99$$62, 15);
					zephir_array_update_string(&definition, SL("type"), &_99$$62, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_23: ;
					ZEPHIR_INIT_NVAR(&_100$$63);
					ZVAL_LONG(&_100$$63, 24);
					zephir_array_update_string(&definition, SL("type"), &_100$$63, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_24: ;
					ZEPHIR_INIT_NVAR(&_101$$64);
					ZVAL_LONG(&_101$$64, 23);
					zephir_array_update_string(&definition, SL("type"), &_101$$64, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_25: ;
					ZEPHIR_INIT_NVAR(&_102$$65);
					ZVAL_LONG(&_102$$65, 25);
					zephir_array_update_string(&definition, SL("type"), &_102$$65, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_26: ;
					ZEPHIR_INIT_NVAR(&_103$$66);
					ZVAL_LONG(&_103$$66, 6);
					zephir_array_update_string(&definition, SL("type"), &_103$$66, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_27: ;
				zephir_switch_1_clause_28: ;
					ZEPHIR_INIT_NVAR(&_104$$67);
					ZVAL_LONG(&_104$$67, 2);
					zephir_array_update_string(&definition, SL("type"), &_104$$67, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("size"), &charSize, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_29: ;
					ZEPHIR_INIT_NVAR(&_105$$68);
					ZVAL_LONG(&_105$$68, 5);
					zephir_array_update_string(&definition, SL("type"), &_105$$68, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("size"), &charSize, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_30: ;
					ZEPHIR_INIT_NVAR(&_106$$69);
					ZVAL_LONG(&_106$$69, 5);
					zephir_array_update_string(&definition, SL("type"), &_106$$69, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_107$$69);
					ZVAL_LONG(&_107$$69, 36);
					zephir_array_update_string(&definition, SL("size"), &_107$$69, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_31: ;
					ZEPHIR_INIT_NVAR(&_108$$70);
					ZVAL_LONG(&_108$$70, 2);
					zephir_array_update_string(&definition, SL("type"), &_108$$70, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_end: ;

				if (Z_TYPE_P(&oldColumn) == IS_NULL) {
					zephir_array_update_string(&definition, SL("first"), &__$true, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_109$$41);
				zephir_array_fetch_long(&_109$$41, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 481);
				if (ZEPHIR_IS_STRING(&_109$$41, "PRI")) {
					zephir_array_update_string(&definition, SL("primary"), &__$true, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_110$$41);
				zephir_array_fetch_long(&_110$$41, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 488);
				if (ZEPHIR_IS_STRING(&_110$$41, "YES")) {
					zephir_array_update_string(&definition, SL("notNull"), &__$false, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_111$$41);
				zephir_array_fetch_long(&_111$$41, &field, 7, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 495);
				if (ZEPHIR_IS_STRING(&_111$$41, "auto_increment")) {
					zephir_array_update_string(&definition, SL("autoIncrement"), &__$true, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_112$$41);
				zephir_array_fetch_long(&_112$$41, &field, 9, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 502);
				if (Z_TYPE_P(&_112$$41) != IS_NULL) {
					ZEPHIR_OBS_NVAR(&_113$$76);
					zephir_array_fetch_long(&_113$$76, &field, 9, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 507);
					ZEPHIR_INIT_NVAR(&_114$$76);
					ZVAL_STRING(&_114$$76, "/^'|'?::[[:alnum:][:space:]]+$/");
					ZEPHIR_INIT_NVAR(&_115$$76);
					ZVAL_STRING(&_115$$76, "");
					ZEPHIR_CALL_FUNCTION(&_116$$76, "preg_replace", &_56, 40, &_114$$76, &_115$$76, &_113$$76);
					zephir_check_call_status();
					zephir_array_update_string(&definition, SL("default"), &_116$$76, PH_COPY | PH_SEPARATE);
					zephir_array_fetch_string(&_117$$76, &definition, SL("default"), PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 509);
					ZEPHIR_INIT_NVAR(&_114$$76);
					ZVAL_STRING(&_114$$76, "null");
					ZEPHIR_CALL_FUNCTION(&_118$$76, "strcasecmp", &_59, 38, &_117$$76, &_114$$76);
					zephir_check_call_status();
					if (ZEPHIR_IS_LONG(&_118$$76, 0)) {
						zephir_array_update_string(&definition, SL("default"), &__$null, PH_COPY | PH_SEPARATE);
					}
				}
				ZEPHIR_OBS_NVAR(&_119$$41);
				zephir_array_fetch_long(&_119$$41, &field, 10, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 517);
				if (Z_TYPE_P(&_119$$41) != IS_NULL) {
					ZEPHIR_OBS_NVAR(&_120$$78);
					zephir_array_fetch_long(&_120$$78, &field, 10, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 518);
					zephir_array_update_string(&definition, SL("comment"), &_120$$78, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&columnName);
				zephir_array_fetch_long(&columnName, &field, 0, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 524);
				ZEPHIR_INIT_NVAR(&_121$$41);
				object_init_ex(&_121$$41, phalcon_db_column_ce);
				ZEPHIR_CALL_METHOD(NULL, &_121$$41, "__construct", &_63, 243, &columnName, &definition);
				zephir_check_call_status();
				zephir_array_append(&columns, &_121$$41, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 525);
				ZEPHIR_CPY_WRT(&oldColumn, &columnName);
		}
	}
	ZEPHIR_INIT_NVAR(&field);
	RETURN_CCTOR(&columns);
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
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, describeReferences)
{
	zval _15$$3, _26$$6, _33$$9;
	zend_ulong _30;
	zend_bool _17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_35 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, references, reference, arrayReference, constraintName, referenceObjects, name, referencedSchema, referencedTable, columns, referencedColumns, referenceUpdate, referenceDelete, _0, _1, _2, _3, *_4, _5, *_6, _16, *_27, _28, *_29, _7$$5, _8$$5, _9$$5, _10$$5, _11$$5, _12$$5, _13$$3, _14$$3, _18$$8, _19$$8, _20$$8, _21$$8, _22$$8, _23$$8, _24$$6, _25$$6, _32$$9, _34$$9;
	zend_string *table = NULL, *schema = NULL, *_31;
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
	ZVAL_UNDEF(&referenceUpdate);
	ZVAL_UNDEF(&referenceDelete);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
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
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$6);
	ZVAL_UNDEF(&_25$$6);
	ZVAL_UNDEF(&_32$$9);
	ZVAL_UNDEF(&_34$$9);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_26$$6);
	ZVAL_UNDEF(&_33$$9);
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
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 408, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 581);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&reference);
			ZVAL_COPY(&reference, _6);
			ZEPHIR_OBS_NVAR(&constraintName);
			zephir_array_fetch_long(&constraintName, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 550);
			if (!(zephir_array_isset_value(&references, &constraintName))) {
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_long(&referencedSchema, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 553);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_long(&referencedTable, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 554);
				ZEPHIR_OBS_NVAR(&referenceUpdate);
				zephir_array_fetch_long(&referenceUpdate, &reference, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 555);
				ZEPHIR_OBS_NVAR(&referenceDelete);
				zephir_array_fetch_long(&referenceDelete, &reference, 7, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 556);
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
				ZEPHIR_INIT_NVAR(&referencedColumns);
				array_init(&referencedColumns);
			} else {
				zephir_array_fetch(&_7$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 560);
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_string(&referencedSchema, &_7$$5, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 560);
				zephir_array_fetch(&_8$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 561);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_string(&referencedTable, &_8$$5, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 561);
				zephir_array_fetch(&_9$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 562);
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch_string(&columns, &_9$$5, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 562);
				zephir_array_fetch(&_10$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 563);
				ZEPHIR_OBS_NVAR(&referencedColumns);
				zephir_array_fetch_string(&referencedColumns, &_10$$5, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 563);
				zephir_array_fetch(&_11$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 564);
				ZEPHIR_OBS_NVAR(&referenceUpdate);
				zephir_array_fetch_string(&referenceUpdate, &_11$$5, SL("onUpdate"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 564);
				zephir_array_fetch(&_12$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 565);
				ZEPHIR_OBS_NVAR(&referenceDelete);
				zephir_array_fetch_string(&referenceDelete, &_12$$5, SL("onDelete"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 565);
			}
			ZEPHIR_OBS_NVAR(&_13$$3);
			zephir_array_fetch_long(&_13$$3, &reference, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 568);
			zephir_array_append(&columns, &_13$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 568);
			ZEPHIR_OBS_NVAR(&_14$$3);
			zephir_array_fetch_long(&_14$$3, &reference, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 569);
			zephir_array_append(&referencedColumns, &_14$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 569);
			ZEPHIR_INIT_NVAR(&_15$$3);
			zephir_create_array(&_15$$3, 6, 0);
			zephir_array_update_string(&_15$$3, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("onUpdate"), &referenceUpdate, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_15$$3, SL("onDelete"), &referenceDelete, PH_COPY | PH_SEPARATE);
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
			ZEPHIR_CALL_METHOD(&reference, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&constraintName);
				zephir_array_fetch_long(&constraintName, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 550);
				if (!(zephir_array_isset_value(&references, &constraintName))) {
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_long(&referencedSchema, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 553);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_long(&referencedTable, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 554);
					ZEPHIR_OBS_NVAR(&referenceUpdate);
					zephir_array_fetch_long(&referenceUpdate, &reference, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 555);
					ZEPHIR_OBS_NVAR(&referenceDelete);
					zephir_array_fetch_long(&referenceDelete, &reference, 7, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 556);
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
					ZEPHIR_INIT_NVAR(&referencedColumns);
					array_init(&referencedColumns);
				} else {
					zephir_array_fetch(&_18$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 560);
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_string(&referencedSchema, &_18$$8, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 560);
					zephir_array_fetch(&_19$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 561);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_string(&referencedTable, &_19$$8, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 561);
					zephir_array_fetch(&_20$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 562);
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch_string(&columns, &_20$$8, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 562);
					zephir_array_fetch(&_21$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 563);
					ZEPHIR_OBS_NVAR(&referencedColumns);
					zephir_array_fetch_string(&referencedColumns, &_21$$8, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 563);
					zephir_array_fetch(&_22$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 564);
					ZEPHIR_OBS_NVAR(&referenceUpdate);
					zephir_array_fetch_string(&referenceUpdate, &_22$$8, SL("onUpdate"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 564);
					zephir_array_fetch(&_23$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 565);
					ZEPHIR_OBS_NVAR(&referenceDelete);
					zephir_array_fetch_string(&referenceDelete, &_23$$8, SL("onDelete"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 565);
				}
				ZEPHIR_OBS_NVAR(&_24$$6);
				zephir_array_fetch_long(&_24$$6, &reference, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 568);
				zephir_array_append(&columns, &_24$$6, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 568);
				ZEPHIR_OBS_NVAR(&_25$$6);
				zephir_array_fetch_long(&_25$$6, &reference, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 569);
				zephir_array_append(&referencedColumns, &_25$$6, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 569);
				ZEPHIR_INIT_NVAR(&_26$$6);
				zephir_create_array(&_26$$6, 6, 0);
				zephir_array_update_string(&_26$$6, SL("referencedSchema"), &referencedSchema, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_26$$6, SL("referencedTable"), &referencedTable, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_26$$6, SL("columns"), &columns, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_26$$6, SL("referencedColumns"), &referencedColumns, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_26$$6, SL("onUpdate"), &referenceUpdate, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_26$$6, SL("onDelete"), &referenceDelete, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&references, &constraintName, &_26$$6, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&reference);
	ZEPHIR_INIT_VAR(&referenceObjects);
	array_init(&referenceObjects);
	if (Z_TYPE_P(&references) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_28);
		zephir_string_to_char_array(&_28, &references);
		_27 = &_28;
	} else {
		_27 = &references;
	}
	zephir_is_iterable(_27, 0, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 597);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_27), _30, _31, _29)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_31 != NULL) { 
			ZVAL_STR_COPY(&name, _31);
		} else {
			ZVAL_LONG(&name, _30);
		}
		ZEPHIR_INIT_NVAR(&arrayReference);
		ZVAL_COPY(&arrayReference, _29);
		ZEPHIR_INIT_NVAR(&_32$$9);
		object_init_ex(&_32$$9, phalcon_db_reference_ce);
		ZEPHIR_INIT_NVAR(&_33$$9);
		zephir_create_array(&_33$$9, 6, 0);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 587);
		zephir_array_update_string(&_33$$9, SL("referencedSchema"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 588);
		zephir_array_update_string(&_33$$9, SL("referencedTable"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 589);
		zephir_array_update_string(&_33$$9, SL("columns"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 590);
		zephir_array_update_string(&_33$$9, SL("referencedColumns"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("onUpdate"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 591);
		zephir_array_update_string(&_33$$9, SL("onUpdate"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("onDelete"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 593);
		zephir_array_update_string(&_33$$9, SL("onDelete"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, &_32$$9, "__construct", &_35, 34, &name, &_33$$9);
		zephir_check_call_status();
		zephir_array_update_zval(&referenceObjects, &name, &_32$$9, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&arrayReference);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&referenceObjects);
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
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, getDefaultIdValue)
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
 * Modifies a table column based on a definition
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, modifyColumn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, *currentColumn = NULL, currentColumn_sub, __$null, sql, queries, query, exception, _0, *_1$$4, _2$$4, *_3$$4, _4$$5, _6$$3, _7$$9, _8$$9, _9$$9;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&currentColumn_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&queries);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&exception);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_9$$9);
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
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 408, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&sql, &_0, "modifyColumn", NULL, 0, &tableName_zv, &schemaName_zv, column, currentColumn);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&queries);
	zephir_fast_explode_str(&queries, SL(";"), &sql, NULL);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_fast_count_int(&queries) > 1) {

		/* try_start_1: */

			ZEPHIR_CALL_METHOD(NULL, this_ptr, "begin", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			if (Z_TYPE_P(&queries) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_2$$4);
				zephir_string_to_char_array(&_2$$4, &queries);
				_1$$4 = &_2$$4;
			} else {
				_1$$4 = &queries;
			}
			zephir_is_iterable(_1$$4, 0, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 653);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1$$4), _3$$4)
			{
				ZEPHIR_INIT_NVAR(&query);
				ZVAL_COPY(&query, _3$$4);
				if (ZEPHIR_IS_EMPTY(&query)) {
					continue;
				}
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZEPHIR_CONCAT_VS(&_4$$5, &query, ";");
				if (UNEXPECTED(EG(exception))) {
					goto try_end_1;
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "query", &_5, 0, &_4$$5);
				zephir_check_call_status_or_jump(try_end_1);
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&query);
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "commit", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
			RETURN_MM();

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_VAR(&_6$$3);
			ZVAL_OBJ(&_6$$3, EG(exception));
			Z_ADDREF_P(&_6$$3);
			if (zephir_is_instance_of(&_6$$3, SL("Throwable"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&exception, &_6$$3);
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "rollback", NULL, 0);
				zephir_check_call_status();
				zephir_throw_exception_debug(&exception, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 657);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	} else {
		ZEPHIR_INIT_VAR(&_7$$9);
		if (!(ZEPHIR_IS_EMPTY(&sql))) {
			zephir_memory_observe(&_8$$9);
			zephir_array_fetch_long(&_8$$9, &queries, 0, PH_NOISY, "phalcon/Db/Adapter/Pdo/Postgresql.zep", 660);
			ZEPHIR_INIT_VAR(&_9$$9);
			ZEPHIR_CONCAT_VS(&_9$$9, &_8$$9, ";");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_7$$9, this_ptr, "execute", NULL, 0, &_9$$9);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&_7$$9);
			ZVAL_BOOL(&_7$$9, 1);
		}
		RETURN_CCTOR(&_7$$9);
	}
	RETURN_MM_BOOL(1);
}

/**
 * Check whether the database system requires a sequence to produce
 * auto-numeric values
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, supportSequences)
{

	RETURN_BOOL(1);
}

/**
 * Check whether the database system requires an explicit value for identity
 * columns
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, useExplicitIdValue)
{

	RETURN_BOOL(1);
}

/**
 * Returns PDO adapter DSN defaults as a key-value map.
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Postgresql, getDsnDefaults)
{

	array_init(return_value);
	return;
}

