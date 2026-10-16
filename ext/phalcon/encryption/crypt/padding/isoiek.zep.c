
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
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Class IsoIek
 *
 * @package Phalcon\Encryption\Crypt\Padding
 */
ZEPHIR_INIT_CLASS(Phalcon_Encryption_Crypt_Padding_IsoIek)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Encryption\\Crypt\\Padding, IsoIek, phalcon, encryption_crypt_padding_isoiek, phalcon_encryption_crypt_padding_isoiek_method_entry, 0);

	zend_class_implements(phalcon_encryption_crypt_padding_isoiek_ce, 1, phalcon_encryption_crypt_padding_padinterface_ce);
	return SUCCESS;
}

/**
 * @param int $paddingSize
 *
 * @return string
 */
PHP_METHOD(Phalcon_Encryption_Crypt_Padding_IsoIek, pad)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *paddingSize_param = NULL, _0, _1, _2, _3;
	zend_long paddingSize, ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(paddingSize)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &paddingSize_param);
	ZVAL_LONG(&_0, 0x80);
	ZEPHIR_CALL_FUNCTION(&_1, "chr", NULL, 273, &_0);
	zephir_check_call_status();
	ZVAL_LONG(&_0, 0);
	ZEPHIR_CALL_FUNCTION(&_2, "chr", NULL, 273, &_0);
	zephir_check_call_status();
	ZVAL_LONG(&_0, (paddingSize - 1));
	ZEPHIR_CALL_FUNCTION(&_3, "str_repeat", NULL, 1, &_2, &_0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &_1, &_3);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * @param string $input
 * @param int    $blockSize
 *
 * @return int
 */
PHP_METHOD(Phalcon_Encryption_Crypt_Padding_IsoIek, unpad)
{
	zend_bool _2, _7, _10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long blockSize, ZEPHIR_LAST_CALL_STATUS, counter = 0, paddingSize = 0;
	zval input_zv, *blockSize_param = NULL, length, inputArray, _0, _1, _3, _4, _5, _8, _9;
	zend_string *input = NULL;

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&length);
	ZVAL_UNDEF(&inputArray);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(input)
		Z_PARAM_LONG(blockSize)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	blockSize_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	paddingSize = 0;
	ZEPHIR_CALL_FUNCTION(&length, "mb_strlen", NULL, 276, &input_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&inputArray, "str_split", NULL, 96, &input_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, 1);
	ZEPHIR_INIT_VAR(&_1);
	zephir_sub_function(&_1, &length, &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	counter = zephir_get_intval(&_1);
	while (1) {
		_2 = counter > 0;
		if (_2) {
			ZEPHIR_OBS_NVAR(&_3);
			zephir_array_fetch_long(&_3, &inputArray, counter, PH_NOISY, "phalcon/Encryption/Crypt/Padding/IsoIek.zep", 48);
			ZVAL_LONG(&_4, 0);
			ZEPHIR_CALL_FUNCTION(&_5, "chr", &_6, 273, &_4);
			zephir_check_call_status();
			_2 = ZEPHIR_IS_IDENTICAL(&_3, &_5);
		}
		_7 = _2;
		if (_7) {
			_7 = paddingSize < blockSize;
		}
		if (!(_7)) {
			break;
		}
		paddingSize++;
		counter--;
	}
	zephir_memory_observe(&_8);
	zephir_array_fetch_long(&_8, &inputArray, counter, PH_NOISY, "phalcon/Encryption/Crypt/Padding/IsoIek.zep", 55);
	ZVAL_LONG(&_4, 0x80);
	ZEPHIR_CALL_FUNCTION(&_9, "chr", &_6, 273, &_4);
	zephir_check_call_status();
	_10 = ZEPHIR_IS_EQUAL(&_8, &_9);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (_10) {
		paddingSize++;
	} else {
		paddingSize = 0;
	}
	RETURN_MM_LONG(paddingSize);
}

