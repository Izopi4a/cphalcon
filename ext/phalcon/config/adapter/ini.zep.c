
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
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/object.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Reads ini files and converts them to Phalcon\Config\Config objects.
 *
 * Given the next configuration file:
 *
 *```ini
 * [database]
 * adapter = Mysql
 * host = localhost
 * username = scott
 * password = cheetah
 * dbname = test_db
 *
 * [phalcon]
 * controllersDir = "../app/controllers/"
 * modelsDir = "../app/models/"
 * viewsDir = "../app/views/"
 * ```
 *
 * You can read it as follows:
 *
 *```php
 * use Phalcon\Config\Adapter\Ini;
 *
 * $config = new Ini("path/config.ini");
 *
 * echo $config->phalcon->controllersDir;
 * echo $config->database->username;
 *```
 *
 * PHP constants may also be parsed in the ini file, so if you define a constant
 * as an ini value before calling the constructor, the constant's value will be
 * integrated into the results. To use it this way you must specify the optional
 * second parameter as `INI_SCANNER_NORMAL` when calling the constructor:
 *
 * ```php
 * $config = new \Phalcon\Config\Adapter\Ini(
 *     "path/config-with-constants.ini",
 *     INI_SCANNER_NORMAL
 * );
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Config_Adapter_Ini)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Config\\Adapter, Ini, phalcon, config_adapter_ini, phalcon_config_config_ce, phalcon_config_adapter_ini_method_entry, 0);

	return SUCCESS;
}

/**
 * Ini constructor.
 *
 * @param string $filePath
 * @param int    $mode
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Config_Adapter_Ini, __construct)
{
	zval _16$$6, _21$$7, _34$$11, _38$$12;
	zend_bool _27, _19$$5, _36$$10;
	zend_ulong _8, _13$$5, _31$$10;
	zval config;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_17 = NULL, *_25 = NULL;
	zend_long mode, ZEPHIR_LAST_CALL_STATUS;
	zval filePath_zv, *mode_param = NULL, directives, iniConfig, lastValue, path, section, sections, _0, _1, *_5, _6, *_7, _26, _2$$3, _3$$3, _4$$3, *_10$$5, _11$$5, *_12$$5, _18$$5, _15$$6, _20$$7, _22$$8, _23$$8, _24$$4, *_28$$10, _29$$10, *_30$$10, _35$$10, _33$$11, _37$$12, _39$$13, _40$$13, _41$$9;
	zend_string *filePath = NULL, *_9, *_14$$5, *_32$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&filePath_zv);
	ZVAL_UNDEF(&directives);
	ZVAL_UNDEF(&iniConfig);
	ZVAL_UNDEF(&lastValue);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&section);
	ZVAL_UNDEF(&sections);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$4);
	ZVAL_UNDEF(&_29$$10);
	ZVAL_UNDEF(&_35$$10);
	ZVAL_UNDEF(&_33$$11);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_39$$13);
	ZVAL_UNDEF(&_40$$13);
	ZVAL_UNDEF(&_41$$9);
	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_34$$11);
	ZVAL_UNDEF(&_38$$12);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(filePath)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(mode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		mode_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&filePath_zv);
	ZVAL_STR_COPY(&filePath_zv, filePath);
	if (!mode_param) {
		mode = 1;
	} else {
		}
	ZVAL_BOOL(&_0, 1);
	ZVAL_LONG(&_1, mode);
	ZEPHIR_CALL_METHOD(&iniConfig, this_ptr, "phpParseIniFile", NULL, 0, &filePath_zv, &_0, &_1);
	zephir_check_call_status();
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&iniConfig))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, phalcon_config_exception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_basename(&_3$$3, &filePath_zv);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SVS(&_4$$3, "Configuration file ", &_3$$3, " cannot be loaded");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 32, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Config/Adapter/Ini.zep", 79);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&config);
	array_init(&config);
	if (Z_TYPE_P(&iniConfig) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_6);
		zephir_string_to_char_array(&_6, &iniConfig);
		_5 = &_6;
	} else {
		_5 = &iniConfig;
	}
	zephir_is_iterable(_5, 0, "phalcon/Config/Adapter/Ini.zep", 108);
	if (Z_TYPE_P(_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_5), _8, _9, _7)
		{
			ZEPHIR_INIT_NVAR(&section);
			if (_9 != NULL) { 
				ZVAL_STR_COPY(&section, _9);
			} else {
				ZVAL_LONG(&section, _8);
			}
			ZEPHIR_INIT_NVAR(&directives);
			ZVAL_COPY(&directives, _7);
			if (Z_TYPE_P(&directives) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(&sections);
				array_init(&sections);
				if (Z_TYPE_P(&directives) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_11$$5);
					zephir_string_to_char_array(&_11$$5, &directives);
					_10$$5 = &_11$$5;
				} else {
					_10$$5 = &directives;
				}
				zephir_is_iterable(_10$$5, 0, "phalcon/Config/Adapter/Ini.zep", 95);
				if (Z_TYPE_P(_10$$5) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_10$$5), _13$$5, _14$$5, _12$$5)
					{
						ZEPHIR_INIT_NVAR(&path);
						if (_14$$5 != NULL) { 
							ZVAL_STR_COPY(&path, _14$$5);
						} else {
							ZVAL_LONG(&path, _13$$5);
						}
						ZEPHIR_INIT_NVAR(&lastValue);
						ZVAL_COPY(&lastValue, _12$$5);
						zephir_cast_to_string(&_16$$6, &path);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&_15$$6, this_ptr, "parseIniString", &_17, 0, &_16$$6, &lastValue);
						zephir_check_call_status();
						zephir_array_append(&sections, &_15$$6, PH_SEPARATE, "phalcon/Config/Adapter/Ini.zep", 92);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _10$$5, "rewind", NULL, 0);
					zephir_check_call_status();
					_19$$5 = 1;
					while (1) {
						if (_19$$5) {
							_19$$5 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _10$$5, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_18$$5, _10$$5, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_18$$5)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&path, _10$$5, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&lastValue, _10$$5, "current", NULL, 0);
						zephir_check_call_status();
							zephir_cast_to_string(&_21$$7, &path);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(&_20$$7, this_ptr, "parseIniString", &_17, 0, &_21$$7, &lastValue);
							zephir_check_call_status();
							zephir_array_append(&sections, &_20$$7, PH_SEPARATE, "phalcon/Config/Adapter/Ini.zep", 92);
					}
				}
				ZEPHIR_INIT_NVAR(&lastValue);
				ZEPHIR_INIT_NVAR(&path);
				if (zephir_fast_count_int(&sections)) {
					ZEPHIR_INIT_NVAR(&_22$$8);
					ZEPHIR_INIT_NVAR(&_23$$8);
					ZVAL_STRING(&_23$$8, "array_replace_recursive");
					ZEPHIR_CALL_USER_FUNC_ARRAY(&_22$$8, &_23$$8, &sections);
					zephir_check_call_status();
					zephir_array_update_zval(&config, &section, &_22$$8, PH_COPY | PH_SEPARATE);
				}
				continue;
			}
			ZEPHIR_CALL_METHOD(&_24$$4, this_ptr, "cast", &_25, 0, &directives);
			zephir_check_call_status();
			zephir_array_update_zval(&config, &section, &_24$$4, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _5, "rewind", NULL, 0);
		zephir_check_call_status();
		_27 = 1;
		while (1) {
			if (_27) {
				_27 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _5, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_26, _5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_26)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&section, _5, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&directives, _5, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&directives) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&sections);
					array_init(&sections);
					if (Z_TYPE_P(&directives) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_29$$10);
						zephir_string_to_char_array(&_29$$10, &directives);
						_28$$10 = &_29$$10;
					} else {
						_28$$10 = &directives;
					}
					zephir_is_iterable(_28$$10, 0, "phalcon/Config/Adapter/Ini.zep", 95);
					if (Z_TYPE_P(_28$$10) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_28$$10), _31$$10, _32$$10, _30$$10)
						{
							ZEPHIR_INIT_NVAR(&path);
							if (_32$$10 != NULL) { 
								ZVAL_STR_COPY(&path, _32$$10);
							} else {
								ZVAL_LONG(&path, _31$$10);
							}
							ZEPHIR_INIT_NVAR(&lastValue);
							ZVAL_COPY(&lastValue, _30$$10);
							zephir_cast_to_string(&_34$$11, &path);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(&_33$$11, this_ptr, "parseIniString", &_17, 0, &_34$$11, &lastValue);
							zephir_check_call_status();
							zephir_array_append(&sections, &_33$$11, PH_SEPARATE, "phalcon/Config/Adapter/Ini.zep", 92);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _28$$10, "rewind", NULL, 0);
						zephir_check_call_status();
						_36$$10 = 1;
						while (1) {
							if (_36$$10) {
								_36$$10 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _28$$10, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_35$$10, _28$$10, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_35$$10)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&path, _28$$10, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&lastValue, _28$$10, "current", NULL, 0);
							zephir_check_call_status();
								zephir_cast_to_string(&_38$$12, &path);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(&_37$$12, this_ptr, "parseIniString", &_17, 0, &_38$$12, &lastValue);
								zephir_check_call_status();
								zephir_array_append(&sections, &_37$$12, PH_SEPARATE, "phalcon/Config/Adapter/Ini.zep", 92);
						}
					}
					ZEPHIR_INIT_NVAR(&lastValue);
					ZEPHIR_INIT_NVAR(&path);
					if (zephir_fast_count_int(&sections)) {
						ZEPHIR_INIT_NVAR(&_39$$13);
						ZEPHIR_INIT_NVAR(&_40$$13);
						ZVAL_STRING(&_40$$13, "array_replace_recursive");
						ZEPHIR_CALL_USER_FUNC_ARRAY(&_39$$13, &_40$$13, &sections);
						zephir_check_call_status();
						zephir_array_update_zval(&config, &section, &_39$$13, PH_COPY | PH_SEPARATE);
					}
					continue;
				}
				ZEPHIR_CALL_METHOD(&_41$$9, this_ptr, "cast", &_25, 0, &directives);
				zephir_check_call_status();
				zephir_array_update_zval(&config, &section, &_41$$9, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&directives);
	ZEPHIR_INIT_NVAR(&section);
	ZEPHIR_CALL_PARENT(NULL, phalcon_config_adapter_ini_ce, getThis(), "__construct", NULL, 0, &config);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * We have to cast values manually because parse_ini_file() has a poor
 * implementation.
 *
 * @param mixed $ini
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Config_Adapter_Ini, cast)
{
	zend_bool _3;
	zval _0;
	zval castMap;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ini = NULL, ini_sub, __$true, __$false, lowerIni, _1, _2$$5, _4$$6, _5$$6, _6$$6, _7$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ini_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&lowerIni);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&castMap);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(ini)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &ini);
	ZEPHIR_SEPARATE_PARAM(ini);
	if (Z_TYPE_P(ini) == IS_ARRAY) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "castArray", NULL, 0, ini);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_cast_to_string(&_0, ini);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(ini, &_0);
	ZEPHIR_INIT_VAR(&lowerIni);
	zephir_fast_strtolower(&lowerIni, ini);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "null");
	if (ZEPHIR_IS_IDENTICAL(&_1, &lowerIni)) {
		RETURN_MM_NULL();
	}
	ZEPHIR_INIT_VAR(&castMap);
	zephir_create_array(&castMap, 6, 0);
	zephir_array_update_string(&castMap, SL("on"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&castMap, SL("true"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&castMap, SL("yes"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&castMap, SL("off"), &__$false, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&castMap, SL("no"), &__$false, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&castMap, SL("false"), &__$false, PH_COPY | PH_SEPARATE);
	if (1 == zephir_array_isset_value(&castMap, &lowerIni)) {
		zephir_array_fetch(&_2$$5, &castMap, &lowerIni, PH_NOISY | PH_READONLY, "phalcon/Config/Adapter/Ini.zep", 147);
		RETURN_CTOR(&_2$$5);
	}
	_3 = Z_TYPE_P(ini) == IS_STRING;
	if (_3) {
		_3 = zephir_is_numeric(ini);
	}
	if (_3) {
		ZEPHIR_INIT_VAR(&_4$$6);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZVAL_STRING(&_5$$6, "/[.]+/");
		ZEPHIR_INIT_VAR(&_6$$6);
		ZEPHIR_INIT_VAR(&_7$$6);
		ZVAL_STRING(&_7$$6, "/[.]+/");
		zephir_preg_match(&_6$$6, &_7$$6, ini, &_4$$6, 0, 0 , 0 );
		if (zephir_is_true(&_6$$6)) {
			RETURN_MM_DOUBLE(zephir_get_doubleval(ini));
		}
		RETURN_MM_LONG(zephir_get_intval(ini));
	}
	RETVAL_ZVAL(ini, 1, 0);
	RETURN_MM();
}

/**
 * @param array $ini
 *
 * @return array
 */
PHP_METHOD(Phalcon_Config_Adapter_Ini, castArray)
{
	zend_bool _6;
	zend_string *_2;
	zend_ulong _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ini_param = NULL, key, value, *_0, _5, _3$$3, _7$$4;
	zval ini;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ini);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_7$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(ini, ini_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &ini_param);
	zephir_get_arrval(&ini, ini_param);
	zephir_is_iterable(&ini, 1, "phalcon/Config/Adapter/Ini.zep", 175);
	if (Z_TYPE_P(&ini) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&ini), _1, _2, _0)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_2 != NULL) { 
				ZVAL_STR_COPY(&key, _2);
			} else {
				ZVAL_LONG(&key, _1);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _0);
			ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "cast", &_4, 0, &value);
			zephir_check_call_status();
			zephir_array_update_zval(&ini, &key, &_3$$3, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &ini, "rewind", NULL, 0);
		zephir_check_call_status();
		_6 = 1;
		while (1) {
			if (_6) {
				_6 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &ini, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_5, &ini, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &ini, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &ini, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_7$$4, this_ptr, "cast", &_4, 0, &value);
				zephir_check_call_status();
				zephir_array_update_zval(&ini, &key, &_7$$4, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CTOR(&ini);
}

/**
 * Build multidimensional array from string
 *
 * @param string $path
 * @param mixed  $value
 *
 * @return array
 */
PHP_METHOD(Phalcon_Config_Adapter_Ini, parseIniString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, *value, value_sub, castValue, key, position, result, _0, _1, _2, _3, _4;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&castValue);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(path_param)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &path_param, &value);
	zephir_get_strval(&path, path_param);
	ZEPHIR_CALL_METHOD(&castValue, this_ptr, "cast", NULL, 0, value);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, ".");
	ZEPHIR_INIT_VAR(&position);
	zephir_fast_strpos(&position, &path, &_0, 0 );
	if (ZEPHIR_IS_FALSE_IDENTICAL(&position)) {
		zephir_create_array(return_value, 1, 0);
		zephir_array_update_zval(return_value, &path, &castValue, PH_COPY);
		RETURN_MM();
	}
	ZVAL_LONG(&_1, 0);
	ZEPHIR_INIT_VAR(&key);
	zephir_substr(&key, &path, 0 , zephir_get_intval(&position), 0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_LONG(&_2, 1);
	ZEPHIR_INIT_VAR(&_3);
	zephir_add_function(&_3, &position, &_2);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_4);
	zephir_substr(&_4, &path, zephir_get_intval(&_3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	zephir_get_strval(&path, &_4);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&result, this_ptr, "parseIniString", NULL, 200, &path, &castValue);
	zephir_check_call_status();
	zephir_create_array(return_value, 1, 0);
	zephir_array_update_zval(return_value, &key, &result, PH_COPY);
	RETURN_MM();
}

/**
 * @todo to be removed when we get traits
 */
PHP_METHOD(Phalcon_Config_Adapter_Ini, phpParseIniFile)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long scannerMode, ZEPHIR_LAST_CALL_STATUS;
	zend_bool processSections;
	zval filename_zv, *processSections_param = NULL, *scannerMode_param = NULL, _0, _1;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(filename)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(processSections)
		Z_PARAM_LONG(scannerMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		processSections_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		scannerMode_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	if (!processSections_param) {
		processSections = 0;
	} else {
		}
	if (!scannerMode_param) {
		scannerMode = 1;
	} else {
		}
	ZVAL_BOOL(&_0, (processSections ? 1 : 0));
	ZVAL_LONG(&_1, scannerMode);
	ZEPHIR_RETURN_CALL_FUNCTION("parse_ini_file", NULL, 201, &filename_zv, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

