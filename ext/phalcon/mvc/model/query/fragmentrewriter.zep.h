
extern zend_class_entry *phalcon_mvc_model_query_fragmentrewriter_ce;

ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Query_FragmentRewriter);

PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, __construct);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, addModel);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, addAlias);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, escape);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, getBindTypes);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, qualify);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, rewrite);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, rewriteString);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, splitList);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, splitAlias);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, tokenize);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, bareColumn);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, getReverseMap);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, isModel);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, lazyDomain);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, modelTable);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, joinTokens);
PHP_METHOD(Phalcon_Mvc_Model_Query_FragmentRewriter, significant);
zend_object *zephir_init_properties_Phalcon_Mvc_Model_Query_FragmentRewriter(zend_class_entry *class_type);

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter___construct, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, manager, Phalcon\\Mvc\\Model\\ManagerInterface, 0)
	ZEND_ARG_OBJ_INFO(0, metaData, Phalcon\\Mvc\\Model\\MetaDataInterface, 0)
	ZEND_ARG_OBJ_INFO(0, dialect, Phalcon\\Db\\DialectInterface, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, bindParams, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_addmodel, 0, 3, Phalcon\\Mvc\\Model\\Query\\FragmentRewriter, 0)
	ZEND_ARG_TYPE_INFO(0, modelName, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, model, Phalcon\\Mvc\\ModelInterface, 0)
	ZEND_ARG_TYPE_INFO(0, sqlAlias, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, hasAlias, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_addalias, 0, 1, Phalcon\\Mvc\\Model\\Query\\FragmentRewriter, 0)
	ZEND_ARG_TYPE_INFO(0, alias, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_escape, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, identifier, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_getbindtypes, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_qualify, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, domain, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, property, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_rewrite, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, fragment, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_rewritestring, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, fragment, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_splitlist, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, sql, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_splitalias, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, item, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_tokenize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, fragment, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_barecolumn, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_getreversemap, 0, 1, IS_ARRAY, 1)
	ZEND_ARG_OBJ_INFO(0, model, Phalcon\\Mvc\\ModelInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_ismodel, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_lazydomain, 0, 1, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_modeltable, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_jointokens, 0, 3, IS_STRING, 0)
	ZEND_ARG_ARRAY_INFO(0, tokens, 0)
	ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, end, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_significant, 0, 3, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, tokens, 0)
	ZEND_ARG_TYPE_INFO(0, from, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phalcon_mvc_model_query_fragmentrewriter_zephir_init_properties_phalcon_mvc_model_query_fragmentrewriter, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_mvc_model_query_fragmentrewriter_method_entry) {
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, __construct, arginfo_phalcon_mvc_model_query_fragmentrewriter___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, addModel, arginfo_phalcon_mvc_model_query_fragmentrewriter_addmodel, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, addAlias, arginfo_phalcon_mvc_model_query_fragmentrewriter_addalias, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, escape, arginfo_phalcon_mvc_model_query_fragmentrewriter_escape, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, getBindTypes, arginfo_phalcon_mvc_model_query_fragmentrewriter_getbindtypes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, qualify, arginfo_phalcon_mvc_model_query_fragmentrewriter_qualify, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, rewrite, arginfo_phalcon_mvc_model_query_fragmentrewriter_rewrite, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, rewriteString, arginfo_phalcon_mvc_model_query_fragmentrewriter_rewritestring, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, splitList, arginfo_phalcon_mvc_model_query_fragmentrewriter_splitlist, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, splitAlias, arginfo_phalcon_mvc_model_query_fragmentrewriter_splitalias, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, tokenize, arginfo_phalcon_mvc_model_query_fragmentrewriter_tokenize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, bareColumn, arginfo_phalcon_mvc_model_query_fragmentrewriter_barecolumn, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, getReverseMap, arginfo_phalcon_mvc_model_query_fragmentrewriter_getreversemap, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, isModel, arginfo_phalcon_mvc_model_query_fragmentrewriter_ismodel, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, lazyDomain, arginfo_phalcon_mvc_model_query_fragmentrewriter_lazydomain, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, modelTable, arginfo_phalcon_mvc_model_query_fragmentrewriter_modeltable, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, joinTokens, arginfo_phalcon_mvc_model_query_fragmentrewriter_jointokens, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Phalcon_Mvc_Model_Query_FragmentRewriter, significant, arginfo_phalcon_mvc_model_query_fragmentrewriter_significant, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_FE_END
};
