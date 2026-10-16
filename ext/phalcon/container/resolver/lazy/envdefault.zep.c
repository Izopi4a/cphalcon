
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/memory.h"


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
ZEPHIR_INIT_CLASS(Phalcon_Container_Resolver_Lazy_EnvDefault)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Container\\Resolver\\Lazy, EnvDefault, phalcon, container_resolver_lazy_envdefault, phalcon_container_resolver_lazy_env_ce, phalcon_container_resolver_lazy_envdefault_method_entry, 0);

	/**
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_container_resolver_lazy_envdefault_ce, SL("defaultValue"), ZEND_ACC_PROTECTED);
	return SUCCESS;
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_EnvDefault, __construct)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval varname_zv, *defaultValue, defaultValue_sub, *vartype = NULL, vartype_sub, __$null;
	zend_string *varname = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&varname_zv);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_UNDEF(&vartype_sub);
	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultValue", 12, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(varname)
		Z_PARAM_ZVAL(defaultValue)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(vartype)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	defaultValue = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 2) {
		vartype = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&varname_zv);
	ZVAL_STR_COPY(&varname_zv, varname);
	if (!vartype) {
		vartype = &vartype_sub;
		vartype = &__$null;
	}
	_0 = Z_TYPE_P(vartype) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(vartype) != IS_NULL;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_ce_type_error, "Argument 'vartype' must be string or null", "phalcon/Container/Resolver/Lazy/EnvDefault.zep", 44);
		return;
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_container_resolver_lazy_envdefault_ce, getThis(), "__construct", NULL, 0, &varname_zv, vartype);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 367, defaultValue);
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Container_Resolver_Lazy_EnvDefault, resolve)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, _0, _1;

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT(container)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &container);
	/* try_start_1: */

		ZEPHIR_RETURN_CALL_PARENT(phalcon_container_resolver_lazy_envdefault_ce, getThis(), "resolve", NULL, 0, container);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_0);
		ZVAL_OBJ(&_0, EG(exception));
		Z_ADDREF_P(&_0);
		ZEPHIR_INIT_VAR(&_1);
		if (zephir_instance_of_ev(&_0, phalcon_container_exception_notfound_ce)) {
			zend_clear_exception();
			ZEPHIR_CPY_WRT(&_1, &_0);
			RETURN_MM_MEMBER(getThis(), "defaultValue");
		} else {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
}

