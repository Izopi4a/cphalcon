
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/exception.h"
#include "kernel/main.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the
 * LICENSE.txt file that was distributed with this source code.
 */
/**
 * Allows to validate data using custom or built-in validators
 */
ZEPHIR_INIT_CLASS(Phalcon_Filter_Validation)
{
	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Filter, Validation, phalcon, filter_validation, phalcon_di_injectable_ce, phalcon_filter_validation_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("combinedFieldsValidators"), ZEND_ACC_PROTECTED);
	/**
	 * @var mixed
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("data"), ZEND_ACC_PROTECTED);
	/**
	 * @var object|null
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("entity"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("filters"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("whitelist"), ZEND_ACC_PROTECTED);
	/**
	 * @var array
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("labels"), ZEND_ACC_PROTECTED);
	/**
	 * @var Messages|null
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("messages"), ZEND_ACC_PROTECTED);
	/**
	 * List of validators
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("validators"), ZEND_ACC_PROTECTED);
	/**
	 * Calculated values
	 *
	 * @var array
	 */
	zend_declare_property_null(phalcon_filter_validation_ce, SL("values"), ZEND_ACC_PROTECTED);
	phalcon_filter_validation_ce->create_object = zephir_init_properties_Phalcon_Filter_Validation;

	zend_class_implements(phalcon_filter_validation_ce, 1, phalcon_filter_validation_validationinterface_ce);
	return SUCCESS;
}

/**
 * Phalcon\Filter\Validation constructor
 */
PHP_METHOD(Phalcon_Filter_Validation, __construct)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *validators_param = NULL, _0, _1, _2, _3;
	zval validators;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&validators);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("validators", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("combinedFieldsValidators", 24, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(validators, validators_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &validators_param);
	if (!validators_param) {
		ZEPHIR_INIT_VAR(&validators);
		array_init(&validators);
	} else {
		zephir_get_arrval(&validators, validators_param);
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_NVAR(&_0);
	zephir_create_closure_ex(&_0, NULL, phalcon_11__closure_ce, SL("__invoke"));
	ZEPHIR_CALL_FUNCTION(&_1, "array_filter", NULL, 16, &validators, &_0);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 518, &_1);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_INIT_NVAR(&_2);
	zephir_create_closure_ex(&_2, NULL, phalcon_12__closure_ce, SL("__invoke"));
	ZEPHIR_CALL_FUNCTION(&_3, "array_filter", NULL, 16, &validators, &_2);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 519, &_3);
	if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("initialize")) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initialize", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();
}

/**
 * Adds a validator to a field
 *
 * @param string|array       $field
 * @param ValidatorInterface $validator
 *
 * @return ValidationInterface
 */
PHP_METHOD(Phalcon_Filter_Validation, add)
{
	zend_bool _5$$5;
	zval _0$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *field, field_sub, *validator, validator_sub, singleField, *_1$$5, _2$$5, *_3$$5, _4$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_sub);
	ZVAL_UNDEF(&validator_sub);
	ZVAL_UNDEF(&singleField);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_0$$4);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(field)
		Z_PARAM_OBJECT_OF_CLASS(validator, phalcon_filter_validation_validatorinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &field, &validator);
	if (Z_TYPE_P(field) == IS_ARRAY) {
		if (zephir_instance_of_ev(validator, phalcon_filter_validation_abstractcombinedfieldsvalidator_ce)) {
			ZEPHIR_INIT_VAR(&_0$$4);
			zephir_create_array(&_0$$4, 2, 0);
			zephir_array_fast_append(&_0$$4, field);
			zephir_array_fast_append(&_0$$4, validator);
			zephir_update_property_array_append(this_ptr, SL("combinedFieldsValidators"), &_0$$4);
		} else {
			if (Z_TYPE_P(field) == IS_STRING) {
				ZEPHIR_INIT_VAR(&_2$$5);
				zephir_string_to_char_array(&_2$$5, field);
				_1$$5 = &_2$$5;
			} else {
				_1$$5 = field;
			}
			zephir_is_iterable(_1$$5, 0, "phalcon/Filter/Validation.zep", 125);
			if (Z_TYPE_P(_1$$5) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1$$5), _3$$5)
				{
					ZEPHIR_INIT_NVAR(&singleField);
					ZVAL_COPY(&singleField, _3$$5);
					zephir_update_property_array_multi(this_ptr, SL("validators"), validator, SL("za"), 2, &singleField);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1$$5, "rewind", NULL, 0);
				zephir_check_call_status();
				_5$$5 = 1;
				while (1) {
					if (_5$$5) {
						_5$$5 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _1$$5, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_4$$5, _1$$5, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&singleField, _1$$5, "current", NULL, 0);
					zephir_check_call_status();
						zephir_update_property_array_multi(this_ptr, SL("validators"), validator, SL("za"), 2, &singleField);
				}
			}
			ZEPHIR_INIT_NVAR(&singleField);
		}
	} else if (Z_TYPE_P(field) == IS_STRING) {
		zephir_update_property_array_multi(this_ptr, SL("validators"), validator, SL("za"), 2, field);
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "Field must be passed as array of fields or string", "phalcon/Filter/Validation.zep", 131);
		return;
	}
	RETURN_THIS();
}

/**
 * Appends a message to the messages list
 *
 * @param MessageInterface $message
 */
PHP_METHOD(Phalcon_Filter_Validation, appendMessage)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *message, message_sub, messages, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&message_sub);
	ZVAL_UNDEF(&messages);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("messages", 8, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(message, phalcon_messages_messageinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &message);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 520, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&messages, &_0);
	if (Z_TYPE_P(&messages) != IS_OBJECT) {
		ZEPHIR_INIT_NVAR(&messages);
		object_init_ex(&messages, phalcon_messages_messages_ce);
		ZEPHIR_CALL_METHOD(NULL, &messages, "__construct", NULL, 10);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, &messages, "appendMessage", NULL, 323, message);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 520, &messages);
	RETURN_THIS();
}

/**
 * Assigns the data to an entity
 * The entity is used to obtain the validation values
 *
 * ```php
 * $entity = new Author();
 * $fields = ['name', 'email', 'imageUrl'];
 * $validation = new AuthorValidation();
 * $validation->bind($entity, $_POST, $fields);
 * $validation->validate();
 * ```
 *
 * @param object $entity the entity object to assign data to
 * @param array|object $data the data that needs to be validated
 * @param array $whitelist only allow these fields to be mutated when entity is used
 */
