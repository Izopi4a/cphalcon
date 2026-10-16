
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
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/main.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
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
 * Phalcon\Mvc\Model\Query\Builder
 *
 * Helps to create PHQL queries using an OO interface
 *
 *```php
 * $params = [
 *     "models"     => [
 *         Users::class,
 *     ],
 *     "columns"    => ["id", "name", "status"],
 *     "conditions" => [
 *         [
 *             "created > :min: AND created < :max:",
 *             [
 *                 "min" => "2013-01-01",
 *                 "max" => "2014-01-01",
 *             ],
 *             [
 *                 "min" => PDO::PARAM_STR,
 *                 "max" => PDO::PARAM_STR,
 *             ],
 *         ],
 *     ],
 *     // or "conditions" => "created > '2013-01-01' AND created < '2014-01-01'",
 *     "group"      => ["id", "name"],
 *     "having"     => "name = 'Kamil'",
 *     "order"      => ["name", "id"],
 *     "limit"      => 20,
 *     "offset"     => 20,
 *     // or "limit" => [20, 20],
 * ];
 *
 * $queryBuilder = new \Phalcon\Mvc\Model\Query\Builder($params);
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Query_Builder)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\Model\\Query, Builder, phalcon, mvc_model_query_builder, phalcon_mvc_model_query_builder_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("bindParams"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("bindTypes"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|string|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("columns"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|string|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("conditions"), ZEND_ACC_PROTECTED);
	/**
	 * @var DiInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("container"), ZEND_ACC_PROTECTED);
	/**
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("distinct"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_query_builder_ce, SL("forUpdate"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("group"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("having"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_model_query_builder_ce, SL("hiddenParamNumber"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("joins"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|string
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("limit"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|string
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("models"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_model_query_builder_ce, SL("offset"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array|string
	 */
	zend_declare_property_null(phalcon_mvc_model_query_builder_ce, SL("order"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_model_query_builder_ce, SL("sharedLock"), 0, ZEND_ACC_PROTECTED);
	phalcon_mvc_model_query_builder_ce->create_object = zephir_init_properties_Phalcon_Mvc_Model_Query_Builder;

	zend_class_implements(phalcon_mvc_model_query_builder_ce, 1, phalcon_mvc_model_query_builderinterface_ce);
	zend_class_implements(phalcon_mvc_model_query_builder_ce, 1, phalcon_di_injectionawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\Model\Query\Builder constructor
 *
 * @param array|string|null params
 * @param DiInterface|null container
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, __construct)
{
	zend_bool _6$$7, _10$$38;
	zval mergedConditions, mergedParams, mergedTypes;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *params = NULL, params_sub, *container = NULL, container_sub, __$null, conditions, columns, groupClause, havingClause, limitClause, forUpdate, sharedLock, orderClause, offsetClause, joinsClause, singleConditionArray, limit, offset, fromClause, singleCondition, singleParams, singleTypes, distinct, bind, bindTypes, *_0$$7, _1$$7, *_2$$7, _5$$7, _9$$7, _3$$11, _4$$12, _7$$16, _8$$17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&groupClause);
	ZVAL_UNDEF(&havingClause);
	ZVAL_UNDEF(&limitClause);
	ZVAL_UNDEF(&forUpdate);
	ZVAL_UNDEF(&sharedLock);
	ZVAL_UNDEF(&orderClause);
	ZVAL_UNDEF(&offsetClause);
	ZVAL_UNDEF(&joinsClause);
	ZVAL_UNDEF(&singleConditionArray);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&offset);
	ZVAL_UNDEF(&fromClause);
	ZVAL_UNDEF(&singleCondition);
	ZVAL_UNDEF(&singleParams);
	ZVAL_UNDEF(&singleTypes);
	ZVAL_UNDEF(&distinct);
	ZVAL_UNDEF(&bind);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&_1$$7);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_3$$11);
	ZVAL_UNDEF(&_4$$12);
	ZVAL_UNDEF(&_7$$16);
	ZVAL_UNDEF(&_8$$17);
	ZVAL_UNDEF(&mergedConditions);
	ZVAL_UNDEF(&mergedParams);
	ZVAL_UNDEF(&mergedTypes);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	static zend_string *_zephir_prop_9 = NULL;
	static zend_string *_zephir_prop_10 = NULL;
	static zend_string *_zephir_prop_11 = NULL;
	static zend_string *_zephir_prop_12 = NULL;
	static zend_string *_zephir_prop_13 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("conditions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindTypes", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("distinct", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("columns", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("joins", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("having", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("order", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("limit", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("offset", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("forUpdate", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_12)) {
		_zephir_prop_12 = zend_string_init("sharedLock", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_13)) {
		_zephir_prop_13 = zend_string_init("container", 9, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(params)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &params, &container);
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}
	if (!container) {
		container = &container_sub;
		container = &__$null;
	}
	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_memory_observe(&conditions);
		if (zephir_array_isset_long_fetch(&conditions, params, 0, 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 781, &conditions);
		} else {
			ZEPHIR_OBS_NVAR(&conditions);
			if (zephir_array_isset_string_fetch(&conditions, params, SL("conditions"), 0)) {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 781, &conditions);
			}
		}
		if (Z_TYPE_P(&conditions) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&mergedConditions);
			array_init(&mergedConditions);
			ZEPHIR_INIT_VAR(&mergedParams);
			array_init(&mergedParams);
			ZEPHIR_INIT_VAR(&mergedTypes);
			array_init(&mergedTypes);
			if (Z_TYPE_P(&conditions) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_1$$7);
				zephir_string_to_char_array(&_1$$7, &conditions);
				_0$$7 = &_1$$7;
			} else {
				_0$$7 = &conditions;
			}
			zephir_is_iterable(_0$$7, 0, "phalcon/Mvc/Model/Query/Builder.zep", 196);
			if (Z_TYPE_P(_0$$7) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$7), _2$$7)
				{
					ZEPHIR_INIT_NVAR(&singleConditionArray);
					ZVAL_COPY(&singleConditionArray, _2$$7);
					if (Z_TYPE_P(&singleConditionArray) == IS_ARRAY) {
						ZEPHIR_OBS_NVAR(&singleCondition);
						zephir_array_isset_long_fetch(&singleCondition, &singleConditionArray, 0, 0);
						ZEPHIR_OBS_NVAR(&singleParams);
						zephir_array_isset_long_fetch(&singleParams, &singleConditionArray, 1, 0);
						ZEPHIR_OBS_NVAR(&singleTypes);
						zephir_array_isset_long_fetch(&singleTypes, &singleConditionArray, 2, 0);
						if (Z_TYPE_P(&singleCondition) == IS_STRING) {
							zephir_array_append(&mergedConditions, &singleCondition, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 183);
						}
						if (Z_TYPE_P(&singleParams) == IS_ARRAY) {
							ZEPHIR_INIT_NVAR(&_3$$11);
							zephir_add_function(&_3$$11, &mergedParams, &singleParams);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if (UNEXPECTED(Z_TYPE_P(&_3$$11) != IS_ARRAY)) {
								zephir_throw_variable_type_error(&_3$$11, "mergedParams", "array");
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CPY_WRT(&mergedParams, &_3$$11);
						}
						if (Z_TYPE_P(&singleTypes) == IS_ARRAY) {
							ZEPHIR_INIT_NVAR(&_4$$12);
							zephir_add_function(&_4$$12, &mergedTypes, &singleTypes);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if (UNEXPECTED(Z_TYPE_P(&_4$$12) != IS_ARRAY)) {
								zephir_throw_variable_type_error(&_4$$12, "mergedTypes", "array");
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CPY_WRT(&mergedTypes, &_4$$12);
						}
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0$$7, "rewind", NULL, 0);
				zephir_check_call_status();
				_6$$7 = 1;
				while (1) {
					if (_6$$7) {
						_6$$7 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _0$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_5$$7, _0$$7, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_5$$7)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&singleConditionArray, _0$$7, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&singleConditionArray) == IS_ARRAY) {
							ZEPHIR_OBS_NVAR(&singleCondition);
							zephir_array_isset_long_fetch(&singleCondition, &singleConditionArray, 0, 0);
							ZEPHIR_OBS_NVAR(&singleParams);
							zephir_array_isset_long_fetch(&singleParams, &singleConditionArray, 1, 0);
							ZEPHIR_OBS_NVAR(&singleTypes);
							zephir_array_isset_long_fetch(&singleTypes, &singleConditionArray, 2, 0);
							if (Z_TYPE_P(&singleCondition) == IS_STRING) {
								zephir_array_append(&mergedConditions, &singleCondition, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 183);
							}
							if (Z_TYPE_P(&singleParams) == IS_ARRAY) {
								ZEPHIR_INIT_NVAR(&_7$$16);
								zephir_add_function(&_7$$16, &mergedParams, &singleParams);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								if (UNEXPECTED(Z_TYPE_P(&_7$$16) != IS_ARRAY)) {
									zephir_throw_variable_type_error(&_7$$16, "mergedParams", "array");
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CPY_WRT(&mergedParams, &_7$$16);
							}
							if (Z_TYPE_P(&singleTypes) == IS_ARRAY) {
								ZEPHIR_INIT_NVAR(&_8$$17);
								zephir_add_function(&_8$$17, &mergedTypes, &singleTypes);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								if (UNEXPECTED(Z_TYPE_P(&_8$$17) != IS_ARRAY)) {
									zephir_throw_variable_type_error(&_8$$17, "mergedTypes", "array");
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CPY_WRT(&mergedTypes, &_8$$17);
							}
						}
				}
			}
			ZEPHIR_INIT_NVAR(&singleConditionArray);
			ZEPHIR_INIT_VAR(&_9$$7);
			zephir_fast_join_str(&_9$$7, SL(" AND "), &mergedConditions);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 781, &_9$$7);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 782, &mergedParams);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 783, &mergedTypes);
		}
		zephir_memory_observe(&bind);
		if (zephir_array_isset_string_fetch(&bind, params, SL("bind"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 782, &bind);
		}
		zephir_memory_observe(&bindTypes);
		if (zephir_array_isset_string_fetch(&bindTypes, params, SL("bindTypes"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 783, &bindTypes);
		}
		zephir_memory_observe(&distinct);
		if (zephir_array_isset_string_fetch(&distinct, params, SL("distinct"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 784, &distinct);
		}
		zephir_memory_observe(&fromClause);
		if (zephir_array_isset_string_fetch(&fromClause, params, SL("models"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 785, &fromClause);
		}
		zephir_memory_observe(&columns);
		if (zephir_array_isset_string_fetch(&columns, params, SL("columns"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 786, &columns);
		}
		zephir_memory_observe(&joinsClause);
		if (zephir_array_isset_string_fetch(&joinsClause, params, SL("joins"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 787, &joinsClause);
		}
		zephir_memory_observe(&groupClause);
		if (zephir_array_isset_string_fetch(&groupClause, params, SL("group"), 0)) {
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "groupBy", NULL, 0, &groupClause);
			zephir_check_call_status();
		}
		zephir_memory_observe(&havingClause);
		if (zephir_array_isset_string_fetch(&havingClause, params, SL("having"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 788, &havingClause);
		}
		zephir_memory_observe(&orderClause);
		if (zephir_array_isset_string_fetch(&orderClause, params, SL("order"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 789, &orderClause);
		}
		zephir_memory_observe(&limitClause);
		if (zephir_array_isset_string_fetch(&limitClause, params, SL("limit"), 0)) {
			if (Z_TYPE_P(&limitClause) == IS_ARRAY) {
				zephir_memory_observe(&limit);
				if (zephir_array_isset_long_fetch(&limit, &limitClause, 0, 0)) {
					if (Z_TYPE_P(&limit) == IS_LONG) {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 790, &limit);
					}
					zephir_memory_observe(&offset);
					if (zephir_array_isset_long_fetch(&offset, &limitClause, 1, 0)) {
						if (Z_TYPE_P(&offset) == IS_LONG) {
							zephir_update_property_zval_cached(this_ptr, _zephir_prop_10, 791, &offset);
						}
					}
				} else {
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 790, &limitClause);
				}
			} else {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 790, &limitClause);
			}
		}
		zephir_memory_observe(&offsetClause);
		if (zephir_array_isset_string_fetch(&offsetClause, params, SL("offset"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_10, 791, &offsetClause);
		}
		zephir_memory_observe(&forUpdate);
		if (zephir_array_isset_string_fetch(&forUpdate, params, SL("for_update"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_11, 792, &forUpdate);
		}
		zephir_memory_observe(&sharedLock);
		if (zephir_array_isset_string_fetch(&sharedLock, params, SL("shared_lock"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_12, 793, &sharedLock);
		}
	} else {
		_10$$38 = Z_TYPE_P(params) == IS_STRING;
		if (_10$$38) {
			_10$$38 = !ZEPHIR_IS_STRING_IDENTICAL(params, "");
		}
		if (_10$$38) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 781, params);
		}
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_13, 794, container);
	ZEPHIR_MM_RESTORE();
}

/**
 * Add a model to take part of the query
 *
 *```php
 * // Load data from models Robots
 * $builder->addFrom(
 *     Robots::class
 * );
 *
 * // Load data from model 'Robots' using 'r' as alias in PHQL
 * $builder->addFrom(
 *     Robots::class,
 *     "r"
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, addFrom)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval model_zv, alias_zv, models, currentModel, _0, _1$$4;
	zend_string *model = NULL, *alias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_zv);
	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&currentModel);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("models", 6, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(model)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(alias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&model_zv);
	ZVAL_STR_COPY(&model_zv, model);
	if (!alias) {
		ZEPHIR_INIT_VAR(&alias_zv);
	} else {
		zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 785, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&models, &_0);
	if (Z_TYPE_P(&models) != IS_ARRAY) {
		if (Z_TYPE_P(&models) != IS_NULL) {
			ZEPHIR_CPY_WRT(&currentModel, &models);
			ZEPHIR_INIT_VAR(&_1$$4);
			zephir_create_array(&_1$$4, 1, 0);
			zephir_array_fast_append(&_1$$4, &currentModel);
			ZEPHIR_CPY_WRT(&models, &_1$$4);
		} else {
			ZEPHIR_INIT_NVAR(&models);
			array_init(&models);
		}
	}
	_2 = 1 == 1;
	if (_2) {
		_2 = !ZEPHIR_IS_NULL(&alias_zv);
	}
	if (_2) {
		zephir_array_update_zval(&models, &alias_zv, &model_zv, PH_COPY | PH_SEPARATE);
	} else {
		zephir_array_append(&models, &model_zv, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 351);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 785, &models);
	RETURN_THIS();
}

