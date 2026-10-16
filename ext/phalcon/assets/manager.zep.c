
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/file.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Manages collections of CSS/JavaScript assets
 */
ZEPHIR_INIT_CLASS(Phalcon_Assets_Manager)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Assets, Manager, phalcon, assets_manager, phalcon_di_abstractinjectionaware_ce, phalcon_assets_manager_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_assets_manager_ce, SL("collections"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_assets_manager_ce, SL("implicitOutput"), 1, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_assets_manager_ce, SL("options"), ZEND_ACC_PROTECTED);
	/**
	 * @var TagFactory
	 */
	zend_declare_property_null(phalcon_assets_manager_ce, SL("tagFactory"), ZEND_ACC_PROTECTED);
	phalcon_assets_manager_ce->create_object = zephir_init_properties_Phalcon_Assets_Manager;

	return SUCCESS;
}

/**
 * Manager constructor.
 *
 * @param TagFactory $tagFactory
 * @param array      $options
 */
PHP_METHOD(Phalcon_Assets_Manager, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval options;
	zval *tagFactory, tagFactory_sub, *options_param = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tagFactory_sub);
	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("tagFactory", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("options", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_OBJECT_OF_CLASS(tagFactory, phalcon_html_tagfactory_ce)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &tagFactory, &options_param);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 290, tagFactory);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 291, &options);
	ZEPHIR_MM_RESTORE();
}

/**
 * Adds a raw asset to the manager
 *
 * @param Asset $asset
 */
PHP_METHOD(Phalcon_Assets_Manager, addAsset)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *asset, asset_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&asset_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(asset, phalcon_assets_asset_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &asset);
	ZEPHIR_CALL_METHOD(&_0, asset, "getType", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addAssetByType", NULL, 0, &_0, asset);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds a asset by its type
 *
 * @param string $type
 * @param Asset  $asset
 */
PHP_METHOD(Phalcon_Assets_Manager, addAssetByType)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval type_zv, *asset, asset_sub, collection;
	zend_string *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&asset_sub);
	ZVAL_UNDEF(&collection);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(type)
		Z_PARAM_OBJECT_OF_CLASS(asset, phalcon_assets_asset_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	asset = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	ZEPHIR_CALL_METHOD(&collection, this_ptr, "checkAndCreateCollection", NULL, 174, &type_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &collection, "add", NULL, 0, asset);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds a CSS asset to the 'css' collection
 *
 * @param string      $path
 * @param bool        $local
 * @param bool        $filter
 * @param array       $attributes
 * @param string|null $version
 * @param bool        $autoVersion
 */
PHP_METHOD(Phalcon_Assets_Manager, addCss)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes;
	zend_bool local, filter, autoVersion;
	zval path_zv, *local_param = NULL, *filter_param = NULL, *attributes_param = NULL, version_zv, *autoVersion_param = NULL, _0, _1, _2, _3, _4;
	zend_string *path = NULL, *version = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&version_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&attributes);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 6)
		Z_PARAM_STR(path)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(local)
		Z_PARAM_BOOL(filter)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_STR_OR_NULL(version)
		Z_PARAM_BOOL(autoVersion)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		local_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		filter_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		attributes_param = ZEND_CALL_ARG(execute_data, 4);
	}
	if (ZEND_NUM_ARGS() > 5) {
		autoVersion_param = ZEND_CALL_ARG(execute_data, 6);
	}
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	if (!local_param) {
		local = 1;
	} else {
		}
	if (!filter_param) {
		filter = 1;
	} else {
		}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	if (!version) {
		ZEPHIR_INIT_VAR(&version_zv);
	} else {
		zephir_memory_observe(&version_zv);
	ZVAL_STR_COPY(&version_zv, version);
	}
	if (!autoVersion_param) {
		autoVersion = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_asset_css_ce);
	if (local) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	if (filter) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	if (autoVersion) {
		ZVAL_BOOL(&_3, 1);
	} else {
		ZVAL_BOOL(&_3, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 175, &path_zv, &_1, &_2, &attributes, &version_zv, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "css");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addAssetByType", NULL, 0, &_4, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds a raw inline code to the manager
 *
 * @param Inline $code
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineCode)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *code, code_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&code_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(code, phalcon_assets_inline_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &code);
	ZEPHIR_CALL_METHOD(&_0, code, "getType", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addInlineCodeByType", NULL, 0, &_0, code);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds an inline code by its type
 *
 * @param string $type
 * @param Inline $code
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineCodeByType)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval type_zv, *code, code_sub, collection;
	zend_string *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&code_sub);
	ZVAL_UNDEF(&collection);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(type)
		Z_PARAM_OBJECT_OF_CLASS(code, phalcon_assets_inline_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	code = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	ZEPHIR_CALL_METHOD(&collection, this_ptr, "checkAndCreateCollection", NULL, 174, &type_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &collection, "addInline", NULL, 0, code);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds an inline CSS to the 'css' collection
 *
 * @param string $content
 * @param bool   $filter
 * @param array  $attributes
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineCss)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes;
	zend_bool filter;
	zval content_zv, *filter_param = NULL, *attributes_param = NULL, _0, _1, _2;
	zend_string *content = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(content)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(filter)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		filter_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		attributes_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&content_zv);
	ZVAL_STR_COPY(&content_zv, content);
	if (!filter_param) {
		filter = 1;
	} else {
		}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_inline_css_ce);
	if (filter) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 176, &content_zv, &_1, &attributes);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "css");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addInlineCodeByType", NULL, 0, &_2, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds an inline JavaScript to the 'js' collection
 *
 * @param string $content
 * @param bool   $filter
 * @param array  $attributes
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineJs)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes;
	zend_bool filter;
	zval content_zv, *filter_param = NULL, *attributes_param = NULL, _0, _1, _2;
	zend_string *content = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&attributes);
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STR(content)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(filter)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		filter_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		attributes_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&content_zv);
	ZVAL_STR_COPY(&content_zv, content);
	if (!filter_param) {
		filter = 1;
	} else {
		}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_inline_js_ce);
	if (filter) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 177, &content_zv, &_1, &attributes);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "js");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addInlineCodeByType", NULL, 0, &_2, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Adds a JavaScript asset to the 'js' collection
 *
 *```php
 * $assets->addJs("scripts/jquery.js");
 * $assets->addJs("http://jquery.my-cdn.com/jquery.js", false);
 *```
 *
 * @param string      $path
 * @param bool        $local
 * @param bool        $filter
 * @param array       $attributes
 * @param string|null $version
 * @param bool        $autoVersion
 */