PHP_METHOD(Phalcon_Filter_Validation, bind)
{
	zend_string *_10;
	zend_ulong _9;
	zend_bool _0, _1, _2, _21, _11$$8, _22$$14;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_13 = NULL, *_19 = NULL, *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval whitelist;
	zval *entity, entity_sub, *data, data_sub, *whitelist_param = NULL, container, field, value, fieldFilters, filterService, filters, method, _3, _4, _6, *_7, *_8, _20, _5$$7, _14$$8, _15$$8, _16$$8, _17$$8, _18$$8, _12$$10, _25$$14, _26$$14, _27$$14, _28$$14, _29$$14, _23$$16;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&entity_sub);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&fieldFilters);
	ZVAL_UNDEF(&filterService);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_26$$14);
	ZVAL_UNDEF(&_27$$14);
	ZVAL_UNDEF(&_28$$14);
	ZVAL_UNDEF(&_29$$14);
	ZVAL_UNDEF(&_23$$16);
	ZVAL_UNDEF(&whitelist);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("data", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("whitelist", 9, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("filters", 7, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("entity", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_ZVAL(entity)
		Z_PARAM_ZVAL(data)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(whitelist, whitelist_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &entity, &data, &whitelist_param);
	if (!whitelist_param) {
		ZEPHIR_INIT_VAR(&whitelist);
		array_init(&whitelist);
	} else {
		zephir_get_arrval(&whitelist, whitelist_param);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 521, data);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setEntity", NULL, 0, entity);
	zephir_check_call_status();
	_0 = Z_TYPE_P(data) != IS_ARRAY;
	if (_0) {
		_0 = Z_TYPE_P(data) != IS_OBJECT;
	}
	_1 = _0;
	if (!(_1)) {
		_1 = (Z_TYPE_P(entity) == IS_NULL);
	}
	_2 = _1;
	if (!(_2)) {
		_2 = ZEPHIR_IS_EMPTY(data);
	}
	if (UNEXPECTED(_2)) {
		RETURN_THIS();
	}
	ZEPHIR_CALL_METHOD(&container, this_ptr, "getDI", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&container) == IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&container) == IS_NULL) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "A dependency injection container is required to access the 'filter' service", "phalcon/Filter/Validation.zep", 194);
			return;
		}
	}
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "filter");
	ZEPHIR_CALL_METHOD(&_3, &container, "getShared", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&filterService, &_3);
	if (UNEXPECTED(Z_TYPE_P(&filterService) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "Returned 'filter' service is invalid", "phalcon/Filter/Validation.zep", 199);
		return;
	}
	if (ZEPHIR_IS_EMPTY(&whitelist)) {
		zephir_read_property_cached(&_5$$7, this_ptr, _zephir_prop_1, 522, PH_NOISY_CC | PH_READONLY);
		if (UNEXPECTED(Z_TYPE_P(&_5$$7) != IS_ARRAY)) {
			zephir_throw_variable_type_error(&_5$$7, "whitelist", "array");
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CPY_WRT(&whitelist, &_5$$7);
	}
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_2, 523, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&filters, &_6);
	if (Z_TYPE_P(data) == IS_STRING) {
		ZEPHIR_INIT_NVAR(&_4);
		zephir_string_to_char_array(&_4, data);
		_7 = &_4;
	} else {
		_7 = data;
	}
	zephir_is_iterable(_7, 0, "phalcon/Filter/Validation.zep", 233);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _9, _10, _8)
		{
			ZEPHIR_INIT_NVAR(&field);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&field, _10);
			} else {
				ZVAL_LONG(&field, _9);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _8);
			_11$$8 = !(ZEPHIR_IS_EMPTY(&whitelist));
			if (_11$$8) {
				_11$$8 = !(zephir_fast_in_array(&field, &whitelist));
			}
			if (_11$$8) {
				continue;
			}
			ZEPHIR_OBS_NVAR(&fieldFilters);
			if (zephir_array_isset_fetch(&fieldFilters, &filters, &field, 0)) {
				ZEPHIR_CALL_METHOD(&_12$$10, &filterService, "sanitize", &_13, 0, &value, &fieldFilters);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&value, &_12$$10);
			}
			ZEPHIR_INIT_NVAR(&_14$$8);
			zephir_camelize(&_14$$8, &field, NULL );
			ZEPHIR_INIT_NVAR(&method);
			ZEPHIR_CONCAT_SV(&method, "set", &_14$$8);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_read_property_cached(&_15$$8, this_ptr, _zephir_prop_3, 524, PH_NOISY_CC | PH_READONLY);
			if ((zephir_method_exists(&_15$$8, &method)  == SUCCESS)) {
				ZEPHIR_CALL_METHOD_ZVAL(NULL, entity, &method, NULL, 0, &value);
				zephir_check_call_status();
			} else {
				zephir_read_property_cached(&_16$$8, this_ptr, _zephir_prop_3, 524, PH_NOISY_CC | PH_READONLY);
				if ((zephir_method_exists_ex(&_16$$8, ZEND_STRL("writeattribute")) == SUCCESS)) {
					ZEPHIR_CALL_METHOD(NULL, entity, "writeAttribute", NULL, 0, &field, &value);
					zephir_check_call_status();
				} else {
					zephir_read_property_cached(&_17$$8, this_ptr, _zephir_prop_3, 524, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_CALL_FUNCTION(&_18$$8, "property_exists", &_19, 324, &_17$$8, &field);
					zephir_check_call_status();
					if (zephir_is_true(&_18$$8)) {
						zephir_update_property_zval_zval(entity, &field, &value);
					}
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_21 = 1;
		while (1) {
			if (_21) {
				_21 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_20, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_20)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, _7, "current", NULL, 0);
			zephir_check_call_status();
				_22$$14 = !(ZEPHIR_IS_EMPTY(&whitelist));
				if (_22$$14) {
					_22$$14 = !(zephir_fast_in_array(&field, &whitelist));
				}
				if (_22$$14) {
					continue;
				}
				ZEPHIR_OBS_NVAR(&fieldFilters);
				if (zephir_array_isset_fetch(&fieldFilters, &filters, &field, 0)) {
					ZEPHIR_CALL_METHOD(&_23$$16, &filterService, "sanitize", &_24, 0, &value, &fieldFilters);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&value, &_23$$16);
				}
				ZEPHIR_INIT_NVAR(&_25$$14);
				zephir_camelize(&_25$$14, &field, NULL );
				ZEPHIR_INIT_NVAR(&method);
				ZEPHIR_CONCAT_SV(&method, "set", &_25$$14);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_read_property_cached(&_26$$14, this_ptr, _zephir_prop_3, 524, PH_NOISY_CC | PH_READONLY);
				if ((zephir_method_exists(&_26$$14, &method)  == SUCCESS)) {
					ZEPHIR_CALL_METHOD_ZVAL(NULL, entity, &method, NULL, 0, &value);
					zephir_check_call_status();
				} else {
					zephir_read_property_cached(&_27$$14, this_ptr, _zephir_prop_3, 524, PH_NOISY_CC | PH_READONLY);
					if ((zephir_method_exists_ex(&_27$$14, ZEND_STRL("writeattribute")) == SUCCESS)) {
						ZEPHIR_CALL_METHOD(NULL, entity, "writeAttribute", NULL, 0, &field, &value);
						zephir_check_call_status();
					} else {
						zephir_read_property_cached(&_28$$14, this_ptr, _zephir_prop_3, 524, PH_NOISY_CC | PH_READONLY);
						ZEPHIR_CALL_FUNCTION(&_29$$14, "property_exists", &_19, 324, &_28$$14, &field);
						zephir_check_call_status();
						if (zephir_is_true(&_29$$14)) {
							zephir_update_property_zval_zval(entity, &field, &value);
						}
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&field);
	RETURN_THIS();
}

/**
 * @return mixed
 */
PHP_METHOD(Phalcon_Filter_Validation, getData)
{

	RETURN_MEMBER(getThis(), "data");
}

/**
 * Returns the bound entity
 *
 * @return object
 */
PHP_METHOD(Phalcon_Filter_Validation, getEntity)
{

	RETURN_MEMBER(getThis(), "entity");
}

/**
 * Returns all the filters or a specific one
 */
PHP_METHOD(Phalcon_Filter_Validation, getFilters)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval field_zv, filters, fieldFilters, _0;
	zend_string *field = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_zv);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&fieldFilters);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("filters", 7, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(field)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	if (!field) {
		ZEPHIR_INIT_VAR(&field_zv);
	} else {
		zephir_memory_observe(&field_zv);
	ZVAL_STR_COPY(&field_zv, field);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 523, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&filters, &_0);
	if (!(!(ZEPHIR_IS_EMPTY(&field_zv)))) {
		RETURN_CCTOR(&filters);
	}
	zephir_memory_observe(&fieldFilters);
	if (!(zephir_array_isset_fetch(&fieldFilters, &filters, &field_zv, 0))) {
		RETURN_MM_NULL();
	}
	RETURN_CCTOR(&fieldFilters);
}

