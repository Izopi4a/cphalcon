
extern zend_class_entry *phalcon_container_exception_notfound_ce;

ZEPHIR_INIT_CLASS(Phalcon_Container_Exception_NotFound);

PHP_METHOD(Phalcon_Container_Exception_NotFound, envNotDefined);
PHP_METHOD(Phalcon_Container_Exception_NotFound, instanceNotFound);
PHP_METHOD(Phalcon_Container_Exception_NotFound, parameterNotFound);
PHP_METHOD(Phalcon_Container_Exception_NotFound, serviceNotFound);

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_notfound_envnotdefined, 0, 1, Phalcon\\Container\\Exception\\NotFound, 0)
	ZEND_ARG_TYPE_INFO(0, varname, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_notfound_instancenotfound, 0, 1, Phalcon\\Container\\Exception\\NotFound, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_notfound_parameternotfound, 0, 1, Phalcon\\Container\\Exception\\NotFound, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_container_exception_notfound_servicenotfound, 0, 1, Phalcon\\Container\\Exception\\NotFound, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_container_exception_notfound_method_entry) {
	PHP_ME(Phalcon_Container_Exception_NotFound, envNotDefined, arginfo_phalcon_container_exception_notfound_envnotdefined, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_NotFound, instanceNotFound, arginfo_phalcon_container_exception_notfound_instancenotfound, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_NotFound, parameterNotFound, arginfo_phalcon_container_exception_notfound_parameternotfound, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Container_Exception_NotFound, serviceNotFound, arginfo_phalcon_container_exception_notfound_servicenotfound, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
