
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/string.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the
 * LICENSE.txt file that was distributed with this source code.
 */
/**
 * This is the base class for Phalcon\Mvc\Dispatcher and Phalcon\Cli\Dispatcher.
 * This class can't be instantiated directly, you can use it to create your own
 * dispatchers.
 */
ZEPHIR_INIT_CLASS(Phalcon_Dispatcher_AbstractDispatcher)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Dispatcher, AbstractDispatcher, phalcon, dispatcher_abstractdispatcher, phalcon_di_abstractinjectionaware_ce, phalcon_dispatcher_abstractdispatcher_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * @var object|null
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("activeHandler"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("activeMethodMap"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("actionName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("actionSuffix"), "Action", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("camelCaseMap"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("defaultAction"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("defaultNamespace"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("defaultHandler"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("handlerHashes"), ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("handlerName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("handlerSuffix"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var ManagerInterface|null
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("eventsManager"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_dispatcher_abstractdispatcher_ce, SL("finished"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_dispatcher_abstractdispatcher_ce, SL("forwarded"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_dispatcher_abstractdispatcher_ce, SL("isControllerInitialize"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var mixed|null
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("lastHandler"), ZEND_ACC_PROTECTED);
	/**
	 * @var BinderInterface|null
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("modelBinder"), ZEND_ACC_PROTECTED);
	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_dispatcher_abstractdispatcher_ce, SL("modelBinding"), 0, ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("moduleName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("namespaceName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("params"), ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("previousActionName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("previousHandlerName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_string(phalcon_dispatcher_abstractdispatcher_ce, SL("previousNamespaceName"), "", ZEND_ACC_PROTECTED);
	/**
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_dispatcher_abstractdispatcher_ce, SL("returnedValue"), ZEND_ACC_PROTECTED);
	phalcon_dispatcher_abstractdispatcher_ce->create_object = zephir_init_properties_Phalcon_Dispatcher_AbstractDispatcher;

	zend_class_implements(phalcon_dispatcher_abstractdispatcher_ce, 1, phalcon_dispatcher_dispatcherinterface_ce);
	zend_class_implements(phalcon_dispatcher_abstractdispatcher_ce, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;
}

PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, callActionMethod)
{
	zend_bool _1, _14;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params, _11, _5$$3, _6$$3;
	zend_string *actionMethod = NULL;
	zval *handler, handler_sub, actionMethod_zv, *params_param = NULL, result, observer, altHandler, altAction, altParams, _0, _2, _12, _13, _15, _3$$3, _4$$3, _7$$3, _8$$3, _9$$3, _10$$3, _16$$4, _17$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZVAL_UNDEF(&actionMethod_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&observer);
	ZVAL_UNDEF(&altHandler);
	ZVAL_UNDEF(&altAction);
	ZVAL_UNDEF(&altParams);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("eventsManager", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_ZVAL(handler)
		Z_PARAM_STR(actionMethod)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	handler = ZEND_CALL_ARG(execute_data, 1);
	if (ZEND_NUM_ARGS() > 2) {
		params_param = ZEND_CALL_ARG(execute_data, 3);
	}
	zephir_memory_observe(&actionMethod_zv);
	ZVAL_STR_COPY(&actionMethod_zv, actionMethod);
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&params, params_param);
	}
	ZEPHIR_INIT_VAR(&observer);
	ZEPHIR_CPY_WRT(&altHandler, handler);
	ZEPHIR_CPY_WRT(&altAction, &actionMethod_zv);
	ZEPHIR_CPY_WRT(&altParams, &params);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 127, PH_NOISY_CC | PH_READONLY);
	_1 = Z_TYPE_P(&_0) != IS_NULL;
	if (_1) {
		zephir_memory_observe(&_2);
		zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 127, PH_NOISY_CC);
		_1 = zephir_instance_of_ev(&_2, phalcon_events_managerinterface_ce);
	}
	if (_1) {
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "getDi", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		zephir_create_array(&_5$$3, 1, 0);
		ZEPHIR_INIT_VAR(&_6$$3);
		zephir_create_array(&_6$$3, 3, 0);
		zephir_array_update_string(&_6$$3, SL("handler"), handler, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_6$$3, SL("action"), &actionMethod_zv, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_6$$3, SL("params"), &params, PH_COPY | PH_SEPARATE);
		zephir_array_fast_append(&_5$$3, &_6$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "Phalcon\\Support\\Collection");
		ZEPHIR_CALL_METHOD(&_4$$3, &_3$$3, "get", NULL, 0, &_7$$3, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&observer, &_4$$3);
		zephir_read_property_cached(&_8$$3, this_ptr, _zephir_prop_0, 127, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "dispatch:beforeCallAction");
		ZEPHIR_CALL_METHOD(NULL, &_8$$3, "fire", NULL, 0, &_7$$3, this_ptr, &observer);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "handler");
		ZEPHIR_CALL_METHOD(&altHandler, &observer, "get", NULL, 0, &_7$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "action");
		ZEPHIR_CALL_METHOD(&altAction, &observer, "get", NULL, 0, &_7$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_7$$3);
		array_init(&_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZVAL_STRING(&_9$$3, "params");
		ZEPHIR_INIT_VAR(&_10$$3);
		ZVAL_STRING(&_10$$3, "array");
		ZEPHIR_CALL_METHOD(&altParams, &observer, "get", NULL, 0, &_9$$3, &_7$$3, &_10$$3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_11);
	zephir_create_array(&_11, 2, 0);
	zephir_array_fast_append(&_11, &altHandler);
	zephir_array_fast_append(&_11, &altAction);
	ZEPHIR_CALL_FUNCTION(&_12, "array_values", NULL, 13, &altParams);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZEPHIR_CALL_USER_FUNC_ARRAY(&result, &_11, &_12);
	zephir_check_call_status();
	zephir_read_property_cached(&_13, this_ptr, _zephir_prop_0, 127, PH_NOISY_CC | PH_READONLY);
	_14 = Z_TYPE_P(&_13) != IS_NULL;
	if (_14) {
		zephir_memory_observe(&_15);
		zephir_read_property_cached(&_15, this_ptr, _zephir_prop_0, 127, PH_NOISY_CC);
		_14 = zephir_instance_of_ev(&_15, phalcon_events_managerinterface_ce);
	}
	if (_14) {
		zephir_array_update_string(&observer, SL("result"), &result, PH_COPY | PH_SEPARATE);
		zephir_read_property_cached(&_16$$4, this_ptr, _zephir_prop_0, 127, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_17$$4);
		ZVAL_STRING(&_17$$4, "dispatch:afterCallAction");
		ZEPHIR_CALL_METHOD(NULL, &_16$$4, "fire", NULL, 0, &_17$$4, this_ptr, &observer);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&result);
}

/**
 * Process the results of the router by calling into the appropriate
 * controller action(s) including any routing data or injected parameters.
 *
 * @return mixed Returns the dispatched handler class (the Controller for Mvc dispatching or a Task
 *               for CLI dispatching) or <tt>false</tt> if an exception occurred and the operation was
 *               stopped by returning <tt>false</tt> in the exception handler.
 *
 * @throws \Exception if any uncaught or unhandled exception occurs during the dispatcher process.
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, dispatch)
{
	zval _44$$11;
	zend_bool hasService = 0, hasEventsManager = 0, isNewHandler = 0, _5$$5, _16$$14, _21$$16, _29$$20, _34$$22, _42$$25, _52$$27, _56$$33, _62$$35, _66$$39, _72$$41, _78$$47, _83$$51, _88$$53, _105$$65, _110$$69, _115$$71, _118$$75, _123$$77, _130$$82;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL, *_12 = NULL, *_15 = NULL, *_20 = NULL, *_23 = NULL, *_25 = NULL, *_28 = NULL, *_30 = NULL, *_33 = NULL, *_35 = NULL, *_41 = NULL, *_43 = NULL, *_47 = NULL, *_51 = NULL, *_55 = NULL, *_58 = NULL, *_61 = NULL, *_64 = NULL, *_68 = NULL, *_71 = NULL, *_74 = NULL, *_77 = NULL, *_82 = NULL, *_87 = NULL, *_94 = NULL, *_100 = NULL, *_104 = NULL, *_109 = NULL, *_114 = NULL, *_122 = NULL, *_126 = NULL, *_129 = NULL;
	zval __$true, __$false, value, handler, container, namespaceName, handlerName, actionName, eventsManager, handlerClass, status, actionMethod, modelBinder, bindCacheKey, handlerHash, e, _0, _1$$3, _2$$3, _3$$5, _4$$5, _6$$5, _7$$4, _8$$7, _9$$12, _10$$12, _13$$14, _14$$14, _17$$14, _18$$13, _19$$16, _22$$16, _24$$11, _36$$11, _37$$11, _38$$11, _102$$11, _26$$20, _27$$20, _31$$22, _32$$22, _39$$25, _40$$25, _45$$28, _46$$28, _48$$28, _49$$27, _50$$27, _53$$33, _54$$33, _57$$33, _59$$32, _60$$35, _63$$35, _65$$39, _67$$39, _69$$38, _70$$41, _73$$41, _75$$45, _76$$47, _79$$47, _80$$51, _81$$51, _84$$51, _85$$50, _86$$53, _89$$53, _90$$56, _91$$56, _92$$57, _93$$57, _95$$57, _96$$60, _97$$60, _98$$63, _99$$63, _101$$63, _103$$65, _106$$65, _107$$69, _108$$69, _111$$69, _112$$68, _113$$71, _116$$71, _117$$75, _119$$75, _120$$74, _121$$77, _124$$77, _125$$81, _127$$80, _128$$82, _131$$82, _132$$86, _133$$85, _134$$87;
	zend_long ZEPHIR_LAST_CALL_STATUS, numberDispatches = 0;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&namespaceName);
	ZVAL_UNDEF(&handlerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&handlerClass);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&actionMethod);
	ZVAL_UNDEF(&modelBinder);
	ZVAL_UNDEF(&bindCacheKey);
	ZVAL_UNDEF(&handlerHash);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_10$$12);
	ZVAL_UNDEF(&_13$$14);
	ZVAL_UNDEF(&_14$$14);
	ZVAL_UNDEF(&_17$$14);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$16);
	ZVAL_UNDEF(&_22$$16);
	ZVAL_UNDEF(&_24$$11);
	ZVAL_UNDEF(&_36$$11);
	ZVAL_UNDEF(&_37$$11);
	ZVAL_UNDEF(&_38$$11);
	ZVAL_UNDEF(&_102$$11);
	ZVAL_UNDEF(&_26$$20);
	ZVAL_UNDEF(&_27$$20);
	ZVAL_UNDEF(&_31$$22);
	ZVAL_UNDEF(&_32$$22);
	ZVAL_UNDEF(&_39$$25);
	ZVAL_UNDEF(&_40$$25);
	ZVAL_UNDEF(&_45$$28);
	ZVAL_UNDEF(&_46$$28);
	ZVAL_UNDEF(&_48$$28);
	ZVAL_UNDEF(&_49$$27);
	ZVAL_UNDEF(&_50$$27);
	ZVAL_UNDEF(&_53$$33);
	ZVAL_UNDEF(&_54$$33);
	ZVAL_UNDEF(&_57$$33);
	ZVAL_UNDEF(&_59$$32);
	ZVAL_UNDEF(&_60$$35);
	ZVAL_UNDEF(&_63$$35);
	ZVAL_UNDEF(&_65$$39);
	ZVAL_UNDEF(&_67$$39);
	ZVAL_UNDEF(&_69$$38);
	ZVAL_UNDEF(&_70$$41);
	ZVAL_UNDEF(&_73$$41);
	ZVAL_UNDEF(&_75$$45);
	ZVAL_UNDEF(&_76$$47);
	ZVAL_UNDEF(&_79$$47);
	ZVAL_UNDEF(&_80$$51);
	ZVAL_UNDEF(&_81$$51);
	ZVAL_UNDEF(&_84$$51);
	ZVAL_UNDEF(&_85$$50);
	ZVAL_UNDEF(&_86$$53);
	ZVAL_UNDEF(&_89$$53);
	ZVAL_UNDEF(&_90$$56);
	ZVAL_UNDEF(&_91$$56);
	ZVAL_UNDEF(&_92$$57);
	ZVAL_UNDEF(&_93$$57);
	ZVAL_UNDEF(&_95$$57);
	ZVAL_UNDEF(&_96$$60);
	ZVAL_UNDEF(&_97$$60);
	ZVAL_UNDEF(&_98$$63);
	ZVAL_UNDEF(&_99$$63);
	ZVAL_UNDEF(&_101$$63);
	ZVAL_UNDEF(&_103$$65);
	ZVAL_UNDEF(&_106$$65);
	ZVAL_UNDEF(&_107$$69);
	ZVAL_UNDEF(&_108$$69);
	ZVAL_UNDEF(&_111$$69);
	ZVAL_UNDEF(&_112$$68);
	ZVAL_UNDEF(&_113$$71);
	ZVAL_UNDEF(&_116$$71);
	ZVAL_UNDEF(&_117$$75);
	ZVAL_UNDEF(&_119$$75);
	ZVAL_UNDEF(&_120$$74);
	ZVAL_UNDEF(&_121$$77);
	ZVAL_UNDEF(&_124$$77);
	ZVAL_UNDEF(&_125$$81);
	ZVAL_UNDEF(&_127$$80);
	ZVAL_UNDEF(&_128$$82);
	ZVAL_UNDEF(&_131$$82);
	ZVAL_UNDEF(&_132$$86);
	ZVAL_UNDEF(&_133$$85);
	ZVAL_UNDEF(&_134$$87);
	ZVAL_UNDEF(&_44$$11);
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
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("eventsManager", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("finished", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("handlerHashes", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("activeHandler", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("namespaceName", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("handlerName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("actionName", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("params", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("isControllerInitialize", 22, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("modelBinding", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("modelBinder", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_12)) {
		_zephir_prop_12 = zend_string_init("lastHandler", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_13)) {
		_zephir_prop_13 = zend_string_init("returnedValue", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 128, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_0);
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "A dependency injection container is required to access related dispatching services");
		ZVAL_LONG(&_2$$3, 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwDispatchException", NULL, 0, &_1$$3, &_2$$3);
		zephir_check_call_status();
		RETURN_MM_BOOL(0);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 127, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	hasEventsManager = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 129, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 129, &__$false);
	}
	if (hasEventsManager) {

		/* try_start_1: */

			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "dispatch:beforeDispatchLoop");
			ZEPHIR_CALL_METHOD(&_3$$5, &eventsManager, "fire", NULL, 0, &_4$$5, this_ptr);
			zephir_check_call_status_or_jump(try_end_1);
			_5$$5 = ZEPHIR_IS_FALSE_IDENTICAL(&_3$$5);
			if (_5$$5) {
				zephir_read_property_cached(&_6$$5, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				_5$$5 = !ZEPHIR_IS_FALSE_IDENTICAL(&_6$$5);
			}
			if (_5$$5) {
				RETURN_MM_BOOL(0);
			}

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_VAR(&_7$$4);
			ZVAL_OBJ(&_7$$4, EG(exception));
			Z_ADDREF_P(&_7$$4);
			if (zephir_is_instance_of(&_7$$4, SL("Exception"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&e, &_7$$4);
				ZEPHIR_CALL_METHOD(&status, this_ptr, "handleException", NULL, 0, &e);
				zephir_check_call_status();
				zephir_read_property_cached(&_8$$7, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				if (!ZEPHIR_IS_FALSE_IDENTICAL(&_8$$7)) {
					if (ZEPHIR_IS_FALSE_IDENTICAL(&status)) {
						RETURN_MM_BOOL(0);
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 272);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_INIT_VAR(&value);
	ZVAL_NULL(&value);
	ZEPHIR_INIT_VAR(&handler);
	ZVAL_NULL(&handler);
	numberDispatches = 0;
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 129, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 129, &__$false);
	}
	while (1) {
		zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
		if (!(!(zephir_is_true(&_0)))) {
			break;
		}
		numberDispatches++;
		if (UNEXPECTED(numberDispatches == 256)) {
			ZEPHIR_INIT_NVAR(&_9$$12);
			ZVAL_STRING(&_9$$12, "Dispatcher has detected a cyclic routing causing stability problems");
			ZVAL_LONG(&_10$$12, 1);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwDispatchException", &_11, 0, &_9$$12, &_10$$12);
			zephir_check_call_status();
			break;
		}
		if (1) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 129, &__$true);
		} else {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 129, &__$false);
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "resolveEmptyProperties", &_12, 0);
		zephir_check_call_status();
		if (hasEventsManager) {

			/* try_start_2: */

				ZEPHIR_INIT_NVAR(&_14$$14);
				ZVAL_STRING(&_14$$14, "dispatch:beforeDispatch");
				ZEPHIR_CALL_METHOD(&_13$$14, &eventsManager, "fire", &_15, 0, &_14$$14, this_ptr);
				zephir_check_call_status_or_jump(try_end_2);
				_16$$14 = ZEPHIR_IS_FALSE_IDENTICAL(&_13$$14);
				if (!(_16$$14)) {
					zephir_read_property_cached(&_17$$14, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
					_16$$14 = ZEPHIR_IS_FALSE_IDENTICAL(&_17$$14);
				}
				if (_16$$14) {
					continue;
				}

			try_end_2:

			if (EG(exception)) {
				ZEPHIR_INIT_NVAR(&_18$$13);
				ZVAL_OBJ(&_18$$13, EG(exception));
				Z_ADDREF_P(&_18$$13);
				if (zephir_is_instance_of(&_18$$13, SL("Exception"))) {
					zend_clear_exception();
					ZEPHIR_CPY_WRT(&e, &_18$$13);
					ZEPHIR_CALL_METHOD(&_19$$16, this_ptr, "handleException", &_20, 0, &e);
					zephir_check_call_status();
					_21$$16 = ZEPHIR_IS_FALSE_IDENTICAL(&_19$$16);
					if (!(_21$$16)) {
						zephir_read_property_cached(&_22$$16, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_21$$16 = ZEPHIR_IS_FALSE_IDENTICAL(&_22$$16);
					}
					if (_21$$16) {
						continue;
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 312);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		ZEPHIR_CALL_METHOD(&handlerClass, this_ptr, "getHandlerClass", &_23, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_24$$11, &container, "has", &_25, 0, &handlerClass);
		zephir_check_call_status();
		hasService = zephir_get_boolval(&_24$$11);
		if (!(hasService)) {
			hasService = zephir_class_exists(&handlerClass, 1);
		}
		if (!(hasService)) {
			ZEPHIR_INIT_NVAR(&_26$$20);
			ZEPHIR_CONCAT_VS(&_26$$20, &handlerClass, " handler class cannot be loaded");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZVAL_LONG(&_27$$20, 2);
			ZEPHIR_CALL_METHOD(&status, this_ptr, "throwDispatchException", &_28, 0, &_26$$20, &_27$$20);
			zephir_check_call_status();
			_29$$20 = ZEPHIR_IS_FALSE_IDENTICAL(&status);
			if (_29$$20) {
				zephir_read_property_cached(&_27$$20, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				_29$$20 = ZEPHIR_IS_FALSE_IDENTICAL(&_27$$20);
			}
			if (_29$$20) {
				continue;
			}
			break;
		}
		ZEPHIR_CALL_METHOD(&handler, &container, "getShared", &_30, 0, &handlerClass);
		zephir_check_call_status();
		if (UNEXPECTED(Z_TYPE_P(&handler) != IS_OBJECT)) {
			ZEPHIR_INIT_NVAR(&_31$$22);
			ZVAL_STRING(&_31$$22, "Invalid handler returned from the services container");
			ZVAL_LONG(&_32$$22, 3);
			ZEPHIR_CALL_METHOD(&status, this_ptr, "throwDispatchException", &_33, 0, &_31$$22, &_32$$22);
			zephir_check_call_status();
			_34$$22 = ZEPHIR_IS_FALSE_IDENTICAL(&status);
			if (_34$$22) {
				zephir_read_property_cached(&_32$$22, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				_34$$22 = ZEPHIR_IS_FALSE_IDENTICAL(&_32$$22);
			}
			if (_34$$22) {
				continue;
			}
			break;
		}
		ZEPHIR_CALL_FUNCTION(&handlerHash, "spl_object_hash", &_35, 88, &handler);
		zephir_check_call_status();
		zephir_read_property_cached(&_36$$11, this_ptr, _zephir_prop_3, 130, PH_NOISY_CC | PH_READONLY);
		isNewHandler = !((zephir_array_isset_value(&_36$$11, &handlerHash)));
		if (isNewHandler) {
			zephir_update_property_array(this_ptr, SL("handlerHashes"), &handlerHash, &__$true);
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 131, &handler);
		zephir_read_property_cached(&_37$$11, this_ptr, _zephir_prop_5, 132, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&namespaceName, &_37$$11);
		zephir_read_property_cached(&_37$$11, this_ptr, _zephir_prop_6, 133, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&handlerName, &_37$$11);
		zephir_read_property_cached(&_37$$11, this_ptr, _zephir_prop_7, 134, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&actionName, &_37$$11);
		ZEPHIR_OBS_NVAR(&_38$$11);
		zephir_read_property_cached(&_38$$11, this_ptr, _zephir_prop_8, 135, PH_NOISY_CC);
		if (UNEXPECTED(Z_TYPE_P(&_38$$11) != IS_ARRAY)) {
			ZEPHIR_INIT_NVAR(&_39$$25);
			ZVAL_STRING(&_39$$25, "Action parameters must be an Array");
			ZVAL_LONG(&_40$$25, 4);
			ZEPHIR_CALL_METHOD(&status, this_ptr, "throwDispatchException", &_41, 0, &_39$$25, &_40$$25);
			zephir_check_call_status();
			_42$$25 = ZEPHIR_IS_FALSE_IDENTICAL(&status);
			if (_42$$25) {
				zephir_read_property_cached(&_40$$25, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				_42$$25 = ZEPHIR_IS_FALSE_IDENTICAL(&_40$$25);
			}
			if (_42$$25) {
				continue;
			}
			break;
		}
		ZEPHIR_CALL_METHOD(&actionMethod, this_ptr, "getActiveMethod", &_43, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_44$$11);
		zephir_create_array(&_44$$11, 2, 0);
		zephir_array_fast_append(&_44$$11, &handler);
		zephir_array_fast_append(&_44$$11, &actionMethod);
		if (UNEXPECTED(!(zephir_is_callable(&_44$$11)))) {
			if (hasEventsManager) {
				ZEPHIR_INIT_NVAR(&_46$$28);
				ZVAL_STRING(&_46$$28, "dispatch:beforeNotFoundAction");
				ZEPHIR_CALL_METHOD(&_45$$28, &eventsManager, "fire", &_47, 0, &_46$$28, this_ptr);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_45$$28)) {
					continue;
				}
				zephir_read_property_cached(&_48$$28, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_48$$28)) {
					continue;
				}
			}
			ZEPHIR_INIT_NVAR(&_49$$27);
			ZEPHIR_CONCAT_SVSVS(&_49$$27, "Action '", &actionName, "' was not found on handler '", &handlerName, "'");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZVAL_LONG(&_50$$27, 5);
			ZEPHIR_CALL_METHOD(&status, this_ptr, "throwDispatchException", &_51, 0, &_49$$27, &_50$$27);
			zephir_check_call_status();
			_52$$27 = ZEPHIR_IS_FALSE_IDENTICAL(&status);
			if (_52$$27) {
				zephir_read_property_cached(&_50$$27, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
				_52$$27 = ZEPHIR_IS_FALSE_IDENTICAL(&_50$$27);
			}
			if (_52$$27) {
				continue;
			}
			break;
		}
		if (hasEventsManager) {

			/* try_start_3: */

				ZEPHIR_INIT_NVAR(&_54$$33);
				ZVAL_STRING(&_54$$33, "dispatch:beforeExecuteRoute");
				ZEPHIR_CALL_METHOD(&_53$$33, &eventsManager, "fire", &_55, 0, &_54$$33, this_ptr);
				zephir_check_call_status_or_jump(try_end_3);
				_56$$33 = ZEPHIR_IS_FALSE_IDENTICAL(&_53$$33);
				if (!(_56$$33)) {
					zephir_read_property_cached(&_57$$33, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
					_56$$33 = ZEPHIR_IS_FALSE_IDENTICAL(&_57$$33);
				}
				if (_56$$33) {
					ZEPHIR_CALL_METHOD(NULL, &container, "remove", &_58, 0, &handlerClass);
					zephir_check_call_status_or_jump(try_end_3);
					continue;
				}

			try_end_3:

			if (EG(exception)) {
				ZEPHIR_INIT_NVAR(&_59$$32);
				ZVAL_OBJ(&_59$$32, EG(exception));
				Z_ADDREF_P(&_59$$32);
				if (zephir_is_instance_of(&_59$$32, SL("Exception"))) {
					zend_clear_exception();
					ZEPHIR_CPY_WRT(&e, &_59$$32);
					ZEPHIR_CALL_METHOD(&_60$$35, this_ptr, "handleException", &_61, 0, &e);
					zephir_check_call_status();
					_62$$35 = ZEPHIR_IS_FALSE_IDENTICAL(&_60$$35);
					if (!(_62$$35)) {
						zephir_read_property_cached(&_63$$35, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_62$$35 = ZEPHIR_IS_FALSE_IDENTICAL(&_63$$35);
					}
					if (_62$$35) {
						ZEPHIR_CALL_METHOD(NULL, &container, "remove", &_64, 0, &handlerClass);
						zephir_check_call_status();
						continue;
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 451);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		if ((zephir_method_exists_ex(&handler, ZEND_STRL("beforeexecuteroute")) == SUCCESS)) {

			/* try_start_4: */

				ZEPHIR_CALL_METHOD(&_65$$39, &handler, "beforeExecuteRoute", NULL, 0, this_ptr);
				zephir_check_call_status_or_jump(try_end_4);
				_66$$39 = ZEPHIR_IS_FALSE_IDENTICAL(&_65$$39);
				if (!(_66$$39)) {
					zephir_read_property_cached(&_67$$39, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
					_66$$39 = ZEPHIR_IS_FALSE_IDENTICAL(&_67$$39);
				}
				if (_66$$39) {
					ZEPHIR_CALL_METHOD(NULL, &container, "remove", &_68, 0, &handlerClass);
					zephir_check_call_status_or_jump(try_end_4);
					continue;
				}

			try_end_4:

			if (EG(exception)) {
				ZEPHIR_INIT_NVAR(&_69$$38);
				ZVAL_OBJ(&_69$$38, EG(exception));
				Z_ADDREF_P(&_69$$38);
				if (zephir_is_instance_of(&_69$$38, SL("Exception"))) {
					zend_clear_exception();
					ZEPHIR_CPY_WRT(&e, &_69$$38);
					ZEPHIR_CALL_METHOD(&_70$$41, this_ptr, "handleException", &_71, 0, &e);
					zephir_check_call_status();
					_72$$41 = ZEPHIR_IS_FALSE_IDENTICAL(&_70$$41);
					if (!(_72$$41)) {
						zephir_read_property_cached(&_73$$41, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_72$$41 = ZEPHIR_IS_FALSE_IDENTICAL(&_73$$41);
					}
					if (_72$$41) {
						ZEPHIR_CALL_METHOD(NULL, &container, "remove", &_74, 0, &handlerClass);
						zephir_check_call_status();
						continue;
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 470);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		if (isNewHandler) {
			if ((zephir_method_exists_ex(&handler, ZEND_STRL("initialize")) == SUCCESS)) {

				/* try_start_5: */

					if (1) {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 136, &__$true);
					} else {
						zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 136, &__$false);
					}
					ZEPHIR_CALL_METHOD(NULL, &handler, "initialize", NULL, 0);
					zephir_check_call_status_or_jump(try_end_5);

				try_end_5:

				if (EG(exception)) {
					ZEPHIR_INIT_NVAR(&_75$$45);
					ZVAL_OBJ(&_75$$45, EG(exception));
					Z_ADDREF_P(&_75$$45);
					if (zephir_is_instance_of(&_75$$45, SL("Exception"))) {
						zend_clear_exception();
						ZEPHIR_CPY_WRT(&e, &_75$$45);
						if (0) {
							zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 136, &__$true);
						} else {
							zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 136, &__$false);
						}
						ZEPHIR_CALL_METHOD(&_76$$47, this_ptr, "handleException", &_77, 0, &e);
						zephir_check_call_status();
						_78$$47 = ZEPHIR_IS_FALSE_IDENTICAL(&_76$$47);
						if (!(_78$$47)) {
							zephir_read_property_cached(&_79$$47, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
							_78$$47 = ZEPHIR_IS_FALSE_IDENTICAL(&_79$$47);
						}
						if (_78$$47) {
							continue;
						}
						zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 512);
						ZEPHIR_MM_RESTORE();
						return;
					} else {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			}
			if (0) {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 136, &__$true);
			} else {
				zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 136, &__$false);
			}
			if (zephir_is_true(&eventsManager)) {

				/* try_start_6: */

					ZEPHIR_INIT_NVAR(&_81$$51);
					ZVAL_STRING(&_81$$51, "dispatch:afterInitialize");
					ZEPHIR_CALL_METHOD(&_80$$51, &eventsManager, "fire", &_82, 0, &_81$$51, this_ptr);
					zephir_check_call_status_or_jump(try_end_6);
					_83$$51 = ZEPHIR_IS_FALSE_IDENTICAL(&_80$$51);
					if (!(_83$$51)) {
						zephir_read_property_cached(&_84$$51, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_83$$51 = ZEPHIR_IS_FALSE_IDENTICAL(&_84$$51);
					}
					if (_83$$51) {
						continue;
					}

				try_end_6:

				if (EG(exception)) {
					ZEPHIR_INIT_NVAR(&_85$$50);
					ZVAL_OBJ(&_85$$50, EG(exception));
					Z_ADDREF_P(&_85$$50);
					if (zephir_is_instance_of(&_85$$50, SL("Exception"))) {
						zend_clear_exception();
						ZEPHIR_CPY_WRT(&e, &_85$$50);
						ZEPHIR_CALL_METHOD(&_86$$53, this_ptr, "handleException", &_87, 0, &e);
						zephir_check_call_status();
						_88$$53 = ZEPHIR_IS_FALSE_IDENTICAL(&_86$$53);
						if (!(_88$$53)) {
							zephir_read_property_cached(&_89$$53, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
							_88$$53 = ZEPHIR_IS_FALSE_IDENTICAL(&_89$$53);
						}
						if (_88$$53) {
							continue;
						}
						zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 531);
						ZEPHIR_MM_RESTORE();
						return;
					} else {
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
			}
		}
		zephir_read_property_cached(&_37$$11, this_ptr, _zephir_prop_10, 137, PH_NOISY_CC | PH_READONLY);
		if (zephir_is_true(&_37$$11)) {
			zephir_read_property_cached(&_90$$56, this_ptr, _zephir_prop_11, 138, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&modelBinder, &_90$$56);
			ZEPHIR_INIT_NVAR(&bindCacheKey);
			ZEPHIR_CONCAT_SVSV(&bindCacheKey, "_PHMB_", &handlerClass, "_", &actionMethod);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_90$$56, this_ptr, _zephir_prop_8, 135, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_91$$56, &modelBinder, "bindToHandler", NULL, 0, &handler, &_90$$56, &bindCacheKey, &actionMethod);
			zephir_check_call_status();
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 135, &_91$$56);
		}
		if (hasEventsManager) {
			ZEPHIR_INIT_NVAR(&_93$$57);
			ZVAL_STRING(&_93$$57, "dispatch:afterBinding");
			ZEPHIR_CALL_METHOD(&_92$$57, &eventsManager, "fire", &_94, 0, &_93$$57, this_ptr);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_92$$57)) {
				continue;
			}
			zephir_read_property_cached(&_95$$57, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_95$$57)) {
				continue;
			}
		}
		if ((zephir_method_exists_ex(&handler, ZEND_STRL("afterbinding")) == SUCCESS)) {
			ZEPHIR_CALL_METHOD(&_96$$60, &handler, "afterBinding", NULL, 0, this_ptr);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_96$$60)) {
				continue;
			}
			zephir_read_property_cached(&_97$$60, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_97$$60)) {
				continue;
			}
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_12, 139, &handler);

		/* try_start_7: */

			zephir_read_property_cached(&_99$$63, this_ptr, _zephir_prop_8, 135, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_98$$63, this_ptr, "callActionMethod", &_100, 0, &handler, &actionMethod, &_99$$63);
			zephir_check_call_status_or_jump(try_end_7);
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_13, 140, &_98$$63);
			zephir_read_property_cached(&_101$$63, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_101$$63)) {
				continue;
			}

		try_end_7:

		if (EG(exception)) {
			ZEPHIR_INIT_NVAR(&_102$$11);
			ZVAL_OBJ(&_102$$11, EG(exception));
			Z_ADDREF_P(&_102$$11);
			if (zephir_is_instance_of(&_102$$11, SL("Exception"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&e, &_102$$11);
				ZEPHIR_CALL_METHOD(&_103$$65, this_ptr, "handleException", &_104, 0, &e);
				zephir_check_call_status();
				_105$$65 = ZEPHIR_IS_FALSE_IDENTICAL(&_103$$65);
				if (!(_105$$65)) {
					zephir_read_property_cached(&_106$$65, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
					_105$$65 = ZEPHIR_IS_FALSE_IDENTICAL(&_106$$65);
				}
				if (_105$$65) {
					continue;
				}
				zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 603);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		if (hasEventsManager) {

			/* try_start_8: */

				ZEPHIR_INIT_NVAR(&_108$$69);
				ZVAL_STRING(&_108$$69, "dispatch:afterExecuteRoute");
				ZEPHIR_CALL_METHOD(&_107$$69, &eventsManager, "fire", &_109, 0, &_108$$69, this_ptr, &value);
				zephir_check_call_status_or_jump(try_end_8);
				_110$$69 = ZEPHIR_IS_FALSE_IDENTICAL(&_107$$69);
				if (!(_110$$69)) {
					zephir_read_property_cached(&_111$$69, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
					_110$$69 = ZEPHIR_IS_FALSE_IDENTICAL(&_111$$69);
				}
				if (_110$$69) {
					continue;
				}

			try_end_8:

			if (EG(exception)) {
				ZEPHIR_INIT_NVAR(&_112$$68);
				ZVAL_OBJ(&_112$$68, EG(exception));
				Z_ADDREF_P(&_112$$68);
				if (zephir_is_instance_of(&_112$$68, SL("Exception"))) {
					zend_clear_exception();
					ZEPHIR_CPY_WRT(&e, &_112$$68);
					ZEPHIR_CALL_METHOD(&_113$$71, this_ptr, "handleException", &_114, 0, &e);
					zephir_check_call_status();
					_115$$71 = ZEPHIR_IS_FALSE_IDENTICAL(&_113$$71);
					if (!(_115$$71)) {
						zephir_read_property_cached(&_116$$71, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_115$$71 = ZEPHIR_IS_FALSE_IDENTICAL(&_116$$71);
					}
					if (_115$$71) {
						continue;
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 619);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		if ((zephir_method_exists_ex(&handler, ZEND_STRL("afterexecuteroute")) == SUCCESS)) {

			/* try_start_9: */

				ZEPHIR_CALL_METHOD(&_117$$75, &handler, "afterExecuteRoute", NULL, 0, this_ptr, &value);
				zephir_check_call_status_or_jump(try_end_9);
				_118$$75 = ZEPHIR_IS_FALSE_IDENTICAL(&_117$$75);
				if (!(_118$$75)) {
					zephir_read_property_cached(&_119$$75, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
					_118$$75 = ZEPHIR_IS_FALSE_IDENTICAL(&_119$$75);
				}
				if (_118$$75) {
					continue;
				}

			try_end_9:

			if (EG(exception)) {
				ZEPHIR_INIT_NVAR(&_120$$74);
				ZVAL_OBJ(&_120$$74, EG(exception));
				Z_ADDREF_P(&_120$$74);
				if (zephir_is_instance_of(&_120$$74, SL("Exception"))) {
					zend_clear_exception();
					ZEPHIR_CPY_WRT(&e, &_120$$74);
					ZEPHIR_CALL_METHOD(&_121$$77, this_ptr, "handleException", &_122, 0, &e);
					zephir_check_call_status();
					_123$$77 = ZEPHIR_IS_FALSE_IDENTICAL(&_121$$77);
					if (!(_123$$77)) {
						zephir_read_property_cached(&_124$$77, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_123$$77 = ZEPHIR_IS_FALSE_IDENTICAL(&_124$$77);
					}
					if (_123$$77) {
						continue;
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 636);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		if (hasEventsManager) {

			/* try_start_10: */

				ZEPHIR_INIT_NVAR(&_125$$81);
				ZVAL_STRING(&_125$$81, "dispatch:afterDispatch");
				ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_126, 0, &_125$$81, this_ptr, &value);
				zephir_check_call_status_or_jump(try_end_10);

			try_end_10:

			if (EG(exception)) {
				ZEPHIR_INIT_NVAR(&_127$$80);
				ZVAL_OBJ(&_127$$80, EG(exception));
				Z_ADDREF_P(&_127$$80);
				if (zephir_is_instance_of(&_127$$80, SL("Exception"))) {
					zend_clear_exception();
					ZEPHIR_CPY_WRT(&e, &_127$$80);
					ZEPHIR_CALL_METHOD(&_128$$82, this_ptr, "handleException", &_129, 0, &e);
					zephir_check_call_status();
					_130$$82 = ZEPHIR_IS_FALSE_IDENTICAL(&_128$$82);
					if (!(_130$$82)) {
						zephir_read_property_cached(&_131$$82, this_ptr, _zephir_prop_2, 129, PH_NOISY_CC | PH_READONLY);
						_130$$82 = ZEPHIR_IS_FALSE_IDENTICAL(&_131$$82);
					}
					if (_130$$82) {
						continue;
					}
					zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 653);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
	}
	if (hasEventsManager) {

		/* try_start_11: */

			ZEPHIR_INIT_VAR(&_132$$86);
			ZVAL_STRING(&_132$$86, "dispatch:afterDispatchLoop");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_132$$86, this_ptr);
			zephir_check_call_status_or_jump(try_end_11);

		try_end_11:

		if (EG(exception)) {
			ZEPHIR_INIT_VAR(&_133$$85);
			ZVAL_OBJ(&_133$$85, EG(exception));
			Z_ADDREF_P(&_133$$85);
			if (zephir_is_instance_of(&_133$$85, SL("Exception"))) {
				zend_clear_exception();
				ZEPHIR_CPY_WRT(&e, &_133$$85);
				ZEPHIR_CALL_METHOD(&_134$$87, this_ptr, "handleException", NULL, 0, &e);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_134$$87)) {
					RETURN_MM_BOOL(0);
				}
				zephir_throw_exception_debug(&e, "phalcon/Dispatcher/AbstractDispatcher.zep", 670);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CCTOR(&handler);
}

/**
 * Forwards the execution flow to another controller/action.
 *
 * ```php
 * $this->dispatcher->forward(
 *     [
 *         "controller" => "posts",
 *         "action"     => "index",
 *     ]
 * );
 * ```
 *
 * @throws PhalconException
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, forward)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *forward_param = NULL, __$true, __$false, namespaceName, controllerName, params, actionName, taskName, _0, _1, _2, _3;
	zval forward;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&forward);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&namespaceName);
	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&taskName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
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
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("isControllerInitialize", 22, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("namespaceName", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("previousNamespaceName", 21, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("handlerName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("previousHandlerName", 19, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("actionName", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("previousActionName", 18, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("params", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("finished", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("forwarded", 9, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(forward, forward_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &forward_param);
	zephir_get_arrval(&forward, forward_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 136, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(ZEPHIR_IS_TRUE_IDENTICAL(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_dispatcher_exception_ce, "Forwarding inside a controller's initialize() method is forbidden", "phalcon/Dispatcher/AbstractDispatcher.zep", 704);
		return;
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 132, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 141, &_1);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_3, 133, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 142, &_2);
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_5, 134, PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_6, 143, &_3);
	zephir_memory_observe(&namespaceName);
	if (zephir_array_isset_string_fetch(&namespaceName, &forward, SL("namespace"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 132, &namespaceName);
	}
	zephir_memory_observe(&controllerName);
	if (zephir_array_isset_string_fetch(&controllerName, &forward, SL("controller"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 133, &controllerName);
	} else {
		zephir_memory_observe(&taskName);
		if (zephir_array_isset_string_fetch(&taskName, &forward, SL("task"), 0)) {
			zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 133, &taskName);
		}
	}
	zephir_memory_observe(&actionName);
	if (zephir_array_isset_string_fetch(&actionName, &forward, SL("action"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_5, 134, &actionName);
	}
	zephir_memory_observe(&params);
	if (zephir_array_isset_string_fetch(&params, &forward, SL("params"), 0)) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 135, &params);
	}
	if (0) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 129, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_8, 129, &__$false);
	}
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 144, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_9, 144, &__$false);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Gets the latest dispatched action name
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getActionName)
{

	RETURN_MEMBER_TYPED(getThis(), "actionName", IS_STRING);
}

/**
 * Gets the default action suffix
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getActionSuffix)
{

	RETURN_MEMBER_TYPED(getThis(), "actionSuffix", IS_STRING);
}

/**
 * Returns the current method to be/executed in the dispatcher
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getActiveMethod)
{
	zval activeMethodName, _0, _1, _5, _2$$3, _3$$3, _4$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&activeMethodName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("activeMethodMap", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("actionName", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("actionSuffix", 12, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&activeMethodName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 145, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 134, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&activeMethodName, &_0, &_1, 0))) {
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_1, 134, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "toCamelCase", NULL, 0, &_3$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&activeMethodName, "lcfirst", NULL, 83, &_2$$3);
		zephir_check_call_status();
		zephir_memory_observe(&_4$$3);
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_1, 134, PH_NOISY_CC);
		zephir_update_property_array(this_ptr, SL("activeMethodMap"), &_4$$3, &activeMethodName);
	}
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_2, 146, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CONCAT_VV(return_value, &activeMethodName, &_5);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM();
}

/**
 * Returns bound models from binder instance
 *
 * ```php
 * class UserController extends Controller
 * {
 *     public function showAction(User $user)
 *     {
 *         // return array with $user
 *         $boundModels = $this->dispatcher->getBoundModels();
 *     }
 * }
 * ```
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getBoundModels)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("modelBinder", 11, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 138, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 138, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_1, "getBoundModels", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Returns the default namespace
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getDefaultNamespace)
{

	RETURN_MEMBER_TYPED(getThis(), "defaultNamespace", IS_STRING);
}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getEventsManager)
{

	RETURN_MEMBER(getThis(), "eventsManager");
}

/**
 * Gets the default handler suffix
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getHandlerSuffix)
{

	RETURN_MEMBER_TYPED(getThis(), "handlerSuffix", IS_STRING);
}

/**
 * Gets model binder
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getModelBinder)
{

	RETURN_MEMBER(getThis(), "modelBinder");
}

/**
 * Gets the module where the controller class is
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getModuleName)
{

	RETURN_MEMBER(getThis(), "moduleName");
}

/**
 * Gets a namespace to be prepended to the current handler name
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getNamespaceName)
{

	RETURN_MEMBER_TYPED(getThis(), "namespaceName", IS_STRING);
}

/**
 * Gets a param by its name or numeric index
 *
 * @param  mixed param
 * @param  string|array filters
 * @param  mixed defaultValue
 * @return mixed
 *
 * @todo remove this in future versions
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getParam)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *param, param_sub, *filters = NULL, filters_sub, *defaultValue = NULL, defaultValue_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZVAL_UNDEF(&filters_sub);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(filters)
		Z_PARAM_ZVAL_OR_NULL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &param, &filters, &defaultValue);
	if (!filters) {
		filters = &filters_sub;
		filters = &__$null;
	}
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getParameter", NULL, 0, param, filters, defaultValue);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets a param by its name or numeric index
 *
 * @param  mixed param
 * @param  string|array filters
 * @param  mixed defaultValue
 * @return mixed
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getParameter)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *param, param_sub, *filters = NULL, filters_sub, *defaultValue = NULL, defaultValue_sub, __$null, params, filter, paramValue, _0, _3, _4, _5, _1$$5, _2$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZVAL_UNDEF(&filters_sub);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&paramValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("params", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("container", 9, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL(param)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(filters)
		Z_PARAM_ZVAL_OR_NULL(defaultValue)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 2, &param, &filters, &defaultValue);
	if (!filters) {
		filters = &filters_sub;
		filters = &__$null;
	}
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 135, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&params, &_0);
	zephir_memory_observe(&paramValue);
	if (!(zephir_array_isset_fetch(&paramValue, &params, param, 0))) {
		RETVAL_ZVAL(defaultValue, 1, 0);
		RETURN_MM();
	}
	if (Z_TYPE_P(filters) == IS_NULL) {
		RETURN_CCTOR(&paramValue);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 128, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$5);
		ZVAL_STRING(&_1$$5, "A dependency injection container is required to access the 'filter' service");
		ZVAL_LONG(&_2$$5, 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwDispatchException", NULL, 0, &_1$$5, &_2$$5);
		zephir_check_call_status();
	}
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 128, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "filter");
	ZEPHIR_CALL_METHOD(&_4, &_3, "getShared", NULL, 0, &_5);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&filter, &_4);
	ZEPHIR_RETURN_CALL_METHOD(&filter, "sanitize", NULL, 0, &paramValue, filters);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets action params
 *
 * @todo remove this in future versions
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getParams)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getParameters", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Gets action params
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getParameters)
{

	RETURN_MEMBER_TYPED(getThis(), "params", IS_ARRAY);
}

/**
 * Check if a param exists
 * @todo deprecate this in the future
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, hasParam)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *param, param_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &param);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "hasParameter", NULL, 0, param);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Check if a param exists
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, hasParameter)
{
	zval *param, param_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("params", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(param)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 135, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_value(&_0, param));
}

/**
 * Checks if the dispatch loop is finished or has more pendent
 * controllers/tasks to dispatch
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, isFinished)
{

	RETURN_MEMBER(getThis(), "finished");
}

/**
 * Sets the action name to be dispatched
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setActionName)
{
	zval actionName_zv;
	zend_string *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&actionName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("actionName", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(actionName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&actionName_zv, actionName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 134, &actionName_zv);
}

/**
 * Sets the default action name
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setDefaultAction)
{
	zval actionName_zv;
	zend_string *actionName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&actionName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultAction", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(actionName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&actionName_zv, actionName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 147, &actionName_zv);
}

/**
 * Sets the default namespace
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setDefaultNamespace)
{
	zval defaultNamespace_zv;
	zend_string *defaultNamespace = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&defaultNamespace_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("defaultNamespace", 16, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(defaultNamespace)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&defaultNamespace_zv, defaultNamespace);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 148, &defaultNamespace_zv);
}

/**
 * Possible class name that will be located to dispatch the request
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getHandlerClass)
{
	zval handlerSuffix, handlerName, namespaceName, camelizedClass, handlerClass, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handlerSuffix);
	ZVAL_UNDEF(&handlerName);
	ZVAL_UNDEF(&namespaceName);
	ZVAL_UNDEF(&camelizedClass);
	ZVAL_UNDEF(&handlerClass);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("handlerSuffix", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("handlerName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("namespaceName", 13, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "resolveEmptyProperties", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 149, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&handlerSuffix, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 133, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&handlerName, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 132, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&namespaceName, &_0);
	if (!(zephir_memnstr_str(&handlerName, SL("\\"), "phalcon/Dispatcher/AbstractDispatcher.zep", 981))) {
		ZEPHIR_CALL_METHOD(&camelizedClass, this_ptr, "toCamelCase", NULL, 0, &handlerName);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&camelizedClass, &handlerName);
	}
	ZEPHIR_INIT_VAR(&handlerClass);
	if (zephir_is_true(&namespaceName)) {
		if (!(zephir_end_with_str(&namespaceName, SL("\\")))) {
			zephir_concat_self_str(&namespaceName, SL("\\"));
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CONCAT_VVV(&handlerClass, &namespaceName, &camelizedClass, &handlerSuffix);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CONCAT_VV(&handlerClass, &camelizedClass, &handlerSuffix);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CCTOR(&handlerClass);
}

/**
 * Set a param by its name or numeric index
 * @todo deprecate this in the future
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setParam)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *param, param_sub, *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(param)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &param, &value);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setParameter", NULL, 0, param, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Set a param by its name or numeric index
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setParameter)
{
	zval *param, param_sub, *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&param_sub);
	ZVAL_UNDEF(&value_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(param)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &param, &value);
	zephir_update_property_array(this_ptr, SL("params"), param, value);
}

/**
 * Sets action params to be dispatched
 * @todo deprecate this in the future
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setParams)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *params_param = NULL;
	zval params;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &params_param);
	zephir_get_arrval(&params, params_param);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setParameters", NULL, 0, &params);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets action params to be dispatched
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setParameters)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *params_param = NULL;
	zval params;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("params", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(params, params_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &params_param);
	zephir_get_arrval(&params, params_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 135, &params);
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the latest returned value by an action manually
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setReturnedValue)
{
	zval *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("returnedValue", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &value);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 140, value);
}

/**
 * Sets the default action suffix
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setActionSuffix)
{
	zval actionSuffix_zv;
	zend_string *actionSuffix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&actionSuffix_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("actionSuffix", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(actionSuffix)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&actionSuffix_zv, actionSuffix);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 146, &actionSuffix_zv);
}

/**
 * Sets the events manager
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setEventsManager)
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
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 127, eventsManager);
}

/**
 * Sets the default suffix for the handler
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setHandlerSuffix)
{
	zval handlerSuffix_zv;
	zend_string *handlerSuffix = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handlerSuffix_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("handlerSuffix", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(handlerSuffix)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&handlerSuffix_zv, handlerSuffix);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 149, &handlerSuffix_zv);
}

/**
 * Enable model binding during dispatch
 *
 * ```php
 * $di->set(
 *     'dispatcher',
 *     function() {
 *         $dispatcher = new Dispatcher();
 *
 *         $dispatcher->setModelBinder(
 *             new Binder(),
 *             'cache'
 *         );
 *
 *         return $dispatcher;
 *     }
 * );
 * ```
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setModelBinder)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *modelBinder, modelBinder_sub, *cache = NULL, cache_sub, __$true, __$false, __$null, container, _0$$3, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&modelBinder_sub);
	ZVAL_UNDEF(&cache_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("container", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("modelBinding", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("modelBinder", 11, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_OBJECT_OF_CLASS(modelBinder, phalcon_mvc_model_binderinterface_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(cache)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &modelBinder, &cache);
	if (!cache) {
		cache = &cache_sub;
		ZEPHIR_CPY_WRT(cache, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(cache);
	}
	if (Z_TYPE_P(cache) == IS_STRING) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 128, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&container, &_0$$3);
		ZEPHIR_CALL_METHOD(&_1$$3, &container, "get", NULL, 0, cache);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(cache, &_1$$3);
	}
	if (Z_TYPE_P(cache) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, modelBinder, "setCache", NULL, 0, cache);
		zephir_check_call_status();
	}
	if (1) {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 137, &__$true);
	} else {
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 137, &__$false);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 138, modelBinder);
	RETURN_THIS();
}

/**
 * Sets the module where the controller is (only informative)
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setModuleName)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval moduleName_zv;
	zend_string *moduleName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&moduleName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("moduleName", 10, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(moduleName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!moduleName) {
		ZEPHIR_INIT_VAR(&moduleName_zv);
	} else {
		zephir_memory_observe(&moduleName_zv);
	ZVAL_STR_COPY(&moduleName_zv, moduleName);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 150, &moduleName_zv);
	ZEPHIR_MM_RESTORE();
}

/**
 * Sets the namespace where the controller class is
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, setNamespaceName)
{
	zval namespaceName_zv;
	zend_string *namespaceName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&namespaceName_zv);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("namespaceName", 13, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(namespaceName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&namespaceName_zv, namespaceName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 132, &namespaceName_zv);
}

/**
 * Returns value returned by the latest dispatched action
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, getReturnedValue)
{

	RETURN_MEMBER(getThis(), "returnedValue");
}

/**
 * Check if the current executed action was forwarded by another one
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, wasForwarded)
{

	RETURN_MEMBER(getThis(), "forwarded");
}

/**
 * Set empty properties to their defaults (where defaults are available)
 */
PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, resolveEmptyProperties)
{
	zval _0, _2, _4, _1$$3, _3$$4, _5$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("namespaceName", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("defaultNamespace", 16, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("handlerName", 11, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("defaultHandler", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("actionName", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("defaultAction", 13, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 132, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_1, 148, PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 132, &_1$$3);
	}
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_2, 133, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_2))) {
		zephir_read_property_cached(&_3$$4, this_ptr, _zephir_prop_3, 151, PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 133, &_3$$4);
	}
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_4, 134, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_4))) {
		zephir_read_property_cached(&_5$$5, this_ptr, _zephir_prop_5, 147, PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 134, &_5$$5);
	}
}

PHP_METHOD(Phalcon_Dispatcher_AbstractDispatcher, toCamelCase)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval input_zv, camelCaseInput, _0, _1$$3, _2$$3, _3$$3;
	zend_string *input = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_zv);
	ZVAL_UNDEF(&camelCaseInput);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("camelCaseMap", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&input_zv);
	ZVAL_STR_COPY(&input_zv, input);
	zephir_memory_observe(&camelCaseInput);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 152, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&camelCaseInput, &_0, &input_zv, 0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/[_-]+/");
		ZEPHIR_CALL_FUNCTION(&_2$$3, "preg_split", NULL, 76, &_1$$3, &input_zv);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "ucfirst");
		ZEPHIR_CALL_FUNCTION(&_3$$3, "array_map", NULL, 89, &_1$$3, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&camelCaseInput);
		zephir_fast_join_str(&camelCaseInput, SL(""), &_3$$3);
		zephir_update_property_array(this_ptr, SL("camelCaseMap"), &input_zv, &camelCaseInput);
	}
	RETURN_CCTOR(&camelCaseInput);
}

zend_object *zephir_init_properties_Phalcon_Dispatcher_AbstractDispatcher(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _1$$3, _3$$4, _5$$5, _7$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("params"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("params"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("handlerHashes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("handlerHashes"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("camelCaseMap"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("camelCaseMap"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("activeMethodMap"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("activeMethodMap"), &_7$$6);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