/**
 * Get label for field
 *
 * @param string field
 */
PHP_METHOD(Phalcon_Filter_Validation, getLabel)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *field, field_sub, labels, value, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_sub);
	ZVAL_UNDEF(&labels);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("labels", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(field)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &field);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 525, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&labels, &_0);
	if (Z_TYPE_P(field) == IS_ARRAY) {
		zephir_fast_join_str(return_value, SL(", "), field);
		RETURN_MM();
	}
	zephir_memory_observe(&value);
	if (zephir_array_isset_fetch(&value, &labels, field, 0)) {
		RETURN_CCTOR(&value);
	}
	RETVAL_ZVAL(field, 1, 0);
	RETURN_MM();
}

/**
 * Returns the registered validators
 */
PHP_METHOD(Phalcon_Filter_Validation, getMessages)
{

	RETURN_MEMBER(getThis(), "messages");
}

/**
 * Returns the validators added to the validation
 */
PHP_METHOD(Phalcon_Filter_Validation, getValidators)
{

	RETURN_MEMBER_TYPED(getThis(), "validators", IS_ARRAY);
}

/**
 * Gets the a value to validate in the object entity source
 *
 * @param mixed $entity
 * @param string $field
 */
PHP_METHOD(Phalcon_Filter_Validation, getValueByEntity)
{
	zval method;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_string *field = NULL;
	zval *entity, entity_sub, field_zv, _0, _1, _2$$5;

	ZVAL_UNDEF(&entity_sub);
	ZVAL_UNDEF(&field_zv);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&method);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(entity)
		Z_PARAM_STR(field)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	entity = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&field_zv);
	ZVAL_STR_COPY(&field_zv, field);
	ZEPHIR_INIT_VAR(&_0);
	zephir_camelize(&_0, &field_zv, NULL );
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SV(&_1, "get", &_0);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&method, &_1);
	if (UNEXPECTED(EG(exception))) {
		ZEPHIR_MM_RESTORE();
		return;
	}
	if ((zephir_method_exists(entity, &method)  == SUCCESS)) {
		ZEPHIR_RETURN_CALL_METHOD_ZVAL(entity, &method, NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	if ((zephir_method_exists_ex(entity, ZEND_STRL("readattribute")) == SUCCESS)) {
		ZEPHIR_RETURN_CALL_METHOD(entity, "readAttribute", NULL, 0, &field_zv);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_isset_property_value_zval(entity, &field_zv)) {
		zephir_memory_observe(&_2$$5);
		zephir_read_property_zval(&_2$$5, entity, &field_zv, PH_NOISY_CC);
		RETURN_CCTOR(&_2$$5);
	}
	RETURN_MM_NULL();
}

/**
 * Gets the a value to validate in the array/object data source
 *
 * @param mixed $data
 * @param string $field
 */
PHP_METHOD(Phalcon_Filter_Validation, getValueByData)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_string *field = NULL;
	zval *data, data_sub, field_zv, value, values, _0, _1$$5, _2$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&field_zv);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$7);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("values", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(data)
		Z_PARAM_STR(field)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	data = ZEND_CALL_ARG(execute_data, 1);
	zephir_memory_observe(&field_zv);
	ZVAL_STR_COPY(&field_zv, field);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 526, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&values, &_0);
	zephir_memory_observe(&value);
	if (zephir_array_isset_fetch(&value, &values, &field_zv, 0)) {
		RETURN_CCTOR(&value);
	}
	if (Z_TYPE_P(data) == IS_ARRAY) {
		if (zephir_array_isset_value(data, &field_zv)) {
			zephir_memory_observe(&_1$$5);
			zephir_array_fetch(&_1$$5, data, &field_zv, PH_NOISY, "phalcon/Filter/Validation.zep", 358);
			RETURN_CCTOR(&_1$$5);
		}
	}
	if (Z_TYPE_P(data) == IS_OBJECT) {
		if (zephir_isset_property_value_zval(data, &field_zv)) {
			zephir_memory_observe(&_2$$7);
			zephir_read_property_zval(&_2$$7, data, &field_zv, PH_NOISY_CC);
			RETURN_CCTOR(&_2$$7);
		}
	}
	RETURN_MM_NULL();
}

/**
 * Gets the a value to validate in the array/object data source
 *
 * @param string $field
 */
