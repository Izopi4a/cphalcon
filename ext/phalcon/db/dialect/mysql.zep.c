
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
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/exception.h"
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
 * Generates database specific SQL for the MySQL RDBMS
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Dialect_Mysql)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Dialect, Mysql, phalcon, db_dialect_mysql, phalcon_db_dialect_ce, phalcon_db_dialect_mysql_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_db_dialect_mysql_ce, SL("escapeChar"), "`", ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Generates SQL to add a column to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, addColumn)
{
	zend_bool _6$$5, _7$$5, _8$$5;
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, afterPosition, defaultValue, upperDefaultValue, _0, _1, _2, _3, _4, _5, _14, _15, _9$$5, _10$$6, _11$$7, _12$$7, _13$$7, _16$$11;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&afterPosition);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&upperDefaultValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_16$$11);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, column, "getName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getColumnDefinition", NULL, 0, column);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SVSVSV(&_3, "ALTER TABLE ", &_0, " ADD `", &_1, "` ", &_2);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&sql, &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_4, column, "isNotNull", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_4)) {
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
	ZEPHIR_CALL_METHOD(&_5, column, "hasDefault", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_5)) {
		ZEPHIR_CALL_METHOD(&defaultValue, column, "getDefault", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&upperDefaultValue);
		zephir_fast_strtoupper(&upperDefaultValue, &defaultValue);
		_6$$5 = zephir_memnstr_str(&upperDefaultValue, SL("CURRENT_TIMESTAMP"), "phalcon/Db/Dialect/Mysql.zep", 54);
		if (!(_6$$5)) {
			_6$$5 = zephir_memnstr_str(&upperDefaultValue, SL("NULL"), "phalcon/Db/Dialect/Mysql.zep", 54);
		}
		_7$$5 = _6$$5;
		if (!(_7$$5)) {
			_7$$5 = Z_TYPE_P(&defaultValue) == IS_LONG;
		}
		_8$$5 = _7$$5;
		if (!(_8$$5)) {
			ZEPHIR_CALL_FUNCTION(&_9$$5, "is_float", NULL, 244, &defaultValue);
			zephir_check_call_status();
			_8$$5 = zephir_is_true(&_9$$5);
		}
		if (_8$$5) {
			ZEPHIR_INIT_VAR(&_10$$6);
			ZEPHIR_CONCAT_SV(&_10$$6, " DEFAULT ", &defaultValue);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_10$$6);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_VAR(&_11$$7);
			ZVAL_STRING(&_11$$7, "\"");
			ZEPHIR_CALL_FUNCTION(&_12$$7, "addcslashes", NULL, 245, &defaultValue, &_11$$7);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_13$$7);
			ZEPHIR_CONCAT_SVS(&_13$$7, " DEFAULT \"", &_12$$7, "\"");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_13$$7);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(&_14, column, "isAutoIncrement", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_14)) {
		zephir_concat_self_str(&sql, " AUTO_INCREMENT", sizeof(" AUTO_INCREMENT") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_15, column, "isFirst", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_15)) {
		zephir_concat_self_str(&sql, " FIRST", sizeof(" FIRST") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(&afterPosition, column, "getAfterPosition", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&afterPosition)) {
			ZEPHIR_INIT_VAR(&_16$$11);
			ZEPHIR_CONCAT_SVS(&_16$$11, " AFTER `", &afterPosition, "`");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_16$$11);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to add an index to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, addForeignKey)
{
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *reference, reference_sub, onDelete, onUpdate, _0, _1, _2, _5, _6, _7, _8, _9, _10, _11, _12, _3$$3, _4$$3, _13$$4, _14$$5;
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
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
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
		ZEPHIR_CONCAT_SVS(&_4$$3, " CONSTRAINT `", &_3$$3, "`");
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
	ZEPHIR_CALL_METHOD(&_8, reference, "getReferencedTable", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, reference, "getReferencedSchema", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "prepareTable", NULL, 0, &_8, &_9);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_11, reference, "getReferencedColumns", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_10, this_ptr, "getColumnList", NULL, 57, &_11);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_12);
	ZEPHIR_CONCAT_SVSVSVS(&_12, " FOREIGN KEY (", &_5, ") REFERENCES ", &_7, "(", &_10, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_12);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&onDelete, reference, "getOnDelete", NULL, 0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&onDelete))) {
		ZEPHIR_INIT_VAR(&_13$$4);
		ZEPHIR_CONCAT_SV(&_13$$4, " ON DELETE ", &onDelete);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_13$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&onUpdate, reference, "getOnUpdate", NULL, 0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&onUpdate))) {
		ZEPHIR_INIT_VAR(&_14$$5);
		ZEPHIR_CONCAT_SV(&_14$$5, " ON UPDATE ", &onUpdate);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_14$$5);
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
PHP_METHOD(Phalcon_Db_Dialect_Mysql, addIndex)
{
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *index, index_sub, indexType, _0, _1, _3, _4, _5, _6, _2$$3;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&indexType);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SV(&_1, "ALTER TABLE ", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&sql, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&indexType, index, "getType", NULL, 0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(&indexType))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SVS(&_2$$3, " ADD ", &indexType, " INDEX ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_2$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		zephir_concat_self_str(&sql, " ADD INDEX ", sizeof(" ADD INDEX ") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_3, index, "getName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, index, "getColumns", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getColumnList", NULL, 57, &_5);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SVSVS(&_6, "`", &_3, "` (", &_4, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_6);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to add the primary key to a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, addPrimaryKey)
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
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " ADD PRIMARY KEY (", &_1, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to create a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, createTable)
{
	zend_bool _26, _10$$10, _11$$10, _12$$10, _31$$19, _32$$19, _33$$19, _58$$25, _83$$36;
	zval indexSql, referenceSql, sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_14 = NULL, *_18 = NULL, *_49 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval definition, createLines;
	zval tableName_zv, schemaName_zv, *definition_param = NULL, temporary, options, table, columns, column, indexes, index, reference, references, indexName, columnLine, indexType, onDelete, onUpdate, defaultValue, upperDefaultValue, *_2, _3, *_4, _25, _95, _96, _0$$5, _1$$6, _5$$7, _6$$7, _8$$7, _9$$7, _20$$7, _21$$7, _22$$7, _13$$10, _15$$11, _16$$12, _17$$12, _19$$12, _23$$15, _24$$15, _27$$16, _28$$16, _29$$16, _30$$16, _39$$16, _40$$16, _41$$16, _34$$19, _35$$20, _36$$21, _37$$21, _38$$21, _42$$24, _43$$24, *_44$$25, _45$$25, *_46$$25, _57$$25, _47$$27, _48$$27, _50$$27, _51$$29, _52$$29, _53$$29, _54$$30, _55$$30, _56$$30, _59$$32, _60$$32, _61$$32, _62$$34, _63$$34, _64$$34, _65$$35, _66$$35, _67$$35, *_68$$36, _69$$36, *_70$$36, _82$$36, _71$$37, _72$$37, _73$$37, _74$$37, _75$$37, _76$$37, _77$$37, _78$$37, _79$$37, _80$$38, _81$$39, _84$$40, _85$$40, _86$$40, _87$$40, _88$$40, _89$$40, _90$$40, _91$$40, _92$$40, _93$$41, _94$$42, _97$$43, _98$$43;
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
	ZVAL_UNDEF(&columnLine);
	ZVAL_UNDEF(&indexType);
	ZVAL_UNDEF(&onDelete);
	ZVAL_UNDEF(&onUpdate);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&upperDefaultValue);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_95);
	ZVAL_UNDEF(&_96);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&_27$$16);
	ZVAL_UNDEF(&_28$$16);
	ZVAL_UNDEF(&_29$$16);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_39$$16);
	ZVAL_UNDEF(&_40$$16);
	ZVAL_UNDEF(&_41$$16);
	ZVAL_UNDEF(&_34$$19);
	ZVAL_UNDEF(&_35$$20);
	ZVAL_UNDEF(&_36$$21);
	ZVAL_UNDEF(&_37$$21);
	ZVAL_UNDEF(&_38$$21);
	ZVAL_UNDEF(&_42$$24);
	ZVAL_UNDEF(&_43$$24);
	ZVAL_UNDEF(&_45$$25);
	ZVAL_UNDEF(&_57$$25);
	ZVAL_UNDEF(&_47$$27);
	ZVAL_UNDEF(&_48$$27);
	ZVAL_UNDEF(&_50$$27);
	ZVAL_UNDEF(&_51$$29);
	ZVAL_UNDEF(&_52$$29);
	ZVAL_UNDEF(&_53$$29);
	ZVAL_UNDEF(&_54$$30);
	ZVAL_UNDEF(&_55$$30);
	ZVAL_UNDEF(&_56$$30);
	ZVAL_UNDEF(&_59$$32);
	ZVAL_UNDEF(&_60$$32);
	ZVAL_UNDEF(&_61$$32);
	ZVAL_UNDEF(&_62$$34);
	ZVAL_UNDEF(&_63$$34);
	ZVAL_UNDEF(&_64$$34);
	ZVAL_UNDEF(&_65$$35);
	ZVAL_UNDEF(&_66$$35);
	ZVAL_UNDEF(&_67$$35);
	ZVAL_UNDEF(&_69$$36);
	ZVAL_UNDEF(&_82$$36);
	ZVAL_UNDEF(&_71$$37);
	ZVAL_UNDEF(&_72$$37);
	ZVAL_UNDEF(&_73$$37);
	ZVAL_UNDEF(&_74$$37);
	ZVAL_UNDEF(&_75$$37);
	ZVAL_UNDEF(&_76$$37);
	ZVAL_UNDEF(&_77$$37);
	ZVAL_UNDEF(&_78$$37);
	ZVAL_UNDEF(&_79$$37);
	ZVAL_UNDEF(&_80$$38);
	ZVAL_UNDEF(&_81$$39);
	ZVAL_UNDEF(&_84$$40);
	ZVAL_UNDEF(&_85$$40);
	ZVAL_UNDEF(&_86$$40);
	ZVAL_UNDEF(&_87$$40);
	ZVAL_UNDEF(&_88$$40);
	ZVAL_UNDEF(&_89$$40);
	ZVAL_UNDEF(&_90$$40);
	ZVAL_UNDEF(&_91$$40);
	ZVAL_UNDEF(&_92$$40);
	ZVAL_UNDEF(&_93$$41);
	ZVAL_UNDEF(&_94$$42);
	ZVAL_UNDEF(&_97$$43);
	ZVAL_UNDEF(&_98$$43);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&createLines);
	ZVAL_UNDEF(&indexSql);
	ZVAL_UNDEF(&referenceSql);
	ZVAL_UNDEF(&sql);
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
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The index 'columns' is required in the definition array", "phalcon/Db/Dialect/Mysql.zep", 151);
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
	ZEPHIR_INIT_VAR(&createLines);
	array_init(&createLines);
	if (Z_TYPE_P(&columns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &columns);
		_2 = &_3;
	} else {
		_2 = &columns;
	}
	zephir_is_iterable(_2, 0, "phalcon/Db/Dialect/Mysql.zep", 228);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
		{
			ZEPHIR_INIT_NVAR(&column);
			ZVAL_COPY(&column, _4);
			ZEPHIR_CALL_METHOD(&_5$$7, &column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_6$$7, this_ptr, "getColumnDefinition", &_7, 0, &column);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&columnLine);
			ZEPHIR_CONCAT_SVSV(&columnLine, "`", &_5$$7, "` ", &_6$$7);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_8$$7, &column, "isNotNull", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_8$$7)) {
				zephir_concat_self_str(&columnLine, SL(" NOT NULL"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				zephir_concat_self_str(&columnLine, SL(" NULL"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_CALL_METHOD(&_9$$7, &column, "hasDefault", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_9$$7)) {
				ZEPHIR_CALL_METHOD(&defaultValue, &column, "getDefault", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&upperDefaultValue);
				zephir_fast_strtoupper(&upperDefaultValue, &defaultValue);
				_10$$10 = zephir_memnstr_str(&upperDefaultValue, SL("CURRENT_TIMESTAMP"), "phalcon/Db/Dialect/Mysql.zep", 194);
				if (!(_10$$10)) {
					_10$$10 = zephir_memnstr_str(&upperDefaultValue, SL("NULL"), "phalcon/Db/Dialect/Mysql.zep", 194);
				}
				_11$$10 = _10$$10;
				if (!(_11$$10)) {
					_11$$10 = Z_TYPE_P(&defaultValue) == IS_LONG;
				}
				_12$$10 = _11$$10;
				if (!(_12$$10)) {
					ZEPHIR_CALL_FUNCTION(&_13$$10, "is_float", &_14, 244, &defaultValue);
					zephir_check_call_status();
					_12$$10 = zephir_is_true(&_13$$10);
				}
				if (_12$$10) {
					ZEPHIR_INIT_NVAR(&_15$$11);
					ZEPHIR_CONCAT_SV(&_15$$11, " DEFAULT ", &defaultValue);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&columnLine, &_15$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_INIT_NVAR(&_16$$12);
					ZVAL_STRING(&_16$$12, "\"");
					ZEPHIR_CALL_FUNCTION(&_17$$12, "addcslashes", &_18, 245, &defaultValue, &_16$$12);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_19$$12);
					ZEPHIR_CONCAT_SVS(&_19$$12, " DEFAULT \"", &_17$$12, "\"");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&columnLine, &_19$$12);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			}
			ZEPHIR_CALL_METHOD(&_20$$7, &column, "isAutoIncrement", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_20$$7)) {
				zephir_concat_self_str(&columnLine, SL(" AUTO_INCREMENT"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_CALL_METHOD(&_21$$7, &column, "isPrimary", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_21$$7)) {
				zephir_concat_self_str(&columnLine, SL(" PRIMARY KEY"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_CALL_METHOD(&_22$$7, &column, "getComment", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_22$$7)) {
				ZEPHIR_CALL_METHOD(&_23$$15, &column, "getComment", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_24$$15);
				ZEPHIR_CONCAT_SVS(&_24$$15, " COMMENT '", &_23$$15, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&columnLine, &_24$$15);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			zephir_array_append(&createLines, &columnLine, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 222);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_26 = 1;
		while (1) {
			if (_26) {
				_26 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_25, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_25)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&column, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_27$$16, &column, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_28$$16, this_ptr, "getColumnDefinition", &_7, 0, &column);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&columnLine);
				ZEPHIR_CONCAT_SVSV(&columnLine, "`", &_27$$16, "` ", &_28$$16);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_29$$16, &column, "isNotNull", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_29$$16)) {
					zephir_concat_self_str(&columnLine, SL(" NOT NULL"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					zephir_concat_self_str(&columnLine, SL(" NULL"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&_30$$16, &column, "hasDefault", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_30$$16)) {
					ZEPHIR_CALL_METHOD(&defaultValue, &column, "getDefault", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&upperDefaultValue);
					zephir_fast_strtoupper(&upperDefaultValue, &defaultValue);
					_31$$19 = zephir_memnstr_str(&upperDefaultValue, SL("CURRENT_TIMESTAMP"), "phalcon/Db/Dialect/Mysql.zep", 194);
					if (!(_31$$19)) {
						_31$$19 = zephir_memnstr_str(&upperDefaultValue, SL("NULL"), "phalcon/Db/Dialect/Mysql.zep", 194);
					}
					_32$$19 = _31$$19;
					if (!(_32$$19)) {
						_32$$19 = Z_TYPE_P(&defaultValue) == IS_LONG;
					}
					_33$$19 = _32$$19;
					if (!(_33$$19)) {
						ZEPHIR_CALL_FUNCTION(&_34$$19, "is_float", &_14, 244, &defaultValue);
						zephir_check_call_status();
						_33$$19 = zephir_is_true(&_34$$19);
					}
					if (_33$$19) {
						ZEPHIR_INIT_NVAR(&_35$$20);
						ZEPHIR_CONCAT_SV(&_35$$20, " DEFAULT ", &defaultValue);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&columnLine, &_35$$20);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_INIT_NVAR(&_36$$21);
						ZVAL_STRING(&_36$$21, "\"");
						ZEPHIR_CALL_FUNCTION(&_37$$21, "addcslashes", &_18, 245, &defaultValue, &_36$$21);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_38$$21);
						ZEPHIR_CONCAT_SVS(&_38$$21, " DEFAULT \"", &_37$$21, "\"");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&columnLine, &_38$$21);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
				ZEPHIR_CALL_METHOD(&_39$$16, &column, "isAutoIncrement", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_39$$16)) {
					zephir_concat_self_str(&columnLine, SL(" AUTO_INCREMENT"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&_40$$16, &column, "isPrimary", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_40$$16)) {
					zephir_concat_self_str(&columnLine, SL(" PRIMARY KEY"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&_41$$16, &column, "getComment", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&_41$$16)) {
					ZEPHIR_CALL_METHOD(&_42$$24, &column, "getComment", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_43$$24);
					ZEPHIR_CONCAT_SVS(&_43$$24, " COMMENT '", &_42$$24, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&columnLine, &_43$$24);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				zephir_array_append(&createLines, &columnLine, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 222);
		}
	}
	ZEPHIR_INIT_NVAR(&column);
	zephir_memory_observe(&indexes);
	if (zephir_array_isset_string_fetch(&indexes, &definition, SL("indexes"), 0)) {
		if (Z_TYPE_P(&indexes) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_45$$25);
			zephir_string_to_char_array(&_45$$25, &indexes);
			_44$$25 = &_45$$25;
		} else {
			_44$$25 = &indexes;
		}
		zephir_is_iterable(_44$$25, 0, "phalcon/Db/Dialect/Mysql.zep", 248);
		if (Z_TYPE_P(_44$$25) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_44$$25), _46$$25)
			{
				ZEPHIR_INIT_NVAR(&index);
				ZVAL_COPY(&index, _46$$25);
				ZEPHIR_CALL_METHOD(&indexName, &index, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&indexType, &index, "getType", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_STRING(&indexName, "PRIMARY")) {
					ZEPHIR_CALL_METHOD(&_48$$27, &index, "getColumns", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_47$$27, this_ptr, "getColumnList", &_49, 57, &_48$$27);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_50$$27);
					ZEPHIR_CONCAT_SVS(&_50$$27, "PRIMARY KEY (", &_47$$27, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_get_strval(&indexSql, &_50$$27);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					if (!(ZEPHIR_IS_EMPTY(&indexType))) {
						ZEPHIR_CALL_METHOD(&_52$$29, &index, "getColumns", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_51$$29, this_ptr, "getColumnList", &_49, 57, &_52$$29);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_53$$29);
						ZEPHIR_CONCAT_VSVSVS(&_53$$29, &indexType, " KEY `", &indexName, "` (", &_51$$29, ")");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_get_strval(&indexSql, &_53$$29);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CALL_METHOD(&_55$$30, &index, "getColumns", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_54$$30, this_ptr, "getColumnList", &_49, 57, &_55$$30);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_56$$30);
						ZEPHIR_CONCAT_SVSVS(&_56$$30, "KEY `", &indexName, "` (", &_54$$30, ")");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_get_strval(&indexSql, &_56$$30);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
				zephir_array_append(&createLines, &indexSql, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 246);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _44$$25, "rewind", NULL, 0);
			zephir_check_call_status();
			_58$$25 = 1;
			while (1) {
				if (_58$$25) {
					_58$$25 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _44$$25, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_57$$25, _44$$25, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_57$$25)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&index, _44$$25, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&indexName, &index, "getName", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&indexType, &index, "getType", NULL, 0);
					zephir_check_call_status();
					if (ZEPHIR_IS_STRING(&indexName, "PRIMARY")) {
						ZEPHIR_CALL_METHOD(&_60$$32, &index, "getColumns", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_59$$32, this_ptr, "getColumnList", &_49, 57, &_60$$32);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_61$$32);
						ZEPHIR_CONCAT_SVS(&_61$$32, "PRIMARY KEY (", &_59$$32, ")");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_get_strval(&indexSql, &_61$$32);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						if (!(ZEPHIR_IS_EMPTY(&indexType))) {
							ZEPHIR_CALL_METHOD(&_63$$34, &index, "getColumns", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_62$$34, this_ptr, "getColumnList", &_49, 57, &_63$$34);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_64$$34);
							ZEPHIR_CONCAT_VSVSVS(&_64$$34, &indexType, " KEY `", &indexName, "` (", &_62$$34, ")");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_get_strval(&indexSql, &_64$$34);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZEPHIR_CALL_METHOD(&_66$$35, &index, "getColumns", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&_65$$35, this_ptr, "getColumnList", &_49, 57, &_66$$35);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_67$$35);
							ZEPHIR_CONCAT_SVSVS(&_67$$35, "KEY `", &indexName, "` (", &_65$$35, ")");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_get_strval(&indexSql, &_67$$35);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
					zephir_array_append(&createLines, &indexSql, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 246);
			}
		}
		ZEPHIR_INIT_NVAR(&index);
	}
	zephir_memory_observe(&references);
	if (zephir_array_isset_string_fetch(&references, &definition, SL("references"), 0)) {
		if (Z_TYPE_P(&references) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_69$$36);
			zephir_string_to_char_array(&_69$$36, &references);
			_68$$36 = &_69$$36;
		} else {
			_68$$36 = &references;
		}
		zephir_is_iterable(_68$$36, 0, "phalcon/Db/Dialect/Mysql.zep", 270);
		if (Z_TYPE_P(_68$$36) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_68$$36), _70$$36)
			{
				ZEPHIR_INIT_NVAR(&reference);
				ZVAL_COPY(&reference, _70$$36);
				ZEPHIR_CALL_METHOD(&_71$$37, &reference, "getName", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_73$$37, &reference, "getColumns", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_72$$37, this_ptr, "getColumnList", &_49, 57, &_73$$37);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_75$$37, &reference, "getReferencedTable", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_76$$37, &reference, "getReferencedSchema", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_74$$37, this_ptr, "prepareTable", NULL, 0, &_75$$37, &_76$$37);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_78$$37, &reference, "getReferencedColumns", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_77$$37, this_ptr, "getColumnList", &_49, 57, &_78$$37);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_79$$37);
				ZEPHIR_CONCAT_SVSVSSVSVS(&_79$$37, "CONSTRAINT `", &_71$$37, "` FOREIGN KEY (", &_72$$37, ")", " REFERENCES ", &_74$$37, " (", &_77$$37, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_get_strval(&referenceSql, &_79$$37);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&onDelete, &reference, "getOnDelete", NULL, 0);
				zephir_check_call_status();
				if (!(ZEPHIR_IS_EMPTY(&onDelete))) {
					ZEPHIR_INIT_NVAR(&_80$$38);
					ZEPHIR_CONCAT_SV(&_80$$38, " ON DELETE ", &onDelete);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&referenceSql, &_80$$38);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&onUpdate, &reference, "getOnUpdate", NULL, 0);
				zephir_check_call_status();
				if (!(ZEPHIR_IS_EMPTY(&onUpdate))) {
					ZEPHIR_INIT_NVAR(&_81$$39);
					ZEPHIR_CONCAT_SV(&_81$$39, " ON UPDATE ", &onUpdate);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&referenceSql, &_81$$39);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				zephir_array_append(&createLines, &referenceSql, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 268);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _68$$36, "rewind", NULL, 0);
			zephir_check_call_status();
			_83$$36 = 1;
			while (1) {
				if (_83$$36) {
					_83$$36 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _68$$36, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_82$$36, _68$$36, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_82$$36)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&reference, _68$$36, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_84$$40, &reference, "getName", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_86$$40, &reference, "getColumns", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_85$$40, this_ptr, "getColumnList", &_49, 57, &_86$$40);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_88$$40, &reference, "getReferencedTable", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_89$$40, &reference, "getReferencedSchema", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_87$$40, this_ptr, "prepareTable", NULL, 0, &_88$$40, &_89$$40);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_91$$40, &reference, "getReferencedColumns", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_90$$40, this_ptr, "getColumnList", &_49, 57, &_91$$40);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_92$$40);
					ZEPHIR_CONCAT_SVSVSSVSVS(&_92$$40, "CONSTRAINT `", &_84$$40, "` FOREIGN KEY (", &_85$$40, ")", " REFERENCES ", &_87$$40, " (", &_90$$40, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_get_strval(&referenceSql, &_92$$40);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&onDelete, &reference, "getOnDelete", NULL, 0);
					zephir_check_call_status();
					if (!(ZEPHIR_IS_EMPTY(&onDelete))) {
						ZEPHIR_INIT_NVAR(&_93$$41);
						ZEPHIR_CONCAT_SV(&_93$$41, " ON DELETE ", &onDelete);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&referenceSql, &_93$$41);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					ZEPHIR_CALL_METHOD(&onUpdate, &reference, "getOnUpdate", NULL, 0);
					zephir_check_call_status();
					if (!(ZEPHIR_IS_EMPTY(&onUpdate))) {
						ZEPHIR_INIT_NVAR(&_94$$42);
						ZEPHIR_CONCAT_SV(&_94$$42, " ON UPDATE ", &onUpdate);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&referenceSql, &_94$$42);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					zephir_array_append(&createLines, &referenceSql, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 268);
			}
		}
		ZEPHIR_INIT_NVAR(&reference);
	}
	ZEPHIR_INIT_VAR(&_95);
	zephir_fast_join_str(&_95, SL(",\n\t"), &createLines);
	ZEPHIR_INIT_VAR(&_96);
	ZEPHIR_CONCAT_VS(&_96, &_95, "\n)");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&sql, &_96);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_array_isset_value_string(&definition, SL("options"))) {
		ZEPHIR_CALL_METHOD(&_97$$43, this_ptr, "getTableOptions", NULL, 0, &definition);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_98$$43);
		ZEPHIR_CONCAT_SV(&_98$$43, " ", &_97$$43);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_98$$43);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to create a view
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, createView)
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
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The index 'sql' is required in the definition array", "phalcon/Db/Dialect/Mysql.zep", 291);
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
PHP_METHOD(Phalcon_Db_Dialect_Mysql, describeColumns)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, _0;
	zend_string *table = NULL, *schema = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&_0);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &table_zv, &schema_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SV(return_value, "SHOW FULL COLUMNS FROM ", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to query indexes on a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, describeIndexes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval table_zv, schema_zv, _0;
	zend_string *table = NULL, *schema = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&_0);
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
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &table_zv, &schema_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SV(return_value, "SHOW INDEXES FROM ", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to query foreign keys on a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, describeReferences)
{
	zval sql, _0$$3, _1$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval table_zv, schema_zv;
	zend_string *table = NULL, *schema = NULL;

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
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
	ZEPHIR_INIT_VAR(&sql);
	ZVAL_STRING(&sql, "SELECT DISTINCT KCU.TABLE_NAME, KCU.COLUMN_NAME, KCU.CONSTRAINT_NAME, KCU.REFERENCED_TABLE_SCHEMA, KCU.REFERENCED_TABLE_NAME, KCU.REFERENCED_COLUMN_NAME, RC.UPDATE_RULE, RC.DELETE_RULE FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS KCU LEFT JOIN INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS RC ON RC.CONSTRAINT_NAME = KCU.CONSTRAINT_NAME AND RC.CONSTRAINT_SCHEMA = KCU.CONSTRAINT_SCHEMA WHERE KCU.REFERENCED_TABLE_NAME IS NOT NULL AND ");
	if (!(ZEPHIR_IS_EMPTY(&schema_zv))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SVSVS(&_0$$3, "KCU.CONSTRAINT_SCHEMA = '", &schema_zv, "' AND KCU.TABLE_NAME = '", &table_zv, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_VAR(&_1$$4);
		ZEPHIR_CONCAT_SVS(&_1$$4, "KCU.CONSTRAINT_SCHEMA = DATABASE() AND KCU.TABLE_NAME = '", &table_zv, "'");
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
	RETURN_CTOR(&sql);
}

/**
 * Generates SQL to delete a column from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, dropColumn)
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
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " DROP COLUMN `", &columnName_zv, "`");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to delete a foreign key from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, dropForeignKey)
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
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " DROP FOREIGN KEY `", &referenceName_zv, "`");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to delete an index from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, dropIndex)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, indexName_zv, _0;
	zend_string *tableName = NULL, *schemaName = NULL, *indexName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&indexName_zv);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(tableName)
		Z_PARAM_STR(schemaName)
		Z_PARAM_STR(indexName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&tableName_zv);
	ZVAL_STR_COPY(&tableName_zv, tableName);
	zephir_memory_observe(&schemaName_zv);
	ZVAL_STR_COPY(&schemaName_zv, schemaName);
	zephir_memory_observe(&indexName_zv);
	ZVAL_STR_COPY(&indexName_zv, indexName);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prepareTable", NULL, 0, &tableName_zv, &schemaName_zv);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "ALTER TABLE ", &_0, " DROP INDEX `", &indexName_zv, "`");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to delete primary key from a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, dropPrimaryKey)
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
	ZEPHIR_CONCAT_SVS(return_value, "ALTER TABLE ", &_0, " DROP PRIMARY KEY");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to drop a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, dropTable)
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
PHP_METHOD(Phalcon_Db_Dialect_Mysql, dropView)
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
 * Gets the column name in MySQL
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, getColumnDefinition)
{
	zend_bool _45$$61;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_42 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column, column_sub, columnType, columnSql, typeValues, _0$$3, _1$$3, _2$$3, _3$$5, _4$$11, _5$$15, _6$$17, _7$$18, _8$$18, _9$$18, _10$$20, _11$$20, _12$$20, _13$$22, _14$$24, _15$$24, _16$$24, _17$$26, _18$$26, _19$$26, _20$$36, _21$$36, _22$$36, _23$$40, _24$$40, _25$$40, _26$$44, _27$$46, _28$$47, _29$$49, _30$$52, _31$$52, _32$$52, _33$$56, _34$$59, _35$$59, _36$$59, value$$61, valueSql$$61, *_37$$61, _38$$61, *_39$$61, _44$$61, _49$$61, _50$$61, _51$$61, _52$$61, _40$$62, _41$$62, _43$$62, _46$$63, _47$$63, _48$$63, _53$$64, _54$$64, _55$$64;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&columnType);
	ZVAL_UNDEF(&columnSql);
	ZVAL_UNDEF(&typeValues);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$11);
	ZVAL_UNDEF(&_5$$15);
	ZVAL_UNDEF(&_6$$17);
	ZVAL_UNDEF(&_7$$18);
	ZVAL_UNDEF(&_8$$18);
	ZVAL_UNDEF(&_9$$18);
	ZVAL_UNDEF(&_10$$20);
	ZVAL_UNDEF(&_11$$20);
	ZVAL_UNDEF(&_12$$20);
	ZVAL_UNDEF(&_13$$22);
	ZVAL_UNDEF(&_14$$24);
	ZVAL_UNDEF(&_15$$24);
	ZVAL_UNDEF(&_16$$24);
	ZVAL_UNDEF(&_17$$26);
	ZVAL_UNDEF(&_18$$26);
	ZVAL_UNDEF(&_19$$26);
	ZVAL_UNDEF(&_20$$36);
	ZVAL_UNDEF(&_21$$36);
	ZVAL_UNDEF(&_22$$36);
	ZVAL_UNDEF(&_23$$40);
	ZVAL_UNDEF(&_24$$40);
	ZVAL_UNDEF(&_25$$40);
	ZVAL_UNDEF(&_26$$44);
	ZVAL_UNDEF(&_27$$46);
	ZVAL_UNDEF(&_28$$47);
	ZVAL_UNDEF(&_29$$49);
	ZVAL_UNDEF(&_30$$52);
	ZVAL_UNDEF(&_31$$52);
	ZVAL_UNDEF(&_32$$52);
	ZVAL_UNDEF(&_33$$56);
	ZVAL_UNDEF(&_34$$59);
	ZVAL_UNDEF(&_35$$59);
	ZVAL_UNDEF(&_36$$59);
	ZVAL_UNDEF(&value$$61);
	ZVAL_UNDEF(&valueSql$$61);
	ZVAL_UNDEF(&_38$$61);
	ZVAL_UNDEF(&_44$$61);
	ZVAL_UNDEF(&_49$$61);
	ZVAL_UNDEF(&_50$$61);
	ZVAL_UNDEF(&_51$$61);
	ZVAL_UNDEF(&_52$$61);
	ZVAL_UNDEF(&_40$$62);
	ZVAL_UNDEF(&_41$$62);
	ZVAL_UNDEF(&_43$$62);
	ZVAL_UNDEF(&_46$$63);
	ZVAL_UNDEF(&_47$$63);
	ZVAL_UNDEF(&_48$$63);
	ZVAL_UNDEF(&_53$$64);
	ZVAL_UNDEF(&_54$$64);
	ZVAL_UNDEF(&_55$$64);
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
	if (ZEPHIR_IS_LONG(&columnType, 19)) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_LONG(&columnType, 11)) { goto zephir_switch_0_clause_2; }
	if (ZEPHIR_IS_LONG(&columnType, 8)) { goto zephir_switch_0_clause_3; }
	if (ZEPHIR_IS_LONG(&columnType, 5)) { goto zephir_switch_0_clause_4; }
	if (ZEPHIR_IS_LONG(&columnType, 1)) { goto zephir_switch_0_clause_5; }
	if (ZEPHIR_IS_LONG(&columnType, 4)) { goto zephir_switch_0_clause_6; }
	if (ZEPHIR_IS_LONG(&columnType, 3)) { goto zephir_switch_0_clause_7; }
	if (ZEPHIR_IS_LONG(&columnType, 9)) { goto zephir_switch_0_clause_8; }
	if (ZEPHIR_IS_LONG(&columnType, 18)) { goto zephir_switch_0_clause_9; }
	if (ZEPHIR_IS_LONG(&columnType, 7)) { goto zephir_switch_0_clause_10; }
	if (ZEPHIR_IS_LONG(&columnType, 0)) { goto zephir_switch_0_clause_11; }
	if (ZEPHIR_IS_LONG(&columnType, 15)) { goto zephir_switch_0_clause_12; }
	if (ZEPHIR_IS_LONG(&columnType, 13)) { goto zephir_switch_0_clause_13; }
	if (ZEPHIR_IS_LONG(&columnType, 24)) { goto zephir_switch_0_clause_14; }
	if (ZEPHIR_IS_LONG(&columnType, 12)) { goto zephir_switch_0_clause_15; }
	if (ZEPHIR_IS_LONG(&columnType, 21)) { goto zephir_switch_0_clause_16; }
	if (ZEPHIR_IS_LONG(&columnType, 23)) { goto zephir_switch_0_clause_17; }
	if (ZEPHIR_IS_LONG(&columnType, 22)) { goto zephir_switch_0_clause_18; }
	if (ZEPHIR_IS_LONG(&columnType, 6)) { goto zephir_switch_0_clause_19; }
	if (ZEPHIR_IS_LONG(&columnType, 20)) { goto zephir_switch_0_clause_20; }
	if (ZEPHIR_IS_LONG(&columnType, 17)) { goto zephir_switch_0_clause_21; }
	if (ZEPHIR_IS_LONG(&columnType, 10)) { goto zephir_switch_0_clause_22; }
	if (ZEPHIR_IS_LONG(&columnType, 26)) { goto zephir_switch_0_clause_23; }
	if (ZEPHIR_IS_LONG(&columnType, 25)) { goto zephir_switch_0_clause_24; }
	if (ZEPHIR_IS_LONG(&columnType, 2)) { goto zephir_switch_0_clause_25; }
	goto zephir_switch_0_clause_26;
	zephir_switch_0_clause_0: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("BIGINT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_0$$3, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_VV(&_2$$3, &_0$$3, &_1$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_2$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("BIT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_3$$5, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_3$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_2: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("BLOB"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_3: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TINYINT(1)"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_4: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("CHAR"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_4$$11, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_4$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_5: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("DATE"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_6: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("DATETIME"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_5$$15, column, "getSize", NULL, 0);
		zephir_check_call_status();
		if (ZEPHIR_GT_LONG(&_5$$15, 0)) {
			ZEPHIR_CALL_METHOD(&_6$$17, this_ptr, "getColumnSize", NULL, 0, column);
			zephir_check_call_status();
			zephir_concat_self(&columnSql, &_6$$17);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_7: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("DECIMAL"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_7$$18, this_ptr, "getColumnSizeAndScale", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_8$$18, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_9$$18);
		ZEPHIR_CONCAT_VV(&_9$$18, &_7$$18, &_8$$18);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_9$$18);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_8: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("DOUBLE"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_10$$20, this_ptr, "checkColumnSizeAndScale", NULL, 247, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_11$$20, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$20);
		ZEPHIR_CONCAT_VV(&_12$$20, &_10$$20, &_11$$20);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_12$$20);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_9: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("ENUM"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_13$$22, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_13$$22);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_10: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("FLOAT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_14$$24, this_ptr, "checkColumnSizeAndScale", NULL, 247, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_15$$24, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_16$$24);
		ZEPHIR_CONCAT_VV(&_16$$24, &_14$$24, &_15$$24);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_16$$24);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_11: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("INT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_17$$26, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_18$$26, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_19$$26);
		ZEPHIR_CONCAT_VV(&_19$$26, &_17$$26, &_18$$26);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_19$$26);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_12: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("JSON"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_13: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("LONGBLOB"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_14: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("LONGTEXT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_15: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("MEDIUMBLOB"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_16: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("MEDIUMINT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_20$$36, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_21$$36, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_22$$36);
		ZEPHIR_CONCAT_VV(&_22$$36, &_20$$36, &_21$$36);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_22$$36);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_17: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("MEDIUMTEXT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_18: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("SMALLINT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_23$$40, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_24$$40, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_25$$40);
		ZEPHIR_CONCAT_VV(&_25$$40, &_23$$40, &_24$$40);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_25$$40);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_19: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TEXT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_20: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TIME"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_26$$44, column, "getSize", NULL, 0);
		zephir_check_call_status();
		if (ZEPHIR_GT_LONG(&_26$$44, 0)) {
			ZEPHIR_CALL_METHOD(&_27$$46, this_ptr, "getColumnSize", NULL, 0, column);
			zephir_check_call_status();
			zephir_concat_self(&columnSql, &_27$$46);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_21: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TIMESTAMP"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_28$$47, column, "getSize", NULL, 0);
		zephir_check_call_status();
		if (ZEPHIR_GT_LONG(&_28$$47, 0)) {
			ZEPHIR_CALL_METHOD(&_29$$49, this_ptr, "getColumnSize", NULL, 0, column);
			zephir_check_call_status();
			zephir_concat_self(&columnSql, &_29$$49);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_22: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TINYBLOB"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_23: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TINYINT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_30$$52, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_31$$52, this_ptr, "checkColumnUnsigned", NULL, 246, column);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_32$$52);
		ZEPHIR_CONCAT_VV(&_32$$52, &_30$$52, &_31$$52);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_32$$52);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_24: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("TINYTEXT"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_25: ;
		if (ZEPHIR_IS_EMPTY(&columnSql)) {
			zephir_concat_self_str(&columnSql, SL("VARCHAR"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_33$$56, this_ptr, "getColumnSize", NULL, 0, column);
		zephir_check_call_status();
		zephir_concat_self(&columnSql, &_33$$56);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_26: ;
		if (UNEXPECTED(ZEPHIR_IS_EMPTY(&columnSql))) {
			ZEPHIR_INIT_VAR(&_34$$59);
			object_init_ex(&_34$$59, phalcon_db_exception_ce);
			ZEPHIR_CALL_METHOD(&_35$$59, column, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_36$$59);
			ZEPHIR_CONCAT_SV(&_36$$59, "Unrecognized MySQL data type at column ", &_35$$59);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_34$$59, "__construct", NULL, 32, &_36$$59);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_34$$59, "phalcon/Db/Dialect/Mysql.zep", 635);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&typeValues, column, "getTypeValues", NULL, 0);
		zephir_check_call_status();
		if (!(ZEPHIR_IS_EMPTY(&typeValues))) {
			if (Z_TYPE_P(&typeValues) == IS_ARRAY) {
				ZEPHIR_INIT_VAR(&valueSql$$61);
				ZVAL_STRING(&valueSql$$61, "");
				if (Z_TYPE_P(&typeValues) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_38$$61);
					zephir_string_to_char_array(&_38$$61, &typeValues);
					_37$$61 = &_38$$61;
				} else {
					_37$$61 = &typeValues;
				}
				zephir_is_iterable(_37$$61, 0, "phalcon/Db/Dialect/Mysql.zep", 649);
				if (Z_TYPE_P(_37$$61) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_37$$61), _39$$61)
					{
						ZEPHIR_INIT_NVAR(&value$$61);
						ZVAL_COPY(&value$$61, _39$$61);
						ZEPHIR_INIT_NVAR(&_40$$62);
						ZVAL_STRING(&_40$$62, "\"");
						ZEPHIR_CALL_FUNCTION(&_41$$62, "addcslashes", &_42, 245, &value$$61, &_40$$62);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_43$$62);
						ZEPHIR_CONCAT_SVS(&_43$$62, "\"", &_41$$62, "\", ");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&valueSql$$61, &_43$$62);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _37$$61, "rewind", NULL, 0);
					zephir_check_call_status();
					_45$$61 = 1;
					while (1) {
						if (_45$$61) {
							_45$$61 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _37$$61, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_44$$61, _37$$61, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_44$$61)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&value$$61, _37$$61, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_46$$63);
							ZVAL_STRING(&_46$$63, "\"");
							ZEPHIR_CALL_FUNCTION(&_47$$63, "addcslashes", &_42, 245, &value$$61, &_46$$63);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_48$$63);
							ZEPHIR_CONCAT_SVS(&_48$$63, "\"", &_47$$63, "\", ");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&valueSql$$61, &_48$$63);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
					}
				}
				ZEPHIR_INIT_NVAR(&value$$61);
				ZVAL_LONG(&_49$$61, 0);
				ZVAL_LONG(&_50$$61, -2);
				ZEPHIR_INIT_VAR(&_51$$61);
				zephir_substr(&_51$$61, &valueSql$$61, 0 , -2 , 0);
				ZEPHIR_INIT_VAR(&_52$$61);
				ZEPHIR_CONCAT_SVS(&_52$$61, "(", &_51$$61, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&columnSql, &_52$$61);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_INIT_VAR(&_53$$64);
				ZVAL_STRING(&_53$$64, "\"");
				ZEPHIR_CALL_FUNCTION(&_54$$64, "addcslashes", &_42, 245, &typeValues, &_53$$64);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_55$$64);
				ZEPHIR_CONCAT_SVS(&_55$$64, "(\"", &_54$$64, "\")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&columnSql, &_55$$64);
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
 * Generates SQL to check DB parameter FOREIGN_KEY_CHECKS.
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, getForeignKeyChecks)
{

	RETURN_STRING("SELECT @@foreign_key_checks");
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
PHP_METHOD(Phalcon_Db_Dialect_Mysql, listTables)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval schemaName_zv;
	zend_string *schemaName = NULL;

	ZVAL_UNDEF(&schemaName_zv);
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
	if (!(ZEPHIR_IS_EMPTY(&schemaName_zv))) {
		ZEPHIR_CONCAT_SVS(return_value, "SHOW TABLES FROM `", &schemaName_zv, "`");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	RETURN_MM_STRING("SHOW TABLES");
}

/**
 * Generates the SQL to list all views of a schema or user
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, listViews)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval schemaName_zv;
	zend_string *schemaName = NULL;

	ZVAL_UNDEF(&schemaName_zv);
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
	if (!(ZEPHIR_IS_EMPTY(&schemaName_zv))) {
		ZEPHIR_CONCAT_SVS(return_value, "SELECT `TABLE_NAME` AS view_name FROM `INFORMATION_SCHEMA`.`VIEWS` WHERE `TABLE_SCHEMA` = '", &schemaName_zv, "' ORDER BY view_name");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	RETURN_MM_STRING("SELECT `TABLE_NAME` AS view_name FROM `INFORMATION_SCHEMA`.`VIEWS` WHERE `TABLE_SCHEMA` = DATABASE() ORDER BY view_name");
}

/**
 * Generates SQL to modify a column in a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, modifyColumn)
{
	zend_bool _11$$8, _12$$8, _13$$8;
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tableName_zv, schemaName_zv, *column, column_sub, *currentColumn = NULL, currentColumn_sub, __$null, afterPosition, defaultValue, upperDefaultValue, columnDefinition, _0, _1, _2, _3, _9, _10, _19, _20, _23, _4$$4, _5$$4, _6$$4, _7$$5, _8$$5, _14$$8, _15$$9, _16$$10, _17$$10, _18$$10, _21$$12, _22$$12, _24$$15;
	zend_string *tableName = NULL, *schemaName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&currentColumn_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&afterPosition);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&upperDefaultValue);
	ZVAL_UNDEF(&columnDefinition);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&_22$$12);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&sql);
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
	zephir_get_strval(&sql, &_1);
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
		ZEPHIR_CONCAT_SVSVSV(&_6$$4, " CHANGE COLUMN `", &_4$$4, "` `", &_5$$4, "` ", &columnDefinition);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_6$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(&_7$$5, column, "getName", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$5);
		ZEPHIR_CONCAT_SVSV(&_8$$5, " MODIFY `", &_7$$5, "` ", &columnDefinition);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_8$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_9, column, "isNotNull", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_9)) {
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
	ZEPHIR_CALL_METHOD(&_10, column, "hasDefault", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_10)) {
		ZEPHIR_CALL_METHOD(&defaultValue, column, "getDefault", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&upperDefaultValue);
		zephir_fast_strtoupper(&upperDefaultValue, &defaultValue);
		_11$$8 = zephir_memnstr_str(&upperDefaultValue, SL("CURRENT_TIMESTAMP"), "phalcon/Db/Dialect/Mysql.zep", 731);
		if (!(_11$$8)) {
			_11$$8 = zephir_memnstr_str(&upperDefaultValue, SL("NULL"), "phalcon/Db/Dialect/Mysql.zep", 731);
		}
		_12$$8 = _11$$8;
		if (!(_12$$8)) {
			_12$$8 = Z_TYPE_P(&defaultValue) == IS_LONG;
		}
		_13$$8 = _12$$8;
		if (!(_13$$8)) {
			ZEPHIR_CALL_FUNCTION(&_14$$8, "is_float", NULL, 244, &defaultValue);
			zephir_check_call_status();
			_13$$8 = zephir_is_true(&_14$$8);
		}
		if (_13$$8) {
			ZEPHIR_INIT_VAR(&_15$$9);
			ZEPHIR_CONCAT_SV(&_15$$9, " DEFAULT ", &defaultValue);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_15$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_VAR(&_16$$10);
			ZVAL_STRING(&_16$$10, "\"");
			ZEPHIR_CALL_FUNCTION(&_17$$10, "addcslashes", NULL, 245, &defaultValue, &_16$$10);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_18$$10);
			ZEPHIR_CONCAT_SVS(&_18$$10, " DEFAULT \"", &_17$$10, "\"");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_18$$10);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(&_19, column, "isAutoIncrement", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_19)) {
		zephir_concat_self_str(&sql, " AUTO_INCREMENT", sizeof(" AUTO_INCREMENT") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_20, column, "getComment", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_20)) {
		ZEPHIR_CALL_METHOD(&_21$$12, column, "getComment", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_22$$12);
		ZEPHIR_CONCAT_SVS(&_22$$12, " COMMENT '", &_21$$12, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&sql, &_22$$12);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_23, column, "isFirst", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_23)) {
		zephir_concat_self_str(&sql, " FIRST", sizeof(" FIRST") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(&afterPosition, column, "getAfterPosition", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&afterPosition)) {
			ZEPHIR_INIT_VAR(&_24$$15);
			ZEPHIR_CONCAT_SVS(&_24$$15, " AFTER `", &afterPosition, "`");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&sql, &_24$$15);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CTOR(&sql);
}

/**
 * Returns a SQL modified with a LOCK IN SHARE MODE clause
 *
 *```php
 * $sql = $dialect->sharedLock("SELECT * FROM robots");
 *
 * echo $sql; // SELECT * FROM robots LOCK IN SHARE MODE
 *```
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, sharedLock)
{
	zval sqlQuery_zv;
	zend_string *sqlQuery = NULL;

	ZVAL_UNDEF(&sqlQuery_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sqlQuery)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&sqlQuery_zv, sqlQuery);
	ZEPHIR_CONCAT_VS(return_value, &sqlQuery_zv, " LOCK IN SHARE MODE");
	if (UNEXPECTED(EG(exception))) {
		return;
	}
	return;
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
PHP_METHOD(Phalcon_Db_Dialect_Mysql, tableExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval tableName_zv, schemaName_zv;
	zend_string *tableName = NULL, *schemaName = NULL;

	ZVAL_UNDEF(&tableName_zv);
	ZVAL_UNDEF(&schemaName_zv);
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
	if (!(ZEPHIR_IS_EMPTY(&schemaName_zv))) {
		ZEPHIR_CONCAT_SVSVS(return_value, "SELECT IF(COUNT(*) > 0, 1, 0) FROM `INFORMATION_SCHEMA`.`TABLES` WHERE `TABLE_NAME`= '", &tableName_zv, "' AND `TABLE_SCHEMA` = '", &schemaName_zv, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SVS(return_value, "SELECT IF(COUNT(*) > 0, 1, 0) FROM `INFORMATION_SCHEMA`.`TABLES` WHERE `TABLE_NAME` = '", &tableName_zv, "' AND `TABLE_SCHEMA` = DATABASE()");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates the SQL to describe the table creation options
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, tableOptions)
{
	zval sql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval table_zv, schema_zv;
	zend_string *table = NULL, *schema = NULL;

	ZVAL_UNDEF(&table_zv);
	ZVAL_UNDEF(&schema_zv);
	ZVAL_UNDEF(&sql);
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
	ZEPHIR_INIT_VAR(&sql);
	ZVAL_STRING(&sql, "SELECT TABLES.TABLE_TYPE AS table_type,TABLES.AUTO_INCREMENT AS auto_increment,TABLES.ENGINE AS engine,TABLES.TABLE_COLLATION AS table_collation FROM INFORMATION_SCHEMA.TABLES WHERE ");
	if (!(ZEPHIR_IS_EMPTY(&schema_zv))) {
		ZEPHIR_CONCAT_VSVSVS(return_value, &sql, "TABLES.TABLE_SCHEMA = '", &schema_zv, "' AND TABLES.TABLE_NAME = '", &table_zv, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_VSVS(return_value, &sql, "TABLES.TABLE_SCHEMA = DATABASE() AND TABLES.TABLE_NAME = '", &table_zv, "'");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to truncate a table
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, truncateTable)
{
	zval table;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval tableName_zv, schemaName_zv;
	zend_string *tableName = NULL, *schemaName = NULL;

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
		ZEPHIR_INIT_VAR(&table);
		ZEPHIR_CONCAT_SVSVS(&table, "`", &schemaName_zv, "`.`", &tableName_zv, "`");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_NVAR(&table);
		ZEPHIR_CONCAT_SVS(&table, "`", &tableName_zv, "`");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
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
PHP_METHOD(Phalcon_Db_Dialect_Mysql, viewExists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval viewName_zv, schemaName_zv;
	zend_string *viewName = NULL, *schemaName = NULL;

	ZVAL_UNDEF(&viewName_zv);
	ZVAL_UNDEF(&schemaName_zv);
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
	if (!(ZEPHIR_IS_EMPTY(&schemaName_zv))) {
		ZEPHIR_CONCAT_SVSVS(return_value, "SELECT IF(COUNT(*) > 0, 1, 0) FROM `INFORMATION_SCHEMA`.`VIEWS` WHERE `TABLE_NAME`= '", &viewName_zv, "' AND `TABLE_SCHEMA`='", &schemaName_zv, "'");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SVS(return_value, "SELECT IF(COUNT(*) > 0, 1, 0) FROM `INFORMATION_SCHEMA`.`VIEWS` WHERE `TABLE_NAME`='", &viewName_zv, "' AND `TABLE_SCHEMA` = DATABASE()");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates SQL to add the table creation options
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, getTableOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *definition_param = NULL, options, engine, autoIncrement, tableCollation, collationParts, _0$$5, _1$$7, _2$$9, _3$$9, _4$$9;
	zval definition, tableOptions;

	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&tableOptions);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&engine);
	ZVAL_UNDEF(&autoIncrement);
	ZVAL_UNDEF(&tableCollation);
	ZVAL_UNDEF(&collationParts);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$7);
	ZVAL_UNDEF(&_2$$9);
	ZVAL_UNDEF(&_3$$9);
	ZVAL_UNDEF(&_4$$9);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(definition, definition_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &definition_param);
	ZEPHIR_OBS_COPY_OR_DUP(&definition, definition_param);
	zephir_memory_observe(&options);
	if (!(zephir_array_isset_string_fetch(&options, &definition, SL("options"), 0))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_INIT_VAR(&tableOptions);
	array_init(&tableOptions);
	zephir_memory_observe(&engine);
	if (zephir_array_isset_string_fetch(&engine, &options, SL("ENGINE"), 0)) {
		if (zephir_is_true(&engine)) {
			ZEPHIR_INIT_VAR(&_0$$5);
			ZEPHIR_CONCAT_SV(&_0$$5, "ENGINE=", &engine);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&tableOptions, &_0$$5, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 857);
		}
	}
	zephir_memory_observe(&autoIncrement);
	if (zephir_array_isset_string_fetch(&autoIncrement, &options, SL("AUTO_INCREMENT"), 0)) {
		if (zephir_is_true(&autoIncrement)) {
			ZEPHIR_INIT_VAR(&_1$$7);
			ZEPHIR_CONCAT_SV(&_1$$7, "AUTO_INCREMENT=", &autoIncrement);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&tableOptions, &_1$$7, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 866);
		}
	}
	zephir_memory_observe(&tableCollation);
	if (zephir_array_isset_string_fetch(&tableCollation, &options, SL("TABLE_COLLATION"), 0)) {
		if (zephir_is_true(&tableCollation)) {
			ZEPHIR_INIT_VAR(&collationParts);
			zephir_fast_explode_str(&collationParts, SL("_"), &tableCollation, NULL);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_memory_observe(&_2$$9);
			zephir_array_fetch_long(&_2$$9, &collationParts, 0, PH_NOISY, "phalcon/Db/Dialect/Mysql.zep", 876);
			ZEPHIR_INIT_VAR(&_3$$9);
			ZEPHIR_CONCAT_SV(&_3$$9, "DEFAULT CHARSET=", &_2$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&tableOptions, &_3$$9, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 876);
			ZEPHIR_INIT_VAR(&_4$$9);
			ZEPHIR_CONCAT_SV(&_4$$9, "COLLATE=", &tableCollation);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&tableOptions, &_4$$9, PH_SEPARATE, "phalcon/Db/Dialect/Mysql.zep", 877);
		}
	}
	zephir_fast_join_str(return_value, SL(" "), &tableOptions);
	RETURN_MM();
}

/**
 * Checks if the size and/or scale are present and encloses those values
 * in parentheses if need be
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, checkColumnSizeAndScale)
{
	zval columnSql;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column, column_sub, _0, _1$$3, _2$$3, _3$$3, _4$$4, _5$$4;

	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&columnSql);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &column);
	ZEPHIR_INIT_VAR(&columnSql);
	ZEPHIR_CALL_METHOD(&_0, column, "getSize", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(&_1$$3, column, "getSize", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "(", &_1$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&columnSql, &_2$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_3$$3, column, "getScale", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&_3$$3)) {
			ZEPHIR_CALL_METHOD(&_4$$4, column, "getScale", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_5$$4);
			ZEPHIR_CONCAT_SVS(&_5$$4, ",", &_4$$4, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&columnSql, &_5$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_concat_self_str(&columnSql, ")", sizeof(")") - 1);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CTOR(&columnSql);
}

/**
 * Checks if a column is unsigned or not and returns the relevant SQL syntax
 */
PHP_METHOD(Phalcon_Db_Dialect_Mysql, checkColumnUnsigned)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *column, column_sub, _0;

	ZVAL_UNDEF(&column_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(column, phalcon_db_columninterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &column);
	ZEPHIR_CALL_METHOD(&_0, column, "isUnsigned", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		RETURN_MM_STRING(" UNSIGNED");
	}
	RETURN_MM_STRING("");
}

