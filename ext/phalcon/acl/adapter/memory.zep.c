
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
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/main.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Manages ACL lists in memory
 *
 *```php
 * $acl = new \Phalcon\Acl\Adapter\Memory();
 *
 * $acl->setDefaultAction(
 *     \Phalcon\Acl\Enum::DENY
 * );
 *
 * // Register roles
 * $roles = [
 *     "users"  => new \Phalcon\Acl\Role("Users"),
 *     "guests" => new \Phalcon\Acl\Role("Guests"),
 * ];
 * foreach ($roles as $role) {
 *     $acl->addRole($role);
 * }
 *
 * // Private area components
 * $privateComponents = [
 *     "companies" => ["index", "search", "new", "edit", "save", "create", "delete"],
 *     "products"  => ["index", "search", "new", "edit", "save", "create", "delete"],
 *     "invoices"  => ["index", "profile"],
 * ];
 *
 * foreach ($privateComponents as $componentName => $actions) {
 *     $acl->addComponent(
 *         new \Phalcon\Acl\Component($componentName),
 *         $actions
 *     );
 * }
 *
 * // Public area components
 * $publicComponents = [
 *     "index"   => ["index"],
 *     "about"   => ["index"],
 *     "session" => ["index", "register", "start", "end"],
 *     "contact" => ["index", "send"],
 * ];
 *
 * foreach ($publicComponents as $componentName => $actions) {
 *     $acl->addComponent(
 *         new \Phalcon\Acl\Component($componentName),
 *         $actions
 *     );
 * }
 *
 * // Grant access to public areas to both users and guests
 * foreach ($roles as $role) {
 *     foreach ($publicComponents as $component => $actions) {
 *         $acl->allow($role->getName(), $component, "*");
 *     }
 * }
 *
 * // Grant access to private area to role Users
 * foreach ($privateComponents as $component => $actions) {
 *     foreach ($actions as $action) {
 *         $acl->allow("Users", $component, $action);
 *     }
 * }
 *```
 */
