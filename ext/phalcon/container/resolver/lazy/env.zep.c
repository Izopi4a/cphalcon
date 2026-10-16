
#ifdef HAVE_CONFIG_H
#include "../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../php_ext.h"
#include "../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 *
 * Implementation of this file has been heavily influenced by CapsulePHP.
 * Additionally, there are implementations from ioc-interop, service-interop
 * and resolver-interop. These have been copied and implemented here since
 * PHP extensions cannot have more than one namespace.
 *
 * @link    https://github.com/capsulephp/di
 * @license https://github.com/capsulephp/di/blob/3.x/LICENSE.md
 *
 * @link    https://github.com/ioc-interop/interface
 * @license https://github.com/ioc-interop/interface/blob/1.x/LICENSE.md
 *
 * @link    https://github.com/service-interop/interface
 * @license https://github.com/service-interop/interface/blob/1.x/LICENSE.md
 *
 * @link    https://github.com/resolver-interop/interface/tree/1.x
 * @license https://github.com/resolver-interop/interface/blob/1.x/LICENSE.md
 */
ZEPHIR_INIT_CLASS(Phalcon_Container_Resolver_Lazy_Env)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Container\\Resolver\\Lazy, Env, phalcon, container_resolver_lazy_env, phalcon_container_resolver_lazy_lazy_ce, phalcon_container_resolver_lazy_env_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_container_resolver_lazy_env_ce, SL("varname"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_container_resolver_lazy_env_ce, SL("vartype"), ZEND_ACC_PROTECTED);
	return SUCCESS;
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_Env, __construct)
{
	zend_bool _0;
	zval varname_zv, *vartype = NULL, vartype_sub, __$null;
	zend_string *varname = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&varname_zv);
	ZVAL_UNDEF(&vartype_sub);
	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("varname", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("vartype", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(varname)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(vartype)
	ZEND_PARSE_PARAMETERS_END();
	if (ZEND_NUM_ARGS() > 1) {
		vartype = ZEND_CALL_ARG(execute_data, 2);
	}
	ZVAL_STR(&varname_zv, varname);
	if (!vartype) {
		vartype = &vartype_sub;
		vartype = &__$null;
	}
	_0 = Z_TYPE_P(vartype) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(vartype) != IS_NULL;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(zend_ce_type_error, "Argument 'vartype' must be string or null", "phalcon/Container/Resolver/Lazy/Env.zep", 48);
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 122, &varname_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 123, vartype);
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_Env, resolve)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT(container)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &container);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getEnv", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "cast", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_Env, cast)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval value_zv, castValue, _0, _1$$3;
	zend_string *value = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_zv);
	ZVAL_UNDEF(&castValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("vartype", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&value_zv);
	ZVAL_STR_COPY(&value_zv, value);
	ZEPHIR_CPY_WRT(&castValue, &value_zv);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 123, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) != IS_NULL) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 123, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_MAKE_REF(&castValue);
		ZEPHIR_CALL_FUNCTION(NULL, "settype", NULL, 8, &castValue, &_1$$3);
		ZEPHIR_UNREF(&castValue);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&castValue);
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_Env, getEnv)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval _ENV, envs, _0, _1, _4, _5, _2$$3, _3$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_ENV);
	ZVAL_UNDEF(&envs);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("varname", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_get_global(&_ENV, SL("_ENV"));

	ZEPHIR_CALL_FUNCTION(&_0, "getenv", NULL, 84);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&envs);
	zephir_fast_array_merge(&envs, &_ENV, &_0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 122, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_key_exists(&envs, &_1))) {
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 122, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_2$$3, phalcon_container_exception_notfound_ce, "envNotDefined", NULL, 0, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "phalcon/Container/Resolver/Lazy/Env.zep", 80);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_memory_observe(&_4);
	zephir_memory_observe(&_5);
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_0, 122, PH_NOISY_CC);
	zephir_array_fetch(&_4, &envs, &_5, PH_NOISY, "phalcon/Container/Resolver/Lazy/Env.zep", 83);
	RETURN_CCTOR(&_4);
}

