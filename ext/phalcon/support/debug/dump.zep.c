
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/main.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Dumps information about a variable(s)
 *
 * ```php
 * $foo = 123;
 *
 * echo (new \Phalcon\Debug\Dump())->variable($foo, "foo");
 * ```
 *
 * ```php
 * $foo = "string";
 * $bar = ["key" => "value"];
 * $baz = new stdClass();
 *
 * echo (new \Phalcon\Debug\Dump())->variables($foo, $bar, $baz);
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Support_Debug_Dump)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Support\\Debug, Dump, phalcon, support_debug_dump, phalcon_support_debug_dump_method_entry, 0);

	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_support_debug_dump_ce, SL("detailed"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_support_debug_dump_ce, SL("methods"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_support_debug_dump_ce, SL("styles"), ZEND_ACC_PROTECTED);
	/**
	 * @var Encode
	 */
	zend_declare_property_null(phalcon_support_debug_dump_ce, SL("encode"), ZEND_ACC_PRIVATE);
	phalcon_support_debug_dump_ce->create_object = zephir_init_properties_Phalcon_Support_Debug_Dump;

	return SUCCESS;
}

/**
 * Phalcon\Debug\Dump constructor
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool detailed;
	zval *styles_param = NULL, *detailed_param = NULL, __$true, __$false, _0;
	zval styles;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&styles);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("encode", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("detailed", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(styles, styles_param)
		Z_PARAM_BOOL(detailed)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &styles_param, &detailed_param);
	if (!styles_param) {
		ZEPHIR_INIT_VAR(&styles);
		array_init(&styles);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&styles, styles_param);
	}
	if (!detailed_param) {
		detailed = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_support_helper_json_encode_ce);
	if (zephir_has_constructor(&_0)) {
		ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 994, &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setStyles", NULL, 0, &styles);
	zephir_check_call_status();
	if (detailed) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 995, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 995, &__$false);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Alias of variables() method
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, all)
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
	ZVAL_STRING(&_1, "variables");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_get_args(&_1);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Support_Debug_Dump, getDetailed)
{

	RETURN_MEMBER(getThis(), "detailed");
}

/**
 * Alias of variable() method
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, one)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *name = NULL;
	zval *variable, variable_sub, name_zv;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&variable_sub);
	ZVAL_UNDEF(&name_zv);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(variable)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	variable = ZEND_CALL_ARG(execute_data, 1);
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "variable", NULL, 0, variable, &name_zv);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Support_Debug_Dump, setDetailed)
{
	zval *flag_param = NULL, __$true, __$false;
	zend_bool flag;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("detailed", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(flag)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &flag_param);
	if (flag) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 995, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 995, &__$false);
	}
}

/**
 * Set styles for vars type
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, setStyles)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *styles_param = NULL, defaultStyles, _0;
	zval styles;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&styles);
	ZVAL_UNDEF(&defaultStyles);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("styles", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(styles, styles_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &styles_param);
	if (!styles_param) {
		ZEPHIR_INIT_VAR(&styles);
		array_init(&styles);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&styles, styles_param);
	}
	ZEPHIR_INIT_VAR(&defaultStyles);
	zephir_create_array(&defaultStyles, 11, 0);
	add_assoc_stringl_ex(&defaultStyles, SL("pre"), SL("background-color:#f3f3f3; font-size:11px; padding:10px; border:1px solid #ccc; text-align:left; color:#333"));
	add_assoc_stringl_ex(&defaultStyles, SL("arr"), SL("color:red"));
	add_assoc_stringl_ex(&defaultStyles, SL("bool"), SL("color:green"));
	add_assoc_stringl_ex(&defaultStyles, SL("float"), SL("color:fuchsia"));
	add_assoc_stringl_ex(&defaultStyles, SL("int"), SL("color:blue"));
	add_assoc_stringl_ex(&defaultStyles, SL("null"), SL("color:black"));
	add_assoc_stringl_ex(&defaultStyles, SL("num"), SL("color:navy"));
	add_assoc_stringl_ex(&defaultStyles, SL("obj"), SL("color:purple"));
	add_assoc_stringl_ex(&defaultStyles, SL("other"), SL("color:maroon"));
	add_assoc_stringl_ex(&defaultStyles, SL("res"), SL("color:lime"));
	add_assoc_stringl_ex(&defaultStyles, SL("str"), SL("color:teal"));
	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_array_merge(&_0, &defaultStyles, &styles);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 996, &_0);
	RETURN_MM_MEMBER_TYPED(getThis(), "styles", IS_ARRAY);
}

/**
 * Returns an JSON string of information about a single variable.
 *
 * ```php
 * $foo = [
 *     "key" => "value",
 * ];
 *
 * echo (new \Phalcon\Debug\Dump())->toJson($foo);
 *
 * $foo = new stdClass();
 * $foo->bar = "buz";
 *
 * echo (new \Phalcon\Debug\Dump())->toJson($foo);
 * ```
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, toJson)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *variable, variable_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&variable_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("encode", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(variable)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &variable);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 994, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, (((128 | 64) | 256) | 4194304));
	ZEPHIR_RETURN_CALL_METHOD(&_0, "__invoke", NULL, 0, variable, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns an HTML string of information about a single variable.
 *
 * ```php
 * echo (new \Phalcon\Debug\Dump())->variable($foo, "foo");
 * ```
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, variable)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *name = NULL;
	zval *variable, variable_sub, name_zv, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&variable_sub);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(variable)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	variable = ZEND_CALL_ARG(execute_data, 1);
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "pre");
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getStyle", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL(":style"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "output", NULL, 0, variable, &name_zv);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL(":output"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "<pre style=\":style\">:output</pre>");
	ZEPHIR_RETURN_CALL_FUNCTION("strtr", NULL, 5, &_2, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns an HTML string of debugging information about any number of
 * variables, each wrapped in a "pre" tag.
 *
 * ```php
 * $foo = "string";
 * $bar = ["key" => "value"];
 * $baz = new stdClass();
 *
 * echo (new \Phalcon\Debug\Dump())->variables($foo, $bar, $baz);
 * ```
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, variables)
{
	zend_bool _10;
	zend_string *_5;
	zend_ulong _4;
	zval output;
	zval key, value, _0, *_1, _2, *_3, _9, _6$$3, _7$$3, _11$$4, _12$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&output);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	ZEPHIR_INIT_VAR(&_0);
	zephir_get_args(&_0);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "phalcon/Support/Debug/Dump.zep", 198);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_1), _4, _5, _3)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_5 != NULL) { 
				ZVAL_STR_COPY(&key, _5);
			} else {
				ZVAL_LONG(&key, _4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZEPHIR_CONCAT_SV(&_7$$3, "var ", &key);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_6$$3, this_ptr, "one", &_8, 0, &value, &_7$$3);
			zephir_check_call_status();
			zephir_concat_self(&output, &_6$$3);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_10 = 1;
		while (1) {
			if (_10) {
				_10 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_9, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&key, _1, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_12$$4);
				ZEPHIR_CONCAT_SV(&_12$$4, "var ", &key);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_11$$4, this_ptr, "one", &_8, 0, &value, &_12$$4);
				zephir_check_call_status();
				zephir_concat_self(&output, &_11$$4);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CTOR(&output);
}

/**
 * Get style for type
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, getStyle)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval type_zv, style, _0;
	zend_string *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&style);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("styles", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	zephir_memory_observe(&style);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 996, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&style, &_0, &type_zv, 0))) {
		RETURN_MM_STRING("color:gray");
	}
	RETURN_CCTOR(&style);
}

/**
 * Prepare an HTML string of information about a single variable.
 */
PHP_METHOD(Phalcon_Support_Debug_Dump, output)
{
	zend_class_entry *_82$$16, *_101$$17;
	zend_bool _23$$4, _15$$5, _16$$5, _17$$5, _18$$5, _30$$7, _31$$7, _32$$7, _33$$7, _46$$9, _65$$12, _96$$15, _138$$19;
	zend_ulong _6$$4, _54$$12;
	zval _0$$3, _164$$28, _168$$29;
	zval _181, _1$$4, _11$$5, _26$$7, _38$$9, _115$$9, _42$$10, _58$$13, _68$$14, _87$$16, _105$$17, _127$$21, _133$$22, _142$$24, _148$$25, _157$$26, _161$$27, _165$$28, _169$$29, _174$$30, _178$$31;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_20 = NULL, *_79 = NULL, *_80 = NULL, *_83 = NULL, *_85 = NULL, *_93 = NULL, *_98 = NULL, *_99 = NULL, *_103 = NULL, *_111 = NULL;
	zend_long tab, ZEPHIR_LAST_CALL_STATUS;
	zend_string *name = NULL, *_7$$4, *_55$$12;
	zval *variable, variable_sub, name_zv, *tab_param = NULL, key, value, output, space, type, attr, _160, _182, _183, _2$$4, _3$$4, *_4$$4, *_5$$4, _22$$4, _36$$4, _37$$4, _8$$5, _9$$5, _12$$5, _13$$5, _14$$5, _19$$5, _21$$5, _24$$7, _25$$7, _27$$7, _28$$7, _29$$7, _34$$7, _35$$7, _39$$9, _40$$9, _41$$9, _45$$9, _113$$9, _114$$9, _116$$9, _117$$9, _155$$9, _156$$9, _43$$10, _44$$10, _47$$11, _48$$11, _49$$11, _50$$12, *_51$$12, _52$$12, *_53$$12, _64$$12, _56$$13, _57$$13, _59$$13, _60$$13, _61$$13, _62$$13, _63$$13, _66$$14, _67$$14, _69$$14, _70$$14, _71$$14, _72$$14, _73$$14, reflect$$15, props$$15, property$$15, _74$$15, *_75$$15, _76$$15, *_77$$15, _95$$15, _78$$16, _81$$16, _84$$16, _86$$16, _88$$16, _89$$16, _90$$16, _91$$16, _92$$16, _94$$16, _97$$17, _100$$17, _102$$17, _104$$17, _106$$17, _107$$17, _108$$17, _109$$17, _110$$17, _112$$17, _118$$18, _119$$18, _120$$18, *_121$$19, _122$$19, *_123$$19, _137$$19, _152$$19, _153$$19, _154$$19, _124$$20, _125$$21, _126$$21, _128$$21, _129$$21, _130$$21, _131$$22, _132$$22, _134$$22, _135$$22, _136$$22, _139$$23, _140$$24, _141$$24, _143$$24, _144$$24, _145$$24, _146$$25, _147$$25, _149$$25, _150$$25, _151$$25, _158$$26, _159$$26, _162$$27, _163$$27, _166$$28, _167$$28, _170$$29, _171$$29, _172$$29, _173$$29, _175$$30, _176$$30, _177$$30, _179$$31, _180$$31;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&variable_sub);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&output);
	ZVAL_UNDEF(&space);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&attr);
	ZVAL_UNDEF(&_160);
	ZVAL_UNDEF(&_182);
	ZVAL_UNDEF(&_183);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_22$$4);
	ZVAL_UNDEF(&_36$$4);
	ZVAL_UNDEF(&_37$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_27$$7);
	ZVAL_UNDEF(&_28$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_34$$7);
	ZVAL_UNDEF(&_35$$7);
	ZVAL_UNDEF(&_39$$9);
	ZVAL_UNDEF(&_40$$9);
	ZVAL_UNDEF(&_41$$9);
	ZVAL_UNDEF(&_45$$9);
	ZVAL_UNDEF(&_113$$9);
	ZVAL_UNDEF(&_114$$9);
	ZVAL_UNDEF(&_116$$9);
	ZVAL_UNDEF(&_117$$9);
	ZVAL_UNDEF(&_155$$9);
	ZVAL_UNDEF(&_156$$9);
	ZVAL_UNDEF(&_43$$10);
	ZVAL_UNDEF(&_44$$10);
	ZVAL_UNDEF(&_47$$11);
	ZVAL_UNDEF(&_48$$11);
	ZVAL_UNDEF(&_49$$11);
	ZVAL_UNDEF(&_50$$12);
	ZVAL_UNDEF(&_52$$12);
	ZVAL_UNDEF(&_64$$12);
	ZVAL_UNDEF(&_56$$13);
	ZVAL_UNDEF(&_57$$13);
	ZVAL_UNDEF(&_59$$13);
	ZVAL_UNDEF(&_60$$13);
	ZVAL_UNDEF(&_61$$13);
	ZVAL_UNDEF(&_62$$13);
	ZVAL_UNDEF(&_63$$13);
	ZVAL_UNDEF(&_66$$14);
	ZVAL_UNDEF(&_67$$14);
	ZVAL_UNDEF(&_69$$14);
	ZVAL_UNDEF(&_70$$14);
	ZVAL_UNDEF(&_71$$14);
	ZVAL_UNDEF(&_72$$14);
	ZVAL_UNDEF(&_73$$14);
	ZVAL_UNDEF(&reflect$$15);
	ZVAL_UNDEF(&props$$15);
	ZVAL_UNDEF(&property$$15);
	ZVAL_UNDEF(&_74$$15);
	ZVAL_UNDEF(&_76$$15);
	ZVAL_UNDEF(&_95$$15);
	ZVAL_UNDEF(&_78$$16);
	ZVAL_UNDEF(&_81$$16);
	ZVAL_UNDEF(&_84$$16);
	ZVAL_UNDEF(&_86$$16);
	ZVAL_UNDEF(&_88$$16);
	ZVAL_UNDEF(&_89$$16);
	ZVAL_UNDEF(&_90$$16);
	ZVAL_UNDEF(&_91$$16);
	ZVAL_UNDEF(&_92$$16);
	ZVAL_UNDEF(&_94$$16);
	ZVAL_UNDEF(&_97$$17);
	ZVAL_UNDEF(&_100$$17);
	ZVAL_UNDEF(&_102$$17);
	ZVAL_UNDEF(&_104$$17);
	ZVAL_UNDEF(&_106$$17);
	ZVAL_UNDEF(&_107$$17);
	ZVAL_UNDEF(&_108$$17);
	ZVAL_UNDEF(&_109$$17);
	ZVAL_UNDEF(&_110$$17);
	ZVAL_UNDEF(&_112$$17);
	ZVAL_UNDEF(&_118$$18);
	ZVAL_UNDEF(&_119$$18);
	ZVAL_UNDEF(&_120$$18);
	ZVAL_UNDEF(&_122$$19);
	ZVAL_UNDEF(&_137$$19);
	ZVAL_UNDEF(&_152$$19);
	ZVAL_UNDEF(&_153$$19);
	ZVAL_UNDEF(&_154$$19);
	ZVAL_UNDEF(&_124$$20);
	ZVAL_UNDEF(&_125$$21);
	ZVAL_UNDEF(&_126$$21);
	ZVAL_UNDEF(&_128$$21);
	ZVAL_UNDEF(&_129$$21);
	ZVAL_UNDEF(&_130$$21);
	ZVAL_UNDEF(&_131$$22);
	ZVAL_UNDEF(&_132$$22);
	ZVAL_UNDEF(&_134$$22);
	ZVAL_UNDEF(&_135$$22);
	ZVAL_UNDEF(&_136$$22);
	ZVAL_UNDEF(&_139$$23);
	ZVAL_UNDEF(&_140$$24);
	ZVAL_UNDEF(&_141$$24);
	ZVAL_UNDEF(&_143$$24);
	ZVAL_UNDEF(&_144$$24);
	ZVAL_UNDEF(&_145$$24);
	ZVAL_UNDEF(&_146$$25);
	ZVAL_UNDEF(&_147$$25);
	ZVAL_UNDEF(&_149$$25);
	ZVAL_UNDEF(&_150$$25);
	ZVAL_UNDEF(&_151$$25);
	ZVAL_UNDEF(&_158$$26);
	ZVAL_UNDEF(&_159$$26);
	ZVAL_UNDEF(&_162$$27);
	ZVAL_UNDEF(&_163$$27);
	ZVAL_UNDEF(&_166$$28);
	ZVAL_UNDEF(&_167$$28);
	ZVAL_UNDEF(&_170$$29);
	ZVAL_UNDEF(&_171$$29);
	ZVAL_UNDEF(&_172$$29);
	ZVAL_UNDEF(&_173$$29);
	ZVAL_UNDEF(&_175$$30);
	ZVAL_UNDEF(&_176$$30);
	ZVAL_UNDEF(&_177$$30);
	ZVAL_UNDEF(&_179$$31);
	ZVAL_UNDEF(&_180$$31);
	ZVAL_UNDEF(&_181);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_38$$9);
	ZVAL_UNDEF(&_115$$9);
	ZVAL_UNDEF(&_42$$10);
	ZVAL_UNDEF(&_58$$13);
	ZVAL_UNDEF(&_68$$14);
	ZVAL_UNDEF(&_87$$16);
	ZVAL_UNDEF(&_105$$17);
	ZVAL_UNDEF(&_127$$21);
	ZVAL_UNDEF(&_133$$22);
	ZVAL_UNDEF(&_142$$24);
	ZVAL_UNDEF(&_148$$25);
	ZVAL_UNDEF(&_157$$26);
	ZVAL_UNDEF(&_161$$27);
	ZVAL_UNDEF(&_165$$28);
	ZVAL_UNDEF(&_169$$29);
	ZVAL_UNDEF(&_174$$30);
	ZVAL_UNDEF(&_178$$31);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_164$$28);
	ZVAL_UNDEF(&_168$$29);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("detailed", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("methods", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(variable)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
		Z_PARAM_LONG(tab)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	variable = ZEND_CALL_ARG(execute_data, 1);
	if (ZEND_NUM_ARGS() > 2) {
		tab_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	if (!tab_param) {
		tab = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&space);
	ZVAL_STRING(&space, "  ");
	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	if (!(ZEPHIR_IS_EMPTY(&name_zv))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_VS(&_0$$3, &name_zv, " ");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&output, &_0$$3);
	}
	if (Z_TYPE_P(variable) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_1$$4);
		zephir_create_array(&_1$$4, 2, 0);
		ZEPHIR_INIT_VAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "arr");
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "getStyle", NULL, 0, &_3$$4);
		zephir_check_call_status();
		zephir_array_update_string(&_1$$4, SL(":style"), &_2$$4, PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(&_1$$4, SL(":count"), zephir_fast_count_int(variable));
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "<b style=\":style\">Array</b> (<span style=\":style\">:count</span>) (\n");
		ZEPHIR_CALL_FUNCTION(&_2$$4, "strtr", NULL, 5, &_3$$4, &_1$$4);
		zephir_check_call_status();
		zephir_concat_self(&output, &_2$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (Z_TYPE_P(variable) == IS_STRING) {
			ZEPHIR_INIT_NVAR(&_3$$4);
			zephir_string_to_char_array(&_3$$4, variable);
			_4$$4 = &_3$$4;
		} else {
			_4$$4 = variable;
		}
		zephir_is_iterable(_4$$4, 0, "phalcon/Support/Debug/Dump.zep", 249);
		if (Z_TYPE_P(_4$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4$$4), _6$$4, _7$$4, _5$$4)
			{
				ZEPHIR_INIT_NVAR(&key);
				if (_7$$4 != NULL) { 
					ZVAL_STR_COPY(&key, _7$$4);
				} else {
					ZVAL_LONG(&key, _6$$4);
				}
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _5$$4);
				ZVAL_LONG(&_8$$5, tab);
				ZEPHIR_CALL_FUNCTION(&_9$$5, "str_repeat", &_10, 1, &space, &_8$$5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_11$$5);
				zephir_create_array(&_11$$5, 2, 0);
				ZEPHIR_INIT_NVAR(&_13$$5);
				ZVAL_STRING(&_13$$5, "arr");
				ZEPHIR_CALL_METHOD(&_12$$5, this_ptr, "getStyle", NULL, 0, &_13$$5);
				zephir_check_call_status();
				zephir_array_update_string(&_11$$5, SL(":style"), &_12$$5, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_11$$5, SL(":key"), &key, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_13$$5);
				ZVAL_STRING(&_13$$5, "[<span style=\":style\">:key</span>] => ");
				ZEPHIR_CALL_FUNCTION(&_12$$5, "strtr", NULL, 5, &_13$$5, &_11$$5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_14$$5);
				ZEPHIR_CONCAT_VV(&_14$$5, &_9$$5, &_12$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&output, &_14$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				_15$$5 = tab == 1;
				if (_15$$5) {
					_15$$5 = !ZEPHIR_IS_STRING(&name_zv, "");
				}
				_16$$5 = _15$$5;
				if (_16$$5) {
					_16$$5 = !(Z_TYPE_P(&key) == IS_LONG);
				}
				_17$$5 = _16$$5;
				if (_17$$5) {
					_18$$5 = ZEPHIR_IS_EQUAL(&name_zv, &key);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					_17$$5 = _18$$5;
				}
				if (_17$$5) {
					continue;
				}
				ZEPHIR_INIT_NVAR(&_13$$5);
				ZVAL_STRING(&_13$$5, "");
				ZVAL_LONG(&_8$$5, (tab + 1));
				ZEPHIR_CALL_METHOD(&_19$$5, this_ptr, "output", &_20, 0, &value, &_13$$5, &_8$$5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_21$$5);
				ZEPHIR_CONCAT_VS(&_21$$5, &_19$$5, "\n");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_concat_self(&output, &_21$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _4$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_23$$4 = 1;
			while (1) {
				if (_23$$4) {
					_23$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _4$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_22$$4, _4$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_22$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&key, _4$$4, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&value, _4$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZVAL_LONG(&_24$$7, tab);
					ZEPHIR_CALL_FUNCTION(&_25$$7, "str_repeat", &_10, 1, &space, &_24$$7);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_create_array(&_26$$7, 2, 0);
					ZEPHIR_INIT_NVAR(&_28$$7);
					ZVAL_STRING(&_28$$7, "arr");
					ZEPHIR_CALL_METHOD(&_27$$7, this_ptr, "getStyle", NULL, 0, &_28$$7);
					zephir_check_call_status();
					zephir_array_update_string(&_26$$7, SL(":style"), &_27$$7, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_26$$7, SL(":key"), &key, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(&_28$$7);
					ZVAL_STRING(&_28$$7, "[<span style=\":style\">:key</span>] => ");
					ZEPHIR_CALL_FUNCTION(&_27$$7, "strtr", NULL, 5, &_28$$7, &_26$$7);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_29$$7);
					ZEPHIR_CONCAT_VV(&_29$$7, &_25$$7, &_27$$7);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&output, &_29$$7);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					_30$$7 = tab == 1;
					if (_30$$7) {
						_30$$7 = !ZEPHIR_IS_STRING(&name_zv, "");
					}
					_31$$7 = _30$$7;
					if (_31$$7) {
						_31$$7 = !(Z_TYPE_P(&key) == IS_LONG);
					}
					_32$$7 = _31$$7;
					if (_32$$7) {
						_33$$7 = ZEPHIR_IS_EQUAL(&name_zv, &key);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						_32$$7 = _33$$7;
					}
					if (_32$$7) {
						continue;
					}
					ZEPHIR_INIT_NVAR(&_28$$7);
					ZVAL_STRING(&_28$$7, "");
					ZVAL_LONG(&_24$$7, (tab + 1));
					ZEPHIR_CALL_METHOD(&_34$$7, this_ptr, "output", &_20, 0, &value, &_28$$7, &_24$$7);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_35$$7);
					ZEPHIR_CONCAT_VS(&_35$$7, &_34$$7, "\n");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&output, &_35$$7);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
		ZVAL_LONG(&_36$$4, (tab - 1));
		ZEPHIR_CALL_FUNCTION(&_37$$4, "str_repeat", &_10, 1, &space, &_36$$4);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VVS(return_value, &output, &_37$$4, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (Z_TYPE_P(variable) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_38$$9);
		zephir_create_array(&_38$$9, 2, 0);
		ZEPHIR_INIT_VAR(&_40$$9);
		ZVAL_STRING(&_40$$9, "obj");
		ZEPHIR_CALL_METHOD(&_39$$9, this_ptr, "getStyle", NULL, 0, &_40$$9);
		zephir_check_call_status();
		zephir_array_update_string(&_38$$9, SL(":style"), &_39$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_40$$9);
		zephir_get_class(&_40$$9, variable, 0);
		zephir_array_update_string(&_38$$9, SL(":class"), &_40$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_40$$9);
		ZVAL_STRING(&_40$$9, "<b style=\":style\">Object</b> :class");
		ZEPHIR_CALL_FUNCTION(&_39$$9, "strtr", NULL, 5, &_40$$9, &_38$$9);
		zephir_check_call_status();
		zephir_concat_self(&output, &_39$$9);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_FUNCTION(&_41$$9, "get_parent_class", NULL, 0, variable);
		zephir_check_call_status();
		if (zephir_is_true(&_41$$9)) {
			ZEPHIR_INIT_VAR(&_42$$10);
			zephir_create_array(&_42$$10, 2, 0);
			ZEPHIR_INIT_VAR(&_44$$10);
			ZVAL_STRING(&_44$$10, "obj");
			ZEPHIR_CALL_METHOD(&_43$$10, this_ptr, "getStyle", NULL, 0, &_44$$10);
			zephir_check_call_status();
			zephir_array_update_string(&_42$$10, SL(":style"), &_43$$10, PH_COPY | PH_SEPARATE);
			ZEPHIR_CALL_FUNCTION(&_43$$10, "get_parent_class", NULL, 0, variable);
			zephir_check_call_status();
			zephir_array_update_string(&_42$$10, SL(":parent"), &_43$$10, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_44$$10);
			ZVAL_STRING(&_44$$10, " <b style=\":style\">extends</b> :parent");
			ZEPHIR_CALL_FUNCTION(&_43$$10, "strtr", NULL, 5, &_44$$10, &_42$$10);
			zephir_check_call_status();
			zephir_concat_self(&output, &_43$$10);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_concat_self_str(&output, SL(" (\n"));
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (zephir_instance_of_ev(variable, phalcon_di_diinterface_ce)) {
			ZVAL_LONG(&_47$$11, tab);
			ZEPHIR_CALL_FUNCTION(&_48$$11, "str_repeat", &_10, 1, &space, &_47$$11);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_49$$11);
			ZEPHIR_CONCAT_VS(&_49$$11, &_48$$11, "[skipped]\n");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&output, &_49$$11);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_read_property_cached(&_45$$9, this_ptr, _zephir_prop_0, 995, PH_NOISY_CC | PH_READONLY);
			_46$$9 = !zephir_is_true(&_45$$9);
			if (!(_46$$9)) {
				_46$$9 = zephir_is_instance_of(variable, SL("stdClass"));
			}
			if (_46$$9) {
				ZEPHIR_CALL_FUNCTION(&_50$$12, "get_object_vars", NULL, 467, variable);
				zephir_check_call_status();
				if (Z_TYPE_P(&_50$$12) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_52$$12);
					zephir_string_to_char_array(&_52$$12, &_50$$12);
					_51$$12 = &_52$$12;
				} else {
					_51$$12 = &_50$$12;
				}
				zephir_is_iterable(_51$$12, 0, "phalcon/Support/Debug/Dump.zep", 285);
				if (Z_TYPE_P(_51$$12) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_51$$12), _54$$12, _55$$12, _53$$12)
					{
						ZEPHIR_INIT_NVAR(&key);
						if (_55$$12 != NULL) { 
							ZVAL_STR_COPY(&key, _55$$12);
						} else {
							ZVAL_LONG(&key, _54$$12);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _53$$12);
						ZVAL_LONG(&_56$$13, tab);
						ZEPHIR_CALL_FUNCTION(&_57$$13, "str_repeat", &_10, 1, &space, &_56$$13);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_58$$13);
						zephir_create_array(&_58$$13, 3, 0);
						ZEPHIR_INIT_NVAR(&_60$$13);
						ZVAL_STRING(&_60$$13, "obj");
						ZEPHIR_CALL_METHOD(&_59$$13, this_ptr, "getStyle", NULL, 0, &_60$$13);
						zephir_check_call_status();
						zephir_array_update_string(&_58$$13, SL(":style"), &_59$$13, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_58$$13, SL(":key"), &key, PH_COPY | PH_SEPARATE);
						add_assoc_stringl_ex(&_58$$13, SL(":type"), SL("public"));
						ZEPHIR_INIT_NVAR(&_60$$13);
						ZVAL_STRING(&_60$$13, "-><span style=\":style\">:key</span> (<span style=\":style\">:type</span>) = ");
						ZEPHIR_CALL_FUNCTION(&_59$$13, "strtr", NULL, 5, &_60$$13, &_58$$13);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_61$$13);
						ZEPHIR_CONCAT_VV(&_61$$13, &_57$$13, &_59$$13);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&output, &_61$$13);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_INIT_NVAR(&_60$$13);
						ZVAL_STRING(&_60$$13, "");
						ZVAL_LONG(&_56$$13, (tab + 1));
						ZEPHIR_CALL_METHOD(&_62$$13, this_ptr, "output", &_20, 0, &value, &_60$$13, &_56$$13);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_63$$13);
						ZEPHIR_CONCAT_VS(&_63$$13, &_62$$13, "\n");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&output, &_63$$13);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _51$$12, "rewind", NULL, 0);
					zephir_check_call_status();
					_65$$12 = 1;
					while (1) {
						if (_65$$12) {
							_65$$12 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _51$$12, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_64$$12, _51$$12, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_64$$12)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&key, _51$$12, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, _51$$12, "current", NULL, 0);
						zephir_check_call_status();
							ZVAL_LONG(&_66$$14, tab);
							ZEPHIR_CALL_FUNCTION(&_67$$14, "str_repeat", &_10, 1, &space, &_66$$14);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_68$$14);
							zephir_create_array(&_68$$14, 3, 0);
							ZEPHIR_INIT_NVAR(&_70$$14);
							ZVAL_STRING(&_70$$14, "obj");
							ZEPHIR_CALL_METHOD(&_69$$14, this_ptr, "getStyle", NULL, 0, &_70$$14);
							zephir_check_call_status();
							zephir_array_update_string(&_68$$14, SL(":style"), &_69$$14, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_68$$14, SL(":key"), &key, PH_COPY | PH_SEPARATE);
							add_assoc_stringl_ex(&_68$$14, SL(":type"), SL("public"));
							ZEPHIR_INIT_NVAR(&_70$$14);
							ZVAL_STRING(&_70$$14, "-><span style=\":style\">:key</span> (<span style=\":style\">:type</span>) = ");
							ZEPHIR_CALL_FUNCTION(&_69$$14, "strtr", NULL, 5, &_70$$14, &_68$$14);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_71$$14);
							ZEPHIR_CONCAT_VV(&_71$$14, &_67$$14, &_69$$14);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&output, &_71$$14);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_INIT_NVAR(&_70$$14);
							ZVAL_STRING(&_70$$14, "");
							ZVAL_LONG(&_66$$14, (tab + 1));
							ZEPHIR_CALL_METHOD(&_72$$14, this_ptr, "output", &_20, 0, &value, &_70$$14, &_66$$14);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_73$$14);
							ZEPHIR_CONCAT_VS(&_73$$14, &_72$$14, "\n");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&output, &_73$$14);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&key);
			} else {
				ZEPHIR_INIT_VAR(&reflect$$15);
				object_init_ex(&reflect$$15, zephir_get_internal_ce(SL("reflectionclass")));
				ZEPHIR_CALL_METHOD(NULL, &reflect$$15, "__construct", NULL, 160, variable);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&reflect$$15, &reflect$$15);
				ZVAL_LONG(&_74$$15, ((1 | 2) | 4));
				ZEPHIR_CALL_METHOD(&props$$15, &reflect$$15, "getProperties", NULL, 171, &_74$$15);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&props$$15, &props$$15);
				if (Z_TYPE_P(&props$$15) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_76$$15);
					zephir_string_to_char_array(&_76$$15, &props$$15);
					_75$$15 = &_76$$15;
				} else {
					_75$$15 = &props$$15;
				}
				zephir_is_iterable(_75$$15, 0, "phalcon/Support/Debug/Dump.zep", 315);
				if (Z_TYPE_P(_75$$15) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_75$$15), _77$$15)
					{
						ZEPHIR_INIT_NVAR(&property$$15);
						ZVAL_COPY(&property$$15, _77$$15);
						ZVAL_BOOL(&_78$$16, 1);
						ZEPHIR_CALL_METHOD(NULL, &property$$15, "setAccessible", &_79, 0, &_78$$16);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&key, &property$$15, "getName", &_80, 0);
						zephir_check_call_status();
						_82$$16 = zephir_fetch_class_str_ex(SL("Reflection"), ZEND_FETCH_CLASS_AUTO);
						ZEPHIR_CALL_METHOD(&_84$$16, &property$$15, "getModifiers", &_85, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_CE_STATIC(&_81$$16, _82$$16, "getModifierNames", &_83, 0, &_84$$16);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&type);
						zephir_fast_join_str(&type, SL(" "), &_81$$16);
						ZVAL_LONG(&_78$$16, tab);
						ZEPHIR_CALL_FUNCTION(&_86$$16, "str_repeat", &_10, 1, &space, &_78$$16);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_87$$16);
						zephir_create_array(&_87$$16, 3, 0);
						ZEPHIR_INIT_NVAR(&_89$$16);
						ZVAL_STRING(&_89$$16, "obj");
						ZEPHIR_CALL_METHOD(&_88$$16, this_ptr, "getStyle", NULL, 0, &_89$$16);
						zephir_check_call_status();
						zephir_array_update_string(&_87$$16, SL(":style"), &_88$$16, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_87$$16, SL(":key"), &key, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_87$$16, SL(":type"), &type, PH_COPY | PH_SEPARATE);
						ZEPHIR_INIT_NVAR(&_89$$16);
						ZVAL_STRING(&_89$$16, "-><span style=\":style\">:key</span> (<span style=\":style\">:type</span>) = ");
						ZEPHIR_CALL_FUNCTION(&_88$$16, "strtr", NULL, 5, &_89$$16, &_87$$16);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_90$$16);
						ZEPHIR_CONCAT_VV(&_90$$16, &_86$$16, &_88$$16);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&output, &_90$$16);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&_92$$16, &property$$15, "getValue", &_93, 0, variable);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_89$$16);
						ZVAL_STRING(&_89$$16, "");
						ZVAL_LONG(&_78$$16, (tab + 1));
						ZEPHIR_CALL_METHOD(&_91$$16, this_ptr, "output", &_20, 0, &_92$$16, &_89$$16, &_78$$16);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_94$$16);
						ZEPHIR_CONCAT_VS(&_94$$16, &_91$$16, "\n");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&output, &_94$$16);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _75$$15, "rewind", NULL, 0);
					zephir_check_call_status();
					_96$$15 = 1;
					while (1) {
						if (_96$$15) {
							_96$$15 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _75$$15, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_95$$15, _75$$15, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_95$$15)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&property$$15, _75$$15, "current", NULL, 0);
						zephir_check_call_status();
							ZVAL_BOOL(&_97$$17, 1);
							ZEPHIR_CALL_METHOD(NULL, &property$$15, "setAccessible", &_98, 0, &_97$$17);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&key, &property$$15, "getName", &_99, 0);
							zephir_check_call_status();
							_101$$17 = zephir_fetch_class_str_ex(SL("Reflection"), ZEND_FETCH_CLASS_AUTO);
							ZEPHIR_CALL_METHOD(&_102$$17, &property$$15, "getModifiers", &_103, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_CE_STATIC(&_100$$17, _101$$17, "getModifierNames", &_83, 0, &_102$$17);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&type);
							zephir_fast_join_str(&type, SL(" "), &_100$$17);
							ZVAL_LONG(&_97$$17, tab);
							ZEPHIR_CALL_FUNCTION(&_104$$17, "str_repeat", &_10, 1, &space, &_97$$17);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_105$$17);
							zephir_create_array(&_105$$17, 3, 0);
							ZEPHIR_INIT_NVAR(&_107$$17);
							ZVAL_STRING(&_107$$17, "obj");
							ZEPHIR_CALL_METHOD(&_106$$17, this_ptr, "getStyle", NULL, 0, &_107$$17);
							zephir_check_call_status();
							zephir_array_update_string(&_105$$17, SL(":style"), &_106$$17, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_105$$17, SL(":key"), &key, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_105$$17, SL(":type"), &type, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_107$$17);
							ZVAL_STRING(&_107$$17, "-><span style=\":style\">:key</span> (<span style=\":style\">:type</span>) = ");
							ZEPHIR_CALL_FUNCTION(&_106$$17, "strtr", NULL, 5, &_107$$17, &_105$$17);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_108$$17);
							ZEPHIR_CONCAT_VV(&_108$$17, &_104$$17, &_106$$17);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&output, &_108$$17);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(&_110$$17, &property$$15, "getValue", &_111, 0, variable);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_107$$17);
							ZVAL_STRING(&_107$$17, "");
							ZVAL_LONG(&_97$$17, (tab + 1));
							ZEPHIR_CALL_METHOD(&_109$$17, this_ptr, "output", &_20, 0, &_110$$17, &_107$$17, &_97$$17);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_112$$17);
							ZEPHIR_CONCAT_VS(&_112$$17, &_109$$17, "\n");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&output, &_112$$17);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
					}
				}
				ZEPHIR_INIT_NVAR(&property$$15);
			}
		}
		ZEPHIR_CALL_FUNCTION(&attr, "get_class_methods", NULL, 0, variable);
		zephir_check_call_status();
		ZVAL_LONG(&_113$$9, tab);
		ZEPHIR_CALL_FUNCTION(&_114$$9, "str_repeat", &_10, 1, &space, &_113$$9);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_115$$9);
		zephir_create_array(&_115$$9, 3, 0);
		ZEPHIR_INIT_NVAR(&_40$$9);
		ZVAL_STRING(&_40$$9, "obj");
		ZEPHIR_CALL_METHOD(&_116$$9, this_ptr, "getStyle", NULL, 0, &_40$$9);
		zephir_check_call_status();
		zephir_array_update_string(&_115$$9, SL(":style"), &_116$$9, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_40$$9);
		zephir_get_class(&_40$$9, variable, 0);
		zephir_array_update_string(&_115$$9, SL(":class"), &_40$$9, PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(&_115$$9, SL(":count"), zephir_fast_count_int(&attr));
		ZEPHIR_INIT_NVAR(&_40$$9);
		ZVAL_STRING(&_40$$9, ":class <b style=\":style\">methods</b>: (<span style=\":style\">:count</span>) (\n");
		ZEPHIR_CALL_FUNCTION(&_116$$9, "strtr", NULL, 5, &_40$$9, &_115$$9);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_117$$9);
		ZEPHIR_CONCAT_VV(&_117$$9, &_114$$9, &_116$$9);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_concat_self(&output, &_117$$9);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_NVAR(&_40$$9);
		zephir_get_class(&_40$$9, variable, 0);
		zephir_read_property_cached(&_113$$9, this_ptr, _zephir_prop_1, 997, PH_NOISY_CC | PH_READONLY);
		if (zephir_fast_in_array(&_40$$9, &_113$$9)) {
			ZVAL_LONG(&_118$$18, tab);
			ZEPHIR_CALL_FUNCTION(&_119$$18, "str_repeat", &_10, 1, &space, &_118$$18);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_120$$18);
			ZEPHIR_CONCAT_VS(&_120$$18, &_119$$18, "[already listed]\n");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&output, &_120$$18);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			if (Z_TYPE_P(&attr) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_122$$19);
				zephir_string_to_char_array(&_122$$19, &attr);
				_121$$19 = &_122$$19;
			} else {
				_121$$19 = &attr;
			}
			zephir_is_iterable(_121$$19, 0, "phalcon/Support/Debug/Dump.zep", 345);
			if (Z_TYPE_P(_121$$19) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_121$$19), _123$$19)
				{
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _123$$19);
					ZEPHIR_INIT_NVAR(&_124$$20);
					zephir_get_class(&_124$$20, variable, 0);
					zephir_update_property_array_append(this_ptr, SL("methods"), &_124$$20);
					if (ZEPHIR_IS_STRING(&value, "__construct")) {
						ZVAL_LONG(&_125$$21, (tab + 1));
						ZEPHIR_CALL_FUNCTION(&_126$$21, "str_repeat", &_10, 1, &space, &_125$$21);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_127$$21);
						zephir_create_array(&_127$$21, 2, 0);
						ZEPHIR_INIT_NVAR(&_129$$21);
						ZVAL_STRING(&_129$$21, "obj");
						ZEPHIR_CALL_METHOD(&_128$$21, this_ptr, "getStyle", NULL, 0, &_129$$21);
						zephir_check_call_status();
						zephir_array_update_string(&_127$$21, SL(":style"), &_128$$21, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_127$$21, SL(":method"), &value, PH_COPY | PH_SEPARATE);
						ZEPHIR_INIT_NVAR(&_129$$21);
						ZVAL_STRING(&_129$$21, "-><span style=\":style\">:method</span>(); [<b style=\":style\">constructor</b>]\n");
						ZEPHIR_CALL_FUNCTION(&_128$$21, "strtr", NULL, 5, &_129$$21, &_127$$21);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_130$$21);
						ZEPHIR_CONCAT_VV(&_130$$21, &_126$$21, &_128$$21);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&output, &_130$$21);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZVAL_LONG(&_131$$22, (tab + 1));
						ZEPHIR_CALL_FUNCTION(&_132$$22, "str_repeat", &_10, 1, &space, &_131$$22);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_133$$22);
						zephir_create_array(&_133$$22, 2, 0);
						ZEPHIR_INIT_NVAR(&_135$$22);
						ZVAL_STRING(&_135$$22, "obj");
						ZEPHIR_CALL_METHOD(&_134$$22, this_ptr, "getStyle", NULL, 0, &_135$$22);
						zephir_check_call_status();
						zephir_array_update_string(&_133$$22, SL(":style"), &_134$$22, PH_COPY | PH_SEPARATE);
						zephir_array_update_string(&_133$$22, SL(":method"), &value, PH_COPY | PH_SEPARATE);
						ZEPHIR_INIT_NVAR(&_135$$22);
						ZVAL_STRING(&_135$$22, "-><span style=\":style\">:method</span>();\n");
						ZEPHIR_CALL_FUNCTION(&_134$$22, "strtr", NULL, 5, &_135$$22, &_133$$22);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_136$$22);
						ZEPHIR_CONCAT_VV(&_136$$22, &_132$$22, &_134$$22);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&output, &_136$$22);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _121$$19, "rewind", NULL, 0);
				zephir_check_call_status();
				_138$$19 = 1;
				while (1) {
					if (_138$$19) {
						_138$$19 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _121$$19, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_137$$19, _121$$19, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_137$$19)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&value, _121$$19, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_139$$23);
						zephir_get_class(&_139$$23, variable, 0);
						zephir_update_property_array_append(this_ptr, SL("methods"), &_139$$23);
						if (ZEPHIR_IS_STRING(&value, "__construct")) {
							ZVAL_LONG(&_140$$24, (tab + 1));
							ZEPHIR_CALL_FUNCTION(&_141$$24, "str_repeat", &_10, 1, &space, &_140$$24);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_142$$24);
							zephir_create_array(&_142$$24, 2, 0);
							ZEPHIR_INIT_NVAR(&_144$$24);
							ZVAL_STRING(&_144$$24, "obj");
							ZEPHIR_CALL_METHOD(&_143$$24, this_ptr, "getStyle", NULL, 0, &_144$$24);
							zephir_check_call_status();
							zephir_array_update_string(&_142$$24, SL(":style"), &_143$$24, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_142$$24, SL(":method"), &value, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_144$$24);
							ZVAL_STRING(&_144$$24, "-><span style=\":style\">:method</span>(); [<b style=\":style\">constructor</b>]\n");
							ZEPHIR_CALL_FUNCTION(&_143$$24, "strtr", NULL, 5, &_144$$24, &_142$$24);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_145$$24);
							ZEPHIR_CONCAT_VV(&_145$$24, &_141$$24, &_143$$24);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&output, &_145$$24);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZVAL_LONG(&_146$$25, (tab + 1));
							ZEPHIR_CALL_FUNCTION(&_147$$25, "str_repeat", &_10, 1, &space, &_146$$25);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_148$$25);
							zephir_create_array(&_148$$25, 2, 0);
							ZEPHIR_INIT_NVAR(&_150$$25);
							ZVAL_STRING(&_150$$25, "obj");
							ZEPHIR_CALL_METHOD(&_149$$25, this_ptr, "getStyle", NULL, 0, &_150$$25);
							zephir_check_call_status();
							zephir_array_update_string(&_148$$25, SL(":style"), &_149$$25, PH_COPY | PH_SEPARATE);
							zephir_array_update_string(&_148$$25, SL(":method"), &value, PH_COPY | PH_SEPARATE);
							ZEPHIR_INIT_NVAR(&_150$$25);
							ZVAL_STRING(&_150$$25, "-><span style=\":style\">:method</span>();\n");
							ZEPHIR_CALL_FUNCTION(&_149$$25, "strtr", NULL, 5, &_150$$25, &_148$$25);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_151$$25);
							ZEPHIR_CONCAT_VV(&_151$$25, &_147$$25, &_149$$25);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_concat_self(&output, &_151$$25);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_LONG(&_152$$19, tab);
			ZEPHIR_CALL_FUNCTION(&_153$$19, "str_repeat", &_10, 1, &space, &_152$$19);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_154$$19);
			ZEPHIR_CONCAT_VS(&_154$$19, &_153$$19, ")\n");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&output, &_154$$19);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZVAL_LONG(&_155$$9, (tab - 1));
		ZEPHIR_CALL_FUNCTION(&_156$$9, "str_repeat", &_10, 1, &space, &_155$$9);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VVS(return_value, &output, &_156$$9, ")");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (Z_TYPE_P(variable) == IS_LONG) {
		ZEPHIR_INIT_VAR(&_157$$26);
		zephir_create_array(&_157$$26, 2, 0);
		ZEPHIR_INIT_VAR(&_159$$26);
		ZVAL_STRING(&_159$$26, "int");
		ZEPHIR_CALL_METHOD(&_158$$26, this_ptr, "getStyle", NULL, 0, &_159$$26);
		zephir_check_call_status();
		zephir_array_update_string(&_157$$26, SL(":style"), &_158$$26, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_157$$26, SL(":var"), variable, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_159$$26);
		ZVAL_STRING(&_159$$26, "<b style=\":style\">Integer</b> (<span style=\":style\">:var</span>)");
		ZEPHIR_CALL_FUNCTION(&_158$$26, "strtr", NULL, 5, &_159$$26, &_157$$26);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VV(return_value, &output, &_158$$26);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_CALL_FUNCTION(&_160, "is_float", NULL, 247, variable);
	zephir_check_call_status();
	if (zephir_is_true(&_160)) {
		ZEPHIR_INIT_VAR(&_161$$27);
		zephir_create_array(&_161$$27, 2, 0);
		ZEPHIR_INIT_VAR(&_163$$27);
		ZVAL_STRING(&_163$$27, "float");
		ZEPHIR_CALL_METHOD(&_162$$27, this_ptr, "getStyle", NULL, 0, &_163$$27);
		zephir_check_call_status();
		zephir_array_update_string(&_161$$27, SL(":style"), &_162$$27, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_161$$27, SL(":var"), variable, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_163$$27);
		ZVAL_STRING(&_163$$27, "<b style=\":style\">Float</b> (<span style=\":style\">:var</span>)");
		ZEPHIR_CALL_FUNCTION(&_162$$27, "strtr", NULL, 5, &_163$$27, &_161$$27);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VV(return_value, &output, &_162$$27);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (zephir_is_numeric(variable)) {
		ZEPHIR_INIT_VAR(&_164$$28);
		ZEPHIR_CONCAT_SS(&_164$$28, "<b style=\":style\">Numeric String</b> ", "(<span style=\":style\">:length</span>) \"<span style=\":style\">:var</span>\"");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_165$$28);
		zephir_create_array(&_165$$28, 3, 0);
		ZEPHIR_INIT_VAR(&_167$$28);
		ZVAL_STRING(&_167$$28, "num");
		ZEPHIR_CALL_METHOD(&_166$$28, this_ptr, "getStyle", NULL, 0, &_167$$28);
		zephir_check_call_status();
		zephir_array_update_string(&_165$$28, SL(":style"), &_166$$28, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_FUNCTION(&_166$$28, "mb_strlen", NULL, 279, variable);
		zephir_check_call_status();
		zephir_array_update_string(&_165$$28, SL(":length"), &_166$$28, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_165$$28, SL(":var"), variable, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_FUNCTION(&_166$$28, "strtr", NULL, 5, &_164$$28, &_165$$28);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VV(return_value, &output, &_166$$28);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (Z_TYPE_P(variable) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_168$$29);
		ZEPHIR_CONCAT_SS(&_168$$29, "<b style=\":style\">String</b> ", "(<span style=\":style\">:length</span>) \"<span style=\":style\">:var</span>\"");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_169$$29);
		zephir_create_array(&_169$$29, 3, 0);
		ZEPHIR_INIT_VAR(&_171$$29);
		ZVAL_STRING(&_171$$29, "str");
		ZEPHIR_CALL_METHOD(&_170$$29, this_ptr, "getStyle", NULL, 0, &_171$$29);
		zephir_check_call_status();
		zephir_array_update_string(&_169$$29, SL(":style"), &_170$$29, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_FUNCTION(&_170$$29, "mb_strlen", NULL, 279, variable);
		zephir_check_call_status();
		zephir_array_update_string(&_169$$29, SL(":length"), &_170$$29, PH_COPY | PH_SEPARATE);
		ZVAL_LONG(&_172$$29, 4);
		ZEPHIR_INIT_NVAR(&_171$$29);
		ZVAL_STRING(&_171$$29, "utf-8");
		ZEPHIR_CALL_FUNCTION(&_170$$29, "htmlentities", NULL, 0, variable, &_172$$29, &_171$$29);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_173$$29, "nl2br", NULL, 0, &_170$$29);
		zephir_check_call_status();
		zephir_array_update_string(&_169$$29, SL(":var"), &_173$$29, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_FUNCTION(&_173$$29, "strtr", NULL, 5, &_168$$29, &_169$$29);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VV(return_value, &output, &_173$$29);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if ((Z_TYPE_P(variable) == IS_TRUE || Z_TYPE_P(variable) == IS_FALSE)) {
		ZEPHIR_INIT_VAR(&_174$$30);
		zephir_create_array(&_174$$30, 2, 0);
		ZEPHIR_INIT_VAR(&_176$$30);
		ZVAL_STRING(&_176$$30, "bool");
		ZEPHIR_CALL_METHOD(&_175$$30, this_ptr, "getStyle", NULL, 0, &_176$$30);
		zephir_check_call_status();
		zephir_array_update_string(&_174$$30, SL(":style"), &_175$$30, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_177$$30);
		if (zephir_is_true(variable)) {
			ZEPHIR_INIT_NVAR(&_177$$30);
			ZVAL_STRING(&_177$$30, "TRUE");
		} else {
			ZEPHIR_INIT_NVAR(&_177$$30);
			ZVAL_STRING(&_177$$30, "FALSE");
		}
		zephir_array_update_string(&_174$$30, SL(":var"), &_177$$30, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_176$$30);
		ZVAL_STRING(&_176$$30, "<b style=\":style\">Boolean</b> (<span style=\":style\">:var</span>)");
		ZEPHIR_CALL_FUNCTION(&_175$$30, "strtr", NULL, 5, &_176$$30, &_174$$30);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VV(return_value, &output, &_175$$30);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	if (Z_TYPE_P(variable) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_178$$31);
		zephir_create_array(&_178$$31, 1, 0);
		ZEPHIR_INIT_VAR(&_180$$31);
		ZVAL_STRING(&_180$$31, "null");
		ZEPHIR_CALL_METHOD(&_179$$31, this_ptr, "getStyle", NULL, 0, &_180$$31);
		zephir_check_call_status();
		zephir_array_update_string(&_178$$31, SL(":style"), &_179$$31, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_180$$31);
		ZVAL_STRING(&_180$$31, "<b style=\":style\">NULL</b>");
		ZEPHIR_CALL_FUNCTION(&_179$$31, "strtr", NULL, 5, &_180$$31, &_178$$31);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VV(return_value, &output, &_179$$31);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_181);
	zephir_create_array(&_181, 2, 0);
	ZEPHIR_INIT_VAR(&_183);
	ZVAL_STRING(&_183, "other");
	ZEPHIR_CALL_METHOD(&_182, this_ptr, "getStyle", NULL, 0, &_183);
	zephir_check_call_status();
	zephir_array_update_string(&_181, SL(":style"), &_182, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_181, SL(":var"), variable, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_183);
	ZVAL_STRING(&_183, "(<span style=\":style\">:var</span>)");
	ZEPHIR_CALL_FUNCTION(&_182, "strtr", NULL, 5, &_183, &_181);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &output, &_182);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

zend_object *zephir_init_properties_Phalcon_Support_Debug_Dump(zend_class_entry *class_type)
{
		zval _0, _2, _1$$3, _3$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("styles"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("styles"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("methods"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("methods"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

