
#ifdef HAVE_CONFIG_H
#include "../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../php_ext.h"
#include "../../../../ext.h"

#include <Zend/zend_exceptions.h>

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
ZEPHIR_INIT_CLASS(Phalcon_Container_Interop_Service_Collection)
{
	ZEPHIR_REGISTER_INTERFACE(Phalcon\\Container\\Interop\\Service, Collection, phalcon, container_interop_service_collection, phalcon_container_interop_service_collection_method_entry);

	zend_class_implements(phalcon_container_interop_service_collection_ce, 1, phalcon_container_interop_ioc_ioccontainer_ce);
	return SUCCESS;
}

ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, bind);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, callableGet);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, callableNew);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, extend);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, get);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, getAlias);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, getByTag);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, getDefinition);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, getInstance);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, getParameter);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, getResolver);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, has);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, hasAlias);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, hasDefinition);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, hasInstance);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, hasParameter);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, isAutowireEnabled);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, new);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, newDefinition);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, set);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, setAlias);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, setAutowire);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, setDefinition);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, setInstance);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, setParameter);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, unsetAlias);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, unsetDefinition);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, unsetInstance);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, unsetInstances);
ZEPHIR_DOC_METHOD(Phalcon_Container_Interop_Service_Collection, unsetParameter);