PHP_METHOD(Phalcon_Assets_Manager, addJs)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval attributes;
	zend_bool local, filter, autoVersion;
	zval path_zv, *local_param = NULL, *filter_param = NULL, *attributes_param = NULL, version_zv, *autoVersion_param = NULL, _0, _1, _2, _3, _4;
	zend_string *path = NULL, *version = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&version_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&attributes);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 6)
		Z_PARAM_STR(path)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(local)
		Z_PARAM_BOOL(filter)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_STR_OR_NULL(version)
		Z_PARAM_BOOL(autoVersion)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		local_param = ZEND_CALL_ARG(execute_data, 2);
	}
	if (ZEND_NUM_ARGS() > 2) {
		filter_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		attributes_param = ZEND_CALL_ARG(execute_data, 4);
	}
	if (ZEND_NUM_ARGS() > 5) {
		autoVersion_param = ZEND_CALL_ARG(execute_data, 6);
	}
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	if (!local_param) {
		local = 1;
	} else {
		}
	if (!filter_param) {
		filter = 1;
	} else {
		}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	if (!version) {
		ZEPHIR_INIT_VAR(&version_zv);
	} else {
		zephir_memory_observe(&version_zv);
	ZVAL_STR_COPY(&version_zv, version);
	}
	if (!autoVersion_param) {
		autoVersion = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_asset_js_ce);
	if (local) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	if (filter) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	if (autoVersion) {
		ZVAL_BOOL(&_3, 1);
	} else {
		ZVAL_BOOL(&_3, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 178, &path_zv, &_1, &_2, &attributes, &version_zv, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "js");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addAssetByType", NULL, 0, &_4, &_0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Creates/Returns a collection of assets
 *
 * @param string $name
 */
PHP_METHOD(Phalcon_Assets_Manager, collection)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "checkAndCreateCollection", NULL, 174, &name_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Creates/Returns a collection of assets by type
 *
 * @param array  $assets
 * @param string $type
 */
PHP_METHOD(Phalcon_Assets_Manager, collectionAssetsByType)
{
	zend_bool _4, _1$$3, _5$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *type = NULL;
	zval *assets_param = NULL, type_zv, asset, *_0, _3, _2$$3, _6$$5;
	zval assets, filtered;

	ZVAL_UNDEF(&assets);
	ZVAL_UNDEF(&filtered);
	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&asset);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$5);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		ZEPHIR_Z_PARAM_ARRAY(assets, assets_param)
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	assets_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&assets, assets_param);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	ZEPHIR_INIT_VAR(&filtered);
	array_init(&filtered);
	zephir_is_iterable(&assets, 0, "phalcon/Assets/Manager.zep", 253);
	if (Z_TYPE_P(&assets) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&assets), _0)
		{
			ZEPHIR_INIT_NVAR(&asset);
			ZVAL_COPY(&asset, _0);
			_1$$3 = zephir_instance_of_ev(&asset, phalcon_assets_assetinterface_ce);
			if (_1$$3) {
				ZEPHIR_CALL_METHOD(&_2$$3, &asset, "getType", NULL, 0);
				zephir_check_call_status();
				_1$$3 = ZEPHIR_IS_IDENTICAL(&type_zv, &_2$$3);
			}
			if (_1$$3) {
				zephir_array_append(&filtered, &asset, PH_SEPARATE, "phalcon/Assets/Manager.zep", 249);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &assets, "rewind", NULL, 0);
		zephir_check_call_status();
		_4 = 1;
		while (1) {
			if (_4) {
				_4 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &assets, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_3, &assets, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&asset, &assets, "current", NULL, 0);
			zephir_check_call_status();
				_5$$5 = zephir_instance_of_ev(&asset, phalcon_assets_assetinterface_ce);
				if (_5$$5) {
					ZEPHIR_CALL_METHOD(&_6$$5, &asset, "getType", NULL, 0);
					zephir_check_call_status();
					_5$$5 = ZEPHIR_IS_IDENTICAL(&type_zv, &_6$$5);
				}
				if (_5$$5) {
					zephir_array_append(&filtered, &asset, PH_SEPARATE, "phalcon/Assets/Manager.zep", 249);
				}
		}
	}
	ZEPHIR_INIT_NVAR(&asset);
	RETURN_CTOR(&filtered);
}

/**
 * Returns true or false if collection exists.
 *
 * ```php
 * if ($manager->exists("jsHeader")) {
 *     // \Phalcon\Assets\Collection
 *     $collection = $manager->get("jsHeader");
 * }
 * ```
 *
 * @param string $name
 * @deprecated
 */
PHP_METHOD(Phalcon_Assets_Manager, exists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "has", NULL, 0, &name_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns a collection by its id.
 *
 * ```php
 * $scripts = $assets->get("js");
 * ```
 *
 * @param string $name
 *
 * @return Collection
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, get)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval name_zv, _0, _1, _2;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("collections", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 292, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(1 != zephir_array_isset_value(&_0, &name_zv))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The collection does not exist in the manager", "phalcon/Assets/Manager.zep", 289);
		return;
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 292, PH_NOISY_CC | PH_READONLY);
	zephir_memory_observe(&_2);
	zephir_array_fetch(&_2, &_1, &name_zv, PH_NOISY, "phalcon/Assets/Manager.zep", 292);
	RETURN_CCTOR(&_2);
}

/**
 * Returns existing collections in the manager
 *
 * @return Collection[]
 */
PHP_METHOD(Phalcon_Assets_Manager, getCollections)
{

	RETURN_MEMBER_TYPED(getThis(), "collections", IS_ARRAY);
}

/**
 * Returns the CSS collection of assets
 *
 * @return Collection
 */
PHP_METHOD(Phalcon_Assets_Manager, getCss)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "css");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "checkAndCreateCollection", NULL, 174, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the CSS collection of assets
 *
 * @return Collection
 */
PHP_METHOD(Phalcon_Assets_Manager, getJs)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "js");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "checkAndCreateCollection", NULL, 174, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the manager options
 */
PHP_METHOD(Phalcon_Assets_Manager, getOptions)
{

	RETURN_MEMBER_TYPED(getThis(), "options", IS_ARRAY);
}

/**
 * Returns true or false if collection exists.
 *
 * ```php
 * if ($manager->has("jsHeader")) {
 *     // \Phalcon\Assets\Collection
 *     $collection = $manager->get("jsHeader");
 * }
 * ```
 *
 * @param string $name
 */
PHP_METHOD(Phalcon_Assets_Manager, has)
{
	zval name_zv, _0;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("collections", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&name_zv, name);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 292, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_value(&_0, &name_zv));
}