ZEPHIR_INIT_CLASS(Phalcon_Acl_Adapter_Memory)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Acl\\Adapter, Memory, phalcon, acl_adapter_memory, phalcon_acl_adapter_abstractadapter_ce, phalcon_acl_adapter_memory_method_entry, 0);

	/**
	 * Access
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("access"), ZEND_ACC_PROTECTED);
	/**
	 * Access List
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("accessList"), ZEND_ACC_PROTECTED);
	/**
	 * Returns the latest function used to acquire access
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("activeFunction"), ZEND_ACC_PROTECTED);
	/**
	 * Returns number of additional arguments(excluding role and resource) for active function
	 *
	 * @var int
	 */
	zend_declare_property_long(phalcon_acl_adapter_memory_ce, SL("activeFunctionCustomArgumentsCount"), 0, ZEND_ACC_PROTECTED);
	/**
	 * Returns the latest key used to acquire access
	 *
	 * @var string|null
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("activeKey"), ZEND_ACC_PROTECTED);
	/**
	 * Components
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("components"), ZEND_ACC_PROTECTED);
	/**
	 * Component Names
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("componentsNames"), ZEND_ACC_PROTECTED);
	/**
	 * Function List
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("func"), ZEND_ACC_PROTECTED);
	/**
	 * Default action for no arguments is `allow`
	 *
	 * @var mixed
	 */
	zend_declare_property_long(phalcon_acl_adapter_memory_ce, SL("noArgumentsDefaultAction"), 0, ZEND_ACC_PROTECTED);
	/**
	 * Roles
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("roles"), ZEND_ACC_PROTECTED);
	/**
	 * Role Inherits
	 *
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_acl_adapter_memory_ce, SL("roleInherits"), ZEND_ACC_PROTECTED);
	return SUCCESS;
}

/**
 * Phalcon\Acl\Adapter\Memory constructor
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, __construct)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval __$true;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("componentsNames", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("accessList", 10, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 1, 0);
	zephir_array_update_string(&_0, SL("*"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 248, &_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 1, 0);
	zephir_array_update_string(&_1, SL("*!*"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 249, &_1);
	ZEPHIR_MM_RESTORE();
}

/**
 * Adds a component to the ACL list
 *
 * Access names can be a particular action, by example
 * search, update, delete, etc. or a list of them
 *
 * Example:
 * ```php
 * // Add a component to the list allowing access to an action
 * $acl->addComponent(
 *     new Phalcon\Acl\Component("customers"),
 *     "search"
 * );
 *
 * $acl->addComponent("customers", "search");
 *
 * // Add a component  with an access list
 * $acl->addComponent(
 *     new Phalcon\Acl\Component("customers"),
 *     [
 *         "create",
 *         "search",
 *     ]
 * );
 *
 * $acl->addComponent(
 *     "customers",
 *     [
 *         "create",
 *         "search",
 *     ]
 * );
 * ```
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, addComponent)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *componentValue, componentValue_sub, *accessList, accessList_sub, __$true, componentName, componentObject, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&componentValue_sub);
	ZVAL_UNDEF(&accessList_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&componentName);
	ZVAL_UNDEF(&componentObject);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("componentsNames", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(componentValue)
		Z_PARAM_ZVAL(accessList)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &componentValue, &accessList);
	_0 = Z_TYPE_P(componentValue) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(componentValue, phalcon_acl_componentinterface_ce);
	}
	if (_0) {
		ZEPHIR_CPY_WRT(&componentObject, componentValue);
	} else {
		ZEPHIR_INIT_NVAR(&componentObject);
		object_init_ex(&componentObject, phalcon_acl_component_ce);
		ZEPHIR_CALL_METHOD(NULL, &componentObject, "__construct", NULL, 146, componentValue);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&componentName, &componentObject, "getName", NULL, 147);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 248, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_value(&_1, &componentName))) {
		zephir_update_property_array(this_ptr, SL("components"), &componentName, &componentObject);
		zephir_update_property_array(this_ptr, SL("componentsNames"), &componentName, &__$true);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addComponentAccess", NULL, 0, &componentName, accessList);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds access to components
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, addComponentAccess)
{
	zend_bool exists = 0, _2, _10$$4;
	zval accessKey;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval componentName_zv, *accessList, accessList_sub, accessName, _0, _1, *_3$$4, _4$$4, *_5$$4, _9$$4, _6$$5, _7$$5, _8$$6, _11$$7, _12$$7, _13$$8, _14$$9, _15$$9, _16$$10;
	zend_string *componentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&accessList_sub);
	ZVAL_UNDEF(&accessName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&accessKey);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("componentsNames", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("accessList", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(componentName)
		Z_PARAM_ZVAL(accessList)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	accessList = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&componentName_zv);
	ZVAL_STR_COPY(&componentName_zv, componentName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 248, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Component");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkExists", NULL, 148, &_0, &componentName_zv, &_1);
	zephir_check_call_status();
	_2 = Z_TYPE_P(accessList) != IS_ARRAY;
	if (_2) {
		_2 = Z_TYPE_P(accessList) != IS_STRING;
	}
	if (UNEXPECTED(_2)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_acl_exception_ce, "Invalid value for the accessList", "phalcon/Acl/Adapter/Memory.zep", 242);
		return;
	}
	exists = 1;
	if (Z_TYPE_P(accessList) == IS_ARRAY) {
		if (Z_TYPE_P(accessList) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_4$$4);
			zephir_string_to_char_array(&_4$$4, accessList);
			_3$$4 = &_4$$4;
		} else {
			_3$$4 = accessList;
		}
		zephir_is_iterable(_3$$4, 0, "phalcon/Acl/Adapter/Memory.zep", 255);
		if (Z_TYPE_P(_3$$4) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3$$4), _5$$4)
			{
				ZEPHIR_INIT_NVAR(&accessName);
				ZVAL_COPY(&accessName, _5$$4);
				ZEPHIR_INIT_NVAR(&_6$$5);
				ZEPHIR_CONCAT_VSV(&_6$$5, &componentName_zv, "!", &accessName);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_get_strval(&accessKey, &_6$$5);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_read_property_cached(&_7$$5, this_ptr, _zephir_prop_1, 249, PH_NOISY_CC | PH_READONLY);
				if (!(zephir_array_isset_value(&_7$$5, &accessKey))) {
					ZEPHIR_INIT_NVAR(&_8$$6);
					ZVAL_BOOL(&_8$$6, exists);
					zephir_update_property_array(this_ptr, SL("accessList"), &accessKey, &_8$$6);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _3$$4, "rewind", NULL, 0);
			zephir_check_call_status();
			_10$$4 = 1;
			while (1) {
				if (_10$$4) {
					_10$$4 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _3$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_9$$4, _3$$4, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_9$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&accessName, _3$$4, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_11$$7);
					ZEPHIR_CONCAT_VSV(&_11$$7, &componentName_zv, "!", &accessName);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_get_strval(&accessKey, &_11$$7);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_read_property_cached(&_12$$7, this_ptr, _zephir_prop_1, 249, PH_NOISY_CC | PH_READONLY);
					if (!(zephir_array_isset_value(&_12$$7, &accessKey))) {
						ZEPHIR_INIT_NVAR(&_13$$8);
						ZVAL_BOOL(&_13$$8, exists);
						zephir_update_property_array(this_ptr, SL("accessList"), &accessKey, &_13$$8);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&accessName);
	} else {
		ZEPHIR_INIT_VAR(&_14$$9);
		ZEPHIR_CONCAT_VSV(&_14$$9, &componentName_zv, "!", accessList);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_get_strval(&accessKey, &_14$$9);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_read_property_cached(&_15$$9, this_ptr, _zephir_prop_1, 249, PH_NOISY_CC | PH_READONLY);
		if (!(zephir_array_isset_value(&_15$$9, &accessKey))) {
			ZEPHIR_INIT_VAR(&_16$$10);
			ZVAL_BOOL(&_16$$10, exists);
			zephir_update_property_array(this_ptr, SL("accessList"), &accessKey, &_16$$10);
		}
	}
	RETURN_MM_BOOL(1);
}

/**
 * Do a role inherit from another existing role
 *
 * ```php
 * $acl->addRole("administrator", "consultant");
 * $acl->addRole("administrator", ["consultant", "consultant2"]);
 * ```
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, addInherit)
{
	zend_bool _37, _7$$6, _14$$6, _23$$12, _25$$15, _35$$18, _38$$21, _44$$21, _52$$27, _53$$30, _63$$33;
	zval checkRoleToInherits, usedRoleToInherits;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_13 = NULL, *_21 = NULL, *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval roleName_zv, *roleToInherits, roleToInherits_sub, __$true, roleInheritName, roleToInherit, checkRoleToInherit, roleToInheritList, usedRoleToInherit, _0, _1, _2, _3, *_5, *_6, _36, _4$$3, _8$$6, _9$$6, _10$$6, _15$$6, _11$$10, _12$$10, _16$$12, _17$$12, *_18$$12, _19$$12, *_20$$12, _22$$12, _28$$15, _26$$17, _27$$17, _29$$18, _30$$18, *_31$$18, _32$$18, *_33$$18, _34$$18, _39$$21, _40$$21, _41$$21, _45$$21, _42$$25, _43$$25, _46$$27, _47$$27, *_48$$27, _49$$27, *_50$$27, _51$$27, _56$$30, _54$$32, _55$$32, _57$$33, _58$$33, *_59$$33, _60$$33, *_61$$33, _62$$33;
	zend_string *roleName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&roleToInherits_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&roleInheritName);
	ZVAL_UNDEF(&roleToInherit);
	ZVAL_UNDEF(&checkRoleToInherit);
	ZVAL_UNDEF(&roleToInheritList);
	ZVAL_UNDEF(&usedRoleToInherit);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_11$$10);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_22$$12);
	ZVAL_UNDEF(&_28$$15);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_32$$18);
	ZVAL_UNDEF(&_34$$18);
	ZVAL_UNDEF(&_39$$21);
	ZVAL_UNDEF(&_40$$21);
	ZVAL_UNDEF(&_41$$21);
	ZVAL_UNDEF(&_45$$21);
	ZVAL_UNDEF(&_42$$25);
	ZVAL_UNDEF(&_43$$25);
	ZVAL_UNDEF(&_46$$27);
	ZVAL_UNDEF(&_47$$27);
	ZVAL_UNDEF(&_49$$27);
	ZVAL_UNDEF(&_51$$27);
	ZVAL_UNDEF(&_56$$30);
	ZVAL_UNDEF(&_54$$32);
	ZVAL_UNDEF(&_55$$32);
	ZVAL_UNDEF(&_57$$33);
	ZVAL_UNDEF(&_58$$33);
	ZVAL_UNDEF(&_60$$33);
	ZVAL_UNDEF(&_62$$33);
	ZVAL_UNDEF(&checkRoleToInherits);
	ZVAL_UNDEF(&usedRoleToInherits);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roles", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("roleInherits", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(roleName)
		Z_PARAM_ZVAL(roleToInherits)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	roleToInherits = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&roleName_zv);
	ZVAL_STR_COPY(&roleName_zv, roleName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Role");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "role list");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkExists", NULL, 148, &_0, &roleName_zv, &_1, &_2);
	zephir_check_call_status();
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_value(&_3, &roleName_zv))) {
		ZEPHIR_INIT_VAR(&_4$$3);
		array_init(&_4$$3);
		zephir_update_property_array(this_ptr, SL("roleInherits"), &roleName_zv, &_4$$3);
	}
	if (Z_TYPE_P(roleToInherits) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&roleToInheritList);
		zephir_create_array(&roleToInheritList, 1, 0);
		zephir_array_fast_append(&roleToInheritList, roleToInherits);
	} else {
		ZEPHIR_CPY_WRT(&roleToInheritList, roleToInherits);
	}
	if (Z_TYPE_P(&roleToInheritList) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_1);
		zephir_string_to_char_array(&_1, &roleToInheritList);
		_5 = &_1;
	} else {
		_5 = &roleToInheritList;
	}
	zephir_is_iterable(_5, 0, "phalcon/Acl/Adapter/Memory.zep", 368);
	if (Z_TYPE_P(_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5), _6)
		{
			ZEPHIR_INIT_NVAR(&roleToInherit);
			ZVAL_COPY(&roleToInherit, _6);
			_7$$6 = Z_TYPE_P(&roleToInherit) == IS_OBJECT;
			if (_7$$6) {
				_7$$6 = zephir_instance_of_ev(&roleToInherit, phalcon_acl_roleinterface_ce);
			}
			if (_7$$6) {
				ZEPHIR_CALL_METHOD(&roleInheritName, &roleToInherit, "getName", NULL, 0);
				zephir_check_call_status();
			} else {
				ZEPHIR_CPY_WRT(&roleInheritName, &roleToInherit);
			}
			zephir_read_property_cached(&_8$$6, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_9$$6);
			zephir_array_fetch(&_9$$6, &_8$$6, &roleName_zv, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 308);
			if (zephir_fast_in_array(&roleInheritName, &_9$$6)) {
				continue;
			}
			zephir_read_property_cached(&_10$$6, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
			if (UNEXPECTED(!(zephir_array_isset_value(&_10$$6, &roleInheritName)))) {
				ZEPHIR_INIT_NVAR(&_11$$10);
				object_init_ex(&_11$$10, phalcon_acl_exception_ce);
				ZEPHIR_INIT_NVAR(&_12$$10);
				ZEPHIR_CONCAT_SVS(&_12$$10, "Role '", &roleInheritName, "' (to inherit) does not exist in the role list");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_11$$10, "__construct", &_13, 32, &_12$$10);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_11$$10, "phalcon/Acl/Adapter/Memory.zep", 319);
				ZEPHIR_MM_RESTORE();
				return;
			}
			_14$$6 = ZEPHIR_IS_EQUAL(&roleName_zv, &roleInheritName);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (_14$$6) {
				RETURN_MM_BOOL(0);
			}
			zephir_read_property_cached(&_15$$6, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
			if (zephir_array_isset_value(&_15$$6, &roleInheritName)) {
				ZEPHIR_INIT_NVAR(&checkRoleToInherits);
				array_init(&checkRoleToInherits);
				zephir_read_property_cached(&_16$$12, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_17$$12);
				zephir_array_fetch(&_17$$12, &_16$$12, &roleInheritName, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 332);
				if (Z_TYPE_P(&_17$$12) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_19$$12);
					zephir_string_to_char_array(&_19$$12, &_17$$12);
					_18$$12 = &_19$$12;
				} else {
					_18$$12 = &_17$$12;
				}
				zephir_is_iterable(_18$$12, 0, "phalcon/Acl/Adapter/Memory.zep", 336);
				if (Z_TYPE_P(_18$$12) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_18$$12), _20$$12)
					{
						ZEPHIR_INIT_NVAR(&usedRoleToInherit);
						ZVAL_COPY(&usedRoleToInherit, _20$$12);
						ZEPHIR_MAKE_REF(&checkRoleToInherits);
						ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
						ZEPHIR_UNREF(&checkRoleToInherits);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _18$$12, "rewind", NULL, 0);
					zephir_check_call_status();
					_23$$12 = 1;
					while (1) {
						if (_23$$12) {
							_23$$12 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _18$$12, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_22$$12, _18$$12, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$12)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&usedRoleToInherit, _18$$12, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_MAKE_REF(&checkRoleToInherits);
							ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
							ZEPHIR_UNREF(&checkRoleToInherits);
							zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&usedRoleToInherit);
				ZEPHIR_INIT_NVAR(&usedRoleToInherits);
				array_init(&usedRoleToInherits);
				while (1) {
					if (!(!(ZEPHIR_IS_EMPTY(&checkRoleToInherits)))) {
						break;
					}
					ZEPHIR_MAKE_REF(&checkRoleToInherits);
					ZEPHIR_CALL_FUNCTION(&checkRoleToInherit, "array_shift", &_24, 21, &checkRoleToInherits);
					ZEPHIR_UNREF(&checkRoleToInherits);
					zephir_check_call_status();
					if (zephir_array_isset_value(&usedRoleToInherits, &checkRoleToInherit)) {
						continue;
					}
					zephir_array_update_zval(&usedRoleToInherits, &checkRoleToInherit, &__$true, PH_COPY | PH_SEPARATE);
					_25$$15 = ZEPHIR_IS_EQUAL(&roleName_zv, &checkRoleToInherit);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (UNEXPECTED(_25$$15)) {
						ZEPHIR_INIT_NVAR(&_26$$17);
						object_init_ex(&_26$$17, phalcon_acl_exception_ce);
						ZEPHIR_INIT_NVAR(&_27$$17);
						ZEPHIR_CONCAT_SVS(&_27$$17, "Role '", &roleInheritName, "' (to inherit) produces an infinite loop");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_26$$17, "__construct", &_13, 32, &_27$$17);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_26$$17, "phalcon/Acl/Adapter/Memory.zep", 351);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_read_property_cached(&_28$$15, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
					if (zephir_array_isset_value(&_28$$15, &checkRoleToInherit)) {
						zephir_read_property_cached(&_29$$18, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_OBS_NVAR(&_30$$18);
						zephir_array_fetch(&_30$$18, &_29$$18, &checkRoleToInherit, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 358);
						if (Z_TYPE_P(&_30$$18) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_32$$18);
							zephir_string_to_char_array(&_32$$18, &_30$$18);
							_31$$18 = &_32$$18;
						} else {
							_31$$18 = &_30$$18;
						}
						zephir_is_iterable(_31$$18, 0, "phalcon/Acl/Adapter/Memory.zep", 361);
						if (Z_TYPE_P(_31$$18) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_31$$18), _33$$18)
							{
								ZEPHIR_INIT_NVAR(&usedRoleToInherit);
								ZVAL_COPY(&usedRoleToInherit, _33$$18);
								ZEPHIR_MAKE_REF(&checkRoleToInherits);
								ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
								ZEPHIR_UNREF(&checkRoleToInherits);
								zephir_check_call_status();
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _31$$18, "rewind", NULL, 0);
							zephir_check_call_status();
							_35$$18 = 1;
							while (1) {
								if (_35$$18) {
									_35$$18 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _31$$18, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_34$$18, _31$$18, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_34$$18)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&usedRoleToInherit, _31$$18, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_MAKE_REF(&checkRoleToInherits);
									ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
									ZEPHIR_UNREF(&checkRoleToInherits);
									zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&usedRoleToInherit);
					}
				}
			}
			zephir_update_property_array_multi(this_ptr, SL("roleInherits"), &roleInheritName, SL("za"), 2, &roleName_zv);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _5, "rewind", NULL, 0);
		zephir_check_call_status();
		_37 = 1;
		while (1) {
			if (_37) {
				_37 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _5, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_36, _5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_36)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&roleToInherit, _5, "current", NULL, 0);
			zephir_check_call_status();
				_38$$21 = Z_TYPE_P(&roleToInherit) == IS_OBJECT;
				if (_38$$21) {
					_38$$21 = zephir_instance_of_ev(&roleToInherit, phalcon_acl_roleinterface_ce);
				}
				if (_38$$21) {
					ZEPHIR_CALL_METHOD(&roleInheritName, &roleToInherit, "getName", NULL, 0);
					zephir_check_call_status();
				} else {
					ZEPHIR_CPY_WRT(&roleInheritName, &roleToInherit);
				}
				zephir_read_property_cached(&_39$$21, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_40$$21);
				zephir_array_fetch(&_40$$21, &_39$$21, &roleName_zv, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 308);
				if (zephir_fast_in_array(&roleInheritName, &_40$$21)) {
					continue;
				}
				zephir_read_property_cached(&_41$$21, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
				if (UNEXPECTED(!(zephir_array_isset_value(&_41$$21, &roleInheritName)))) {
					ZEPHIR_INIT_NVAR(&_42$$25);
					object_init_ex(&_42$$25, phalcon_acl_exception_ce);
					ZEPHIR_INIT_NVAR(&_43$$25);
					ZEPHIR_CONCAT_SVS(&_43$$25, "Role '", &roleInheritName, "' (to inherit) does not exist in the role list");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_42$$25, "__construct", &_13, 32, &_43$$25);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_42$$25, "phalcon/Acl/Adapter/Memory.zep", 319);
					ZEPHIR_MM_RESTORE();
					return;
				}
				_44$$21 = ZEPHIR_IS_EQUAL(&roleName_zv, &roleInheritName);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (_44$$21) {
					RETURN_MM_BOOL(0);
				}
				zephir_read_property_cached(&_45$$21, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
				if (zephir_array_isset_value(&_45$$21, &roleInheritName)) {
					ZEPHIR_INIT_NVAR(&checkRoleToInherits);
					array_init(&checkRoleToInherits);
					zephir_read_property_cached(&_46$$27, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_OBS_NVAR(&_47$$27);
					zephir_array_fetch(&_47$$27, &_46$$27, &roleInheritName, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 332);
					if (Z_TYPE_P(&_47$$27) == IS_STRING) {
						ZEPHIR_INIT_NVAR(&_49$$27);
						zephir_string_to_char_array(&_49$$27, &_47$$27);
						_48$$27 = &_49$$27;
					} else {
						_48$$27 = &_47$$27;
					}
					zephir_is_iterable(_48$$27, 0, "phalcon/Acl/Adapter/Memory.zep", 336);
					if (Z_TYPE_P(_48$$27) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_48$$27), _50$$27)
						{
							ZEPHIR_INIT_NVAR(&usedRoleToInherit);
							ZVAL_COPY(&usedRoleToInherit, _50$$27);
							ZEPHIR_MAKE_REF(&checkRoleToInherits);
							ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
							ZEPHIR_UNREF(&checkRoleToInherits);
							zephir_check_call_status();
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, _48$$27, "rewind", NULL, 0);
						zephir_check_call_status();
						_52$$27 = 1;
						while (1) {
							if (_52$$27) {
								_52$$27 = 0;
							} else {
								ZEPHIR_CALL_METHOD(NULL, _48$$27, "next", NULL, 0);
								zephir_check_call_status();
							}
							ZEPHIR_CALL_METHOD(&_51$$27, _48$$27, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_51$$27)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&usedRoleToInherit, _48$$27, "current", NULL, 0);
							zephir_check_call_status();
								ZEPHIR_MAKE_REF(&checkRoleToInherits);
								ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
								ZEPHIR_UNREF(&checkRoleToInherits);
								zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&usedRoleToInherit);
					ZEPHIR_INIT_NVAR(&usedRoleToInherits);
					array_init(&usedRoleToInherits);
					while (1) {
						if (!(!(ZEPHIR_IS_EMPTY(&checkRoleToInherits)))) {
							break;
						}
						ZEPHIR_MAKE_REF(&checkRoleToInherits);
						ZEPHIR_CALL_FUNCTION(&checkRoleToInherit, "array_shift", &_24, 21, &checkRoleToInherits);
						ZEPHIR_UNREF(&checkRoleToInherits);
						zephir_check_call_status();
						if (zephir_array_isset_value(&usedRoleToInherits, &checkRoleToInherit)) {
							continue;
						}
						zephir_array_update_zval(&usedRoleToInherits, &checkRoleToInherit, &__$true, PH_COPY | PH_SEPARATE);
						_53$$30 = ZEPHIR_IS_EQUAL(&roleName_zv, &checkRoleToInherit);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						if (UNEXPECTED(_53$$30)) {
							ZEPHIR_INIT_NVAR(&_54$$32);
							object_init_ex(&_54$$32, phalcon_acl_exception_ce);
							ZEPHIR_INIT_NVAR(&_55$$32);
							ZEPHIR_CONCAT_SVS(&_55$$32, "Role '", &roleInheritName, "' (to inherit) produces an infinite loop");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_54$$32, "__construct", &_13, 32, &_55$$32);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_54$$32, "phalcon/Acl/Adapter/Memory.zep", 351);
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_read_property_cached(&_56$$30, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
						if (zephir_array_isset_value(&_56$$30, &checkRoleToInherit)) {
							zephir_read_property_cached(&_57$$33, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
							ZEPHIR_OBS_NVAR(&_58$$33);
							zephir_array_fetch(&_58$$33, &_57$$33, &checkRoleToInherit, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 358);
							if (Z_TYPE_P(&_58$$33) == IS_STRING) {
								ZEPHIR_INIT_NVAR(&_60$$33);
								zephir_string_to_char_array(&_60$$33, &_58$$33);
								_59$$33 = &_60$$33;
							} else {
								_59$$33 = &_58$$33;
							}
							zephir_is_iterable(_59$$33, 0, "phalcon/Acl/Adapter/Memory.zep", 361);
							if (Z_TYPE_P(_59$$33) == IS_ARRAY) {
								ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_59$$33), _61$$33)
								{
									ZEPHIR_INIT_NVAR(&usedRoleToInherit);
									ZVAL_COPY(&usedRoleToInherit, _61$$33);
									ZEPHIR_MAKE_REF(&checkRoleToInherits);
									ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
									ZEPHIR_UNREF(&checkRoleToInherits);
									zephir_check_call_status();
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, _59$$33, "rewind", NULL, 0);
								zephir_check_call_status();
								_63$$33 = 1;
								while (1) {
									if (_63$$33) {
										_63$$33 = 0;
									} else {
										ZEPHIR_CALL_METHOD(NULL, _59$$33, "next", NULL, 0);
										zephir_check_call_status();
									}
									ZEPHIR_CALL_METHOD(&_62$$33, _59$$33, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_62$$33)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&usedRoleToInherit, _59$$33, "current", NULL, 0);
									zephir_check_call_status();
										ZEPHIR_MAKE_REF(&checkRoleToInherits);
										ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_21, 149, &checkRoleToInherits, &usedRoleToInherit);
										ZEPHIR_UNREF(&checkRoleToInherits);
										zephir_check_call_status();
								}
							}
							ZEPHIR_INIT_NVAR(&usedRoleToInherit);
						}
					}
				}
				zephir_update_property_array_multi(this_ptr, SL("roleInherits"), &roleInheritName, SL("za"), 2, &roleName_zv);
		}
	}
	ZEPHIR_INIT_NVAR(&roleToInherit);
	RETURN_MM_BOOL(1);
}

/**
 * Adds a role to the ACL list. Second parameter allows inheriting access data from other existing role
 *
 * ```php
 * $acl->addRole(
 *     new Phalcon\Acl\Role("administrator"),
 *     "consultant"
 * );
 *
 * $acl->addRole("administrator", "consultant");
 * $acl->addRole("administrator", ["consultant", "consultant2"]);
 * ```
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, addRole)
{
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *role, role_sub, *accessInherits = NULL, accessInherits_sub, __$null, roleName, roleObject, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&role_sub);
	ZVAL_UNDEF(&accessInherits_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&roleName);
	ZVAL_UNDEF(&roleObject);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roles", 5, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(role)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(accessInherits)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &role, &accessInherits);
	if (!accessInherits) {
		accessInherits = &accessInherits_sub;
		accessInherits = &__$null;
	}
	ZEPHIR_INIT_VAR(&roleObject);
	_0 = Z_TYPE_P(role) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(role, phalcon_acl_roleinterface_ce);
	}
	if (_0) {
		ZEPHIR_CPY_WRT(&roleObject, role);
	} else if (Z_TYPE_P(role) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&roleObject);
		object_init_ex(&roleObject, phalcon_acl_role_ce);
		ZEPHIR_CALL_METHOD(NULL, &roleObject, "__construct", NULL, 150, role);
		zephir_check_call_status();
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_acl_exception_ce, "Role must be either a string or implement RoleInterface", "phalcon/Acl/Adapter/Memory.zep", 395);
		return;
	}
	ZEPHIR_CALL_METHOD(&roleName, &roleObject, "getName", NULL, 151);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_value(&_1, &roleName)) {
		RETURN_MM_BOOL(0);
	}
	zephir_update_property_array(this_ptr, SL("roles"), &roleName, &roleObject);
	if (Z_TYPE_P(accessInherits) != IS_NULL) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addInherit", NULL, 0, &roleName, accessInherits);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(1);
}

/**
 * Allow access to a role on a component. You can use `*` as wildcard
 *
 * ```php
 * // Allow access to guests to search on customers
 * $acl->allow("guests", "customers", "search");
 *
 * // Allow access to guests to search or create on customers
 * $acl->allow("guests", "customers", ["search", "create"]);
 *
 * // Allow access to any role to browse on products
 * $acl->allow("*", "products", "browse");
 *
 * // Allow access to any role to browse on any component
 * $acl->allow("*", "*", "browse");
 * ```
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, allow)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval roleName_zv, componentName_zv, *access, access_sub, *func = NULL, func_sub, __$null, role, rolesArray, _0, *_2, _3, *_4, _1$$3, _5$$4;
	zend_string *roleName = NULL, *componentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&access_sub);
	ZVAL_UNDEF(&func_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&role);
	ZVAL_UNDEF(&rolesArray);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roles", 5, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(roleName)
		Z_PARAM_STR(componentName)
		Z_PARAM_ZVAL(access)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(func)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	access = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		func = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&roleName_zv);
	ZVAL_STR_COPY(&roleName_zv, roleName);
	zephir_memory_observe(&componentName_zv);
	ZVAL_STR_COPY(&componentName_zv, componentName);
	if (!func) {
		func = &func_sub;
		func = &__$null;
	}
	ZEPHIR_INIT_VAR(&rolesArray);
	zephir_create_array(&rolesArray, 1, 0);
	zephir_array_fast_append(&rolesArray, &roleName_zv);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "*");
	if (ZEPHIR_IS_IDENTICAL(&_0, &roleName_zv)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&rolesArray);
		zephir_array_keys(&rolesArray, &_1$$3);
	}
	if (Z_TYPE_P(&rolesArray) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &rolesArray);
		_2 = &_3;
	} else {
		_2 = &rolesArray;
	}
	zephir_is_iterable(_2, 0, "phalcon/Acl/Adapter/Memory.zep", 448);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
	{
		ZEPHIR_INIT_NVAR(&role);
		ZVAL_COPY(&role, _4);
		ZVAL_LONG(&_5$$4, 1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "allowOrDeny", &_6, 152, &role, &componentName_zv, access, &_5$$4, func);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&role);
	ZEPHIR_MM_RESTORE();
}

/**
 * Deny access to a role on a component. You can use `*` as wildcard
 *
 * ```php
 * // Deny access to guests to search on customers
 * $acl->deny("guests", "customers", "search");
 *
 * // Deny access to guests to search or create on customers
 * $acl->deny("guests", "customers", ["search", "create"]);
 *
 * // Deny access to any role to browse on products
 * $acl->deny("*", "products", "browse");
 *
 * // Deny access to any role to browse on any component
 * $acl->deny("*", "*", "browse");
 * ```
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, deny)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval roleName_zv, componentName_zv, *access, access_sub, *func = NULL, func_sub, __$null, role, rolesArray, _0, *_2, _3, *_4, _1$$3, _5$$4;
	zend_string *roleName = NULL, *componentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&access_sub);
	ZVAL_UNDEF(&func_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&role);
	ZVAL_UNDEF(&rolesArray);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$4);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roles", 5, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_STR(roleName)
		Z_PARAM_STR(componentName)
		Z_PARAM_ZVAL(access)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(func)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	access = ZEND_CALL_ARG(execute_data, 3);
	if (ZEND_NUM_ARGS() > 3) {
		func = ZEND_CALL_ARG(execute_data, 4);
	}
	zephir_memory_observe(&roleName_zv);
	ZVAL_STR_COPY(&roleName_zv, roleName);
	zephir_memory_observe(&componentName_zv);
	ZVAL_STR_COPY(&componentName_zv, componentName);
	if (!func) {
		func = &func_sub;
		func = &__$null;
	}
	ZEPHIR_INIT_VAR(&rolesArray);
	zephir_create_array(&rolesArray, 1, 0);
	zephir_array_fast_append(&rolesArray, &roleName_zv);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "*");
	if (ZEPHIR_IS_IDENTICAL(&_0, &roleName_zv)) {
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&rolesArray);
		zephir_array_keys(&rolesArray, &_1$$3);
	}
	if (Z_TYPE_P(&rolesArray) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &rolesArray);
		_2 = &_3;
	} else {
		_2 = &rolesArray;
	}
	zephir_is_iterable(_2, 0, "phalcon/Acl/Adapter/Memory.zep", 485);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
	{
		ZEPHIR_INIT_NVAR(&role);
		ZVAL_COPY(&role, _4);
		ZVAL_LONG(&_5$$4, 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "allowOrDeny", &_6, 152, &role, &componentName_zv, access, &_5$$4, func);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&role);
	ZEPHIR_MM_RESTORE();
}

/**
 * Removes access from a component
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, dropComponentAccess)
{
	zval localAccess;
	zval accessKey;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval componentName_zv, *accessList, accessList_sub, accessName, _0$$3, *_1$$5, _2$$6, _3$$6;
	zend_string *componentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&accessList_sub);
	ZVAL_UNDEF(&accessName);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&accessKey);
	ZVAL_UNDEF(&localAccess);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("accessList", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(componentName)
		Z_PARAM_ZVAL(accessList)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	accessList = ZEND_CALL_ARG(execute_data, 2);
	zephir_memory_observe(&componentName_zv);
	ZVAL_STR_COPY(&componentName_zv, componentName);
	ZEPHIR_INIT_VAR(&localAccess);
	array_init(&localAccess);
	if (Z_TYPE_P(accessList) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0);
		zephir_array_fast_append(&_0$$3, accessList);
		ZEPHIR_CPY_WRT(&localAccess, &_0$$3);
	} else {
		if (UNEXPECTED(Z_TYPE_P(accessList) != IS_ARRAY)) {
			zephir_throw_variable_type_error(accessList, "localAccess", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&localAccess, accessList);
	}
	if (Z_TYPE_P(accessList) == IS_ARRAY) {
		zephir_is_iterable(&localAccess, 0, "phalcon/Acl/Adapter/Memory.zep", 510);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&localAccess), _1$$5)
		{
			ZEPHIR_INIT_NVAR(&accessName);
			ZVAL_COPY(&accessName, _1$$5);
			ZEPHIR_INIT_NVAR(&_2$$6);
			ZEPHIR_CONCAT_VSV(&_2$$6, &componentName_zv, "!", &accessName);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&accessKey, &_2$$6);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_3$$6, this_ptr, _zephir_prop_0, 249, PH_NOISY_CC | PH_READONLY);
			if (zephir_array_isset_value(&_3$$6, &accessKey)) {
				zephir_unset_property_array(this_ptr, ZEND_STRL("accessList"), &accessKey);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&accessName);
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Returns the latest function used to acquire access
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getActiveFunction)
{

	RETURN_MEMBER(getThis(), "activeFunction");
}

/**
 * Returns number of additional arguments(excluding role and resource) for active function
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getActiveFunctionCustomArgumentsCount)
{

	RETURN_MEMBER_TYPED(getThis(), "activeFunctionCustomArgumentsCount", IS_LONG);
}

/**
 * Returns the latest key used to acquire access
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getActiveKey)
{

	RETURN_MEMBER(getThis(), "activeKey");
}

/**
 * Return an array with every component registered in the list
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getComponents)
{

	RETURN_MEMBER_TYPED(getThis(), "components", IS_ARRAY);
}

/**
 * Returns the inherited roles for a passed role name. If no role name
 * has been specified it will return the whole array. If the role has not
 * been found it returns an empty array
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getInheritedRoles)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval roleName_zv, result, _0, _1;
	zend_string *roleName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roleInherits", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(roleName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!roleName) {
		roleName = zend_string_init(ZEND_STRL(""), 0);
		zephir_memory_observe(&roleName_zv);
		ZVAL_STR(&roleName_zv, roleName);
	} else {
		zephir_memory_observe(&roleName_zv);
	ZVAL_STR_COPY(&roleName_zv, roleName);
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "");
	if (ZEPHIR_IS_IDENTICAL(&_0, &roleName_zv)) {
		RETURN_MM_MEMBER_TYPED(getThis(), "roleInherits", IS_ARRAY);
	}
	zephir_memory_observe(&result);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 251, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&result, &_1, &roleName_zv, 0))) {
		array_init(return_value);
		RETURN_MM();
	}
	RETURN_CCTOR(&result);
}

/**
 * Returns the default ACL access level for no arguments provided in
 * `isAllowed` action if a `func` (callable) exists for `accessKey`
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getNoArgumentsDefaultAction)
{

	RETURN_MEMBER_TYPED(getThis(), "noArgumentsDefaultAction", IS_LONG);
}

/**
 * Return an array with every role registered in the list
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, getRoles)
{

	RETURN_MEMBER_TYPED(getThis(), "roles", IS_ARRAY);
}

/**
 * Check whether a role is allowed to access an action from a component
 *
 * ```php
 * // Does andres have access to the customers component to create?
 * $acl->isAllowed("andres", "Products", "create");
 *
 * // Do guests have access to any component to edit?
 * $acl->isAllowed("guests", "*", "edit");
 * ```
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, isAllowed)
{
	zval _2$$6, _5$$10;
	zend_bool hasComponent, hasRole, _10, _13$$16, _40$$15, _18$$17, _20$$18, _23$$18, _24$$18, _26$$18, _27$$18, _29$$18, _41$$23, _42$$24, _44$$24, _45$$24, _47$$24, _48$$24, _50$$24, _62$$31, _64$$30, _66$$32;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_19 = NULL, *_22 = NULL, *_36 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zend_string *access = NULL;
	zval *roleName = NULL, roleName_sub, *componentName = NULL, componentName_sub, access_zv, *parameters_param = NULL, __$null, accessKey, accessList, className, componentObject, haveAccess, funcAccess, funcList, numberOfRequiredParameters, parameterNumber, parameterToCheck, parametersForFunction, reflectionClass, reflectionFunction, reflectionParameter, reflectionParameters, reflectionType, roleObject, userParametersSizeShouldBe, _6, _7, _8, _0$$5, _1$$6, _3$$9, _4$$10, _9$$12, _11$$14, _12$$14, _14$$16, *_15$$15, _16$$15, *_17$$15, _39$$15, _68$$15, _69$$15, _21$$18, _25$$18, _28$$18, _30$$18, _31$$18, _32$$21, _33$$21, _34$$21, _35$$21, _37$$21, _38$$22, _43$$24, _46$$24, _49$$24, _51$$24, _52$$24, _53$$27, _54$$27, _55$$27, _56$$27, _57$$27, _58$$28, _59$$29, _60$$29, _61$$31, _63$$31, _65$$30, _67$$32;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_sub);
	ZVAL_UNDEF(&componentName_sub);
	ZVAL_UNDEF(&access_zv);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&accessKey);
	ZVAL_UNDEF(&accessList);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&componentObject);
	ZVAL_UNDEF(&haveAccess);
	ZVAL_UNDEF(&funcAccess);
	ZVAL_UNDEF(&funcList);
	ZVAL_UNDEF(&numberOfRequiredParameters);
	ZVAL_UNDEF(&parameterNumber);
	ZVAL_UNDEF(&parameterToCheck);
	ZVAL_UNDEF(&parametersForFunction);
	ZVAL_UNDEF(&reflectionClass);
	ZVAL_UNDEF(&reflectionFunction);
	ZVAL_UNDEF(&reflectionParameter);
	ZVAL_UNDEF(&reflectionParameters);
	ZVAL_UNDEF(&reflectionType);
	ZVAL_UNDEF(&roleObject);
	ZVAL_UNDEF(&userParametersSizeShouldBe);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_0$$5);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_3$$9);
	ZVAL_UNDEF(&_4$$10);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_11$$14);
	ZVAL_UNDEF(&_12$$14);
	ZVAL_UNDEF(&_14$$16);
	ZVAL_UNDEF(&_16$$15);
	ZVAL_UNDEF(&_39$$15);
	ZVAL_UNDEF(&_68$$15);
	ZVAL_UNDEF(&_69$$15);
	ZVAL_UNDEF(&_21$$18);
	ZVAL_UNDEF(&_25$$18);
	ZVAL_UNDEF(&_28$$18);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_31$$18);
	ZVAL_UNDEF(&_32$$21);
	ZVAL_UNDEF(&_33$$21);
	ZVAL_UNDEF(&_34$$21);
	ZVAL_UNDEF(&_35$$21);
	ZVAL_UNDEF(&_37$$21);
	ZVAL_UNDEF(&_38$$22);
	ZVAL_UNDEF(&_43$$24);
	ZVAL_UNDEF(&_46$$24);
	ZVAL_UNDEF(&_49$$24);
	ZVAL_UNDEF(&_51$$24);
	ZVAL_UNDEF(&_52$$24);
	ZVAL_UNDEF(&_53$$27);
	ZVAL_UNDEF(&_54$$27);
	ZVAL_UNDEF(&_55$$27);
	ZVAL_UNDEF(&_56$$27);
	ZVAL_UNDEF(&_57$$27);
	ZVAL_UNDEF(&_58$$28);
	ZVAL_UNDEF(&_59$$29);
	ZVAL_UNDEF(&_60$$29);
	ZVAL_UNDEF(&_61$$31);
	ZVAL_UNDEF(&_63$$31);
	ZVAL_UNDEF(&_65$$30);
	ZVAL_UNDEF(&_67$$32);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_5$$10);
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
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("activeRole", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("activeComponent", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("activeAccess", 12, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("activeKey", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("activeFunction", 14, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("access", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_6)) {
		_zephir_prop_6 = zend_string_init("func", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_7)) {
		_zephir_prop_7 = zend_string_init("activeFunctionCustomArgumentsCount", 34, 1);
	}
	if (UNEXPECTED(!_zephir_prop_8)) {
		_zephir_prop_8 = zend_string_init("roles", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_9)) {
		_zephir_prop_9 = zend_string_init("defaultAccess", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_10)) {
		_zephir_prop_10 = zend_string_init("accessGranted", 13, 1);
	}
	if (UNEXPECTED(!_zephir_prop_11)) {
		_zephir_prop_11 = zend_string_init("noArgumentsDefaultAction", 24, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(3, 4)
		Z_PARAM_ZVAL(roleName)
		Z_PARAM_ZVAL(componentName)
		Z_PARAM_STR(access)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY_OR_NULL(parameters, parameters_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	roleName = ZEND_CALL_ARG(execute_data, 1);
	componentName = ZEND_CALL_ARG(execute_data, 2);
	if (ZEND_NUM_ARGS() > 3) {
		parameters_param = ZEND_CALL_ARG(execute_data, 4);
	}
	ZEPHIR_SEPARATE_PARAM(roleName);
	ZEPHIR_SEPARATE_PARAM(componentName);
	zephir_memory_observe(&access_zv);
	ZVAL_STR_COPY(&access_zv, access);
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}
	ZEPHIR_INIT_VAR(&componentObject);
	ZVAL_NULL(&componentObject);
	ZEPHIR_INIT_VAR(&haveAccess);
	ZVAL_NULL(&haveAccess);
	ZEPHIR_INIT_VAR(&funcAccess);
	ZVAL_NULL(&funcAccess);
	ZEPHIR_INIT_VAR(&roleObject);
	ZVAL_NULL(&roleObject);
	hasComponent = 0;
	hasRole = 0;
	if (Z_TYPE_P(roleName) == IS_OBJECT) {
		if (zephir_instance_of_ev(roleName, phalcon_acl_roleawareinterface_ce)) {
			ZEPHIR_CPY_WRT(&roleObject, roleName);
			ZEPHIR_CALL_METHOD(roleName, &roleObject, "getRoleName", NULL, 0);
			zephir_check_call_status();
		} else if (zephir_instance_of_ev(roleName, phalcon_acl_roleinterface_ce)) {
			ZEPHIR_CALL_METHOD(&_0$$5, roleName, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(roleName, &_0$$5);
		} else {
			ZEPHIR_INIT_VAR(&_1$$6);
			object_init_ex(&_1$$6, phalcon_acl_exception_ce);
			ZEPHIR_INIT_VAR(&_2$$6);
			ZEPHIR_CONCAT_SS(&_2$$6, "Object passed as roleName must implement ", "Phalcon\\Acl\\RoleAwareInterface or Phalcon\\Acl\\RoleInterface");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_1$$6, "__construct", NULL, 32, &_2$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_1$$6, "phalcon/Acl/Adapter/Memory.zep", 615);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(componentName) == IS_OBJECT) {
		if (zephir_instance_of_ev(componentName, phalcon_acl_componentawareinterface_ce)) {
			ZEPHIR_CPY_WRT(&componentObject, componentName);
			ZEPHIR_CALL_METHOD(componentName, &componentObject, "getComponentName", NULL, 0);
			zephir_check_call_status();
		} else if (zephir_instance_of_ev(componentName, phalcon_acl_componentinterface_ce)) {
			ZEPHIR_CALL_METHOD(&_3$$9, componentName, "getName", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(componentName, &_3$$9);
		} else {
			ZEPHIR_INIT_VAR(&_4$$10);
			object_init_ex(&_4$$10, phalcon_acl_exception_ce);
			ZEPHIR_INIT_VAR(&_5$$10);
			ZEPHIR_CONCAT_SS(&_5$$10, "Object passed as componentName must implement ", "Phalcon\\Acl\\ComponentAwareInterface or Phalcon\\Acl\\ComponentInterface");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, &_4$$10, "__construct", NULL, 32, &_5$$10);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_4$$10, "phalcon/Acl/Adapter/Memory.zep", 629);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 252, roleName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 253, componentName);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 254, &access_zv);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 255, &__$null);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 255, &__$null);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 256, &__$null);
	zephir_memory_observe(&accessList);
	zephir_read_property_cached(&accessList, this_ptr, _zephir_prop_5, 257, PH_NOISY_CC);
	zephir_memory_observe(&funcList);
	zephir_read_property_cached(&funcList, this_ptr, _zephir_prop_6, 258, PH_NOISY_CC);
	ZVAL_UNDEF(&_6);
	ZVAL_LONG(&_6, 0);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 259, &_6);
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "acl:beforeCheckAccess");
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "fireManagerEvent", NULL, 0, &_8, this_ptr);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_7)) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_8, 250, PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_value(&_6, roleName))) {
		zephir_read_property_cached(&_9$$12, this_ptr, _zephir_prop_9, 260, PH_NOISY_CC | PH_READONLY);
		RETURN_MM_BOOL((ZEPHIR_IS_LONG(&_9$$12, 1)));
	}
	ZEPHIR_CALL_METHOD(&accessKey, this_ptr, "canAccess", NULL, 153, roleName, componentName, &access_zv);
	zephir_check_call_status();
	_10 = Z_TYPE_P(&accessKey) != IS_NULL;
	if (_10) {
		_10 = zephir_array_isset_value(&accessList, &accessKey);
	}
	if (_10) {
		ZEPHIR_OBS_NVAR(&haveAccess);
		zephir_array_fetch(&haveAccess, &accessList, &accessKey, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 661);
		ZEPHIR_OBS_NVAR(&funcAccess);
		zephir_array_isset_fetch(&funcAccess, &funcList, &accessKey, 0);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_10, 261, &haveAccess);
	ZEPHIR_INIT_NVAR(&_8);
	ZVAL_STRING(&_8, "acl:afterCheckAccess");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "fireManagerEvent", NULL, 0, &_8, this_ptr);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 255, &accessKey);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 256, &funcAccess);
	if (Z_TYPE_P(&haveAccess) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_11$$14);
		ZEPHIR_CONCAT_VSVSV(&_11$$14, roleName, "!", componentName, "!", &access_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 255, &_11$$14);
		zephir_read_property_cached(&_12$$14, this_ptr, _zephir_prop_9, 260, PH_NOISY_CC | PH_READONLY);
		RETURN_MM_BOOL(ZEPHIR_IS_LONG(&_12$$14, 1));
	}
	if (zephir_is_callable(&funcAccess)) {
		ZEPHIR_INIT_VAR(&reflectionFunction);
		object_init_ex(&reflectionFunction, zephir_get_internal_ce(SL("reflectionfunction")));
		ZEPHIR_CALL_METHOD(NULL, &reflectionFunction, "__construct", NULL, 154, &funcAccess);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&reflectionParameters, &reflectionFunction, "getParameters", NULL, 155);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&parameterNumber);
		ZVAL_LONG(&parameterNumber, zephir_fast_count_int(&reflectionParameters));
		if (ZEPHIR_IS_LONG_IDENTICAL(&parameterNumber, 0)) {
			_13$$16 = ZEPHIR_IS_LONG(&haveAccess, 1);
			if (_13$$16) {
				ZEPHIR_INIT_VAR(&_14$$16);
				ZEPHIR_CALL_USER_FUNC(&_14$$16, &funcAccess);
				zephir_check_call_status();
				_13$$16 = zephir_is_true(&_14$$16);
			}
			RETURN_MM_BOOL(_13$$16);
		}
		ZEPHIR_INIT_VAR(&parametersForFunction);
		array_init(&parametersForFunction);
		ZEPHIR_CALL_METHOD(&numberOfRequiredParameters, &reflectionFunction, "getNumberOfRequiredParameters", NULL, 156);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&userParametersSizeShouldBe, &parameterNumber);
		if (Z_TYPE_P(&reflectionParameters) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_16$$15);
			zephir_string_to_char_array(&_16$$15, &reflectionParameters);
			_15$$15 = &_16$$15;
		} else {
			_15$$15 = &reflectionParameters;
		}
		zephir_is_iterable(_15$$15, 0, "phalcon/Acl/Adapter/Memory.zep", 768);
		if (Z_TYPE_P(_15$$15) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$15), _17$$15)
			{
				ZEPHIR_INIT_NVAR(&reflectionParameter);
				ZVAL_COPY(&reflectionParameter, _17$$15);
				ZEPHIR_CALL_METHOD(&reflectionType, &reflectionParameter, "getType", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&parameterToCheck, &reflectionParameter, "getName", NULL, 0);
				zephir_check_call_status();
				_18$$17 = Z_TYPE_P(&reflectionType) != IS_NULL;
				if (_18$$17) {
					_18$$17 = (zephir_is_instance_of(&reflectionType, SL("ReflectionNamedType")));
				}
				if (_18$$17) {
					ZEPHIR_CALL_METHOD(&className, &reflectionType, "getName", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&reflectionClass);
					object_init_ex(&reflectionClass, zephir_get_internal_ce(SL("reflectionclass")));
					ZEPHIR_CALL_METHOD(NULL, &reflectionClass, "__construct", &_19, 157, &className);
					zephir_check_call_status();
					_20$$18 = Z_TYPE_P(&roleObject) != IS_NULL;
					if (_20$$18) {
						ZEPHIR_CALL_METHOD(&_21$$18, &reflectionClass, "isInstance", &_22, 158, &roleObject);
						zephir_check_call_status();
						_20$$18 = zephir_is_true(&_21$$18);
					}
					_23$$18 = _20$$18;
					if (_23$$18) {
						_23$$18 = !hasRole;
					}
					if (_23$$18) {
						hasRole = 1;
						zephir_array_append(&parametersForFunction, &roleObject, PH_SEPARATE, "phalcon/Acl/Adapter/Memory.zep", 721);
						SEPARATE_ZVAL(&userParametersSizeShouldBe);
						zephir_decrement(&userParametersSizeShouldBe);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
					_24$$18 = Z_TYPE_P(&componentObject) != IS_NULL;
					if (_24$$18) {
						ZEPHIR_CALL_METHOD(&_25$$18, &reflectionClass, "isInstance", &_22, 158, &componentObject);
						zephir_check_call_status();
						_24$$18 = zephir_is_true(&_25$$18);
					}
					_26$$18 = _24$$18;
					if (_26$$18) {
						_26$$18 = !hasComponent;
					}
					if (_26$$18) {
						hasComponent = 1;
						zephir_array_append(&parametersForFunction, &componentObject, PH_SEPARATE, "phalcon/Acl/Adapter/Memory.zep", 733);
						SEPARATE_ZVAL(&userParametersSizeShouldBe);
						zephir_decrement(&userParametersSizeShouldBe);
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						continue;
					}
					_27$$18 = zephir_array_isset_value(&parameters, &parameterToCheck);
					if (_27$$18) {
						ZEPHIR_OBS_NVAR(&_28$$18);
						zephir_array_fetch(&_28$$18, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 744);
						_27$$18 = Z_TYPE_P(&_28$$18) == IS_OBJECT;
					}
					_29$$18 = _27$$18;
					if (_29$$18) {
						ZEPHIR_OBS_NVAR(&_31$$18);
						zephir_array_fetch(&_31$$18, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 745);
						ZEPHIR_CALL_METHOD(&_30$$18, &reflectionClass, "isInstance", &_22, 158, &_31$$18);
						zephir_check_call_status();
						_29$$18 = !zephir_is_true(&_30$$18);
					}
					if (UNEXPECTED(_29$$18)) {
						ZEPHIR_INIT_NVAR(&_32$$21);
						object_init_ex(&_32$$21, phalcon_acl_exception_ce);
						ZEPHIR_INIT_NVAR(&_33$$21);
						ZEPHIR_OBS_NVAR(&_34$$21);
						zephir_array_fetch(&_34$$21, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 752);
						zephir_get_class(&_33$$21, &_34$$21, 0);
						ZEPHIR_CALL_METHOD(&_35$$21, &reflectionClass, "getName", &_36, 159);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_37$$21);
						ZEPHIR_CONCAT_SSSVSVSVSVSVS(&_37$$21, "Your passed parameter does not have the ", "same class as the parameter in defined function ", "when checking if ", roleName, " can ", &access_zv, " ", componentName, ". Class passed: ", &_33$$21, " , Class in defined function: ", &_35$$21, ".");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_32$$21, "__construct", NULL, 32, &_37$$21);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_32$$21, "phalcon/Acl/Adapter/Memory.zep", 755);
						ZEPHIR_MM_RESTORE();
						return;
					}
				}
				if (zephir_array_isset_value(&parameters, &parameterToCheck)) {
					ZEPHIR_OBS_NVAR(&_38$$22);
					zephir_array_fetch(&_38$$22, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 764);
					zephir_array_append(&parametersForFunction, &_38$$22, PH_SEPARATE, "phalcon/Acl/Adapter/Memory.zep", 764);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _15$$15, "rewind", NULL, 0);
			zephir_check_call_status();
			_40$$15 = 1;
			while (1) {
				if (_40$$15) {
					_40$$15 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _15$$15, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_39$$15, _15$$15, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_39$$15)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&reflectionParameter, _15$$15, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&reflectionType, &reflectionParameter, "getType", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&parameterToCheck, &reflectionParameter, "getName", NULL, 0);
					zephir_check_call_status();
					_41$$23 = Z_TYPE_P(&reflectionType) != IS_NULL;
					if (_41$$23) {
						_41$$23 = (zephir_is_instance_of(&reflectionType, SL("ReflectionNamedType")));
					}
					if (_41$$23) {
						ZEPHIR_CALL_METHOD(&className, &reflectionType, "getName", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&reflectionClass);
						object_init_ex(&reflectionClass, zephir_get_internal_ce(SL("reflectionclass")));
						ZEPHIR_CALL_METHOD(NULL, &reflectionClass, "__construct", &_19, 157, &className);
						zephir_check_call_status();
						_42$$24 = Z_TYPE_P(&roleObject) != IS_NULL;
						if (_42$$24) {
							ZEPHIR_CALL_METHOD(&_43$$24, &reflectionClass, "isInstance", &_22, 158, &roleObject);
							zephir_check_call_status();
							_42$$24 = zephir_is_true(&_43$$24);
						}
						_44$$24 = _42$$24;
						if (_44$$24) {
							_44$$24 = !hasRole;
						}
						if (_44$$24) {
							hasRole = 1;
							zephir_array_append(&parametersForFunction, &roleObject, PH_SEPARATE, "phalcon/Acl/Adapter/Memory.zep", 721);
							SEPARATE_ZVAL(&userParametersSizeShouldBe);
							zephir_decrement(&userParametersSizeShouldBe);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							continue;
						}
						_45$$24 = Z_TYPE_P(&componentObject) != IS_NULL;
						if (_45$$24) {
							ZEPHIR_CALL_METHOD(&_46$$24, &reflectionClass, "isInstance", &_22, 158, &componentObject);
							zephir_check_call_status();
							_45$$24 = zephir_is_true(&_46$$24);
						}
						_47$$24 = _45$$24;
						if (_47$$24) {
							_47$$24 = !hasComponent;
						}
						if (_47$$24) {
							hasComponent = 1;
							zephir_array_append(&parametersForFunction, &componentObject, PH_SEPARATE, "phalcon/Acl/Adapter/Memory.zep", 733);
							SEPARATE_ZVAL(&userParametersSizeShouldBe);
							zephir_decrement(&userParametersSizeShouldBe);
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							continue;
						}
						_48$$24 = zephir_array_isset_value(&parameters, &parameterToCheck);
						if (_48$$24) {
							ZEPHIR_OBS_NVAR(&_49$$24);
							zephir_array_fetch(&_49$$24, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 744);
							_48$$24 = Z_TYPE_P(&_49$$24) == IS_OBJECT;
						}
						_50$$24 = _48$$24;
						if (_50$$24) {
							ZEPHIR_OBS_NVAR(&_52$$24);
							zephir_array_fetch(&_52$$24, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 745);
							ZEPHIR_CALL_METHOD(&_51$$24, &reflectionClass, "isInstance", &_22, 158, &_52$$24);
							zephir_check_call_status();
							_50$$24 = !zephir_is_true(&_51$$24);
						}
						if (UNEXPECTED(_50$$24)) {
							ZEPHIR_INIT_NVAR(&_53$$27);
							object_init_ex(&_53$$27, phalcon_acl_exception_ce);
							ZEPHIR_INIT_NVAR(&_54$$27);
							ZEPHIR_OBS_NVAR(&_55$$27);
							zephir_array_fetch(&_55$$27, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 752);
							zephir_get_class(&_54$$27, &_55$$27, 0);
							ZEPHIR_CALL_METHOD(&_56$$27, &reflectionClass, "getName", &_36, 159);
							zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_57$$27);
							ZEPHIR_CONCAT_SSSVSVSVSVSVS(&_57$$27, "Your passed parameter does not have the ", "same class as the parameter in defined function ", "when checking if ", roleName, " can ", &access_zv, " ", componentName, ". Class passed: ", &_54$$27, " , Class in defined function: ", &_56$$27, ".");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							ZEPHIR_CALL_METHOD(NULL, &_53$$27, "__construct", NULL, 32, &_57$$27);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_53$$27, "phalcon/Acl/Adapter/Memory.zep", 755);
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					if (zephir_array_isset_value(&parameters, &parameterToCheck)) {
						ZEPHIR_OBS_NVAR(&_58$$28);
						zephir_array_fetch(&_58$$28, &parameters, &parameterToCheck, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 764);
						zephir_array_append(&parametersForFunction, &_58$$28, PH_SEPARATE, "phalcon/Acl/Adapter/Memory.zep", 764);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&reflectionParameter);
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_7, 259, &userParametersSizeShouldBe);
		if (UNEXPECTED(ZEPHIR_LT_LONG(&userParametersSizeShouldBe, zephir_fast_count_int(&parameters)))) {
			ZEPHIR_INIT_VAR(&_59$$29);
			ZEPHIR_CONCAT_SSVSVSVS(&_59$$29, "Number of parameters in array is higher than ", "the number of parameters in defined function when checking if '", roleName, "' can '", &access_zv, "' '", componentName, "'. Extra parameters will be ignored.");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZVAL_LONG(&_60$$29, 512);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_59$$29, &_60$$29);
			zephir_check_call_status();
		}
		if (zephir_fast_count_int(&parametersForFunction) == 0) {
			if (UNEXPECTED(ZEPHIR_GT_LONG(&numberOfRequiredParameters, 0))) {
				ZEPHIR_INIT_VAR(&_61$$31);
				ZEPHIR_CONCAT_SVSVSVS(&_61$$31, "You did not provide any parameters when '", roleName, "' can '", &access_zv, "' '", componentName, "'. We will use default action when no arguments.");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", NULL, 9, &_61$$31);
				zephir_check_call_status();
				_62$$31 = ZEPHIR_IS_LONG(&haveAccess, 1);
				if (_62$$31) {
					zephir_read_property_cached(&_63$$31, this_ptr, _zephir_prop_11, 262, PH_NOISY_CC | PH_READONLY);
					_62$$31 = ZEPHIR_IS_LONG(&_63$$31, 1);
				}
				RETURN_MM_BOOL(_62$$31);
			}
			_64$$30 = ZEPHIR_IS_LONG(&haveAccess, 1);
			if (_64$$30) {
				ZEPHIR_INIT_VAR(&_65$$30);
				ZEPHIR_CALL_USER_FUNC(&_65$$30, &funcAccess);
				zephir_check_call_status();
				_64$$30 = zephir_is_true(&_65$$30);
			}
			RETURN_MM_BOOL(_64$$30);
		}
		if (ZEPHIR_LE_LONG(&numberOfRequiredParameters, zephir_fast_count_int(&parametersForFunction))) {
			_66$$32 = ZEPHIR_IS_LONG(&haveAccess, 1);
			if (_66$$32) {
				ZEPHIR_INIT_VAR(&_67$$32);
				ZEPHIR_CALL_USER_FUNC_ARRAY(&_67$$32, &funcAccess, &parametersForFunction);
				zephir_check_call_status();
				_66$$32 = zephir_is_true(&_67$$32);
			}
			RETURN_MM_BOOL(_66$$32);
		}
		ZEPHIR_INIT_VAR(&_68$$15);
		object_init_ex(&_68$$15, phalcon_acl_exception_ce);
		ZEPHIR_INIT_VAR(&_69$$15);
		ZEPHIR_CONCAT_SSVSVSVS(&_69$$15, "You did not provide all necessary parameters for the ", "defined function when checking if '", roleName, "' can '", &access_zv, "' for '", componentName, "'.");
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_68$$15, "__construct", NULL, 32, &_69$$15);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_68$$15, "phalcon/Acl/Adapter/Memory.zep", 809);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_BOOL(ZEPHIR_IS_LONG(&haveAccess, 1));
}

/**
 * Check whether role exist in the roles list
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, isRole)
{
	zval roleName_zv, _0;
	zend_string *roleName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roles", 5, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(roleName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&roleName_zv, roleName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_value(&_0, &roleName_zv));
}

/**
 * Check whether component exist in the components list
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, isComponent)
{
	zval componentName_zv, _0;
	zend_string *componentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("componentsNames", 15, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(componentName)
	ZEND_PARSE_PARAMETERS_END();
	ZVAL_STR(&componentName_zv, componentName);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 248, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_value(&_0, &componentName_zv));
}

/**
 * Sets the default access level (`Phalcon\Enum::ALLOW` or `Phalcon\Enum::DENY`)
 * for no arguments provided in isAllowed action if there exists func for
 * accessKey
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, setNoArgumentsDefaultAction)
{
	zval *defaultAccess_param = NULL, _0;
	zend_long defaultAccess;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("noArgumentsDefaultAction", 24, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(defaultAccess)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &defaultAccess_param);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, defaultAccess);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 262, &_0);
}

/**
 * Checks if a role has access to a component
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, allowOrDeny)
{
	zend_bool _11$$3, _18$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval roleName_zv, componentName_zv, *access, access_sub, *action, action_sub, *func = NULL, func_sub, __$null, accessList, accessName, accessKey, _0, _1, _2, _3, *_4$$3, _5$$3, *_6$$3, _10$$3, *_14$$3, _15$$3, *_16$$3, _17$$3, _7$$5, _8$$5, _12$$7, _13$$7, _19$$14, _20$$14;
	zend_string *roleName = NULL, *componentName = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&access_sub);
	ZVAL_UNDEF(&action_sub);
	ZVAL_UNDEF(&func_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&accessList);
	ZVAL_UNDEF(&accessName);
	ZVAL_UNDEF(&accessKey);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_20$$14);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("roles", 5, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("componentsNames", 15, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("accessList", 10, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(4, 5)
		Z_PARAM_STR(roleName)
		Z_PARAM_STR(componentName)
		Z_PARAM_ZVAL(access)
		Z_PARAM_ZVAL(action)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(func)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	access = ZEND_CALL_ARG(execute_data, 3);
	action = ZEND_CALL_ARG(execute_data, 4);
	if (ZEND_NUM_ARGS() > 4) {
		func = ZEND_CALL_ARG(execute_data, 5);
	}
	zephir_memory_observe(&roleName_zv);
	ZVAL_STR_COPY(&roleName_zv, roleName);
	zephir_memory_observe(&componentName_zv);
	ZVAL_STR_COPY(&componentName_zv, componentName);
	if (!func) {
		func = &func_sub;
		func = &__$null;
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 250, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Role");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkExists", NULL, 148, &_0, &roleName_zv, &_1);
	zephir_check_call_status();
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 248, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "Component");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkExists", NULL, 148, &_2, &componentName_zv, &_1);
	zephir_check_call_status();
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_2, 249, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&accessList, &_3);
	if (Z_TYPE_P(access) == IS_ARRAY) {
		if (Z_TYPE_P(access) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_5$$3);
			zephir_string_to_char_array(&_5$$3, access);
			_4$$3 = &_5$$3;
		} else {
			_4$$3 = access;
		}
		zephir_is_iterable(_4$$3, 0, "phalcon/Acl/Adapter/Memory.zep", 865);
		if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
			{
				ZEPHIR_INIT_NVAR(&accessName);
				ZVAL_COPY(&accessName, _6$$3);
				ZEPHIR_INIT_NVAR(&accessKey);
				ZEPHIR_CONCAT_VSV(&accessKey, &componentName_zv, "!", &accessName);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if (UNEXPECTED(!(zephir_array_isset_value(&accessList, &accessKey)))) {
					ZEPHIR_INIT_NVAR(&_7$$5);
					object_init_ex(&_7$$5, phalcon_acl_exception_ce);
					ZEPHIR_INIT_NVAR(&_8$$5);
					ZEPHIR_CONCAT_SVSVS(&_8$$5, "Access '", &accessName, "' does not exist in component '", &componentName_zv, "'");
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_CALL_METHOD(NULL, &_7$$5, "__construct", &_9, 32, &_8$$5);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_7$$5, "phalcon/Acl/Adapter/Memory.zep", 861);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_11$$3 = 1;
			while (1) {
				if (_11$$3) {
					_11$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_10$$3, _4$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_10$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&accessName, _4$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&accessKey);
					ZEPHIR_CONCAT_VSV(&accessKey, &componentName_zv, "!", &accessName);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					if (UNEXPECTED(!(zephir_array_isset_value(&accessList, &accessKey)))) {
						ZEPHIR_INIT_NVAR(&_12$$7);
						object_init_ex(&_12$$7, phalcon_acl_exception_ce);
						ZEPHIR_INIT_NVAR(&_13$$7);
						ZEPHIR_CONCAT_SVSVS(&_13$$7, "Access '", &accessName, "' does not exist in component '", &componentName_zv, "'");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						ZEPHIR_CALL_METHOD(NULL, &_12$$7, "__construct", &_9, 32, &_13$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_12$$7, "phalcon/Acl/Adapter/Memory.zep", 861);
						ZEPHIR_MM_RESTORE();
						return;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&accessName);
		if (Z_TYPE_P(access) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_15$$3);
			zephir_string_to_char_array(&_15$$3, access);
			_14$$3 = &_15$$3;
		} else {
			_14$$3 = access;
		}
		zephir_is_iterable(_14$$3, 0, "phalcon/Acl/Adapter/Memory.zep", 873);
		if (Z_TYPE_P(_14$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_14$$3), _16$$3)
			{
				ZEPHIR_INIT_NVAR(&accessName);
				ZVAL_COPY(&accessName, _16$$3);
				ZEPHIR_INIT_NVAR(&accessKey);
				ZEPHIR_CONCAT_VSVSV(&accessKey, &roleName_zv, "!", &componentName_zv, "!", &accessName);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_update_property_array(this_ptr, SL("access"), &accessKey, action);
				if (Z_TYPE_P(func) != IS_NULL) {
					zephir_update_property_array(this_ptr, SL("func"), &accessKey, func);
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _14$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_18$$3 = 1;
			while (1) {
				if (_18$$3) {
					_18$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _14$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_17$$3, _14$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_17$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&accessName, _14$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&accessKey);
					ZEPHIR_CONCAT_VSVSV(&accessKey, &roleName_zv, "!", &componentName_zv, "!", &accessName);
					if (UNEXPECTED(EG(exception))) {
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_update_property_array(this_ptr, SL("access"), &accessKey, action);
					if (Z_TYPE_P(func) != IS_NULL) {
						zephir_update_property_array(this_ptr, SL("func"), &accessKey, func);
					}
			}
		}
		ZEPHIR_INIT_NVAR(&accessName);
	} else {
		if (!ZEPHIR_IS_STRING(access, "*")) {
			ZEPHIR_INIT_NVAR(&accessKey);
			ZEPHIR_CONCAT_VSV(&accessKey, &componentName_zv, "!", access);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (UNEXPECTED(!(zephir_array_isset_value(&accessList, &accessKey)))) {
				ZEPHIR_INIT_VAR(&_19$$14);
				object_init_ex(&_19$$14, phalcon_acl_exception_ce);
				ZEPHIR_INIT_VAR(&_20$$14);
				ZEPHIR_CONCAT_SVSVS(&_20$$14, "Access '", access, "' does not exist in component '", &componentName_zv, "'");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(NULL, &_19$$14, "__construct", &_9, 32, &_20$$14);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_19$$14, "phalcon/Acl/Adapter/Memory.zep", 881);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_INIT_NVAR(&accessKey);
		ZEPHIR_CONCAT_VSVSV(&accessKey, &roleName_zv, "!", &componentName_zv, "!", access);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_array(this_ptr, SL("access"), &accessKey, action);
		if (Z_TYPE_P(func) != IS_NULL) {
			zephir_update_property_array(this_ptr, SL("func"), &accessKey, func);
		}
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Check whether a role is allowed to access an action from a component
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, canAccess)
{
	zend_bool _8$$6, _20$$14;
	zval accessKey;
	zval usedRoleToInherits, checkRoleToInherits;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval roleName_zv, componentName_zv, access_zv, __$true, accessList, checkRoleToInherit, usedRoleToInherit, _0, _1$$6, _2$$6, *_3$$6, _4$$6, *_5$$6, _7$$6, _10$$9, _11$$9, _12$$9, _13$$9, _14$$14, _15$$14, *_16$$14, _17$$14, *_18$$14, _19$$14;
	zend_string *roleName = NULL, *componentName = NULL, *access = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&roleName_zv);
	ZVAL_UNDEF(&componentName_zv);
	ZVAL_UNDEF(&access_zv);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&accessList);
	ZVAL_UNDEF(&checkRoleToInherit);
	ZVAL_UNDEF(&usedRoleToInherit);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$14);
	ZVAL_UNDEF(&_15$$14);
	ZVAL_UNDEF(&_17$$14);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&usedRoleToInherits);
	ZVAL_UNDEF(&checkRoleToInherits);
	ZVAL_UNDEF(&accessKey);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("access", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("roleInherits", 12, 1);
	}

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(roleName)
		Z_PARAM_STR(componentName)
		Z_PARAM_STR(access)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&roleName_zv);
	ZVAL_STR_COPY(&roleName_zv, roleName);
	zephir_memory_observe(&componentName_zv);
	ZVAL_STR_COPY(&componentName_zv, componentName);
	zephir_memory_observe(&access_zv);
	ZVAL_STR_COPY(&access_zv, access);
	zephir_memory_observe(&accessList);
	zephir_read_property_cached(&accessList, this_ptr, _zephir_prop_0, 257, PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&accessKey);
	ZEPHIR_CONCAT_VSVSV(&accessKey, &roleName_zv, "!", &componentName_zv, "!", &access_zv);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_array_isset_value(&accessList, &accessKey)) {
		RETURN_CTOR(&accessKey);
	}
	ZEPHIR_INIT_NVAR(&accessKey);
	ZEPHIR_CONCAT_VSVS(&accessKey, &roleName_zv, "!", &componentName_zv, "!*");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_array_isset_value(&accessList, &accessKey)) {
		RETURN_CTOR(&accessKey);
	}
	ZEPHIR_INIT_NVAR(&accessKey);
	ZEPHIR_CONCAT_VS(&accessKey, &roleName_zv, "!*!*");
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_array_isset_value(&accessList, &accessKey)) {
		RETURN_CTOR(&accessKey);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_value(&_0, &roleName_zv)) {
		ZEPHIR_INIT_VAR(&checkRoleToInherits);
		array_init(&checkRoleToInherits);
		zephir_read_property_cached(&_1$$6, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
		zephir_memory_observe(&_2$$6);
		zephir_array_fetch(&_2$$6, &_1$$6, &roleName_zv, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 942);
		if (Z_TYPE_P(&_2$$6) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_4$$6);
			zephir_string_to_char_array(&_4$$6, &_2$$6);
			_3$$6 = &_4$$6;
		} else {
			_3$$6 = &_2$$6;
		}
		zephir_is_iterable(_3$$6, 0, "phalcon/Acl/Adapter/Memory.zep", 946);
		if (Z_TYPE_P(_3$$6) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3$$6), _5$$6)
			{
				ZEPHIR_INIT_NVAR(&usedRoleToInherit);
				ZVAL_COPY(&usedRoleToInherit, _5$$6);
				ZEPHIR_MAKE_REF(&checkRoleToInherits);
				ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_6, 149, &checkRoleToInherits, &usedRoleToInherit);
				ZEPHIR_UNREF(&checkRoleToInherits);
				zephir_check_call_status();
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _3$$6, "rewind", NULL, 0);
			zephir_check_call_status();
			_8$$6 = 1;
			while (1) {
				if (_8$$6) {
					_8$$6 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _3$$6, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_7$$6, _3$$6, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_7$$6)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&usedRoleToInherit, _3$$6, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_MAKE_REF(&checkRoleToInherits);
					ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_6, 149, &checkRoleToInherits, &usedRoleToInherit);
					ZEPHIR_UNREF(&checkRoleToInherits);
					zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&usedRoleToInherit);
		ZEPHIR_INIT_VAR(&usedRoleToInherits);
		array_init(&usedRoleToInherits);
		while (1) {
			if (!(!(ZEPHIR_IS_EMPTY(&checkRoleToInherits)))) {
				break;
			}
			ZEPHIR_MAKE_REF(&checkRoleToInherits);
			ZEPHIR_CALL_FUNCTION(&checkRoleToInherit, "array_shift", &_9, 21, &checkRoleToInherits);
			ZEPHIR_UNREF(&checkRoleToInherits);
			zephir_check_call_status();
			if (zephir_array_isset_value(&usedRoleToInherits, &checkRoleToInherit)) {
				continue;
			}
			zephir_array_update_zval(&usedRoleToInherits, &checkRoleToInherit, &__$true, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_10$$9);
			ZEPHIR_CONCAT_VSVSV(&_10$$9, &checkRoleToInherit, "!", &componentName_zv, "!", &access_zv);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&accessKey, &_10$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (zephir_array_isset_value(&accessList, &accessKey)) {
				RETURN_CTOR(&accessKey);
			}
			ZEPHIR_INIT_NVAR(&_11$$9);
			ZEPHIR_CONCAT_VSVS(&_11$$9, &checkRoleToInherit, "!", &componentName_zv, "!*");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&accessKey, &_11$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (zephir_array_isset_value(&accessList, &accessKey)) {
				RETURN_CTOR(&accessKey);
			}
			ZEPHIR_INIT_NVAR(&_12$$9);
			ZEPHIR_CONCAT_VS(&_12$$9, &checkRoleToInherit, "!*!*");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_get_strval(&accessKey, &_12$$9);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (zephir_array_isset_value(&accessList, &accessKey)) {
				RETURN_CTOR(&accessKey);
			}
			zephir_read_property_cached(&_13$$9, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
			if (zephir_array_isset_value(&_13$$9, &checkRoleToInherit)) {
				zephir_read_property_cached(&_14$$14, this_ptr, _zephir_prop_1, 251, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_15$$14);
				zephir_array_fetch(&_15$$14, &_14$$14, &checkRoleToInherit, PH_NOISY, "phalcon/Acl/Adapter/Memory.zep", 989);
				if (Z_TYPE_P(&_15$$14) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_17$$14);
					zephir_string_to_char_array(&_17$$14, &_15$$14);
					_16$$14 = &_17$$14;
				} else {
					_16$$14 = &_15$$14;
				}
				zephir_is_iterable(_16$$14, 0, "phalcon/Acl/Adapter/Memory.zep", 992);
				if (Z_TYPE_P(_16$$14) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_16$$14), _18$$14)
					{
						ZEPHIR_INIT_NVAR(&usedRoleToInherit);
						ZVAL_COPY(&usedRoleToInherit, _18$$14);
						ZEPHIR_MAKE_REF(&checkRoleToInherits);
						ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_6, 149, &checkRoleToInherits, &usedRoleToInherit);
						ZEPHIR_UNREF(&checkRoleToInherits);
						zephir_check_call_status();
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _16$$14, "rewind", NULL, 0);
					zephir_check_call_status();
					_20$$14 = 1;
					while (1) {
						if (_20$$14) {
							_20$$14 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _16$$14, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_19$$14, _16$$14, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$14)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&usedRoleToInherit, _16$$14, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_MAKE_REF(&checkRoleToInherits);
							ZEPHIR_CALL_FUNCTION(NULL, "array_push", &_6, 149, &checkRoleToInherits, &usedRoleToInherit);
							ZEPHIR_UNREF(&checkRoleToInherits);
							zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&usedRoleToInherit);
			}
		}
	}
	RETURN_MM_BOOL(0);
}

/**
 * @param array  $collection
 * @param string $element
 * @param string $elementName
 * @param string $suffix
 *
 * @throws Exception
 */
