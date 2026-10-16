
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
#include "Zend/zend_closures.h"
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/main.h"
#include "kernel/variables.h"
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
 *
 * @phpstan-import-type mvc_volt_node from MvcTypes
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Compiler)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt, Compiler, phalcon, mvc_view_engine_volt_compiler, phalcon_mvc_view_engine_volt_compiler_method_entry, 0);

	{
		zval _zc0;
		ZVAL_BOOL(&_zc0, 0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("autoescape"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_BOOL, NULL, 0);
	}

	{
		zval _zc0;
		ZVAL_LONG(&_zc0, 0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("blockLevel"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_LONG, NULL, 0);
	}

	/**
	 * @var array|null
	 *
	 * TODO: Make array only?
	 *
	 * @phpstan-var array<array-key, mixed>|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("blocks"), ZEND_ACC_PROTECTED);
	{
		zval _zc0;
		ZVAL_NULL(&_zc0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("container"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_NULL, SL("Phalcon\\Di\\DiInterface"));
	}

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
	{
		zval _zc0;
		ZVAL_LONG(&_zc0, 0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("exprLevel"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_LONG, NULL, 0);
	}

	{
		zval _zc0;
		ZVAL_BOOL(&_zc0, 0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("extended"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_BOOL, NULL, 0);
	}

	/**
	 * @var array|bool
	 *
	 * TODO: Make it always array
	 *
	 * @phpstan-var array<array-key, mixed>|bool|string
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("extendedBlocks"), ZEND_ACC_PROTECTED);
	/**
	 * @phpstan-var list<object>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("extensions"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * @phpstan-var array<string, mixed>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("filters"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	{
		zval _zc0;
		ZVAL_LONG(&_zc0, 0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("foreachLevel"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_LONG, NULL, 0);
	}

	/**
	 * @phpstan-var array<int, string>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("forElsePointers"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * @phpstan-var array<string, mixed>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("functions"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	{
		zval _zc0;
		ZVAL_LONG(&_zc0, 0);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("level"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_LONG, NULL, 0);
	}

	/**
	 * @phpstan-var array<int, int>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("loopPointers"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * @phpstan-var array<string, string>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("macros"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * @phpstan-var array<string, mixed>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("options"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * @var string
	 *
	 * @phpstan-var Closure|string
	 */
	zend_declare_property_string(phalcon_mvc_view_engine_volt_compiler_ce, SL("prefix"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var ViewBaseInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("view"), ZEND_ACC_PROTECTED);
	/**
	 * The virtual path of each template path (see compile())
	 *
	 * @phpstan-var array<string, string>
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("virtualPaths"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * Files inlined into the template being compiled: path => mtime
	 *
	 * @var array
	 */
	{
		zval _zc0;
		array_init_size(&_zc0, 1);
		zephir_declare_typed_property(phalcon_mvc_view_engine_volt_compiler_ce, SL("dependencies"), &_zc0, ZEND_ACC_PROTECTED, MAY_BE_ARRAY, NULL, 0);
	}

	/**
	 * Parent template for a child compiled against a parent chosen at render
	 * time ({% extends layoutVar %})
	 *
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("extendsOverride"), ZEND_ACC_PROTECTED);
	/**
	 * Runtime functions, filters and tests (shared with the engine)
	 *
	 * @var Registry|null
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_compiler_ce, SL("registry"), ZEND_ACC_PROTECTED);
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 912, view);
}

/**
 * Registers a Volt's extension
 *
 * @var mixed extension
 *
 * @return static
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, addExtension)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *extension, extension_sub, _0$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extension_sub);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(extension)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &extension);
	if (UNEXPECTED(Z_TYPE_P(extension) != IS_OBJECT)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_invalidextension_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 204);
		ZEPHIR_MM_RESTORE();
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
 * @return static
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
 * @return static
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
 *
 * @phpstan-param mvc_volt_node $expr
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
	zephir_get_arrval(&expr, expr_param);
	ZEPHIR_INIT_VAR(&exprCode);
	ZVAL_STRING(&exprCode, "");
	zephir_memory_observe(&left);
	zephir_array_fetch_string(&left, &expr, SL("left"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 265);
	zephir_memory_observe(&_0);
	zephir_array_fetch_string(&_0, &left, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 267);
	if (ZEPHIR_IS_LONG(&_0, 265)) {
		zephir_memory_observe(&variable);
		zephir_array_fetch_string(&variable, &left, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 268);
		if (ZEPHIR_IS_STRING(&variable, "loop")) {
			zephir_memory_observe(&level);
			zephir_read_property_cached(&level, this_ptr, _zephir_prop_0, 913, PH_NOISY_CC);
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
			zephir_read_property_cached(&_3$$5, this_ptr, _zephir_prop_1, 914, PH_NOISY_CC | PH_READONLY);
			_4$$5 = Z_TYPE_P(&_3$$5) != IS_NULL;
			if (_4$$5) {
				zephir_read_property_cached(&_5$$5, this_ptr, _zephir_prop_1, 914, PH_NOISY_CC | PH_READONLY);
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
		zephir_array_fetch_string(&leftType, &left, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 290);
		_9$$8 = ZEPHIR_CHAR_VALUE(&leftType) != '.';
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
	zephir_array_fetch_string(&right, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 301);
	zephir_memory_observe(&_10);
	zephir_array_fetch_string(&_10, &right, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 303);
	if (ZEPHIR_IS_LONG(&_10, 265)) {
		zephir_memory_observe(&_11$$11);
		zephir_array_fetch_string(&_11$$11, &right, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 304);
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
	zval _23$$28, _33$$38;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _21, _28, _35, _36, _37, _39$$41;
	zval templatePath_zv, *extendsMode_param = NULL, __$false, blocksCode, compilation, compileAlways, compiledExtension, compiledPath, compiledSeparator, options, prefix, realTemplatePath, stat, templateSepPath, compiledTemplatePath, _0, _27, _1$$4, _2$$4, _3$$6, _4$$6, _5$$6, _6$$8, _7$$8, _8$$8, _9$$10, _10$$10, _11$$13, _12$$13, _13$$15, _14$$15, _15$$15, _16$$17, _17$$17, _18$$19, _19$$19, _20$$19, _22$$22, _24$$28, _25$$29, _26$$30, _29$$31, _30$$33, _31$$34, _32$$37, _34$$39, _38$$41, _40$$41, _41$$41, _42$$42;
	zend_string *templatePath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templatePath_zv);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&blocksCode);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&compileAlways);
	ZVAL_UNDEF(&compiledExtension);
	ZVAL_UNDEF(&compiledPath);
	ZVAL_UNDEF(&compiledSeparator);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&realTemplatePath);
	ZVAL_UNDEF(&stat);
	ZVAL_UNDEF(&templateSepPath);
	ZVAL_UNDEF(&compiledTemplatePath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$10);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_11$$13);
	ZVAL_UNDEF(&_12$$13);
	ZVAL_UNDEF(&_13$$15);
	ZVAL_UNDEF(&_14$$15);
	ZVAL_UNDEF(&_15$$15);
	ZVAL_UNDEF(&_16$$17);
	ZVAL_UNDEF(&_17$$17);
	ZVAL_UNDEF(&_18$$19);
	ZVAL_UNDEF(&_19$$19);
	ZVAL_UNDEF(&_20$$19);
	ZVAL_UNDEF(&_22$$22);
	ZVAL_UNDEF(&_24$$28);
	ZVAL_UNDEF(&_25$$29);
	ZVAL_UNDEF(&_26$$30);
	ZVAL_UNDEF(&_29$$31);
	ZVAL_UNDEF(&_30$$33);
	ZVAL_UNDEF(&_31$$34);
	ZVAL_UNDEF(&_32$$37);
	ZVAL_UNDEF(&_34$$39);
	ZVAL_UNDEF(&_38$$41);
	ZVAL_UNDEF(&_40$$41);
	ZVAL_UNDEF(&_41$$41);
	ZVAL_UNDEF(&_42$$42);
	ZVAL_UNDEF(&_23$$28);
	ZVAL_UNDEF(&_33$$38);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("virtualPaths", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("compiledTemplatePath", 20, 1);
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
	ZVAL_STRING(&compiledTemplatePath, "");
	ZEPHIR_INIT_VAR(&compilation);
	ZVAL_NULL(&compilation);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 915, PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, phalcon_mvc_view_engine_volt_exceptions_invalidoptiontype_ce);
		ZEPHIR_INIT_VAR(&_4$$6);
		ZVAL_STRING(&_4$$6, "always");
		ZEPHIR_INIT_VAR(&_5$$6);
		ZVAL_STRING(&_5$$6, "bool value");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 0, &_4$$6, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 353);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&prefix);
	if (!(zephir_array_isset_string_fetch(&prefix, &options, SL("prefix"), 0))) {
		ZEPHIR_INIT_NVAR(&prefix);
		ZVAL_STRING(&prefix, "");
	}
	if (UNEXPECTED(Z_TYPE_P(&prefix) != IS_STRING)) {
		ZEPHIR_INIT_VAR(&_6$$8);
		object_init_ex(&_6$$8, phalcon_mvc_view_engine_volt_exceptions_invalidoptiontype_ce);
		ZEPHIR_INIT_VAR(&_7$$8);
		ZVAL_STRING(&_7$$8, "prefix");
		ZEPHIR_INIT_VAR(&_8$$8);
		ZVAL_STRING(&_8$$8, "string");
		ZEPHIR_CALL_METHOD(NULL, &_6$$8, "__construct", NULL, 0, &_7$$8, &_8$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$8, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 364);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&compiledPath);
	if (!(zephir_array_isset_string_fetch(&compiledPath, &options, SL("path"), 0))) {
		ZEPHIR_OBS_NVAR(&compiledPath);
		if (zephir_array_isset_string_fetch(&compiledPath, &options, SL("compiledPath"), 0)) {
			ZEPHIR_INIT_VAR(&_9$$10);
			ZVAL_STRING(&_9$$10, "The 'compiledPath' option is deprecated. Use 'path' instead.");
			ZVAL_LONG(&_10$$10, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_9$$10, &_10$$10);
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
			ZEPHIR_INIT_VAR(&_11$$13);
			ZVAL_STRING(&_11$$13, "The 'compiledSeparator' option is deprecated. Use 'separator' instead.");
			ZVAL_LONG(&_12$$13, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_11$$13, &_12$$13);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&compiledSeparator);
			ZVAL_STRING(&compiledSeparator, "%%");
		}
	}
	if (UNEXPECTED(Z_TYPE_P(&compiledSeparator) != IS_STRING)) {
		ZEPHIR_INIT_VAR(&_13$$15);
		object_init_ex(&_13$$15, phalcon_mvc_view_engine_volt_exceptions_invalidoptiontype_ce);
		ZEPHIR_INIT_VAR(&_14$$15);
		ZVAL_STRING(&_14$$15, "separator");
		ZEPHIR_INIT_VAR(&_15$$15);
		ZVAL_STRING(&_15$$15, "string");
		ZEPHIR_CALL_METHOD(NULL, &_13$$15, "__construct", NULL, 0, &_14$$15, &_15$$15);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_13$$15, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 397);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&compiledExtension);
	if (!(zephir_array_isset_string_fetch(&compiledExtension, &options, SL("extension"), 0))) {
		ZEPHIR_OBS_NVAR(&compiledExtension);
		if (zephir_array_isset_string_fetch(&compiledExtension, &options, SL("compiledExtension"), 0)) {
			ZEPHIR_INIT_VAR(&_16$$17);
			ZVAL_STRING(&_16$$17, "The 'compiledExtension' option is deprecated. Use 'extension' instead.");
			ZVAL_LONG(&_17$$17, 16384);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_16$$17, &_17$$17);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&compiledExtension);
			ZVAL_STRING(&compiledExtension, ".php");
		}
	}
	if (UNEXPECTED(Z_TYPE_P(&compiledExtension) != IS_STRING)) {
		ZEPHIR_INIT_VAR(&_18$$19);
		object_init_ex(&_18$$19, phalcon_mvc_view_engine_volt_exceptions_invalidoptiontype_ce);
		ZEPHIR_INIT_VAR(&_19$$19);
		ZVAL_STRING(&_19$$19, "extension");
		ZEPHIR_INIT_VAR(&_20$$19);
		ZVAL_STRING(&_20$$19, "string");
		ZEPHIR_CALL_METHOD(NULL, &_18$$19, "__construct", NULL, 0, &_19$$19, &_20$$19);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_18$$19, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 415);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&stat);
	if (!(zephir_array_isset_string_fetch(&stat, &options, SL("stat"), 0))) {
		ZEPHIR_INIT_NVAR(&stat);
		ZVAL_BOOL(&stat, 1);
	}
	if (Z_TYPE_P(&compiledPath) == IS_STRING) {
		if (!(ZEPHIR_IS_EMPTY(&compiledPath))) {
			zephir_memory_observe(&templateSepPath);
			zephir_read_property_cached(&_22$$22, this_ptr, _zephir_prop_1, 916, PH_NOISY_CC | PH_READONLY);
			if (!(zephir_array_isset_fetch(&templateSepPath, &_22$$22, &templatePath_zv, 0))) {
				ZEPHIR_CALL_FUNCTION(&realTemplatePath, "realpath", NULL, 83, &templatePath_zv);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&templateSepPath);
				zephir_prepare_virtual_path(&templateSepPath, &realTemplatePath, &compiledSeparator);
				if (Z_TYPE_P(&realTemplatePath) == IS_STRING) {
					zephir_update_property_array(this_ptr, SL("virtualPaths"), &templatePath_zv, &templateSepPath);
				}
			}
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
		_21 = Z_TYPE_P(&compiledPath) == IS_OBJECT;
		if (_21) {
			_21 = zephir_is_instance_of(&compiledPath, SL("Closure"));
		}
		if (_21) {
			ZEPHIR_INIT_VAR(&_23$$28);
			zephir_create_array(&_23$$28, 3, 0);
			zephir_array_fast_append(&_23$$28, &templatePath_zv);
			zephir_array_fast_append(&_23$$28, &options);
			ZEPHIR_INIT_VAR(&_24$$28);
			ZVAL_BOOL(&_24$$28, extendsMode);
			zephir_array_fast_append(&_23$$28, &_24$$28);
			ZEPHIR_INIT_NVAR(&compiledTemplatePath);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&compiledTemplatePath, &compiledPath, &_23$$28);
			zephir_check_call_status();
			if (UNEXPECTED(Z_TYPE_P(&compiledTemplatePath) != IS_STRING)) {
				ZEPHIR_INIT_VAR(&_25$$29);
				object_init_ex(&_25$$29, phalcon_mvc_view_engine_volt_exceptions_invalidpathclosurereturn_ce);
				ZEPHIR_CALL_METHOD(NULL, &_25$$29, "__construct", NULL, 0);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_25$$29, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 474);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_VAR(&_26$$30);
			object_init_ex(&_26$$30, phalcon_mvc_view_engine_volt_exceptions_invalidpathtype_ce);
			ZEPHIR_CALL_METHOD(NULL, &_26$$30, "__construct", NULL, 0);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_26$$30, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 477);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_27, this_ptr, "phpFileExists", NULL, 0, &compiledTemplatePath);
	zephir_check_call_status();
	_28 = !zephir_is_true(&_27);
	if (!(_28)) {
		_28 = zephir_is_true(&compileAlways);
	}
	if (_28) {
		if (extendsMode) {
			ZVAL_BOOL(&_29$$31, 1);
		} else {
			ZVAL_BOOL(&_29$$31, 0);
		}
		ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileFile", NULL, 0, &templatePath_zv, &compiledTemplatePath, &_29$$31);
		zephir_check_call_status();
	} else {
		if (ZEPHIR_IS_TRUE_IDENTICAL(&stat)) {
			ZEPHIR_INIT_VAR(&_30$$33);
			if (zephir_compare_mtime(&templatePath_zv, &compiledTemplatePath)) {
				if (extendsMode) {
					ZVAL_BOOL(&_31$$34, 1);
				} else {
					ZVAL_BOOL(&_31$$34, 0);
				}
				ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileFile", NULL, 0, &templatePath_zv, &compiledTemplatePath, &_31$$34);
				zephir_check_call_status();
			} else {
				if (extendsMode) {
					ZEPHIR_CALL_METHOD(&blocksCode, this_ptr, "phpFileGetContents", NULL, 0, &compiledTemplatePath);
					zephir_check_call_status();
					if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&blocksCode))) {
						ZEPHIR_INIT_VAR(&_32$$37);
						object_init_ex(&_32$$37, phalcon_mvc_view_engine_volt_exceptions_cannotopencompiledfile_ce);
						ZEPHIR_CALL_METHOD(NULL, &_32$$37, "__construct", NULL, 0, &compiledTemplatePath);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_32$$37, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 514);
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (zephir_is_true(&blocksCode)) {
						ZEPHIR_INIT_VAR(&_33$$38);
						zephir_create_array(&_33$$38, 1, 0);
						zephir_array_update_string(&_33$$38, SL("allowed_classes"), &__$false, PH_COPY | PH_SEPARATE);
						ZEPHIR_CALL_FUNCTION(&compilation, "unserialize", NULL, 15, &blocksCode, &_33$$38);
						zephir_check_call_status();
						if (Z_TYPE_P(&compilation) != IS_ARRAY) {
							if (extendsMode) {
								ZVAL_BOOL(&_34$$39, 1);
							} else {
								ZVAL_BOOL(&_34$$39, 0);
							}
							ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileFile", NULL, 0, &templatePath_zv, &compiledTemplatePath, &_34$$39);
							zephir_check_call_status();
						}
					} else {
						ZEPHIR_INIT_NVAR(&compilation);
						array_init(&compilation);
					}
				}
			}
		}
	}
	_35 = Z_TYPE_P(&compilation) == IS_NULL;
	if (_35) {
		_35 = !extendsMode;
	}
	_36 = _35;
	if (_36) {
		_36 = !ZEPHIR_IS_FALSE_IDENTICAL(&stat);
	}
	_37 = _36;
	if (_37) {
		_37 = Z_TYPE_P(&compiledTemplatePath) == IS_STRING;
	}
	if (_37) {
		ZEPHIR_CALL_METHOD(&_38$$41, this_ptr, "phpFileExists", NULL, 0, &compiledTemplatePath);
		zephir_check_call_status();
		_39$$41 = zephir_is_true(&_38$$41);
		if (_39$$41) {
			ZEPHIR_CALL_METHOD(&_41$$41, this_ptr, "getSignature", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_CE_STATIC(&_40$$41, phalcon_mvc_view_engine_volt_dependencies_ce, "staleReason", NULL, 0, &compiledTemplatePath, &_41$$41);
			zephir_check_call_status();
			_39$$41 = Z_TYPE_P(&_40$$41) != IS_NULL;
		}
		if (_39$$41) {
			if (extendsMode) {
				ZVAL_BOOL(&_42$$42, 1);
			} else {
				ZVAL_BOOL(&_42$$42, 0);
			}
			ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileFile", NULL, 0, &templatePath_zv, &compiledTemplatePath, &_42$$42);
			zephir_check_call_status();
		}
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 917, &compiledTemplatePath);
	RETURN_CCTOR(&compilation);
}

/**
 * Compiles a "autoescape" statement returning PHP code
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @return string
 *
 * @phpstan-param mvc_volt_node $statement
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileAutoEscape)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL, autoescape, oldAutoescape, compilation, _1, _2, _0$$3;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&autoescape);
	ZVAL_UNDEF(&oldAutoescape);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$3);
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
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&autoescape);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&autoescape, &statement, SL("enable"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 580);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&oldAutoescape);
	zephir_read_property_cached(&oldAutoescape, this_ptr, _zephir_prop_0, 918, PH_NOISY_CC);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 918, &autoescape);
	zephir_array_fetch_string(&_1, &statement, SL("block_statements"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 590);
	if (extendsMode) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	ZEPHIR_CALL_METHOD(&compilation, this_ptr, "statementList", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 918, &oldAutoescape);
	RETURN_CCTOR(&compilation);
}

/**
 * Compiles calls to macros
 *
 * @param array statement
 * @param bool extendsMode
 *
 * @phpstan-param mvc_volt_node $statement
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _1, _2, _8;
	zval *statement_param = NULL, *extendsMode_param = NULL, name, arguments, caller, macroName, argumentsCode, _3, _9, _10, _0$$3, _4$$4, _5$$4, _6$$4, _7$$4;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&caller);
	ZVAL_UNDEF(&macroName);
	ZVAL_UNDEF(&argumentsCode);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &statement_param, &extendsMode_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&name);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&name, &statement, SL("name"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 612);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_1 = Z_TYPE_P(&name) != IS_ARRAY;
	if (!(_1)) {
		_1 = !(zephir_array_isset_value_string(&name, SL("type")));
	}
	_2 = _1;
	if (!(_2)) {
		zephir_memory_observe(&_3);
		zephir_array_fetch_string(&_3, &name, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 615);
		_2 = !ZEPHIR_IS_LONG(&_3, 265);
	}
	if (UNEXPECTED(_2)) {
		ZEPHIR_INIT_VAR(&_4$$4);
		object_init_ex(&_4$$4, phalcon_mvc_view_engine_volt_exception_ce);
		zephir_array_fetch_string(&_5$$4, &statement, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 617);
		zephir_array_fetch_string(&_6$$4, &statement, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 618);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_SVSV(&_7$$4, "{% call %} needs a macro name in ", &_5$$4, " on line ", &_6$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 0, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 618);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&macroName);
	zephir_array_fetch_string(&macroName, &name, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 621);
	zephir_memory_observe(&arguments);
	if (zephir_array_isset_string_fetch(&arguments, &statement, SL("arguments"), 0)) {
		ZEPHIR_CALL_METHOD(&argumentsCode, this_ptr, "expression", NULL, 0, &arguments);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&argumentsCode);
		ZVAL_STRING(&argumentsCode, "");
	}
	zephir_memory_observe(&caller);
	_8 = !(zephir_array_isset_string_fetch(&caller, &statement, SL("caller"), 0));
	if (!(_8)) {
		_8 = Z_TYPE_P(&caller) != IS_ARRAY;
	}
	if (_8) {
		ZEPHIR_INIT_NVAR(&caller);
		array_init(&caller);
	}
	if (extendsMode) {
		ZVAL_BOOL(&_10, 1);
	} else {
		ZVAL_BOOL(&_10, 0);
	}
	ZEPHIR_CALL_METHOD(&_9, this_ptr, "statementList", NULL, 0, &caller, &_10);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVSVS(return_value, "<?php $this->pushMacroCaller((function (array $__volt_vars) { return function () use ($__volt_vars) { extract($__volt_vars); ?>", &_9, "<?php }; })(get_defined_vars())); $this->callMacro('", &macroName, "', [", &argumentsCode, "]); $this->popMacroCaller(); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a "case"/"default" clause returning PHP code
 *
 * @param array statement
 * @param bool caseClause
 *
 * @return string
 *
 * @phpstan-param mvc_volt_node $statement
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileCase)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool caseClause;
	zval *statement_param = NULL, *caseClause_param = NULL, expr, _1, _0$$4;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$4);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(caseClause)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &caseClause_param);
	zephir_get_arrval(&statement, statement_param);
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
		object_init_ex(&_0$$4, phalcon_mvc_view_engine_volt_exceptions_corruptedstatementwithdata_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$4, "__construct", NULL, 0, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 667);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php case ", &_1, ": ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a "do" statement returning PHP code
 *
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileDo)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, _1, _0$$3;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 691);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php ", &_1, "; ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles a `{{` `}}` statement returning PHP code
 *
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileEcho)
{
	zend_bool _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, exprCode, name, _1, _6, _8, _0$$3, _2$$4, _4$$4, _3$$5, _5$$6;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$6);
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
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatementwithdata_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 715);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	zephir_memory_observe(&_1);
	zephir_array_fetch_string(&_1, &expr, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 723);
	if (ZEPHIR_IS_LONG(&_1, 350)) {
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "isTagFactory", NULL, 0, &expr);
		zephir_check_call_status();
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_2$$4)) {
			ZVAL_BOOL(&_3$$5, 1);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", NULL, 0, &expr, &_3$$5);
			zephir_check_call_status();
		}
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 728);
		zephir_memory_observe(&_4$$4);
		zephir_array_fetch_string(&_4$$4, &name, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 729);
		if (ZEPHIR_IS_LONG(&_4$$4, 265)) {
			zephir_memory_observe(&_5$$6);
			zephir_array_fetch_string(&_5$$6, &name, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 734);
			if (ZEPHIR_IS_STRING(&_5$$6, "super")) {
				RETURN_CCTOR(&exprCode);
			}
		}
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_0, 918, PH_NOISY_CC | PH_READONLY);
	_7 = zephir_is_true(&_6);
	if (_7) {
		ZEPHIR_CALL_METHOD(&_8, this_ptr, "isSafeExpression", NULL, 0, &expr);
		zephir_check_call_status();
		_7 = !zephir_is_true(&_8);
	}
	if (_7) {
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
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileElseIf)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, _1, _0$$3;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatementwithdata_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 767);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php } elseif (", &_1, ") { ?>");
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
 *
 * @phpstan-return array<array-key, mixed>|string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileFile)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _0;
	zval path_zv, compiledPath_zv, *extendsMode_param = NULL, viewCode, compilation, finalCompilation, _2, _5, _6, _7, _1$$3, _3$$4, _4$$5, _8$$8, _9$$9, _10$$9;
	zend_string *path = NULL, *compiledPath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&compiledPath_zv);
	ZVAL_UNDEF(&viewCode);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&finalCompilation);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$9);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentPath", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("dependencies", 12, 1);
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
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_view_engine_volt_exceptions_templatepathcollision_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 800);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "phpFileExists", NULL, 0, &path_zv);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_2))) {
		ZEPHIR_INIT_VAR(&_3$$4);
		object_init_ex(&_3$$4, phalcon_mvc_view_engine_volt_exceptions_templatefilenotfound_ce);
		ZEPHIR_CALL_METHOD(NULL, &_3$$4, "__construct", NULL, 0, &path_zv);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 807);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&viewCode, this_ptr, "phpFileGetContents", NULL, 0, &path_zv);
	zephir_check_call_status();
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&viewCode))) {
		ZEPHIR_INIT_VAR(&_4$$5);
		object_init_ex(&_4$$5, phalcon_mvc_view_engine_volt_exceptions_templatefilenotopenable_ce);
		ZEPHIR_CALL_METHOD(NULL, &_4$$5, "__construct", NULL, 0, &path_zv);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$5, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 817);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 919, &path_zv);
	ZEPHIR_INIT_VAR(&_5);
	array_init(&_5);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 920, &_5);
	if (extendsMode) {
		ZVAL_BOOL(&_6, 1);
	} else {
		ZVAL_BOOL(&_6, 0);
	}
	ZEPHIR_CALL_METHOD(&compilation, this_ptr, "compileSource", NULL, 0, &viewCode, &_6);
	zephir_check_call_status();
	if (Z_TYPE_P(&compilation) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&finalCompilation, "serialize", NULL, 14, &compilation);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&finalCompilation, &compilation);
	}
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "phpFilePutContents", NULL, 0, &compiledPath_zv, &finalCompilation);
	zephir_check_call_status();
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&_7))) {
		ZEPHIR_INIT_VAR(&_8$$8);
		object_init_ex(&_8$$8, phalcon_mvc_view_engine_volt_exceptions_voltdirectorynotwritable_ce);
		ZEPHIR_CALL_METHOD(NULL, &_8$$8, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_8$$8, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 839);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (Z_TYPE_P(&compilation) == IS_STRING) {
		zephir_read_property_cached(&_9$$9, this_ptr, _zephir_prop_1, 920, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_10$$9, this_ptr, "getSignature", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_CE_STATIC(NULL, phalcon_mvc_view_engine_volt_dependencies_ce, "write", NULL, 0, &compiledPath_zv, &_9$$9, &_10$$9);
		zephir_check_call_status();
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
 *
 * @phpstan-param mvc_volt_node $statement
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileForeach)
{
	zval compilation;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _6$$4;
	zval *statement_param = NULL, *extendsMode_param = NULL, prefix, level, prefixLevel, expr, exprCode, bstatement, type, blockStatements, forElse, code, loopContext, iterator, key, ifExpr, variable, _8, _0$$3, *_1$$4, _2$$4, *_3$$4, _5$$4, _4$$7, _7$$10, _9$$11, _10$$11, _11$$11, _12$$11, _13$$11, _14$$11, _15$$11, _16$$11, _17$$11, _18$$13, _19$$14, _20$$15, _21$$15, _22$$17, _23$$17, _24$$17, _25$$17, _26$$17, _27$$17, _28$$18, _29$$22;
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
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_20$$15);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_22$$17);
	ZVAL_UNDEF(&_23$$17);
	ZVAL_UNDEF(&_24$$17);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_28$$18);
	ZVAL_UNDEF(&_29$$22);
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
	zephir_get_arrval(&statement, statement_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	if (UNEXPECTED(!(zephir_array_isset_value_string(&statement, SL("expr"))))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 870);
		ZEPHIR_MM_RESTORE();
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
	zephir_read_property_cached(&level, this_ptr, _zephir_prop_0, 913, PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&prefixLevel);
	ZEPHIR_CONCAT_VV(&prefixLevel, &prefix, &level);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&expr);
	zephir_array_fetch_string(&expr, &statement, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 888);
	ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	zephir_memory_observe(&blockStatements);
	zephir_array_fetch_string(&blockStatements, &statement, SL("block_statements"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 894);
	ZEPHIR_INIT_NVAR(&forElse);
	ZVAL_BOOL(&forElse, 0);
	if (Z_TYPE_P(&blockStatements) == IS_ARRAY) {
		if (Z_TYPE_P(&blockStatements) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_2$$4);
			zephir_string_to_char_array(&_2$$4, &blockStatements);
			_1$$4 = &_2$$4;
		} else {
			_1$$4 = &blockStatements;
		}
		zephir_is_iterable(_1$$4, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 914);
		if (Z_TYPE_P(_1$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1$$4), _3$$4)
			{
				ZEPHIR_INIT_NVAR(&bstatement);
				ZVAL_COPY(&bstatement, _3$$4);
				ZEPHIR_OBS_NVAR(&type);
				if (!(zephir_array_isset_string_fetch(&type, &bstatement, SL("type"), 0))) {
					break;
				}
				if (ZEPHIR_IS_LONG(&type, 321)) {
					ZEPHIR_INIT_NVAR(&_4$$7);
					ZEPHIR_CONCAT_SVS(&_4$$7, "<?php $", &prefixLevel, "iterated = false; ?>");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_4$$7);
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
				ZEPHIR_CALL_METHOD(&bstatement, _1$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&type);
					if (!(zephir_array_isset_string_fetch(&type, &bstatement, SL("type"), 0))) {
						break;
					}
					if (ZEPHIR_IS_LONG(&type, 321)) {
						ZEPHIR_INIT_NVAR(&_7$$10);
						ZEPHIR_CONCAT_SVS(&_7$$10, "<?php $", &prefixLevel, "iterated = false; ?>");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&compilation, &_7$$10);
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
		ZVAL_BOOL(&_8, 1);
	} else {
		ZVAL_BOOL(&_8, 0);
	}
	ZEPHIR_CALL_METHOD(&code, this_ptr, "statementList", NULL, 0, &blockStatements, &_8);
	zephir_check_call_status();
	zephir_memory_observe(&loopContext);
	zephir_read_property_cached(&loopContext, this_ptr, _zephir_prop_1, 921, PH_NOISY_CC);
	if (zephir_array_isset_value(&loopContext, &level)) {
		ZEPHIR_INIT_VAR(&_9$$11);
		ZEPHIR_CONCAT_SVSVS(&_9$$11, "<?php $", &prefixLevel, "iterator = ", &exprCode, "; ");
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
		ZEPHIR_CONCAT_SVS(&_10$$11, "$", &prefixLevel, "incr = 0; ");
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
		ZEPHIR_CONCAT_SVS(&_11$$11, "$", &prefixLevel, "loop = new stdClass(); ");
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
		ZEPHIR_CONCAT_SVSVS(&_12$$11, "$", &prefixLevel, "loop->self = &$", &prefixLevel, "loop; ");
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
		ZEPHIR_CONCAT_SVSVS(&_13$$11, "$", &prefixLevel, "loop->length = count($", &prefixLevel, "iterator); ");
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
		ZEPHIR_CONCAT_SVS(&_14$$11, "$", &prefixLevel, "loop->index = 1; ");
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
		ZEPHIR_CONCAT_SVS(&_15$$11, "$", &prefixLevel, "loop->index0 = 1; ");
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
		ZEPHIR_CONCAT_SVSVS(&_16$$11, "$", &prefixLevel, "loop->revindex = $", &prefixLevel, "loop->length; ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_16$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_17$$11);
		ZEPHIR_CONCAT_SVSVS(&_17$$11, "$", &prefixLevel, "loop->revindex0 = $", &prefixLevel, "loop->length - 1; ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_17$$11);
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
	zephir_array_fetch_string(&variable, &statement, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 944);
	zephir_memory_observe(&key);
	if (zephir_array_isset_string_fetch(&key, &statement, SL("key"), 0)) {
		ZEPHIR_INIT_VAR(&_18$$13);
		ZEPHIR_CONCAT_SVSVSVS(&_18$$13, "<?php foreach (", &iterator, " as $", &key, " => $", &variable, ") { ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_18$$13);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_VAR(&_19$$14);
		ZEPHIR_CONCAT_SVSVS(&_19$$14, "<?php foreach (", &iterator, " as $", &variable, ") { ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_19$$14);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_memory_observe(&ifExpr);
	if (zephir_array_isset_string_fetch(&ifExpr, &statement, SL("if_expr"), 0)) {
		ZEPHIR_CALL_METHOD(&_20$$15, this_ptr, "expression", NULL, 0, &ifExpr);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_21$$15);
		ZEPHIR_CONCAT_SVS(&_21$$15, "if (", &_20$$15, ") { ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_21$$15);
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
		ZEPHIR_INIT_VAR(&_22$$17);
		ZEPHIR_CONCAT_SVSVS(&_22$$17, "<?php $", &prefixLevel, "loop->first = ($", &prefixLevel, "incr == 0); ");
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
		ZEPHIR_CONCAT_SVSVS(&_23$$17, "$", &prefixLevel, "loop->index = $", &prefixLevel, "incr + 1; ");
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
		ZEPHIR_CONCAT_SVSVS(&_24$$17, "$", &prefixLevel, "loop->index0 = $", &prefixLevel, "incr; ");
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
		ZEPHIR_CONCAT_SVSVSVS(&_25$$17, "$", &prefixLevel, "loop->revindex = $", &prefixLevel, "loop->length - $", &prefixLevel, "incr; ");
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
		ZEPHIR_CONCAT_SVSVSVS(&_26$$17, "$", &prefixLevel, "loop->revindex0 = $", &prefixLevel, "loop->length - ($", &prefixLevel, "incr + 1); ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_26$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_27$$17);
		ZEPHIR_CONCAT_SVSVSVS(&_27$$17, "$", &prefixLevel, "loop->last = ($", &prefixLevel, "incr == ($", &prefixLevel, "loop->length - 1)); ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_27$$17);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(&forElse) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_28$$18);
		ZEPHIR_CONCAT_SVS(&_28$$18, "<?php $", &forElse, "iterated = true; ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_28$$18);
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
			ZEPHIR_INIT_VAR(&_29$$22);
			ZEPHIR_CONCAT_SVS(&_29$$22, "<?php $", &prefixLevel, "incr++; } ?>");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&compilation, &_29$$22);
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
	zephir_read_property_cached(&level, this_ptr, _zephir_prop_0, 913, PH_NOISY_CC);
	zephir_memory_observe(&prefix);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 922, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&prefix, &_0, &level, 0))) {
		RETURN_MM_STRING("");
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_2, 921, PH_NOISY_CC | PH_READONLY);
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
 *
 * @phpstan-param mvc_volt_node $statement
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileIf)
{
	zval compilation;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL, blockStatements, expr, _1, _2, _3, _4, _5, _0$$3, _6$$4, _7$$4, _8$$4;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&blockStatements);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&compilation);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &extendsMode_param);
	zephir_get_arrval(&statement, statement_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatementwithdata_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1049);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	zephir_array_fetch_string(&_3, &statement, SL("true_statements"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1055);
	if (extendsMode) {
		ZVAL_BOOL(&_4, 1);
	} else {
		ZVAL_BOOL(&_4, 0);
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "statementList", NULL, 0, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SVSV(&_5, "<?php if (", &_1, ") { ?>", &_2);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&compilation, &_5);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&blockStatements);
	if (zephir_array_isset_string_fetch(&blockStatements, &statement, SL("false_statements"), 0)) {
		if (extendsMode) {
			ZVAL_BOOL(&_7$$4, 1);
		} else {
			ZVAL_BOOL(&_7$$4, 0);
		}
		ZEPHIR_CALL_METHOD(&_6$$4, this_ptr, "statementList", NULL, 0, &blockStatements, &_7$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SV(&_8$$4, "<?php } else { ?>", &_6$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&compilation, &_8$$4);
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
 *
 * @phpstan-param mvc_volt_node $statement
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileInclude)
{
	zend_string *_11$$7;
	zend_ulong _10$$7;
	zend_bool _6$$5, _13$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, pathExpr, subCompiler, finalPath, compilation, params, dependencies, files, file, mtime, path, _1, _15, _0$$3, _2$$4, _3$$5, _5$$5, _14$$5, _4$$6, *_7$$7, _8$$7, *_9$$7, _12$$7;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&pathExpr);
	ZVAL_UNDEF(&subCompiler);
	ZVAL_UNDEF(&finalPath);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&dependencies);
	ZVAL_UNDEF(&files);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&mtime);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_12$$7);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&pathExpr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&pathExpr, &statement, SL("path"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1092);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_1);
	zephir_array_fetch_string(&_1, &pathExpr, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1099);
	if (ZEPHIR_IS_LONG(&_1, 260)) {
		zephir_memory_observe(&_2$$4);
		zephir_array_fetch_string(&_2$$4, &pathExpr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1100);
		ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "findTemplate", NULL, 0, &_2$$4);
		zephir_check_call_status();
		if (Z_TYPE_P(&finalPath) != IS_NULL) {
			ZEPHIR_INIT_VAR(&subCompiler);
			if (zephir_clone(&subCompiler, this_ptr) == FAILURE) {
				RETURN_MM();
			}
			ZVAL_BOOL(&_3$$5, 0);
			ZEPHIR_CALL_METHOD(&compilation, &subCompiler, "compile", NULL, 0, &finalPath, &_3$$5);
			zephir_check_call_status();
			if (Z_TYPE_P(&compilation) == IS_NULL) {
				ZEPHIR_CALL_METHOD(&_4$$6, &subCompiler, "getCompiledTemplatePath", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&compilation, this_ptr, "phpFileGetContents", NULL, 0, &_4$$6);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "addDependency", NULL, 0, &finalPath);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_5$$5, &subCompiler, "getCompiledTemplatePath", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_CE_STATIC(&dependencies, phalcon_mvc_view_engine_volt_dependencies_ce, "read", NULL, 0, &_5$$5);
			zephir_check_call_status();
			_6$$5 = Z_TYPE_P(&dependencies) == IS_ARRAY;
			if (_6$$5) {
				zephir_memory_observe(&files);
				_6$$5 = zephir_array_isset_string_fetch(&files, &dependencies, SL("files"), 0);
			}
			if (_6$$5) {
				if (Z_TYPE_P(&files) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_8$$7);
					zephir_string_to_char_array(&_8$$7, &files);
					_7$$7 = &_8$$7;
				} else {
					_7$$7 = &files;
				}
				zephir_is_iterable(_7$$7, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1132);
				if (Z_TYPE_P(_7$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7$$7), _10$$7, _11$$7, _9$$7)
					{
						ZEPHIR_INIT_NVAR(&file);
						if (_11$$7 != NULL) { 
							ZVAL_STR_COPY(&file, _11$$7);
						} else {
							ZVAL_LONG(&file, _10$$7);
						}
						ZEPHIR_INIT_NVAR(&mtime);
						ZVAL_COPY(&mtime, _9$$7);
						zephir_update_property_array(this_ptr, SL("dependencies"), &file, &mtime);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _7$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_13$$7 = 1;
					while (1) {
						if (_13$$7) {
							_13$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _7$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_12$$7, _7$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_12$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&file, _7$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&mtime, _7$$7, "current", NULL, 0);
						zephir_check_call_status();
							zephir_update_property_array(this_ptr, SL("dependencies"), &file, &mtime);
					}
				}
				ZEPHIR_INIT_NVAR(&mtime);
				ZEPHIR_INIT_NVAR(&file);
			}
			zephir_memory_observe(&params);
			if (!(zephir_array_isset_string_fetch(&params, &statement, SL("params"), 0))) {
				RETURN_CCTOR(&compilation);
			}
			ZEPHIR_CALL_METHOD(&_14$$5, this_ptr, "expression", NULL, 0, &params);
			zephir_check_call_status();
			ZEPHIR_CONCAT_SVSVS(return_value, "<?php (function (array $__volt_scope) { extract($__volt_scope); ?>", &compilation, "<?php })(array_merge(get_defined_vars(), ", &_14$$5, ")); ?>");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
	}
	ZEPHIR_CALL_METHOD(&path, this_ptr, "expression", NULL, 0, &pathExpr);
	zephir_check_call_status();
	ZEPHIR_OBS_NVAR(&params);
	if (!(zephir_array_isset_string_fetch(&params, &statement, SL("params"), 0))) {
		ZEPHIR_CONCAT_SVS(return_value, "<?php $this->partial(", &path, "); ?>");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&_15, this_ptr, "expression", NULL, 0, &params);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVS(return_value, "<?php $this->partial(", &path, ", ", &_15, "); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Compiles macros
 *
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
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
	zval *statement_param = NULL, *extendsMode_param = NULL, name, defaultValue, parameters, position, parameter, variableName, blockStatements, _1, _3, _0$$3, _2$$4, *_6$$6, _7$$6, *_8$$6, _19$$6, _11$$7, _12$$7, _13$$7, _14$$7, _15$$8, _17$$8, _18$$9, _21$$10, _22$$10, _23$$10, _24$$10, _25$$11, _26$$11, _27$$12, _28$$13, _29$$13, _30$$13;
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
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$3);
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
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&name);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&name, &statement, SL("name"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1180);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 923, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(zephir_array_isset_value(&_1, &name))) {
		ZEPHIR_INIT_VAR(&_2$$4);
		object_init_ex(&_2$$4, phalcon_mvc_view_engine_volt_exceptions_macroalreadydefined_ce);
		ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 0, &name);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1187);
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
		zephir_is_iterable(_6$$6, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1224);
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
				zephir_array_fetch_string(&variableName, &parameter, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1206);
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
					zephir_array_fetch_string(&variableName, &parameter, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1206);
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
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileReturn)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, expr, _1, _0$$3;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1262);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "<?php return ", &_1, "; ?>");
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
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSet)
{
	zend_bool _14;
	zval compilation;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statement_param = NULL, assignments, assignment, exprCode, target, *_1, _2, *_3, _13, _0$$3, _4$$4, _6$$4, _7$$4, _8$$5, _9$$6, _10$$7, _11$$8, _12$$9, _15$$10, _16$$10, _17$$10, _18$$11, _19$$12, _20$$13, _21$$14, _22$$15;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&assignments);
	ZVAL_UNDEF(&assignment);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&target);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$10);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_20$$13);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_22$$15);
	ZVAL_UNDEF(&compilation);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statement_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&assignments);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&assignments, &statement, SL("assignments"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1337);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&compilation);
	ZVAL_STRING(&compilation, "<?php");
	if (Z_TYPE_P(&assignments) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &assignments);
		_1 = &_2;
	} else {
		_1 = &assignments;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1386);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&assignment);
			ZVAL_COPY(&assignment, _3);
			ZEPHIR_OBS_NVAR(&_4$$4);
			zephir_array_fetch_string(&_4$$4, &assignment, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1348);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", &_5, 0, &_4$$4);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_6$$4);
			zephir_array_fetch_string(&_6$$4, &assignment, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1355);
			ZEPHIR_CALL_METHOD(&target, this_ptr, "expression", &_5, 0, &_6$$4);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_7$$4);
			zephir_array_fetch_string(&_7$$4, &assignment, SL("op"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1361);
			if (ZEPHIR_IS_LONG(&_7$$4, 281)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&_7$$4, 282)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&_7$$4, 283)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&_7$$4, 284)) { goto zephir_switch_0_clause_3; }
			goto zephir_switch_0_clause_4;
			zephir_switch_0_clause_0: ;
				ZEPHIR_INIT_NVAR(&_8$$5);
				ZEPHIR_CONCAT_SVSVS(&_8$$5, " ", &target, " += ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_8$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				ZEPHIR_INIT_NVAR(&_9$$6);
				ZEPHIR_CONCAT_SVSVS(&_9$$6, " ", &target, " -= ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_9$$6);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_2: ;
				ZEPHIR_INIT_NVAR(&_10$$7);
				ZEPHIR_CONCAT_SVSVS(&_10$$7, " ", &target, " *= ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_10$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				ZEPHIR_INIT_NVAR(&_11$$8);
				ZEPHIR_CONCAT_SVSVS(&_11$$8, " ", &target, " /= ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_11$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_INIT_NVAR(&_12$$9);
				ZEPHIR_CONCAT_SVSVS(&_12$$9, " ", &target, " = ", &exprCode, ";");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&compilation, &_12$$9);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_end: ;

		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&assignment, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_15$$10);
				zephir_array_fetch_string(&_15$$10, &assignment, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1348);
				ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "expression", &_5, 0, &_15$$10);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_16$$10);
				zephir_array_fetch_string(&_16$$10, &assignment, SL("variable"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1355);
				ZEPHIR_CALL_METHOD(&target, this_ptr, "expression", &_5, 0, &_16$$10);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_17$$10);
				zephir_array_fetch_string(&_17$$10, &assignment, SL("op"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1361);
				if (ZEPHIR_IS_LONG(&_17$$10, 281)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&_17$$10, 282)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&_17$$10, 283)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&_17$$10, 284)) { goto zephir_switch_1_clause_3; }
				goto zephir_switch_1_clause_4;
				zephir_switch_1_clause_0: ;
					ZEPHIR_INIT_NVAR(&_18$$11);
					ZEPHIR_CONCAT_SVSVS(&_18$$11, " ", &target, " += ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_18$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					ZEPHIR_INIT_NVAR(&_19$$12);
					ZEPHIR_CONCAT_SVSVS(&_19$$12, " ", &target, " -= ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_19$$12);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_2: ;
					ZEPHIR_INIT_NVAR(&_20$$13);
					ZEPHIR_CONCAT_SVSVS(&_20$$13, " ", &target, " *= ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_20$$13);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					ZEPHIR_INIT_NVAR(&_21$$14);
					ZEPHIR_CONCAT_SVSVS(&_21$$14, " ", &target, " /= ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_21$$14);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_INIT_NVAR(&_22$$15);
					ZEPHIR_CONCAT_SVSVS(&_22$$15, " ", &target, " = ", &exprCode, ";");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&compilation, &_22$$15);
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
 * echo $compiler->compileString('{{ "hello world" }}');
 *```
 *
 * @throws Exception
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 919, &_0);
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
 * @phpstan-param mvc_volt_node $statement
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSwitch)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode;
	zval *statement_param = NULL, *extendsMode_param = NULL, compilation, caseClauses, expr, lines, _1, _0$$3, _2$$4, _3$$5, _4$$5, _5$$5;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&compilation);
	ZVAL_UNDEF(&caseClauses);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&lines);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &statement_param, &extendsMode_param);
	zephir_get_arrval(&statement, statement_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	zephir_memory_observe(&expr);
	if (UNEXPECTED(!(zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0)))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_mvc_view_engine_volt_exceptions_corruptedstatementwithdata_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 0, &statement);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1422);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "expression", NULL, 0, &expr);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&compilation);
	ZEPHIR_CONCAT_SVS(&compilation, "<?php switch (", &_1, "): ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&caseClauses);
	if (zephir_array_isset_string_fetch(&caseClauses, &statement, SL("case_clauses"), 0)) {
		if (extendsMode) {
			ZVAL_BOOL(&_2$$4, 1);
		} else {
			ZVAL_BOOL(&_2$$4, 0);
		}
		ZEPHIR_CALL_METHOD(&lines, this_ptr, "statementList", NULL, 0, &caseClauses, &_2$$4);
		zephir_check_call_status();
		if (zephir_fast_strlen_ev(&lines) != 0) {
			ZEPHIR_INIT_VAR(&_3$$5);
			ZVAL_STRING(&_3$$5, "/(*ANYCRLF)^\\h+|\\h+$|(\\h){2,}/mu");
			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "");
			ZEPHIR_CALL_FUNCTION(&_5$$5, "preg_replace", NULL, 40, &_3$$5, &_4$$5, &lines);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&lines, &_5$$5);
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
 * @phpstan-param mvc_volt_node $expr
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, expression)
{
	zval _48$$81;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_7 = NULL, *_11 = NULL, *_21 = NULL, *_25 = NULL, *_26 = NULL, *_28 = NULL, *_40 = NULL, *_52 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool doubleQuotes, _14$$6, _23$$3;
	zval *expr_param = NULL, *doubleQuotes_param = NULL, end, endCode, extensions, items, left, name, right, singleExpr, singleExprCode, start, startCode, type, exprCode, leftCode, rightCode, _0, _2$$4, *_4$$6, _13$$6, _5$$7, _6$$7, _8$$8, _9$$8, _10$$8, _12$$8, _15$$10, _16$$10, _17$$11, _18$$11, _19$$11, _20$$11, _22$$14, _24$$15, _27$$17, _29$$18, _30$$36, _31$$36, _32$$36, _33$$36, _34$$37, _35$$37, _36$$37, _37$$37, _38$$41, _39$$51, _41$$55, _42$$57, _43$$75, _44$$75, _45$$75, _46$$81, _47$$81, _49$$81, _50$$81, _51$$81;
	zval expr, _1$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&end);
	ZVAL_UNDEF(&endCode);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&items);
	ZVAL_UNDEF(&left);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&singleExpr);
	ZVAL_UNDEF(&singleExprCode);
	ZVAL_UNDEF(&start);
	ZVAL_UNDEF(&startCode);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&exprCode);
	ZVAL_UNDEF(&leftCode);
	ZVAL_UNDEF(&rightCode);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_19$$11);
	ZVAL_UNDEF(&_20$$11);
	ZVAL_UNDEF(&_22$$14);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_30$$36);
	ZVAL_UNDEF(&_31$$36);
	ZVAL_UNDEF(&_32$$36);
	ZVAL_UNDEF(&_33$$36);
	ZVAL_UNDEF(&_34$$37);
	ZVAL_UNDEF(&_35$$37);
	ZVAL_UNDEF(&_36$$37);
	ZVAL_UNDEF(&_37$$37);
	ZVAL_UNDEF(&_38$$41);
	ZVAL_UNDEF(&_39$$51);
	ZVAL_UNDEF(&_41$$55);
	ZVAL_UNDEF(&_42$$57);
	ZVAL_UNDEF(&_43$$75);
	ZVAL_UNDEF(&_44$$75);
	ZVAL_UNDEF(&_45$$75);
	ZVAL_UNDEF(&_46$$81);
	ZVAL_UNDEF(&_47$$81);
	ZVAL_UNDEF(&_49$$81);
	ZVAL_UNDEF(&_50$$81);
	ZVAL_UNDEF(&_51$$81);
	ZVAL_UNDEF(&_48$$81);
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
	zephir_get_arrval(&expr, expr_param);
	if (!doubleQuotes_param) {
		doubleQuotes = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&exprCode);
	ZVAL_NULL(&exprCode);
	ZEPHIR_INIT_VAR(&leftCode);
	ZVAL_STRING(&leftCode, "");
	ZEPHIR_INIT_VAR(&rightCode);
	ZVAL_STRING(&rightCode, "");
	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("exprLevel")));
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 924, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_0);
	while (1) {
		if (!(ZEPHIR_IS_EMPTY(&extensions))) {
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
			zephir_is_iterable(&expr, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1538);
			if (Z_TYPE_P(&expr) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&expr), _4$$6)
				{
					ZEPHIR_INIT_NVAR(&singleExpr);
					ZVAL_COPY(&singleExpr, _4$$6);
					ZEPHIR_OBS_NVAR(&_5$$7);
					zephir_array_fetch_string(&_5$$7, &singleExpr, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1512);
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
						ZEPHIR_INIT_NVAR(&_8$$8);
						zephir_create_closure_ex(&_8$$8, NULL, phalcon_14__closure_ce, SL("__invoke"));
						ZEPHIR_INIT_NVAR(&_9$$8);
						ZVAL_STRING(&_9$$8, "/\\\\.|'/s");
						ZEPHIR_CALL_FUNCTION(&_10$$8, "preg_replace_callback", &_11, 0, &_9$$8, &_8$$8, &name);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_12$$8);
						ZEPHIR_CONCAT_SVSV(&_12$$8, "'", &_10$$8, "' => ", &singleExprCode);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&items, &_12$$8, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1532);
					} else {
						zephir_array_append(&items, &singleExprCode, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1534);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &expr, "rewind", NULL, 0);
				zephir_check_call_status();
				_14$$6 = 1;
				while (1) {
					if (_14$$6) {
						_14$$6 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, &expr, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_13$$6, &expr, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$6)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&singleExpr, &expr, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&_15$$10);
						zephir_array_fetch_string(&_15$$10, &singleExpr, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1512);
						if (doubleQuotes) {
							ZVAL_BOOL(&_16$$10, 1);
						} else {
							ZVAL_BOOL(&_16$$10, 0);
						}
						ZEPHIR_CALL_METHOD(&singleExprCode, this_ptr, "expression", &_7, 0, &_15$$10, &_16$$10);
						zephir_check_call_status();
						ZEPHIR_OBS_NVAR(&name);
						if (zephir_array_isset_string_fetch(&name, &singleExpr, SL("name"), 0)) {
							ZEPHIR_INIT_NVAR(&_17$$11);
							ZEPHIR_INIT_NVAR(&_17$$11);
							zephir_create_closure_ex(&_17$$11, NULL, phalcon_15__closure_ce, SL("__invoke"));
							ZEPHIR_INIT_NVAR(&_18$$11);
							ZVAL_STRING(&_18$$11, "/\\\\.|'/s");
							ZEPHIR_CALL_FUNCTION(&_19$$11, "preg_replace_callback", &_11, 0, &_18$$11, &_17$$11, &name);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_20$$11);
							ZEPHIR_CONCAT_SVSV(&_20$$11, "'", &_19$$11, "' => ", &singleExprCode);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&items, &_20$$11, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1532);
						} else {
							zephir_array_append(&items, &singleExprCode, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1534);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&singleExpr);
			ZEPHIR_INIT_NVAR(&exprCode);
			zephir_fast_join_str(&exprCode, SL(", "), &items);
			break;
		}
		if (ZEPHIR_CHAR_VALUE(&type) == '.') {
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "attributeReader", &_21, 0, &expr);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_OBS_NVAR(&left);
		if (zephir_array_isset_string_fetch(&left, &expr, SL("left"), 0)) {
			if (doubleQuotes) {
				ZVAL_BOOL(&_22$$14, 1);
			} else {
				ZVAL_BOOL(&_22$$14, 0);
			}
			ZEPHIR_CALL_METHOD(&leftCode, this_ptr, "expression", &_7, 0, &left, &_22$$14);
			zephir_check_call_status();
		}
		_23$$3 = ZEPHIR_IS_LONG(&type, 311);
		if (!(_23$$3)) {
			_23$$3 = ZEPHIR_IS_LONG(&type, 422);
		}
		if (_23$$3) {
			ZVAL_BOOL(&_24$$15, ZEPHIR_IS_LONG(&type, 422));
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "compileTestExpression", &_25, 0, &expr, &leftCode, &_24$$15);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_LONG(&type, 421)) {
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "compileNullsafe", &_26, 0, &expr, &leftCode);
			zephir_check_call_status();
			break;
		}
		if (ZEPHIR_IS_LONG(&type, 124)) {
			ZEPHIR_OBS_NVAR(&_27$$17);
			zephir_array_fetch_string(&_27$$17, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1586);
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "resolveFilter", &_28, 0, &_27$$17, &leftCode);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_OBS_NVAR(&right);
		if (zephir_array_isset_string_fetch(&right, &expr, SL("right"), 0)) {
			if (doubleQuotes) {
				ZVAL_BOOL(&_29$$18, 1);
			} else {
				ZVAL_BOOL(&_29$$18, 0);
			}
			ZEPHIR_CALL_METHOD(&rightCode, this_ptr, "expression", &_7, 0, &right, &_29$$18);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(&exprCode);
		ZVAL_NULL(&exprCode);
		if (ZEPHIR_CHAR_VALUE(&type) == '!') { goto zephir_switch_0_clause_0; }
		if (ZEPHIR_CHAR_VALUE(&type) == '*') { goto zephir_switch_0_clause_1; }
		if (ZEPHIR_CHAR_VALUE(&type) == '+') { goto zephir_switch_0_clause_2; }
		if (ZEPHIR_CHAR_VALUE(&type) == '-') { goto zephir_switch_0_clause_3; }
		if (ZEPHIR_CHAR_VALUE(&type) == '/') { goto zephir_switch_0_clause_4; }
		if (ZEPHIR_IS_LONG(&type, 37)) { goto zephir_switch_0_clause_5; }
		if (ZEPHIR_CHAR_VALUE(&type) == '<') { goto zephir_switch_0_clause_6; }
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
		if (ZEPHIR_IS_LONG(&type, 420)) { goto zephir_switch_0_clause_52; }
		if (ZEPHIR_IS_LONG(&type, 427)) { goto zephir_switch_0_clause_53; }
		goto zephir_switch_0_clause_54;
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
			zephir_array_fetch_string(&exprCode, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1657);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_13: ;
			ZEPHIR_OBS_NVAR(&exprCode);
			zephir_array_fetch_string(&exprCode, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1661);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_14: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			if (EXPECTED(doubleQuotes == 0)) {
				ZEPHIR_INIT_NVAR(&_30$$36);
				ZEPHIR_INIT_NVAR(&_30$$36);
				zephir_create_closure_ex(&_30$$36, NULL, phalcon_16__closure_ce, SL("__invoke"));
				ZEPHIR_OBS_NVAR(&_31$$36);
				zephir_array_fetch_string(&_31$$36, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1680);
				ZEPHIR_INIT_NVAR(&_32$$36);
				ZVAL_STRING(&_32$$36, "/\\\\.|'/s");
				ZEPHIR_CALL_FUNCTION(&_33$$36, "preg_replace_callback", &_11, 0, &_32$$36, &_30$$36, &_31$$36);
				zephir_check_call_status();
				ZEPHIR_CONCAT_SVS(&exprCode, "'", &_33$$36, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_INIT_NVAR(&_34$$37);
				ZEPHIR_INIT_NVAR(&_34$$37);
				zephir_create_closure_ex(&_34$$37, NULL, phalcon_17__closure_ce, SL("__invoke"));
				ZEPHIR_OBS_NVAR(&_35$$37);
				zephir_array_fetch_string(&_35$$37, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1700);
				ZEPHIR_INIT_NVAR(&_36$$37);
				ZVAL_STRING(&_36$$37, "/\\\\.|[\"$]/s");
				ZEPHIR_CALL_FUNCTION(&_37$$37, "preg_replace_callback", &_11, 0, &_36$$37, &_34$$37, &_35$$37);
				zephir_check_call_status();
				ZEPHIR_CONCAT_SVS(&exprCode, "\"", &_37$$37, "\"");
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
			ZEPHIR_OBS_NVAR(&_38$$41);
			zephir_array_fetch_string(&_38$$41, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1718);
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SV(&exprCode, "$", &_38$$41);
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
				ZVAL_BOOL(&_39$$51, 1);
			} else {
				ZVAL_BOOL(&_39$$51, 0);
			}
			ZEPHIR_CALL_METHOD(&exprCode, this_ptr, "functionCall", &_40, 0, &expr, &_39$$51);
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
					ZVAL_BOOL(&_41$$55, 1);
				} else {
					ZVAL_BOOL(&_41$$55, 0);
				}
				ZEPHIR_CALL_METHOD(&startCode, this_ptr, "expression", &_7, 0, &start, &_41$$55);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&startCode);
				ZVAL_STRING(&startCode, "null");
			}
			ZEPHIR_OBS_NVAR(&end);
			if (zephir_array_isset_string_fetch(&end, &expr, SL("end"), 0)) {
				if (doubleQuotes) {
					ZVAL_BOOL(&_42$$57, 1);
				} else {
					ZVAL_BOOL(&_42$$57, 0);
				}
				ZEPHIR_CALL_METHOD(&endCode, this_ptr, "expression", &_7, 0, &end, &_42$$57);
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
			ZEPHIR_OBS_NVAR(&_44$$75);
			zephir_array_fetch_string(&_44$$75, &expr, SL("ternary"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1857);
			if (doubleQuotes) {
				ZVAL_BOOL(&_45$$75, 1);
			} else {
				ZVAL_BOOL(&_45$$75, 0);
			}
			ZEPHIR_CALL_METHOD(&_43$$75, this_ptr, "expression", &_7, 0, &_44$$75, &_45$$75);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVSVS(&exprCode, "(", &_43$$75, " ? ", &leftCode, " : ", &rightCode, ")");
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
			zephir_array_fetch_string(&exprCode, &expr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1869);
			goto zephir_switch_0_end;
		zephir_switch_0_clause_52: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "(", &leftCode, " ?? ", &rightCode, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_53: ;
			ZEPHIR_INIT_NVAR(&exprCode);
			ZEPHIR_CONCAT_SVSVS(&exprCode, "(int) floor((", &leftCode, ") / (", &rightCode, "))");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			goto zephir_switch_0_end;
		zephir_switch_0_clause_54: ;
			ZEPHIR_INIT_NVAR(&_46$$81);
			object_init_ex(&_46$$81, phalcon_mvc_view_engine_volt_exceptions_unknownvoltexpression_ce);
			ZEPHIR_OBS_NVAR(&_47$$81);
			zephir_array_fetch_string(&_47$$81, &expr, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1881);
			zephir_cast_to_string(&_48$$81, &_47$$81);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_OBS_NVAR(&_49$$81);
			zephir_array_fetch_string(&_49$$81, &expr, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1881);
			ZVAL_LONG(&_50$$81, zephir_get_intval(&type));
			ZVAL_LONG(&_51$$81, zephir_get_intval(&_49$$81));
			ZEPHIR_CALL_METHOD(NULL, &_46$$81, "__construct", &_52, 0, &_50$$81, &_48$$81, &_51$$81);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_46$$81, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1881);
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
 * @phpstan-param array<array-key, mixed> $arguments
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
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 924, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_0);
	if (Z_TYPE_P(&extensions) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &extensions);
		_1 = &_2;
	} else {
		_1 = &extensions;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1928);
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
 * @phpstan-param mvc_volt_node $expr
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, functionCall)
{
	zval _9$$10, _11$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool doubleQuotes, _14$$5, _20$$5, _17$$17;
	zval *expr_param = NULL, *doubleQuotes_param = NULL, __$true, arguments, arrayHelpers, block, currentBlock, definition, escapedCode, exprLevel, extendedBlocks, extensions, functions, method, name, nameExpr, nameType, tagService, runtime, code, funcArguments, _28, _29, _0$$3, _1$$5, _4$$5, _19$$5, _21$$5, _22$$5, _23$$5, _3$$6, _5$$8, _6$$8, _8$$10, _10$$10, _12$$10, _13$$10, _15$$16, _16$$17, _18$$18, _24$$29, _25$$29, _26$$29, _27$$31;
	zval expr, _2$$6, _7$$13;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_7$$13);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&arrayHelpers);
	ZVAL_UNDEF(&block);
	ZVAL_UNDEF(&currentBlock);
	ZVAL_UNDEF(&definition);
	ZVAL_UNDEF(&escapedCode);
	ZVAL_UNDEF(&exprLevel);
	ZVAL_UNDEF(&extendedBlocks);
	ZVAL_UNDEF(&extensions);
	ZVAL_UNDEF(&functions);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&nameExpr);
	ZVAL_UNDEF(&nameType);
	ZVAL_UNDEF(&tagService);
	ZVAL_UNDEF(&runtime);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&funcArguments);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_23$$5);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_8$$10);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_15$$16);
	ZVAL_UNDEF(&_16$$17);
	ZVAL_UNDEF(&_18$$18);
	ZVAL_UNDEF(&_24$$29);
	ZVAL_UNDEF(&_25$$29);
	ZVAL_UNDEF(&_26$$29);
	ZVAL_UNDEF(&_27$$31);
	ZVAL_UNDEF(&_9$$10);
	ZVAL_UNDEF(&_11$$10);
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
	zephir_get_arrval(&expr, expr_param);
	if (!doubleQuotes_param) {
		doubleQuotes = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&code);
	ZVAL_NULL(&code);
	ZEPHIR_INIT_VAR(&funcArguments);
	ZVAL_NULL(&funcArguments);
	zephir_memory_observe(&nameExpr);
	zephir_array_fetch_string(&nameExpr, &expr, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1944);
	zephir_memory_observe(&nameType);
	zephir_array_fetch_string(&nameType, &nameExpr, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1945);
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
		zephir_array_fetch_string(&name, &nameExpr, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 1962);
		zephir_read_property_cached(&_1$$5, this_ptr, _zephir_prop_0, 924, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&extensions, &_1$$5);
		if (!(ZEPHIR_IS_EMPTY(&extensions))) {
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
		ZEPHIR_INIT_VAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "function");
		ZEPHIR_CALL_METHOD(&runtime, this_ptr, "getRuntime", NULL, 0, &_4$$5, &name);
		zephir_check_call_status();
		if (Z_TYPE_P(&runtime) != IS_NULL) {
			ZEPHIR_CALL_METHOD(&_5$$8, this_ptr, "runtimeArguments", NULL, 0, &funcArguments);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_6$$8);
			ZVAL_STRING(&_6$$8, "function");
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "compileRuntimeCall", NULL, 0, &_6$$8, &runtime, &_5$$8);
			zephir_check_call_status();
			RETURN_MM();
		}
		zephir_read_property_cached(&_1$$5, this_ptr, _zephir_prop_1, 925, PH_NOISY_CC | PH_READONLY);
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
						ZEPHIR_INIT_VAR(&_7$$13);
						zephir_create_array(&_7$$13, 2, 0);
						zephir_array_fast_append(&_7$$13, &arguments);
						zephir_array_fast_append(&_7$$13, &funcArguments);
						ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &definition, &_7$$13);
						zephir_check_call_status();
						RETURN_MM();
					}
				}
				ZEPHIR_INIT_VAR(&_8$$10);
				object_init_ex(&_8$$10, phalcon_mvc_view_engine_volt_exceptions_invaliduserfunctiondefinition_ce);
				zephir_cast_to_string(&_9$$10, &name);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_memory_observe(&_10$$10);
				zephir_array_fetch_string(&_10$$10, &expr, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2024);
				zephir_cast_to_string(&_11$$10, &_10$$10);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_memory_observe(&_12$$10);
				zephir_array_fetch_string(&_12$$10, &expr, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2024);
				ZVAL_LONG(&_13$$10, zephir_get_intval(&_12$$10));
				ZEPHIR_CALL_METHOD(NULL, &_8$$10, "__construct", NULL, 0, &_9$$10, &_11$$10, &_13$$10);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_8$$10, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2024);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		_14$$5 = ZEPHIR_IS_STRING(&name, "get_content");
		if (!(_14$$5)) {
			_14$$5 = ZEPHIR_IS_STRING(&name, "content");
		}
		if (_14$$5) {
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
			zephir_read_property_cached(&_15$$16, this_ptr, _zephir_prop_2, 926, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&extendedBlocks, &_15$$16);
			if (Z_TYPE_P(&extendedBlocks) == IS_ARRAY) {
				zephir_read_property_cached(&_16$$17, this_ptr, _zephir_prop_3, 927, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&currentBlock, &_16$$17);
				_17$$17 = Z_TYPE_P(&currentBlock) != IS_NULL;
				if (_17$$17) {
					zephir_memory_observe(&block);
					_17$$17 = zephir_array_isset_fetch(&block, &extendedBlocks, &currentBlock, 0);
				}
				if (_17$$17) {
					zephir_read_property_cached(&_18$$18, this_ptr, _zephir_prop_4, 928, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CPY_WRT(&exprLevel, &_18$$18);
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
		ZEPHIR_INIT_NVAR(&_4$$5);
		zephir_camelize(&_4$$5, &name, NULL );
		ZEPHIR_CALL_FUNCTION(&method, "lcfirst", NULL, 86, &_4$$5);
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
		ZEPHIR_INIT_VAR(&_19$$5);
		ZVAL_STRING(&_19$$5, "Phalcon\\Tag");
		if ((zephir_method_exists(&_19$$5, &method)  == SUCCESS)) {
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
		zephir_read_property_cached(&_1$$5, this_ptr, _zephir_prop_5, 914, PH_NOISY_CC | PH_READONLY);
		_20$$5 = Z_TYPE_P(&_1$$5) != IS_NULL;
		if (_20$$5) {
			zephir_read_property_cached(&_21$$5, this_ptr, _zephir_prop_5, 914, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_23$$5);
			ZVAL_STRING(&_23$$5, "tag");
			ZEPHIR_CALL_METHOD(&_22$$5, &_21$$5, "has", NULL, 0, &_23$$5);
			zephir_check_call_status();
			_20$$5 = ZEPHIR_IS_TRUE_IDENTICAL(&_22$$5);
		}
		if (_20$$5) {
			zephir_read_property_cached(&_24$$29, this_ptr, _zephir_prop_5, 914, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_25$$29);
			ZVAL_STRING(&_25$$29, "tag");
			ZEPHIR_CALL_METHOD(&tagService, &_24$$29, "get", NULL, 0, &_25$$29);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_26$$29, &tagService, "has", NULL, 0, &name);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_26$$29)) {
				ZEPHIR_INIT_NVAR(&funcArguments);
				ZVAL_NULL(&funcArguments);
				ZEPHIR_OBS_NVAR(&funcArguments);
				if (zephir_array_isset_string_fetch(&funcArguments, &expr, SL("arguments"), 0)) {
					ZVAL_BOOL(&_27$$31, 1);
					ZEPHIR_CALL_METHOD(&arguments, this_ptr, "expression", NULL, 0, &funcArguments, &_27$$31);
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
		if (ZEPHIR_IS_STRING(&name, "constant")) {
			ZEPHIR_CONCAT_SVS(return_value, "constant(", &arguments, ")");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM();
		}
		if (ZEPHIR_IS_STRING(&name, "caller")) {
			RETURN_MM_STRING("$this->renderMacroCaller()");
		}
		ZEPHIR_CONCAT_SVSVS(return_value, "$this->callMacro('", &name, "', [", &arguments, "])");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (doubleQuotes) {
		ZVAL_BOOL(&_29, 1);
	} else {
		ZVAL_BOOL(&_29, 0);
	}
	ZEPHIR_CALL_METHOD(&_28, this_ptr, "expression", NULL, 0, &nameExpr, &_29);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSVS(return_value, &_28, "(", &arguments, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Returns the path to the last compiled template
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
 * @phpstan-return list<object>
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getExtensions)
{

	RETURN_MEMBER_TYPED(getThis(), "extensions", IS_ARRAY);
}

/**
 * Register the user registered filters
 *
 * @phpstan-return array<string, mixed>
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getFilters)
{

	RETURN_MEMBER_TYPED(getThis(), "filters", IS_ARRAY);
}

/**
 * Register the user registered functions
 *
 * @phpstan-return array<string, mixed>
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getFunctions)
{

	RETURN_MEMBER_TYPED(getThis(), "functions", IS_ARRAY);
}

/**
 * Returns a compiler's option
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
 * @phpstan-return array<string, mixed>
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getOptions)
{

	RETURN_MEMBER_TYPED(getThis(), "options", IS_ARRAY);
}

/**
 * Returns the path that is currently being compiled
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
	zval _0, _3, _8, _1$$3, _2$$3, _4$$4, _5$$5, _6$$5, _9$$6;
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
	ZVAL_UNDEF(&_9$$6);
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

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 929, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_1, 919, PH_NOISY_CC | PH_READONLY);
		zephir_unique_path_key(&_1$$3, &_2$$3);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 929, &_1$$3);
	}
	zephir_memory_observe(&_3);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 929, PH_NOISY_CC);
	if (Z_TYPE_P(&_3) == IS_OBJECT) {
		zephir_memory_observe(&_4$$4);
		zephir_read_property_cached(&_4$$4, this_ptr, _zephir_prop_0, 929, PH_NOISY_CC);
		if (zephir_is_instance_of(&_4$$4, SL("Closure"))) {
			ZEPHIR_INIT_VAR(&_5$$5);
			zephir_read_property_cached(&_6$$5, this_ptr, _zephir_prop_0, 929, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_7$$5);
			zephir_create_array(&_7$$5, 1, 0);
			zephir_array_fast_append(&_7$$5, this_ptr);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&_5$$5, &_6$$5, &_7$$5);
			zephir_check_call_status();
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 929, &_5$$5);
		}
	}
	zephir_memory_observe(&_8);
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_0, 929, PH_NOISY_CC);
	if (UNEXPECTED(Z_TYPE_P(&_8) != IS_STRING)) {
		ZEPHIR_INIT_VAR(&_9$$6);
		object_init_ex(&_9$$6, phalcon_mvc_view_engine_volt_exceptions_invalidcompilationprefix_ce);
		ZEPHIR_CALL_METHOD(NULL, &_9$$6, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_9$$6, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2314);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_MEMBER_TYPED(getThis(), "prefix", IS_STRING);
}

/**
 * Parses a Volt template returning its intermediate representation
 *
 *```php
 * print_r(
 *     $compiler->parse("{{ 3 + 2 }}")
 * );
 *```
 *
 * @phpstan-return mvc_volt_node
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
 *
 * @phpstan-param mvc_volt_node $test
 *
 * @throws Exception
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
	zephir_get_arrval(&test, test_param);
	zephir_memory_observe(&left_zv);
	ZVAL_STR_COPY(&left_zv, left);
	zephir_memory_observe(&type);
	zephir_array_fetch_string(&type, &test, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2349);
	if (ZEPHIR_IS_LONG(&type, 265)) {
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &test, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2355);
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
		zephir_array_fetch_string(&testName, &test, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2378);
		ZEPHIR_OBS_NVAR(&name);
		if (zephir_array_isset_string_fetch(&name, &testName, SL("value"), 0)) {
			if (ZEPHIR_IS_STRING(&name, "divisibleby")) { goto zephir_switch_1_clause_0; }
			if (ZEPHIR_IS_STRING(&name, "sameas")) { goto zephir_switch_1_clause_1; }
			if (ZEPHIR_IS_STRING(&name, "type")) { goto zephir_switch_1_clause_2; }
			goto zephir_switch_1_end;
			zephir_switch_1_clause_0: ;
				zephir_memory_observe(&_1$$12);
				zephir_array_fetch_string(&_1$$12, &test, SL("arguments"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2383);
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
				zephir_array_fetch_string(&_3$$13, &test, SL("arguments"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2385);
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
				zephir_array_fetch_string(&_5$$14, &test, SL("arguments"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2387);
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 914, container);
}

/**
 * Sets a single compiler option
 *
 * @param mixed value
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setOption)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval option_zv, *value, value_sub, _0;
	zend_string *option = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&option_zv);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("virtualPaths", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(option)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	value = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&option_zv);
	ZVAL_STR_COPY(&option_zv, option);
	zephir_update_property_array(this_ptr, SL("options"), &option_zv, value);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 916, &_0);
	RETURN_THIS();
}

/**
 * Sets the compiler options
 *
 * @phpstan-param array<string, mixed> $options
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *options_param = NULL, _0;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("virtualPaths", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &options_param);
	zephir_get_arrval(&options, options_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 915, &options);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 916, &_0);
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 929, &prefix_zv);
	RETURN_THISW();
}

/**
 * Records a file inlined into the template being compiled
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, addDependency)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval path_zv, __$true, _0, _1;
	zend_string *path = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_CALL_FUNCTION(NULL, "clearstatcache", NULL, 0, &__$true, &path_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	zephir_filemtime(&_0, &path_zv);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, zephir_get_intval(&_0));
	zephir_update_property_array(this_ptr, SL("dependencies"), &path_zv, &_1);
	ZEPHIR_MM_RESTORE();
}

/**
 * Compiles a child template against a parent chosen at render time
 * ({% extends layoutVar %}): one compiled file per (child, parent) pair
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileVariant)
{
	zend_bool stale = 0, _1, _2, _7, _8, _11$$6, _12$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval childPath_zv, parentName_zv, parentPath, options, compiledPath, variant, always, stat, subCompiler, _0, _4, _5, _6, _3$$3, _9$$6, _10$$6, _13$$6, _14$$6;
	zend_string *childPath = NULL, *parentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&childPath_zv);
	ZVAL_UNDEF(&parentName_zv);
	ZVAL_UNDEF(&parentPath);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&compiledPath);
	ZVAL_UNDEF(&variant);
	ZVAL_UNDEF(&always);
	ZVAL_UNDEF(&stat);
	ZVAL_UNDEF(&subCompiler);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(childPath)
		Z_PARAM_STR(parentName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&childPath_zv);
	ZVAL_STR_COPY(&childPath_zv, childPath);
	zephir_memory_observe(&parentName_zv);
	ZVAL_STR_COPY(&parentName_zv, parentName);
	ZEPHIR_CALL_METHOD(&parentPath, this_ptr, "resolveTemplatePath", NULL, 0, &parentName_zv, &childPath_zv);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 915, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&options, &_0);
	zephir_memory_observe(&compiledPath);
	_1 = !(zephir_array_isset_string_fetch(&compiledPath, &options, SL("path"), 0));
	if (!(_1)) {
		_1 = Z_TYPE_P(&compiledPath) != IS_STRING;
	}
	_2 = _1;
	if (!(_2)) {
		_2 = ZEPHIR_IS_STRING_IDENTICAL(&compiledPath, "");
	}
	if (_2) {
		ZEPHIR_CALL_FUNCTION(&_3$$3, "sys_get_temp_dir", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&compiledPath);
		ZEPHIR_CONCAT_VS(&compiledPath, &_3$$3, "/");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_VSV(&_4, &childPath_zv, "|", &parentPath);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_FUNCTION(&_5, "sha1", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&variant);
	ZEPHIR_CONCAT_VSVS(&variant, &compiledPath, "variant%%", &_5, ".php");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&always);
	if (!(zephir_array_isset_string_fetch(&always, &options, SL("always"), 0))) {
		ZEPHIR_INIT_NVAR(&always);
		ZVAL_BOOL(&always, 0);
	}
	zephir_memory_observe(&stat);
	if (!(zephir_array_isset_string_fetch(&stat, &options, SL("stat"), 0))) {
		ZEPHIR_INIT_NVAR(&stat);
		ZVAL_BOOL(&stat, 1);
	}
	ZEPHIR_CALL_FUNCTION(NULL, "clearstatcache", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, this_ptr, "phpFileExists", NULL, 0, &variant);
	zephir_check_call_status();
	_7 = !zephir_is_true(&_6);
	if (!(_7)) {
		_7 = zephir_is_true(&always);
	}
	stale = _7;
	_8 = !stale;
	if (_8) {
		_8 = !ZEPHIR_IS_FALSE_IDENTICAL(&stat);
	}
	if (_8) {
		ZEPHIR_INIT_VAR(&_9$$6);
		zephir_filemtime(&_9$$6, &childPath_zv);
		ZEPHIR_INIT_VAR(&_10$$6);
		zephir_filemtime(&_10$$6, &variant);
		_11$$6 = ZEPHIR_GE(&_9$$6, &_10$$6);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		_12$$6 = _11$$6;
		if (!(_12$$6)) {
			ZEPHIR_CALL_METHOD(&_14$$6, this_ptr, "getSignature", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_CE_STATIC(&_13$$6, phalcon_mvc_view_engine_volt_dependencies_ce, "staleReason", NULL, 0, &variant, &_14$$6);
			zephir_check_call_status();
			_12$$6 = Z_TYPE_P(&_13$$6) != IS_NULL;
		}
		stale = _12$$6;
	}
	if (stale) {
		ZEPHIR_INIT_VAR(&subCompiler);
		if (zephir_clone(&subCompiler, this_ptr) == FAILURE) {
			RETURN_MM();
		}
		ZEPHIR_CALL_METHOD(NULL, &subCompiler, "setExtendsOverride", NULL, 0, &parentPath);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &subCompiler, "compileFile", NULL, 0, &childPath_zv, &variant);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&variant);
}

/**
 * The registry of runtime functions, filters and tests
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getRegistry)
{
	zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("registry", 8, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 930, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_view_engine_volt_runtime_registry_ce);
		if (zephir_has_constructor(&_1$$3)) {
			ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 0);
			zephir_check_call_status();
		}

		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 930, &_1$$3);
	}
	RETURN_MM_MEMBER(getThis(), "registry");
}

/**
 * What the compiled output depends on besides files: the runtime
 * registry, autoescape and strict tests
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getSignature)
{
	zval autoescape, registrySignature, _0, _1, _3, _4, _5, _2$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&autoescape);
	ZVAL_UNDEF(&registrySignature);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("registry", 8, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&autoescape);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 915, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string_fetch(&autoescape, &_0, SL("autoescape"), 0))) {
		ZEPHIR_INIT_NVAR(&autoescape);
		ZVAL_BOOL(&autoescape, 0);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 930, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_1) == IS_NULL) {
		ZEPHIR_INIT_VAR(&registrySignature);
		ZVAL_STRING(&registrySignature, "");
	} else {
		zephir_read_property_cached(&_2$$5, this_ptr, _zephir_prop_1, 930, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&registrySignature, &_2$$5, "getSignature", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_3);
	if (zephir_is_true(&autoescape)) {
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_STRING(&_3, "true");
	} else {
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_STRING(&_3, "false");
	}
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "isStrictTests", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_5)) {
		ZEPHIR_INIT_NVAR(&_4);
		ZVAL_STRING(&_4, "true");
	} else {
		ZEPHIR_INIT_NVAR(&_4);
		ZVAL_STRING(&_4, "false");
	}
	ZEPHIR_CONCAT_SVSVSV(return_value, "volt-2|", &registrySignature, "|autoescape=", &_3, "|strictTests=", &_4);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Unknown "is" tests are a compile error instead of compiling to "=="
 * (option "strictTests", default true)
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, isStrictTests)
{
	zval strictTests, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&strictTests);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&strictTests);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 915, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string_fetch(&strictTests, &_0, SL("strictTests"), 0)) {
		RETURN_MM_BOOL(zephir_get_boolval(&strictTests));
	}
	RETURN_MM_BOOL(1);
}

/**
 * Parses a template file used by the resolver (parent, embedded) and
 * records it as a dependency
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, parseFile)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval path_zv, viewCode, intermediate, _0, _1$$3, _2$$4, _3$$5;
	zend_string *path = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&viewCode);
	ZVAL_UNDEF(&intermediate);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "phpFileExists", NULL, 0, &path_zv);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_mvc_view_engine_volt_exceptions_templatefilenotfound_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 0, &path_zv);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2563);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addDependency", NULL, 0, &path_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&viewCode, this_ptr, "phpFileGetContents", NULL, 0, &path_zv);
	zephir_check_call_status();
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&viewCode))) {
		ZEPHIR_INIT_VAR(&_2$$4);
		object_init_ex(&_2$$4, phalcon_mvc_view_engine_volt_exceptions_templatefilenotopenable_ce);
		ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 0, &path_zv);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2571);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&intermediate);
	ZEPHIR_LAST_CALL_STATUS = phvolt_parse_view(&intermediate, &viewCode, &path_zv);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&intermediate) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(&_3$$5);
		object_init_ex(&_3$$5, phalcon_mvc_view_engine_volt_exceptions_invalidintermediaterepresentation_ce);
		ZEPHIR_CALL_METHOD(NULL, &_3$$5, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$5, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2577);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(&intermediate);
}

/**
 * The path of a template named in extends/embed, relative to the
 * template that names it
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, resolveTemplatePath)
{
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, relativeTo_zv, saved, finalPath, _0, _2, _3, _4;
	zend_string *name = NULL, *relativeTo = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&relativeTo_zv);
	ZVAL_UNDEF(&saved);
	ZVAL_UNDEF(&finalPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentPath", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_STR(relativeTo)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_memory_observe(&relativeTo_zv);
	ZVAL_STR_COPY(&relativeTo_zv, relativeTo);
	zephir_memory_observe(&saved);
	zephir_read_property_cached(&saved, this_ptr, _zephir_prop_0, 919, PH_NOISY_CC);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 919, &relativeTo_zv);
	ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", NULL, 0, &name_zv);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 919, &saved);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "phpFileExists", NULL, 0, &finalPath);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		RETURN_CCTOR(&finalPath);
	}
	_1 = !(zephir_end_with_str(&name_zv, SL(".volt")));
	if (_1) {
		ZEPHIR_INIT_VAR(&_3);
		ZEPHIR_CONCAT_VS(&_3, &finalPath, ".volt");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "phpFileExists", NULL, 0, &_3);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_CONCAT_VS(return_value, &finalPath, ".volt");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_4);
	object_init_ex(&_4, phalcon_mvc_view_engine_volt_exceptions_templatefilenotfound_ce);
	ZEPHIR_CALL_METHOD(NULL, &_4, "__construct", NULL, 0, &finalPath);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_4, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2606);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * The parent a dynamic-extends variant is compiled against
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setExtendsOverride)
{
	zval *path, path_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extendsOverride", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(path)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &path);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 931, path);
	RETURN_THISW();
}

/**
 * Shares the runtime registry (the engine owns it)
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, setRegistry)
{
	zval *registry, registry_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&registry_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("registry", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(registry, phalcon_mvc_view_engine_volt_runtime_registry_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &registry);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 930, registry);
	RETURN_THISW();
}

/**
 * Returns and clears the parent override of a dynamic-extends variant
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, takeExtendsOverride)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null, override;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&override);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("extendsOverride", 15, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&override);
	zephir_read_property_cached(&override, this_ptr, _zephir_prop_0, 931, PH_NOISY_CC);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 931, &__$null);
	RETURN_CCTOR(&override);
}

/**
 * a?.b / a?.b(...): only a member name can follow "?."
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileNullsafe)
{
	zend_bool _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *leftCode = NULL;
	zval *expr_param = NULL, leftCode_zv, right, _3, _8, _4$$3, _5$$3, _6$$3, _7$$3;
	zval expr;

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&leftCode_zv);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
		Z_PARAM_STR(leftCode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	expr_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&expr, expr_param);
	zephir_memory_observe(&leftCode_zv);
	ZVAL_STR_COPY(&leftCode_zv, leftCode);
	zephir_memory_observe(&right);
	_0 = !(zephir_array_isset_string_fetch(&right, &expr, SL("right"), 0));
	if (!(_0)) {
		_0 = Z_TYPE_P(&right) != IS_ARRAY;
	}
	_1 = _0;
	if (!(_1)) {
		_1 = !(zephir_array_isset_value_string(&right, SL("type")));
	}
	_2 = _1;
	if (!(_2)) {
		zephir_memory_observe(&_3);
		zephir_array_fetch_string(&_3, &right, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2649);
		_2 = !ZEPHIR_IS_LONG(&_3, 265);
	}
	if (_2) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, phalcon_mvc_view_engine_volt_exception_ce);
		zephir_array_fetch_string(&_5$$3, &expr, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2652);
		zephir_array_fetch_string(&_6$$3, &expr, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2653);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSV(&_7$$3, "Only a property or method name can follow \"?.\" in ", &_5$$3, " on line ", &_6$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 0, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2653);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_8);
	zephir_array_fetch_string(&_8, &right, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2656);
	ZEPHIR_CONCAT_VSV(return_value, &leftCode_zv, "?->", &_8);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * A call to a runtime function, filter or test: a direct call for
 * functions and static methods, otherwise a lookup memoized on the engine
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileRuntimeCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval arguments, _2$$3;
	zval kind_zv, *handler, handler_sub, *arguments_param = NULL, staticCode, method, name, _0, _5, _6, _7, _8, _1$$3, _3$$3, _4$$4;
	zend_string *kind = NULL;

	ZVAL_UNDEF(&kind_zv);
	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&staticCode);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&_2$$3);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(kind)
		Z_PARAM_OBJECT_OF_CLASS(handler, phalcon_mvc_view_engine_volt_runtime_voltcallable_ce)
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 2);
	arguments_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&kind_zv);
	ZVAL_STR_COPY(&kind_zv, kind);
	zephir_get_arrval(&arguments, arguments_param);
	ZEPHIR_CALL_METHOD(&_0, handler, "needsContext", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_create_array(&_2$$3, 1, 0);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "get_defined_vars()");
		zephir_array_fast_append(&_2$$3, &_3$$3);
		zephir_fast_array_merge(&_1$$3, &_2$$3, &arguments);
		if (UNEXPECTED(Z_TYPE_P(&_1$$3) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&_1$$3, "arguments", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&arguments, &_1$$3);
	}
	ZEPHIR_CALL_METHOD(&staticCode, handler, "getStaticCallCode", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&staticCode) != IS_NULL) {
		ZEPHIR_INIT_VAR(&_4$$4);
		zephir_fast_join_str(&_4$$4, SL(", "), &arguments);
		ZEPHIR_CONCAT_VSVS(return_value, &staticCode, "(", &_4$$4, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(&kind_zv, "filter")) {
		ZEPHIR_INIT_VAR(&method);
		ZVAL_STRING(&method, "getRuntimeFilter");
	} else if (ZEPHIR_IS_STRING(&kind_zv, "test")) {
		ZEPHIR_INIT_NVAR(&method);
		ZVAL_STRING(&method, "getRuntimeTest");
	} else {
		ZEPHIR_INIT_NVAR(&method);
		ZVAL_STRING(&method, "getRuntimeFunction");
	}
	ZEPHIR_CALL_METHOD(&name, handler, "getName", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_VSV(&_6, &kind_zv, ":", &name);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_NVAR(&_5);
	zephir_var_export_ex(&_5, &_6);
	ZEPHIR_INIT_VAR(&_7);
	ZEPHIR_INIT_NVAR(&_7);
	zephir_var_export_ex(&_7, &name);
	ZEPHIR_INIT_VAR(&_8);
	zephir_fast_join_str(&_8, SL(", "), &arguments);
	ZEPHIR_CONCAT_SVSVSVSVS(return_value, "($this->runtime[", &_5, "] ??= $this->", &method, "(", &_7, "))(", &_8, ")");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * {% set name %}...{% endset %}: the rendered body in a variable
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSetCapture)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _0;
	zval *statement_param = NULL, *extendsMode_param = NULL, statements, _1, _2, _3;
	zval statement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statement, statement_param)
		Z_PARAM_BOOL(extendsMode)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &statement_param, &extendsMode_param);
	zephir_get_arrval(&statement, statement_param);
	zephir_memory_observe(&statements);
	_0 = !(zephir_array_isset_string_fetch(&statements, &statement, SL("block_statements"), 0));
	if (!(_0)) {
		_0 = Z_TYPE_P(&statements) != IS_ARRAY;
	}
	if (_0) {
		ZEPHIR_INIT_NVAR(&statements);
		array_init(&statements);
	}
	if (extendsMode) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "statementList", NULL, 0, &statements, &_2);
	zephir_check_call_status();
	zephir_array_fetch_string(&_3, &statement, SL("name"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2704);
	ZEPHIR_CONCAT_SVSVS(return_value, "<?php ob_start(); ?>", &_1, "<?php $", &_3, " = ob_get_clean(); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * value is name / value is name(args) / value is not ...
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileTestExpression)
{
	zval _16$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool negate, _2, _3, _4, _7, _8, _10, _0$$5;
	zend_string *leftCode = NULL;
	zval *expr_param = NULL, leftCode_zv, *negate_param = NULL, right, type, name, nameNode, test, testArguments, code, _6, _11, _1$$8, _12$$9, _14$$9, _15$$9, _17$$14, _18$$14, _19$$14, _20$$14;
	zval expr, _5, _9, _13$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&leftCode_zv);
	ZVAL_UNDEF(&right);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&nameNode);
	ZVAL_UNDEF(&test);
	ZVAL_UNDEF(&testArguments);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_1$$8);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_17$$14);
	ZVAL_UNDEF(&_18$$14);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_16$$11);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
		Z_PARAM_STR(leftCode)
		Z_PARAM_BOOL(negate)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	expr_param = ZEND_CALL_ARG(execute_data, 1);
	negate_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_get_arrval(&expr, expr_param);
	zephir_memory_observe(&leftCode_zv);
	ZVAL_STR_COPY(&leftCode_zv, leftCode);
	zephir_memory_observe(&right);
	zephir_array_fetch_string(&right, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2714);
	zephir_memory_observe(&type);
	zephir_array_fetch_string(&type, &right, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2715);
	ZEPHIR_INIT_VAR(&name);
	ZVAL_NULL(&name);
	if (ZEPHIR_IS_LONG(&type, 265)) {
		ZEPHIR_OBS_NVAR(&name);
		zephir_array_fetch_string(&name, &right, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2719);
	} else if (ZEPHIR_IS_LONG(&type, 350)) {
		zephir_memory_observe(&nameNode);
		if (zephir_array_isset_string_fetch(&nameNode, &right, SL("name"), 0)) {
			_0$$5 = Z_TYPE_P(&nameNode) == IS_ARRAY;
			if (_0$$5) {
				_0$$5 = zephir_array_isset_value_string(&nameNode, SL("value"));
			}
			if (_0$$5) {
				ZEPHIR_OBS_NVAR(&name);
				zephir_array_fetch_string(&name, &nameNode, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2723);
			}
		}
	} else if (ZEPHIR_IS_LONG(&type, 261)) {
		ZEPHIR_INIT_NVAR(&name);
		ZVAL_STRING(&name, "null");
	}
	ZEPHIR_INIT_VAR(&test);
	ZVAL_NULL(&test);
	if (Z_TYPE_P(&name) != IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$8);
		ZVAL_STRING(&_1$$8, "test");
		ZEPHIR_CALL_METHOD(&test, this_ptr, "getRuntime", NULL, 0, &_1$$8, &name);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(&test) != IS_NULL) {
		zephir_memory_observe(&testArguments);
		if (!(zephir_array_isset_string_fetch(&testArguments, &right, SL("arguments"), 0))) {
			ZEPHIR_INIT_NVAR(&testArguments);
			ZVAL_NULL(&testArguments);
		}
		ZEPHIR_INIT_VAR(&_12$$9);
		ZEPHIR_INIT_VAR(&_13$$9);
		zephir_create_array(&_13$$9, 1, 0);
		zephir_array_fast_append(&_13$$9, &leftCode_zv);
		ZEPHIR_CALL_METHOD(&_14$$9, this_ptr, "runtimeArguments", NULL, 0, &testArguments);
		zephir_check_call_status();
		zephir_fast_array_merge(&_12$$9, &_13$$9, &_14$$9);
		ZEPHIR_INIT_VAR(&_15$$9);
		ZVAL_STRING(&_15$$9, "test");
		ZEPHIR_CALL_METHOD(&code, this_ptr, "compileRuntimeCall", NULL, 0, &_15$$9, &test, &_12$$9);
		zephir_check_call_status();
	} else {
		_2 = ZEPHIR_IS_STRING_IDENTICAL(&name, "null");
		if (!(_2)) {
			_2 = ZEPHIR_IS_STRING_IDENTICAL(&name, "none");
		}
		if (_2) {
			ZEPHIR_INIT_VAR(&_16$$11);
			ZEPHIR_CONCAT_SVS(&_16$$11, "(", &leftCode_zv, " === null)");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CPY_WRT(&code, &_16$$11);
		} else {
			_3 = Z_TYPE_P(&name) != IS_NULL;
			if (_3) {
				_3 = ZEPHIR_IS_LONG(&type, 265);
			}
			_4 = _3;
			if (_4) {
				ZEPHIR_INIT_VAR(&_5);
				zephir_create_array(&_5, 6, 0);
				ZEPHIR_INIT_VAR(&_6);
				ZVAL_STRING(&_6, "empty");
				zephir_array_fast_append(&_5, &_6);
				ZEPHIR_INIT_NVAR(&_6);
				ZVAL_STRING(&_6, "even");
				zephir_array_fast_append(&_5, &_6);
				ZEPHIR_INIT_NVAR(&_6);
				ZVAL_STRING(&_6, "odd");
				zephir_array_fast_append(&_5, &_6);
				ZEPHIR_INIT_NVAR(&_6);
				ZVAL_STRING(&_6, "numeric");
				zephir_array_fast_append(&_5, &_6);
				ZEPHIR_INIT_NVAR(&_6);
				ZVAL_STRING(&_6, "scalar");
				zephir_array_fast_append(&_5, &_6);
				ZEPHIR_INIT_NVAR(&_6);
				ZVAL_STRING(&_6, "iterable");
				zephir_array_fast_append(&_5, &_6);
				_4 = zephir_fast_in_array(&name, &_5);
			}
			if (_4) {
				ZEPHIR_CALL_METHOD(&code, this_ptr, "resolveTest", NULL, 0, &right, &leftCode_zv);
				zephir_check_call_status();
			} else {
				_7 = Z_TYPE_P(&name) != IS_NULL;
				if (_7) {
					_7 = ZEPHIR_IS_LONG(&type, 350);
				}
				_8 = _7;
				if (_8) {
					ZEPHIR_INIT_VAR(&_9);
					zephir_create_array(&_9, 3, 0);
					ZEPHIR_INIT_NVAR(&_6);
					ZVAL_STRING(&_6, "divisibleby");
					zephir_array_fast_append(&_9, &_6);
					ZEPHIR_INIT_NVAR(&_6);
					ZVAL_STRING(&_6, "sameas");
					zephir_array_fast_append(&_9, &_6);
					ZEPHIR_INIT_NVAR(&_6);
					ZVAL_STRING(&_6, "type");
					zephir_array_fast_append(&_9, &_6);
					_8 = zephir_fast_in_array(&name, &_9);
				}
				if (_8) {
					ZEPHIR_CALL_METHOD(&code, this_ptr, "resolveTest", NULL, 0, &right, &leftCode_zv);
					zephir_check_call_status();
				} else {
					_10 = Z_TYPE_P(&name) != IS_NULL;
					if (_10) {
						ZEPHIR_CALL_METHOD(&_11, this_ptr, "isStrictTests", NULL, 0);
						zephir_check_call_status();
						_10 = zephir_is_true(&_11);
					}
					if (_10) {
						ZEPHIR_INIT_VAR(&_17$$14);
						object_init_ex(&_17$$14, phalcon_mvc_view_engine_volt_exception_ce);
						zephir_array_fetch_string(&_18$$14, &expr, SL("file"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2757);
						zephir_array_fetch_string(&_19$$14, &expr, SL("line"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2758);
						ZEPHIR_INIT_VAR(&_20$$14);
						ZEPHIR_CONCAT_SVSVSVS(&_20$$14, "Unknown test \"", &name, "\" in ", &_18$$14, " on line ", &_19$$14, " (register it with Volt::addTest(), or set the 'strictTests' option to false)");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_17$$14, "__construct", NULL, 0, &_20$$14);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_17$$14, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2759);
						ZEPHIR_MM_RESTORE();
						return;
					} else {
						ZEPHIR_CALL_METHOD(&code, this_ptr, "resolveTest", NULL, 0, &right, &leftCode_zv);
						zephir_check_call_status();
					}
				}
			}
		}
	}
	if (negate) {
		ZEPHIR_CONCAT_SVS(return_value, "!(", &code, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	RETURN_CCTOR(&code);
}

/**
 * A template named by a string literal in include: with or without
 * ".volt", or null when it is not a file
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, findTemplate)
{
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, finalPath, _0, _2, _3;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&finalPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", NULL, 0, &name_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "phpFileExists", NULL, 0, &finalPath);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		RETURN_CCTOR(&finalPath);
	}
	_1 = !(zephir_end_with_str(&name_zv, SL(".volt")));
	if (_1) {
		ZEPHIR_INIT_VAR(&_3);
		ZEPHIR_CONCAT_VS(&_3, &finalPath, ".volt");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "phpFileExists", NULL, 0, &_3);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_CONCAT_VS(return_value, &finalPath, ".volt");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	RETURN_MM_NULL();
}

/**
 * A registered runtime function, filter or test, or null
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getRuntime)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval kind_zv, name_zv, _0, _1;
	zend_string *kind = NULL, *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kind_zv);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("registry", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(kind)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&kind_zv);
	ZVAL_STR_COPY(&kind_zv, kind);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 930, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 930, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_1, "get", NULL, 0, &kind_zv, &name_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * An expression whose result must not be HTML-escaped again by autoescape
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, isSafeExpression)
{
	zend_bool _6, _4$$4, _1$$6, _7$$11, _8$$11, _12$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *expr_param = NULL, type, filter, filterName, nameNode, name, runtime, _0$$4, _3$$4, _5$$4, _9$$11, _11$$11, _13$$11;
	zval expr, _2$$4, _10$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&filterName);
	ZVAL_UNDEF(&nameNode);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&runtime);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_13$$11);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(expr, expr_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expr_param);
	zephir_get_arrval(&expr, expr_param);
	zephir_memory_observe(&type);
	if (!(zephir_array_isset_string_fetch(&type, &expr, SL("type"), 0))) {
		RETURN_MM_BOOL(0);
	}
	if (ZEPHIR_IS_LONG(&type, 124)) {
		zephir_memory_observe(&filter);
		zephir_array_fetch_string(&filter, &expr, SL("right"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2820);
		ZEPHIR_INIT_VAR(&filterName);
		ZVAL_NULL(&filterName);
		zephir_memory_observe(&_0$$4);
		zephir_array_fetch_string(&_0$$4, &filter, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2823);
		if (ZEPHIR_IS_LONG(&_0$$4, 350)) {
			zephir_memory_observe(&nameNode);
			if (zephir_array_isset_string_fetch(&nameNode, &filter, SL("name"), 0)) {
				_1$$6 = Z_TYPE_P(&nameNode) == IS_ARRAY;
				if (_1$$6) {
					_1$$6 = zephir_array_isset_value_string(&nameNode, SL("value"));
				}
				if (_1$$6) {
					ZEPHIR_OBS_NVAR(&filterName);
					zephir_array_fetch_string(&filterName, &nameNode, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2826);
				}
			}
		} else if (zephir_array_isset_value_string(&filter, SL("value"))) {
			ZEPHIR_OBS_NVAR(&filterName);
			zephir_array_fetch_string(&filterName, &filter, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2830);
		}
		if (Z_TYPE_P(&filterName) != IS_STRING) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_VAR(&_2$$4);
		zephir_create_array(&_2$$4, 7, 0);
		ZEPHIR_INIT_VAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "raw");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "e");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "escape");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "escape_js");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "escape_css");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "escape_attr");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "url_encode");
		zephir_array_fast_append(&_2$$4, &_3$$4);
		if (zephir_fast_in_array(&filterName, &_2$$4)) {
			RETURN_MM_BOOL(1);
		}
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "filter");
		ZEPHIR_CALL_METHOD(&runtime, this_ptr, "getRuntime", NULL, 0, &_3$$4, &filterName);
		zephir_check_call_status();
		_4$$4 = Z_TYPE_P(&runtime) != IS_NULL;
		if (_4$$4) {
			ZEPHIR_CALL_METHOD(&_5$$4, &runtime, "isSafe", NULL, 0);
			zephir_check_call_status();
			_4$$4 = zephir_is_true(&_5$$4);
		}
		RETURN_MM_BOOL(_4$$4);
	}
	_6 = ZEPHIR_IS_LONG(&type, 350);
	if (_6) {
		ZEPHIR_OBS_NVAR(&nameNode);
		_6 = zephir_array_isset_string_fetch(&nameNode, &expr, SL("name"), 0);
	}
	if (_6) {
		_7$$11 = Z_TYPE_P(&nameNode) != IS_ARRAY;
		if (!(_7$$11)) {
			_7$$11 = !(zephir_array_isset_value_string(&nameNode, SL("type")));
		}
		_8$$11 = _7$$11;
		if (!(_8$$11)) {
			zephir_memory_observe(&_9$$11);
			zephir_array_fetch_string(&_9$$11, &nameNode, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2847);
			_8$$11 = !ZEPHIR_IS_LONG(&_9$$11, 265);
		}
		if (_8$$11) {
			RETURN_MM_BOOL(0);
		}
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &nameNode, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2851);
		ZEPHIR_INIT_VAR(&_10$$11);
		zephir_create_array(&_10$$11, 3, 0);
		ZEPHIR_INIT_VAR(&_11$$11);
		ZVAL_STRING(&_11$$11, "content");
		zephir_array_fast_append(&_10$$11, &_11$$11);
		ZEPHIR_INIT_NVAR(&_11$$11);
		ZVAL_STRING(&_11$$11, "get_content");
		zephir_array_fast_append(&_10$$11, &_11$$11);
		ZEPHIR_INIT_NVAR(&_11$$11);
		ZVAL_STRING(&_11$$11, "partial");
		zephir_array_fast_append(&_10$$11, &_11$$11);
		if (zephir_fast_in_array(&name, &_10$$11)) {
			RETURN_MM_BOOL(1);
		}
		ZEPHIR_INIT_NVAR(&_11$$11);
		ZVAL_STRING(&_11$$11, "function");
		ZEPHIR_CALL_METHOD(&runtime, this_ptr, "getRuntime", NULL, 0, &_11$$11, &name);
		zephir_check_call_status();
		_12$$11 = Z_TYPE_P(&runtime) != IS_NULL;
		if (_12$$11) {
			ZEPHIR_CALL_METHOD(&_13$$11, &runtime, "isSafe", NULL, 0);
			zephir_check_call_status();
			_12$$11 = zephir_is_true(&_13$$11);
		}
		RETURN_MM_BOOL(_12$$11);
	}
	RETURN_MM_BOOL(0);
}

/**
 * Compiled arguments of a runtime call; 'name': value becomes a PHP named
 * argument
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, runtimeArguments)
{
	zend_bool _14;
	zval items;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exprArgs, exprArgs_sub, argument, code, name, *_0, _1, *_2, _13, _3$$4, _5$$5, _6$$5, _7$$5, _8$$5, _12$$5, _9$$6, _10$$6, _15$$7, _16$$8, _17$$8, _18$$8, _19$$8, _22$$8, _20$$9, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exprArgs_sub);
	ZVAL_UNDEF(&argument);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&items);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(exprArgs)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &exprArgs);
	ZEPHIR_INIT_VAR(&items);
	array_init(&items);
	if (Z_TYPE_P(exprArgs) != IS_ARRAY) {
		RETURN_CTOR(&items);
	}
	if (Z_TYPE_P(exprArgs) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_1);
		zephir_string_to_char_array(&_1, exprArgs);
		_0 = &_1;
	} else {
		_0 = exprArgs;
	}
	zephir_is_iterable(_0, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2894);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0), _2)
		{
			ZEPHIR_INIT_NVAR(&argument);
			ZVAL_COPY(&argument, _2);
			ZEPHIR_OBS_NVAR(&_3$$4);
			zephir_array_fetch_string(&_3$$4, &argument, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2881);
			ZEPHIR_CALL_METHOD(&code, this_ptr, "expression", &_4, 0, &_3$$4);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&name);
			if (zephir_array_isset_string_fetch(&name, &argument, SL("name"), 0)) {
				ZEPHIR_INIT_NVAR(&_5$$5);
				ZEPHIR_INIT_NVAR(&_6$$5);
				ZVAL_STRING(&_6$$5, "/^[A-Za-z_][A-Za-z0-9_]*$/");
				ZEPHIR_INIT_NVAR(&_7$$5);
				ZEPHIR_INIT_NVAR(&_8$$5);
				ZVAL_STRING(&_8$$5, "/^[A-Za-z_][A-Za-z0-9_]*$/");
				zephir_preg_match(&_7$$5, &_8$$5, &name, &_5$$5, 0, 0 , 0 );
				if (UNEXPECTED(!zephir_is_true(&_7$$5))) {
					ZEPHIR_INIT_NVAR(&_9$$6);
					object_init_ex(&_9$$6, phalcon_mvc_view_engine_volt_exception_ce);
					ZEPHIR_INIT_NVAR(&_10$$6);
					ZEPHIR_CONCAT_SVS(&_10$$6, "Invalid argument name '", &name, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_9$$6, "__construct", &_11, 0, &_10$$6);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_9$$6, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2885);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_INIT_NVAR(&_12$$5);
				ZEPHIR_CONCAT_VSV(&_12$$5, &name, ": ", &code);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CPY_WRT(&code, &_12$$5);
			}
			zephir_array_append(&items, &code, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2891);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _0, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _0, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&argument, _0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_15$$7);
				zephir_array_fetch_string(&_15$$7, &argument, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2881);
				ZEPHIR_CALL_METHOD(&code, this_ptr, "expression", &_4, 0, &_15$$7);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&name);
				if (zephir_array_isset_string_fetch(&name, &argument, SL("name"), 0)) {
					ZEPHIR_INIT_NVAR(&_16$$8);
					ZEPHIR_INIT_NVAR(&_17$$8);
					ZVAL_STRING(&_17$$8, "/^[A-Za-z_][A-Za-z0-9_]*$/");
					ZEPHIR_INIT_NVAR(&_18$$8);
					ZEPHIR_INIT_NVAR(&_19$$8);
					ZVAL_STRING(&_19$$8, "/^[A-Za-z_][A-Za-z0-9_]*$/");
					zephir_preg_match(&_18$$8, &_19$$8, &name, &_16$$8, 0, 0 , 0 );
					if (UNEXPECTED(!zephir_is_true(&_18$$8))) {
						ZEPHIR_INIT_NVAR(&_20$$9);
						object_init_ex(&_20$$9, phalcon_mvc_view_engine_volt_exception_ce);
						ZEPHIR_INIT_NVAR(&_21$$9);
						ZEPHIR_CONCAT_SVS(&_21$$9, "Invalid argument name '", &name, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_20$$9, "__construct", &_11, 0, &_21$$9);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_20$$9, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2885);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_22$$8);
					ZEPHIR_CONCAT_VSV(&_22$$8, &name, ": ", &code);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CPY_WRT(&code, &_22$$8);
				}
				zephir_array_append(&items, &code, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2891);
		}
	}
	ZEPHIR_INIT_NVAR(&argument);
	RETURN_CTOR(&items);
}

/**
 * Compiles a Volt source code returning a PHP plain version
 *
 * @phpstan-return array<array-key, mixed>|string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, compileSource)
{
	zend_ulong _13$$7;
	zval _7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _16$$7;
	zval viewCode_zv, *extendsMode_param = NULL, __$true, __$false, __$null, currentPath, intermediate, extended, finalCompilation, blocks, extendedBlocks, name, block, blockCompilation, localBlock, compilation, options, autoescape, _0, _5, _6, _8, _1$$5, _2$$5, _3$$5, _4$$6, _9$$7, *_10$$7, _11$$7, *_12$$7, _15$$7, _17$$35;
	zend_string *viewCode = NULL, *_14$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewCode_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
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
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_17$$35);
	ZVAL_UNDEF(&_7);
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
		_zephir_prop_7 = zend_string_init("currentPath", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("autoescape", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("currentBlock", 12, 1);
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
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 932, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 932, &__$false);
	}
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 926, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 926, &__$false);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 933, &__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 934, &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 913, &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 935, &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 928, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_7, 919, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&currentPath, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_8, 915, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&options, &_0);
	if (Z_TYPE_P(&options) == IS_ARRAY) {
		zephir_memory_observe(&autoescape);
		if (zephir_array_isset_string_fetch(&autoescape, &options, SL("autoescape"), 0)) {
			if (UNEXPECTED(((Z_TYPE_P(&autoescape) == IS_TRUE || Z_TYPE_P(&autoescape) == IS_FALSE) != 1))) {
				ZEPHIR_INIT_VAR(&_1$$5);
				object_init_ex(&_1$$5, phalcon_mvc_view_engine_volt_exceptions_invalidoptiontype_ce);
				ZEPHIR_INIT_VAR(&_2$$5);
				ZVAL_STRING(&_2$$5, "autoescape");
				ZEPHIR_INIT_VAR(&_3$$5);
				ZVAL_STRING(&_3$$5, "bool");
				ZEPHIR_CALL_METHOD(NULL, &_1$$5, "__construct", NULL, 0, &_2$$5, &_3$$5);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_1$$5, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2933);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 918, &autoescape);
		}
	}
	ZEPHIR_INIT_VAR(&intermediate);
	ZEPHIR_LAST_CALL_STATUS = phvolt_parse_view(&intermediate, &viewCode_zv, &currentPath);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&intermediate) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(&_4$$6);
		object_init_ex(&_4$$6, phalcon_mvc_view_engine_volt_exceptions_invalidintermediaterepresentation_ce);
		ZEPHIR_CALL_METHOD(NULL, &_4$$6, "__construct", NULL, 0);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$6, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2946);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	object_init_ex(&_5, phalcon_mvc_view_engine_volt_resolver_ce);
	ZEPHIR_CALL_METHOD(NULL, &_5, "__construct", NULL, 0, this_ptr);
	zephir_check_call_status();
	zephir_cast_to_string(&_7, &currentPath);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_6, &_5, "resolve", NULL, 0, &intermediate, &_7);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&intermediate, &_6);
	if (extendsMode) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_CALL_METHOD(&compilation, this_ptr, "statementList", NULL, 0, &intermediate, &_0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_0, 932, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extended, &_8);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&extended)) {
		ZEPHIR_INIT_VAR(&finalCompilation);
		if (extendsMode == 1) {
			array_init(&finalCompilation);
		} else {
			ZVAL_NULL(&finalCompilation);
		}
		zephir_read_property_cached(&_9$$7, this_ptr, _zephir_prop_2, 933, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&blocks, &_9$$7);
		zephir_read_property_cached(&_9$$7, this_ptr, _zephir_prop_1, 926, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&extendedBlocks, &_9$$7);
		if (Z_TYPE_P(&blocks) != IS_ARRAY) {
			ZEPHIR_INIT_NVAR(&blocks);
			array_init(&blocks);
		}
		if (Z_TYPE_P(&extendedBlocks) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_11$$7);
			zephir_string_to_char_array(&_11$$7, &extendedBlocks);
			_10$$7 = &_11$$7;
		} else {
			_10$$7 = &extendedBlocks;
		}
		zephir_is_iterable(_10$$7, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3033);
		if (Z_TYPE_P(_10$$7) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_10$$7), _13$$7, _14$$7, _12$$7)
			{
				ZEPHIR_INIT_NVAR(&name);
				if (_14$$7 != NULL) { 
					ZVAL_STR_COPY(&name, _14$$7);
				} else {
					ZVAL_LONG(&name, _13$$7);
				}
				ZEPHIR_INIT_NVAR(&block);
				ZVAL_COPY(&block, _12$$7);
				if (Z_TYPE_P(&name) == IS_STRING) {
					if (zephir_array_key_exists(&blocks, &name)) {
						ZEPHIR_OBS_NVAR(&localBlock);
						zephir_array_fetch(&localBlock, &blocks, &name, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2993);
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_10, 927, &name);
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
						zephir_array_append(&finalCompilation, &block, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3026);
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
			ZEPHIR_CALL_METHOD(NULL, _10$$7, "rewind", NULL, 0);
			zephir_check_call_status();
			_16$$7 = 1;
			while (1) {
				if (_16$$7) {
					_16$$7 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _10$$7, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_15$$7, _10$$7, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_15$$7)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&name, _10$$7, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&block, _10$$7, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&name) == IS_STRING) {
						if (zephir_array_key_exists(&blocks, &name)) {
							ZEPHIR_OBS_NVAR(&localBlock);
							zephir_array_fetch(&localBlock, &blocks, &name, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 2993);
							zephir_update_property_zval_cached(this_ptr, _zephir_prop_10, 927, &name);
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
							zephir_array_append(&finalCompilation, &block, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3026);
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
		zephir_read_property_cached(&_17$$35, this_ptr, _zephir_prop_2, 933, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&blocks, &_17$$35);
		if (Z_TYPE_P(&blocks) != IS_ARRAY) {
			ZEPHIR_INIT_NVAR(&blocks);
			array_init(&blocks);
		}
		RETURN_CCTOR(&blocks);
	}
	RETURN_CCTOR(&compilation);
}

/**
 * Gets the final path with VIEW
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, getFinalPath)
{
	zend_bool _1, _12$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval path_zv, view, viewsDirs, viewsDir, _0, _4, _2$$4, _3$$4, *_5$$6, _6$$6, *_7$$6, _11$$6, _8$$7, _9$$7, _13$$9, _14$$9;
	zend_string *path = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&viewsDirs);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$9);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentPath", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("view", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_INIT_VAR(&viewsDir);
	ZVAL_STRING(&viewsDir, "");
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isAbsolutePath", NULL, 0, &path_zv);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		RETURN_MM_STR(zend_string_copy(path));
	}
	_1 = zephir_start_with_str(&path_zv, SL("./"));
	if (!(_1)) {
		_1 = zephir_start_with_str(&path_zv, SL("../"));
	}
	if (_1) {
		zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_0, 919, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(&_3$$4, "dirname", NULL, 0, &_2$$4);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VSV(return_value, &_3$$4, "/", &path_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_1, 912, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&view, &_4);
	if (Z_TYPE_P(&view) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(&viewsDirs, &view, "getViewsDir", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&viewsDirs) == IS_ARRAY) {
			if (Z_TYPE_P(&viewsDirs) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_6$$6);
				zephir_string_to_char_array(&_6$$6, &viewsDirs);
				_5$$6 = &_6$$6;
			} else {
				_5$$6 = &viewsDirs;
			}
			zephir_is_iterable(_5$$6, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3092);
			if (Z_TYPE_P(_5$$6) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5$$6), _7$$6)
				{
					ZEPHIR_INIT_NVAR(&viewsDir);
					ZVAL_COPY(&viewsDir, _7$$6);
					ZEPHIR_INIT_NVAR(&_9$$7);
					ZEPHIR_CONCAT_VV(&_9$$7, &viewsDir, &path_zv);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_8$$7, this_ptr, "phpFileExists", &_10, 0, &_9$$7);
					zephir_check_call_status();
					if (zephir_is_true(&_8$$7)) {
						ZEPHIR_CONCAT_VV(return_value, &viewsDir, &path_zv);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						RETURN_MM();
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _5$$6, "rewind", NULL, 0);
				zephir_check_call_status();
				_12$$6 = 1;
				while (1) {
					if (_12$$6) {
						_12$$6 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _5$$6, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_11$$6, _5$$6, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$6)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&viewsDir, _5$$6, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_14$$9);
						ZEPHIR_CONCAT_VV(&_14$$9, &viewsDir, &path_zv);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&_13$$9, this_ptr, "phpFileExists", &_10, 0, &_14$$9);
						zephir_check_call_status();
						if (zephir_is_true(&_13$$9)) {
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
 *
 * @phpstan-param mvc_volt_node $filter
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, resolveFilter)
{
	zend_bool _29$$33, _34$$44;
	zval _38, _40, _2$$5, _12$$11, _14$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *left = NULL;
	zval *filter_param = NULL, left_zv, code, type, functionName, name, file, line, extensions, filters, funcArguments, arguments, definition, runtime, runtimeArguments, _7, _17, _39, _41, _0$$5, _1$$5, _3$$5, _4$$5, _9$$9, _11$$11, _13$$11, _15$$11, _16$$11, _18$$15, _20$$15, _21$$15, _22$$27, _23$$27, _24$$27, _25$$27, _26$$27, _27$$27, _28$$33, _30$$33, _31$$33, _32$$33, _33$$44, _35$$44, _36$$44, _37$$44;
	zval filter, _5$$7, _6$$7, _8$$9, _10$$14, _19$$15;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_10$$14);
	ZVAL_UNDEF(&_19$$15);
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
	ZVAL_UNDEF(&runtime);
	ZVAL_UNDEF(&runtimeArguments);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_18$$15);
	ZVAL_UNDEF(&_20$$15);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_22$$27);
	ZVAL_UNDEF(&_23$$27);
	ZVAL_UNDEF(&_24$$27);
	ZVAL_UNDEF(&_25$$27);
	ZVAL_UNDEF(&_26$$27);
	ZVAL_UNDEF(&_27$$27);
	ZVAL_UNDEF(&_28$$33);
	ZVAL_UNDEF(&_30$$33);
	ZVAL_UNDEF(&_31$$33);
	ZVAL_UNDEF(&_32$$33);
	ZVAL_UNDEF(&_33$$44);
	ZVAL_UNDEF(&_35$$44);
	ZVAL_UNDEF(&_36$$44);
	ZVAL_UNDEF(&_37$$44);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_14$$11);
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
	zephir_get_arrval(&filter, filter_param);
	zephir_memory_observe(&left_zv);
	ZVAL_STR_COPY(&left_zv, left);
	ZEPHIR_INIT_VAR(&code);
	ZVAL_NULL(&code);
	zephir_memory_observe(&type);
	zephir_array_fetch_string(&type, &filter, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3114);
	if (ZEPHIR_IS_LONG(&type, 265)) {
		zephir_memory_observe(&name);
		zephir_array_fetch_string(&name, &filter, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3120);
	} else {
		if (UNEXPECTED(!ZEPHIR_IS_LONG(&type, 350))) {
			ZEPHIR_INIT_VAR(&_0$$5);
			object_init_ex(&_0$$5, phalcon_mvc_view_engine_volt_exceptions_unknownvoltfiltertype_ce);
			zephir_memory_observe(&_1$$5);
			zephir_array_fetch_string(&_1$$5, &filter, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3126);
			zephir_cast_to_string(&_2$$5, &_1$$5);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_memory_observe(&_3$$5);
			zephir_array_fetch_string(&_3$$5, &filter, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3126);
			ZVAL_LONG(&_4$$5, zephir_get_intval(&_3$$5));
			ZEPHIR_CALL_METHOD(NULL, &_0$$5, "__construct", NULL, 0, &_2$$5, &_4$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_0$$5, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3126);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_memory_observe(&functionName);
		zephir_array_fetch_string(&functionName, &filter, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3129);
		ZEPHIR_OBS_NVAR(&name);
		zephir_array_fetch_string(&name, &functionName, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3130);
	}
	ZEPHIR_INIT_VAR(&funcArguments);
	ZVAL_NULL(&funcArguments);
	ZEPHIR_INIT_VAR(&arguments);
	ZVAL_NULL(&arguments);
	ZEPHIR_OBS_NVAR(&funcArguments);
	if (zephir_array_isset_string_fetch(&funcArguments, &filter, SL("arguments"), 0)) {
		if (!ZEPHIR_IS_STRING(&name, "default")) {
			zephir_memory_observe(&file);
			zephir_array_fetch_string(&file, &filter, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3144);
			zephir_memory_observe(&line);
			zephir_array_fetch_string(&line, &filter, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3145);
			ZEPHIR_INIT_VAR(&_5$$7);
			zephir_create_array(&_5$$7, 3, 0);
			ZEPHIR_INIT_VAR(&_6$$7);
			zephir_create_array(&_6$$7, 4, 0);
			add_assoc_long_ex(&_6$$7, SL("type"), 364);
			zephir_array_update_string(&_6$$7, SL("value"), &left_zv, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_6$$7, SL("file"), &file, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_6$$7, SL("line"), &line, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_5$$7, SL("expr"), &_6$$7, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_5$$7, SL("file"), &file, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_5$$7, SL("line"), &line, PH_COPY | PH_SEPARATE);
			ZEPHIR_MAKE_REF(&funcArguments);
			ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 303, &funcArguments, &_5$$7);
			ZEPHIR_UNREF(&funcArguments);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&arguments, this_ptr, "expression", NULL, 0, &funcArguments);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&arguments, &left_zv);
	}
	zephir_read_property_cached(&_7, this_ptr, _zephir_prop_0, 924, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&extensions, &_7);
	if (!(ZEPHIR_IS_EMPTY(&extensions))) {
		ZEPHIR_INIT_VAR(&_8$$9);
		zephir_create_array(&_8$$9, 3, 0);
		zephir_array_fast_append(&_8$$9, &name);
		zephir_array_fast_append(&_8$$9, &arguments);
		zephir_array_fast_append(&_8$$9, &funcArguments);
		ZEPHIR_INIT_VAR(&_9$$9);
		ZVAL_STRING(&_9$$9, "compileFilter");
		ZEPHIR_CALL_METHOD(&code, this_ptr, "fireExtensionEvent", NULL, 0, &_9$$9, &_8$$9);
		zephir_check_call_status();
		if (Z_TYPE_P(&code) == IS_STRING) {
			RETURN_CCTOR(&code);
		}
	}
	zephir_read_property_cached(&_7, this_ptr, _zephir_prop_1, 936, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&filters, &_7);
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
				ZEPHIR_INIT_VAR(&_10$$14);
				zephir_create_array(&_10$$14, 2, 0);
				zephir_array_fast_append(&_10$$14, &arguments);
				zephir_array_fast_append(&_10$$14, &funcArguments);
				ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &definition, &_10$$14);
				zephir_check_call_status();
				RETURN_MM();
			}
		}
		ZEPHIR_INIT_VAR(&_11$$11);
		object_init_ex(&_11$$11, phalcon_mvc_view_engine_volt_exceptions_invaliduserfilterdefinition_ce);
		zephir_cast_to_string(&_12$$11, &name);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_memory_observe(&_13$$11);
		zephir_array_fetch_string(&_13$$11, &filter, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3218);
		zephir_cast_to_string(&_14$$11, &_13$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_memory_observe(&_15$$11);
		zephir_array_fetch_string(&_15$$11, &filter, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3218);
		ZVAL_LONG(&_16$$11, zephir_get_intval(&_15$$11));
		ZEPHIR_CALL_METHOD(NULL, &_11$$11, "__construct", NULL, 0, &_12$$11, &_14$$11, &_16$$11);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_11$$11, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3218);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_17);
	ZVAL_STRING(&_17, "filter");
	ZEPHIR_CALL_METHOD(&runtime, this_ptr, "getRuntime", NULL, 0, &_17, &name);
	zephir_check_call_status();
	if (Z_TYPE_P(&runtime) != IS_NULL) {
		zephir_memory_observe(&runtimeArguments);
		if (!(zephir_array_isset_string_fetch(&runtimeArguments, &filter, SL("arguments"), 0))) {
			ZEPHIR_INIT_NVAR(&runtimeArguments);
			ZVAL_NULL(&runtimeArguments);
		}
		ZEPHIR_INIT_VAR(&_18$$15);
		ZEPHIR_INIT_VAR(&_19$$15);
		zephir_create_array(&_19$$15, 1, 0);
		zephir_array_fast_append(&_19$$15, &left_zv);
		ZEPHIR_CALL_METHOD(&_20$$15, this_ptr, "runtimeArguments", NULL, 0, &runtimeArguments);
		zephir_check_call_status();
		zephir_fast_array_merge(&_18$$15, &_19$$15, &_20$$15);
		ZEPHIR_INIT_VAR(&_21$$15);
		ZVAL_STRING(&_21$$15, "filter");
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "compileRuntimeCall", NULL, 0, &_21$$15, &runtime, &_18$$15);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(&name, "raw")) {
		RETURN_MM_STR(zend_string_copy(left));
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
		zephir_memory_observe(&_23$$27);
		zephir_array_fetch_long(&_23$$27, &funcArguments, 1, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3269);
		zephir_memory_observe(&_24$$27);
		zephir_array_fetch_string(&_24$$27, &_23$$27, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3269);
		ZEPHIR_CALL_METHOD(&_22$$27, this_ptr, "expression", NULL, 0, &_24$$27);
		zephir_check_call_status();
		zephir_memory_observe(&_26$$27);
		zephir_array_fetch_long(&_26$$27, &funcArguments, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3270);
		zephir_memory_observe(&_27$$27);
		zephir_array_fetch_string(&_27$$27, &_26$$27, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3270);
		ZEPHIR_CALL_METHOD(&_25$$27, this_ptr, "expression", NULL, 0, &_27$$27);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVSVS(return_value, "join(", &_22$$27, ", ", &_25$$27, ")");
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
		zephir_read_property_cached(&_28$$33, this_ptr, _zephir_prop_2, 914, PH_NOISY_CC | PH_READONLY);
		_29$$33 = Z_TYPE_P(&_28$$33) != IS_NULL;
		if (_29$$33) {
			zephir_read_property_cached(&_30$$33, this_ptr, _zephir_prop_2, 914, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_32$$33);
			ZVAL_STRING(&_32$$33, "helper");
			ZEPHIR_CALL_METHOD(&_31$$33, &_30$$33, "has", NULL, 0, &_32$$33);
			zephir_check_call_status();
			_29$$33 = ZEPHIR_IS_TRUE_IDENTICAL(&_31$$33);
		}
		if (_29$$33) {
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
		zephir_read_property_cached(&_33$$44, this_ptr, _zephir_prop_2, 914, PH_NOISY_CC | PH_READONLY);
		_34$$44 = Z_TYPE_P(&_33$$44) != IS_NULL;
		if (_34$$44) {
			zephir_read_property_cached(&_35$$44, this_ptr, _zephir_prop_2, 914, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_37$$44);
			ZVAL_STRING(&_37$$44, "helper");
			ZEPHIR_CALL_METHOD(&_36$$44, &_35$$44, "has", NULL, 0, &_37$$44);
			zephir_check_call_status();
			_34$$44 = ZEPHIR_IS_TRUE_IDENTICAL(&_36$$44);
		}
		if (_34$$44) {
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

	ZEPHIR_INIT_NVAR(&_17);
	object_init_ex(&_17, phalcon_mvc_view_engine_volt_exceptions_unknownvoltfilter_ce);
	zephir_cast_to_string(&_38, &name);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_39);
	zephir_array_fetch_string(&_39, &filter, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3315);
	zephir_cast_to_string(&_40, &_39);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_41);
	zephir_array_fetch_string(&_41, &filter, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3315);
	ZVAL_LONG(&_7, zephir_get_intval(&_41));
	ZEPHIR_CALL_METHOD(NULL, &_17, "__construct", NULL, 0, &_38, &_40, &_7);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_17, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3315);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Traverses a statement list compiling each of its nodes
 *
 * @phpstan-param mvc_volt_node $statements
 * @phpstan-return string
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, statementList)
{
	zval _128, _7$$7, _71$$41, _81$$44, _124$$78;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_10 = NULL, *_14 = NULL, *_18 = NULL, *_23 = NULL, *_27 = NULL, *_29 = NULL, *_32 = NULL, *_34 = NULL, *_39 = NULL, *_41 = NULL, *_43 = NULL, *_47 = NULL, *_49 = NULL, *_51 = NULL, *_53 = NULL, *_55 = NULL, *_57 = NULL, *_60 = NULL, *_62 = NULL, *_65 = NULL, *_68 = NULL, *_75 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool extendsMode, _1, _77;
	zval *statements_param = NULL, *extendsMode_param = NULL, __$true, __$false, extended, blockMode, compilation, extensions, statement, tempCompilation, type, blockName, blockStatements, blocks, path, finalPath, subCompiler, level, _0, *_2, _76, _3$$6, _5$$7, _6$$7, _8$$7, _9$$7, _11$$5, _13$$8, _15$$10, _16$$11, _17$$11, _19$$12, _20$$12, _21$$12, _22$$12, _24$$14, _25$$15, _26$$15, _28$$16, _30$$17, _31$$17, _33$$18, _35$$19, _36$$19, _37$$20, _38$$20, _40$$21, _42$$22, _44$$23, _45$$28, _46$$28, _48$$29, _50$$30, _52$$31, _54$$32, _56$$33, _58$$34, _59$$34, _61$$37, _63$$38, _64$$38, _66$$39, _67$$39, _69$$41, _70$$41, _72$$41, _73$$41, _74$$41, _78$$43, _79$$44, _80$$44, _82$$44, _83$$44, _84$$42, _86$$45, _87$$47, _88$$48, _89$$48, _90$$49, _91$$49, _92$$49, _93$$49, _94$$51, _95$$52, _96$$52, _97$$53, _98$$54, _99$$54, _100$$55, _101$$56, _102$$56, _103$$57, _104$$57, _105$$58, _106$$59, _107$$60, _108$$65, _109$$65, _110$$66, _111$$67, _112$$68, _113$$69, _114$$70, _115$$71, _116$$71, _117$$74, _118$$75, _119$$75, _120$$76, _121$$76, _122$$78, _123$$78, _125$$78, _126$$78, _127$$78;
	zval statements, _12$$8, _85$$45;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_85$$45);
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
	ZVAL_UNDEF(&_76);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&_22$$12);
	ZVAL_UNDEF(&_24$$14);
	ZVAL_UNDEF(&_25$$15);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_28$$16);
	ZVAL_UNDEF(&_30$$17);
	ZVAL_UNDEF(&_31$$17);
	ZVAL_UNDEF(&_33$$18);
	ZVAL_UNDEF(&_35$$19);
	ZVAL_UNDEF(&_36$$19);
	ZVAL_UNDEF(&_37$$20);
	ZVAL_UNDEF(&_38$$20);
	ZVAL_UNDEF(&_40$$21);
	ZVAL_UNDEF(&_42$$22);
	ZVAL_UNDEF(&_44$$23);
	ZVAL_UNDEF(&_45$$28);
	ZVAL_UNDEF(&_46$$28);
	ZVAL_UNDEF(&_48$$29);
	ZVAL_UNDEF(&_50$$30);
	ZVAL_UNDEF(&_52$$31);
	ZVAL_UNDEF(&_54$$32);
	ZVAL_UNDEF(&_56$$33);
	ZVAL_UNDEF(&_58$$34);
	ZVAL_UNDEF(&_59$$34);
	ZVAL_UNDEF(&_61$$37);
	ZVAL_UNDEF(&_63$$38);
	ZVAL_UNDEF(&_64$$38);
	ZVAL_UNDEF(&_66$$39);
	ZVAL_UNDEF(&_67$$39);
	ZVAL_UNDEF(&_69$$41);
	ZVAL_UNDEF(&_70$$41);
	ZVAL_UNDEF(&_72$$41);
	ZVAL_UNDEF(&_73$$41);
	ZVAL_UNDEF(&_74$$41);
	ZVAL_UNDEF(&_78$$43);
	ZVAL_UNDEF(&_79$$44);
	ZVAL_UNDEF(&_80$$44);
	ZVAL_UNDEF(&_82$$44);
	ZVAL_UNDEF(&_83$$44);
	ZVAL_UNDEF(&_84$$42);
	ZVAL_UNDEF(&_86$$45);
	ZVAL_UNDEF(&_87$$47);
	ZVAL_UNDEF(&_88$$48);
	ZVAL_UNDEF(&_89$$48);
	ZVAL_UNDEF(&_90$$49);
	ZVAL_UNDEF(&_91$$49);
	ZVAL_UNDEF(&_92$$49);
	ZVAL_UNDEF(&_93$$49);
	ZVAL_UNDEF(&_94$$51);
	ZVAL_UNDEF(&_95$$52);
	ZVAL_UNDEF(&_96$$52);
	ZVAL_UNDEF(&_97$$53);
	ZVAL_UNDEF(&_98$$54);
	ZVAL_UNDEF(&_99$$54);
	ZVAL_UNDEF(&_100$$55);
	ZVAL_UNDEF(&_101$$56);
	ZVAL_UNDEF(&_102$$56);
	ZVAL_UNDEF(&_103$$57);
	ZVAL_UNDEF(&_104$$57);
	ZVAL_UNDEF(&_105$$58);
	ZVAL_UNDEF(&_106$$59);
	ZVAL_UNDEF(&_107$$60);
	ZVAL_UNDEF(&_108$$65);
	ZVAL_UNDEF(&_109$$65);
	ZVAL_UNDEF(&_110$$66);
	ZVAL_UNDEF(&_111$$67);
	ZVAL_UNDEF(&_112$$68);
	ZVAL_UNDEF(&_113$$69);
	ZVAL_UNDEF(&_114$$70);
	ZVAL_UNDEF(&_115$$71);
	ZVAL_UNDEF(&_116$$71);
	ZVAL_UNDEF(&_117$$74);
	ZVAL_UNDEF(&_118$$75);
	ZVAL_UNDEF(&_119$$75);
	ZVAL_UNDEF(&_120$$76);
	ZVAL_UNDEF(&_121$$76);
	ZVAL_UNDEF(&_122$$78);
	ZVAL_UNDEF(&_123$$78);
	ZVAL_UNDEF(&_125$$78);
	ZVAL_UNDEF(&_126$$78);
	ZVAL_UNDEF(&_127$$78);
	ZVAL_UNDEF(&_128);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_71$$41);
	ZVAL_UNDEF(&_81$$44);
	ZVAL_UNDEF(&_124$$78);
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
	zephir_get_arrval(&statements, statements_param);
	if (!extendsMode_param) {
		extendsMode = 0;
	} else {
		}
	if (ZEPHIR_IS_EMPTY(&statements)) {
		RETURN_MM_STRING("");
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 932, PH_NOISY_CC | PH_READONLY);
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
	zephir_is_iterable(&statements, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3627);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&statements), _2)
		{
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _2);
			if (UNEXPECTED(Z_TYPE_P(&statement) != IS_ARRAY)) {
				ZEPHIR_INIT_NVAR(&_3$$6);
				object_init_ex(&_3$$6, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
				ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", &_4, 0);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_3$$6, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3356);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (UNEXPECTED(!(zephir_array_isset_value_string(&statement, SL("type"))))) {
				ZEPHIR_INIT_NVAR(&_5$$7);
				object_init_ex(&_5$$7, phalcon_mvc_view_engine_volt_exceptions_invalidstatement_ce);
				ZEPHIR_OBS_NVAR(&_6$$7);
				zephir_array_fetch_string(&_6$$7, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3363);
				zephir_cast_to_string(&_7$$7, &_6$$7);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_OBS_NVAR(&_8$$7);
				zephir_array_fetch_string(&_8$$7, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3363);
				ZVAL_LONG(&_9$$7, zephir_get_intval(&_8$$7));
				ZEPHIR_CALL_METHOD(NULL, &_5$$7, "__construct", &_10, 0, &_7$$7, &_9$$7, &statement);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_5$$7, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3363);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_11$$5, this_ptr, _zephir_prop_1, 924, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&extensions, &_11$$5);
			if (!(ZEPHIR_IS_EMPTY(&extensions))) {
				ZEPHIR_INIT_NVAR(&_12$$8);
				zephir_create_array(&_12$$8, 1, 0);
				zephir_array_fast_append(&_12$$8, &statement);
				ZEPHIR_INIT_NVAR(&_13$$8);
				ZVAL_STRING(&_13$$8, "compileStatement");
				ZEPHIR_CALL_METHOD(&tempCompilation, this_ptr, "fireExtensionEvent", &_14, 0, &_13$$8, &_12$$8);
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
			zephir_array_fetch_string(&type, &statement, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3392);
			if (ZEPHIR_IS_STRING_IDENTICAL(&type, "volt:php")) {
				ZEPHIR_OBS_NVAR(&_15$$10);
				zephir_array_fetch_string(&_15$$10, &statement, SL("code"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3399);
				zephir_concat_self(&compilation, &_15$$10);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				continue;
			}
			if (ZEPHIR_IS_LONG(&type, 426)) { goto zephir_switch_0_clause_0; }
			if (ZEPHIR_IS_LONG(&type, 314)) { goto zephir_switch_0_clause_1; }
			if (ZEPHIR_IS_LONG(&type, 357)) { goto zephir_switch_0_clause_2; }
			if (ZEPHIR_IS_LONG(&type, 300)) { goto zephir_switch_0_clause_3; }
			if (ZEPHIR_IS_LONG(&type, 302)) { goto zephir_switch_0_clause_4; }
			if (ZEPHIR_IS_LONG(&type, 411)) { goto zephir_switch_0_clause_5; }
			if (ZEPHIR_IS_LONG(&type, 412)) { goto zephir_switch_0_clause_6; }
			if (ZEPHIR_IS_LONG(&type, 413)) { goto zephir_switch_0_clause_7; }
			if (ZEPHIR_IS_LONG(&type, 304)) { goto zephir_switch_0_clause_8; }
			if (ZEPHIR_IS_LONG(&type, 306)) { goto zephir_switch_0_clause_9; }
			if (ZEPHIR_IS_LONG(&type, 359)) { goto zephir_switch_0_clause_10; }
			if (ZEPHIR_IS_LONG(&type, 307)) { goto zephir_switch_0_clause_11; }
			if (ZEPHIR_IS_LONG(&type, 310)) { goto zephir_switch_0_clause_12; }
			if (ZEPHIR_IS_LONG(&type, 313)) { goto zephir_switch_0_clause_13; }
			if (ZEPHIR_IS_LONG(&type, 316)) { goto zephir_switch_0_clause_14; }
			if (ZEPHIR_IS_LONG(&type, 327)) { goto zephir_switch_0_clause_15; }
			if (ZEPHIR_IS_LONG(&type, 317)) { goto zephir_switch_0_clause_16; }
			if (ZEPHIR_IS_LONG(&type, 319)) { goto zephir_switch_0_clause_17; }
			if (ZEPHIR_IS_LONG(&type, 320)) { goto zephir_switch_0_clause_18; }
			if (ZEPHIR_IS_LONG(&type, 321)) { goto zephir_switch_0_clause_19; }
			if (ZEPHIR_IS_LONG(&type, 322)) { goto zephir_switch_0_clause_20; }
			if (ZEPHIR_IS_LONG(&type, 325)) { goto zephir_switch_0_clause_21; }
			if (ZEPHIR_IS_LONG(&type, 358)) { goto zephir_switch_0_clause_22; }
			goto zephir_switch_0_clause_23;
			zephir_switch_0_clause_0: ;
				if (extendsMode) {
					ZVAL_BOOL(&_17$$11, 1);
				} else {
					ZVAL_BOOL(&_17$$11, 0);
				}
				ZEPHIR_CALL_METHOD(&_16$$11, this_ptr, "compileSetCapture", &_18, 0, &statement, &_17$$11);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_16$$11);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_1: ;
				ZEPHIR_INIT_NVAR(&_19$$12);
				object_init_ex(&_19$$12, phalcon_mvc_view_engine_volt_exception_ce);
				ZEPHIR_OBS_NVAR(&_20$$12);
				zephir_array_fetch_string(&_20$$12, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3420);
				ZEPHIR_OBS_NVAR(&_21$$12);
				zephir_array_fetch_string(&_21$$12, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3421);
				ZEPHIR_INIT_NVAR(&_22$$12);
				ZEPHIR_CONCAT_SVSV(&_22$$12, "{% cache %} was removed in Phalcon 4; use the view cache or a partial in ", &_20$$12, " on line ", &_21$$12);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_19$$12, "__construct", &_23, 0, &_22$$12);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_19$$12, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3421);
				ZEPHIR_MM_RESTORE();
				return;
			zephir_switch_0_clause_2: ;
				if (zephir_array_isset_value_string(&statement, SL("value"))) {
					ZEPHIR_OBS_NVAR(&_24$$14);
					zephir_array_fetch_string(&_24$$14, &statement, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3425);
					zephir_concat_self(&compilation, &_24$$14);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_3: ;
				if (extendsMode) {
					ZVAL_BOOL(&_26$$15, 1);
				} else {
					ZVAL_BOOL(&_26$$15, 0);
				}
				ZEPHIR_CALL_METHOD(&_25$$15, this_ptr, "compileIf", &_27, 0, &statement, &_26$$15);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_25$$15);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_4: ;
				ZEPHIR_CALL_METHOD(&_28$$16, this_ptr, "compileElseIf", &_29, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_28$$16);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_5: ;
				if (extendsMode) {
					ZVAL_BOOL(&_31$$17, 1);
				} else {
					ZVAL_BOOL(&_31$$17, 0);
				}
				ZEPHIR_CALL_METHOD(&_30$$17, this_ptr, "compileSwitch", &_32, 0, &statement, &_31$$17);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_30$$17);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_6: ;
				ZEPHIR_CALL_METHOD(&_33$$18, this_ptr, "compileCase", &_34, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_33$$18);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_7: ;
				ZVAL_BOOL(&_36$$19, 0);
				ZEPHIR_CALL_METHOD(&_35$$19, this_ptr, "compileCase", &_34, 0, &statement, &_36$$19);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_35$$19);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_8: ;
				if (extendsMode) {
					ZVAL_BOOL(&_38$$20, 1);
				} else {
					ZVAL_BOOL(&_38$$20, 0);
				}
				ZEPHIR_CALL_METHOD(&_37$$20, this_ptr, "compileForeach", &_39, 0, &statement, &_38$$20);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_37$$20);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_9: ;
				ZEPHIR_CALL_METHOD(&_40$$21, this_ptr, "compileSet", &_41, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_40$$21);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_10: ;
				ZEPHIR_CALL_METHOD(&_42$$22, this_ptr, "compileEcho", &_43, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_42$$22);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_11: ;
				ZEPHIR_OBS_NVAR(&blockName);
				zephir_array_fetch_string(&blockName, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3474);
				ZEPHIR_OBS_NVAR(&blockStatements);
				zephir_array_isset_string_fetch(&blockStatements, &statement, SL("block_statements"), 0);
				zephir_read_property_cached(&_44$$23, this_ptr, _zephir_prop_2, 933, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&blocks, &_44$$23);
				if (zephir_is_true(&blockMode)) {
					if (Z_TYPE_P(&blocks) != IS_ARRAY) {
						ZEPHIR_INIT_NVAR(&blocks);
						array_init(&blocks);
					}
					if (Z_TYPE_P(&compilation) != IS_NULL) {
						zephir_array_append(&blocks, &compilation, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3489);
						ZEPHIR_INIT_NVAR(&compilation);
						ZVAL_NULL(&compilation);
					}
					zephir_array_update_zval(&blocks, &blockName, &blockStatements, PH_COPY | PH_SEPARATE);
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 933, &blocks);
				} else {
					if (Z_TYPE_P(&blockStatements) == IS_ARRAY) {
						if (extendsMode) {
							ZVAL_BOOL(&_46$$28, 1);
						} else {
							ZVAL_BOOL(&_46$$28, 0);
						}
						ZEPHIR_CALL_METHOD(&_45$$28, this_ptr, "statementList", &_47, 0, &blockStatements, &_46$$28);
						zephir_check_call_status();
						zephir_concat_self(&compilation, &_45$$28);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_12: ;
				ZEPHIR_OBS_NVAR(&path);
				zephir_array_fetch_string(&path, &statement, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3514);
				ZEPHIR_OBS_NVAR(&_48$$29);
				zephir_array_fetch_string(&_48$$29, &path, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3518);
				ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", &_49, 0, &_48$$29);
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
					ZEPHIR_CALL_METHOD(&_50$$30, &subCompiler, "getCompiledTemplatePath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&tempCompilation, this_ptr, "phpFileGetContents", &_51, 0, &_50$$30);
					zephir_check_call_status();
				}
				if (1) {
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 932, &__$true);
				} else {
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 932, &__$false);
				}
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 926, &tempCompilation);
				ZEPHIR_CPY_WRT(&blockMode, &extended);
				goto zephir_switch_0_end;
			zephir_switch_0_clause_13: ;
				ZEPHIR_CALL_METHOD(&_52$$31, this_ptr, "compileInclude", &_53, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_52$$31);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_14: ;
				ZEPHIR_CALL_METHOD(&_54$$32, this_ptr, "compileDo", &_55, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_54$$32);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_15: ;
				ZEPHIR_CALL_METHOD(&_56$$33, this_ptr, "compileReturn", &_57, 0, &statement);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_56$$33);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_16: ;
				if (extendsMode) {
					ZVAL_BOOL(&_59$$34, 1);
				} else {
					ZVAL_BOOL(&_59$$34, 0);
				}
				ZEPHIR_CALL_METHOD(&_58$$34, this_ptr, "compileAutoEscape", &_60, 0, &statement, &_59$$34);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_58$$34);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_17: ;
				zephir_concat_self_str(&compilation, SL("<?php continue; ?>"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_18: ;
				zephir_concat_self_str(&compilation, SL("<?php break; ?>"));
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_19: ;
				ZEPHIR_CALL_METHOD(&_61$$37, this_ptr, "compileForElse", &_62, 0);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_61$$37);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_20: ;
				if (extendsMode) {
					ZVAL_BOOL(&_64$$38, 1);
				} else {
					ZVAL_BOOL(&_64$$38, 0);
				}
				ZEPHIR_CALL_METHOD(&_63$$38, this_ptr, "compileMacro", &_65, 0, &statement, &_64$$38);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_63$$38);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_21: ;
				if (extendsMode) {
					ZVAL_BOOL(&_67$$39, 1);
				} else {
					ZVAL_BOOL(&_67$$39, 0);
				}
				ZEPHIR_CALL_METHOD(&_66$$39, this_ptr, "compileCall", &_68, 0, &statement, &_67$$39);
				zephir_check_call_status();
				zephir_concat_self(&compilation, &_66$$39);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				goto zephir_switch_0_end;
			zephir_switch_0_clause_22: ;
				goto zephir_switch_0_end;
			zephir_switch_0_clause_23: ;
				ZEPHIR_INIT_NVAR(&_69$$41);
				object_init_ex(&_69$$41, phalcon_mvc_view_engine_volt_exceptions_unknownvoltstatement_ce);
				ZEPHIR_OBS_NVAR(&_70$$41);
				zephir_array_fetch_string(&_70$$41, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3619);
				zephir_cast_to_string(&_71$$41, &_70$$41);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_OBS_NVAR(&_72$$41);
				zephir_array_fetch_string(&_72$$41, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3619);
				ZVAL_LONG(&_73$$41, zephir_get_intval(&type));
				ZVAL_LONG(&_74$$41, zephir_get_intval(&_72$$41));
				ZEPHIR_CALL_METHOD(NULL, &_69$$41, "__construct", &_75, 0, &_73$$41, &_71$$41, &_74$$41);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_69$$41, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3619);
				ZEPHIR_MM_RESTORE();
				return;
			zephir_switch_0_end: ;

		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_77 = 1;
		while (1) {
			if (_77) {
				_77 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_76, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_76)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&statement) != IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(&_78$$43);
					object_init_ex(&_78$$43, phalcon_mvc_view_engine_volt_exceptions_corruptedstatement_ce);
					ZEPHIR_CALL_METHOD(NULL, &_78$$43, "__construct", &_4, 0);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_78$$43, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3356);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (UNEXPECTED(!(zephir_array_isset_value_string(&statement, SL("type"))))) {
					ZEPHIR_INIT_NVAR(&_79$$44);
					object_init_ex(&_79$$44, phalcon_mvc_view_engine_volt_exceptions_invalidstatement_ce);
					ZEPHIR_OBS_NVAR(&_80$$44);
					zephir_array_fetch_string(&_80$$44, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3363);
					zephir_cast_to_string(&_81$$44, &_80$$44);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&_82$$44);
					zephir_array_fetch_string(&_82$$44, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3363);
					ZVAL_LONG(&_83$$44, zephir_get_intval(&_82$$44));
					ZEPHIR_CALL_METHOD(NULL, &_79$$44, "__construct", &_10, 0, &_81$$44, &_83$$44, &statement);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_79$$44, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3363);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_read_property_cached(&_84$$42, this_ptr, _zephir_prop_1, 924, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&extensions, &_84$$42);
				if (!(ZEPHIR_IS_EMPTY(&extensions))) {
					ZEPHIR_INIT_NVAR(&_85$$45);
					zephir_create_array(&_85$$45, 1, 0);
					zephir_array_fast_append(&_85$$45, &statement);
					ZEPHIR_INIT_NVAR(&_86$$45);
					ZVAL_STRING(&_86$$45, "compileStatement");
					ZEPHIR_CALL_METHOD(&tempCompilation, this_ptr, "fireExtensionEvent", &_14, 0, &_86$$45, &_85$$45);
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
				zephir_array_fetch_string(&type, &statement, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3392);
				if (ZEPHIR_IS_STRING_IDENTICAL(&type, "volt:php")) {
					ZEPHIR_OBS_NVAR(&_87$$47);
					zephir_array_fetch_string(&_87$$47, &statement, SL("code"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3399);
					zephir_concat_self(&compilation, &_87$$47);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					continue;
				}
				if (ZEPHIR_IS_LONG(&type, 426)) { goto zephir_switch_1_clause_0; }
				if (ZEPHIR_IS_LONG(&type, 314)) { goto zephir_switch_1_clause_1; }
				if (ZEPHIR_IS_LONG(&type, 357)) { goto zephir_switch_1_clause_2; }
				if (ZEPHIR_IS_LONG(&type, 300)) { goto zephir_switch_1_clause_3; }
				if (ZEPHIR_IS_LONG(&type, 302)) { goto zephir_switch_1_clause_4; }
				if (ZEPHIR_IS_LONG(&type, 411)) { goto zephir_switch_1_clause_5; }
				if (ZEPHIR_IS_LONG(&type, 412)) { goto zephir_switch_1_clause_6; }
				if (ZEPHIR_IS_LONG(&type, 413)) { goto zephir_switch_1_clause_7; }
				if (ZEPHIR_IS_LONG(&type, 304)) { goto zephir_switch_1_clause_8; }
				if (ZEPHIR_IS_LONG(&type, 306)) { goto zephir_switch_1_clause_9; }
				if (ZEPHIR_IS_LONG(&type, 359)) { goto zephir_switch_1_clause_10; }
				if (ZEPHIR_IS_LONG(&type, 307)) { goto zephir_switch_1_clause_11; }
				if (ZEPHIR_IS_LONG(&type, 310)) { goto zephir_switch_1_clause_12; }
				if (ZEPHIR_IS_LONG(&type, 313)) { goto zephir_switch_1_clause_13; }
				if (ZEPHIR_IS_LONG(&type, 316)) { goto zephir_switch_1_clause_14; }
				if (ZEPHIR_IS_LONG(&type, 327)) { goto zephir_switch_1_clause_15; }
				if (ZEPHIR_IS_LONG(&type, 317)) { goto zephir_switch_1_clause_16; }
				if (ZEPHIR_IS_LONG(&type, 319)) { goto zephir_switch_1_clause_17; }
				if (ZEPHIR_IS_LONG(&type, 320)) { goto zephir_switch_1_clause_18; }
				if (ZEPHIR_IS_LONG(&type, 321)) { goto zephir_switch_1_clause_19; }
				if (ZEPHIR_IS_LONG(&type, 322)) { goto zephir_switch_1_clause_20; }
				if (ZEPHIR_IS_LONG(&type, 325)) { goto zephir_switch_1_clause_21; }
				if (ZEPHIR_IS_LONG(&type, 358)) { goto zephir_switch_1_clause_22; }
				goto zephir_switch_1_clause_23;
				zephir_switch_1_clause_0: ;
					if (extendsMode) {
						ZVAL_BOOL(&_89$$48, 1);
					} else {
						ZVAL_BOOL(&_89$$48, 0);
					}
					ZEPHIR_CALL_METHOD(&_88$$48, this_ptr, "compileSetCapture", &_18, 0, &statement, &_89$$48);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_88$$48);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_1: ;
					ZEPHIR_INIT_NVAR(&_90$$49);
					object_init_ex(&_90$$49, phalcon_mvc_view_engine_volt_exception_ce);
					ZEPHIR_OBS_NVAR(&_91$$49);
					zephir_array_fetch_string(&_91$$49, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3420);
					ZEPHIR_OBS_NVAR(&_92$$49);
					zephir_array_fetch_string(&_92$$49, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3421);
					ZEPHIR_INIT_NVAR(&_93$$49);
					ZEPHIR_CONCAT_SVSV(&_93$$49, "{% cache %} was removed in Phalcon 4; use the view cache or a partial in ", &_91$$49, " on line ", &_92$$49);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_90$$49, "__construct", &_23, 0, &_93$$49);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_90$$49, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3421);
					ZEPHIR_MM_RESTORE();
					return;
				zephir_switch_1_clause_2: ;
					if (zephir_array_isset_value_string(&statement, SL("value"))) {
						ZEPHIR_OBS_NVAR(&_94$$51);
						zephir_array_fetch_string(&_94$$51, &statement, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3425);
						zephir_concat_self(&compilation, &_94$$51);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_3: ;
					if (extendsMode) {
						ZVAL_BOOL(&_96$$52, 1);
					} else {
						ZVAL_BOOL(&_96$$52, 0);
					}
					ZEPHIR_CALL_METHOD(&_95$$52, this_ptr, "compileIf", &_27, 0, &statement, &_96$$52);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_95$$52);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_4: ;
					ZEPHIR_CALL_METHOD(&_97$$53, this_ptr, "compileElseIf", &_29, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_97$$53);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_5: ;
					if (extendsMode) {
						ZVAL_BOOL(&_99$$54, 1);
					} else {
						ZVAL_BOOL(&_99$$54, 0);
					}
					ZEPHIR_CALL_METHOD(&_98$$54, this_ptr, "compileSwitch", &_32, 0, &statement, &_99$$54);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_98$$54);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_6: ;
					ZEPHIR_CALL_METHOD(&_100$$55, this_ptr, "compileCase", &_34, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_100$$55);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_7: ;
					ZVAL_BOOL(&_102$$56, 0);
					ZEPHIR_CALL_METHOD(&_101$$56, this_ptr, "compileCase", &_34, 0, &statement, &_102$$56);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_101$$56);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_8: ;
					if (extendsMode) {
						ZVAL_BOOL(&_104$$57, 1);
					} else {
						ZVAL_BOOL(&_104$$57, 0);
					}
					ZEPHIR_CALL_METHOD(&_103$$57, this_ptr, "compileForeach", &_39, 0, &statement, &_104$$57);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_103$$57);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_9: ;
					ZEPHIR_CALL_METHOD(&_105$$58, this_ptr, "compileSet", &_41, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_105$$58);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_10: ;
					ZEPHIR_CALL_METHOD(&_106$$59, this_ptr, "compileEcho", &_43, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_106$$59);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_11: ;
					ZEPHIR_OBS_NVAR(&blockName);
					zephir_array_fetch_string(&blockName, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3474);
					ZEPHIR_OBS_NVAR(&blockStatements);
					zephir_array_isset_string_fetch(&blockStatements, &statement, SL("block_statements"), 0);
					zephir_read_property_cached(&_107$$60, this_ptr, _zephir_prop_2, 933, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CPY_WRT(&blocks, &_107$$60);
					if (zephir_is_true(&blockMode)) {
						if (Z_TYPE_P(&blocks) != IS_ARRAY) {
							ZEPHIR_INIT_NVAR(&blocks);
							array_init(&blocks);
						}
						if (Z_TYPE_P(&compilation) != IS_NULL) {
							zephir_array_append(&blocks, &compilation, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3489);
							ZEPHIR_INIT_NVAR(&compilation);
							ZVAL_NULL(&compilation);
						}
						zephir_array_update_zval(&blocks, &blockName, &blockStatements, PH_COPY | PH_SEPARATE);
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 933, &blocks);
					} else {
						if (Z_TYPE_P(&blockStatements) == IS_ARRAY) {
							if (extendsMode) {
								ZVAL_BOOL(&_109$$65, 1);
							} else {
								ZVAL_BOOL(&_109$$65, 0);
							}
							ZEPHIR_CALL_METHOD(&_108$$65, this_ptr, "statementList", &_47, 0, &blockStatements, &_109$$65);
							zephir_check_call_status();
							zephir_concat_self(&compilation, &_108$$65);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_12: ;
					ZEPHIR_OBS_NVAR(&path);
					zephir_array_fetch_string(&path, &statement, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3514);
					ZEPHIR_OBS_NVAR(&_110$$66);
					zephir_array_fetch_string(&_110$$66, &path, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3518);
					ZEPHIR_CALL_METHOD(&finalPath, this_ptr, "getFinalPath", &_49, 0, &_110$$66);
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
						ZEPHIR_CALL_METHOD(&_111$$67, &subCompiler, "getCompiledTemplatePath", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&tempCompilation, this_ptr, "phpFileGetContents", &_51, 0, &_111$$67);
						zephir_check_call_status();
					}
					if (1) {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 932, &__$true);
					} else {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 932, &__$false);
					}
					zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 926, &tempCompilation);
					ZEPHIR_CPY_WRT(&blockMode, &extended);
					goto zephir_switch_1_end;
				zephir_switch_1_clause_13: ;
					ZEPHIR_CALL_METHOD(&_112$$68, this_ptr, "compileInclude", &_53, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_112$$68);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_14: ;
					ZEPHIR_CALL_METHOD(&_113$$69, this_ptr, "compileDo", &_55, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_113$$69);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_15: ;
					ZEPHIR_CALL_METHOD(&_114$$70, this_ptr, "compileReturn", &_57, 0, &statement);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_114$$70);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_16: ;
					if (extendsMode) {
						ZVAL_BOOL(&_116$$71, 1);
					} else {
						ZVAL_BOOL(&_116$$71, 0);
					}
					ZEPHIR_CALL_METHOD(&_115$$71, this_ptr, "compileAutoEscape", &_60, 0, &statement, &_116$$71);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_115$$71);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_17: ;
					zephir_concat_self_str(&compilation, SL("<?php continue; ?>"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_18: ;
					zephir_concat_self_str(&compilation, SL("<?php break; ?>"));
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_19: ;
					ZEPHIR_CALL_METHOD(&_117$$74, this_ptr, "compileForElse", &_62, 0);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_117$$74);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_20: ;
					if (extendsMode) {
						ZVAL_BOOL(&_119$$75, 1);
					} else {
						ZVAL_BOOL(&_119$$75, 0);
					}
					ZEPHIR_CALL_METHOD(&_118$$75, this_ptr, "compileMacro", &_65, 0, &statement, &_119$$75);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_118$$75);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_21: ;
					if (extendsMode) {
						ZVAL_BOOL(&_121$$76, 1);
					} else {
						ZVAL_BOOL(&_121$$76, 0);
					}
					ZEPHIR_CALL_METHOD(&_120$$76, this_ptr, "compileCall", &_68, 0, &statement, &_121$$76);
					zephir_check_call_status();
					zephir_concat_self(&compilation, &_120$$76);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					goto zephir_switch_1_end;
				zephir_switch_1_clause_22: ;
					goto zephir_switch_1_end;
				zephir_switch_1_clause_23: ;
					ZEPHIR_INIT_NVAR(&_122$$78);
					object_init_ex(&_122$$78, phalcon_mvc_view_engine_volt_exceptions_unknownvoltstatement_ce);
					ZEPHIR_OBS_NVAR(&_123$$78);
					zephir_array_fetch_string(&_123$$78, &statement, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3619);
					zephir_cast_to_string(&_124$$78, &_123$$78);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_OBS_NVAR(&_125$$78);
					zephir_array_fetch_string(&_125$$78, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3619);
					ZVAL_LONG(&_126$$78, zephir_get_intval(&type));
					ZVAL_LONG(&_127$$78, zephir_get_intval(&_125$$78));
					ZEPHIR_CALL_METHOD(NULL, &_122$$78, "__construct", &_75, 0, &_126$$78, &_124$$78, &_127$$78);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_122$$78, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3619);
					ZEPHIR_MM_RESTORE();
					return;
				zephir_switch_1_end: ;

		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	if (ZEPHIR_IS_TRUE_IDENTICAL(&blockMode)) {
		zephir_read_property_cached(&level, this_ptr, _zephir_prop_4, 935, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_LONG(&level, 1)) {
			if (Z_TYPE_P(&compilation) != IS_NULL) {
				zephir_update_property_array_append(this_ptr, SL("blocks"), &compilation);
			}
		}
		RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("blockLevel")));
	}
	RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("level")));
	zephir_cast_to_string(&_128, &compilation);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&_128);
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
		zephir_is_iterable(_0$$4, 0, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3676);
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

/**
 * Checks whether a path is absolute (Unix root, Windows UNC or drive)
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, isAbsolutePath)
{
	zend_bool _0, _1, _6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval path_zv, _2, _3, _4, _5, _7, _8, _9;
	zend_string *path = NULL;

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	_0 = zephir_start_with_str(&path_zv, SL("/"));
	if (!(_0)) {
		_0 = zephir_start_with_str(&path_zv, SL("\\"));
	}
	if (_0) {
		RETURN_MM_BOOL(1);
	}
	_1 = zephir_fast_strlen_ev(&path_zv) >= 2;
	if (_1) {
		ZVAL_LONG(&_2, 0);
		ZVAL_LONG(&_3, 1);
		ZEPHIR_INIT_VAR(&_4);
		zephir_substr(&_4, &path_zv, 0 , 1 , 0);
		ZEPHIR_CALL_FUNCTION(&_5, "ctype_alpha", NULL, 0, &_4);
		zephir_check_call_status();
		_1 = zephir_is_true(&_5);
	}
	_6 = _1;
	if (_6) {
		ZVAL_LONG(&_7, 1);
		ZVAL_LONG(&_8, 1);
		ZEPHIR_INIT_VAR(&_9);
		zephir_substr(&_9, &path_zv, 1 , 1 , 0);
		_6 = ZEPHIR_IS_STRING_IDENTICAL(&_9, ":");
	}
	if (_6) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);
}

/**
 * @phpstan-param mvc_volt_node $expression
 */
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
				RETURN_MM_BOOL(ZEPHIR_IS_STRING_IDENTICAL(&leftValue, "tag"));
			} else {
				_0$$6 = zephir_array_isset_value_string(&left, SL("name"));
				if (_0$$6) {
					zephir_memory_observe(&_1$$6);
					zephir_array_fetch_string(&_1$$6, &left, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Compiler.zep", 3738);
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

/**
 * Closes an open file pointer
 *
 * @link https://php.net/manual/en/function.fclose.php
 *
 * @param resource $handle
 *
 * @return bool
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFclose)
{
	zval *handle, handle_sub;

	ZVAL_UNDEF(&handle_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle);
	RETURN_BOOL(zephir_fclose(handle));
}

/**
 * Gets line from file pointer and parse for CSV fields
 *
 * @param resource $stream
 * @param int      $length
 * @param string   $separator
 * @param string   $enclosure
 * @param string   $escape
 *
 * @return array<array-key, mixed>|false
 *
 * @link https://php.net/manual/en/function.fgetcsv.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFgetCsv)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_string *separator = NULL;
	zend_long length, ZEPHIR_LAST_CALL_STATUS;
	zval *stream, stream_sub, *length_param = NULL, separator_zv, *enclosure = NULL, enclosure_sub, *escape = NULL, escape_sub, __$null, _0;

	ZVAL_UNDEF(&stream_sub);
	ZVAL_UNDEF(&separator_zv);
	ZVAL_UNDEF(&enclosure_sub);
	ZVAL_UNDEF(&escape_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 5)
		Z_PARAM_ZVAL(stream)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(length)
		Z_PARAM_STR(separator)
		Z_PARAM_ZVAL_OR_NULL(enclosure)
		Z_PARAM_ZVAL_OR_NULL(escape)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	stream = ZEND_CALL_ARG(execute_data, 1);
	if (ZEND_NUM_ARGS() > 1) {
		length_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 3) {
		enclosure = ZEND_CALL_ARG(execute_data, 4);
	}
	if (ZEND_NUM_ARGS() > 4) {
		escape = ZEND_CALL_ARG(execute_data, 5);
	}
	if (!length_param) {
		length = 0;
	} else {
		}
	if (!separator) {
		separator = zend_string_init(ZEND_STRL(","), 0);
		zephir_memory_observe(&separator_zv);
		ZVAL_STR(&separator_zv, separator);
	} else {
		zephir_memory_observe(&separator_zv);
	ZVAL_STR_COPY(&separator_zv, separator);
	}
	if (!enclosure) {
		enclosure = &enclosure_sub;
		ZEPHIR_CPY_WRT(enclosure, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(enclosure);
	}
	if (!escape) {
		escape = &escape_sub;
		ZEPHIR_CPY_WRT(escape, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(escape);
	}
	if (Z_TYPE_P(enclosure) == IS_NULL) {
		ZEPHIR_INIT_NVAR(enclosure);
		ZVAL_STRING(enclosure, "\"");
	}
	if (Z_TYPE_P(escape) == IS_NULL) {
		ZEPHIR_INIT_NVAR(escape);
		ZVAL_STRING(escape, "\\");
	}
	ZVAL_LONG(&_0, length);
	ZEPHIR_RETURN_CALL_FUNCTION("fgetcsv", NULL, 0, stream, &_0, &separator_zv, enclosure, escape);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param string $filename
 *
 * @return bool
 *
 * @link https://php.net/manual/en/function.file-exists.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFileExists)
{
	zval filename_zv;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(filename)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&filename_zv, filename);
	RETURN_BOOL((zephir_file_exists(&filename_zv) == SUCCESS));
}

/**
 * @param string        $filename
 * @param bool          $useIncludePath
 * @param resource|null $context
 * @param int           $offset
 * @param int|null      $length
 *
 * @return false|string
 *
 * @link https://php.net/manual/en/function.file-get-contents.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFileGetContents)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long offset, length, ZEPHIR_LAST_CALL_STATUS;
	zend_bool useIncludePath;
	zval filename_zv, *useIncludePath_param = NULL, *context = NULL, context_sub, *offset_param = NULL, *length_param = NULL, __$null, _0$$3, _1$$3, _2, _3, _4;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZVAL_UNDEF(&context_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 5)
		Z_PARAM_STR(filename)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(useIncludePath)
		Z_PARAM_ZVAL_OR_NULL(context)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG_OR_NULL(length, is_null_true)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		useIncludePath_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		context = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		offset_param = ZEND_CALL_ARG(execute_data, 4);
	}
	if (ZEND_NUM_ARGS() > 4) {
		length_param = ZEND_CALL_ARG(execute_data, 5);
	}
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	if (!useIncludePath_param) {
		useIncludePath = 0;
	} else {
		}
	if (!context) {
		context = &context_sub;
		context = &__$null;
	}
	if (!offset_param) {
		offset = 0;
	} else {
		}
	if (!length_param) {
		length = 0;
	} else {
		}
	if (0 == length) {
		ZVAL_BOOL(&_0$$3, (useIncludePath ? 1 : 0));
		ZVAL_LONG(&_1$$3, offset);
		ZEPHIR_RETURN_CALL_FUNCTION("file_get_contents", NULL, 0, &filename_zv, &_0$$3, context, &_1$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZVAL_BOOL(&_2, (useIncludePath ? 1 : 0));
	ZVAL_LONG(&_3, offset);
	ZVAL_LONG(&_4, length);
	ZEPHIR_RETURN_CALL_FUNCTION("file_get_contents", NULL, 0, &filename_zv, &_2, context, &_3, &_4);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param string   $filename
 * @param mixed    $data
 * @param int      $flags
 * @param resource $context
 *
 * @return false|int
 *
 * @link https://php.net/manual/en/function.file-put-contents.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFilePutContents)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long flags, ZEPHIR_LAST_CALL_STATUS;
	zval filename_zv, *data, data_sub, *flags_param = NULL, *context = NULL, context_sub, __$null, _0;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&context_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(filename)
		Z_PARAM_ZVAL(data)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(flags)
		Z_PARAM_ZVAL_OR_NULL(context)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	data = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		flags_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		context = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	if (!flags_param) {
		flags = 0;
	} else {
		}
	if (!context) {
		context = &context_sub;
		context = &__$null;
	}
	ZVAL_LONG(&_0, flags);
	ZEPHIR_RETURN_CALL_FUNCTION("file_put_contents", NULL, 145, &filename_zv, data, &_0, context);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param string        $filename
 * @param string        $mode
 * @param bool          $useIncludePath
 * @param resource|null $context
 *
 * @return resource|false
 *
 * @link https://php.net/manual/en/function.fopen.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFopen)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool useIncludePath;
	zval filename_zv, mode_zv, *useIncludePath_param = NULL, *context = NULL, context_sub, __$null, _0;
	zend_string *filename = NULL, *mode = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZVAL_UNDEF(&mode_zv);
	ZVAL_UNDEF(&context_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(filename)
		Z_PARAM_STR(mode)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(useIncludePath)
		Z_PARAM_ZVAL_OR_NULL(context)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		useIncludePath_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		context = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	zephir_memory_observe(&mode_zv);
	ZVAL_STR_COPY(&mode_zv, mode);
	if (!useIncludePath_param) {
		useIncludePath = 0;
	} else {
		}
	if (!context) {
		context = &context_sub;
		context = &__$null;
	}
	ZVAL_BOOL(&_0, (useIncludePath ? 1 : 0));
	ZEPHIR_RETURN_CALL_FUNCTION("fopen", NULL, 146, &filename_zv, &mode_zv, &_0, context);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Binary-safe file write
 *
 * @link https://php.net/manual/en/function.fwrite.php
 *
 * @param resource $handle
 * @param string   $data
 * @param int|null $length
 *
 * @return false|int
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpFwrite)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long length, ZEPHIR_LAST_CALL_STATUS;
	zend_string *data = NULL;
	zval *handle, handle_sub, data_zv, *length_param = NULL, _0;

	ZVAL_UNDEF(&handle_sub);
	ZVAL_UNDEF(&data_zv);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_ZVAL(handle)
		Z_PARAM_STR(data)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(length, is_null_true)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handle = ZEND_CALL_ARG(execute_data, 1);
	if (ZEND_NUM_ARGS() > 2) {
		length_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&data_zv);
	ZVAL_STR_COPY(&data_zv, data);
	if (!length_param) {
		length = 0;
	} else {
		}
	if (0 == length) {
		zephir_fwrite(return_value, handle, &data_zv);
		RETURN_MM();
	}
	ZVAL_LONG(&_0, length);
	ZEPHIR_RETURN_CALL_FUNCTION("fwrite", NULL, 0, handle, &data_zv, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Tells whether the filename is a directory
 *
 * @param string $filename
 *
 * @return bool
 *
 * @link https://php.net/manual/en/function.is-dir.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpIsDir)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval filename_zv;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(filename)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	ZEPHIR_RETURN_CALL_FUNCTION("is_dir", NULL, 143, &filename_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Tells whether the filename is writable
 *
 * @param string $filename
 *
 * @return bool
 *
 * @link https://php.net/manual/en/function.is-writable.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpIsWritable)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval filename_zv;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(filename)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	ZEPHIR_RETURN_CALL_FUNCTION("is_writable", NULL, 0, &filename_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Makes a directory
 *
 * @param string        $directory
 * @param int           $permissions
 * @param bool          $recursive
 * @param resource|null $context
 *
 * @return bool
 *
 * @link https://php.net/manual/en/function.mkdir.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpMkdir)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool recursive;
	zend_long permissions, ZEPHIR_LAST_CALL_STATUS;
	zval directory_zv, *permissions_param = NULL, *recursive_param = NULL, *context = NULL, context_sub, __$null, _0, _1;
	zend_string *directory = NULL;

	ZVAL_UNDEF(&directory_zv);
	ZVAL_UNDEF(&context_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STR(directory)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(permissions)
		Z_PARAM_BOOL(recursive)
		Z_PARAM_ZVAL_OR_NULL(context)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		permissions_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		recursive_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		context = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&directory_zv);
	ZVAL_STR_COPY(&directory_zv, directory);
	if (!permissions_param) {
		permissions = 0777;
	} else {
		}
	if (!recursive_param) {
		recursive = 0;
	} else {
		}
	if (!context) {
		context = &context_sub;
		context = &__$null;
	}
	ZVAL_LONG(&_0, permissions);
	ZVAL_BOOL(&_1, (recursive ? 1 : 0));
	ZEPHIR_RETURN_CALL_FUNCTION("mkdir", NULL, 144, &directory_zv, &_0, &_1, context);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param string        $filename
 * @param resource|null $context
 *
 * @return bool
 *
 * @link https://php.net/manual/en/function.unlink.php
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Compiler, phpUnlink)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval filename_zv, *context = NULL, context_sub, __$null;
	zend_string *filename = NULL;

	ZVAL_UNDEF(&filename_zv);
	ZVAL_UNDEF(&context_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(filename)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(context)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		context = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&filename_zv);
	ZVAL_STR_COPY(&filename_zv, filename);
	if (!context) {
		context = &context_sub;
		context = &__$null;
	}
	ZEPHIR_RETURN_CALL_FUNCTION("unlink", NULL, 131, &filename_zv, context);
	zephir_check_call_status();
	RETURN_MM();
}