/**
 * Appends a condition to the current HAVING conditions clause using a AND operator
 *
 *```php
 * $builder->andHaving("SUM(Robots.price) > 0");
 *
 * $builder->andHaving(
 *     "SUM(Robots.price) > :sum:",
 *     [
 *         "sum" => 100,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, andHaving)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes;
	zval *conditions_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, currentConditions, _0$$3;
	zval conditions;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&currentConditions);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("having", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(conditions_param)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &conditions_param, &bindParams_param, &bindTypes_param);
	if (UNEXPECTED(Z_TYPE_P(conditions_param) != IS_STRING && Z_TYPE_P(conditions_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'conditions' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(conditions_param) == IS_STRING)) {
		zephir_get_strval(&conditions, conditions_param);
	} else {
		ZEPHIR_INIT_VAR(&conditions);
	}
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
	zephir_memory_observe(&currentConditions);
	zephir_read_property_cached(&currentConditions, this_ptr, _zephir_prop_0, 788, PH_NOISY_CC);
	if (zephir_is_true(&currentConditions)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SVSVS(&_0$$3, "(", &currentConditions, ") AND (", &conditions, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&conditions, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "having", NULL, 0, &conditions, &bindParams, &bindTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Appends a condition to the current WHERE conditions using a AND operator
 *
 *```php
 * $builder->andWhere("name = 'Peter'");
 *
 * $builder->andWhere(
 *     "name = :name: AND id > :id:",
 *     [
 *         "name" => "Peter",
 *         "id"   => 100,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, andWhere)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes;
	zval *conditions_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, currentConditions, _0$$3;
	zval conditions;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&currentConditions);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("conditions", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(conditions_param)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &conditions_param, &bindParams_param, &bindTypes_param);
	if (UNEXPECTED(Z_TYPE_P(conditions_param) != IS_STRING && Z_TYPE_P(conditions_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'conditions' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(conditions_param) == IS_STRING)) {
		zephir_get_strval(&conditions, conditions_param);
	} else {
		ZEPHIR_INIT_VAR(&conditions);
	}
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
	zephir_memory_observe(&currentConditions);
	zephir_read_property_cached(&currentConditions, this_ptr, _zephir_prop_0, 781, PH_NOISY_CC);
	if (zephir_is_true(&currentConditions)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SVSVS(&_0$$3, "(", &currentConditions, ") AND (", &conditions, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&conditions, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "where", NULL, 0, &conditions, &bindParams, &bindTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Automatically escapes identifiers but only if they need to be escaped.
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, autoescape)
{
	zend_bool _0, _1;
	zval identifier_zv;
	zend_string *identifier = NULL;

	ZVAL_UNDEF(&identifier_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(identifier)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&identifier_zv, identifier);
	_0 = zephir_memnstr_str(&identifier_zv, SL("["), "phalcon/Mvc/Model/Query/Builder.zep", 425);
	if (!(_0)) {
		_0 = zephir_memnstr_str(&identifier_zv, SL("."), "phalcon/Mvc/Model/Query/Builder.zep", 425);
	}
	_1 = _0;
	if (!(_1)) {
		_1 = zephir_is_numeric(&identifier_zv);
	}
	if (_1) {
		RETURN_STR(zend_string_copy(identifier));
	}
	ZEPHIR_CONCAT_SVS(return_value, "[", &identifier_zv, "]");
	if (UNEXPECTED(EG(exception))) {
		return;
	}
	return;
}

/**
 * Appends a BETWEEN condition to the current HAVING conditions clause
 *
 *```php
 * $builder->betweenHaving("SUM(Robots.price)", 100.25, 200.50);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, betweenHaving)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval expr_zv, *minimum, minimum_sub, *maximum, maximum_sub, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&minimum_sub);
	ZVAL_UNDEF(&maximum_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(expr)
		Z_PARAM_ZVAL(minimum)
		Z_PARAM_ZVAL(maximum)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	minimum = ZEND_CALL_ARG(execute_data, 2);
	maximum = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		operator_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Having");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionBetween", NULL, 0, &_0, &operator, &expr_zv, minimum, maximum);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Appends a BETWEEN condition to the current WHERE conditions
 *
 *```php
 * $builder->betweenWhere("price", 100.25, 200.50);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, betweenWhere)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval expr_zv, *minimum, minimum_sub, *maximum, maximum_sub, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&minimum_sub);
	ZVAL_UNDEF(&maximum_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(expr)
		Z_PARAM_ZVAL(minimum)
		Z_PARAM_ZVAL(maximum)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	minimum = ZEND_CALL_ARG(execute_data, 2);
	maximum = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		operator_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Where");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionBetween", NULL, 0, &_0, &operator, &expr_zv, minimum, maximum);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Sets the columns to be queried. The columns can be either a `string` or
 * an `array` of strings. If the argument is a (single, non-embedded) string,
 * its content can specify one or more columns, separated by commas, the same
 * way that one uses the SQL select statement. You can use aliases, aggregate
 * functions, etc. If you need to reference other models you will need to
 * reference them with their namespaces.
 *
 * When using an array as a parameter, you will need to specify one field
 * per array element. If a non-numeric key is defined in the array, it will
 * be used as the alias in the query
 *
 *```php
 * <?php
 *
 * // String, comma separated values
 * $builder->columns("id, category");
 *
 * // Array, one column per element
 * $builder->columns(
 *     [
 *         "inv_id",
 *         "inv_total",
 *     ]
 * );
 *
 * // Array with named key. The name of the key acts as an
 * // alias (`AS` clause)
 * $builder->columns(
 *     [
 *         "inv_cst_id",
 *         "total_invoices" => "COUNT(*)",
 *     ]
 * );
 *
 * // Different models
 * $builder->columns(
 *     [
 *         "\Phalcon\Models\Invoices.*",
 *         "\Phalcon\Models\Customers.cst_name_first",
 *         "\Phalcon\Models\Customers.cst_name_last",
 *     ]
 * );
 *```
 *
 * @param string|array $columns
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, columns)
{
	zval *columns, columns_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&columns_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("columns", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(columns)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &columns);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 786, columns);
	RETURN_THISW();
}

/**
 * Sets SELECT DISTINCT / SELECT ALL flag
 *
 *```php
 * $builder->distinct("status");
 * $builder->distinct(null);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, distinct)
{
	zval *distinct, distinct_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&distinct_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("distinct", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(distinct)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &distinct);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 784, distinct);
	RETURN_THISW();
}

/**
 * Sets a FOR UPDATE clause
 *
 *```php
 * $builder->forUpdate(true);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, forUpdate)
{
	zval *forUpdate_param = NULL, __$true, __$false;
	zend_bool forUpdate;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("forUpdate", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(forUpdate)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &forUpdate_param);
	if (forUpdate) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 792, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 792, &__$false);
	}
	RETURN_THISW();
}

/**
 * Sets the models who makes part of the query
 *
 *```php
 * $builder->from(
 *     Robots::class
 * );
 *
 * $builder->from(
 *     [
 *         Robots::class,
 *         RobotsParts::class,
 *     ]
 * );
 *
 * $builder->from(
 *     [
 *         "r"  => Robots::class,
 *         "rp" => RobotsParts::class,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, from)
{
	zval *models, models_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&models_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("models", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(models)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &models);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 785, models);
	RETURN_THISW();
}

/**
 * Returns default bind params
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getBindParams)
{

	RETURN_MEMBER_TYPED(getThis(), "bindParams", IS_ARRAY);
}

/**
 * Returns default bind types
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getBindTypes)
{

	RETURN_MEMBER_TYPED(getThis(), "bindTypes", IS_ARRAY);
}

/**
 * Return the columns to be queried
 *
 * @return array|string
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getColumns)
{

	RETURN_MEMBER(getThis(), "columns");
}

/**
 * Returns the DependencyInjector container
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getDI)
{

	RETURN_MEMBER(getThis(), "container");
}

/**
 * Returns SELECT DISTINCT / SELECT ALL flag
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getDistinct)
{

	RETURN_MEMBER(getThis(), "distinct");
}

/**
 * Return the models who makes part of the query
 *
 * @return array|string
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getFrom)
{

	RETURN_MEMBER(getThis(), "models");
}

/**
 * Returns the GROUP BY clause
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getGroupBy)
{

	RETURN_MEMBER_TYPED(getThis(), "group", IS_ARRAY);
}

/**
 * Return the current having clause
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getHaving)
{

	RETURN_MEMBER(getThis(), "having");
}

/**
 * Return join parts of the query
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getJoins)
{

	RETURN_MEMBER_TYPED(getThis(), "joins", IS_ARRAY);
}

/**
 * Returns the current LIMIT clause
 *
 * @return array|string
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getLimit)
{

	RETURN_MEMBER(getThis(), "limit");
}

/**
 * Returns the models involved in the query
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getModels)
{
	zend_bool _1;
	zval models, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("models", 6, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 785, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&models, &_0);
	_1 = Z_TYPE_P(&models) == IS_ARRAY;
	if (_1) {
		_1 = zephir_fast_count_int(&models) == 1;
	}
	if (_1) {
		ZEPHIR_MAKE_REF(&models);
		ZEPHIR_RETURN_CALL_FUNCTION("reset", NULL, 0, &models);
		ZEPHIR_UNREF(&models);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CCTOR(&models);
}

/**
 * Returns the current OFFSET clause
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getOffset)
{

	RETURN_MEMBER_TYPED(getThis(), "offset", IS_LONG);
}

/**
 * Returns the set ORDER BY clause
 *
 * @return array|string
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getOrderBy)
{

	RETURN_MEMBER(getThis(), "order");
}

/**
 * Returns a PHQL statement built based on the builder parameters
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getPhql)
{
	zend_string *_13$$25, *_25$$34, *_39$$42;
	zend_ulong _12$$25, _24$$34, _38$$42;
	zval _2$$8;
	zend_bool noPrimary = 0, _17$$25, _29$$34, _43$$42, _61$$50, _75$$63, _89$$69, _104$$85;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null, container, models, conditions, model, metaData, modelInstance, primaryKeys, firstPrimaryKey, columnMap, modelAlias, attributeField, phql, column, columns, selectedColumns, selectedColumn, selectedModel, selectedModels, columnAlias, modelColumnAlias, joins, join, joinModel, joinConditions, joinAlias, joinType, group, groupItems, groupItem, having, order, orderItems, orderItem, limit, number, offset, forUpdate, distinct, _0, _1$$8, _3$$13, _4$$13, _7$$13, _8$$13, _5$$17, _6$$17, *_9$$25, _10$$25, *_11$$25, _16$$25, _20$$25, _14$$28, _15$$28, _18$$31, _19$$31, *_21$$34, _22$$34, *_23$$34, _28$$34, _32$$34, _26$$36, _27$$37, _30$$39, _31$$40, _33$$41, _34$$41, *_35$$42, _36$$42, *_37$$42, _42$$42, _46$$42, _47$$42, _40$$44, _41$$44, _44$$47, _45$$47, _48$$49, _49$$49, *_50$$50, _51$$50, *_52$$50, _60$$50, _53$$52, _54$$52, _55$$53, _56$$53, _57$$54, _58$$54, _59$$55, _62$$57, _63$$57, _64$$58, _65$$58, _66$$59, _67$$59, _68$$60, _69$$62, *_70$$63, _71$$63, *_72$$63, _74$$63, _77$$63, _78$$63, _73$$64, _76$$65, _79$$67, *_80$$69, _81$$69, *_82$$69, _88$$69, _95$$69, _96$$69, itemExplode$$72, _83$$72, _84$$72, _85$$72, _86$$72, _87$$70, itemExplode$$75, _90$$75, _91$$75, _92$$75, _93$$75, _94$$73, _97$$76, _98$$82, _99$$85, _100$$85, _101$$85, _102$$85, _103$$85, _105$$86, _106$$86, _107$$86, _108$$86, _109$$86;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&modelInstance);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&firstPrimaryKey);
	ZVAL_UNDEF(&columnMap);
	ZVAL_UNDEF(&modelAlias);
	ZVAL_UNDEF(&attributeField);
	ZVAL_UNDEF(&phql);
	ZVAL_UNDEF(&column);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&selectedColumns);
	ZVAL_UNDEF(&selectedColumn);
	ZVAL_UNDEF(&selectedModel);
	ZVAL_UNDEF(&selectedModels);
	ZVAL_UNDEF(&columnAlias);
	ZVAL_UNDEF(&modelColumnAlias);
	ZVAL_UNDEF(&joins);
	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&joinModel);
	ZVAL_UNDEF(&joinConditions);
	ZVAL_UNDEF(&joinAlias);
	ZVAL_UNDEF(&joinType);
	ZVAL_UNDEF(&group);
	ZVAL_UNDEF(&groupItems);
	ZVAL_UNDEF(&groupItem);
	ZVAL_UNDEF(&having);
	ZVAL_UNDEF(&order);
	ZVAL_UNDEF(&orderItems);
	ZVAL_UNDEF(&orderItem);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&offset);
	ZVAL_UNDEF(&forUpdate);
	ZVAL_UNDEF(&distinct);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$8);
	ZVAL_UNDEF(&_3$$13);
	ZVAL_UNDEF(&_4$$13);
	ZVAL_UNDEF(&_7$$13);
	ZVAL_UNDEF(&_8$$13);
	ZVAL_UNDEF(&_5$$17);
	ZVAL_UNDEF(&_6$$17);
	ZVAL_UNDEF(&_10$$25);
	ZVAL_UNDEF(&_16$$25);
	ZVAL_UNDEF(&_20$$25);
	ZVAL_UNDEF(&_14$$28);
	ZVAL_UNDEF(&_15$$28);
	ZVAL_UNDEF(&_18$$31);
	ZVAL_UNDEF(&_19$$31);
	ZVAL_UNDEF(&_22$$34);
	ZVAL_UNDEF(&_28$$34);
	ZVAL_UNDEF(&_32$$34);
	ZVAL_UNDEF(&_26$$36);
	ZVAL_UNDEF(&_27$$37);
	ZVAL_UNDEF(&_30$$39);
	ZVAL_UNDEF(&_31$$40);
	ZVAL_UNDEF(&_33$$41);
	ZVAL_UNDEF(&_34$$41);
	ZVAL_UNDEF(&_36$$42);
	ZVAL_UNDEF(&_42$$42);
	ZVAL_UNDEF(&_46$$42);
	ZVAL_UNDEF(&_47$$42);
	ZVAL_UNDEF(&_40$$44);
	ZVAL_UNDEF(&_41$$44);
	ZVAL_UNDEF(&_44$$47);
	ZVAL_UNDEF(&_45$$47);
	ZVAL_UNDEF(&_48$$49);
	ZVAL_UNDEF(&_49$$49);
	ZVAL_UNDEF(&_51$$50);
	ZVAL_UNDEF(&_60$$50);
	ZVAL_UNDEF(&_53$$52);
	ZVAL_UNDEF(&_54$$52);
	ZVAL_UNDEF(&_55$$53);
	ZVAL_UNDEF(&_56$$53);
	ZVAL_UNDEF(&_57$$54);
	ZVAL_UNDEF(&_58$$54);
	ZVAL_UNDEF(&_59$$55);
	ZVAL_UNDEF(&_62$$57);
	ZVAL_UNDEF(&_63$$57);
	ZVAL_UNDEF(&_64$$58);
	ZVAL_UNDEF(&_65$$58);
	ZVAL_UNDEF(&_66$$59);
	ZVAL_UNDEF(&_67$$59);
	ZVAL_UNDEF(&_68$$60);
	ZVAL_UNDEF(&_69$$62);
	ZVAL_UNDEF(&_71$$63);
	ZVAL_UNDEF(&_74$$63);
	ZVAL_UNDEF(&_77$$63);
	ZVAL_UNDEF(&_78$$63);
	ZVAL_UNDEF(&_73$$64);
	ZVAL_UNDEF(&_76$$65);
	ZVAL_UNDEF(&_79$$67);
	ZVAL_UNDEF(&_81$$69);
	ZVAL_UNDEF(&_88$$69);
	ZVAL_UNDEF(&_95$$69);
	ZVAL_UNDEF(&_96$$69);
	ZVAL_UNDEF(&itemExplode$$72);
	ZVAL_UNDEF(&_83$$72);
	ZVAL_UNDEF(&_84$$72);
	ZVAL_UNDEF(&_85$$72);
	ZVAL_UNDEF(&_86$$72);
	ZVAL_UNDEF(&_87$$70);
	ZVAL_UNDEF(&itemExplode$$75);
	ZVAL_UNDEF(&_90$$75);
	ZVAL_UNDEF(&_91$$75);
	ZVAL_UNDEF(&_92$$75);
	ZVAL_UNDEF(&_93$$75);
	ZVAL_UNDEF(&_94$$73);
	ZVAL_UNDEF(&_97$$76);
	ZVAL_UNDEF(&_98$$82);
	ZVAL_UNDEF(&_99$$85);
	ZVAL_UNDEF(&_100$$85);
	ZVAL_UNDEF(&_101$$85);
	ZVAL_UNDEF(&_102$$85);
	ZVAL_UNDEF(&_103$$85);
	ZVAL_UNDEF(&_105$$86);
	ZVAL_UNDEF(&_106$$86);
	ZVAL_UNDEF(&_107$$86);
	ZVAL_UNDEF(&_108$$86);
	ZVAL_UNDEF(&_109$$86);
	ZVAL_UNDEF(&_2$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	static zend_string *_zephir_prop_9 = NULL;
	static zend_string *_zephir_prop_10 = NULL;
	static zend_string *_zephir_prop_11 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("conditions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("distinct", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("columns", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("joins", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("group", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("having", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("order", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("limit", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("offset", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("forUpdate", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&offset);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 794, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (Z_TYPE_P(&container) != IS_OBJECT) {
		ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 794, &container);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 785, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&models, &_0);
	if (Z_TYPE_P(&models) == IS_ARRAY) {
		if (UNEXPECTED(!(zephir_fast_count_int(&models)))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "At least one model is required to build the query", "phalcon/Mvc/Model/Query/Builder.zep", 712);
			return;
		}
	} else {
		if (UNEXPECTED(!zephir_is_true(&models))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "At least one model is required to build the query", "phalcon/Mvc/Model/Query/Builder.zep", 718);
			return;
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 781, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&conditions, &_0);
	if (zephir_is_numeric(&conditions)) {
		if (Z_TYPE_P(&models) == IS_ARRAY) {
			if (UNEXPECTED(zephir_fast_count_int(&models) > 1)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Cannot build the query. Invalid condition", "phalcon/Mvc/Model/Query/Builder.zep", 733);
				return;
			}
			zephir_memory_observe(&model);
			zephir_array_fetch_long(&model, &models, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 736);
		} else {
			ZEPHIR_CPY_WRT(&model, &models);
		}
		ZEPHIR_INIT_VAR(&_1$$8);
		ZVAL_STRING(&_1$$8, "modelsMetadata");
		ZEPHIR_CALL_METHOD(&metaData, &container, "getShared", NULL, 0, &_1$$8);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$8);
		zephir_create_array(&_2$$8, 2, 0);
		zephir_array_fast_append(&_2$$8, &__$null);
		zephir_array_fast_append(&_2$$8, &container);
		ZEPHIR_INIT_VAR(&modelInstance);
		ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(&modelInstance, &model, &_2$$8);
		zephir_check_call_status();
		noPrimary = 1;
		ZEPHIR_CALL_METHOD(&primaryKeys, &metaData, "getPrimaryKeyAttributes", NULL, 0, &modelInstance);
		zephir_check_call_status();
		if (zephir_fast_count_int(&primaryKeys)) {
			zephir_memory_observe(&firstPrimaryKey);
			if (zephir_array_isset_long_fetch(&firstPrimaryKey, &primaryKeys, 0, 0)) {
				ZEPHIR_INIT_VAR(&_4$$13);
				ZVAL_STRING(&_4$$13, "orm.column_renaming");
				ZEPHIR_CALL_CE_STATIC(&_3$$13, phalcon_support_settings_ce, "get", NULL, 0, &_4$$13);
				zephir_check_call_status();
				if (zephir_is_true(&_3$$13)) {
					ZEPHIR_CALL_METHOD(&columnMap, &metaData, "getColumnMap", NULL, 0, &modelInstance);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(&columnMap);
					ZVAL_NULL(&columnMap);
				}
				if (Z_TYPE_P(&columnMap) == IS_ARRAY) {
					zephir_memory_observe(&attributeField);
					if (UNEXPECTED(!(zephir_array_isset_fetch(&attributeField, &columnMap, &firstPrimaryKey, 0)))) {
						ZEPHIR_INIT_VAR(&_5$$17);
						object_init_ex(&_5$$17, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_VAR(&_6$$17);
						ZEPHIR_CONCAT_SVS(&_6$$17, "Column '", &firstPrimaryKey, "' isn't part of the column map");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_5$$17, "__construct", NULL, 32, &_6$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_5$$17, "phalcon/Mvc/Model/Query/Builder.zep", 772);
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&attributeField, &firstPrimaryKey);
				}
				ZEPHIR_INIT_NVAR(&_4$$13);
				ZVAL_STRING(&_4$$13, "APK0");
				zephir_update_property_array(this_ptr, SL("bindParams"), &_4$$13, &conditions);
				ZEPHIR_CALL_METHOD(&_7$$13, this_ptr, "autoescape", NULL, 0, &model);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_8$$13, this_ptr, "autoescape", NULL, 0, &attributeField);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&conditions);
				ZEPHIR_CONCAT_VSVS(&conditions, &_7$$13, ".", &_8$$13, " = :APK0:");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				noPrimary = 0;
			}
		}
		if (UNEXPECTED(noPrimary)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Source related to this model does not have a primary key defined", "phalcon/Mvc/Model/Query/Builder.zep", 796);
			return;
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 784, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&distinct, &_0);
	if (((Z_TYPE_P(&distinct) == IS_TRUE || Z_TYPE_P(&distinct) == IS_FALSE) == 1)) {
		ZEPHIR_INIT_VAR(&phql);
		if (zephir_is_true(&distinct)) {
			ZVAL_STRING(&phql, "SELECT DISTINCT ");
		} else {
			ZVAL_STRING(&phql, "SELECT ALL ");
		}
	} else {
		ZEPHIR_INIT_NVAR(&phql);
		ZVAL_STRING(&phql, "SELECT ");
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 786, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&columns, &_0);
	if (Z_TYPE_P(&columns) != IS_NULL) {
		if (Z_TYPE_P(&columns) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&selectedColumns);
			array_init(&selectedColumns);
			if (Z_TYPE_P(&columns) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_10$$25);
				zephir_string_to_char_array(&_10$$25, &columns);
				_9$$25 = &_10$$25;
			} else {
				_9$$25 = &columns;
			}
			zephir_is_iterable(_9$$25, 0, "phalcon/Mvc/Model/Query/Builder.zep", 829);
			if (Z_TYPE_P(_9$$25) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9$$25), _12$$25, _13$$25, _11$$25)
				{
					ZEPHIR_INIT_NVAR(&columnAlias);
					if (_13$$25 != NULL) { 
						ZVAL_STR_COPY(&columnAlias, _13$$25);
					} else {
						ZVAL_LONG(&columnAlias, _12$$25);
					}
					ZEPHIR_INIT_NVAR(&column);
					ZVAL_COPY(&column, _11$$25);
					if (Z_TYPE_P(&columnAlias) == IS_LONG) {
						zephir_array_append(&selectedColumns, &column, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 823);
					} else {
						ZEPHIR_CALL_METHOD(&_14$$28, this_ptr, "autoescape", NULL, 0, &columnAlias);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_15$$28);
						ZEPHIR_CONCAT_VSV(&_15$$28, &column, " AS ", &_14$$28);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&selectedColumns, &_15$$28, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 825);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9$$25, "rewind", NULL, 0);
				zephir_check_call_status();
				_17$$25 = 1;
				while (1) {
					if (_17$$25) {
						_17$$25 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _9$$25, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_16$$25, _9$$25, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_16$$25)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&columnAlias, _9$$25, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&column, _9$$25, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&columnAlias) == IS_LONG) {
							zephir_array_append(&selectedColumns, &column, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 823);
						} else {
							ZEPHIR_CALL_METHOD(&_18$$31, this_ptr, "autoescape", NULL, 0, &columnAlias);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_19$$31);
							ZEPHIR_CONCAT_VSV(&_19$$31, &column, " AS ", &_18$$31);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&selectedColumns, &_19$$31, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 825);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&column);
			ZEPHIR_INIT_NVAR(&columnAlias);
			ZEPHIR_INIT_VAR(&_20$$25);
			zephir_fast_join_str(&_20$$25, SL(", "), &selectedColumns);
			zephir_concat_self(&phql, &_20$$25);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_concat_self(&phql, &columns);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	} else {
		if (Z_TYPE_P(&models) == IS_ARRAY) {
			ZEPHIR_INIT_NVAR(&selectedColumns);
			array_init(&selectedColumns);
			if (Z_TYPE_P(&models) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_22$$34);
				zephir_string_to_char_array(&_22$$34, &models);
				_21$$34 = &_22$$34;
			} else {
				_21$$34 = &models;
			}
			zephir_is_iterable(_21$$34, 0, "phalcon/Mvc/Model/Query/Builder.zep", 850);
			if (Z_TYPE_P(_21$$34) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_21$$34), _24$$34, _25$$34, _23$$34)
				{
					ZEPHIR_INIT_NVAR(&modelColumnAlias);
					if (_25$$34 != NULL) { 
						ZVAL_STR_COPY(&modelColumnAlias, _25$$34);
					} else {
						ZVAL_LONG(&modelColumnAlias, _24$$34);
					}
					ZEPHIR_INIT_NVAR(&model);
					ZVAL_COPY(&model, _23$$34);
					ZEPHIR_INIT_NVAR(&selectedColumn);
					if (Z_TYPE_P(&modelColumnAlias) == IS_LONG) {
						ZEPHIR_CALL_METHOD(&_26$$36, this_ptr, "autoescape", NULL, 0, &model);
						zephir_check_call_status();
						ZEPHIR_CONCAT_VS(&selectedColumn, &_26$$36, ".*");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CALL_METHOD(&_27$$37, this_ptr, "autoescape", NULL, 0, &modelColumnAlias);
						zephir_check_call_status();
						ZEPHIR_CONCAT_VS(&selectedColumn, &_27$$37, ".*");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					zephir_array_append(&selectedColumns, &selectedColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 847);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _21$$34, "rewind", NULL, 0);
				zephir_check_call_status();
				_29$$34 = 1;
				while (1) {
					if (_29$$34) {
						_29$$34 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _21$$34, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_28$$34, _21$$34, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_28$$34)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&modelColumnAlias, _21$$34, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&model, _21$$34, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&selectedColumn);
						if (Z_TYPE_P(&modelColumnAlias) == IS_LONG) {
							ZEPHIR_CALL_METHOD(&_30$$39, this_ptr, "autoescape", NULL, 0, &model);
							zephir_check_call_status();
							ZEPHIR_CONCAT_VS(&selectedColumn, &_30$$39, ".*");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZEPHIR_CALL_METHOD(&_31$$40, this_ptr, "autoescape", NULL, 0, &modelColumnAlias);
							zephir_check_call_status();
							ZEPHIR_CONCAT_VS(&selectedColumn, &_31$$40, ".*");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
						zephir_array_append(&selectedColumns, &selectedColumn, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 847);
				}
			}
			ZEPHIR_INIT_NVAR(&model);
			ZEPHIR_INIT_NVAR(&modelColumnAlias);
			ZEPHIR_INIT_VAR(&_32$$34);
			zephir_fast_join_str(&_32$$34, SL(", "), &selectedColumns);
			zephir_concat_self(&phql, &_32$$34);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CALL_METHOD(&_33$$41, this_ptr, "autoescape", NULL, 0, &models);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_34$$41);
			ZEPHIR_CONCAT_VS(&_34$$41, &_33$$41, ".*");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&phql, &_34$$41);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	if (Z_TYPE_P(&models) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&selectedModels);
		array_init(&selectedModels);
		if (Z_TYPE_P(&models) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_36$$42);
			zephir_string_to_char_array(&_36$$42, &models);
			_35$$42 = &_36$$42;
		} else {
			_35$$42 = &models;
		}
		zephir_is_iterable(_35$$42, 0, "phalcon/Mvc/Model/Query/Builder.zep", 872);
		if (Z_TYPE_P(_35$$42) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_35$$42), _38$$42, _39$$42, _37$$42)
			{
				ZEPHIR_INIT_NVAR(&modelAlias);
				if (_39$$42 != NULL) { 
					ZVAL_STR_COPY(&modelAlias, _39$$42);
				} else {
					ZVAL_LONG(&modelAlias, _38$$42);
				}
				ZEPHIR_INIT_NVAR(&model);
				ZVAL_COPY(&model, _37$$42);
				if (Z_TYPE_P(&modelAlias) == IS_STRING) {
					ZEPHIR_CALL_METHOD(&_40$$44, this_ptr, "autoescape", NULL, 0, &model);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_41$$44, this_ptr, "autoescape", NULL, 0, &modelAlias);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&selectedModel);
					ZEPHIR_CONCAT_VSV(&selectedModel, &_40$$44, " AS ", &_41$$44);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CALL_METHOD(&selectedModel, this_ptr, "autoescape", NULL, 0, &model);
					zephir_check_call_status();
				}
				zephir_array_append(&selectedModels, &selectedModel, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 869);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _35$$42, "rewind", NULL, 0);
			zephir_check_call_status();
			_43$$42 = 1;
			while (1) {
				if (_43$$42) {
					_43$$42 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _35$$42, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_42$$42, _35$$42, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_42$$42)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&modelAlias, _35$$42, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&model, _35$$42, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&modelAlias) == IS_STRING) {
						ZEPHIR_CALL_METHOD(&_44$$47, this_ptr, "autoescape", NULL, 0, &model);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_45$$47, this_ptr, "autoescape", NULL, 0, &modelAlias);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&selectedModel);
						ZEPHIR_CONCAT_VSV(&selectedModel, &_44$$47, " AS ", &_45$$47);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CALL_METHOD(&selectedModel, this_ptr, "autoescape", NULL, 0, &model);
						zephir_check_call_status();
					}
					zephir_array_append(&selectedModels, &selectedModel, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 869);
			}
		}
		ZEPHIR_INIT_NVAR(&model);
		ZEPHIR_INIT_NVAR(&modelAlias);
		ZEPHIR_INIT_VAR(&_46$$42);
		zephir_fast_join_str(&_46$$42, SL(", "), &selectedModels);
		ZEPHIR_INIT_VAR(&_47$$42);
		ZEPHIR_CONCAT_SV(&_47$$42, " FROM ", &_46$$42);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&phql, &_47$$42);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(&_48$$49, this_ptr, "autoescape", NULL, 0, &models);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_49$$49);
		ZEPHIR_CONCAT_SV(&_49$$49, " FROM ", &_48$$49);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&phql, &_49$$49);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_5, 787, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&joins, &_0);
	if (Z_TYPE_P(&joins) == IS_ARRAY) {
		if (Z_TYPE_P(&joins) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_51$$50);
			zephir_string_to_char_array(&_51$$50, &joins);
			_50$$50 = &_51$$50;
		} else {
			_50$$50 = &joins;
		}
		zephir_is_iterable(_50$$50, 0, "phalcon/Mvc/Model/Query/Builder.zep", 927);
		if (Z_TYPE_P(_50$$50) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_50$$50), _52$$50)
			{
				ZEPHIR_INIT_NVAR(&join);
				ZVAL_COPY(&join, _52$$50);
				ZEPHIR_OBS_NVAR(&joinModel);
				zephir_array_fetch_long(&joinModel, &join, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 887);
				ZEPHIR_OBS_NVAR(&joinConditions);
				zephir_array_fetch_long(&joinConditions, &join, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 892);
				ZEPHIR_OBS_NVAR(&joinAlias);
				zephir_array_fetch_long(&joinAlias, &join, 2, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 897);
				ZEPHIR_OBS_NVAR(&joinType);
				zephir_array_fetch_long(&joinType, &join, 3, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 902);
				if (zephir_is_true(&joinType)) {
					ZEPHIR_CALL_METHOD(&_53$$52, this_ptr, "autoescape", NULL, 0, &joinModel);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_54$$52);
					ZEPHIR_CONCAT_SVSV(&_54$$52, " ", &joinType, " JOIN ", &_53$$52);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&phql, &_54$$52);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CALL_METHOD(&_55$$53, this_ptr, "autoescape", NULL, 0, &joinModel);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_56$$53);
					ZEPHIR_CONCAT_SV(&_56$$53, " JOIN ", &_55$$53);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&phql, &_56$$53);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				if (zephir_is_true(&joinAlias)) {
					ZEPHIR_CALL_METHOD(&_57$$54, this_ptr, "autoescape", NULL, 0, &joinAlias);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_58$$54);
					ZEPHIR_CONCAT_SV(&_58$$54, " AS ", &_57$$54);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&phql, &_58$$54);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				if (zephir_is_true(&joinConditions)) {
					ZEPHIR_INIT_NVAR(&_59$$55);
					ZEPHIR_CONCAT_SV(&_59$$55, " ON ", &joinConditions);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&phql, &_59$$55);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _50$$50, "rewind", NULL, 0);
			zephir_check_call_status();
			_61$$50 = 1;
			while (1) {
				if (_61$$50) {
					_61$$50 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _50$$50, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_60$$50, _50$$50, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_60$$50)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&join, _50$$50, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&joinModel);
					zephir_array_fetch_long(&joinModel, &join, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 887);
					ZEPHIR_OBS_NVAR(&joinConditions);
					zephir_array_fetch_long(&joinConditions, &join, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 892);
					ZEPHIR_OBS_NVAR(&joinAlias);
					zephir_array_fetch_long(&joinAlias, &join, 2, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 897);
					ZEPHIR_OBS_NVAR(&joinType);
					zephir_array_fetch_long(&joinType, &join, 3, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 902);
					if (zephir_is_true(&joinType)) {
						ZEPHIR_CALL_METHOD(&_62$$57, this_ptr, "autoescape", NULL, 0, &joinModel);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_63$$57);
						ZEPHIR_CONCAT_SVSV(&_63$$57, " ", &joinType, " JOIN ", &_62$$57);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&phql, &_63$$57);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CALL_METHOD(&_64$$58, this_ptr, "autoescape", NULL, 0, &joinModel);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_65$$58);
						ZEPHIR_CONCAT_SV(&_65$$58, " JOIN ", &_64$$58);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&phql, &_65$$58);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					if (zephir_is_true(&joinAlias)) {
						ZEPHIR_CALL_METHOD(&_66$$59, this_ptr, "autoescape", NULL, 0, &joinAlias);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_67$$59);
						ZEPHIR_CONCAT_SV(&_67$$59, " AS ", &_66$$59);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&phql, &_67$$59);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					if (zephir_is_true(&joinConditions)) {
						ZEPHIR_INIT_NVAR(&_68$$60);
						ZEPHIR_CONCAT_SV(&_68$$60, " ON ", &joinConditions);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&phql, &_68$$60);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
			}
		}
		ZEPHIR_INIT_NVAR(&join);
	}
	if (Z_TYPE_P(&conditions) == IS_STRING) {
		if (!(ZEPHIR_IS_EMPTY(&conditions))) {
			ZEPHIR_INIT_VAR(&_69$$62);
			ZEPHIR_CONCAT_SV(&_69$$62, " WHERE ", &conditions);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&phql, &_69$$62);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_6, 795, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&group, &_0);
	if (!(ZEPHIR_IS_EMPTY(&group))) {
		ZEPHIR_INIT_VAR(&groupItems);
		array_init(&groupItems);
		if (Z_TYPE_P(&group) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_71$$63);
			zephir_string_to_char_array(&_71$$63, &group);
			_70$$63 = &_71$$63;
		} else {
			_70$$63 = &group;
		}
		zephir_is_iterable(_70$$63, 0, "phalcon/Mvc/Model/Query/Builder.zep", 947);
		if (Z_TYPE_P(_70$$63) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_70$$63), _72$$63)
			{
				ZEPHIR_INIT_NVAR(&groupItem);
				ZVAL_COPY(&groupItem, _72$$63);
				ZEPHIR_CALL_METHOD(&_73$$64, this_ptr, "autoescape", NULL, 0, &groupItem);
				zephir_check_call_status();
				zephir_array_append(&groupItems, &_73$$64, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 944);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _70$$63, "rewind", NULL, 0);
			zephir_check_call_status();
			_75$$63 = 1;
			while (1) {
				if (_75$$63) {
					_75$$63 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _70$$63, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_74$$63, _70$$63, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_74$$63)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&groupItem, _70$$63, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_76$$65, this_ptr, "autoescape", NULL, 0, &groupItem);
					zephir_check_call_status();
					zephir_array_append(&groupItems, &_76$$65, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 944);
			}
		}
		ZEPHIR_INIT_NVAR(&groupItem);
		ZEPHIR_INIT_VAR(&_77$$63);
		zephir_fast_join_str(&_77$$63, SL(", "), &groupItems);
		ZEPHIR_INIT_VAR(&_78$$63);
		ZEPHIR_CONCAT_SV(&_78$$63, " GROUP BY ", &_77$$63);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&phql, &_78$$63);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_7, 788, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&having, &_0);
	if (Z_TYPE_P(&having) != IS_NULL) {
		if (!(ZEPHIR_IS_EMPTY(&having))) {
			ZEPHIR_INIT_VAR(&_79$$67);
			ZEPHIR_CONCAT_SV(&_79$$67, " HAVING ", &having);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&phql, &_79$$67);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_8, 789, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&order, &_0);
	if (Z_TYPE_P(&order) != IS_NULL) {
		if (Z_TYPE_P(&order) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&orderItems);
			array_init(&orderItems);
			if (Z_TYPE_P(&order) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_81$$69);
				zephir_string_to_char_array(&_81$$69, &order);
				_80$$69 = &_81$$69;
			} else {
				_80$$69 = &order;
			}
			zephir_is_iterable(_80$$69, 0, "phalcon/Mvc/Model/Query/Builder.zep", 991);
			if (Z_TYPE_P(_80$$69) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_80$$69), _82$$69)
				{
					ZEPHIR_INIT_NVAR(&orderItem);
					ZVAL_COPY(&orderItem, _82$$69);
					if (Z_TYPE_P(&orderItem) == IS_LONG) {
						zephir_array_append(&orderItems, &orderItem, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 974);
						continue;
					}
					if (zephir_memnstr_str(&orderItem, SL(" "), "phalcon/Mvc/Model/Query/Builder.zep", 979) != 0) {
						ZEPHIR_INIT_NVAR(&itemExplode$$72);
						zephir_fast_explode_str(&itemExplode$$72, SL(" "), &orderItem, NULL);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CPY_WRT(&itemExplode$$72, &itemExplode$$72);
						ZEPHIR_OBS_NVAR(&_84$$72);
						zephir_array_fetch_long(&_84$$72, &itemExplode$$72, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 983);
						ZEPHIR_CALL_METHOD(&_83$$72, this_ptr, "autoescape", NULL, 0, &_84$$72);
						zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&_85$$72);
						zephir_array_fetch_long(&_85$$72, &itemExplode$$72, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 983);
						ZEPHIR_INIT_NVAR(&_86$$72);
						ZEPHIR_CONCAT_VSV(&_86$$72, &_83$$72, " ", &_85$$72);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&orderItems, &_86$$72, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 983);
						continue;
					}
					ZEPHIR_CALL_METHOD(&_87$$70, this_ptr, "autoescape", NULL, 0, &orderItem);
					zephir_check_call_status();
					zephir_array_append(&orderItems, &_87$$70, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 988);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _80$$69, "rewind", NULL, 0);
				zephir_check_call_status();
				_89$$69 = 1;
				while (1) {
					if (_89$$69) {
						_89$$69 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _80$$69, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_88$$69, _80$$69, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_88$$69)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&orderItem, _80$$69, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&orderItem) == IS_LONG) {
							zephir_array_append(&orderItems, &orderItem, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 974);
							continue;
						}
						if (zephir_memnstr_str(&orderItem, SL(" "), "phalcon/Mvc/Model/Query/Builder.zep", 979) != 0) {
							ZEPHIR_INIT_NVAR(&itemExplode$$75);
							zephir_fast_explode_str(&itemExplode$$75, SL(" "), &orderItem, NULL);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CPY_WRT(&itemExplode$$75, &itemExplode$$75);
							ZEPHIR_OBS_NVAR(&_91$$75);
							zephir_array_fetch_long(&_91$$75, &itemExplode$$75, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 983);
							ZEPHIR_CALL_METHOD(&_90$$75, this_ptr, "autoescape", NULL, 0, &_91$$75);
							zephir_check_call_status();
							ZEPHIR_OBS_NVAR(&_92$$75);
							zephir_array_fetch_long(&_92$$75, &itemExplode$$75, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 983);
							ZEPHIR_INIT_NVAR(&_93$$75);
							ZEPHIR_CONCAT_VSV(&_93$$75, &_90$$75, " ", &_92$$75);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&orderItems, &_93$$75, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 983);
							continue;
						}
						ZEPHIR_CALL_METHOD(&_94$$73, this_ptr, "autoescape", NULL, 0, &orderItem);
						zephir_check_call_status();
						zephir_array_append(&orderItems, &_94$$73, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 988);
				}
			}
			ZEPHIR_INIT_NVAR(&orderItem);
			ZEPHIR_INIT_VAR(&_95$$69);
			zephir_fast_join_str(&_95$$69, SL(", "), &orderItems);
			ZEPHIR_INIT_VAR(&_96$$69);
			ZEPHIR_CONCAT_SV(&_96$$69, " ORDER BY ", &_95$$69);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&phql, &_96$$69);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_VAR(&_97$$76);
			ZEPHIR_CONCAT_SV(&_97$$76, " ORDER BY ", &order);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&phql, &_97$$76);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_9, 790, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&limit, &_0);
	if (Z_TYPE_P(&limit) != IS_NULL) {
		ZEPHIR_INIT_VAR(&number);
		ZVAL_NULL(&number);
		if (Z_TYPE_P(&limit) == IS_ARRAY) {
			ZEPHIR_OBS_NVAR(&number);
			zephir_array_fetch_string(&number, &limit, SL("number"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1005);
			ZEPHIR_OBS_NVAR(&offset);
			if (zephir_array_isset_string_fetch(&offset, &limit, SL("offset"), 0)) {
				if (!(zephir_is_numeric(&offset))) {
					ZEPHIR_INIT_NVAR(&offset);
					ZVAL_LONG(&offset, 0);
				}
			}
		} else {
			if (zephir_is_numeric(&limit)) {
				ZEPHIR_CPY_WRT(&number, &limit);
				zephir_read_property_cached(&_98$$82, this_ptr, _zephir_prop_10, 791, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&offset, &_98$$82);
				if (Z_TYPE_P(&offset) != IS_NULL) {
					if (!(zephir_is_numeric(&offset))) {
						ZEPHIR_INIT_NVAR(&offset);
						ZVAL_LONG(&offset, 0);
					}
				}
			}
		}
		if (zephir_is_numeric(&number)) {
			zephir_concat_self_str(&phql, SL(" LIMIT :APL0:"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZVAL_LONG(&_99$$85, 10);
			ZEPHIR_CALL_FUNCTION(&_100$$85, "intval", NULL, 41, &number, &_99$$85);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_101$$85);
			ZVAL_STRING(&_101$$85, "APL0");
			zephir_update_property_array(this_ptr, SL("bindParams"), &_101$$85, &_100$$85);
			ZEPHIR_INIT_VAR(&_102$$85);
			ZVAL_STRING(&_102$$85, "APL0");
			ZEPHIR_INIT_VAR(&_103$$85);
			ZVAL_LONG(&_103$$85, 1);
			zephir_update_property_array(this_ptr, SL("bindTypes"), &_102$$85, &_103$$85);
			_104$$85 = zephir_is_numeric(&offset);
			if (_104$$85) {
				_104$$85 = !ZEPHIR_IS_LONG_IDENTICAL(&offset, 0);
			}
			if (_104$$85) {
				zephir_concat_self_str(&phql, SL(" OFFSET :APL1:"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZVAL_LONG(&_105$$86, 10);
				ZEPHIR_CALL_FUNCTION(&_106$$86, "intval", NULL, 41, &offset, &_105$$86);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_107$$86);
				ZVAL_STRING(&_107$$86, "APL1");
				zephir_update_property_array(this_ptr, SL("bindParams"), &_107$$86, &_106$$86);
				ZEPHIR_INIT_VAR(&_108$$86);
				ZVAL_STRING(&_108$$86, "APL1");
				ZEPHIR_INIT_VAR(&_109$$86);
				ZVAL_LONG(&_109$$86, 1);
				zephir_update_property_array(this_ptr, SL("bindTypes"), &_108$$86, &_109$$86);
			}
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_11, 792, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&forUpdate, &_0);
	if (((Z_TYPE_P(&forUpdate) == IS_TRUE || Z_TYPE_P(&forUpdate) == IS_FALSE) == 1)) {
		if (zephir_is_true(&forUpdate)) {
			zephir_concat_self_str(&phql, SL(" FOR UPDATE"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CCTOR(&phql);
}

/**
 * Returns the query built
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getQuery)
{
	zval _13, _4$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null, query, bindParams, bindTypes, phql, container, compiled, _0, _1, _11, _12, _14, _2$$3, _3$$3, _5$$3, _6$$3, _7$$3, _8$$3, _9$$3, _10$$4, _15$$8;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&phql);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&compiled);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_4$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("sharedLock", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("bindTypes", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "orm.native_compiler");
	ZEPHIR_CALL_CE_STATIC(&_0, phalcon_support_settings_ce, "get", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(&compiled, this_ptr, "compileIntermediate", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 794, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&container, &_2$$3);
		ZEPHIR_INIT_VAR(&_4$$3);
		zephir_create_array(&_4$$3, 2, 0);
		zephir_array_fast_append(&_4$$3, &__$null);
		zephir_array_fast_append(&_4$$3, &container);
		ZEPHIR_INIT_VAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "Phalcon\\Mvc\\Model\\Query");
		ZEPHIR_CALL_METHOD(&_3$$3, &container, "get", NULL, 0, &_5$$3, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&query, &_3$$3);
		ZVAL_LONG(&_2$$3, 309);
		ZEPHIR_CALL_METHOD(NULL, &query, "setType", NULL, 0, &_2$$3);
		zephir_check_call_status();
		zephir_memory_observe(&_6$$3);
		zephir_array_fetch_string(&_6$$3, &compiled, SL("intermediate"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1072);
		ZEPHIR_CALL_METHOD(NULL, &query, "setIntermediate", NULL, 0, &_6$$3);
		zephir_check_call_status();
		zephir_memory_observe(&_7$$3);
		zephir_array_fetch_string(&_7$$3, &compiled, SL("bindParams"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1073);
		ZEPHIR_CALL_METHOD(NULL, &query, "setBindParams", NULL, 0, &_7$$3);
		zephir_check_call_status();
		zephir_memory_observe(&_8$$3);
		zephir_array_fetch_string(&_8$$3, &compiled, SL("bindTypes"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1074);
		ZEPHIR_CALL_METHOD(NULL, &query, "setBindTypes", NULL, 0, &_8$$3);
		zephir_check_call_status();
		zephir_memory_observe(&_9$$3);
		zephir_read_property_cached(&_9$$3, this_ptr, _zephir_prop_1, 793, PH_NOISY_CC);
		if (((Z_TYPE_P(&_9$$3) == IS_TRUE || Z_TYPE_P(&_9$$3) == IS_FALSE) == 1)) {
			zephir_read_property_cached(&_10$$4, this_ptr, _zephir_prop_1, 793, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &query, "setSharedLock", NULL, 0, &_10$$4);
			zephir_check_call_status();
		}
		RETURN_CCTOR(&query);
	}
	ZEPHIR_CALL_METHOD(&phql, this_ptr, "getPhql", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_0, 794, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_11);
	if (UNEXPECTED(Z_TYPE_P(&container) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "A dependency injection container is required to access the services related to the ORM", "phalcon/Mvc/Model/Query/Builder.zep", 1090);
		return;
	}
	ZEPHIR_INIT_VAR(&_13);
	zephir_create_array(&_13, 2, 0);
	zephir_array_fast_append(&_13, &phql);
	zephir_array_fast_append(&_13, &container);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "Phalcon\\Mvc\\Model\\Query");
	ZEPHIR_CALL_METHOD(&_12, &container, "get", NULL, 0, &_1, &_13);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&query, &_12);
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_2, 782, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&bindParams, &_11);
	if (Z_TYPE_P(&bindParams) == IS_ARRAY) {
		ZEPHIR_CALL_METHOD(NULL, &query, "setBindParams", NULL, 0, &bindParams);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_3, 783, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&bindTypes, &_11);
	if (Z_TYPE_P(&bindTypes) == IS_ARRAY) {
		ZEPHIR_CALL_METHOD(NULL, &query, "setBindTypes", NULL, 0, &bindTypes);
		zephir_check_call_status();
	}
	zephir_memory_observe(&_14);
	zephir_read_property_cached(&_14, this_ptr, _zephir_prop_1, 793, PH_NOISY_CC);
	if (((Z_TYPE_P(&_14) == IS_TRUE || Z_TYPE_P(&_14) == IS_FALSE) == 1)) {
		zephir_read_property_cached(&_15$$8, this_ptr, _zephir_prop_1, 793, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &query, "setSharedLock", NULL, 0, &_15$$8);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&query);
}

/**
 * Return the conditions for the query
 *
 * @return array|string
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, getWhere)
{

	RETURN_MEMBER(getThis(), "conditions");
}

/**
 * Sets a GROUP BY clause
 *
 *```php
 * $builder->groupBy(
 *     [
 *         "Robots.name",
 *     ]
 * );
 *```
 *
 * @param array|string group
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, groupBy)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *group = NULL, group_sub, _0$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&group_sub);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("group", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(group)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &group);
	ZEPHIR_SEPARATE_PARAM(group);
	if (Z_TYPE_P(group) == IS_STRING) {
		ZEPHIR_CALL_CE_STATIC(&_0$$3, phalcon_mvc_model_query_fragmentrewriter_ce, "splitList", NULL, 0, group);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(group, &_0$$3);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 795, group);
	RETURN_THIS();
}

/**
 * Sets the HAVING condition clause
 *
 *```php
 * $builder->having("SUM(Robots.price) > 0");
 *
 * $builder->having(
 *     "SUM(Robots.price) > :sum:",
 *     [
 *         "sum" => 100,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, having)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval bindParams, bindTypes;
	zval conditions_zv, *bindParams_param = NULL, *bindTypes_param = NULL, currentBindParams, currentBindTypes, _0$$3, _1$$5;
	zend_string *conditions = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&conditions_zv);
	ZVAL_UNDEF(&currentBindParams);
	ZVAL_UNDEF(&currentBindTypes);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("having", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindTypes", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(conditions)
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
	zephir_memory_observe(&conditions_zv);
	ZVAL_STR_COPY(&conditions_zv, conditions);
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 788, &conditions_zv);
	zephir_memory_observe(&currentBindParams);
	zephir_read_property_cached(&currentBindParams, this_ptr, _zephir_prop_1, 782, PH_NOISY_CC);
	if (Z_TYPE_P(&currentBindParams) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_add_function(&_0$$3, &currentBindParams, &bindParams);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 782, &_0$$3);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 782, &bindParams);
	}
	zephir_memory_observe(&currentBindTypes);
	zephir_read_property_cached(&currentBindTypes, this_ptr, _zephir_prop_2, 783, PH_NOISY_CC);
	if (Z_TYPE_P(&currentBindTypes) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_1$$5);
		zephir_add_function(&_1$$5, &currentBindTypes, &bindTypes);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 783, &_1$$5);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 783, &bindTypes);
	}
	RETURN_THIS();
}

/**
 * Appends an IN condition to the current HAVING conditions clause
 *
 *```php
 * $builder->inHaving("SUM(Robots.price)", [100, 200]);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, inHaving)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval values;
	zval expr_zv, *values_param = NULL, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(expr)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		operator_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Having");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionIn", NULL, 0, &_0, &operator, &expr_zv, &values);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds an INNER join to the query
 *
 *```php
 * // Inner Join model 'Robots' with automatic conditions and alias
 * $builder->innerJoin(
 *     Robots::class
 * );
 *
 * // Inner Join model 'Robots' specifying conditions
 * $builder->innerJoin(
 *     Robots::class,
 *     "Robots.id = RobotsParts.robots_id"
 * );
 *
 * // Inner Join model 'Robots' specifying conditions and alias
 * $builder->innerJoin(
 *     Robots::class,
 *     "r.id = RobotsParts.robots_id",
 *     "r"
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, innerJoin)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval model_zv, conditions_zv, alias_zv, _1;
	zend_string *model = NULL, *conditions = NULL, *alias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_zv);
	ZVAL_UNDEF(&conditions_zv);
	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(model)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(conditions)
		Z_PARAM_STR_OR_NULL(alias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&model_zv);
	ZVAL_STR_COPY(&model_zv, model);
	if (!conditions) {
		ZEPHIR_INIT_VAR(&conditions_zv);
	} else {
		zephir_memory_observe(&conditions_zv);
	ZVAL_STR_COPY(&conditions_zv, conditions);
	}
	if (!alias) {
		ZEPHIR_INIT_VAR(&alias_zv);
	} else {
		zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0);
	zephir_array_fast_append(&_0, &model_zv);
	zephir_array_fast_append(&_0, &conditions_zv);
	zephir_array_fast_append(&_0, &alias_zv);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "INNER");
	zephir_array_fast_append(&_0, &_1);
	zephir_update_property_array_append(this_ptr, SL("joins"), &_0);
	RETURN_THIS();
}

/**
 * Appends an IN condition to the current WHERE conditions
 *
 *```php
 * $builder->inWhere(
 *     "id",
 *     [1, 2, 3]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, inWhere)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval values;
	zval expr_zv, *values_param = NULL, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(expr)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		operator_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Where");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionIn", NULL, 0, &_0, &operator, &expr_zv, &values);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds an :type: join (by default type - INNER) to the query
 *
 *```php
 * // Inner Join model 'Robots' with automatic conditions and alias
 * $builder->join(
 *     Robots::class
 * );
 *
 * // Inner Join model 'Robots' specifying conditions
 * $builder->join(
 *     Robots::class,
 *     "Robots.id = RobotsParts.robots_id"
 * );
 *
 * // Inner Join model 'Robots' specifying conditions and alias
 * $builder->join(
 *     Robots::class,
 *     "r.id = RobotsParts.robots_id",
 *     "r"
 * );
 *
 * // Left Join model 'Robots' specifying conditions, alias and type of join
 * $builder->join(
 *     Robots::class,
 *     "r.id = RobotsParts.robots_id",
 *     "r",
 *     "LEFT"
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, join)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval model_zv, conditions_zv, alias_zv, type_zv;
	zend_string *model = NULL, *conditions = NULL, *alias = NULL, *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_zv);
	ZVAL_UNDEF(&conditions_zv);
	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(model)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(conditions)
		Z_PARAM_STR_OR_NULL(alias)
		Z_PARAM_STR_OR_NULL(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&model_zv);
	ZVAL_STR_COPY(&model_zv, model);
	if (!conditions) {
		ZEPHIR_INIT_VAR(&conditions_zv);
	} else {
		zephir_memory_observe(&conditions_zv);
	ZVAL_STR_COPY(&conditions_zv, conditions);
	}
	if (!alias) {
		ZEPHIR_INIT_VAR(&alias_zv);
	} else {
		zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	}
	if (!type) {
		ZEPHIR_INIT_VAR(&type_zv);
	} else {
		zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0);
	zephir_array_fast_append(&_0, &model_zv);
	zephir_array_fast_append(&_0, &conditions_zv);
	zephir_array_fast_append(&_0, &alias_zv);
	zephir_array_fast_append(&_0, &type_zv);
	zephir_update_property_array_append(this_ptr, SL("joins"), &_0);
	RETURN_THIS();
}

/**
 * Adds a LEFT join to the query
 *
 *```php
 * $builder->leftJoin(
 *     Robots::class,
 *     "r.id = RobotsParts.robots_id",
 *     "r"
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, leftJoin)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval model_zv, conditions_zv, alias_zv, _1;
	zend_string *model = NULL, *conditions = NULL, *alias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_zv);
	ZVAL_UNDEF(&conditions_zv);
	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(model)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(conditions)
		Z_PARAM_STR_OR_NULL(alias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&model_zv);
	ZVAL_STR_COPY(&model_zv, model);
	if (!conditions) {
		ZEPHIR_INIT_VAR(&conditions_zv);
	} else {
		zephir_memory_observe(&conditions_zv);
	ZVAL_STR_COPY(&conditions_zv, conditions);
	}
	if (!alias) {
		ZEPHIR_INIT_VAR(&alias_zv);
	} else {
		zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0);
	zephir_array_fast_append(&_0, &model_zv);
	zephir_array_fast_append(&_0, &conditions_zv);
	zephir_array_fast_append(&_0, &alias_zv);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "LEFT");
	zephir_array_fast_append(&_0, &_1);
	zephir_update_property_array_append(this_ptr, SL("joins"), &_0);
	RETURN_THIS();
}

/**
 * Sets a LIMIT clause, optionally an offset clause
 *
 * ```php
 * $builder->limit(100);
 * $builder->limit(100, 20);
 * $builder->limit("100", "20");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, limit)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *limit_param = NULL, *offset = NULL, offset_sub, __$null, _0, _1, _2$$4, _3$$4;
	zend_long limit, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&offset_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("limit", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("offset", 6, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_LONG(limit)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &limit_param, &offset);
	if (!offset) {
		offset = &offset_sub;
		offset = &__$null;
	}
	ZVAL_LONG(&_0, limit);
	ZEPHIR_CALL_FUNCTION(&_1, "abs", NULL, 314, &_0);
	zephir_check_call_status();
	limit = zephir_get_intval(&_1);
	if (UNEXPECTED(limit == 0)) {
		RETURN_THIS();
	}
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, limit);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 790, &_0);
	if (zephir_is_numeric(offset)) {
		ZVAL_LONG(&_2$$4, zephir_get_intval(offset));
		ZEPHIR_CALL_FUNCTION(&_3$$4, "abs", NULL, 314, &_2$$4);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 791, &_3$$4);
	}
	RETURN_THIS();
}

/**
 * Appends a NOT BETWEEN condition to the current HAVING conditions clause
 *
 *```php
 * $builder->notBetweenHaving("SUM(Robots.price)", 100.25, 200.50);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, notBetweenHaving)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval expr_zv, *minimum, minimum_sub, *maximum, maximum_sub, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&minimum_sub);
	ZVAL_UNDEF(&maximum_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(expr)
		Z_PARAM_ZVAL(minimum)
		Z_PARAM_ZVAL(maximum)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	minimum = ZEND_CALL_ARG(execute_data, 2);
	maximum = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		operator_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Having");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionNotBetween", NULL, 0, &_0, &operator, &expr_zv, minimum, maximum);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Appends a NOT BETWEEN condition to the current WHERE conditions
 *
 *```php
 * $builder->notBetweenWhere("price", 100.25, 200.50);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, notBetweenWhere)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval expr_zv, *minimum, minimum_sub, *maximum, maximum_sub, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&minimum_sub);
	ZVAL_UNDEF(&maximum_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(expr)
		Z_PARAM_ZVAL(minimum)
		Z_PARAM_ZVAL(maximum)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	minimum = ZEND_CALL_ARG(execute_data, 2);
	maximum = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		operator_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Where");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionNotBetween", NULL, 0, &_0, &operator, &expr_zv, minimum, maximum);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Appends a NOT IN condition to the current HAVING conditions clause
 *
 *```php
 * $builder->notInHaving("SUM(Robots.price)", [100, 200]);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, notInHaving)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval values;
	zval expr_zv, *values_param = NULL, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(expr)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		operator_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Having");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionNotIn", NULL, 0, &_0, &operator, &expr_zv, &values);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Appends a NOT IN condition to the current WHERE conditions
 *
 *```php
 * $builder->notInWhere("id", [1, 2, 3]);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, notInWhere)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval operator;
	zval values;
	zval expr_zv, *values_param = NULL, *operator_param = NULL, _0;
	zend_string *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&operator);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(expr)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(operator_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		operator_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	if (!operator_param) {
		ZEPHIR_INIT_VAR(&operator);
		ZVAL_STRING(&operator, "and");
	} else {
	if (UNEXPECTED(Z_TYPE_P(operator_param) != IS_STRING && Z_TYPE_P(operator_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'operator' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(operator_param) == IS_STRING)) {
		zephir_get_strval(&operator, operator_param);
	} else {
		ZEPHIR_INIT_VAR(&operator);
	}
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Where");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "conditionNotIn", NULL, 0, &_0, &operator, &expr_zv, &values);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Sets an OFFSET clause
 *
 *```php
 * $builder->offset(30);
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, offset)
{
	zval *offset_param = NULL, _0;
	zend_long offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("offset", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &offset_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, offset);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 791, &_0);
	RETURN_THISW();
}

/**
 * Sets an ORDER BY condition clause
 *
 *```php
 * $builder->orderBy("Robots.name");
 * $builder->orderBy(["1", "Robots.name"]);
 * $builder->orderBy(["Robots.name DESC"]);
 *```
 *
 * @param array|string orderBy
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, orderBy)
{
	zval *orderBy, orderBy_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&orderBy_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("order", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(orderBy)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &orderBy);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 789, orderBy);
	RETURN_THISW();
}

/**
 * Appends a condition to the current HAVING conditions clause using an OR operator
 *
 *```php
 * $builder->orHaving("SUM(Robots.price) > 0");
 *
 * $builder->orHaving(
 *     "SUM(Robots.price) > :sum:",
 *     [
 *         "sum" => 100,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, orHaving)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes;
	zval *conditions_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, currentConditions, _0$$3;
	zval conditions;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&currentConditions);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("having", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(conditions_param)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &conditions_param, &bindParams_param, &bindTypes_param);
	if (UNEXPECTED(Z_TYPE_P(conditions_param) != IS_STRING && Z_TYPE_P(conditions_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'conditions' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(conditions_param) == IS_STRING)) {
		zephir_get_strval(&conditions, conditions_param);
	} else {
		ZEPHIR_INIT_VAR(&conditions);
	}
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
	zephir_memory_observe(&currentConditions);
	zephir_read_property_cached(&currentConditions, this_ptr, _zephir_prop_0, 788, PH_NOISY_CC);
	if (zephir_is_true(&currentConditions)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SVSVS(&_0$$3, "(", &currentConditions, ") OR (", &conditions, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&conditions, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "having", NULL, 0, &conditions, &bindParams, &bindTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Appends a condition to the current conditions using an OR operator
 *
 *```php
 * $builder->orWhere("name = 'Peter'");
 *
 * $builder->orWhere(
 *     "name = :name: AND id > :id:",
 *     [
 *         "name" => "Peter",
 *         "id"   => 100,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, orWhere)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval bindParams, bindTypes;
	zval *conditions_param = NULL, *bindParams_param = NULL, *bindTypes_param = NULL, currentConditions, _0$$3;
	zval conditions;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&currentConditions);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("conditions", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(conditions_param)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &conditions_param, &bindParams_param, &bindTypes_param);
	if (UNEXPECTED(Z_TYPE_P(conditions_param) != IS_STRING && Z_TYPE_P(conditions_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'conditions' must be of the type string"));
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(conditions_param) == IS_STRING)) {
		zephir_get_strval(&conditions, conditions_param);
	} else {
		ZEPHIR_INIT_VAR(&conditions);
	}
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
	zephir_memory_observe(&currentConditions);
	zephir_read_property_cached(&currentConditions, this_ptr, _zephir_prop_0, 781, PH_NOISY_CC);
	if (zephir_is_true(&currentConditions)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SVSVS(&_0$$3, "(", &currentConditions, ") OR (", &conditions, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&conditions, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "where", NULL, 0, &conditions, &bindParams, &bindTypes);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds a RIGHT join to the query
 *
 *```php
 * $builder->rightJoin(
 *     Robots::class,
 *     "r.id = RobotsParts.robots_id",
 *     "r"
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, rightJoin)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval model_zv, conditions_zv, alias_zv, _1;
	zend_string *model = NULL, *conditions = NULL, *alias = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_zv);
	ZVAL_UNDEF(&conditions_zv);
	ZVAL_UNDEF(&alias_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(model)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(conditions)
		Z_PARAM_STR_OR_NULL(alias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&model_zv);
	ZVAL_STR_COPY(&model_zv, model);
	if (!conditions) {
		ZEPHIR_INIT_VAR(&conditions_zv);
	} else {
		zephir_memory_observe(&conditions_zv);
	ZVAL_STR_COPY(&conditions_zv, conditions);
	}
	if (!alias) {
		ZEPHIR_INIT_VAR(&alias_zv);
	} else {
		zephir_memory_observe(&alias_zv);
	ZVAL_STR_COPY(&alias_zv, alias);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0);
	zephir_array_fast_append(&_0, &model_zv);
	zephir_array_fast_append(&_0, &conditions_zv);
	zephir_array_fast_append(&_0, &alias_zv);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "RIGHT");
	zephir_array_fast_append(&_0, &_1);
	zephir_update_property_array_append(this_ptr, SL("joins"), &_0);
	RETURN_THIS();
}

/**
 * Set default bind parameters
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, setBindParams)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool merge;
	zval *bindParams_param = NULL, *merge_param = NULL, currentBindParams, _0$$4;
	zval bindParams;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&currentBindParams);
	ZVAL_UNDEF(&_0$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("bindParams", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(bindParams, bindParams_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &bindParams_param, &merge_param);
	ZEPHIR_OBS_COPY_OR_DUP(&bindParams, bindParams_param);
	if (!merge_param) {
		merge = 0;
	} else {
		}
	if (merge) {
		zephir_memory_observe(&currentBindParams);
		zephir_read_property_cached(&currentBindParams, this_ptr, _zephir_prop_0, 782, PH_NOISY_CC);
		if (Z_TYPE_P(&currentBindParams) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_0$$4);
			zephir_add_function(&_0$$4, &currentBindParams, &bindParams);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 782, &_0$$4);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 782, &bindParams);
		}
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 782, &bindParams);
	}
	RETURN_THIS();
}

/**
 * Set default bind types
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, setBindTypes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool merge;
	zval *bindTypes_param = NULL, *merge_param = NULL, currentBindTypes, _0$$4;
	zval bindTypes;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&currentBindTypes);
	ZVAL_UNDEF(&_0$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("bindTypes", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(bindTypes, bindTypes_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &bindTypes_param, &merge_param);
	ZEPHIR_OBS_COPY_OR_DUP(&bindTypes, bindTypes_param);
	if (!merge_param) {
		merge = 0;
	} else {
		}
	if (UNEXPECTED(merge)) {
		zephir_memory_observe(&currentBindTypes);
		zephir_read_property_cached(&currentBindTypes, this_ptr, _zephir_prop_0, 783, PH_NOISY_CC);
		if (Z_TYPE_P(&currentBindTypes) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_0$$4);
			zephir_add_function(&_0$$4, &currentBindTypes, &bindTypes);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 783, &_0$$4);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 783, &bindTypes);
		}
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 783, &bindTypes);
	}
	RETURN_THIS();
}

/**
 * Sets the DependencyInjector container
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, setDI)
{
	zval *container, container_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(container, phalcon_di_diinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &container);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 794, container);
}

/**
 * Sets the query WHERE conditions
 *
 *```php
 * $builder->where(100);
 *
 * $builder->where("name = 'Peter'");
 *
 * $builder->where(
 *     "name = :name: AND id > :id:",
 *     [
 *         "name" => "Peter",
 *         "id"   => 100,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, where)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval bindParams, bindTypes;
	zval conditions_zv, *bindParams_param = NULL, *bindTypes_param = NULL, currentBindParams, currentBindTypes, _0$$4, _1$$7;
	zend_string *conditions = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&conditions_zv);
	ZVAL_UNDEF(&currentBindParams);
	ZVAL_UNDEF(&currentBindTypes);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$7);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("conditions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindTypes", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(conditions)
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
	zephir_memory_observe(&conditions_zv);
	ZVAL_STR_COPY(&conditions_zv, conditions);
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 781, &conditions_zv);
	if (zephir_fast_count_int(&bindParams) > 0) {
		zephir_memory_observe(&currentBindParams);
		zephir_read_property_cached(&currentBindParams, this_ptr, _zephir_prop_1, 782, PH_NOISY_CC);
		if (Z_TYPE_P(&currentBindParams) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_0$$4);
			zephir_add_function(&_0$$4, &currentBindParams, &bindParams);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 782, &_0$$4);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 782, &bindParams);
		}
	}
	if (zephir_fast_count_int(&bindTypes) > 0) {
		zephir_read_property_cached(&currentBindTypes, this_ptr, _zephir_prop_2, 783, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&currentBindTypes) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_1$$7);
			zephir_add_function(&_1$$7, &currentBindTypes, &bindTypes);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 783, &_1$$7);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 783, &bindTypes);
		}
	}
	RETURN_THIS();
}

/**
 * Compiles the builder state into the intermediate representation that
 * Phalcon\Mvc\Model\Query executes, with no PHQL string and no parser.
 *
 * Models, aliases, default columns, joins (including implicit joins from
 * relations), LIMIT/OFFSET and FOR UPDATE are built from metadata. The
 * raw parts (conditions, columns, group, having, order, join conditions)
 * go through FragmentRewriter and reach the database as written.
 *
 * Returns ["intermediate": array, "bindParams": array, "bindTypes": array]
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, compileIntermediate)
{
	zval _79$$49, _118$$63, _152$$77, _191$$96, _194$$97, _199$$99, _202$$100;
	zval _14$$10, _23$$16, _35$$23, _36$$23, _45$$29, _46$$29, _52$$36, _54$$36, _68$$43, _77$$46, _91$$55, _110$$56, _126$$69, _144$$70, _163$$82, _189$$96, _190$$96, _192$$97, _197$$99, _198$$99, _200$$100, _206$$107, _211$$108;
	zend_string *_7, *_157, *_219, *_84$$47;
	zend_ulong _6, _156, _218, _83$$47;
	zend_bool named = 0, _17, _161, _170, _182, _184, _221, _39$$22, _51$$35, _67$$40, _120$$47, _101$$57, _136$$71, _158$$78, _178$$86, _174$$87, _179$$89, _196$$93, _204$$105, _210$$107;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, __$false, container, manager, metaData, models, modelAlias, modelName, model, source, schema, table, sqlAlias, rewriter, dialect, irModels, irTables, irColumns, irJoins, queryModels, join, joinModel, joinConditions, joinAlias, joinType, joinItems, joinItem, columns, items, key, item, split, columnAlias, domain, domainInfo, expression, conditions, primaryKeys, group, groupItems, having, order, orderItems, limit, number, offset, bindParams, bindTypes, typeName, typeValue, intermediate, matches, relationJoins, relationJoin, queryModel, distinct, _0, _2, _3, *_4, *_5, _16, _25, *_48, _49, *_50, *_153, _154, *_155, *_215, _216, *_217, _220, _1$$5, _9$$11, _11$$14, _12$$10, _15$$10, _19$$17, _20$$18, _21$$20, _22$$16, _24$$16, _26$$22, *_27$$22, _28$$22, *_29$$22, _38$$22, _31$$24, _32$$25, _33$$23, _37$$23, _34$$27, _41$$30, _42$$31, _43$$29, _47$$29, _44$$33, *_57$$35, _58$$35, *_59$$35, _53$$36, _55$$36, _60$$37, _61$$37, *_63$$40, _64$$40, *_65$$40, _66$$40, _69$$43, _70$$43, *_71$$44, _72$$44, *_73$$44, _74$$45, _75$$46, _78$$46, *_80$$47, _81$$47, *_82$$47, _119$$47, *_86$$53, _87$$53, *_88$$53, _89$$54, _90$$55, _92$$55, _93$$56, _94$$56, _95$$56, _96$$56, *_97$$56, _98$$56, *_99$$56, _111$$56, _100$$57, _102$$57, _103$$57, _104$$57, _105$$57, _106$$57, _107$$59, _108$$59, _112$$60, _113$$60, _114$$60, _115$$50, _116$$50, _117$$63, *_121$$67, _122$$67, *_123$$67, _124$$68, _125$$69, _127$$69, _128$$70, _129$$70, _130$$70, _131$$70, *_132$$70, _133$$70, *_134$$70, _145$$70, _135$$71, _137$$71, _138$$71, _139$$71, _140$$71, _141$$71, _142$$73, _143$$73, _146$$74, _147$$74, _148$$74, _149$$64, _150$$64, _151$$77, _159$$78, _162$$82, _164$$82, _165$$82, _166$$82, _167$$82, _168$$82, _169$$85, *_171$$86, _172$$86, *_173$$86, _177$$86, _175$$87, _176$$88, _180$$89, _181$$90, _183$$92, _185$$94, *_186$$93, _187$$93, *_188$$93, _195$$93, _193$$97, _201$$100, _203$$105, _205$$107, _207$$107, _208$$107, _209$$107, _212$$108, _213$$108, _214$$108;
	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL, *_13 = NULL, *_18 = NULL, *_30 = NULL, *_40 = NULL, *_56 = NULL, *_62 = NULL, *_76 = NULL, *_85 = NULL, *_109 = NULL, *_160 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, position = 0;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&manager);
	ZVAL_UNDEF(&metaData);
	ZVAL_UNDEF(&models);
	ZVAL_UNDEF(&modelAlias);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&model);
	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&schema);
	ZVAL_UNDEF(&table);
	ZVAL_UNDEF(&sqlAlias);
	ZVAL_UNDEF(&rewriter);
	ZVAL_UNDEF(&dialect);
	ZVAL_UNDEF(&irModels);
	ZVAL_UNDEF(&irTables);
	ZVAL_UNDEF(&irColumns);
	ZVAL_UNDEF(&irJoins);
	ZVAL_UNDEF(&queryModels);
	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&joinModel);
	ZVAL_UNDEF(&joinConditions);
	ZVAL_UNDEF(&joinAlias);
	ZVAL_UNDEF(&joinType);
	ZVAL_UNDEF(&joinItems);
	ZVAL_UNDEF(&joinItem);
	ZVAL_UNDEF(&columns);
	ZVAL_UNDEF(&items);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&split);
	ZVAL_UNDEF(&columnAlias);
	ZVAL_UNDEF(&domain);
	ZVAL_UNDEF(&domainInfo);
	ZVAL_UNDEF(&expression);
	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&group);
	ZVAL_UNDEF(&groupItems);
	ZVAL_UNDEF(&having);
	ZVAL_UNDEF(&order);
	ZVAL_UNDEF(&orderItems);
	ZVAL_UNDEF(&limit);
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&offset);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&bindTypes);
	ZVAL_UNDEF(&typeName);
	ZVAL_UNDEF(&typeValue);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&relationJoins);
	ZVAL_UNDEF(&relationJoin);
	ZVAL_UNDEF(&queryModel);
	ZVAL_UNDEF(&distinct);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_49);
	ZVAL_UNDEF(&_154);
	ZVAL_UNDEF(&_216);
	ZVAL_UNDEF(&_220);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_19$$17);
	ZVAL_UNDEF(&_20$$18);
	ZVAL_UNDEF(&_21$$20);
	ZVAL_UNDEF(&_22$$16);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_26$$22);
	ZVAL_UNDEF(&_28$$22);
	ZVAL_UNDEF(&_38$$22);
	ZVAL_UNDEF(&_31$$24);
	ZVAL_UNDEF(&_32$$25);
	ZVAL_UNDEF(&_33$$23);
	ZVAL_UNDEF(&_37$$23);
	ZVAL_UNDEF(&_34$$27);
	ZVAL_UNDEF(&_41$$30);
	ZVAL_UNDEF(&_42$$31);
	ZVAL_UNDEF(&_43$$29);
	ZVAL_UNDEF(&_47$$29);
	ZVAL_UNDEF(&_44$$33);
	ZVAL_UNDEF(&_58$$35);
	ZVAL_UNDEF(&_53$$36);
	ZVAL_UNDEF(&_55$$36);
	ZVAL_UNDEF(&_60$$37);
	ZVAL_UNDEF(&_61$$37);
	ZVAL_UNDEF(&_64$$40);
	ZVAL_UNDEF(&_66$$40);
	ZVAL_UNDEF(&_69$$43);
	ZVAL_UNDEF(&_70$$43);
	ZVAL_UNDEF(&_72$$44);
	ZVAL_UNDEF(&_74$$45);
	ZVAL_UNDEF(&_75$$46);
	ZVAL_UNDEF(&_78$$46);
	ZVAL_UNDEF(&_81$$47);
	ZVAL_UNDEF(&_119$$47);
	ZVAL_UNDEF(&_87$$53);
	ZVAL_UNDEF(&_89$$54);
	ZVAL_UNDEF(&_90$$55);
	ZVAL_UNDEF(&_92$$55);
	ZVAL_UNDEF(&_93$$56);
	ZVAL_UNDEF(&_94$$56);
	ZVAL_UNDEF(&_95$$56);
	ZVAL_UNDEF(&_96$$56);
	ZVAL_UNDEF(&_98$$56);
	ZVAL_UNDEF(&_111$$56);
	ZVAL_UNDEF(&_100$$57);
	ZVAL_UNDEF(&_102$$57);
	ZVAL_UNDEF(&_103$$57);
	ZVAL_UNDEF(&_104$$57);
	ZVAL_UNDEF(&_105$$57);
	ZVAL_UNDEF(&_106$$57);
	ZVAL_UNDEF(&_107$$59);
	ZVAL_UNDEF(&_108$$59);
	ZVAL_UNDEF(&_112$$60);
	ZVAL_UNDEF(&_113$$60);
	ZVAL_UNDEF(&_114$$60);
	ZVAL_UNDEF(&_115$$50);
	ZVAL_UNDEF(&_116$$50);
	ZVAL_UNDEF(&_117$$63);
	ZVAL_UNDEF(&_122$$67);
	ZVAL_UNDEF(&_124$$68);
	ZVAL_UNDEF(&_125$$69);
	ZVAL_UNDEF(&_127$$69);
	ZVAL_UNDEF(&_128$$70);
	ZVAL_UNDEF(&_129$$70);
	ZVAL_UNDEF(&_130$$70);
	ZVAL_UNDEF(&_131$$70);
	ZVAL_UNDEF(&_133$$70);
	ZVAL_UNDEF(&_145$$70);
	ZVAL_UNDEF(&_135$$71);
	ZVAL_UNDEF(&_137$$71);
	ZVAL_UNDEF(&_138$$71);
	ZVAL_UNDEF(&_139$$71);
	ZVAL_UNDEF(&_140$$71);
	ZVAL_UNDEF(&_141$$71);
	ZVAL_UNDEF(&_142$$73);
	ZVAL_UNDEF(&_143$$73);
	ZVAL_UNDEF(&_146$$74);
	ZVAL_UNDEF(&_147$$74);
	ZVAL_UNDEF(&_148$$74);
	ZVAL_UNDEF(&_149$$64);
	ZVAL_UNDEF(&_150$$64);
	ZVAL_UNDEF(&_151$$77);
	ZVAL_UNDEF(&_159$$78);
	ZVAL_UNDEF(&_162$$82);
	ZVAL_UNDEF(&_164$$82);
	ZVAL_UNDEF(&_165$$82);
	ZVAL_UNDEF(&_166$$82);
	ZVAL_UNDEF(&_167$$82);
	ZVAL_UNDEF(&_168$$82);
	ZVAL_UNDEF(&_169$$85);
	ZVAL_UNDEF(&_172$$86);
	ZVAL_UNDEF(&_177$$86);
	ZVAL_UNDEF(&_175$$87);
	ZVAL_UNDEF(&_176$$88);
	ZVAL_UNDEF(&_180$$89);
	ZVAL_UNDEF(&_181$$90);
	ZVAL_UNDEF(&_183$$92);
	ZVAL_UNDEF(&_185$$94);
	ZVAL_UNDEF(&_187$$93);
	ZVAL_UNDEF(&_195$$93);
	ZVAL_UNDEF(&_193$$97);
	ZVAL_UNDEF(&_201$$100);
	ZVAL_UNDEF(&_203$$105);
	ZVAL_UNDEF(&_205$$107);
	ZVAL_UNDEF(&_207$$107);
	ZVAL_UNDEF(&_208$$107);
	ZVAL_UNDEF(&_209$$107);
	ZVAL_UNDEF(&_212$$108);
	ZVAL_UNDEF(&_213$$108);
	ZVAL_UNDEF(&_214$$108);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_23$$16);
	ZVAL_UNDEF(&_35$$23);
	ZVAL_UNDEF(&_36$$23);
	ZVAL_UNDEF(&_45$$29);
	ZVAL_UNDEF(&_46$$29);
	ZVAL_UNDEF(&_52$$36);
	ZVAL_UNDEF(&_54$$36);
	ZVAL_UNDEF(&_68$$43);
	ZVAL_UNDEF(&_77$$46);
	ZVAL_UNDEF(&_91$$55);
	ZVAL_UNDEF(&_110$$56);
	ZVAL_UNDEF(&_126$$69);
	ZVAL_UNDEF(&_144$$70);
	ZVAL_UNDEF(&_163$$82);
	ZVAL_UNDEF(&_189$$96);
	ZVAL_UNDEF(&_190$$96);
	ZVAL_UNDEF(&_192$$97);
	ZVAL_UNDEF(&_197$$99);
	ZVAL_UNDEF(&_198$$99);
	ZVAL_UNDEF(&_200$$100);
	ZVAL_UNDEF(&_206$$107);
	ZVAL_UNDEF(&_211$$108);
	ZVAL_UNDEF(&_79$$49);
	ZVAL_UNDEF(&_118$$63);
	ZVAL_UNDEF(&_152$$77);
	ZVAL_UNDEF(&_191$$96);
	ZVAL_UNDEF(&_194$$97);
	ZVAL_UNDEF(&_199$$99);
	ZVAL_UNDEF(&_202$$100);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	static zend_string *_zephir_prop_9 = NULL;
	static zend_string *_zephir_prop_10 = NULL;
	static zend_string *_zephir_prop_11 = NULL;
	static zend_string *_zephir_prop_12 = NULL;
	static zend_string *_zephir_prop_13 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("models", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("bindParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("bindTypes", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("joins", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("columns", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("distinct", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("conditions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("group", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("having", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("order", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("limit", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_12)) {
		_zephir_prop_12 = zend_string_init("offset", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_13)) {
		_zephir_prop_13 = zend_string_init("forUpdate", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 794, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (Z_TYPE_P(&container) != IS_OBJECT) {
		ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 794, &container);
	}
	if (UNEXPECTED(Z_TYPE_P(&container) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "A dependency injection container is required to access the services related to the ORM", "phalcon/Mvc/Model/Query/Builder.zep", 1647);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 785, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&models, &_0);
	if (Z_TYPE_P(&models) != IS_ARRAY) {
		if (UNEXPECTED(!zephir_is_true(&models))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "At least one model is required to build the query", "phalcon/Mvc/Model/Query/Builder.zep", 1656);
			return;
		}
		ZEPHIR_INIT_VAR(&_1$$5);
		zephir_create_array(&_1$$5, 1, 0);
		zephir_array_fast_append(&_1$$5, &models);
		ZEPHIR_CPY_WRT(&models, &_1$$5);
	} else if (UNEXPECTED(!(zephir_fast_count_int(&models)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "At least one model is required to build the query", "phalcon/Mvc/Model/Query/Builder.zep", 1663);
		return;
	}
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "modelsManager");
	ZEPHIR_CALL_METHOD(&_2, &container, "getShared", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&manager, &_2);
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "modelsMetadata");
	ZEPHIR_CALL_METHOD(&_2, &container, "getShared", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&metaData, &_2);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 782, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&bindParams, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_3, 783, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&bindTypes, &_0);
	if (Z_TYPE_P(&bindParams) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(&bindParams);
		array_init(&bindParams);
	}
	if (Z_TYPE_P(&bindTypes) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(&bindTypes);
		array_init(&bindTypes);
	}
	ZEPHIR_INIT_VAR(&irModels);
	array_init(&irModels);
	ZEPHIR_INIT_VAR(&irTables);
	array_init(&irTables);
	ZEPHIR_INIT_VAR(&irJoins);
	array_init(&irJoins);
	ZEPHIR_INIT_VAR(&irColumns);
	array_init(&irColumns);
	ZEPHIR_INIT_VAR(&queryModels);
	array_init(&queryModels);
	ZEPHIR_INIT_VAR(&joinItems);
	array_init(&joinItems);
	ZEPHIR_INIT_VAR(&rewriter);
	ZVAL_NULL(&rewriter);
	if (Z_TYPE_P(&models) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_3);
		zephir_string_to_char_array(&_3, &models);
		_4 = &_3;
	} else {
		_4 = &models;
	}
	zephir_is_iterable(_4, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1736);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _6, _7, _5)
		{
			ZEPHIR_INIT_NVAR(&modelAlias);
			if (_7 != NULL) { 
				ZVAL_STR_COPY(&modelAlias, _7);
			} else {
				ZVAL_LONG(&modelAlias, _6);
			}
			ZEPHIR_INIT_NVAR(&modelName);
			ZVAL_COPY(&modelName, _5);
			ZEPHIR_CALL_METHOD(&model, &manager, "load", &_8, 0, &modelName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&rewriter) == IS_NULL) {
				ZEPHIR_CALL_METHOD(&_9$$11, &model, "getReadConnection", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&dialect, &_9$$11, "getDialect", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rewriter);
				object_init_ex(&rewriter, phalcon_mvc_model_query_fragmentrewriter_ce);
				ZEPHIR_CALL_METHOD(NULL, &rewriter, "__construct", &_10, 0, &manager, &metaData, &dialect, &bindParams);
				zephir_check_call_status();
			}
			named = Z_TYPE_P(&modelAlias) == IS_STRING;
			if (named) {
				ZEPHIR_INIT_NVAR(&table);
				zephir_create_array(&table, 3, 0);
				zephir_array_fast_append(&table, &source);
				zephir_array_fast_append(&table, &schema);
				zephir_array_fast_append(&table, &modelAlias);
				ZEPHIR_CPY_WRT(&sqlAlias, &modelAlias);
			} else {
				ZEPHIR_CPY_WRT(&sqlAlias, &source);
				if (zephir_is_true(&schema)) {
					ZEPHIR_INIT_NVAR(&_11$$14);
					zephir_create_array(&_11$$14, 2, 0);
					zephir_array_fast_append(&_11$$14, &source);
					zephir_array_fast_append(&_11$$14, &schema);
					ZEPHIR_CPY_WRT(&table, &_11$$14);
				} else {
					ZEPHIR_CPY_WRT(&table, &source);
				}
			}
			if (named) {
				ZVAL_BOOL(&_12$$10, 1);
			} else {
				ZVAL_BOOL(&_12$$10, 0);
			}
			ZEPHIR_CALL_METHOD(NULL, &rewriter, "addModel", &_13, 0, &modelName, &model, &sqlAlias, &_12$$10);
			zephir_check_call_status();
			zephir_array_append(&irModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1722);
			zephir_array_append(&irTables, &table, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1723);
			ZEPHIR_INIT_NVAR(&_14$$10);
			zephir_create_array(&_14$$10, 5, 0);
			zephir_array_update_string(&_14$$10, SL("model"), &modelName, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_14$$10, SL("alias"), &sqlAlias, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_15$$10);
			ZVAL_BOOL(&_15$$10, named);
			zephir_array_update_string(&_14$$10, SL("named"), &_15$$10, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_14$$10, SL("source"), &source, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_14$$10, SL("from"), &__$true, PH_COPY | PH_SEPARATE);
			zephir_array_append(&queryModels, &_14$$10, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1730);
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
			ZEPHIR_CALL_METHOD(&modelAlias, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&modelName, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&model, &manager, "load", &_18, 0, &modelName);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&rewriter) == IS_NULL) {
					ZEPHIR_CALL_METHOD(&_19$$17, &model, "getReadConnection", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&dialect, &_19$$17, "getDialect", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&rewriter);
					object_init_ex(&rewriter, phalcon_mvc_model_query_fragmentrewriter_ce);
					ZEPHIR_CALL_METHOD(NULL, &rewriter, "__construct", &_10, 0, &manager, &metaData, &dialect, &bindParams);
					zephir_check_call_status();
				}
				named = Z_TYPE_P(&modelAlias) == IS_STRING;
				if (named) {
					ZEPHIR_INIT_NVAR(&_20$$18);
					zephir_create_array(&_20$$18, 3, 0);
					zephir_array_fast_append(&_20$$18, &source);
					zephir_array_fast_append(&_20$$18, &schema);
					zephir_array_fast_append(&_20$$18, &modelAlias);
					ZEPHIR_CPY_WRT(&table, &_20$$18);
					ZEPHIR_CPY_WRT(&sqlAlias, &modelAlias);
				} else {
					ZEPHIR_CPY_WRT(&sqlAlias, &source);
					if (zephir_is_true(&schema)) {
						ZEPHIR_INIT_NVAR(&_21$$20);
						zephir_create_array(&_21$$20, 2, 0);
						zephir_array_fast_append(&_21$$20, &source);
						zephir_array_fast_append(&_21$$20, &schema);
						ZEPHIR_CPY_WRT(&table, &_21$$20);
					} else {
						ZEPHIR_CPY_WRT(&table, &source);
					}
				}
				if (named) {
					ZVAL_BOOL(&_22$$16, 1);
				} else {
					ZVAL_BOOL(&_22$$16, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, &rewriter, "addModel", &_13, 0, &modelName, &model, &sqlAlias, &_22$$16);
				zephir_check_call_status();
				zephir_array_append(&irModels, &modelName, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1722);
				zephir_array_append(&irTables, &table, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1723);
				ZEPHIR_INIT_NVAR(&_23$$16);
				zephir_create_array(&_23$$16, 5, 0);
				zephir_array_update_string(&_23$$16, SL("model"), &modelName, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_23$$16, SL("alias"), &sqlAlias, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_24$$16);
				ZVAL_BOOL(&_24$$16, named);
				zephir_array_update_string(&_23$$16, SL("named"), &_24$$16, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_23$$16, SL("source"), &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_23$$16, SL("from"), &__$true, PH_COPY | PH_SEPARATE);
				zephir_array_append(&queryModels, &_23$$16, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1730);
		}
	}
	ZEPHIR_INIT_NVAR(&modelName);
	ZEPHIR_INIT_NVAR(&modelAlias);
	zephir_memory_observe(&_25);
	zephir_read_property_cached(&_25, this_ptr, _zephir_prop_4, 787, PH_NOISY_CC);
	if (Z_TYPE_P(&_25) == IS_ARRAY) {
		zephir_read_property_cached(&_26$$22, this_ptr, _zephir_prop_4, 787, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_26$$22) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_28$$22);
			zephir_string_to_char_array(&_28$$22, &_26$$22);
			_27$$22 = &_28$$22;
		} else {
			_27$$22 = &_26$$22;
		}
		zephir_is_iterable(_27$$22, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1787);
		if (Z_TYPE_P(_27$$22) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_27$$22), _29$$22)
			{
				ZEPHIR_INIT_NVAR(&join);
				ZVAL_COPY(&join, _29$$22);
				ZEPHIR_OBS_NVAR(&joinModel);
				zephir_array_fetch_long(&joinModel, &join, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1741);
				ZEPHIR_OBS_NVAR(&joinConditions);
				zephir_array_fetch_long(&joinConditions, &join, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1742);
				ZEPHIR_OBS_NVAR(&joinAlias);
				zephir_array_fetch_long(&joinAlias, &join, 2, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1743);
				ZEPHIR_OBS_NVAR(&joinType);
				zephir_array_fetch_long(&joinType, &join, 3, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1744);
				ZEPHIR_CALL_METHOD(&model, &manager, "load", &_30, 0, &joinModel);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
				zephir_check_call_status();
				named = !(ZEPHIR_IS_EMPTY(&joinAlias));
				if (named) {
					ZEPHIR_INIT_NVAR(&_31$$24);
					zephir_create_array(&_31$$24, 3, 0);
					zephir_array_fast_append(&_31$$24, &source);
					zephir_array_fast_append(&_31$$24, &schema);
					zephir_array_fast_append(&_31$$24, &joinAlias);
					ZEPHIR_CPY_WRT(&table, &_31$$24);
					ZEPHIR_CPY_WRT(&sqlAlias, &joinAlias);
				} else if (zephir_is_true(&schema)) {
					ZEPHIR_INIT_NVAR(&_32$$25);
					zephir_create_array(&_32$$25, 2, 0);
					zephir_array_fast_append(&_32$$25, &source);
					zephir_array_fast_append(&_32$$25, &schema);
					ZEPHIR_CPY_WRT(&table, &_32$$25);
					ZEPHIR_CPY_WRT(&sqlAlias, &source);
				} else {
					ZEPHIR_CPY_WRT(&table, &source);
					ZEPHIR_CPY_WRT(&sqlAlias, &source);
				}
				if (named) {
					ZVAL_BOOL(&_33$$23, 1);
				} else {
					ZVAL_BOOL(&_33$$23, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, &rewriter, "addModel", &_13, 0, &joinModel, &model, &sqlAlias, &_33$$23);
				zephir_check_call_status();
				if (zephir_is_true(&joinType)) {
					ZEPHIR_INIT_NVAR(&_34$$27);
					zephir_fast_strtoupper(&_34$$27, &joinType);
					ZEPHIR_CPY_WRT(&joinType, &_34$$27);
				} else {
					ZEPHIR_INIT_NVAR(&joinType);
					ZVAL_STRING(&joinType, "INNER");
				}
				ZEPHIR_INIT_NVAR(&_35$$23);
				zephir_create_array(&_35$$23, 5, 0);
				zephir_array_update_string(&_35$$23, SL("model"), &joinModel, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_35$$23, SL("alias"), &sqlAlias, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_35$$23, SL("table"), &table, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_35$$23, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_35$$23, SL("conditions"), &joinConditions, PH_COPY | PH_SEPARATE);
				zephir_array_append(&joinItems, &_35$$23, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1777);
				ZEPHIR_INIT_NVAR(&_36$$23);
				zephir_create_array(&_36$$23, 5, 0);
				zephir_array_update_string(&_36$$23, SL("model"), &joinModel, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_36$$23, SL("alias"), &sqlAlias, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_37$$23);
				ZVAL_BOOL(&_37$$23, named);
				zephir_array_update_string(&_36$$23, SL("named"), &_37$$23, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_36$$23, SL("source"), &source, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_36$$23, SL("from"), &__$false, PH_COPY | PH_SEPARATE);
				zephir_array_append(&queryModels, &_36$$23, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1785);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _27$$22, "rewind", NULL, 0);
			zephir_check_call_status();
			_39$$22 = 1;
			while (1) {
				if (_39$$22) {
					_39$$22 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _27$$22, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_38$$22, _27$$22, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_38$$22)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&join, _27$$22, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&joinModel);
					zephir_array_fetch_long(&joinModel, &join, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1741);
					ZEPHIR_OBS_NVAR(&joinConditions);
					zephir_array_fetch_long(&joinConditions, &join, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1742);
					ZEPHIR_OBS_NVAR(&joinAlias);
					zephir_array_fetch_long(&joinAlias, &join, 2, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1743);
					ZEPHIR_OBS_NVAR(&joinType);
					zephir_array_fetch_long(&joinType, &join, 3, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1744);
					ZEPHIR_CALL_METHOD(&model, &manager, "load", &_40, 0, &joinModel);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&source, &model, "getSource", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&schema, &model, "getSchema", NULL, 0);
					zephir_check_call_status();
					named = !(ZEPHIR_IS_EMPTY(&joinAlias));
					if (named) {
						ZEPHIR_INIT_NVAR(&_41$$30);
						zephir_create_array(&_41$$30, 3, 0);
						zephir_array_fast_append(&_41$$30, &source);
						zephir_array_fast_append(&_41$$30, &schema);
						zephir_array_fast_append(&_41$$30, &joinAlias);
						ZEPHIR_CPY_WRT(&table, &_41$$30);
						ZEPHIR_CPY_WRT(&sqlAlias, &joinAlias);
					} else if (zephir_is_true(&schema)) {
						ZEPHIR_INIT_NVAR(&_42$$31);
						zephir_create_array(&_42$$31, 2, 0);
						zephir_array_fast_append(&_42$$31, &source);
						zephir_array_fast_append(&_42$$31, &schema);
						ZEPHIR_CPY_WRT(&table, &_42$$31);
						ZEPHIR_CPY_WRT(&sqlAlias, &source);
					} else {
						ZEPHIR_CPY_WRT(&table, &source);
						ZEPHIR_CPY_WRT(&sqlAlias, &source);
					}
					if (named) {
						ZVAL_BOOL(&_43$$29, 1);
					} else {
						ZVAL_BOOL(&_43$$29, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, &rewriter, "addModel", &_13, 0, &joinModel, &model, &sqlAlias, &_43$$29);
					zephir_check_call_status();
					if (zephir_is_true(&joinType)) {
						ZEPHIR_INIT_NVAR(&_44$$33);
						zephir_fast_strtoupper(&_44$$33, &joinType);
						ZEPHIR_CPY_WRT(&joinType, &_44$$33);
					} else {
						ZEPHIR_INIT_NVAR(&joinType);
						ZVAL_STRING(&joinType, "INNER");
					}
					ZEPHIR_INIT_NVAR(&_45$$29);
					zephir_create_array(&_45$$29, 5, 0);
					zephir_array_update_string(&_45$$29, SL("model"), &joinModel, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_45$$29, SL("alias"), &sqlAlias, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_45$$29, SL("table"), &table, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_45$$29, SL("type"), &joinType, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_45$$29, SL("conditions"), &joinConditions, PH_COPY | PH_SEPARATE);
					zephir_array_append(&joinItems, &_45$$29, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1777);
					ZEPHIR_INIT_NVAR(&_46$$29);
					zephir_create_array(&_46$$29, 5, 0);
					zephir_array_update_string(&_46$$29, SL("model"), &joinModel, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_46$$29, SL("alias"), &sqlAlias, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_47$$29);
					ZVAL_BOOL(&_47$$29, named);
					zephir_array_update_string(&_46$$29, SL("named"), &_47$$29, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_46$$29, SL("source"), &source, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_46$$29, SL("from"), &__$false, PH_COPY | PH_SEPARATE);
					zephir_array_append(&queryModels, &_46$$29, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1785);
			}
		}
		ZEPHIR_INIT_NVAR(&join);
	}
	if (Z_TYPE_P(&joinItems) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_49);
		zephir_string_to_char_array(&_49, &joinItems);
		_48 = &_49;
	} else {
		_48 = &joinItems;
	}
	zephir_is_iterable(_48, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1841);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_48), _50)
	{
		ZEPHIR_INIT_NVAR(&joinItem);
		ZVAL_COPY(&joinItem, _50);
		ZEPHIR_OBS_NVAR(&joinConditions);
		zephir_array_fetch_string(&joinConditions, &joinItem, SL("conditions"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1790);
		_51$$35 = Z_TYPE_P(&joinConditions) == IS_STRING;
		if (_51$$35) {
			_51$$35 = !ZEPHIR_IS_STRING_IDENTICAL(&joinConditions, "");
		}
		if (_51$$35) {
			ZEPHIR_INIT_NVAR(&_52$$36);
			zephir_create_array(&_52$$36, 3, 0);
			ZEPHIR_OBS_NVAR(&_53$$36);
			zephir_array_fetch_string(&_53$$36, &joinItem, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1794);
			zephir_array_update_string(&_52$$36, SL("type"), &_53$$36, PH_COPY | PH_SEPARATE);
			ZEPHIR_OBS_NVAR(&_53$$36);
			zephir_array_fetch_string(&_53$$36, &joinItem, SL("table"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1795);
			zephir_array_update_string(&_52$$36, SL("source"), &_53$$36, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_54$$36);
			zephir_create_array(&_54$$36, 1, 0);
			ZEPHIR_CALL_METHOD(&_55$$36, &rewriter, "rewrite", &_56, 0, &joinConditions);
			zephir_check_call_status();
			zephir_array_fast_append(&_54$$36, &_55$$36);
			zephir_array_update_string(&_52$$36, SL("conditions"), &_54$$36, PH_COPY | PH_SEPARATE);
			zephir_array_append(&irJoins, &_52$$36, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1797);
			continue;
		}
		ZEPHIR_INIT_NVAR(&relationJoins);
		ZVAL_NULL(&relationJoins);
		if (Z_TYPE_P(&queryModels) == IS_STRING) {
			ZEPHIR_INIT_NVAR(&_58$$35);
			zephir_string_to_char_array(&_58$$35, &queryModels);
			_57$$35 = &_58$$35;
		} else {
			_57$$35 = &queryModels;
		}
		zephir_is_iterable(_57$$35, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1825);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_57$$35), _59$$35)
		{
			ZEPHIR_INIT_NVAR(&queryModel);
			ZVAL_COPY(&queryModel, _59$$35);
			ZEPHIR_OBS_NVAR(&_60$$37);
			zephir_array_fetch_string(&_60$$37, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1809);
			ZEPHIR_OBS_NVAR(&_61$$37);
			zephir_array_fetch_string(&_61$$37, &joinItem, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1809);
			if (ZEPHIR_IS_IDENTICAL(&_60$$37, &_61$$37)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&relationJoins, this_ptr, "compileRelationJoin", &_62, 0, &manager, &rewriter, &queryModel, &joinItem);
			zephir_check_call_status();
			if (Z_TYPE_P(&relationJoins) == IS_ARRAY) {
				break;
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&queryModel);
		if (Z_TYPE_P(&relationJoins) == IS_ARRAY) {
			if (Z_TYPE_P(&relationJoins) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_64$$40);
				zephir_string_to_char_array(&_64$$40, &relationJoins);
				_63$$40 = &_64$$40;
			} else {
				_63$$40 = &relationJoins;
			}
			zephir_is_iterable(_63$$40, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1829);
			if (Z_TYPE_P(_63$$40) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_63$$40), _65$$40)
				{
					ZEPHIR_INIT_NVAR(&relationJoin);
					ZVAL_COPY(&relationJoin, _65$$40);
					zephir_array_append(&irJoins, &relationJoin, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1827);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _63$$40, "rewind", NULL, 0);
				zephir_check_call_status();
				_67$$40 = 1;
				while (1) {
					if (_67$$40) {
						_67$$40 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _63$$40, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_66$$40, _63$$40, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_66$$40)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&relationJoin, _63$$40, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_append(&irJoins, &relationJoin, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1827);
				}
			}
			ZEPHIR_INIT_NVAR(&relationJoin);
		} else {
			ZEPHIR_INIT_NVAR(&_68$$43);
			zephir_create_array(&_68$$43, 3, 0);
			ZEPHIR_OBS_NVAR(&_69$$43);
			zephir_array_fetch_string(&_69$$43, &joinItem, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1831);
			zephir_array_update_string(&_68$$43, SL("type"), &_69$$43, PH_COPY | PH_SEPARATE);
			ZEPHIR_OBS_NVAR(&_69$$43);
			zephir_array_fetch_string(&_69$$43, &joinItem, SL("table"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1832);
			zephir_array_update_string(&_68$$43, SL("source"), &_69$$43, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_70$$43);
			array_init(&_70$$43);
			zephir_array_update_string(&_68$$43, SL("conditions"), &_70$$43, PH_COPY | PH_SEPARATE);
			zephir_array_append(&irJoins, &_68$$43, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 1834);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&joinItem);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_5, 786, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&columns, &_0);
	if (Z_TYPE_P(&columns) == IS_NULL) {
		if (Z_TYPE_P(&queryModels) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_72$$44);
			zephir_string_to_char_array(&_72$$44, &queryModels);
			_71$$44 = &_72$$44;
		} else {
			_71$$44 = &queryModels;
		}
		zephir_is_iterable(_71$$44, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1855);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_71$$44), _73$$44)
		{
			ZEPHIR_INIT_NVAR(&queryModel);
			ZVAL_COPY(&queryModel, _73$$44);
			ZEPHIR_OBS_NVAR(&_74$$45);
			zephir_array_fetch_string(&_74$$45, &queryModel, SL("from"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1845);
			if (zephir_is_true(&_74$$45)) {
				ZVAL_NULL(&_75$$46);
				ZEPHIR_CALL_METHOD(&columnAlias, this_ptr, "compileObjectAlias", &_76, 0, &queryModel, &_75$$46);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_77$$46);
				zephir_create_array(&_77$$46, 4, 0);
				add_assoc_stringl_ex(&_77$$46, SL("type"), SL("object"));
				ZEPHIR_OBS_NVAR(&_78$$46);
				zephir_array_fetch_string(&_78$$46, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1849);
				zephir_array_update_string(&_77$$46, SL("model"), &_78$$46, PH_COPY | PH_SEPARATE);
				ZEPHIR_OBS_NVAR(&_78$$46);
				zephir_array_fetch_string(&_78$$46, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1850);
				zephir_array_update_string(&_77$$46, SL("column"), &_78$$46, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_77$$46, SL("balias"), &columnAlias, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&irColumns, &columnAlias, &_77$$46, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&queryModel);
	} else {
		if (Z_TYPE_P(&columns) == IS_ARRAY) {
			ZEPHIR_CPY_WRT(&items, &columns);
		} else {
			zephir_cast_to_string(&_79$$49, &columns);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_CE_STATIC(&items, phalcon_mvc_model_query_fragmentrewriter_ce, "splitList", NULL, 0, &_79$$49);
			zephir_check_call_status();
		}
		position = 0;
		if (Z_TYPE_P(&items) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_81$$47);
			zephir_string_to_char_array(&_81$$47, &items);
			_80$$47 = &_81$$47;
		} else {
			_80$$47 = &items;
		}
		zephir_is_iterable(_80$$47, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1953);
		if (Z_TYPE_P(_80$$47) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_80$$47), _83$$47, _84$$47, _82$$47)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_84$$47 != NULL) { 
					ZVAL_STR_COPY(&key, _84$$47);
				} else {
					ZVAL_LONG(&key, _83$$47);
				}
				ZEPHIR_INIT_NVAR(&item);
				ZVAL_COPY(&item, _82$$47);
				if (Z_TYPE_P(&key) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&expression);
					zephir_fast_trim(&expression, &item, NULL , ZEPHIR_TRIM_BOTH);
					ZEPHIR_CPY_WRT(&columnAlias, &key);
				} else {
					ZEPHIR_CALL_CE_STATIC(&split, phalcon_mvc_model_query_fragmentrewriter_ce, "splitAlias", &_85, 0, &item);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&expression);
					zephir_array_fetch_long(&expression, &split, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1870);
					ZEPHIR_OBS_NVAR(&columnAlias);
					zephir_array_fetch_long(&columnAlias, &split, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1871);
				}
				if (ZEPHIR_IS_STRING_IDENTICAL(&expression, "*")) {
					if (Z_TYPE_P(&queryModels) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_87$$53);
						zephir_string_to_char_array(&_87$$53, &queryModels);
						_86$$53 = &_87$$53;
					} else {
						_86$$53 = &queryModels;
					}
					zephir_is_iterable(_86$$53, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1890);
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_86$$53), _88$$53)
					{
						ZEPHIR_INIT_NVAR(&queryModel);
						ZVAL_COPY(&queryModel, _88$$53);
						ZEPHIR_OBS_NVAR(&_89$$54);
						zephir_array_fetch_string(&_89$$54, &queryModel, SL("from"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1879);
						if (zephir_is_true(&_89$$54)) {
							ZVAL_NULL(&_90$$55);
							ZEPHIR_CALL_METHOD(&domain, this_ptr, "compileObjectAlias", &_76, 0, &queryModel, &_90$$55);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_91$$55);
							zephir_create_array(&_91$$55, 4, 0);
							add_assoc_stringl_ex(&_91$$55, SL("type"), SL("object"));
							ZEPHIR_OBS_NVAR(&_92$$55);
							zephir_array_fetch_string(&_92$$55, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1883);
							zephir_array_update_string(&_91$$55, SL("model"), &_92$$55, PH_COPY | PH_SEPARATE);
							ZEPHIR_OBS_NVAR(&_92$$55);
							zephir_array_fetch_string(&_92$$55, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1884);
							zephir_array_update_string(&_91$$55, SL("column"), &_92$$55, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_91$$55, SL("balias"), &domain, PH_COPY | PH_SEPARATE);
							zephir_array_update_zval(&irColumns, &domain, &_91$$55, PH_COPY | PH_SEPARATE);
						}
					} ZEND_HASH_FOREACH_END();
					ZEPHIR_INIT_NVAR(&queryModel);
					position++;
					continue;
				}
				if (zephir_end_with_str(&expression, SL(".*"))) {
					ZVAL_LONG(&_93$$56, 0);
					ZVAL_LONG(&_94$$56, -2);
					ZEPHIR_INIT_NVAR(&_95$$56);
					zephir_substr(&_95$$56, &expression, 0 , -2 , 0);
					ZEPHIR_INIT_NVAR(&_96$$56);
					ZVAL_STRING(&_96$$56, "[]");
					ZEPHIR_INIT_NVAR(&domain);
					zephir_fast_trim(&domain, &_95$$56, &_96$$56, ZEPHIR_TRIM_BOTH);
					ZEPHIR_INIT_NVAR(&domainInfo);
					ZVAL_NULL(&domainInfo);
					if (Z_TYPE_P(&queryModels) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_98$$56);
						zephir_string_to_char_array(&_98$$56, &queryModels);
						_97$$56 = &_98$$56;
					} else {
						_97$$56 = &queryModels;
					}
					zephir_is_iterable(_97$$56, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1908);
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_97$$56), _99$$56)
					{
						ZEPHIR_INIT_NVAR(&queryModel);
						ZVAL_COPY(&queryModel, _99$$56);
						ZEPHIR_OBS_NVAR(&_100$$57);
						zephir_array_fetch_string(&_100$$57, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1902);
						_101$$57 = ZEPHIR_IS_IDENTICAL(&_100$$57, &domain);
						if (!(_101$$57)) {
							ZEPHIR_INIT_NVAR(&_102$$57);
							ZEPHIR_OBS_NVAR(&_103$$57);
							zephir_array_fetch_string(&_103$$57, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1902);
							ZEPHIR_INIT_NVAR(&_104$$57);
							ZVAL_STRING(&_104$$57, "\\");
							zephir_fast_trim(&_102$$57, &_103$$57, &_104$$57, ZEPHIR_TRIM_LEFT);
							ZEPHIR_INIT_NVAR(&_105$$57);
							ZEPHIR_INIT_NVAR(&_106$$57);
							ZVAL_STRING(&_106$$57, "\\");
							zephir_fast_trim(&_105$$57, &domain, &_106$$57, ZEPHIR_TRIM_LEFT);
							_101$$57 = ZEPHIR_IS_IDENTICAL(&_102$$57, &_105$$57);
						}
						if (_101$$57) {
							ZEPHIR_CPY_WRT(&domainInfo, &queryModel);
							break;
						}
					} ZEND_HASH_FOREACH_END();
					ZEPHIR_INIT_NVAR(&queryModel);
					if (UNEXPECTED(Z_TYPE_P(&domainInfo) != IS_ARRAY)) {
						ZEPHIR_INIT_NVAR(&_107$$59);
						object_init_ex(&_107$$59, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_NVAR(&_108$$59);
						ZEPHIR_CONCAT_SVS(&_108$$59, "Unknown model or alias '", &domain, "' in the columns");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_107$$59, "__construct", &_109, 32, &_108$$59);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_107$$59, "phalcon/Mvc/Model/Query/Builder.zep", 1911);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&domain, this_ptr, "compileObjectAlias", &_76, 0, &domainInfo, &columnAlias);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_110$$56);
					zephir_create_array(&_110$$56, 4, 0);
					add_assoc_stringl_ex(&_110$$56, SL("type"), SL("object"));
					ZEPHIR_OBS_NVAR(&_111$$56);
					zephir_array_fetch_string(&_111$$56, &domainInfo, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1917);
					zephir_array_update_string(&_110$$56, SL("model"), &_111$$56, PH_COPY | PH_SEPARATE);
					ZEPHIR_OBS_NVAR(&_111$$56);
					zephir_array_fetch_string(&_111$$56, &domainInfo, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1918);
					zephir_array_update_string(&_110$$56, SL("column"), &_111$$56, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_110$$56, SL("balias"), &domain, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&irColumns, &domain, &_110$$56, PH_COPY | PH_SEPARATE);
					position++;
					continue;
				}
				if (Z_TYPE_P(&columnAlias) == IS_NULL) {
					ZEPHIR_INIT_NVAR(&matches);
					ZVAL_NULL(&matches);
					ZEPHIR_INIT_NVAR(&_112$$60);
					ZVAL_STRING(&_112$$60, "/^(?:\\[?[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\]?\\.)?\\[?([A-Za-z_][A-Za-z0-9_]*)\\]?$/");
					ZEPHIR_INIT_NVAR(&_113$$60);
					ZEPHIR_INIT_NVAR(&_114$$60);
					ZVAL_STRING(&_114$$60, "/^(?:\\[?[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\]?\\.)?\\[?([A-Za-z_][A-Za-z0-9_]*)\\]?$/");
					zephir_preg_match(&_113$$60, &_114$$60, &expression, &matches, 0, 0 , 0 );
					if (zephir_is_true(&_113$$60)) {
						ZEPHIR_OBS_NVAR(&columnAlias);
						zephir_array_fetch_long(&columnAlias, &matches, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1934);
					}
				}
				ZEPHIR_INIT_NVAR(&_115$$50);
				zephir_create_array(&_115$$50, 2, 0);
				add_assoc_stringl_ex(&_115$$50, SL("type"), SL("scalar"));
				ZEPHIR_CALL_METHOD(&_116$$50, &rewriter, "rewrite", &_56, 0, &expression);
				zephir_check_call_status();
				zephir_array_update_string(&_115$$50, SL("column"), &_116$$50, PH_COPY | PH_SEPARATE);
				ZEPHIR_CPY_WRT(&expression, &_115$$50);
				if (Z_TYPE_P(&columnAlias) != IS_NULL) {
					zephir_array_update_string(&expression, SL("balias"), &columnAlias, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&expression, SL("sqlAlias"), &columnAlias, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&irColumns, &columnAlias, &expression, PH_COPY | PH_SEPARATE);
				} else {
					ZEPHIR_INIT_NVAR(&_117$$63);
					ZVAL_LONG(&_117$$63, position);
					ZEPHIR_INIT_NVAR(&_118$$63);
					ZEPHIR_CONCAT_SV(&_118$$63, "_", &_117$$63);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_zval(&irColumns, &_118$$63, &expression, PH_COPY | PH_SEPARATE);
				}
				position++;
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _80$$47, "rewind", NULL, 0);
			zephir_check_call_status();
			_120$$47 = 1;
			while (1) {
				if (_120$$47) {
					_120$$47 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _80$$47, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_119$$47, _80$$47, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_119$$47)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, _80$$47, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&item, _80$$47, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&key) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&expression);
						zephir_fast_trim(&expression, &item, NULL , ZEPHIR_TRIM_BOTH);
						ZEPHIR_CPY_WRT(&columnAlias, &key);
					} else {
						ZEPHIR_CALL_CE_STATIC(&split, phalcon_mvc_model_query_fragmentrewriter_ce, "splitAlias", &_85, 0, &item);
						zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&expression);
						zephir_array_fetch_long(&expression, &split, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1870);
						ZEPHIR_OBS_NVAR(&columnAlias);
						zephir_array_fetch_long(&columnAlias, &split, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1871);
					}
					if (ZEPHIR_IS_STRING_IDENTICAL(&expression, "*")) {
						if (Z_TYPE_P(&queryModels) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_122$$67);
							zephir_string_to_char_array(&_122$$67, &queryModels);
							_121$$67 = &_122$$67;
						} else {
							_121$$67 = &queryModels;
						}
						zephir_is_iterable(_121$$67, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1890);
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_121$$67), _123$$67)
						{
							ZEPHIR_INIT_NVAR(&queryModel);
							ZVAL_COPY(&queryModel, _123$$67);
							ZEPHIR_OBS_NVAR(&_124$$68);
							zephir_array_fetch_string(&_124$$68, &queryModel, SL("from"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1879);
							if (zephir_is_true(&_124$$68)) {
								ZVAL_NULL(&_125$$69);
								ZEPHIR_CALL_METHOD(&domain, this_ptr, "compileObjectAlias", &_76, 0, &queryModel, &_125$$69);
								zephir_check_call_status();
								ZEPHIR_INIT_NVAR(&_126$$69);
								zephir_create_array(&_126$$69, 4, 0);
								add_assoc_stringl_ex(&_126$$69, SL("type"), SL("object"));
								ZEPHIR_OBS_NVAR(&_127$$69);
								zephir_array_fetch_string(&_127$$69, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1883);
								zephir_array_update_string(&_126$$69, SL("model"), &_127$$69, PH_COPY | PH_SEPARATE);
								ZEPHIR_OBS_NVAR(&_127$$69);
								zephir_array_fetch_string(&_127$$69, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1884);
								zephir_array_update_string(&_126$$69, SL("column"), &_127$$69, PH_COPY | PH_SEPARATE);
								zephir_array_update_string(&_126$$69, SL("balias"), &domain, PH_COPY | PH_SEPARATE);
								zephir_array_update_zval(&irColumns, &domain, &_126$$69, PH_COPY | PH_SEPARATE);
							}
						} ZEND_HASH_FOREACH_END();
						ZEPHIR_INIT_NVAR(&queryModel);
						position++;
						continue;
					}
					if (zephir_end_with_str(&expression, SL(".*"))) {
						ZVAL_LONG(&_128$$70, 0);
						ZVAL_LONG(&_129$$70, -2);
						ZEPHIR_INIT_NVAR(&_130$$70);
						zephir_substr(&_130$$70, &expression, 0 , -2 , 0);
						ZEPHIR_INIT_NVAR(&_131$$70);
						ZVAL_STRING(&_131$$70, "[]");
						ZEPHIR_INIT_NVAR(&domain);
						zephir_fast_trim(&domain, &_130$$70, &_131$$70, ZEPHIR_TRIM_BOTH);
						ZEPHIR_INIT_NVAR(&domainInfo);
						ZVAL_NULL(&domainInfo);
						if (Z_TYPE_P(&queryModels) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_133$$70);
							zephir_string_to_char_array(&_133$$70, &queryModels);
							_132$$70 = &_133$$70;
						} else {
							_132$$70 = &queryModels;
						}
						zephir_is_iterable(_132$$70, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1908);
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_132$$70), _134$$70)
						{
							ZEPHIR_INIT_NVAR(&queryModel);
							ZVAL_COPY(&queryModel, _134$$70);
							ZEPHIR_OBS_NVAR(&_135$$71);
							zephir_array_fetch_string(&_135$$71, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1902);
							_136$$71 = ZEPHIR_IS_IDENTICAL(&_135$$71, &domain);
							if (!(_136$$71)) {
								ZEPHIR_INIT_NVAR(&_137$$71);
								ZEPHIR_OBS_NVAR(&_138$$71);
								zephir_array_fetch_string(&_138$$71, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1902);
								ZEPHIR_INIT_NVAR(&_139$$71);
								ZVAL_STRING(&_139$$71, "\\");
								zephir_fast_trim(&_137$$71, &_138$$71, &_139$$71, ZEPHIR_TRIM_LEFT);
								ZEPHIR_INIT_NVAR(&_140$$71);
								ZEPHIR_INIT_NVAR(&_141$$71);
								ZVAL_STRING(&_141$$71, "\\");
								zephir_fast_trim(&_140$$71, &domain, &_141$$71, ZEPHIR_TRIM_LEFT);
								_136$$71 = ZEPHIR_IS_IDENTICAL(&_137$$71, &_140$$71);
							}
							if (_136$$71) {
								ZEPHIR_CPY_WRT(&domainInfo, &queryModel);
								break;
							}
						} ZEND_HASH_FOREACH_END();
						ZEPHIR_INIT_NVAR(&queryModel);
						if (UNEXPECTED(Z_TYPE_P(&domainInfo) != IS_ARRAY)) {
							ZEPHIR_INIT_NVAR(&_142$$73);
							object_init_ex(&_142$$73, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_NVAR(&_143$$73);
							ZEPHIR_CONCAT_SVS(&_143$$73, "Unknown model or alias '", &domain, "' in the columns");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_142$$73, "__construct", &_109, 32, &_143$$73);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_142$$73, "phalcon/Mvc/Model/Query/Builder.zep", 1911);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&domain, this_ptr, "compileObjectAlias", &_76, 0, &domainInfo, &columnAlias);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_144$$70);
						zephir_create_array(&_144$$70, 4, 0);
						add_assoc_stringl_ex(&_144$$70, SL("type"), SL("object"));
						ZEPHIR_OBS_NVAR(&_145$$70);
						zephir_array_fetch_string(&_145$$70, &domainInfo, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1917);
						zephir_array_update_string(&_144$$70, SL("model"), &_145$$70, PH_COPY | PH_SEPARATE);
						ZEPHIR_OBS_NVAR(&_145$$70);
						zephir_array_fetch_string(&_145$$70, &domainInfo, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1918);
						zephir_array_update_string(&_144$$70, SL("column"), &_145$$70, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_144$$70, SL("balias"), &domain, PH_COPY | PH_SEPARATE);
						zephir_array_update_zval(&irColumns, &domain, &_144$$70, PH_COPY | PH_SEPARATE);
						position++;
						continue;
					}
					if (Z_TYPE_P(&columnAlias) == IS_NULL) {
						ZEPHIR_INIT_NVAR(&matches);
						ZVAL_NULL(&matches);
						ZEPHIR_INIT_NVAR(&_146$$74);
						ZVAL_STRING(&_146$$74, "/^(?:\\[?[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\]?\\.)?\\[?([A-Za-z_][A-Za-z0-9_]*)\\]?$/");
						ZEPHIR_INIT_NVAR(&_147$$74);
						ZEPHIR_INIT_NVAR(&_148$$74);
						ZVAL_STRING(&_148$$74, "/^(?:\\[?[A-Za-z_\\\\][A-Za-z0-9_\\\\]*\\]?\\.)?\\[?([A-Za-z_][A-Za-z0-9_]*)\\]?$/");
						zephir_preg_match(&_147$$74, &_148$$74, &expression, &matches, 0, 0 , 0 );
						if (zephir_is_true(&_147$$74)) {
							ZEPHIR_OBS_NVAR(&columnAlias);
							zephir_array_fetch_long(&columnAlias, &matches, 1, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1934);
						}
					}
					ZEPHIR_INIT_NVAR(&_149$$64);
					zephir_create_array(&_149$$64, 2, 0);
					add_assoc_stringl_ex(&_149$$64, SL("type"), SL("scalar"));
					ZEPHIR_CALL_METHOD(&_150$$64, &rewriter, "rewrite", &_56, 0, &expression);
					zephir_check_call_status();
					zephir_array_update_string(&_149$$64, SL("column"), &_150$$64, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&expression, &_149$$64);
					if (Z_TYPE_P(&columnAlias) != IS_NULL) {
						zephir_array_update_string(&expression, SL("balias"), &columnAlias, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&expression, SL("sqlAlias"), &columnAlias, PH_COPY | PH_SEPARATE);
						zephir_array_update_zval(&irColumns, &columnAlias, &expression, PH_COPY | PH_SEPARATE);
					} else {
						ZEPHIR_INIT_NVAR(&_151$$77);
						ZVAL_LONG(&_151$$77, position);
						ZEPHIR_INIT_NVAR(&_152$$77);
						ZEPHIR_CONCAT_SV(&_152$$77, "_", &_151$$77);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_update_zval(&irColumns, &_152$$77, &expression, PH_COPY | PH_SEPARATE);
					}
					position++;
			}
		}
		ZEPHIR_INIT_NVAR(&item);
		ZEPHIR_INIT_NVAR(&key);
	}
	if (Z_TYPE_P(&irColumns) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_154);
		zephir_string_to_char_array(&_154, &irColumns);
		_153 = &_154;
	} else {
		_153 = &irColumns;
	}
	zephir_is_iterable(_153, 0, "phalcon/Mvc/Model/Query/Builder.zep", 1964);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_153), _156, _157, _155)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_157 != NULL) { 
			ZVAL_STR_COPY(&key, _157);
		} else {
			ZVAL_LONG(&key, _156);
		}
		ZEPHIR_INIT_NVAR(&item);
		ZVAL_COPY(&item, _155);
		_158$$78 = Z_TYPE_P(&key) == IS_STRING;
		if (_158$$78) {
			ZEPHIR_OBS_NVAR(&_159$$78);
			zephir_array_fetch_string(&_159$$78, &item, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1959);
			_158$$78 = ZEPHIR_IS_STRING(&_159$$78, "scalar");
		}
		if (_158$$78) {
			ZEPHIR_CALL_METHOD(NULL, &rewriter, "addAlias", &_160, 0, &key);
			zephir_check_call_status();
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_INIT_VAR(&intermediate);
	zephir_create_array(&intermediate, 3, 0);
	zephir_array_update_string(&intermediate, SL("models"), &irModels, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&intermediate, SL("tables"), &irTables, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&intermediate, SL("columns"), &irColumns, PH_COPY | PH_SEPARATE);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_6, 784, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&distinct, &_0);
	if (((Z_TYPE_P(&distinct) == IS_TRUE || Z_TYPE_P(&distinct) == IS_FALSE) == 1)) {
		zephir_array_update_string(&intermediate, SL("distinct"), &distinct, PH_COPY | PH_SEPARATE);
	}
	if (zephir_fast_count_int(&irJoins)) {
		zephir_array_update_string(&intermediate, SL("joins"), &irJoins, PH_COPY | PH_SEPARATE);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_7, 781, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&conditions, &_0);
	if (zephir_is_numeric(&conditions)) {
		if (UNEXPECTED(zephir_fast_count_int(&irModels) > 1)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Cannot build the query. Invalid condition", "phalcon/Mvc/Model/Query/Builder.zep", 1989);
			return;
		}
		ZEPHIR_OBS_NVAR(&queryModel);
		zephir_array_fetch_long(&queryModel, &queryModels, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1992);
		zephir_memory_observe(&_162$$82);
		zephir_array_fetch_string(&_162$$82, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 1993);
		ZEPHIR_CALL_METHOD(&model, &manager, "load", NULL, 0, &_162$$82);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&primaryKeys, &metaData, "getPrimaryKeyAttributes", NULL, 0, &model);
		zephir_check_call_status();
		if (UNEXPECTED(!(zephir_fast_count_int(&primaryKeys)))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "Source related to this model does not have a primary key defined", "phalcon/Mvc/Model/Query/Builder.zep", 1999);
			return;
		}
		zephir_array_update_string(&bindParams, SL("APK0"), &conditions, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_163$$82);
		zephir_create_array(&_163$$82, 2, 0);
		add_assoc_stringl_ex(&_163$$82, SL("type"), SL("literal"));
		zephir_memory_observe(&_165$$82);
		zephir_array_fetch_string(&_165$$82, &queryModel, SL("alias"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2006);
		ZEPHIR_CALL_METHOD(&_164$$82, &rewriter, "escape", NULL, 0, &_165$$82);
		zephir_check_call_status();
		zephir_memory_observe(&_167$$82);
		zephir_array_fetch_long(&_167$$82, &primaryKeys, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2006);
		ZEPHIR_CALL_METHOD(&_166$$82, &rewriter, "escape", NULL, 0, &_167$$82);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_168$$82);
		ZEPHIR_CONCAT_VSVS(&_168$$82, &_164$$82, ".", &_166$$82, " = :APK0");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_update_string(&_163$$82, SL("value"), &_168$$82, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&intermediate, SL("where"), &_163$$82, PH_COPY | PH_SEPARATE);
	} else {
		_161 = Z_TYPE_P(&conditions) == IS_STRING;
		if (_161) {
			_161 = !ZEPHIR_IS_STRING_IDENTICAL(&conditions, "");
		}
		if (_161) {
			ZEPHIR_CALL_METHOD(&_169$$85, &rewriter, "rewrite", &_56, 0, &conditions);
			zephir_check_call_status();
			zephir_array_update_string(&intermediate, SL("where"), &_169$$85, PH_COPY | PH_SEPARATE);
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_8, 795, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&group, &_0);
	_170 = Z_TYPE_P(&group) == IS_ARRAY;
	if (_170) {
		_170 = ((zephir_fast_count_int(&group)) ? 1 : 0);
	}
	if (_170) {
		ZEPHIR_INIT_VAR(&groupItems);
		array_init(&groupItems);
		if (Z_TYPE_P(&group) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_172$$86);
			zephir_string_to_char_array(&_172$$86, &group);
			_171$$86 = &_172$$86;
		} else {
			_171$$86 = &group;
		}
		zephir_is_iterable(_171$$86, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2026);
		if (Z_TYPE_P(_171$$86) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_171$$86), _173$$86)
			{
				ZEPHIR_INIT_NVAR(&item);
				ZVAL_COPY(&item, _173$$86);
				_174$$87 = Z_TYPE_P(&item) == IS_STRING;
				if (_174$$87) {
					ZEPHIR_INIT_NVAR(&_175$$87);
					zephir_fast_trim(&_175$$87, &item, NULL , ZEPHIR_TRIM_BOTH);
					_174$$87 = !ZEPHIR_IS_STRING_IDENTICAL(&_175$$87, "");
				}
				if (_174$$87) {
					ZEPHIR_CALL_METHOD(&_176$$88, &rewriter, "rewrite", &_56, 0, &item);
					zephir_check_call_status();
					zephir_array_append(&groupItems, &_176$$88, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2022);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _171$$86, "rewind", NULL, 0);
			zephir_check_call_status();
			_178$$86 = 1;
			while (1) {
				if (_178$$86) {
					_178$$86 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _171$$86, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_177$$86, _171$$86, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_177$$86)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&item, _171$$86, "current", NULL, 0);
				zephir_check_call_status();
					_179$$89 = Z_TYPE_P(&item) == IS_STRING;
					if (_179$$89) {
						ZEPHIR_INIT_NVAR(&_180$$89);
						zephir_fast_trim(&_180$$89, &item, NULL , ZEPHIR_TRIM_BOTH);
						_179$$89 = !ZEPHIR_IS_STRING_IDENTICAL(&_180$$89, "");
					}
					if (_179$$89) {
						ZEPHIR_CALL_METHOD(&_181$$90, &rewriter, "rewrite", &_56, 0, &item);
						zephir_check_call_status();
						zephir_array_append(&groupItems, &_181$$90, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2022);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&item);
		if (zephir_fast_count_int(&groupItems)) {
			zephir_array_update_string(&intermediate, SL("group"), &groupItems, PH_COPY | PH_SEPARATE);
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_9, 788, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&having, &_0);
	_182 = Z_TYPE_P(&having) == IS_STRING;
	if (_182) {
		_182 = !ZEPHIR_IS_STRING_IDENTICAL(&having, "");
	}
	if (_182) {
		ZEPHIR_CALL_METHOD(&_183$$92, &rewriter, "rewrite", &_56, 0, &having);
		zephir_check_call_status();
		zephir_array_update_string(&intermediate, SL("having"), &_183$$92, PH_COPY | PH_SEPARATE);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_10, 789, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&order, &_0);
	_184 = Z_TYPE_P(&order) != IS_NULL;
	if (_184) {
		_184 = !ZEPHIR_IS_STRING_IDENTICAL(&order, "");
	}
	if (_184) {
		if (Z_TYPE_P(&order) != IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_185$$94);
			zephir_create_array(&_185$$94, 1, 0);
			zephir_array_fast_append(&_185$$94, &order);
			ZEPHIR_CPY_WRT(&order, &_185$$94);
		}
		ZEPHIR_INIT_VAR(&orderItems);
		array_init(&orderItems);
		if (Z_TYPE_P(&order) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_187$$93);
			zephir_string_to_char_array(&_187$$93, &order);
			_186$$93 = &_187$$93;
		} else {
			_186$$93 = &order;
		}
		zephir_is_iterable(_186$$93, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2065);
		if (Z_TYPE_P(_186$$93) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_186$$93), _188$$93)
			{
				ZEPHIR_INIT_NVAR(&item);
				ZVAL_COPY(&item, _188$$93);
				if (Z_TYPE_P(&item) == IS_LONG) {
					ZEPHIR_INIT_NVAR(&_189$$96);
					zephir_create_array(&_189$$96, 1, 0);
					ZEPHIR_INIT_NVAR(&_190$$96);
					zephir_create_array(&_190$$96, 2, 0);
					add_assoc_stringl_ex(&_190$$96, SL("type"), SL("literal"));
					zephir_cast_to_string(&_191$$96, &item);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_update_string(&_190$$96, SL("value"), &_191$$96, PH_COPY | PH_SEPARATE);
					zephir_array_fast_append(&_189$$96, &_190$$96);
					zephir_array_append(&orderItems, &_189$$96, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2059);
				} else {
					ZEPHIR_INIT_NVAR(&_192$$97);
					zephir_create_array(&_192$$97, 1, 0);
					zephir_cast_to_string(&_194$$97, &item);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_193$$97, &rewriter, "rewrite", &_56, 0, &_194$$97);
					zephir_check_call_status();
					zephir_array_fast_append(&_192$$97, &_193$$97);
					zephir_array_append(&orderItems, &_192$$97, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2061);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _186$$93, "rewind", NULL, 0);
			zephir_check_call_status();
			_196$$93 = 1;
			while (1) {
				if (_196$$93) {
					_196$$93 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _186$$93, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_195$$93, _186$$93, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_195$$93)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&item, _186$$93, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&item) == IS_LONG) {
						ZEPHIR_INIT_NVAR(&_197$$99);
						zephir_create_array(&_197$$99, 1, 0);
						ZEPHIR_INIT_NVAR(&_198$$99);
						zephir_create_array(&_198$$99, 2, 0);
						add_assoc_stringl_ex(&_198$$99, SL("type"), SL("literal"));
						zephir_cast_to_string(&_199$$99, &item);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_update_string(&_198$$99, SL("value"), &_199$$99, PH_COPY | PH_SEPARATE);
						zephir_array_fast_append(&_197$$99, &_198$$99);
						zephir_array_append(&orderItems, &_197$$99, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2059);
					} else {
						ZEPHIR_INIT_NVAR(&_200$$100);
						zephir_create_array(&_200$$100, 1, 0);
						zephir_cast_to_string(&_202$$100, &item);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&_201$$100, &rewriter, "rewrite", &_56, 0, &_202$$100);
						zephir_check_call_status();
						zephir_array_fast_append(&_200$$100, &_201$$100);
						zephir_array_append(&orderItems, &_200$$100, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2061);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&item);
		zephir_array_update_string(&intermediate, SL("order"), &orderItems, PH_COPY | PH_SEPARATE);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_11, 790, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&limit, &_0);
	if (Z_TYPE_P(&limit) != IS_NULL) {
		ZEPHIR_INIT_VAR(&number);
		ZVAL_NULL(&number);
		ZEPHIR_INIT_VAR(&offset);
		ZVAL_NULL(&offset);
		if (Z_TYPE_P(&limit) == IS_ARRAY) {
			ZEPHIR_OBS_NVAR(&number);
			zephir_array_isset_string_fetch(&number, &limit, SL("number"), 0);
			ZEPHIR_OBS_NVAR(&offset);
			if (zephir_array_isset_string_fetch(&offset, &limit, SL("offset"), 0)) {
				if (!(zephir_is_numeric(&offset))) {
					ZEPHIR_INIT_NVAR(&offset);
					ZVAL_LONG(&offset, 0);
				}
			}
		} else if (zephir_is_numeric(&limit)) {
			ZEPHIR_CPY_WRT(&number, &limit);
			zephir_read_property_cached(&_203$$105, this_ptr, _zephir_prop_12, 791, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&offset, &_203$$105);
			_204$$105 = Z_TYPE_P(&offset) != IS_NULL;
			if (_204$$105) {
				_204$$105 = !(zephir_is_numeric(&offset));
			}
			if (_204$$105) {
				ZEPHIR_INIT_NVAR(&offset);
				ZVAL_LONG(&offset, 0);
			}
		}
		if (zephir_is_numeric(&number)) {
			ZEPHIR_INIT_VAR(&_205$$107);
			zephir_create_array(&_205$$107, 1, 0);
			ZEPHIR_INIT_VAR(&_206$$107);
			zephir_create_array(&_206$$107, 2, 0);
			add_assoc_stringl_ex(&_206$$107, SL("type"), SL("placeholder"));
			add_assoc_stringl_ex(&_206$$107, SL("value"), SL(":APL0"));
			zephir_array_update_string(&_205$$107, SL("number"), &_206$$107, PH_COPY | PH_SEPARATE);
			ZEPHIR_CPY_WRT(&limit, &_205$$107);
			ZVAL_LONG(&_207$$107, 10);
			ZEPHIR_CALL_FUNCTION(&_208$$107, "intval", NULL, 41, &number, &_207$$107);
			zephir_check_call_status();
			zephir_array_update_string(&bindParams, SL("APL0"), &_208$$107, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_VAR(&_209$$107);
			ZVAL_LONG(&_209$$107, 1);
			zephir_array_update_string(&bindTypes, SL("APL0"), &_209$$107, PH_COPY | PH_SEPARATE);
			_210$$107 = zephir_is_numeric(&offset);
			if (_210$$107) {
				_210$$107 = !ZEPHIR_IS_LONG(&offset, 0);
			}
			if (_210$$107) {
				ZEPHIR_INIT_VAR(&_211$$108);
				zephir_create_array(&_211$$108, 2, 0);
				add_assoc_stringl_ex(&_211$$108, SL("type"), SL("placeholder"));
				add_assoc_stringl_ex(&_211$$108, SL("value"), SL(":APL1"));
				zephir_array_update_string(&limit, SL("offset"), &_211$$108, PH_COPY | PH_SEPARATE);
				ZVAL_LONG(&_212$$108, 10);
				ZEPHIR_CALL_FUNCTION(&_213$$108, "intval", NULL, 41, &offset, &_212$$108);
				zephir_check_call_status();
				zephir_array_update_string(&bindParams, SL("APL1"), &_213$$108, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_VAR(&_214$$108);
				ZVAL_LONG(&_214$$108, 1);
				zephir_array_update_string(&bindTypes, SL("APL1"), &_214$$108, PH_COPY | PH_SEPARATE);
			}
			zephir_array_update_string(&intermediate, SL("limit"), &limit, PH_COPY | PH_SEPARATE);
		}
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_13, 792, PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&_0)) {
		zephir_array_update_string(&intermediate, SL("forUpdate"), &__$true, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_CALL_METHOD(&_2, &rewriter, "getBindTypes", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_2) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_216);
		zephir_string_to_char_array(&_216, &_2);
		_215 = &_216;
	} else {
		_215 = &_2;
	}
	zephir_is_iterable(_215, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2131);
	if (Z_TYPE_P(_215) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_215), _218, _219, _217)
		{
			ZEPHIR_INIT_NVAR(&typeName);
			if (_219 != NULL) { 
				ZVAL_STR_COPY(&typeName, _219);
			} else {
				ZVAL_LONG(&typeName, _218);
			}
			ZEPHIR_INIT_NVAR(&typeValue);
			ZVAL_COPY(&typeValue, _217);
			zephir_array_update_zval(&bindTypes, &typeName, &typeValue, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _215, "rewind", NULL, 0);
		zephir_check_call_status();
		_221 = 1;
		while (1) {
			if (_221) {
				_221 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _215, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_220, _215, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_220)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&typeName, _215, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&typeValue, _215, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_update_zval(&bindTypes, &typeName, &typeValue, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&typeValue);
	ZEPHIR_INIT_NVAR(&typeName);
	zephir_create_array(return_value, 3, 0);
	zephir_array_update_string(return_value, SL("intermediate"), &intermediate, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("bindParams"), &bindParams, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("bindTypes"), &bindTypes, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

/**
 * Best alias for a complete object in the resultset, as PHQL picks it
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, compileObjectAlias)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *queryModel_param = NULL, *columnAlias, columnAlias_sub, modelName, _1, _2$$4;
	zval queryModel;

	ZVAL_UNDEF(&queryModel);
	ZVAL_UNDEF(&columnAlias_sub);
	ZVAL_UNDEF(&modelName);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$4);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(queryModel, queryModel_param)
		Z_PARAM_ZVAL(columnAlias)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &queryModel_param, &columnAlias);
	zephir_get_arrval(&queryModel, queryModel_param);
	_0 = Z_TYPE_P(columnAlias) == IS_STRING;
	if (_0) {
		_0 = !ZEPHIR_IS_STRING_IDENTICAL(columnAlias, "");
	}
	if (_0) {
		RETVAL_ZVAL(columnAlias, 1, 0);
		RETURN_MM();
	}
	zephir_array_fetch_string(&_1, &queryModel, SL("named"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2149);
	if (zephir_is_true(&_1)) {
		zephir_array_fetch_string(&_2$$4, &queryModel, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2150);
		RETURN_CTOR(&_2$$4);
	}
	zephir_memory_observe(&modelName);
	zephir_array_fetch_string(&modelName, &queryModel, SL("model"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2153);
	if (zephir_memnstr_str(&modelName, SL("\\"), "phalcon/Mvc/Model/Query/Builder.zep", 2155)) {
		RETURN_CCTOR(&modelName);
	}
	ZEPHIR_RETURN_CALL_FUNCTION("lcfirst", NULL, 83, &modelName);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Join conditions for an implicit join, from the relation between a
 * model already in the query and the joined model. Returns null when the
 * models are not related.
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, compileRelationJoin)
{
	zend_bool _60, _77, _28$$7;
	zend_string *_53, *_70, *_15$$7;
	zend_ulong _52, _69, _14$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval left, right, _83, _85, _86, _39$$7, _41$$7, _42$$7;
	zval *manager, manager_sub, *rewriter, rewriter_sub, *left_param = NULL, *right_param = NULL, relation, relations, fields, referencedFields, position, field, conditions, intermediateModelName, intermediateModel, intermediateFields, intermediateReferencedFields, intermediateSource, intermediateSchema, intermediateTable, intermediateConditions, _0, _1, _8, _44, *_49, _50, *_51, _59, *_66, _67, *_68, _76, _84, _87, _2$$3, _3$$3, _4$$5, _5$$5, _6$$5, _7$$5, _9$$8, _10$$8, *_11$$7, _12$$7, *_13$$7, _27$$7, _40$$7, _43$$7, _16$$10, _17$$10, _18$$10, _19$$10, _20$$9, _21$$9, _23$$9, _24$$9, _25$$9, _26$$9, _29$$12, _30$$12, _31$$12, _32$$12, _33$$11, _34$$11, _35$$11, _36$$11, _37$$11, _38$$11, _45$$15, _46$$15, _47$$15, _48$$15, _54$$16, _55$$16, _56$$16, _57$$16, _58$$16, _61$$17, _62$$17, _63$$17, _64$$17, _65$$17, _71$$18, _72$$18, _73$$18, _74$$18, _75$$18, _78$$19, _79$$19, _80$$19, _81$$19, _82$$19;

	ZVAL_UNDEF(&manager_sub);
	ZVAL_UNDEF(&rewriter_sub);
	ZVAL_UNDEF(&relation);
	ZVAL_UNDEF(&relations);
	ZVAL_UNDEF(&fields);
	ZVAL_UNDEF(&referencedFields);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&conditions);
	ZVAL_UNDEF(&intermediateModelName);
	ZVAL_UNDEF(&intermediateModel);
	ZVAL_UNDEF(&intermediateFields);
	ZVAL_UNDEF(&intermediateReferencedFields);
	ZVAL_UNDEF(&intermediateSource);
	ZVAL_UNDEF(&intermediateSchema);
	ZVAL_UNDEF(&intermediateTable);
	ZVAL_UNDEF(&intermediateConditions);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_44);
	ZVAL_UNDEF(&_50);
	ZVAL_UNDEF(&_59);
	ZVAL_UNDEF(&_67);
	ZVAL_UNDEF(&_76);
	ZVAL_UNDEF(&_84);
	ZVAL_UNDEF(&_87);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_27$$7);
	ZVAL_UNDEF(&_40$$7);
	ZVAL_UNDEF(&_43$$7);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_29$$12);
	ZVAL_UNDEF(&_30$$12);
	ZVAL_UNDEF(&_31$$12);
	ZVAL_UNDEF(&_32$$12);
	ZVAL_UNDEF(&_33$$11);
	ZVAL_UNDEF(&_34$$11);
	ZVAL_UNDEF(&_35$$11);
	ZVAL_UNDEF(&_36$$11);
	ZVAL_UNDEF(&_37$$11);
	ZVAL_UNDEF(&_38$$11);
	ZVAL_UNDEF(&_45$$15);
	ZVAL_UNDEF(&_46$$15);
	ZVAL_UNDEF(&_47$$15);
	ZVAL_UNDEF(&_48$$15);
	ZVAL_UNDEF(&_54$$16);
	ZVAL_UNDEF(&_55$$16);
	ZVAL_UNDEF(&_56$$16);
	ZVAL_UNDEF(&_57$$16);
	ZVAL_UNDEF(&_58$$16);
	ZVAL_UNDEF(&_61$$17);
	ZVAL_UNDEF(&_62$$17);
	ZVAL_UNDEF(&_63$$17);
	ZVAL_UNDEF(&_64$$17);
	ZVAL_UNDEF(&_65$$17);
	ZVAL_UNDEF(&_71$$18);
	ZVAL_UNDEF(&_72$$18);
	ZVAL_UNDEF(&_73$$18);
	ZVAL_UNDEF(&_74$$18);
	ZVAL_UNDEF(&_75$$18);
	ZVAL_UNDEF(&_78$$19);
	ZVAL_UNDEF(&_79$$19);
	ZVAL_UNDEF(&_80$$19);
	ZVAL_UNDEF(&_81$$19);
	ZVAL_UNDEF(&_82$$19);
	ZVAL_UNDEF(&left);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&_83);
	ZVAL_UNDEF(&_85);
	ZVAL_UNDEF(&_86);
	ZVAL_UNDEF(&_39$$7);
	ZVAL_UNDEF(&_41$$7);
	ZVAL_UNDEF(&_42$$7);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(manager, phalcon_mvc_model_managerinterface_ce)
		Z_PARAM_OBJECT_OF_CLASS(rewriter, phalcon_mvc_model_query_fragmentrewriter_ce)
		ZEPHIR_Z_PARAM_ARRAY(left, left_param)
		ZEPHIR_Z_PARAM_ARRAY(right, right_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &manager, &rewriter, &left_param, &right_param);
	zephir_get_arrval(&left, left_param);
	zephir_get_arrval(&right, right_param);
	zephir_array_fetch_string(&_0, &left, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2179);
	zephir_array_fetch_string(&_1, &right, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2179);
	ZEPHIR_CALL_METHOD(&relation, manager, "getRelationByAlias", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&relation)) {
		zephir_array_fetch_string(&_2$$3, &left, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2182);
		zephir_array_fetch_string(&_3$$3, &right, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2182);
		ZEPHIR_CALL_METHOD(&relations, manager, "getRelationsBetween", NULL, 0, &_2$$3, &_3$$3);
		zephir_check_call_status();
		if (Z_TYPE_P(&relations) != IS_ARRAY) {
			RETURN_MM_NULL();
		}
		if (UNEXPECTED(zephir_fast_count_int(&relations) != 1)) {
			ZEPHIR_INIT_VAR(&_4$$5);
			object_init_ex(&_4$$5, phalcon_mvc_model_exception_ce);
			zephir_array_fetch_string(&_5$$5, &left, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2190);
			zephir_array_fetch_string(&_6$$5, &right, SL("model"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2190);
			ZEPHIR_INIT_VAR(&_7$$5);
			ZEPHIR_CONCAT_SVSVS(&_7$$5, "There is more than one relation between models '", &_5$$5, "' and '", &_6$$5, "', the join must be done using an alias");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_4$$5, "__construct", NULL, 32, &_7$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_4$$5, "phalcon/Mvc/Model/Query/Builder.zep", 2191);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_OBS_NVAR(&relation);
		zephir_array_fetch_long(&relation, &relations, 0, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2194);
	}
	if (Z_TYPE_P(&relation) != IS_OBJECT) {
		RETURN_MM_NULL();
	}
	ZEPHIR_CALL_METHOD(&fields, &relation, "getFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&referencedFields, &relation, "getReferencedFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, &relation, "isThrough", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_8))) {
		if (Z_TYPE_P(&fields) != IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_9$$8);
			zephir_create_array(&_9$$8, 1, 0);
			zephir_array_fast_append(&_9$$8, &fields);
			ZEPHIR_CPY_WRT(&fields, &_9$$8);
			ZEPHIR_INIT_VAR(&_10$$8);
			zephir_create_array(&_10$$8, 1, 0);
			zephir_array_fast_append(&_10$$8, &referencedFields);
			ZEPHIR_CPY_WRT(&referencedFields, &_10$$8);
		}
		ZEPHIR_INIT_VAR(&conditions);
		array_init(&conditions);
		if (Z_TYPE_P(&fields) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_12$$7);
			zephir_string_to_char_array(&_12$$7, &fields);
			_11$$7 = &_12$$7;
		} else {
			_11$$7 = &fields;
		}
		zephir_is_iterable(_11$$7, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2222);
		if (Z_TYPE_P(_11$$7) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_11$$7), _14$$7, _15$$7, _13$$7)
			{
				ZEPHIR_INIT_NVAR(&position);
				if (_15$$7 != NULL) { 
					ZVAL_STR_COPY(&position, _15$$7);
				} else {
					ZVAL_LONG(&position, _14$$7);
				}
				ZEPHIR_INIT_NVAR(&field);
				ZVAL_COPY(&field, _13$$7);
				if (UNEXPECTED(!(zephir_array_isset_value(&referencedFields, &position)))) {
					ZEPHIR_INIT_NVAR(&_16$$10);
					object_init_ex(&_16$$10, phalcon_mvc_model_exception_ce);
					zephir_array_fetch_string(&_17$$10, &left, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2215);
					zephir_array_fetch_string(&_18$$10, &right, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2216);
					ZEPHIR_INIT_NVAR(&_19$$10);
					ZEPHIR_CONCAT_SVSV(&_19$$10, "The number of fields must be equal to the number of referenced fields in join ", &_17$$10, "-", &_18$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_16$$10, "__construct", NULL, 32, &_19$$10);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_16$$10, "phalcon/Mvc/Model/Query/Builder.zep", 2216);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_fetch_string(&_21$$9, &left, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
				ZEPHIR_CALL_METHOD(&_20$$9, rewriter, "qualify", &_22, 0, &_21$$9, &field);
				zephir_check_call_status();
				zephir_array_fetch_string(&_24$$9, &right, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
				ZEPHIR_OBS_NVAR(&_25$$9);
				zephir_array_fetch(&_25$$9, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
				ZEPHIR_CALL_METHOD(&_23$$9, rewriter, "qualify", &_22, 0, &_24$$9, &_25$$9);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_26$$9);
				ZEPHIR_CONCAT_VSV(&_26$$9, &_20$$9, " = ", &_23$$9);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&conditions, &_26$$9, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _11$$7, "rewind", NULL, 0);
			zephir_check_call_status();
			_28$$7 = 1;
			while (1) {
				if (_28$$7) {
					_28$$7 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _11$$7, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_27$$7, _11$$7, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_27$$7)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&position, _11$$7, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&field, _11$$7, "current", NULL, 0);
				zephir_check_call_status();
					if (UNEXPECTED(!(zephir_array_isset_value(&referencedFields, &position)))) {
						ZEPHIR_INIT_NVAR(&_29$$12);
						object_init_ex(&_29$$12, phalcon_mvc_model_exception_ce);
						zephir_array_fetch_string(&_30$$12, &left, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2215);
						zephir_array_fetch_string(&_31$$12, &right, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2216);
						ZEPHIR_INIT_NVAR(&_32$$12);
						ZEPHIR_CONCAT_SVSV(&_32$$12, "The number of fields must be equal to the number of referenced fields in join ", &_30$$12, "-", &_31$$12);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_29$$12, "__construct", NULL, 32, &_32$$12);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_29$$12, "phalcon/Mvc/Model/Query/Builder.zep", 2216);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_fetch_string(&_34$$11, &left, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
					ZEPHIR_CALL_METHOD(&_33$$11, rewriter, "qualify", &_22, 0, &_34$$11, &field);
					zephir_check_call_status();
					zephir_array_fetch_string(&_36$$11, &right, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
					ZEPHIR_OBS_NVAR(&_37$$11);
					zephir_array_fetch(&_37$$11, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
					ZEPHIR_CALL_METHOD(&_35$$11, rewriter, "qualify", &_22, 0, &_36$$11, &_37$$11);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_38$$11);
					ZEPHIR_CONCAT_VSV(&_38$$11, &_33$$11, " = ", &_35$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&conditions, &_38$$11, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2219);
			}
		}
		ZEPHIR_INIT_NVAR(&field);
		ZEPHIR_INIT_NVAR(&position);
		zephir_create_array(return_value, 1, 0);
		ZEPHIR_INIT_VAR(&_39$$7);
		zephir_create_array(&_39$$7, 3, 0);
		zephir_memory_observe(&_40$$7);
		zephir_array_fetch_string(&_40$$7, &right, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2224);
		zephir_array_update_string(&_39$$7, SL("type"), &_40$$7, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(&_40$$7);
		zephir_array_fetch_string(&_40$$7, &right, SL("table"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2225);
		zephir_array_update_string(&_39$$7, SL("source"), &_40$$7, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_41$$7);
		zephir_create_array(&_41$$7, 1, 0);
		ZEPHIR_INIT_VAR(&_42$$7);
		zephir_create_array(&_42$$7, 2, 0);
		add_assoc_stringl_ex(&_42$$7, SL("type"), SL("literal"));
		ZEPHIR_INIT_VAR(&_43$$7);
		zephir_fast_join_str(&_43$$7, SL(" AND "), &conditions);
		zephir_array_update_string(&_42$$7, SL("value"), &_43$$7, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_41$$7, &_42$$7);
		zephir_array_update_string(&_39$$7, SL("conditions"), &_41$$7, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(return_value, &_39$$7);
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&intermediateModelName, &relation, "getIntermediateModel", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateModel, manager, "load", NULL, 0, &intermediateModelName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateSource, &intermediateModel, "getSource", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateSchema, &intermediateModel, "getSchema", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateFields, &relation, "getIntermediateFields", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&intermediateReferencedFields, &relation, "getIntermediateReferencedFields", NULL, 0);
	zephir_check_call_status();
	ZVAL_BOOL(&_44, 0);
	ZEPHIR_CALL_METHOD(NULL, rewriter, "addModel", NULL, 0, &intermediateModelName, &intermediateModel, &intermediateSource, &_44);
	zephir_check_call_status();
	if (zephir_is_true(&intermediateSchema)) {
		ZEPHIR_INIT_VAR(&intermediateTable);
		zephir_create_array(&intermediateTable, 2, 0);
		zephir_array_fast_append(&intermediateTable, &intermediateSource);
		zephir_array_fast_append(&intermediateTable, &intermediateSchema);
	} else {
		ZEPHIR_CPY_WRT(&intermediateTable, &intermediateSource);
	}
	if (Z_TYPE_P(&fields) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_45$$15);
		zephir_create_array(&_45$$15, 1, 0);
		zephir_array_fast_append(&_45$$15, &fields);
		ZEPHIR_CPY_WRT(&fields, &_45$$15);
		ZEPHIR_INIT_VAR(&_46$$15);
		zephir_create_array(&_46$$15, 1, 0);
		zephir_array_fast_append(&_46$$15, &referencedFields);
		ZEPHIR_CPY_WRT(&referencedFields, &_46$$15);
		ZEPHIR_INIT_VAR(&_47$$15);
		zephir_create_array(&_47$$15, 1, 0);
		zephir_array_fast_append(&_47$$15, &intermediateFields);
		ZEPHIR_CPY_WRT(&intermediateFields, &_47$$15);
		ZEPHIR_INIT_VAR(&_48$$15);
		zephir_create_array(&_48$$15, 1, 0);
		zephir_array_fast_append(&_48$$15, &intermediateReferencedFields);
		ZEPHIR_CPY_WRT(&intermediateReferencedFields, &_48$$15);
	}
	ZEPHIR_INIT_VAR(&intermediateConditions);
	array_init(&intermediateConditions);
	ZEPHIR_INIT_NVAR(&conditions);
	array_init(&conditions);
	if (Z_TYPE_P(&fields) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_50);
		zephir_string_to_char_array(&_50, &fields);
		_49 = &_50;
	} else {
		_49 = &fields;
	}
	zephir_is_iterable(_49, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2268);
	if (Z_TYPE_P(_49) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_49), _52, _53, _51)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_53 != NULL) { 
				ZVAL_STR_COPY(&position, _53);
			} else {
				ZVAL_LONG(&position, _52);
			}
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _51);
			zephir_array_fetch_string(&_55$$16, &left, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2265);
			ZEPHIR_CALL_METHOD(&_54$$16, rewriter, "qualify", &_22, 0, &_55$$16, &field);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_57$$16);
			zephir_array_fetch(&_57$$16, &intermediateFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2265);
			ZEPHIR_CALL_METHOD(&_56$$16, rewriter, "qualify", &_22, 0, &intermediateSource, &_57$$16);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_58$$16);
			ZEPHIR_CONCAT_VSV(&_58$$16, &_54$$16, " = ", &_56$$16);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&intermediateConditions, &_58$$16, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2265);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _49, "rewind", NULL, 0);
		zephir_check_call_status();
		_60 = 1;
		while (1) {
			if (_60) {
				_60 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _49, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_59, _49, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_59)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&position, _49, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&field, _49, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch_string(&_62$$17, &left, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2265);
				ZEPHIR_CALL_METHOD(&_61$$17, rewriter, "qualify", &_22, 0, &_62$$17, &field);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_64$$17);
				zephir_array_fetch(&_64$$17, &intermediateFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2265);
				ZEPHIR_CALL_METHOD(&_63$$17, rewriter, "qualify", &_22, 0, &intermediateSource, &_64$$17);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_65$$17);
				ZEPHIR_CONCAT_VSV(&_65$$17, &_61$$17, " = ", &_63$$17);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&intermediateConditions, &_65$$17, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2265);
		}
	}
	ZEPHIR_INIT_NVAR(&field);
	ZEPHIR_INIT_NVAR(&position);
	if (Z_TYPE_P(&intermediateReferencedFields) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_67);
		zephir_string_to_char_array(&_67, &intermediateReferencedFields);
		_66 = &_67;
	} else {
		_66 = &intermediateReferencedFields;
	}
	zephir_is_iterable(_66, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2272);
	if (Z_TYPE_P(_66) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_66), _69, _70, _68)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_70 != NULL) { 
				ZVAL_STR_COPY(&position, _70);
			} else {
				ZVAL_LONG(&position, _69);
			}
			ZEPHIR_INIT_NVAR(&field);
			ZVAL_COPY(&field, _68);
			ZEPHIR_CALL_METHOD(&_71$$18, rewriter, "qualify", &_22, 0, &intermediateSource, &field);
			zephir_check_call_status();
			zephir_array_fetch_string(&_73$$18, &right, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2269);
			ZEPHIR_OBS_NVAR(&_74$$18);
			zephir_array_fetch(&_74$$18, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2269);
			ZEPHIR_CALL_METHOD(&_72$$18, rewriter, "qualify", &_22, 0, &_73$$18, &_74$$18);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_75$$18);
			ZEPHIR_CONCAT_VSV(&_75$$18, &_71$$18, " = ", &_72$$18);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&conditions, &_75$$18, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2269);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _66, "rewind", NULL, 0);
		zephir_check_call_status();
		_77 = 1;
		while (1) {
			if (_77) {
				_77 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _66, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_76, _66, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_76)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&position, _66, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&field, _66, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_78$$19, rewriter, "qualify", &_22, 0, &intermediateSource, &field);
				zephir_check_call_status();
				zephir_array_fetch_string(&_80$$19, &right, SL("alias"), PH_NOISY | PH_READONLY, "phalcon/Mvc/Model/Query/Builder.zep", 2269);
				ZEPHIR_OBS_NVAR(&_81$$19);
				zephir_array_fetch(&_81$$19, &referencedFields, &position, PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2269);
				ZEPHIR_CALL_METHOD(&_79$$19, rewriter, "qualify", &_22, 0, &_80$$19, &_81$$19);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_82$$19);
				ZEPHIR_CONCAT_VSV(&_82$$19, &_78$$19, " = ", &_79$$19);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&conditions, &_82$$19, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2269);
		}
	}
	ZEPHIR_INIT_NVAR(&field);
	ZEPHIR_INIT_NVAR(&position);
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_83);
	zephir_create_array(&_83, 3, 0);
	zephir_memory_observe(&_84);
	zephir_array_fetch_string(&_84, &right, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2274);
	zephir_array_update_string(&_83, SL("type"), &_84, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_83, SL("source"), &intermediateTable, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_85);
	zephir_create_array(&_85, 1, 0);
	ZEPHIR_INIT_VAR(&_86);
	zephir_create_array(&_86, 2, 0);
	add_assoc_stringl_ex(&_86, SL("type"), SL("literal"));
	ZEPHIR_INIT_VAR(&_87);
	zephir_fast_join_str(&_87, SL(" AND "), &intermediateConditions);
	zephir_array_update_string(&_86, SL("value"), &_87, PH_COPY | PH_SEPARATE);
	zephir_array_fast_append(&_85, &_86);
	zephir_array_update_string(&_83, SL("conditions"), &_85, PH_COPY | PH_SEPARATE);
	zephir_array_fast_append(return_value, &_83);
	ZEPHIR_INIT_NVAR(&_83);
	zephir_create_array(&_83, 3, 0);
	ZEPHIR_OBS_NVAR(&_84);
	zephir_array_fetch_string(&_84, &right, SL("type"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2284);
	zephir_array_update_string(&_83, SL("type"), &_84, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_84);
	zephir_array_fetch_string(&_84, &right, SL("table"), PH_NOISY, "phalcon/Mvc/Model/Query/Builder.zep", 2285);
	zephir_array_update_string(&_83, SL("source"), &_84, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_85);
	zephir_create_array(&_85, 1, 0);
	ZEPHIR_INIT_NVAR(&_86);
	zephir_create_array(&_86, 2, 0);
	add_assoc_stringl_ex(&_86, SL("type"), SL("literal"));
	ZEPHIR_INIT_NVAR(&_87);
	zephir_fast_join_str(&_87, SL(" AND "), &conditions);
	zephir_array_update_string(&_86, SL("value"), &_87, PH_COPY | PH_SEPARATE);
	zephir_array_fast_append(&_85, &_86);
	zephir_array_update_string(&_83, SL("conditions"), &_85, PH_COPY | PH_SEPARATE);
	zephir_array_fast_append(return_value, &_83);
	RETURN_MM();
}

/**
 * Appends a BETWEEN condition
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, conditionBetween)
{
	zval _7;
	zval _4;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval clause_zv, operator_zv, expr_zv, *minimum, minimum_sub, *maximum, maximum_sub, hiddenParam, nextHiddenParam, minimumKey, maximumKey, operatorMethod, _5, _6, _1$$3, _2$$3, _3$$3;
	zend_string *clause = NULL, *operator = NULL, *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&clause_zv);
	ZVAL_UNDEF(&operator_zv);
	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&minimum_sub);
	ZVAL_UNDEF(&maximum_sub);
	ZVAL_UNDEF(&hiddenParam);
	ZVAL_UNDEF(&nextHiddenParam);
	ZVAL_UNDEF(&minimumKey);
	ZVAL_UNDEF(&maximumKey);
	ZVAL_UNDEF(&operatorMethod);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("hiddenParamNumber", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(clause)
		Z_PARAM_STR(operator)
		Z_PARAM_STR(expr)
		Z_PARAM_ZVAL(minimum)
		Z_PARAM_ZVAL(maximum)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	minimum = ZEND_CALL_ARG(execute_data, 4);
	maximum = ZEND_CALL_ARG(execute_data, 5);
	zephir_memory_observe(&clause_zv);
	ZVAL_STR_COPY(&clause_zv, clause);
	zephir_memory_observe(&operator_zv);
	ZVAL_STR_COPY(&operator_zv, operator);
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "and");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "or");
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Operator % is not available.");
		ZEPHIR_CALL_FUNCTION(&_3$$3, "sprintf", NULL, 73, &_2$$3, &operator_zv);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model/Query/Builder.zep", 2309);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_VV(&_4, &operator_zv, &clause_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&operatorMethod, &_4);
	zephir_memory_observe(&hiddenParam);
	zephir_read_property_cached(&hiddenParam, this_ptr, _zephir_prop_0, 796, PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_LONG(&_5, 1);
	ZEPHIR_INIT_VAR(&nextHiddenParam);
	zephir_add_function(&nextHiddenParam, &hiddenParam, &_5);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&minimumKey);
	ZEPHIR_CONCAT_SV(&minimumKey, "AP", &hiddenParam);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&maximumKey);
	ZEPHIR_CONCAT_SV(&maximumKey, "AP", &nextHiddenParam);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_VSVSVS(&_6, &expr_zv, " BETWEEN :", &minimumKey, ": AND :", &maximumKey, ":");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_7);
	zephir_create_array(&_7, 2, 0);
	zephir_array_update_zval(&_7, &minimumKey, minimum, PH_COPY);
	zephir_array_update_zval(&_7, &maximumKey, maximum, PH_COPY);
	ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &operatorMethod, NULL, 0, &_6, &_7);
	zephir_check_call_status();
	SEPARATE_ZVAL(&nextHiddenParam);
	zephir_increment(&nextHiddenParam);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 796, &nextHiddenParam);
	RETURN_THIS();
}

/**
 * Appends an IN condition
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, conditionIn)
{
	zval _4, _5$$4, _9$$5, _13$$6;
	zend_bool _0, _11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, hiddenParam = 0;
	zval values;
	zval clause_zv, operator_zv, expr_zv, *values_param = NULL, key, queryKey, value, bindKeys, bindParams, operatorMethod, _6, *_7, _10, _14, _15, _16, _1$$3, _2$$3, _3$$3, _8$$5, _12$$6;
	zend_string *clause = NULL, *operator = NULL, *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&clause_zv);
	ZVAL_UNDEF(&operator_zv);
	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&queryKey);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&bindKeys);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&operatorMethod);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_13$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("hiddenParamNumber", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_STR(clause)
		Z_PARAM_STR(operator)
		Z_PARAM_STR(expr)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 4);
	zephir_memory_observe(&clause_zv);
	ZVAL_STR_COPY(&clause_zv, clause);
	zephir_memory_observe(&operator_zv);
	ZVAL_STR_COPY(&operator_zv, operator);
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "and");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "or");
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Operator % is not available.");
		ZEPHIR_CALL_FUNCTION(&_3$$3, "sprintf", NULL, 73, &_2$$3, &operator_zv);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model/Query/Builder.zep", 2357);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_VV(&_4, &operator_zv, &clause_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&operatorMethod, &_4);
	if (!(zephir_fast_count_int(&values))) {
		ZEPHIR_INIT_VAR(&_5$$4);
		ZEPHIR_CONCAT_VSV(&_5$$4, &expr_zv, " != ", &expr_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &operatorMethod, NULL, 0, &_5$$4);
		zephir_check_call_status();
		RETURN_THIS();
	}
	zephir_memory_observe(&_6);
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_0, 796, PH_NOISY_CC);
	hiddenParam = zephir_get_intval(&_6);
	ZEPHIR_INIT_VAR(&bindParams);
	array_init(&bindParams);
	ZEPHIR_INIT_VAR(&bindKeys);
	array_init(&bindKeys);
	zephir_is_iterable(&values, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2388);
	if (Z_TYPE_P(&values) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&values), _7)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _7);
			ZEPHIR_INIT_NVAR(&_8$$5);
			ZVAL_LONG(&_8$$5, hiddenParam);
			ZEPHIR_INIT_NVAR(&_9$$5);
			ZEPHIR_CONCAT_SV(&_9$$5, "AP", &_8$$5);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CPY_WRT(&key, &_9$$5);
			ZEPHIR_INIT_NVAR(&queryKey);
			ZEPHIR_CONCAT_SVS(&queryKey, ":", &key, ":");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&bindKeys, &queryKey, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2379);
			zephir_array_update_zval(&bindParams, &key, &value, PH_COPY | PH_SEPARATE);
			hiddenParam++;
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &values, "rewind", NULL, 0);
		zephir_check_call_status();
		_11 = 1;
		while (1) {
			if (_11) {
				_11 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &values, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_10, &values, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&value, &values, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_12$$6);
				ZVAL_LONG(&_12$$6, hiddenParam);
				ZEPHIR_INIT_NVAR(&_13$$6);
				ZEPHIR_CONCAT_SV(&_13$$6, "AP", &_12$$6);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CPY_WRT(&key, &_13$$6);
				ZEPHIR_INIT_NVAR(&queryKey);
				ZEPHIR_CONCAT_SVS(&queryKey, ":", &key, ":");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&bindKeys, &queryKey, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2379);
				zephir_array_update_zval(&bindParams, &key, &value, PH_COPY | PH_SEPARATE);
				hiddenParam++;
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_VAR(&_14);
	zephir_fast_join_str(&_14, SL(", "), &bindKeys);
	ZEPHIR_INIT_VAR(&_15);
	ZEPHIR_CONCAT_VSVS(&_15, &expr_zv, " IN (", &_14, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &operatorMethod, NULL, 0, &_15, &bindParams);
	zephir_check_call_status();
	ZVAL_UNDEF(&_16);
	ZVAL_LONG(&_16, hiddenParam);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 796, &_16);
	RETURN_THIS();
}

/**
 * Appends a NOT BETWEEN condition
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, conditionNotBetween)
{
	zval _7;
	zval _4;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval clause_zv, operator_zv, expr_zv, *minimum, minimum_sub, *maximum, maximum_sub, hiddenParam, nextHiddenParam, minimumKey, maximumKey, operatorMethod, _5, _6, _1$$3, _2$$3, _3$$3;
	zend_string *clause = NULL, *operator = NULL, *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&clause_zv);
	ZVAL_UNDEF(&operator_zv);
	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&minimum_sub);
	ZVAL_UNDEF(&maximum_sub);
	ZVAL_UNDEF(&hiddenParam);
	ZVAL_UNDEF(&nextHiddenParam);
	ZVAL_UNDEF(&minimumKey);
	ZVAL_UNDEF(&maximumKey);
	ZVAL_UNDEF(&operatorMethod);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("hiddenParamNumber", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(clause)
		Z_PARAM_STR(operator)
		Z_PARAM_STR(expr)
		Z_PARAM_ZVAL(minimum)
		Z_PARAM_ZVAL(maximum)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	minimum = ZEND_CALL_ARG(execute_data, 4);
	maximum = ZEND_CALL_ARG(execute_data, 5);
	zephir_memory_observe(&clause_zv);
	ZVAL_STR_COPY(&clause_zv, clause);
	zephir_memory_observe(&operator_zv);
	ZVAL_STR_COPY(&operator_zv, operator);
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "and");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "or");
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Operator % is not available.");
		ZEPHIR_CALL_FUNCTION(&_3$$3, "sprintf", NULL, 73, &_2$$3, &operator_zv);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model/Query/Builder.zep", 2411);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_VV(&_4, &operator_zv, &clause_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&operatorMethod, &_4);
	zephir_memory_observe(&hiddenParam);
	zephir_read_property_cached(&hiddenParam, this_ptr, _zephir_prop_0, 796, PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_LONG(&_5, 1);
	ZEPHIR_INIT_VAR(&nextHiddenParam);
	zephir_add_function(&nextHiddenParam, &hiddenParam, &_5);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&minimumKey);
	ZEPHIR_CONCAT_SV(&minimumKey, "AP", &hiddenParam);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&maximumKey);
	ZEPHIR_CONCAT_SV(&maximumKey, "AP", &nextHiddenParam);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_VSVSVS(&_6, &expr_zv, " NOT BETWEEN :", &minimumKey, ": AND :", &maximumKey, ":");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_7);
	zephir_create_array(&_7, 2, 0);
	zephir_array_update_zval(&_7, &minimumKey, minimum, PH_COPY);
	zephir_array_update_zval(&_7, &maximumKey, maximum, PH_COPY);
	ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &operatorMethod, NULL, 0, &_6, &_7);
	zephir_check_call_status();
	SEPARATE_ZVAL(&nextHiddenParam);
	zephir_increment(&nextHiddenParam);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 796, &nextHiddenParam);
	RETURN_THIS();
}

/**
 * Appends a NOT IN condition
 */
