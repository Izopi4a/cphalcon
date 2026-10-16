
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/time.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
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
 * Provides debug capabilities to Phalcon applications
 */
ZEPHIR_INIT_CLASS(Phalcon_Support_Debug)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Support, Debug, phalcon, support_debug, phalcon_support_debug_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_support_debug_ce, SL("blacklist"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_support_debug_ce, SL("data"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_support_debug_ce, SL("hideDocumentRoot"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_support_debug_ce, SL("isActive"), 0, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_support_debug_ce, SL("showBackTrace"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_support_debug_ce, SL("showFileFragment"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_support_debug_ce, SL("showFiles"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_support_debug_ce, SL("uri"), "https://assets.phalcon.io/debug/5.0.x/", ZEND_ACC_PROTECTED);
	phalcon_support_debug_ce->create_object = zephir_init_properties_Phalcon_Support_Debug;

	return SUCCESS;
}

/**
 * Clears are variables added previously
 */
PHP_METHOD(Phalcon_Support_Debug, clearVars)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("data", 4, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 960, &_0);
	RETURN_THIS();
}

/**
 * Adds a variable to the debug output
 *
 * @param mixed $variable
 */
PHP_METHOD(Phalcon_Support_Debug, debugVar)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *varz, varz_sub, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&varz_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(varz)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &varz);
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0);
	zephir_array_fast_append(&_0, varz);
	ZEPHIR_CALL_FUNCTION(&_1, "debug_backtrace", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_VAR(&_2);
	zephir_time(&_2);
	zephir_array_fast_append(&_0, &_2);
	zephir_update_property_array_append(this_ptr, SL("data"), &_0);
	RETURN_THIS();
}

/**
 * Returns the CSS sources
 */
PHP_METHOD(Phalcon_Support_Debug, getCssSources)
{
	zval template, _0, _1, _2, _3, _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&template);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uri", 3, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 961, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&template);
	ZEPHIR_CONCAT_SVS(&template, "\n    <link href='", &_0, "%s'\n          rel='stylesheet'\n          type='text/css' />");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "assets/jquery-ui/themes/ui-lightness/jquery-ui.min.css");
	ZEPHIR_CALL_FUNCTION(&_2, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "assets/jquery-ui/themes/ui-lightness/theme.css");
	ZEPHIR_CALL_FUNCTION(&_3, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "themes/default/style.css");
	ZEPHIR_CALL_FUNCTION(&_4, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VVV(return_value, &_2, &_3, &_4);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Returns the JavaScript sources
 */
PHP_METHOD(Phalcon_Support_Debug, getJsSources)
{
	zval template, _0, _1, _2, _3, _4, _5, _6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&template);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uri", 3, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 961, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&template);
	ZEPHIR_CONCAT_SVS(&template, "\n    <script type='application/javascript'\n            src='", &_0, "%s'></script>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "assets/jquery/dist/jquery.min.js");
	ZEPHIR_CALL_FUNCTION(&_2, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "assets/jquery-ui/jquery-ui.min.js");
	ZEPHIR_CALL_FUNCTION(&_3, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "assets/jquery.scrollTo/jquery.scrollTo.min.js");
	ZEPHIR_CALL_FUNCTION(&_4, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "prettify/prettify.js");
	ZEPHIR_CALL_FUNCTION(&_5, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "pretty.js");
	ZEPHIR_CALL_FUNCTION(&_6, "sprintf", NULL, 73, &template, &_1);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VVVVV(return_value, &_2, &_3, &_4, &_5, &_6);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Generates a link to the current version documentation
 */
PHP_METHOD(Phalcon_Support_Debug, getVersion)
{
	zval version, link, _0, _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&version);
	ZVAL_UNDEF(&link);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&version);
	object_init_ex(&version, phalcon_support_version_ce);
	if (zephir_has_constructor(&version)) {
		ZEPHIR_CALL_METHOD(NULL, &version, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	ZVAL_LONG(&_1, 0);
	ZEPHIR_CALL_METHOD(&_0, &version, "getPart", NULL, 0, &_1);
	zephir_check_call_status();
	ZVAL_LONG(&_1, 1);
	ZEPHIR_CALL_METHOD(&_2, &version, "getPart", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&link);
	ZEPHIR_CONCAT_SVSVS(&link, "https://docs.phalcon.io/", &_0, ".", &_2, "/");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_3, &version, "get", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "<div class='version'>\n    Phalcon Framework <a href='", &link, "' target='_new'>", &_3, "</a>\n</div>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Halts the request showing a backtrace
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Support_Debug, halt)
{

	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_support_debug_exception_ce, "Halted request", "phalcon/Support/Debug.zep", 145);
	return;
}

/**
 * Listen for uncaught exceptions and non silent notices or warnings
 *
 * @param bool $exceptions
 * @param bool $lowSeverity
 */
PHP_METHOD(Phalcon_Support_Debug, listen)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exceptions_param = NULL, *lowSeverity_param = NULL;
	zend_bool exceptions, lowSeverity;
	zval *this_ptr = getThis();

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(exceptions)
		Z_PARAM_BOOL(lowSeverity)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &exceptions_param, &lowSeverity_param);
	if (!exceptions_param) {
		exceptions = 1;
	} else {
		}
	if (!lowSeverity_param) {
		lowSeverity = 0;
	} else {
		}
	if (exceptions) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "listenExceptions", NULL, 0);
		zephir_check_call_status();
	}
	if (lowSeverity) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "listenLowSeverity", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_THIS();
}

/**
 * Listen for uncaught exceptions
 */