/**
 * Traverses a collection calling the callback to generate its HTML
 *
 * @param Collection $collection
 * @param string     $type
 *
 * @return string|null
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, output)
{
	zend_bool filterNeeded = 0, _40, _66, _32$$25, _60$$53;
	zval output;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL, *_26 = NULL, *_37 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *type = NULL;
	zval *collection, collection_sub, type_zv, asset, assets, callback, callbackMethod, collectionSourcePath, collectionTargetPath, completeSourcePath, completeTargetPath, content, filter, filters, filteredContent, filteredJoinedContent, html, join, mustFilter, options, prefixedPath, sourceBasePath, sourcePath, targetBasePath, targetPath, typeCss, _0, _1, _2, *_8, _9, *_10, _39, _3$$9, _4$$9, _5$$8, _6$$10, _7$$10, _11$$12, _16$$12, _12$$14, _13$$14, _14$$15, _15$$15, _17$$17, _18$$17, _19$$18, _20$$18, _21$$21, _22$$21, _24$$21, _25$$21, _27$$21, *_28$$25, _29$$25, *_30$$25, _31$$25, _33$$30, _34$$36, _35$$36, _36$$36, _38$$36, _41$$40, _46$$40, _42$$42, _43$$42, _44$$43, _45$$43, _47$$45, _48$$45, _49$$46, _50$$46, _51$$49, _52$$49, _53$$49, _54$$49, _55$$49, *_56$$53, _57$$53, *_58$$53, _59$$53, _61$$58, _62$$64, _63$$64, _64$$64, _65$$64, _67$$67, _68$$67, _69$$67, _70$$67;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&asset);
	ZVAL_UNDEF(&assets);
	ZVAL_UNDEF(&callback);
	ZVAL_UNDEF(&callbackMethod);
	ZVAL_UNDEF(&collectionSourcePath);
	ZVAL_UNDEF(&collectionTargetPath);
	ZVAL_UNDEF(&completeSourcePath);
	ZVAL_UNDEF(&completeTargetPath);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&filteredContent);
	ZVAL_UNDEF(&filteredJoinedContent);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&mustFilter);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&prefixedPath);
	ZVAL_UNDEF(&sourceBasePath);
	ZVAL_UNDEF(&sourcePath);
	ZVAL_UNDEF(&targetBasePath);
	ZVAL_UNDEF(&targetPath);
	ZVAL_UNDEF(&typeCss);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_3$$9);
	ZVAL_UNDEF(&_4$$9);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_11$$12);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_12$$14);
	ZVAL_UNDEF(&_13$$14);
	ZVAL_UNDEF(&_14$$15);
	ZVAL_UNDEF(&_15$$15);
	ZVAL_UNDEF(&_17$$17);
	ZVAL_UNDEF(&_18$$17);
	ZVAL_UNDEF(&_19$$18);
	ZVAL_UNDEF(&_20$$18);
	ZVAL_UNDEF(&_21$$21);
	ZVAL_UNDEF(&_22$$21);
	ZVAL_UNDEF(&_24$$21);
	ZVAL_UNDEF(&_25$$21);
	ZVAL_UNDEF(&_27$$21);
	ZVAL_UNDEF(&_29$$25);
	ZVAL_UNDEF(&_31$$25);
	ZVAL_UNDEF(&_33$$30);
	ZVAL_UNDEF(&_34$$36);
	ZVAL_UNDEF(&_35$$36);
	ZVAL_UNDEF(&_36$$36);
	ZVAL_UNDEF(&_38$$36);
	ZVAL_UNDEF(&_41$$40);
	ZVAL_UNDEF(&_46$$40);
	ZVAL_UNDEF(&_42$$42);
	ZVAL_UNDEF(&_43$$42);
	ZVAL_UNDEF(&_44$$43);
	ZVAL_UNDEF(&_45$$43);
	ZVAL_UNDEF(&_47$$45);
	ZVAL_UNDEF(&_48$$45);
	ZVAL_UNDEF(&_49$$46);
	ZVAL_UNDEF(&_50$$46);
	ZVAL_UNDEF(&_51$$49);
	ZVAL_UNDEF(&_52$$49);
	ZVAL_UNDEF(&_53$$49);
	ZVAL_UNDEF(&_54$$49);
	ZVAL_UNDEF(&_55$$49);
	ZVAL_UNDEF(&_57$$53);
	ZVAL_UNDEF(&_59$$53);
	ZVAL_UNDEF(&_61$$58);
	ZVAL_UNDEF(&_62$$64);
	ZVAL_UNDEF(&_63$$64);
	ZVAL_UNDEF(&_64$$64);
	ZVAL_UNDEF(&_65$$64);
	ZVAL_UNDEF(&_67$$67);
	ZVAL_UNDEF(&_68$$67);
	ZVAL_UNDEF(&_69$$67);
	ZVAL_UNDEF(&_70$$67);
	ZVAL_UNDEF(&output);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("implicitOutput", 14, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(collection, phalcon_assets_collection_ce)
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	collection = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	ZEPHIR_INIT_VAR(&targetPath);
	ZEPHIR_INIT_VAR(&completeSourcePath);
	ZVAL_STRING(&completeSourcePath, "");
	ZEPHIR_INIT_VAR(&completeTargetPath);
	ZVAL_STRING(&completeTargetPath, "");
	ZEPHIR_INIT_VAR(&filteredContent);
	ZVAL_STRING(&filteredContent, "");
	ZEPHIR_INIT_VAR(&filteredJoinedContent);
	ZVAL_STRING(&filteredJoinedContent, "");
	ZEPHIR_INIT_VAR(&join);
	ZVAL_BOOL(&join, 0);
	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 291, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&options, &_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "css");
	if (ZEPHIR_IS_IDENTICAL(&_1, &type_zv)) {
		ZEPHIR_INIT_VAR(&callbackMethod);
		ZVAL_STRING(&callbackMethod, "cssLink");
	} else {
		ZEPHIR_INIT_NVAR(&callbackMethod);
		ZVAL_STRING(&callbackMethod, "jsLink");
	}
	ZEPHIR_INIT_VAR(&callback);
	zephir_create_array(&callback, 2, 0);
	zephir_array_fast_append(&callback, this_ptr);
	zephir_array_fast_append(&callback, &callbackMethod);
	ZEPHIR_CALL_METHOD(&_2, collection, "getAssets", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&assets, this_ptr, "collectionAssetsByType", NULL, 0, &_2, &type_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&filters, collection, "getFilters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&typeCss);
	ZVAL_STRING(&typeCss, "css");
	if (1 != ZEPHIR_IS_EMPTY(&filters)) {
		zephir_memory_observe(&sourceBasePath);
		if (!(zephir_array_isset_string_fetch(&sourceBasePath, &options, SL("sourceBasePath"), 0))) {
			ZEPHIR_INIT_NVAR(&sourceBasePath);
			ZVAL_STRING(&sourceBasePath, "");
		}
		zephir_memory_observe(&targetBasePath);
		if (!(zephir_array_isset_string_fetch(&targetBasePath, &options, SL("targetBasePath"), 0))) {
			ZEPHIR_INIT_NVAR(&targetBasePath);
			ZVAL_STRING(&targetBasePath, "");
		}
		ZEPHIR_CALL_METHOD(&collectionSourcePath, collection, "getSourcePath", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&completeSourcePath, &sourceBasePath);
		if (1 != ZEPHIR_IS_EMPTY(&collectionSourcePath)) {
			zephir_concat_self(&completeSourcePath, &collectionSourcePath);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&collectionTargetPath, collection, "getTargetPath", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&completeTargetPath, &targetBasePath);
		if (1 != ZEPHIR_IS_EMPTY(&collectionTargetPath)) {
			zephir_concat_self(&completeTargetPath, &collectionTargetPath);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_INIT_NVAR(&filteredJoinedContent);
		ZVAL_STRING(&filteredJoinedContent, "");
		ZEPHIR_CALL_METHOD(&join, collection, "getJoin", NULL, 0);
		zephir_check_call_status();
		if (!(zephir_is_true(&join))) {
			if (1 == ZEPHIR_IS_EMPTY(&completeTargetPath)) {
				ZEPHIR_INIT_VAR(&_3$$9);
				object_init_ex(&_3$$9, phalcon_assets_exception_ce);
				ZEPHIR_INIT_VAR(&_4$$9);
				ZEPHIR_CONCAT_SVS(&_4$$9, "Path '", &completeTargetPath, "' is not a valid target path (1)");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_3$$9, "__construct", NULL, 32, &_4$$9);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_3$$9, "phalcon/Assets/Manager.zep", 457);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_FUNCTION(&_5$$8, "is_dir", NULL, 140, &completeTargetPath);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_5$$8)) {
				ZEPHIR_INIT_VAR(&_6$$10);
				object_init_ex(&_6$$10, phalcon_assets_exception_ce);
				ZEPHIR_INIT_VAR(&_7$$10);
				ZEPHIR_CONCAT_SVS(&_7$$10, "Path '", &completeTargetPath, "' is not a valid target path (2), it is a directory.");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_6$$10, "__construct", NULL, 32, &_7$$10);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_6$$10, "phalcon/Assets/Manager.zep", 463);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	if (Z_TYPE_P(&assets) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_9);
		zephir_string_to_char_array(&_9, &assets);
		_8 = &_9;
	} else {
		_8 = &assets;
	}
	zephir_is_iterable(_8, 0, "phalcon/Assets/Manager.zep", 652);
	if (Z_TYPE_P(_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_8), _10)
		{
			ZEPHIR_INIT_NVAR(&asset);
			ZVAL_COPY(&asset, _10);
			filterNeeded = 0;
			if (1 != ZEPHIR_IS_EMPTY(&filters)) {
				ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getPath", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_11$$12, &asset, "isLocal", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_TRUE_IDENTICAL(&_11$$12)) {
					filterNeeded = 1;
					ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getRealSourcePath", NULL, 0, &completeSourcePath);
					zephir_check_call_status();
					if (1 == ZEPHIR_IS_EMPTY(&sourcePath)) {
						ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getPath", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_12$$14);
						object_init_ex(&_12$$14, phalcon_assets_exception_ce);
						ZEPHIR_INIT_NVAR(&_13$$14);
						ZEPHIR_CONCAT_SVS(&_13$$14, "Asset '", &sourcePath, "' does not have a valid source path");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_12$$14, "__construct", NULL, 32, &_13$$14);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_12$$14, "phalcon/Assets/Manager.zep", 493);
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				ZEPHIR_CALL_METHOD(&targetPath, &asset, "getRealTargetPath", NULL, 0, &completeTargetPath);
				zephir_check_call_status();
				if (1 == ZEPHIR_IS_EMPTY(&targetPath)) {
					ZEPHIR_INIT_NVAR(&_14$$15);
					object_init_ex(&_14$$15, phalcon_assets_exception_ce);
					ZEPHIR_INIT_NVAR(&_15$$15);
					ZEPHIR_CONCAT_SVS(&_15$$15, "Asset '", &sourcePath, "' does not have a valid target path");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_14$$15, "__construct", NULL, 32, &_15$$15);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_14$$15, "phalcon/Assets/Manager.zep", 509);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_16$$12, &asset, "isLocal", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_TRUE_IDENTICAL(&_16$$12)) {
					if (ZEPHIR_IS_IDENTICAL(&targetPath, &sourcePath)) {
						ZEPHIR_INIT_NVAR(&_17$$17);
						object_init_ex(&_17$$17, phalcon_assets_exception_ce);
						ZEPHIR_INIT_NVAR(&_18$$17);
						ZEPHIR_CONCAT_SVS(&_18$$17, "Asset '", &targetPath, "' have the same source and target paths");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_17$$17, "__construct", NULL, 32, &_18$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_17$$17, "phalcon/Assets/Manager.zep", 519);
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (1 == (zephir_file_exists(&targetPath) == SUCCESS)) {
						ZEPHIR_INIT_NVAR(&_19$$18);
						zephir_filemtime(&_19$$18, &targetPath);
						ZEPHIR_INIT_NVAR(&_20$$18);
						zephir_filemtime(&_20$$18, &sourcePath);
						if (!ZEPHIR_IS_IDENTICAL(&_19$$18, &_20$$18)) {
							filterNeeded = 1;
						}
					} else {
						filterNeeded = 1;
					}
				}
			} else {
				ZEPHIR_CALL_METHOD(&_21$$21, &asset, "getRealTargetUri", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_22$$21, &asset, "getRealSourcePath", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "calculatePrefixedPath", &_23, 179, collection, &_21$$21, &_22$$21);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_24$$21, &asset, "getAttributes", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_25$$21, &asset, "isLocal", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&html, this_ptr, "doCallback", &_26, 180, &callback, &_24$$21, &prefixedPath, &_25$$21);
				zephir_check_call_status();
				zephir_read_property_cached(&_27$$21, this_ptr, _zephir_prop_1, 293, PH_NOISY_CC | PH_READONLY);
				if (ZEPHIR_IS_TRUE_IDENTICAL(&_27$$21)) {
					zend_print_zval(&html, 0);
				} else {
					zephir_concat_self(&output, &html);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				continue;
			}
			if (filterNeeded) {
				ZEPHIR_CALL_METHOD(&content, &asset, "getContent", NULL, 0, &completeSourcePath);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&mustFilter, &asset, "getFilter", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(&mustFilter)) {
					if (Z_TYPE_P(&filters) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_29$$25);
						zephir_string_to_char_array(&_29$$25, &filters);
						_28$$25 = &_29$$25;
					} else {
						_28$$25 = &filters;
					}
					zephir_is_iterable(_28$$25, 0, "phalcon/Assets/Manager.zep", 595);
					if (Z_TYPE_P(_28$$25) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_28$$25), _30$$25)
						{
							ZEPHIR_INIT_NVAR(&filter);
							ZVAL_COPY(&filter, _30$$25);
							if (Z_TYPE_P(&filter) != IS_OBJECT) {
								ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 581);
								return;
							}
							ZEPHIR_CALL_METHOD(&filteredContent, &filter, "filter", NULL, 0, &content);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&content, &filteredContent);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _28$$25, "rewind", NULL, 0);
						zephir_check_call_status();
						_32$$25 = 1;
						while (1) {
							if (_32$$25) {
								_32$$25 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _28$$25, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_31$$25, _28$$25, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_31$$25)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&filter, _28$$25, "current", NULL, 0);
							zephir_check_call_status();
								if (Z_TYPE_P(&filter) != IS_OBJECT) {
									ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 581);
									return;
								}
								ZEPHIR_CALL_METHOD(&filteredContent, &filter, "filter", NULL, 0, &content);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&content, &filteredContent);
						}
					}
					ZEPHIR_INIT_NVAR(&filter);
					if (zephir_is_true(&join)) {
						zephir_concat_self(&filteredJoinedContent, &filteredContent);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(&_33$$30, &asset, "getType", NULL, 0);
						zephir_check_call_status();
						if (!ZEPHIR_IS_IDENTICAL(&_33$$30, &typeCss)) {
							zephir_concat_self_str(&filteredJoinedContent, SL(";"));
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
				} else {
					if (zephir_is_true(&join)) {
						zephir_concat_self(&filteredJoinedContent, &content);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CPY_WRT(&filteredContent, &content);
					}
				}
				if (!zephir_is_true(&join)) {
					zephir_file_put_contents(NULL, &targetPath, &filteredContent);
				}
			}
			if (!zephir_is_true(&join)) {
				ZEPHIR_CALL_METHOD(&_34$$36, &asset, "getRealTargetUri", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_35$$36, &asset, "getRealSourcePath", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "calculatePrefixedPath", &_23, 179, collection, &_34$$36, &_35$$36);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_36$$36, collection, "getAttributes", &_37, 0);
				zephir_check_call_status();
				ZVAL_BOOL(&_38$$36, 1);
				ZEPHIR_CALL_METHOD(&html, this_ptr, "doCallback", &_26, 180, &callback, &_36$$36, &prefixedPath, &_38$$36);
				zephir_check_call_status();
				zephir_read_property_cached(&_38$$36, this_ptr, _zephir_prop_1, 293, PH_NOISY_CC | PH_READONLY);
				if (ZEPHIR_IS_TRUE_IDENTICAL(&_38$$36)) {
					zend_print_zval(&html, 0);
				} else {
					zephir_concat_self(&output, &html);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _8, "rewind", NULL, 0);
		zephir_check_call_status();
		_40 = 1;
		while (1) {
			if (_40) {
				_40 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _8, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_39, _8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_39)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&asset, _8, "current", NULL, 0);
			zephir_check_call_status();
				filterNeeded = 0;
				if (1 != ZEPHIR_IS_EMPTY(&filters)) {
					ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getPath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_41$$40, &asset, "isLocal", NULL, 0);
					zephir_check_call_status();
					if (ZEPHIR_IS_TRUE_IDENTICAL(&_41$$40)) {
						filterNeeded = 1;
						ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getRealSourcePath", NULL, 0, &completeSourcePath);
						zephir_check_call_status();
						if (1 == ZEPHIR_IS_EMPTY(&sourcePath)) {
							ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getPath", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_42$$42);
							object_init_ex(&_42$$42, phalcon_assets_exception_ce);
							ZEPHIR_INIT_NVAR(&_43$$42);
							ZEPHIR_CONCAT_SVS(&_43$$42, "Asset '", &sourcePath, "' does not have a valid source path");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_42$$42, "__construct", NULL, 32, &_43$$42);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_42$$42, "phalcon/Assets/Manager.zep", 493);
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					ZEPHIR_CALL_METHOD(&targetPath, &asset, "getRealTargetPath", NULL, 0, &completeTargetPath);
					zephir_check_call_status();
					if (1 == ZEPHIR_IS_EMPTY(&targetPath)) {
						ZEPHIR_INIT_NVAR(&_44$$43);
						object_init_ex(&_44$$43, phalcon_assets_exception_ce);
						ZEPHIR_INIT_NVAR(&_45$$43);
						ZEPHIR_CONCAT_SVS(&_45$$43, "Asset '", &sourcePath, "' does not have a valid target path");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_44$$43, "__construct", NULL, 32, &_45$$43);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_44$$43, "phalcon/Assets/Manager.zep", 509);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(&_46$$40, &asset, "isLocal", NULL, 0);
					zephir_check_call_status();
					if (ZEPHIR_IS_TRUE_IDENTICAL(&_46$$40)) {
						if (ZEPHIR_IS_IDENTICAL(&targetPath, &sourcePath)) {
							ZEPHIR_INIT_NVAR(&_47$$45);
							object_init_ex(&_47$$45, phalcon_assets_exception_ce);
							ZEPHIR_INIT_NVAR(&_48$$45);
							ZEPHIR_CONCAT_SVS(&_48$$45, "Asset '", &targetPath, "' have the same source and target paths");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_47$$45, "__construct", NULL, 32, &_48$$45);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_47$$45, "phalcon/Assets/Manager.zep", 519);
							ZEPHIR_MM_RESTORE();
							return;
						}
						if (1 == (zephir_file_exists(&targetPath) == SUCCESS)) {
							ZEPHIR_INIT_NVAR(&_49$$46);
							zephir_filemtime(&_49$$46, &targetPath);
							ZEPHIR_INIT_NVAR(&_50$$46);
							zephir_filemtime(&_50$$46, &sourcePath);
							if (!ZEPHIR_IS_IDENTICAL(&_49$$46, &_50$$46)) {
								filterNeeded = 1;
							}
						} else {
							filterNeeded = 1;
						}
					}
				} else {
					ZEPHIR_CALL_METHOD(&_51$$49, &asset, "getRealTargetUri", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_52$$49, &asset, "getRealSourcePath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "calculatePrefixedPath", &_23, 179, collection, &_51$$49, &_52$$49);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_53$$49, &asset, "getAttributes", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_54$$49, &asset, "isLocal", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&html, this_ptr, "doCallback", &_26, 180, &callback, &_53$$49, &prefixedPath, &_54$$49);
					zephir_check_call_status();
					zephir_read_property_cached(&_55$$49, this_ptr, _zephir_prop_1, 293, PH_NOISY_CC | PH_READONLY);
					if (ZEPHIR_IS_TRUE_IDENTICAL(&_55$$49)) {
						zend_print_zval(&html, 0);
					} else {
						zephir_concat_self(&output, &html);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					continue;
				}
				if (filterNeeded) {
					ZEPHIR_CALL_METHOD(&content, &asset, "getContent", NULL, 0, &completeSourcePath);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&mustFilter, &asset, "getFilter", NULL, 0);
					zephir_check_call_status();
					if (zephir_is_true(&mustFilter)) {
						if (Z_TYPE_P(&filters) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_57$$53);
							zephir_string_to_char_array(&_57$$53, &filters);
							_56$$53 = &_57$$53;
						} else {
							_56$$53 = &filters;
						}
						zephir_is_iterable(_56$$53, 0, "phalcon/Assets/Manager.zep", 595);
						if (Z_TYPE_P(_56$$53) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_56$$53), _58$$53)
							{
								ZEPHIR_INIT_NVAR(&filter);
								ZVAL_COPY(&filter, _58$$53);
								if (Z_TYPE_P(&filter) != IS_OBJECT) {
									ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 581);
									return;
								}
								ZEPHIR_CALL_METHOD(&filteredContent, &filter, "filter", NULL, 0, &content);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&content, &filteredContent);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _56$$53, "rewind", NULL, 0);
							zephir_check_call_status();
							_60$$53 = 1;
							while (1) {
								if (_60$$53) {
									_60$$53 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _56$$53, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_59$$53, _56$$53, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_59$$53)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&filter, _56$$53, "current", NULL, 0);
								zephir_check_call_status();
									if (Z_TYPE_P(&filter) != IS_OBJECT) {
										ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 581);
										return;
									}
									ZEPHIR_CALL_METHOD(&filteredContent, &filter, "filter", NULL, 0, &content);
									zephir_check_call_status();
									ZEPHIR_CPY_WRT(&content, &filteredContent);
							}
						}
						ZEPHIR_INIT_NVAR(&filter);
						if (zephir_is_true(&join)) {
							zephir_concat_self(&filteredJoinedContent, &filteredContent);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(&_61$$58, &asset, "getType", NULL, 0);
							zephir_check_call_status();
							if (!ZEPHIR_IS_IDENTICAL(&_61$$58, &typeCss)) {
								zephir_concat_self_str(&filteredJoinedContent, SL(";"));
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
							}
						}
					} else {
						if (zephir_is_true(&join)) {
							zephir_concat_self(&filteredJoinedContent, &content);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
						} else {
							ZEPHIR_CPY_WRT(&filteredContent, &content);
						}
					}
					if (!zephir_is_true(&join)) {
						zephir_file_put_contents(NULL, &targetPath, &filteredContent);
					}
				}
				if (!zephir_is_true(&join)) {
					ZEPHIR_CALL_METHOD(&_62$$64, &asset, "getRealTargetUri", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_63$$64, &asset, "getRealSourcePath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "calculatePrefixedPath", &_23, 179, collection, &_62$$64, &_63$$64);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_64$$64, collection, "getAttributes", &_37, 0);
					zephir_check_call_status();
					ZVAL_BOOL(&_65$$64, 1);
					ZEPHIR_CALL_METHOD(&html, this_ptr, "doCallback", &_26, 180, &callback, &_64$$64, &prefixedPath, &_65$$64);
					zephir_check_call_status();
					zephir_read_property_cached(&_65$$64, this_ptr, _zephir_prop_1, 293, PH_NOISY_CC | PH_READONLY);
					if (ZEPHIR_IS_TRUE_IDENTICAL(&_65$$64)) {
						zend_print_zval(&html, 0);
					} else {
						zephir_concat_self(&output, &html);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&asset);
	_66 = 1 != ZEPHIR_IS_EMPTY(&filters);
	if (_66) {
		_66 = zephir_is_true(&join);
	}
	if (_66) {
		zephir_file_put_contents(NULL, &completeTargetPath, &filteredJoinedContent);
		ZEPHIR_CALL_METHOD(&_67$$67, collection, "getTargetUri", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "calculatePrefixedPath", &_23, 179, collection, &_67$$67, &completeTargetPath);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_68$$67, collection, "getAttributes", &_37, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_69$$67, collection, "getTargetIsLocal", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&html, this_ptr, "doCallback", &_26, 180, &callback, &_68$$67, &prefixedPath, &_69$$67);
		zephir_check_call_status();
		zephir_read_property_cached(&_70$$67, this_ptr, _zephir_prop_1, 293, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_70$$67)) {
			zend_print_zval(&html, 0);
		} else {
			zephir_concat_self(&output, &html);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CTOR(&output);
}

/**
 * Prints the HTML for CSS assets
 *
 * @param string|null $name
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, outputCss)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, collection, _0;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	ZEPHIR_CALL_METHOD(&collection, this_ptr, "getCss", NULL, 0);
	zephir_check_call_status();
	if (1 != ZEPHIR_IS_EMPTY(&name_zv)) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &name_zv);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "css");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "output", NULL, 0, &collection, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Traverses a collection and generate its HTML
 *
 * @param Collection $collection
 * @param string     $type
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, outputInline)
{
	zend_bool _16$$3, _8$$4, _22$$11;
	zval html, joinedContent, output;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collection, collection_sub, *type, type_sub, attributes, code, codes, content, filter, filters, join, *_0$$3, _1$$3, *_2$$3, _15$$3, _34$$3, *_3$$4, _4$$4, *_5$$4, _7$$4, _6$$5, _9$$7, _10$$10, _11$$10, _12$$10, _13$$10, _14$$10, *_17$$11, _18$$11, *_19$$11, _21$$11, _20$$12, _23$$14, _24$$17, _25$$17, _26$$17, _27$$17, _28$$17, _29$$18, _30$$18, _31$$18, _32$$18, _33$$18;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&type_sub);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&codes);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_34$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_21$$11);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_24$$17);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_28$$17);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_31$$18);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_33$$18);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&joinedContent);
	ZVAL_UNDEF(&output);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("tagFactory", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("implicitOutput", 14, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(collection, phalcon_assets_collection_ce)
		Z_PARAM_ZVAL(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &collection, &type);
	ZEPHIR_INIT_VAR(&attributes);
	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	ZEPHIR_INIT_VAR(&html);
	ZVAL_STRING(&html, "");
	ZEPHIR_INIT_VAR(&joinedContent);
	ZVAL_STRING(&joinedContent, "");
	ZEPHIR_CALL_METHOD(&codes, collection, "getCodes", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&filters, collection, "getFilters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&join, collection, "getJoin", NULL, 0);
	zephir_check_call_status();
	if (1 != ZEPHIR_IS_EMPTY(&codes)) {
		if (Z_TYPE_P(&codes) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_string_to_char_array(&_1$$3, &codes);
			_0$$3 = &_1$$3;
		} else {
			_0$$3 = &codes;
		}
		zephir_is_iterable(_0$$3, 0, "phalcon/Assets/Manager.zep", 764);
		if (Z_TYPE_P(_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$3), _2$$3)
			{
				ZEPHIR_INIT_NVAR(&code);
				ZVAL_COPY(&code, _2$$3);
				ZEPHIR_CALL_METHOD(&attributes, &code, "getAttributes", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&content, &code, "getContent", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&filters) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_4$$4);
					zephir_string_to_char_array(&_4$$4, &filters);
					_3$$4 = &_4$$4;
				} else {
					_3$$4 = &filters;
				}
				zephir_is_iterable(_3$$4, 0, "phalcon/Assets/Manager.zep", 752);
				if (Z_TYPE_P(_3$$4) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3$$4), _5$$4)
					{
						ZEPHIR_INIT_NVAR(&filter);
						ZVAL_COPY(&filter, _5$$4);
						if (Z_TYPE_P(&filter) != IS_OBJECT) {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 742);
							return;
						}
						ZEPHIR_CALL_METHOD(&_6$$5, &filter, "filter", NULL, 0, &content);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&content, &_6$$5);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _3$$4, "rewind", NULL, 0);
					zephir_check_call_status();
					_8$$4 = 1;
					while (1) {
						if (_8$$4) {
							_8$$4 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _3$$4, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_7$$4, _3$$4, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_7$$4)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&filter, _3$$4, "current", NULL, 0);
						zephir_check_call_status();
							if (Z_TYPE_P(&filter) != IS_OBJECT) {
								ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 742);
								return;
							}
							ZEPHIR_CALL_METHOD(&_9$$7, &filter, "filter", NULL, 0, &content);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&content, &_9$$7);
					}
				}
				ZEPHIR_INIT_NVAR(&filter);
				if (ZEPHIR_IS_TRUE_IDENTICAL(&join)) {
					zephir_concat_self(&joinedContent, &content);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					zephir_read_property_cached(&_10$$10, this_ptr, _zephir_prop_0, 290, PH_NOISY_CC | PH_READONLY);
					ZVAL_BOOL(&_12$$10, 1);
					ZEPHIR_CALL_METHOD(&_11$$10, &_10$$10, "element", NULL, 0, type, &content, &attributes, &_12$$10);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_13$$10);
					ZEPHIR_GET_CONSTANT(&_13$$10, "PHP_EOL");
					ZEPHIR_INIT_NVAR(&_14$$10);
					ZEPHIR_CONCAT_VV(&_14$$10, &_11$$10, &_13$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_concat_self(&html, &_14$$10);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _0$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_16$$3 = 1;
			while (1) {
				if (_16$$3) {
					_16$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _0$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_15$$3, _0$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_15$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&code, _0$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&attributes, &code, "getAttributes", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&content, &code, "getContent", NULL, 0);
					zephir_check_call_status();
					if (Z_TYPE_P(&filters) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_18$$11);
						zephir_string_to_char_array(&_18$$11, &filters);
						_17$$11 = &_18$$11;
					} else {
						_17$$11 = &filters;
					}
					zephir_is_iterable(_17$$11, 0, "phalcon/Assets/Manager.zep", 752);
					if (Z_TYPE_P(_17$$11) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_17$$11), _19$$11)
						{
							ZEPHIR_INIT_NVAR(&filter);
							ZVAL_COPY(&filter, _19$$11);
							if (Z_TYPE_P(&filter) != IS_OBJECT) {
								ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 742);
								return;
							}
							ZEPHIR_CALL_METHOD(&_20$$12, &filter, "filter", NULL, 0, &content);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&content, &_20$$12);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _17$$11, "rewind", NULL, 0);
						zephir_check_call_status();
						_22$$11 = 1;
						while (1) {
							if (_22$$11) {
								_22$$11 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _17$$11, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_21$$11, _17$$11, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_21$$11)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&filter, _17$$11, "current", NULL, 0);
							zephir_check_call_status();
								if (Z_TYPE_P(&filter) != IS_OBJECT) {
									ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The filter is not valid", "phalcon/Assets/Manager.zep", 742);
									return;
								}
								ZEPHIR_CALL_METHOD(&_23$$14, &filter, "filter", NULL, 0, &content);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&content, &_23$$14);
						}
					}
					ZEPHIR_INIT_NVAR(&filter);
					if (ZEPHIR_IS_TRUE_IDENTICAL(&join)) {
						zephir_concat_self(&joinedContent, &content);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						zephir_read_property_cached(&_24$$17, this_ptr, _zephir_prop_0, 290, PH_NOISY_CC | PH_READONLY);
						ZVAL_BOOL(&_26$$17, 1);
						ZEPHIR_CALL_METHOD(&_25$$17, &_24$$17, "element", NULL, 0, type, &content, &attributes, &_26$$17);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_27$$17);
						ZEPHIR_GET_CONSTANT(&_27$$17, "PHP_EOL");
						ZEPHIR_INIT_NVAR(&_28$$17);
						ZEPHIR_CONCAT_VV(&_28$$17, &_25$$17, &_27$$17);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_concat_self(&html, &_28$$17);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
			}
		}
		ZEPHIR_INIT_NVAR(&code);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&join)) {
			zephir_read_property_cached(&_29$$18, this_ptr, _zephir_prop_0, 290, PH_NOISY_CC | PH_READONLY);
			ZVAL_BOOL(&_31$$18, 1);
			ZEPHIR_CALL_METHOD(&_30$$18, &_29$$18, "element", NULL, 0, type, &joinedContent, &attributes, &_31$$18);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_32$$18);
			ZEPHIR_GET_CONSTANT(&_32$$18, "PHP_EOL");
			ZEPHIR_INIT_VAR(&_33$$18);
			ZEPHIR_CONCAT_VV(&_33$$18, &_30$$18, &_32$$18);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_concat_self(&html, &_33$$18);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		zephir_read_property_cached(&_34$$3, this_ptr, _zephir_prop_1, 293, PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&_34$$3)) {
			zend_print_zval(&html, 0);
		} else {
			zephir_concat_self(&output, &html);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CTOR(&output);
}

/**
 * Prints the HTML for inline CSS
 *
 * @param string|null $name
 *
 * @return string
 */
