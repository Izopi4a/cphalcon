
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
ZEPHIR_INIT_CLASS(Phalcon_Container_Definition_DefinitionType)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Container\\Definition, DefinitionType, phalcon, container_definition_definitiontype, NULL, 0);

	/**
	 * @var string
	 */
	zephir_declare_class_constant_string(phalcon_container_definition_definitiontype_ce, SL("DEF_CLOSURE"), "closure");

	/**
	 * @var string
	 */
	zephir_declare_class_constant_string(phalcon_container_definition_definitiontype_ce, SL("DEF_OBJECT"), "object");

	/**
	 * @var string
	 */
	zephir_declare_class_constant_string(phalcon_container_definition_definitiontype_ce, SL("DEF_PARAMETER"), "parameter");

	/**
	 * @var string
	 */
	zephir_declare_class_constant_string(phalcon_container_definition_definitiontype_ce, SL("DEF_STRING"), "string");

	return SUCCESS;
}

