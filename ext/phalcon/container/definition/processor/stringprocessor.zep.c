
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
#include "kernel/memory.h"
#include "kernel/fcall.h"


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
ZEPHIR_INIT_CLASS(Phalcon_Container_Definition_Processor_StringProcessor)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Container\\Definition\\Processor, StringProcessor, phalcon, container_definition_processor_stringprocessor, phalcon_container_definition_processor_stringprocessor_method_entry, 0);

	zend_class_implements(phalcon_container_definition_processor_stringprocessor_ce, 1, phalcon_container_definition_processor_processor_ce);
	return SUCCESS;
}

PHP_METHOD(Phalcon_Container_Definition_Processor_StringProcessor, canProcess)
{
	zend_bool _0;
	zval *definition, definition_sub;

	ZVAL_UNDEF(&definition_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(definition)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &definition);
	_0 = Z_TYPE_P(definition) == IS_STRING;
	if (_0) {
		_0 = zephir_class_exists(definition, 1);
	}
	RETURN_BOOL(_0);
}

PHP_METHOD(Phalcon_Container_Definition_Processor_StringProcessor, process)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, *definition, definition_sub, *container, container_sub, def, _0, _1;
	zend_string *name = NULL;

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&definition_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&def);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(name)
		Z_PARAM_ZVAL(definition)
		Z_PARAM_OBJECT(container)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	definition = ZEND_CALL_ARG(execute_data, 2);
	container = ZEND_CALL_ARG(execute_data, 3);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_INIT_VAR(&def);
	object_init_ex(&def, phalcon_container_definition_servicedefinition_ce);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "string");
	ZEPHIR_CALL_METHOD(NULL, &def, "__construct", NULL, 206, &name_zv, &_0, definition);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &def, "setClass", NULL, 213, definition);
	zephir_check_call_status();
	ZVAL_BOOL(&_1, 1);
	ZEPHIR_CALL_METHOD(NULL, &def, "setIsCacheable", NULL, 212, &_1);
	zephir_check_call_status();
	RETURN_CCTOR(&def);
}

