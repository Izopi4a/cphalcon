
#ifdef HAVE_CONFIG_H
#include "../../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../../php_ext.h"
#include "../../../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * A template function that runs at render time: {{ name(args) }}
 *
 *```php
 * $volt->addFunction(new VoltFunction("name", $callable, ["safe" => false]));
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Runtime_VoltFunction)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime, VoltFunction, phalcon, mvc_view_engine_volt_runtime_voltfunction, phalcon_mvc_view_engine_volt_runtime_voltcallable_ce, NULL, ZEND_ACC_FINAL_CLASS);

	return SUCCESS;
}

