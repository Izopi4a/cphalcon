
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
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/main.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/variables.h"
#include "kernel/string.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Template inheritance resolved on the AST, before anything is compiled.
 *
 * The chain leaf -> ... -> root is loaded as ASTs, the blocks of every level
 * are collected by name (at any depth: inside blocks, if, for, switch), and the
 * root's statements are expanded: each {% block %} node becomes the statements
 * of its most derived definition, recursively, and {{ super() }} becomes the
 * next definition up the chain. {{ block("name") }} renders a block again and
 * {% embed %} resolves its body as an anonymous child of the embedded template.
 *
 * The result is one flat statement list without extends, block or embed nodes,
 * which Compiler::statementList() compiles as before: one PHP file per rendered
 * template and no block dispatch at run time.
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Resolver)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt, Resolver, phalcon, mvc_view_engine_volt_resolver, phalcon_mvc_view_engine_volt_resolver_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_resolver_ce, SL("collected"), ZEND_ACC_PROTECTED);
	/**
	 * @var Compiler
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_resolver_ce, SL("compiler"), ZEND_ACC_PROTECTED);
	/**
	 * Blocks being expanded, "name@level" => true (cycle guard)
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_resolver_ce, SL("expanding"), ZEND_ACC_PROTECTED);
	/**
	 * Leaf first, root last: [["path" => string, "blocks" => [name => node]]]
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_engine_volt_resolver_ce, SL("levels"), ZEND_ACC_PROTECTED);
	phalcon_mvc_view_engine_volt_resolver_ce->create_object = zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Resolver;
	/**
	 * Node type of raw PHP emitted by the resolver (scope wrappers, dynamic
	 * extends). Compiler::statementList() outputs its "code" as it is.
	 */
	zephir_declare_class_constant_string(phalcon_mvc_view_engine_volt_resolver_ce, SL("PHP_NODE"), "volt:php");

	return SUCCESS;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, __construct)
{
	zval *compiler, compiler_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&compiler_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("compiler", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(compiler, phalcon_mvc_view_engine_volt_compiler_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &compiler);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 937, compiler);
}

