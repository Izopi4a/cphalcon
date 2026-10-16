
#ifdef HAVE_CONFIG_H
#include "../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../php_ext.h"
#include "../../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/require.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/variables.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Every compiled template gets a sidecar "<compiled>.deps.php" listing the
 * files inlined into it (parents, embeds, static includes) with their mtimes,
 * plus a signature of the compiler configuration (runtime registry,
 * autoescape, strict tests). With "stat" on, a compiled template is stale when
 * any of them changed, not only the template itself.
 *
 * The sidecar is a PHP file returning an array, so opcache serves it.
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Dependencies)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt, Dependencies, phalcon, mvc_view_engine_volt_dependencies, phalcon_mvc_view_engine_volt_dependencies_method_entry, 0);

	return SUCCESS;
}

/**
 * @return array|null ["files" => [path => mtime], "signature" => string]
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Dependencies, read)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval compiledPath_zv, file, data, _1, _2;
	zend_string *compiledPath = NULL;

	ZVAL_UNDEF(&compiledPath_zv);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(compiledPath)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&compiledPath_zv);
	ZVAL_STR_COPY(&compiledPath_zv, compiledPath);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_VS(&_0, &compiledPath_zv, ".deps.php");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&file, &_0);
	ZEPHIR_CALL_FUNCTION(&_1, "is_file", NULL, 0, &file);
	zephir_check_call_status();
	if (!(zephir_is_true(&_1))) {
		RETURN_MM_NULL();
	}
	ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(&_2);
	if (zephir_require_zval_ret(&_2, &file) == FAILURE) {
		RETURN_MM_NULL();
	}
	ZEPHIR_CPY_WRT(&data, &_2);
	if (Z_TYPE_P(&data) != IS_ARRAY) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&data);
}

/**
 * Why the compiled template must be rebuilt, or null when it is fresh
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Dependencies, staleReason)
{
	zend_ulong _5;
	zend_bool _0, _1, _13, _10$$6, _15$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval compiledPath_zv, signature_zv, __$true, data, files, file, mtime, storedSignature, *_2, _3, *_4, _12, _8$$6, _11$$6, _14$$8, _16$$8;
	zend_string *compiledPath = NULL, *signature = NULL, *_6;

	ZVAL_UNDEF(&compiledPath_zv);
	ZVAL_UNDEF(&signature_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&files);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&mtime);
	ZVAL_UNDEF(&storedSignature);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_16$$8);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(compiledPath)
		Z_PARAM_STR(signature)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&compiledPath_zv);
	ZVAL_STR_COPY(&compiledPath_zv, compiledPath);
	zephir_memory_observe(&signature_zv);
	ZVAL_STR_COPY(&signature_zv, signature);
	ZEPHIR_CALL_SELF(&data, "read", NULL, 0, &compiledPath_zv);
	zephir_check_call_status();
	if (Z_TYPE_P(&data) == IS_NULL) {
		RETURN_MM_STRING("no dependency data");
	}
	zephir_memory_observe(&storedSignature);
	_0 = !(zephir_array_isset_string_fetch(&storedSignature, &data, SL("signature"), 0));
	if (!(_0)) {
		_0 = !ZEPHIR_IS_IDENTICAL(&storedSignature, &signature_zv);
	}
	if (_0) {
		RETURN_MM_STRING("compiler configuration changed");
	}
	zephir_memory_observe(&files);
	_1 = !(zephir_array_isset_string_fetch(&files, &data, SL("files"), 0));
	if (!(_1)) {
		_1 = Z_TYPE_P(&files) != IS_ARRAY;
	}
	if (_1) {
		RETURN_MM_STRING("no dependency data");
	}
	if (Z_TYPE_P(&files) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &files);
		_2 = &_3;
	} else {
		_2 = &files;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/View/Engine/Volt/Dependencies.zep", 75);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_2), _5, _6, _4)
		{
			ZEPHIR_INIT_NVAR(&file);
			if (_6 != NULL) { 
				ZVAL_STR_COPY(&file, _6);
			} else {
				ZVAL_LONG(&file, _5);
			}
			ZEPHIR_INIT_NVAR(&mtime);
			ZVAL_COPY(&mtime, _4);
			ZEPHIR_CALL_FUNCTION(NULL, "clearstatcache", &_7, 0, &__$true, &file);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(&_8$$6, "is_file", &_9, 0, &file);
			zephir_check_call_status();
			_10$$6 = !zephir_is_true(&_8$$6);
			if (!(_10$$6)) {
				ZEPHIR_INIT_NVAR(&_11$$6);
				zephir_filemtime(&_11$$6, &file);
				_10$$6 = !ZEPHIR_IS_IDENTICAL(&_11$$6, &mtime);
			}
			if (_10$$6) {
				ZEPHIR_CONCAT_SV(return_value, "dependency changed: ", &file);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_MM();
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_13 = 1;
		while (1) {
			if (_13) {
				_13 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_12, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_12)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&file, _2, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&mtime, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(NULL, "clearstatcache", &_7, 0, &__$true, &file);
				zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_14$$8, "is_file", &_9, 0, &file);
				zephir_check_call_status();
				_15$$8 = !zephir_is_true(&_14$$8);
				if (!(_15$$8)) {
					ZEPHIR_INIT_NVAR(&_16$$8);
					zephir_filemtime(&_16$$8, &file);
					_15$$8 = !ZEPHIR_IS_IDENTICAL(&_16$$8, &mtime);
				}
				if (_15$$8) {
					ZEPHIR_CONCAT_SV(return_value, "dependency changed: ", &file);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					RETURN_MM();
				}
		}
	}
	ZEPHIR_INIT_NVAR(&mtime);
	ZEPHIR_INIT_NVAR(&file);
	RETURN_MM_NULL();
}

/**
 * @param array files path => mtime at compile time
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Dependencies, write)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval files, _2;
	zval compiledPath_zv, *files_param = NULL, signature_zv, _1, _3, _4, _5;
	zend_string *compiledPath = NULL, *signature = NULL;

	ZVAL_UNDEF(&compiledPath_zv);
	ZVAL_UNDEF(&signature_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&files);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(compiledPath)
		ZEPHIR_Z_PARAM_ARRAY(files, files_param)
		Z_PARAM_STR(signature)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	files_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&compiledPath_zv);
	ZVAL_STR_COPY(&compiledPath_zv, compiledPath);
	zephir_get_arrval(&files, files_param);
	zephir_memory_observe(&signature_zv);
	ZVAL_STR_COPY(&signature_zv, signature);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_VS(&_0, &compiledPath_zv, ".deps.php");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 2, 0);
	zephir_array_update_string(&_2, SL("files"), &files, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_2, SL("signature"), &signature_zv, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_var_export_ex(&_1, &_2);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_GET_CONSTANT(&_3, "PHP_EOL");
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_SVSV(&_4, "<?php return ", &_1, ";", &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_5, 2);
	ZEPHIR_CALL_FUNCTION(NULL, "file_put_contents", NULL, 145, &_0, &_4, &_5);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

