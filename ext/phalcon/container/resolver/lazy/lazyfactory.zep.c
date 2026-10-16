
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"


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
ZEPHIR_INIT_CLASS(Phalcon_Container_Resolver_Lazy_LazyFactory)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Container\\Resolver\\Lazy, LazyFactory, phalcon, container_resolver_lazy_lazyfactory, phalcon_container_resolver_lazy_lazyfactory_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, arrayValues)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *values_param = NULL;
	zval values;

	ZVAL_UNDEF(&values);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(values, values_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &values_param);
	zephir_get_arrval(&values, values_param);
	object_init_ex(return_value, phalcon_container_resolver_lazy_arrayvalues_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 221, &values);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, call)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callableObject, callableObject_sub;

	ZVAL_UNDEF(&callableObject_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(callableObject)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &callableObject);
	object_init_ex(return_value, phalcon_container_resolver_lazy_call_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 222, callableObject);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, callableGet)
{
	zval id_zv;
	zend_string *id = NULL;

	ZVAL_UNDEF(&id_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(id)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&id_zv, id);
	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Not implemented: requires Zephir \\$this-in-closure support", "phalcon/Container/Resolver/Lazy/LazyFactory.zep", 58);
	return;
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, callableNew)
{
	zval id_zv;
	zend_string *id = NULL;

	ZVAL_UNDEF(&id_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(id)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&id_zv, id);
	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Not implemented: requires Zephir \\$this-in-closure support", "phalcon/Container/Resolver/Lazy/LazyFactory.zep", 63);
	return;
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, csEnv)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, *type = NULL, type_sub, __$null;
	zend_string *name = NULL;

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&type_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		type = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	if (!type) {
		type = &type_sub;
		type = &__$null;
	}
	_0 = Z_TYPE_P(type) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(type) != IS_NULL;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'type' must be string or null", "phalcon/Container/Resolver/Lazy/LazyFactory.zep", 69);
		return;
	}
	object_init_ex(return_value, phalcon_container_resolver_lazy_csenv_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 223, &name_zv, type);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, env)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, *type = NULL, type_sub, __$null;
	zend_string *name = NULL;

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&type_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(name)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		type = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	if (!type) {
		type = &type_sub;
		type = &__$null;
	}
	_0 = Z_TYPE_P(type) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(type) != IS_NULL;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'type' must be string or null", "phalcon/Container/Resolver/Lazy/LazyFactory.zep", 78);
		return;
	}
	object_init_ex(return_value, phalcon_container_resolver_lazy_env_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 223, &name_zv, type);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, envDefault)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, *defaultValue, defaultValue_sub, *type = NULL, type_sub, __$null;
	zend_string *name = NULL;

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_UNDEF(&type_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(defaultValue)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	defaultValue = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		type = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	if (!type) {
		type = &type_sub;
		type = &__$null;
	}
	_0 = Z_TYPE_P(type) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(type) != IS_NULL;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'type' must be string or null", "phalcon/Container/Resolver/Lazy/LazyFactory.zep", 87);
		return;
	}
	object_init_ex(return_value, phalcon_container_resolver_lazy_envdefault_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 224, &name_zv, defaultValue, type);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, functionCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval args;
	zval functionName_zv, *args_param = NULL;
	zend_string *functionName = NULL;

	ZVAL_UNDEF(&functionName_zv);
	ZVAL_UNDEF(&args);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(functionName)
		ZEPHIR_Z_PARAM_ARRAY(args, args_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	args_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&functionName_zv);
	ZVAL_STR_COPY(&functionName_zv, functionName);
	zephir_get_arrval(&args, args_param);
	object_init_ex(return_value, phalcon_container_resolver_lazy_functioncall_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 225, &functionName_zv, &args);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, get)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval id_zv;
	zend_string *id = NULL;

	ZVAL_UNDEF(&id_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&id_zv);
	ZVAL_STR_COPY(&id_zv, id);
	object_init_ex(return_value, phalcon_container_resolver_lazy_get_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 226, &id_zv);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, getCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval args;
	zend_string *method = NULL;
	zval *id, id_sub, method_zv, *args_param = NULL;

	ZVAL_UNDEF(&id_sub);
	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&args);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(id)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(args, args_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	id = ZEND_CALL_ARG(execute_data, 1);
	args_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	zephir_get_arrval(&args, args_param);
	object_init_ex(return_value, phalcon_container_resolver_lazy_getcall_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 227, id, &method_zv, &args);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, newCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval args;
	zend_string *method = NULL;
	zval *id, id_sub, method_zv, *args_param = NULL;

	ZVAL_UNDEF(&id_sub);
	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&args);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(id)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(args, args_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	id = ZEND_CALL_ARG(execute_data, 1);
	args_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	zephir_get_arrval(&args, args_param);
	object_init_ex(return_value, phalcon_container_resolver_lazy_newcall_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 228, id, &method_zv, &args);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, newInstance)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval id_zv;
	zend_string *id = NULL;

	ZVAL_UNDEF(&id_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(id)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&id_zv);
	ZVAL_STR_COPY(&id_zv, id);
	object_init_ex(return_value, phalcon_container_resolver_lazy_newinstance_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 229, &id_zv);
	zephir_check_call_status();
	RETURN_MM();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_LazyFactory, staticCall)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval args;
	zend_string *method = NULL;
	zval *className, className_sub, method_zv, *args_param = NULL;

	ZVAL_UNDEF(&className_sub);
	ZVAL_UNDEF(&method_zv);
	ZVAL_UNDEF(&args);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(className)
		Z_PARAM_STR(method)
		ZEPHIR_Z_PARAM_ARRAY(args, args_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	className = ZEND_CALL_ARG(execute_data, 1);
	args_param = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&method_zv);
	ZVAL_STR_COPY(&method_zv, method);
	zephir_get_arrval(&args, args_param);
	object_init_ex(return_value, phalcon_container_resolver_lazy_staticcall_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 230, className, &method_zv, &args);
	zephir_check_call_status();
	RETURN_MM();
}

