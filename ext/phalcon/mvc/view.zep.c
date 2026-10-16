
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
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "Zend/zend_closures.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\View
 *
 * Phalcon\Mvc\View is a class for working with the "view" portion of the
 * model-view-controller pattern. That is, it exists to help keep the view
 * script separate from the model and controller scripts. It provides a system
 * of helpers, output filters, and variable escaping.
 *
 * ```php
 * use Phalcon\Mvc\View;
 *
 * $view = new View();
 *
 * // Setting views directory
 * $view->setViewsDir("app/views/");
 *
 * $view->start();
 *
 * // Shows recent posts view (app/views/posts/recent.phtml)
 * $view->render("posts", "recent");
 * $view->finish();
 *
 * // Printing views output
 * echo $view->getContent();
 * ```
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, View, phalcon, mvc_view, phalcon_di_injectable_ce, phalcon_mvc_view_method_entry, 0);

	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("actionName"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("activeRenderPaths"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("basePath"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("content"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("controllerName"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_ce, SL("currentRenderLevel"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_mvc_view_ce, SL("disabled"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("disabledLevels"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|bool
	 */
	zend_declare_property_bool(phalcon_mvc_view_ce, SL("engines"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("layout"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("layoutsDir"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("mainView"), "index", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("options"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("params"), ZEND_ACC_PROTECTED);
	/**
	 * @var array|null
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("pickView"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_mvc_view_ce, SL("partialsDir"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("registeredEngines"), ZEND_ACC_PROTECTED);
	/**
	 * @var int
	 */
	zend_declare_property_long(phalcon_mvc_view_ce, SL("renderLevel"), 5, ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("templatesAfter"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("templatesBefore"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("viewsDirs"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_mvc_view_ce, SL("viewParams"), ZEND_ACC_PROTECTED);
	phalcon_mvc_view_ce->create_object = zephir_init_properties_Phalcon_Mvc_View;
	/**
	 * Render Level: To the action view
	 *
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_ACTION_VIEW"), 1);

	/**
	 * Render Level: To the templates "before"
	 *
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_BEFORE_TEMPLATE"), 2);

	/**
	 * Render Level: To the controller layout
	 *
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_LAYOUT"), 3);

	/**
	 * Render Level: To the main layout
	 *
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_MAIN_LAYOUT"), 5);

	/**
	 * Render Level: No render any view
	 *
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_NO_RENDER"), 0);

	/**
	 * Render Level: Render to the templates "after"
	 *
	 * @var int
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_AFTER_TEMPLATE"), 4);

	zend_class_implements(phalcon_mvc_view_ce, 1, phalcon_mvc_viewinterface_ce);
	zend_class_implements(phalcon_mvc_view_ce, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Mvc\View constructor
 */
PHP_METHOD(Phalcon_Mvc_View, __construct)
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

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(options, options_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &options_param);
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 876, &options);
	ZEPHIR_MM_RESTORE();
}

/**
 * Magic method to retrieve a variable passed to the view
 *
 *```php
 * echo $this->view->products;
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, __get)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval key_zv;
	zend_string *key = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&key_zv);
	ZVAL_STR_COPY(&key_zv, key);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getVar", NULL, 0, &key_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Magic method to retrieve if a variable is set in the view
 *
 *```php
 * echo isset($this->view->products);
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, __isset)
{
	zval key_zv, _0;
	zend_string *key = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("viewParams", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&key_zv, key);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 877, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_value(&_0, &key_zv));
}

/**
 * Magic method to pass variables to the views
 *
 *```php
 * $this->view->products = $products;
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, __set)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval key_zv, *value, value_sub;
	zend_string *key = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_zv);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(key)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	value = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&key_zv);
	ZVAL_STR_COPY(&key_zv, key);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setVar", NULL, 0, &key_zv, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Resets any template before layouts
 */
PHP_METHOD(Phalcon_Mvc_View, cleanTemplateAfter)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("templatesAfter", 14, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 878, &_0);
	RETURN_THIS();
}

/**
 * Resets any "template before" layouts
 */
PHP_METHOD(Phalcon_Mvc_View, cleanTemplateBefore)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("templatesBefore", 15, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 879, &_0);
	RETURN_THIS();
}

/**
 * Disables a specific level of rendering
 *
 *```php
 * // Render all levels except ACTION level
 * $this->view->disableLevel(
 *     View::LEVEL_ACTION_VIEW
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, disableLevel)
{
	zval *level, level_sub, __$true;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&level_sub);
	ZVAL_BOOL(&__$true, 1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("disabledLevels", 14, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(level)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &level);
	if (Z_TYPE_P(level) == IS_ARRAY) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 880, level);
	} else {
		zephir_update_property_array(this_ptr, SL("disabledLevels"), level, &__$true);
	}
	RETURN_THISW();
}

/**
 * Disables the auto-rendering process
 */
PHP_METHOD(Phalcon_Mvc_View, disable)
{
	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("disabled", 8, 1);
	}
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 881, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 881, &__$false);
	}
	RETURN_THISW();
}

/**
 * Enables the auto-rendering process
 */
PHP_METHOD(Phalcon_Mvc_View, enable)
{
	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("disabled", 8, 1);
	}
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 881, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 881, &__$false);
	}
	RETURN_THISW();
}

/**
 * Checks whether view exists
 * @deprecated
 */
PHP_METHOD(Phalcon_Mvc_View, exists)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval view_zv;
	zend_string *view = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&view_zv);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(view)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&view_zv);
	ZVAL_STR_COPY(&view_zv, view);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "has", NULL, 0, &view_zv);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Finishes the render process by stopping the output buffering
 */
PHP_METHOD(Phalcon_Mvc_View, finish)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_FUNCTION(NULL, "ob_end_clean", NULL, 0);
	zephir_check_call_status();
	RETURN_THIS();
}

/**
 * Gets the name of the action rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getActionName)
{

	RETURN_MEMBER_TYPED(getThis(), "actionName", IS_STRING);
}

/**
 * Returns the path (or paths) of the views that are currently rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getActiveRenderPath)
{
	zend_bool _1$$3;
	zval activeRenderPath, _0, _2$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, viewsDirsCount = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&activeRenderPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("activeRenderPaths", 17, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getViewsDirs", NULL, 0);
	zephir_check_call_status();
	viewsDirsCount = zephir_fast_count_int(&_0);
	zephir_memory_observe(&activeRenderPath);
	zephir_read_property_cached(&activeRenderPath, this_ptr, _zephir_prop_0, 882, PH_NOISY_CC);
	if (viewsDirsCount == 1) {
		_1$$3 = Z_TYPE_P(&activeRenderPath) == IS_ARRAY;
		if (_1$$3) {
			_1$$3 = ((zephir_fast_count_int(&activeRenderPath)) ? 1 : 0);
		}
		if (_1$$3) {
			zephir_memory_observe(&_2$$4);
			zephir_array_fetch_long(&_2$$4, &activeRenderPath, 0, PH_NOISY, "phalcon/Mvc/View.zep", 351);
			ZEPHIR_CPY_WRT(&activeRenderPath, &_2$$4);
		}
	}
	if (Z_TYPE_P(&activeRenderPath) == IS_NULL) {
		ZEPHIR_INIT_NVAR(&activeRenderPath);
		ZVAL_STRING(&activeRenderPath, "");
	}
	RETURN_CCTOR(&activeRenderPath);
}

/**
 * Gets base path
 */
PHP_METHOD(Phalcon_Mvc_View, getBasePath)
{

	RETURN_MEMBER_TYPED(getThis(), "basePath", IS_STRING);
}

/**
 * Returns output from another view stage
 */
PHP_METHOD(Phalcon_Mvc_View, getContent)
{

	RETURN_MEMBER_TYPED(getThis(), "content", IS_STRING);
}

/**
 * Gets the name of the controller rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getControllerName)
{

	RETURN_MEMBER_TYPED(getThis(), "controllerName", IS_STRING);
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_View, getCurrentRenderLevel)
{

	RETURN_MEMBER_TYPED(getThis(), "currentRenderLevel", IS_LONG);
}

/**
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_View, getRegisteredEngines)
{

	RETURN_MEMBER_TYPED(getThis(), "registeredEngines", IS_ARRAY);
}

/**
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_View, getRenderLevel)
{

	RETURN_MEMBER_TYPED(getThis(), "renderLevel", IS_LONG);
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Mvc_View, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Returns the name of the main view
 */
PHP_METHOD(Phalcon_Mvc_View, getLayout)
{

	RETURN_MEMBER(getThis(), "layout");
}

/**
 * Gets the current layouts sub-directory
 */
PHP_METHOD(Phalcon_Mvc_View, getLayoutsDir)
{

	RETURN_MEMBER_TYPED(getThis(), "layoutsDir", IS_STRING);
}

/**
 * Returns the name of the main view
 */
PHP_METHOD(Phalcon_Mvc_View, getMainView)
{

	RETURN_MEMBER_TYPED(getThis(), "mainView", IS_STRING);
}

/**
 * Returns parameters to views
 */
PHP_METHOD(Phalcon_Mvc_View, getParamsToView)
{

	RETURN_MEMBER_TYPED(getThis(), "viewParams", IS_ARRAY);
}

/**
 * Renders a partial view
 *
 * ```php
 * // Retrieve the contents of a partial
 * echo $this->getPartial("shared/footer");
 * ```
 *
 * ```php
 * // Retrieve the contents of a partial with arguments
 * echo $this->getPartial(
 *     "shared/footer",
 *     [
 *         "content" => $html,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, getPartial)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval partialPath_zv, *params = NULL, params_sub, __$null;
	zend_string *partialPath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialPath_zv);
	ZVAL_UNDEF(&params_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(partialPath)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(params)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		params = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&partialPath_zv);
	ZVAL_STR_COPY(&partialPath_zv, partialPath);
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}
	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", NULL, 425);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "partial", NULL, 0, &partialPath_zv, params);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", NULL, 432);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets the current partials sub-directory
 */
PHP_METHOD(Phalcon_Mvc_View, getPartialsDir)
{

	RETURN_MEMBER_TYPED(getThis(), "partialsDir", IS_STRING);
}

/**
 * Perform the automatic rendering returning the output as a string
 *
 * ```php
 * $template = $this->view->getRender(
 *     "products",
 *     "show",
 *     [
 *         "products" => $products,
 *     ]
 * );
 * ```
 *
 * @param mixed configCallback
 */
PHP_METHOD(Phalcon_Mvc_View, getRender)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params, _1$$3;
	zval controllerName_zv, actionName_zv, *params_param = NULL, *configCallback = NULL, configCallback_sub, __$null, view, _0$$3;
	zend_string *controllerName = NULL, *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName_zv);
	ZVAL_UNDEF(&actionName_zv);
	ZVAL_UNDEF(&configCallback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_1$$3);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
		Z_PARAM_ZVAL_OR_NULL(configCallback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		params_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		configCallback = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&controllerName_zv);
	ZVAL_STR_COPY(&controllerName_zv, controllerName);
	zephir_memory_observe(&actionName_zv);
	ZVAL_STR_COPY(&actionName_zv, actionName);
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	if (!configCallback) {
		configCallback = &configCallback_sub;
		configCallback = &__$null;
	}
	ZEPHIR_INIT_VAR(&view);
	if (zephir_clone(&view, this_ptr) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(NULL, &view, "reset", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "setVars", NULL, 0, &params);
	zephir_check_call_status();
	if (Z_TYPE_P(configCallback) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 1, 0);
		zephir_array_fast_append(&_1$$3, &view);
		ZEPHIR_CALL_USER_FUNC_ARRAY(&_0$$3, configCallback, &_1$$3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, &view, "start", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "render", NULL, 0, &controllerName_zv, &actionName_zv);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "finish", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&view, "getContent", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns a parameter previously set in the view
 *
 * @return mixed|null
 */
PHP_METHOD(Phalcon_Mvc_View, getVar)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval key_zv, value, _0;
	zend_string *key = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_zv);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("viewParams", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(key)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&key_zv);
	ZVAL_STR_COPY(&key_zv, key);
	zephir_memory_observe(&value);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 877, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&value, &_0, &key_zv, 0))) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&value);
}

