
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/fcall.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Paginator\Adapter\Model
 *
 * This adapter allows to paginate data using a Phalcon\Mvc\Model resultset as a
 * base.
 *
 * ```php
 * use Phalcon\Paginator\Adapter\Model;
 *
 * $paginator = new Model(
 *     [
 *         "model" => Robots::class,
 *         "limit" => 25,
 *         "page"  => $currentPage,
 *     ]
 * );
 *
 *
 * $paginator = new Model(
 *     [
 *         "model" => Robots::class,
 *         "parameters" => [
 *              "columns" => "id, name"
 *         ],
 *         "limit" => 12,
 *         "page"  => $currentPage,
 *     ]
 * );
 *
 *
 * $paginator = new Model(
 *     [
 *         "model" => Robots::class,
 *         "parameters" => [
 *              "type = :type:",
 *              "bind" => [
 *                  "type" => "mechanical"
 *              ],
 *              "order" => "name"
 *         ],
 *         "limit" => 16,
 *         "page"  => $currentPage,
 *     ]
 * );
 *
 * $paginator = new Model(
 *     [
 *         "model" => Robots::class,
 *         "parameters" => "(id % 2) = 0",
 *         "limit" => 8,
 *         "page"  => $currentPage,
 *     ]
 * );
 *
 *
 * $paginator = new Model(
 *     [
 *         "model" => Robots::class,
 *         "parameters" => [ "(id % 2) = 0" ],
 *         "limit" => 8,
 *         "page"  => $currentPage,
 *     ]
 * );
 *
 * $paginate = $paginator->paginate();
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Paginator_Adapter_Model)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Paginator\\Adapter, Model, phalcon, paginator_adapter_model, phalcon_paginator_adapter_abstractadapter_ce, phalcon_paginator_adapter_model_method_entry, 0);

	return SUCCESS;
}

/**
 * Returns a slice of the resultset to show in the pagination
 */
PHP_METHOD(Phalcon_Paginator_Adapter_Model, paginate)
{
	zend_long _9;
	zval _6, _19, _5$$4, _16$$10;
	zval config, modelClass, parameters, rowCountResult, pageItems, _0, _1, _2, _3, _7, _4$$4, _8$$6, _10$$8, _11$$8, _12$$8, _13$$9, _14$$10, _15$$10, _17$$10, _18$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, pageNumber = 0, limit = 0, rowcount = 0, next = 0, totalPages = 0, previous = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&modelClass);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&rowCountResult);
	ZVAL_UNDEF(&pageItems);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_16$$10);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("limitRows", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("config", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("page", 4, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&pageItems);
	array_init(&pageItems);
	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 955, PH_NOISY_CC);
	limit = zephir_get_intval(&_0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 956, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&config, &_1);
	zephir_memory_observe(&_2);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_2, 957, PH_NOISY_CC);
	pageNumber = zephir_get_intval(&_2);
	zephir_memory_observe(&_3);
	zephir_array_fetch_string(&_3, &config, SL("model"), PH_NOISY, "phalcon/Paginator/Adapter/Model.zep", 100);
	ZEPHIR_CPY_WRT(&modelClass, &_3);
	zephir_memory_observe(&parameters);
	if (!(zephir_array_isset_string_fetch(&parameters, &config, SL("parameters"), 0))) {
		ZEPHIR_INIT_NVAR(&parameters);
		array_init(&parameters);
	}
	if (UNEXPECTED(Z_TYPE_P(&parameters) != IS_ARRAY)) {
		ZEPHIR_CPY_WRT(&_4$$4, &parameters);
		zephir_get_arrval(&_5$$4, &_4$$4);
		ZEPHIR_CPY_WRT(&parameters, &_5$$4);
	}
	if (pageNumber <= 0) {
		pageNumber = 1;
	}
	ZEPHIR_INIT_VAR(&_6);
	zephir_create_array(&_6, 2, 0);
	zephir_array_fast_append(&_6, &modelClass);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "count");
	zephir_array_fast_append(&_6, &_7);
	ZEPHIR_CALL_FUNCTION(&rowCountResult, "call_user_func", NULL, 194, &_6, &parameters);
	zephir_check_call_status();
	if (Z_TYPE_P(&rowCountResult) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(&_8$$6, &rowCountResult, "count", NULL, 0);
		zephir_check_call_status();
		rowcount = zephir_get_intval(&_8$$6);
	} else {
		rowcount = zephir_get_intval(&rowCountResult);
	}
	_9 = zephir_safe_mod_long_long(rowcount, limit);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (_9 != 0) {
		ZEPHIR_INIT_VAR(&_10$$8);
		zephir_div_long_long(&_10$$8, rowcount, limit);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_11$$8);
		ZVAL_LONG(&_11$$8, 1);
		ZEPHIR_INIT_VAR(&_12$$8);
		zephir_add_function(&_12$$8, &_10$$8, &_11$$8);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		totalPages = zephir_get_intval(&_12$$8);
	} else {
		ZEPHIR_INIT_VAR(&_13$$9);
		zephir_div_long_long(&_13$$9, rowcount, limit);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		totalPages = zephir_get_intval(&_13$$9);
	}
	if (rowcount > 0) {
		ZEPHIR_INIT_VAR(&_14$$10);
		ZVAL_LONG(&_14$$10, limit);
		zephir_array_update_string(&parameters, SL("limit"), &_14$$10, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_15$$10);
		ZVAL_LONG(&_15$$10, (limit * ((pageNumber - 1))));
		zephir_array_update_string(&parameters, SL("offset"), &_15$$10, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_16$$10);
		zephir_create_array(&_16$$10, 2, 0);
		zephir_array_fast_append(&_16$$10, &modelClass);
		ZEPHIR_INIT_VAR(&_17$$10);
		ZVAL_STRING(&_17$$10, "find");
		zephir_array_fast_append(&_16$$10, &_17$$10);
		ZEPHIR_CALL_FUNCTION(&_18$$10, "call_user_func", NULL, 194, &_16$$10, &parameters);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&pageItems, &_18$$10);
	}
	next = (pageNumber + 1);
	if (next > totalPages) {
		next = totalPages;
	}
	if (pageNumber > 1) {
		previous = (pageNumber - 1);
	} else {
		previous = 1;
	}
	ZEPHIR_INIT_VAR(&_19);
	zephir_create_array(&_19, 8, 0);
	zephir_array_update_string(&_19, SL("items"), &pageItems, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_LONG(&_7, rowcount);
	zephir_array_update_string(&_19, SL("total_items"), &_7, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_3);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 955, PH_NOISY_CC);
	zephir_array_update_string(&_19, SL("limit"), &_3, PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(&_19, SL("first"), 1);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_LONG(&_7, previous);
	zephir_array_update_string(&_19, SL("previous"), &_7, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_LONG(&_7, pageNumber);
	zephir_array_update_string(&_19, SL("current"), &_7, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_LONG(&_7, next);
	zephir_array_update_string(&_19, SL("next"), &_7, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_LONG(&_7, totalPages);
	zephir_array_update_string(&_19, SL("last"), &_7, PH_COPY | PH_SEPARATE);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getRepository", NULL, 0, &_19);
	zephir_check_call_status();
	RETURN_MM();
}