PHP_METHOD(Phalcon_Filter_Validation, getValue)
{
	zend_bool isRawFetched = 0, _1$$5, _4$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval field_zv, entity, method, value, data, filters, fieldFilters, container, filterService, _0, _2$$9, _3$$9, _5$$13, _6$$13;
	zend_string *field = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_zv);
	ZVAL_UNDEF(&entity);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&fieldFilters);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&filterService);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$9);
	ZVAL_UNDEF(&_3$$9);
	ZVAL_UNDEF(&_5$$13);
	ZVAL_UNDEF(&_6$$13);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("entity", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("data", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("filters", 7, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(field)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_memory_observe(&field_zv);
	ZVAL_STR_COPY(&field_zv, field);
	isRawFetched = 0;
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 524, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&entity, &_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 521, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&data, &_0);
	if (Z_TYPE_P(&entity) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(&value, this_ptr, "getValueByEntity", NULL, 0, &entity, &field_zv);
		zephir_check_call_status();
		if (Z_TYPE_P(&value) == IS_NULL) {
			isRawFetched = 1;
			ZEPHIR_CALL_METHOD(&value, this_ptr, "getValueByData", NULL, 0, &data, &field_zv);
			zephir_check_call_status();
		}
	} else {
		_1$$5 = Z_TYPE_P(&data) != IS_ARRAY;
		if (_1$$5) {
			_1$$5 = Z_TYPE_P(&data) != IS_OBJECT;
		}
		if (UNEXPECTED(_1$$5)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "There is no data to validate", "phalcon/Filter/Validation.zep", 395);
			return;
		}
		ZEPHIR_CALL_METHOD(&value, this_ptr, "getValueByData", NULL, 0, &data, &field_zv);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(&value) == IS_NULL) {
		RETURN_MM_NULL();
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_2, 523, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&filters, &_0);
	zephir_memory_observe(&fieldFilters);
	if (zephir_array_isset_fetch(&fieldFilters, &filters, &field_zv, 0)) {
		if (zephir_is_true(&fieldFilters)) {
			ZEPHIR_CALL_METHOD(&container, this_ptr, "getDI", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&container) == IS_NULL) {
				ZEPHIR_CALL_CE_STATIC(&container, phalcon_di_di_ce, "getDefault", NULL, 0);
				zephir_check_call_status();
				if (Z_TYPE_P(&container) == IS_NULL) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "A dependency injection container is required to access the 'filter' service", "phalcon/Filter/Validation.zep", 416);
					return;
				}
			}
			ZEPHIR_INIT_VAR(&_3$$9);
			ZVAL_STRING(&_3$$9, "filter");
			ZEPHIR_CALL_METHOD(&_2$$9, &container, "getShared", NULL, 0, &_3$$9);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&filterService, &_2$$9);
			if (UNEXPECTED(Z_TYPE_P(&filterService) != IS_OBJECT)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "Returned 'filter' service is invalid", "phalcon/Filter/Validation.zep", 423);
				return;
			}
			ZEPHIR_CALL_METHOD(&_2$$9, &filterService, "sanitize", NULL, 0, &value, &fieldFilters);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&value, &_2$$9);
			_4$$9 = Z_TYPE_P(&entity) == IS_OBJECT;
			if (_4$$9) {
				_4$$9 = isRawFetched == 0;
			}
			if (_4$$9) {
				ZEPHIR_INIT_VAR(&_5$$13);
				zephir_camelize(&_5$$13, &field_zv, NULL );
				ZEPHIR_INIT_VAR(&method);
				ZEPHIR_CONCAT_SV(&method, "set", &_5$$13);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				if ((zephir_method_exists(&entity, &method)  == SUCCESS)) {
					ZEPHIR_CALL_METHOD_ZVAL(NULL, &entity, &method, NULL, 0, &value);
					zephir_check_call_status();
				} else if ((zephir_method_exists_ex(&entity, ZEND_STRL("writeattribute")) == SUCCESS)) {
					ZEPHIR_CALL_METHOD(NULL, &entity, "writeAttribute", NULL, 0, &field_zv, &value);
					zephir_check_call_status();
				} else {
					ZEPHIR_CALL_FUNCTION(&_6$$13, "property_exists", NULL, 324, &entity, &field_zv);
					zephir_check_call_status();
					if (zephir_is_true(&_6$$13)) {
						zephir_update_property_zval_zval(&entity, &field_zv, &value);
					}
				}
			}
			RETURN_CCTOR(&value);
		}
	}
	if (Z_TYPE_P(&entity) != IS_OBJECT) {
		zephir_update_property_array(this_ptr, SL("values"), &field_zv, &value);
	}
	RETURN_CCTOR(&value);
}

/**
 * Alias of `add` method
 *
 * @param string|array       $field
 * @param ValidatorInterface $validator
 *
 * @return ValidationInterface
 */
PHP_METHOD(Phalcon_Filter_Validation, rule)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *field, field_sub, *validator, validator_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_sub);
	ZVAL_UNDEF(&validator_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(field)
		Z_PARAM_OBJECT_OF_CLASS(validator, phalcon_filter_validation_validatorinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &field, &validator);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, 0, field, validator);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Adds the validators to a field
 */
PHP_METHOD(Phalcon_Filter_Validation, rules)
{
	zend_bool _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_1 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval validators;
	zval *field, field_sub, *validators_param = NULL, validator, *_0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_sub);
	ZVAL_UNDEF(&validator);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&validators);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(field)
		ZEPHIR_Z_PARAM_ARRAY(validators, validators_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &field, &validators_param);
	ZEPHIR_OBS_COPY_OR_DUP(&validators, validators_param);
	zephir_is_iterable(&validators, 0, "phalcon/Filter/Validation.zep", 481);
	if (Z_TYPE_P(&validators) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&validators), _0)
		{
			ZEPHIR_INIT_NVAR(&validator);
			ZVAL_COPY(&validator, _0);
			if (zephir_instance_of_ev(&validator, phalcon_filter_validation_validatorinterface_ce)) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_1, 0, field, &validator);
				zephir_check_call_status();
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &validators, "rewind", NULL, 0);
		zephir_check_call_status();
		_3 = 1;
		while (1) {
			if (_3) {
				_3 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &validators, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_2, &validators, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&validator, &validators, "current", NULL, 0);
			zephir_check_call_status();
				if (zephir_instance_of_ev(&validator, phalcon_filter_validation_validatorinterface_ce)) {
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", &_1, 0, field, &validator);
					zephir_check_call_status();
				}
		}
	}
	ZEPHIR_INIT_NVAR(&validator);
	RETURN_THIS();
}

/**
 * Sets the bound entity
 *
 * @param object entity
 */
PHP_METHOD(Phalcon_Filter_Validation, setEntity)
{
	zval *entity, entity_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&entity_sub);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("entity", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(entity)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &entity);
	if (UNEXPECTED(Z_TYPE_P(entity) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_filter_validation_exception_ce, "Entity must be an object", "phalcon/Filter/Validation.zep", 492);
		return;
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 524, entity);
}

/**
 * Adds filters to the field
 *
 * @param string field
 * @param array|string filters
 */