PHP_METHOD(Phalcon_Mvc_Model_Query_Builder, conditionNotIn)
{
	zval _4, _5$$4, _9$$5, _13$$6;
	zend_bool _0, _11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, hiddenParam = 0;
	zval values;
	zval clause_zv, operator_zv, expr_zv, *values_param = NULL, key, queryKey, value, bindKeys, bindParams, operatorMethod, _6, *_7, _10, _14, _15, _16, _1$$3, _2$$3, _3$$3, _8$$5, _12$$6;
	zend_string *clause = NULL, *operator = NULL, *expr = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&clause_zv);
	ZVAL_UNDEF(&operator_zv);
	ZVAL_UNDEF(&expr_zv);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&queryKey);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&bindKeys);
	ZVAL_UNDEF(&bindParams);
	ZVAL_UNDEF(&operatorMethod);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_13$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("hiddenParamNumber", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_STR(clause)
		Z_PARAM_STR(operator)
		Z_PARAM_STR(expr)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	values_param = ZEND_CALL_ARG(execute_data, 4);
	zephir_memory_observe(&clause_zv);
	ZVAL_STR_COPY(&clause_zv, clause);
	zephir_memory_observe(&operator_zv);
	ZVAL_STR_COPY(&operator_zv, operator);
	zephir_memory_observe(&expr_zv);
	ZVAL_STR_COPY(&expr_zv, expr);
	ZEPHIR_OBS_COPY_OR_DUP(&values, values_param);
	_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "and");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING_IDENTICAL(&operator_zv, "or");
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Operator % is not available.");
		ZEPHIR_CALL_FUNCTION(&_3$$3, "sprintf", NULL, 73, &_2$$3, &operator_zv);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/Model/Query/Builder.zep", 2458);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_VV(&_4, &operator_zv, &clause_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&operatorMethod, &_4);
	if (!(zephir_fast_count_int(&values))) {
		ZEPHIR_INIT_VAR(&_5$$4);
		ZEPHIR_CONCAT_VSV(&_5$$4, &expr_zv, " != ", &expr_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &operatorMethod, NULL, 0, &_5$$4);
		zephir_check_call_status();
		RETURN_THIS();
	}
	zephir_memory_observe(&_6);
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_0, 796, PH_NOISY_CC);
	hiddenParam = zephir_get_intval(&_6);
	ZEPHIR_INIT_VAR(&bindParams);
	array_init(&bindParams);
	ZEPHIR_INIT_VAR(&bindKeys);
	array_init(&bindKeys);
	zephir_is_iterable(&values, 0, "phalcon/Mvc/Model/Query/Builder.zep", 2489);
	if (Z_TYPE_P(&values) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&values), _7)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _7);
			ZEPHIR_INIT_NVAR(&_8$$5);
			ZVAL_LONG(&_8$$5, hiddenParam);
			ZEPHIR_INIT_NVAR(&_9$$5);
			ZEPHIR_CONCAT_SV(&_9$$5, "AP", &_8$$5);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CPY_WRT(&key, &_9$$5);
			ZEPHIR_INIT_NVAR(&queryKey);
			ZEPHIR_CONCAT_SVS(&queryKey, ":", &key, ":");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&bindKeys, &queryKey, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2480);
			zephir_array_update_zval(&bindParams, &key, &value, PH_COPY | PH_SEPARATE);
			hiddenParam++;
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &values, "rewind", NULL, 0);
		zephir_check_call_status();
		_11 = 1;
		while (1) {
			if (_11) {
				_11 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &values, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_10, &values, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&value, &values, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_12$$6);
				ZVAL_LONG(&_12$$6, hiddenParam);
				ZEPHIR_INIT_NVAR(&_13$$6);
				ZEPHIR_CONCAT_SV(&_13$$6, "AP", &_12$$6);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CPY_WRT(&key, &_13$$6);
				ZEPHIR_INIT_NVAR(&queryKey);
				ZEPHIR_CONCAT_SVS(&queryKey, ":", &key, ":");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&bindKeys, &queryKey, PH_SEPARATE, "phalcon/Mvc/Model/Query/Builder.zep", 2480);
				zephir_array_update_zval(&bindParams, &key, &value, PH_COPY | PH_SEPARATE);
				hiddenParam++;
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_VAR(&_14);
	zephir_fast_join_str(&_14, SL(", "), &bindKeys);
	ZEPHIR_INIT_VAR(&_15);
	ZEPHIR_CONCAT_VSVS(&_15, &expr_zv, " NOT IN (", &_14, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, &operatorMethod, NULL, 0, &_15, &bindParams);
	zephir_check_call_status();
	ZVAL_UNDEF(&_16);
	ZVAL_LONG(&_16, hiddenParam);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 796, &_16);
	RETURN_THIS();
}

zend_object *zephir_init_properties_Phalcon_Mvc_Model_Query_Builder(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _1$$3, _3$$4, _5$$5, _7$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("joins"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("joins"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("group"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("group"), &_3$$4);
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
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