PHP_METHOD(Phalcon_Assets_Manager, outputInlineCss)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, collection, _0;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	ZEPHIR_CALL_METHOD(&collection, this_ptr, "getCss", NULL, 0);
	zephir_check_call_status();
	if (1 != ZEPHIR_IS_EMPTY(&name_zv)) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &name_zv);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "style");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "outputInline", NULL, 0, &collection, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Prints the HTML for inline JS
 *
 * @param string|null $name
 *
 * @return string
 */
PHP_METHOD(Phalcon_Assets_Manager, outputInlineJs)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, collection, _0;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	ZEPHIR_CALL_METHOD(&collection, this_ptr, "getJs", NULL, 0);
	zephir_check_call_status();
	if (1 != ZEPHIR_IS_EMPTY(&name_zv)) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &name_zv);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "script");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "outputInline", NULL, 0, &collection, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Prints the HTML for JS assets
 *
 * @param string|null $name
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, outputJs)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval name_zv, collection, _0;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!name) {
		ZEPHIR_INIT_VAR(&name_zv);
	} else {
		zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	}
	ZEPHIR_CALL_METHOD(&collection, this_ptr, "getJs", NULL, 0);
	zephir_check_call_status();
	if (1 != ZEPHIR_IS_EMPTY(&name_zv)) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &name_zv);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "js");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "output", NULL, 0, &collection, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Sets a collection in the Assets Manager
 *
 *```php
 * $assets->set("js", $collection);
 *```
 *
 * @param string     $name
 * @param Collection $collection
 */