/**
 * A node holding raw PHP for the compiled output
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, php)
{
	zval code_zv;
	zend_string *code = NULL;

	ZVAL_UNDEF(&code_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(code)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&code_zv, code);
	zephir_create_array(return_value, 4, 0);
	add_assoc_stringl_ex(return_value, SL("type"), SL("volt:php"));
	zephir_array_update_string(return_value, SL("code"), &code_zv, PH_COPY | PH_SEPARATE);
	add_assoc_stringl_ex(return_value, SL("file"), SL(""));
	add_assoc_long_ex(return_value, SL("line"), 0);
	return;
}

/**
 * Statements with no extends, block or embed nodes
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, resolve)
{
	zend_bool _0, _5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL;
	zval *ast_param = NULL, path_zv, extendsNode, override, _1, _2, _6, _3$$3, _4$$3;
	zval ast;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ast);
	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&extendsNode);
	ZVAL_UNDEF(&override);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("compiler", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(ast, ast_param)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	ast_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&ast, ast_param);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_CALL_METHOD(&extendsNode, this_ptr, "findExtends", NULL, 0, &ast);
	zephir_check_call_status();
	_0 = Z_TYPE_P(&extendsNode) != IS_NULL;
	if (_0) {
		zephir_memory_observe(&_2);
		zephir_array_fetch_string(&_2, &extendsNode, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 86);
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "isLiteral", NULL, 0, &_2);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 937, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&override, &_3$$3, "takeExtendsOverride", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&override) == IS_NULL) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dynamicExtends", NULL, 0, &extendsNode, &path_zv);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "withExtendsPath", NULL, 0, &ast, &override);
		zephir_check_call_status();
		if (UNEXPECTED(Z_TYPE_P(&_4$$3) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&_4$$3, "ast", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&ast, &_4$$3);
	}
	_5 = Z_TYPE_P(&extendsNode) == IS_NULL;
	if (_5) {
		ZEPHIR_CALL_METHOD(&_6, this_ptr, "hasInheritanceNodes", NULL, 0, &ast);
		zephir_check_call_status();
		_5 = !zephir_is_true(&_6);
	}
	if (_5) {
		RETURN_CTOR(&ast);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "resolveChain", NULL, 0, &ast, &path_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Loads the chain from ast up to the root and expands the root
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, resolveChain)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_4 = NULL, *_6 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL;
	zval *ast_param = NULL, path_zv, __$true, current, currentPath, extendsNode, parentPath, _0, _16, _2$$3, _5$$3, _10$$3, _11$$3, _12$$3, _15$$3, _7$$5, _8$$5, _13$$6, _14$$6;
	zval ast, seen, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ast);
	ZVAL_UNDEF(&seen);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&path_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&current);
	ZVAL_UNDEF(&currentPath);
	ZVAL_UNDEF(&extendsNode);
	ZVAL_UNDEF(&parentPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("levels", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("compiler", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(ast, ast_param)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	ast_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&ast, ast_param);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 938, &_0);
	ZEPHIR_INIT_VAR(&seen);
	array_init(&seen);
	ZEPHIR_CPY_WRT(&current, &ast);
	ZEPHIR_CPY_WRT(&currentPath, &path_zv);
	zephir_array_update_zval(&seen, &path_zv, &__$true, PH_COPY | PH_SEPARATE);
	while (1) {
		ZEPHIR_INIT_NVAR(&_1$$3);
		zephir_create_array(&_1$$3, 2, 0);
		zephir_array_update_string(&_1$$3, SL("path"), &currentPath, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "collectBlocks", &_3, 0, &current, &currentPath);
		zephir_check_call_status();
		zephir_array_update_string(&_1$$3, SL("blocks"), &_2$$3, PH_COPY | PH_SEPARATE);
		zephir_update_property_array_append(this_ptr, SL("levels"), &_1$$3);
		ZEPHIR_CALL_METHOD(&extendsNode, this_ptr, "findExtends", &_4, 0, &current);
		zephir_check_call_status();
		if (Z_TYPE_P(&extendsNode) == IS_NULL) {
			break;
		}
		ZEPHIR_OBS_NVAR(&_5$$3);
		zephir_array_fetch_string(&_5$$3, &extendsNode, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 133);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "isLiteral", &_6, 0, &_5$$3);
		zephir_check_call_status();
		if (UNEXPECTED(!zephir_is_true(&_2$$3))) {
			ZEPHIR_INIT_NVAR(&_8$$5);
			ZVAL_STRING(&_8$$5, "Only the rendered template may extend a variable");
			ZEPHIR_CALL_METHOD(&_7$$5, this_ptr, "error", &_9, 0, &_8$$5, &extendsNode);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_7$$5, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 134);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_10$$3, this_ptr, _zephir_prop_1, 937, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_NVAR(&_11$$3);
		zephir_array_fetch_string(&_11$$3, &extendsNode, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 137);
		ZEPHIR_OBS_NVAR(&_12$$3);
		zephir_array_fetch_string(&_12$$3, &_11$$3, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 137);
		ZEPHIR_CALL_METHOD(&parentPath, &_10$$3, "resolveTemplatePath", NULL, 0, &_12$$3, &currentPath);
		zephir_check_call_status();
		if (UNEXPECTED(zephir_array_isset_value(&seen, &parentPath))) {
			ZEPHIR_INIT_NVAR(&_14$$6);
			ZEPHIR_CONCAT_SV(&_14$$6, "Circular inheritance: ", &parentPath);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_13$$6, this_ptr, "error", &_9, 0, &_14$$6, &extendsNode);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_13$$6, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 140);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_update_zval(&seen, &parentPath, &__$true, PH_COPY | PH_SEPARATE);
		zephir_read_property_cached(&_15$$3, this_ptr, _zephir_prop_1, 937, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&current, &_15$$3, "parseFile", NULL, 0, &parentPath);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&currentPath, &parentPath);
	}
	ZVAL_NULL(&_16);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "expand", NULL, 0, &current, &_16);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * All blocks of one template, at any depth, except those inside an embed
 * body: those belong to the embedded template
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, collectBlocks)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL;
	zval *statements_param = NULL, path_zv, _0;
	zval statements;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("collected", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	statements_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&statements, statements_param);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 939, &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "collectInto", NULL, 0, &statements, &path_zv);
	zephir_check_call_status();
	RETURN_MM_MEMBER_TYPED(getThis(), "collected", IS_ARRAY);
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, collectInto)
{
	zend_bool _15, _1$$3, _16$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_9 = NULL, *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL;
	zval *statements_param = NULL, path_zv, statement, type, name, existing, key, children, *_0, _14, _11$$3, *_12$$3, _2$$6, _3$$7, _4$$7, _5$$7, _6$$7, _7$$7, _24$$11, *_25$$11, _17$$14, _18$$15, _19$$15, _20$$15, _21$$15, _22$$15;
	zval statements, _10$$3, _23$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_23$$11);
	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&existing);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&children);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_24$$11);
	ZVAL_UNDEF(&_17$$14);
	ZVAL_UNDEF(&_18$$15);
	ZVAL_UNDEF(&_19$$15);
	ZVAL_UNDEF(&_20$$15);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_22$$15);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("collected", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	statements_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&statements, statements_param);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	zephir_is_iterable(&statements, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 205);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&statements), _0)
		{
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _0);
			_1$$3 = Z_TYPE_P(&statement) != IS_ARRAY;
			if (!(_1$$3)) {
				ZEPHIR_OBS_NVAR(&type);
				_1$$3 = !(zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0));
			}
			if (_1$$3) {
				continue;
			}
			if (ZEPHIR_IS_LONG(&type, 423)) {
				continue;
			}
			if (ZEPHIR_IS_LONG(&type, 307)) {
				ZEPHIR_OBS_NVAR(&name);
				zephir_array_fetch_string(&name, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 179);
				ZEPHIR_OBS_NVAR(&existing);
				zephir_read_property_cached(&_2$$6, this_ptr, _zephir_prop_0, 939, PH_NOISY_CC | PH_READONLY);
				if (UNEXPECTED(zephir_array_isset_fetch(&existing, &_2$$6, &name, 0))) {
					ZEPHIR_OBS_NVAR(&_4$$7);
					zephir_array_fetch_string(&_4$$7, &existing, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 187);
					ZEPHIR_OBS_NVAR(&_5$$7);
					zephir_array_fetch_string(&_5$$7, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 189);
					ZEPHIR_INIT_NVAR(&_6$$7);
					ZVAL_STRING(&_6$$7, "Block '%s' is defined twice in %s (lines %d and %d)");
					ZEPHIR_CALL_FUNCTION(&_7$$7, "sprintf", &_8, 76, &_6$$7, &name, &path_zv, &_4$$7, &_5$$7);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_3$$7, this_ptr, "error", &_9, 0, &_7$$7, &statement);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_3$$7, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 191);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_update_property_array(this_ptr, SL("collected"), &name, &statement);
			}
			ZEPHIR_INIT_NVAR(&_10$$3);
			zephir_create_array(&_10$$3, 5, 0);
			ZEPHIR_INIT_NVAR(&_11$$3);
			ZVAL_STRING(&_11$$3, "block_statements");
			zephir_array_fast_append(&_10$$3, &_11$$3);
			ZEPHIR_INIT_NVAR(&_11$$3);
			ZVAL_STRING(&_11$$3, "true_statements");
			zephir_array_fast_append(&_10$$3, &_11$$3);
			ZEPHIR_INIT_NVAR(&_11$$3);
			ZVAL_STRING(&_11$$3, "false_statements");
			zephir_array_fast_append(&_10$$3, &_11$$3);
			ZEPHIR_INIT_NVAR(&_11$$3);
			ZVAL_STRING(&_11$$3, "case_clauses");
			zephir_array_fast_append(&_10$$3, &_11$$3);
			ZEPHIR_INIT_NVAR(&_11$$3);
			ZVAL_STRING(&_11$$3, "caller");
			zephir_array_fast_append(&_10$$3, &_11$$3);
			zephir_is_iterable(&_10$$3, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 204);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_10$$3), _12$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				ZVAL_COPY(&key, _12$$3);
				ZEPHIR_OBS_NVAR(&children);
				if (zephir_array_isset_fetch(&children, &statement, &key, 0)) {
					if (Z_TYPE_P(&children) == IS_ARRAY) {
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "collectInto", &_13, 0, &children, &path_zv);
						zephir_check_call_status();
					}
				}
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&key);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_15 = 1;
		while (1) {
			if (_15) {
				_15 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_14, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_14)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				_16$$11 = Z_TYPE_P(&statement) != IS_ARRAY;
				if (!(_16$$11)) {
					ZEPHIR_OBS_NVAR(&type);
					_16$$11 = !(zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0));
				}
				if (_16$$11) {
					continue;
				}
				if (ZEPHIR_IS_LONG(&type, 423)) {
					continue;
				}
				if (ZEPHIR_IS_LONG(&type, 307)) {
					ZEPHIR_OBS_NVAR(&name);
					zephir_array_fetch_string(&name, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 179);
					ZEPHIR_OBS_NVAR(&existing);
					zephir_read_property_cached(&_17$$14, this_ptr, _zephir_prop_0, 939, PH_NOISY_CC | PH_READONLY);
					if (UNEXPECTED(zephir_array_isset_fetch(&existing, &_17$$14, &name, 0))) {
						ZEPHIR_OBS_NVAR(&_19$$15);
						zephir_array_fetch_string(&_19$$15, &existing, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 187);
						ZEPHIR_OBS_NVAR(&_20$$15);
						zephir_array_fetch_string(&_20$$15, &statement, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 189);
						ZEPHIR_INIT_NVAR(&_21$$15);
						ZVAL_STRING(&_21$$15, "Block '%s' is defined twice in %s (lines %d and %d)");
						ZEPHIR_CALL_FUNCTION(&_22$$15, "sprintf", &_8, 76, &_21$$15, &name, &path_zv, &_19$$15, &_20$$15);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_18$$15, this_ptr, "error", &_9, 0, &_22$$15, &statement);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_18$$15, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 191);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_update_property_array(this_ptr, SL("collected"), &name, &statement);
				}
				ZEPHIR_INIT_NVAR(&_23$$11);
				zephir_create_array(&_23$$11, 5, 0);
				ZEPHIR_INIT_NVAR(&_24$$11);
				ZVAL_STRING(&_24$$11, "block_statements");
				zephir_array_fast_append(&_23$$11, &_24$$11);
				ZEPHIR_INIT_NVAR(&_24$$11);
				ZVAL_STRING(&_24$$11, "true_statements");
				zephir_array_fast_append(&_23$$11, &_24$$11);
				ZEPHIR_INIT_NVAR(&_24$$11);
				ZVAL_STRING(&_24$$11, "false_statements");
				zephir_array_fast_append(&_23$$11, &_24$$11);
				ZEPHIR_INIT_NVAR(&_24$$11);
				ZVAL_STRING(&_24$$11, "case_clauses");
				zephir_array_fast_append(&_23$$11, &_24$$11);
				ZEPHIR_INIT_NVAR(&_24$$11);
				ZVAL_STRING(&_24$$11, "caller");
				zephir_array_fast_append(&_23$$11, &_24$$11);
				zephir_is_iterable(&_23$$11, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 204);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_23$$11), _25$$11)
				{
					ZEPHIR_INIT_NVAR(&key);
					ZVAL_COPY(&key, _25$$11);
					ZEPHIR_OBS_NVAR(&children);
					if (zephir_array_isset_fetch(&children, &statement, &key, 0)) {
						if (Z_TYPE_P(&children) == IS_ARRAY) {
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "collectInto", &_13, 0, &children, &path_zv);
							zephir_check_call_status();
						}
					}
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&key);
		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	ZEPHIR_MM_RESTORE();
}

/**
 * {% extends layoutVar %}: the parent is only known at render time. The
 * template compiles to a call that compiles (once per parent) and runs the
 * child against that parent.
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, dynamicExtends)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL;
	zval *extendsNode_param = NULL, path_zv, _0, _1, _2, _3, _4, _5;
	zval extendsNode;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extendsNode);
	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("compiler", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(extendsNode, extendsNode_param)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	extendsNode_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&extendsNode, extendsNode_param);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	zephir_create_array(return_value, 1, 0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 937, PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_string(&_3, &extendsNode, SL("path"), PH_NOISY | PH_READONLY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 217);
	ZEPHIR_CALL_METHOD(&_2, &_1, "expression", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_INIT_NVAR(&_4);
	zephir_var_export_ex(&_4, &path_zv);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SVSVS(&_5, "<?php $this->renderDynamicExtends(", &_2, ", ", &_4, ", get_defined_vars()); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_SELF(&_0, "php", NULL, 0, &_5);
	zephir_check_call_status();
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, error)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval node;
	zval message_zv, *node_param = NULL, file, line, _0, _1;
	zend_string *message = NULL;

	ZVAL_UNDEF(&message_zv);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&line);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&node);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(message)
		ZEPHIR_Z_PARAM_ARRAY(node, node_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	node_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&message_zv);
	ZVAL_STR_COPY(&message_zv, message);
	zephir_get_arrval(&node, node_param);
	zephir_memory_observe(&file);
	if (!(zephir_array_isset_string_fetch(&file, &node, SL("file"), 0))) {
		ZEPHIR_INIT_NVAR(&file);
		ZVAL_STRING(&file, "?");
	}
	zephir_memory_observe(&line);
	if (!(zephir_array_isset_string_fetch(&line, &node, SL("line"), 0))) {
		ZEPHIR_INIT_NVAR(&line);
		ZVAL_LONG(&line, 0);
	}
	object_init_ex(return_value, phalcon_mvc_view_engine_volt_exception_ce);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "%s in %s on line %d");
	ZEPHIR_CALL_FUNCTION(&_1, "sprintf", NULL, 76, &_0, &message_zv, &file, &line);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expand)
{
	zend_bool _42, _1$$3, _17$$3, _9$$6, _16$$9, _27$$13, _35$$16, _43$$22, _57$$22, _50$$25, _56$$28, _65$$32, _72$$35;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_11 = NULL, *_20 = NULL, *_22 = NULL, *_30 = NULL, *_40 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statements_param = NULL, *context, context_sub, statement, type, key, children, item, expr, *_0, _41, _37$$3, *_38$$3, _2$$6, _3$$6, *_5$$6, _6$$6, *_7$$6, _8$$6, _10$$9, *_12$$9, _13$$9, *_14$$9, _15$$9, _18$$12, _19$$12, _28$$12, _21$$13, *_23$$13, _24$$13, *_25$$13, _26$$13, _29$$16, *_31$$16, _32$$16, *_33$$16, _34$$16, _39$$21, _74$$22, *_75$$22, _44$$25, _45$$25, *_46$$25, _47$$25, *_48$$25, _49$$25, _51$$28, *_52$$28, _53$$28, *_54$$28, _55$$28, _58$$31, _59$$31, _66$$31, _60$$32, *_61$$32, _62$$32, *_63$$32, _64$$32, _67$$35, *_68$$35, _69$$35, *_70$$35, _71$$35, _76$$40;
	zval statements, out, _36$$3, _73$$22;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&out);
	ZVAL_UNDEF(&_36$$3);
	ZVAL_UNDEF(&_73$$22);
	ZVAL_UNDEF(&context_sub);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&children);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_37$$3);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_28$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_24$$13);
	ZVAL_UNDEF(&_26$$13);
	ZVAL_UNDEF(&_29$$16);
	ZVAL_UNDEF(&_32$$16);
	ZVAL_UNDEF(&_34$$16);
	ZVAL_UNDEF(&_39$$21);
	ZVAL_UNDEF(&_74$$22);
	ZVAL_UNDEF(&_44$$25);
	ZVAL_UNDEF(&_45$$25);
	ZVAL_UNDEF(&_47$$25);
	ZVAL_UNDEF(&_49$$25);
	ZVAL_UNDEF(&_51$$28);
	ZVAL_UNDEF(&_53$$28);
	ZVAL_UNDEF(&_55$$28);
	ZVAL_UNDEF(&_58$$31);
	ZVAL_UNDEF(&_59$$31);
	ZVAL_UNDEF(&_66$$31);
	ZVAL_UNDEF(&_60$$32);
	ZVAL_UNDEF(&_62$$32);
	ZVAL_UNDEF(&_64$$32);
	ZVAL_UNDEF(&_67$$35);
	ZVAL_UNDEF(&_69$$35);
	ZVAL_UNDEF(&_71$$35);
	ZVAL_UNDEF(&_76$$40);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
		Z_PARAM_ZVAL(context)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &statements_param, &context);
	zephir_get_arrval(&statements, statements_param);
	ZEPHIR_INIT_VAR(&out);
	array_init(&out);
	zephir_is_iterable(&statements, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 300);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&statements), _0)
		{
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _0);
			_1$$3 = Z_TYPE_P(&statement) != IS_ARRAY;
			if (!(_1$$3)) {
				ZEPHIR_OBS_NVAR(&type);
				_1$$3 = !(zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0));
			}
			if (_1$$3) {
				zephir_array_append(&out, &statement, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 247);
				continue;
			}
			if (ZEPHIR_IS_LONG(&type, 310)) {
				continue;
			}
			if (ZEPHIR_IS_LONG(&type, 307)) {
				ZEPHIR_OBS_NVAR(&_3$$6);
				zephir_array_fetch_string(&_3$$6, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 256);
				ZEPHIR_CALL_METHOD(&_2$$6, this_ptr, "expandBlock", &_4, 0, &_3$$6, &statement);
				zephir_check_call_status();
				if (Z_TYPE_P(&_2$$6) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_6$$6);
					zephir_string_to_char_array(&_6$$6, &_2$$6);
					_5$$6 = &_6$$6;
				} else {
					_5$$6 = &_2$$6;
				}
				zephir_is_iterable(_5$$6, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 260);
				if (Z_TYPE_P(_5$$6) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5$$6), _7$$6)
					{
						ZEPHIR_INIT_NVAR(&item);
						ZVAL_COPY(&item, _7$$6);
						zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 257);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _5$$6, "rewind", NULL, 0);
					zephir_check_call_status();
					_9$$6 = 1;
					while (1) {
						if (_9$$6) {
							_9$$6 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _5$$6, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_8$$6, _5$$6, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_8$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&item, _5$$6, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 257);
					}
				}
				ZEPHIR_INIT_NVAR(&item);
				continue;
			}
			if (ZEPHIR_IS_LONG(&type, 423)) {
				ZEPHIR_CALL_METHOD(&_10$$9, this_ptr, "expandEmbed", &_11, 0, &statement);
				zephir_check_call_status();
				if (Z_TYPE_P(&_10$$9) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_13$$9);
					zephir_string_to_char_array(&_13$$9, &_10$$9);
					_12$$9 = &_13$$9;
				} else {
					_12$$9 = &_10$$9;
				}
				zephir_is_iterable(_12$$9, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 268);
				if (Z_TYPE_P(_12$$9) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_12$$9), _14$$9)
					{
						ZEPHIR_INIT_NVAR(&item);
						ZVAL_COPY(&item, _14$$9);
						zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 265);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _12$$9, "rewind", NULL, 0);
					zephir_check_call_status();
					_16$$9 = 1;
					while (1) {
						if (_16$$9) {
							_16$$9 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _12$$9, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_15$$9, _12$$9, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_15$$9)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&item, _12$$9, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 265);
					}
				}
				ZEPHIR_INIT_NVAR(&item);
				continue;
			}
			_17$$3 = ZEPHIR_IS_LONG(&type, 359);
			if (_17$$3) {
				ZEPHIR_OBS_NVAR(&expr);
				_17$$3 = zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0);
			}
			if (_17$$3) {
				ZEPHIR_INIT_NVAR(&_19$$12);
				ZVAL_STRING(&_19$$12, "super");
				ZEPHIR_CALL_METHOD(&_18$$12, this_ptr, "isCall", &_20, 0, &expr, &_19$$12);
				zephir_check_call_status();
				if (zephir_is_true(&_18$$12)) {
					ZEPHIR_CALL_METHOD(&_21$$13, this_ptr, "expandSuper", &_22, 0, context, &statement);
					zephir_check_call_status();
					if (Z_TYPE_P(&_21$$13) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_24$$13);
						zephir_string_to_char_array(&_24$$13, &_21$$13);
						_23$$13 = &_24$$13;
					} else {
						_23$$13 = &_21$$13;
					}
					zephir_is_iterable(_23$$13, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 277);
					if (Z_TYPE_P(_23$$13) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_23$$13), _25$$13)
						{
							ZEPHIR_INIT_NVAR(&item);
							ZVAL_COPY(&item, _25$$13);
							zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 274);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _23$$13, "rewind", NULL, 0);
						zephir_check_call_status();
						_27$$13 = 1;
						while (1) {
							if (_27$$13) {
								_27$$13 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _23$$13, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_26$$13, _23$$13, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_26$$13)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&item, _23$$13, "current", NULL, 0);
							zephir_check_call_status();
								zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 274);
						}
					}
					ZEPHIR_INIT_NVAR(&item);
					continue;
				}
				ZEPHIR_INIT_NVAR(&_19$$12);
				ZVAL_STRING(&_19$$12, "block");
				ZEPHIR_CALL_METHOD(&_28$$12, this_ptr, "isCall", &_20, 0, &expr, &_19$$12);
				zephir_check_call_status();
				if (zephir_is_true(&_28$$12)) {
					ZEPHIR_CALL_METHOD(&_29$$16, this_ptr, "expandBlockFunction", &_30, 0, &expr);
					zephir_check_call_status();
					if (Z_TYPE_P(&_29$$16) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_32$$16);
						zephir_string_to_char_array(&_32$$16, &_29$$16);
						_31$$16 = &_32$$16;
					} else {
						_31$$16 = &_29$$16;
					}
					zephir_is_iterable(_31$$16, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 285);
					if (Z_TYPE_P(_31$$16) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_31$$16), _33$$16)
						{
							ZEPHIR_INIT_NVAR(&item);
							ZVAL_COPY(&item, _33$$16);
							zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 282);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _31$$16, "rewind", NULL, 0);
						zephir_check_call_status();
						_35$$16 = 1;
						while (1) {
							if (_35$$16) {
								_35$$16 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _31$$16, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_34$$16, _31$$16, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_34$$16)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&item, _31$$16, "current", NULL, 0);
							zephir_check_call_status();
								zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 282);
						}
					}
					ZEPHIR_INIT_NVAR(&item);
					continue;
				}
			}
			ZEPHIR_INIT_NVAR(&_36$$3);
			zephir_create_array(&_36$$3, 5, 0);
			ZEPHIR_INIT_NVAR(&_37$$3);
			ZVAL_STRING(&_37$$3, "block_statements");
			zephir_array_fast_append(&_36$$3, &_37$$3);
			ZEPHIR_INIT_NVAR(&_37$$3);
			ZVAL_STRING(&_37$$3, "true_statements");
			zephir_array_fast_append(&_36$$3, &_37$$3);
			ZEPHIR_INIT_NVAR(&_37$$3);
			ZVAL_STRING(&_37$$3, "false_statements");
			zephir_array_fast_append(&_36$$3, &_37$$3);
			ZEPHIR_INIT_NVAR(&_37$$3);
			ZVAL_STRING(&_37$$3, "case_clauses");
			zephir_array_fast_append(&_36$$3, &_37$$3);
			ZEPHIR_INIT_NVAR(&_37$$3);
			ZVAL_STRING(&_37$$3, "caller");
			zephir_array_fast_append(&_36$$3, &_37$$3);
			zephir_is_iterable(&_36$$3, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 297);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_36$$3), _38$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				ZVAL_COPY(&key, _38$$3);
				ZEPHIR_OBS_NVAR(&children);
				if (zephir_array_isset_fetch(&children, &statement, &key, 0)) {
					if (Z_TYPE_P(&children) == IS_ARRAY) {
						ZEPHIR_CALL_METHOD(&_39$$21, this_ptr, "expand", &_40, 0, &children, context);
						zephir_check_call_status();
						zephir_array_update_zval(&statement, &key, &_39$$21, PH_COPY | PH_SEPARATE);
					}
				}
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&key);
			zephir_array_append(&out, &statement, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 297);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_42 = 1;
		while (1) {
			if (_42) {
				_42 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_41, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_41)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				_43$$22 = Z_TYPE_P(&statement) != IS_ARRAY;
				if (!(_43$$22)) {
					ZEPHIR_OBS_NVAR(&type);
					_43$$22 = !(zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0));
				}
				if (_43$$22) {
					zephir_array_append(&out, &statement, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 247);
					continue;
				}
				if (ZEPHIR_IS_LONG(&type, 310)) {
					continue;
				}
				if (ZEPHIR_IS_LONG(&type, 307)) {
					ZEPHIR_OBS_NVAR(&_45$$25);
					zephir_array_fetch_string(&_45$$25, &statement, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 256);
					ZEPHIR_CALL_METHOD(&_44$$25, this_ptr, "expandBlock", &_4, 0, &_45$$25, &statement);
					zephir_check_call_status();
					if (Z_TYPE_P(&_44$$25) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_47$$25);
						zephir_string_to_char_array(&_47$$25, &_44$$25);
						_46$$25 = &_47$$25;
					} else {
						_46$$25 = &_44$$25;
					}
					zephir_is_iterable(_46$$25, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 260);
					if (Z_TYPE_P(_46$$25) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_46$$25), _48$$25)
						{
							ZEPHIR_INIT_NVAR(&item);
							ZVAL_COPY(&item, _48$$25);
							zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 257);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _46$$25, "rewind", NULL, 0);
						zephir_check_call_status();
						_50$$25 = 1;
						while (1) {
							if (_50$$25) {
								_50$$25 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _46$$25, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_49$$25, _46$$25, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_49$$25)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&item, _46$$25, "current", NULL, 0);
							zephir_check_call_status();
								zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 257);
						}
					}
					ZEPHIR_INIT_NVAR(&item);
					continue;
				}
				if (ZEPHIR_IS_LONG(&type, 423)) {
					ZEPHIR_CALL_METHOD(&_51$$28, this_ptr, "expandEmbed", &_11, 0, &statement);
					zephir_check_call_status();
					if (Z_TYPE_P(&_51$$28) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_53$$28);
						zephir_string_to_char_array(&_53$$28, &_51$$28);
						_52$$28 = &_53$$28;
					} else {
						_52$$28 = &_51$$28;
					}
					zephir_is_iterable(_52$$28, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 268);
					if (Z_TYPE_P(_52$$28) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_52$$28), _54$$28)
						{
							ZEPHIR_INIT_NVAR(&item);
							ZVAL_COPY(&item, _54$$28);
							zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 265);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _52$$28, "rewind", NULL, 0);
						zephir_check_call_status();
						_56$$28 = 1;
						while (1) {
							if (_56$$28) {
								_56$$28 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _52$$28, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_55$$28, _52$$28, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_55$$28)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&item, _52$$28, "current", NULL, 0);
							zephir_check_call_status();
								zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 265);
						}
					}
					ZEPHIR_INIT_NVAR(&item);
					continue;
				}
				_57$$22 = ZEPHIR_IS_LONG(&type, 359);
				if (_57$$22) {
					ZEPHIR_OBS_NVAR(&expr);
					_57$$22 = zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0);
				}
				if (_57$$22) {
					ZEPHIR_INIT_NVAR(&_59$$31);
					ZVAL_STRING(&_59$$31, "super");
					ZEPHIR_CALL_METHOD(&_58$$31, this_ptr, "isCall", &_20, 0, &expr, &_59$$31);
					zephir_check_call_status();
					if (zephir_is_true(&_58$$31)) {
						ZEPHIR_CALL_METHOD(&_60$$32, this_ptr, "expandSuper", &_22, 0, context, &statement);
						zephir_check_call_status();
						if (Z_TYPE_P(&_60$$32) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_62$$32);
							zephir_string_to_char_array(&_62$$32, &_60$$32);
							_61$$32 = &_62$$32;
						} else {
							_61$$32 = &_60$$32;
						}
						zephir_is_iterable(_61$$32, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 277);
						if (Z_TYPE_P(_61$$32) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_61$$32), _63$$32)
							{
								ZEPHIR_INIT_NVAR(&item);
								ZVAL_COPY(&item, _63$$32);
								zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 274);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _61$$32, "rewind", NULL, 0);
							zephir_check_call_status();
							_65$$32 = 1;
							while (1) {
								if (_65$$32) {
									_65$$32 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _61$$32, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_64$$32, _61$$32, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_64$$32)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&item, _61$$32, "current", NULL, 0);
								zephir_check_call_status();
									zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 274);
							}
						}
						ZEPHIR_INIT_NVAR(&item);
						continue;
					}
					ZEPHIR_INIT_NVAR(&_59$$31);
					ZVAL_STRING(&_59$$31, "block");
					ZEPHIR_CALL_METHOD(&_66$$31, this_ptr, "isCall", &_20, 0, &expr, &_59$$31);
					zephir_check_call_status();
					if (zephir_is_true(&_66$$31)) {
						ZEPHIR_CALL_METHOD(&_67$$35, this_ptr, "expandBlockFunction", &_30, 0, &expr);
						zephir_check_call_status();
						if (Z_TYPE_P(&_67$$35) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_69$$35);
							zephir_string_to_char_array(&_69$$35, &_67$$35);
							_68$$35 = &_69$$35;
						} else {
							_68$$35 = &_67$$35;
						}
						zephir_is_iterable(_68$$35, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 285);
						if (Z_TYPE_P(_68$$35) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_68$$35), _70$$35)
							{
								ZEPHIR_INIT_NVAR(&item);
								ZVAL_COPY(&item, _70$$35);
								zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 282);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _68$$35, "rewind", NULL, 0);
							zephir_check_call_status();
							_72$$35 = 1;
							while (1) {
								if (_72$$35) {
									_72$$35 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _68$$35, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_71$$35, _68$$35, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_71$$35)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&item, _68$$35, "current", NULL, 0);
								zephir_check_call_status();
									zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 282);
							}
						}
						ZEPHIR_INIT_NVAR(&item);
						continue;
					}
				}
				ZEPHIR_INIT_NVAR(&_73$$22);
				zephir_create_array(&_73$$22, 5, 0);
				ZEPHIR_INIT_NVAR(&_74$$22);
				ZVAL_STRING(&_74$$22, "block_statements");
				zephir_array_fast_append(&_73$$22, &_74$$22);
				ZEPHIR_INIT_NVAR(&_74$$22);
				ZVAL_STRING(&_74$$22, "true_statements");
				zephir_array_fast_append(&_73$$22, &_74$$22);
				ZEPHIR_INIT_NVAR(&_74$$22);
				ZVAL_STRING(&_74$$22, "false_statements");
				zephir_array_fast_append(&_73$$22, &_74$$22);
				ZEPHIR_INIT_NVAR(&_74$$22);
				ZVAL_STRING(&_74$$22, "case_clauses");
				zephir_array_fast_append(&_73$$22, &_74$$22);
				ZEPHIR_INIT_NVAR(&_74$$22);
				ZVAL_STRING(&_74$$22, "caller");
				zephir_array_fast_append(&_73$$22, &_74$$22);
				zephir_is_iterable(&_73$$22, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 297);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_73$$22), _75$$22)
				{
					ZEPHIR_INIT_NVAR(&key);
					ZVAL_COPY(&key, _75$$22);
					ZEPHIR_OBS_NVAR(&children);
					if (zephir_array_isset_fetch(&children, &statement, &key, 0)) {
						if (Z_TYPE_P(&children) == IS_ARRAY) {
							ZEPHIR_CALL_METHOD(&_76$$40, this_ptr, "expand", &_40, 0, &children, context);
							zephir_check_call_status();
							zephir_array_update_zval(&statement, &key, &_76$$40, PH_COPY | PH_SEPARATE);
						}
					}
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&key);
				zephir_array_append(&out, &statement, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 297);
		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	RETURN_CTOR(&out);
}

/**
 * A {% block %} node: the most derived definition of that name
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlock)
{
	zval _12;
	zend_bool _9;
	zend_ulong _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval node;
	zval name_zv, *node_param = NULL, index, level, _0, *_1, _2, *_3, _8, _11, _6$$3, _10$$5;
	zend_string *name = NULL, *_5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&node);
	ZVAL_UNDEF(&_12);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("levels", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		ZEPHIR_Z_PARAM_ARRAY(node, node_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	node_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_get_arrval(&node, node_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 938, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 316);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&index);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&index, _5);
			} else {
				ZVAL_LONG(&index, _4);
			}
			ZEPHIR_INIT_NVAR(&level);
			ZVAL_COPY(&level, _3);
			ZEPHIR_OBS_NVAR(&_6$$3);
			zephir_array_fetch_string(&_6$$3, &level, SL("blocks"), 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 311);
			if (zephir_array_isset_value(&_6$$3, &name_zv)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "expandBlockAt", &_7, 0, &name_zv, &index);
				zephir_check_call_status();
				RETURN_MM();
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_9 = 1;
		while (1) {
			if (_9) {
				_9 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_8, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&index, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&level, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_10$$5);
				zephir_array_fetch_string(&_10$$5, &level, SL("blocks"), 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 311);
				if (zephir_array_isset_value(&_10$$5, &name_zv)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "expandBlockAt", &_7, 0, &name_zv, &index);
					zephir_check_call_status();
					RETURN_MM();
				}
		}
	}
	ZEPHIR_INIT_NVAR(&level);
	ZEPHIR_INIT_NVAR(&index);
	ZEPHIR_INIT_VAR(&_12);
	ZEPHIR_CONCAT_SVS(&_12, "Block '", &name_zv, "' is not defined");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_11, this_ptr, "error", NULL, 0, &_12, &node);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_11, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 316);
	ZEPHIR_MM_RESTORE();
	return;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlockAt)
{
	zval _9;
	zend_bool _8;
	zval _1, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, *index_param = NULL, __$true, key, block, statements, result, _0, _2, _3, _4, _5, _10, _6$$3;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&block);
	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_9);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("levels", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("expanding", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	index_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, index);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_VSV(&_1, &name_zv, "@", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&key, &_1);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 938, PH_NOISY_CC | PH_READONLY);
	zephir_memory_observe(&_3);
	zephir_array_fetch_long(&_3, &_2, index, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 324);
	zephir_memory_observe(&_4);
	zephir_array_fetch_string(&_4, &_3, SL("blocks"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 324);
	zephir_memory_observe(&block);
	zephir_array_fetch(&block, &_4, &name_zv, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 324);
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_1, 940, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(zephir_array_isset_value(&_5, &key))) {
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVS(&_7$$3, "Block '", &name_zv, "' renders itself");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_6$$3, this_ptr, "error", NULL, 0, &_7$$3, &block);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$3, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 327);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&statements);
	_8 = !(zephir_array_isset_string_fetch(&statements, &block, SL("block_statements"), 0));
	if (!(_8)) {
		_8 = Z_TYPE_P(&statements) != IS_ARRAY;
	}
	if (_8) {
		ZEPHIR_INIT_NVAR(&statements);
		array_init(&statements);
	}
	zephir_update_property_array(this_ptr, SL("expanding"), &key, &__$true);
	ZEPHIR_INIT_VAR(&_9);
	zephir_create_array(&_9, 2, 0);
	zephir_array_update_string(&_9, SL("name"), &name_zv, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_LONG(&_10, index);
	zephir_array_update_string(&_9, SL("level"), &_10, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&result, this_ptr, "expand", NULL, 0, &statements, &_9);
	zephir_check_call_status();
	zephir_unset_property_array(this_ptr, ZEND_STRL("expanding"), &key);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(&result);
}

/**
 * {{ block("name") }}: render a block again elsewhere (<title> and <h1>)
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlockFunction)
{
	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *call_param = NULL, arguments, argument, _4, _5, _8, _9, _2$$3, _3$$3, _6$$4, _7$$4;
	zval call;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&call);
	ZVAL_UNDEF(&arguments);
	ZVAL_UNDEF(&argument);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(call, call_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &call_param);
	zephir_get_arrval(&call, call_param);
	zephir_memory_observe(&arguments);
	_0 = !(zephir_array_isset_string_fetch(&arguments, &call, SL("arguments"), 0));
	if (!(_0)) {
		_0 = Z_TYPE_P(&arguments) != IS_ARRAY;
	}
	_1 = _0;
	if (!(_1)) {
		_1 = zephir_fast_count_int(&arguments) != 1;
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "block() takes one string literal: {{ block(\"name\") }}");
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "error", NULL, 0, &_3$$3, &call);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 357);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&argument);
	zephir_array_fetch_long(&argument, &arguments, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 360);
	zephir_memory_observe(&_5);
	zephir_array_fetch_string(&_5, &argument, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 362);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "isLiteral", NULL, 0, &_5);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_4))) {
		ZEPHIR_INIT_VAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "block() takes one string literal: {{ block(\"name\") }}");
		ZEPHIR_CALL_METHOD(&_6$$4, this_ptr, "error", NULL, 0, &_7$$4, &call);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$4, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 363);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_8);
	zephir_array_fetch_string(&_8, &argument, SL("expr"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 366);
	zephir_memory_observe(&_9);
	zephir_array_fetch_string(&_9, &_8, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 366);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "expandBlock", NULL, 0, &_9, &call);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * {% embed "card.volt" with [...] %}{% block body %}...{% endblock %}{% endembed %}
 *
 * The body is an anonymous child template of "card.volt", resolved on its
 * own, inlined here and run in a scope of its own.
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandEmbed)
{
	zend_bool _21, _10$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *node_param = NULL, child, statements, params, statement, sub, item, _0, _1, _5, _11, _14, _15, _16, _17, *_18, *_19, _20, _22, _23, _2$$3, _3$$3, *_6$$5, _7$$5, *_8$$5, _9$$5, _12$$8, _13$$8;
	zval node, out, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&node);
	ZVAL_UNDEF(&out);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&child);
	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&sub);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_13$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("compiler", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("levels", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(node, node_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &node_param);
	zephir_get_arrval(&node, node_param);
	zephir_memory_observe(&_1);
	zephir_array_fetch_string(&_1, &node, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 380);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isLiteral", NULL, 0, &_1);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "embed needs a string literal template name");
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "error", NULL, 0, &_3$$3, &node);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 381);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&child);
	zephir_create_array(&child, 1, 0);
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_array(&_4, 4, 0);
	add_assoc_long_ex(&_4, SL("type"), 310);
	zephir_memory_observe(&_5);
	zephir_array_fetch_string(&_5, &node, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 387);
	zephir_array_update_string(&_4, SL("path"), &_5, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_5);
	zephir_array_fetch_string(&_5, &node, SL("file"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 388);
	zephir_array_update_string(&_4, SL("file"), &_5, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_5);
	zephir_array_fetch_string(&_5, &node, SL("line"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 390);
	zephir_array_update_string(&_4, SL("line"), &_5, PH_COPY | PH_SEPARATE);
	zephir_array_fast_append(&child, &_4);
	zephir_memory_observe(&statements);
	if (zephir_array_isset_string_fetch(&statements, &node, SL("block_statements"), 0)) {
		if (Z_TYPE_P(&statements) == IS_ARRAY) {
			if (Z_TYPE_P(&statements) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_7$$5);
				zephir_string_to_char_array(&_7$$5, &statements);
				_6$$5 = &_7$$5;
			} else {
				_6$$5 = &statements;
			}
			zephir_is_iterable(_6$$5, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 398);
			if (Z_TYPE_P(_6$$5) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_6$$5), _8$$5)
				{
					ZEPHIR_INIT_NVAR(&statement);
					ZVAL_COPY(&statement, _8$$5);
					zephir_array_append(&child, &statement, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 396);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _6$$5, "rewind", NULL, 0);
				zephir_check_call_status();
				_10$$5 = 1;
				while (1) {
					if (_10$$5) {
						_10$$5 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _6$$5, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_9$$5, _6$$5, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&statement, _6$$5, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_append(&child, &statement, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 396);
				}
			}
			ZEPHIR_INIT_NVAR(&statement);
		}
	}
	ZEPHIR_INIT_VAR(&sub);
	object_init_ex(&sub, phalcon_mvc_view_engine_volt_resolver_ce);
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_0, 937, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &sub, "__construct", NULL, 0, &_11);
	zephir_check_call_status();
	zephir_memory_observe(&params);
	if (zephir_array_isset_string_fetch(&params, &node, SL("params"), 0)) {
		zephir_read_property_cached(&_12$$8, this_ptr, _zephir_prop_0, 937, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_13$$8, &_12$$8, "expression", NULL, 0, &params);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&params, &_13$$8);
	} else {
		ZEPHIR_INIT_NVAR(&params);
		ZVAL_STRING(&params, "[]");
	}
	ZEPHIR_INIT_VAR(&out);
	zephir_create_array(&out, 1, 0);
	ZEPHIR_INIT_VAR(&_15);
	ZVAL_STRING(&_15, "<?php (function (array $__volt_scope) { extract($__volt_scope); ?>");
	ZEPHIR_CALL_SELF(&_14, "php", NULL, 0, &_15);
	zephir_check_call_status();
	zephir_array_fast_append(&out, &_14);
	zephir_read_property_cached(&_16, this_ptr, _zephir_prop_1, 938, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_NVAR(&_5);
	zephir_array_fetch_long(&_5, &_16, 0, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 413);
	zephir_memory_observe(&_17);
	zephir_array_fetch_string(&_17, &_5, SL("path"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 413);
	ZEPHIR_CALL_METHOD(&_14, &sub, "resolveChain", NULL, 0, &child, &_17);
	zephir_check_call_status();
	if (Z_TYPE_P(&_14) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_15);
		zephir_string_to_char_array(&_15, &_14);
		_18 = &_15;
	} else {
		_18 = &_14;
	}
	zephir_is_iterable(_18, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 417);
	if (Z_TYPE_P(_18) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_18), _19)
		{
			ZEPHIR_INIT_NVAR(&item);
			ZVAL_COPY(&item, _19);
			zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 414);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _18, "rewind", NULL, 0);
		zephir_check_call_status();
		_21 = 1;
		while (1) {
			if (_21) {
				_21 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _18, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_20, _18, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_20)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&item, _18, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_append(&out, &item, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 414);
		}
	}
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_INIT_VAR(&_23);
	ZEPHIR_CONCAT_SVS(&_23, "<?php })(array_merge(get_defined_vars(), ", &params, ")); ?>");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_SELF(&_22, "php", NULL, 0, &_23);
	zephir_check_call_status();
	zephir_array_append(&out, &_22, PH_SEPARATE, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 417);
	RETURN_CTOR(&out);
}

/**
 * {{ super() }}: the definition of the current block one level up
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandSuper)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, index = 0, total = 0;
	zval node;
	zval *context, context_sub, *node_param = NULL, name, _2, _3, _9, _10, _0$$3, _1$$3, _4$$4, _5$$4, _6$$4, _7$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&context_sub);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&node);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("levels", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(context)
		ZEPHIR_Z_PARAM_ARRAY(node, node_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &context, &node_param);
	zephir_get_arrval(&node, node_param);
	if (UNEXPECTED(Z_TYPE_P(context) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "super() can only be used inside a block");
		ZEPHIR_CALL_METHOD(&_0$$3, this_ptr, "error", NULL, 0, &_1$$3, &node);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 431);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&name);
	zephir_array_fetch_string(&name, context, SL("name"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 434);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 938, PH_NOISY_CC | PH_READONLY);
	total = zephir_fast_count_int(&_2);
	zephir_memory_observe(&_3);
	zephir_array_fetch_string(&_3, context, SL("level"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 436);
	index = (zephir_get_intval(&_3) + 1);
	while (1) {
		if (!(index < total)) {
			break;
		}
		zephir_read_property_cached(&_4$$4, this_ptr, _zephir_prop_0, 938, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_NVAR(&_5$$4);
		zephir_array_fetch_long(&_5$$4, &_4$$4, index, PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 439);
		ZEPHIR_OBS_NVAR(&_6$$4);
		zephir_array_fetch_string(&_6$$4, &_5$$4, SL("blocks"), 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 439);
		if (zephir_array_isset_value(&_6$$4, &name)) {
			ZVAL_LONG(&_7$$5, index);
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "expandBlockAt", &_8, 0, &name, &_7$$5);
			zephir_check_call_status();
			RETURN_MM();
		}
		index++;
	}
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_CONCAT_SVS(&_10, "super() in block '", &name, "': no parent template defines it");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_9, this_ptr, "error", NULL, 0, &_10, &node);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_9, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 446);
	ZEPHIR_MM_RESTORE();
	return;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, findExtends)
{
	zend_bool _3, _1$$3, _4$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statements_param = NULL, statement, type, *_0, _2;
	zval statements;

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statements_param);
	zephir_get_arrval(&statements, statements_param);
	zephir_is_iterable(&statements, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 461);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&statements), _0)
		{
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _0);
			_1$$3 = Z_TYPE_P(&statement) == IS_ARRAY;
			if (_1$$3) {
				ZEPHIR_OBS_NVAR(&type);
				_1$$3 = zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0);
			}
			if (_1$$3) {
				if (ZEPHIR_IS_LONG(&type, 310)) {
					RETURN_CCTOR(&statement);
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_3 = 1;
		while (1) {
			if (_3) {
				_3 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_2, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				_4$$6 = Z_TYPE_P(&statement) == IS_ARRAY;
				if (_4$$6) {
					ZEPHIR_OBS_NVAR(&type);
					_4$$6 = zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0);
				}
				if (_4$$6) {
					if (ZEPHIR_IS_LONG(&type, 310)) {
						RETURN_CCTOR(&statement);
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	RETURN_MM_NULL();
}

/**
 * Whether a template uses blocks, embed, block() or super() anywhere
 */
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, hasInheritanceNodes)
{
	zend_bool _16, _1$$3, _2$$3, _3$$3, _7$$6, _12$$9, _17$$11, _18$$11, _19$$11, _22$$14, _27$$17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_14 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *statements_param = NULL, statement, type, key, children, expr, *_0, _15, _10$$3, *_11$$3, _4$$6, _5$$6, _8$$6, _13$$9, _25$$11, *_26$$11, _20$$14, _21$$14, _23$$14, _28$$17;
	zval statements, _9$$3, _24$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_24$$11);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&children);
	ZVAL_UNDEF(&expr);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_25$$11);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_28$$17);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &statements_param);
	zephir_get_arrval(&statements, statements_param);
	zephir_is_iterable(&statements, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 495);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&statements), _0)
		{
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _0);
			_1$$3 = Z_TYPE_P(&statement) != IS_ARRAY;
			if (!(_1$$3)) {
				ZEPHIR_OBS_NVAR(&type);
				_1$$3 = !(zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0));
			}
			if (_1$$3) {
				continue;
			}
			_2$$3 = ZEPHIR_IS_LONG(&type, 307);
			if (!(_2$$3)) {
				_2$$3 = ZEPHIR_IS_LONG(&type, 423);
			}
			if (_2$$3) {
				RETURN_MM_BOOL(1);
			}
			_3$$3 = ZEPHIR_IS_LONG(&type, 359);
			if (_3$$3) {
				ZEPHIR_OBS_NVAR(&expr);
				_3$$3 = zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0);
			}
			if (_3$$3) {
				ZEPHIR_INIT_NVAR(&_5$$6);
				ZVAL_STRING(&_5$$6, "block");
				ZEPHIR_CALL_METHOD(&_4$$6, this_ptr, "isCall", &_6, 0, &expr, &_5$$6);
				zephir_check_call_status();
				_7$$6 = zephir_is_true(&_4$$6);
				if (!(_7$$6)) {
					ZEPHIR_INIT_NVAR(&_5$$6);
					ZVAL_STRING(&_5$$6, "super");
					ZEPHIR_CALL_METHOD(&_8$$6, this_ptr, "isCall", &_6, 0, &expr, &_5$$6);
					zephir_check_call_status();
					_7$$6 = zephir_is_true(&_8$$6);
				}
				if (_7$$6) {
					RETURN_MM_BOOL(1);
				}
			}
			ZEPHIR_INIT_NVAR(&_9$$3);
			zephir_create_array(&_9$$3, 5, 0);
			ZEPHIR_INIT_NVAR(&_10$$3);
			ZVAL_STRING(&_10$$3, "block_statements");
			zephir_array_fast_append(&_9$$3, &_10$$3);
			ZEPHIR_INIT_NVAR(&_10$$3);
			ZVAL_STRING(&_10$$3, "true_statements");
			zephir_array_fast_append(&_9$$3, &_10$$3);
			ZEPHIR_INIT_NVAR(&_10$$3);
			ZVAL_STRING(&_10$$3, "false_statements");
			zephir_array_fast_append(&_9$$3, &_10$$3);
			ZEPHIR_INIT_NVAR(&_10$$3);
			ZVAL_STRING(&_10$$3, "case_clauses");
			zephir_array_fast_append(&_9$$3, &_10$$3);
			ZEPHIR_INIT_NVAR(&_10$$3);
			ZVAL_STRING(&_10$$3, "caller");
			zephir_array_fast_append(&_9$$3, &_10$$3);
			zephir_is_iterable(&_9$$3, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 493);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_9$$3), _11$$3)
			{
				ZEPHIR_INIT_NVAR(&key);
				ZVAL_COPY(&key, _11$$3);
				ZEPHIR_OBS_NVAR(&children);
				if (zephir_array_isset_fetch(&children, &statement, &key, 0)) {
					_12$$9 = Z_TYPE_P(&children) == IS_ARRAY;
					if (_12$$9) {
						ZEPHIR_CALL_METHOD(&_13$$9, this_ptr, "hasInheritanceNodes", &_14, 0, &children);
						zephir_check_call_status();
						_12$$9 = zephir_is_true(&_13$$9);
					}
					if (_12$$9) {
						RETURN_MM_BOOL(1);
					}
				}
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&key);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				_17$$11 = Z_TYPE_P(&statement) != IS_ARRAY;
				if (!(_17$$11)) {
					ZEPHIR_OBS_NVAR(&type);
					_17$$11 = !(zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0));
				}
				if (_17$$11) {
					continue;
				}
				_18$$11 = ZEPHIR_IS_LONG(&type, 307);
				if (!(_18$$11)) {
					_18$$11 = ZEPHIR_IS_LONG(&type, 423);
				}
				if (_18$$11) {
					RETURN_MM_BOOL(1);
				}
				_19$$11 = ZEPHIR_IS_LONG(&type, 359);
				if (_19$$11) {
					ZEPHIR_OBS_NVAR(&expr);
					_19$$11 = zephir_array_isset_string_fetch(&expr, &statement, SL("expr"), 0);
				}
				if (_19$$11) {
					ZEPHIR_INIT_NVAR(&_21$$14);
					ZVAL_STRING(&_21$$14, "block");
					ZEPHIR_CALL_METHOD(&_20$$14, this_ptr, "isCall", &_6, 0, &expr, &_21$$14);
					zephir_check_call_status();
					_22$$14 = zephir_is_true(&_20$$14);
					if (!(_22$$14)) {
						ZEPHIR_INIT_NVAR(&_21$$14);
						ZVAL_STRING(&_21$$14, "super");
						ZEPHIR_CALL_METHOD(&_23$$14, this_ptr, "isCall", &_6, 0, &expr, &_21$$14);
						zephir_check_call_status();
						_22$$14 = zephir_is_true(&_23$$14);
					}
					if (_22$$14) {
						RETURN_MM_BOOL(1);
					}
				}
				ZEPHIR_INIT_NVAR(&_24$$11);
				zephir_create_array(&_24$$11, 5, 0);
				ZEPHIR_INIT_NVAR(&_25$$11);
				ZVAL_STRING(&_25$$11, "block_statements");
				zephir_array_fast_append(&_24$$11, &_25$$11);
				ZEPHIR_INIT_NVAR(&_25$$11);
				ZVAL_STRING(&_25$$11, "true_statements");
				zephir_array_fast_append(&_24$$11, &_25$$11);
				ZEPHIR_INIT_NVAR(&_25$$11);
				ZVAL_STRING(&_25$$11, "false_statements");
				zephir_array_fast_append(&_24$$11, &_25$$11);
				ZEPHIR_INIT_NVAR(&_25$$11);
				ZVAL_STRING(&_25$$11, "case_clauses");
				zephir_array_fast_append(&_24$$11, &_25$$11);
				ZEPHIR_INIT_NVAR(&_25$$11);
				ZVAL_STRING(&_25$$11, "caller");
				zephir_array_fast_append(&_24$$11, &_25$$11);
				zephir_is_iterable(&_24$$11, 0, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 493);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_24$$11), _26$$11)
				{
					ZEPHIR_INIT_NVAR(&key);
					ZVAL_COPY(&key, _26$$11);
					ZEPHIR_OBS_NVAR(&children);
					if (zephir_array_isset_fetch(&children, &statement, &key, 0)) {
						_27$$17 = Z_TYPE_P(&children) == IS_ARRAY;
						if (_27$$17) {
							ZEPHIR_CALL_METHOD(&_28$$17, this_ptr, "hasInheritanceNodes", &_14, 0, &children);
							zephir_check_call_status();
							_27$$17 = zephir_is_true(&_28$$17);
						}
						if (_27$$17) {
							RETURN_MM_BOOL(1);
						}
					}
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&key);
		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	RETURN_MM_BOOL(0);
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, isCall)
{
	zend_bool _0, _1, _2, _3, _5, _6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_string *name = NULL;
	zval *expr, expr_sub, name_zv, type, nameNode, _4, _7;

	ZVAL_UNDEF(&expr_sub);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&nameNode);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(expr)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	expr = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	_0 = Z_TYPE_P(expr) != IS_ARRAY;
	if (!(_0)) {
		zephir_memory_observe(&type);
		_0 = !(zephir_array_isset_string_fetch(&type, expr, SL("type"), 0));
	}
	_1 = _0;
	if (!(_1)) {
		_1 = !ZEPHIR_IS_LONG(&type, 350);
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	zephir_memory_observe(&nameNode);
	_2 = !(zephir_array_isset_string_fetch(&nameNode, expr, SL("name"), 0));
	if (!(_2)) {
		_2 = Z_TYPE_P(&nameNode) != IS_ARRAY;
	}
	if (_2) {
		RETURN_MM_BOOL(0);
	}
	_3 = zephir_array_isset_value_string(&nameNode, SL("type"));
	if (_3) {
		zephir_memory_observe(&_4);
		zephir_array_fetch_string(&_4, &nameNode, SL("type"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 510);
		_3 = ZEPHIR_IS_LONG(&_4, 265);
	}
	_5 = _3;
	if (_5) {
		_5 = zephir_array_isset_value_string(&nameNode, SL("value"));
	}
	_6 = _5;
	if (_6) {
		zephir_memory_observe(&_7);
		zephir_array_fetch_string(&_7, &nameNode, SL("value"), PH_NOISY, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 511);
		_6 = ZEPHIR_IS_IDENTICAL(&_7, &name_zv);
	}
	RETURN_MM_BOOL(_6);
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, isLiteral)
{
	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *expr, expr_sub, type;

	ZVAL_UNDEF(&expr_sub);
	ZVAL_UNDEF(&type);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(expr)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &expr);
	_0 = Z_TYPE_P(expr) == IS_ARRAY;
	if (_0) {
		zephir_memory_observe(&type);
		_0 = zephir_array_isset_string_fetch(&type, expr, SL("type"), 0);
	}
	_1 = _0;
	if (_1) {
		_1 = ZEPHIR_IS_LONG(&type, 260);
	}
	RETURN_MM_BOOL(_1);
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, withExtendsPath)
{
	zend_bool _6, _3$$3, _7$$6;
	zend_ulong _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL, *_2;
	zval *statements_param = NULL, path_zv, index, statement, type, *_0, _5;
	zval statements, _4$$5, _8$$8;

	ZVAL_UNDEF(&statements);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&_5);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(statements, statements_param)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	statements_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&statements, statements_param);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	zephir_is_iterable(&statements, 1, "phalcon/Mvc/View/Engine/Volt/Resolver.zep", 538);
	if (Z_TYPE_P(&statements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&statements), _1, _2, _0)
		{
			ZEPHIR_INIT_NVAR(&index);
			if (_2 != NULL) { 
				ZVAL_STR_COPY(&index, _2);
			} else {
				ZVAL_LONG(&index, _1);
			}
			ZEPHIR_INIT_NVAR(&statement);
			ZVAL_COPY(&statement, _0);
			_3$$3 = Z_TYPE_P(&statement) == IS_ARRAY;
			if (_3$$3) {
				ZEPHIR_OBS_NVAR(&type);
				_3$$3 = zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0);
			}
			if (_3$$3) {
				if (ZEPHIR_IS_LONG(&type, 310)) {
					ZEPHIR_INIT_NVAR(&_4$$5);
					zephir_create_array(&_4$$5, 2, 0);
					add_assoc_long_ex(&_4$$5, SL("type"), 260);
					zephir_array_update_string(&_4$$5, SL("value"), &path_zv, PH_COPY | PH_SEPARATE);
					zephir_array_update_multi(&statements, &_4$$5, SL("zs"), 3, &index, SL("path"));
					break;
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &statements, "rewind", NULL, 0);
		zephir_check_call_status();
		_6 = 1;
		while (1) {
			if (_6) {
				_6 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &statements, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_5, &statements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&index, &statements, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&statement, &statements, "current", NULL, 0);
			zephir_check_call_status();
				_7$$6 = Z_TYPE_P(&statement) == IS_ARRAY;
				if (_7$$6) {
					ZEPHIR_OBS_NVAR(&type);
					_7$$6 = zephir_array_isset_string_fetch(&type, &statement, SL("type"), 0);
				}
				if (_7$$6) {
					if (ZEPHIR_IS_LONG(&type, 310)) {
						ZEPHIR_INIT_NVAR(&_8$$8);
						zephir_create_array(&_8$$8, 2, 0);
						add_assoc_long_ex(&_8$$8, SL("type"), 260);
						zephir_array_update_string(&_8$$8, SL("value"), &path_zv, PH_COPY | PH_SEPARATE);
						zephir_array_update_multi(&statements, &_8$$8, SL("zs"), 3, &index, SL("path"));
						break;
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&statement);
	ZEPHIR_INIT_NVAR(&index);
	RETURN_CTOR(&statements);
}

zend_object *zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Resolver(zend_class_entry *class_type)
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
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("levels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("levels"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("expanding"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("expanding"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("collected"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("collected"), &_5$$5);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