PHP_METHOD(Phalcon_Filter_Validation, setFilters)
{
	zend_bool _4$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *field, field_sub, *filters, filters_sub, singleField, *_0$$3, _1$$3, *_2$$3, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_sub);
	ZVAL_UNDEF(&filters_sub);
	ZVAL_UNDEF(&singleField);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(field)
		Z_PARAM_ZVAL(filters)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &field, &filters);
	if (Z_TYPE_P(field) == IS_ARRAY) {
		if (Z_TYPE_P(field) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_string_to_char_array(&_1$$3, field);
			_0$$3 = &_1$$3;
		} else {
			_0$$3 = field;
		}
		zephir_is_iterable(_0$$3, 0, "phalcon/Filter/Validation.zep", 512);
		if (Z_TYPE_P(_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$3), _2$$3)
			{
				ZEPHIR_INIT_NVAR(&singleField);
				ZVAL_COPY(&singleField, _2$$3);
				zephir_update_property_array(this_ptr, SL("filters"), &singleField, filters);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _0$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_4$$3 = 1;
			while (1) {
				if (_4$$3) {
					_4$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _0$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_3$$3, _0$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_3$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&singleField, _0$$3, "current", NULL, 0);
				zephir_check_call_status();
					zephir_update_property_array(this_ptr, SL("filters"), &singleField, filters);
			}
		}
		ZEPHIR_INIT_NVAR(&singleField);
	} else if (Z_TYPE_P(field) == IS_STRING) {
		zephir_update_property_array(this_ptr, SL("filters"), field, filters);
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "Field must be passed as array of fields or string.", "phalcon/Filter/Validation.zep", 517);
		return;
	}
	RETURN_THIS();
}

/**
 * Adds labels for fields
 */
PHP_METHOD(Phalcon_Filter_Validation, setLabels)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *labels_param = NULL;
	zval labels;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&labels);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("labels", 6, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(labels, labels_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &labels_param);
	ZEPHIR_OBS_COPY_OR_DUP(&labels, labels_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 525, &labels);
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Phalcon_Filter_Validation, setValidators)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *validators_param = NULL;
	zval validators;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&validators);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("validators", 10, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(validators, validators_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &validators_param);
	zephir_get_arrval(&validators, validators_param);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 518, &validators);
	RETURN_THIS();
}

/**
 * Validate a set of data according to a set of rules
 *
 * You can use $validation->bind(entity, data, whitelist)->validate()
 * When you use bind(), the this->data is already set, so you can reuse it here
 *
 * ```php
 * // using bind() with $whitelist fields
 * $entity = new Author();
 * $fields = ['name', 'email', 'imageUrl'];
 * $validation = new AuthorValidation();
 * $validation->bind($entity, $_POST, $fields);
 * $validation->validate();
 *
 * // directly using validate
 * $validation = new AuthorValidation();
 * $validation->validate($_POST, $entity, $fields);
 * ```
 *
 * @param array|object $data the data that needs to be validated
 * @param object $entity the entity object to assign data to
 * @param array $whitelist only allow these fields to be mutated when entity is used
 *
 * @return Messages|false
 */
