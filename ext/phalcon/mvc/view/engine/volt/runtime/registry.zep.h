
extern zend_class_entry *phalcon_mvc_view_engine_volt_runtime_registry_ce;

ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry);

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, add);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, addExtension);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, get);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, getSignature);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, has);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, resolve);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, instance);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, isStatic);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, kindOf);
zend_object *zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Runtime_Registry(zend_class_entry *class_type);

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_add, 0, 1, Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime\\Registry, 0)
	ZEND_ARG_OBJ_INFO(0, item, Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime\\VoltCallable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_addextension, 0, 1, Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime\\Registry, 0)
	ZEND_ARG_OBJ_INFO(0, extension, Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime\\ExtensionInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_get, 0, 2, Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime\\VoltCallable, 1)
	ZEND_ARG_TYPE_INFO(0, kind, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_getsignature, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_has, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, kind, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_resolve, 0, 2, Closure, 0)
	ZEND_ARG_TYPE_INFO(0, kind, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, container, Phalcon\\Di\\DiInterface, MAY_BE_NULL, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_instance, 0, 1, MAY_BE_OBJECT)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, container, Phalcon\\Di\\DiInterface, MAY_BE_NULL, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_isstatic, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, className, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_kindof, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, item, Phalcon\\Mvc\\View\\Engine\\Volt\\Runtime\\VoltCallable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_runtime_registry_zephir_init_properties_phalcon_mvc_view_engine_volt_runtime_registry, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_mvc_view_engine_volt_runtime_registry_method_entry) {
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, add, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_add, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, addExtension, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_addextension, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, get, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_get, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, getSignature, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_getsignature, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, has, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_has, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, resolve, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_resolve, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, instance, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_instance, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, isStatic, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_isstatic, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Runtime_Registry, kindOf, arginfo_phalcon_mvc_view_engine_volt_runtime_registry_kindof, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