/**
 * Gets views directory
 */
PHP_METHOD(Phalcon_Mvc_View, getViewsDir)
{

	RETURN_MEMBER(getThis(), "viewsDirs");
}

/**
 * Gets views directories
 */
PHP_METHOD(Phalcon_Mvc_View, getViewsDirs)
{
	zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("viewsDirs", 9, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 883, PH_NOISY_CC);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		zephir_create_array(return_value, 1, 0);
		zephir_memory_observe(&_1$$3);
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 883, PH_NOISY_CC);
		zephir_array_fast_append(return_value, &_1$$3);
		RETURN_MM();
	}
	RETURN_MM_MEMBER_TYPED(getThis(), "viewsDirs", IS_ARRAY);
}

/**
 * Checks whether view exists
 */
PHP_METHOD(Phalcon_Mvc_View, has)
{
	zend_ulong _10$$4, _22$$9;
	zend_bool _17, _14$$4, _26$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval view_zv, basePath, viewsDir, engines, extension, _0, _2, *_3, _4, *_5, _16, _1$$3, *_6$$4, _7$$4, _8$$4, *_9$$4, _13$$4, _12$$5, _15$$7, *_18$$9, _19$$9, _20$$9, *_21$$9, _25$$9, _24$$10, _27$$12;
	zend_string *view = NULL, *_11$$4, *_23$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&view_zv);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_24$$10);
	ZVAL_UNDEF(&_27$$12);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("basePath", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("registeredEngines", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(view)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&view_zv);
	ZVAL_STR_COPY(&view_zv, view);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 884, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&basePath, &_0);
	zephir_memory_observe(&engines);
	zephir_read_property_cached(&engines, this_ptr, _zephir_prop_1, 885, PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(&engines)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 1, 0);
		add_assoc_stringl_ex(&_1$$3, SL(".phtml"), SL("Phalcon\\Mvc\\View\\Engine\\Php"));
		ZEPHIR_CPY_WRT(&engines, &_1$$3);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "registerEngines", NULL, 0, &engines);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getViewsDirs", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_2) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4);
		zephir_string_to_char_array(&_4, &_2);
		_3 = &_4;
	} else {
		_3 = &_2;
	}
	zephir_is_iterable(_3, 0, "phalcon/Mvc/View.zep", 611);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&viewsDir);
			ZVAL_COPY(&viewsDir, _5);
			if (Z_TYPE_P(&engines) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_7$$4);
				zephir_string_to_char_array(&_7$$4, &engines);
				_6$$4 = &_7$$4;
			} else {
				_6$$4 = &engines;
			}
			ZEPHIR_INIT_NVAR(&_8$$4);
			zephir_is_iterable(_6$$4, 0, "phalcon/Mvc/View.zep", 609);
			if (Z_TYPE_P(_6$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_6$$4), _10$$4, _11$$4, _9$$4)
				{
					ZEPHIR_INIT_NVAR(&extension);
					if (_11$$4 != NULL) { 
						ZVAL_STR_COPY(&extension, _11$$4);
					} else {
						ZVAL_LONG(&extension, _10$$4);
					}
					ZEPHIR_INIT_NVAR(&_8$$4);
					ZVAL_COPY(&_8$$4, _9$$4);
					ZEPHIR_INIT_NVAR(&_12$$5);
					ZEPHIR_CONCAT_VVVV(&_12$$5, &basePath, &viewsDir, &view_zv, &extension);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if ((zephir_file_exists(&_12$$5) == SUCCESS)) {
						RETURN_MM_BOOL(1);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _6$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_14$$4 = 1;
				while (1) {
					if (_14$$4) {
						_14$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _6$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_13$$4, _6$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&extension, _6$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_8$$4, _6$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_15$$7);
						ZEPHIR_CONCAT_VVVV(&_15$$7, &basePath, &viewsDir, &view_zv, &extension);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if ((zephir_file_exists(&_15$$7) == SUCCESS)) {
							RETURN_MM_BOOL(1);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZEPHIR_INIT_NVAR(&extension);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_17 = 1;
		while (1) {
			if (_17) {
				_17 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_16, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_16)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&viewsDir, _3, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&engines) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_19$$9);
					zephir_string_to_char_array(&_19$$9, &engines);
					_18$$9 = &_19$$9;
				} else {
					_18$$9 = &engines;
				}
				ZEPHIR_INIT_NVAR(&_20$$9);
				zephir_is_iterable(_18$$9, 0, "phalcon/Mvc/View.zep", 609);
				if (Z_TYPE_P(_18$$9) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_18$$9), _22$$9, _23$$9, _21$$9)
					{
						ZEPHIR_INIT_NVAR(&extension);
						if (_23$$9 != NULL) { 
							ZVAL_STR_COPY(&extension, _23$$9);
						} else {
							ZVAL_LONG(&extension, _22$$9);
						}
						ZEPHIR_INIT_NVAR(&_20$$9);
						ZVAL_COPY(&_20$$9, _21$$9);
						ZEPHIR_INIT_NVAR(&_24$$10);
						ZEPHIR_CONCAT_VVVV(&_24$$10, &basePath, &viewsDir, &view_zv, &extension);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if ((zephir_file_exists(&_24$$10) == SUCCESS)) {
							RETURN_MM_BOOL(1);
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _18$$9, "rewind", NULL, 0);
					zephir_check_call_status();
					_26$$9 = 1;
					while (1) {
						if (_26$$9) {
							_26$$9 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _18$$9, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_25$$9, _18$$9, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_25$$9)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&extension, _18$$9, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_20$$9, _18$$9, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$12);
							ZEPHIR_CONCAT_VVVV(&_27$$12, &basePath, &viewsDir, &view_zv, &extension);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if ((zephir_file_exists(&_27$$12) == SUCCESS)) {
								RETURN_MM_BOOL(1);
							}
					}
				}
				ZEPHIR_INIT_NVAR(&_20$$9);
				ZEPHIR_INIT_NVAR(&extension);
		}
	}
	ZEPHIR_INIT_NVAR(&viewsDir);
	RETURN_MM_BOOL(0);
}