PHP_METHOD(Phalcon_Support_Debug, listenExceptions)
{
	zval _1;
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0);
	zephir_array_fast_append(&_0, this_ptr);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "onUncaughtException");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_CALL_FUNCTION(NULL, "set_exception_handler", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Listen for non silent notices or warnings
 */
PHP_METHOD(Phalcon_Support_Debug, listenLowSeverity)
{
	zval _1;
	zval _0, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0);
	zephir_array_fast_append(&_0, this_ptr);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "onUncaughtLowSeverity");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_CALL_FUNCTION(NULL, "set_error_handler", NULL, 138, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 2, 0);
	zephir_array_fast_append(&_2, this_ptr);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "onUncaughtException");
	zephir_array_fast_append(&_2, &_1);
	ZEPHIR_CALL_FUNCTION(NULL, "set_exception_handler", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Handles uncaught exceptions
 */
PHP_METHOD(Phalcon_Support_Debug, onUncaughtException)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub, __$true, __$false, obLevel, _0, _2, _1$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&obLevel);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(exception, zend_ce_throwable)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &exception);
	ZEPHIR_CALL_FUNCTION(&obLevel, "ob_get_level", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_GT_LONG(&obLevel, 0)) {
		ZEPHIR_CALL_FUNCTION(NULL, "ob_end_clean", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_static_property_ce(&_0, phalcon_support_debug_ce, SL("isActive"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_TRUE_IDENTICAL(&_0)) {
		zephir_update_static_property_ce(phalcon_support_debug_ce, ZEND_STRL("isActive"), &__$true);
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "renderHtml", NULL, 0, exception);
		zephir_check_call_status();
		zend_print_zval(&_1$$4, 0);
		zephir_update_static_property_ce(phalcon_support_debug_ce, ZEND_STRL("isActive"), &__$false);
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_CALL_METHOD(&_2, exception, "getMessage", NULL, 0);
	zephir_check_call_status();
	zend_print_zval(&_2, 0);
	RETURN_MM_BOOL(0);
}

/**
 * Throws an exception when a notice or warning is raised
 */
PHP_METHOD(Phalcon_Support_Debug, onUncaughtLowSeverity)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *severity, severity_sub, *message, message_sub, *file, file_sub, *line, line_sub, _0, _1, _2$$3, _3$$3;

	ZVAL_UNDEF(&severity_sub);
	ZVAL_UNDEF(&message_sub);
	ZVAL_UNDEF(&file_sub);
	ZVAL_UNDEF(&line_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ZVAL(severity)
		Z_PARAM_ZVAL(message)
		Z_PARAM_ZVAL(file)
		Z_PARAM_ZVAL(line)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &severity, &message, &file, &line);
	ZEPHIR_CALL_FUNCTION(&_0, "error_reporting", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	zephir_bitwise_and_function(&_1, &_0, severity);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(zephir_is_true(&_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, zend_ce_error_exception);
		ZVAL_LONG(&_3$$3, 0);
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 0, message, &_3$$3, severity, file, line);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Support/Debug.zep", 244);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Render exception to html format.
 *
 * @param Throwable $exception
 *
 * @return string
 * @throws ReflectionException
 */
PHP_METHOD(Phalcon_Support_Debug, renderHtml)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub, _REQUEST, _SERVER, className, escapedMessage, html, _0, _1, _2, _3, _4, _5, _6, _15, _7$$3, _8$$3, _9$$3, _10$$3, _11$$3, _12$$3, _13$$3, _14$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&_REQUEST);
	ZVAL_UNDEF(&_SERVER);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&escapedMessage);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("showBackTrace", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("data", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(exception, zend_ce_throwable)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_get_global(&_SERVER, SL("_SERVER"));
	zephir_get_global(&_REQUEST, SL("_REQUEST"));
	zephir_fetch_params(1, 1, 0, &exception);
	ZEPHIR_INIT_VAR(&className);
	zephir_get_class(&className, exception, 0);
	ZEPHIR_CALL_METHOD(&_0, exception, "getMessage", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&escapedMessage, this_ptr, "escapeString", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getCssSources", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&html);
	ZEPHIR_CONCAT_SVSVSVS(&html, "<!DOCTYPE html>\n<html lang='en'>\n<head>\n    <title>", &className, ":", &escapedMessage, "</title>", &_1, "\n</head>\n<body>\n");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getVersion", NULL, 0);
	zephir_check_call_status();
	zephir_concat_self(&html, &_2);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_3, exception, "getFile", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, exception, "getLine", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SVSVSVSVS(&_5, "\n<div align='center'>\n    <div class='error-main'>\n        <h1>", &className, ": ", &escapedMessage, "</h1>\n        <span class='error-file'>", &_3, " (", &_4, ")</span>\n    </div>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&html, &_5);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_0, 962, PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&_6)) {
		zephir_concat_self_str(&html, SL("\n\n    <div class='error-info'>\n        <div id='tabs'>\n            <ul>\n                <li><a href='#backtrace'>Backtrace</a></li>\n                <li><a href='#request'>Request</a></li>\n                <li><a href='#server'>Server</a></li>\n                <li><a href='#files'>Included Files</a></li>\n                <li><a href='#memory'>Memory</a></li>"));
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_memory_observe(&_7$$3);
		zephir_read_property_cached(&_7$$3, this_ptr, _zephir_prop_1, 960, PH_NOISY_CC);
		if (!(ZEPHIR_IS_EMPTY(&_7$$3))) {
			zephir_concat_self_str(&html, SL("\n                <li><a href='#variables'>Variables</a></li>"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_concat_self_str(&html, SL("\n            </ul>"));
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_8$$3, this_ptr, "printBacktrace", NULL, 0, exception);
		zephir_check_call_status();
		zephir_concat_self(&html, &_8$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_10$$3);
		ZVAL_STRING(&_10$$3, "request");
		ZEPHIR_CALL_METHOD(&_9$$3, this_ptr, "printSuperglobal", NULL, 0, &_REQUEST, &_10$$3);
		zephir_check_call_status();
		zephir_concat_self(&html, &_9$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(&_10$$3);
		ZVAL_STRING(&_10$$3, "server");
		ZEPHIR_CALL_METHOD(&_11$$3, this_ptr, "printSuperglobal", NULL, 0, &_SERVER, &_10$$3);
		zephir_check_call_status();
		zephir_concat_self(&html, &_11$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_12$$3, this_ptr, "printIncludedFiles", NULL, 0);
		zephir_check_call_status();
		zephir_concat_self(&html, &_12$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_13$$3, this_ptr, "printMemoryUsage", NULL, 0);
		zephir_check_call_status();
		zephir_concat_self(&html, &_13$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_14$$3, this_ptr, "printExtraVariables", NULL, 0);
		zephir_check_call_status();
		zephir_concat_self(&html, &_14$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self_str(&html, SL("\n            </div>"));
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_15, this_ptr, "getJsSources", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VVS(return_value, &html, &_15, "\n        </div>\n    </body>\n</html>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Sets if files the exception's backtrace must be showed
 *
 * @param array $blacklist
 */
PHP_METHOD(Phalcon_Support_Debug, setBlacklist)
{
	zend_bool _8, _18;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *blacklist_param = NULL, area, result, subArray, value, _0, _1, *_2, *_3, _7, _11, _12, *_13, *_14, _17, _4$$3, _6$$3, _9$$4, _10$$4, _15$$5, _16$$5, _19$$6, _20$$6;
	zval blacklist;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&blacklist);
	ZVAL_UNDEF(&area);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&subArray);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("blacklist", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(blacklist, blacklist_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &blacklist_param);
	zephir_get_arrval(&blacklist, blacklist_param);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "request");
	ZEPHIR_CALL_METHOD(&area, this_ptr, "getArrVal", NULL, 0, &blacklist, &_1, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&subArray);
	array_init(&subArray);
	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	if (Z_TYPE_P(&area) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_1);
		zephir_string_to_char_array(&_1, &area);
		_2 = &_1;
	} else {
		_2 = &area;
	}
	zephir_is_iterable(_2, 0, "phalcon/Support/Debug.zep", 354);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _3)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			ZEPHIR_CALL_FUNCTION(&_4$$3, "mb_strtolower", &_5, 7, &value);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&value, &_4$$3);
			ZEPHIR_INIT_NVAR(&_6$$3);
			ZVAL_LONG(&_6$$3, 1);
			zephir_array_update_zval(&subArray, &value, &_6$$3, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&value, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_9$$4, "mb_strtolower", &_5, 7, &value);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&value, &_9$$4);
				ZEPHIR_INIT_NVAR(&_10$$4);
				ZVAL_LONG(&_10$$4, 1);
				zephir_array_update_zval(&subArray, &value, &_10$$4, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	zephir_array_update_string(&result, SL("request"), &subArray, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_11);
	array_init(&_11);
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "server");
	ZEPHIR_CALL_METHOD(&area, this_ptr, "getArrVal", NULL, 0, &blacklist, &_12, &_11);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&subArray);
	array_init(&subArray);
	if (Z_TYPE_P(&area) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_12);
		zephir_string_to_char_array(&_12, &area);
		_13 = &_12;
	} else {
		_13 = &area;
	}
	zephir_is_iterable(_13, 0, "phalcon/Support/Debug.zep", 363);
	if (Z_TYPE_P(_13) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13), _14)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _14);
			ZEPHIR_CALL_FUNCTION(&_15$$5, "mb_strtolower", &_5, 7, &value);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&value, &_15$$5);
			ZEPHIR_INIT_NVAR(&_16$$5);
			ZVAL_LONG(&_16$$5, 1);
			zephir_array_update_zval(&subArray, &value, &_16$$5, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _13, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _13, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _13, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&value, _13, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_19$$6, "mb_strtolower", &_5, 7, &value);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&value, &_19$$6);
				ZEPHIR_INIT_NVAR(&_20$$6);
				ZVAL_LONG(&_20$$6, 1);
				zephir_array_update_zval(&subArray, &value, &_20$$6, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	zephir_array_update_string(&result, SL("server"), &subArray, PH_COPY | PH_SEPARATE);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 963, &result);
	RETURN_THIS();
}