PHP_METHOD(Phalcon_Assets_Manager, set)
{
	zval name_zv, *collection, collection_sub;
	zend_string *name = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&collection_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(name)
		Z_PARAM_OBJECT_OF_CLASS(collection, phalcon_assets_collection_ce)
	ZEND_PARSE_PARAMETERS_END();
	collection = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&name_zv, name);
	zephir_update_property_array(this_ptr, SL("collections"), &name_zv, collection);
	RETURN_THISW();
}

/**
 * Sets the manager options
 *
 * @param array $options
 */
PHP_METHOD(Phalcon_Assets_Manager, setOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *options_param = NULL;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("options", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &options_param);
	zephir_get_arrval(&options, options_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 291, &options);
	RETURN_THIS();
}

/**
 * Sets if the HTML generated must be directly printed or returned
 *
 * @param bool $implicitOutput
 */
PHP_METHOD(Phalcon_Assets_Manager, useImplicitOutput)
{
	zval *implicitOutput_param = NULL, __$true, __$false;
	zend_bool implicitOutput;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("implicitOutput", 14, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(implicitOutput)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &implicitOutput_param);
	if (implicitOutput) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 293, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 293, &__$false);
	}
	RETURN_THISW();
}

/**
 * Calculates the prefixed path including the version
 *
 * @param Collection $collection
 * @param string     $path
 * @param string     $filePath
 *
 * @return string
 */