/**
 * Whether automatic rendering is enabled
 */
PHP_METHOD(Phalcon_Mvc_View, isDisabled)
{

	RETURN_MEMBER(getThis(), "disabled");
}

/**
 * Renders a partial view
 *
 * ```php
 * // Show a partial inside another view
 * $this->partial("shared/footer");
 * ```
 *
 * ```php
 * // Show a partial inside another view with parameters
 * $this->partial(
 *     "shared/footer",
 *     [
 *         "content" => $html,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, partial)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval partialPath_zv, *params = NULL, params_sub, __$null, viewParams, _3, _4, _5, _6, _7, _0$$3, _1$$3, _2$$3;
	zend_string *partialPath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialPath_zv);
	ZVAL_UNDEF(&params_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&viewParams);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("viewParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("partialsDir", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(partialPath)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(params)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 1) {
		params = ZEND_CALL_ARG(execute_data, 2);
	}
	zephir_memory_observe(&partialPath_zv);
	ZVAL_STR_COPY(&partialPath_zv, partialPath);
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}
	ZEPHIR_INIT_VAR(&viewParams);
	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 877, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&viewParams, &_0$$3);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_fast_array_merge(&_1$$3, &viewParams, params);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 877, &_1$$3);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CREATE_SYMBOL_TABLE();
		
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "loadTemplateEngines", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_1, 886, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_VV(&_5, &_4, &partialPath_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_BOOL(&_6, 0);
	ZVAL_BOOL(&_7, 0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &_3, &_5, &_6, &_7);
	zephir_check_call_status();
	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 877, &viewParams);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Choose a different view to render instead of last-controller/last-action
 *
 * ```php
 * use Phalcon\Mvc\Controller;
 *
 * class ProductsController extends Controller
 * {
 *     public function saveAction()
 *     {
 *         // Do some save stuff...
 *
 *         // Then show the list view
 *         $this->view->pick("products/list");
 *     }
 * }
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, pick)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *renderView, renderView_sub, pickView, layout, parts, _0$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&renderView_sub);
	ZVAL_UNDEF(&pickView);
	ZVAL_UNDEF(&layout);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_0$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("pickView", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(renderView)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &renderView);
	if (Z_TYPE_P(renderView) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&pickView, renderView);
	} else {
		ZEPHIR_INIT_VAR(&layout);
		ZVAL_NULL(&layout);
		if (zephir_memnstr_str(renderView, SL("/"), "phalcon/Mvc/View.zep", 713)) {
			ZEPHIR_INIT_VAR(&parts);
			zephir_fast_explode_str(&parts, SL("/"), renderView, NULL);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_OBS_NVAR(&layout);
			zephir_array_fetch_long(&layout, &parts, 0, PH_NOISY, "phalcon/Mvc/View.zep", 715);
		}
		ZEPHIR_INIT_VAR(&_0$$4);
		zephir_create_array(&_0$$4, 1, 0);
		zephir_array_fast_append(&_0$$4, renderView);
		ZEPHIR_CPY_WRT(&pickView, &_0$$4);
		if (Z_TYPE_P(&layout) != IS_NULL) {
			zephir_array_append(&pickView, &layout, PH_SEPARATE, "phalcon/Mvc/View.zep", 721);
		}
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 887, &pickView);
	RETURN_THIS();
}

/**
 * Register templating engines
 *
 * ```php
 * $this->view->registerEngines(
 *     [
 *         ".phtml" => \Phalcon\Mvc\View\Engine\Php::class,
 *         ".volt"  => \Phalcon\Mvc\View\Engine\Volt::class,
 *         ".mhtml" => \MyCustomEngine::class,
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, registerEngines)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *engines_param = NULL;
	zval engines;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("registeredEngines", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(engines, engines_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &engines_param);
	ZEPHIR_OBS_COPY_OR_DUP(&engines, engines_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 885, &engines);
	RETURN_THIS();
}

/**
 * Executes render process from dispatching data
 *
 *```php
 * // Shows recent posts view (app/views/posts/recent.phtml)
 * $view->start()->render("posts", "recent")->finish();
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, render)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval controllerName_zv, actionName_zv, *params_param = NULL, result;
	zend_string *controllerName = NULL, *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName_zv);
	ZVAL_UNDEF(&actionName_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&params);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		params_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&controllerName_zv);
	ZVAL_STR_COPY(&controllerName_zv, controllerName);
	zephir_memory_observe(&actionName_zv);
	ZVAL_STR_COPY(&actionName_zv, actionName);
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	ZEPHIR_CALL_METHOD(&result, this_ptr, "processRender", NULL, 0, &controllerName_zv, &actionName_zv, &params);
	zephir_check_call_status();
	if (!(zephir_is_true(&result))) {
		RETURN_MM_BOOL(0);
	}
	RETURN_THIS();
}

/**
 * Resets the view component to its factory default values
 */
PHP_METHOD(Phalcon_Mvc_View, reset)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true, __$false, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("disabled", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("engines", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("renderLevel", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("content", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("templatesBefore", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("templatesAfter", 14, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 881, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 881, &__$false);
	}
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 888, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 888, &__$false);
	}
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 5);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 889, &_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "");
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 890, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	array_init(&_1);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 879, &_1);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 878, &_2);
	RETURN_THIS();
}

/**
 * Sets base path. Depending of your platform, always add a trailing slash
 * or backslash
 *
 * ```php
 * $view->setBasePath(__DIR__ . "/");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setBasePath)
{
	zval basePath_zv;
	zend_string *basePath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&basePath_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("basePath", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(basePath)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&basePath_zv, basePath);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 884, &basePath_zv);
	RETURN_THISW();
}

/**
 * Externally sets the view content
 *
 *```php
 * $this->view->setContent("<h1>hello</h1>");
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setContent)
{
	zval content_zv;
	zend_string *content = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("content", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(content)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&content_zv, content);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 890, &content_zv);
	RETURN_THISW();
}

/**
 * Sets the events manager
 */
