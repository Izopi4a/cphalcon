
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/file.h"
#include "kernel/require.h"
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
 * This component allows to create CLI applications using Phalcon
 */
ZEPHIR_INIT_CLASS(Phalcon_Cli_Console)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Cli, Console, phalcon, cli_console, phalcon_application_abstractapplication_ce, phalcon_cli_console_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_cli_console_ce, SL("arguments"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_cli_console_ce, SL("options"), ZEND_ACC_PROTECTED);
	phalcon_cli_console_ce->create_object = zephir_init_properties_Phalcon_Cli_Console;

	return SUCCESS;
}

/**
 * Handle the whole command-line tasks
 */
PHP_METHOD(Phalcon_Cli_Console, handle)
{
	zend_bool _8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *arguments_param = NULL, __$false, className, dispatcher, module, moduleName, moduleObject, modules, path, router, task, _0, _1, _5, _6, _7, _9, _26, _27, _28, _29, _30, _31, _35, _2$$4, _3$$4, _4$$4, _10$$6, _11$$9, _15$$9, _20$$9, _21$$9, _22$$9, _12$$10, _13$$10, _14$$10, _16$$12, _17$$12, _18$$16, _19$$16, _23$$18, _24$$18, _25$$18, _32$$20, _33$$20, _34$$20, _36$$22, _37$$22;
	zval arguments;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arguments);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&dispatcher);
	ZVAL_UNDEF(&module);
	ZVAL_UNDEF(&moduleName);
	ZVAL_UNDEF(&moduleObject);
	ZVAL_UNDEF(&modules);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&router);
	ZVAL_UNDEF(&task);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_18$$16);
	ZVAL_UNDEF(&_19$$16);
	ZVAL_UNDEF(&_23$$18);
	ZVAL_UNDEF(&_24$$18);
	ZVAL_UNDEF(&_25$$18);
	ZVAL_UNDEF(&_32$$20);
	ZVAL_UNDEF(&_33$$20);
	ZVAL_UNDEF(&_34$$20);
	ZVAL_UNDEF(&_36$$22);
	ZVAL_UNDEF(&_37$$22);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("arguments", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("defaultModule", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("modules", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("options", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY_OR_NULL(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &arguments_param);
	if (!arguments_param) {
		ZEPHIR_INIT_VAR(&arguments);
	} else {
		zephir_get_arrval(&arguments, arguments_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 310, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_cli_console_exception_ce, "A dependency injection container is required to access internal services", "phalcon/Cli/Console.zep", 45);
		return;
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_1) != IS_NULL) {
		zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_4$$4);
		ZVAL_STRING(&_4$$4, "console:boot");
		ZEPHIR_CALL_METHOD(&_3$$4, &_2$$4, "fire", NULL, 0, &_4$$4, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_3$$4)) {
			RETURN_MM_BOOL(0);
		}
	}
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_0, 310, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "router");
	ZEPHIR_CALL_METHOD(&_6, &_5, "getShared", NULL, 0, &_7);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&router, &_6);
	_8 = !(zephir_fast_count_int(&arguments));
	if (_8) {
		zephir_read_property_cached(&_9, this_ptr, _zephir_prop_2, 312, PH_NOISY_CC | PH_READONLY);
		_8 = zephir_is_true(&_9);
	}
	if (_8) {
		zephir_read_property_cached(&_10$$6, this_ptr, _zephir_prop_2, 312, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &router, "handle", NULL, 0, &_10$$6);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &router, "handle", NULL, 0, &arguments);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&moduleName, &router, "getModuleName", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&moduleName))) {
		ZEPHIR_OBS_NVAR(&moduleName);
		zephir_read_property_cached(&moduleName, this_ptr, _zephir_prop_3, 313, PH_NOISY_CC);
	}
	if (zephir_is_true(&moduleName)) {
		zephir_read_property_cached(&_11$$9, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_11$$9) != IS_NULL) {
			zephir_read_property_cached(&_12$$10, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_14$$10);
			ZVAL_STRING(&_14$$10, "console:beforeStartModule");
			ZEPHIR_CALL_METHOD(&_13$$10, &_12$$10, "fire", NULL, 0, &_14$$10, this_ptr, &moduleName);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_13$$10)) {
				RETURN_MM_BOOL(0);
			}
		}
		zephir_read_property_cached(&_15$$9, this_ptr, _zephir_prop_4, 314, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&modules, &_15$$9);
		if (UNEXPECTED(!(zephir_array_isset_value(&modules, &moduleName)))) {
			ZEPHIR_INIT_VAR(&_16$$12);
			object_init_ex(&_16$$12, phalcon_cli_console_exception_ce);
			ZEPHIR_INIT_VAR(&_17$$12);
			ZEPHIR_CONCAT_SVS(&_17$$12, "Module '", &moduleName, "' isn't registered in the console container");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_16$$12, "__construct", NULL, 32, &_17$$12);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_16$$12, "phalcon/Cli/Console.zep", 87);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_memory_observe(&module);
		zephir_array_fetch(&module, &modules, &moduleName, PH_NOISY, "phalcon/Cli/Console.zep", 90);
		if (UNEXPECTED(Z_TYPE_P(&module) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_cli_console_exception_ce, "Invalid module definition path", "phalcon/Cli/Console.zep", 93);
			return;
		}
		zephir_memory_observe(&className);
		if (!(zephir_array_isset_string_fetch(&className, &module, SL("className"), 0))) {
			ZEPHIR_INIT_NVAR(&className);
			ZVAL_STRING(&className, "Module");
		}
		zephir_memory_observe(&path);
		if (zephir_array_isset_string_fetch(&path, &module, SL("path"), 0)) {
			if (UNEXPECTED(!((zephir_file_exists(&path) == SUCCESS)))) {
				ZEPHIR_INIT_VAR(&_18$$16);
				object_init_ex(&_18$$16, phalcon_cli_console_exception_ce);
				ZEPHIR_INIT_VAR(&_19$$16);
				ZEPHIR_CONCAT_SVS(&_19$$16, "Module definition path '", &path, "' does not exist");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_18$$16, "__construct", NULL, 32, &_19$$16);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_18$$16, "phalcon/Cli/Console.zep", 104);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (!(zephir_class_exists(&className, zephir_is_true(&__$false) ))) {
				if (zephir_require_once_zval(&path) == FAILURE) {
					RETURN_MM_NULL();
				}
			}
		}
		zephir_read_property_cached(&_15$$9, this_ptr, _zephir_prop_0, 310, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&moduleObject, &_15$$9, "get", NULL, 0, &className);
		zephir_check_call_status();
		zephir_read_property_cached(&_20$$9, this_ptr, _zephir_prop_0, 310, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &moduleObject, "registerAutoloaders", NULL, 0, &_20$$9);
		zephir_check_call_status();
		zephir_read_property_cached(&_21$$9, this_ptr, _zephir_prop_0, 310, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &moduleObject, "registerServices", NULL, 0, &_21$$9);
		zephir_check_call_status();
		zephir_read_property_cached(&_22$$9, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_22$$9) != IS_NULL) {
			zephir_read_property_cached(&_23$$18, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_25$$18);
			ZVAL_STRING(&_25$$18, "console:afterStartModule");
			ZEPHIR_CALL_METHOD(&_24$$18, &_23$$18, "fire", NULL, 0, &_25$$18, this_ptr, &moduleObject);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_24$$18)) {
				RETURN_MM_BOOL(0);
			}
		}
	}
	zephir_read_property_cached(&_26, this_ptr, _zephir_prop_0, 310, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_STRING(&_7, "dispatcher");
	ZEPHIR_CALL_METHOD(&_6, &_26, "getShared", NULL, 0, &_7);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&dispatcher, &_6);
	ZEPHIR_CALL_METHOD(&_6, &router, "getModuleName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setModuleName", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_27, &router, "getTaskName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setTaskName", NULL, 0, &_27);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_28, &router, "getActionName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setActionName", NULL, 0, &_28);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_29, &router, "getParameters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setParams", NULL, 0, &_29);
	zephir_check_call_status();
	zephir_read_property_cached(&_30, this_ptr, _zephir_prop_5, 315, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &dispatcher, "setOptions", NULL, 0, &_30);
	zephir_check_call_status();
	zephir_read_property_cached(&_31, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_31) != IS_NULL) {
		zephir_read_property_cached(&_32$$20, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_34$$20);
		ZVAL_STRING(&_34$$20, "console:beforeHandleTask");
		ZEPHIR_CALL_METHOD(&_33$$20, &_32$$20, "fire", NULL, 0, &_34$$20, this_ptr, &dispatcher);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_33$$20)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_METHOD(&task, &dispatcher, "dispatch", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_35, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_35) != IS_NULL) {
		zephir_read_property_cached(&_36$$22, this_ptr, _zephir_prop_1, 311, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_37$$22);
		ZVAL_STRING(&_37$$22, "console:afterHandleTask");
		ZEPHIR_CALL_METHOD(NULL, &_36$$22, "fire", NULL, 0, &_37$$22, this_ptr, &task);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&task);
}

