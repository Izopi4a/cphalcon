
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
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "ext/spl/spl_exceptions.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Generates database specific SQL for the PostgreSQL RDBMS
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Dialect_Postgresql)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Dialect, Postgresql, phalcon, db_dialect_postgresql, phalcon_db_dialect_ce, phalcon_db_dialect_postgresql_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_dialect_postgresql_ce, SL("escapeChar"), "\"", ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Generates SQL to add a column to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, addColumn)
{
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, columnDefinition, _0, _1, _2, _3, _4, _7, _5$$3, _6$$3;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&columnDefinition);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&sql);
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
	ZEPHIR_CALL_METHOD(&columnDefinition, this_ptr, "getColumnDefinition", NULL, 0, column);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "ALTER TABLE ", &_0, " ADD COLUMN ");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&sql, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, column, "getName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SVSV(&_3, "\"", &_2, "\" ", &columnDefinition);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_4, column, "hasDefault", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_4)) {
		ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "castDefault", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$3);
		ZEPHIR_CONCAT_SV(&_6$$3, " DEFAULT ", &_5$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_6$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_7, column, "isNotNull", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_7)) {
		zephir_concat_self_str(&sql, " NOT NULL", sizeof(" NOT NULL") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		zephir_concat_self_str(&sql, " NULL", sizeof(" NULL") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to add an index to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, addForeignKey)
{
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *reference, reference_sub, onDelete, onUpdate, _0, _1, _2, _5, _6, _7, _8, _9, _10, _3$$3, _4$$3, _11$$4, _12$$5;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&reference_sub);
	ZVAL_UNDEF(&onDelete);
	ZVAL_UNDEF(&onUpdate);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&sql);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "ALTER TABLE ", &_0, " ADD");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&sql, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, reference, "getName", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_CALL_METHOD(&_3$$3, reference, "getName", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SVS(&_4$$3, " CONSTRAINT \"", &_3$$3, "\"");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_4$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_6, reference, "getColumns", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "getColumnList", NULL, 57, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, reference, "getReferencedTable", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, reference, "getReferencedColumns", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, this_ptr, "getColumnList", NULL, 57, &_9);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_CONCAT_SVSSVSVS(&_10, " FOREIGN KEY (", &_5, ")", " REFERENCES \"", &_7, "\" (", &_8, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_10);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&onDelete, reference, "getOnDelete", NULL, 0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&onDelete))) {
		ZEPHIR_INIT_VAR(&_11$$4);
		ZEPHIR_CONCAT_SV(&_11$$4, " ON DELETE ", &onDelete);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_11$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&onUpdate, reference, "getOnUpdate", NULL, 0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&onUpdate))) {
		ZEPHIR_INIT_VAR(&_12$$5);
		ZEPHIR_CONCAT_SV(&_12$$5, " ON UPDATE ", &onUpdate);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_12$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to add an index to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, addIndex)
{
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *index, index_sub, indexType, _0, _2, _3, _4, _5, _6, _7, _1$$4;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&indexType);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&sql);
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
	ZEPHIR_CALL_METHOD(&_0, index, "getName", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING_IDENTICAL(&_0, "PRIMARY")) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addPrimaryKey", NULL, 0, &tableName_zv, &schemaName_zv, index);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&sql);
	ZVAL_STRING(&sql, "CREATE");
	ZEPHIR_CALL_METHOD(&indexType, index, "getType", NULL, 0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&indexType))) {
		ZEPHIR_INIT_VAR(&_1$$4);
		ZEPHIR_CONCAT_SV(&_1$$4, " ", &indexType);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_1$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_2, index, "getName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_SVSV(&_4, " INDEX \"", &_2, "\" ON ", &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_4);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_6, index, "getColumns", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "getColumnList", NULL, 57, &_6);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_7);
	ZEPHIR_CONCAT_SVS(&_7, " (", &_5, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_7);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to add the primary key to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, addPrimaryKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *index, index_sub, _0, _1, _2;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, index, "getColumns", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getColumnList", NULL, 57, &_2);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVSVS(return_value, "ALTER TABLE ", &_0, " ADD CONSTRAINT \"", &tableName_zv, "_PRIMARY\" PRIMARY KEY (", &_1, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to create a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, createTable)
{
	zend_bool _20, _51$$20, _79$$33;
	zval indexSql, indexSqlAfterCreate, columnLine, referenceSql, sql, _95;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval definition, createLines, primaryColumns;
	zval tableName_zv, schemaName_zv, *definition_param = NULL, temporary, options, table, columns, column, indexes, index, reference, references, indexName, indexType, onDelete, onUpdate, columnDefinition, *_2, _3, *_4, _19, _91, _92, _0$$5, _1$$6, _6$$7, _7$$7, _8$$7, _12$$7, _13$$7, _15$$7, _9$$8, _11$$8, _14$$11, _16$$12, _17$$12, _18$$12, _21$$13, _22$$13, _23$$13, _26$$13, _27$$13, _29$$13, _24$$14, _25$$14, _28$$17, _30$$18, _31$$18, _32$$18, _33$$19, _34$$19, *_35$$20, _36$$20, *_37$$20, _50$$20, _38$$22, _39$$22, _40$$22, _41$$24, _42$$24, _43$$24, _44$$25, _45$$25, _46$$25, _47$$25, _48$$25, _49$$25, _52$$28, _53$$28, _54$$28, _55$$30, _56$$30, _57$$30, _58$$31, _59$$31, _60$$31, _61$$31, _62$$31, _63$$31, *_64$$33, _65$$33, *_66$$33, _78$$33, _67$$34, _68$$34, _69$$34, _70$$34, _71$$34, _72$$34, _73$$34, _74$$34, _75$$34, _76$$35, _77$$36, _80$$37, _81$$37, _82$$37, _83$$37, _84$$37, _85$$37, _86$$37, _87$$37, _88$$37, _89$$38, _90$$39, _93$$40, _94$$40;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&temporary);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&indexes);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&reference);
	ZVAL_UNDEF(&references);
	ZVAL_UNDEF(&indexName);
	ZVAL_UNDEF(&indexType);
	ZVAL_UNDEF(&onDelete);
	ZVAL_UNDEF(&onUpdate);
	ZVAL_UNDEF(&columnDefinition);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_91);
	ZVAL_UNDEF(&_92);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_22$$13);
	ZVAL_UNDEF(&_23$$13);
	ZVAL_UNDEF(&_26$$13);
	ZVAL_UNDEF(&_27$$13);
	ZVAL_UNDEF(&_29$$13);
	ZVAL_UNDEF(&_24$$14);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_31$$18);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_33$$19);
	ZVAL_UNDEF(&_34$$19);
	ZVAL_UNDEF(&_36$$20);
	ZVAL_UNDEF(&_50$$20);
	ZVAL_UNDEF(&_38$$22);
	ZVAL_UNDEF(&_39$$22);
	ZVAL_UNDEF(&_40$$22);
	ZVAL_UNDEF(&_41$$24);
	ZVAL_UNDEF(&_42$$24);
	ZVAL_UNDEF(&_43$$24);
	ZVAL_UNDEF(&_44$$25);
	ZVAL_UNDEF(&_45$$25);
	ZVAL_UNDEF(&_46$$25);
	ZVAL_UNDEF(&_47$$25);
	ZVAL_UNDEF(&_48$$25);
	ZVAL_UNDEF(&_49$$25);
	ZVAL_UNDEF(&_52$$28);
	ZVAL_UNDEF(&_53$$28);
	ZVAL_UNDEF(&_54$$28);
	ZVAL_UNDEF(&_55$$30);
	ZVAL_UNDEF(&_56$$30);
	ZVAL_UNDEF(&_57$$30);
	ZVAL_UNDEF(&_58$$31);
	ZVAL_UNDEF(&_59$$31);
	ZVAL_UNDEF(&_60$$31);
	ZVAL_UNDEF(&_61$$31);
	ZVAL_UNDEF(&_62$$31);
	ZVAL_UNDEF(&_63$$31);
	ZVAL_UNDEF(&_65$$33);
	ZVAL_UNDEF(&_78$$33);
	ZVAL_UNDEF(&_67$$34);
	ZVAL_UNDEF(&_68$$34);
	ZVAL_UNDEF(&_69$$34);
	ZVAL_UNDEF(&_70$$34);
	ZVAL_UNDEF(&_71$$34);
	ZVAL_UNDEF(&_72$$34);
	ZVAL_UNDEF(&_73$$34);
	ZVAL_UNDEF(&_74$$34);
	ZVAL_UNDEF(&_75$$34);
	ZVAL_UNDEF(&_76$$35);
	ZVAL_UNDEF(&_77$$36);
	ZVAL_UNDEF(&_80$$37);
	ZVAL_UNDEF(&_81$$37);
	ZVAL_UNDEF(&_82$$37);
	ZVAL_UNDEF(&_83$$37);
	ZVAL_UNDEF(&_84$$37);
	ZVAL_UNDEF(&_85$$37);
	ZVAL_UNDEF(&_86$$37);
	ZVAL_UNDEF(&_87$$37);
	ZVAL_UNDEF(&_88$$37);
	ZVAL_UNDEF(&_89$$38);
	ZVAL_UNDEF(&_90$$39);
	ZVAL_UNDEF(&_93$$40);
	ZVAL_UNDEF(&_94$$40);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&createLines);
	ZVAL_UNDEF(&primaryColumns);
	ZVAL_UNDEF(&indexSql);
	ZVAL_UNDEF(&indexSqlAfterCreate);
	ZVAL_UNDEF(&columnLine);
	ZVAL_UNDEF(&referenceSql);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&_95);
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
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The index 'columns' is required in the definition array", "phalcon/Db/Dialect/Postgresql.zep", 134);
		return;
	}
	ZEPHIR_CALL_METHOD(&table, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&temporary);
	ZVAL_BOOL(&temporary, 0);
	zephir_memory_observe(&options);
	if (zephir_array_isset_string_fetch(&options, &definition, SL("options"), 0)) {
		ZEPHIR_OBS_NVAR(&temporary);
		zephir_array_isset_string_fetch(&temporary, &options, SL("temporary"), 0);
	}
	if (zephir_is_true(&temporary)) {
		ZEPHIR_INIT_VAR(&_0$$5);
		ZEPHIR_CONCAT_SVS(&_0$$5, "CREATE TEMPORARY TABLE ", &table, " (\n\t");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&sql, &_0$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_VAR(&_1$$6);
		ZEPHIR_CONCAT_SVS(&_1$$6, "CREATE TABLE ", &table, " (\n\t");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&sql, &_1$$6);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_INIT_VAR(&indexSqlAfterCreate);
	ZVAL_STRING(&indexSqlAfterCreate, "");
	ZEPHIR_INIT_VAR(&createLines);
	array_init(&createLines);
	ZEPHIR_INIT_VAR(&primaryColumns);
	array_init(&primaryColumns);
	if (Z_TYPE_P(&columns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &columns);
		_2 = &_3;
	} else {
		_2 = &columns;
	}
	zephir_is_iterable(_2, 0, "phalcon/Db/Dialect/Postgresql.zep", 198);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
		{
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _4);
			ZEPHIR_CALL_METHOD(&columnDefinition, this_ptr, "getColumnDefinition", &_5, 0, &column);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_6$$7, &column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_7$$7);
			ZEPHIR_CONCAT_SVSV(&_7$$7, "\"", &_6$$7, "\" ", &columnDefinition);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&columnLine, &_7$$7);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_8$$7, &column, "hasDefault", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_8$$7)) {
				ZEPHIR_CALL_METHOD(&_9$$8, this_ptr, "castDefault", &_10, 0, &column);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_11$$8);
				ZEPHIR_CONCAT_SV(&_11$$8, " DEFAULT ", &_9$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&columnLine, &_11$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_CALL_METHOD(&_12$$7, &column, "isNotNull", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_12$$7)) {
				zephir_concat_self_str(&columnLine, " NOT NULL", sizeof(" NOT NULL") - 1);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				zephir_concat_self_str(&columnLine, " NULL", sizeof(" NULL") - 1);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_CALL_METHOD(&_13$$7, &column, "isPrimary", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_13$$7)) {
				ZEPHIR_CALL_METHOD(&_14$$11, &column, "getName", NULL, 0);
				zephir_check_call_status();
				zephir_array_append(&primaryColumns, &_14$$11, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 185);
			}
			zephir_array_append(&createLines, &columnLine, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 188);
			ZEPHIR_CALL_METHOD(&_15$$7, &column, "getComment", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_15$$7)) {
				ZEPHIR_CALL_METHOD(&_16$$12, &column, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_17$$12, &column, "getComment", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_18$$12);
				ZEPHIR_CONCAT_SVSVSVS(&_18$$12, " COMMENT ON COLUMN ", &table, ".\"", &_16$$12, "\" IS '", &_17$$12, "';");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&indexSqlAfterCreate, &_18$$12);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
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
			ZEPHIR_CALL_METHOD(&column, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&columnDefinition, this_ptr, "getColumnDefinition", &_5, 0, &column);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_21$$13, &column, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_22$$13);
				ZEPHIR_CONCAT_SVSV(&_22$$13, "\"", &_21$$13, "\" ", &columnDefinition);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_get_strval(&columnLine, &_22$$13);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_23$$13, &column, "hasDefault", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_23$$13)) {
					ZEPHIR_CALL_METHOD(&_24$$14, this_ptr, "castDefault", &_10, 0, &column);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_25$$14);
					ZEPHIR_CONCAT_SV(&_25$$14, " DEFAULT ", &_24$$14);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&columnLine, &_25$$14);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&_26$$13, &column, "isNotNull", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_26$$13)) {
					zephir_concat_self_str(&columnLine, " NOT NULL", sizeof(" NOT NULL") - 1);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					zephir_concat_self_str(&columnLine, " NULL", sizeof(" NULL") - 1);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&_27$$13, &column, "isPrimary", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_27$$13)) {
					ZEPHIR_CALL_METHOD(&_28$$17, &column, "getName", NULL, 0);
					zephir_check_call_status();
					zephir_array_append(&primaryColumns, &_28$$17, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 185);
				}
				zephir_array_append(&createLines, &columnLine, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 188);
				ZEPHIR_CALL_METHOD(&_29$$13, &column, "getComment", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_29$$13)) {
					ZEPHIR_CALL_METHOD(&_30$$18, &column, "getName", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_31$$18, &column, "getComment", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_32$$18);
					ZEPHIR_CONCAT_SVSVSVS(&_32$$18, " COMMENT ON COLUMN ", &table, ".\"", &_30$$18, "\" IS '", &_31$$18, "';");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&indexSqlAfterCreate, &_32$$18);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	if (!(ZEPHIR_IS_EMPTY(&primaryColumns))) {
		ZEPHIR_CALL_METHOD(&_33$$19, this_ptr, "getColumnList", NULL, 57, &primaryColumns);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_34$$19);
		ZEPHIR_CONCAT_SVS(&_34$$19, "PRIMARY KEY (", &_33$$19, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_append(&createLines, &_34$$19, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 199);
	}
	zephir_memory_observe(&indexes);
	if (zephir_array_isset_string_fetch(&indexes, &definition, SL("indexes"), 0)) {
		if (Z_TYPE_P(&indexes) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_36$$20);
			zephir_string_to_char_array(&_36$$20, &indexes);
			_35$$20 = &_36$$20;
		} else {
			_35$$20 = &indexes;
		}
		zephir_is_iterable(_35$$20, 0, "phalcon/Db/Dialect/Postgresql.zep", 227);
		if (Z_TYPE_P(_35$$20) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_35$$20), _37$$20)
			{
				ZEPHIR_INIT_NVAR(&index);
				ZVAL_COPY(&index, _37$$20);
				ZEPHIR_CALL_METHOD(&indexName, &index, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&indexType, &index, "getType", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&indexSql);
				ZVAL_STRING(&indexSql, "");
				if (ZEPHIR_IS_STRING(&indexName, "PRIMARY")) {
					ZEPHIR_CALL_METHOD(&_39$$22, &index, "getColumns", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_38$$22, this_ptr, "getColumnList", NULL, 57, &_39$$22);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_40$$22);
					ZEPHIR_CONCAT_SVS(&_40$$22, "CONSTRAINT \"PRIMARY\" PRIMARY KEY (", &_38$$22, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_get_strval(&indexSql, &_40$$22);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					if (!(ZEPHIR_IS_EMPTY(&indexType))) {
						ZEPHIR_CALL_METHOD(&_42$$24, &index, "getColumns", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_41$$24, this_ptr, "getColumnList", NULL, 57, &_42$$24);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_43$$24);
						ZEPHIR_CONCAT_SVSVSVS(&_43$$24, "CONSTRAINT \"", &indexName, "\" ", &indexType, " (", &_41$$24, ")");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_get_strval(&indexSql, &_43$$24);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CALL_METHOD(&_44$$25, &index, "getName", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_45$$25, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_46$$25);
						ZEPHIR_CONCAT_SVSV(&_46$$25, "CREATE INDEX \"", &_44$$25, "\" ON ", &_45$$25);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&indexSqlAfterCreate, &_46$$25);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&_48$$25, &index, "getColumns", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_47$$25, this_ptr, "getColumnList", NULL, 57, &_48$$25);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_49$$25);
						ZEPHIR_CONCAT_SVS(&_49$$25, " (", &_47$$25, ");");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&indexSqlAfterCreate, &_49$$25);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
				if (!(ZEPHIR_IS_EMPTY(&indexSql))) {
					zephir_array_append(&createLines, &indexSql, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 224);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _35$$20, "rewind", NULL, 0);
			zephir_check_call_status();
			_51$$20 = 1;
			while (1) {
				if (_51$$20) {
					_51$$20 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _35$$20, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_50$$20, _35$$20, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_50$$20)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&index, _35$$20, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&indexName, &index, "getName", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&indexType, &index, "getType", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&indexSql);
					ZVAL_STRING(&indexSql, "");
					if (ZEPHIR_IS_STRING(&indexName, "PRIMARY")) {
						ZEPHIR_CALL_METHOD(&_53$$28, &index, "getColumns", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_52$$28, this_ptr, "getColumnList", NULL, 57, &_53$$28);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_54$$28);
						ZEPHIR_CONCAT_SVS(&_54$$28, "CONSTRAINT \"PRIMARY\" PRIMARY KEY (", &_52$$28, ")");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_get_strval(&indexSql, &_54$$28);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						if (!(ZEPHIR_IS_EMPTY(&indexType))) {
							ZEPHIR_CALL_METHOD(&_56$$30, &index, "getColumns", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_55$$30, this_ptr, "getColumnList", NULL, 57, &_56$$30);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_57$$30);
							ZEPHIR_CONCAT_SVSVSVS(&_57$$30, "CONSTRAINT \"", &indexName, "\" ", &indexType, " (", &_55$$30, ")");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_get_strval(&indexSql, &_57$$30);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZEPHIR_CALL_METHOD(&_58$$31, &index, "getName", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_59$$31, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_60$$31);
							ZEPHIR_CONCAT_SVSV(&_60$$31, "CREATE INDEX \"", &_58$$31, "\" ON ", &_59$$31);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&indexSqlAfterCreate, &_60$$31);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(&_62$$31, &index, "getColumns", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_61$$31, this_ptr, "getColumnList", NULL, 57, &_62$$31);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_63$$31);
							ZEPHIR_CONCAT_SVS(&_63$$31, " (", &_61$$31, ");");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&indexSqlAfterCreate, &_63$$31);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
					if (!(ZEPHIR_IS_EMPTY(&indexSql))) {
						zephir_array_append(&createLines, &indexSql, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 224);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&index);
	}
	zephir_memory_observe(&references);
	if (zephir_array_isset_string_fetch(&references, &definition, SL("references"), 0)) {
		if (Z_TYPE_P(&references) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_65$$33);
			zephir_string_to_char_array(&_65$$33, &references);
			_64$$33 = &_65$$33;
		} else {
			_64$$33 = &references;
		}
		zephir_is_iterable(_64$$33, 0, "phalcon/Db/Dialect/Postgresql.zep", 255);
		if (Z_TYPE_P(_64$$33) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_64$$33), _66$$33)
			{
				ZEPHIR_INIT_NVAR(&reference);
				ZVAL_COPY(&reference, _66$$33);
				ZEPHIR_CALL_METHOD(&_67$$34, &reference, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_69$$34, &reference, "getColumns", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_68$$34, this_ptr, "getColumnList", NULL, 57, &_69$$34);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_70$$34);
				ZEPHIR_CONCAT_SVSVS(&_70$$34, "CONSTRAINT \"", &_67$$34, "\" FOREIGN KEY (", &_68$$34, ") REFERENCES ");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_get_strval(&referenceSql, &_70$$34);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_72$$34, &reference, "getReferencedTable", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_71$$34, this_ptr, "prepareTable", NULL, 0, &_72$$34, &schemaName_zv);
				zephir_check_call_status();
				zephir_concat_self(&referenceSql, &_71$$34);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_74$$34, &reference, "getReferencedColumns", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_73$$34, this_ptr, "getColumnList", NULL, 57, &_74$$34);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_75$$34);
				ZEPHIR_CONCAT_SVS(&_75$$34, " (", &_73$$34, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&referenceSql, &_75$$34);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&onDelete, &reference, "getOnDelete", NULL, 0);
				zephir_check_call_status();
				if (!(ZEPHIR_IS_EMPTY(&onDelete))) {
					ZEPHIR_INIT_NVAR(&_76$$35);
					ZEPHIR_CONCAT_SV(&_76$$35, " ON DELETE ", &onDelete);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&referenceSql, &_76$$35);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&onUpdate, &reference, "getOnUpdate", NULL, 0);
				zephir_check_call_status();
				if (!(ZEPHIR_IS_EMPTY(&onUpdate))) {
					ZEPHIR_INIT_NVAR(&_77$$36);
					ZEPHIR_CONCAT_SV(&_77$$36, " ON UPDATE ", &onUpdate);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&referenceSql, &_77$$36);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				zephir_array_append(&createLines, &referenceSql, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 253);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _64$$33, "rewind", NULL, 0);
			zephir_check_call_status();
			_79$$33 = 1;
			while (1) {
				if (_79$$33) {
					_79$$33 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _64$$33, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_78$$33, _64$$33, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_78$$33)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&reference, _64$$33, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_80$$37, &reference, "getName", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_82$$37, &reference, "getColumns", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_81$$37, this_ptr, "getColumnList", NULL, 57, &_82$$37);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_83$$37);
					ZEPHIR_CONCAT_SVSVS(&_83$$37, "CONSTRAINT \"", &_80$$37, "\" FOREIGN KEY (", &_81$$37, ") REFERENCES ");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_get_strval(&referenceSql, &_83$$37);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_85$$37, &reference, "getReferencedTable", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_84$$37, this_ptr, "prepareTable", NULL, 0, &_85$$37, &schemaName_zv);
					zephir_check_call_status();
					zephir_concat_self(&referenceSql, &_84$$37);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_87$$37, &reference, "getReferencedColumns", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_86$$37, this_ptr, "getColumnList", NULL, 57, &_87$$37);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_88$$37);
					ZEPHIR_CONCAT_SVS(&_88$$37, " (", &_86$$37, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&referenceSql, &_88$$37);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&onDelete, &reference, "getOnDelete", NULL, 0);
					zephir_check_call_status();
					if (!(ZEPHIR_IS_EMPTY(&onDelete))) {
						ZEPHIR_INIT_NVAR(&_89$$38);
						ZEPHIR_CONCAT_SV(&_89$$38, " ON DELETE ", &onDelete);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&referenceSql, &_89$$38);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					ZEPHIR_CALL_METHOD(&onUpdate, &reference, "getOnUpdate", NULL, 0);
					zephir_check_call_status();
					if (!(ZEPHIR_IS_EMPTY(&onUpdate))) {
						ZEPHIR_INIT_NVAR(&_90$$39);
						ZEPHIR_CONCAT_SV(&_90$$39, " ON UPDATE ", &onUpdate);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&referenceSql, &_90$$39);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					zephir_array_append(&createLines, &referenceSql, PH_SEPARATE, "phalcon/Db/Dialect/Postgresql.zep", 253);
			}
		}
		ZEPHIR_INIT_NVAR(&reference);
	}
	ZEPHIR_INIT_VAR(&_91);
	zephir_fast_join_str(&_91, SL(",\n\t"), &createLines);
	ZEPHIR_INIT_VAR(&_92);
	ZEPHIR_CONCAT_VS(&_92, &_91, "\n)");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_92);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_array_isset_value_string(&definition, SL("options"))) {
		ZEPHIR_CALL_METHOD(&_93$$40, this_ptr, "getTableOptions", NULL, 0, &definition);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_94$$40);
		ZEPHIR_CONCAT_SV(&_94$$40, " ", &_93$$40);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_94$$40);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_INIT_VAR(&_95);
	ZEPHIR_CONCAT_SV(&_95, ";", &indexSqlAfterCreate);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_95);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to create a view
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, createView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval definition;
	zval viewName_zv, *definition_param = NULL, schemaName_zv, viewSql, _0;
	zend_string *viewName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&viewSql);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&definition);
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
	zephir_memory_observe(&viewSql);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&viewSql, &definition, SL("sql"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The index 'sql' is required in the definition array", "phalcon/Db/Dialect/Postgresql.zep", 276);
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &viewName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSV(return_value, "CREATE VIEW ", &_0, " AS ", &viewSql);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL describing a table
 *
 * ```php
 * print_r(
 *     $dialect->describeColumns("posts")
 * );
 * ```
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, describeColumns)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval schema;
	zval table_zv, *schema_param = NULL;
	zend_string *table = NULL;

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(table)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(schema_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		schema_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!schema_param) {
		ZEPHIR_INIT_VAR(&schema);
	} else {
		zephir_get_strval(&schema, schema_param);
	}
	if (ZEPHIR_IS_NULL(&schema)) {
		ZEPHIR_INIT_NVAR(&schema);
		ZVAL_STRING(&schema, "public");
	}
	ZEPHIR_CONCAT_SVSVS(return_value, "SELECT DISTINCT c.column_name AS Field, c.data_type AS Type, c.character_maximum_length AS Size, c.numeric_precision AS NumericSize, c.numeric_scale AS NumericScale, c.is_nullable AS Null, CASE WHEN pkc.column_name NOTNULL THEN 'PRI' ELSE '' END AS Key, CASE WHEN c.data_type LIKE '%int%' AND c.column_default LIKE '%nextval%' THEN 'auto_increment' ELSE '' END AS Extra, c.ordinal_position AS Position, c.column_default, des.description FROM information_schema.columns c LEFT JOIN ( SELECT kcu.column_name, kcu.table_name, kcu.table_schema FROM information_schema.table_constraints tc INNER JOIN information_schema.key_column_usage kcu on (kcu.constraint_name = tc.constraint_name and kcu.table_name=tc.table_name and kcu.table_schema=tc.table_schema) WHERE tc.constraint_type='PRIMARY KEY') pkc ON (c.column_name=pkc.column_name AND c.table_schema = pkc.table_schema AND c.table_name=pkc.table_name) LEFT JOIN ( SELECT objsubid, description, relname, nspname FROM pg_description JOIN pg_class ON pg_description.objoid = pg_class.oid JOIN pg_namespace ON pg_class.relnamespace = pg_namespace.oid ) des ON ( des.objsubid = C.ordinal_position AND C.table_schema = des.nspname AND C.TABLE_NAME = des.relname ) WHERE c.table_schema='", &schema, "' AND c.table_name='", &table_zv, "' ORDER BY c.ordinal_position");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to query indexes on a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, describeIndexes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval table_zv, schema_zv;
	zend_string *table = NULL, *schema = NULL;

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
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
	ZEPHIR_CONCAT_SVS(return_value, "SELECT 0 as c0, t.relname as table_name, i.relname as key_name, 3 as c3, a.attname as column_name FROM pg_class t, pg_class i, pg_index ix, pg_attribute a WHERE t.oid = ix.indrelid AND i.oid = ix.indexrelid AND a.attrelid = t.oid AND a.attnum = ANY(ix.indkey) AND t.relkind = 'r' AND t.relname = '", &table_zv, "' ORDER BY t.relname, i.relname;");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to query foreign keys on a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, describeReferences)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval schema;
	zval table_zv, *schema_param = NULL;
	zend_string *table = NULL;

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(table)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(schema_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		schema_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&table_zv);
	ZVAL_STR_COPY(&table_zv, table);
	if (!schema_param) {
		ZEPHIR_INIT_VAR(&schema);
	} else {
		zephir_get_strval(&schema, schema_param);
	}
	if (ZEPHIR_IS_NULL(&schema)) {
		ZEPHIR_INIT_NVAR(&schema);
		ZVAL_STRING(&schema, "public");
	}
	ZEPHIR_CONCAT_SVSVS(return_value, "SELECT DISTINCT tc.table_name AS TABLE_NAME, kcu.column_name AS COLUMN_NAME, tc.constraint_name AS CONSTRAINT_NAME, tc.table_catalog AS REFERENCED_TABLE_SCHEMA, ccu.table_name AS REFERENCED_TABLE_NAME, ccu.column_name AS REFERENCED_COLUMN_NAME, rc.update_rule AS UPDATE_RULE, rc.delete_rule AS DELETE_RULE FROM information_schema.table_constraints AS tc JOIN information_schema.key_column_usage AS kcu ON tc.constraint_name = kcu.constraint_name JOIN information_schema.constraint_column_usage AS ccu ON ccu.constraint_name = tc.constraint_name JOIN information_schema.referential_constraints rc ON tc.constraint_catalog = rc.constraint_catalog AND tc.constraint_schema = rc.constraint_schema AND tc.constraint_name = rc.constraint_name AND tc.constraint_type = 'FOREIGN KEY' WHERE constraint_type = 'FOREIGN KEY' AND tc.table_schema = '", &schema, "' AND tc.table_name='", &table_zv, "'");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to delete a column from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, dropColumn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, columnName_zv, _0;
	zend_string *tableName = NULL, *schemaName = NULL, *columnName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&columnName_zv);
	ZVAL_UNDEF(&_0);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " DROP COLUMN \"", &columnName_zv, "\"");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to delete a foreign key from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, dropForeignKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, referenceName_zv, _0;
	zend_string *tableName = NULL, *schemaName = NULL, *referenceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&referenceName_zv);
	ZVAL_UNDEF(&_0);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " DROP CONSTRAINT \"", &referenceName_zv, "\"");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to delete an index from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, dropIndex)
{
	zval tableName_zv, schemaName_zv, indexName_zv;
	zend_string *tableName = NULL, *schemaName = NULL, *indexName = NULL;

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&indexName_zv);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_STR(indexName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&tableName_zv, tableName);
	ZVAL_STR(&schemaName_zv, schemaName);
	ZVAL_STR(&indexName_zv, indexName);
	ZEPHIR_CONCAT_SVS(return_value, "DROP INDEX \"", &indexName_zv, "\"");
	if (UNEXPECTED(EG(exception))) {
		return;
	}
	return;
}

