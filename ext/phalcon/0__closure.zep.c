
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(phalcon_0__closure)
{
	ZEPHIR_REGISTER_CLASS(phalcon, 0__closure, phalcon, 0__closure, phalcon_0__closure_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(phalcon_0__closure_ce, SL("serializer"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(phalcon_0__closure_ce, SL("defaultValue"), ZEND_ACC_PUBLIC);
	return SUCCESS;
}

PHP_METHOD(phalcon_0__closure, __invoke)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval serializer, defaultValue, *element, element_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&serializer);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&element_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(element)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&defaultValue);
	zephir_read_property(&defaultValue, this_ptr, SL("defaultValue"), PH_NOISY_CC);
	zephir_memory_observe(&serializer);
	zephir_read_property(&serializer, this_ptr, SL("serializer"), PH_NOISY_CC);
	zephir_fetch_params(1, 1, 0, &element);
	ZEPHIR_CALL_METHOD(NULL, &serializer, "unserialize", NULL, 0, element);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	if (ZEPHIR_IS_FALSE_IDENTICAL(element)) {
		ZEPHIR_CPY_WRT(&_0, &defaultValue);
	} else {
		ZEPHIR_CALL_METHOD(&_0, &serializer, "getData", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&_0);
}