/**
 * Set an specific argument
 */
PHP_METHOD(Phalcon_Cli_Console, setArgument)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool str, shift, _0, _24;
	zval *arguments_param = NULL, *str_param = NULL, *shift_param = NULL, __$true, arg, pos, args, opts, handleArgs, *_1, _23, _2$$5, _3$$5, _4$$5, _6$$6, _7$$7, _8$$7, _9$$7, _10$$7, _11$$7, _12$$7, _13$$7, _14$$7, _15$$8, _16$$8, _17$$8, _18$$9, _19$$9, _20$$9, _21$$10, _22$$10, _25$$14, _26$$14, _27$$14, _28$$15, _29$$16, _30$$16, _31$$16, _32$$16, _33$$16, _34$$16, _35$$16, _36$$16, _37$$17, _38$$17, _39$$17, _40$$18, _41$$18, _42$$18, _43$$19, _44$$19, _45$$22, _46$$22, _47$$24, _48$$25, _49$$26;
	zval arguments;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arguments);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&arg);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&args);
	ZVAL_UNDEF(&opts);
	ZVAL_UNDEF(&handleArgs);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$10);
	ZVAL_UNDEF(&_22$$10);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_26$$14);
	ZVAL_UNDEF(&_27$$14);
	ZVAL_UNDEF(&_28$$15);
	ZVAL_UNDEF(&_29$$16);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_31$$16);
	ZVAL_UNDEF(&_32$$16);
	ZVAL_UNDEF(&_33$$16);
	ZVAL_UNDEF(&_34$$16);
	ZVAL_UNDEF(&_35$$16);
	ZVAL_UNDEF(&_36$$16);
	ZVAL_UNDEF(&_37$$17);
	ZVAL_UNDEF(&_38$$17);
	ZVAL_UNDEF(&_39$$17);
	ZVAL_UNDEF(&_40$$18);
	ZVAL_UNDEF(&_41$$18);
	ZVAL_UNDEF(&_42$$18);
	ZVAL_UNDEF(&_43$$19);
	ZVAL_UNDEF(&_44$$19);
	ZVAL_UNDEF(&_45$$22);
	ZVAL_UNDEF(&_46$$22);
	ZVAL_UNDEF(&_47$$24);
	ZVAL_UNDEF(&_48$$25);
	ZVAL_UNDEF(&_49$$26);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("arguments", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("options", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY_OR_NULL(arguments, arguments_param)
		Z_PARAM_BOOL(str)
		Z_PARAM_BOOL(shift)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &arguments_param, &str_param, &shift_param);
	if (!arguments_param) {
		ZEPHIR_INIT_VAR(&arguments);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&arguments, arguments_param);
	}
	if (!str_param) {
		str = 1;
	} else {
	if (UNEXPECTED(Z_TYPE_P(str_param) != IS_TRUE && Z_TYPE_P(str_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'str' must be of the type bool"));
		RETURN_MM_NULL();
	}
	str = (Z_TYPE_P(str_param) == IS_TRUE);
	}
	if (!shift_param) {
		shift = 1;
	} else {
	if (UNEXPECTED(Z_TYPE_P(shift_param) != IS_TRUE && Z_TYPE_P(shift_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'shift' must be of the type bool"));
		RETURN_MM_NULL();
	}
	shift = (Z_TYPE_P(shift_param) == IS_TRUE);
	}
	ZEPHIR_INIT_VAR(&args);
	array_init(&args);
	ZEPHIR_INIT_VAR(&opts);
	array_init(&opts);
	ZEPHIR_INIT_VAR(&handleArgs);
	array_init(&handleArgs);
	_0 = shift;
	if (_0) {
		_0 = ((zephir_fast_count_int(&arguments)) ? 1 : 0);
	}
	if (_0) {
		ZEPHIR_MAKE_REF(&arguments);
		ZEPHIR_CALL_FUNCTION(NULL, "array_shift", NULL, 21, &arguments);
		ZEPHIR_UNREF(&arguments);
		zephir_check_call_status();
	}
	zephir_is_iterable(&arguments, 0, "phalcon/Cli/Console.zep", 185);
	if (Z_TYPE_P(&arguments) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arguments), _1)
		{
			ZEPHIR_INIT_NVAR(&arg);
			ZVAL_COPY(&arg, _1);
			if (Z_TYPE_P(&arg) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_2$$5);
				ZVAL_STRING(&_2$$5, "--");
				ZVAL_LONG(&_3$$5, 2);
				ZEPHIR_CALL_FUNCTION(&_4$$5, "strncmp", &_5, 196, &arg, &_2$$5, &_3$$5);
				zephir_check_call_status();
				if (ZEPHIR_IS_LONG(&_4$$5, 0)) {
					ZEPHIR_INIT_NVAR(&_6$$6);
					ZVAL_STRING(&_6$$6, "=");
					ZEPHIR_INIT_NVAR(&pos);
					zephir_fast_strpos(&pos, &arg, &_6$$6, 0 );
					if (zephir_is_true(&pos)) {
						ZEPHIR_INIT_NVAR(&_7$$7);
						ZEPHIR_INIT_NVAR(&_8$$7);
						ZVAL_LONG(&_8$$7, 2);
						ZEPHIR_INIT_NVAR(&_9$$7);
						zephir_sub_function(&_9$$7, &pos, &_8$$7);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZVAL_LONG(&_10$$7, 2);
						ZEPHIR_INIT_NVAR(&_11$$7);
						zephir_substr(&_11$$7, &arg, 2 , zephir_get_intval(&_9$$7), 0);
						zephir_fast_trim(&_7$$7, &_11$$7, NULL , ZEPHIR_TRIM_BOTH);
						ZEPHIR_INIT_NVAR(&_12$$7);
						ZEPHIR_INIT_NVAR(&_8$$7);
						ZVAL_LONG(&_8$$7, 1);
						ZEPHIR_INIT_NVAR(&_13$$7);
						zephir_add_function(&_13$$7, &pos, &_8$$7);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_INIT_NVAR(&_14$$7);
						zephir_substr(&_14$$7, &arg, zephir_get_intval(&_13$$7), 0, ZEPHIR_SUBSTR_NO_LENGTH);
						zephir_fast_trim(&_12$$7, &_14$$7, NULL , ZEPHIR_TRIM_BOTH);
						zephir_array_update_zval(&opts, &_7$$7, &_12$$7, PH_COPY | PH_SEPARATE);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$8);
						ZVAL_LONG(&_16$$8, 2);
						ZEPHIR_INIT_NVAR(&_17$$8);
						zephir_substr(&_17$$8, &arg, 2 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
						zephir_fast_trim(&_15$$8, &_17$$8, NULL , ZEPHIR_TRIM_BOTH);
						zephir_array_update_zval(&opts, &_15$$8, &__$true, PH_COPY | PH_SEPARATE);
					}
				} else {
					ZEPHIR_INIT_NVAR(&_18$$9);
					ZVAL_STRING(&_18$$9, "-");
					ZVAL_LONG(&_19$$9, 1);
					ZEPHIR_CALL_FUNCTION(&_20$$9, "strncmp", &_5, 196, &arg, &_18$$9, &_19$$9);
					zephir_check_call_status();
					if (ZEPHIR_IS_LONG(&_20$$9, 0)) {
						ZVAL_LONG(&_21$$10, 1);
						ZEPHIR_INIT_NVAR(&_22$$10);
						zephir_substr(&_22$$10, &arg, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
						zephir_array_update_zval(&opts, &_22$$10, &__$true, PH_COPY | PH_SEPARATE);
					} else {
						zephir_array_append(&args, &arg, PH_SEPARATE, "phalcon/Cli/Console.zep", 177);
					}
				}
			} else {
				zephir_array_append(&args, &arg, PH_SEPARATE, "phalcon/Cli/Console.zep", 181);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &arguments, "rewind", NULL, 0);
		zephir_check_call_status();
		_24 = 1;
		while (1) {
			if (_24) {
				_24 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &arguments, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_23, &arguments, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_23)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&arg, &arguments, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&arg) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_25$$14);
					ZVAL_STRING(&_25$$14, "--");
					ZVAL_LONG(&_26$$14, 2);
					ZEPHIR_CALL_FUNCTION(&_27$$14, "strncmp", &_5, 196, &arg, &_25$$14, &_26$$14);
					zephir_check_call_status();
					if (ZEPHIR_IS_LONG(&_27$$14, 0)) {
						ZEPHIR_INIT_NVAR(&_28$$15);
						ZVAL_STRING(&_28$$15, "=");
						ZEPHIR_INIT_NVAR(&pos);
						zephir_fast_strpos(&pos, &arg, &_28$$15, 0 );
						if (zephir_is_true(&pos)) {
							ZEPHIR_INIT_NVAR(&_29$$16);
							ZEPHIR_INIT_NVAR(&_30$$16);
							ZVAL_LONG(&_30$$16, 2);
							ZEPHIR_INIT_NVAR(&_31$$16);
							zephir_sub_function(&_31$$16, &pos, &_30$$16);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZVAL_LONG(&_32$$16, 2);
							ZEPHIR_INIT_NVAR(&_33$$16);
							zephir_substr(&_33$$16, &arg, 2 , zephir_get_intval(&_31$$16), 0);
							zephir_fast_trim(&_29$$16, &_33$$16, NULL , ZEPHIR_TRIM_BOTH);
							ZEPHIR_INIT_NVAR(&_34$$16);
							ZEPHIR_INIT_NVAR(&_30$$16);
							ZVAL_LONG(&_30$$16, 1);
							ZEPHIR_INIT_NVAR(&_35$$16);
							zephir_add_function(&_35$$16, &pos, &_30$$16);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_INIT_NVAR(&_36$$16);
							zephir_substr(&_36$$16, &arg, zephir_get_intval(&_35$$16), 0, ZEPHIR_SUBSTR_NO_LENGTH);
							zephir_fast_trim(&_34$$16, &_36$$16, NULL , ZEPHIR_TRIM_BOTH);
							zephir_array_update_zval(&opts, &_29$$16, &_34$$16, PH_COPY | PH_SEPARATE);
						} else {
							ZEPHIR_INIT_NVAR(&_37$$17);
							ZVAL_LONG(&_38$$17, 2);
							ZEPHIR_INIT_NVAR(&_39$$17);
							zephir_substr(&_39$$17, &arg, 2 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
							zephir_fast_trim(&_37$$17, &_39$$17, NULL , ZEPHIR_TRIM_BOTH);
							zephir_array_update_zval(&opts, &_37$$17, &__$true, PH_COPY | PH_SEPARATE);
						}
					} else {
						ZEPHIR_INIT_NVAR(&_40$$18);
						ZVAL_STRING(&_40$$18, "-");
						ZVAL_LONG(&_41$$18, 1);
						ZEPHIR_CALL_FUNCTION(&_42$$18, "strncmp", &_5, 196, &arg, &_40$$18, &_41$$18);
						zephir_check_call_status();
						if (ZEPHIR_IS_LONG(&_42$$18, 0)) {
							ZVAL_LONG(&_43$$19, 1);
							ZEPHIR_INIT_NVAR(&_44$$19);
							zephir_substr(&_44$$19, &arg, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
							zephir_array_update_zval(&opts, &_44$$19, &__$true, PH_COPY | PH_SEPARATE);
						} else {
							zephir_array_append(&args, &arg, PH_SEPARATE, "phalcon/Cli/Console.zep", 177);
						}
					}
				} else {
					zephir_array_append(&args, &arg, PH_SEPARATE, "phalcon/Cli/Console.zep", 181);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&arg);
	if (str) {
		ZEPHIR_INIT_VAR(&_45$$22);
		ZEPHIR_CALL_CE_STATIC(&_46$$22, phalcon_cli_router_route_ce, "getDelimiter", NULL, 0);
		zephir_check_call_status();
		zephir_fast_join(&_45$$22, &_46$$22, &args);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 312, &_45$$22);
	} else {
		if (zephir_fast_count_int(&args)) {
			ZEPHIR_MAKE_REF(&args);
			ZEPHIR_CALL_FUNCTION(&_47$$24, "array_shift", NULL, 21, &args);
			ZEPHIR_UNREF(&args);
			zephir_check_call_status();
			zephir_array_update_string(&handleArgs, SL("task"), &_47$$24, PH_COPY | PH_SEPARATE);
		}
		if (zephir_fast_count_int(&args)) {
			ZEPHIR_MAKE_REF(&args);
			ZEPHIR_CALL_FUNCTION(&_48$$25, "array_shift", NULL, 21, &args);
			ZEPHIR_UNREF(&args);
			zephir_check_call_status();
			zephir_array_update_string(&handleArgs, SL("action"), &_48$$25, PH_COPY | PH_SEPARATE);
		}
		if (zephir_fast_count_int(&args)) {
			ZEPHIR_INIT_VAR(&_49$$26);
			zephir_fast_array_merge(&_49$$26, &handleArgs, &args);
			ZEPHIR_CPY_WRT(&handleArgs, &_49$$26);
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 312, &handleArgs);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 315, &opts);
	RETURN_THIS();
}

zend_object *zephir_init_properties_Phalcon_Cli_Console(zend_class_entry *class_type)
{
		zval _0, _2, _4, _1$$3, _3$$4, _5$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("options"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("modules"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("modules"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("arguments"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("arguments"), &_5$$5);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

