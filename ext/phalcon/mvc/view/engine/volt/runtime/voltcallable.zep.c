
#ifdef HAVE_CONFIG_H
#include "../../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../../php_ext.h"
#include "../../../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * A template function, filter or test backed by a PHP handler that runs at
 * RENDER time with the evaluated argument values. The counterpart of
 * Compiler::addFunction(), whose definition runs at COMPILE time and returns
 * PHP source.
 *
 * Accepted callables:
 * - any Closure, including first-class callables (Money::format(...))
 * - "strlen", "App\\Money::format", [Money::class, "format"] (static)
 * - [$object, "method"] and invokable objects
 * - [ServiceOrClass::class, "method"] with a non-static method: the instance
 *   comes from the DI container the first time a template calls it
 *
 * Options:
 * - safe:         the result is HTML, autoescape leaves it alone
 * - needsContext: the template variables are passed as the first argument
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime, VoltCallable, phalcon, mvc_view_engine_volt_runtime_voltcallable, phalcon_mvc_view_engine_volt_runtime_voltcallable_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_runtime_voltcallable_ce, SL("handler"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_runtime_voltcallable_ce, SL("name"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_runtime_voltcallable_ce, SL("options"), ZEND_ACC_PROTECTED);
	phalcon_mvc_view_engine_volt_runtime_voltcallable_ce->create_object = zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable;

	return SUCCESS;
}

