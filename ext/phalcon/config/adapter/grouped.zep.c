
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
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
 * Reads multiple files (or arrays) and merges them all together.
 *
 * See `Phalcon\Config\ConfigFactory::load` To load Config Adapter class using 'adapter' option.
 *
 * ```php
 * use Phalcon\Config\Adapter\Grouped;
 *
 * $config = new Grouped(
 *     [
 *         "path/to/config.php",
 *         "path/to/config.dist.php",
 *     ]
 * );
 * ```
 *
 * ```php
 * use Phalcon\Config\Adapter\Grouped;
 *
 * $config = new Grouped(
 *     [
 *         "path/to/config.json",
 *         "path/to/config.dist.json",
 *     ],
 *     "json"
 * );
 * ```
 *
 * ```php
 * use Phalcon\Config\Adapter\Grouped;
 *
 * $config = new Grouped(
 *     [
 *         [
 *             "filePath" => "path/to/config.php",
 *             "adapter"  => "php",
 *         ],
 *         [
 *             "filePath" => "path/to/config.json",
 *             "adapter"  => "json",
 *         ],
 *         [
 *             "adapter"  => "array",
 *             "config"   => [
 *                 "property" => "value",
 *             ],
 *         ],
 *     ],
 * );
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Config_Adapter_Grouped)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Config\\Adapter, Grouped, phalcon, config_adapter_grouped, phalcon_config_config_ce, phalcon_config_adapter_grouped_method_entry, 0);

	return SUCCESS;
}

/**
 * Phalcon\Config\Adapter\Grouped constructor
 */
PHP_METHOD(Phalcon_Config_Adapter_Grouped, __construct)
{
	zval _13$$9, _29$$17;
	zend_bool _20, _2$$3, _21$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_6 = NULL, *_8 = NULL, *_14 = NULL, *_16 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *defaultAdapter = NULL;
	zval *arrayConfig_param = NULL, defaultAdapter_zv, configArray, configInstance, configName, _0, *_1, _19, _10$$3, _11$$3, _4$$5, _9$$5, _5$$6, _7$$6, _12$$9, _15$$8, _17$$10, _18$$10, _26$$11, _27$$11, _22$$13, _25$$13, _23$$14, _24$$14, _28$$17, _30$$16, _31$$18, _32$$18;
	zval arrayConfig;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arrayConfig);
	ZVAL_UNDEF(&defaultAdapter_zv);
	ZVAL_UNDEF(&configArray);
	ZVAL_UNDEF(&configInstance);
	ZVAL_UNDEF(&configName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_26$$11);
	ZVAL_UNDEF(&_27$$11);
	ZVAL_UNDEF(&_22$$13);
	ZVAL_UNDEF(&_25$$13);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_24$$14);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_31$$18);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_29$$17);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("insensitive", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(arrayConfig, arrayConfig_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(defaultAdapter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	arrayConfig_param = ZEND_CALL_ARG(execute_data, 1);
	ZEPHIR_OBS_COPY_OR_DUP(&arrayConfig, arrayConfig_param);
	if (!defaultAdapter) {
		defaultAdapter = zend_string_init(ZEND_STRL("php"), 0);
		zephir_memory_observe(&defaultAdapter_zv);
		ZVAL_STR(&defaultAdapter_zv, defaultAdapter);
	} else {
	zephir_memory_observe(&defaultAdapter_zv);
	ZVAL_STR_COPY(&defaultAdapter_zv, defaultAdapter);
	}
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	ZEPHIR_CALL_PARENT(NULL, phalcon_config_adapter_grouped_ce, getThis(), "__construct", NULL, 0, &_0);
	zephir_check_call_status();
	zephir_is_iterable(&arrayConfig, 0, "phalcon/Config/Adapter/Grouped.zep", 121);
	if (Z_TYPE_P(&arrayConfig) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arrayConfig), _1)
		{
			ZEPHIR_INIT_NVAR(&configName);
			ZVAL_COPY(&configName, _1);
			ZEPHIR_CPY_WRT(&configInstance, &configName);
			_2$$3 = Z_TYPE_P(&configName) == IS_OBJECT;
			if (_2$$3) {
				_2$$3 = zephir_instance_of_ev(&configName, phalcon_config_configinterface_ce);
			}
			if (_2$$3) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "merge", &_3, 0, &configInstance);
				zephir_check_call_status();
				continue;
			} else if (Z_TYPE_P(&configName) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZVAL_STRING(&_4$$5, "");
				if (ZEPHIR_IS_IDENTICAL(&_4$$5, &defaultAdapter_zv)) {
					ZEPHIR_INIT_NVAR(&_5$$6);
					object_init_ex(&_5$$6, phalcon_config_configfactory_ce);
					ZEPHIR_CALL_METHOD(NULL, &_5$$6, "__construct", &_6, 195);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_7$$6, &_5$$6, "load", &_8, 196, &configName);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "merge", &_3, 0, &_7$$6);
					zephir_check_call_status();
					continue;
				}
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_create_array(&_9$$5, 2, 0);
				zephir_array_update_string(&_9$$5, SL("filePath"), &configName, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_9$$5, SL("adapter"), &defaultAdapter_zv, PH_COPY | PH_SEPARATE);
				ZEPHIR_CPY_WRT(&configInstance, &_9$$5);
			} else if (!(zephir_array_isset_value_string(&configInstance, SL("adapter")))) {
				zephir_array_update_string(&configInstance, SL("adapter"), &defaultAdapter_zv, PH_COPY | PH_SEPARATE);
			}
			ZEPHIR_OBS_NVAR(&_10$$3);
			zephir_array_fetch_string(&_10$$3, &configInstance, SL("adapter"), PH_NOISY, "phalcon/Config/Adapter/Grouped.zep", 105);
			ZEPHIR_INIT_NVAR(&_11$$3);
			ZVAL_STRING(&_11$$3, "array");
			if (ZEPHIR_IS_IDENTICAL(&_11$$3, &_10$$3)) {
				if (!(zephir_array_isset_value_string(&configInstance, SL("config")))) {
					ZEPHIR_INIT_NVAR(&_12$$9);
					object_init_ex(&_12$$9, phalcon_config_exception_ce);
					ZEPHIR_INIT_NVAR(&_13$$9);
					ZEPHIR_CONCAT_SS(&_13$$9, "To use 'array' adapter you have to specify ", "the 'config' as an array.");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_12$$9, "__construct", &_14, 32, &_13$$9);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_12$$9, "phalcon/Config/Adapter/Grouped.zep", 110);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_OBS_NVAR(&configArray);
				zephir_array_fetch_string(&configArray, &configInstance, SL("config"), PH_NOISY, "phalcon/Config/Adapter/Grouped.zep", 113);
				ZEPHIR_INIT_NVAR(&configInstance);
				object_init_ex(&configInstance, phalcon_config_config_ce);
				zephir_read_property_cached(&_15$$8, this_ptr, _zephir_prop_0, 339, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_METHOD(NULL, &configInstance, "__construct", &_16, 22, &configArray, &_15$$8);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&_17$$10);
				object_init_ex(&_17$$10, phalcon_config_configfactory_ce);
				ZEPHIR_CALL_METHOD(NULL, &_17$$10, "__construct", &_6, 195);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_18$$10, &_17$$10, "load", &_8, 196, &configInstance);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&configInstance, &_18$$10);
			}
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "merge", &_3, 0, &configInstance);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &arrayConfig, "rewind", NULL, 0);
		zephir_check_call_status();
		_20 = 1;
		while (1) {
			if (_20) {
				_20 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &arrayConfig, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_19, &arrayConfig, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_19)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&configName, &arrayConfig, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CPY_WRT(&configInstance, &configName);
				_21$$11 = Z_TYPE_P(&configName) == IS_OBJECT;
				if (_21$$11) {
					_21$$11 = zephir_instance_of_ev(&configName, phalcon_config_configinterface_ce);
				}
				if (_21$$11) {
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "merge", &_3, 0, &configInstance);
					zephir_check_call_status();
					continue;
				} else if (Z_TYPE_P(&configName) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_22$$13);
					ZVAL_STRING(&_22$$13, "");
					if (ZEPHIR_IS_IDENTICAL(&_22$$13, &defaultAdapter_zv)) {
						ZEPHIR_INIT_NVAR(&_23$$14);
						object_init_ex(&_23$$14, phalcon_config_configfactory_ce);
						ZEPHIR_CALL_METHOD(NULL, &_23$$14, "__construct", &_6, 195);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_24$$14, &_23$$14, "load", &_8, 196, &configName);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "merge", &_3, 0, &_24$$14);
						zephir_check_call_status();
						continue;
					}
					ZEPHIR_INIT_NVAR(&_25$$13);
					zephir_create_array(&_25$$13, 2, 0);
					zephir_array_update_string(&_25$$13, SL("filePath"), &configName, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_25$$13, SL("adapter"), &defaultAdapter_zv, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&configInstance, &_25$$13);
				} else if (!(zephir_array_isset_value_string(&configInstance, SL("adapter")))) {
					zephir_array_update_string(&configInstance, SL("adapter"), &defaultAdapter_zv, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(&_26$$11);
				zephir_array_fetch_string(&_26$$11, &configInstance, SL("adapter"), PH_NOISY, "phalcon/Config/Adapter/Grouped.zep", 105);
				ZEPHIR_INIT_NVAR(&_27$$11);
				ZVAL_STRING(&_27$$11, "array");
				if (ZEPHIR_IS_IDENTICAL(&_27$$11, &_26$$11)) {
					if (!(zephir_array_isset_value_string(&configInstance, SL("config")))) {
						ZEPHIR_INIT_NVAR(&_28$$17);
						object_init_ex(&_28$$17, phalcon_config_exception_ce);
						ZEPHIR_INIT_NVAR(&_29$$17);
						ZEPHIR_CONCAT_SS(&_29$$17, "To use 'array' adapter you have to specify ", "the 'config' as an array.");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_28$$17, "__construct", &_14, 32, &_29$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_28$$17, "phalcon/Config/Adapter/Grouped.zep", 110);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&configArray);
					zephir_array_fetch_string(&configArray, &configInstance, SL("config"), PH_NOISY, "phalcon/Config/Adapter/Grouped.zep", 113);
					ZEPHIR_INIT_NVAR(&configInstance);
					object_init_ex(&configInstance, phalcon_config_config_ce);
					zephir_read_property_cached(&_30$$16, this_ptr, _zephir_prop_0, 339, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CALL_METHOD(NULL, &configInstance, "__construct", &_16, 22, &configArray, &_30$$16);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(&_31$$18);
					object_init_ex(&_31$$18, phalcon_config_configfactory_ce);
					ZEPHIR_CALL_METHOD(NULL, &_31$$18, "__construct", &_6, 195);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_32$$18, &_31$$18, "load", &_8, 196, &configInstance);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&configInstance, &_32$$18);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "merge", &_3, 0, &configInstance);
				zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&configName);
	ZEPHIR_MM_RESTORE();
}

