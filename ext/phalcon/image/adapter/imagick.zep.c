
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/file.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/string.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Image\Adapter\Imagick
 *
 * Image manipulation support. Resize, rotate, crop etc.
 *
 *```php
 * $image = new \Phalcon\Image\Adapter\Imagick("upload/test.jpg");
 *
 * $image->resize(200, 200)->rotate(90)->crop(100, 100);
 *
 * if ($image->save()) {
 *     echo "success";
 * }
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Image_Adapter_Imagick)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Image\\Adapter, Imagick, phalcon, image_adapter_imagick, phalcon_image_adapter_abstractadapter_ce, phalcon_image_adapter_imagick_method_entry, 0);

	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_image_adapter_imagick_ce, SL("version"), 0, ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Constructor
 *
 * @param string   $file
 * @param int|null $width
 * @param int|null $height
 *
 * @throws Exception
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, __construct)
{
	zend_bool _22$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long width, height, ZEPHIR_LAST_CALL_STATUS;
	zval file_zv, *width_param = NULL, *height_param = NULL, image, _0, _1, _32, _33, _34, _35, _36, _37, _38, _39, _40, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _10$$3, _11$$3, _15$$3, _16$$3, _17$$3, _18$$3, _7$$4, _8$$4, _9$$4, _12$$5, _13$$5, _14$$5, _19$$6, _20$$6, _21$$6, _26$$7, _27$$7, _28$$7, _29$$7, _30$$7, _31$$7, _23$$8, _24$$8, _25$$8;
	zend_string *file = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&file_zv);
	ZVAL_UNDEF(&image);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_38);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_18$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_27$$7);
	ZVAL_UNDEF(&_28$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_30$$7);
	ZVAL_UNDEF(&_31$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("file", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("realpath", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("height", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("mime", 4, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(file)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG_OR_NULL(width, is_null_true)
		Z_PARAM_LONG_OR_NULL(height, is_null_true)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		width_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		height_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&file_zv);
	ZVAL_STR_COPY(&file_zv, file);
	if (!width_param) {
		width = 0;
	} else {
		}
	if (!height_param) {
		height = 0;
	} else {
		}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "check", NULL, 445);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 636, &file_zv);
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zephir_get_internal_ce(SL("imagick")));
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 637, &_0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 636, PH_NOISY_CC | PH_READONLY);
	if (1 == (zephir_file_exists(&_1) == SUCCESS)) {
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 636, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(&_3$$3, "realpath", NULL, 80, &_2$$3);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 638, &_3$$3);
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_6$$3, this_ptr, _zephir_prop_2, 638, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_5$$3, &_4$$3, "readImage", NULL, 0, &_6$$3);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_5$$3)) {
			ZEPHIR_INIT_VAR(&_7$$4);
			object_init_ex(&_7$$4, phalcon_image_exception_ce);
			zephir_read_property_cached(&_8$$4, this_ptr, _zephir_prop_0, 636, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_9$$4);
			ZEPHIR_CONCAT_SVS(&_9$$4, "Imagick::readImage ", &_8$$4, " failed");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_7$$4, "__construct", NULL, 32, &_9$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_7$$4, "phalcon/Image/Adapter/Imagick.zep", 72);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_10$$3, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_11$$3, &_10$$3, "getImageAlphaChannel", NULL, 0);
		zephir_check_call_status();
		if (!zephir_is_true(&_11$$3)) {
			zephir_read_property_cached(&_12$$5, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_13$$5);
			ZVAL_STRING(&_13$$5, "Imagick::ALPHACHANNEL_SET");
			ZEPHIR_CALL_FUNCTION(&_14$$5, "constant", NULL, 75, &_13$$5);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_12$$5, "setImageAlphaChannel", NULL, 0, &_14$$5);
			zephir_check_call_status();
		}
		zephir_read_property_cached(&_15$$3, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_16$$3, &_15$$3, "getImageType", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 639, &_16$$3);
		zephir_read_property_cached(&_17$$3, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_18$$3, &_17$$3, "getImageType", NULL, 0);
		zephir_check_call_status();
		if (ZEPHIR_IS_LONG(&_18$$3, 1)) {
			zephir_read_property_cached(&_19$$6, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&image, &_19$$6, "coalesceImages", NULL, 0);
			zephir_check_call_status();
			zephir_read_property_cached(&_20$$6, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_20$$6, "clear", NULL, 0);
			zephir_check_call_status();
			zephir_read_property_cached(&_21$$6, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_21$$6, "destroy", NULL, 0);
			zephir_check_call_status();
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 637, &image);
		}
	} else {
		_22$$7 = 0 == width;
		if (!(_22$$7)) {
			_22$$7 = 0 == height;
		}
		if (_22$$7) {
			ZEPHIR_INIT_VAR(&_23$$8);
			object_init_ex(&_23$$8, phalcon_image_exception_ce);
			zephir_read_property_cached(&_24$$8, this_ptr, _zephir_prop_0, 636, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_25$$8);
			ZEPHIR_CONCAT_SV(&_25$$8, "Failed to create image from file ", &_24$$8);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_23$$8, "__construct", NULL, 32, &_25$$8);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_23$$8, "phalcon/Image/Adapter/Imagick.zep", 97);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_26$$7, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_27$$7);
		object_init_ex(&_27$$7, zephir_get_internal_ce(SL("imagickpixel")));
		ZEPHIR_INIT_VAR(&_28$$7);
		ZVAL_STRING(&_28$$7, "transparent");
		ZEPHIR_CALL_METHOD(NULL, &_27$$7, "__construct", NULL, 0, &_28$$7);
		zephir_check_call_status();
		ZVAL_LONG(&_29$$7, width);
		ZVAL_LONG(&_30$$7, height);
		ZEPHIR_CALL_METHOD(NULL, &_26$$7, "newImage", NULL, 0, &_29$$7, &_30$$7, &_27$$7);
		zephir_check_call_status();
		zephir_read_property_cached(&_29$$7, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_28$$7);
		ZVAL_STRING(&_28$$7, "png");
		ZEPHIR_CALL_METHOD(NULL, &_29$$7, "setFormat", NULL, 0, &_28$$7);
		zephir_check_call_status();
		zephir_read_property_cached(&_30$$7, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_28$$7);
		ZVAL_STRING(&_28$$7, "png");
		ZEPHIR_CALL_METHOD(NULL, &_30$$7, "setImageFormat", NULL, 0, &_28$$7);
		zephir_check_call_status();
		zephir_read_property_cached(&_31$$7, this_ptr, _zephir_prop_0, 636, PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 638, &_31$$7);
	}
	zephir_read_property_cached(&_32, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_33, &_32, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 640, &_33);
	zephir_read_property_cached(&_34, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_35, &_34, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 641, &_35);
	zephir_read_property_cached(&_36, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_37, &_36, "getImageType", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 639, &_37);
	zephir_read_property_cached(&_38, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_39, &_38, "getImageFormat", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_40);
	ZEPHIR_CONCAT_SV(&_40, "image/", &_39);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 642, &_40);
	ZEPHIR_MM_RESTORE();
}

/**
 * Destroys the loaded image to free up resources.
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, __destruct)
{
	zval _0, _1$$3, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC);
	if (zephir_is_instance_of(&_0, SL("Imagick"))) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "clear", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "destroy", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * This method scales the images using liquid rescaling method. Only support
 * Imagick
 *
 * @param int $width    new width
 * @param int $height   new height
 * @param int $deltaX   How much the seam can traverse on x-axis. Passing
 *                      0 causes the seams to be straight.
 * @param int $rigidity Introduces a bias for non-straight seams. This
 *                      parameter is typically 0.
 *
 * @return AbstractAdapter
 * @throws Exception
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, liquidRescale)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_7 = NULL;
	zval *width_param = NULL, *height_param = NULL, *deltaX_param = NULL, *rigidity_param = NULL, image, result, _0, _8, _9, _1$$3, _2$$3, _3$$3, _4$$3, _6$$3;
	zend_long width, height, deltaX, rigidity, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&image);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(deltaX)
		Z_PARAM_LONG(rigidity)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 2, &width_param, &height_param, &deltaX_param, &rigidity_param);
	if (!deltaX_param) {
		deltaX = 0;
	} else {
		}
	if (!rigidity_param) {
		rigidity = 0;
	} else {
		}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&image, &_0);
	ZVAL_LONG(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, &image, "setIteratorIndex", NULL, 0, &_0);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZVAL_LONG(&_1$$3, width);
		ZVAL_LONG(&_2$$3, height);
		ZVAL_LONG(&_3$$3, deltaX);
		ZVAL_LONG(&_4$$3, rigidity);
		ZEPHIR_CALL_METHOD(&result, &image, "liquidRescaleImage", &_5, 0, &_1$$3, &_2$$3, &_3$$3, &_4$$3);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::liquidRescale failed", "phalcon/Image/Adapter/Imagick.zep", 165);
			return;
		}
		ZEPHIR_CALL_METHOD(&_6$$3, &image, "nextImage", &_7, 0);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_6$$3)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(&_8, &image, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 640, &_8);
	ZEPHIR_CALL_METHOD(&_9, &image, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 641, &_9);
	RETURN_THIS();
}

/**
 * Sets the limit for a particular resource in megabytes
 *
 * @param int $type
 * @param int $limit
 *
 * @return void
 * @throws Exception
 * @throws ImagickException
 *
 * @link https://www.php.net/manual/en/imagick.constants.php#imagick.constants.resourcetypes
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, setResourceLimit)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *type_param = NULL, *limit_param = NULL, _1$$3, _2$$3, _3$$3;
	zend_long type, limit, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(type)
		Z_PARAM_LONG(limit)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &type_param, &limit_param);
	_0 = type >= 0;
	if (_0) {
		_0 = type <= 6;
	}
	if (_0) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_2$$3, type);
		ZVAL_LONG(&_3$$3, limit);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "setResourceLimit", NULL, 0, &_2$$3, &_3$$3);
		zephir_check_call_status();
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Cannot set the Resource Type for this image", "phalcon/Image/Adapter/Imagick.zep", 201);
		return;
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a background.
 *
 * @param int $red
 * @param int $green
 * @param int $blue
 * @param int $opacity
 *
 * @return void
 * @throws Exception
 * @throws ImagickException
 * @throws ImagickPixelException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processBackground)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_19 = NULL, *_21 = NULL, *_26 = NULL;
	zval *red_param = NULL, *green_param = NULL, *blue_param = NULL, *opacity_param = NULL, background, color, pixel1, pixel2, result, _0, _1, _2, _3, _4, _5$$3, _6$$3, _8$$3, _15$$3, _16$$3, _17$$3, _18$$3, _20$$3, _22$$3, _23$$3, _24$$3, _25$$3, _27$$3, _10$$4, _11$$4;
	zend_long red, green, blue, opacity, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&background);
	ZVAL_UNDEF(&color);
	ZVAL_UNDEF(&pixel1);
	ZVAL_UNDEF(&pixel2);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_18$$3);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_22$$3);
	ZVAL_UNDEF(&_23$$3);
	ZVAL_UNDEF(&_24$$3);
	ZVAL_UNDEF(&_25$$3);
	ZVAL_UNDEF(&_27$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(red)
		Z_PARAM_LONG(green)
		Z_PARAM_LONG(blue)
		Z_PARAM_LONG(opacity)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &red_param, &green_param, &blue_param, &opacity_param);
	ZEPHIR_INIT_VAR(&_0);
	zephir_div_long_long(&_0, opacity, 100);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	opacity = zephir_get_intval(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "rgb(%d, %d, %d)");
	ZVAL_LONG(&_2, red);
	ZVAL_LONG(&_3, green);
	ZVAL_LONG(&_4, blue);
	ZEPHIR_CALL_FUNCTION(&color, "sprintf", NULL, 73, &_1, &_2, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&pixel1);
	object_init_ex(&pixel1, zephir_get_internal_ce(SL("imagickpixel")));
	ZEPHIR_CALL_METHOD(NULL, &pixel1, "__construct", NULL, 0, &color);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&pixel2);
	object_init_ex(&pixel2, zephir_get_internal_ce(SL("imagickpixel")));
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "transparent");
	ZEPHIR_CALL_METHOD(NULL, &pixel2, "__construct", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&background);
	object_init_ex(&background, zephir_get_internal_ce(SL("imagick")));
	ZEPHIR_CALL_METHOD(NULL, &background, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(NULL, &_2, "setIteratorIndex", NULL, 0, &_3);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_1, 640, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_6$$3, this_ptr, _zephir_prop_2, 641, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &background, "newImage", &_7, 0, &_5$$3, &_6$$3, &pixel1);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_8$$3, &background, "getImageAlphaChannel", &_9, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_8$$3)) {
			ZEPHIR_INIT_NVAR(&_10$$4);
			ZVAL_STRING(&_10$$4, "Imagick::ALPHACHANNEL_SET");
			ZEPHIR_CALL_FUNCTION(&_11$$4, "constant", &_12, 75, &_10$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &background, "setImageAlphaChannel", &_13, 0, &_11$$4);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(NULL, &background, "setImageBackgroundColor", &_14, 0, &pixel2);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15$$3);
		ZVAL_STRING(&_15$$3, "Imagick::EVALUATE_MULTIPLY");
		ZEPHIR_CALL_FUNCTION(&_16$$3, "constant", &_12, 75, &_15$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15$$3);
		ZVAL_STRING(&_15$$3, "Imagick::CHANNEL_ALPHA");
		ZEPHIR_CALL_FUNCTION(&_17$$3, "constant", &_12, 75, &_15$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_18$$3, opacity);
		ZEPHIR_CALL_METHOD(NULL, &background, "evaluateImage", &_19, 0, &_16$$3, &_18$$3, &_17$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_18$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_20$$3, &_18$$3, "getColorspace", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &background, "setColorspace", &_21, 0, &_20$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_22$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_15$$3);
		ZVAL_STRING(&_15$$3, "Imagick::COMPOSITE_DISSOLVE");
		ZEPHIR_CALL_FUNCTION(&_23$$3, "constant", &_12, 75, &_15$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_24$$3, 0);
		ZVAL_LONG(&_25$$3, 0);
		ZEPHIR_CALL_METHOD(&result, &background, "compositeImage", &_26, 0, &_22$$3, &_23$$3, &_24$$3, &_25$$3);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::compositeImage failed", "phalcon/Image/Adapter/Imagick.zep", 263);
			return;
		}
		zephir_read_property_cached(&_24$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_27$$3, &_24$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_27$$3)) {
			break;
		}
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_3, "clear", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_4, "destroy", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 637, &background);
	ZEPHIR_MM_RESTORE();
}

/**
 * Blur image
 *
 * @param int $radius Blur radius
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processBlur)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *radius_param = NULL, _0, _1, _2$$3, _3$$3, _4$$3, _5$$3;
	zend_long radius, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(radius)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &radius_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 0);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setIteratorIndex", NULL, 0, &_1);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_3$$3, radius);
		ZVAL_LONG(&_4$$3, 100);
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "blurImage", NULL, 0, &_3$$3, &_4$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_5$$3, &_3$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_5$$3)) {
			break;
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a crop.
 *
 * @param int $width
 * @param int $height
 * @param int $offsetX
 * @param int $offsetY
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processCrop)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_6 = NULL, *_8 = NULL;
	zval *width_param = NULL, *height_param = NULL, *offsetX_param = NULL, *offsetY_param = NULL, image, _0, _9, _10, _1$$3, _2$$3, _3$$3, _4$$3, _7$$3;
	zend_long width, height, offsetX, offsetY, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&image);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(offsetX)
		Z_PARAM_LONG(offsetY)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &width_param, &height_param, &offsetX_param, &offsetY_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&image, &_0);
	ZVAL_LONG(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, &image, "setIteratorIndex", NULL, 0, &_0);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZVAL_LONG(&_1$$3, width);
		ZVAL_LONG(&_2$$3, height);
		ZVAL_LONG(&_3$$3, offsetX);
		ZVAL_LONG(&_4$$3, offsetY);
		ZEPHIR_CALL_METHOD(NULL, &image, "cropImage", &_5, 0, &_1$$3, &_2$$3, &_3$$3, &_4$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_1$$3, width);
		ZVAL_LONG(&_2$$3, height);
		ZVAL_LONG(&_3$$3, 0);
		ZVAL_LONG(&_4$$3, 0);
		ZEPHIR_CALL_METHOD(NULL, &image, "setImagePage", &_6, 0, &_1$$3, &_2$$3, &_3$$3, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_7$$3, &image, "nextImage", &_8, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_7$$3)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(&_9, &image, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 640, &_9);
	ZEPHIR_CALL_METHOD(&_10, &image, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 641, &_10);
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a flip.
 *
 * @param int $direction
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processFlip)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *direction_param = NULL, method, _0, _1, _2$$3, _3$$3, _4$$3;
	zend_long direction, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(direction)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &direction_param);
	if (direction == 11) {
		ZEPHIR_INIT_VAR(&method);
		ZVAL_STRING(&method, "flipImage");
	} else {
		ZEPHIR_INIT_NVAR(&method);
		ZVAL_STRING(&method, "flopImage");
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 0);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setIteratorIndex", NULL, 0, &_1);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD_ZVAL(NULL, &_2$$3, &method, NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_4$$3, &_3$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_4$$3)) {
			break;
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Composite one image onto another
 *
 * @param AdapterInterface $image
 *
 * @return void
 * @throws Exception
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processMask)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *image, image_sub, mask, result, _0, _1, _2, _3$$3, _4$$3, _5$$3, _6$$3, _8$$3, _9$$3, _10$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&image_sub);
	ZVAL_UNDEF(&mask);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(image, phalcon_image_adapter_adapterinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &image);
	ZEPHIR_INIT_VAR(&mask);
	object_init_ex(&mask, zephir_get_internal_ce(SL("imagick")));
	ZEPHIR_CALL_METHOD(NULL, &mask, "__construct", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, image, "render", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &mask, "readImageBlob", NULL, 0, &_0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_2, 0);
	ZEPHIR_CALL_METHOD(NULL, &_1, "setIteratorIndex", NULL, 0, &_2);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_BOOL(&_4$$3, 1);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "setImageMatte", NULL, 0, &_4$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "Imagick::COMPOSITE_DSTIN");
		ZEPHIR_CALL_FUNCTION(&_6$$3, "constant", &_7, 75, &_5$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_8$$3, 0);
		ZVAL_LONG(&_9$$3, 0);
		ZEPHIR_CALL_METHOD(&result, &_4$$3, "compositeImage", NULL, 0, &mask, &_6$$3, &_8$$3, &_9$$3);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::compositeImage failed", "phalcon/Image/Adapter/Imagick.zep", 388);
			return;
		}
		zephir_read_property_cached(&_8$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_10$$3, &_8$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_10$$3)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &mask, "clear", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &mask, "destroy", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Pixelate image
 *
 * @param int $amount amount to pixelate
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processPixelate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *amount_param = NULL, _0, _1, _2, _3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3, _9$$3;
	zend_long amount, ZEPHIR_LAST_CALL_STATUS, height = 0, width = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("height", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(amount)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &amount_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 640, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	zephir_div_zval_long(&_1, &_0, amount);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	width = zephir_get_intval(&_1);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 641, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	zephir_div_zval_long(&_2, &_0, amount);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	height = zephir_get_intval(&_2);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setIteratorIndex", NULL, 0, &_3);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_2, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_5$$3, width);
		ZVAL_LONG(&_6$$3, height);
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "scaleImage", NULL, 0, &_5$$3, &_6$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_2, 637, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_6$$3, this_ptr, _zephir_prop_0, 640, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_7$$3, this_ptr, _zephir_prop_1, 641, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_5$$3, "scaleImage", NULL, 0, &_6$$3, &_7$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_8$$3, this_ptr, _zephir_prop_2, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_9$$3, &_8$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_9$$3)) {
			break;
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a reflection.
 *
 * @param int  $height
 * @param int  $opacity
 * @param bool $fadeIn
 *
 * @return void
 * @throws Exception
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processReflection)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_7 = NULL, *_11 = NULL, *_13 = NULL, *_14 = NULL, *_21 = NULL, *_24 = NULL, *_27 = NULL, *_36 = NULL, *_39 = NULL, *_41 = NULL, *_44 = NULL, *_49 = NULL, *_56 = NULL;
	zend_bool fadeIn, _57$$13;
	zval *height_param = NULL, *opacity_param = NULL, *fadeIn_param = NULL, fade, image, pixel, pseudo, reflection, result, _0, _4, _16, _17, _18, _29, _30, _31, _32, _33, _59, _60, _61, _62, _1$$3, _2$$4, _3$$4, _6$$5, _8$$5, _9$$5, _10$$5, _12$$5, _15$$5, _19$$7, _20$$7, _22$$7, _23$$7, _25$$7, _26$$7, _28$$7, _34$$10, _35$$10, _37$$10, _38$$10, _40$$10, _42$$10, _43$$10, _45$$10, _46$$10, _47$$10, _48$$10, _50$$10, _51$$13, _52$$13, _53$$13, _54$$13, _55$$13, _58$$13;
	zend_long height, opacity, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fade);
	ZVAL_UNDEF(&image);
	ZVAL_UNDEF(&pixel);
	ZVAL_UNDEF(&pseudo);
	ZVAL_UNDEF(&reflection);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_59);
	ZVAL_UNDEF(&_60);
	ZVAL_UNDEF(&_61);
	ZVAL_UNDEF(&_62);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_28$$7);
	ZVAL_UNDEF(&_34$$10);
	ZVAL_UNDEF(&_35$$10);
	ZVAL_UNDEF(&_37$$10);
	ZVAL_UNDEF(&_38$$10);
	ZVAL_UNDEF(&_40$$10);
	ZVAL_UNDEF(&_42$$10);
	ZVAL_UNDEF(&_43$$10);
	ZVAL_UNDEF(&_45$$10);
	ZVAL_UNDEF(&_46$$10);
	ZVAL_UNDEF(&_47$$10);
	ZVAL_UNDEF(&_48$$10);
	ZVAL_UNDEF(&_50$$10);
	ZVAL_UNDEF(&_51$$13);
	ZVAL_UNDEF(&_52$$13);
	ZVAL_UNDEF(&_53$$13);
	ZVAL_UNDEF(&_54$$13);
	ZVAL_UNDEF(&_55$$13);
	ZVAL_UNDEF(&_58$$13);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("version", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(opacity)
		Z_PARAM_BOOL(fadeIn)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &height_param, &opacity_param, &fadeIn_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 643, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&reflection);
	if (ZEPHIR_GE_LONG(&_0, 30100)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		if (zephir_clone(&reflection, &_1$$3) == FAILURE) {
			RETURN_MM();
		}
	} else {
		zephir_read_property_cached(&_2$$4, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_3$$4, &_2$$4, "clone", NULL, 0);
		zephir_check_call_status();
		if (zephir_clone(&reflection, &_3$$4) == FAILURE) {
			RETURN_MM();
		}
	}
	ZVAL_LONG(&_4, 0);
	ZEPHIR_CALL_METHOD(NULL, &reflection, "setIteratorIndex", NULL, 0, &_4);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZEPHIR_CALL_METHOD(NULL, &reflection, "flipImage", &_5, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_6$$5, &reflection, "getImageWidth", &_7, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_8$$5, height);
		ZVAL_LONG(&_9$$5, 0);
		ZVAL_LONG(&_10$$5, 0);
		ZEPHIR_CALL_METHOD(NULL, &reflection, "cropImage", &_11, 0, &_6$$5, &_8$$5, &_9$$5, &_10$$5);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_12$$5, &reflection, "getImageWidth", &_13, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_8$$5, height);
		ZVAL_LONG(&_9$$5, 0);
		ZVAL_LONG(&_10$$5, 0);
		ZEPHIR_CALL_METHOD(NULL, &reflection, "setImagePage", &_14, 0, &_12$$5, &_8$$5, &_9$$5, &_10$$5);
		zephir_check_call_status();
		zephir_read_property_cached(&_8$$5, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_15$$5, &_8$$5, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_15$$5)) {
			break;
		}
	}
	if (fadeIn) {
		ZEPHIR_INIT_VAR(&pseudo);
		ZVAL_STRING(&pseudo, "gradient:black-transparent");
	} else {
		ZEPHIR_INIT_NVAR(&pseudo);
		ZVAL_STRING(&pseudo, "gradient:transparent-black");
	}
	ZEPHIR_INIT_VAR(&fade);
	object_init_ex(&fade, zephir_get_internal_ce(SL("imagick")));
	ZEPHIR_CALL_METHOD(NULL, &fade, "__construct", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_16, &reflection, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_17, &reflection, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &fade, "newPseudoImage", NULL, 0, &_16, &_17, &pseudo);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_18);
	zephir_div_long_long(&_18, opacity, 100);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	opacity = zephir_get_intval(&_18);
	ZVAL_LONG(&_4, 0);
	ZEPHIR_CALL_METHOD(NULL, &reflection, "setIteratorIndex", NULL, 0, &_4);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&_19$$7);
		ZVAL_STRING(&_19$$7, "Imagick::COMPOSITE_DSTOUT");
		ZEPHIR_CALL_FUNCTION(&_20$$7, "constant", &_21, 75, &_19$$7);
		zephir_check_call_status();
		ZVAL_LONG(&_22$$7, 0);
		ZVAL_LONG(&_23$$7, 0);
		ZEPHIR_CALL_METHOD(&result, &reflection, "compositeImage", &_24, 0, &fade, &_20$$7, &_22$$7, &_23$$7);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::compositeImage failed", "phalcon/Image/Adapter/Imagick.zep", 495);
			return;
		}
		ZEPHIR_INIT_NVAR(&_19$$7);
		ZVAL_STRING(&_19$$7, "Imagick::EVALUATE_MULTIPLY");
		ZEPHIR_CALL_FUNCTION(&_25$$7, "constant", &_21, 75, &_19$$7);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_19$$7);
		ZVAL_STRING(&_19$$7, "Imagick::CHANNEL_ALPHA");
		ZEPHIR_CALL_FUNCTION(&_26$$7, "constant", &_21, 75, &_19$$7);
		zephir_check_call_status();
		ZVAL_LONG(&_22$$7, opacity);
		ZEPHIR_CALL_METHOD(NULL, &reflection, "evaluateImage", &_27, 0, &_25$$7, &_22$$7, &_26$$7);
		zephir_check_call_status();
		zephir_read_property_cached(&_22$$7, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_28$$7, &_22$$7, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_28$$7)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &fade, "destroy", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&image);
	object_init_ex(&image, zephir_get_internal_ce(SL("imagick")));
	ZEPHIR_CALL_METHOD(NULL, &image, "__construct", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&pixel);
	object_init_ex(&pixel, zephir_get_internal_ce(SL("imagickpixel")));
	ZEPHIR_CALL_METHOD(NULL, &pixel, "__construct", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_29, &_4, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_30);
	ZVAL_LONG(&_30, height);
	ZEPHIR_INIT_VAR(&_31);
	zephir_add_function(&_31, &_29, &_30);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	height = zephir_get_intval(&_31);
	zephir_read_property_cached(&_32, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_33, 0);
	ZEPHIR_CALL_METHOD(NULL, &_32, "setIteratorIndex", NULL, 0, &_33);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_34$$10, this_ptr, _zephir_prop_2, 640, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_35$$10, height);
		ZEPHIR_CALL_METHOD(NULL, &image, "newImage", &_36, 0, &_34$$10, &_35$$10, &pixel);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_37$$10);
		ZVAL_STRING(&_37$$10, "Imagick::ALPHACHANNEL_SET");
		ZEPHIR_CALL_FUNCTION(&_38$$10, "constant", &_21, 75, &_37$$10);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &image, "setImageAlphaChannel", &_39, 0, &_38$$10);
		zephir_check_call_status();
		zephir_read_property_cached(&_35$$10, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_40$$10, &_35$$10, "getColorspace", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &image, "setColorspace", &_41, 0, &_40$$10);
		zephir_check_call_status();
		zephir_read_property_cached(&_42$$10, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_43$$10, &_42$$10, "getImageDelay", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &image, "setImageDelay", &_44, 0, &_43$$10);
		zephir_check_call_status();
		zephir_read_property_cached(&_45$$10, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_37$$10);
		ZVAL_STRING(&_37$$10, "Imagick::COMPOSITE_SRC");
		ZEPHIR_CALL_FUNCTION(&_46$$10, "constant", &_21, 75, &_37$$10);
		zephir_check_call_status();
		ZVAL_LONG(&_47$$10, 0);
		ZVAL_LONG(&_48$$10, 0);
		ZEPHIR_CALL_METHOD(&result, &image, "compositeImage", &_49, 0, &_45$$10, &_46$$10, &_47$$10, &_48$$10);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::compositeImage failed", "phalcon/Image/Adapter/Imagick.zep", 534);
			return;
		}
		zephir_read_property_cached(&_47$$10, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_50$$10, &_47$$10, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_50$$10)) {
			break;
		}
	}
	ZVAL_LONG(&_33, 0);
	ZEPHIR_CALL_METHOD(NULL, &image, "setIteratorIndex", NULL, 0, &_33);
	zephir_check_call_status();
	ZVAL_LONG(&_33, 0);
	ZEPHIR_CALL_METHOD(NULL, &reflection, "setIteratorIndex", NULL, 0, &_33);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&_51$$13);
		ZVAL_STRING(&_51$$13, "Imagick::COMPOSITE_OVER");
		ZEPHIR_CALL_FUNCTION(&_52$$13, "constant", &_21, 75, &_51$$13);
		zephir_check_call_status();
		zephir_read_property_cached(&_53$$13, this_ptr, _zephir_prop_3, 641, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_54$$13, 0);
		ZEPHIR_CALL_METHOD(&result, &image, "compositeImage", &_49, 0, &reflection, &_52$$13, &_54$$13, &_53$$13);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::compositeImage failed", "phalcon/Image/Adapter/Imagick.zep", 554);
			return;
		}
		ZEPHIR_CALL_METHOD(&_55$$13, &image, "nextImage", &_56, 0);
		zephir_check_call_status();
		_57$$13 = !ZEPHIR_IS_TRUE_IDENTICAL(&_55$$13);
		if (!(_57$$13)) {
			ZEPHIR_CALL_METHOD(&_58$$13, &reflection, "nextImage", NULL, 0);
			zephir_check_call_status();
			_57$$13 = !ZEPHIR_IS_TRUE_IDENTICAL(&_58$$13);
		}
		if (_57$$13) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &reflection, "destroy", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_33, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_33, "clear", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_59, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_59, "destroy", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 637, &image);
	zephir_read_property_cached(&_60, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_29, &_60, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 640, &_29);
	zephir_read_property_cached(&_61, this_ptr, _zephir_prop_1, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_62, &_61, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 641, &_62);
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a render.
 *
 * @param string $extension
 * @param int    $quality
 *
 * @return string
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processRender)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long quality, ZEPHIR_LAST_CALL_STATUS;
	zval *extension_param = NULL, *quality_param = NULL, image, _0, _1, _2, _3, _4, _5$$4, _6$$4, _7$$4;
	zval extension;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&image);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("mime", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(extension_param)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &extension_param, &quality_param);
	zephir_get_strval(&extension, extension_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&image, &_0);
	ZEPHIR_CALL_METHOD(NULL, &image, "setFormat", NULL, 0, &extension);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &image, "setImageFormat", NULL, 0, &extension);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &image, "stripImage", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &image, "getImageType", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 639, &_1);
	ZEPHIR_CALL_METHOD(&_2, &image, "getImageFormat", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SV(&_3, "image/", &_2);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 642, &_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_fast_strtolower(&_4, &extension);
	zephir_get_strval(&extension, &_4);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_IS_STRING(&extension, "gif")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&extension, "jpg")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&extension, "jpeg")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		ZEPHIR_CALL_METHOD(NULL, &image, "optimizeImageLayers", NULL, 0);
		zephir_check_call_status();
		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_INIT_VAR(&_5$$4);
		ZVAL_STRING(&_5$$4, "Imagick::COMPRESSION_JPEG");
		ZEPHIR_CALL_FUNCTION(&_6$$4, "constant", NULL, 75, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &image, "setImageCompression", NULL, 0, &_6$$4);
		zephir_check_call_status();
		ZVAL_LONG(&_7$$4, quality);
		ZEPHIR_CALL_METHOD(NULL, &image, "setImageCompressionQuality", NULL, 0, &_7$$4);
		zephir_check_call_status();
	zephir_switch_0_end: ;

	ZEPHIR_RETURN_CALL_METHOD(&image, "getImageBlob", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Execute a resize.
 *
 * @param int $width
 * @param int $height
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processResize)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_5 = NULL;
	zval *width_param = NULL, *height_param = NULL, image, _0, _6, _7, _1$$3, _2$$3, _4$$3;
	zend_long width, height, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&image);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &width_param, &height_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&image, &_0);
	ZVAL_LONG(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, &image, "setIteratorIndex", NULL, 0, &_0);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZVAL_LONG(&_1$$3, width);
		ZVAL_LONG(&_2$$3, height);
		ZEPHIR_CALL_METHOD(NULL, &image, "scaleImage", &_3, 0, &_1$$3, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, &image, "nextImage", &_5, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_4$$3)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(&_6, &image, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 640, &_6);
	ZEPHIR_CALL_METHOD(&_7, &image, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 641, &_7);
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a rotation.
 *
 * @param int $degrees
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processRotate)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *degrees_param = NULL, pixel, _0, _1, _9, _10, _11, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3;
	zend_long degrees, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pixel);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("width", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("height", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(degrees)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &degrees_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 0);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setIteratorIndex", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&pixel);
	object_init_ex(&pixel, zephir_get_internal_ce(SL("imagickpixel")));
	ZEPHIR_CALL_METHOD(NULL, &pixel, "__construct", NULL, 0);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_2$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_3$$3, degrees);
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "rotateImage", NULL, 0, &pixel, &_3$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_1, 640, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_2, 641, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_6$$3, 0);
		ZVAL_LONG(&_7$$3, 0);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "setImagePage", NULL, 0, &_4$$3, &_5$$3, &_6$$3, &_7$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_6$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_8$$3, &_6$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_8$$3)) {
			break;
		}
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_9, &_1, "getImageWidth", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 640, &_9);
	zephir_read_property_cached(&_10, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_11, &_10, "getImageHeight", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 641, &_11);
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a save.
 *
 * @param string $file
 * @param int    $quality
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processSave)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long quality, ZEPHIR_LAST_CALL_STATUS;
	zval file_zv, *quality_param = NULL, extension, fp, _0, _1, _2, _3, _4, _5, _6, _7, _17, _8$$3, _9$$3, _10$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zend_string *file = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&file_zv);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&fp);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("type", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("mime", 4, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(file)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	quality_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&file_zv);
	ZVAL_STR_COPY(&file_zv, file);
	ZVAL_LONG(&_0, 4);
	ZEPHIR_CALL_FUNCTION(&extension, "pathinfo", NULL, 97, &file_zv, &_0);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "setFormat", NULL, 0, &extension);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_1, "setImageFormat", NULL, 0, &extension);
	zephir_check_call_status();
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_3, &_2, "getImageType", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 639, &_3);
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_5, &_4, "getImageFormat", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SV(&_6, "image/", &_5);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 642, &_6);
	ZEPHIR_INIT_VAR(&_7);
	zephir_fast_strtolower(&_7, &extension);
	ZEPHIR_CPY_WRT(&extension, &_7);
	if (ZEPHIR_IS_STRING(&extension, "gif")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&extension, "jpg")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&extension, "jpeg")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		zephir_read_property_cached(&_8$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_8$$3, "optimizeImageLayers", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_9$$3);
		ZVAL_STRING(&_9$$3, "w");
		ZEPHIR_CALL_FUNCTION(&fp, "fopen", NULL, 143, &file_zv, &_9$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_10$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_10$$3, "writeImagesFile", NULL, 0, &fp);
		zephir_check_call_status();
		zephir_fclose(&fp);
		RETURN_MM_NULL();
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		zephir_read_property_cached(&_11$$4, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "Imagick::COMPRESSION_JPEG");
		ZEPHIR_CALL_FUNCTION(&_13$$4, "constant", NULL, 75, &_12$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_11$$4, "setImageCompression", NULL, 0, &_13$$4);
		zephir_check_call_status();
	zephir_switch_0_end: ;

	if (quality >= 0) {
		ZVAL_LONG(&_15$$5, quality);
		ZVAL_LONG(&_16$$5, 1);
		ZEPHIR_CALL_METHOD(&_14$$5, this_ptr, "checkHighLow", NULL, 0, &_15$$5, &_16$$5);
		zephir_check_call_status();
		quality = zephir_get_intval(&_14$$5);
		zephir_read_property_cached(&_15$$5, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_16$$5, quality);
		ZEPHIR_CALL_METHOD(NULL, &_15$$5, "setImageCompressionQuality", NULL, 0, &_16$$5);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_17, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_17, "writeImage", NULL, 0, &file_zv);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a sharpen.
 *
 * @param int $amount
 *
 * @return void
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processSharpen)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *amount_param = NULL, _0, _1, _2, _3$$3, _4$$3, _5$$3, _6$$3;
	zend_long amount, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(amount)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &amount_param);
	ZEPHIR_INIT_VAR(&_0);
	if (amount < 5) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_LONG(&_0, 5);
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_LONG(&_0, amount);
	}
	amount = zephir_get_intval(&_0);
	amount = (long) (zephir_safe_div_double_long((((double) (amount) * 3.0)), 100));
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_2, 0);
	ZEPHIR_CALL_METHOD(NULL, &_1, "setIteratorIndex", NULL, 0, &_2);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_4$$3, 0);
		ZVAL_LONG(&_5$$3, amount);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "sharpenImage", NULL, 0, &_4$$3, &_5$$3);
		zephir_check_call_status();
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_6$$3, &_4$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_6$$3)) {
			break;
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Execute a text
 *
 * @param string      $text
 * @param mixed       $offsetX
 * @param mixed       $offsetY
 * @param int         $opacity
 * @param int         $red
 * @param int         $green
 * @param int         $blue
 * @param int         $size
 * @param string|null $fontFile
 *
 * @return void
 * @throws ImagickDrawException
 * @throws ImagickException
 * @throws ImagickPixelException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processText)
{
	zend_bool _8$$8, _10$$8, _11$$8, _12$$8, _14$$11, _16$$11, _17$$11, _18$$11;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long opacity, red, green, blue, size, ZEPHIR_LAST_CALL_STATUS;
	zval text_zv, *offsetX = NULL, offsetX_sub, *offsetY = NULL, offsetY_sub, *opacity_param = NULL, *red_param = NULL, *green_param = NULL, *blue_param = NULL, *size_param = NULL, fontFile_zv, color, draw, gravity, x, y, _0, _1, _2, _3, _4, _5$$4, _6$$5, _7$$7, _9$$8, _13$$8, _15$$11, _19$$11, _20$$12, _21$$12, _22$$14, _23$$14, _24$$14;
	zend_string *text = NULL, *fontFile = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&text_zv);
	ZVAL_UNDEF(&offsetX_sub);
	ZVAL_UNDEF(&offsetY_sub);
	ZVAL_UNDEF(&fontFile_zv);
	ZVAL_UNDEF(&color);
	ZVAL_UNDEF(&draw);
	ZVAL_UNDEF(&gravity);
	ZVAL_UNDEF(&x);
	ZVAL_UNDEF(&y);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_19$$11);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&_22$$14);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_24$$14);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(8, 9)
		Z_PARAM_STR(text)
		Z_PARAM_ZVAL(offsetX)
		Z_PARAM_ZVAL(offsetY)
		Z_PARAM_LONG(opacity)
		Z_PARAM_LONG(red)
		Z_PARAM_LONG(green)
		Z_PARAM_LONG(blue)
		Z_PARAM_LONG(size)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(fontFile)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	offsetX = ZEND_CALL_ARG(execute_data, 2);
	offsetY = ZEND_CALL_ARG(execute_data, 3);
	opacity_param = ZEND_CALL_ARG(execute_data, 4);
	red_param = ZEND_CALL_ARG(execute_data, 5);
	green_param = ZEND_CALL_ARG(execute_data, 6);
	blue_param = ZEND_CALL_ARG(execute_data, 7);
	size_param = ZEND_CALL_ARG(execute_data, 8);
	zephir_memory_observe(&text_zv);
	ZVAL_STR_COPY(&text_zv, text);
	ZEPHIR_SEPARATE_PARAM(offsetX);
	ZEPHIR_SEPARATE_PARAM(offsetY);
	if (!fontFile) {
		ZEPHIR_INIT_VAR(&fontFile_zv);
	} else {
		zephir_memory_observe(&fontFile_zv);
	ZVAL_STR_COPY(&fontFile_zv, fontFile);
	}
	ZEPHIR_INIT_VAR(&_0);
	zephir_div_long_long(&_0, opacity, 100);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	opacity = zephir_get_intval(&_0);
	ZEPHIR_INIT_VAR(&draw);
	object_init_ex(&draw, zephir_get_internal_ce(SL("imagickdraw")));
	ZEPHIR_CALL_METHOD(NULL, &draw, "__construct", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "rgb(%d, %d, %d)");
	ZVAL_LONG(&_2, red);
	ZVAL_LONG(&_3, green);
	ZVAL_LONG(&_4, blue);
	ZEPHIR_CALL_FUNCTION(&color, "sprintf", NULL, 73, &_1, &_2, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	object_init_ex(&_1, zephir_get_internal_ce(SL("imagickpixel")));
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 0, &color);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &draw, "setFillColor", NULL, 0, &_1);
	zephir_check_call_status();
	if (Z_TYPE_P(&fontFile_zv) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, &draw, "setFont", NULL, 0, &fontFile_zv);
		zephir_check_call_status();
	}
	if (size) {
		ZVAL_LONG(&_5$$4, size);
		ZEPHIR_CALL_METHOD(NULL, &draw, "setFontSize", NULL, 0, &_5$$4);
		zephir_check_call_status();
	}
	if (opacity) {
		ZVAL_LONG(&_6$$5, opacity);
		ZEPHIR_CALL_METHOD(NULL, &draw, "setfillopacity", NULL, 0, &_6$$5);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&gravity);
	ZVAL_NULL(&gravity);
	if (((Z_TYPE_P(offsetX) == IS_TRUE || Z_TYPE_P(offsetX) == IS_FALSE) == 1)) {
		if (((Z_TYPE_P(offsetY) == IS_TRUE || Z_TYPE_P(offsetY) == IS_FALSE) == 1)) {
			ZEPHIR_INIT_NVAR(offsetX);
			ZVAL_LONG(offsetX, 0);
			ZEPHIR_INIT_NVAR(offsetY);
			ZVAL_LONG(offsetY, 0);
			ZEPHIR_INIT_VAR(&_7$$7);
			ZVAL_STRING(&_7$$7, "Imagick::GRAVITY_CENTER");
			ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_7$$7);
			zephir_check_call_status();
		} else if (Z_TYPE_P(offsetY) == IS_LONG) {
			ZEPHIR_INIT_VAR(&y);
			ZVAL_LONG(&y, zephir_get_intval(offsetY));
			_8$$8 = ZEPHIR_IS_TRUE_IDENTICAL(offsetX);
			if (_8$$8) {
				_8$$8 = ZEPHIR_LT_LONG(&y, 0);
			}
			if (_8$$8) {
				ZEPHIR_INIT_VAR(&_9$$8);
				ZVAL_STRING(&_9$$8, "Imagick::GRAVITY_SOUTHEAST");
				ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_9$$8);
				zephir_check_call_status();
			} else {
			}
			_10$$8 = ZEPHIR_IS_TRUE_IDENTICAL(offsetX);
			if (_10$$8) {
				_10$$8 = ZEPHIR_GE_LONG(&y, 0);
			}
			if (_10$$8) {
				ZEPHIR_INIT_NVAR(&_9$$8);
				ZVAL_STRING(&_9$$8, "Imagick::GRAVITY_NORTHEAST");
				ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_9$$8);
				zephir_check_call_status();
			} else {
			}
			_11$$8 = !ZEPHIR_IS_TRUE_IDENTICAL(offsetX);
			if (_11$$8) {
				_11$$8 = ZEPHIR_LT_LONG(&y, 0);
			}
			if (_11$$8) {
				ZEPHIR_INIT_NVAR(&_9$$8);
				ZVAL_STRING(&_9$$8, "Imagick::GRAVITY_SOUTH");
				ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_9$$8);
				zephir_check_call_status();
			} else {
			}
			_12$$8 = !ZEPHIR_IS_TRUE_IDENTICAL(offsetX);
			if (_12$$8) {
				_12$$8 = ZEPHIR_GE_LONG(&y, 0);
			}
			if (_12$$8) {
				ZEPHIR_INIT_NVAR(&_9$$8);
				ZVAL_STRING(&_9$$8, "Imagick::GRAVITY_NORTH");
				ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_9$$8);
				zephir_check_call_status();
			} else {
			}
			ZEPHIR_INIT_NVAR(offsetX);
			ZVAL_LONG(offsetX, 0);
			if (ZEPHIR_LT_LONG(&y, 0)) {
				ZEPHIR_INIT_VAR(&_13$$8);
				ZVAL_LONG(&_13$$8, -1);
				ZEPHIR_INIT_NVAR(offsetY);
				mul_function(offsetY, &y, &_13$$8);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
			}
		}
	} else if (Z_TYPE_P(offsetX) == IS_LONG) {
		ZEPHIR_INIT_VAR(&x);
		ZVAL_LONG(&x, zephir_get_intval(offsetX));
		if (zephir_is_true(offsetX)) {
			if (((Z_TYPE_P(offsetY) == IS_TRUE || Z_TYPE_P(offsetY) == IS_FALSE) == 1)) {
				_14$$11 = ZEPHIR_IS_TRUE_IDENTICAL(offsetY);
				if (_14$$11) {
					_14$$11 = ZEPHIR_LT_LONG(&x, 0);
				}
				if (_14$$11) {
					ZEPHIR_INIT_VAR(&_15$$11);
					ZVAL_STRING(&_15$$11, "Imagick::GRAVITY_SOUTHEAST");
					ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_15$$11);
					zephir_check_call_status();
				} else {
				}
				_16$$11 = ZEPHIR_IS_TRUE_IDENTICAL(offsetY);
				if (_16$$11) {
					_16$$11 = ZEPHIR_GE_LONG(&x, 0);
				}
				if (_16$$11) {
					ZEPHIR_INIT_NVAR(&_15$$11);
					ZVAL_STRING(&_15$$11, "Imagick::GRAVITY_SOUTH");
					ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_15$$11);
					zephir_check_call_status();
				} else {
				}
				_17$$11 = !ZEPHIR_IS_TRUE_IDENTICAL(offsetY);
				if (_17$$11) {
					_17$$11 = ZEPHIR_LT_LONG(&x, 0);
				}
				if (_17$$11) {
					ZEPHIR_INIT_NVAR(&_15$$11);
					ZVAL_STRING(&_15$$11, "Imagick::GRAVITY_EAST");
					ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_15$$11);
					zephir_check_call_status();
				} else {
				}
				_18$$11 = !ZEPHIR_IS_TRUE_IDENTICAL(offsetY);
				if (_18$$11) {
					_18$$11 = ZEPHIR_GE_LONG(&x, 0);
				}
				if (_18$$11) {
					ZEPHIR_INIT_NVAR(&_15$$11);
					ZVAL_STRING(&_15$$11, "Imagick::GRAVITY_WEST");
					ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_15$$11);
					zephir_check_call_status();
				} else {
				}
				ZEPHIR_INIT_NVAR(offsetY);
				ZVAL_LONG(offsetY, 0);
				if (ZEPHIR_LT_LONG(&x, 0)) {
					ZEPHIR_INIT_VAR(&_19$$11);
					ZVAL_LONG(&_19$$11, -1);
					ZEPHIR_INIT_NVAR(offsetX);
					mul_function(offsetX, &x, &_19$$11);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
				}
			} else if (Z_TYPE_P(offsetY) == IS_LONG) {
				ZEPHIR_INIT_NVAR(&y);
				ZVAL_LONG(&y, zephir_get_intval(offsetY));
				if (ZEPHIR_LT_LONG(&x, 0)) {
					ZEPHIR_INIT_VAR(&_20$$12);
					ZVAL_LONG(&_20$$12, -1);
					ZEPHIR_INIT_NVAR(offsetX);
					mul_function(offsetX, &x, &_20$$12);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_INIT_NVAR(offsetX);
					ZVAL_LONG(offsetX, 0);
				}
				if (ZEPHIR_LT_LONG(&y, 0)) {
					ZEPHIR_INIT_NVAR(&_20$$12);
					ZVAL_LONG(&_20$$12, -1);
					ZEPHIR_INIT_NVAR(offsetY);
					mul_function(offsetY, &y, &_20$$12);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
				}
				if (ZEPHIR_LT_LONG(&y, 0)) {
					ZEPHIR_INIT_VAR(&_21$$12);
					ZVAL_STRING(&_21$$12, "Imagick::GRAVITY_SOUTHEAST");
					ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_21$$12);
					zephir_check_call_status();
				} else {
				}
				if (ZEPHIR_GE_LONG(&y, 0)) {
					ZEPHIR_INIT_NVAR(&_21$$12);
					ZVAL_STRING(&_21$$12, "Imagick::GRAVITY_NORTHEAST");
					ZEPHIR_CALL_FUNCTION(&gravity, "constant", NULL, 75, &_21$$12);
					zephir_check_call_status();
				} else {
				}
			}
		}
	}
	if (Z_TYPE_P(&gravity) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, &draw, "setGravity", NULL, 0, &gravity);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(NULL, &_2, "setIteratorIndex", NULL, 0, &_3);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_22$$14, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_23$$14, 0);
		ZEPHIR_CALL_METHOD(NULL, &_22$$14, "annotateImage", NULL, 0, &draw, offsetX, offsetY, &_23$$14, &text_zv);
		zephir_check_call_status();
		zephir_read_property_cached(&_23$$14, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_24$$14, &_23$$14, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_24$$14)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &draw, "destroy", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Add Watermark
 *
 * @param AdapterInterface $image
 * @param int              $offsetX
 * @param int              $offsetY
 * @param int              $opacity
 *
 * @return void
 * @throws Exception
 * @throws ImagickException
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, processWatermark)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long offsetX, offsetY, opacity, ZEPHIR_LAST_CALL_STATUS;
	zval *image, image_sub, *offsetX_param = NULL, *offsetY_param = NULL, *opacity_param = NULL, result, watermark, _0, _1, _2, _3, _4, _5, _6, _7$$3, _8$$3, _9$$3, _10$$3, _11$$3, _12$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&image_sub);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&watermark);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("image", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(image, phalcon_image_adapter_adapterinterface_ce)
		Z_PARAM_LONG(offsetX)
		Z_PARAM_LONG(offsetY)
		Z_PARAM_LONG(opacity)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &image, &offsetX_param, &offsetY_param, &opacity_param);
	ZEPHIR_INIT_VAR(&_0);
	zephir_div_long_long(&_0, opacity, 100);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	opacity = zephir_get_intval(&_0);
	ZEPHIR_INIT_VAR(&watermark);
	object_init_ex(&watermark, zephir_get_internal_ce(SL("imagick")));
	ZEPHIR_CALL_METHOD(NULL, &watermark, "__construct", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, image, "render", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &watermark, "readImageBlob", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Imagick::EVALUATE_MULTIPLY");
	ZEPHIR_CALL_FUNCTION(&_3, "constant", NULL, 75, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "Imagick::CHANNEL_ALPHA");
	ZEPHIR_CALL_FUNCTION(&_4, "constant", NULL, 75, &_2);
	zephir_check_call_status();
	ZVAL_LONG(&_5, opacity);
	ZEPHIR_CALL_METHOD(NULL, &watermark, "evaluateImage", NULL, 0, &_3, &_5, &_4);
	zephir_check_call_status();
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_6, 0);
	ZEPHIR_CALL_METHOD(NULL, &_5, "setIteratorIndex", NULL, 0, &_6);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		zephir_read_property_cached(&_7$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_8$$3);
		ZVAL_STRING(&_8$$3, "Imagick::COMPOSITE_OVER");
		ZEPHIR_CALL_FUNCTION(&_9$$3, "constant", NULL, 75, &_8$$3);
		zephir_check_call_status();
		ZVAL_LONG(&_10$$3, offsetX);
		ZVAL_LONG(&_11$$3, offsetY);
		ZEPHIR_CALL_METHOD(&result, &_7$$3, "compositeImage", NULL, 0, &watermark, &_9$$3, &_10$$3, &_11$$3);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&result)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick::compositeImage failed", "phalcon/Image/Adapter/Imagick.zep", 893);
			return;
		}
		zephir_read_property_cached(&_10$$3, this_ptr, _zephir_prop_0, 637, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_12$$3, &_10$$3, "nextImage", NULL, 0);
		zephir_check_call_status();
		if (!ZEPHIR_IS_TRUE_IDENTICAL(&_12$$3)) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(NULL, &watermark, "clear", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &watermark, "destroy", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Checks if Imagick is enabled
 *
 * @return void
 * @throws Exception
 */
PHP_METHOD(Phalcon_Image_Adapter_Imagick, check)
{
	zval _0, _1, _2, _3$$4, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("version", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "imagick");
	if (1 != zephir_class_exists(&_0, 1)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_image_exception_ce, "Imagick is not installed, or the extension is not loaded", "phalcon/Image/Adapter/Imagick.zep", 916);
		return;
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Imagick::IMAGICK_EXTNUM");
	ZEPHIR_CALL_FUNCTION(&_2, "defined", NULL, 74, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_INIT_VAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "Imagick::IMAGICK_EXTNUM");
		ZEPHIR_CALL_FUNCTION(&_4$$4, "constant", NULL, 75, &_3$$4);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 643, &_4$$4);
	}
	ZEPHIR_MM_RESTORE();
}