PHP_METHOD(Phalcon_Assets_Manager, calculatePrefixedPath)
{
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *path = NULL, *filePath = NULL;
	zval *collection, collection_sub, path_zv, filePath_zv, modificationTime, prefixedPath, version, _0, _1, _3, _4$$3, _5$$4;

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&filePath_zv);
	ZVAL_UNDEF(&modificationTime);
	ZVAL_UNDEF(&prefixedPath);
	ZVAL_UNDEF(&version);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(collection, phalcon_assets_collection_ce)
		Z_PARAM_STR(path)
		Z_PARAM_STR(filePath)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	collection = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	zephir_memory_observe(&filePath_zv);
	ZVAL_STR_COPY(&filePath_zv, filePath);
	ZEPHIR_CALL_METHOD(&_0, collection, "getPrefix", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&prefixedPath);
	ZEPHIR_CONCAT_VV(&prefixedPath, &_0, &path_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&version, collection, "getVersion", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, collection, "isAutoVersion", NULL, 0);
	zephir_check_call_status();
	_2 = ZEPHIR_IS_TRUE_IDENTICAL(&_1);
	if (_2) {
		ZEPHIR_CALL_METHOD(&_3, collection, "isLocal", NULL, 0);
		zephir_check_call_status();
		_2 = ZEPHIR_IS_TRUE_IDENTICAL(&_3);
	}
	if (_2) {
		ZEPHIR_INIT_VAR(&modificationTime);
		zephir_filemtime(&modificationTime, &filePath_zv);
		ZEPHIR_INIT_VAR(&_4$$3);
		if (zephir_is_true(&version)) {
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZEPHIR_CONCAT_VSV(&_4$$3, &version, ".", &modificationTime);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(&_4$$3, &modificationTime);
		}
		ZEPHIR_CPY_WRT(&version, &_4$$3);
	}
	if (zephir_is_true(&version)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		ZEPHIR_CONCAT_VSV(&_5$$4, &prefixedPath, "?ver=", &version);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&prefixedPath, &_5$$4);
	}
	RETURN_CCTOR(&prefixedPath);
}

