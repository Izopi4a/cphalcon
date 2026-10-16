
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/exception.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\Model\Query\FragmentRewriter
 *
 * The only "parsing" the native compiler does. A raw SQL fragment (a
 * condition, order, group, having, join condition or column) is scanned once,
 * left to right, and only Phalcon's own spellings are rewritten:
 *
 * - `:name:` becomes `:name`, `?0` becomes `:0`
 * - `{name}` and `{name:type}` become `:name` (the type is recorded as a bind
 *   type); `{name:array}` expands to one placeholder per bound element
 * - `[Fully\Qualified\Model]` (or the unbracketed namespaced name) becomes
 *   the model's alias in the query, or its table when it is not part of the
 *   query (subqueries)
 * - `[identifier]` becomes an escaped identifier
 * - a model property becomes its column, through the model's column map
 * - `"text"` is a string, as in PHQL, and becomes `'text'`
 *
 * String literals, quoted identifiers, keywords, operators, function names and
 * `::` casts are never touched, so any SQL the database understands passes
 * through.
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Query_FragmentRewriter)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\Model\\Query, FragmentRewriter, phalcon, mvc_model_query_fragmentrewriter, phalcon_mvc_model_query_fragmentrewriter_method_entry, 0);

	/**
	 * Column maps (property => column) of the queried models, in query order
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("bareMaps"), ZEND_ACC_PROTECTED);
	/**
	 * Bind parameters, used to expand array placeholders
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("bindParams"), ZEND_ACC_PROTECTED);
	/**
	 * Bind types collected from typed placeholders ({name:int})
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("bindTypes"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_query_fragmentrewriter_ce, SL("columnRenaming"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var DialectInterface
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("dialect"), ZEND_ACC_PROTECTED);
	/**
	 * Names that can qualify a column: alias / source / model class
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("domains"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_query_fragmentrewriter_ce, SL("literals"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("manager"), ZEND_ACC_PROTECTED);
	/**
	 * @var MetaDataInterface
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("metaData"), ZEND_ACC_PROTECTED);
	/**
	 * Model class => table expression, for models referenced as tables
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_fragmentrewriter_ce, SL("tables"), ZEND_ACC_PROTECTED);
	phalcon_mvc_model_query_fragmentrewriter_ce->create_object = zephir_init_properties_Phalcon_Mvc_Model_Query_FragmentRewriter;

	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Query\FragmentRewriter constructor
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams;
	zval *manager, manager_sub, *metaData, metaData_sub, *dialect, dialect_sub, *bindParams_param = NULL, __$true, __$false, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&manager_sub);
	ZVAL_UNDEF(&metaData_sub);
	ZVAL_UNDEF(&dialect_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&bindParams);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("metaData", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dialect", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("literals", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("columnRenaming", 14, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_OBJECT_OF_CLASS(manager, phalcon_mvc_model_managerinterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(metaData, phalcon_mvc_model_metadatainterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(dialect, phalcon_db_dialectinterface_ce)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 1, &manager, &metaData, &dialect, &bindParams_param);
	if (!bindParams_param) {
		ZEPHIR_INIT_VAR(&bindParams);
		array_init(&bindParams);
	} else {
		zephir_get_arrval(&bindParams, bindParams_param);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 796, manager);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 797, metaData);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 798, dialect);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 799, &bindParams);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "orm.enable_literals");
	ZEPHIR_CALL_CE_STATIC(&_0, phalcon_support_settings_ce, "get", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_get_boolval(&_0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 800, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 800, &__$false);
	}
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "orm.column_renaming");
	ZEPHIR_CALL_CE_STATIC(&_0, phalcon_support_settings_ce, "get", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_get_boolval(&_0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 801, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 801, &__$false);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Registers a model taking part in the query under its SQL alias (the
 * table alias, or the table name when there is no alias)
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, addModel)
{
	zval _6$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool hasAlias;
	zval modelName_zv, *model, model_sub, sqlAlias_zv, *hasAlias_param = NULL, className, map, info, schema, source, _1, _2, _3, _0$$4, _4$$8, _5$$8, _7$$9, _8$$9;
	zend_string *modelName = NULL, *sqlAlias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&modelName_zv);
	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&sqlAlias_zv);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&info);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_4$$8);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_6$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("domains", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("tables", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(modelName)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
		Z_PARAM_STR(sqlAlias)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(hasAlias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	model = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 3) {
		hasAlias_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&modelName_zv);
	ZVAL_STR_COPY(&modelName_zv, modelName);
	zephir_memory_observe(&sqlAlias_zv);
	ZVAL_STR_COPY(&sqlAlias_zv, sqlAlias);
	if (!hasAlias_param) {
		hasAlias = 0;
	} else {
		}
	ZEPHIR_CALL_METHOD(&map, this_ptr, "getReverseMap", NULL, 0, model);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&info);
	zephir_create_array(&info, 2, 0);
	zephir_array_update_string(&info, SL("alias"), &sqlAlias_zv, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&info, SL("map"), &map, PH_COPY | PH_SEPARATE);
	if (hasAlias) {
		zephir_update_property_array(this_ptr, SL("domains"), &sqlAlias_zv, &info);
	} else {
		ZEPHIR_CALL_METHOD(&source, model, "getSource", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_0$$4, this_ptr, _zephir_prop_0, 802, PH_NOISY_CC | PH_READONLY);
		if (!(zephir_array_isset_value(&_0$$4, &source))) {
			zephir_update_property_array(this_ptr, SL("domains"), &source, &info);
		}
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "\\");
	ZEPHIR_INIT_VAR(&className);
	zephir_fast_trim(&className, &modelName_zv, &_1, ZEPHIR_TRIM_LEFT);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 802, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_value(&_2, &className))) {
		zephir_update_property_array(this_ptr, SL("domains"), &className, &info);
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 803, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_value(&_3, &className))) {
		ZEPHIR_CALL_METHOD(&source, model, "getSource", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&schema, model, "getSchema", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&schema)) {
			zephir_read_property_cached(&_4$$8, this_ptr, _zephir_prop_2, 798, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_6$$8);
			zephir_create_array(&_6$$8, 2, 0);
			zephir_array_fast_append(&_6$$8, &source);
			zephir_array_fast_append(&_6$$8, &schema);
			ZEPHIR_CALL_METHOD(&_5$$8, &_4$$8, "getSqlTable", NULL, 0, &_6$$8);
			zephir_check_call_status();
			zephir_update_property_array(this_ptr, SL("tables"), &className, &_5$$8);
		} else {
			zephir_read_property_cached(&_7$$9, this_ptr, _zephir_prop_2, 798, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_8$$9, &_7$$9, "getSqlTable", NULL, 0, &source);
			zephir_check_call_status();
			zephir_update_property_array(this_ptr, SL("tables"), &className, &_8$$9);
		}
	}
	if (Z_TYPE_P(&map) == IS_ARRAY) {
		zephir_update_property_array_append(this_ptr, SL("bareMaps"), &map);
	}
	RETURN_THIS();
}

/**
 * Escapes an identifier with the dialect's escape character
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, escape)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval identifier_zv, _0;
	zend_string *identifier = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&identifier_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(identifier)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&identifier_zv);
	ZVAL_STR_COPY(&identifier_zv, identifier);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 798, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "escape", NULL, 0, &identifier_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Bind types collected from typed placeholders
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, getBindTypes)
{

	RETURN_MEMBER_TYPED(getThis(), "bindTypes", IS_ARRAY);
}

/**
 * Resolves a column reference (`name`, `alias.name`, `[Model].[name]`) to
 * the escaped SQL column, through the column map
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, qualify)
{
	zend_bool _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval domain_zv, property_zv, info, map, column, _0, _4, _5, _6, _1$$4, _2$$4;
	zend_string *domain = NULL, *property = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&domain_zv);
	ZVAL_UNDEF(&property_zv);
	ZVAL_UNDEF(&info);
	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("domains", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(domain)
		Z_PARAM_STR(property)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&domain_zv);
	ZVAL_STR_COPY(&domain_zv, domain);
	zephir_memory_observe(&property_zv);
	ZVAL_STR_COPY(&property_zv, property);
	zephir_memory_observe(&info);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 802, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&info, &_0, &domain_zv, 0))) {
		ZEPHIR_CALL_METHOD(&info, this_ptr, "lazyDomain", NULL, 0, &domain_zv);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(&info) != IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "escape", NULL, 0, &domain_zv);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "escape", NULL, 0, &property_zv);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VSV(return_value, &_1$$4, ".", &_2$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	zephir_memory_observe(&map);
	zephir_array_fetch_string(&map, &info, SL("map"), PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 205);
	_3 = Z_TYPE_P(&map) != IS_ARRAY;
	if (!(_3)) {
		zephir_memory_observe(&column);
		_3 = !(zephir_array_isset_fetch(&column, &map, &property_zv, 0));
	}
	if (_3) {
		ZEPHIR_CPY_WRT(&column, &property_zv);
	}
	zephir_memory_observe(&_5);
	zephir_array_fetch_string(&_5, &info, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 211);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "escape", NULL, 0, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, this_ptr, "escape", NULL, 0, &column);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSV(return_value, &_4, ".", &_6);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Rewrites a fragment and returns a Dialect expression: a `literal`, or
 * a `list` of literals and expanded placeholders when the fragment uses
 * array placeholders
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, rewrite)
{
	zend_bool _47$$24, _48$$24, _49$$24, _64$$24, _61$$39;
	zval _34$$18, _35$$18, _69$$50;
	zval output;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL, *_42 = NULL, *_52 = NULL, *_56 = NULL, *_65 = NULL, *_66 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, total = 0, i = 0;
	zval fragment_zv, __$false, tokens, token, kind, text, name, info, next, prev, before, domainOf, pieces, bindType, bindValue, map, column, typeParts, nextIndex, prevIndex, _0$$4, _1$$6, _2$$6, _3$$6, _4$$6, _5$$6, _6$$6, _7$$6, _8$$6, _9$$6, _10$$8, _11$$8, _12$$8, _13$$9, _14$$9, _15$$9, _16$$10, _17$$10, _19$$10, _18$$11, _20$$12, _21$$13, _22$$14, _23$$15, _24$$16, _25$$17, _26$$18, _36$$18, _27$$19, _28$$19, _30$$20, _31$$20, _32$$21, _33$$21, _37$$22, _38$$22, _39$$23, _40$$25, _41$$25, _43$$24, _44$$24, _50$$24, _45$$27, _46$$28, _51$$30, _53$$32, _54$$32, _55$$32, _57$$34, _58$$34, _59$$35, _60$$37, _62$$40, _63$$41, _67$$45, _68$$46;
	zend_string *fragment = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fragment_zv);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&kind);
	ZVAL_UNDEF(&text);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&info);
	ZVAL_UNDEF(&next);
	ZVAL_UNDEF(&prev);
	ZVAL_UNDEF(&before);
	ZVAL_UNDEF(&domainOf);
	ZVAL_UNDEF(&pieces);
	ZVAL_UNDEF(&bindType);
	ZVAL_UNDEF(&bindValue);
	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&typeParts);
	ZVAL_UNDEF(&nextIndex);
	ZVAL_UNDEF(&prevIndex);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_22$$14);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$18);
	ZVAL_UNDEF(&_36$$18);
	ZVAL_UNDEF(&_27$$19);
	ZVAL_UNDEF(&_28$$19);
	ZVAL_UNDEF(&_30$$20);
	ZVAL_UNDEF(&_31$$20);
	ZVAL_UNDEF(&_32$$21);
	ZVAL_UNDEF(&_33$$21);
	ZVAL_UNDEF(&_37$$22);
	ZVAL_UNDEF(&_38$$22);
	ZVAL_UNDEF(&_39$$23);
	ZVAL_UNDEF(&_40$$25);
	ZVAL_UNDEF(&_41$$25);
	ZVAL_UNDEF(&_43$$24);
	ZVAL_UNDEF(&_44$$24);
	ZVAL_UNDEF(&_50$$24);
	ZVAL_UNDEF(&_45$$27);
	ZVAL_UNDEF(&_46$$28);
	ZVAL_UNDEF(&_51$$30);
	ZVAL_UNDEF(&_53$$32);
	ZVAL_UNDEF(&_54$$32);
	ZVAL_UNDEF(&_55$$32);
	ZVAL_UNDEF(&_57$$34);
	ZVAL_UNDEF(&_58$$34);
	ZVAL_UNDEF(&_59$$35);
	ZVAL_UNDEF(&_60$$37);
	ZVAL_UNDEF(&_62$$40);
	ZVAL_UNDEF(&_63$$41);
	ZVAL_UNDEF(&_67$$45);
	ZVAL_UNDEF(&_68$$46);
	ZVAL_UNDEF(&output);
	ZVAL_UNDEF(&_34$$18);
	ZVAL_UNDEF(&_35$$18);
	ZVAL_UNDEF(&_69$$50);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("literals", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("domains", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(fragment)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&fragment_zv);
	ZVAL_STR_COPY(&fragment_zv, fragment);
	ZEPHIR_CALL_SELF(&tokens, "tokenize", NULL, 0, &fragment_zv);
	zephir_check_call_status();
	total = zephir_fast_count_int(&tokens);
	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	ZEPHIR_INIT_VAR(&pieces);
	array_init(&pieces);
	ZEPHIR_INIT_VAR(&domainOf);
	array_init(&domainOf);
	i = 0;
	while (1) {
		if (!(i < total)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&token);
		zephir_array_fetch_long(&token, &tokens, i, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 235);
		ZEPHIR_OBS_NVAR(&kind);
		zephir_array_fetch_long(&kind, &token, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 236);
		ZEPHIR_OBS_NVAR(&text);
		zephir_array_fetch_long(&text, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 237);
		if (ZEPHIR_IS_STRING(&kind, "str")) { goto zephir_switch_0_clause_0; }
		if (ZEPHIR_IS_STRING(&kind, "num")) { goto zephir_switch_0_clause_1; }
		if (ZEPHIR_IS_STRING(&kind, "dq")) { goto zephir_switch_0_clause_2; }
		if (ZEPHIR_IS_STRING(&kind, "spl")) { goto zephir_switch_0_clause_3; }
		if (ZEPHIR_IS_STRING(&kind, "npl")) { goto zephir_switch_0_clause_4; }
		if (ZEPHIR_IS_STRING(&kind, "bpl")) { goto zephir_switch_0_clause_5; }
		if (ZEPHIR_IS_STRING(&kind, "id")) { goto zephir_switch_0_clause_6; }
		if (ZEPHIR_IS_STRING(&kind, "br")) { goto zephir_switch_0_clause_7; }
		goto zephir_switch_0_clause_8;
		zephir_switch_0_clause_0: ;
		zephir_switch_0_clause_1: ;
			zephir_read_property_cached(&_0$$4, this_ptr, _zephir_prop_0, 800, PH_NOISY_CC | PH_READONLY);
			if (UNEXPECTED(!zephir_is_true(&_0$$4))) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Literals are disabled in PHQL statements", "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 245);
				return;
			}
			zephir_concat_self(&output, &text);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_2: ;
			zephir_read_property_cached(&_1$$6, this_ptr, _zephir_prop_0, 800, PH_NOISY_CC | PH_READONLY);
			if (UNEXPECTED(!zephir_is_true(&_1$$6))) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Literals are disabled in PHQL statements", "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 259);
				return;
			}
			ZEPHIR_INIT_NVAR(&_2$$6);
			ZEPHIR_INIT_NVAR(&_3$$6);
			ZVAL_LONG(&_4$$6, 1);
			ZVAL_LONG(&_5$$6, -1);
			ZEPHIR_INIT_NVAR(&_6$$6);
			zephir_substr(&_6$$6, &text, 1 , -1 , 0);
			zephir_stripcslashes(&_3$$6, &_6$$6);
			ZEPHIR_INIT_NVAR(&_7$$6);
			ZVAL_STRING(&_7$$6, "'");
			ZEPHIR_INIT_NVAR(&_8$$6);
			ZVAL_STRING(&_8$$6, "''");
			zephir_fast_str_replace(&_2$$6, &_7$$6, &_8$$6, &_3$$6);
			ZEPHIR_INIT_NVAR(&_9$$6);
			ZEPHIR_CONCAT_SVS(&_9$$6, "'", &_2$$6, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&output, &_9$$6);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_3: ;
			ZVAL_LONG(&_10$$8, 0);
			ZVAL_LONG(&_11$$8, -1);
			ZEPHIR_INIT_NVAR(&_12$$8);
			zephir_substr(&_12$$8, &text, 0 , -1 , 0);
			zephir_concat_self(&output, &_12$$8);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_4: ;
			ZVAL_LONG(&_13$$9, 1);
			ZEPHIR_INIT_NVAR(&_14$$9);
			zephir_substr(&_14$$9, &text, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
			ZEPHIR_INIT_NVAR(&_15$$9);
			ZEPHIR_CONCAT_SV(&_15$$9, ":", &_14$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&output, &_15$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_5: ;
			ZVAL_LONG(&_16$$10, 1);
			ZVAL_LONG(&_17$$10, -1);
			ZEPHIR_INIT_NVAR(&name);
			zephir_substr(&name, &text, 1 , -1 , 0);
			if (!(zephir_memnstr_str(&name, SL(":"), "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 280))) {
				ZEPHIR_INIT_NVAR(&_18$$11);
				ZEPHIR_CONCAT_SV(&_18$$11, ":", &name);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&output, &_18$$11);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			}
			ZVAL_LONG(&_19$$10, 2);
			ZEPHIR_INIT_NVAR(&typeParts);
			zephir_fast_explode_str(&typeParts, SL(":"), &name, &_19$$10);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_OBS_NVAR(&name);
			zephir_array_fetch_long(&name, &typeParts, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 286);
			ZEPHIR_OBS_NVAR(&bindType);
			zephir_array_fetch_long(&bindType, &typeParts, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 287);
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
				ZEPHIR_INIT_NVAR(&_20$$12);
				ZVAL_LONG(&_20$$12, 2);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_20$$12);
				goto zephir_switch_1_end;
			zephir_switch_1_clause_1: ;
				ZEPHIR_INIT_NVAR(&_21$$13);
				ZVAL_LONG(&_21$$13, 1);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_21$$13);
				goto zephir_switch_1_end;
			zephir_switch_1_clause_2: ;
				ZEPHIR_INIT_NVAR(&_22$$14);
				ZVAL_LONG(&_22$$14, 32);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_22$$14);
				goto zephir_switch_1_end;
			zephir_switch_1_clause_3: ;
				ZEPHIR_INIT_NVAR(&_23$$15);
				ZVAL_LONG(&_23$$15, 5);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_23$$15);
				goto zephir_switch_1_end;
			zephir_switch_1_clause_4: ;
				ZEPHIR_INIT_NVAR(&_24$$16);
				ZVAL_LONG(&_24$$16, 3);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_24$$16);
				goto zephir_switch_1_end;
			zephir_switch_1_clause_5: ;
				ZEPHIR_INIT_NVAR(&_25$$17);
				ZVAL_LONG(&_25$$17, 0);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &name, &_25$$17);
				goto zephir_switch_1_end;
			zephir_switch_1_clause_6: ;
			zephir_switch_1_clause_7: ;
			zephir_switch_1_clause_8: ;
				ZEPHIR_OBS_NVAR(&bindValue);
				zephir_read_property_cached(&_26$$18, this_ptr, _zephir_prop_1, 799, PH_NOISY_CC | PH_READONLY);
				if (UNEXPECTED(!(zephir_array_isset_fetch(&bindValue, &_26$$18, &name, 0)))) {
					ZEPHIR_INIT_NVAR(&_27$$19);
					object_init_ex(&_27$$19, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_28$$19);
					ZEPHIR_CONCAT_SV(&_28$$19, "Bind value is required for array type placeholder: ", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_27$$19, "__construct", &_29, 32, &_28$$19);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_27$$19, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 320);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (UNEXPECTED(Z_TYPE_P(&bindValue) != IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(&_30$$20);
					object_init_ex(&_30$$20, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_31$$20);
					ZEPHIR_CONCAT_SV(&_31$$20, "Bind type requires an array in placeholder: ", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_30$$20, "__construct", &_29, 32, &_31$$20);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_30$$20, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 326);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (UNEXPECTED(zephir_fast_count_int(&bindValue) < 1)) {
					ZEPHIR_INIT_NVAR(&_32$$21);
					object_init_ex(&_32$$21, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_NVAR(&_33$$21);
					ZEPHIR_CONCAT_SV(&_33$$21, "At least one value must be bound in placeholder: ", &name);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_32$$21, "__construct", &_29, 32, &_33$$21);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_32$$21, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 332);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_34$$18);
				zephir_create_array(&_34$$18, 2, 0);
				add_assoc_stringl_ex(&_34$$18, SL("type"), SL("literal"));
				zephir_array_update_string(&_34$$18, SL("value"), &output, PH_COPY | PH_SEPARATE);
				zephir_array_append(&pieces, &_34$$18, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 338);
				ZEPHIR_INIT_NVAR(&_35$$18);
				zephir_create_array(&_35$$18, 4, 0);
				add_assoc_stringl_ex(&_35$$18, SL("type"), SL("placeholder"));
				ZEPHIR_INIT_NVAR(&_36$$18);
				ZEPHIR_CONCAT_SV(&_36$$18, ":", &name);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_update_string(&_35$$18, SL("value"), &_36$$18, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_35$$18, SL("rawValue"), &name, PH_COPY | PH_SEPARATE);
				add_assoc_long_ex(&_35$$18, SL("times"), zephir_fast_count_int(&bindValue));
				zephir_array_append(&pieces, &_35$$18, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 345);
				ZEPHIR_INIT_NVAR(&output);
				ZVAL_STRING(&output, "");
				goto zephir_switch_1_end;
			zephir_switch_1_clause_9: ;
				ZEPHIR_INIT_NVAR(&_37$$22);
				object_init_ex(&_37$$22, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_NVAR(&_38$$22);
				ZEPHIR_CONCAT_SV(&_38$$22, "Unknown bind type: ", &bindType);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_37$$22, "__construct", &_29, 32, &_38$$22);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_37$$22, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 351);
				ZEPHIR_MM_RESTORE();
				return;
			zephir_switch_1_end: ;

			if (!(zephir_start_with_str(&bindType, SL("array")))) {
				ZEPHIR_INIT_NVAR(&_39$$23);
				ZEPHIR_CONCAT_SV(&_39$$23, ":", &name);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&output, &_39$$23);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_6: ;
		zephir_switch_0_clause_7: ;
			if (ZEPHIR_IS_STRING(&kind, "br")) {
				ZVAL_LONG(&_40$$25, 1);
				ZVAL_LONG(&_41$$25, -1);
				ZEPHIR_INIT_NVAR(&name);
				zephir_substr(&name, &text, 1 , -1 , 0);
			} else {
				ZEPHIR_CPY_WRT(&name, &text);
			}
			ZVAL_LONG(&_43$$24, i);
			ZVAL_LONG(&_44$$24, 1);
			ZEPHIR_CALL_SELF(&nextIndex, "significant", &_42, 0, &tokens, &_43$$24, &_44$$24);
			zephir_check_call_status();
			ZVAL_LONG(&_43$$24, i);
			ZVAL_LONG(&_44$$24, -1);
			ZEPHIR_CALL_SELF(&prevIndex, "significant", &_42, 0, &tokens, &_43$$24, &_44$$24);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&next);
			ZVAL_STRING(&next, "");
			ZEPHIR_INIT_NVAR(&prev);
			ZVAL_STRING(&prev, "");
			if (ZEPHIR_GE_LONG(&nextIndex, 0)) {
				ZEPHIR_OBS_NVAR(&_45$$27);
				zephir_array_fetch(&_45$$27, &tokens, &nextIndex, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 374);
				ZEPHIR_OBS_NVAR(&next);
				zephir_array_fetch_long(&next, &_45$$27, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 374);
			}
			if (ZEPHIR_GE_LONG(&prevIndex, 0)) {
				ZEPHIR_OBS_NVAR(&_46$$28);
				zephir_array_fetch(&_46$$28, &tokens, &prevIndex, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 378);
				ZEPHIR_OBS_NVAR(&prev);
				zephir_array_fetch_long(&prev, &_46$$28, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 378);
			}
			_47$$24 = ZEPHIR_IS_STRING(&prev, "::");
			if (!(_47$$24)) {
				_48$$24 = ZEPHIR_IS_STRING(&kind, "id");
				if (_48$$24) {
					_48$$24 = ZEPHIR_IS_STRING(&next, "(");
				}
				_47$$24 = _48$$24;
			}
			_49$$24 = _47$$24;
			if (!(_49$$24)) {
				ZEPHIR_INIT_NVAR(&_50$$24);
				zephir_fast_strtoupper(&_50$$24, &prev);
				_49$$24 = ZEPHIR_IS_STRING(&_50$$24, "AS");
			}
			if (_49$$24) {
				if (ZEPHIR_IS_STRING(&kind, "br")) {
					ZEPHIR_CALL_METHOD(&_51$$30, this_ptr, "escape", &_52, 0, &name);
					zephir_check_call_status();
					zephir_concat_self(&output, &_51$$30);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					zephir_concat_self(&output, &text);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				goto zephir_switch_0_end;
			}
			if (ZEPHIR_IS_STRING(&next, ".")) {
				ZEPHIR_OBS_NVAR(&info);
				zephir_read_property_cached(&_53$$32, this_ptr, _zephir_prop_2, 802, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_NVAR(&_54$$32);
				ZEPHIR_INIT_NVAR(&_55$$32);
				ZVAL_STRING(&_55$$32, "\\");
				zephir_fast_trim(&_54$$32, &name, &_55$$32, ZEPHIR_TRIM_LEFT);
				if (!(zephir_array_isset_fetch(&info, &_53$$32, &_54$$32, 0))) {
					ZEPHIR_CALL_METHOD(&info, this_ptr, "lazyDomain", &_56, 0, &name);
					zephir_check_call_status();
				}
				zephir_array_update_long(&domainOf, i, &info, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				if (Z_TYPE_P(&info) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&_58$$34);
					zephir_array_fetch_string(&_58$$34, &info, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 405);
					ZEPHIR_CALL_METHOD(&_57$$34, this_ptr, "escape", &_52, 0, &_58$$34);
					zephir_check_call_status();
					zephir_concat_self(&output, &_57$$34);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else if (ZEPHIR_IS_STRING(&kind, "br")) {
					ZEPHIR_CALL_METHOD(&_59$$35, this_ptr, "escape", &_52, 0, &name);
					zephir_check_call_status();
					zephir_concat_self(&output, &_59$$35);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					zephir_concat_self(&output, &text);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				goto zephir_switch_0_end;
			}
			if (ZEPHIR_IS_STRING(&prev, ".")) {
				ZVAL_LONG(&_60$$37, -1);
				ZEPHIR_CALL_SELF(&before, "significant", &_42, 0, &tokens, &prevIndex, &_60$$37);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&info);
				ZVAL_NULL(&info);
				if (ZEPHIR_GE_LONG(&before, 0)) {
					ZEPHIR_OBS_NVAR(&info);
					zephir_array_isset_fetch(&info, &domainOf, &before, 0);
				}
				if (Z_TYPE_P(&info) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(&map);
					zephir_array_fetch_string(&map, &info, SL("map"), PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 427);
					_61$$39 = Z_TYPE_P(&map) == IS_ARRAY;
					if (_61$$39) {
						ZEPHIR_OBS_NVAR(&column);
						_61$$39 = zephir_array_isset_fetch(&column, &map, &name, 0);
					}
					if (_61$$39) {
						ZEPHIR_CALL_METHOD(&_62$$40, this_ptr, "escape", &_52, 0, &column);
						zephir_check_call_status();
						zephir_concat_self(&output, &_62$$40);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						goto zephir_switch_0_end;
					}
				}
				if (ZEPHIR_IS_STRING(&kind, "br")) {
					ZEPHIR_CALL_METHOD(&_63$$41, this_ptr, "escape", &_52, 0, &name);
					zephir_check_call_status();
					zephir_concat_self(&output, &_63$$41);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					zephir_concat_self(&output, &text);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				goto zephir_switch_0_end;
			}
			_64$$24 = ZEPHIR_IS_STRING(&kind, "br");
			if (!(_64$$24)) {
				_64$$24 = zephir_memnstr_str(&name, SL("\\"), "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 447);
			}
			if (_64$$24) {
				ZEPHIR_CALL_METHOD(&column, this_ptr, "modelTable", &_65, 0, &name);
				zephir_check_call_status();
				if (Z_TYPE_P(&column) != IS_NULL) {
					zephir_concat_self(&output, &column);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_0_end;
				}
			}
			ZEPHIR_CALL_METHOD(&column, this_ptr, "bareColumn", &_66, 0, &name);
			zephir_check_call_status();
			if (Z_TYPE_P(&column) != IS_NULL) {
				ZEPHIR_CALL_METHOD(&_67$$45, this_ptr, "escape", &_52, 0, &column);
				zephir_check_call_status();
				zephir_concat_self(&output, &_67$$45);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else if (ZEPHIR_IS_STRING(&kind, "br")) {
				ZEPHIR_CALL_METHOD(&_68$$46, this_ptr, "escape", &_52, 0, &name);
				zephir_check_call_status();
				zephir_concat_self(&output, &_68$$46);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				zephir_concat_self(&output, &text);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_8: ;
			zephir_concat_self(&output, &text);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_end: ;

		i++;
	}
	if (ZEPHIR_IS_EMPTY(&pieces)) {
		zephir_create_array(return_value, 2, 0);
		add_assoc_stringl_ex(return_value, SL("type"), SL("literal"));
		zephir_array_update_string(return_value, SL("value"), &output, PH_COPY | PH_SEPARATE);
		RETURN_MM();
	}
	if (!ZEPHIR_IS_STRING_IDENTICAL(&output, "")) {
		ZEPHIR_INIT_VAR(&_69$$50);
		zephir_create_array(&_69$$50, 2, 0);
		add_assoc_stringl_ex(&_69$$50, SL("type"), SL("literal"));
		zephir_array_update_string(&_69$$50, SL("value"), &output, PH_COPY | PH_SEPARATE);
		zephir_array_append(&pieces, &_69$$50, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 490);
	}
	zephir_create_array(return_value, 4, 0);
	add_assoc_stringl_ex(return_value, SL("type"), SL("list"));
	zephir_array_update_string(return_value, SL("value"), &pieces, PH_COPY | PH_SEPARATE);
	add_assoc_stringl_ex(return_value, SL("separator"), SL(""));
	zephir_array_update_string(return_value, SL("parentheses"), &__$false, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Rewrites a fragment that must stay a plain string (no array
 * placeholders)
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, rewriteString)
{
	zval _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval fragment_zv, expression, _0, _3, _1$$3;
	zend_string *fragment = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fragment_zv);
	ZVAL_UNDEF(&expression);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(fragment)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&fragment_zv);
	ZVAL_STR_COPY(&fragment_zv, fragment);
	ZEPHIR_CALL_METHOD(&expression, this_ptr, "rewrite", NULL, 0, &fragment_zv);
	zephir_check_call_status();
	zephir_memory_observe(&_0);
	zephir_array_fetch_string(&_0, &expression, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 511);
	if (UNEXPECTED(!ZEPHIR_IS_STRING(&_0, "literal"))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "Array placeholders are not allowed in this clause: ", &fragment_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 514);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_3);
	zephir_array_fetch_string(&_3, &expression, SL("value"), PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 517);
	RETURN_CCTOR(&_3);
}

/**
 * Splits a SQL list on the commas that are not inside parentheses,
 * quotes or brackets
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, splitList)
{
	zend_bool _12, _8$$4, _17$$9;
	zval buffer;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, depth = 0;
	zval sql_zv, token, parts, _0, *_1, _2, *_3, _11, _20, _4$$3, _10$$3, _5$$4, _6$$4, _7$$4, _9$$7, _13$$8, _19$$8, _14$$9, _15$$9, _16$$9, _18$$12, _21$$13;
	zend_string *sql = NULL;

	ZVAL_UNDEF(&sql_zv);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&buffer);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sql)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&sql_zv);
	ZVAL_STR_COPY(&sql_zv, sql);
	ZEPHIR_INIT_VAR(&parts);
	array_init(&parts);
	ZEPHIR_INIT_VAR(&buffer);
	ZVAL_STRING(&buffer, "");
	depth = 0;
	ZEPHIR_CALL_SELF(&_0, "tokenize", NULL, 0, &sql_zv);
	zephir_check_call_status();
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 551);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&token);
			ZVAL_COPY(&token, _3);
			ZEPHIR_OBS_NVAR(&_4$$3);
			zephir_array_fetch_long(&_4$$3, &token, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 535);
			if (ZEPHIR_IS_STRING(&_4$$3, "ch")) {
				ZEPHIR_OBS_NVAR(&_5$$4);
				zephir_array_fetch_long(&_5$$4, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 536);
				if (ZEPHIR_IS_STRING(&_5$$4, "(")) {
					depth++;
				} else {
					ZEPHIR_OBS_NVAR(&_6$$4);
					zephir_array_fetch_long(&_6$$4, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 538);
					if (ZEPHIR_IS_STRING(&_6$$4, ")")) {
						depth--;
					} else {
						ZEPHIR_OBS_NVAR(&_7$$4);
						zephir_array_fetch_long(&_7$$4, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 540);
						_8$$4 = ZEPHIR_IS_STRING(&_7$$4, ",");
						if (_8$$4) {
							_8$$4 = depth == 0;
						}
						if (_8$$4) {
							ZEPHIR_INIT_NVAR(&_9$$7);
							zephir_fast_trim(&_9$$7, &buffer, NULL , ZEPHIR_TRIM_BOTH);
							zephir_array_append(&parts, &_9$$7, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 541);
							ZEPHIR_INIT_NVAR(&buffer);
							ZVAL_STRING(&buffer, "");
							continue;
						}
					}
				}
			}
			ZEPHIR_OBS_NVAR(&_10$$3);
			zephir_array_fetch_long(&_10$$3, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 548);
			zephir_concat_self(&buffer, &_10$$3);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
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
			ZEPHIR_CALL_METHOD(&token, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_13$$8);
				zephir_array_fetch_long(&_13$$8, &token, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 535);
				if (ZEPHIR_IS_STRING(&_13$$8, "ch")) {
					ZEPHIR_OBS_NVAR(&_14$$9);
					zephir_array_fetch_long(&_14$$9, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 536);
					if (ZEPHIR_IS_STRING(&_14$$9, "(")) {
						depth++;
					} else {
						ZEPHIR_OBS_NVAR(&_15$$9);
						zephir_array_fetch_long(&_15$$9, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 538);
						if (ZEPHIR_IS_STRING(&_15$$9, ")")) {
							depth--;
						} else {
							ZEPHIR_OBS_NVAR(&_16$$9);
							zephir_array_fetch_long(&_16$$9, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 540);
							_17$$9 = ZEPHIR_IS_STRING(&_16$$9, ",");
							if (_17$$9) {
								_17$$9 = depth == 0;
							}
							if (_17$$9) {
								ZEPHIR_INIT_NVAR(&_18$$12);
								zephir_fast_trim(&_18$$12, &buffer, NULL , ZEPHIR_TRIM_BOTH);
								zephir_array_append(&parts, &_18$$12, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 541);
								ZEPHIR_INIT_NVAR(&buffer);
								ZVAL_STRING(&buffer, "");
								continue;
							}
						}
					}
				}
				ZEPHIR_OBS_NVAR(&_19$$8);
				zephir_array_fetch_long(&_19$$8, &token, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 548);
				zephir_concat_self(&buffer, &_19$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&token);
	ZEPHIR_INIT_VAR(&_20);
	zephir_fast_trim(&_20, &buffer, NULL , ZEPHIR_TRIM_BOTH);
	if (!ZEPHIR_IS_STRING_IDENTICAL(&_20, "")) {
		ZEPHIR_INIT_VAR(&_21$$13);
		zephir_fast_trim(&_21$$13, &buffer, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_append(&parts, &_21$$13, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 552);
	}
	RETURN_CCTOR(&parts);
}

/**
 * Splits `expr AS alias`, `expr [alias]` and `expr alias` into the
 * expression and the alias (null when there is none)
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, splitAlias)
{
	zend_bool _5, _7, _9, _14, _25, _27, _33, _40, _44, _48, _53, _55, _57;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, total = 0, i = 0, depth = 0, _15;
	zval item_zv, __$null, tokens, last, prev, alias, keywords, lastIndex, prevIndex, expression, _0, _1, _2, _4, _6, _8, _10, _12, _13, _16, _24, _26, _28, _32, _34, _35, _38, _39, _41, _43, _45, _47, _49, _50, _52, _54, _56, _58, _60, _3$$3, _11$$4, _17$$5, _18$$5, _19$$6, _20$$6, _21$$6, _22$$6, _23$$9, _29$$10, _30$$10, _31$$10, _36$$12, _37$$12, _42$$13, _46$$14, _51$$15, _59$$16;
	zend_string *item = NULL;

	ZVAL_UNDEF(&item_zv);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&last);
	ZVAL_UNDEF(&prev);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&keywords);
	ZVAL_UNDEF(&lastIndex);
	ZVAL_UNDEF(&prevIndex);
	ZVAL_UNDEF(&expression);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_43);
	ZVAL_UNDEF(&_45);
	ZVAL_UNDEF(&_47);
	ZVAL_UNDEF(&_49);
	ZVAL_UNDEF(&_50);
	ZVAL_UNDEF(&_52);
	ZVAL_UNDEF(&_54);
	ZVAL_UNDEF(&_56);
	ZVAL_UNDEF(&_58);
	ZVAL_UNDEF(&_60);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_29$$10);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_31$$10);
	ZVAL_UNDEF(&_36$$12);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_42$$13);
	ZVAL_UNDEF(&_46$$14);
	ZVAL_UNDEF(&_51$$15);
	ZVAL_UNDEF(&_59$$16);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(item)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&item_zv);
	ZVAL_STR_COPY(&item_zv, item);
	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_trim(&_0, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
	ZEPHIR_CALL_SELF(&tokens, "tokenize", NULL, 0, &_0);
	zephir_check_call_status();
	total = zephir_fast_count_int(&tokens);
	ZVAL_LONG(&_1, total);
	ZVAL_LONG(&_2, -1);
	ZEPHIR_CALL_SELF(&lastIndex, "significant", NULL, 0, &tokens, &_1, &_2);
	zephir_check_call_status();
	if (ZEPHIR_LT_LONG(&lastIndex, 1)) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_fast_trim(&_3$$3, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_3$$3);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	zephir_memory_observe(&last);
	zephir_array_fetch(&last, &tokens, &lastIndex, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 578);
	zephir_memory_observe(&_4);
	zephir_array_fetch_long(&_4, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 580);
	_5 = !ZEPHIR_IS_STRING(&_4, "id");
	if (_5) {
		zephir_memory_observe(&_6);
		zephir_array_fetch_long(&_6, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 580);
		_5 = !ZEPHIR_IS_STRING(&_6, "br");
	}
	_7 = _5;
	if (_7) {
		zephir_memory_observe(&_8);
		zephir_array_fetch_long(&_8, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 580);
		_7 = !ZEPHIR_IS_STRING(&_8, "qid");
	}
	_9 = _7;
	if (_9) {
		zephir_memory_observe(&_10);
		zephir_array_fetch_long(&_10, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 580);
		_9 = !ZEPHIR_IS_STRING(&_10, "dq");
	}
	if (_9) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_11$$4);
		zephir_fast_trim(&_11$$4, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_11$$4);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	ZVAL_LONG(&_1, -1);
	ZEPHIR_CALL_SELF(&prevIndex, "significant", NULL, 0, &tokens, &lastIndex, &_1);
	zephir_check_call_status();
	zephir_memory_observe(&prev);
	zephir_array_fetch(&prev, &tokens, &prevIndex, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 585);
	depth = 0;
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_LONG(&_12, 1);
	ZEPHIR_INIT_VAR(&_13);
	zephir_sub_function(&_13, &lastIndex, &_12);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&_16, &_13);
	_15 = 0;
	_14 = 0;
	if (ZEPHIR_GE_LONG(&_16, _15)) {
		while (1) {
			if (_14) {
				_15++;
				if (!(ZEPHIR_GE_LONG(&_16, _15))) {
					break;
				}
			} else {
				_14 = 1;
			}
			i = _15;
			ZEPHIR_OBS_NVAR(&_17$$5);
			zephir_array_fetch_long(&_17$$5, &tokens, i, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 593);
			ZEPHIR_OBS_NVAR(&_18$$5);
			zephir_array_fetch_long(&_18$$5, &_17$$5, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 593);
			if (ZEPHIR_IS_STRING(&_18$$5, "ch")) {
				ZEPHIR_OBS_NVAR(&_19$$6);
				zephir_array_fetch_long(&_19$$6, &tokens, i, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 594);
				ZEPHIR_OBS_NVAR(&_20$$6);
				zephir_array_fetch_long(&_20$$6, &_19$$6, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 594);
				if (ZEPHIR_IS_STRING(&_20$$6, "(")) {
					depth++;
				} else {
					ZEPHIR_OBS_NVAR(&_21$$6);
					zephir_array_fetch_long(&_21$$6, &tokens, i, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 596);
					ZEPHIR_OBS_NVAR(&_22$$6);
					zephir_array_fetch_long(&_22$$6, &_21$$6, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 596);
					if (ZEPHIR_IS_STRING(&_22$$6, ")")) {
						depth--;
					}
				}
			}
		}
	}
	if (depth != 0) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_23$$9);
		zephir_fast_trim(&_23$$9, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_23$$9);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	zephir_memory_observe(&_24);
	zephir_array_fetch_long(&_24, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 606);
	_25 = ZEPHIR_IS_STRING(&_24, "br");
	if (!(_25)) {
		zephir_memory_observe(&_26);
		zephir_array_fetch_long(&_26, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 606);
		_25 = ZEPHIR_IS_STRING(&_26, "qid");
	}
	_27 = _25;
	if (!(_27)) {
		zephir_memory_observe(&_28);
		zephir_array_fetch_long(&_28, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 606);
		_27 = ZEPHIR_IS_STRING(&_28, "dq");
	}
	if (_27) {
		zephir_memory_observe(&_29$$10);
		zephir_array_fetch_long(&_29$$10, &last, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 607);
		ZVAL_LONG(&_30$$10, 1);
		ZVAL_LONG(&_31$$10, -1);
		ZEPHIR_INIT_VAR(&alias);
		zephir_substr(&alias, &_29$$10, 1 , -1 , 0);
	} else {
		ZEPHIR_OBS_NVAR(&alias);
		zephir_array_fetch_long(&alias, &last, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 609);
	}
	zephir_memory_observe(&_32);
	zephir_array_fetch_long(&_32, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 612);
	_33 = ZEPHIR_IS_STRING(&_32, "id");
	if (_33) {
		ZEPHIR_INIT_VAR(&_34);
		zephir_memory_observe(&_35);
		zephir_array_fetch_long(&_35, &prev, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 612);
		zephir_fast_strtoupper(&_34, &_35);
		_33 = ZEPHIR_IS_STRING(&_34, "AS");
	}
	if (_33) {
		ZVAL_LONG(&_36$$12, 0);
		ZEPHIR_CALL_SELF(&expression, "joinTokens", NULL, 0, &tokens, &_36$$12, &prevIndex);
		zephir_check_call_status();
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_37$$12);
		zephir_fast_trim(&_37$$12, &expression, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_37$$12);
		zephir_array_fast_append(return_value, &alias);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&keywords);
	zephir_create_array(&keywords, 19, 0);
	ZEPHIR_INIT_VAR(&_38);
	ZVAL_STRING(&_38, "AND");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "AS");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "ASC");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "BETWEEN");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "CASE");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "DESC");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "DISTINCT");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "ELSE");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "END");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "FALSE");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "IN");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "IS");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "LIKE");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "NOT");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "NULL");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "OR");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "THEN");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "TRUE");
	zephir_array_fast_append(&keywords, &_38);
	ZEPHIR_INIT_NVAR(&_38);
	ZVAL_STRING(&_38, "WHEN");
	zephir_array_fast_append(&keywords, &_38);
	zephir_memory_observe(&_39);
	zephir_array_fetch_long(&_39, &last, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 627);
	_40 = ZEPHIR_IS_STRING(&_39, "id");
	if (_40) {
		ZEPHIR_INIT_NVAR(&_38);
		zephir_memory_observe(&_41);
		zephir_array_fetch_long(&_41, &last, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 627);
		zephir_fast_strtoupper(&_38, &_41);
		_40 = zephir_fast_in_array(&_38, &keywords);
	}
	if (_40) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_42$$13);
		zephir_fast_trim(&_42$$13, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_42$$13);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	zephir_memory_observe(&_43);
	zephir_array_fetch_long(&_43, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 631);
	_44 = ZEPHIR_IS_STRING(&_43, "ch");
	if (_44) {
		zephir_memory_observe(&_45);
		zephir_array_fetch_long(&_45, &prev, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 631);
		_44 = !ZEPHIR_IS_STRING(&_45, ")");
	}
	if (_44) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_46$$14);
		zephir_fast_trim(&_46$$14, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_46$$14);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	zephir_memory_observe(&_47);
	zephir_array_fetch_long(&_47, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 635);
	_48 = ZEPHIR_IS_STRING(&_47, "id");
	if (_48) {
		ZEPHIR_INIT_VAR(&_49);
		zephir_memory_observe(&_50);
		zephir_array_fetch_long(&_50, &prev, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 635);
		zephir_fast_strtoupper(&_49, &_50);
		_48 = zephir_fast_in_array(&_49, &keywords);
	}
	if (_48) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_51$$15);
		zephir_fast_trim(&_51$$15, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_51$$15);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	zephir_memory_observe(&_52);
	zephir_array_fetch_long(&_52, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 639);
	_53 = ZEPHIR_IS_STRING(&_52, "cast");
	if (!(_53)) {
		zephir_memory_observe(&_54);
		zephir_array_fetch_long(&_54, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 639);
		_53 = ZEPHIR_IS_STRING(&_54, "spl");
	}
	_55 = _53;
	if (!(_55)) {
		zephir_memory_observe(&_56);
		zephir_array_fetch_long(&_56, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 639);
		_55 = ZEPHIR_IS_STRING(&_56, "npl");
	}
	_57 = _55;
	if (!(_57)) {
		zephir_memory_observe(&_58);
		zephir_array_fetch_long(&_58, &prev, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 639);
		_57 = ZEPHIR_IS_STRING(&_58, "bpl");
	}
	if (_57) {
		zephir_create_array(return_value, 2, 0);
		ZEPHIR_INIT_VAR(&_59$$16);
		zephir_fast_trim(&_59$$16, &item_zv, NULL , ZEPHIR_TRIM_BOTH);
		zephir_array_fast_append(return_value, &_59$$16);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	ZVAL_LONG(&_1, 0);
	ZEPHIR_CALL_SELF(&expression, "joinTokens", NULL, 0, &tokens, &_1, &lastIndex);
	zephir_check_call_status();
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_60);
	zephir_fast_trim(&_60, &expression, NULL , ZEPHIR_TRIM_BOTH);
	zephir_array_fast_append(return_value, &_60);
	zephir_array_fast_append(return_value, &alias);
	RETURN_MM();
}

/**
 * Splits a fragment into tokens: [kind, text]
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, tokenize)
{
	zval kinds, _9$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval fragment_zv, matches, match, kind, tokens, _0, _1, _2, _3, _4, *_5, _6, *_7, *_8$$3, _10$$5;
	zend_string *fragment = NULL;

	ZVAL_UNDEF(&fragment_zv);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&match);
	ZVAL_UNDEF(&kind);
	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&kinds);
	ZVAL_UNDEF(&_9$$5);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(fragment)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&fragment_zv);
	ZVAL_STR_COPY(&fragment_zv, fragment);
	ZEPHIR_INIT_VAR(&kinds);
	zephir_create_array(&kinds, 14, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "cm");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "str");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "dq");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "qid");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "br");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "cast");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "spl");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "pdo");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "npl");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "bpl");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "id");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "num");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "ws");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "ch");
	zephir_array_fast_append(&kinds, &_0);
	ZEPHIR_INIT_VAR(&matches);
	ZVAL_NULL(&matches);
	ZEPHIR_INIT_VAR(&tokens);
	array_init(&tokens);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "/(?<cm>--[^\\n]*|\\/\\*.*?\\*\\/)|(?<str>'(?:[^']|'')*')|(?<dq>\"(?:\\\\.|[^\"\\\\])*\")|(?<qid>`[^`]*`)|(?<br>\\[[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\])|(?<cast>::)|(?<spl>:[A-Za-z_][A-Za-z0-9_-]*:(?!:))|(?<pdo>:[A-Za-z_][A-Za-z0-9_]*)|(?<npl>\\?[0-9]+)|(?<bpl>\\{[A-Za-z_][A-Za-z0-9_-]*(?::[a-z-]+)?\\})|(?<id>\\\\?[A-Za-z_][A-Za-z0-9_]*(?:\\\\[A-Za-z_][A-Za-z0-9_]*)*)|(?<num>[0-9]+(?:\\.[0-9]+)?(?:[eE][-+]?[0-9]+)?)|(?<ws>\\s+)|(?<ch>.)/s");
	ZVAL_LONG(&_1, (2 | 512));
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "/(?<cm>--[^\\n]*|\\/\\*.*?\\*\\/)|(?<str>'(?:[^']|'')*')|(?<dq>\"(?:\\\\.|[^\"\\\\])*\")|(?<qid>`[^`]*`)|(?<br>\\[[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\])|(?<cast>::)|(?<spl>:[A-Za-z_][A-Za-z0-9_-]*:(?!:))|(?<pdo>:[A-Za-z_][A-Za-z0-9_]*)|(?<npl>\\?[0-9]+)|(?<bpl>\\{[A-Za-z_][A-Za-z0-9_-]*(?::[a-z-]+)?\\})|(?<id>\\\\?[A-Za-z_][A-Za-z0-9_]*(?:\\\\[A-Za-z_][A-Za-z0-9_]*)*)|(?<num>[0-9]+(?:\\.[0-9]+)?(?:[eE][-+]?[0-9]+)?)|(?<ws>\\s+)|(?<ch>.)/s");
	ZVAL_LONG(&_4, (2 | 512));
	zephir_preg_match(&_2, &_3, &fragment_zv, &matches, 1, zephir_get_intval(&_1) , 0 );
	if (Z_TYPE_P(&matches) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_6);
		zephir_string_to_char_array(&_6, &matches);
		_5 = &_6;
	} else {
		_5 = &matches;
	}
	zephir_is_iterable(_5, 0, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 680);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5), _7)
	{
		ZEPHIR_INIT_NVAR(&match);
		ZVAL_COPY(&match, _7);
		zephir_is_iterable(&kinds, 0, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 678);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&kinds), _8$$3)
		{
			ZEPHIR_INIT_NVAR(&kind);
			ZVAL_COPY(&kind, _8$$3);
			if (zephir_array_isset_value(&match, &kind)) {
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_create_array(&_9$$5, 2, 0);
				zephir_array_fast_append(&_9$$5, &kind);
				ZEPHIR_OBS_NVAR(&_10$$5);
				zephir_array_fetch(&_10$$5, &match, &kind, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 674);
				zephir_array_fast_append(&_9$$5, &_10$$5);
				zephir_array_append(&tokens, &_9$$5, PH_SEPARATE, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 674);
				break;
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&kind);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&match);
	RETURN_CCTOR(&tokens);
}

/**
 * Column of a bare property, searching the queried models in order
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, bareColumn)
{
	zend_bool _5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, map, column, _0, *_1, _2, *_3, _4;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("bareMaps", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 804, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 696);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&map);
			ZVAL_COPY(&map, _3);
			ZEPHIR_OBS_NVAR(&column);
			if (zephir_array_isset_fetch(&column, &map, &name_zv, 0)) {
				RETURN_CCTOR(&column);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_5 = 1;
		while (1) {
			if (_5) {
				_5 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_4, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_4)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&map, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&column);
				if (zephir_array_isset_fetch(&column, &map, &name_zv, 0)) {
					RETURN_CCTOR(&column);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&map);
	RETURN_MM_NULL();
}

/**
 * Reverse column map (property => column) of a model, when column
 * renaming is on and the model has a column map
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, getReverseMap)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *model, model_sub, map, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&map);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("columnRenaming", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("metaData", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(model, phalcon_mvc_modelinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &model);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 801, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 797, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&map, &_1, "getReverseColumnMap", NULL, 0, model);
	zephir_check_call_status();
	if (Z_TYPE_P(&map) != IS_ARRAY) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&map);
}

/**
 * Whether a name refers to a model class. Only namespaced names are
 * autoloaded, so `[name]` does not hit the autoloader.
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, isModel)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, __$false, className, _0, _1;
	zend_string *name = NULL;

	ZVAL_UNDEF(&name_zv);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "\\");
	ZEPHIR_INIT_VAR(&className);
	zephir_fast_trim(&className, &name_zv, &_0, ZEPHIR_TRIM_LEFT);
	if (zephir_memnstr_str(&className, SL("\\"), "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 730)) {
		if (!(zephir_class_exists(&className, 1))) {
			RETURN_MM_BOOL(0);
		}
	} else if (!(zephir_class_exists(&className, zephir_is_true(&__$false) ))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Phalcon\\Mvc\\ModelInterface");
	ZEPHIR_RETURN_CALL_FUNCTION("is_subclass_of", NULL, 466, &className, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Registers a model that is not part of the query but is used as a
 * domain (`[Other\Model].column` in a subquery)
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, lazyDomain)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, className, model, info, source, _0, _1, _2, _3;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&info);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("manager", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "\\");
	ZEPHIR_INIT_VAR(&className);
	zephir_fast_trim(&className, &name_zv, &_0, ZEPHIR_TRIM_LEFT);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "isModel", NULL, 0, &className);
	zephir_check_call_status();
	if (!(zephir_is_true(&_1))) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 796, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&model, &_2, "load", NULL, 0, &className);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&info);
	zephir_create_array(&info, 2, 0);
	zephir_array_update_string(&info, SL("alias"), &source, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getReverseMap", NULL, 0, &model);
	zephir_check_call_status();
	zephir_array_update_string(&info, SL("map"), &_3, PH_COPY | PH_SEPARATE);
	zephir_update_property_array(this_ptr, SL("domains"), &className, &info);
	RETURN_CCTOR(&info);
}

/**
 * Table of a model referenced by class name, or null if the name is not
 * a model
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, modelTable)
{
	zval _5$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, className, table, model, schema, _0, _1, _2, _3, _4$$5, _6$$5, _7$$6, _8$$6;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_5$$5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("tables", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("manager", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("dialect", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "\\");
	ZEPHIR_INIT_VAR(&className);
	zephir_fast_trim(&className, &name_zv, &_0, ZEPHIR_TRIM_LEFT);
	zephir_memory_observe(&table);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 803, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_fetch(&table, &_1, &className, 0)) {
		RETURN_CCTOR(&table);
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "isModel", NULL, 0, &className);
	zephir_check_call_status();
	if (!(zephir_is_true(&_2))) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 796, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&model, &_3, "load", NULL, 0, &className);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&schema)) {
		zephir_read_property_cached(&_4$$5, this_ptr, _zephir_prop_2, 798, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_5$$5);
		zephir_create_array(&_5$$5, 2, 0);
		ZEPHIR_CALL_METHOD(&_6$$5, &model, "getSource", NULL, 0);
		zephir_check_call_status();
		zephir_array_fast_append(&_5$$5, &_6$$5);
		zephir_array_fast_append(&_5$$5, &schema);
		ZEPHIR_CALL_METHOD(&table, &_4$$5, "getSqlTable", NULL, 0, &_5$$5);
		zephir_check_call_status();
	} else {
		zephir_read_property_cached(&_7$$6, this_ptr, _zephir_prop_2, 798, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_8$$6, &model, "getSource", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&table, &_7$$6, "getSqlTable", NULL, 0, &_8$$6);
		zephir_check_call_status();
	}
	zephir_update_property_array(this_ptr, SL("tables"), &className, &table);
	RETURN_CCTOR(&table);
}

/**
 * Joins token texts from start (inclusive) to end (exclusive)
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, joinTokens)
{
	zval output;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long start, end, i = 0;
	zval *tokens_param = NULL, *start_param = NULL, *end_param = NULL, _0$$3, _1$$3;
	zval tokens;

	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&output);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(tokens, tokens_param)
		Z_PARAM_LONG(start)
		Z_PARAM_LONG(end)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &tokens_param, &start_param, &end_param);
	zephir_get_arrval(&tokens, tokens_param);
	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	i = start;
	while (1) {
		if (!(i < end)) {
			break;
		}
		zephir_array_fetch_long(&_0$$3, &tokens, i, PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 812);
		ZEPHIR_OBS_NVAR(&_1$$3);
		zephir_array_fetch_long(&_1$$3, &_0$$3, 1, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 812);
		zephir_concat_self(&output, &_1$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		i++;
	}
	RETURN_CTOR(&output);
}

/**
 * Index of the nearest significant token (not whitespace or comment) in
 * the given direction, or -1
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, significant)
{
	zend_bool _0, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long from, direction, i = 0, total = 0;
	zval *tokens_param = NULL, *from_param = NULL, *direction_param = NULL, kind, _1$$3;
	zval tokens;

	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&kind);
	ZVAL_UNDEF(&_1$$3);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(tokens, tokens_param)
		Z_PARAM_LONG(from)
		Z_PARAM_LONG(direction)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &tokens_param, &from_param, &direction_param);
	zephir_get_arrval(&tokens, tokens_param);
	total = zephir_fast_count_int(&tokens);
	i = (from + direction);
	while (1) {
		_0 = i >= 0;
		if (_0) {
			_0 = i < total;
		}
		if (!(_0)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&_1$$3);
		zephir_array_fetch_long(&_1$$3, &tokens, i, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 832);
		ZEPHIR_OBS_NVAR(&kind);
		zephir_array_fetch_long(&kind, &_1$$3, 0, PH_NOISY, "phalcon/Mvc/Model/Query/FragmentRewriter.zep", 832);
		_2$$3 = !ZEPHIR_IS_STRING(&kind, "ws");
		if (_2$$3) {
			_2$$3 = !ZEPHIR_IS_STRING(&kind, "cm");
		}
		if (_2$$3) {
			RETURN_MM_LONG(i);
		}
		i += direction;
	}
	RETURN_MM_LONG(-1);
}

zend_object *zephir_init_properties_Phalcon_Mvc_Model_Query_FragmentRewriter(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("tables"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("tables"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("domains"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("domains"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("bindTypes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("bindTypes"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("bindParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("bindParams"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("bareMaps"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("bareMaps"), &_9$$7);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