PHP_METHOD(Phalcon_Filter_Validation, validate)
{
	zend_bool _26, _48, _3$$4, _20$$10, _35$$21;
	zend_string *_10;
	zend_ulong _9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval whitelist;
	zval *data = NULL, data_sub, *entity = NULL, entity_sub, *whitelist_param = NULL, __$null, combinedFieldsValidators, field, scope, status, validator, validatorData, validators, inputData, _0, _1, _2, *_6, _7, *_8, _25, *_40, _41, *_42, _47, _4$$8, _5$$8, *_11$$10, _12$$10, *_13$$10, _19$$10, _14$$11, _16$$11, _17$$14, _18$$14, _21$$16, _22$$16, _23$$19, _24$$19, *_27$$21, _28$$21, *_29$$21, _34$$21, _30$$22, _31$$22, _32$$25, _33$$25, _36$$27, _37$$27, _38$$30, _39$$30, _43$$32, _44$$32, _45$$36, _46$$36, _49$$38, _50$$38, _51$$42, _52$$42, _53$$44, _54$$44;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&entity_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&combinedFieldsValidators);
	ZVAL_UNDEF(&field);
	ZVAL_UNDEF(&scope);
	ZVAL_UNDEF(&status);
	ZVAL_UNDEF(&validator);
	ZVAL_UNDEF(&validatorData);
	ZVAL_UNDEF(&validators);
	ZVAL_UNDEF(&inputData);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_47);
	ZVAL_UNDEF(&_4$$8);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$14);
	ZVAL_UNDEF(&_18$$14);
	ZVAL_UNDEF(&_21$$16);
	ZVAL_UNDEF(&_22$$16);
	ZVAL_UNDEF(&_23$$19);
	ZVAL_UNDEF(&_24$$19);
	ZVAL_UNDEF(&_28$$21);
	ZVAL_UNDEF(&_34$$21);
	ZVAL_UNDEF(&_30$$22);
	ZVAL_UNDEF(&_31$$22);
	ZVAL_UNDEF(&_32$$25);
	ZVAL_UNDEF(&_33$$25);
	ZVAL_UNDEF(&_36$$27);
	ZVAL_UNDEF(&_37$$27);
	ZVAL_UNDEF(&_38$$30);
	ZVAL_UNDEF(&_39$$30);
	ZVAL_UNDEF(&_43$$32);
	ZVAL_UNDEF(&_44$$32);
	ZVAL_UNDEF(&_45$$36);
	ZVAL_UNDEF(&_46$$36);
	ZVAL_UNDEF(&_49$$38);
	ZVAL_UNDEF(&_50$$38);
	ZVAL_UNDEF(&_51$$42);
	ZVAL_UNDEF(&_52$$42);
	ZVAL_UNDEF(&_53$$44);
	ZVAL_UNDEF(&_54$$44);
	ZVAL_UNDEF(&whitelist);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	static zend_string *_zephir_prop_3 = NULL;
	static zend_string *_zephir_prop_4 = NULL;
	static zend_string *_zephir_prop_5 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("validators", 10, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("combinedFieldsValidators", 24, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("values", 6, 1);
	}
	if (UNEXPECTED(!_zephir_prop_3)) {
		_zephir_prop_3 = zend_string_init("messages", 8, 1);
	}
	if (UNEXPECTED(!_zephir_prop_4)) {
		_zephir_prop_4 = zend_string_init("data", 4, 1);
	}
	if (UNEXPECTED(!_zephir_prop_5)) {
		_zephir_prop_5 = zend_string_init("entity", 6, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(data)
		Z_PARAM_ZVAL_OR_NULL(entity)
		ZEPHIR_Z_PARAM_ARRAY(whitelist, whitelist_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 3, &data, &entity, &whitelist_param);
	if (!data) {
		data = &data_sub;
		data = &__$null;
	}
	if (!entity) {
		entity = &entity_sub;
		entity = &__$null;
	}
	if (!whitelist_param) {
		ZEPHIR_INIT_VAR(&whitelist);
		array_init(&whitelist);
	} else {
		zephir_get_arrval(&whitelist, whitelist_param);
	}
	ZEPHIR_INIT_VAR(&inputData);
	ZVAL_NULL(&inputData);
	zephir_memory_observe(&validatorData);
	zephir_read_property_cached(&validatorData, this_ptr, _zephir_prop_0, 518, PH_NOISY_CC);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 519, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&combinedFieldsValidators, &_0);
	if (UNEXPECTED(Z_TYPE_P(&validatorData) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "There are no validators to validate", "phalcon/Filter/Validation.zep", 572);
		return;
	}
	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 526, &_1);
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, phalcon_messages_messages_ce);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 10);
	zephir_check_call_status();
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_3, 520, &_2);
	if (Z_TYPE_P(data) != IS_NULL) {
		_3$$4 = Z_TYPE_P(data) != IS_ARRAY;
		if (_3$$4) {
			_3$$4 = Z_TYPE_P(data) != IS_OBJECT;
		}
		if (UNEXPECTED(_3$$4)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "Invalid data to validate", "phalcon/Filter/Validation.zep", 587);
			return;
		}
		zephir_update_property_zval_cached(this_ptr, _zephir_prop_4, 521, data);
		ZEPHIR_CPY_WRT(&inputData, data);
	} else {
		zephir_read_property_cached(&_0, this_ptr, _zephir_prop_4, 521, PH_NOISY_CC | PH_READONLY);
		if (!(ZEPHIR_IS_EMPTY(&_0))) {
			ZEPHIR_OBS_NVAR(&inputData);
			zephir_read_property_cached(&inputData, this_ptr, _zephir_prop_4, 521, PH_NOISY_CC);
		}
	}
	if (Z_TYPE_P(entity) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "bind", NULL, 0, entity, &inputData, &whitelist);
		zephir_check_call_status();
	}
	if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("beforevalidation")) == SUCCESS)) {
		zephir_read_property_cached(&_4$$8, this_ptr, _zephir_prop_5, 524, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_5$$8, this_ptr, _zephir_prop_3, 520, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&status, this_ptr, "beforeValidation", NULL, 0, &inputData, &_4$$8, &_5$$8);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&status)) {
			RETURN_CCTOR(&status);
		}
	}
	if (Z_TYPE_P(&validatorData) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_7);
		zephir_string_to_char_array(&_7, &validatorData);
		_6 = &_7;
	} else {
		_6 = &validatorData;
	}
	zephir_is_iterable(_6, 0, "phalcon/Filter/Validation.zep", 637);
	if (Z_TYPE_P(_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_6), _9, _10, _8)
		{
			ZEPHIR_INIT_NVAR(&field);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&field, _10);
			} else {
				ZVAL_LONG(&field, _9);
			}
			ZEPHIR_INIT_NVAR(&validators);
			ZVAL_COPY(&validators, _8);
			if (Z_TYPE_P(&validators) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_12$$10);
				zephir_string_to_char_array(&_12$$10, &validators);
				_11$$10 = &_12$$10;
			} else {
				_11$$10 = &validators;
			}
			zephir_is_iterable(_11$$10, 0, "phalcon/Filter/Validation.zep", 635);
			if (Z_TYPE_P(_11$$10) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_11$$10), _13$$10)
				{
					ZEPHIR_INIT_NVAR(&validator);
					ZVAL_COPY(&validator, _13$$10);
					if (UNEXPECTED(Z_TYPE_P(&validator) != IS_OBJECT)) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "One of the validators is not valid", "phalcon/Filter/Validation.zep", 615);
						return;
					}
					ZEPHIR_CALL_METHOD(&_14$$11, this_ptr, "preChecking", &_15, 0, &field, &validator);
					zephir_check_call_status();
					if (zephir_is_true(&_14$$11)) {
						continue;
					}
					ZEPHIR_CALL_METHOD(&_16$$11, &validator, "validate", NULL, 0, this_ptr, &field);
					zephir_check_call_status();
					if (ZEPHIR_IS_FALSE_IDENTICAL(&_16$$11)) {
						ZEPHIR_INIT_NVAR(&_18$$14);
						ZVAL_STRING(&_18$$14, "cancelOnFail");
						ZEPHIR_CALL_METHOD(&_17$$14, &validator, "getOption", NULL, 0, &_18$$14);
						zephir_check_call_status();
						if (zephir_is_true(&_17$$14)) {
							break;
						}
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _11$$10, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$10 = 1;
				while (1) {
					if (_20$$10) {
						_20$$10 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _11$$10, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$10, _11$$10, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$10)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&validator, _11$$10, "current", NULL, 0);
					zephir_check_call_status();
						if (UNEXPECTED(Z_TYPE_P(&validator) != IS_OBJECT)) {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "One of the validators is not valid", "phalcon/Filter/Validation.zep", 615);
							return;
						}
						ZEPHIR_CALL_METHOD(&_21$$16, this_ptr, "preChecking", &_15, 0, &field, &validator);
						zephir_check_call_status();
						if (zephir_is_true(&_21$$16)) {
							continue;
						}
						ZEPHIR_CALL_METHOD(&_22$$16, &validator, "validate", NULL, 0, this_ptr, &field);
						zephir_check_call_status();
						if (ZEPHIR_IS_FALSE_IDENTICAL(&_22$$16)) {
							ZEPHIR_INIT_NVAR(&_24$$19);
							ZVAL_STRING(&_24$$19, "cancelOnFail");
							ZEPHIR_CALL_METHOD(&_23$$19, &validator, "getOption", NULL, 0, &_24$$19);
							zephir_check_call_status();
							if (zephir_is_true(&_23$$19)) {
								break;
							}
						}
				}
			}
			ZEPHIR_INIT_NVAR(&validator);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _6, "rewind", NULL, 0);
		zephir_check_call_status();
		_26 = 1;
		while (1) {
			if (_26) {
				_26 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _6, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_25, _6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_25)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&field, _6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&validators, _6, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&validators) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_28$$21);
					zephir_string_to_char_array(&_28$$21, &validators);
					_27$$21 = &_28$$21;
				} else {
					_27$$21 = &validators;
				}
				zephir_is_iterable(_27$$21, 0, "phalcon/Filter/Validation.zep", 635);
				if (Z_TYPE_P(_27$$21) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_27$$21), _29$$21)
					{
						ZEPHIR_INIT_NVAR(&validator);
						ZVAL_COPY(&validator, _29$$21);
						if (UNEXPECTED(Z_TYPE_P(&validator) != IS_OBJECT)) {
							ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "One of the validators is not valid", "phalcon/Filter/Validation.zep", 615);
							return;
						}
						ZEPHIR_CALL_METHOD(&_30$$22, this_ptr, "preChecking", &_15, 0, &field, &validator);
						zephir_check_call_status();
						if (zephir_is_true(&_30$$22)) {
							continue;
						}
						ZEPHIR_CALL_METHOD(&_31$$22, &validator, "validate", NULL, 0, this_ptr, &field);
						zephir_check_call_status();
						if (ZEPHIR_IS_FALSE_IDENTICAL(&_31$$22)) {
							ZEPHIR_INIT_NVAR(&_33$$25);
							ZVAL_STRING(&_33$$25, "cancelOnFail");
							ZEPHIR_CALL_METHOD(&_32$$25, &validator, "getOption", NULL, 0, &_33$$25);
							zephir_check_call_status();
							if (zephir_is_true(&_32$$25)) {
								break;
							}
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _27$$21, "rewind", NULL, 0);
					zephir_check_call_status();
					_35$$21 = 1;
					while (1) {
						if (_35$$21) {
							_35$$21 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _27$$21, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_34$$21, _27$$21, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_34$$21)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&validator, _27$$21, "current", NULL, 0);
						zephir_check_call_status();
							if (UNEXPECTED(Z_TYPE_P(&validator) != IS_OBJECT)) {
								ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "One of the validators is not valid", "phalcon/Filter/Validation.zep", 615);
								return;
							}
							ZEPHIR_CALL_METHOD(&_36$$27, this_ptr, "preChecking", &_15, 0, &field, &validator);
							zephir_check_call_status();
							if (zephir_is_true(&_36$$27)) {
								continue;
							}
							ZEPHIR_CALL_METHOD(&_37$$27, &validator, "validate", NULL, 0, this_ptr, &field);
							zephir_check_call_status();
							if (ZEPHIR_IS_FALSE_IDENTICAL(&_37$$27)) {
								ZEPHIR_INIT_NVAR(&_39$$30);
								ZVAL_STRING(&_39$$30, "cancelOnFail");
								ZEPHIR_CALL_METHOD(&_38$$30, &validator, "getOption", NULL, 0, &_39$$30);
								zephir_check_call_status();
								if (zephir_is_true(&_38$$30)) {
									break;
								}
							}
					}
				}
				ZEPHIR_INIT_NVAR(&validator);
		}
	}
	ZEPHIR_INIT_NVAR(&validators);
	ZEPHIR_INIT_NVAR(&field);
	if (Z_TYPE_P(&combinedFieldsValidators) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_41);
		zephir_string_to_char_array(&_41, &combinedFieldsValidators);
		_40 = &_41;
	} else {
		_40 = &combinedFieldsValidators;
	}
	zephir_is_iterable(_40, 0, "phalcon/Filter/Validation.zep", 670);
	if (Z_TYPE_P(_40) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_40), _42)
		{
			ZEPHIR_INIT_NVAR(&scope);
			ZVAL_COPY(&scope, _42);
			if (UNEXPECTED(Z_TYPE_P(&scope) != IS_ARRAY)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "The validator scope is not valid", "phalcon/Filter/Validation.zep", 639);
				return;
			}
			ZEPHIR_OBS_NVAR(&field);
			zephir_array_fetch_long(&field, &scope, 0, PH_NOISY, "phalcon/Filter/Validation.zep", 642);
			ZEPHIR_OBS_NVAR(&validator);
			zephir_array_fetch_long(&validator, &scope, 1, PH_NOISY, "phalcon/Filter/Validation.zep", 643);
			if (UNEXPECTED(Z_TYPE_P(&validator) != IS_OBJECT)) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "One of the validators is not valid", "phalcon/Filter/Validation.zep", 646);
				return;
			}
			ZEPHIR_CALL_METHOD(&_43$$32, this_ptr, "preChecking", &_15, 0, &field, &validator);
			zephir_check_call_status();
			if (zephir_is_true(&_43$$32)) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&_44$$32, &validator, "validate", NULL, 0, this_ptr, &field);
			zephir_check_call_status();
			if (ZEPHIR_IS_FALSE_IDENTICAL(&_44$$32)) {
				ZEPHIR_INIT_NVAR(&_46$$36);
				ZVAL_STRING(&_46$$36, "cancelOnFail");
				ZEPHIR_CALL_METHOD(&_45$$36, &validator, "getOption", NULL, 0, &_46$$36);
				zephir_check_call_status();
				if (zephir_is_true(&_45$$36)) {
					break;
				}
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _40, "rewind", NULL, 0);
		zephir_check_call_status();
		_48 = 1;
		while (1) {
			if (_48) {
				_48 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _40, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_47, _40, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_47)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&scope, _40, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(Z_TYPE_P(&scope) != IS_ARRAY)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "The validator scope is not valid", "phalcon/Filter/Validation.zep", 639);
					return;
				}
				ZEPHIR_OBS_NVAR(&field);
				zephir_array_fetch_long(&field, &scope, 0, PH_NOISY, "phalcon/Filter/Validation.zep", 642);
				ZEPHIR_OBS_NVAR(&validator);
				zephir_array_fetch_long(&validator, &scope, 1, PH_NOISY, "phalcon/Filter/Validation.zep", 643);
				if (UNEXPECTED(Z_TYPE_P(&validator) != IS_OBJECT)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_filter_validation_exception_ce, "One of the validators is not valid", "phalcon/Filter/Validation.zep", 646);
					return;
				}
				ZEPHIR_CALL_METHOD(&_49$$38, this_ptr, "preChecking", &_15, 0, &field, &validator);
				zephir_check_call_status();
				if (zephir_is_true(&_49$$38)) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&_50$$38, &validator, "validate", NULL, 0, this_ptr, &field);
				zephir_check_call_status();
				if (ZEPHIR_IS_FALSE_IDENTICAL(&_50$$38)) {
					ZEPHIR_INIT_NVAR(&_52$$42);
					ZVAL_STRING(&_52$$42, "cancelOnFail");
					ZEPHIR_CALL_METHOD(&_51$$42, &validator, "getOption", NULL, 0, &_52$$42);
					zephir_check_call_status();
					if (zephir_is_true(&_51$$42)) {
						break;
					}
				}
		}
	}
	ZEPHIR_INIT_NVAR(&scope);
	if ((zephir_method_exists_ex(this_ptr, ZEND_STRL("aftervalidation")) == SUCCESS)) {
		zephir_read_property_cached(&_53$$44, this_ptr, _zephir_prop_5, 524, PH_NOISY_CC | PH_READONLY);
		zephir_read_property_cached(&_54$$44, this_ptr, _zephir_prop_3, 520, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "afterValidation", NULL, 0, &inputData, &_53$$44, &_54$$44);
		zephir_check_call_status();
	}
	RETURN_MM_MEMBER(getThis(), "messages");
}