/**
 * @param string $type
 */
PHP_METHOD(Phalcon_Assets_Manager, checkAndCreateCollection)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval type_zv, _0, _2, _3, _1$$3;
	zend_string *type = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("collections", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 292, PH_NOISY_CC | PH_READONLY);
	if (1 != zephir_array_isset_value(&_0, &type_zv)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, phalcon_assets_collection_ce);
		if (zephir_has_constructor(&_1$$3)) {
			ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 0);
			zephir_check_call_status();
		}

		zephir_update_property_array(this_ptr, SL("collections"), &type_zv, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 292, PH_NOISY_CC | PH_READONLY);
	zephir_memory_observe(&_3);
	zephir_array_fetch(&_3, &_2, &type_zv, PH_NOISY, "phalcon/Assets/Manager.zep", 928);
	RETURN_CCTOR(&_3);
}

/**
 * Builds a LINK[rel="stylesheet"] tag
 *
 * @param mixed $parameters
 * @param bool  $local
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, cssLink)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool local;
	zval *parameters = NULL, parameters_sub, *local_param = NULL, _0, _1, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(parameters)
		Z_PARAM_BOOL(local)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &parameters, &local_param);
	if (!parameters) {
		parameters = &parameters_sub;
		ZEPHIR_INIT_VAR(parameters);
		array_init(parameters);
	}
	if (!local_param) {
		local = 1;
	} else {
		}
	if (local) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "link");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "text/css");
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "href");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "processParameters", NULL, 181, parameters, &_0, &_1, &_2, &_3);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param mixed  $callback
 * @param array  $attributes
 * @param string $prefixedPath
 * @param bool   $local
 *
 * @return string
 */