/**
 * Generates SQL to delete primary key from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, dropPrimaryKey)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, _0;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&_0);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " DROP CONSTRAINT \"", &tableName_zv, "_PRIMARY\"");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to drop a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, dropTable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool ifExists;
	zval tableName_zv, schemaName_zv, *ifExists_param = NULL, table;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&table);
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
	if (UNEXPECTED(Z_TYPE_P(ifExists_param) != IS_TRUE && Z_TYPE_P(ifExists_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'ifExists' must be of the type bool"));
		RETURN_MM_NULL();
	}
	ifExists = (Z_TYPE_P(ifExists_param) == IS_TRUE);
	}
	ZEPHIR_CALL_METHOD(&table, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	if (ifExists) {
		ZEPHIR_CONCAT_SV(return_value, "DROP TABLE IF EXISTS ", &table);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SV(return_value, "DROP TABLE ", &table);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to drop a view
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, dropView)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool ifExists;
	zval viewName_zv, schemaName_zv, *ifExists_param = NULL, view;
	zend_string *viewName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&view);
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
	if (UNEXPECTED(Z_TYPE_P(ifExists_param) != IS_TRUE && Z_TYPE_P(ifExists_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'ifExists' must be of the type bool"));
		RETURN_MM_NULL();
	}
	ifExists = (Z_TYPE_P(ifExists_param) == IS_TRUE);
	}
	ZEPHIR_CALL_METHOD(&view, this_ptr, "prepareTable", NULL, 0, &viewName_zv, &schemaName_zv);
	zephir_check_call_status();
	if (ifExists) {
		ZEPHIR_CONCAT_SV(return_value, "DROP VIEW IF EXISTS ", &view);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SV(return_value, "DROP VIEW ", &view);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Gets the column name in PostgreSQL
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, getColumnDefinition)
{
	zend_bool _16$$38;
	zval valueSql$$38;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column, column_sub, columnType, columnSql, typeValues, _0$$4, _1$$9, _2$$15, _3$$20, _4$$33, _5$$36, _6$$36, _7$$36, value$$38, *_8$$38, _9$$38, *_10$$38, _15$$38, _20$$38, _21$$38, _22$$38, _23$$38, _11$$39, _12$$39, _14$$39, _17$$40, _18$$40, _19$$40, _24$$41, _25$$41, _26$$41;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&columnType);
	ZVAL_UNDEF(&columnSql);
	ZVAL_UNDEF(&typeValues);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$9);
	ZVAL_UNDEF(&_2$$15);
	ZVAL_UNDEF(&_3$$20);
	ZVAL_UNDEF(&_4$$33);
	ZVAL_UNDEF(&_5$$36);
	ZVAL_UNDEF(&_6$$36);
	ZVAL_UNDEF(&_7$$36);
	ZVAL_UNDEF(&value$$38);
	ZVAL_UNDEF(&_9$$38);
	ZVAL_UNDEF(&_15$$38);
	ZVAL_UNDEF(&_20$$38);
	ZVAL_UNDEF(&_21$$38);
	ZVAL_UNDEF(&_22$$38);
	ZVAL_UNDEF(&_23$$38);
	ZVAL_UNDEF(&_11$$39);
	ZVAL_UNDEF(&_12$$39);
	ZVAL_UNDEF(&_14$$39);
	ZVAL_UNDEF(&_17$$40);
	ZVAL_UNDEF(&_18$$40);
	ZVAL_UNDEF(&_19$$40);
	ZVAL_UNDEF(&_24$$41);
	ZVAL_UNDEF(&_25$$41);
	ZVAL_UNDEF(&_26$$41);
	ZVAL_UNDEF(&valueSql$$38);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &column);
	ZEPHIR_CALL_METHOD(&columnSql, this_ptr, "checkColumnTypeSql", NULL, 0, column);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&columnType, this_ptr, "checkColumnType", NULL, 0, column);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(&columnType, 14)) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_LONG(&columnType, 8)) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_LONG(&columnType, 5)) { goto zephir_switch_0_clause_2; }
	if (ZEPHIR_IS_LONG(&columnType, 1)) { goto zephir_switch_0_clause_3; }
	if (ZEPHIR_IS_LONG(&columnType, 4)) { goto zephir_switch_0_clause_4; }
	if (ZEPHIR_IS_LONG(&columnType, 3)) { goto zephir_switch_0_clause_5; }
	if (ZEPHIR_IS_LONG(&columnType, 7)) { goto zephir_switch_0_clause_6; }
	if (ZEPHIR_IS_LONG(&columnType, 0)) { goto zephir_switch_0_clause_7; }
	if (ZEPHIR_IS_LONG(&columnType, 22)) { goto zephir_switch_0_clause_8; }
	if (ZEPHIR_IS_LONG(&columnType, 15)) { goto zephir_switch_0_clause_9; }
	if (ZEPHIR_IS_LONG(&columnType, 16)) { goto zephir_switch_0_clause_10; }
	if (ZEPHIR_IS_LONG(&columnType, 17)) { goto zephir_switch_0_clause_11; }
	if (ZEPHIR_IS_LONG(&columnType, 6)) { goto zephir_switch_0_clause_12; }
	if (ZEPHIR_IS_LONG(&columnType, 2)) { goto zephir_switch_0_clause_13; }
	goto zephir_switch_0_clause_14;
	zephir_switch_0_clause_0: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			ZEPHIR_CALL_METHOD(&_0$$4, column, "isAutoIncrement", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_0$$4)) {
				zephir_concat_self_str(&columnSql, SL("BIGSERIAL"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				zephir_concat_self_str(&columnSql, SL("BIGINT"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("BOOLEAN"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_2: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("CHARACTER"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_1$$9, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_1$$9);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_3: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("DATE"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_4: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TIMESTAMP"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_5: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("NUMERIC"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_2$$15, this_ptr, "getColumnSizeAndScale", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_2$$15);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_6: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("FLOAT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_7: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			ZEPHIR_CALL_METHOD(&_3$$20, column, "isAutoIncrement", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_3$$20)) {
				zephir_concat_self_str(&columnSql, SL("SERIAL"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				zephir_concat_self_str(&columnSql, SL("INT"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_8: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("SMALLINT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_9: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("JSON"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_10: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("JSONB"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_11: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TIMESTAMP"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_12: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TEXT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_13: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("CHARACTER VARYING"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_4$$33, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_4$$33);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_14: ;
		if (UNEXPECTED(ZEPHIR_IS_EMPTY(&columnSql))) {
			ZEPHIR_INIT_VAR(&_5$$36);
			object_init_ex(&_5$$36, phalcon_db_exception_ce);
			ZEPHIR_CALL_METHOD(&_6$$36, column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_7$$36);
			ZEPHIR_CONCAT_SV(&_7$$36, "Unrecognized PostgreSQL data type at column ", &_6$$36);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_5$$36, "__construct", NULL, 32, &_7$$36);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_5$$36, "phalcon/Db/Dialect/Postgresql.zep", 511);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&typeValues, column, "getTypeValues", NULL, 0);
		zephir_check_call_status();
		if (!(ZEPHIR_IS_EMPTY(&typeValues))) {
			if (Z_TYPE_P(&typeValues) == IS_ARRAY) {
				ZEPHIR_INIT_VAR(&valueSql$$38);
				ZVAL_STRING(&valueSql$$38, "");
				if (Z_TYPE_P(&typeValues) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_9$$38);
					zephir_string_to_char_array(&_9$$38, &typeValues);
					_8$$38 = &_9$$38;
				} else {
					_8$$38 = &typeValues;
				}
				zephir_is_iterable(_8$$38, 0, "phalcon/Db/Dialect/Postgresql.zep", 526);
				if (Z_TYPE_P(_8$$38) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_8$$38), _10$$38)
					{
						ZEPHIR_INIT_NVAR(&value$$38);
						ZVAL_COPY(&value$$38, _10$$38);
						ZEPHIR_INIT_NVAR(&_11$$39);
						ZVAL_STRING(&_11$$39, "\'");
						ZEPHIR_CALL_FUNCTION(&_12$$39, "addcslashes", &_13, 248, &value$$38, &_11$$39);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_14$$39);
						ZEPHIR_CONCAT_SVS(&_14$$39, "'", &_12$$39, "', ");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&valueSql$$38, &_14$$39);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _8$$38, "rewind", NULL, 0);
					zephir_check_call_status();
					_16$$38 = 1;
					while (1) {
						if (_16$$38) {
							_16$$38 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _8$$38, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_15$$38, _8$$38, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_15$$38)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&value$$38, _8$$38, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_17$$40);
							ZVAL_STRING(&_17$$40, "\'");
							ZEPHIR_CALL_FUNCTION(&_18$$40, "addcslashes", &_13, 248, &value$$38, &_17$$40);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_19$$40);
							ZEPHIR_CONCAT_SVS(&_19$$40, "'", &_18$$40, "', ");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&valueSql$$38, &_19$$40);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
					}
				}
				ZEPHIR_INIT_NVAR(&value$$38);
				ZVAL_LONG(&_20$$38, 0);
				ZVAL_LONG(&_21$$38, -2);
				ZEPHIR_INIT_VAR(&_22$$38);
				zephir_substr(&_22$$38, &valueSql$$38, 0 , -2 , 0);
				ZEPHIR_INIT_VAR(&_23$$38);
				ZEPHIR_CONCAT_SVS(&_23$$38, "(", &_22$$38, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&columnSql, &_23$$38);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_INIT_VAR(&_24$$41);
				ZVAL_STRING(&_24$$41, "\'");
				ZEPHIR_CALL_FUNCTION(&_25$$41, "addcslashes", &_13, 248, &typeValues, &_24$$41);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_26$$41);
				ZEPHIR_CONCAT_SVS(&_26$$41, "('", &_25$$41, "')");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&columnSql, &_26$$41);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
	zephir_switch_0_end: ;

	RETURN_CCTOR(&columnSql);
}

/**
 * List all tables in database
 *
 * ```php
 * print_r(
 *     $dialect->listTables("blog")
 * );
 * ```
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, listTables)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *schemaName_param = NULL;
	zval schemaName;

	ZVAL_UNDEF(&schemaName);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(schemaName_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &schemaName_param);
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(&schemaName);
	} else {
		zephir_get_strval(&schemaName, schemaName_param);
	}
	if (ZEPHIR_IS_NULL(&schemaName)) {
		ZEPHIR_INIT_NVAR(&schemaName);
		ZVAL_STRING(&schemaName, "public");
	}
	ZEPHIR_CONCAT_SVS(return_value, "SELECT table_name FROM information_schema.tables WHERE table_schema = '", &schemaName, "' ORDER BY table_name");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates the SQL to list all views of a schema or user
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, listViews)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *schemaName_param = NULL;
	zval schemaName;

	ZVAL_UNDEF(&schemaName);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(schemaName_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &schemaName_param);
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(&schemaName);
	} else {
		zephir_get_strval(&schemaName, schemaName_param);
	}
	if (ZEPHIR_IS_NULL(&schemaName)) {
		ZEPHIR_INIT_NVAR(&schemaName);
		ZVAL_STRING(&schemaName, "public");
	}
	ZEPHIR_CONCAT_SVS(return_value, "SELECT viewname AS view_name FROM pg_views WHERE schemaname = '", &schemaName, "' ORDER BY view_name");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to modify a column in a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, modifyColumn)
{
	zend_bool _26$$10;
	zval sql, sqlAlterTable;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, *currentColumn = NULL, currentColumn_sub, __$null, defaultValue, columnDefinition, _0, _1, _2, _3, _7, _8, _11, _12, _18, _23, _24, _4$$4, _5$$4, _6$$4, _9$$5, _10$$5, _13$$6, _14$$7, _15$$7, _16$$8, _17$$8, _19$$9, _20$$9, _21$$9, _22$$9, _25$$10, _27$$10, _30$$10, _28$$11, _29$$11, _31$$12, _32$$13, _33$$13, _34$$14, _35$$14;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&currentColumn_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&columnDefinition);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_25$$10);
	ZVAL_UNDEF(&_27$$10);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_28$$11);
	ZVAL_UNDEF(&_29$$11);
	ZVAL_UNDEF(&_31$$12);
	ZVAL_UNDEF(&_32$$13);
	ZVAL_UNDEF(&_33$$13);
	ZVAL_UNDEF(&_34$$14);
	ZVAL_UNDEF(&_35$$14);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&sqlAlterTable);
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
		ZEPHIR_CPY_WRT(currentColumn, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(currentColumn);
	}
	ZEPHIR_INIT_VAR(&sql);
	ZVAL_STRING(&sql, "");
	ZEPHIR_CALL_METHOD(&columnDefinition, this_ptr, "getColumnDefinition", NULL, 0, column);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SV(&_1, "ALTER TABLE ", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&sqlAlterTable, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (Z_TYPE_P(currentColumn) != IS_OBJECT) {
		ZEPHIR_CPY_WRT(currentColumn, column);
	}
	ZEPHIR_CALL_METHOD(&_2, column, "getName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, currentColumn, "getName", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_2, &_3)) {
		ZEPHIR_CALL_METHOD(&_4$$4, currentColumn, "getName", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_5$$4, column, "getName", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$4);
		ZEPHIR_CONCAT_VSVSVS(&_6$$4, &sqlAlterTable, " RENAME COLUMN \"", &_4$$4, "\" TO \"", &_5$$4, "\";");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_6$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_7, column, "getType", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, currentColumn, "getType", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_7, &_8)) {
		ZEPHIR_CALL_METHOD(&_9$$5, column, "getName", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_10$$5);
		ZEPHIR_CONCAT_VSVSVS(&_10$$5, &sqlAlterTable, " ALTER COLUMN \"", &_9$$5, "\" TYPE ", &columnDefinition, ";");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_10$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_11, column, "isNotNull", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_12, currentColumn, "isNotNull", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_11, &_12)) {
		ZEPHIR_CALL_METHOD(&_13$$6, column, "isNotNull", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&_13$$6)) {
			ZEPHIR_CALL_METHOD(&_14$$7, column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_15$$7);
			ZEPHIR_CONCAT_VSVS(&_15$$7, &sqlAlterTable, " ALTER COLUMN \"", &_14$$7, "\" SET NOT NULL;");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_15$$7);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CALL_METHOD(&_16$$8, column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_17$$8);
			ZEPHIR_CONCAT_VSVS(&_17$$8, &sqlAlterTable, " ALTER COLUMN \"", &_16$$8, "\" DROP NOT NULL;");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_17$$8);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(&_18, column, "getComment", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_18)) {
		ZEPHIR_CALL_METHOD(&_19$$9, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_20$$9, column, "getName", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_21$$9, column, "getComment", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_22$$9);
		ZEPHIR_CONCAT_SVSVSVS(&_22$$9, "COMMENT ON COLUMN ", &_19$$9, ".\"", &_20$$9, "\" IS '", &_21$$9, "';");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_22$$9);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_23, column, "getDefault", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_24, currentColumn, "getDefault", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_23, &_24)) {
		ZEPHIR_CALL_METHOD(&_25$$10, column, "getDefault", NULL, 0);
		zephir_check_call_status();
		_26$$10 = ZEPHIR_IS_EMPTY(&_25$$10);
		if (_26$$10) {
			ZEPHIR_CALL_METHOD(&_27$$10, currentColumn, "getDefault", NULL, 0);
			zephir_check_call_status();
			_26$$10 = !(ZEPHIR_IS_EMPTY(&_27$$10));
		}
		if (_26$$10) {
			ZEPHIR_CALL_METHOD(&_28$$11, column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_29$$11);
			ZEPHIR_CONCAT_VSVS(&_29$$11, &sqlAlterTable, " ALTER COLUMN \"", &_28$$11, "\" DROP DEFAULT;");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_29$$11);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_30$$10, column, "hasDefault", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&_30$$10)) {
			ZEPHIR_CALL_METHOD(&defaultValue, this_ptr, "castDefault", NULL, 0, column);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_31$$12);
			zephir_fast_strtoupper(&_31$$12, &columnDefinition);
			if (zephir_memnstr_str(&_31$$12, SL("BOOLEAN"), "phalcon/Db/Dialect/Postgresql.zep", 616)) {
				ZEPHIR_CALL_METHOD(&_32$$13, column, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_33$$13);
				ZEPHIR_CONCAT_SVSV(&_33$$13, " ALTER COLUMN \"", &_32$$13, "\" SET DEFAULT ", &defaultValue);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&sql, &_33$$13);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CALL_METHOD(&_34$$14, column, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_35$$14);
				ZEPHIR_CONCAT_VSVSV(&_35$$14, &sqlAlterTable, " ALTER COLUMN \"", &_34$$14, "\" SET DEFAULT ", &defaultValue);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&sql, &_35$$14);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
	}
	RETURN_CTOR(&sql);
}

/**
 * Returns a SQL modified a shared lock statement. For now this method
 * returns the original query
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, sharedLock)
{
	zval sqlQuery_zv;
	zend_string *sqlQuery = NULL;

	ZVAL_UNDEF(&sqlQuery_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sqlQuery)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&sqlQuery_zv, sqlQuery);
	RETURN_STR(zend_string_copy(sqlQuery));
}

/**
 * Generates SQL checking for the existence of a schema.table
 *
 * ```php
 * echo $dialect->tableExists("posts", "blog");
 *
 * echo $dialect->tableExists("posts");
 * ```
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, tableExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval schemaName;
	zval tableName_zv, *schemaName_param = NULL;
	zend_string *tableName = NULL;

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(tableName)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(schemaName_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		schemaName_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(&schemaName);
	} else {
		zephir_get_strval(&schemaName, schemaName_param);
	}
	if (ZEPHIR_IS_NULL(&schemaName)) {
		ZEPHIR_INIT_NVAR(&schemaName);
		ZVAL_STRING(&schemaName, "public");
	}
	ZEPHIR_CONCAT_SVSVS(return_value, "SELECT CASE WHEN COUNT(*) > 0 THEN 1 ELSE 0 END FROM information_schema.tables WHERE table_schema = '", &schemaName, "' AND table_name='", &tableName_zv, "'");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates the SQL to describe the table creation options
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, tableOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval table_zv, schema_zv;
	zend_string *table = NULL, *schema = NULL;

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
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
	RETURN_MM_STRING("");
}

/**
 * Generates SQL to truncate a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, truncateTable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, table;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&table);
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
	if (!(ZEPHIR_IS_EMPTY(&schemaName_zv))) {
		ZEPHIR_CALL_METHOD(&table, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&table, this_ptr, "prepareTable", NULL, 0, &tableName_zv);
		zephir_check_call_status();
	}
	ZEPHIR_CONCAT_SV(return_value, "TRUNCATE TABLE ", &table);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL checking for the existence of a schema.view
 */
