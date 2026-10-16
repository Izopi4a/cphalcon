
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/object.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalcon.io>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Class Phalcon\Http\Link\Serializer\Header
 */
ZEPHIR_INIT_CLASS(Phalcon_Html_Link_Serializer_Header)
{
	ZEPHIR_REGISTER_CLASS(Phalcon\\Html\\Link\\Serializer, Header, phalcon, html_link_serializer_header, phalcon_html_link_serializer_header_method_entry, 0);

	zend_class_implements(phalcon_html_link_serializer_header_ce, 1, phalcon_html_link_serializer_serializerinterface_ce);
	return SUCCESS;
}

/**
 * Serializes all the passed links to a HTTP link header
 */
PHP_METHOD(Phalcon_Html_Link_Serializer_Header, serialize)
{
	zend_string *_8$$3, *_39$$17;
	zend_ulong _7$$3, _38$$17;
	zend_bool _30, _18$$3, _14$$6, _24$$12, _49$$17, _45$$20, _55$$26;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *links_param = NULL, attributes, key, link, rels, result, subValue, value, *_0, _29, _1$$3, _2$$3, _3$$3, *_4$$3, _5$$3, *_6$$3, _17$$3, _27$$3, _28$$3, *_9$$6, _10$$6, *_11$$6, _13$$6, _12$$7, _15$$8, _16$$9, *_19$$12, _20$$12, *_21$$12, _23$$12, _22$$13, _25$$14, _26$$15, _31$$17, _32$$17, _33$$17, _34$$17, *_35$$17, _36$$17, *_37$$17, _48$$17, _58$$17, _59$$17, *_40$$20, _41$$20, *_42$$20, _44$$20, _43$$21, _46$$22, _47$$23, *_50$$26, _51$$26, *_52$$26, _54$$26, _53$$27, _56$$28, _57$$29;
	zval links, elements, parts;

	ZVAL_UNDEF(&links);
	ZVAL_UNDEF(&elements);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&link);
	ZVAL_UNDEF(&rels);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&subValue);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_27$$3);
	ZVAL_UNDEF(&_28$$3);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_23$$12);
	ZVAL_UNDEF(&_22$$13);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_26$$15);
	ZVAL_UNDEF(&_31$$17);
	ZVAL_UNDEF(&_32$$17);
	ZVAL_UNDEF(&_33$$17);
	ZVAL_UNDEF(&_34$$17);
	ZVAL_UNDEF(&_36$$17);
	ZVAL_UNDEF(&_48$$17);
	ZVAL_UNDEF(&_58$$17);
	ZVAL_UNDEF(&_59$$17);
	ZVAL_UNDEF(&_41$$20);
	ZVAL_UNDEF(&_44$$20);
	ZVAL_UNDEF(&_43$$21);
	ZVAL_UNDEF(&_46$$22);
	ZVAL_UNDEF(&_47$$23);
	ZVAL_UNDEF(&_51$$26);
	ZVAL_UNDEF(&_54$$26);
	ZVAL_UNDEF(&_53$$27);
	ZVAL_UNDEF(&_56$$28);
	ZVAL_UNDEF(&_57$$29);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(links, links_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &links_param);
	zephir_get_arrval(&links, links_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_NULL(&result);
	ZEPHIR_INIT_VAR(&elements);
	array_init(&elements);
	zephir_is_iterable(&links, 0, "phalcon/Html/Link/Serializer/Header.zep", 70);
	if (Z_TYPE_P(&links) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&links), _0)
		{
			ZEPHIR_INIT_NVAR(&link);
			ZVAL_COPY(&link, _0);
			ZEPHIR_CALL_METHOD(&_1$$3, &link, "isTemplated", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE_IDENTICAL(&_1$$3)) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&attributes, &link, "getAttributes", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rels, &link, "getRels", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&parts);
			zephir_create_array(&parts, 2, 0);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "");
			zephir_array_fast_append(&parts, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			zephir_fast_join_str(&_2$$3, SL(" "), &rels);
			ZEPHIR_INIT_NVAR(&_3$$3);
			ZEPHIR_CONCAT_SVS(&_3$$3, "rel=\"", &_2$$3, "\"");
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_fast_append(&parts, &_3$$3);
			if (Z_TYPE_P(&attributes) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &attributes);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &attributes;
			}
			zephir_is_iterable(_4$$3, 0, "phalcon/Html/Link/Serializer/Header.zep", 64);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_4$$3), _7$$3, _8$$3, _6$$3)
				{
					ZEPHIR_INIT_NVAR(&key);
					if (_8$$3 != NULL) { 
						ZVAL_STR_COPY(&key, _8$$3);
					} else {
						ZVAL_LONG(&key, _7$$3);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _6$$3);
					if (Z_TYPE_P(&value) == IS_ARRAY) {
						if (Z_TYPE_P(&value) == IS_STRING) {
							ZEPHIR_INIT_NVAR(&_10$$6);
							zephir_string_to_char_array(&_10$$6, &value);
							_9$$6 = &_10$$6;
						} else {
							_9$$6 = &value;
						}
						zephir_is_iterable(_9$$6, 0, "phalcon/Html/Link/Serializer/Header.zep", 50);
						if (Z_TYPE_P(_9$$6) == IS_ARRAY) {
							ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9$$6), _11$$6)
							{
								ZEPHIR_INIT_NVAR(&subValue);
								ZVAL_COPY(&subValue, _11$$6);
								ZEPHIR_INIT_NVAR(&_12$$7);
								ZEPHIR_CONCAT_VSVS(&_12$$7, &key, "=\"", &subValue, "\"");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_append(&parts, &_12$$7, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, _9$$6, "rewind", NULL, 0);
							zephir_check_call_status();
							_14$$6 = 1;
							while (1) {
								if (_14$$6) {
									_14$$6 = 0;
								} else {
									ZEPHIR_CALL_METHOD(NULL, _9$$6, "next", NULL, 0);
									zephir_check_call_status();
								}
								ZEPHIR_CALL_METHOD(&_13$$6, _9$$6, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_13$$6)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&subValue, _9$$6, "current", NULL, 0);
								zephir_check_call_status();
									ZEPHIR_INIT_NVAR(&_15$$8);
									ZEPHIR_CONCAT_VSVS(&_15$$8, &key, "=\"", &subValue, "\"");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_append(&parts, &_15$$8, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
							}
						}
						ZEPHIR_INIT_NVAR(&subValue);
						continue;
					}
					if (((Z_TYPE_P(&value) == IS_TRUE || Z_TYPE_P(&value) == IS_FALSE) != 1)) {
						ZEPHIR_INIT_NVAR(&_16$$9);
						ZEPHIR_CONCAT_VSVS(&_16$$9, &key, "=\"", &value, "\"");
						if (UNEXPECTED(EG(exception))) {
							ZEPHIR_MM_RESTORE();
							return;
						}
						zephir_array_append(&parts, &_16$$9, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 54);
						continue;
					}
					if (ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
						zephir_array_append(&parts, &key, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 59);
						continue;
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_18$$3 = 1;
				while (1) {
					if (_18$$3) {
						_18$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_17$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_17$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&key, _4$$3, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						if (Z_TYPE_P(&value) == IS_ARRAY) {
							if (Z_TYPE_P(&value) == IS_STRING) {
								ZEPHIR_INIT_NVAR(&_20$$12);
								zephir_string_to_char_array(&_20$$12, &value);
								_19$$12 = &_20$$12;
							} else {
								_19$$12 = &value;
							}
							zephir_is_iterable(_19$$12, 0, "phalcon/Html/Link/Serializer/Header.zep", 50);
							if (Z_TYPE_P(_19$$12) == IS_ARRAY) {
								ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_19$$12), _21$$12)
								{
									ZEPHIR_INIT_NVAR(&subValue);
									ZVAL_COPY(&subValue, _21$$12);
									ZEPHIR_INIT_NVAR(&_22$$13);
									ZEPHIR_CONCAT_VSVS(&_22$$13, &key, "=\"", &subValue, "\"");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_append(&parts, &_22$$13, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, _19$$12, "rewind", NULL, 0);
								zephir_check_call_status();
								_24$$12 = 1;
								while (1) {
									if (_24$$12) {
										_24$$12 = 0;
									} else {
										ZEPHIR_CALL_METHOD(NULL, _19$$12, "next", NULL, 0);
										zephir_check_call_status();
									}
									ZEPHIR_CALL_METHOD(&_23$$12, _19$$12, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_23$$12)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&subValue, _19$$12, "current", NULL, 0);
									zephir_check_call_status();
										ZEPHIR_INIT_NVAR(&_25$$14);
										ZEPHIR_CONCAT_VSVS(&_25$$14, &key, "=\"", &subValue, "\"");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										zephir_array_append(&parts, &_25$$14, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
								}
							}
							ZEPHIR_INIT_NVAR(&subValue);
							continue;
						}
						if (((Z_TYPE_P(&value) == IS_TRUE || Z_TYPE_P(&value) == IS_FALSE) != 1)) {
							ZEPHIR_INIT_NVAR(&_26$$15);
							ZEPHIR_CONCAT_VSVS(&_26$$15, &key, "=\"", &value, "\"");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&parts, &_26$$15, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 54);
							continue;
						}
						if (ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
							zephir_array_append(&parts, &key, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 59);
							continue;
						}
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&key);
			ZEPHIR_CALL_METHOD(&_27$$3, &link, "getHref", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_28$$3);
			zephir_fast_join_str(&_28$$3, SL("; "), &parts);
			ZEPHIR_INIT_NVAR(&_3$$3);
			ZEPHIR_CONCAT_SVSV(&_3$$3, "<", &_27$$3, ">", &_28$$3);
			if (UNEXPECTED(EG(exception))) {
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&elements, &_3$$3, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 67);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &links, "rewind", NULL, 0);
		zephir_check_call_status();
		_30 = 1;
		while (1) {
			if (_30) {
				_30 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, &links, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_29, &links, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_29)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&link, &links, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_31$$17, &link, "isTemplated", NULL, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_TRUE_IDENTICAL(&_31$$17)) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&attributes, &link, "getAttributes", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&rels, &link, "getRels", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_32$$17);
				zephir_create_array(&_32$$17, 2, 0);
				ZEPHIR_INIT_NVAR(&_33$$17);
				ZVAL_STRING(&_33$$17, "");
				zephir_array_fast_append(&_32$$17, &_33$$17);
				ZEPHIR_INIT_NVAR(&_33$$17);
				zephir_fast_join_str(&_33$$17, SL(" "), &rels);
				ZEPHIR_INIT_NVAR(&_34$$17);
				ZEPHIR_CONCAT_SVS(&_34$$17, "rel=\"", &_33$$17, "\"");
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_fast_append(&_32$$17, &_34$$17);
				ZEPHIR_CPY_WRT(&parts, &_32$$17);
				if (Z_TYPE_P(&attributes) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_36$$17);
					zephir_string_to_char_array(&_36$$17, &attributes);
					_35$$17 = &_36$$17;
				} else {
					_35$$17 = &attributes;
				}
				zephir_is_iterable(_35$$17, 0, "phalcon/Html/Link/Serializer/Header.zep", 64);
				if (Z_TYPE_P(_35$$17) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_35$$17), _38$$17, _39$$17, _37$$17)
					{
						ZEPHIR_INIT_NVAR(&key);
						if (_39$$17 != NULL) { 
							ZVAL_STR_COPY(&key, _39$$17);
						} else {
							ZVAL_LONG(&key, _38$$17);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _37$$17);
						if (Z_TYPE_P(&value) == IS_ARRAY) {
							if (Z_TYPE_P(&value) == IS_STRING) {
								ZEPHIR_INIT_NVAR(&_41$$20);
								zephir_string_to_char_array(&_41$$20, &value);
								_40$$20 = &_41$$20;
							} else {
								_40$$20 = &value;
							}
							zephir_is_iterable(_40$$20, 0, "phalcon/Html/Link/Serializer/Header.zep", 50);
							if (Z_TYPE_P(_40$$20) == IS_ARRAY) {
								ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_40$$20), _42$$20)
								{
									ZEPHIR_INIT_NVAR(&subValue);
									ZVAL_COPY(&subValue, _42$$20);
									ZEPHIR_INIT_NVAR(&_43$$21);
									ZEPHIR_CONCAT_VSVS(&_43$$21, &key, "=\"", &subValue, "\"");
									if (UNEXPECTED(EG(exception))) {
										ZEPHIR_MM_RESTORE();
										return;
									}
									zephir_array_append(&parts, &_43$$21, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, _40$$20, "rewind", NULL, 0);
								zephir_check_call_status();
								_45$$20 = 1;
								while (1) {
									if (_45$$20) {
										_45$$20 = 0;
									} else {
										ZEPHIR_CALL_METHOD(NULL, _40$$20, "next", NULL, 0);
										zephir_check_call_status();
									}
									ZEPHIR_CALL_METHOD(&_44$$20, _40$$20, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_44$$20)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&subValue, _40$$20, "current", NULL, 0);
									zephir_check_call_status();
										ZEPHIR_INIT_NVAR(&_46$$22);
										ZEPHIR_CONCAT_VSVS(&_46$$22, &key, "=\"", &subValue, "\"");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										zephir_array_append(&parts, &_46$$22, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
								}
							}
							ZEPHIR_INIT_NVAR(&subValue);
							continue;
						}
						if (((Z_TYPE_P(&value) == IS_TRUE || Z_TYPE_P(&value) == IS_FALSE) != 1)) {
							ZEPHIR_INIT_NVAR(&_47$$23);
							ZEPHIR_CONCAT_VSVS(&_47$$23, &key, "=\"", &value, "\"");
							if (UNEXPECTED(EG(exception))) {
								ZEPHIR_MM_RESTORE();
								return;
							}
							zephir_array_append(&parts, &_47$$23, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 54);
							continue;
						}
						if (ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
							zephir_array_append(&parts, &key, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 59);
							continue;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _35$$17, "rewind", NULL, 0);
					zephir_check_call_status();
					_49$$17 = 1;
					while (1) {
						if (_49$$17) {
							_49$$17 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _35$$17, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_48$$17, _35$$17, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_48$$17)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&key, _35$$17, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, _35$$17, "current", NULL, 0);
						zephir_check_call_status();
							if (Z_TYPE_P(&value) == IS_ARRAY) {
								if (Z_TYPE_P(&value) == IS_STRING) {
									ZEPHIR_INIT_NVAR(&_51$$26);
									zephir_string_to_char_array(&_51$$26, &value);
									_50$$26 = &_51$$26;
								} else {
									_50$$26 = &value;
								}
								zephir_is_iterable(_50$$26, 0, "phalcon/Html/Link/Serializer/Header.zep", 50);
								if (Z_TYPE_P(_50$$26) == IS_ARRAY) {
									ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_50$$26), _52$$26)
									{
										ZEPHIR_INIT_NVAR(&subValue);
										ZVAL_COPY(&subValue, _52$$26);
										ZEPHIR_INIT_NVAR(&_53$$27);
										ZEPHIR_CONCAT_VSVS(&_53$$27, &key, "=\"", &subValue, "\"");
										if (UNEXPECTED(EG(exception))) {
											ZEPHIR_MM_RESTORE();
											return;
										}
										zephir_array_append(&parts, &_53$$27, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
									} ZEND_HASH_FOREACH_END();
								} else {
									ZEPHIR_CALL_METHOD(NULL, _50$$26, "rewind", NULL, 0);
									zephir_check_call_status();
									_55$$26 = 1;
									while (1) {
										if (_55$$26) {
											_55$$26 = 0;
										} else {
											ZEPHIR_CALL_METHOD(NULL, _50$$26, "next", NULL, 0);
											zephir_check_call_status();
										}
										ZEPHIR_CALL_METHOD(&_54$$26, _50$$26, "valid", NULL, 0);
										zephir_check_call_status();
										if (!zend_is_true(&_54$$26)) {
											break;
										}
										ZEPHIR_CALL_METHOD(&subValue, _50$$26, "current", NULL, 0);
										zephir_check_call_status();
											ZEPHIR_INIT_NVAR(&_56$$28);
											ZEPHIR_CONCAT_VSVS(&_56$$28, &key, "=\"", &subValue, "\"");
											if (UNEXPECTED(EG(exception))) {
												ZEPHIR_MM_RESTORE();
												return;
											}
											zephir_array_append(&parts, &_56$$28, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 48);
									}
								}
								ZEPHIR_INIT_NVAR(&subValue);
								continue;
							}
							if (((Z_TYPE_P(&value) == IS_TRUE || Z_TYPE_P(&value) == IS_FALSE) != 1)) {
								ZEPHIR_INIT_NVAR(&_57$$29);
								ZEPHIR_CONCAT_VSVS(&_57$$29, &key, "=\"", &value, "\"");
								if (UNEXPECTED(EG(exception))) {
									ZEPHIR_MM_RESTORE();
									return;
								}
								zephir_array_append(&parts, &_57$$29, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 54);
								continue;
							}
							if (ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
								zephir_array_append(&parts, &key, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 59);
								continue;
							}
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&key);
				ZEPHIR_CALL_METHOD(&_58$$17, &link, "getHref", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_59$$17);
				zephir_fast_join_str(&_59$$17, SL("; "), &parts);
				ZEPHIR_INIT_NVAR(&_34$$17);
				ZEPHIR_CONCAT_SVSV(&_34$$17, "<", &_58$$17, ">", &_59$$17);
				if (UNEXPECTED(EG(exception))) {
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&elements, &_34$$17, PH_SEPARATE, "phalcon/Html/Link/Serializer/Header.zep", 67);
		}
	}
	ZEPHIR_INIT_NVAR(&link);
	if (zephir_fast_count_int(&elements) > 0) {
		ZEPHIR_INIT_NVAR(&result);
		zephir_fast_join_str(&result, SL(","), &elements);
	}
	RETURN_CCTOR(&result);
}