PHP_METHOD(Phalcon_Assets_Manager, doCallback)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool local;
	zend_string *prefixedPath = NULL;
	zval attributes, parameters;
	zval *callback, callback_sub, *attributes_param = NULL, prefixedPath_zv, *local_param = NULL, _1, _0$$4;

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&prefixedPath_zv);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&parameters);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ZVAL(callback)
		ZEPHIR_Z_PARAM_ARRAY(attributes, attributes_param)
		Z_PARAM_STR(prefixedPath)
		Z_PARAM_BOOL(local)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	callback = ZEND_CALL_ARG(execute_data, 1);
	attributes_param = ZEND_CALL_ARG(execute_data, 2);
	local_param = ZEND_CALL_ARG(execute_data, 4);
	zephir_get_arrval(&attributes, attributes_param);
	zephir_memory_observe(&prefixedPath_zv);
	ZVAL_STR_COPY(&prefixedPath_zv, prefixedPath);
	if (1 != ZEPHIR_IS_EMPTY(&attributes)) {
		zephir_array_update_long(&attributes, 0, &prefixedPath_zv, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		ZEPHIR_INIT_VAR(&parameters);
		zephir_create_array(&parameters, 1, 0);
		zephir_array_fast_append(&parameters, &attributes);
	} else {
		ZEPHIR_INIT_VAR(&_0$$4);
		zephir_create_array(&_0$$4, 1, 0);
		zephir_array_fast_append(&_0$$4, &prefixedPath_zv);
		ZEPHIR_CPY_WRT(&parameters, &_0$$4);
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_BOOL(&_1, local);
	zephir_array_append(&parameters, &_1, PH_SEPARATE, "phalcon/Assets/Manager.zep", 976);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, callback, &parameters);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param mixed $parameters
 * @param bool  $local
 *
 * @return string
 * @throws Exception
 */
PHP_METHOD(Phalcon_Assets_Manager, jsLink)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool local;
	zval *parameters = NULL, parameters_sub, *local_param = NULL, _0, _1, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(parameters)
		Z_PARAM_BOOL(local)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 2, &parameters, &local_param);
	if (!parameters) {
		parameters = &parameters_sub;
		ZEPHIR_INIT_VAR(parameters);
		array_init(parameters);
	}
	if (!local_param) {
		local = 1;
	} else {
		}
	if (local) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "script");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "application/javascript");
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "src");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "processParameters", NULL, 181, parameters, &_0, &_1, &_2, &_3);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Processes common parameters for js/css link generation
 */
PHP_METHOD(Phalcon_Assets_Manager, processParameters)
{
	zval _13;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *helperClass = NULL, *type = NULL, *name = NULL;
	zend_bool local;
	zval *parameters, parameters_sub, *local_param = NULL, helperClass_zv, type_zv, name_zv, helper, output, params, tag, _4, _11, _12, _0$$3, _1$$3, _2$$4, _3$$6, _5$$8, _6$$9, _7$$10, _8$$11, _9$$11, _10$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters_sub);
	ZVAL_UNDEF(&helperClass_zv);
	ZVAL_UNDEF(&type_zv);
	ZVAL_UNDEF(&name_zv);
	ZVAL_UNDEF(&helper);
	ZVAL_UNDEF(&output);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&tag);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_13);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("tagFactory", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_ZVAL(parameters)
		Z_PARAM_BOOL(local)
		Z_PARAM_STR(helperClass)
		Z_PARAM_STR(type)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	parameters = ZEND_CALL_ARG(execute_data, 1);
	local_param = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&helperClass_zv);
	ZVAL_STR_COPY(&helperClass_zv, helperClass);
	zephir_memory_observe(&type_zv);
	ZVAL_STR_COPY(&type_zv, type);
	zephir_memory_observe(&name_zv);
	ZVAL_STR_COPY(&name_zv, name);
	ZEPHIR_CPY_WRT(&params, parameters);
	if (Z_TYPE_P(&params) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 2, 0);
		zephir_array_fast_append(&_0$$3, parameters);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_BOOL(&_1$$3, local);
		zephir_array_fast_append(&_0$$3, &_1$$3);
		ZEPHIR_CPY_WRT(&params, &_0$$3);
	}
	if (1 == zephir_array_isset_value_long(&params, 1)) {
		zephir_memory_observe(&_2$$4);
		zephir_array_fetch_long(&_2$$4, &params, 1, PH_NOISY, "phalcon/Assets/Manager.zep", 1020);
		local = zephir_get_boolval(&_2$$4);
		zephir_array_unset_long(&params, 1, PH_SEPARATE);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		if (1 == zephir_array_isset_value_string(&params, SL("local"))) {
			zephir_memory_observe(&_3$$6);
			zephir_array_fetch_string(&_3$$6, &params, SL("local"), PH_NOISY, "phalcon/Assets/Manager.zep", 1024);
			local = zephir_get_boolval(&_3$$6);
			zephir_array_unset_string(&params, SL("local"), PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	if (1 != zephir_array_isset_value_string(&params, SL("type"))) {
		zephir_array_update_string(&params, SL("type"), &type_zv, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "link");
	if (ZEPHIR_IS_IDENTICAL(&_4, &helperClass_zv)) {
		ZEPHIR_INIT_VAR(&_5$$8);
		ZVAL_STRING(&_5$$8, "stylesheet");
		zephir_array_update_string(&params, SL("rel"), &_5$$8, PH_COPY | PH_SEPARATE);
	}
	if (1 != zephir_array_isset_value(&params, &name_zv)) {
		ZEPHIR_INIT_VAR(&_6$$9);
		ZVAL_STRING(&_6$$9, "");
		zephir_array_update_zval(&params, &name_zv, &_6$$9, PH_COPY | PH_SEPARATE);
		if (1 == zephir_array_isset_value_long(&params, 0)) {
			zephir_memory_observe(&_7$$10);
			zephir_array_fetch_long(&_7$$10, &params, 0, PH_NOISY, "phalcon/Assets/Manager.zep", 1044);
			zephir_array_update_zval(&params, &name_zv, &_7$$10, PH_COPY | PH_SEPARATE);
			zephir_array_unset_long(&params, 0, PH_SEPARATE);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_memory_observe(&tag);
	zephir_array_fetch(&tag, &params, &name_zv, PH_NOISY, "phalcon/Assets/Manager.zep", 1049);
	zephir_array_unset(&params, &name_zv, PH_SEPARATE);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (local) {
		ZEPHIR_INIT_VAR(&_8$$11);
		ZEPHIR_INIT_VAR(&_9$$11);
		ZVAL_STRING(&_9$$11, "/");
		zephir_fast_trim(&_8$$11, &tag, &_9$$11, ZEPHIR_TRIM_LEFT);
		ZEPHIR_INIT_VAR(&_10$$11);
		ZEPHIR_CONCAT_SV(&_10$$11, "/", &_8$$11);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&tag, &_10$$11);
	}
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_0, 290, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&helper, &_11, "newInstance", NULL, 0, &helperClass_zv);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "");
	ZEPHIR_CALL_METHOD(NULL, &helper, "__invoke", NULL, 0, &_12);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &helper, "add", NULL, 0, &tag, &params);
	zephir_check_call_status();
	zephir_cast_to_string(&_13, &helper);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&output, &_13);
	ZEPHIR_CALL_METHOD(NULL, &helper, "reset", NULL, 0);
	zephir_check_call_status();
	RETURN_CCTOR(&output);
}

zend_object *zephir_init_properties_Phalcon_Assets_Manager(zend_class_entry *class_type)
{
		zval _0, _2, _1$$3, _3$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("options"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("collections"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("collections"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

