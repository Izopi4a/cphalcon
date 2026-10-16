
extern zend_class_entry *phalcon_mvc_view_engine_volt_dependencies_ce;

ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Dependencies);

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Dependencies, read);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Dependencies, staleReason);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Dependencies, write);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_dependencies_read, 0, 1, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, compiledPath, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_dependencies_stalereason, 0, 2, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, compiledPath, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, signature, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_dependencies_write, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, compiledPath, IS_STRING, 0)
	ZEND_ARG_ARRAY_INFO(0, files, 0)
	ZEND_ARG_TYPE_INFO(0, signature, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_mvc_view_engine_volt_dependencies_method_entry) {
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Dependencies, read, arginfo_phalcon_mvc_view_engine_volt_dependencies_read, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Dependencies, staleReason, arginfo_phalcon_mvc_view_engine_volt_dependencies_stalereason, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Dependencies, write, arginfo_phalcon_mvc_view_engine_volt_dependencies_write, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
