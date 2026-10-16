
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
#include "kernel/string.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/math.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * All image adapters must use this class
 */
ZEPHIR_INIT_CLASS(Phalcon_Image_Adapter_AbstractAdapter)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Image\\Adapter, AbstractAdapter, phalcon, image_adapter_abstractadapter, phalcon_image_adapter_abstractadapter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("file"), ZEND_ACC_PROTECTED);
	/**
	 * Image height
	 *
	 * @var int
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("height"), ZEND_ACC_PROTECTED);
	/**
	 * @var mixed|null
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("image"), ZEND_ACC_PROTECTED);
	/**
	 * Image mime type
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("mime"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("realpath"), ZEND_ACC_PROTECTED);
	/**
	 * Image type
	 *
	 * Driver dependent
	 *
	 * @var int
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("type"), ZEND_ACC_PROTECTED);
	/**
	 * Image width
	 *
	 * @var int
	 */
	zend_declare_property_null(phalcon_image_adapter_abstractadapter_ce, SL("width"), ZEND_ACC_PROTECTED);
	zend_class_implements(phalcon_image_adapter_abstractadapter_ce, 1, phalcon_image_adapter_adapterinterface_ce);
	return SUCCESS;
}

/**
 * Set the background color of an image
 *
 * @param string $color
 * @param int    $opacity
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, background)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long opacity, ZEPHIR_LAST_CALL_STATUS;
	zval *color_param = NULL, *opacity_param = NULL, colors, _1, _2, _3, _9, _10, _11, _12, _13, _14, _4$$3, _5$$3, _6$$4, _7$$4, _8$$4;
	zval color;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&color);
	ZVAL_UNDEF(&colors);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(color_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(opacity)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &color_param, &opacity_param);
	zephir_get_strval(&color, color_param);
	if (!opacity_param) {
		opacity = 100;
	} else {
		}
	_0 = zephir_fast_strlen_ev(&color) > 1;
	if (_0) {
		ZVAL_LONG(&_1, 0);
		ZVAL_LONG(&_2, 1);
		ZEPHIR_INIT_VAR(&_3);
		zephir_substr(&_3, &color, 0 , 1 , 0);
		_0 = ZEPHIR_IS_STRING_IDENTICAL(&_3, "#");
	}
	if (_0) {
		ZVAL_LONG(&_4$$3, 1);
		ZEPHIR_INIT_VAR(&_5$$3);
		zephir_substr(&_5$$3, &color, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_get_strval(&color, &_5$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (zephir_fast_strlen_ev(&color) == 3) {
		ZEPHIR_INIT_VAR(&_6$$4);
		ZVAL_STRING(&_6$$4, "/./");
		ZEPHIR_INIT_VAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "$0$0");
		ZEPHIR_CALL_FUNCTION(&_8$$4, "preg_replace", NULL, 40, &_6$$4, &_7$$4, &color);
		zephir_check_call_status();
		zephir_get_strval(&color, &_8$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZVAL_LONG(&_9, 2);
	ZEPHIR_CALL_FUNCTION(&_10, "str_split", NULL, 96, &color, &_9);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_11);
	ZVAL_STRING(&_11, "hexdec");
	ZEPHIR_CALL_FUNCTION(&colors, "array_map", NULL, 89, &_11, &_10);
	zephir_check_call_status();
	zephir_memory_observe(&_12);
	zephir_array_fetch_long(&_12, &colors, 0, PH_NOISY, "phalcon/Image/Adapter/AbstractAdapter.zep", 96);
	zephir_memory_observe(&_13);
	zephir_array_fetch_long(&_13, &colors, 1, PH_NOISY, "phalcon/Image/Adapter/AbstractAdapter.zep", 96);
	zephir_memory_observe(&_14);
	zephir_array_fetch_long(&_14, &colors, 2, PH_NOISY, "phalcon/Image/Adapter/AbstractAdapter.zep", 96);
	ZVAL_LONG(&_9, opacity);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processBackground", NULL, 0, &_12, &_13, &_14, &_9);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Blur image
 *
 * @param int $radius
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, blur)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *radius_param = NULL, _0, _1, _2;
	zend_long radius, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(radius)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &radius_param);
	ZVAL_LONG(&_1, radius);
	ZVAL_LONG(&_2, 1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "checkHighLow", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	radius = zephir_get_intval(&_0);
	ZVAL_LONG(&_1, radius);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processBlur", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Crop an image to the given size
 *
 * @param int      $width
 * @param int      $height
 * @param int|null $offsetX
 * @param int|null $offsetY
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, crop)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *width_param = NULL, *height_param = NULL, *offsetX_param = NULL, *offsetY_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4$$4, _5$$4, _6$$4, _7$$4, _8$$4, _9$$5, _10$$5, _11$$5, _12$$5, _13$$6, _14$$6, _15$$6, _16$$6, _17$$6, _18, _19, _20, _24, _28, _29, _30, _21$$7, _22$$7, _23$$7, _25$$8, _26$$8, _27$$8;
	zend_long width, height, offsetX, offsetY, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("height", 6, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(offsetX, is_null_true)
		Z_PARAM_LONG_OR_NULL(offsetY, is_null_true)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 2, &width_param, &height_param, &offsetX_param, &offsetY_param);
	if (!offsetX_param) {
		offsetX = 0;
	} else {
		}
	if (!offsetY_param) {
		offsetY = 0;
	} else {
		}
	if (0 == offsetX) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_LONG(&_1$$3, width);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_sub_function(&_2$$3, &_0$$3, &_1$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_div_zval_long(&_3$$3, &_2$$3, 2);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		offsetX = zephir_get_intval(&_3$$3);
	} else {
		ZEPHIR_INIT_VAR(&_4$$4);
		if (offsetX < 0) {
			zephir_read_property_cached(&_5$$4, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_6$$4);
			ZVAL_LONG(&_6$$4, width);
			ZEPHIR_INIT_VAR(&_7$$4);
			zephir_sub_function(&_7$$4, &_5$$4, &_6$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZVAL_LONG(&_6$$4, offsetX);
			ZEPHIR_INIT_NVAR(&_4$$4);
			zephir_add_function(&_4$$4, &_7$$4, &_6$$4);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_NVAR(&_4$$4);
			ZVAL_LONG(&_4$$4, offsetX);
		}
		offsetX = zephir_get_intval(&_4$$4);
		ZEPHIR_INIT_VAR(&_8$$4);
		zephir_read_property_cached(&_5$$4, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_LT_LONG(&_5$$4, offsetX)) {
			ZEPHIR_OBS_NVAR(&_8$$4);
			zephir_read_property_cached(&_8$$4, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZVAL_LONG(&_8$$4, offsetX);
		}
		offsetX = zephir_get_intval(&_8$$4);
	}
	if (0 == offsetY) {
		zephir_read_property_cached(&_9$$5, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_10$$5);
		ZVAL_LONG(&_10$$5, height);
		ZEPHIR_INIT_VAR(&_11$$5);
		zephir_sub_function(&_11$$5, &_9$$5, &_10$$5);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_VAR(&_12$$5);
		zephir_div_zval_long(&_12$$5, &_11$$5, 2);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		offsetY = zephir_get_intval(&_12$$5);
	} else {
		ZEPHIR_INIT_VAR(&_13$$6);
		if (offsetY < 0) {
			zephir_read_property_cached(&_14$$6, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_15$$6);
			ZVAL_LONG(&_15$$6, height);
			ZEPHIR_INIT_VAR(&_16$$6);
			zephir_sub_function(&_16$$6, &_14$$6, &_15$$6);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_NVAR(&_15$$6);
			ZVAL_LONG(&_15$$6, offsetY);
			ZEPHIR_INIT_NVAR(&_13$$6);
			zephir_add_function(&_13$$6, &_16$$6, &_15$$6);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_NVAR(&_13$$6);
			ZVAL_LONG(&_13$$6, offsetY);
		}
		offsetY = zephir_get_intval(&_13$$6);
		ZEPHIR_INIT_VAR(&_17$$6);
		zephir_read_property_cached(&_14$$6, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_LT_LONG(&_14$$6, offsetY)) {
			ZEPHIR_OBS_NVAR(&_17$$6);
			zephir_read_property_cached(&_17$$6, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_17$$6);
			ZVAL_LONG(&_17$$6, offsetY);
		}
		offsetY = zephir_get_intval(&_17$$6);
	}
	zephir_read_property_cached(&_18, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_19);
	ZVAL_LONG(&_19, offsetX);
	ZEPHIR_INIT_VAR(&_20);
	zephir_sub_function(&_20, &_18, &_19);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_LT_LONG(&_20, width)) {
		zephir_read_property_cached(&_21$$7, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_22$$7);
		ZVAL_LONG(&_22$$7, offsetX);
		ZEPHIR_INIT_VAR(&_23$$7);
		zephir_sub_function(&_23$$7, &_21$$7, &_22$$7);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		width = zephir_get_intval(&_23$$7);
	}
	zephir_read_property_cached(&_18, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_19);
	ZVAL_LONG(&_19, offsetY);
	ZEPHIR_INIT_VAR(&_24);
	zephir_sub_function(&_24, &_18, &_19);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_LT_LONG(&_24, height)) {
		zephir_read_property_cached(&_25$$8, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_26$$8);
		ZVAL_LONG(&_26$$8, offsetY);
		ZEPHIR_INIT_VAR(&_27$$8);
		zephir_sub_function(&_27$$8, &_25$$8, &_26$$8);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		height = zephir_get_intval(&_27$$8);
	}
	ZVAL_LONG(&_18, width);
	ZVAL_LONG(&_28, height);
	ZVAL_LONG(&_29, offsetX);
	ZVAL_LONG(&_30, offsetY);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processCrop", NULL, 0, &_18, &_28, &_29, &_30);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Flip the image along the horizontal or vertical axis
 *
 * @param int $direction
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, flip)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *direction_param = NULL, _1;
	zend_long direction, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(direction)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &direction_param);
	_0 = direction != 11;
	if (_0) {
		_0 = direction != 12;
	}
	if (_0) {
		direction = 11;
	}
	ZVAL_LONG(&_1, direction);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processFlip", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, getHeight)
{

	RETURN_MEMBER_TYPED(getThis(), "height", IS_LONG);
}

/**
 * @return object|null
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, getImage)
{

	RETURN_MEMBER(getThis(), "image");
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, getMime)
{

	RETURN_MEMBER_TYPED(getThis(), "mime", IS_STRING);
}

/**
 * @return string
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, getRealpath)
{

	RETURN_MEMBER_TYPED(getThis(), "realpath", IS_STRING);
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, getType)
{

	RETURN_MEMBER_TYPED(getThis(), "type", IS_LONG);
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, getWidth)
{

	RETURN_MEMBER_TYPED(getThis(), "width", IS_LONG);
}

/**
 * Composite one image onto another
 *
 * @param AdapterInterface $mask
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, mask)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *mask, mask_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&mask_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(mask, phalcon_image_adapter_adapterinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &mask);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processMask", NULL, 0, mask);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Pixelate image
 *
 * @param int $amount
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, pixelate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *amount_param = NULL, _0;
	zend_long amount, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(amount)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &amount_param);
	if (amount < 2) {
		amount = 2;
	}
	ZVAL_LONG(&_0, amount);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processPixelate", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Add a reflection to an image
 *
 * @param int  $height
 * @param int  $opacity
 * @param bool $fadeIn
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, reflection)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool fadeIn, _0;
	zval *height_param = NULL, *opacity_param = NULL, *fadeIn_param = NULL, _1, _3, _4, _5, _6, _2$$3;
	zend_long height, opacity, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_LONG(height)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(opacity)
		Z_PARAM_BOOL(fadeIn)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &height_param, &opacity_param, &fadeIn_param);
	if (!opacity_param) {
		opacity = 100;
	} else {
		}
	if (!fadeIn_param) {
		fadeIn = 0;
	} else {
		}
	_0 = height <= 0;
	if (!(_0)) {
		zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 170, PH_NOISY_CC | PH_READONLY);
		_0 = ZEPHIR_LT_LONG(&_1, height);
	}
	if (_0) {
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 170, PH_NOISY_CC | PH_READONLY);
		height = zephir_get_intval(&_2$$3);
	}
	ZVAL_LONG(&_4, opacity);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "checkHighLow", NULL, 0, &_4);
	zephir_check_call_status();
	opacity = zephir_get_intval(&_3);
	ZVAL_LONG(&_4, height);
	ZVAL_LONG(&_5, opacity);
	if (fadeIn) {
		ZVAL_BOOL(&_6, 1);
	} else {
		ZVAL_BOOL(&_6, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processReflection", NULL, 0, &_4, &_5, &_6);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Render the image and return the binary string
 *
 * @param string|null $extension
 * @param int         $quality
 *
 * @return string
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, render)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long quality, ZEPHIR_LAST_CALL_STATUS;
	zval *extension_param = NULL, *quality_param = NULL, _0$$3, _1$$3, _2$$3, _4, _5, _6;
	zval extension, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("file", 4, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(extension_param)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &extension_param, &quality_param);
	if (!extension_param) {
		ZEPHIR_INIT_VAR(&extension);
	} else {
		zephir_get_strval(&extension, extension_param);
	}
	if (!quality_param) {
		quality = 100;
	} else {
		}
	if (Z_TYPE_P(&extension) == IS_NULL) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 171, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_1$$3, 4);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "pathinfo", NULL, 97, &_0$$3, &_1$$3);
		zephir_check_call_status();
		zephir_cast_to_string(&_3$$3, &_2$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&extension, &_3$$3);
	}
	if (1 == ZEPHIR_IS_EMPTY(&extension)) {
		ZEPHIR_INIT_NVAR(&extension);
		ZVAL_STRING(&extension, "png");
	}
	ZVAL_LONG(&_5, quality);
	ZVAL_LONG(&_6, 1);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "checkHighLow", NULL, 0, &_5, &_6);
	zephir_check_call_status();
	quality = zephir_get_intval(&_4);
	ZVAL_LONG(&_5, quality);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "processRender", NULL, 0, &extension, &_5);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Resize the image to the given size
 *
 * @param int|null $width
 * @param int|null $height
 * @param int      $master
 *
 * @return AdapterInterface
 * @throws Exception
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, resize)
{
	zend_bool _0$$3, _5$$10, _10$$11, _22$$14;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *width_param = NULL, *height_param = NULL, *master_param = NULL, ratio, _33, _34, _35, _36, _37, _38, _39, _40, _1$$10, _2$$10, _3$$10, _4$$10, _6$$11, _7$$11, _8$$11, _9$$11, _11$$12, _12$$12, _13$$12, _14$$12, _15$$13, _16$$13, _17$$13, _18$$13, _19$$14, _20$$14, _21$$14, _23$$15, _24$$15, _25$$15, _26$$15, _27$$16, _28$$16, _29$$16, _30$$16, _31$$17, _32$$17;
	zend_long width, height, master, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ratio);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_1$$10);
	ZVAL_UNDEF(&_2$$10);
	ZVAL_UNDEF(&_3$$10);
	ZVAL_UNDEF(&_4$$10);
	ZVAL_UNDEF(&_6$$11);
	ZVAL_UNDEF(&_7$$11);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_11$$12);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_14$$12);
	ZVAL_UNDEF(&_15$$13);
	ZVAL_UNDEF(&_16$$13);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&_25$$15);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_27$$16);
	ZVAL_UNDEF(&_28$$16);
	ZVAL_UNDEF(&_29$$16);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_31$$17);
	ZVAL_UNDEF(&_32$$17);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("height", 6, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(width, is_null_true)
		Z_PARAM_LONG_OR_NULL(height, is_null_true)
		Z_PARAM_LONG(master)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &width_param, &height_param, &master_param);
	if (!width_param) {
		width = 0;
	} else {
		}
	if (!height_param) {
		height = 0;
	} else {
		}
	if (!master_param) {
		master = 4;
	} else {
		}
	if (master == 7) { goto zephir_switch_0_clause_0; }
	if (master == 4) { goto zephir_switch_0_clause_1; }
	if (master == 5) { goto zephir_switch_0_clause_2; }
	if (master == 6) { goto zephir_switch_0_clause_3; }
	if (master == 2) { goto zephir_switch_0_clause_4; }
	if (master == 3) { goto zephir_switch_0_clause_5; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
	zephir_switch_0_clause_3: ;
		_0$$3 = 0 == width;
		if (!(_0$$3)) {
			_0$$3 = 0 == height;
		}
		if (_0$$3) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "width and height must be specified", "phalcon/Image/Adapter/AbstractAdapter.zep", 329);
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_4: ;
		if (0 == width) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "width must be specified", "phalcon/Image/Adapter/AbstractAdapter.zep", 334);
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_clause_5: ;
		if (0 == height) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "height must be specified", "phalcon/Image/Adapter/AbstractAdapter.zep", 339);
			return;
		}
		goto zephir_switch_0_end;
	zephir_switch_0_end: ;

	if (master != 7) {
		if (master == 4) {
			ZEPHIR_INIT_VAR(&_1$$10);
			zephir_read_property_cached(&_2$$10, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_3$$10);
			zephir_div_zval_long(&_3$$10, &_2$$10, width);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_2$$10, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_4$$10);
			zephir_div_zval_long(&_4$$10, &_2$$10, height);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			_5$$10 = ZEPHIR_GT(&_3$$10, &_4$$10);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_5$$10) {
				ZEPHIR_INIT_NVAR(&_1$$10);
				ZVAL_LONG(&_1$$10, 2);
			} else {
				ZEPHIR_INIT_NVAR(&_1$$10);
				ZVAL_LONG(&_1$$10, 3);
			}
			master = zephir_get_intval(&_1$$10);
		}
		if (master == 5) {
			ZEPHIR_INIT_VAR(&_6$$11);
			zephir_read_property_cached(&_7$$11, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_8$$11);
			zephir_div_zval_long(&_8$$11, &_7$$11, width);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_7$$11, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_9$$11);
			zephir_div_zval_long(&_9$$11, &_7$$11, height);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			_10$$11 = ZEPHIR_GT(&_8$$11, &_9$$11);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_10$$11) {
				ZEPHIR_INIT_NVAR(&_6$$11);
				ZVAL_LONG(&_6$$11, 3);
			} else {
				ZEPHIR_INIT_NVAR(&_6$$11);
				ZVAL_LONG(&_6$$11, 2);
			}
			master = zephir_get_intval(&_6$$11);
		}
		if (master == 2) { goto zephir_switch_1_clause_0; }
		if (master == 3) { goto zephir_switch_1_clause_1; }
		if (master == 6) { goto zephir_switch_1_clause_2; }
		if (master == 1) { goto zephir_switch_1_clause_3; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_INIT_VAR(&_11$$12);
			zephir_read_property_cached(&_12$$12, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_13$$12);
			ZVAL_LONG(&_13$$12, width);
			ZEPHIR_INIT_VAR(&_14$$12);
			mul_function(&_14$$12, &_12$$12, &_13$$12);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_12$$12, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_NVAR(&_13$$12);
			div_function(&_13$$12, &_14$$12, &_12$$12);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_round(&_11$$12, &_13$$12, NULL, NULL);
			height = zephir_get_intval(&_11$$12);
			goto zephir_switch_1_end;
		zephir_switch_1_clause_1: ;
			ZEPHIR_INIT_VAR(&_15$$13);
			zephir_read_property_cached(&_16$$13, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_17$$13);
			ZVAL_LONG(&_17$$13, height);
			ZEPHIR_INIT_VAR(&_18$$13);
			mul_function(&_18$$13, &_16$$13, &_17$$13);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_16$$13, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_NVAR(&_17$$13);
			div_function(&_17$$13, &_18$$13, &_16$$13);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_round(&_15$$13, &_17$$13, NULL, NULL);
			width = zephir_get_intval(&_15$$13);
			goto zephir_switch_1_end;
		zephir_switch_1_clause_2: ;
			zephir_read_property_cached(&_19$$14, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
			zephir_read_property_cached(&_20$$14, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&ratio);
			div_function(&ratio, &_19$$14, &_20$$14);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_VAR(&_21$$14);
			zephir_div_long_long(&_21$$14, width, height);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			_22$$14 = ZEPHIR_GT(&_21$$14, &ratio);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_22$$14) {
				ZEPHIR_INIT_VAR(&_23$$15);
				zephir_read_property_cached(&_24$$15, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_25$$15);
				ZVAL_LONG(&_25$$15, width);
				ZEPHIR_INIT_VAR(&_26$$15);
				mul_function(&_26$$15, &_24$$15, &_25$$15);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_read_property_cached(&_24$$15, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_NVAR(&_25$$15);
				div_function(&_25$$15, &_26$$15, &_24$$15);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_round(&_23$$15, &_25$$15, NULL, NULL);
				height = zephir_get_intval(&_23$$15);
			} else {
				ZEPHIR_INIT_VAR(&_27$$16);
				zephir_read_property_cached(&_28$$16, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_29$$16);
				ZVAL_LONG(&_29$$16, height);
				ZEPHIR_INIT_VAR(&_30$$16);
				mul_function(&_30$$16, &_28$$16, &_29$$16);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_read_property_cached(&_28$$16, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_NVAR(&_29$$16);
				div_function(&_29$$16, &_30$$16, &_28$$16);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_round(&_27$$16, &_29$$16, NULL, NULL);
				width = zephir_get_intval(&_27$$16);
			}
			goto zephir_switch_1_end;
		zephir_switch_1_clause_3: ;
			ZEPHIR_INIT_VAR(&_31$$17);
			if (0 == width) {
				ZEPHIR_OBS_NVAR(&_31$$17);
				zephir_read_property_cached(&_31$$17, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC);
			} else {
				ZEPHIR_INIT_NVAR(&_31$$17);
				ZVAL_LONG(&_31$$17, width);
			}
			width = zephir_get_intval(&_31$$17);
			ZEPHIR_INIT_VAR(&_32$$17);
			if (0 == height) {
				ZEPHIR_OBS_NVAR(&_32$$17);
				zephir_read_property_cached(&_32$$17, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC);
			} else {
				ZEPHIR_INIT_NVAR(&_32$$17);
				ZVAL_LONG(&_32$$17, height);
			}
			height = zephir_get_intval(&_32$$17);
			goto zephir_switch_1_end;
		zephir_switch_1_end: ;

	}
	ZEPHIR_INIT_VAR(&_33);
	ZVAL_LONG(&_34, width);
	zephir_round(&_33, &_34, NULL, NULL);
	ZVAL_LONG(&_35, 1);
	ZEPHIR_CALL_FUNCTION(&_36, "max", NULL, 98, &_33, &_35);
	zephir_check_call_status();
	width = zephir_get_intval(&_36);
	ZEPHIR_INIT_VAR(&_37);
	ZVAL_LONG(&_35, height);
	zephir_round(&_37, &_35, NULL, NULL);
	ZVAL_LONG(&_38, 1);
	ZEPHIR_CALL_FUNCTION(&_39, "max", NULL, 98, &_37, &_38);
	zephir_check_call_status();
	height = zephir_get_intval(&_39);
	ZVAL_LONG(&_38, width);
	ZVAL_LONG(&_40, height);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processResize", NULL, 0, &_38, &_40);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Rotate the image by a given amount
 *
 * @param int $degrees
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, rotate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *degrees_param = NULL, _0;
	zend_long degrees, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(degrees)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &degrees_param);
	if (degrees > 180) {
		degrees = zephir_safe_mod_long_long(degrees, 360);
		if (degrees > 180) {
			degrees -= 360;
		}
	} else {
		while (1) {
			if (!(degrees < -180)) {
				break;
			}
			degrees += 360;
		}
	}
	ZVAL_LONG(&_0, degrees);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processRotate", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Save the image
 *
 * @param string|null $file
 * @param int         $quality
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, save)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long quality, ZEPHIR_LAST_CALL_STATUS;
	zval *file_param = NULL, *quality_param = NULL, _0$$3, _2;
	zval file, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("realpath", 8, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(file_param)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &file_param, &quality_param);
	if (!file_param) {
		ZEPHIR_INIT_VAR(&file);
	} else {
		zephir_get_strval(&file, file_param);
	}
	if (!quality_param) {
		quality = -1;
	} else {
		}
	if (Z_TYPE_P(&file) == IS_NULL) {
		zephir_memory_observe(&_0$$3);
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 172, PH_NOISY_CC);
		zephir_cast_to_string(&_1$$3, &_0$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&file, &_1$$3);
	}
	ZVAL_LONG(&_2, quality);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processSave", NULL, 0, &file, &_2);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Sharpen the image by a given amount
 *
 * @param int $amount
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, sharpen)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *amount_param = NULL, _0, _1, _2;
	zend_long amount, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(amount)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &amount_param);
	ZVAL_LONG(&_1, amount);
	ZVAL_LONG(&_2, 1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "checkHighLow", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	amount = zephir_get_intval(&_0);
	ZVAL_LONG(&_1, amount);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processSharpen", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Add a text to an image with a specified opacity
 *
 * @param string      $text
 * @param mixed       $offsetX
 * @param mixed       $offsetY
 * @param int         $opacity
 * @param string      $color
 * @param int         $size
 * @param string|null $fontFile
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, text)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval color;
	zend_long opacity, size, ZEPHIR_LAST_CALL_STATUS;
	zval text_zv, *offsetX = NULL, offsetX_sub, *offsetY = NULL, offsetY_sub, *opacity_param = NULL, *color_param = NULL, *size_param = NULL, fontFile_zv, __$false, colors, _0, _1, _3, _4, _10, _11, _12, _13, _14, _15, _16, _5$$3, _6$$3, _7$$4, _8$$4, _9$$4;
	zend_string *text = NULL, *fontFile = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&offsetX_sub);
	ZVAL_UNDEF(&offsetY_sub);
	ZVAL_UNDEF(&fontFile_zv);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&colors);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&color);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 7)
		Z_PARAM_STR(text)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(offsetX)
		Z_PARAM_ZVAL(offsetY)
		Z_PARAM_LONG(opacity)
		Z_PARAM_ZVAL(color_param)
		Z_PARAM_LONG(size)
		Z_PARAM_STR_OR_NULL(fontFile)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		offsetX = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		offsetY = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		opacity_param = ZEND_CALL_ARG(execute_data, 4);
	}
	if (ZEND_NUM_ARGS() > 4) {
		color_param = ZEND_CALL_ARG(execute_data, 5);
	}
	if (ZEND_NUM_ARGS() > 5) {
		size_param = ZEND_CALL_ARG(execute_data, 6);
	}
	zephir_memory_observe(&text_zv);
	ZVAL_STR_COPY(&text_zv, text);
	if (!offsetX) {
		offsetX = &offsetX_sub;
		offsetX = &__$false;
	}
	if (!offsetY) {
		offsetY = &offsetY_sub;
		offsetY = &__$false;
	}
	if (!opacity_param) {
		opacity = 100;
	} else {
		}
	if (!color_param) {
		ZEPHIR_INIT_VAR(&color);
		ZVAL_STRING(&color, "000000");
	} else {
		zephir_get_strval(&color, color_param);
	}
	if (!size_param) {
		size = 12;
	} else {
		}
	if (!fontFile) {
		ZEPHIR_INIT_VAR(&fontFile_zv);
	} else {
		zephir_memory_observe(&fontFile_zv);
	ZVAL_STR_COPY(&fontFile_zv, fontFile);
	}
	ZVAL_LONG(&_1, opacity);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "checkHighLow", NULL, 0, &_1);
	zephir_check_call_status();
	opacity = zephir_get_intval(&_0);
	_2 = zephir_fast_strlen_ev(&color) > 1;
	if (_2) {
		ZVAL_LONG(&_1, 0);
		ZVAL_LONG(&_3, 1);
		ZEPHIR_INIT_VAR(&_4);
		zephir_substr(&_4, &color, 0 , 1 , 0);
		_2 = ZEPHIR_IS_STRING_IDENTICAL(&_4, "#");
	}
	if (_2) {
		ZVAL_LONG(&_5$$3, 1);
		ZEPHIR_INIT_VAR(&_6$$3);
		zephir_substr(&_6$$3, &color, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_get_strval(&color, &_6$$3);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (zephir_fast_strlen_ev(&color) == 3) {
		ZEPHIR_INIT_VAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "/./");
		ZEPHIR_INIT_VAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "$0$0");
		ZEPHIR_CALL_FUNCTION(&_9$$4, "preg_replace", NULL, 40, &_7$$4, &_8$$4, &color);
		zephir_check_call_status();
		zephir_get_strval(&color, &_9$$4);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZVAL_LONG(&_10, 2);
	ZEPHIR_CALL_FUNCTION(&_11, "str_split", NULL, 96, &color, &_10);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "hexdec");
	ZEPHIR_CALL_FUNCTION(&colors, "array_map", NULL, 89, &_12, &_11);
	zephir_check_call_status();
	zephir_memory_observe(&_13);
	zephir_array_fetch_long(&_13, &colors, 0, PH_NOISY, "phalcon/Image/Adapter/AbstractAdapter.zep", 495);
	zephir_memory_observe(&_14);
	zephir_array_fetch_long(&_14, &colors, 1, PH_NOISY, "phalcon/Image/Adapter/AbstractAdapter.zep", 496);
	zephir_memory_observe(&_15);
	zephir_array_fetch_long(&_15, &colors, 2, PH_NOISY, "phalcon/Image/Adapter/AbstractAdapter.zep", 497);
	ZVAL_LONG(&_10, opacity);
	ZVAL_LONG(&_16, size);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processText", NULL, 0, &text_zv, offsetX, offsetY, &_10, &_13, &_14, &_15, &_16, &fontFile_zv);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Add a watermark to an image with the specified opacity
 *
 * @param AdapterInterface $watermark
 * @param int              $offsetX
 * @param int              $offsetY
 * @param int              $opacity
 *
 * @return AdapterInterface
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, watermark)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long offsetX, offsetY, opacity, ZEPHIR_LAST_CALL_STATUS;
	zval *watermark, watermark_sub, *offsetX_param = NULL, *offsetY_param = NULL, *opacity_param = NULL, op, x, y, _0, _1, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&watermark_sub);
	ZVAL_UNDEF(&op);
	ZVAL_UNDEF(&x);
	ZVAL_UNDEF(&y);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_OBJECT_OF_CLASS(watermark, phalcon_image_adapter_adapterinterface_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(offsetX)
		Z_PARAM_LONG(offsetY)
		Z_PARAM_LONG(opacity)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 3, &watermark, &offsetX_param, &offsetY_param, &opacity_param);
	if (!offsetX_param) {
		offsetX = 0;
	} else {
		}
	if (!offsetY_param) {
		offsetY = 0;
	} else {
		}
	if (!opacity_param) {
		opacity = 100;
	} else {
		}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 169, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, watermark, "getWidth", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	zephir_sub_function(&_2, &_0, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_0, offsetX);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(&x, this_ptr, "checkHighLow", NULL, 0, &_0, &_3, &_2);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 170, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, watermark, "getHeight", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	zephir_sub_function(&_4, &_0, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_0, offsetY);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(&y, this_ptr, "checkHighLow", NULL, 0, &_0, &_3, &_4);
	zephir_check_call_status();
	ZVAL_LONG(&_0, opacity);
	ZEPHIR_CALL_METHOD(&op, this_ptr, "checkHighLow", NULL, 0, &_0);
	zephir_check_call_status();
	ZVAL_LONG(&_0, opacity);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "processWatermark", NULL, 0, watermark, &x, &y, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * @param int $value
 * @param int $min
 * @param int $max
 *
 * @return int
 */
PHP_METHOD(Phalcon_Image_Adapter_AbstractAdapter, checkHighLow)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *value_param = NULL, *min_param = NULL, *max_param = NULL, _0, _1, _2;
	zend_long value, min, max, ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_LONG(value)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(min)
		Z_PARAM_LONG(max)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &value_param, &min_param, &max_param);
	if (!min_param) {
		min = 0;
	} else {
		}
	if (!max_param) {
		max = 100;
	} else {
		}
	ZVAL_LONG(&_0, value);
	ZVAL_LONG(&_1, min);
	ZEPHIR_CALL_FUNCTION(&_2, "max", NULL, 98, &_0, &_1);
	zephir_check_call_status();
	ZVAL_LONG(&_0, max);
	ZEPHIR_RETURN_CALL_FUNCTION("min", NULL, 99, &_0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