/**
 * Sets if files the exception's backtrace must be showed
 *
 * @param bool $showBackTrace
 */
PHP_METHOD(Phalcon_Support_Debug, setShowBackTrace)
{
	zval *showBackTrace_param = NULL, __$true, __$false;
	zend_bool showBackTrace;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("showBackTrace", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(showBackTrace)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &showBackTrace_param);
	if (showBackTrace) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 962, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 962, &__$false);
	}
	RETURN_THISW();
}

/**
 * Sets if files must be completely opened and showed in the output
 * or just the fragment related to the exception
 *
 * @param bool $showFileFragment
 */
PHP_METHOD(Phalcon_Support_Debug, setShowFileFragment)
{
	zval *showFileFragment_param = NULL, __$true, __$false;
	zend_bool showFileFragment;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("showFileFragment", 16, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(showFileFragment)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &showFileFragment_param);
	if (showFileFragment) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 964, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 964, &__$false);
	}
	RETURN_THISW();
}

/**
 * Set if files part of the backtrace must be shown in the output
 *
 * @param bool $showFiles
 */
PHP_METHOD(Phalcon_Support_Debug, setShowFiles)
{
	zval *showFiles_param = NULL, __$true, __$false;
	zend_bool showFiles;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("showFiles", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(showFiles)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &showFiles_param);
	if (showFiles) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 965, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 965, &__$false);
	}
	RETURN_THISW();
}

/**
 * Change the base URI for static resources
 *
 * @param string $uri
 */
PHP_METHOD(Phalcon_Support_Debug, setUri)
{
	zval uri_zv;
	zend_string *uri = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("uri", 3, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&uri_zv, uri);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 961, &uri_zv);
	RETURN_THISW();
}

/**
 * Escapes a string with htmlentities
 *
 * @param string $value
 */
PHP_METHOD(Phalcon_Support_Debug, escapeString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval value_zv, _0, _1, _2, _3, _4;
	zend_string *value = NULL;

	ZVAL_UNDEF(&value_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&value_zv);
	ZVAL_STR_COPY(&value_zv, value);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "\n");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "\\n");
	zephir_fast_str_replace(&_0, &_1, &_2, &value_zv);
	ZVAL_LONG(&_3, 2);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "utf-8");
	ZEPHIR_RETURN_CALL_FUNCTION("htmlentities", NULL, 0, &_0, &_3, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Produces a recursive representation of an array
 *
 * @param array $arguments
 * @param int   $number
 *
 * @return string|null
 */
PHP_METHOD(Phalcon_Support_Debug, getArrayDump)
{
	zend_string *_3;
	zend_ulong _2;
	zend_bool _0, _12;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *argument_param = NULL, *n = NULL, n_sub, numberArguments, dump, varDump, k, v, *_1, _11, _5$$8, _6$$8, _7$$8, _9$$9, _10$$5, _13$$15, _14$$15, _15$$15, _16$$16, _17$$12;
	zval argument;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&argument);
	ZVAL_UNDEF(&n_sub);
	ZVAL_UNDEF(&numberArguments);
	ZVAL_UNDEF(&dump);
	ZVAL_UNDEF(&varDump);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&v);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_13$$15);
	ZVAL_UNDEF(&_14$$15);
	ZVAL_UNDEF(&_15$$15);
	ZVAL_UNDEF(&_16$$16);
	ZVAL_UNDEF(&_17$$12);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(argument, argument_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &argument_param, &n);
	ZEPHIR_OBS_COPY_OR_DUP(&argument, argument_param);
	if (!n) {
		n = &n_sub;
		ZEPHIR_INIT_VAR(n);
		ZVAL_LONG(n, 0);
	}
	ZEPHIR_INIT_VAR(&numberArguments);
	ZVAL_LONG(&numberArguments, zephir_fast_count_int(&argument));
	_0 = ZEPHIR_GE_LONG(n, 3);
	if (!(_0)) {
		_0 = ZEPHIR_IS_LONG(&numberArguments, 0);
	}
	if (_0) {
		RETURN_MM_NULL();
	}
	if (ZEPHIR_GE_LONG(&numberArguments, 10)) {
		RETURN_CCTOR(&numberArguments);
	}
	ZEPHIR_INIT_VAR(&dump);
	array_init(&dump);
	zephir_is_iterable(&argument, 0, "phalcon/Support/Debug.zep", 474);
	if (Z_TYPE_P(&argument) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&argument), _2, _3, _1)
		{
			ZEPHIR_INIT_NVAR(&k);
			if (_3 != NULL) { 
				ZVAL_STR_COPY(&k, _3);
			} else {
				ZVAL_LONG(&k, _2);
			}
			ZEPHIR_INIT_NVAR(&v);
			ZVAL_COPY(&v, _1);
			if (ZEPHIR_IS_STRING(&v, "")) {
				ZEPHIR_INIT_NVAR(&varDump);
				ZVAL_STRING(&varDump, "(empty string)");
			} else if (zephir_is_scalar(&v)) {
				ZEPHIR_CALL_METHOD(&varDump, this_ptr, "escapeString", &_4, 0, &v);
				zephir_check_call_status();
			} else if (Z_TYPE_P(&v) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(&_6$$8);
				ZVAL_LONG(&_6$$8, 1);
				ZEPHIR_INIT_NVAR(&_7$$8);
				zephir_add_function(&_7$$8, n, &_6$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_5$$8, this_ptr, "getArrayDump", &_8, 0, &v, &_7$$8);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&varDump);
				ZEPHIR_CONCAT_SVS(&varDump, "Array(", &_5$$8, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else if (Z_TYPE_P(&v) == IS_OBJECT) {
				ZEPHIR_INIT_NVAR(&_9$$9);
				zephir_get_class(&_9$$9, &v, 0);
				ZEPHIR_INIT_NVAR(&varDump);
				ZEPHIR_CONCAT_SVS(&varDump, "Object(", &_9$$9, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else if (Z_TYPE_P(&v) == IS_NULL) {
				ZEPHIR_INIT_NVAR(&varDump);
				ZVAL_STRING(&varDump, "null");
			} else {
				ZEPHIR_CPY_WRT(&varDump, &v);
			}
			ZEPHIR_INIT_NVAR(&_10$$5);
			ZEPHIR_CONCAT_SVSV(&_10$$5, "[", &k, "] =&gt; ", &varDump);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&dump, &_10$$5, PH_SEPARATE, "phalcon/Support/Debug.zep", 471);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &argument, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &argument, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, &argument, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&k, &argument, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&v, &argument, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_IS_STRING(&v, "")) {
					ZEPHIR_INIT_NVAR(&varDump);
					ZVAL_STRING(&varDump, "(empty string)");
				} else if (zephir_is_scalar(&v)) {
					ZEPHIR_CALL_METHOD(&varDump, this_ptr, "escapeString", &_4, 0, &v);
					zephir_check_call_status();
				} else if (Z_TYPE_P(&v) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&_14$$15);
					ZVAL_LONG(&_14$$15, 1);
					ZEPHIR_INIT_NVAR(&_15$$15);
					zephir_add_function(&_15$$15, n, &_14$$15);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_13$$15, this_ptr, "getArrayDump", &_8, 0, &v, &_15$$15);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&varDump);
					ZEPHIR_CONCAT_SVS(&varDump, "Array(", &_13$$15, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else if (Z_TYPE_P(&v) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_16$$16);
					zephir_get_class(&_16$$16, &v, 0);
					ZEPHIR_INIT_NVAR(&varDump);
					ZEPHIR_CONCAT_SVS(&varDump, "Object(", &_16$$16, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else if (Z_TYPE_P(&v) == IS_NULL) {
					ZEPHIR_INIT_NVAR(&varDump);
					ZVAL_STRING(&varDump, "null");
				} else {
					ZEPHIR_CPY_WRT(&varDump, &v);
				}
				ZEPHIR_INIT_NVAR(&_17$$12);
				ZEPHIR_CONCAT_SVSV(&_17$$12, "[", &k, "] =&gt; ", &varDump);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&dump, &_17$$12, PH_SEPARATE, "phalcon/Support/Debug.zep", 471);
		}
	}
	ZEPHIR_INIT_NVAR(&v);
	ZEPHIR_INIT_NVAR(&k);
	zephir_fast_join_str(return_value, SL(", "), &dump);
	RETURN_MM();
}