PHP_METHOD(Phalcon_Mvc_View, setEventsManager)
{
	zval *eventsManager, eventsManager_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventsManager_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("eventsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(eventsManager, phalcon_events_managerinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &eventsManager);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 891, eventsManager);
}

/**
 * Change the layout to be used instead of using the name of the latest
 * controller name
 *
 * ```php
 * $this->view->setLayout("main");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setLayout)
{
	zval layout_zv;
	zend_string *layout = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&layout_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("layout", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(layout)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&layout_zv, layout);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 892, &layout_zv);
	RETURN_THISW();
}

/**
 * Sets the layouts sub-directory. Must be a directory under the views
 * directory. Depending of your platform, always add a trailing slash or
 * backslash
 *
 *```php
 * $view->setLayoutsDir("../common/layouts/");
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setLayoutsDir)
{
	zval layoutsDir_zv;
	zend_string *layoutsDir = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&layoutsDir_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("layoutsDir", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(layoutsDir)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&layoutsDir_zv, layoutsDir);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 893, &layoutsDir_zv);
	RETURN_THISW();
}

/**
 * Sets default view name. Must be a file without extension in the views
 * directory
 *
 * ```php
 * // Renders as main view views-dir/base.phtml
 * $this->view->setMainView("base");
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setMainView)
{
	zval viewPath_zv;
	zend_string *viewPath = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewPath_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("mainView", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(viewPath)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&viewPath_zv, viewPath);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 894, &viewPath_zv);
	RETURN_THISW();
}

/**
 * Sets a partials sub-directory. Must be a directory under the views
 * directory. Depending of your platform, always add a trailing slash or
 * backslash
 *
 *```php
 * $view->setPartialsDir("../common/partials/");
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setPartialsDir)
{
	zval partialsDir_zv;
	zend_string *partialsDir = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialsDir_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("partialsDir", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(partialsDir)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&partialsDir_zv, partialsDir);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 886, &partialsDir_zv);
	RETURN_THISW();
}

/**
 * Adds parameters to views (alias of setVar)
 *
 *```php
 * $this->view->setParamToView("products", $products);
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setParamToView)
{
	zval key_zv, *value, value_sub;
	zend_string *key = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_zv);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(key)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	value = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&key_zv, key);
	zephir_update_property_array(this_ptr, SL("viewParams"), &key_zv, value);
	RETURN_THISW();
}

/**
 * Sets the render level for the view
 *
 * ```php
 * // Render the view related to the controller only
 * $this->view->setRenderLevel(
 *     View::LEVEL_LAYOUT
 * );
 * ```
 */
PHP_METHOD(Phalcon_Mvc_View, setRenderLevel)
{
	zval *level_param = NULL, _0;
	zend_long level;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("renderLevel", 11, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(level)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &level_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, level);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 889, &_0);
	RETURN_THISW();
}

/**
 * Sets a "template after" controller layout
 */
PHP_METHOD(Phalcon_Mvc_View, setTemplateAfter)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *templateAfter, templateAfter_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templateAfter_sub);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("templatesAfter", 14, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(templateAfter)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &templateAfter);
	if (Z_TYPE_P(templateAfter) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		zephir_array_fast_append(&_0$$3, templateAfter);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 878, &_0$$3);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 878, templateAfter);
	}
	RETURN_THIS();
}

/**
 * Sets a template before the controller layout
 */
PHP_METHOD(Phalcon_Mvc_View, setTemplateBefore)
{
	zval _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *templateBefore, templateBefore_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templateBefore_sub);
	ZVAL_UNDEF(&_0$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("templatesBefore", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(templateBefore)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &templateBefore);
	if (Z_TYPE_P(templateBefore) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		zephir_array_fast_append(&_0$$3, templateBefore);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 879, &_0$$3);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 879, templateBefore);
	}
	RETURN_THIS();
}

/**
 * Set a single view parameter
 *
 *```php
 * $this->view->setVar("products", $products);
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setVar)
{
	zval key_zv, *value, value_sub;
	zend_string *key = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_zv);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(key)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	value = ZEND_CALL_ARG(execute_data, 2);
	ZVAL_STR(&key_zv, key);
	zephir_update_property_array(this_ptr, SL("viewParams"), &key_zv, value);
	RETURN_THISW();
}

/**
 * Set all the render params
 *
 *```php
 * $this->view->setVars(
 *     [
 *         "products" => $products,
 *     ]
 * );
 *```
 */
PHP_METHOD(Phalcon_Mvc_View, setVars)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_bool merge;
	zval *params_param = NULL, *merge_param = NULL, _0$$3, _1$$3;
	zval params;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("viewParams", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(merge)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &params_param, &merge_param);
	ZEPHIR_OBS_COPY_OR_DUP(&params, params_param);
	if (!merge_param) {
		merge = 1;
	} else {
		}
	if (merge) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 877, PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_0$$3, &_1$$3, &params);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 877, &_0$$3);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 877, &params);
	}
	RETURN_THIS();
}

/**
 * Sets the views directory. Depending of your platform,
 * always add a trailing slash or backslash
 */
PHP_METHOD(Phalcon_Mvc_View, setViewsDir)
{
	zend_string *_6$$5;
	zend_ulong _5$$5;
	zend_bool _0, _9$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *viewsDir, viewsDir_sub, position, directory, newViewsDir, _1$$4, *_2$$5, _3$$5, *_4$$5, _8$$5, _7$$6, _10$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewsDir_sub);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&directory);
	ZVAL_UNDEF(&newViewsDir);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_10$$8);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("viewsDirs", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(viewsDir)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &viewsDir);
	_0 = Z_TYPE_P(viewsDir) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(viewsDir) != IS_ARRAY;
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory must be a string or an array", "phalcon/Mvc/View.zep", 994);
		return;
	}
	if (Z_TYPE_P(viewsDir) == IS_STRING) {
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "getDirSeparator", NULL, 0, viewsDir);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 883, &_1$$4);
	} else {
		ZEPHIR_INIT_VAR(&newViewsDir);
		array_init(&newViewsDir);
		if (Z_TYPE_P(viewsDir) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_3$$5);
			zephir_string_to_char_array(&_3$$5, viewsDir);
			_2$$5 = &_3$$5;
		} else {
			_2$$5 = viewsDir;
		}
		zephir_is_iterable(_2$$5, 0, "phalcon/Mvc/View.zep", 1012);
		if (Z_TYPE_P(_2$$5) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_2$$5), _5$$5, _6$$5, _4$$5)
			{
				ZEPHIR_INIT_NVAR(&position);
				if (_6$$5 != NULL) { 
					ZVAL_STR_COPY(&position, _6$$5);
				} else {
					ZVAL_LONG(&position, _5$$5);
				}
				ZEPHIR_INIT_NVAR(&directory);
				ZVAL_COPY(&directory, _4$$5);
				if (Z_TYPE_P(&directory) != IS_STRING) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory item must be a string", "phalcon/Mvc/View.zep", 1006);
					return;
				}
				ZEPHIR_CALL_METHOD(&_7$$6, this_ptr, "getDirSeparator", NULL, 0, &directory);
				zephir_check_call_status();
				zephir_array_update_zval(&newViewsDir, &position, &_7$$6, PH_COPY | PH_SEPARATE);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _2$$5, "rewind", NULL, 0);
			zephir_check_call_status();
			_9$$5 = 1;
			while (1) {
				if (_9$$5) {
					_9$$5 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _2$$5, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_8$$5, _2$$5, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_8$$5)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&position, _2$$5, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&directory, _2$$5, "current", NULL, 0);
				zephir_check_call_status();
					if (Z_TYPE_P(&directory) != IS_STRING) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory item must be a string", "phalcon/Mvc/View.zep", 1006);
						return;
					}
					ZEPHIR_CALL_METHOD(&_10$$8, this_ptr, "getDirSeparator", NULL, 0, &directory);
					zephir_check_call_status();
					zephir_array_update_zval(&newViewsDir, &position, &_10$$8, PH_COPY | PH_SEPARATE);
			}
		}
		ZEPHIR_INIT_NVAR(&directory);
		ZEPHIR_INIT_NVAR(&position);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 883, &newViewsDir);
	}
	RETURN_THIS();
}

/**
 * Starts rendering process enabling the output buffering
 */
PHP_METHOD(Phalcon_Mvc_View, start)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$null;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("content", 7, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", NULL, 425);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 890, &__$null);
	RETURN_THIS();
}

/**
 * Renders the view and returns it as a string
 */
PHP_METHOD(Phalcon_Mvc_View, toString)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval controllerName_zv, actionName_zv, *params_param = NULL, result, _0;
	zend_string *controllerName = NULL, *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName_zv);
	ZVAL_UNDEF(&actionName_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&params);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		params_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&controllerName_zv);
	ZVAL_STR_COPY(&controllerName_zv, controllerName);
	zephir_memory_observe(&actionName_zv);
	ZVAL_STR_COPY(&actionName_zv, actionName);
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "start", NULL, 0);
	zephir_check_call_status();
	ZVAL_BOOL(&_0, 0);
	ZEPHIR_CALL_METHOD(&result, this_ptr, "processRender", NULL, 0, &controllerName_zv, &actionName_zv, &params, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "finish", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&result))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getContent", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Checks whether view exists on registered extensions and render it
 */
