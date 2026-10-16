
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
#include "kernel/object.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Base class for runtime extensions: override what you provide
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Runtime_AbstractExtension)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime, AbstractExtension, phalcon, mvc_view_engine_volt_runtime_abstractextension, phalcon_mvc_view_engine_volt_runtime_abstractextension_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_class_implements(phalcon_mvc_view_engine_volt_runtime_abstractextension_ce, 1, phalcon_mvc_view_engine_volt_runtime_extensioninterface_ce);
	return SUCCESS;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_AbstractExtension, getFilters)
{

	array_init(return_value);
	return;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_AbstractExtension, getFunctions)
{

	array_init(return_value);
	return;
}

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_AbstractExtension, getTests)
{

	array_init(return_value);
	return;
}

