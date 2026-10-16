
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "Zend/zend_closures.h"
#include "kernel/file.h"
#include "kernel/string.h"
#include "phalcon/mvc/view/engine/volt/scanner.h"
#include "phalcon/mvc/view/engine/volt/volt.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * This class reads and compiles Volt templates into PHP plain code
 *
 *```php
 * $compiler = new \Phalcon\Mvc\View\Engine\Volt\Compiler();
 *
 * $compiler->compile("views/partials/header.volt");
 *
 * require $compiler->getCompiledTemplatePath();
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Compiler)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt, Compiler, phalcon, mvc_view_engine_volt_compiler, phalcon_mvc_view_engine_volt_compiler_method_entry, 0);

	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_view_engine_volt_compiler_ce, SL("autoescape"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_engine_volt_compiler_ce, SL("blockLevel"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array|null
	 *
	 * TODO: Make array only?
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("blocks"), ZEND_ACC_PROTECTED);
	/**
	 * @var DiInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("container"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("compiledTemplatePath"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("currentBlock"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("currentPath"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_engine_volt_compiler_ce, SL("exprLevel"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_view_engine_volt_compiler_ce, SL("extended"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("extensions"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|bool
	 *
	 * TODO: Make it always array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("extendedBlocks"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("filters"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_engine_volt_compiler_ce, SL("foreachLevel"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("forElsePointers"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("functions"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_engine_volt_compiler_ce, SL("level"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("loopPointers"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("macros"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("options"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_engine_volt_compiler_ce, SL("prefix"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var ViewBaseInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("view"), ZEND_ACC_PROTECTED);
	phalcon_mvc_view_engine_volt_compiler_ce->create_object = zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Compiler;

	zend_class_implements(phalcon_mvc_view_engine_volt_compiler_ce, 1, phalcon_di_injectionawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\View\Engine\Volt\Compiler
 *
 * @param ViewBaseInterface|null view
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, __construct)
{
	zval *view = NULL, view_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&view_sub);
	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("view", 4, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(view, phalcon_mvc_viewbaseinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(0, 1, &view);
	if (!view) {
		view = &view_sub;
		view = &__$null;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 906, view);
}

/**
 * Registers a Volt's extension
 *
 * @var mixed extension
 *
 * @return Compiler
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, addExtension)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *extension, extension_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extension_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(extension)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extension);
	if (UNEXPECTED(Z_TYPE_P(extension) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "The extension is not valid", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 160);
		return;
	}
	if ((zephir_method_exists_ex(extension, ZEND_STRL("initialize")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(NULL, extension, "initialize", NULL, 0, this_ptr);
		zephir_check_call_status();
	}
	zephir_update_property_array_append(this_ptr, SL("extensions"), extension);
	RETURN_THIS();
}

/**
 * Register a new filter in the compiler
 *
 * @param string name
 * @param mixed definition
 *
 * @return Compiler
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, addFilter)
{
	zval name_zv, *definition, definition_sub;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&definition_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(definition)
	ZEND_PARSE_PARAMETERS_END();
	definition = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&name_zv, name);
	zephir_update_property_array(this_ptr, SL("filters"), &name_zv, definition);
	RETURN_THISW();
}

/**
 * Register a new function in the compiler
 *
 * @param string name
 * @param mixed definition
 *
 * @return Compiler
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, addFunction)
{
	zval name_zv, *definition, definition_sub;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&definition_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(definition)
	ZEND_PARSE_PARAMETERS_END();
	definition = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&name_zv, name);
	zephir_update_property_array(this_ptr, SL("functions"), &name_zv, definition);
	RETURN_THISW();
}

/**
 * Resolves attribute reading
 *
 * @param array expr
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, attributeReader)
{
	zend_bool _4$$5, _9$$8;
	zval exprCode;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *expr_param = NULL, left, leftType, variable, level, leftCode, right, _0, _10, _1$$4, _2$$4, _3$$5, _5$$5, _6$$5, _7$$6, _8$$7, _11$$11, _12$$12;
	zval expr;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&left);
	ZVAL_UNDEF(&leftType);
	ZVAL_UNDEF(&variable);
	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&leftCode);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&exprCode);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("foreachLevel", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expr_param);
	ZEPHIR_OBS_COPY_OR_DUP(&expr, expr_param);
	ZEPHIR_INIT_VAR(&exprCode);
	ZVAL_STRING(&exprCode, "");
	zephir_memory_observe(&left);
	zephir_array_fetch_string(&left, &expr, SL("left"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 219);
	zephir_memory_observe(&_0);
	zephir_array_fetch_string(&_0, &left, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 221);
	if (ZEPHIR_IS_LONG(&_0, 265)) {
		zephir_memory_observe(&variable);
		zephir_array_fetch_string(&variable, &left, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 222);
		if (ZEPHIR_IS_STRING(&variable, "loop")) {
			zephir_memory_observe(&level);
			zephir_read_property_cached(&level, this_ptr, _zephir_prop_0, 907, PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "getUniquePrefix", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_2$$4);
			ZEPHIR_CONCAT_SVVS(&_2$$4, "$", &_1$$4, &level, "loop");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&exprCode, &_2$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_array(this_ptr, SL("loopPointers"), &level, &level);
		} else {
			zephir_read_property_cached(&_3$$5, this_ptr, _zephir_prop_1, 908, PH_NOISY_CC | PH_READONLY);
			_4$$5 = Z_TYPE_P(&_3$$5) != IS_NULL;
			if (_4$$5) {
				zephir_read_property_cached(&_5$$5, this_ptr, _zephir_prop_1, 908, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_METHOD(&_6$$5, &_5$$5, "has", NULL, 0, &variable);
				zephir_check_call_status();
				_4$$5 = zephir_is_true(&_6$$5);
			}
			if (_4$$5) {
				ZEPHIR_INIT_VAR(&_7$$6);
				ZEPHIR_CONCAT_SV(&_7$$6, "$this->", &variable);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&exprCode, &_7$$6);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_INIT_VAR(&_8$$7);
				ZEPHIR_CONCAT_SV(&_8$$7, "$", &variable);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&exprCode, &_8$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
	} else {
		ZEPHIR_CALL_METHOD(&leftCode, this_ptr, "expression", NULL, 0, &left);
		zephir_check_call_status();
		zephir_memory_observe(&leftType);
		zephir_array_fetch_string(&leftType, &left, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 244);
		_9$$8 = !ZEPHIR_IS_LONG(&leftType, '.');
		if (_9$$8) {
			_9$$8 = !ZEPHIR_IS_LONG(&leftType, 350);
		}
		if (_9$$8) {
			zephir_concat_self(&exprCode, &leftCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_concat_self(&exprCode, &leftCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_concat_self_str(&exprCode, "->", sizeof("->") - 1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&right);
	zephir_array_fetch_string(&right, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 255);
	zephir_memory_observe(&_10);
	zephir_array_fetch_string(&_10, &right, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 257);
	if (ZEPHIR_IS_LONG(&_10, 265)) {
		zephir_memory_observe(&_11$$11);
		zephir_array_fetch_string(&_11$$11, &right, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 258);
		zephir_concat_self(&exprCode, &_11$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(&_12$$12, this_ptr, "expression", NULL, 0, &right);
		zephir_check_call_status();
		zephir_concat_self(&exprCode, &_12$$12);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CTOR(&exprCode);
}

/**
 * Compiles a template into a file applying the compiler options
 * This method does not return the compiled path if the template was not compiled
 *
 *```php
 * $compiler->compile("views/layouts/main.volt");
 *
 * require $compiler->getCompiledTemplatePath();
 *```
 *
 * @param string templatePath
 * @param bool extendsMode
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compile)
{
	zval _11$$26;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _9, _13;
	zval templatePath_zv, *extendsMode_param = NULL, __$true, __$false, __$null, blocksCode, compilation, compileAlways, compiledExtension, compiledPath, compiledSeparator, compiledTemplatePath, options, prefix, stat, templateSepPath, _0, _1$$4, _2$$4, _3$$10, _4$$10, _5$$13, _6$$13, _7$$17, _8$$17, _10$$22, _12$$26, _14$$29, _15$$31, _16$$32, _17$$35, _18$$35;
	zend_string *templatePath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templatePath_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&blocksCode);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&compileAlways);
	ZVAL_UNDEF(&compiledExtension);
	ZVAL_UNDEF(&compiledPath);
	ZVAL_UNDEF(&compiledSeparator);
	ZVAL_UNDEF(&compiledTemplatePath);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&stat);
	ZVAL_UNDEF(&templateSepPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$10);
	ZVAL_UNDEF(&_4$$10);
	ZVAL_UNDEF(&_5$$13);
	ZVAL_UNDEF(&_6$$13);
	ZVAL_UNDEF(&_7$$17);
	ZVAL_UNDEF(&_8$$17);
	ZVAL_UNDEF(&_10$$22);
	ZVAL_UNDEF(&_12$$26);
	ZVAL_UNDEF(&_14$$29);
	ZVAL_UNDEF(&_15$$31);
	ZVAL_UNDEF(&_16$$32);
	ZVAL_UNDEF(&_17$$35);
	ZVAL_UNDEF(&_18$$35);
	ZVAL_UNDEF(&_11$$26);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extended", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("extendedBlocks", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("blocks", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("level", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("foreachLevel", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("blockLevel", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("exprLevel", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("compiledTemplatePath", 20, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(templatePath)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		extendsMode_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&templatePath_zv);
	ZVAL_STR_COPY(&templatePath_zv, templatePath);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&compiledTemplatePath);
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 909, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 909, &__$false);
	}
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 910, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 910, &__$false);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 911, &__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 912, &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 907, &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 913, &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 914, &_0);
	ZEPHIR_INIT_VAR(&compilation);
	ZVAL_NULL(&compilation);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_7, 915, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&options, &_0);
	zephir_memory_observe(&compileAlways);
	if (!(zephir_array_isset_string_fetch(&compileAlways, &options, SL("always"), 0))) {
		ZEPHIR_OBS_NVAR(&compileAlways);
		if (zephir_array_isset_string_fetch(&compileAlways, &options, SL("compileAlways"), 0)) {
			ZEPHIR_INIT_VAR(&_1$$4);
			ZVAL_STRING(&_1$$4, "The 'compileAlways' option is deprecated. Use 'always' instead.");
			ZVAL_LONG(&_2$$4, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_1$$4, &_2$$4);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&compileAlways);
			ZVAL_BOOL(&compileAlways, 0);
		}
	}
	if (UNEXPECTED(((Z_TYPE_P(&compileAlways) == IS_TRUE || Z_TYPE_P(&compileAlways) == IS_FALSE) != 1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'always' must be a bool value", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 319);
		return;
	}
	zephir_memory_observe(&prefix);
	if (!(zephir_array_isset_string_fetch(&prefix, &options, SL("prefix"), 0))) {
		ZEPHIR_INIT_NVAR(&prefix);
		ZVAL_STRING(&prefix, "");
	}
	if (UNEXPECTED(Z_TYPE_P(&prefix) != IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'prefix' must be a string", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 330);
		return;
	}
	zephir_memory_observe(&compiledPath);
	if (!(zephir_array_isset_string_fetch(&compiledPath, &options, SL("path"), 0))) {
		ZEPHIR_OBS_NVAR(&compiledPath);
		if (zephir_array_isset_string_fetch(&compiledPath, &options, SL("compiledPath"), 0)) {
			ZEPHIR_INIT_VAR(&_3$$10);
			ZVAL_STRING(&_3$$10, "The 'compiledPath' option is deprecated. Use 'path' instead.");
			ZVAL_LONG(&_4$$10, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_3$$10, &_4$$10);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&compiledPath);
			ZVAL_STRING(&compiledPath, "");
		}
	}
	zephir_memory_observe(&compiledSeparator);
	if (!(zephir_array_isset_string_fetch(&compiledSeparator, &options, SL("separator"), 0))) {
		ZEPHIR_OBS_NVAR(&compiledSeparator);
		if (zephir_array_isset_string_fetch(&compiledSeparator, &options, SL("compiledSeparator"), 0)) {
			ZEPHIR_INIT_VAR(&_5$$13);
			ZVAL_STRING(&_5$$13, "The 'compiledSeparator' option is deprecated. Use 'separator' instead.");
			ZVAL_LONG(&_6$$13, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_5$$13, &_6$$13);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&compiledSeparator);
			ZVAL_STRING(&compiledSeparator, "%%");
		}
	}
	if (UNEXPECTED(Z_TYPE_P(&compiledSeparator) != IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'separator' must be a string", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 363);
		return;
	}
	zephir_memory_observe(&compiledExtension);
	if (!(zephir_array_isset_string_fetch(&compiledExtension, &options, SL("extension"), 0))) {
		ZEPHIR_OBS_NVAR(&compiledExtension);
		if (zephir_array_isset_string_fetch(&compiledExtension, &options, SL("compiledExtension"), 0)) {
			ZEPHIR_INIT_VAR(&_7$$17);
			ZVAL_STRING(&_7$$17, "The 'compiledExtension' option is deprecated. Use 'extension' instead.");
			ZVAL_LONG(&_8$$17, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_7$$17, &_8$$17);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&compiledExtension);
			ZVAL_STRING(&compiledExtension, ".php");
		}
	}
	if (UNEXPECTED(Z_TYPE_P(&compiledExtension) != IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'extension' must be a string", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 381);
		return;
	}
	zephir_memory_observe(&stat);
	if (!(zephir_array_isset_string_fetch(&stat, &options, SL("stat"), 0))) {
		ZEPHIR_INIT_NVAR(&stat);
		ZVAL_BOOL(&stat, 1);
	}
	if (Z_TYPE_P(&compiledPath) == IS_STRING) {
		if (!(ZEPHIR_IS_EMPTY(&compiledPath))) {
			ZEPHIR_CALL_FUNCTION(&_10$$22, "realpath", NULL, 80, &templatePath_zv);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&templateSepPath);
			zephir_prepare_virtual_path(&templateSepPath, &_10$$22, &compiledSeparator);
		} else {
			ZEPHIR_CPY_WRT(&templateSepPath, &templatePath_zv);
		}
		ZEPHIR_INIT_NVAR(&compiledTemplatePath);
		if (extendsMode) {
			ZEPHIR_CONCAT_VVVVSVV(&compiledTemplatePath, &compiledPath, &prefix, &templateSepPath, &compiledSeparator, "e", &compiledSeparator, &compiledExtension);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CONCAT_VVVV(&compiledTemplatePath, &compiledPath, &prefix, &templateSepPath, &compiledExtension);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	} else {
		_9 = Z_TYPE_P(&compiledPath) == IS_OBJECT;
		if (_9) {
			_9 = zephir_is_instance_of(&compiledPath, SL("Closure"));
		}
		if (_9) {
			ZEPHIR_INIT_VAR(&_11$$26);
			zephir_create_array(&_11$$26, 3, 0);
			zephir_array_fast_append(&_11$$26, &templatePath_zv);
			zephir_array_fast_append(&_11$$26, &options);
			ZEPHIR_INIT_VAR(&_12$$26);
			ZVAL_BOOL(&_12$$26, extendsMode);
			zephir_array_fast_append(&_11$$26, &_12$$26);
			ZEPHIR_INIT_NVAR(&compiledTemplatePath);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&compiledTemplatePath, &compiledPath, &_11$$26);
			zephir_check_call_status();
			if (UNEXPECTED(Z_TYPE_P(&compiledTemplatePath) != IS_STRING)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'path' closure didn't return a valid string", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 434);
				return;
			}
		} else {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'path' must be a string or a closure", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 439);
			return;
		}
	}
	_13 = !((zephir_file_exists(&compiledTemplatePath) == SUCCESS));
	if (!(_13)) {
		_13 = zephir_is_true(&compileAlways);
	}
	if (_13) {
		if (extendsMode) {
			ZVAL_BOOL(&_14$$29, 1);
		} else {
			ZVAL_BOOL(&_14$$29, 0);
		}
		ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileFile", NULL, 0, &templatePath_zv, &compiledTemplatePath, &_14$$29);
		zephir_check_call_status();
	} else {
		if (ZEPHIR_IS_TRUE_IDENTICAL(&stat)) {
			ZEPHIR_INIT_VAR(&_15$$31);
			if (zephir_compare_mtime(&templatePath_zv, &compiledTemplatePath)) {
				if (extendsMode) {
					ZVAL_BOOL(&_16$$32, 1);
				} else {
					ZVAL_BOOL(&_16$$32, 0);
				}
				ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileFile", NULL, 0, &templatePath_zv, &compiledTemplatePath, &_16$$32);
				zephir_check_call_status();
			} else {
				if (extendsMode) {
					ZEPHIR_INIT_VAR(&blocksCode);
					zephir_file_get_contents(&blocksCode, &compiledTemplatePath);
					if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&blocksCode))) {
						ZEPHIR_INIT_VAR(&_17$$35);
						object_init_ex(&_17$$35, phalcon_mvc_view_engine_volt_exception_ce);
						ZEPHIR_INIT_VAR(&_18$$35);
						ZEPHIR_CONCAT_SVS(&_18$$35, "Extends compilation file ", &compiledTemplatePath, " could not be opened");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_17$$35, "__construct", NULL, 0, &_18$$35);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_17$$35, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 478);
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (zephir_is_true(&blocksCode)) {
						ZEPHIR_CALL_FUNCTION(&compilation, "unserialize", NULL, 15, &blocksCode);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(&compilation);
						array_init(&compilation);
					}
				}
			}
		}
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 916, &compiledTemplatePath);
	RETURN_CCTOR(&compilation);
}

/**
 * Compiles a "autoescape" statement returning PHP code
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileAutoEscape)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL, autoescape, oldAutoescape, compilation, _0, _1;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&autoescape);
	ZVAL_UNDEF(&oldAutoescape);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("autoescape", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &statement_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&autoescape);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&autoescape, &statement, SL("enable"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 515);
		return;
	}
	zephir_memory_observe(&oldAutoescape);
	zephir_read_property_cached(&oldAutoescape, this_ptr, _zephir_prop_0, 917, PH_NOISY_CC);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 917, &autoescape);
	zephir_array_fetch_string(&_0, &statement, SL("block_statements"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 525);
	if (extendsMode) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_CALL_METHOD(&compilation, this_ptr, "statementList", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 917, &oldAutoescape);
	RETURN_CCTOR(&compilation);
}

/**
 * Compiles calls to macros
 *
 * @param array statement
 * @param bool extendsMode
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL;
	zval statement;

	ZVAL_UNDEF(&statement);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &statement_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	ZEPHIR_MM_RESTORE();
}

/**
 * Compiles a "case"/"default" clause returning PHP code
 *
 * @param array statement
 * @param bool caseClause
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileCase)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool caseClause;
	zval *statement_param = NULL, *caseClause_param = NULL, expr, _2, _0$$4, _1$$4;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(caseClause)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &caseClause_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	if (!caseClause_param) {
		caseClause = 1;
	} else {
		}
	if (UNEXPECTED(caseClause == 0)) {
		RETURN_MM_STRING("<?php default: ?>");
	}
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$4);
		object_init_ex(&_0$$4, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$4);
		ZVAL_STRING(&_1$$4, "Corrupt statement");
		ZEPHIR_CALL_METHOD(NULL, &_0$$4, "__construct", NULL, 0, &_1$$4, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 568);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php case ", &_2, ": ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a "do" statement returning PHP code
 *
 * @param array statement
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileDo)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, _0;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 592);
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php ", &_0, "; ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a {% raw %}`{{` `}}`{% endraw %} statement returning PHP code
 *
 * @param array statement
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileEcho)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, exprCode, name, _2, _7, _0$$3, _1$$3, _3$$4, _5$$4, _4$$5, _6$$6;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("autoescape", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "Corrupt statement");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &_1$$3, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 616);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	zephir_memory_observe(&_2);
	zephir_array_fetch_string(&_2, &expr, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 624);
	if (ZEPHIR_IS_LONG(&_2, 350)) {
		ZEPHIR_CALL_METHOD(&_3$$4, this_ptr, "isTagFactory", NULL, 0, &expr);
		zephir_check_call_status();
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_3$$4)) {
			ZVAL_BOOL(&_4$$5, 1);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", NULL, 0, &expr, &_4$$5);
			zephir_check_call_status();
		}
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 629);
		zephir_memory_observe(&_5$$4);
		zephir_array_fetch_string(&_5$$4, &name, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 630);
		if (ZEPHIR_IS_LONG(&_5$$4, 265)) {
			zephir_memory_observe(&_6$$6);
			zephir_array_fetch_string(&_6$$6, &name, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 635);
			if (ZEPHIR_IS_STRING(&_6$$6, "super")) {
				RETURN_CCTOR(&exprCode);
			}
		}
	}
	zephir_read_property_cached(&_7, this_ptr, _zephir_prop_0, 917, PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_7)) {
		ZEPHIR_CONCAT_SVS(return_value, "<?= $this->escaper->html(", &exprCode, ") ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SVS(return_value, "<?= ", &exprCode, " ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a "elseif" statement returning PHP code
 *
 * @param array statement
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileElseIf)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, _2, _0$$3, _1$$3;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "Corrupt statement");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &_1$$3, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 666);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php } elseif (", &_2, ") { ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a template into a file forcing the destination path
 *
 *```php
 * $compiler->compileFile(
 *     "views/layouts/main.volt",
 *     "views/layouts/main.volt.php"
 * );
 *```
 *
 * @param string path
 * @param string compiledPath
 * @param bool extendsMode
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string|array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileFile)
{
	zval _2$$4, _4$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _0;
	zval path_zv, compiledPath_zv, *extendsMode_param = NULL, viewCode, compilation, finalCompilation, _5, _6, _1$$4, _3$$5;
	zend_string *path = NULL, *compiledPath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&compiledPath_zv);
	ZVAL_UNDEF(&viewCode);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&finalCompilation);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$5);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentPath", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(path)
		Z_PARAM_STR(compiledPath)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		extendsMode_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	zephir_memory_observe(&compiledPath_zv);
	ZVAL_STR_COPY(&compiledPath_zv, compiledPath);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	_0 = ZEPHIR_IS_EQUAL(&path_zv, &compiledPath_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Template path and compilation template path cannot be the same", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 699);
		return;
	}
	if (UNEXPECTED(!((zephir_file_exists(&path_zv) == SUCCESS)))) {
		ZEPHIR_INIT_VAR(&_1$$4);
		object_init_ex(&_1$$4, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$4);
		ZEPHIR_CONCAT_SVS(&_2$$4, "Template file ", &path_zv, " does not exist");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", NULL, 0, &_2$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 706);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&viewCode);
	zephir_file_get_contents(&viewCode, &path_zv);
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&viewCode))) {
		ZEPHIR_INIT_VAR(&_3$$5);
		object_init_ex(&_3$$5, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_4$$5);
		ZEPHIR_CONCAT_SVS(&_4$$5, "Template file ", &path_zv, " could not be opened");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_3$$5, "__construct", NULL, 0, &_4$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$5, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 718);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 918, &path_zv);
	if (extendsMode) {
		ZVAL_BOOL(&_5, 1);
	} else {
		ZVAL_BOOL(&_5, 0);
	}
	ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileSource", NULL, 0, &viewCode, &_5);
	zephir_check_call_status();
	if (Z_TYPE_P(&compilation) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&finalCompilation, "serialize", NULL, 14, &compilation);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&finalCompilation, &compilation);
	}
	ZEPHIR_INIT_VAR(&_6);
	zephir_file_put_contents(&_6, &compiledPath_zv, &finalCompilation);
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&_6))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Volt directory can't be written", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 739);
		return;
	}
	RETURN_CCTOR(&compilation);
}

/**
 * Compiles a "foreach" intermediate code representation into plain PHP code
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileForeach)
{
	zval compilation;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _5$$4;
	zval *statement_param = NULL, *extendsMode_param = NULL, prefix, level, prefixLevel, expr, exprCode, bstatement, type, blockStatements, forElse, code, loopContext, iterator, key, ifExpr, variable, _7, *_0$$4, _1$$4, *_2$$4, _4$$4, _3$$7, _6$$10, _8$$11, _9$$11, _10$$11, _11$$11, _12$$11, _13$$11, _14$$11, _15$$11, _16$$11, _17$$13, _18$$14, _19$$15, _20$$15, _21$$17, _22$$17, _23$$17, _24$$17, _25$$17, _26$$17, _27$$18, _28$$22;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&prefixLevel);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&bstatement);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&blockStatements);
	ZVAL_UNDEF(&forElse);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&loopContext);
	ZVAL_UNDEF(&iterator);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&ifExpr);
	ZVAL_UNDEF(&variable);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_18$$14);
	ZVAL_UNDEF(&_19$$15);
	ZVAL_UNDEF(&_20$$15);
	ZVAL_UNDEF(&_21$$17);
	ZVAL_UNDEF(&_22$$17);
	ZVAL_UNDEF(&_23$$17);
	ZVAL_UNDEF(&_24$$17);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$18);
	ZVAL_UNDEF(&_28$$22);
	ZVAL_UNDEF(&compilation);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("foreachLevel", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("loopPointers", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	if (UNEXPECTED(!(zephir_array_isset_value_string(&statement, SL("expr"))))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 764);
		return;
	}
	ZEPHIR_INIT_VAR(&compilation);
	ZVAL_STRING(&compilation, "");
	ZEPHIR_INIT_VAR(&forElse);
	ZVAL_NULL(&forElse);
	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("foreachLevel")));
	ZEPHIR_CALL_METHOD(&prefix, this_ptr, "getUniquePrefix", NULL, 0);
	zephir_check_call_status();
	zephir_memory_observe(&level);
	zephir_read_property_cached(&level, this_ptr, _zephir_prop_0, 907, PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&prefixLevel);
	ZEPHIR_CONCAT_VV(&prefixLevel, &prefix, &level);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&expr);
	zephir_array_fetch_string(&expr, &statement, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 782);
	ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	zephir_memory_observe(&blockStatements);
	zephir_array_fetch_string(&blockStatements, &statement, SL("block_statements"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 788);
	ZEPHIR_INIT_NVAR(&forElse);
	ZVAL_BOOL(&forElse, 0);
	if (Z_TYPE_P(&blockStatements) == IS_ARRAY) {
		if (Z_TYPE_P(&blockStatements) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$4);
			zephir_string_to_char_array(&_1$$4, &blockStatements);
			_0$$4 = &_1$$4;
		} else {
			_0$$4 = &blockStatements;
		}
		zephir_is_iterable(_0$$4, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 808);
		if (Z_TYPE_P(_0$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$4), _2$$4)
			{
				ZEPHIR_INIT_NVAR(&bstatement);
				ZVAL_COPY(&bstatement, _2$$4);
				ZEPHIR_OBS_NVAR(&type);
				if (!(zephir_array_isset_string_fetch(&type, &bstatement, SL("type"), 0))) {
					break;
				}
				if (ZEPHIR_IS_LONG(&type, 321)) {
					ZEPHIR_INIT_NVAR(&_3$$7);
					ZEPHIR_CONCAT_SVS(&_3$$7, "<?php $", &prefixLevel, "iterated = false; ?>");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_3$$7);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CPY_WRT(&forElse, &prefixLevel);
					zephir_update_property_array(this_ptr, SL("forElsePointers"), &level, &forElse);
					break;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _0$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_5$$4 = 1;
			while (1) {
				if (_5$$4) {
					_5$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _0$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_4$$4, _0$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_4$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&bstatement, _0$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&type);
					if (!(zephir_array_isset_string_fetch(&type, &bstatement, SL("type"), 0))) {
						break;
					}
					if (ZEPHIR_IS_LONG(&type, 321)) {
						ZEPHIR_INIT_NVAR(&_6$$10);
						ZEPHIR_CONCAT_SVS(&_6$$10, "<?php $", &prefixLevel, "iterated = false; ?>");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&compilation, &_6$$10);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CPY_WRT(&forElse, &prefixLevel);
						zephir_update_property_array(this_ptr, SL("forElsePointers"), &level, &forElse);
						break;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&bstatement);
	}
	if (extendsMode) {
		ZVAL_BOOL(&_7, 1);
	} else {
		ZVAL_BOOL(&_7, 0);
	}
	ZEPHIR_CALL_METHOD(&code, this_ptr, "statementList", NULL, 0, &blockStatements, &_7);
	zephir_check_call_status();
	zephir_memory_observe(&loopContext);
	zephir_read_property_cached(&loopContext, this_ptr, _zephir_prop_1, 919, PH_NOISY_CC);
	if (zephir_array_isset_value(&loopContext, &level)) {
		ZEPHIR_INIT_VAR(&_8$$11);
		ZEPHIR_CONCAT_SVSVS(&_8$$11, "<?php $", &prefixLevel, "iterator = ", &exprCode, "; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_8$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_9$$11);
		ZEPHIR_CONCAT_SVS(&_9$$11, "$", &prefixLevel, "incr = 0; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_9$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_10$$11);
		ZEPHIR_CONCAT_SVS(&_10$$11, "$", &prefixLevel, "loop = new stdClass(); ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_10$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_11$$11);
		ZEPHIR_CONCAT_SVSVS(&_11$$11, "$", &prefixLevel, "loop->self = &$", &prefixLevel, "loop; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_11$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_12$$11);
		ZEPHIR_CONCAT_SVSVS(&_12$$11, "$", &prefixLevel, "loop->length = count($", &prefixLevel, "iterator); ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_12$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_13$$11);
		ZEPHIR_CONCAT_SVS(&_13$$11, "$", &prefixLevel, "loop->index = 1; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_13$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_14$$11);
		ZEPHIR_CONCAT_SVS(&_14$$11, "$", &prefixLevel, "loop->index0 = 1; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_14$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_15$$11);
		ZEPHIR_CONCAT_SVSVS(&_15$$11, "$", &prefixLevel, "loop->revindex = $", &prefixLevel, "loop->length; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_15$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_16$$11);
		ZEPHIR_CONCAT_SVSVS(&_16$$11, "$", &prefixLevel, "loop->revindex0 = $", &prefixLevel, "loop->length - 1; ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_16$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&iterator);
		ZEPHIR_CONCAT_SVS(&iterator, "$", &prefixLevel, "iterator");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CPY_WRT(&iterator, &exprCode);
	}
	zephir_memory_observe(&variable);
	zephir_array_fetch_string(&variable, &statement, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 838);
	zephir_memory_observe(&key);
	if (zephir_array_isset_string_fetch(&key, &statement, SL("key"), 0)) {
		ZEPHIR_INIT_VAR(&_17$$13);
		ZEPHIR_CONCAT_SVSVSVS(&_17$$13, "<?php foreach (", &iterator, " as $", &key, " => $", &variable, ") { ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_17$$13);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_VAR(&_18$$14);
		ZEPHIR_CONCAT_SVSVS(&_18$$14, "<?php foreach (", &iterator, " as $", &variable, ") { ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_18$$14);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_memory_observe(&ifExpr);
	if (zephir_array_isset_string_fetch(&ifExpr, &statement, SL("if_expr"), 0)) {
		ZEPHIR_CALL_METHOD(&_19$$15, this_ptr, "expression", NULL, 0, &ifExpr);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_20$$15);
		ZEPHIR_CONCAT_SVS(&_20$$15, "if (", &_19$$15, ") { ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_20$$15);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		zephir_concat_self_str(&compilation, "?>", sizeof("?>") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (zephir_array_isset_value(&loopContext, &level)) {
		ZEPHIR_INIT_VAR(&_21$$17);
		ZEPHIR_CONCAT_SVSVS(&_21$$17, "<?php $", &prefixLevel, "loop->first = ($", &prefixLevel, "incr == 0); ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_21$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_22$$17);
		ZEPHIR_CONCAT_SVSVS(&_22$$17, "$", &prefixLevel, "loop->index = $", &prefixLevel, "incr + 1; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_22$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_23$$17);
		ZEPHIR_CONCAT_SVSVS(&_23$$17, "$", &prefixLevel, "loop->index0 = $", &prefixLevel, "incr; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_23$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_24$$17);
		ZEPHIR_CONCAT_SVSVSVS(&_24$$17, "$", &prefixLevel, "loop->revindex = $", &prefixLevel, "loop->length - $", &prefixLevel, "incr; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_24$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_25$$17);
		ZEPHIR_CONCAT_SVSVSVS(&_25$$17, "$", &prefixLevel, "loop->revindex0 = $", &prefixLevel, "loop->length - ($", &prefixLevel, "incr + 1); ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_25$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_26$$17);
		ZEPHIR_CONCAT_SVSVSVS(&_26$$17, "$", &prefixLevel, "loop->last = ($", &prefixLevel, "incr == ($", &prefixLevel, "loop->length - 1)); ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_26$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(&forElse) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_27$$18);
		ZEPHIR_CONCAT_SVS(&_27$$18, "<?php $", &forElse, "iterated = true; ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_27$$18);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_concat_self(&compilation, &code);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_array_isset_value_string(&statement, SL("if_expr"))) {
		zephir_concat_self_str(&compilation, "<?php } ?>", sizeof("<?php } ?>") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(&forElse) == IS_STRING) {
		zephir_concat_self_str(&compilation, "<?php } ?>", sizeof("<?php } ?>") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		if (zephir_array_isset_value(&loopContext, &level)) {
			ZEPHIR_INIT_VAR(&_28$$22);
			ZEPHIR_CONCAT_SVS(&_28$$22, "<?php $", &prefixLevel, "incr++; } ?>");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&compilation, &_28$$22);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_concat_self_str(&compilation, "<?php } ?>", sizeof("<?php } ?>") - 1);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("foreachLevel")));
	RETURN_CTOR(&compilation);
}

/**
 * Generates a 'forelse' PHP code
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileForElse)
{
	zval level, prefix, _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("foreachLevel", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("forElsePointers", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("loopPointers", 12, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&level);
	zephir_read_property_cached(&level, this_ptr, _zephir_prop_0, 907, PH_NOISY_CC);
	zephir_memory_observe(&prefix);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 920, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&prefix, &_0, &level, 0))) {
		RETURN_MM_STRING("");
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_2, 919, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_value(&_1, &level)) {
		ZEPHIR_CONCAT_SVSVS(return_value, "<?php $", &prefix, "incr++; } if (!$", &prefix, "iterated) { ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SVS(return_value, "<?php } if (!$", &prefix, "iterated) { ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a 'if' statement returning PHP code
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileIf)
{
	zval compilation;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL, blockStatements, expr, _2, _3, _4, _5, _6, _0$$3, _1$$3, _7$$4, _8$$4, _9$$4;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&blockStatements);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&compilation);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "Corrupt statement");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &_1$$3, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 941);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	zephir_array_fetch_string(&_4, &statement, SL("true_statements"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 947);
	if (extendsMode) {
		ZVAL_BOOL(&_5, 1);
	} else {
		ZVAL_BOOL(&_5, 0);
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "statementList", NULL, 0, &_4, &_5);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SVSV(&_6, "<?php if (", &_2, ") { ?>", &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&compilation, &_6);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&blockStatements);
	if (zephir_array_isset_string_fetch(&blockStatements, &statement, SL("false_statements"), 0)) {
		if (extendsMode) {
			ZVAL_BOOL(&_8$$4, 1);
		} else {
			ZVAL_BOOL(&_8$$4, 0);
		}
		ZEPHIR_CALL_METHOD(&_7$$4, this_ptr, "statementList", NULL, 0, &blockStatements, &_8$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_9$$4);
		ZEPHIR_CONCAT_SV(&_9$$4, "<?php } else { ?>", &_7$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_9$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_concat_self_str(&compilation, "<?php } ?>", sizeof("<?php } ?>") - 1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&compilation);
}

/**
 * Compiles a 'include' statement returning PHP code
 *
 * @param array statement
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileInclude)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, pathExpr, path, subCompiler, finalPath, compilation, params, _0, _3, _1$$5, _2$$6;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&pathExpr);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&subCompiler);
	ZVAL_UNDEF(&finalPath);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$6);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&pathExpr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&pathExpr, &statement, SL("path"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 981);
		return;
	}
	zephir_memory_observe(&_0);
	zephir_array_fetch_string(&_0, &pathExpr, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 988);
	if (ZEPHIR_IS_LONG(&_0, 260)) {
		if (!(zephir_array_isset_value_string(&statement, SL("params")))) {
			zephir_memory_observe(&path);
			zephir_array_fetch_string(&path, &pathExpr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 997);
			ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", NULL, 0, &path);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&subCompiler);
			if (zephir_clone(&subCompiler, this_ptr) == FAILURE) {
				RETURN_MM();
			}
			ZVAL_BOOL(&_1$$5, 0);
			ZEPHIR_CALL_METHOD(&compilation, &subCompiler, "compile", NULL, 0, &finalPath, &_1$$5);
			zephir_check_call_status();
			if (Z_TYPE_P(&compilation) == IS_NULL) {
				ZEPHIR_CALL_METHOD(&_2$$6, &subCompiler, "getCompiledTemplatePath", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&compilation);
				zephir_file_get_contents(&compilation, &_2$$6);
			}
			RETURN_CCTOR(&compilation);
		}
	}
	ZEPHIR_CALL_METHOD(&path, this_ptr, "expression", NULL, 0, &pathExpr);
	zephir_check_call_status();
	zephir_memory_observe(&params);
	if (!(zephir_array_isset_string_fetch(&params, &statement, SL("params"), 0))) {
		ZEPHIR_CONCAT_SVS(return_value, "<?php $this->partial(", &path, "); ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "expression", NULL, 0, &params);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "<?php $this->partial(", &path, ", ", &_3, "); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles macros
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileMacro)
{
	zend_string *_10$$6;
	zend_ulong _9$$6;
	zval code, macroName, _31, _4$$5, _5$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_16 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _20$$6;
	zval *statement_param = NULL, *extendsMode_param = NULL, name, defaultValue, parameters, position, parameter, variableName, blockStatements, _0, _3, _1$$4, _2$$4, *_6$$6, _7$$6, *_8$$6, _19$$6, _11$$7, _12$$7, _13$$7, _14$$7, _15$$8, _17$$8, _18$$9, _21$$10, _22$$10, _23$$10, _24$$10, _25$$11, _26$$11, _27$$12, _28$$13, _29$$13, _30$$13;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&parameter);
	ZVAL_UNDEF(&variableName);
	ZVAL_UNDEF(&blockStatements);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_21$$10);
	ZVAL_UNDEF(&_22$$10);
	ZVAL_UNDEF(&_23$$10);
	ZVAL_UNDEF(&_24$$10);
	ZVAL_UNDEF(&_25$$11);
	ZVAL_UNDEF(&_26$$11);
	ZVAL_UNDEF(&_27$$12);
	ZVAL_UNDEF(&_28$$13);
	ZVAL_UNDEF(&_29$$13);
	ZVAL_UNDEF(&_30$$13);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&macroName);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("macros", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &statement_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&name);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&name, &statement, SL("name"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1056);
		return;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 921, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(zephir_array_isset_value(&_0, &name))) {
		ZEPHIR_INIT_VAR(&_1$$4);
		object_init_ex(&_1$$4, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$4);
		ZEPHIR_CONCAT_SVS(&_2$$4, "Macro '", &name, "' is already defined");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", NULL, 0, &_2$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1063);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_array(this_ptr, SL("macros"), &name, &name);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SVS(&_3, "$this->macros['", &name, "']");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&macroName, &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&code);
	ZVAL_STRING(&code, "<?php ");
	zephir_memory_observe(&parameters);
	if (!(zephir_array_isset_string_fetch(&parameters, &statement, SL("parameters"), 0))) {
		ZEPHIR_INIT_VAR(&_4$$5);
		ZEPHIR_CONCAT_VS(&_4$$5, &macroName, " = function() { ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&code, &_4$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_VS(&_5$$6, &macroName, " = function($__p = null) { ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&code, &_5$$6);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (Z_TYPE_P(&parameters) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_7$$6);
			zephir_string_to_char_array(&_7$$6, &parameters);
			_6$$6 = &_7$$6;
		} else {
			_6$$6 = &parameters;
		}
		zephir_is_iterable(_6$$6, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1100);
		if (Z_TYPE_P(_6$$6) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_6$$6), _9$$6, _10$$6, _8$$6)
			{
				ZEPHIR_INIT_NVAR(&position);
				if (_10$$6 != NULL) { 
					ZVAL_STR_COPY(&position, _10$$6);
				} else {
					ZVAL_LONG(&position, _9$$6);
				}
				ZEPHIR_INIT_NVAR(&parameter);
				ZVAL_COPY(&parameter, _8$$6);
				ZEPHIR_OBS_NVAR(&variableName);
				zephir_array_fetch_string(&variableName, &parameter, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1082);
				ZEPHIR_INIT_NVAR(&_11$$7);
				ZEPHIR_CONCAT_SVS(&_11$$7, "if (isset($__p[", &position, "])) { ");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&code, &_11$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_12$$7);
				ZEPHIR_CONCAT_SVSVS(&_12$$7, "$", &variableName, " = $__p[", &position, "];");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&code, &_12$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self_str(&code, " } else { ", sizeof(" } else { ") - 1);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_13$$7);
				ZEPHIR_CONCAT_SVS(&_13$$7, "if (array_key_exists(\"", &variableName, "\", $__p)) { ");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&code, &_13$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_14$$7);
				ZEPHIR_CONCAT_SVSVS(&_14$$7, "$", &variableName, " = $__p[\"", &variableName, "\"];");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&code, &_14$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self_str(&code, " } else { ", sizeof(" } else { ") - 1);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_OBS_NVAR(&defaultValue);
				if (EXPECTED(zephir_array_isset_string_fetch(&defaultValue, &parameter, SL("default"), 0))) {
					ZEPHIR_CALL_METHOD(&_15$$8, this_ptr, "expression", &_16, 0, &defaultValue);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_17$$8);
					ZEPHIR_CONCAT_SVSVS(&_17$$8, "$", &variableName, " = ", &_15$$8, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&code, &_17$$8);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_INIT_NVAR(&_18$$9);
					ZEPHIR_CONCAT_SVSVS(&_18$$9, " throw new \\Phalcon\\Mvc\\View\\Exception(\"Macro '", &name, "' was called without parameter: ", &variableName, "\"); ");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&code, &_18$$9);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				zephir_concat_self_str(&code, " } } ", sizeof(" } } ") - 1);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _6$$6, "rewind", NULL, 0);
			zephir_check_call_status();
			_20$$6 = 1;
			while (1) {
				if (_20$$6) {
					_20$$6 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _6$$6, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_19$$6, _6$$6, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_19$$6)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&position, _6$$6, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&parameter, _6$$6, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&variableName);
					zephir_array_fetch_string(&variableName, &parameter, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1082);
					ZEPHIR_INIT_NVAR(&_21$$10);
					ZEPHIR_CONCAT_SVS(&_21$$10, "if (isset($__p[", &position, "])) { ");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&code, &_21$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_22$$10);
					ZEPHIR_CONCAT_SVSVS(&_22$$10, "$", &variableName, " = $__p[", &position, "];");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&code, &_22$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self_str(&code, " } else { ", sizeof(" } else { ") - 1);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_23$$10);
					ZEPHIR_CONCAT_SVS(&_23$$10, "if (array_key_exists(\"", &variableName, "\", $__p)) { ");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&code, &_23$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_24$$10);
					ZEPHIR_CONCAT_SVSVS(&_24$$10, "$", &variableName, " = $__p[\"", &variableName, "\"];");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&code, &_24$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self_str(&code, " } else { ", sizeof(" } else { ") - 1);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&defaultValue);
					if (EXPECTED(zephir_array_isset_string_fetch(&defaultValue, &parameter, SL("default"), 0))) {
						ZEPHIR_CALL_METHOD(&_25$$11, this_ptr, "expression", &_16, 0, &defaultValue);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_26$$11);
						ZEPHIR_CONCAT_SVSVS(&_26$$11, "$", &variableName, " = ", &_25$$11, ";");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&code, &_26$$11);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_INIT_NVAR(&_27$$12);
						ZEPHIR_CONCAT_SVSVS(&_27$$12, " throw new \\Phalcon\\Mvc\\View\\Exception(\"Macro '", &name, "' was called without parameter: ", &variableName, "\"); ");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&code, &_27$$12);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					zephir_concat_self_str(&code, " } } ", sizeof(" } } ") - 1);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&parameter);
		ZEPHIR_INIT_NVAR(&position);
		zephir_concat_self_str(&code, " ?>", sizeof(" ?>") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_memory_observe(&blockStatements);
	if (zephir_array_isset_string_fetch(&blockStatements, &statement, SL("block_statements"), 0)) {
		if (extendsMode) {
			ZVAL_BOOL(&_29$$13, 1);
		} else {
			ZVAL_BOOL(&_29$$13, 0);
		}
		ZEPHIR_CALL_METHOD(&_28$$13, this_ptr, "statementList", NULL, 0, &blockStatements, &_29$$13);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_30$$13);
		ZEPHIR_CONCAT_VS(&_30$$13, &_28$$13, "<?php }; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&code, &_30$$13);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		zephir_concat_self_str(&code, "<?php }; ", sizeof("<?php }; ") - 1);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_INIT_VAR(&_31);
	ZEPHIR_CONCAT_VSVS(&_31, &macroName, " = \\Closure::bind(", &macroName, ", $this); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_concat_self(&code, &_31);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&code);
}

/**
 * Compiles a "return" statement returning PHP code
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileReturn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, _0;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1137);
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php return ", &_0, "; ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a "set" statement returning PHP code. The method accepts an
 * array produced by the Volt parser and creates the `set` statement in PHP.
 * This method is not particularly useful in development, since it requires
 * advanced knowledge of the Volt parser.
 *
 * ```php
 * <?php
 *
 * use Phalcon\Mvc\View\Engine\Volt\Compiler;
 *
 * $compiler = new Compiler();
 *
 * // {% set a = ['first': 1] %}

 * $source = [
 *     "type" => 306,
 *     "assignments" => [
 *         [
 *             "variable" => [
 *                 "type" => 265,
 *                 "value" => "a",
 *                 "file" => "eval code",
 *                 "line" => 1
 *             ],
 *             "op" => 61,
 *             "expr" => [
 *                 "type" => 360,
 *                 "left" => [
 *                     [
 *                         "expr" => [
 *                             "type" => 258,
 *                             "value" => "1",
 *                             "file" => "eval code",
 *                             "line" => 1
 *                         ],
 *                         "name" => "first",
 *                         "file" => "eval code",
 *                         "line" => 1
 *                     ]
 *                 ],
 *                 "file" => "eval code",
 *                 "line" => 1
 *             ],
 *             "file" => "eval code",
 *             "line" => 1
 *         ]
 *     ]
 * ];
 *
 * echo $compiler->compileSet($source);
 * // <?php $a = ['first' => 1]; ?>";
 * ```
 *
 * @param array $statement
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSet)
{
	zend_bool _13;
	zval compilation;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, assignments, assignment, exprCode, target, *_0, _1, *_2, _12, _3$$4, _5$$4, _6$$4, _7$$5, _8$$6, _9$$7, _10$$8, _11$$9, _14$$10, _15$$10, _16$$10, _17$$11, _18$$12, _19$$13, _20$$14, _21$$15;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&assignments);
	ZVAL_UNDEF(&assignment);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&target);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_19$$13);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&compilation);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	zephir_memory_observe(&assignments);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&assignments, &statement, SL("assignments"), 0)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1214);
		return;
	}
	ZEPHIR_INIT_VAR(&compilation);
	ZVAL_STRING(&compilation, "<?php");
	if (Z_TYPE_P(&assignments) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_1);
		zephir_string_to_char_array(&_1, &assignments);
		_0 = &_1;
	} else {
		_0 = &assignments;
	}
	zephir_is_iterable(_0, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1263);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0), _2)
		{
			ZEPHIR_INIT_NVAR(&assignment);
			ZVAL_COPY(&assignment, _2);
			ZEPHIR_OBS_NVAR(&_3$$4);
			zephir_array_fetch_string(&_3$$4, &assignment, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1225);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", &_4, 0, &_3$$4);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_5$$4);
			zephir_array_fetch_string(&_5$$4, &assignment, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1232);
			ZEPHIR_CALL_METHOD(&target, this_ptr, "expression", &_4, 0, &_5$$4);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_6$$4);
			zephir_array_fetch_string(&_6$$4, &assignment, SL("op"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1238);
			if (ZEPHIR_IS_LONG(&_6$$4, 281)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&_6$$4, 282)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&_6$$4, 283)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&_6$$4, 284)) { goto zephir_switch_0_clause_3; }
			goto zephir_switch_0_clause_4;
			zephir_switch_0_clause_0: ;
				ZEPHIR_INIT_NVAR(&_7$$5);
				ZEPHIR_CONCAT_SVSVS(&_7$$5, " ", &target, " += ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_7$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				ZEPHIR_INIT_NVAR(&_8$$6);
				ZEPHIR_CONCAT_SVSVS(&_8$$6, " ", &target, " -= ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_8$$6);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
				ZEPHIR_INIT_NVAR(&_9$$7);
				ZEPHIR_CONCAT_SVSVS(&_9$$7, " ", &target, " *= ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_9$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_NVAR(&_10$$8);
				ZEPHIR_CONCAT_SVSVS(&_10$$8, " ", &target, " /= ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_10$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_INIT_NVAR(&_11$$9);
				ZEPHIR_CONCAT_SVSVS(&_11$$9, " ", &target, " = ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_11$$9);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_end: ;

		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _0, "rewind", NULL, 0);
		zephir_check_call_status();
		_13 = 1;
		while (1) {
			if (_13) {
				_13 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_12, _0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_12)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&assignment, _0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_14$$10);
				zephir_array_fetch_string(&_14$$10, &assignment, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1225);
				ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", &_4, 0, &_14$$10);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_15$$10);
				zephir_array_fetch_string(&_15$$10, &assignment, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1232);
				ZEPHIR_CALL_METHOD(&target, this_ptr, "expression", &_4, 0, &_15$$10);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_16$$10);
				zephir_array_fetch_string(&_16$$10, &assignment, SL("op"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1238);
				if (ZEPHIR_IS_LONG(&_16$$10, 281)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&_16$$10, 282)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&_16$$10, 283)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&_16$$10, 284)) { goto zephir_switch_1_clause_3; }
				goto zephir_switch_1_clause_4;
				zephir_switch_1_clause_0: ;
					ZEPHIR_INIT_NVAR(&_17$$11);
					ZEPHIR_CONCAT_SVSVS(&_17$$11, " ", &target, " += ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_17$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					ZEPHIR_INIT_NVAR(&_18$$12);
					ZEPHIR_CONCAT_SVSVS(&_18$$12, " ", &target, " -= ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_18$$12);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_2: ;
					ZEPHIR_INIT_NVAR(&_19$$13);
					ZEPHIR_CONCAT_SVSVS(&_19$$13, " ", &target, " *= ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_19$$13);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_NVAR(&_20$$14);
					ZEPHIR_CONCAT_SVSVS(&_20$$14, " ", &target, " /= ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_20$$14);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_INIT_NVAR(&_21$$15);
					ZEPHIR_CONCAT_SVSVS(&_21$$15, " ", &target, " = ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_21$$15);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_end: ;

		}
	}
	ZEPHIR_INIT_NVAR(&assignment);
	zephir_concat_self_str(&compilation, " ?>", sizeof(" ?>") - 1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&compilation);
}

/**
 * Compiles a template into a string
 *
 *```php
 * echo $compiler->compileString({% raw %}'{{ "hello world" }}'{% endraw %});
 *```
 *
 * @param string viewCode
 * @param bool extendsMode
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval viewCode_zv, *extendsMode_param = NULL, _0, _1;
	zend_string *viewCode = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewCode_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentPath", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(viewCode)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		extendsMode_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&viewCode_zv);
	ZVAL_STR_COPY(&viewCode_zv, viewCode);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "eval code");
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 918, &_0);
	if (extendsMode) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "compileSource", NULL, 0, &viewCode_zv, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compiles a 'switch' statement returning PHP code
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSwitch)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL, compilation, caseClauses, expr, lines, _2, _0$$3, _1$$3, _3$$4, _4$$5, _5$$5, _6$$5;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&caseClauses);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&lines);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statement, statement_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "Corrupt statement");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &_1$$3, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1304);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&compilation);
	ZEPHIR_CONCAT_SVS(&compilation, "<?php switch (", &_2, "): ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&caseClauses);
	if (zephir_array_isset_string_fetch(&caseClauses, &statement, SL("case_clauses"), 0)) {
		if (extendsMode) {
			ZVAL_BOOL(&_3$$4, 1);
		} else {
			ZVAL_BOOL(&_3$$4, 0);
		}
		ZEPHIR_CALL_METHOD(&lines, this_ptr, "statementList", NULL, 0, &caseClauses, &_3$$4);
		zephir_check_call_status();
		if (zephir_fast_strlen_ev(&lines) != 0) {
			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "/(*ANYCRLF)^\\h+|\\h+$|(\\h){2,}/mu");
			ZEPHIR_INIT_VAR(&_5$$5);
			ZVAL_STRING(&_5$$5, "");
			ZEPHIR_CALL_FUNCTION(&_6$$5, "preg_replace", NULL, 40, &_4$$5, &_5$$5, &lines);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&lines, &_6$$5);
		}
		zephir_concat_self(&compilation, &lines);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_concat_self_str(&compilation, SL("<?php endswitch ?>"));
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(&compilation);
}

/**
 * Resolves an expression node in an AST volt tree
 *
 * @param array $expr
 * @param bool  $doubleQuotes
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, expression)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_7 = NULL, *_14 = NULL, *_17 = NULL, *_19 = NULL, *_28 = NULL, *_38 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool doubleQuotes, _10$$6;
	zval *expr_param = NULL, *doubleQuotes_param = NULL, end, endCode, exprCode, extensions, items, left, leftCode, name, right, rightCode, singleExpr, singleExprCode, start, startCode, type, _0, _2$$4, *_4$$6, _9$$6, _5$$7, _6$$7, _8$$8, _11$$10, _12$$10, _13$$11, _15$$14, _16$$15, _18$$16, _20$$17, _21$$35, _22$$35, _23$$35, _24$$35, _25$$36, _26$$40, _27$$50, _29$$54, _30$$56, _31$$74, _32$$74, _33$$74, _34$$78, _35$$78, _36$$78, _37$$78;
	zval expr, _1$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&end);
	ZVAL_UNDEF(&endCode);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&items);
	ZVAL_UNDEF(&left);
	ZVAL_UNDEF(&leftCode);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&rightCode);
	ZVAL_UNDEF(&singleExpr);
	ZVAL_UNDEF(&singleExprCode);
	ZVAL_UNDEF(&start);
	ZVAL_UNDEF(&startCode);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_15$$14);
	ZVAL_UNDEF(&_16$$15);
	ZVAL_UNDEF(&_18$$16);
	ZVAL_UNDEF(&_20$$17);
	ZVAL_UNDEF(&_21$$35);
	ZVAL_UNDEF(&_22$$35);
	ZVAL_UNDEF(&_23$$35);
	ZVAL_UNDEF(&_24$$35);
	ZVAL_UNDEF(&_25$$36);
	ZVAL_UNDEF(&_26$$40);
	ZVAL_UNDEF(&_27$$50);
	ZVAL_UNDEF(&_29$$54);
	ZVAL_UNDEF(&_30$$56);
	ZVAL_UNDEF(&_31$$74);
	ZVAL_UNDEF(&_32$$74);
	ZVAL_UNDEF(&_33$$74);
	ZVAL_UNDEF(&_34$$78);
	ZVAL_UNDEF(&_35$$78);
	ZVAL_UNDEF(&_36$$78);
	ZVAL_UNDEF(&_37$$78);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extensions", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(doubleQuotes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &expr_param, &doubleQuotes_param);
	ZEPHIR_OBS_COPY_OR_DUP(&expr, expr_param);
	if (!doubleQuotes_param) {
		doubleQuotes = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&leftCode);
	ZEPHIR_INIT_VAR(&rightCode);
	ZEPHIR_INIT_VAR(&exprCode);
	ZVAL_NULL(&exprCode);
	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("exprLevel")));
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 922, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_0);
	while (1) {
		if (Z_TYPE_P(&extensions) == IS_ARRAY) {
			ZEPHIR_INIT_NVAR(&_1$$4);
			zephir_create_array(&_1$$4, 1, 0);
			zephir_array_fast_append(&_1$$4, &expr);
			ZEPHIR_INIT_NVAR(&_2$$4);
			ZVAL_STRING(&_2$$4, "resolveExpression");
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "fireExtensionEvent", &_3, 0, &_2$$4, &_1$$4);
			zephir_check_call_status();
			if (Z_TYPE_P(&exprCode) == IS_STRING) {
				break;
			}
		}
		ZEPHIR_OBS_NVAR(&type);
		if (!(zephir_array_isset_string_fetch(&type, &expr, SL("type"), 0))) {
			ZEPHIR_INIT_NVAR(&items);
			array_init(&items);
			zephir_is_iterable(&expr, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1403);
			if (Z_TYPE_P(&expr) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&expr), _4$$6)
				{
					ZEPHIR_INIT_NVAR(&singleExpr);
					ZVAL_COPY(&singleExpr, _4$$6);
					ZEPHIR_OBS_NVAR(&_5$$7);
					zephir_array_fetch_string(&_5$$7, &singleExpr, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1392);
					if (doubleQuotes) {
						ZVAL_BOOL(&_6$$7, 1);
					} else {
						ZVAL_BOOL(&_6$$7, 0);
					}
					ZEPHIR_CALL_METHOD(&singleExprCode, this_ptr, "expression", &_7, 0, &_5$$7, &_6$$7);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&name);
					if (zephir_array_isset_string_fetch(&name, &singleExpr, SL("name"), 0)) {
						ZEPHIR_INIT_NVAR(&_8$$8);
						ZEPHIR_CONCAT_SVSV(&_8$$8, "'", &name, "' => ", &singleExprCode);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&items, &_8$$8, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1397);
					} else {
						zephir_array_append(&items, &singleExprCode, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1399);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &expr, "rewind", NULL, 0);
				zephir_check_call_status();
				_10$$6 = 1;
				while (1) {
					if (_10$$6) {
						_10$$6 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, &expr, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_9$$6, &expr, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$6)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&singleExpr, &expr, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&_11$$10);
						zephir_array_fetch_string(&_11$$10, &singleExpr, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1392);
						if (doubleQuotes) {
							ZVAL_BOOL(&_12$$10, 1);
						} else {
							ZVAL_BOOL(&_12$$10, 0);
						}
						ZEPHIR_CALL_METHOD(&singleExprCode, this_ptr, "expression", &_7, 0, &_11$$10, &_12$$10);
						zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&name);
						if (zephir_array_isset_string_fetch(&name, &singleExpr, SL("name"), 0)) {
							ZEPHIR_INIT_NVAR(&_13$$11);
							ZEPHIR_CONCAT_SVSV(&_13$$11, "'", &name, "' => ", &singleExprCode);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&items, &_13$$11, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1397);
						} else {
							zephir_array_append(&items, &singleExprCode, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1399);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&singleExpr);
			ZEPHIR_INIT_NVAR(&exprCode);
			zephir_fast_join_str(&exprCode, SL(", "), &items);
			break;
		}
		if (ZEPHIR_IS_LONG(&type, '.')) {
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "attributeReader", &_14, 0, &expr);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_OBS_NVAR(&left);
		if (zephir_array_isset_string_fetch(&left, &expr, SL("left"), 0)) {
			if (doubleQuotes) {
				ZVAL_BOOL(&_15$$14, 1);
			} else {
				ZVAL_BOOL(&_15$$14, 0);
			}
			ZEPHIR_CALL_METHOD(&leftCode, this_ptr, "expression", &_7, 0, &left, &_15$$14);
			zephir_check_call_status();
		}
		if (ZEPHIR_IS_LONG(&type, 311)) {
			ZEPHIR_OBS_NVAR(&_16$$15);
			zephir_array_fetch_string(&_16$$15, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1429);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "resolveTest", &_17, 0, &_16$$15, &leftCode);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_LONG(&type, 124)) {
			ZEPHIR_OBS_NVAR(&_18$$16);
			zephir_array_fetch_string(&_18$$16, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1441);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "resolveFilter", &_19, 0, &_18$$16, &leftCode);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_OBS_NVAR(&right);
		if (zephir_array_isset_string_fetch(&right, &expr, SL("right"), 0)) {
			if (doubleQuotes) {
				ZVAL_BOOL(&_20$$17, 1);
			} else {
				ZVAL_BOOL(&_20$$17, 0);
			}
			ZEPHIR_CALL_METHOD(&rightCode, this_ptr, "expression", &_7, 0, &right, &_20$$17);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(&exprCode);
		ZVAL_NULL(&exprCode);
		if (ZEPHIR_IS_LONG(&type, '!')) { goto zephir_switch_0_clause_0; }
		if (ZEPHIR_IS_LONG(&type, '*')) { goto zephir_switch_0_clause_1; }
		if (ZEPHIR_IS_LONG(&type, '+')) { goto zephir_switch_0_clause_2; }
		if (ZEPHIR_IS_LONG(&type, '-')) { goto zephir_switch_0_clause_3; }
		if (ZEPHIR_IS_LONG(&type, '/')) { goto zephir_switch_0_clause_4; }
		if (ZEPHIR_IS_LONG(&type, 37)) { goto zephir_switch_0_clause_5; }
		if (ZEPHIR_IS_LONG(&type, '<')) { goto zephir_switch_0_clause_6; }
		if (ZEPHIR_IS_LONG(&type, 61)) { goto zephir_switch_0_clause_7; }
		if (ZEPHIR_IS_LONG(&type, 62)) { goto zephir_switch_0_clause_8; }
		if (ZEPHIR_IS_LONG(&type, 126)) { goto zephir_switch_0_clause_9; }
		if (ZEPHIR_IS_LONG(&type, 278)) { goto zephir_switch_0_clause_10; }
		if (ZEPHIR_IS_LONG(&type, 360)) { goto zephir_switch_0_clause_11; }
		if (ZEPHIR_IS_LONG(&type, 258)) { goto zephir_switch_0_clause_12; }
		if (ZEPHIR_IS_LONG(&type, 259)) { goto zephir_switch_0_clause_13; }
		if (ZEPHIR_IS_LONG(&type, 260)) { goto zephir_switch_0_clause_14; }
		if (ZEPHIR_IS_LONG(&type, 261)) { goto zephir_switch_0_clause_15; }
		if (ZEPHIR_IS_LONG(&type, 262)) { goto zephir_switch_0_clause_16; }
		if (ZEPHIR_IS_LONG(&type, 263)) { goto zephir_switch_0_clause_17; }
		if (ZEPHIR_IS_LONG(&type, 265)) { goto zephir_switch_0_clause_18; }
		if (ZEPHIR_IS_LONG(&type, 266)) { goto zephir_switch_0_clause_19; }
		if (ZEPHIR_IS_LONG(&type, 267)) { goto zephir_switch_0_clause_20; }
		if (ZEPHIR_IS_LONG(&type, 270)) { goto zephir_switch_0_clause_21; }
		if (ZEPHIR_IS_LONG(&type, 271)) { goto zephir_switch_0_clause_22; }
		if (ZEPHIR_IS_LONG(&type, 272)) { goto zephir_switch_0_clause_23; }
		if (ZEPHIR_IS_LONG(&type, 273)) { goto zephir_switch_0_clause_24; }
		if (ZEPHIR_IS_LONG(&type, 274)) { goto zephir_switch_0_clause_25; }
		if (ZEPHIR_IS_LONG(&type, 275)) { goto zephir_switch_0_clause_26; }
		if (ZEPHIR_IS_LONG(&type, 276)) { goto zephir_switch_0_clause_27; }
		if (ZEPHIR_IS_LONG(&type, 350)) { goto zephir_switch_0_clause_28; }
		if (ZEPHIR_IS_LONG(&type, 356)) { goto zephir_switch_0_clause_29; }
		if (ZEPHIR_IS_LONG(&type, 361)) { goto zephir_switch_0_clause_30; }
		if (ZEPHIR_IS_LONG(&type, 365)) { goto zephir_switch_0_clause_31; }
		if (ZEPHIR_IS_LONG(&type, 362)) { goto zephir_switch_0_clause_32; }
		if (ZEPHIR_IS_LONG(&type, 363)) { goto zephir_switch_0_clause_33; }
		if (ZEPHIR_IS_LONG(&type, 392)) { goto zephir_switch_0_clause_34; }
		if (ZEPHIR_IS_LONG(&type, 386)) { goto zephir_switch_0_clause_35; }
		if (ZEPHIR_IS_LONG(&type, 393)) { goto zephir_switch_0_clause_36; }
		if (ZEPHIR_IS_LONG(&type, 387)) { goto zephir_switch_0_clause_37; }
		if (ZEPHIR_IS_LONG(&type, 394)) { goto zephir_switch_0_clause_38; }
		if (ZEPHIR_IS_LONG(&type, 388)) { goto zephir_switch_0_clause_39; }
		if (ZEPHIR_IS_LONG(&type, 395)) { goto zephir_switch_0_clause_40; }
		if (ZEPHIR_IS_LONG(&type, 389)) { goto zephir_switch_0_clause_41; }
		if (ZEPHIR_IS_LONG(&type, 396)) { goto zephir_switch_0_clause_42; }
		if (ZEPHIR_IS_LONG(&type, 390)) { goto zephir_switch_0_clause_43; }
		if (ZEPHIR_IS_LONG(&type, 397)) { goto zephir_switch_0_clause_44; }
		if (ZEPHIR_IS_LONG(&type, 391)) { goto zephir_switch_0_clause_45; }
		if (ZEPHIR_IS_LONG(&type, 309)) { goto zephir_switch_0_clause_46; }
		if (ZEPHIR_IS_LONG(&type, 367)) { goto zephir_switch_0_clause_47; }
		if (ZEPHIR_IS_LONG(&type, 366)) { goto zephir_switch_0_clause_48; }
		if (ZEPHIR_IS_LONG(&type, 368)) { goto zephir_switch_0_clause_49; }
		if (ZEPHIR_IS_LONG(&type, 369)) { goto zephir_switch_0_clause_50; }
		if (ZEPHIR_IS_LONG(&type, 364)) { goto zephir_switch_0_clause_51; }
		goto zephir_switch_0_clause_52;
		zephir_switch_0_clause_0: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SV(&exprCode, "!", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_1: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " * ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_2: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " + ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_3: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " - ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_4: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " / ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_5: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " % ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_6: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " < ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_7: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " > ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_8: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " > ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_9: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " . ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_10: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "pow(", &leftCode, ", ", &rightCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_11: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			if (zephir_array_isset_value_string(&expr, SL("left"))) {
				ZEPHIR_CONCAT_SVS(&exprCode, "[", &leftCode, "]");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZVAL_STRING(&exprCode, "[]");
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_12: ;
			ZEPHIR_OBS_NVAR(&exprCode);
			zephir_array_fetch_string(&exprCode, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1512);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_13: ;
			ZEPHIR_OBS_NVAR(&exprCode);
			zephir_array_fetch_string(&exprCode, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1516);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_14: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			if (EXPECTED(doubleQuotes == 0)) {
				ZEPHIR_INIT_NVAR(&_21$$35);
				ZEPHIR_OBS_NVAR(&_22$$35);
				zephir_array_fetch_string(&_22$$35, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1521);
				ZEPHIR_INIT_NVAR(&_23$$35);
				ZVAL_STRING(&_23$$35, "'");
				ZEPHIR_INIT_NVAR(&_24$$35);
				ZVAL_STRING(&_24$$35, "\\'");
				zephir_fast_str_replace(&_21$$35, &_23$$35, &_24$$35, &_22$$35);
				ZEPHIR_CONCAT_SVS(&exprCode, "'", &_21$$35, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_OBS_NVAR(&_25$$36);
				zephir_array_fetch_string(&_25$$36, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1523);
				ZEPHIR_CONCAT_SVS(&exprCode, "\"", &_25$$36, "\"");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_15: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZVAL_STRING(&exprCode, "null");
			goto zephir_switch_0_end;
		zephir_switch_0_clause_16: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZVAL_STRING(&exprCode, "false");
			goto zephir_switch_0_end;
		zephir_switch_0_clause_17: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZVAL_STRING(&exprCode, "true");
			goto zephir_switch_0_end;
		zephir_switch_0_clause_18: ;
			ZEPHIR_OBS_NVAR(&_26$$40);
			zephir_array_fetch_string(&_26$$40, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1540);
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SV(&exprCode, "$", &_26$$40);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_19: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " && ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_20: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " || ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_21: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " <= ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_22: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " >= ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_23: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " == ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_24: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " != ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_25: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " === ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_26: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSV(&exprCode, &leftCode, " !== ", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_27: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "range(", &leftCode, ", ", &rightCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_28: ;
			if (doubleQuotes) {
				ZVAL_BOOL(&_27$$50, 1);
			} else {
				ZVAL_BOOL(&_27$$50, 0);
			}
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "functionCall", &_28, 0, &expr, &_27$$50);
			zephir_check_call_status();
			goto zephir_switch_0_end;
		zephir_switch_0_clause_29: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_30: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_VSVS(&exprCode, &leftCode, "[", &rightCode, "]");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_31: ;
			ZEPHIR_OBS_NVAR(&start);
			if (zephir_array_isset_string_fetch(&start, &expr, SL("start"), 0)) {
				if (doubleQuotes) {
					ZVAL_BOOL(&_29$$54, 1);
				} else {
					ZVAL_BOOL(&_29$$54, 0);
				}
				ZEPHIR_CALL_METHOD(&startCode, this_ptr, "expression", &_7, 0, &start, &_29$$54);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&startCode);
				ZVAL_STRING(&startCode, "null");
			}
			ZEPHIR_OBS_NVAR(&end);
			if (zephir_array_isset_string_fetch(&end, &expr, SL("end"), 0)) {
				if (doubleQuotes) {
					ZVAL_BOOL(&_30$$56, 1);
				} else {
					ZVAL_BOOL(&_30$$56, 0);
				}
				ZEPHIR_CALL_METHOD(&endCode, this_ptr, "expression", &_7, 0, &end, &_30$$56);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&endCode);
				ZVAL_STRING(&endCode, "null");
			}
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVSVS(&exprCode, "$this->slice(", &leftCode, ", ", &startCode, ", ", &endCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_32: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "!isset(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_33: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "isset(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_34: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "!empty(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_35: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "empty(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_36: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "!(((", &leftCode, ") % 2) == 0)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_37: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "(((", &leftCode, ") % 2) == 0)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_38: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "!(((", &leftCode, ") % 2) != 0)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_39: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "(((", &leftCode, ") % 2) != 0)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_40: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "!is_numeric(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_41: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "is_numeric(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_42: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "!is_scalar(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_43: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVS(&exprCode, "is_scalar(", &leftCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_44: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "!(is_array(", &leftCode, ") || (", &leftCode, ") instanceof Traversable)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_45: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "(is_array(", &leftCode, ") || (", &leftCode, ") instanceof Traversable)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_46: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "$this->isIncluded(", &leftCode, ", ", &rightCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_47: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "!$this->isIncluded(", &leftCode, ", ", &rightCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_48: ;
			ZEPHIR_OBS_NVAR(&_32$$74);
			zephir_array_fetch_string(&_32$$74, &expr, SL("ternary"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1679);
			if (doubleQuotes) {
				ZVAL_BOOL(&_33$$74, 1);
			} else {
				ZVAL_BOOL(&_33$$74, 0);
			}
			ZEPHIR_CALL_METHOD(&_31$$74, this_ptr, "expression", &_7, 0, &_32$$74, &_33$$74);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVSVS(&exprCode, "(", &_31$$74, " ? ", &leftCode, " : ", &rightCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_49: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SV(&exprCode, "-", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_50: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SV(&exprCode, "+", &rightCode);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_51: ;
			ZEPHIR_OBS_NVAR(&exprCode);
			zephir_array_fetch_string(&exprCode, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1691);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_52: ;
			ZEPHIR_INIT_NVAR(&_34$$78);
			object_init_ex(&_34$$78, phalcon_mvc_view_engine_volt_exception_ce);
			ZEPHIR_OBS_NVAR(&_35$$78);
			zephir_array_fetch_string(&_35$$78, &expr, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1696);
			ZEPHIR_OBS_NVAR(&_36$$78);
			zephir_array_fetch_string(&_36$$78, &expr, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1697);
			ZEPHIR_INIT_NVAR(&_37$$78);
			ZEPHIR_CONCAT_SVSVSV(&_37$$78, "Unknown expression ", &type, " in ", &_35$$78, " on line ", &_36$$78);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_34$$78, "__construct", &_38, 0, &_37$$78);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_34$$78, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1697);
			ZEPHIR_MM_RESTORE();
			return;
		zephir_switch_0_end: ;

		break;
	}
	RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("exprLevel")));
	RETURN_CCTOR(&exprCode);
}

/**
 * Fires an event to registered extensions
 *
 * @param string $name
 * @param array  $arguments
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, fireExtensionEvent)
{
	zend_bool _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval arguments, _4$$5, _5$$6, _8$$10, _9$$11;
	zval name_zv, *arguments_param = NULL, extensions, extension, status, _0, *_1, _2, *_3, _6;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_8$$10);
	ZVAL_UNDEF(&_9$$11);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extensions", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		arguments_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	if (!arguments_param) {
		ZEPHIR_INIT_VAR(&arguments);
		array_init(&arguments);
	} else {
		zephir_get_arrval(&arguments, arguments_param);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 922, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_0);
	if (Z_TYPE_P(&extensions) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &extensions);
		_1 = &_2;
	} else {
		_1 = &extensions;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1745);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&extension);
			ZVAL_COPY(&extension, _3);
			if ((zephir_method_exists(&extension, &name_zv)  == SUCCESS)) {
				if (!(ZEPHIR_IS_EMPTY(&arguments))) {
					ZEPHIR_INIT_NVAR(&_4$$5);
					zephir_create_array(&_4$$5, 2, 0);
					zephir_array_fast_append(&_4$$5, &extension);
					zephir_array_fast_append(&_4$$5, &name_zv);
					ZEPHIR_INIT_NVAR(&status);
					ZEPHIR_CALL_USER_FUNC_ARRAY(&status, &_4$$5, &arguments);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(&_5$$6);
					zephir_create_array(&_5$$6, 2, 0);
					zephir_array_fast_append(&_5$$6, &extension);
					zephir_array_fast_append(&_5$$6, &name_zv);
					ZEPHIR_INIT_NVAR(&status);
					ZEPHIR_CALL_USER_FUNC(&status, &_5$$6);
					zephir_check_call_status();
				}
				if (Z_TYPE_P(&status) == IS_STRING) {
					RETURN_CCTOR(&status);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&extension, _1, "current", NULL, 0);
			zephir_check_call_status();
				if ((zephir_method_exists(&extension, &name_zv)  == SUCCESS)) {
					if (!(ZEPHIR_IS_EMPTY(&arguments))) {
						ZEPHIR_INIT_NVAR(&_8$$10);
						zephir_create_array(&_8$$10, 2, 0);
						zephir_array_fast_append(&_8$$10, &extension);
						zephir_array_fast_append(&_8$$10, &name_zv);
						ZEPHIR_INIT_NVAR(&status);
						ZEPHIR_CALL_USER_FUNC_ARRAY(&status, &_8$$10, &arguments);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(&_9$$11);
						zephir_create_array(&_9$$11, 2, 0);
						zephir_array_fast_append(&_9$$11, &extension);
						zephir_array_fast_append(&_9$$11, &name_zv);
						ZEPHIR_INIT_NVAR(&status);
						ZEPHIR_CALL_USER_FUNC(&status, &_9$$11);
						zephir_check_call_status();
					}
					if (Z_TYPE_P(&status) == IS_STRING) {
						RETURN_CCTOR(&status);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&extension);
	ZEPHIR_MM_RESTORE();
}

/**
 * Resolves function intermediate code into PHP function calls
 *
 * @param array $expr
 * @param bool  $doubleQuotes
 *
 * @throws \Phalcon\Mvc\View\Engine\Volt\Exception
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, functionCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool doubleQuotes, _9$$5, _15$$5;
	zval *expr_param = NULL, *doubleQuotes_param = NULL, __$true, arguments, arrayHelpers, block, code, currentBlock, definition, escapedCode, exprLevel, extendedBlocks, extensions, funcArguments, functions, method, name, nameExpr, nameType, tagService, _23, _24, _0$$3, _1$$5, _13$$5, _14$$5, _16$$5, _17$$5, _18$$5, _3$$6, _5$$9, _6$$9, _7$$9, _8$$9, _10$$15, _11$$16, _12$$17, _19$$28, _20$$28, _21$$28, _22$$30;
	zval expr, _2$$6, _4$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_4$$12);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&arrayHelpers);
	ZVAL_UNDEF(&block);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&currentBlock);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&escapedCode);
	ZVAL_UNDEF(&exprLevel);
	ZVAL_UNDEF(&extendedBlocks);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&funcArguments);
	ZVAL_UNDEF(&functions);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&nameExpr);
	ZVAL_UNDEF(&nameType);
	ZVAL_UNDEF(&tagService);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$9);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_10$$15);
	ZVAL_UNDEF(&_11$$16);
	ZVAL_UNDEF(&_12$$17);
	ZVAL_UNDEF(&_19$$28);
	ZVAL_UNDEF(&_20$$28);
	ZVAL_UNDEF(&_21$$28);
	ZVAL_UNDEF(&_22$$30);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extensions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("functions", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("extendedBlocks", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("currentBlock", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("exprLevel", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(doubleQuotes)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &expr_param, &doubleQuotes_param);
	ZEPHIR_OBS_COPY_OR_DUP(&expr, expr_param);
	if (!doubleQuotes_param) {
		doubleQuotes = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&code);
	ZVAL_NULL(&code);
	ZEPHIR_INIT_VAR(&funcArguments);
	ZVAL_NULL(&funcArguments);
	zephir_memory_observe(&nameExpr);
	zephir_array_fetch_string(&nameExpr, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1764);
	zephir_memory_observe(&nameType);
	zephir_array_fetch_string(&nameType, &nameExpr, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1765);
	ZEPHIR_OBS_NVAR(&funcArguments);
	if (zephir_array_isset_string_fetch(&funcArguments, &expr, SL("arguments"), 0)) {
		if (doubleQuotes) {
			ZVAL_BOOL(&_0$$3, 1);
		} else {
			ZVAL_BOOL(&_0$$3, 0);
		}
		ZEPHIR_CALL_METHOD(&arguments, this_ptr, "expression", NULL, 0, &funcArguments, &_0$$3);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&arguments);
		ZVAL_STRING(&arguments, "");
	}
	if (ZEPHIR_IS_LONG(&nameType, 265)) {
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &nameExpr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1782);
		zephir_read_property_cached(&_1$$5, this_ptr, _zephir_prop_0, 922, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&extensions, &_1$$5);
		if (Z_TYPE_P(&extensions) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(&_2$$6);
			zephir_create_array(&_2$$6, 3, 0);
			zephir_array_fast_append(&_2$$6, &name);
			zephir_array_fast_append(&_2$$6, &arguments);
			zephir_array_fast_append(&_2$$6, &funcArguments);
			ZEPHIR_INIT_VAR(&_3$$6);
			ZVAL_STRING(&_3$$6, "compileFunction");
			ZEPHIR_CALL_METHOD(&code, this_ptr, "fireExtensionEvent", NULL, 0, &_3$$6, &_2$$6);
			zephir_check_call_status();
			if (Z_TYPE_P(&code) == IS_STRING) {
				RETURN_CCTOR(&code);
			}
		}
		zephir_read_property_cached(&_1$$5, this_ptr, _zephir_prop_1, 923, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&functions, &_1$$5);
		if (Z_TYPE_P(&functions) == IS_ARRAY) {
			zephir_memory_observe(&definition);
			if (zephir_array_isset_fetch(&definition, &functions, &name, 0)) {
				if (Z_TYPE_P(&definition) == IS_STRING) {
					ZEPHIR_CONCAT_VSVS(return_value, &definition, "(", &arguments, ")");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					RETURN_MM();
				}
				if (Z_TYPE_P(&definition) == IS_OBJECT) {
					if (zephir_is_instance_of(&definition, SL("Closure"))) {
						ZEPHIR_INIT_VAR(&_4$$12);
						zephir_create_array(&_4$$12, 2, 0);
						zephir_array_fast_append(&_4$$12, &arguments);
						zephir_array_fast_append(&_4$$12, &funcArguments);
						ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &definition, &_4$$12);
						zephir_check_call_status();
						RETURN_MM();
					}
				}
				ZEPHIR_INIT_VAR(&_5$$9);
				object_init_ex(&_5$$9, phalcon_mvc_view_engine_volt_exception_ce);
				zephir_array_fetch_string(&_6$$9, &expr, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1832);
				zephir_array_fetch_string(&_7$$9, &expr, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1833);
				ZEPHIR_INIT_VAR(&_8$$9);
				ZEPHIR_CONCAT_SVSVSV(&_8$$9, "Invalid definition for user function '", &name, "' in ", &_6$$9, " on line ", &_7$$9);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_5$$9, "__construct", NULL, 0, &_8$$9);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_5$$9, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1833);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		_9$$5 = ZEPHIR_IS_STRING(&name, "get_content");
		if (!(_9$$5)) {
			_9$$5 = ZEPHIR_IS_STRING(&name, "content");
		}
		if (_9$$5) {
			RETURN_MM_STRING("$this->getContent()");
		}
		if (ZEPHIR_IS_STRING(&name, "partial")) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->partial(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "super")) {
			zephir_read_property_cached(&_10$$15, this_ptr, _zephir_prop_2, 910, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&extendedBlocks, &_10$$15);
			if (Z_TYPE_P(&extendedBlocks) == IS_ARRAY) {
				zephir_read_property_cached(&_11$$16, this_ptr, _zephir_prop_3, 924, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&currentBlock, &_11$$16);
				zephir_memory_observe(&block);
				if (zephir_array_isset_fetch(&block, &extendedBlocks, &currentBlock, 0)) {
					zephir_read_property_cached(&_12$$17, this_ptr, _zephir_prop_4, 914, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CPY_WRT(&exprLevel, &_12$$17);
					if (Z_TYPE_P(&block) == IS_ARRAY) {
						ZEPHIR_CALL_METHOD(&code, this_ptr, "statementListOrExtends", NULL, 0, &block);
						zephir_check_call_status();
						if (ZEPHIR_IS_LONG(&exprLevel, 1)) {
							ZEPHIR_CPY_WRT(&escapedCode, &code);
						} else {
							ZEPHIR_INIT_NVAR(&escapedCode);
							zephir_addslashes(&escapedCode, &code);
						}
					} else {
						if (ZEPHIR_IS_LONG(&exprLevel, 1)) {
							ZEPHIR_CPY_WRT(&escapedCode, &block);
						} else {
							ZEPHIR_INIT_NVAR(&escapedCode);
							zephir_addslashes(&escapedCode, &block);
						}
					}
					if (ZEPHIR_IS_LONG(&exprLevel, 1)) {
						RETURN_CCTOR(&escapedCode);
					}
					ZEPHIR_CONCAT_SVS(return_value, "'", &escapedCode, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					RETURN_MM();
				}
			}
			RETURN_MM_STRING("''");
		}
		if (ZEPHIR_IS_STRING_IDENTICAL(&name, "preload")) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->preload(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_13$$5);
		zephir_camelize(&_13$$5, &name, NULL );
		ZEPHIR_CALL_FUNCTION(&method, "lcfirst", NULL, 83, &_13$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&arrayHelpers);
		zephir_create_array(&arrayHelpers, 16, 0);
		zephir_array_update_string(&arrayHelpers, SL("link_to"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("image"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("form_legacy"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("submit_button"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("radio_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("check_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("file_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("hidden_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("password_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("text_area"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("text_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("email_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("date_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("tel_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("numeric_field"), &__$true, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&arrayHelpers, SL("image_input"), &__$true, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_14$$5);
		ZVAL_STRING(&_14$$5, "Phalcon\\Tag");
		if ((zephir_method_exists(&_14$$5, &method)  == SUCCESS)) {
			if (zephir_array_isset_value(&arrayHelpers, &name)) {
				ZEPHIR_CONCAT_SVSVS(return_value, "\\Phalcon\\Tag::", &method, "([", &arguments, "])");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_MM();
			}
			ZEPHIR_CONCAT_SVSVS(return_value, "\\Phalcon\\Tag::", &method, "(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		zephir_read_property_cached(&_1$$5, this_ptr, _zephir_prop_5, 908, PH_NOISY_CC | PH_READONLY);
		_15$$5 = Z_TYPE_P(&_1$$5) != IS_NULL;
		if (_15$$5) {
			zephir_read_property_cached(&_16$$5, this_ptr, _zephir_prop_5, 908, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_18$$5);
			ZVAL_STRING(&_18$$5, "tag");
			ZEPHIR_CALL_METHOD(&_17$$5, &_16$$5, "has", NULL, 0, &_18$$5);
			zephir_check_call_status();
			_15$$5 = ZEPHIR_IS_TRUE_IDENTICAL(&_17$$5);
		}
		if (_15$$5) {
			zephir_read_property_cached(&_19$$28, this_ptr, _zephir_prop_5, 908, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_20$$28);
			ZVAL_STRING(&_20$$28, "tag");
			ZEPHIR_CALL_METHOD(&tagService, &_19$$28, "get", NULL, 0, &_20$$28);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_21$$28, &tagService, "has", NULL, 0, &name);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_21$$28)) {
				ZEPHIR_INIT_NVAR(&funcArguments);
				ZVAL_NULL(&funcArguments);
				ZEPHIR_OBS_NVAR(&funcArguments);
				if (zephir_array_isset_string_fetch(&funcArguments, &expr, SL("arguments"), 0)) {
					ZVAL_BOOL(&_22$$30, 1);
					ZEPHIR_CALL_METHOD(&arguments, this_ptr, "expression", NULL, 0, &funcArguments, &_22$$30);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(&arguments);
					ZVAL_STRING(&arguments, "");
				}
				ZEPHIR_CONCAT_SVSVS(return_value, "$this->tag->", &name, "(", &arguments, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_MM();
			}
		}
		if (ZEPHIR_IS_STRING(&name, "url")) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->url->get(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "static_url")) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->url->getStatic(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "date")) {
			ZEPHIR_CONCAT_SVS(return_value, "date(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "time")) {
			RETURN_MM_STRING("time()");
		}
		if (ZEPHIR_IS_STRING(&name, "dump")) {
			ZEPHIR_CONCAT_SVS(return_value, "var_dump(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "version")) {
			RETURN_MM_STRING("(new Phalcon\\Support\\Version)->get()");
		}
		if (ZEPHIR_IS_STRING(&name, "version_id")) {
			RETURN_MM_STRING("(new Phalcon\\Support\\Version)->getId()");
		}
		if (ZEPHIR_IS_STRING(&name, "preload")) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->preload(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "constant")) {
			ZEPHIR_CONCAT_SVS(return_value, "constant(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		ZEPHIR_CONCAT_SVSVS(return_value, "$this->callMacro('", &name, "', [", &arguments, "])");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (doubleQuotes) {
		ZVAL_BOOL(&_24, 1);
	} else {
		ZVAL_BOOL(&_24, 0);
	}
	ZEPHIR_CALL_METHOD(&_23, this_ptr, "expression", NULL, 0, &nameExpr, &_24);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSVS(return_value, &_23, "(", &arguments, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Returns the path to the last compiled template
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getCompiledTemplatePath)
{

	RETURN_MEMBER_TYPED(getThis(), "compiledTemplatePath", IS_STRING);
}

/**
 * Returns the internal dependency injector
 *
 * @return DiInterface
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getDI)
{

	RETURN_MEMBER(getThis(), "container");
}

/**
 * Returns the list of extensions registered in Volt
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getExtensions)
{

	RETURN_MEMBER_TYPED(getThis(), "extensions", IS_ARRAY);
}

/**
 * Register the user registered filters
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getFilters)
{

	RETURN_MEMBER_TYPED(getThis(), "filters", IS_ARRAY);
}

/**
 * Register the user registered functions
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getFunctions)
{

	RETURN_MEMBER_TYPED(getThis(), "functions", IS_ARRAY);
}

/**
 * Returns a compiler's option
 *
 * @param string option
 *
 * @return string|null
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getOption)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval option_zv, value, _0;
	zend_string *option = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&option_zv);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(option)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&option_zv);
	ZVAL_STR_COPY(&option_zv, option);
	zephir_memory_observe(&value);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 915, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&value, &_0, &option_zv, 0))) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&value);
}

/**
 * Returns the compiler options
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getOptions)
{

	RETURN_MEMBER_TYPED(getThis(), "options", IS_ARRAY);
}

/**
 * Returns the path that is currently being compiled
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getTemplatePath)
{

	RETURN_MEMBER_TYPED(getThis(), "currentPath", IS_STRING);
}

/**
 * Return a unique prefix to be used as prefix for compiled variables and
 * contexts
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getUniquePrefix)
{
	zval _7$$5;
	zval _0, _3, _8, _1$$3, _2$$3, _4$$4, _5$$5, _6$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("prefix", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("currentPath", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 925, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 918, PH_NOISY_CC | PH_READONLY);
		zephir_unique_path_key(&_1$$3, &_2$$3);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 925, &_1$$3);
	}
	zephir_memory_observe(&_3);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 925, PH_NOISY_CC);
	if (Z_TYPE_P(&_3) == IS_OBJECT) {
		zephir_memory_observe(&_4$$4);
		zephir_read_property_cached(&_4$$4, this_ptr, _zephir_prop_0, 925, PH_NOISY_CC);
		if (zephir_is_instance_of(&_4$$4, SL("Closure"))) {
			ZEPHIR_INIT_VAR(&_5$$5);
			zephir_read_property_cached(&_6$$5, this_ptr, _zephir_prop_0, 925, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_7$$5);
			zephir_create_array(&_7$$5, 1, 0);
			zephir_array_fast_append(&_7$$5, this_ptr);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&_5$$5, &_6$$5, &_7$$5);
			zephir_check_call_status();
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 925, &_5$$5);
		}
	}
	zephir_memory_observe(&_8);
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_0, 925, PH_NOISY_CC);
	if (UNEXPECTED(Z_TYPE_P(&_8) != IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "The unique compilation prefix is invalid", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2127);
		return;
	}
	RETURN_MM_MEMBER_TYPED(getThis(), "prefix", IS_STRING);
}

/**
 * Parses a Volt template returning its intermediate representation
 *
 *```php
 * print_r(
 *     $compiler->parse("{% raw %}{{ 3 + 2 }}{% endraw %}")
 * );
 *```
 *
 * @param string viewCode
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, parse)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval viewCode_zv, currentPath;
	zend_string *viewCode = NULL;

	ZVAL_UNDEF(&viewCode_zv);
	ZVAL_UNDEF(&currentPath);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(viewCode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&viewCode_zv);
	ZVAL_STR_COPY(&viewCode_zv, viewCode);
	ZEPHIR_INIT_VAR(&currentPath);
	ZVAL_STRING(&currentPath, "eval code");
	ZEPHIR_LAST_CALL_STATUS = phvolt_parse_view(return_value, &viewCode_zv, &currentPath);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Resolves filter intermediate code into a valid PHP expression
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, resolveTest)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *left = NULL;
	zval *test_param = NULL, left_zv, type, name, testName, _6, _0$$12, _1$$12, _2$$13, _3$$13, _4$$14, _5$$14;
	zval test;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&test);
	ZVAL_UNDEF(&left_zv);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&testName);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_0$$12);
	ZVAL_UNDEF(&_1$$12);
	ZVAL_UNDEF(&_2$$13);
	ZVAL_UNDEF(&_3$$13);
	ZVAL_UNDEF(&_4$$14);
	ZVAL_UNDEF(&_5$$14);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(test, test_param)
		Z_PARAM_STR(left)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	test_param = ZEND_CALL_ARG(execute_data, 1);
	ZEPHIR_OBS_COPY_OR_DUP(&test, test_param);
	zephir_memory_observe(&left_zv);
	ZVAL_STR_COPY(&left_zv, left);
	zephir_memory_observe(&type);
	zephir_array_fetch_string(&type, &test, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2161);
	if (ZEPHIR_IS_LONG(&type, 265)) {
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &test, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2167);
		if (ZEPHIR_IS_STRING(&name, "empty")) { goto zephir_switch_0_clause_0; }
		if (ZEPHIR_IS_STRING(&name, "even")) { goto zephir_switch_0_clause_1; }
		if (ZEPHIR_IS_STRING(&name, "odd")) { goto zephir_switch_0_clause_2; }
		if (ZEPHIR_IS_STRING(&name, "numeric")) { goto zephir_switch_0_clause_3; }
		if (ZEPHIR_IS_STRING(&name, "scalar")) { goto zephir_switch_0_clause_4; }
		if (ZEPHIR_IS_STRING(&name, "iterable")) { goto zephir_switch_0_clause_5; }
		goto zephir_switch_0_end;
		zephir_switch_0_clause_0: ;
			ZEPHIR_CONCAT_SVS(return_value, "empty(", &left_zv, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		zephir_switch_0_clause_1: ;
			ZEPHIR_CONCAT_SVS(return_value, "(((", &left_zv, ") % 2) == 0)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		zephir_switch_0_clause_2: ;
			ZEPHIR_CONCAT_SVS(return_value, "(((", &left_zv, ") % 2) != 0)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		zephir_switch_0_clause_3: ;
			ZEPHIR_CONCAT_SVS(return_value, "is_numeric(", &left_zv, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		zephir_switch_0_clause_4: ;
			ZEPHIR_CONCAT_SVS(return_value, "is_scalar(", &left_zv, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		zephir_switch_0_clause_5: ;
			ZEPHIR_CONCAT_SVSVS(return_value, "(is_array(", &left_zv, ") || (", &left_zv, ") instanceof Traversable)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		zephir_switch_0_end: ;

	}
	if (ZEPHIR_IS_LONG(&type, 350)) {
		zephir_memory_observe(&testName);
		zephir_array_fetch_string(&testName, &test, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2190);
		ZEPHIR_OBS_NVAR(&name);
		if (zephir_array_isset_string_fetch(&name, &testName, SL("value"), 0)) {
			if (ZEPHIR_IS_STRING(&name, "divisibleby")) { goto zephir_switch_1_clause_0; }
			if (ZEPHIR_IS_STRING(&name, "sameas")) { goto zephir_switch_1_clause_1; }
			if (ZEPHIR_IS_STRING(&name, "type")) { goto zephir_switch_1_clause_2; }
			goto zephir_switch_1_end;
			zephir_switch_1_clause_0: ;
				zephir_memory_observe(&_1$$12);
				zephir_array_fetch_string(&_1$$12, &test, SL("arguments"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2195);
				ZEPHIR_CALL_METHOD(&_0$$12, this_ptr, "expression", NULL, 0, &_1$$12);
				zephir_check_call_status();
				ZEPHIR_CONCAT_SVSVS(return_value, "(((", &left_zv, ") % (", &_0$$12, ")) == 0)");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_MM();
			zephir_switch_1_clause_1: ;
				zephir_memory_observe(&_3$$13);
				zephir_array_fetch_string(&_3$$13, &test, SL("arguments"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2197);
				ZEPHIR_CALL_METHOD(&_2$$13, this_ptr, "expression", NULL, 0, &_3$$13);
				zephir_check_call_status();
				ZEPHIR_CONCAT_SVSVS(return_value, "(", &left_zv, ") === (", &_2$$13, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_MM();
			zephir_switch_1_clause_2: ;
				zephir_memory_observe(&_5$$14);
				zephir_array_fetch_string(&_5$$14, &test, SL("arguments"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2199);
				ZEPHIR_CALL_METHOD(&_4$$14, this_ptr, "expression", NULL, 0, &_5$$14);
				zephir_check_call_status();
				ZEPHIR_CONCAT_SVSVS(return_value, "gettype(", &left_zv, ") === (", &_4$$14, ")");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_MM();
			zephir_switch_1_end: ;

		}
	}
	ZEPHIR_CALL_METHOD(&_6, this_ptr, "expression", NULL, 0, &test);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSV(return_value, &left_zv, " == ", &_6);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Sets the dependency injector
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setDI)
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 908, container);
}

/**
 * Sets a single compiler option
 *
 * @param mixed value
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setOption)
{
	zval option_zv, *value, value_sub;
	zend_string *option = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&option_zv);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(option)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	value = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&option_zv, option);
	zephir_update_property_array(this_ptr, SL("options"), &option_zv, value);
}

/**
 * Sets the compiler options
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *options_param = NULL;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &options_param);
	ZEPHIR_OBS_COPY_OR_DUP(&options, options_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 915, &options);
	RETURN_THIS();
}

/**
 * Set a unique prefix to be used as prefix for compiled variables
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setUniquePrefix)
{
	zval prefix_zv;
	zend_string *prefix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&prefix_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("prefix", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(prefix)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&prefix_zv, prefix);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 925, &prefix_zv);
	RETURN_THISW();
}

/**
 * Compiles a Volt source code returning a PHP plain version
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSource)
{
	zend_ulong _6$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _9$$7;
	zval viewCode_zv, *extendsMode_param = NULL, currentPath, intermediate, extended, finalCompilation, blocks, extendedBlocks, name, block, blockCompilation, localBlock, compilation, options, autoescape, _0, _1, _2$$7, *_3$$7, _4$$7, *_5$$7, _8$$7;
	zend_string *viewCode = NULL, *_7$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewCode_zv);
	ZVAL_UNDEF(&currentPath);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&extended);
	ZVAL_UNDEF(&finalCompilation);
	ZVAL_UNDEF(&blocks);
	ZVAL_UNDEF(&extendedBlocks);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&block);
	ZVAL_UNDEF(&blockCompilation);
	ZVAL_UNDEF(&localBlock);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&autoescape);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$7);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_8$$7);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentPath", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("autoescape", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("extended", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("blocks", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("extendedBlocks", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("currentBlock", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(viewCode)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		extendsMode_param = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&viewCode_zv);
	ZVAL_STR_COPY(&viewCode_zv, viewCode);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 918, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&currentPath, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 915, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&options, &_0);
	if (Z_TYPE_P(&options) == IS_ARRAY) {
		zephir_memory_observe(&autoescape);
		if (zephir_array_isset_string_fetch(&autoescape, &options, SL("autoescape"), 0)) {
			if (UNEXPECTED(((Z_TYPE_P(&autoescape) == IS_TRUE || Z_TYPE_P(&autoescape) == IS_FALSE) != 1))) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "'autoescape' must be bool", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2270);
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 917, &autoescape);
		}
	}
	ZEPHIR_INIT_VAR(&intermediate);
	ZEPHIR_LAST_CALL_STATUS = phvolt_parse_view(&intermediate, &viewCode_zv, &currentPath);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&intermediate) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Invalid intermediate representation", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2283);
		return;
	}
	if (extendsMode) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_CALL_METHOD(&compilation, this_ptr, "statementList", NULL, 0, &intermediate, &_0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_3, 909, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extended, &_1);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&extended)) {
		ZEPHIR_INIT_VAR(&finalCompilation);
		if (extendsMode == 1) {
			array_init(&finalCompilation);
		} else {
			ZVAL_NULL(&finalCompilation);
		}
		zephir_read_property_cached(&_2$$7, this_ptr, _zephir_prop_4, 911, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&blocks, &_2$$7);
		zephir_read_property_cached(&_2$$7, this_ptr, _zephir_prop_5, 910, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&extendedBlocks, &_2$$7);
		if (Z_TYPE_P(&extendedBlocks) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_4$$7);
			zephir_string_to_char_array(&_4$$7, &extendedBlocks);
			_3$$7 = &_4$$7;
		} else {
			_3$$7 = &extendedBlocks;
		}
		zephir_is_iterable(_3$$7, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2355);
		if (Z_TYPE_P(_3$$7) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_3$$7), _6$$7, _7$$7, _5$$7)
			{
				ZEPHIR_INIT_NVAR(&name);
				if (_7$$7 != NULL) { 
					ZVAL_STR_COPY(&name, _7$$7);
				} else {
					ZVAL_LONG(&name, _6$$7);
				}
				ZEPHIR_INIT_NVAR(&block);
				ZVAL_COPY(&block, _5$$7);
				if (Z_TYPE_P(&name) == IS_STRING) {
					if (zephir_array_isset_value(&blocks, &name)) {
						ZEPHIR_OBS_NVAR(&localBlock);
						zephir_array_fetch(&localBlock, &blocks, &name, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2315);
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 924, &name);
						if (Z_TYPE_P(&localBlock) == IS_NULL) {
							ZEPHIR_INIT_NVAR(&localBlock);
							array_init(&localBlock);
						}
						ZEPHIR_CALL_METHOD(&blockCompilation, this_ptr, "statementList", NULL, 0, &localBlock);
						zephir_check_call_status();
					} else {
						if (Z_TYPE_P(&block) == IS_ARRAY) {
							ZEPHIR_CALL_METHOD(&blockCompilation, this_ptr, "statementList", NULL, 0, &block);
							zephir_check_call_status();
						} else {
							ZEPHIR_CPY_WRT(&blockCompilation, &block);
						}
					}
					if (extendsMode) {
						zephir_array_update_zval(&finalCompilation, &name, &blockCompilation, PH_COPY | PH_SEPARATE);
					} else {
						zephir_concat_self(&finalCompilation, &blockCompilation);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} else {
					if (extendsMode) {
						zephir_array_append(&finalCompilation, &block, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2348);
					} else {
						zephir_concat_self(&finalCompilation, &block);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _3$$7, "rewind", NULL, 0);
			zephir_check_call_status();
			_9$$7 = 1;
			while (1) {
				if (_9$$7) {
					_9$$7 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _3$$7, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_8$$7, _3$$7, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_8$$7)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&name, _3$$7, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&block, _3$$7, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&name) == IS_STRING) {
						if (zephir_array_isset_value(&blocks, &name)) {
							ZEPHIR_OBS_NVAR(&localBlock);
							zephir_array_fetch(&localBlock, &blocks, &name, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2315);
							zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 924, &name);
							if (Z_TYPE_P(&localBlock) == IS_NULL) {
								ZEPHIR_INIT_NVAR(&localBlock);
								array_init(&localBlock);
							}
							ZEPHIR_CALL_METHOD(&blockCompilation, this_ptr, "statementList", NULL, 0, &localBlock);
							zephir_check_call_status();
						} else {
							if (Z_TYPE_P(&block) == IS_ARRAY) {
								ZEPHIR_CALL_METHOD(&blockCompilation, this_ptr, "statementList", NULL, 0, &block);
								zephir_check_call_status();
							} else {
								ZEPHIR_CPY_WRT(&blockCompilation, &block);
							}
						}
						if (extendsMode) {
							zephir_array_update_zval(&finalCompilation, &name, &blockCompilation, PH_COPY | PH_SEPARATE);
						} else {
							zephir_concat_self(&finalCompilation, &blockCompilation);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					} else {
						if (extendsMode) {
							zephir_array_append(&finalCompilation, &block, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2348);
						} else {
							zephir_concat_self(&finalCompilation, &block);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
			}
		}
		ZEPHIR_INIT_NVAR(&block);
		ZEPHIR_INIT_NVAR(&name);
		RETURN_CCTOR(&finalCompilation);
	}
	if (extendsMode) {
		RETURN_MM_MEMBER(getThis(), "blocks");
	}
	RETURN_CCTOR(&compilation);
}

/**
 * Gets the final path with VIEW
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getFinalPath)
{
	zend_bool _6$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval path_zv, view, viewsDirs, viewsDir, _0, *_1$$4, _2$$4, *_3$$4, _5$$4, _4$$5, _7$$7;
	zend_string *path = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&viewsDirs);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_7$$7);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("view", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_INIT_VAR(&viewsDir);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 906, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&view, &_0);
	if (Z_TYPE_P(&view) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(&viewsDirs, &view, "getViewsDir", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&viewsDirs) == IS_ARRAY) {
			if (Z_TYPE_P(&viewsDirs) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_2$$4);
				zephir_string_to_char_array(&_2$$4, &viewsDirs);
				_1$$4 = &_2$$4;
			} else {
				_1$$4 = &viewsDirs;
			}
			zephir_is_iterable(_1$$4, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2389);
			if (Z_TYPE_P(_1$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1$$4), _3$$4)
				{
					ZEPHIR_INIT_NVAR(&viewsDir);
					ZVAL_COPY(&viewsDir, _3$$4);
					ZEPHIR_INIT_NVAR(&_4$$5);
					ZEPHIR_CONCAT_VV(&_4$$5, &viewsDir, &path_zv);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if ((zephir_file_exists(&_4$$5) == SUCCESS)) {
						ZEPHIR_CONCAT_VV(return_value, &viewsDir, &path_zv);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						RETURN_MM();
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_6$$4 = 1;
				while (1) {
					if (_6$$4) {
						_6$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _1$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_5$$4, _1$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_5$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&viewsDir, _1$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_7$$7);
						ZEPHIR_CONCAT_VV(&_7$$7, &viewsDir, &path_zv);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if ((zephir_file_exists(&_7$$7) == SUCCESS)) {
							ZEPHIR_CONCAT_VV(return_value, &viewsDir, &path_zv);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							RETURN_MM();
						}
				}
			}
			ZEPHIR_INIT_NVAR(&viewsDir);
			ZEPHIR_CONCAT_VV(return_value, &viewsDir, &path_zv);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		} else {
			ZEPHIR_CONCAT_VV(return_value, &viewsDirs, &path_zv);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
	}
	RETURN_MM_STR(zend_string_copy(path));
}

/**
 * Resolves filter intermediate code into PHP function calls
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, resolveFilter)
{
	zend_bool _21$$30, _26$$41;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *left = NULL;
	zval *filter_param = NULL, left_zv, code, type, functionName, name, file, line, extensions, filters, funcArguments, arguments, definition, _6, _30, _31, _32, _33, _0$$5, _1$$5, _2$$5, _3$$5, _8$$9, _10$$11, _11$$11, _12$$11, _13$$11, _14$$24, _15$$24, _16$$24, _17$$24, _18$$24, _19$$24, _20$$30, _22$$30, _23$$30, _24$$30, _25$$41, _27$$41, _28$$41, _29$$41;
	zval filter, _4$$7, _5$$7, _7$$9, _9$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_9$$14);
	ZVAL_UNDEF(&left_zv);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&functionName);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&line);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&funcArguments);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_14$$24);
	ZVAL_UNDEF(&_15$$24);
	ZVAL_UNDEF(&_16$$24);
	ZVAL_UNDEF(&_17$$24);
	ZVAL_UNDEF(&_18$$24);
	ZVAL_UNDEF(&_19$$24);
	ZVAL_UNDEF(&_20$$30);
	ZVAL_UNDEF(&_22$$30);
	ZVAL_UNDEF(&_23$$30);
	ZVAL_UNDEF(&_24$$30);
	ZVAL_UNDEF(&_25$$41);
	ZVAL_UNDEF(&_27$$41);
	ZVAL_UNDEF(&_28$$41);
	ZVAL_UNDEF(&_29$$41);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extensions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("filters", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("container", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(filter, filter_param)
		Z_PARAM_STR(left)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	filter_param = ZEND_CALL_ARG(execute_data, 1);
	ZEPHIR_OBS_COPY_OR_DUP(&filter, filter_param);
	zephir_memory_observe(&left_zv);
	ZVAL_STR_COPY(&left_zv, left);
	ZEPHIR_INIT_VAR(&code);
	ZVAL_NULL(&code);
	zephir_memory_observe(&type);
	zephir_array_fetch_string(&type, &filter, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2407);
	if (ZEPHIR_IS_LONG(&type, 265)) {
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &filter, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2413);
	} else {
		if (UNEXPECTED(!ZEPHIR_IS_LONG(&type, 350))) {
			ZEPHIR_INIT_VAR(&_0$$5);
			object_init_ex(&_0$$5, phalcon_mvc_view_engine_volt_exception_ce);
			zephir_array_fetch_string(&_1$$5, &filter, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2420);
			zephir_array_fetch_string(&_2$$5, &filter, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2421);
			ZEPHIR_INIT_VAR(&_3$$5);
			ZEPHIR_CONCAT_SVSV(&_3$$5, "Unknown filter type in ", &_1$$5, " on line ", &_2$$5);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_0$$5, "__construct", NULL, 0, &_3$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_0$$5, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2421);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_memory_observe(&functionName);
		zephir_array_fetch_string(&functionName, &filter, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2424);
		ZEPHIR_OBS_NVAR(&name);
		zephir_array_fetch_string(&name, &functionName, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2425);
	}
	ZEPHIR_INIT_VAR(&funcArguments);
	ZVAL_NULL(&funcArguments);
	ZEPHIR_INIT_VAR(&arguments);
	ZVAL_NULL(&arguments);
	ZEPHIR_OBS_NVAR(&funcArguments);
	if (zephir_array_isset_string_fetch(&funcArguments, &filter, SL("arguments"), 0)) {
		if (!ZEPHIR_IS_STRING(&name, "default")) {
			zephir_memory_observe(&file);
			zephir_array_fetch_string(&file, &filter, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2439);
			zephir_memory_observe(&line);
			zephir_array_fetch_string(&line, &filter, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2440);
			ZEPHIR_INIT_VAR(&_4$$7);
			zephir_create_array(&_4$$7, 3, 0);
			ZEPHIR_INIT_VAR(&_5$$7);
			zephir_create_array(&_5$$7, 4, 0);
			add_assoc_long_ex(&_5$$7, SL("type"), 364);
			zephir_array_update_string(&_5$$7, SL("value"), &left_zv, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_5$$7, SL("file"), &file, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_5$$7, SL("line"), &line, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_4$$7, SL("expr"), &_5$$7, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_4$$7, SL("file"), &file, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_4$$7, SL("line"), &line, PH_COPY | PH_SEPARATE);
			ZEPHIR_MAKE_REF(&funcArguments);
			ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 300, &funcArguments, &_4$$7);
			ZEPHIR_UNREF(&funcArguments);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&arguments, this_ptr, "expression", NULL, 0, &funcArguments);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&arguments, &left_zv);
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_0, 922, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_6);
	if (Z_TYPE_P(&extensions) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_7$$9);
		zephir_create_array(&_7$$9, 3, 0);
		zephir_array_fast_append(&_7$$9, &name);
		zephir_array_fast_append(&_7$$9, &arguments);
		zephir_array_fast_append(&_7$$9, &funcArguments);
		ZEPHIR_INIT_VAR(&_8$$9);
		ZVAL_STRING(&_8$$9, "compileFilter");
		ZEPHIR_CALL_METHOD(&code, this_ptr, "fireExtensionEvent", NULL, 0, &_8$$9, &_7$$9);
		zephir_check_call_status();
		if (Z_TYPE_P(&code) == IS_STRING) {
			RETURN_CCTOR(&code);
		}
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_1, 926, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&filters, &_6);
	zephir_memory_observe(&definition);
	if (zephir_array_isset_fetch(&definition, &filters, &name, 0)) {
		if (Z_TYPE_P(&definition) == IS_STRING) {
			ZEPHIR_CONCAT_VSVS(return_value, &definition, "(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (Z_TYPE_P(&definition) == IS_OBJECT) {
			if (zephir_is_instance_of(&definition, SL("Closure"))) {
				ZEPHIR_INIT_VAR(&_9$$14);
				zephir_create_array(&_9$$14, 2, 0);
				zephir_array_fast_append(&_9$$14, &arguments);
				zephir_array_fast_append(&_9$$14, &funcArguments);
				ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &definition, &_9$$14);
				zephir_check_call_status();
				RETURN_MM();
			}
		}
		ZEPHIR_INIT_VAR(&_10$$11);
		object_init_ex(&_10$$11, phalcon_mvc_view_engine_volt_exception_ce);
		zephir_array_fetch_string(&_11$$11, &filter, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2514);
		zephir_array_fetch_string(&_12$$11, &filter, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2515);
		ZEPHIR_INIT_VAR(&_13$$11);
		ZEPHIR_CONCAT_SVSVSV(&_13$$11, "Invalid definition for user filter '", &name, "' in ", &_11$$11, " on line ", &_12$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_10$$11, "__construct", NULL, 0, &_13$$11);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_10$$11, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2515);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_IS_STRING(&name, "abs")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&name, "capitalize")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&name, "convert_encoding")) { goto zephir_switch_0_clause_2; }
	if (ZEPHIR_IS_STRING(&name, "default")) { goto zephir_switch_0_clause_3; }
	if (ZEPHIR_IS_STRING(&name, "e")) { goto zephir_switch_0_clause_4; }
	if (ZEPHIR_IS_STRING(&name, "escape")) { goto zephir_switch_0_clause_5; }
	if (ZEPHIR_IS_STRING(&name, "escape_attr")) { goto zephir_switch_0_clause_6; }
	if (ZEPHIR_IS_STRING(&name, "escape_css")) { goto zephir_switch_0_clause_7; }
	if (ZEPHIR_IS_STRING(&name, "escape_js")) { goto zephir_switch_0_clause_8; }
	if (ZEPHIR_IS_STRING(&name, "format")) { goto zephir_switch_0_clause_9; }
	if (ZEPHIR_IS_STRING(&name, "join")) { goto zephir_switch_0_clause_10; }
	if (ZEPHIR_IS_STRING(&name, "json_encode")) { goto zephir_switch_0_clause_11; }
	if (ZEPHIR_IS_STRING(&name, "json_decode")) { goto zephir_switch_0_clause_12; }
	if (ZEPHIR_IS_STRING(&name, "keys")) { goto zephir_switch_0_clause_13; }
	if (ZEPHIR_IS_STRING(&name, "left_trim")) { goto zephir_switch_0_clause_14; }
	if (ZEPHIR_IS_STRING(&name, "length")) { goto zephir_switch_0_clause_15; }
	if (ZEPHIR_IS_STRING(&name, "lower")) { goto zephir_switch_0_clause_16; }
	if (ZEPHIR_IS_STRING(&name, "lowercase")) { goto zephir_switch_0_clause_17; }
	if (ZEPHIR_IS_STRING(&name, "right_trim")) { goto zephir_switch_0_clause_18; }
	if (ZEPHIR_IS_STRING(&name, "nl2br")) { goto zephir_switch_0_clause_19; }
	if (ZEPHIR_IS_STRING(&name, "slashes")) { goto zephir_switch_0_clause_20; }
	if (ZEPHIR_IS_STRING(&name, "slice")) { goto zephir_switch_0_clause_21; }
	if (ZEPHIR_IS_STRING(&name, "sort")) { goto zephir_switch_0_clause_22; }
	if (ZEPHIR_IS_STRING(&name, "stripslashes")) { goto zephir_switch_0_clause_23; }
	if (ZEPHIR_IS_STRING(&name, "striptags")) { goto zephir_switch_0_clause_24; }
	if (ZEPHIR_IS_STRING(&name, "trim")) { goto zephir_switch_0_clause_25; }
	if (ZEPHIR_IS_STRING(&name, "upper")) { goto zephir_switch_0_clause_26; }
	if (ZEPHIR_IS_STRING(&name, "uppercase")) { goto zephir_switch_0_clause_27; }
	if (ZEPHIR_IS_STRING(&name, "url_encode")) { goto zephir_switch_0_clause_28; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		ZEPHIR_CONCAT_SVS(return_value, "abs(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_1: ;
		ZEPHIR_CONCAT_SVS(return_value, "ucwords(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_2: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->convertEncoding(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_3: ;
		ZEPHIR_CONCAT_SVSVSVS(return_value, "(empty(", &left_zv, ") ? (", &arguments, ") : (", &left_zv, "))");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_4: ;
	zephir_switch_0_clause_5: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->escaper->html(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_6: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->escaper->attributes(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_7: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->escaper->css(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_8: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->escaper->js(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_9: ;
		ZEPHIR_CONCAT_SVS(return_value, "sprintf(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_10: ;
		zephir_memory_observe(&_14$$24);
		zephir_array_fetch_long(&_14$$24, &funcArguments, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2541);
		zephir_memory_observe(&_15$$24);
		zephir_array_fetch_string(&_15$$24, &_14$$24, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2541);
		zephir_memory_observe(&_16$$24);
		zephir_array_fetch_string(&_16$$24, &_15$$24, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2542);
		zephir_memory_observe(&_17$$24);
		zephir_array_fetch_long(&_17$$24, &funcArguments, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2542);
		zephir_memory_observe(&_18$$24);
		zephir_array_fetch_string(&_18$$24, &_17$$24, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2542);
		zephir_memory_observe(&_19$$24);
		zephir_array_fetch_string(&_19$$24, &_18$$24, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2542);
		ZEPHIR_CONCAT_SVSVS(return_value, "join('", &_16$$24, "', ", &_19$$24, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_11: ;
		ZEPHIR_CONCAT_SVS(return_value, "json_encode(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_12: ;
		ZEPHIR_CONCAT_SVS(return_value, "json_decode(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_13: ;
		ZEPHIR_CONCAT_SVS(return_value, "array_keys(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_14: ;
		ZEPHIR_CONCAT_SVS(return_value, "ltrim(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_15: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->length(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_16: ;
	zephir_switch_0_clause_17: ;
		zephir_read_property_cached(&_20$$30, this_ptr, _zephir_prop_2, 908, PH_NOISY_CC | PH_READONLY);
		_21$$30 = Z_TYPE_P(&_20$$30) != IS_NULL;
		if (_21$$30) {
			zephir_read_property_cached(&_22$$30, this_ptr, _zephir_prop_2, 908, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_24$$30);
			ZVAL_STRING(&_24$$30, "helper");
			ZEPHIR_CALL_METHOD(&_23$$30, &_22$$30, "has", NULL, 0, &_24$$30);
			zephir_check_call_status();
			_21$$30 = ZEPHIR_IS_TRUE_IDENTICAL(&_23$$30);
		}
		if (_21$$30) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->helper->lower(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		} else {
			ZEPHIR_CONCAT_SVS(return_value, "strtolower(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
	zephir_switch_0_clause_18: ;
		ZEPHIR_CONCAT_SVS(return_value, "rtrim(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_19: ;
		ZEPHIR_CONCAT_SVS(return_value, "nl2br(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_20: ;
		ZEPHIR_CONCAT_SVS(return_value, "addslashes(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_21: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->slice(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_22: ;
		ZEPHIR_CONCAT_SVS(return_value, "$this->sort(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_23: ;
		ZEPHIR_CONCAT_SVS(return_value, "stripslashes(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_24: ;
		ZEPHIR_CONCAT_SVS(return_value, "strip_tags(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_25: ;
		ZEPHIR_CONCAT_SVS(return_value, "trim(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_clause_26: ;
	zephir_switch_0_clause_27: ;
		zephir_read_property_cached(&_25$$41, this_ptr, _zephir_prop_2, 908, PH_NOISY_CC | PH_READONLY);
		_26$$41 = Z_TYPE_P(&_25$$41) != IS_NULL;
		if (_26$$41) {
			zephir_read_property_cached(&_27$$41, this_ptr, _zephir_prop_2, 908, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_29$$41);
			ZVAL_STRING(&_29$$41, "helper");
			ZEPHIR_CALL_METHOD(&_28$$41, &_27$$41, "has", NULL, 0, &_29$$41);
			zephir_check_call_status();
			_26$$41 = ZEPHIR_IS_TRUE_IDENTICAL(&_28$$41);
		}
		if (_26$$41) {
			ZEPHIR_CONCAT_SVS(return_value, "$this->helper->upper(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		} else {
			ZEPHIR_CONCAT_SVS(return_value, "strtoupper(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
	zephir_switch_0_clause_28: ;
		ZEPHIR_CONCAT_SVS(return_value, "urlencode(", &arguments, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_30);
	object_init_ex(&_30, phalcon_mvc_view_engine_volt_exception_ce);
	zephir_array_fetch_string(&_31, &filter, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2589);
	zephir_array_fetch_string(&_32, &filter, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2590);
	ZEPHIR_INIT_VAR(&_33);
	ZEPHIR_CONCAT_SVSVSV(&_33, "Unknown filter \"", &name, "\" in ", &_31, " on line ", &_32);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, &_30, "__construct", NULL, 0, &_33);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_30, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2590);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Traverses a statement list compiling each of its nodes
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, statementList)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_10 = NULL, *_14 = NULL, *_16 = NULL, *_19 = NULL, *_21 = NULL, *_26 = NULL, *_28 = NULL, *_30 = NULL, *_34 = NULL, *_36 = NULL, *_39 = NULL, *_41 = NULL, *_43 = NULL, *_46 = NULL, *_48 = NULL, *_51 = NULL, *_54 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _1, _60;
	zval *statements_param = NULL, *extendsMode_param = NULL, __$true, __$false, extended, blockMode, compilation, extensions, statement, tempCompilation, type, blockName, blockStatements, blocks, path, finalPath, subCompiler, level, _0, *_2, _59, _3$$7, _4$$7, _5$$7, _6$$7, _9$$8, _11$$10, _12$$11, _13$$11, _15$$12, _17$$13, _18$$13, _20$$14, _22$$15, _23$$15, _24$$16, _25$$16, _27$$17, _29$$18, _31$$19, _32$$24, _33$$24, _35$$25, _37$$26, _38$$27, _40$$28, _42$$29, _44$$30, _45$$30, _47$$33, _49$$34, _50$$34, _52$$35, _53$$35, _55$$37, _56$$37, _57$$37, _58$$37, _61$$40, _62$$40, _63$$40, _64$$40, _66$$41, _67$$43, _68$$44, _69$$44, _70$$45, _71$$46, _72$$46, _73$$47, _74$$48, _75$$48, _76$$49, _77$$49, _78$$50, _79$$51, _80$$52, _81$$57, _82$$57, _83$$58, _84$$59, _85$$60, _86$$61, _87$$62, _88$$63, _89$$63, _90$$66, _91$$67, _92$$67, _93$$68, _94$$68, _95$$70, _96$$70, _97$$70, _98$$70;
	zval statements, _8$$8, _65$$41;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_65$$41);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&extended);
	ZVAL_UNDEF(&blockMode);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&tempCompilation);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&blockName);
	ZVAL_UNDEF(&blockStatements);
	ZVAL_UNDEF(&blocks);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&finalPath);
	ZVAL_UNDEF(&subCompiler);
	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_59);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_22$$15);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$16);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_31$$19);
	ZVAL_UNDEF(&_32$$24);
	ZVAL_UNDEF(&_33$$24);
	ZVAL_UNDEF(&_35$$25);
	ZVAL_UNDEF(&_37$$26);
	ZVAL_UNDEF(&_38$$27);
	ZVAL_UNDEF(&_40$$28);
	ZVAL_UNDEF(&_42$$29);
	ZVAL_UNDEF(&_44$$30);
	ZVAL_UNDEF(&_45$$30);
	ZVAL_UNDEF(&_47$$33);
	ZVAL_UNDEF(&_49$$34);
	ZVAL_UNDEF(&_50$$34);
	ZVAL_UNDEF(&_52$$35);
	ZVAL_UNDEF(&_53$$35);
	ZVAL_UNDEF(&_55$$37);
	ZVAL_UNDEF(&_56$$37);
	ZVAL_UNDEF(&_57$$37);
	ZVAL_UNDEF(&_58$$37);
	ZVAL_UNDEF(&_61$$40);
	ZVAL_UNDEF(&_62$$40);
	ZVAL_UNDEF(&_63$$40);
	ZVAL_UNDEF(&_64$$40);
	ZVAL_UNDEF(&_66$$41);
	ZVAL_UNDEF(&_67$$43);
	ZVAL_UNDEF(&_68$$44);
	ZVAL_UNDEF(&_69$$44);
	ZVAL_UNDEF(&_70$$45);
	ZVAL_UNDEF(&_71$$46);
	ZVAL_UNDEF(&_72$$46);
	ZVAL_UNDEF(&_73$$47);
	ZVAL_UNDEF(&_74$$48);
	ZVAL_UNDEF(&_75$$48);
	ZVAL_UNDEF(&_76$$49);
	ZVAL_UNDEF(&_77$$49);
	ZVAL_UNDEF(&_78$$50);
	ZVAL_UNDEF(&_79$$51);
	ZVAL_UNDEF(&_80$$52);
	ZVAL_UNDEF(&_81$$57);
	ZVAL_UNDEF(&_82$$57);
	ZVAL_UNDEF(&_83$$58);
	ZVAL_UNDEF(&_84$$59);
	ZVAL_UNDEF(&_85$$60);
	ZVAL_UNDEF(&_86$$61);
	ZVAL_UNDEF(&_87$$62);
	ZVAL_UNDEF(&_88$$63);
	ZVAL_UNDEF(&_89$$63);
	ZVAL_UNDEF(&_90$$66);
	ZVAL_UNDEF(&_91$$67);
	ZVAL_UNDEF(&_92$$67);
	ZVAL_UNDEF(&_93$$68);
	ZVAL_UNDEF(&_94$$68);
	ZVAL_UNDEF(&_95$$70);
	ZVAL_UNDEF(&_96$$70);
	ZVAL_UNDEF(&_97$$70);
	ZVAL_UNDEF(&_98$$70);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extended", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("extensions", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("blocks", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("extendedBlocks", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("blockLevel", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statements_param, &extendsMode_param);
	ZEPHIR_OBS_COPY_OR_DUP(&statements, statements_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	if (!(zephir_fast_count_int(&statements))) {
		RETURN_MM_STRING("");
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 909, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extended, &_0);
	_1 = zephir_is_true(&extended);
	if (!(_1)) {
		_1 = extendsMode;
	}
	ZEPHIR_INIT_VAR(&blockMode);
	ZVAL_BOOL(&blockMode, _1);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&blockMode)) {
		RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("blockLevel")));
	}
	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("level")));
	ZEPHIR_INIT_VAR(&compilation);
	ZVAL_NULL(&compilation);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 922, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_0);
	zephir_is_iterable(&statements, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2876);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&statements), _2)
		{
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _2);
			if (UNEXPECTED(Z_TYPE_P(&statement) != IS_ARRAY)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2630);
				return;
			}
			if (UNEXPECTED(!(zephir_array_isset_value_string(&statement, SL("type"))))) {
				ZEPHIR_INIT_NVAR(&_3$$7);
				object_init_ex(&_3$$7, phalcon_mvc_view_engine_volt_exception_ce);
				ZEPHIR_OBS_NVAR(&_4$$7);
				zephir_array_fetch_string(&_4$$7, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2638);
				ZEPHIR_OBS_NVAR(&_5$$7);
				zephir_array_fetch_string(&_5$$7, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2638);
				ZEPHIR_INIT_NVAR(&_6$$7);
				ZEPHIR_CONCAT_SVSV(&_6$$7, "Invalid statement in ", &_4$$7, " on line ", &_5$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_3$$7, "__construct", &_7, 0, &_6$$7, &statement);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_3$$7, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2640);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (Z_TYPE_P(&extensions) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(&_8$$8);
				zephir_create_array(&_8$$8, 1, 0);
				zephir_array_fast_append(&_8$$8, &statement);
				ZEPHIR_INIT_NVAR(&_9$$8);
				ZVAL_STRING(&_9$$8, "compileStatement");
				ZEPHIR_CALL_METHOD(&tempCompilation, this_ptr, "fireExtensionEvent", &_10, 0, &_9$$8, &_8$$8);
				zephir_check_call_status();
				if (Z_TYPE_P(&tempCompilation) == IS_STRING) {
					zephir_concat_self(&compilation, &tempCompilation);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
			}
			ZEPHIR_OBS_NVAR(&type);
			zephir_array_fetch_string(&type, &statement, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2666);
			if (ZEPHIR_IS_LONG(&type, 357)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&type, 300)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&type, 302)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&type, 411)) { goto zephir_switch_0_clause_3; }
			if (ZEPHIR_IS_LONG(&type, 412)) { goto zephir_switch_0_clause_4; }
			if (ZEPHIR_IS_LONG(&type, 413)) { goto zephir_switch_0_clause_5; }
			if (ZEPHIR_IS_LONG(&type, 304)) { goto zephir_switch_0_clause_6; }
			if (ZEPHIR_IS_LONG(&type, 306)) { goto zephir_switch_0_clause_7; }
			if (ZEPHIR_IS_LONG(&type, 359)) { goto zephir_switch_0_clause_8; }
			if (ZEPHIR_IS_LONG(&type, 307)) { goto zephir_switch_0_clause_9; }
			if (ZEPHIR_IS_LONG(&type, 310)) { goto zephir_switch_0_clause_10; }
			if (ZEPHIR_IS_LONG(&type, 313)) { goto zephir_switch_0_clause_11; }
			if (ZEPHIR_IS_LONG(&type, 316)) { goto zephir_switch_0_clause_12; }
			if (ZEPHIR_IS_LONG(&type, 327)) { goto zephir_switch_0_clause_13; }
			if (ZEPHIR_IS_LONG(&type, 317)) { goto zephir_switch_0_clause_14; }
			if (ZEPHIR_IS_LONG(&type, 319)) { goto zephir_switch_0_clause_15; }
			if (ZEPHIR_IS_LONG(&type, 320)) { goto zephir_switch_0_clause_16; }
			if (ZEPHIR_IS_LONG(&type, 321)) { goto zephir_switch_0_clause_17; }
			if (ZEPHIR_IS_LONG(&type, 322)) { goto zephir_switch_0_clause_18; }
			if (ZEPHIR_IS_LONG(&type, 325)) { goto zephir_switch_0_clause_19; }
			if (ZEPHIR_IS_LONG(&type, 358)) { goto zephir_switch_0_clause_20; }
			goto zephir_switch_0_clause_21;
			zephir_switch_0_clause_0: ;
				ZEPHIR_OBS_NVAR(&_11$$10);
				zephir_array_fetch_string(&_11$$10, &statement, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2674);
				zephir_concat_self(&compilation, &_11$$10);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				if (extendsMode) {
					ZVAL_BOOL(&_13$$11, 1);
				} else {
					ZVAL_BOOL(&_13$$11, 0);
				}
				ZEPHIR_CALL_METHOD(&_12$$11, this_ptr, "compileIf", &_14, 0, &statement, &_13$$11);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_12$$11);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
				ZEPHIR_CALL_METHOD(&_15$$12, this_ptr, "compileElseIf", &_16, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_15$$12);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				if (extendsMode) {
					ZVAL_BOOL(&_18$$13, 1);
				} else {
					ZVAL_BOOL(&_18$$13, 0);
				}
				ZEPHIR_CALL_METHOD(&_17$$13, this_ptr, "compileSwitch", &_19, 0, &statement, &_18$$13);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_17$$13);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_CALL_METHOD(&_20$$14, this_ptr, "compileCase", &_21, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_20$$14);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_5: ;
				ZVAL_BOOL(&_23$$15, 0);
				ZEPHIR_CALL_METHOD(&_22$$15, this_ptr, "compileCase", &_21, 0, &statement, &_23$$15);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_22$$15);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_6: ;
				if (extendsMode) {
					ZVAL_BOOL(&_25$$16, 1);
				} else {
					ZVAL_BOOL(&_25$$16, 0);
				}
				ZEPHIR_CALL_METHOD(&_24$$16, this_ptr, "compileForeach", &_26, 0, &statement, &_25$$16);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_24$$16);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_7: ;
				ZEPHIR_CALL_METHOD(&_27$$17, this_ptr, "compileSet", &_28, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_27$$17);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_8: ;
				ZEPHIR_CALL_METHOD(&_29$$18, this_ptr, "compileEcho", &_30, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_29$$18);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_9: ;
				ZEPHIR_OBS_NVAR(&blockName);
				zephir_array_fetch_string(&blockName, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2721);
				ZEPHIR_OBS_NVAR(&blockStatements);
				zephir_array_isset_string_fetch(&blockStatements, &statement, SL("block_statements"), 0);
				zephir_read_property_cached(&_31$$19, this_ptr, _zephir_prop_2, 911, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&blocks, &_31$$19);
				if (zephir_is_true(&blockMode)) {
					if (Z_TYPE_P(&blocks) != IS_ARRAY) {
						ZEPHIR_INIT_NVAR(&blocks);
						array_init(&blocks);
					}
					if (Z_TYPE_P(&compilation) != IS_NULL) {
						zephir_array_append(&blocks, &compilation, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2736);
						ZEPHIR_INIT_NVAR(&compilation);
						ZVAL_NULL(&compilation);
					}
					zephir_array_update_zval(&blocks, &blockName, &blockStatements, PH_COPY | PH_SEPARATE);
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 911, &blocks);
				} else {
					if (Z_TYPE_P(&blockStatements) == IS_ARRAY) {
						if (extendsMode) {
							ZVAL_BOOL(&_33$$24, 1);
						} else {
							ZVAL_BOOL(&_33$$24, 0);
						}
						ZEPHIR_CALL_METHOD(&_32$$24, this_ptr, "statementList", &_34, 0, &blockStatements, &_33$$24);
						zephir_check_call_status();
						zephir_concat_self(&compilation, &_32$$24);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_10: ;
				ZEPHIR_OBS_NVAR(&path);
				zephir_array_fetch_string(&path, &statement, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2761);
				ZEPHIR_OBS_NVAR(&_35$$25);
				zephir_array_fetch_string(&_35$$25, &path, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2765);
				ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", &_36, 0, &_35$$25);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&extended);
				ZVAL_BOOL(&extended, 1);
				ZEPHIR_INIT_NVAR(&subCompiler);
				if (zephir_clone(&subCompiler, this_ptr) == FAILURE) {
					RETURN_MM();
				}
				ZEPHIR_CALL_METHOD(&tempCompilation, &subCompiler, "compile", NULL, 0, &finalPath, &extended);
				zephir_check_call_status();
				if (Z_TYPE_P(&tempCompilation) == IS_NULL) {
					ZEPHIR_CALL_METHOD(&_37$$26, &subCompiler, "getCompiledTemplatePath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&tempCompilation);
					zephir_file_get_contents(&tempCompilation, &_37$$26);
				}
				if (1) {
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 909, &__$true);
				} else {
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 909, &__$false);
				}
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 910, &tempCompilation);
				ZEPHIR_CPY_WRT(&blockMode, &extended);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_11: ;
				ZEPHIR_CALL_METHOD(&_38$$27, this_ptr, "compileInclude", &_39, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_38$$27);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_12: ;
				ZEPHIR_CALL_METHOD(&_40$$28, this_ptr, "compileDo", &_41, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_40$$28);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_13: ;
				ZEPHIR_CALL_METHOD(&_42$$29, this_ptr, "compileReturn", &_43, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_42$$29);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_14: ;
				if (extendsMode) {
					ZVAL_BOOL(&_45$$30, 1);
				} else {
					ZVAL_BOOL(&_45$$30, 0);
				}
				ZEPHIR_CALL_METHOD(&_44$$30, this_ptr, "compileAutoEscape", &_46, 0, &statement, &_45$$30);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_44$$30);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_15: ;
				zephir_concat_self_str(&compilation, SL("<?php continue; ?>"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_16: ;
				zephir_concat_self_str(&compilation, SL("<?php break; ?>"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_17: ;
				ZEPHIR_CALL_METHOD(&_47$$33, this_ptr, "compileForElse", &_48, 0);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_47$$33);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_18: ;
				if (extendsMode) {
					ZVAL_BOOL(&_50$$34, 1);
				} else {
					ZVAL_BOOL(&_50$$34, 0);
				}
				ZEPHIR_CALL_METHOD(&_49$$34, this_ptr, "compileMacro", &_51, 0, &statement, &_50$$34);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_49$$34);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_19: ;
				if (extendsMode) {
					ZVAL_BOOL(&_53$$35, 1);
				} else {
					ZVAL_BOOL(&_53$$35, 0);
				}
				ZEPHIR_CALL_METHOD(&_52$$35, this_ptr, "compileCall", &_54, 0, &statement, &_53$$35);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_52$$35);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_20: ;
				goto zephir_switch_0_end;
			zephir_switch_0_clause_21: ;
				ZEPHIR_INIT_NVAR(&_55$$37);
				object_init_ex(&_55$$37, phalcon_mvc_view_engine_volt_exception_ce);
				ZEPHIR_OBS_NVAR(&_56$$37);
				zephir_array_fetch_string(&_56$$37, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2867);
				ZEPHIR_OBS_NVAR(&_57$$37);
				zephir_array_fetch_string(&_57$$37, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2868);
				ZEPHIR_INIT_NVAR(&_58$$37);
				ZEPHIR_CONCAT_SVSVSV(&_58$$37, "Unknown statement ", &type, " in ", &_56$$37, " on line ", &_57$$37);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_55$$37, "__construct", &_7, 0, &_58$$37);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_55$$37, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2868);
				ZEPHIR_MM_RESTORE();
				return;
			zephir_switch_0_end: ;

		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_60 = 1;
		while (1) {
			if (_60) {
				_60 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_59, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_59)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&statement) != IS_ARRAY)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_engine_volt_exception_ce, "Corrupted statement", "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2630);
					return;
				}
				if (UNEXPECTED(!(zephir_array_isset_value_string(&statement, SL("type"))))) {
					ZEPHIR_INIT_NVAR(&_61$$40);
					object_init_ex(&_61$$40, phalcon_mvc_view_engine_volt_exception_ce);
					ZEPHIR_OBS_NVAR(&_62$$40);
					zephir_array_fetch_string(&_62$$40, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2638);
					ZEPHIR_OBS_NVAR(&_63$$40);
					zephir_array_fetch_string(&_63$$40, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2638);
					ZEPHIR_INIT_NVAR(&_64$$40);
					ZEPHIR_CONCAT_SVSV(&_64$$40, "Invalid statement in ", &_62$$40, " on line ", &_63$$40);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_61$$40, "__construct", &_7, 0, &_64$$40, &statement);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_61$$40, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2640);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (Z_TYPE_P(&extensions) == IS_ARRAY) {
					ZEPHIR_INIT_NVAR(&_65$$41);
					zephir_create_array(&_65$$41, 1, 0);
					zephir_array_fast_append(&_65$$41, &statement);
					ZEPHIR_INIT_NVAR(&_66$$41);
					ZVAL_STRING(&_66$$41, "compileStatement");
					ZEPHIR_CALL_METHOD(&tempCompilation, this_ptr, "fireExtensionEvent", &_10, 0, &_66$$41, &_65$$41);
					zephir_check_call_status();
					if (Z_TYPE_P(&tempCompilation) == IS_STRING) {
						zephir_concat_self(&compilation, &tempCompilation);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
				}
				ZEPHIR_OBS_NVAR(&type);
				zephir_array_fetch_string(&type, &statement, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2666);
				if (ZEPHIR_IS_LONG(&type, 357)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&type, 300)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&type, 302)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&type, 411)) { goto zephir_switch_1_clause_3; }
				if (ZEPHIR_IS_LONG(&type, 412)) { goto zephir_switch_1_clause_4; }
				if (ZEPHIR_IS_LONG(&type, 413)) { goto zephir_switch_1_clause_5; }
				if (ZEPHIR_IS_LONG(&type, 304)) { goto zephir_switch_1_clause_6; }
				if (ZEPHIR_IS_LONG(&type, 306)) { goto zephir_switch_1_clause_7; }
				if (ZEPHIR_IS_LONG(&type, 359)) { goto zephir_switch_1_clause_8; }
				if (ZEPHIR_IS_LONG(&type, 307)) { goto zephir_switch_1_clause_9; }
				if (ZEPHIR_IS_LONG(&type, 310)) { goto zephir_switch_1_clause_10; }
				if (ZEPHIR_IS_LONG(&type, 313)) { goto zephir_switch_1_clause_11; }
				if (ZEPHIR_IS_LONG(&type, 316)) { goto zephir_switch_1_clause_12; }
				if (ZEPHIR_IS_LONG(&type, 327)) { goto zephir_switch_1_clause_13; }
				if (ZEPHIR_IS_LONG(&type, 317)) { goto zephir_switch_1_clause_14; }
				if (ZEPHIR_IS_LONG(&type, 319)) { goto zephir_switch_1_clause_15; }
				if (ZEPHIR_IS_LONG(&type, 320)) { goto zephir_switch_1_clause_16; }
				if (ZEPHIR_IS_LONG(&type, 321)) { goto zephir_switch_1_clause_17; }
				if (ZEPHIR_IS_LONG(&type, 322)) { goto zephir_switch_1_clause_18; }
				if (ZEPHIR_IS_LONG(&type, 325)) { goto zephir_switch_1_clause_19; }
				if (ZEPHIR_IS_LONG(&type, 358)) { goto zephir_switch_1_clause_20; }
				goto zephir_switch_1_clause_21;
				zephir_switch_1_clause_0: ;
					ZEPHIR_OBS_NVAR(&_67$$43);
					zephir_array_fetch_string(&_67$$43, &statement, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2674);
					zephir_concat_self(&compilation, &_67$$43);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					if (extendsMode) {
						ZVAL_BOOL(&_69$$44, 1);
					} else {
						ZVAL_BOOL(&_69$$44, 0);
					}
					ZEPHIR_CALL_METHOD(&_68$$44, this_ptr, "compileIf", &_14, 0, &statement, &_69$$44);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_68$$44);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_2: ;
					ZEPHIR_CALL_METHOD(&_70$$45, this_ptr, "compileElseIf", &_16, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_70$$45);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					if (extendsMode) {
						ZVAL_BOOL(&_72$$46, 1);
					} else {
						ZVAL_BOOL(&_72$$46, 0);
					}
					ZEPHIR_CALL_METHOD(&_71$$46, this_ptr, "compileSwitch", &_19, 0, &statement, &_72$$46);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_71$$46);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_CALL_METHOD(&_73$$47, this_ptr, "compileCase", &_21, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_73$$47);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_5: ;
					ZVAL_BOOL(&_75$$48, 0);
					ZEPHIR_CALL_METHOD(&_74$$48, this_ptr, "compileCase", &_21, 0, &statement, &_75$$48);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_74$$48);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_6: ;
					if (extendsMode) {
						ZVAL_BOOL(&_77$$49, 1);
					} else {
						ZVAL_BOOL(&_77$$49, 0);
					}
					ZEPHIR_CALL_METHOD(&_76$$49, this_ptr, "compileForeach", &_26, 0, &statement, &_77$$49);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_76$$49);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_7: ;
					ZEPHIR_CALL_METHOD(&_78$$50, this_ptr, "compileSet", &_28, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_78$$50);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_8: ;
					ZEPHIR_CALL_METHOD(&_79$$51, this_ptr, "compileEcho", &_30, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_79$$51);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_9: ;
					ZEPHIR_OBS_NVAR(&blockName);
					zephir_array_fetch_string(&blockName, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2721);
					ZEPHIR_OBS_NVAR(&blockStatements);
					zephir_array_isset_string_fetch(&blockStatements, &statement, SL("block_statements"), 0);
					zephir_read_property_cached(&_80$$52, this_ptr, _zephir_prop_2, 911, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CPY_WRT(&blocks, &_80$$52);
					if (zephir_is_true(&blockMode)) {
						if (Z_TYPE_P(&blocks) != IS_ARRAY) {
							ZEPHIR_INIT_NVAR(&blocks);
							array_init(&blocks);
						}
						if (Z_TYPE_P(&compilation) != IS_NULL) {
							zephir_array_append(&blocks, &compilation, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2736);
							ZEPHIR_INIT_NVAR(&compilation);
							ZVAL_NULL(&compilation);
						}
						zephir_array_update_zval(&blocks, &blockName, &blockStatements, PH_COPY | PH_SEPARATE);
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 911, &blocks);
					} else {
						if (Z_TYPE_P(&blockStatements) == IS_ARRAY) {
							if (extendsMode) {
								ZVAL_BOOL(&_82$$57, 1);
							} else {
								ZVAL_BOOL(&_82$$57, 0);
							}
							ZEPHIR_CALL_METHOD(&_81$$57, this_ptr, "statementList", &_34, 0, &blockStatements, &_82$$57);
							zephir_check_call_status();
							zephir_concat_self(&compilation, &_81$$57);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_10: ;
					ZEPHIR_OBS_NVAR(&path);
					zephir_array_fetch_string(&path, &statement, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2761);
					ZEPHIR_OBS_NVAR(&_83$$58);
					zephir_array_fetch_string(&_83$$58, &path, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2765);
					ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", &_36, 0, &_83$$58);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&extended);
					ZVAL_BOOL(&extended, 1);
					ZEPHIR_INIT_NVAR(&subCompiler);
					if (zephir_clone(&subCompiler, this_ptr) == FAILURE) {
						RETURN_MM();
					}
					ZEPHIR_CALL_METHOD(&tempCompilation, &subCompiler, "compile", NULL, 0, &finalPath, &extended);
					zephir_check_call_status();
					if (Z_TYPE_P(&tempCompilation) == IS_NULL) {
						ZEPHIR_CALL_METHOD(&_84$$59, &subCompiler, "getCompiledTemplatePath", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&tempCompilation);
						zephir_file_get_contents(&tempCompilation, &_84$$59);
					}
					if (1) {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 909, &__$true);
					} else {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 909, &__$false);
					}
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 910, &tempCompilation);
					ZEPHIR_CPY_WRT(&blockMode, &extended);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_11: ;
					ZEPHIR_CALL_METHOD(&_85$$60, this_ptr, "compileInclude", &_39, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_85$$60);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_12: ;
					ZEPHIR_CALL_METHOD(&_86$$61, this_ptr, "compileDo", &_41, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_86$$61);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_13: ;
					ZEPHIR_CALL_METHOD(&_87$$62, this_ptr, "compileReturn", &_43, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_87$$62);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_14: ;
					if (extendsMode) {
						ZVAL_BOOL(&_89$$63, 1);
					} else {
						ZVAL_BOOL(&_89$$63, 0);
					}
					ZEPHIR_CALL_METHOD(&_88$$63, this_ptr, "compileAutoEscape", &_46, 0, &statement, &_89$$63);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_88$$63);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_15: ;
					zephir_concat_self_str(&compilation, SL("<?php continue; ?>"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_16: ;
					zephir_concat_self_str(&compilation, SL("<?php break; ?>"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_17: ;
					ZEPHIR_CALL_METHOD(&_90$$66, this_ptr, "compileForElse", &_48, 0);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_90$$66);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_18: ;
					if (extendsMode) {
						ZVAL_BOOL(&_92$$67, 1);
					} else {
						ZVAL_BOOL(&_92$$67, 0);
					}
					ZEPHIR_CALL_METHOD(&_91$$67, this_ptr, "compileMacro", &_51, 0, &statement, &_92$$67);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_91$$67);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_19: ;
					if (extendsMode) {
						ZVAL_BOOL(&_94$$68, 1);
					} else {
						ZVAL_BOOL(&_94$$68, 0);
					}
					ZEPHIR_CALL_METHOD(&_93$$68, this_ptr, "compileCall", &_54, 0, &statement, &_94$$68);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_93$$68);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_20: ;
					goto zephir_switch_1_end;
				zephir_switch_1_clause_21: ;
					ZEPHIR_INIT_NVAR(&_95$$70);
					object_init_ex(&_95$$70, phalcon_mvc_view_engine_volt_exception_ce);
					ZEPHIR_OBS_NVAR(&_96$$70);
					zephir_array_fetch_string(&_96$$70, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2867);
					ZEPHIR_OBS_NVAR(&_97$$70);
					zephir_array_fetch_string(&_97$$70, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2868);
					ZEPHIR_INIT_NVAR(&_98$$70);
					ZEPHIR_CONCAT_SVSVSV(&_98$$70, "Unknown statement ", &type, " in ", &_96$$70, " on line ", &_97$$70);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_95$$70, "__construct", &_7, 0, &_98$$70);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_95$$70, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2868);
					ZEPHIR_MM_RESTORE();
					return;
				zephir_switch_1_end: ;

		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&blockMode)) {
		zephir_read_property_cached(&level, this_ptr, _zephir_prop_4, 913, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_LONG(&level, 1)) {
			if (Z_TYPE_P(&compilation) != IS_NULL) {
				zephir_update_property_array_append(this_ptr, SL("blocks"), &compilation);
			}
		}
		RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("blockLevel")));
	}
	RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("level")));
	RETURN_CCTOR(&compilation);
}

/**
 * Compiles a block of statements
 *
 * @param array statements
 * @return string|array
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, statementListOrExtends)
{
	zend_bool isStatementList = 0, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statements, statements_sub, statement, *_0$$4, _1$$4, *_2$$4, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements_sub);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(statements)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statements);
	if (Z_TYPE_P(statements) != IS_ARRAY) {
		RETVAL_ZVAL(statements, 1, 0);
		RETURN_MM();
	}
	isStatementList = 1;
	if (!(zephir_array_isset_value_string(statements, SL("type")))) {
		if (Z_TYPE_P(statements) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$4);
			zephir_string_to_char_array(&_1$$4, statements);
			_0$$4 = &_1$$4;
		} else {
			_0$$4 = statements;
		}
		zephir_is_iterable(_0$$4, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2925);
		if (Z_TYPE_P(_0$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$4), _2$$4)
			{
				ZEPHIR_INIT_NVAR(&statement);
				ZVAL_COPY(&statement, _2$$4);
				if (Z_TYPE_P(&statement) != IS_ARRAY) {
					isStatementList = 0;
					break;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _0$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_4$$4 = 1;
			while (1) {
				if (_4$$4) {
					_4$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _0$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_3$$4, _0$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_3$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&statement, _0$$4, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&statement) != IS_ARRAY) {
						isStatementList = 0;
						break;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&statement);
	}
	if (isStatementList) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "statementList", NULL, 0, statements);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETVAL_ZVAL(statements, 1, 0);
	RETURN_MM();
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, isTagFactory)
{
	zend_bool _0$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *expression_param = NULL, left, leftValue, name, _1$$6;
	zval expression;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expression);
	ZVAL_UNDEF(&left);
	ZVAL_UNDEF(&leftValue);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_1$$6);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(expression, expression_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expression_param);
	zephir_get_arrval(&expression, expression_param);
	zephir_memory_observe(&name);
	if (zephir_array_isset_string_fetch(&name, &expression, SL("name"), 0)) {
		zephir_memory_observe(&left);
		if (zephir_array_isset_string_fetch(&left, &name, SL("left"), 0)) {
			zephir_memory_observe(&leftValue);
			if (zephir_array_isset_string_fetch(&leftValue, &left, SL("value"), 0)) {
				RETURN_MM_BOOL((ZEPHIR_IS_STRING_IDENTICAL(&leftValue, "tag")));
			} else {
				_0$$6 = zephir_array_isset_value_string(&left, SL("name"));
				if (_0$$6) {
					zephir_memory_observe(&_1$$6);
					zephir_array_fetch_string(&_1$$6, &left, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2962);
					_0$$6 = Z_TYPE_P(&_1$$6) == IS_ARRAY;
				}
				if (_0$$6) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "isTagFactory", NULL, 0, &left);
					zephir_check_call_status();
					RETURN_MM();
				}
			}
		}
	}
	RETURN_MM_BOOL(0);
}

zend_object *zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Compiler(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _12, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	

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
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("macros"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("macros"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("loopPointers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("loopPointers"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("functions"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("functions"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("forElsePointers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("forElsePointers"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("filters"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("filters"), &_11$$8);
		}
		zephir_read_property_ex(&_12, this_ptr, ZEND_STRL("extensions"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("extensions"), &_13$$9);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