PHP_METHOD(Phalcon_Mvc_View, engineRender)
{
	zval _50$$30;
	zend_ulong _8$$3, _30$$16;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_13 = NULL, *_16 = NULL, *_22 = NULL, *_25 = NULL, *_35 = NULL, *_38 = NULL, *_44 = NULL, *_47 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool silence, mustClean, _27, _18$$3, _40$$16;
	zend_string *viewPath = NULL, *_9$$3, *_31$$16;
	zval *engines_param = NULL, viewPath_zv, *silence_param = NULL, *mustClean_param = NULL, basePath, engine, eventsManager, extension, viewsDir, viewsDirPath, viewEnginePath, viewEnginePaths, viewParams, _0, _1, *_2, _3, *_4, _26, _5$$3, *_7$$3, _17$$3, _11$$8, _12$$8, _14$$7, _15$$10, _20$$13, _21$$13, _23$$12, _24$$15, _28$$16, *_29$$16, _39$$16, _33$$21, _34$$21, _36$$20, _37$$23, _42$$26, _43$$26, _45$$25, _46$$28, _48$$29, _49$$30;
	zval engines, _10$$8, _19$$13, _32$$21, _41$$26;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_19$$13);
	ZVAL_UNDEF(&_32$$21);
	ZVAL_UNDEF(&_41$$26);
	ZVAL_UNDEF(&viewPath_zv);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&engine);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&viewsDirPath);
	ZVAL_UNDEF(&viewEnginePath);
	ZVAL_UNDEF(&viewEnginePaths);
	ZVAL_UNDEF(&viewParams);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_20$$13);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_23$$12);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&_28$$16);
	ZVAL_UNDEF(&_39$$16);
	ZVAL_UNDEF(&_33$$21);
	ZVAL_UNDEF(&_34$$21);
	ZVAL_UNDEF(&_36$$20);
	ZVAL_UNDEF(&_37$$23);
	ZVAL_UNDEF(&_42$$26);
	ZVAL_UNDEF(&_43$$26);
	ZVAL_UNDEF(&_45$$25);
	ZVAL_UNDEF(&_46$$28);
	ZVAL_UNDEF(&_48$$29);
	ZVAL_UNDEF(&_49$$30);
	ZVAL_UNDEF(&_50$$30);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("basePath", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("viewParams", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("activeRenderPaths", 17, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 4)
		ZEPHIR_Z_PARAM_ARRAY(engines, engines_param)
		Z_PARAM_STR(viewPath)
		Z_PARAM_BOOL(silence)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(mustClean)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	engines_param = ZEND_CALL_ARG(execute_data, 1);
	silence_param = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		mustClean_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_get_arrval(&engines, engines_param);
	zephir_memory_observe(&viewPath_zv);
	ZVAL_STR_COPY(&viewPath_zv, viewPath);
	if (!mustClean_param) {
		mustClean = 1;
	} else {
		}
	ZEPHIR_INIT_VAR(&viewEnginePath);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 884, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&basePath, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 877, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&viewParams, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 891, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	ZEPHIR_INIT_VAR(&viewEnginePaths);
	array_init(&viewEnginePaths);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getViewsDirs", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_1) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &_1);
		_2 = &_3;
	} else {
		_2 = &_1;
	}
	zephir_is_iterable(_2, 0, "phalcon/Mvc/View.zep", 1118);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
		{
			ZEPHIR_INIT_NVAR(&viewsDir);
			ZVAL_COPY(&viewsDir, _4);
			ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "isAbsolutePath", &_6, 0, &viewPath_zv);
			zephir_check_call_status();
			if (!(zephir_is_true(&_5$$3))) {
				ZEPHIR_INIT_NVAR(&viewsDirPath);
				ZEPHIR_CONCAT_VVV(&viewsDirPath, &basePath, &viewsDir, &viewPath_zv);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(&viewsDirPath, &viewPath_zv);
			}
			zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 1113);
			if (Z_TYPE_P(&engines) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _8$$3, _9$$3, _7$$3)
				{
					ZEPHIR_INIT_NVAR(&extension);
					if (_9$$3 != NULL) { 
						ZVAL_STR_COPY(&extension, _9$$3);
					} else {
						ZVAL_LONG(&extension, _8$$3);
					}
					ZEPHIR_INIT_NVAR(&engine);
					ZVAL_COPY(&engine, _7$$3);
					ZEPHIR_INIT_NVAR(&viewEnginePath);
					ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
						if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
							ZEPHIR_INIT_NVAR(&_10$$8);
							zephir_create_array(&_10$$8, 1, 0);
							zephir_array_fast_append(&_10$$8, &viewEnginePath);
							zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 882, &_10$$8);
							ZEPHIR_INIT_NVAR(&_12$$8);
							ZVAL_STRING(&_12$$8, "view:beforeRenderView");
							ZEPHIR_CALL_METHOD(&_11$$8, &eventsManager, "fire", &_13, 0, &_12$$8, this_ptr, &viewEnginePath);
							zephir_check_call_status();
							if (ZEPHIR_IS_FALSE_IDENTICAL(&_11$$8)) {
								continue;
							}
						}
						if (mustClean) {
							ZVAL_BOOL(&_14$$7, 1);
						} else {
							ZVAL_BOOL(&_14$$7, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_14$$7);
						zephir_check_call_status();
						if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
							ZEPHIR_INIT_NVAR(&_15$$10);
							ZVAL_STRING(&_15$$10, "view:afterRenderView");
							ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_16, 0, &_15$$10, this_ptr);
							zephir_check_call_status();
						}
						RETURN_MM_NULL();
					}
					zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1111);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &engines, "rewind", NULL, 0);
				zephir_check_call_status();
				_18$$3 = 1;
				while (1) {
					if (_18$$3) {
						_18$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, &engines, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_17$$3, &engines, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_17$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&extension, &engines, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&engine, &engines, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&viewEnginePath);
						ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_19$$13);
								zephir_create_array(&_19$$13, 1, 0);
								zephir_array_fast_append(&_19$$13, &viewEnginePath);
								zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 882, &_19$$13);
								ZEPHIR_INIT_NVAR(&_21$$13);
								ZVAL_STRING(&_21$$13, "view:beforeRenderView");
								ZEPHIR_CALL_METHOD(&_20$$13, &eventsManager, "fire", &_22, 0, &_21$$13, this_ptr, &viewEnginePath);
								zephir_check_call_status();
								if (ZEPHIR_IS_FALSE_IDENTICAL(&_20$$13)) {
									continue;
								}
							}
							if (mustClean) {
								ZVAL_BOOL(&_23$$12, 1);
							} else {
								ZVAL_BOOL(&_23$$12, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_23$$12);
							zephir_check_call_status();
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_24$$15);
								ZVAL_STRING(&_24$$15, "view:afterRenderView");
								ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_25, 0, &_24$$15, this_ptr);
								zephir_check_call_status();
							}
							RETURN_MM_NULL();
						}
						zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1111);
				}
			}
			ZEPHIR_INIT_NVAR(&engine);
			ZEPHIR_INIT_NVAR(&extension);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_27 = 1;
		while (1) {
			if (_27) {
				_27 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_26, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_26)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&viewsDir, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_28$$16, this_ptr, "isAbsolutePath", &_6, 0, &viewPath_zv);
				zephir_check_call_status();
				if (!(zephir_is_true(&_28$$16))) {
					ZEPHIR_INIT_NVAR(&viewsDirPath);
					ZEPHIR_CONCAT_VVV(&viewsDirPath, &basePath, &viewsDir, &viewPath_zv);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
				} else {
					ZEPHIR_CPY_WRT(&viewsDirPath, &viewPath_zv);
				}
				zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 1113);
				if (Z_TYPE_P(&engines) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _30$$16, _31$$16, _29$$16)
					{
						ZEPHIR_INIT_NVAR(&extension);
						if (_31$$16 != NULL) { 
							ZVAL_STR_COPY(&extension, _31$$16);
						} else {
							ZVAL_LONG(&extension, _30$$16);
						}
						ZEPHIR_INIT_NVAR(&engine);
						ZVAL_COPY(&engine, _29$$16);
						ZEPHIR_INIT_NVAR(&viewEnginePath);
						ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_32$$21);
								zephir_create_array(&_32$$21, 1, 0);
								zephir_array_fast_append(&_32$$21, &viewEnginePath);
								zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 882, &_32$$21);
								ZEPHIR_INIT_NVAR(&_34$$21);
								ZVAL_STRING(&_34$$21, "view:beforeRenderView");
								ZEPHIR_CALL_METHOD(&_33$$21, &eventsManager, "fire", &_35, 0, &_34$$21, this_ptr, &viewEnginePath);
								zephir_check_call_status();
								if (ZEPHIR_IS_FALSE_IDENTICAL(&_33$$21)) {
									continue;
								}
							}
							if (mustClean) {
								ZVAL_BOOL(&_36$$20, 1);
							} else {
								ZVAL_BOOL(&_36$$20, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_36$$20);
							zephir_check_call_status();
							if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
								ZEPHIR_INIT_NVAR(&_37$$23);
								ZVAL_STRING(&_37$$23, "view:afterRenderView");
								ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_38, 0, &_37$$23, this_ptr);
								zephir_check_call_status();
							}
							RETURN_MM_NULL();
						}
						zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1111);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &engines, "rewind", NULL, 0);
					zephir_check_call_status();
					_40$$16 = 1;
					while (1) {
						if (_40$$16) {
							_40$$16 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, &engines, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_39$$16, &engines, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_39$$16)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&extension, &engines, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&engine, &engines, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&viewEnginePath);
							ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if ((zephir_file_exists(&viewEnginePath) == SUCCESS)) {
								if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
									ZEPHIR_INIT_NVAR(&_41$$26);
									zephir_create_array(&_41$$26, 1, 0);
									zephir_array_fast_append(&_41$$26, &viewEnginePath);
									zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 882, &_41$$26);
									ZEPHIR_INIT_NVAR(&_43$$26);
									ZVAL_STRING(&_43$$26, "view:beforeRenderView");
									ZEPHIR_CALL_METHOD(&_42$$26, &eventsManager, "fire", &_44, 0, &_43$$26, this_ptr, &viewEnginePath);
									zephir_check_call_status();
									if (ZEPHIR_IS_FALSE_IDENTICAL(&_42$$26)) {
										continue;
									}
								}
								if (mustClean) {
									ZVAL_BOOL(&_45$$25, 1);
								} else {
									ZVAL_BOOL(&_45$$25, 0);
								}
								ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_45$$25);
								zephir_check_call_status();
								if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
									ZEPHIR_INIT_NVAR(&_46$$28);
									ZVAL_STRING(&_46$$28, "view:afterRenderView");
									ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_47, 0, &_46$$28, this_ptr);
									zephir_check_call_status();
								}
								RETURN_MM_NULL();
							}
							zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 1111);
					}
				}
				ZEPHIR_INIT_NVAR(&engine);
				ZEPHIR_INIT_NVAR(&extension);
		}
	}
	ZEPHIR_INIT_NVAR(&viewsDir);
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 882, &viewEnginePaths);
		ZEPHIR_INIT_VAR(&_48$$29);
		ZVAL_STRING(&_48$$29, "view:notFoundView");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_48$$29, this_ptr, &viewEnginePath);
		zephir_check_call_status();
	}
	if (!(silence)) {
		ZEPHIR_INIT_VAR(&_49$$30);
		object_init_ex(&_49$$30, phalcon_mvc_view_exception_ce);
		ZEPHIR_INIT_VAR(&_50$$30);
		ZEPHIR_CONCAT_SVS(&_50$$30, "View '", &viewPath_zv, "' was not found in any of the views directory");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_49$$30, "__construct", NULL, 32, &_50$$30);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_49$$30, "phalcon/Mvc/View.zep", 1127);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Checks if a path is absolute or not
 */