PHP_METHOD(Phalcon_Acl_Adapter_Memory, checkExists)
{
	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *element = NULL, *elementName = NULL, *suffix = NULL;
	zval *collection_param = NULL, element_zv, elementName_zv, suffix_zv, _0$$3;
	zval collection;

	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&element_zv);
	ZVAL_UNDEF(&elementName_zv);
	ZVAL_UNDEF(&suffix_zv);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZEND_PARSE_PARAMETERS_START(3, 4)
		ZEPHIR_Z_PARAM_ARRAY(collection, collection_param)
		Z_PARAM_STR(element)
		Z_PARAM_STR(elementName)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(suffix)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	collection_param = ZEND_CALL_ARG(execute_data, 1);
	zephir_get_arrval(&collection, collection_param);
	zephir_memory_observe(&element_zv);
	ZVAL_STR_COPY(&element_zv, element);
	zephir_memory_observe(&elementName_zv);
	ZVAL_STR_COPY(&elementName_zv, elementName);
	if (!suffix) {
		suffix = zend_string_init(ZEND_STRL("ACL"), 0);
		zephir_memory_observe(&suffix_zv);
		ZVAL_STR(&suffix_zv, suffix);
	} else {
		zephir_memory_observe(&suffix_zv);
	ZVAL_STR_COPY(&suffix_zv, suffix);
	}
	if (1 != zephir_array_isset_value(&collection, &element_zv)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, phalcon_acl_exception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_VSVSV(&_1$$3, &elementName_zv, " '", &element_zv, "' does not exist in the ", &suffix_zv);
		if (UNEXPECTED(EG(exception))) {
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 32, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "phalcon/Acl/Adapter/Memory.zep", 1017);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();
}

