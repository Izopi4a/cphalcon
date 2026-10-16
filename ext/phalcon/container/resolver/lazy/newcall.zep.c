
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
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
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
ZEPHIR_INIT_CLASS(Phalcon_Container_Resolver_Lazy_NewCall)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Container\\Resolver\\Lazy, NewCall, phalcon, container_resolver_lazy_newcall, phalcon_container_resolver_lazy_lazy_ce, phalcon_container_resolver_lazy_newcall_method_entry, 0);

	/**
	 * @var string|Lazy
	 */
	zend_declare_property_null(phalcon_container_resolver_lazy_newcall_ce, SL("id"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_container_resolver_lazy_newcall_ce, SL("method"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_container_resolver_lazy_newcall_ce, SL("arguments"), ZEND_ACC_PROTECTED);
	return SUCCESS;
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_NewCall, __construct)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval arguments;
	zend_string *method = NULL;
	zval *id, id_sub, method_zv, *arguments_param = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id_sub);
	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&arguments);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("id", 2, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("method", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("arguments", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(id)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(arguments, arguments_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	id = ZEND_CALL_ARG(execute_data, 1);
	arguments_param = ZEND_CALL_ARG(execute_data, 3);
	ZVAL_STR(&method_zv, method);
	zephir_get_arrval(&arguments, arguments_param);
	_0 = Z_TYPE_P(id) != IS_STRING;
	if (_0) {
		_0 = !((zephir_instance_of_ev(id, phalcon_container_resolver_lazy_lazy_ce)));
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'id' must be string or Lazy", "phalcon/Container/Resolver/Lazy/NewCall.zep", 51);
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 377, id);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 378, &method_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 379, &arguments);
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_NewCall, resolve)
{
	zval _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, resolvedId, resolvedArgs, service, _0, _1, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&resolvedId);
	ZVAL_UNDEF(&resolvedArgs);
	ZVAL_UNDEF(&service);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("id", 2, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("arguments", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("method", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT(container)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &container);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 377, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&resolvedId, this_ptr, "resolveArgument", NULL, 0, container, &_0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 379, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&resolvedArgs, this_ptr, "resolveArguments", NULL, 0, container, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&service, container, "new", NULL, 0, &resolvedId);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 2, 0);
	zephir_array_fast_append(&_2, &service);
	zephir_memory_observe(&_3);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_2, 378, PH_NOISY_CC);
	zephir_array_fast_append(&_2, &_3);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_2, &resolvedArgs);
	zephir_check_call_status();
	RETURN_MM();
}