PHP_METHOD(Phalcon_Mvc_View, isAbsolutePath)
{
	unsigned char _8, _2$$3, _5$$3;
	zend_bool _7, _1$$3, _4$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval path_zv, _0, _9, _3$$3, _6$$3;
	zend_string *path = NULL;

	ZVAL_UNDEF(&path_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_6$$3);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&path_zv);
	ZVAL_STR_COPY(&path_zv, path);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "PHP_OS");
	if (ZEPHIR_IS_STRING_IDENTICAL(&_0, "WINNT")) {
		_1$$3 = zephir_fast_strlen_ev(&path_zv) >= 3;
		if (_1$$3) {
			ZEPHIR_INIT_VAR(&_3$$3);
			zephir_string_offset_read(&_3$$3, &path_zv, 1, PH_NOISY);
			_1$$3 = ZEPHIR_CHAR_VALUE(&_3$$3) == ':';
		}
		_4$$3 = _1$$3;
		if (_4$$3) {
			ZEPHIR_INIT_VAR(&_6$$3);
			zephir_string_offset_read(&_6$$3, &path_zv, 2, PH_NOISY);
			_4$$3 = ZEPHIR_CHAR_VALUE(&_6$$3) == '\\';
		}
		RETURN_MM_BOOL(_4$$3);
	}
	_7 = zephir_fast_strlen_ev(&path_zv) >= 1;
	if (_7) {
		ZEPHIR_INIT_VAR(&_9);
		zephir_string_offset_read(&_9, &path_zv, 0, PH_NOISY);
		_7 = ZEPHIR_CHAR_VALUE(&_9) == '/';
	}
	RETURN_MM_BOOL(_7);
}

/**
 * Loads registered template engines, if none is registered it will use
 * Phalcon\Mvc\View\Engine\Php
 */
PHP_METHOD(Phalcon_Mvc_View, loadTemplateEngines)
{
	zval _16$$11, _24$$17;
	zend_class_entry *_9$$9, *_20$$15;
	zend_bool _18$$5;
	zend_string *_7$$5;
	zend_ulong _6$$5;
	zval engines, di, registeredEngines, engineService, extension, _0, _1$$3, _2$$4, *_3$$5, _4$$5, *_5$$5, _17$$5, _8$$9, _12$$12, _13$$12, _15$$11, _19$$15, _21$$18, _22$$18, _23$$17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_11 = NULL, *_14 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&di);
	ZVAL_UNDEF(&registeredEngines);
	ZVAL_UNDEF(&engineService);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_19$$15);
	ZVAL_UNDEF(&_21$$18);
	ZVAL_UNDEF(&_22$$18);
	ZVAL_UNDEF(&_23$$17);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_24$$17);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("engines", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("registeredEngines", 17, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 888, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&engines, &_0);
	if (ZEPHIR_IS_FALSE_IDENTICAL(&engines)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 895, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&di, &_1$$3);
		ZEPHIR_INIT_NVAR(&engines);
		array_init(&engines);
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_2, 885, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&registeredEngines, &_1$$3);
		if (ZEPHIR_IS_EMPTY(&registeredEngines)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, phalcon_mvc_view_engine_php_ce);
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 0, this_ptr, &di);
			zephir_check_call_status();
			zephir_array_update_string(&engines, SL(".phtml"), &_2$$4, PH_COPY | PH_SEPARATE);
		} else {
			if (Z_TYPE_P(&di) != IS_OBJECT) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "A dependency injection container is required to access application services", "phalcon/Mvc/View.zep", 1171);
				return;
			}
			if (Z_TYPE_P(&registeredEngines) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_4$$5);
				zephir_string_to_char_array(&_4$$5, &registeredEngines);
				_3$$5 = &_4$$5;
			} else {
				_3$$5 = &registeredEngines;
			}
			zephir_is_iterable(_3$$5, 0, "phalcon/Mvc/View.zep", 1208);
			if (Z_TYPE_P(_3$$5) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_3$$5), _6$$5, _7$$5, _5$$5)
				{
					ZEPHIR_INIT_NVAR(&extension);
					if (_7$$5 != NULL) { 
						ZVAL_STR_COPY(&extension, _7$$5);
					} else {
						ZVAL_LONG(&extension, _6$$5);
					}
					ZEPHIR_INIT_NVAR(&engineService);
					ZVAL_COPY(&engineService, _5$$5);
					if (Z_TYPE_P(&engineService) == IS_OBJECT) {
						if (zephir_is_instance_of(&engineService, SL("Closure"))) {
							_9$$9 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
							ZEPHIR_CALL_CE_STATIC(&_8$$9, _9$$9, "bind", &_10, 0, &engineService, &di);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&engineService, &_8$$9);
							ZEPHIR_CALL_FUNCTION(&_8$$9, "call_user_func", &_11, 191, &engineService, this_ptr);
							zephir_check_call_status();
							zephir_array_update_zval(&engines, &extension, &_8$$9, PH_COPY | PH_SEPARATE);
						} else {
							zephir_array_update_zval(&engines, &extension, &engineService, PH_COPY | PH_SEPARATE);
						}
					} else {
						if (Z_TYPE_P(&engineService) != IS_STRING) {
							ZEPHIR_INIT_NVAR(&_12$$12);
							object_init_ex(&_12$$12, phalcon_mvc_view_exception_ce);
							ZEPHIR_INIT_NVAR(&_13$$12);
							ZEPHIR_CONCAT_SV(&_13$$12, "Invalid template engine registration for extension: ", &extension);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_12$$12, "__construct", &_14, 32, &_13$$12);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_12$$12, "phalcon/Mvc/View.zep", 1199);
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_INIT_NVAR(&_16$$11);
						zephir_create_array(&_16$$11, 1, 0);
						zephir_array_fast_append(&_16$$11, this_ptr);
						ZEPHIR_CALL_METHOD(&_15$$11, &di, "get", NULL, 0, &engineService, &_16$$11);
						zephir_check_call_status();
						zephir_array_update_zval(&engines, &extension, &_15$$11, PH_COPY | PH_SEPARATE);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3$$5, "rewind", NULL, 0);
				zephir_check_call_status();
				_18$$5 = 1;
				while (1) {
					if (_18$$5) {
						_18$$5 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _3$$5, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_17$$5, _3$$5, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_17$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&extension, _3$$5, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&engineService, _3$$5, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&engineService) == IS_OBJECT) {
							if (zephir_is_instance_of(&engineService, SL("Closure"))) {
								_20$$15 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
								ZEPHIR_CALL_CE_STATIC(&_19$$15, _20$$15, "bind", &_10, 0, &engineService, &di);
								zephir_check_call_status();
								ZEPHIR_CPY_WRT(&engineService, &_19$$15);
								ZEPHIR_CALL_FUNCTION(&_19$$15, "call_user_func", &_11, 191, &engineService, this_ptr);
								zephir_check_call_status();
								zephir_array_update_zval(&engines, &extension, &_19$$15, PH_COPY | PH_SEPARATE);
							} else {
								zephir_array_update_zval(&engines, &extension, &engineService, PH_COPY | PH_SEPARATE);
							}
						} else {
							if (Z_TYPE_P(&engineService) != IS_STRING) {
								ZEPHIR_INIT_NVAR(&_21$$18);
								object_init_ex(&_21$$18, phalcon_mvc_view_exception_ce);
								ZEPHIR_INIT_NVAR(&_22$$18);
								ZEPHIR_CONCAT_SV(&_22$$18, "Invalid template engine registration for extension: ", &extension);
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								ZEPHIR_CALL_METHOD(NULL, &_21$$18, "__construct", &_14, 32, &_22$$18);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_21$$18, "phalcon/Mvc/View.zep", 1199);
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_INIT_NVAR(&_24$$17);
							zephir_create_array(&_24$$17, 1, 0);
							zephir_array_fast_append(&_24$$17, this_ptr);
							ZEPHIR_CALL_METHOD(&_23$$17, &di, "get", NULL, 0, &engineService, &_24$$17);
							zephir_check_call_status();
							zephir_array_update_zval(&engines, &extension, &_23$$17, PH_COPY | PH_SEPARATE);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&engineService);
			ZEPHIR_INIT_NVAR(&extension);
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 888, &engines);
	}
	RETURN_CCTOR(&engines);
}

