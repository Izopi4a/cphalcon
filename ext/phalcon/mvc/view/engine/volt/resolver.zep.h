
extern zend_class_entry *phalcon_mvc_view_engine_volt_resolver_ce;

ZEPHIR_INIT_CLASS(Phalcon_Mvc_View_Engine_Volt_Resolver);

PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, __construct);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, php);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, resolve);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, resolveChain);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, collectBlocks);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, collectInto);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, dynamicExtends);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, error);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expand);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlock);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlockAt);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlockFunction);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandEmbed);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, expandSuper);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, findExtends);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, hasInheritanceNodes);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, isCall);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, isLiteral);
PHP_METHOD(Phalcon_Mvc_View_Engine_Volt_Resolver, withExtendsPath);
zend_object *zephir_init_properties_Phalcon_Mvc_View_Engine_Volt_Resolver(zend_class_entry *class_type);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, compiler, Phalcon\\Mvc\\View\\Engine\\Volt\\Compiler, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_php, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, code, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_resolve, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, ast, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_resolvechain, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, ast, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_collectblocks, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, statements, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_collectinto, 0, 2, IS_VOID, 0)

	ZEND_ARG_ARRAY_INFO(0, statements, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_dynamicextends, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, extendsNode, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_error, 0, 2, Phalcon\\Mvc\\View\\Engine\\Volt\\Exception, 0)
	ZEND_ARG_TYPE_INFO(0, message, IS_STRING, 0)
	ZEND_ARG_ARRAY_INFO(0, node, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_expand, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, statements, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_expandblock, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_ARRAY_INFO(0, node, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_expandblockat, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_expandblockfunction, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, call, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_expandembed, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, node, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_expandsuper, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_INFO(0, context)
	ZEND_ARG_ARRAY_INFO(0, node, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_findextends, 0, 1, IS_ARRAY, 1)
	ZEND_ARG_ARRAY_INFO(0, statements, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_hasinheritancenodes, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_ARRAY_INFO(0, statements, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_iscall, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, expr)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_isliteral, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, expr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_withextendspath, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_ARRAY_INFO(0, statements, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_view_engine_volt_resolver_zephir_init_properties_phalcon_mvc_view_engine_volt_resolver, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_mvc_view_engine_volt_resolver_method_entry) {
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, __construct, arginfo_phalcon_mvc_view_engine_volt_resolver___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, php, arginfo_phalcon_mvc_view_engine_volt_resolver_php, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, resolve, arginfo_phalcon_mvc_view_engine_volt_resolver_resolve, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, resolveChain, arginfo_phalcon_mvc_view_engine_volt_resolver_resolvechain, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, collectBlocks, arginfo_phalcon_mvc_view_engine_volt_resolver_collectblocks, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, collectInto, arginfo_phalcon_mvc_view_engine_volt_resolver_collectinto, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, dynamicExtends, arginfo_phalcon_mvc_view_engine_volt_resolver_dynamicextends, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, error, arginfo_phalcon_mvc_view_engine_volt_resolver_error, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, expand, arginfo_phalcon_mvc_view_engine_volt_resolver_expand, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlock, arginfo_phalcon_mvc_view_engine_volt_resolver_expandblock, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlockAt, arginfo_phalcon_mvc_view_engine_volt_resolver_expandblockat, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, expandBlockFunction, arginfo_phalcon_mvc_view_engine_volt_resolver_expandblockfunction, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, expandEmbed, arginfo_phalcon_mvc_view_engine_volt_resolver_expandembed, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, expandSuper, arginfo_phalcon_mvc_view_engine_volt_resolver_expandsuper, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, findExtends, arginfo_phalcon_mvc_view_engine_volt_resolver_findextends, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, hasInheritanceNodes, arginfo_phalcon_mvc_view_engine_volt_resolver_hasinheritancenodes, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, isCall, arginfo_phalcon_mvc_view_engine_volt_resolver_iscall, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, isLiteral, arginfo_phalcon_mvc_view_engine_volt_resolver_isliteral, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_View_Engine_Volt_Resolver, withExtendsPath, arginfo_phalcon_mvc_view_engine_volt_resolver_withextendspath, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