/**
 * Phalcon\Mvc\View\Engine\Volt\Runtime\VoltCallable constructor
 *
 * @param array options = [
 *     'safe'         => false,
 *     'needsContext' => false
 * ]
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval options;
	zval name_zv, *handler, handler_sub, *options_param = NULL;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("name", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("handler", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("options", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(handler)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		options_param = ZEND_CALL_ARG(execute_data, 3);
	}
	ZVAL_STR(&name_zv, name);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 91, &name_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 92, handler);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 93, &options);
	ZEPHIR_MM_RESTORE();
}

/**
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, getCallable)
{

	RETURN_MEMBER(getThis(), "handler");
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, getName)
{

	RETURN_MEMBER_TYPED(getThis(), "name", IS_STRING);
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, getOptions)
{

	RETURN_MEMBER_TYPED(getThis(), "options", IS_ARRAY);
}

/**
 * Part of the cache signature: what the compiled code depends on
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, getSignature)
{
	zval code, _0, _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("name", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("options", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&code, this_ptr, "getStaticCallCode", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&code) == IS_NULL) {
		ZEPHIR_INIT_NVAR(&code);
		ZVAL_STRING(&code, "runtime");
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_get_class(&_0, this_ptr, 0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 91, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 93, PH_NOISY_CC | PH_READONLY);
	zephir_json_encode(&_2, &_3, 0 );
	ZEPHIR_CONCAT_VSVSVSV(return_value, &_0, ":", &_1, ":", &code, ":", &_2);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * PHP code that calls the handler directly, when it can be written into
 * the compiled template as is: a function name or a public static method.
 * Null means "resolve it at render time" (closures, objects, services).
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, getStaticCallCode)
{
	zend_bool _1, _6, _7, _9, _12$$6, _18$$6;
	zval handler, method, _0, _8, _10, _2$$4, _3$$4, _4$$5, _5$$5, _11$$6, _13$$6, _14$$6, _15$$6, _16$$6, _17$$6, _19$$6, _20$$8, _21$$8, _22$$8, _23$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_23$$8);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("handler", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 92, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&handler, &_0);
	_1 = Z_TYPE_P(&handler) == IS_STRING;
	if (_1) {
		_1 = !(zephir_memnstr_str(&handler, SL("::"), "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 109));
	}
	if (_1) {
		if ((zephir_function_exists(&handler) == SUCCESS)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			ZEPHIR_INIT_VAR(&_3$$4);
			ZVAL_STRING(&_3$$4, "\\");
			zephir_fast_trim(&_2$$4, &handler, &_3$$4, ZEPHIR_TRIM_LEFT);
			ZEPHIR_CONCAT_SV(return_value, "\\", &_2$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		RETURN_MM_NULL();
	}
	if (Z_TYPE_P(&handler) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4$$5);
		ZVAL_LONG(&_5$$5, 2);
		zephir_fast_explode_str(&_4$$5, SL("::"), &handler, &_5$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&handler, &_4$$5);
	}
	_6 = Z_TYPE_P(&handler) == IS_ARRAY;
	if (_6) {
		_6 = zephir_fast_count_int(&handler) == 2;
	}
	_7 = _6;
	if (_7) {
		zephir_memory_observe(&_8);
		zephir_array_fetch_long(&_8, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 121);
		_7 = Z_TYPE_P(&_8) == IS_STRING;
	}
	_9 = _7;
	if (_9) {
		zephir_memory_observe(&_10);
		zephir_array_fetch_long(&_10, &handler, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 121);
		_9 = Z_TYPE_P(&_10) == IS_STRING;
	}
	if (_9) {
		zephir_memory_observe(&_11$$6);
		zephir_array_fetch_long(&_11$$6, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 122);
		_12$$6 = !(zephir_class_exists(&_11$$6, 1));
		if (!(_12$$6)) {
			zephir_memory_observe(&_13$$6);
			zephir_array_fetch_long(&_13$$6, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 122);
			zephir_memory_observe(&_14$$6);
			zephir_array_fetch_long(&_14$$6, &handler, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 122);
			_12$$6 = !((zephir_method_exists(&_13$$6, &_14$$6)  == SUCCESS));
		}
		if (_12$$6) {
			RETURN_MM_NULL();
		}
		ZEPHIR_INIT_VAR(&method);
		object_init_ex(&method, zephir_get_internal_ce(SL("reflectionmethod")));
		zephir_memory_observe(&_15$$6);
		zephir_array_fetch_long(&_15$$6, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 126);
		zephir_memory_observe(&_16$$6);
		zephir_array_fetch_long(&_16$$6, &handler, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 126);
		ZEPHIR_CALL_METHOD(NULL, &method, "__construct", NULL, 69, &_15$$6, &_16$$6);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_17$$6, &method, "isStatic", NULL, 70);
		zephir_check_call_status();
		_18$$6 = zephir_is_true(&_17$$6);
		if (_18$$6) {
			ZEPHIR_CALL_METHOD(&_19$$6, &method, "isPublic", NULL, 71);
			zephir_check_call_status();
			_18$$6 = zephir_is_true(&_19$$6);
		}
		if (_18$$6) {
			ZEPHIR_INIT_VAR(&_20$$8);
			zephir_memory_observe(&_21$$8);
			zephir_array_fetch_long(&_21$$8, &handler, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 129);
			ZEPHIR_INIT_VAR(&_22$$8);
			ZVAL_STRING(&_22$$8, "\\");
			zephir_fast_trim(&_20$$8, &_21$$8, &_22$$8, ZEPHIR_TRIM_LEFT);
			zephir_memory_observe(&_23$$8);
			zephir_array_fetch_long(&_23$$8, &handler, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Runtime/VoltCallable.zep", 129);
			ZEPHIR_CONCAT_SVSV(return_value, "\\", &_20$$8, "::", &_23$$8);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
	}
	RETURN_MM_NULL();
}

/**
 * Whether the result is HTML that autoescape must not escape again
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, isSafe)
{
	zval safe, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&safe);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&safe);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 93, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string_fetch(&safe, &_0, SL("safe"), 0)) {
		RETURN_MM_BOOL(zephir_get_boolval(&safe));
	}
	RETURN_MM_BOOL(0);
}

/**
 * Whether the template variables are passed as the first argument
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable, needsContext)
{
	zval needsContext, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&needsContext);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&needsContext);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 93, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string_fetch(&needsContext, &_0, SL("needsContext"), 0)) {
		RETURN_MM_BOOL(zephir_get_boolval(&needsContext));
	}
	RETURN_MM_BOOL(0);
}

zend_object *zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Runtime_VoltCallable(zend_class_entry *class_type)
{
		zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	

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
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

