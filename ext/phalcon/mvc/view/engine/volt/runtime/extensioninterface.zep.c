
#ifdef HAVE_CONFIG_H
#include "../../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../../php_ext.h"
#include "../../../../../../ext.h"

#include <Zend/zend_exceptions.h>

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
 * A bundle of runtime functions, filters and tests, registered with
 * Volt::addExtension(). Only names and options are read at compile time; the
 * callables run at render time.
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Runtime_ExtensionInterface)
{
	ZEPHIR_REGISTER_INTERFACE(Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime, ExtensionInterface, phalcon, mvc_view_engine_volt_runtime_extensioninterface, phalcon_mvc_view_engine_volt_runtime_extensioninterface_method_entry);

	return SUCCESS;
}

/**
 * @return VoltFilter[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_ExtensionInterface, getFilters);
/**
 * @return VoltFunction[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_ExtensionInterface, getFunctions);
/**
 * @return VoltTest[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_ExtensionInterface, getTests);