/**
 * Verify if validation fails by verifying if there are messages in the current validation
 */
PHP_METHOD(Phalcon_Filter_Validation, fails)
{
	zend_bool _1;
	zval _0, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("messages", 8, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 520, PH_NOISY_CC | PH_READONLY);
	_1 = !(Z_TYPE_P(&_0) == IS_NULL);
	if (_1) {
		zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 520, PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_3, &_2, "count", NULL, 0);
		zephir_check_call_status();
		_1 = ZEPHIR_GT_LONG(&_3, 0);
	}
	if (UNEXPECTED(_1)) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);
}

/**
 * Internal validations, if it returns true, then skip the current validator
 *
 * @param array|string $field
 * @param ValidatorInterface $validator
 */
PHP_METHOD(Phalcon_Filter_Validation, preChecking)
{
	zend_bool _6$$3, _14$$11;
	zval results;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *field, field_sub, *validator, validator_sub, __$false, singleField, allowEmpty, emptyValue, value, *_0$$3, _1$$3, *_2$$3, _5$$3, _3$$4, _7$$6, _8$$8, _9$$8, *_10$$11, _11$$11, *_12$$11, _13$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&field_sub);
	ZVAL_UNDEF(&validator_sub);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&singleField);
	ZVAL_UNDEF(&allowEmpty);
	ZVAL_UNDEF(&emptyValue);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&results);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(field)
		Z_PARAM_OBJECT_OF_CLASS(validator, phalcon_filter_validation_validatorinterface_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &field, &validator);
	ZEPHIR_INIT_VAR(&results);
	array_init(&results);
	if (Z_TYPE_P(field) == IS_ARRAY) {
		if (Z_TYPE_P(field) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_string_to_char_array(&_1$$3, field);
			_0$$3 = &_1$$3;
		} else {
			_0$$3 = field;
		}
		zephir_is_iterable(_0$$3, 0, "phalcon/Filter/Validation.zep", 710);
		if (Z_TYPE_P(_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_0$$3), _2$$3)
			{
				ZEPHIR_INIT_NVAR(&singleField);
				ZVAL_COPY(&singleField, _2$$3);
				ZEPHIR_CALL_METHOD(&_3$$4, this_ptr, "preChecking", &_4, 325, &singleField, validator);
				zephir_check_call_status();
				zephir_array_append(&results, &_3$$4, PH_SEPARATE, "phalcon/Filter/Validation.zep", 702);
				if (zephir_fast_in_array(&__$false, &results)) {
					RETURN_MM_BOOL(0);
				}
				RETURN_MM_BOOL(1);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _0$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_6$$3 = 1;
			while (1) {
				if (_6$$3) {
					_6$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _0$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_5$$3, _0$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_5$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&singleField, _0$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_7$$6, this_ptr, "preChecking", &_4, 325, &singleField, validator);
					zephir_check_call_status();
					zephir_array_append(&results, &_7$$6, PH_SEPARATE, "phalcon/Filter/Validation.zep", 702);
					if (zephir_fast_in_array(&__$false, &results)) {
						RETURN_MM_BOOL(0);
					}
					RETURN_MM_BOOL(1);
			}
		}
		ZEPHIR_INIT_NVAR(&singleField);
	} else {
		ZEPHIR_INIT_VAR(&_8$$8);
		ZVAL_STRING(&_8$$8, "allowEmpty");
		ZVAL_BOOL(&_9$$8, 0);
		ZEPHIR_CALL_METHOD(&allowEmpty, validator, "getOption", NULL, 0, &_8$$8, &_9$$8);
		zephir_check_call_status();
		if (zephir_is_true(&allowEmpty)) {
			if ((zephir_method_exists_ex(validator, ZEND_STRL("isallowempty")) == SUCCESS)) {
				ZEPHIR_RETURN_CALL_METHOD(validator, "isAllowEmpty", NULL, 0, this_ptr, field);
				zephir_check_call_status();
				RETURN_MM();
			}
			ZEPHIR_CALL_METHOD(&value, this_ptr, "getValue", NULL, 0, field);
			zephir_check_call_status();
			if (Z_TYPE_P(&allowEmpty) == IS_ARRAY) {
				if (Z_TYPE_P(&allowEmpty) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_11$$11);
					zephir_string_to_char_array(&_11$$11, &allowEmpty);
					_10$$11 = &_11$$11;
				} else {
					_10$$11 = &allowEmpty;
				}
				zephir_is_iterable(_10$$11, 0, "phalcon/Filter/Validation.zep", 727);
				if (Z_TYPE_P(_10$$11) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_10$$11), _12$$11)
					{
						ZEPHIR_INIT_NVAR(&emptyValue);
						ZVAL_COPY(&emptyValue, _12$$11);
						if (ZEPHIR_IS_IDENTICAL(&emptyValue, &value)) {
							RETURN_MM_BOOL(1);
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _10$$11, "rewind", NULL, 0);
					zephir_check_call_status();
					_14$$11 = 1;
					while (1) {
						if (_14$$11) {
							_14$$11 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _10$$11, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_13$$11, _10$$11, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$11)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&emptyValue, _10$$11, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_IS_IDENTICAL(&emptyValue, &value)) {
								RETURN_MM_BOOL(1);
							}
					}
				}
				ZEPHIR_INIT_NVAR(&emptyValue);
				RETURN_MM_BOOL(0);
			}
			RETURN_MM_BOOL(ZEPHIR_IS_EMPTY(&value));
		}
	}
	RETURN_MM_BOOL(0);
}

zend_object *zephir_init_properties_Phalcon_Filter_Validation(zend_class_entry *class_type)
{
		zval _0, _2, _4, _6, _8, _10, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	

		ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
		zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property_ex(&_0, this_ptr, ZEND_STRL("values"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("values"), &_1$$3);
		}
		zephir_read_property_ex(&_2, this_ptr, ZEND_STRL("validators"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("validators"), &_3$$4);
		}
		zephir_read_property_ex(&_4, this_ptr, ZEND_STRL("labels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("labels"), &_5$$5);
		}
		zephir_read_property_ex(&_6, this_ptr, ZEND_STRL("whitelist"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("whitelist"), &_7$$6);
		}
		zephir_read_property_ex(&_8, this_ptr, ZEND_STRL("filters"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("filters"), &_9$$7);
		}
		zephir_read_property_ex(&_10, this_ptr, ZEND_STRL("combinedFieldsValidators"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval_ex(this_ptr, ZEND_STRL("combinedFieldsValidators"), &_11$$8);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}
}