/**
 * Produces an string representation of a variable
 */
PHP_METHOD(Phalcon_Support_Debug, getVarDump)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *variable, variable_sub, className, dumpedObject, _0$$8, _1$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&variable_sub);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&dumpedObject);
	ZVAL_UNDEF(&_0$$8);
	ZVAL_UNDEF(&_1$$10);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(variable)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &variable);
	if (ZEPHIR_IS_TRUE_IDENTICAL(variable)) {
		RETURN_MM_STRING("true");
	}
	if (ZEPHIR_IS_FALSE_IDENTICAL(variable)) {
		RETURN_MM_STRING("false");
	}
	if (Z_TYPE_P(variable) == IS_STRING) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "escapeString", NULL, 0, variable);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_is_scalar(variable)) {
		RETVAL_ZVAL(variable, 1, 0);
		RETURN_MM();
	}
	if (Z_TYPE_P(variable) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&className);
		zephir_get_class(&className, variable, 0);
		if ((zephir_method_exists_ex(variable, ZEND_STRL("dump")) == SUCCESS)) {
			ZEPHIR_CALL_METHOD(&dumpedObject, variable, "dump", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_0$$8, this_ptr, "getArrayDump", NULL, 0, &dumpedObject);
			zephir_check_call_status();
			ZEPHIR_CONCAT_SVSVS(return_value, "Object(", &className, ": ", &_0$$8, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		} else {
			ZEPHIR_CONCAT_SVS(return_value, "Object(", &className, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
	}
	if (Z_TYPE_P(variable) == IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&_1$$10, this_ptr, "getArrayDump", NULL, 0, variable);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVS(return_value, "Array(", &_1$$10, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (Z_TYPE_P(variable) == IS_NULL) {
		RETURN_MM_STRING("null");
	}
	zephir_gettype(return_value, variable);
	RETURN_MM();
}

/**
 * Shows a backtrace item
 *
 * @param int   $number
 * @param array $trace
 *
 * @return string
 * @throws ReflectionException
 */
PHP_METHOD(Phalcon_Support_Debug, showTraceItem)
{
	zval _27$$17;
	zend_bool _21$$14, _39$$25, _48$$25;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_18 = NULL, *_55 = NULL;
	zval trace;
	zval *number_param = NULL, *trace_param = NULL, className, prepareInternalClass, preparedFunctionName, html, classReflection, prepareUriClass, functionName, functionReflection, traceArgs, arguments, argument, file, line, lines, numberLines, lastLine, linePosition, currentLine, classNameWithLink, functionNameWithLink, parts, _13, _0$$3, _1$$3, _8$$3, _9$$3, _2$$4, _3$$4, _4$$5, _5$$6, _6$$6, _7$$6, _10$$10, _11$$11, _12$$11, *_14$$14, _15$$14, *_16$$14, _20$$14, _24$$14, _25$$14, _17$$15, _19$$15, _22$$16, _23$$16, _26$$17, _28$$17, _29$$17, _30$$18, _31$$19, _32$$19, _33$$19, _34$$19, _35$$19, _36$$24, _37$$24, _38$$25, _40$$26, _41$$26, _42$$26, _43$$26, _44$$26, _45$$27, _46$$27, _47$$27, _49$$29, _50$$29, _51$$29, _52$$29, _53$$29, _54$$29;
	zend_long number, ZEPHIR_LAST_CALL_STATUS, firstLine = 0, i = 0, beforeLine$$19, afterLine$$19;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&prepareInternalClass);
	ZVAL_UNDEF(&preparedFunctionName);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&classReflection);
	ZVAL_UNDEF(&prepareUriClass);
	ZVAL_UNDEF(&functionName);
	ZVAL_UNDEF(&functionReflection);
	ZVAL_UNDEF(&traceArgs);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&argument);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&line);
	ZVAL_UNDEF(&lines);
	ZVAL_UNDEF(&numberLines);
	ZVAL_UNDEF(&lastLine);
	ZVAL_UNDEF(&linePosition);
	ZVAL_UNDEF(&currentLine);
	ZVAL_UNDEF(&classNameWithLink);
	ZVAL_UNDEF(&functionNameWithLink);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_15$$14);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_24$$14);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_17$$15);
	ZVAL_UNDEF(&_19$$15);
	ZVAL_UNDEF(&_22$$16);
	ZVAL_UNDEF(&_23$$16);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_29$$17);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_31$$19);
	ZVAL_UNDEF(&_32$$19);
	ZVAL_UNDEF(&_33$$19);
	ZVAL_UNDEF(&_34$$19);
	ZVAL_UNDEF(&_35$$19);
	ZVAL_UNDEF(&_36$$24);
	ZVAL_UNDEF(&_37$$24);
	ZVAL_UNDEF(&_38$$25);
	ZVAL_UNDEF(&_40$$26);
	ZVAL_UNDEF(&_41$$26);
	ZVAL_UNDEF(&_42$$26);
	ZVAL_UNDEF(&_43$$26);
	ZVAL_UNDEF(&_44$$26);
	ZVAL_UNDEF(&_45$$27);
	ZVAL_UNDEF(&_46$$27);
	ZVAL_UNDEF(&_47$$27);
	ZVAL_UNDEF(&_49$$29);
	ZVAL_UNDEF(&_50$$29);
	ZVAL_UNDEF(&_51$$29);
	ZVAL_UNDEF(&_52$$29);
	ZVAL_UNDEF(&_53$$29);
	ZVAL_UNDEF(&_54$$29);
	ZVAL_UNDEF(&trace);
	ZVAL_UNDEF(&_27$$17);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("showFiles", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("showFileFragment", 16, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(number)
		ZEPHIR_Z_PARAM_ARRAY(trace, trace_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &number_param, &trace_param);
	ZEPHIR_OBS_COPY_OR_DUP(&trace, trace_param);
	ZEPHIR_INIT_VAR(&html);
	ZVAL_STRING(&html, "\n                    <tr>\n                        <td style='text-align: right; vertical-align: top'\n                            class='error-number'>\n                            #\n                        </td>\n                        <td>");
	zephir_memory_observe(&className);
	if (zephir_array_isset_string_fetch(&className, &trace, SL("class"), 0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "Phalcon");
		ZEPHIR_CALL_FUNCTION(&_1$$3, "str_starts_with", NULL, 367, &className, &_0$$3);
		zephir_check_call_status();
		if (zephir_is_true(&_1$$3)) {
			ZEPHIR_INIT_VAR(&parts);
			zephir_fast_explode_str(&parts, SL("\\"), &className, NULL);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_memory_observe(&_2$$4);
			zephir_array_fetch_long(&_2$$4, &parts, 0, PH_NOISY, "phalcon/Support/Debug.zep", 585);
			zephir_memory_observe(&_3$$4);
			zephir_array_fetch_long(&_3$$4, &parts, 1, PH_NOISY, "phalcon/Support/Debug.zep", 585);
			ZEPHIR_INIT_VAR(&prepareUriClass);
			ZEPHIR_CONCAT_VSV(&prepareUriClass, &_2$$4, "_", &_3$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_VAR(&classNameWithLink);
			ZEPHIR_CONCAT_SSVSVS(&classNameWithLink, "<a target='_new' ", "href='https://docs.phalcon.io/5.0/en/api/", &prepareUriClass, "'>", &className, "</a>");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_VAR(&classReflection);
			object_init_ex(&classReflection, zephir_get_internal_ce(SL("reflectionclass")));
			ZEPHIR_CALL_METHOD(NULL, &classReflection, "__construct", NULL, 157, &className);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_4$$5, &classReflection, "isInternal", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_4$$5)) {
				ZEPHIR_CALL_FUNCTION(&_5$$6, "mb_strtolower", NULL, 7, &className);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_6$$6);
				ZVAL_STRING(&_6$$6, "_");
				ZEPHIR_INIT_VAR(&_7$$6);
				ZVAL_STRING(&_7$$6, "-");
				ZEPHIR_INIT_VAR(&prepareInternalClass);
				zephir_fast_str_replace(&prepareInternalClass, &_6$$6, &_7$$6, &_5$$6);
				ZEPHIR_INIT_NVAR(&classNameWithLink);
				ZEPHIR_CONCAT_SSVSVS(&classNameWithLink, "<a target='_new' ", "href='https://secure.php.net/manual/en/class.", &prepareInternalClass, ".php'>", &className, "</a>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&classNameWithLink, &className);
			}
		}
		ZEPHIR_INIT_VAR(&_8$$3);
		ZEPHIR_CONCAT_SVS(&_8$$3, "\n                        <span class='error-class'>\n                            ", &classNameWithLink, "\n                        </span>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&html, &_8$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_fetch_string(&_9$$3, &trace, SL("type"), PH_NOISY | PH_READONLY, "phalcon/Support/Debug.zep", 622);
		zephir_concat_self(&html, &_9$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_memory_observe(&functionName);
	zephir_array_fetch_string(&functionName, &trace, SL("function"), PH_NOISY, "phalcon/Support/Debug.zep", 628);
	if (zephir_array_isset_value_string(&trace, SL("class"))) {
		ZEPHIR_CPY_WRT(&functionNameWithLink, &functionName);
	} else {
		if (1 == (zephir_function_exists(&functionName) == SUCCESS)) {
			ZEPHIR_INIT_VAR(&functionReflection);
			object_init_ex(&functionReflection, zephir_get_internal_ce(SL("reflectionfunction")));
			ZEPHIR_CALL_METHOD(NULL, &functionReflection, "__construct", NULL, 154, &functionName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_10$$10, &functionReflection, "isInternal", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_10$$10)) {
				ZEPHIR_INIT_VAR(&_11$$11);
				ZVAL_STRING(&_11$$11, "_");
				ZEPHIR_INIT_VAR(&_12$$11);
				ZVAL_STRING(&_12$$11, "-");
				ZEPHIR_INIT_VAR(&preparedFunctionName);
				zephir_fast_str_replace(&preparedFunctionName, &_11$$11, &_12$$11, &functionName);
				ZEPHIR_INIT_NVAR(&functionNameWithLink);
				ZEPHIR_CONCAT_SSVSVS(&functionNameWithLink, "<a target='_new' ", "href='https://secure.php.net/manual/en/function.", &preparedFunctionName, ".php'>", &functionName, "</a>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&functionNameWithLink, &functionName);
			}
		} else {
			ZEPHIR_CPY_WRT(&functionNameWithLink, &functionName);
		}
	}
	ZEPHIR_INIT_VAR(&_13);
	ZEPHIR_CONCAT_SVS(&_13, "\n                        <span class='error-function'>\n                            ", &functionNameWithLink, "\n                        </span>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&html, &_13);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&traceArgs);
	if (zephir_array_isset_string_fetch(&traceArgs, &trace, SL("args"), 0)) {
		ZEPHIR_INIT_VAR(&arguments);
		array_init(&arguments);
		if (Z_TYPE_P(&traceArgs) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_15$$14);
			zephir_string_to_char_array(&_15$$14, &traceArgs);
			_14$$14 = &_15$$14;
		} else {
			_14$$14 = &traceArgs;
		}
		zephir_is_iterable(_14$$14, 0, "phalcon/Support/Debug.zep", 682);
		if (Z_TYPE_P(_14$$14) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_14$$14), _16$$14)
			{
				ZEPHIR_INIT_NVAR(&argument);
				ZVAL_COPY(&argument, _16$$14);
				ZEPHIR_CALL_METHOD(&_17$$15, this_ptr, "getVarDump", &_18, 0, &argument);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$15);
				ZEPHIR_CONCAT_SVS(&_19$$15, "\n                        <span class='error-parameter'>\n                            ", &_17$$15, "\n                        </span>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&arguments, &_19$$15, PH_SEPARATE, "phalcon/Support/Debug.zep", 676);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _14$$14, "rewind", NULL, 0);
			zephir_check_call_status();
			_21$$14 = 1;
			while (1) {
				if (_21$$14) {
					_21$$14 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _14$$14, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_20$$14, _14$$14, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_20$$14)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&argument, _14$$14, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_22$$16, this_ptr, "getVarDump", &_18, 0, &argument);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_23$$16);
					ZEPHIR_CONCAT_SVS(&_23$$16, "\n                        <span class='error-parameter'>\n                            ", &_22$$16, "\n                        </span>");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&arguments, &_23$$16, PH_SEPARATE, "phalcon/Support/Debug.zep", 676);
			}
		}
		ZEPHIR_INIT_NVAR(&argument);
		ZEPHIR_INIT_VAR(&_24$$14);
		zephir_fast_join_str(&_24$$14, SL(", "), &arguments);
		ZEPHIR_INIT_VAR(&_25$$14);
		ZEPHIR_CONCAT_SVS(&_25$$14, "(", &_24$$14, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&html, &_25$$14);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (zephir_array_isset_value_string(&trace, SL("file"))) {
		zephir_memory_observe(&file);
		zephir_array_fetch_string(&file, &trace, SL("file"), PH_NOISY, "phalcon/Support/Debug.zep", 690);
		zephir_memory_observe(&_26$$17);
		zephir_array_fetch_string(&_26$$17, &trace, SL("line"), PH_NOISY, "phalcon/Support/Debug.zep", 691);
		zephir_cast_to_string(&_27$$17, &_26$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&line, &_27$$17);
		ZEPHIR_INIT_VAR(&_28$$17);
		ZEPHIR_CONCAT_SVSVS(&_28$$17, "\n                        <br/>\n                        <div class='error-file'>\n                            ", &file, " (", &line, ")\n                        </div>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&html, &_28$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_29$$17, this_ptr, _zephir_prop_0, 965, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_29$$17)) {
			ZEPHIR_CALL_FUNCTION(&lines, "file", NULL, 0, &file);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&numberLines);
			ZVAL_LONG(&numberLines, zephir_fast_count_int(&lines));
			zephir_read_property_cached(&_30$$18, this_ptr, _zephir_prop_1, 964, PH_NOISY_CC | PH_READONLY);
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_30$$18)) {
				ZEPHIR_INIT_VAR(&_31$$19);
				ZVAL_LONG(&_31$$19, 7);
				ZEPHIR_INIT_VAR(&_32$$19);
				zephir_sub_function(&_32$$19, &line, &_31$$19);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				beforeLine$$19 = zephir_get_intval(&_32$$19);
				if (beforeLine$$19 < 1) {
					firstLine = 1;
				} else {
					firstLine = beforeLine$$19;
				}
				ZEPHIR_INIT_NVAR(&_31$$19);
				ZVAL_LONG(&_31$$19, 5);
				ZEPHIR_INIT_VAR(&_33$$19);
				zephir_add_function(&_33$$19, &line, &_31$$19);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				afterLine$$19 = zephir_get_intval(&_33$$19);
				if (ZEPHIR_LT_LONG(&numberLines, afterLine$$19)) {
					ZEPHIR_CPY_WRT(&lastLine, &numberLines);
				} else {
					ZEPHIR_INIT_NVAR(&lastLine);
					ZVAL_LONG(&lastLine, afterLine$$19);
				}
				ZEPHIR_INIT_NVAR(&_31$$19);
				ZVAL_LONG(&_31$$19, firstLine);
				ZEPHIR_INIT_VAR(&_34$$19);
				ZVAL_LONG(&_34$$19, firstLine);
				ZEPHIR_INIT_VAR(&_35$$19);
				ZEPHIR_CONCAT_SVSVSVS(&_35$$19, "\n                        <pre class='prettyprint highlight:", &_31$$19, ":", &line, " linenums:", &_34$$19, "'>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&html, &_35$$19);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				firstLine = 1;
				ZEPHIR_CPY_WRT(&lastLine, &numberLines);
				ZEPHIR_INIT_VAR(&_36$$24);
				ZVAL_LONG(&_36$$24, firstLine);
				ZEPHIR_INIT_VAR(&_37$$24);
				ZEPHIR_CONCAT_SVSVS(&_37$$24, "\n                        <pre class='prettyprint highlight:", &_36$$24, ":", &line, " linenums error-scroll'>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&html, &_37$$24);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			i = firstLine;
			while (1) {
				if (!(ZEPHIR_GE_LONG(&lastLine, i))) {
					break;
				}
				ZEPHIR_INIT_NVAR(&linePosition);
				ZVAL_LONG(&linePosition, (i - 1));
				ZEPHIR_OBS_NVAR(&currentLine);
				zephir_array_fetch(&currentLine, &lines, &linePosition, PH_NOISY, "phalcon/Support/Debug.zep", 760);
				zephir_read_property_cached(&_38$$25, this_ptr, _zephir_prop_1, 964, PH_NOISY_CC | PH_READONLY);
				_39$$25 = zephir_is_true(&_38$$25);
				if (_39$$25) {
					_39$$25 = i == firstLine;
				}
				if (_39$$25) {
					ZEPHIR_INIT_NVAR(&_40$$26);
					ZEPHIR_INIT_NVAR(&_41$$26);
					zephir_fast_trim(&_41$$26, &currentLine, NULL , ZEPHIR_TRIM_RIGHT);
					ZEPHIR_INIT_NVAR(&_42$$26);
					ZVAL_STRING(&_42$$26, "#\\*\\/#");
					ZEPHIR_INIT_NVAR(&_43$$26);
					ZEPHIR_INIT_NVAR(&_44$$26);
					ZVAL_STRING(&_44$$26, "#\\*\\/#");
					zephir_preg_match(&_43$$26, &_44$$26, &_41$$26, &_40$$26, 0, 0 , 0 );
					if (zephir_is_true(&_43$$26)) {
						ZEPHIR_INIT_NVAR(&_45$$27);
						ZEPHIR_INIT_NVAR(&_46$$27);
						ZVAL_STRING(&_46$$27, "* /");
						ZEPHIR_INIT_NVAR(&_47$$27);
						ZVAL_STRING(&_47$$27, " ");
						zephir_fast_str_replace(&_45$$27, &_46$$27, &_47$$27, &currentLine);
						ZEPHIR_CPY_WRT(&currentLine, &_45$$27);
					}
				}
				_48$$25 = ZEPHIR_IS_STRING(&currentLine, "\n");
				if (!(_48$$25)) {
					_48$$25 = ZEPHIR_IS_STRING(&currentLine, "\r\n");
				}
				if (_48$$25) {
					zephir_concat_self_str(&html, SL("&nbsp;\n"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_INIT_NVAR(&_49$$29);
					ZEPHIR_INIT_NVAR(&_50$$29);
					ZVAL_STRING(&_50$$29, "\t");
					ZEPHIR_INIT_NVAR(&_51$$29);
					ZVAL_STRING(&_51$$29, "  ");
					zephir_fast_str_replace(&_49$$29, &_50$$29, &_51$$29, &currentLine);
					ZVAL_LONG(&_52$$29, 2);
					ZEPHIR_INIT_NVAR(&_53$$29);
					ZVAL_STRING(&_53$$29, "UTF-8");
					ZEPHIR_CALL_FUNCTION(&_54$$29, "htmlentities", &_55, 0, &_49$$29, &_52$$29, &_53$$29);
					zephir_check_call_status();
					zephir_concat_self(&html, &_54$$29);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				i++;
			}
			zephir_concat_self_str(&html, SL("\n                            </pre>"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CONCAT_VS(return_value, &html, "\n                    </td>\n                </tr>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Support_Debug, closeTable)
{

	RETURN_STRING("\n                </tbody>\n            </table>\n        </div>");
}

/**
 * @param Throwable $exception
 *
 * @return string
 * @throws ReflectionException
 */
PHP_METHOD(Phalcon_Support_Debug, printBacktrace)
{
	zend_bool _8;
	zend_string *_4;
	zend_ulong _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub, html, trace, number, item, *_0, _1, *_2, _7, _10, _5$$3, _9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&trace);
	ZVAL_UNDEF(&number);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_9$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(exception, zend_ce_throwable)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &exception);
	ZEPHIR_INIT_VAR(&html);
	ZVAL_STRING(&html, "\n\n        <div id='backtrace'>\n            <table style='border-collapse: collapse; border-spacing: 0; text-align=center; width:100%'>\n                <tbody>");
	ZEPHIR_CALL_METHOD(&trace, exception, "getTrace", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&trace) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_1);
		zephir_string_to_char_array(&_1, &trace);
		_0 = &_1;
	} else {
		_0 = &trace;
	}
	zephir_is_iterable(_0, 0, "phalcon/Support/Debug.zep", 832);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_0), _3, _4, _2)
		{
			ZEPHIR_INIT_NVAR(&number);
			if (_4 != NULL) { 
				ZVAL_STR_COPY(&number, _4);
			} else {
				ZVAL_LONG(&number, _3);
			}
			ZEPHIR_INIT_NVAR(&item);
			ZVAL_COPY(&item, _2);
			ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "showTraceItem", &_6, 0, &number, &item);
			zephir_check_call_status();
			zephir_concat_self(&html, &_5$$3);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _0, "rewind", NULL, 0);
		zephir_check_call_status();
		_8 = 1;
		while (1) {
			if (_8) {
				_8 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, _0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&number, _0, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&item, _0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_9$$4, this_ptr, "showTraceItem", &_6, 0, &number, &item);
				zephir_check_call_status();
				zephir_concat_self(&html, &_9$$4);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_INIT_NVAR(&number);
	ZEPHIR_CALL_METHOD(&_10, this_ptr, "closeTable", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &html, &_10);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Support_Debug, printExtraVariables)
{
	zend_bool _15$$3;
	zend_string *_9$$3;
	zend_ulong _8$$3;
	zval html, key, value, _0, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, *_6$$3, *_7$$3, _14$$3, _19$$3, _10$$4, _11$$4, _13$$4, _16$$5, _17$$5, _18$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_19$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("data", 4, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&html);
	ZVAL_STRING(&html, "");
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 960, PH_NOISY_CC | PH_READONLY);
	if (!(ZEPHIR_IS_EMPTY(&_0))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "variables");
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "Key");
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "Value");
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "printTableHeader", NULL, 0, &_2$$3, &_3$$3, &_4$$3);
		zephir_check_call_status();
		zephir_concat_self(&html, &_1$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_0, 960, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_5$$3) == IS_STRING) {
			ZEPHIR_INIT_NVAR(&_2$$3);
			zephir_string_to_char_array(&_2$$3, &_5$$3);
			_6$$3 = &_2$$3;
		} else {
			_6$$3 = &_5$$3;
		}
		zephir_is_iterable(_6$$3, 0, "phalcon/Support/Debug.zep", 854);
		if (Z_TYPE_P(_6$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_6$$3), _8$$3, _9$$3, _7$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_9$$3 != NULL) { 
					ZVAL_STR_COPY(&key, _9$$3);
				} else {
					ZVAL_LONG(&key, _8$$3);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _7$$3);
				ZEPHIR_OBS_NVAR(&_11$$4);
				zephir_array_fetch_long(&_11$$4, &value, 0, PH_NOISY, "phalcon/Support/Debug.zep", 850);
				ZEPHIR_CALL_METHOD(&_10$$4, this_ptr, "getVarDump", &_12, 0, &_11$$4);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZEPHIR_CONCAT_SVSVS(&_13$$4, "<tr><td class=\"key\">", &key, "</td><td>", &_10$$4, "</td></tr>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&html, &_13$$4);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _6$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_15$$3 = 1;
			while (1) {
				if (_15$$3) {
					_15$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _6$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_14$$3, _6$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_14$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, _6$$3, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&value, _6$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&_17$$5);
					zephir_array_fetch_long(&_17$$5, &value, 0, PH_NOISY, "phalcon/Support/Debug.zep", 850);
					ZEPHIR_CALL_METHOD(&_16$$5, this_ptr, "getVarDump", &_12, 0, &_17$$5);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_18$$5);
					ZEPHIR_CONCAT_SVSVS(&_18$$5, "<tr><td class=\"key\">", &key, "</td><td>", &_16$$5, "</td></tr>");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&html, &_18$$5);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
		ZEPHIR_CALL_METHOD(&_19$$3, this_ptr, "closeTable", NULL, 0);
		zephir_check_call_status();
		zephir_concat_self(&html, &_19$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CCTOR(&html);
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Support_Debug, printIncludedFiles)
{
	zend_bool _10;
	zend_string *_7;
	zend_ulong _6;
	zval html, key, value, _0, _1, _2, _3, *_4, *_5, _9, _12, _8$$3, _11$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_11$$4);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "files");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "#");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Path");
	ZEPHIR_CALL_METHOD(&html, this_ptr, "printTableHeader", NULL, 0, &_0, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_3, "get_included_files", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_3) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_0);
		zephir_string_to_char_array(&_0, &_3);
		_4 = &_0;
	} else {
		_4 = &_3;
	}
	zephir_is_iterable(_4, 0, "phalcon/Support/Debug.zep", 873);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4), _6, _7, _5)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_7 != NULL) { 
				ZVAL_STR_COPY(&key, _7);
			} else {
				ZVAL_LONG(&key, _6);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _5);
			ZEPHIR_INIT_NVAR(&_8$$3);
			ZEPHIR_CONCAT_SVSVS(&_8$$3, "\n                        <tr>\n                            <td>", &key, "</td>\n                            <td>", &value, "</td>\n                        </tr>");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&html, &_8$$3);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_10 = 1;
		while (1) {
			if (_10) {
				_10 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_9, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, _4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_11$$4);
				ZEPHIR_CONCAT_SVSVS(&_11$$4, "\n                        <tr>\n                            <td>", &key, "</td>\n                            <td>", &value, "</td>\n                        </tr>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&html, &_11$$4);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_CALL_METHOD(&_12, this_ptr, "closeTable", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &html, &_12);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Support_Debug, printMemoryUsage)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, _0, _1, _2, _3, _4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "memory");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Memory");
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "");
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "printTableHeader", NULL, 0, &_1, &_2, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_4, "memory_get_usage", NULL, 0, &__$true);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSVS(return_value, &_0, "\n                    <tr>\n                        <td>\n                            Usage\n                        </td>\n                        <td>", &_4, "</td>\n                    </tr>\n                </tbody>\n                </table>\n            </div>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @param array  $source
 * @param string $div
 *
 * @return string
 */
PHP_METHOD(Phalcon_Support_Debug, printSuperglobal)
{
	zend_bool _12;
	zend_ulong _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *div = NULL, *_5;
	zval *source_param = NULL, div_zv, html, filter, key, value, _0, _1, _2, *_3, _11, _6$$3, _8$$4, _10$$4, _13$$5, _14$$6, _15$$6;
	zval source;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&source);
	ZVAL_UNDEF(&div_zv);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("blacklist", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(source, source_param)
		Z_PARAM_STR(div)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	source_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&source, source_param);
	zephir_memory_observe(&div_zv);
	ZVAL_STR_COPY(&div_zv, div);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Key");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Value");
	ZEPHIR_CALL_METHOD(&html, this_ptr, "printTableHeader", NULL, 0, &div_zv, &_0, &_1);
	zephir_check_call_status();
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 963, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_0);
	array_init(&_0);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "server");
	ZEPHIR_CALL_METHOD(&filter, this_ptr, "getArrVal", NULL, 0, &_2, &_1, &_0);
	zephir_check_call_status();
	zephir_is_iterable(&source, 0, "phalcon/Support/Debug.zep", 906);
	if (Z_TYPE_P(&source) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&source), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&key, _5);
			} else {
				ZVAL_LONG(&key, _4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			ZEPHIR_CALL_FUNCTION(&_6$$3, "mb_strtolower", &_7, 7, &key);
			zephir_check_call_status();
			if (!(zephir_array_isset_value(&filter, &_6$$3))) {
				ZEPHIR_CALL_METHOD(&_8$$4, this_ptr, "getVarDump", &_9, 0, &value);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_10$$4);
				ZEPHIR_CONCAT_SVSVS(&_10$$4, "\n                    <tr>\n                        <td class='key'>", &key, "</td>\n                        <td>", &_8$$4, "</td>\n                    </tr>");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&html, &_10$$4);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &source, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &source, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, &source, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, &source, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, &source, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_13$$5, "mb_strtolower", &_7, 7, &key);
				zephir_check_call_status();
				if (!(zephir_array_isset_value(&filter, &_13$$5))) {
					ZEPHIR_CALL_METHOD(&_14$$6, this_ptr, "getVarDump", &_9, 0, &value);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_15$$6);
					ZEPHIR_CONCAT_SVSVS(&_15$$6, "\n                    <tr>\n                        <td class='key'>", &key, "</td>\n                        <td>", &_14$$6, "</td>\n                    </tr>");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&html, &_15$$6);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_CONCAT_VS(return_value, &html, "\n                    </tbody>\n                </table>\n            </div>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @param string $divId
 * @param string $headerOne
 * @param string $headerTwo
 * @param string $colspan
 *
 * @return string
 */
PHP_METHOD(Phalcon_Support_Debug, printTableHeader)
{
	zval _0$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval divId_zv, headerOne_zv, headerTwo_zv, colspan_zv, span;
	zend_string *divId = NULL, *headerOne = NULL, *headerTwo = NULL, *colspan = NULL;

	ZVAL_UNDEF(&divId_zv);
	ZVAL_UNDEF(&headerOne_zv);
	ZVAL_UNDEF(&headerTwo_zv);
	ZVAL_UNDEF(&colspan_zv);
	ZVAL_UNDEF(&span);
	ZVAL_UNDEF(&_0$$4);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(divId)
		Z_PARAM_STR(headerOne)
		Z_PARAM_STR(headerTwo)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(colspan)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&divId_zv);
	ZVAL_STR_COPY(&divId_zv, divId);
	zephir_memory_observe(&headerOne_zv);
	ZVAL_STR_COPY(&headerOne_zv, headerOne);
	zephir_memory_observe(&headerTwo_zv);
	ZVAL_STR_COPY(&headerTwo_zv, headerTwo);
	if (!colspan) {
		colspan = zend_string_init(ZEND_STRL(""), 0);
		zephir_memory_observe(&colspan_zv);
		ZVAL_STR(&colspan_zv, colspan);
	} else {
		zephir_memory_observe(&colspan_zv);
	ZVAL_STR_COPY(&colspan_zv, colspan);
	}
	ZEPHIR_INIT_VAR(&span);
	if (ZEPHIR_IS_EMPTY(&colspan_zv)) {
		ZVAL_STRING(&span, "");
	} else {
		ZEPHIR_INIT_VAR(&_0$$4);
		ZEPHIR_CONCAT_SVS(&_0$$4, " colspan=\"", &colspan_zv, "\"");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&span, &_0$$4);
	}
	ZEPHIR_CONCAT_SVSVSVSVS(return_value, "\n        <div id='", &divId_zv, "'>\n            <table style='border-collapse: collapse; border-spacing: 0; text-align: center'\n                   class='superglobal-detail'>\n                <thead>\n                <tr>\n                    <th", &span, ">", &headerOne_zv, "</th>\n                </tr>\n                <tr>\n                    <th>", &headerTwo_zv, "</th>\n                </tr>\n                </thead>\n                <tbody>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @todo Remove this when we get traits
 */
PHP_METHOD(Phalcon_Support_Debug, getArrVal)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *collection_param = NULL, *index, index_sub, *defaultValue = NULL, defaultValue_sub, __$null, value;
	zval collection;

	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&value);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		ZEPHIR_Z_PARAM_ARRAY(collection, collection_param)
		Z_PARAM_ZVAL(index)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &collection_param, &index, &defaultValue);
	ZEPHIR_OBS_COPY_OR_DUP(&collection, collection_param);
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}
	zephir_memory_observe(&value);
	if (UNEXPECTED(!(zephir_array_isset_fetch(&value, &collection, index, 0)))) {
		RETVAL_ZVAL(defaultValue, 1, 0);
		RETURN_MM();
	}
	RETURN_CCTOR(&value);
}

zend_object *zephir_init_properties_Phalcon_Support_Debug(zend_class_entry *class_type)
{
		zval _3$$4;
	zval _0, _2, _1$$3, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_3$$4);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("data"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("data"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("blacklist"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			zephir_create_array(&_3$$4, 2, 0);
			ZEPHIR_INIT_VAR(&_4$$4);
			array_init(&_4$$4);
			zephir_array_update_string(&_3$$4, SL("request"), &_4$$4, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_4$$4);
			array_init(&_4$$4);
			zephir_array_update_string(&_3$$4, SL("server"), &_4$$4, PH_COPY | PH_SEPARATE);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("blacklist"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

