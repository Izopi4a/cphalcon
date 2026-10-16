
extern zend_class_entry *phalcon_container_exception_invalid_ce;

ZEPHIR_INIT_CLASS(Phalcon_Container_Exception_Invalid);

PHP_METHOD(Phalcon_Container_Exception_Invalid, cannotExtendResolved);
PHP_METHOD(Phalcon_Container_Exception_Invalid, cannotResolveParameter);
PHP_METHOD(Phalcon_Container_Exception_Invalid, circularAlias);
PHP_METHOD(Phalcon_Container_Exception_Invalid, frozenDefinition);
PHP_METHOD(Phalcon_Container_Exception_Invalid, invalidExtender);
PHP_METHOD(Phalcon_Container_Exception_Invalid, noClassSet);
PHP_METHOD(Phalcon_Container_Exception_Invalid, noFactorySet);
PHP_METHOD(Phalcon_Container_Exception_Invalid, noProcessorFound);
PHP_METHOD(Phalcon_Container_Exception_Invalid, serviceNotFound);

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_cannotextendresolved, 0, 1, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_cannotresolveparameter, 0, 2, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, className, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_circularalias, 0, 1, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_frozendefinition, 0, 1, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_invalidextender, 0, 2, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, service, IS_STRING, 0)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_noclassset, 0, 1, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_nofactoryset, 0, 1, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_noprocessorfound, 0, 0, Phalcon\\Container\\Exception\\Invalid, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_invalid_servicenotfound, 0, 1, Phalcon\\Container\\Exception\\Invalid, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_container_exception_invalid_method_entry) {
	PHP_ME(Phalcon_Container_Exception_Invalid, cannotExtendResolved, arginfo_phalcon_container_exception_invalid_cannotextendresolved, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, cannotResolveParameter, arginfo_phalcon_container_exception_invalid_cannotresolveparameter, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, circularAlias, arginfo_phalcon_container_exception_invalid_circularalias, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, frozenDefinition, arginfo_phalcon_container_exception_invalid_frozendefinition, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, invalidExtender, arginfo_phalcon_container_exception_invalid_invalidextender, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, noClassSet, arginfo_phalcon_container_exception_invalid_noclassset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, noFactorySet, arginfo_phalcon_container_exception_invalid_nofactoryset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, noProcessorFound, arginfo_phalcon_container_exception_invalid_noprocessorfound, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_Invalid, serviceNotFound, arginfo_phalcon_container_exception_invalid_servicenotfound, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