PHP_METHOD(Phalcon_Db_Dialect_Postgresql, viewExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval schemaName;
	zval viewName_zv, *schemaName_param = NULL;
	zend_string *viewName = NULL;

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(viewName)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(schemaName_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		schemaName_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&viewName_zv);
	ZVAL_STR_COPY(&viewName_zv, viewName);
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(&schemaName);
	} else {
		zephir_get_strval(&schemaName, schemaName_param);
	}
	if (ZEPHIR_IS_NULL(&schemaName)) {
		ZEPHIR_INIT_NVAR(&schemaName);
		ZVAL_STRING(&schemaName, "public");
	}
	ZEPHIR_CONCAT_SVSVS(return_value, "SELECT CASE WHEN COUNT(*) > 0 THEN 1 ELSE 0 END FROM pg_views WHERE viewname='", &viewName_zv, "' AND schemaname='", &schemaName, "'");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

PHP_METHOD(Phalcon_Db_Dialect_Postgresql, castDefault)
{
	zend_bool _2, _3, _4, _5;
	zval preparedValue, _6$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column, column_sub, defaultValue, columnDefinition, columnType, _0, _1, _7$$6, _8$$6, _9$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&columnDefinition);
	ZVAL_UNDEF(&columnType);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&preparedValue);
	ZVAL_UNDEF(&_6$$5);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &column);
	ZEPHIR_CALL_METHOD(&defaultValue, column, "getDefault", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&columnDefinition, this_ptr, "getColumnDefinition", NULL, 0, column);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&columnType, column, "getType", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_strtoupper(&_0, &columnDefinition);
	if (zephir_memnstr_str(&_0, SL("BOOLEAN"), "phalcon/Db/Dialect/Postgresql.zep", 699)) {
		RETURN_CCTOR(&defaultValue);
	}
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_strtoupper(&_1, &defaultValue);
	if (zephir_memnstr_str(&_1, SL("CURRENT_TIMESTAMP"), "phalcon/Db/Dialect/Postgresql.zep", 703)) {
		RETURN_MM_STRING("CURRENT_TIMESTAMP");
	}
	_2 = ZEPHIR_IS_LONG_IDENTICAL(&columnType, 0);
	if (!(_2)) {
		_2 = ZEPHIR_IS_LONG_IDENTICAL(&columnType, 14);
	}
	_3 = _2;
	if (!(_3)) {
		_3 = ZEPHIR_IS_LONG_IDENTICAL(&columnType, 3);
	}
	_4 = _3;
	if (!(_4)) {
		_4 = ZEPHIR_IS_LONG_IDENTICAL(&columnType, 7);
	}
	_5 = _4;
	if (!(_5)) {
		_5 = ZEPHIR_IS_LONG_IDENTICAL(&columnType, 9);
	}
	if (_5) {
		zephir_cast_to_string(&_6$$5, &defaultValue);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&preparedValue, &_6$$5);
	} else {
		ZEPHIR_INIT_VAR(&_7$$6);
		ZVAL_STRING(&_7$$6, "\'");
		ZEPHIR_CALL_FUNCTION(&_8$$6, "addcslashes", NULL, 248, &defaultValue, &_7$$6);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_9$$6);
		ZEPHIR_CONCAT_SVS(&_9$$6, "'", &_8$$6, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&preparedValue, &_9$$6);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CTOR(&preparedValue);
}

PHP_METHOD(Phalcon_Db_Dialect_Postgresql, getTableOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *definition_param = NULL;
	zval definition;

	ZVAL_UNDEF(&definition);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(definition, definition_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &definition_param);
	ZEPHIR_OBS_COPY_OR_DUP(&definition, definition_param);
	RETURN_MM_STRING("");
}

