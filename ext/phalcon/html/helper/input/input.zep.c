
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


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Class Input
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Helper_Input_Input)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Html\\Helper\\Input, Input, phalcon, html_helper_input_input, phalcon_html_helper_input_abstractinput_ce, phalcon_html_helper_input_input_method_entry, 0);

	return SUCCESS;
}

/**
 * Sets the type of the input
 *
 * @param string $type
 *
 * @return AbstractInput
 */
PHP_METHOD(Phalcon_Html_Helper_Input_Input, setType)
{
	zval type_zv;
	zend_string *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("type", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&type_zv, type);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 561, &type_zv);
	RETURN_THISW();
}