/**
 * Processes the view and templates; Fires events if needed
 */
PHP_METHOD(Phalcon_Mvc_View, processRender)
{
	zval _3$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, renderLevel = 0;
	zend_bool fireEvents, silence = 0, _5, _36, _18$$17, _30$$23;
	zval params;
	zval controllerName_zv, actionName_zv, *params_param = NULL, *fireEvents_param = NULL, layoutsDir, layout, pickView, layoutName, engines, renderView, pickViewAction, eventsManager, disabledLevels, templatesBefore, templatesAfter, templateBefore, templateAfter, _0, _2, _4, _8, _9, _1$$3, _6$$11, _7$$11, _10$$15, _11$$17, *_12$$17, _13$$17, *_14$$17, _17$$17, _15$$18, _16$$18, _19$$19, _20$$19, _21$$21, _22$$21, _23$$23, *_24$$23, _25$$23, *_26$$23, _29$$23, _27$$24, _28$$24, _31$$25, _32$$25, _33$$27, _34$$27, _35$$13, _37$$28;
	zend_string *controllerName = NULL, *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName_zv);
	ZVAL_UNDEF(&actionName_zv);
	ZVAL_UNDEF(&layoutsDir);
	ZVAL_UNDEF(&layout);
	ZVAL_UNDEF(&pickView);
	ZVAL_UNDEF(&layoutName);
	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&renderView);
	ZVAL_UNDEF(&pickViewAction);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&disabledLevels);
	ZVAL_UNDEF(&templatesBefore);
	ZVAL_UNDEF(&templatesAfter);
	ZVAL_UNDEF(&templateBefore);
	ZVAL_UNDEF(&templateAfter);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_6$$11);
	ZVAL_UNDEF(&_7$$11);
	ZVAL_UNDEF(&_10$$15);
	ZVAL_UNDEF(&_11$$17);
	ZVAL_UNDEF(&_13$$17);
	ZVAL_UNDEF(&_17$$17);
	ZVAL_UNDEF(&_15$$18);
	ZVAL_UNDEF(&_16$$18);
	ZVAL_UNDEF(&_19$$19);
	ZVAL_UNDEF(&_20$$19);
	ZVAL_UNDEF(&_21$$21);
	ZVAL_UNDEF(&_22$$21);
	ZVAL_UNDEF(&_23$$23);
	ZVAL_UNDEF(&_25$$23);
	ZVAL_UNDEF(&_29$$23);
	ZVAL_UNDEF(&_27$$24);
	ZVAL_UNDEF(&_28$$24);
	ZVAL_UNDEF(&_31$$25);
	ZVAL_UNDEF(&_32$$25);
	ZVAL_UNDEF(&_33$$27);
	ZVAL_UNDEF(&_34$$27);
	ZVAL_UNDEF(&_35$$13);
	ZVAL_UNDEF(&_37$$28);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_3$$7);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	static zend_string *_zephir_prop_6 = NULL;
	static zend_string *_zephir_prop_7 = NULL;
	static zend_string *_zephir_prop_8 = NULL;
	static zend_string *_zephir_prop_9 = NULL;
	static zend_string *_zephir_prop_10 = NULL;
	static zend_string *_zephir_prop_11 = NULL;
	static zend_string *_zephir_prop_12 = NULL;
	static zend_string *_zephir_prop_13 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("currentRenderLevel", 18, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("disabled", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("content", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("controllerName", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("actionName", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("layoutsDir", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("layout", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("pickView", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("disabledLevels", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("renderLevel", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("templatesBefore", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_12)) {
		_zephir_prop_12 = zend_string_init("templatesAfter", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_13)) {
		_zephir_prop_13 = zend_string_init("mainView", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 4)
		Z_PARAM_STR(controllerName)
		Z_PARAM_STR(actionName)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
		Z_PARAM_BOOL(fireEvents)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (ZEND_NUM_ARGS() > 2) {
		params_param = ZEND_CALL_ARG(execute_data, 3);
	}
	if (ZEND_NUM_ARGS() > 3) {
		fireEvents_param = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&controllerName_zv);
	ZVAL_STR_COPY(&controllerName_zv, controllerName);
	zephir_memory_observe(&actionName_zv);
	ZVAL_STR_COPY(&actionName_zv, actionName);
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	if (!fireEvents_param) {
		fireEvents = 1;
	} else {
		}
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 881, PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_0)) {
		ZEPHIR_CALL_FUNCTION(&_1$$3, "ob_get_contents", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 890, &_1$$3);
		RETURN_MM_BOOL(0);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 897, &controllerName_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 898, &actionName_zv);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setVars", NULL, 0, &params);
	zephir_check_call_status();
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_5, 893, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&layoutsDir, &_2);
	if (!(zephir_is_true(&layoutsDir))) {
		ZEPHIR_INIT_NVAR(&layoutsDir);
		ZVAL_STRING(&layoutsDir, "layouts/");
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_6, 892, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&layout, &_2);
	if (zephir_is_true(&layout)) {
		ZEPHIR_CPY_WRT(&layoutName, &layout);
	} else {
		ZEPHIR_CPY_WRT(&layoutName, &controllerName_zv);
	}
	ZEPHIR_CALL_METHOD(&engines, this_ptr, "loadTemplateEngines", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_7, 887, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&pickView, &_2);
	if (Z_TYPE_P(&pickView) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_3$$7);
		ZEPHIR_CONCAT_VSV(&_3$$7, &controllerName_zv, "/", &actionName_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&renderView, &_3$$7);
	} else {
		ZEPHIR_OBS_NVAR(&renderView);
		zephir_array_fetch_long(&renderView, &pickView, 0, PH_NOISY, "phalcon/Mvc/View.zep", 1286);
		if (Z_TYPE_P(&layoutName) == IS_NULL) {
			zephir_memory_observe(&pickViewAction);
			if (zephir_array_isset_long_fetch(&pickViewAction, &pickView, 1, 0)) {
				ZEPHIR_CPY_WRT(&layoutName, &pickViewAction);
			}
		}
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_8, 891, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_2);
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CREATE_SYMBOL_TABLE();
	
	_5 = fireEvents;
	if (_5) {
		_5 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_5) {
		ZEPHIR_INIT_VAR(&_7$$11);
		ZVAL_STRING(&_7$$11, "view:beforeRender");
		ZEPHIR_CALL_METHOD(&_6$$11, &eventsManager, "fire", NULL, 0, &_7$$11, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_6$$11)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_8, "ob_get_contents", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 890, &_8);
	silence = 1;
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_9, 880, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&disabledLevels, &_2);
	zephir_memory_observe(&_9);
	zephir_read_property_cached(&_9, this_ptr, _zephir_prop_10, 889, PH_NOISY_CC);
	renderLevel = zephir_get_intval(&_9);
	if (renderLevel) {
		if (renderLevel >= 1) {
			if (!(zephir_array_isset_value_long(&disabledLevels, 1))) {
				ZVAL_UNDEF(&_10$$15);
				ZVAL_LONG(&_10$$15, 1);
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_10$$15);
				if (silence) {
					ZVAL_BOOL(&_10$$15, 1);
				} else {
					ZVAL_BOOL(&_10$$15, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &renderView, &_10$$15);
				zephir_check_call_status();
			}
		}
		if (renderLevel >= 2) {
			if (!(zephir_array_isset_value_long(&disabledLevels, 2))) {
				ZVAL_UNDEF(&_11$$17);
				ZVAL_LONG(&_11$$17, 2);
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_11$$17);
				zephir_read_property_cached(&_11$$17, this_ptr, _zephir_prop_11, 879, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&templatesBefore, &_11$$17);
				silence = 0;
				if (Z_TYPE_P(&templatesBefore) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_13$$17);
					zephir_string_to_char_array(&_13$$17, &templatesBefore);
					_12$$17 = &_13$$17;
				} else {
					_12$$17 = &templatesBefore;
				}
				zephir_is_iterable(_12$$17, 0, "phalcon/Mvc/View.zep", 1362);
				if (Z_TYPE_P(_12$$17) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_12$$17), _14$$17)
					{
						ZEPHIR_INIT_NVAR(&templateBefore);
						ZVAL_COPY(&templateBefore, _14$$17);
						ZEPHIR_INIT_NVAR(&_15$$18);
						ZEPHIR_CONCAT_VV(&_15$$18, &layoutsDir, &templateBefore);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if (silence) {
							ZVAL_BOOL(&_16$$18, 1);
						} else {
							ZVAL_BOOL(&_16$$18, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &_15$$18, &_16$$18);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _12$$17, "rewind", NULL, 0);
					zephir_check_call_status();
					_18$$17 = 1;
					while (1) {
						if (_18$$17) {
							_18$$17 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _12$$17, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_17$$17, _12$$17, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_17$$17)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&templateBefore, _12$$17, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_19$$19);
							ZEPHIR_CONCAT_VV(&_19$$19, &layoutsDir, &templateBefore);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if (silence) {
								ZVAL_BOOL(&_20$$19, 1);
							} else {
								ZVAL_BOOL(&_20$$19, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &_19$$19, &_20$$19);
							zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&templateBefore);
				silence = 1;
			}
		}
		if (renderLevel >= 3) {
			if (!(zephir_array_isset_value_long(&disabledLevels, 3))) {
				ZVAL_UNDEF(&_21$$21);
				ZVAL_LONG(&_21$$21, 3);
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_21$$21);
				ZEPHIR_INIT_VAR(&_22$$21);
				ZEPHIR_CONCAT_VV(&_22$$21, &layoutsDir, &layoutName);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (silence) {
					ZVAL_BOOL(&_21$$21, 1);
				} else {
					ZVAL_BOOL(&_21$$21, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &_22$$21, &_21$$21);
				zephir_check_call_status();
			}
		}
		if (renderLevel >= 4) {
			if (!(zephir_array_isset_value_long(&disabledLevels, 4))) {
				ZVAL_UNDEF(&_23$$23);
				ZVAL_LONG(&_23$$23, 4);
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_23$$23);
				zephir_read_property_cached(&_23$$23, this_ptr, _zephir_prop_12, 878, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&templatesAfter, &_23$$23);
				silence = 0;
				if (Z_TYPE_P(&templatesAfter) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_25$$23);
					zephir_string_to_char_array(&_25$$23, &templatesAfter);
					_24$$23 = &_25$$23;
				} else {
					_24$$23 = &templatesAfter;
				}
				zephir_is_iterable(_24$$23, 0, "phalcon/Mvc/View.zep", 1398);
				if (Z_TYPE_P(_24$$23) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_24$$23), _26$$23)
					{
						ZEPHIR_INIT_NVAR(&templateAfter);
						ZVAL_COPY(&templateAfter, _26$$23);
						ZEPHIR_INIT_NVAR(&_27$$24);
						ZEPHIR_CONCAT_VV(&_27$$24, &layoutsDir, &templateAfter);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if (silence) {
							ZVAL_BOOL(&_28$$24, 1);
						} else {
							ZVAL_BOOL(&_28$$24, 0);
						}
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &_27$$24, &_28$$24);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _24$$23, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$23 = 1;
					while (1) {
						if (_30$$23) {
							_30$$23 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _24$$23, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$23, _24$$23, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$23)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&templateAfter, _24$$23, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$25);
							ZEPHIR_CONCAT_VV(&_31$$25, &layoutsDir, &templateAfter);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							if (silence) {
								ZVAL_BOOL(&_32$$25, 1);
							} else {
								ZVAL_BOOL(&_32$$25, 0);
							}
							ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &_31$$25, &_32$$25);
							zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&templateAfter);
				silence = 1;
			}
		}
		if (renderLevel >= 5) {
			if (!(zephir_array_isset_value_long(&disabledLevels, 5))) {
				ZVAL_UNDEF(&_33$$27);
				ZVAL_LONG(&_33$$27, 5);
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_33$$27);
				zephir_read_property_cached(&_33$$27, this_ptr, _zephir_prop_13, 894, PH_NOISY_CC | PH_READONLY);
				if (silence) {
					ZVAL_BOOL(&_34$$27, 1);
				} else {
					ZVAL_BOOL(&_34$$27, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "engineRender", NULL, 0, &engines, &_33$$27, &_34$$27);
				zephir_check_call_status();
			}
		}
		ZVAL_UNDEF(&_35$$13);
		ZVAL_LONG(&_35$$13, 0);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 896, &_35$$13);
	}
	_36 = fireEvents;
	if (_36) {
		_36 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_36) {
		ZEPHIR_INIT_VAR(&_37$$28);
		ZVAL_STRING(&_37$$28, "view:afterRender");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_37$$28, this_ptr);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(1);
}

/**
 * @todo Remove this when we get traits
 */
PHP_METHOD(Phalcon_Mvc_View, getDirSeparator)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval directory_zv, _0, _1;
	zend_string *directory = NULL;

	ZVAL_UNDEF(&directory_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(directory)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&directory_zv);
	ZVAL_STR_COPY(&directory_zv, directory);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/");
	zephir_fast_trim(&_0, &directory_zv, &_1, ZEPHIR_TRIM_RIGHT);
	ZEPHIR_CONCAT_VS(return_value, &_0, "/");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

zend_object *zephir_init_properties_Phalcon_Mvc_View(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _12, _14, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9, _15$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$10);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("viewParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("viewParams"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("viewsDirs"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("viewsDirs"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("templatesBefore"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("templatesBefore"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("templatesAfter"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("templatesAfter"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("registeredEngines"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("registeredEngines"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("params"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("params"), &_11$$8);
		}
		zephir_read_property_ex(&_12, this_ptr, ZEND_STRL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("options"), &_13$$9);
		}
		zephir_read_property_ex(&_14, this_ptr, ZEND_STRL("disabledLevels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_14) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_15$$10);
			array_init(&_15$$10);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("disabledLevels"), &_15$$10);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

