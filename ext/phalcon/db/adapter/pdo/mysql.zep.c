
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/array.h"
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
 * Specific functions for the MySQL database system
 *
 *```php
 * use Phalcon\Db\Adapter\Pdo\Mysql;
 *
 * $config = [
 *     "host"     => "localhost",
 *     "dbname"   => "blog",
 *     "port"     => 3306,
 *     "username" => "sigma",
 *     "password" => "secret",
 * ];
 *
 * $connection = new Mysql($config);
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter_Pdo_Mysql)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Adapter\\Pdo, Mysql, phalcon, db_adapter_pdo_mysql, phalcon_db_adapter_pdo_abstractpdo_ce, phalcon_db_adapter_pdo_mysql_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_adapter_pdo_mysql_ce, SL("dialectType"), "mysql", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_adapter_pdo_mysql_ce, SL("type"), "mysql", ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Adds a foreign key to a table
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Mysql, addForeignKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *reference, reference_sub, foreignKeyCheck, _0, _1, _2, _3, _4;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&reference_sub);
	ZVAL_UNDEF(&foreignKeyCheck);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
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
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 410, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "getForeignKeyChecks", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&foreignKeyCheck, this_ptr, "prepare", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &foreignKeyCheck, "execute", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_2))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "DATABASE PARAMETER 'FOREIGN_KEY_CHECKS' HAS TO BE 1", "phalcon/Db/Adapter/Pdo/Mysql.zep", 66);
		return;
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 410, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_4, &_3, "addForeignKey", NULL, 0, &tableName_zv, &schemaName_zv, reference);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, 0, &_4);
	zephir_check_call_status();
	RETURN_MM();
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
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Mysql, describeColumns)
{
	zend_bool _67, _6$$3, _69$$49;
	zval definition;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_65 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, __$true, __$false, columns, columnType, fields, field, oldColumn, sizePattern, matches, matchOne, matchTwo, columnName, _0, _1, _2, *_3, _4, *_5, _66, _50$$3, _51$$3, _52$$3, _53$$3, _62$$3, _64$$3, _7$$4, _8$$4, _9$$5, _10$$5, _11$$6, _12$$6, _13$$7, _14$$7, _15$$8, _16$$8, _17$$9, _18$$9, _19$$10, _20$$11, _21$$12, _22$$13, _23$$14, _24$$14, _25$$15, _26$$15, _27$$16, _28$$17, _29$$18, _30$$19, _31$$20, _32$$21, _33$$22, _34$$23, _35$$24, _36$$25, _37$$26, _38$$27, _39$$28, _40$$29, _41$$30, _42$$31, _43$$32, _44$$32, _45$$33, _46$$33, _47$$33, _48$$35, _49$$36, _54$$43, _55$$44, _56$$44, _57$$44, _58$$45, _59$$46, _60$$47, _61$$47, _63$$48, _68$$49, _113$$49, _114$$49, _115$$49, _116$$49, _125$$49, _127$$49, _70$$50, _71$$50, _72$$51, _73$$51, _74$$52, _75$$52, _76$$53, _77$$53, _78$$54, _79$$54, _80$$55, _81$$55, _82$$56, _83$$57, _84$$58, _85$$59, _86$$60, _87$$60, _88$$61, _89$$61, _90$$62, _91$$63, _92$$64, _93$$65, _94$$66, _95$$67, _96$$68, _97$$69, _98$$70, _99$$71, _100$$72, _101$$73, _102$$74, _103$$75, _104$$76, _105$$77, _106$$78, _107$$78, _108$$79, _109$$79, _110$$79, _111$$81, _112$$82, _117$$89, _118$$90, _119$$90, _120$$90, _121$$91, _122$$92, _123$$93, _124$$93, _126$$94;
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
	ZVAL_UNDEF(&_66);
	ZVAL_UNDEF(&_50$$3);
	ZVAL_UNDEF(&_51$$3);
	ZVAL_UNDEF(&_52$$3);
	ZVAL_UNDEF(&_53$$3);
	ZVAL_UNDEF(&_62$$3);
	ZVAL_UNDEF(&_64$$3);
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
	ZVAL_UNDEF(&_22$$13);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_24$$14);
	ZVAL_UNDEF(&_25$$15);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_27$$16);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_30$$19);
	ZVAL_UNDEF(&_31$$20);
	ZVAL_UNDEF(&_32$$21);
	ZVAL_UNDEF(&_33$$22);
	ZVAL_UNDEF(&_34$$23);
	ZVAL_UNDEF(&_35$$24);
	ZVAL_UNDEF(&_36$$25);
	ZVAL_UNDEF(&_37$$26);
	ZVAL_UNDEF(&_38$$27);
	ZVAL_UNDEF(&_39$$28);
	ZVAL_UNDEF(&_40$$29);
	ZVAL_UNDEF(&_41$$30);
	ZVAL_UNDEF(&_42$$31);
	ZVAL_UNDEF(&_43$$32);
	ZVAL_UNDEF(&_44$$32);
	ZVAL_UNDEF(&_45$$33);
	ZVAL_UNDEF(&_46$$33);
	ZVAL_UNDEF(&_47$$33);
	ZVAL_UNDEF(&_48$$35);
	ZVAL_UNDEF(&_49$$36);
	ZVAL_UNDEF(&_54$$43);
	ZVAL_UNDEF(&_55$$44);
	ZVAL_UNDEF(&_56$$44);
	ZVAL_UNDEF(&_57$$44);
	ZVAL_UNDEF(&_58$$45);
	ZVAL_UNDEF(&_59$$46);
	ZVAL_UNDEF(&_60$$47);
	ZVAL_UNDEF(&_61$$47);
	ZVAL_UNDEF(&_63$$48);
	ZVAL_UNDEF(&_68$$49);
	ZVAL_UNDEF(&_113$$49);
	ZVAL_UNDEF(&_114$$49);
	ZVAL_UNDEF(&_115$$49);
	ZVAL_UNDEF(&_116$$49);
	ZVAL_UNDEF(&_125$$49);
	ZVAL_UNDEF(&_127$$49);
	ZVAL_UNDEF(&_70$$50);
	ZVAL_UNDEF(&_71$$50);
	ZVAL_UNDEF(&_72$$51);
	ZVAL_UNDEF(&_73$$51);
	ZVAL_UNDEF(&_74$$52);
	ZVAL_UNDEF(&_75$$52);
	ZVAL_UNDEF(&_76$$53);
	ZVAL_UNDEF(&_77$$53);
	ZVAL_UNDEF(&_78$$54);
	ZVAL_UNDEF(&_79$$54);
	ZVAL_UNDEF(&_80$$55);
	ZVAL_UNDEF(&_81$$55);
	ZVAL_UNDEF(&_82$$56);
	ZVAL_UNDEF(&_83$$57);
	ZVAL_UNDEF(&_84$$58);
	ZVAL_UNDEF(&_85$$59);
	ZVAL_UNDEF(&_86$$60);
	ZVAL_UNDEF(&_87$$60);
	ZVAL_UNDEF(&_88$$61);
	ZVAL_UNDEF(&_89$$61);
	ZVAL_UNDEF(&_90$$62);
	ZVAL_UNDEF(&_91$$63);
	ZVAL_UNDEF(&_92$$64);
	ZVAL_UNDEF(&_93$$65);
	ZVAL_UNDEF(&_94$$66);
	ZVAL_UNDEF(&_95$$67);
	ZVAL_UNDEF(&_96$$68);
	ZVAL_UNDEF(&_97$$69);
	ZVAL_UNDEF(&_98$$70);
	ZVAL_UNDEF(&_99$$71);
	ZVAL_UNDEF(&_100$$72);
	ZVAL_UNDEF(&_101$$73);
	ZVAL_UNDEF(&_102$$74);
	ZVAL_UNDEF(&_103$$75);
	ZVAL_UNDEF(&_104$$76);
	ZVAL_UNDEF(&_105$$77);
	ZVAL_UNDEF(&_106$$78);
	ZVAL_UNDEF(&_107$$78);
	ZVAL_UNDEF(&_108$$79);
	ZVAL_UNDEF(&_109$$79);
	ZVAL_UNDEF(&_110$$79);
	ZVAL_UNDEF(&_111$$81);
	ZVAL_UNDEF(&_112$$82);
	ZVAL_UNDEF(&_117$$89);
	ZVAL_UNDEF(&_118$$90);
	ZVAL_UNDEF(&_119$$90);
	ZVAL_UNDEF(&_120$$90);
	ZVAL_UNDEF(&_121$$91);
	ZVAL_UNDEF(&_122$$92);
	ZVAL_UNDEF(&_123$$93);
	ZVAL_UNDEF(&_124$$93);
	ZVAL_UNDEF(&_126$$94);
	ZVAL_UNDEF(&definition);
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
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 410, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(_3, 0, "phalcon/Db/Adapter/Pdo/Mysql.zep", 468);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _5);
			ZEPHIR_INIT_NVAR(&definition);
			zephir_create_array(&definition, 1, 0);
			add_assoc_long_ex(&definition, SL("bindType"), 2);
			ZEPHIR_OBS_NVAR(&columnType);
			zephir_array_fetch_long(&columnType, &field, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 121);
			_6$$3 = 1;
			if (_6$$3 == zephir_start_with_str(&columnType, SL("bigint"))) { goto zephir_switch_0_clause_0; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("mediumint"))) { goto zephir_switch_0_clause_1; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("smallint"))) { goto zephir_switch_0_clause_2; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("tinyint"))) { goto zephir_switch_0_clause_3; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("int"))) { goto zephir_switch_0_clause_4; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("bit"))) { goto zephir_switch_0_clause_5; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("enum"))) { goto zephir_switch_0_clause_6; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("datetime"))) { goto zephir_switch_0_clause_7; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("date"))) { goto zephir_switch_0_clause_8; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("decimal"))) { goto zephir_switch_0_clause_9; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("double"))) { goto zephir_switch_0_clause_10; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("float"))) { goto zephir_switch_0_clause_11; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("mediumblob"))) { goto zephir_switch_0_clause_12; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("longblob"))) { goto zephir_switch_0_clause_13; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("tinyblob"))) { goto zephir_switch_0_clause_14; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("blob"))) { goto zephir_switch_0_clause_15; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("timestamp"))) { goto zephir_switch_0_clause_16; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("time"))) { goto zephir_switch_0_clause_17; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("json"))) { goto zephir_switch_0_clause_18; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("longtext"))) { goto zephir_switch_0_clause_19; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("mediumtext"))) { goto zephir_switch_0_clause_20; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("tinytext"))) { goto zephir_switch_0_clause_21; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("text"))) { goto zephir_switch_0_clause_22; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("varchar"))) { goto zephir_switch_0_clause_23; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("char"))) { goto zephir_switch_0_clause_24; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("varbinary"))) { goto zephir_switch_0_clause_25; }
			if (_6$$3 == zephir_start_with_str(&columnType, SL("binary"))) { goto zephir_switch_0_clause_26; }
			goto zephir_switch_0_clause_27;
			zephir_switch_0_clause_0: ;
				ZEPHIR_INIT_NVAR(&_7$$4);
				ZVAL_LONG(&_7$$4, 14);
				zephir_array_update_string(&definition, SL("type"), &_7$$4, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 2);
				zephir_array_update_string(&definition, SL("bindType"), &_8$$4, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				ZEPHIR_INIT_NVAR(&_9$$5);
				ZVAL_LONG(&_9$$5, 21);
				zephir_array_update_string(&definition, SL("type"), &_9$$5, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_10$$5);
				ZVAL_LONG(&_10$$5, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_10$$5, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
				ZEPHIR_INIT_NVAR(&_11$$6);
				ZVAL_LONG(&_11$$6, 22);
				zephir_array_update_string(&definition, SL("type"), &_11$$6, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_12$$6);
				ZVAL_LONG(&_12$$6, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_12$$6, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_NVAR(&_13$$7);
				ZVAL_LONG(&_13$$7, 26);
				zephir_array_update_string(&definition, SL("type"), &_13$$7, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_14$$7);
				ZVAL_LONG(&_14$$7, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_14$$7, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_INIT_NVAR(&_15$$8);
				ZVAL_LONG(&_15$$8, 0);
				zephir_array_update_string(&definition, SL("type"), &_15$$8, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_16$$8);
				ZVAL_LONG(&_16$$8, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_16$$8, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_5: ;
				ZEPHIR_INIT_NVAR(&_17$$9);
				ZVAL_LONG(&_17$$9, 19);
				zephir_array_update_string(&definition, SL("type"), &_17$$9, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_18$$9);
				ZVAL_LONG(&_18$$9, 1);
				zephir_array_update_string(&definition, SL("bindType"), &_18$$9, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_6: ;
				ZEPHIR_INIT_NVAR(&_19$$10);
				ZVAL_LONG(&_19$$10, 18);
				zephir_array_update_string(&definition, SL("type"), &_19$$10, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_7: ;
				ZEPHIR_INIT_NVAR(&_20$$11);
				ZVAL_LONG(&_20$$11, 4);
				zephir_array_update_string(&definition, SL("type"), &_20$$11, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_8: ;
				ZEPHIR_INIT_NVAR(&_21$$12);
				ZVAL_LONG(&_21$$12, 1);
				zephir_array_update_string(&definition, SL("type"), &_21$$12, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_9: ;
				ZEPHIR_INIT_NVAR(&_22$$13);
				ZVAL_LONG(&_22$$13, 3);
				zephir_array_update_string(&definition, SL("type"), &_22$$13, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_10: ;
				ZEPHIR_INIT_NVAR(&_23$$14);
				ZVAL_LONG(&_23$$14, 9);
				zephir_array_update_string(&definition, SL("type"), &_23$$14, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_24$$14);
				ZVAL_LONG(&_24$$14, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_24$$14, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_11: ;
				ZEPHIR_INIT_NVAR(&_25$$15);
				ZVAL_LONG(&_25$$15, 7);
				zephir_array_update_string(&definition, SL("type"), &_25$$15, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_26$$15);
				ZVAL_LONG(&_26$$15, 32);
				zephir_array_update_string(&definition, SL("bindType"), &_26$$15, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_12: ;
				ZEPHIR_INIT_NVAR(&_27$$16);
				ZVAL_LONG(&_27$$16, 12);
				zephir_array_update_string(&definition, SL("type"), &_27$$16, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_13: ;
				ZEPHIR_INIT_NVAR(&_28$$17);
				ZVAL_LONG(&_28$$17, 13);
				zephir_array_update_string(&definition, SL("type"), &_28$$17, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_14: ;
				ZEPHIR_INIT_NVAR(&_29$$18);
				ZVAL_LONG(&_29$$18, 10);
				zephir_array_update_string(&definition, SL("type"), &_29$$18, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_15: ;
				ZEPHIR_INIT_NVAR(&_30$$19);
				ZVAL_LONG(&_30$$19, 11);
				zephir_array_update_string(&definition, SL("type"), &_30$$19, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_16: ;
				ZEPHIR_INIT_NVAR(&_31$$20);
				ZVAL_LONG(&_31$$20, 17);
				zephir_array_update_string(&definition, SL("type"), &_31$$20, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_17: ;
				ZEPHIR_INIT_NVAR(&_32$$21);
				ZVAL_LONG(&_32$$21, 20);
				zephir_array_update_string(&definition, SL("type"), &_32$$21, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_18: ;
				ZEPHIR_INIT_NVAR(&_33$$22);
				ZVAL_LONG(&_33$$22, 15);
				zephir_array_update_string(&definition, SL("type"), &_33$$22, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_19: ;
				ZEPHIR_INIT_NVAR(&_34$$23);
				ZVAL_LONG(&_34$$23, 24);
				zephir_array_update_string(&definition, SL("type"), &_34$$23, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_20: ;
				ZEPHIR_INIT_NVAR(&_35$$24);
				ZVAL_LONG(&_35$$24, 23);
				zephir_array_update_string(&definition, SL("type"), &_35$$24, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_21: ;
				ZEPHIR_INIT_NVAR(&_36$$25);
				ZVAL_LONG(&_36$$25, 25);
				zephir_array_update_string(&definition, SL("type"), &_36$$25, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_22: ;
				ZEPHIR_INIT_NVAR(&_37$$26);
				ZVAL_LONG(&_37$$26, 6);
				zephir_array_update_string(&definition, SL("type"), &_37$$26, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_23: ;
				ZEPHIR_INIT_NVAR(&_38$$27);
				ZVAL_LONG(&_38$$27, 2);
				zephir_array_update_string(&definition, SL("type"), &_38$$27, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_24: ;
				ZEPHIR_INIT_NVAR(&_39$$28);
				ZVAL_LONG(&_39$$28, 5);
				zephir_array_update_string(&definition, SL("type"), &_39$$28, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_25: ;
				ZEPHIR_INIT_NVAR(&_40$$29);
				ZVAL_LONG(&_40$$29, 28);
				zephir_array_update_string(&definition, SL("type"), &_40$$29, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_26: ;
				ZEPHIR_INIT_NVAR(&_41$$30);
				ZVAL_LONG(&_41$$30, 27);
				zephir_array_update_string(&definition, SL("type"), &_41$$30, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_27: ;
				ZEPHIR_INIT_NVAR(&_42$$31);
				ZVAL_LONG(&_42$$31, 2);
				zephir_array_update_string(&definition, SL("type"), &_42$$31, PH_COPY | PH_SEPARATE);
				goto zephir_switch_0_end;
			zephir_switch_0_end: ;

			if (zephir_memnstr_str(&columnType, SL("("), "phalcon/Db/Adapter/Pdo/Mysql.zep", 385)) {
				ZEPHIR_INIT_NVAR(&matches);
				ZVAL_NULL(&matches);
				zephir_array_fetch_string(&_43$$32, &definition, SL("type"), PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 388);
				if (ZEPHIR_IS_LONG(&_43$$32, 18)) {
					ZVAL_LONG(&_45$$33, 5);
					ZVAL_LONG(&_46$$33, -1);
					ZEPHIR_INIT_NVAR(&_47$$33);
					zephir_substr(&_47$$33, &columnType, 5 , -1 , 0);
					zephir_array_update_string(&definition, SL("size"), &_47$$33, PH_COPY | PH_SEPARATE);
				} else {
					ZEPHIR_INIT_NVAR(&_44$$32);
					zephir_preg_match(&_44$$32, &sizePattern, &columnType, &matches, 0, 0 , 0 );
					if (zephir_is_true(&_44$$32)) {
						ZEPHIR_OBS_NVAR(&matchOne);
						if (zephir_array_isset_long_fetch(&matchOne, &matches, 1, 0)) {
							ZEPHIR_INIT_NVAR(&_48$$35);
							ZVAL_LONG(&_48$$35, zephir_get_intval(&matchOne));
							zephir_array_update_string(&definition, SL("size"), &_48$$35, PH_COPY | PH_SEPARATE);
						}
						ZEPHIR_OBS_NVAR(&matchTwo);
						if (zephir_array_isset_long_fetch(&matchTwo, &matches, 2, 0)) {
							ZEPHIR_INIT_NVAR(&_49$$36);
							ZVAL_LONG(&_49$$36, zephir_get_intval(&matchTwo));
							zephir_array_update_string(&definition, SL("scale"), &_49$$36, PH_COPY | PH_SEPARATE);
						}
					}
				}
			}
			if (zephir_memnstr_str(&columnType, SL("unsigned"), "phalcon/Db/Adapter/Pdo/Mysql.zep", 404)) {
				zephir_array_update_string(&definition, SL("unsigned"), &__$true, PH_COPY | PH_SEPARATE);
			}
			if (Z_TYPE_P(&oldColumn) == IS_NULL) {
				zephir_array_update_string(&definition, SL("first"), &__$true, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_50$$3);
			zephir_array_fetch_long(&_50$$3, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 420);
			if (ZEPHIR_IS_STRING(&_50$$3, "PRI")) {
				zephir_array_update_string(&definition, SL("primary"), &__$true, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_51$$3);
			zephir_array_fetch_long(&_51$$3, &field, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 427);
			if (ZEPHIR_IS_STRING(&_51$$3, "YES")) {
				zephir_array_update_string(&definition, SL("notNull"), &__$false, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_52$$3);
			zephir_array_fetch_long(&_52$$3, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 434);
			if (ZEPHIR_IS_STRING(&_52$$3, "auto_increment")) {
				zephir_array_update_string(&definition, SL("autoIncrement"), &__$true, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_53$$3);
			zephir_array_fetch_long(&_53$$3, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 441);
			if (Z_TYPE_P(&_53$$3) != IS_NULL) {
				ZEPHIR_OBS_NVAR(&_54$$43);
				zephir_array_fetch_long(&_54$$43, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 442);
				if (zephir_memnstr_str(&_54$$43, SL("on update"), "phalcon/Db/Adapter/Pdo/Mysql.zep", 442)) {
					ZEPHIR_OBS_NVAR(&_55$$44);
					zephir_array_fetch_long(&_55$$44, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 443);
					ZEPHIR_OBS_NVAR(&_56$$44);
					zephir_array_fetch_long(&_56$$44, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 443);
					ZEPHIR_INIT_NVAR(&_57$$44);
					ZEPHIR_CONCAT_VSV(&_57$$44, &_55$$44, " ", &_56$$44);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&definition, SL("default"), &_57$$44, PH_COPY | PH_SEPARATE);
				} else {
					ZEPHIR_OBS_NVAR(&_58$$45);
					zephir_array_fetch_long(&_58$$45, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 445);
					zephir_array_update_string(&definition, SL("default"), &_58$$45, PH_COPY | PH_SEPARATE);
				}
			} else {
				ZEPHIR_OBS_NVAR(&_59$$46);
				zephir_array_fetch_long(&_59$$46, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 448);
				if (zephir_memnstr_str(&_59$$46, SL("on update"), "phalcon/Db/Adapter/Pdo/Mysql.zep", 448)) {
					ZEPHIR_OBS_NVAR(&_60$$47);
					zephir_array_fetch_long(&_60$$47, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 449);
					ZEPHIR_INIT_NVAR(&_61$$47);
					ZEPHIR_CONCAT_SV(&_61$$47, "NULL ", &_60$$47);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&definition, SL("default"), &_61$$47, PH_COPY | PH_SEPARATE);
				}
			}
			ZEPHIR_OBS_NVAR(&_62$$3);
			zephir_array_fetch_long(&_62$$3, &field, 8, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 456);
			if (Z_TYPE_P(&_62$$3) != IS_NULL) {
				ZEPHIR_OBS_NVAR(&_63$$48);
				zephir_array_fetch_long(&_63$$48, &field, 8, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 457);
				zephir_array_update_string(&definition, SL("comment"), &_63$$48, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&columnName);
			zephir_array_fetch_long(&columnName, &field, 0, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 463);
			ZEPHIR_INIT_NVAR(&_64$$3);
			object_init_ex(&_64$$3, phalcon_db_column_ce);
			ZEPHIR_CALL_METHOD(NULL, &_64$$3, "__construct", &_65, 246, &columnName, &definition);
			zephir_check_call_status();
			zephir_array_append(&columns, &_64$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 464);
			ZEPHIR_CPY_WRT(&oldColumn, &columnName);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_67 = 1;
		while (1) {
			if (_67) {
				_67 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_66, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_66)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_68$$49);
				zephir_create_array(&_68$$49, 1, 0);
				add_assoc_long_ex(&_68$$49, SL("bindType"), 2);
				ZEPHIR_CPY_WRT(&definition, &_68$$49);
				ZEPHIR_OBS_NVAR(&columnType);
				zephir_array_fetch_long(&columnType, &field, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 121);
				_69$$49 = 1;
				if (_69$$49 == zephir_start_with_str(&columnType, SL("bigint"))) { goto zephir_switch_1_clause_0; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("mediumint"))) { goto zephir_switch_1_clause_1; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("smallint"))) { goto zephir_switch_1_clause_2; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("tinyint"))) { goto zephir_switch_1_clause_3; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("int"))) { goto zephir_switch_1_clause_4; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("bit"))) { goto zephir_switch_1_clause_5; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("enum"))) { goto zephir_switch_1_clause_6; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("datetime"))) { goto zephir_switch_1_clause_7; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("date"))) { goto zephir_switch_1_clause_8; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("decimal"))) { goto zephir_switch_1_clause_9; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("double"))) { goto zephir_switch_1_clause_10; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("float"))) { goto zephir_switch_1_clause_11; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("mediumblob"))) { goto zephir_switch_1_clause_12; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("longblob"))) { goto zephir_switch_1_clause_13; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("tinyblob"))) { goto zephir_switch_1_clause_14; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("blob"))) { goto zephir_switch_1_clause_15; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("timestamp"))) { goto zephir_switch_1_clause_16; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("time"))) { goto zephir_switch_1_clause_17; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("json"))) { goto zephir_switch_1_clause_18; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("longtext"))) { goto zephir_switch_1_clause_19; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("mediumtext"))) { goto zephir_switch_1_clause_20; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("tinytext"))) { goto zephir_switch_1_clause_21; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("text"))) { goto zephir_switch_1_clause_22; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("varchar"))) { goto zephir_switch_1_clause_23; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("char"))) { goto zephir_switch_1_clause_24; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("varbinary"))) { goto zephir_switch_1_clause_25; }
				if (_69$$49 == zephir_start_with_str(&columnType, SL("binary"))) { goto zephir_switch_1_clause_26; }
				goto zephir_switch_1_clause_27;
				zephir_switch_1_clause_0: ;
					ZEPHIR_INIT_NVAR(&_70$$50);
					ZVAL_LONG(&_70$$50, 14);
					zephir_array_update_string(&definition, SL("type"), &_70$$50, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_71$$50);
					ZVAL_LONG(&_71$$50, 2);
					zephir_array_update_string(&definition, SL("bindType"), &_71$$50, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					ZEPHIR_INIT_NVAR(&_72$$51);
					ZVAL_LONG(&_72$$51, 21);
					zephir_array_update_string(&definition, SL("type"), &_72$$51, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_73$$51);
					ZVAL_LONG(&_73$$51, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_73$$51, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_2: ;
					ZEPHIR_INIT_NVAR(&_74$$52);
					ZVAL_LONG(&_74$$52, 22);
					zephir_array_update_string(&definition, SL("type"), &_74$$52, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_75$$52);
					ZVAL_LONG(&_75$$52, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_75$$52, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_NVAR(&_76$$53);
					ZVAL_LONG(&_76$$53, 26);
					zephir_array_update_string(&definition, SL("type"), &_76$$53, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_77$$53);
					ZVAL_LONG(&_77$$53, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_77$$53, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_INIT_NVAR(&_78$$54);
					ZVAL_LONG(&_78$$54, 0);
					zephir_array_update_string(&definition, SL("type"), &_78$$54, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_79$$54);
					ZVAL_LONG(&_79$$54, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_79$$54, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_5: ;
					ZEPHIR_INIT_NVAR(&_80$$55);
					ZVAL_LONG(&_80$$55, 19);
					zephir_array_update_string(&definition, SL("type"), &_80$$55, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_81$$55);
					ZVAL_LONG(&_81$$55, 1);
					zephir_array_update_string(&definition, SL("bindType"), &_81$$55, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_6: ;
					ZEPHIR_INIT_NVAR(&_82$$56);
					ZVAL_LONG(&_82$$56, 18);
					zephir_array_update_string(&definition, SL("type"), &_82$$56, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_7: ;
					ZEPHIR_INIT_NVAR(&_83$$57);
					ZVAL_LONG(&_83$$57, 4);
					zephir_array_update_string(&definition, SL("type"), &_83$$57, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_8: ;
					ZEPHIR_INIT_NVAR(&_84$$58);
					ZVAL_LONG(&_84$$58, 1);
					zephir_array_update_string(&definition, SL("type"), &_84$$58, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_9: ;
					ZEPHIR_INIT_NVAR(&_85$$59);
					ZVAL_LONG(&_85$$59, 3);
					zephir_array_update_string(&definition, SL("type"), &_85$$59, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_10: ;
					ZEPHIR_INIT_NVAR(&_86$$60);
					ZVAL_LONG(&_86$$60, 9);
					zephir_array_update_string(&definition, SL("type"), &_86$$60, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_87$$60);
					ZVAL_LONG(&_87$$60, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_87$$60, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_11: ;
					ZEPHIR_INIT_NVAR(&_88$$61);
					ZVAL_LONG(&_88$$61, 7);
					zephir_array_update_string(&definition, SL("type"), &_88$$61, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&definition, SL("isNumeric"), &__$true, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_89$$61);
					ZVAL_LONG(&_89$$61, 32);
					zephir_array_update_string(&definition, SL("bindType"), &_89$$61, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_12: ;
					ZEPHIR_INIT_NVAR(&_90$$62);
					ZVAL_LONG(&_90$$62, 12);
					zephir_array_update_string(&definition, SL("type"), &_90$$62, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_13: ;
					ZEPHIR_INIT_NVAR(&_91$$63);
					ZVAL_LONG(&_91$$63, 13);
					zephir_array_update_string(&definition, SL("type"), &_91$$63, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_14: ;
					ZEPHIR_INIT_NVAR(&_92$$64);
					ZVAL_LONG(&_92$$64, 10);
					zephir_array_update_string(&definition, SL("type"), &_92$$64, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_15: ;
					ZEPHIR_INIT_NVAR(&_93$$65);
					ZVAL_LONG(&_93$$65, 11);
					zephir_array_update_string(&definition, SL("type"), &_93$$65, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_16: ;
					ZEPHIR_INIT_NVAR(&_94$$66);
					ZVAL_LONG(&_94$$66, 17);
					zephir_array_update_string(&definition, SL("type"), &_94$$66, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_17: ;
					ZEPHIR_INIT_NVAR(&_95$$67);
					ZVAL_LONG(&_95$$67, 20);
					zephir_array_update_string(&definition, SL("type"), &_95$$67, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_18: ;
					ZEPHIR_INIT_NVAR(&_96$$68);
					ZVAL_LONG(&_96$$68, 15);
					zephir_array_update_string(&definition, SL("type"), &_96$$68, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_19: ;
					ZEPHIR_INIT_NVAR(&_97$$69);
					ZVAL_LONG(&_97$$69, 24);
					zephir_array_update_string(&definition, SL("type"), &_97$$69, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_20: ;
					ZEPHIR_INIT_NVAR(&_98$$70);
					ZVAL_LONG(&_98$$70, 23);
					zephir_array_update_string(&definition, SL("type"), &_98$$70, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_21: ;
					ZEPHIR_INIT_NVAR(&_99$$71);
					ZVAL_LONG(&_99$$71, 25);
					zephir_array_update_string(&definition, SL("type"), &_99$$71, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_22: ;
					ZEPHIR_INIT_NVAR(&_100$$72);
					ZVAL_LONG(&_100$$72, 6);
					zephir_array_update_string(&definition, SL("type"), &_100$$72, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_23: ;
					ZEPHIR_INIT_NVAR(&_101$$73);
					ZVAL_LONG(&_101$$73, 2);
					zephir_array_update_string(&definition, SL("type"), &_101$$73, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_24: ;
					ZEPHIR_INIT_NVAR(&_102$$74);
					ZVAL_LONG(&_102$$74, 5);
					zephir_array_update_string(&definition, SL("type"), &_102$$74, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_25: ;
					ZEPHIR_INIT_NVAR(&_103$$75);
					ZVAL_LONG(&_103$$75, 28);
					zephir_array_update_string(&definition, SL("type"), &_103$$75, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_26: ;
					ZEPHIR_INIT_NVAR(&_104$$76);
					ZVAL_LONG(&_104$$76, 27);
					zephir_array_update_string(&definition, SL("type"), &_104$$76, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_27: ;
					ZEPHIR_INIT_NVAR(&_105$$77);
					ZVAL_LONG(&_105$$77, 2);
					zephir_array_update_string(&definition, SL("type"), &_105$$77, PH_COPY | PH_SEPARATE);
					goto zephir_switch_1_end;
				zephir_switch_1_end: ;

				if (zephir_memnstr_str(&columnType, SL("("), "phalcon/Db/Adapter/Pdo/Mysql.zep", 385)) {
					ZEPHIR_INIT_NVAR(&matches);
					ZVAL_NULL(&matches);
					zephir_array_fetch_string(&_106$$78, &definition, SL("type"), PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 388);
					if (ZEPHIR_IS_LONG(&_106$$78, 18)) {
						ZVAL_LONG(&_108$$79, 5);
						ZVAL_LONG(&_109$$79, -1);
						ZEPHIR_INIT_NVAR(&_110$$79);
						zephir_substr(&_110$$79, &columnType, 5 , -1 , 0);
						zephir_array_update_string(&definition, SL("size"), &_110$$79, PH_COPY | PH_SEPARATE);
					} else {
						ZEPHIR_INIT_NVAR(&_107$$78);
						zephir_preg_match(&_107$$78, &sizePattern, &columnType, &matches, 0, 0 , 0 );
						if (zephir_is_true(&_107$$78)) {
							ZEPHIR_OBS_NVAR(&matchOne);
							if (zephir_array_isset_long_fetch(&matchOne, &matches, 1, 0)) {
								ZEPHIR_INIT_NVAR(&_111$$81);
								ZVAL_LONG(&_111$$81, zephir_get_intval(&matchOne));
								zephir_array_update_string(&definition, SL("size"), &_111$$81, PH_COPY | PH_SEPARATE);
							}
							ZEPHIR_OBS_NVAR(&matchTwo);
							if (zephir_array_isset_long_fetch(&matchTwo, &matches, 2, 0)) {
								ZEPHIR_INIT_NVAR(&_112$$82);
								ZVAL_LONG(&_112$$82, zephir_get_intval(&matchTwo));
								zephir_array_update_string(&definition, SL("scale"), &_112$$82, PH_COPY | PH_SEPARATE);
							}
						}
					}
				}
				if (zephir_memnstr_str(&columnType, SL("unsigned"), "phalcon/Db/Adapter/Pdo/Mysql.zep", 404)) {
					zephir_array_update_string(&definition, SL("unsigned"), &__$true, PH_COPY | PH_SEPARATE);
				}
				if (Z_TYPE_P(&oldColumn) == IS_NULL) {
					zephir_array_update_string(&definition, SL("first"), &__$true, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_string(&definition, SL("after"), &oldColumn, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_113$$49);
				zephir_array_fetch_long(&_113$$49, &field, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 420);
				if (ZEPHIR_IS_STRING(&_113$$49, "PRI")) {
					zephir_array_update_string(&definition, SL("primary"), &__$true, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_114$$49);
				zephir_array_fetch_long(&_114$$49, &field, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 427);
				if (ZEPHIR_IS_STRING(&_114$$49, "YES")) {
					zephir_array_update_string(&definition, SL("notNull"), &__$false, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_115$$49);
				zephir_array_fetch_long(&_115$$49, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 434);
				if (ZEPHIR_IS_STRING(&_115$$49, "auto_increment")) {
					zephir_array_update_string(&definition, SL("autoIncrement"), &__$true, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_116$$49);
				zephir_array_fetch_long(&_116$$49, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 441);
				if (Z_TYPE_P(&_116$$49) != IS_NULL) {
					ZEPHIR_OBS_NVAR(&_117$$89);
					zephir_array_fetch_long(&_117$$89, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 442);
					if (zephir_memnstr_str(&_117$$89, SL("on update"), "phalcon/Db/Adapter/Pdo/Mysql.zep", 442)) {
						ZEPHIR_OBS_NVAR(&_118$$90);
						zephir_array_fetch_long(&_118$$90, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 443);
						ZEPHIR_OBS_NVAR(&_119$$90);
						zephir_array_fetch_long(&_119$$90, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 443);
						ZEPHIR_INIT_NVAR(&_120$$90);
						ZEPHIR_CONCAT_VSV(&_120$$90, &_118$$90, " ", &_119$$90);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_update_string(&definition, SL("default"), &_120$$90, PH_COPY | PH_SEPARATE);
					} else {
						ZEPHIR_OBS_NVAR(&_121$$91);
						zephir_array_fetch_long(&_121$$91, &field, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 445);
						zephir_array_update_string(&definition, SL("default"), &_121$$91, PH_COPY | PH_SEPARATE);
					}
				} else {
					ZEPHIR_OBS_NVAR(&_122$$92);
					zephir_array_fetch_long(&_122$$92, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 448);
					if (zephir_memnstr_str(&_122$$92, SL("on update"), "phalcon/Db/Adapter/Pdo/Mysql.zep", 448)) {
						ZEPHIR_OBS_NVAR(&_123$$93);
						zephir_array_fetch_long(&_123$$93, &field, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 449);
						ZEPHIR_INIT_NVAR(&_124$$93);
						ZEPHIR_CONCAT_SV(&_124$$93, "NULL ", &_123$$93);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_update_string(&definition, SL("default"), &_124$$93, PH_COPY | PH_SEPARATE);
					}
				}
				ZEPHIR_OBS_NVAR(&_125$$49);
				zephir_array_fetch_long(&_125$$49, &field, 8, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 456);
				if (Z_TYPE_P(&_125$$49) != IS_NULL) {
					ZEPHIR_OBS_NVAR(&_126$$94);
					zephir_array_fetch_long(&_126$$94, &field, 8, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 457);
					zephir_array_update_string(&definition, SL("comment"), &_126$$94, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&columnName);
				zephir_array_fetch_long(&columnName, &field, 0, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 463);
				ZEPHIR_INIT_NVAR(&_127$$49);
				object_init_ex(&_127$$49, phalcon_db_column_ce);
				ZEPHIR_CALL_METHOD(NULL, &_127$$49, "__construct", &_65, 246, &columnName, &definition);
				zephir_check_call_status();
				zephir_array_append(&columns, &_127$$49, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 464);
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
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Mysql, describeIndexes)
{
	zend_ulong _30;
	zend_bool _17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_35 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, indexes, index, keyName, indexType, indexObjects, columns, name, _0, _1, _2, _3, *_4, _5, *_6, _16, *_27, _28, *_29, _7$$4, _8$$3, _10$$3, _11$$3, _9$$6, _12$$7, _13$$8, _14$$9, _15$$10, _18$$12, _19$$11, _21$$11, _22$$11, _20$$14, _23$$15, _24$$16, _25$$17, _26$$18, _32$$19, _33$$19, _34$$19;
	zend_string *table = NULL, *schema = NULL, *_31;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&indexes);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&keyName);
	ZVAL_UNDEF(&indexType);
	ZVAL_UNDEF(&indexObjects);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_19$$11);
	ZVAL_UNDEF(&_21$$11);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$18);
	ZVAL_UNDEF(&_32$$19);
	ZVAL_UNDEF(&_33$$19);
	ZVAL_UNDEF(&_34$$19);
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
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 410, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/Pdo/Mysql.zep", 514);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&index);
			ZVAL_COPY(&index, _6);
			ZEPHIR_OBS_NVAR(&keyName);
			zephir_array_fetch_string(&keyName, &index, SL("Key_name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 487);
			ZEPHIR_OBS_NVAR(&indexType);
			zephir_array_fetch_string(&indexType, &index, SL("Index_type"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 488);
			if (!(zephir_array_isset_value(&indexes, &keyName))) {
				ZEPHIR_INIT_NVAR(&_7$$4);
				array_init(&_7$$4);
				zephir_array_update_zval(&indexes, &keyName, &_7$$4, PH_COPY | PH_SEPARATE);
			}
			zephir_array_fetch(&_8$$3, &indexes, &keyName, PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 494);
			if (!(zephir_array_isset_value_string(&_8$$3, SL("columns")))) {
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
			} else {
				zephir_array_fetch(&_9$$6, &indexes, &keyName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 497);
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch_string(&columns, &_9$$6, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 497);
			}
			ZEPHIR_OBS_NVAR(&_10$$3);
			zephir_array_fetch_string(&_10$$3, &index, SL("Column_name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 500);
			zephir_array_append(&columns, &_10$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 500);
			zephir_array_update_multi(&indexes, &columns, SL("zs"), 3, &keyName, SL("columns"));
			if (ZEPHIR_IS_STRING(&keyName, "PRIMARY")) {
				ZEPHIR_INIT_NVAR(&_12$$7);
				ZVAL_STRING(&_12$$7, "PRIMARY");
				zephir_array_update_multi(&indexes, &_12$$7, SL("zs"), 3, &keyName, SL("type"));
			} else if (ZEPHIR_IS_STRING(&indexType, "FULLTEXT")) {
				ZEPHIR_INIT_NVAR(&_13$$8);
				ZVAL_STRING(&_13$$8, "FULLTEXT");
				zephir_array_update_multi(&indexes, &_13$$8, SL("zs"), 3, &keyName, SL("type"));
			} else {
				ZEPHIR_OBS_NVAR(&_11$$3);
				zephir_array_fetch_string(&_11$$3, &index, SL("Non_unique"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 507);
				if (ZEPHIR_IS_LONG(&_11$$3, 0)) {
					ZEPHIR_INIT_NVAR(&_14$$9);
					ZVAL_STRING(&_14$$9, "UNIQUE");
					zephir_array_update_multi(&indexes, &_14$$9, SL("zs"), 3, &keyName, SL("type"));
				} else {
					ZEPHIR_INIT_NVAR(&_15$$10);
					ZVAL_STRING(&_15$$10, "");
					zephir_array_update_multi(&indexes, &_15$$10, SL("zs"), 3, &keyName, SL("type"));
				}
			}
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
			ZEPHIR_CALL_METHOD(&index, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&keyName);
				zephir_array_fetch_string(&keyName, &index, SL("Key_name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 487);
				ZEPHIR_OBS_NVAR(&indexType);
				zephir_array_fetch_string(&indexType, &index, SL("Index_type"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 488);
				if (!(zephir_array_isset_value(&indexes, &keyName))) {
					ZEPHIR_INIT_NVAR(&_18$$12);
					array_init(&_18$$12);
					zephir_array_update_zval(&indexes, &keyName, &_18$$12, PH_COPY | PH_SEPARATE);
				}
				zephir_array_fetch(&_19$$11, &indexes, &keyName, PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 494);
				if (!(zephir_array_isset_value_string(&_19$$11, SL("columns")))) {
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
				} else {
					zephir_array_fetch(&_20$$14, &indexes, &keyName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 497);
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch_string(&columns, &_20$$14, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 497);
				}
				ZEPHIR_OBS_NVAR(&_21$$11);
				zephir_array_fetch_string(&_21$$11, &index, SL("Column_name"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 500);
				zephir_array_append(&columns, &_21$$11, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 500);
				zephir_array_update_multi(&indexes, &columns, SL("zs"), 3, &keyName, SL("columns"));
				if (ZEPHIR_IS_STRING(&keyName, "PRIMARY")) {
					ZEPHIR_INIT_NVAR(&_23$$15);
					ZVAL_STRING(&_23$$15, "PRIMARY");
					zephir_array_update_multi(&indexes, &_23$$15, SL("zs"), 3, &keyName, SL("type"));
				} else if (ZEPHIR_IS_STRING(&indexType, "FULLTEXT")) {
					ZEPHIR_INIT_NVAR(&_24$$16);
					ZVAL_STRING(&_24$$16, "FULLTEXT");
					zephir_array_update_multi(&indexes, &_24$$16, SL("zs"), 3, &keyName, SL("type"));
				} else {
					ZEPHIR_OBS_NVAR(&_22$$11);
					zephir_array_fetch_string(&_22$$11, &index, SL("Non_unique"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 507);
					if (ZEPHIR_IS_LONG(&_22$$11, 0)) {
						ZEPHIR_INIT_NVAR(&_25$$17);
						ZVAL_STRING(&_25$$17, "UNIQUE");
						zephir_array_update_multi(&indexes, &_25$$17, SL("zs"), 3, &keyName, SL("type"));
					} else {
						ZEPHIR_INIT_NVAR(&_26$$18);
						ZVAL_STRING(&_26$$18, "");
						zephir_array_update_multi(&indexes, &_26$$18, SL("zs"), 3, &keyName, SL("type"));
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&index);
	ZEPHIR_INIT_VAR(&indexObjects);
	array_init(&indexObjects);
	if (Z_TYPE_P(&indexes) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_28);
		zephir_string_to_char_array(&_28, &indexes);
		_27 = &_28;
	} else {
		_27 = &indexes;
	}
	zephir_is_iterable(_27, 0, "phalcon/Db/Adapter/Pdo/Mysql.zep", 524);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_27), _30, _31, _29)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_31 != NULL) { 
			ZVAL_STR_COPY(&name, _31);
		} else {
			ZVAL_LONG(&name, _30);
		}
		ZEPHIR_INIT_NVAR(&index);
		ZVAL_COPY(&index, _29);
		ZEPHIR_INIT_NVAR(&_32$$19);
		object_init_ex(&_32$$19, phalcon_db_index_ce);
		ZEPHIR_OBS_NVAR(&_33$$19);
		zephir_array_fetch_string(&_33$$19, &index, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 519);
		ZEPHIR_OBS_NVAR(&_34$$19);
		zephir_array_fetch_string(&_34$$19, &index, SL("type"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 521);
		ZEPHIR_CALL_METHOD(NULL, &_32$$19, "__construct", &_35, 33, &name, &_33$$19, &_34$$19);
		zephir_check_call_status();
		zephir_array_update_zval(&indexObjects, &name, &_32$$19, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&index);
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
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Mysql, describeReferences)
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
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 410, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(_4, 0, "phalcon/Db/Adapter/Pdo/Mysql.zep", 577);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&reference);
			ZVAL_COPY(&reference, _6);
			ZEPHIR_OBS_NVAR(&constraintName);
			zephir_array_fetch_long(&constraintName, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 546);
			if (!(zephir_array_isset_value(&references, &constraintName))) {
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_long(&referencedSchema, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 549);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_long(&referencedTable, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 550);
				ZEPHIR_OBS_NVAR(&referenceUpdate);
				zephir_array_fetch_long(&referenceUpdate, &reference, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 551);
				ZEPHIR_OBS_NVAR(&referenceDelete);
				zephir_array_fetch_long(&referenceDelete, &reference, 7, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 552);
				ZEPHIR_INIT_NVAR(&columns);
				array_init(&columns);
				ZEPHIR_INIT_NVAR(&referencedColumns);
				array_init(&referencedColumns);
			} else {
				zephir_array_fetch(&_7$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 556);
				ZEPHIR_OBS_NVAR(&referencedSchema);
				zephir_array_fetch_string(&referencedSchema, &_7$$5, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 556);
				zephir_array_fetch(&_8$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 557);
				ZEPHIR_OBS_NVAR(&referencedTable);
				zephir_array_fetch_string(&referencedTable, &_8$$5, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 557);
				zephir_array_fetch(&_9$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 558);
				ZEPHIR_OBS_NVAR(&columns);
				zephir_array_fetch_string(&columns, &_9$$5, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 558);
				zephir_array_fetch(&_10$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 559);
				ZEPHIR_OBS_NVAR(&referencedColumns);
				zephir_array_fetch_string(&referencedColumns, &_10$$5, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 559);
				zephir_array_fetch(&_11$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 560);
				ZEPHIR_OBS_NVAR(&referenceUpdate);
				zephir_array_fetch_string(&referenceUpdate, &_11$$5, SL("onUpdate"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 560);
				zephir_array_fetch(&_12$$5, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 561);
				ZEPHIR_OBS_NVAR(&referenceDelete);
				zephir_array_fetch_string(&referenceDelete, &_12$$5, SL("onDelete"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 561);
			}
			ZEPHIR_OBS_NVAR(&_13$$3);
			zephir_array_fetch_long(&_13$$3, &reference, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 564);
			zephir_array_append(&columns, &_13$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 564);
			ZEPHIR_OBS_NVAR(&_14$$3);
			zephir_array_fetch_long(&_14$$3, &reference, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 565);
			zephir_array_append(&referencedColumns, &_14$$3, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 565);
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
				zephir_array_fetch_long(&constraintName, &reference, 2, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 546);
				if (!(zephir_array_isset_value(&references, &constraintName))) {
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_long(&referencedSchema, &reference, 3, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 549);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_long(&referencedTable, &reference, 4, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 550);
					ZEPHIR_OBS_NVAR(&referenceUpdate);
					zephir_array_fetch_long(&referenceUpdate, &reference, 6, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 551);
					ZEPHIR_OBS_NVAR(&referenceDelete);
					zephir_array_fetch_long(&referenceDelete, &reference, 7, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 552);
					ZEPHIR_INIT_NVAR(&columns);
					array_init(&columns);
					ZEPHIR_INIT_NVAR(&referencedColumns);
					array_init(&referencedColumns);
				} else {
					zephir_array_fetch(&_18$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 556);
					ZEPHIR_OBS_NVAR(&referencedSchema);
					zephir_array_fetch_string(&referencedSchema, &_18$$8, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 556);
					zephir_array_fetch(&_19$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 557);
					ZEPHIR_OBS_NVAR(&referencedTable);
					zephir_array_fetch_string(&referencedTable, &_19$$8, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 557);
					zephir_array_fetch(&_20$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 558);
					ZEPHIR_OBS_NVAR(&columns);
					zephir_array_fetch_string(&columns, &_20$$8, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 558);
					zephir_array_fetch(&_21$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 559);
					ZEPHIR_OBS_NVAR(&referencedColumns);
					zephir_array_fetch_string(&referencedColumns, &_21$$8, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 559);
					zephir_array_fetch(&_22$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 560);
					ZEPHIR_OBS_NVAR(&referenceUpdate);
					zephir_array_fetch_string(&referenceUpdate, &_22$$8, SL("onUpdate"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 560);
					zephir_array_fetch(&_23$$8, &references, &constraintName, PH_NOISY | PH_READONLY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 561);
					ZEPHIR_OBS_NVAR(&referenceDelete);
					zephir_array_fetch_string(&referenceDelete, &_23$$8, SL("onDelete"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 561);
				}
				ZEPHIR_OBS_NVAR(&_24$$6);
				zephir_array_fetch_long(&_24$$6, &reference, 1, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 564);
				zephir_array_append(&columns, &_24$$6, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 564);
				ZEPHIR_OBS_NVAR(&_25$$6);
				zephir_array_fetch_long(&_25$$6, &reference, 5, PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 565);
				zephir_array_append(&referencedColumns, &_25$$6, PH_SEPARATE, "phalcon/Db/Adapter/Pdo/Mysql.zep", 565);
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
	zephir_is_iterable(_27, 0, "phalcon/Db/Adapter/Pdo/Mysql.zep", 592);
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
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("referencedSchema"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 582);
		zephir_array_update_string(&_33$$9, SL("referencedSchema"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("referencedTable"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 583);
		zephir_array_update_string(&_33$$9, SL("referencedTable"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("columns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 584);
		zephir_array_update_string(&_33$$9, SL("columns"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("referencedColumns"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 585);
		zephir_array_update_string(&_33$$9, SL("referencedColumns"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("onUpdate"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 586);
		zephir_array_update_string(&_33$$9, SL("onUpdate"), &_34$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_34$$9);
		zephir_array_fetch_string(&_34$$9, &arrayReference, SL("onDelete"), PH_NOISY, "phalcon/Db/Adapter/Pdo/Mysql.zep", 588);
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
 * Returns PDO adapter DSN defaults as a key-value map.
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo_Mysql, getDsnDefaults)
{

	zephir_create_array(return_value, 1, 0);
	add_assoc_stringl_ex(return_value, SL("charset"), SL("utf8mb4"));
	return;
}

