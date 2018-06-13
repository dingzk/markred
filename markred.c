/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_markred.h"

#include "trie.h"
#include "token.h"

/* If you declare any globals in php_markred.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(markred)

/* True global resources - no need for thread safety here */
static int le_markred;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("markred.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_markred_globals, markred_globals)
    STD_PHP_INI_ENTRY("markred.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_markred_globals, markred_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_markred_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(build_trie)
{
    zval *input;
    zval *val;
    zend_array *words;
    char *token;
#ifndef FAST_ZPP
    /* Get function parameters and do error-checking. */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &input) == FAILURE) {
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY(input)
    ZEND_PARSE_PARAMETERS_END();
#endif
    words = Z_ARRVAL_P(input);
    Trie *root = create_trie('`', 0);
    ZEND_HASH_FOREACH_VAL(words, val)
        token = Z_STRVAL_P(val);
        //printf("%s\n", token);
        append_trie(token, root);        
    ZEND_HASH_FOREACH_END();
    MARKRED_G(Troot) = root;

    RETURN_TRUE
}

PHP_FUNCTION(markred)
{
    zend_string *str;
    char *target;
#ifndef FAST_ZPP
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &str) == FAILURE) {
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(str)
    ZEND_PARSE_PARAMETERS_END();
#endif
    target = ZSTR_VAL(str);

    if (MARKRED_G(Troot) == NULL) {
        printf("please call build_trie first\n");
        RETURN_FALSE
    }
    char marked[10240] = {0};
    match_all(target, marked, MARKRED_G(Troot));

    RETURN_STRING(marked);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_markred_init_globals
 */
/* Uncomment this function if you have INI entries 
static void php_markred_init_globals(zend_markred_globals *markred_globals)
{
	markred_globals->Troot = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(markred)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(markred)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(markred)
{
#if defined(COMPILE_DL_MARKRED) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
    MARKRED_G(Troot) = NULL;
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(markred)
{
    if (MARKRED_G(Troot) != NULL) {
        free_trie(MARKRED_G(Troot));
    }
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(markred)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "markred support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ markred_functions[]
 *
 * Every user visible function must have an entry in markred_functions[].
 */
const zend_function_entry markred_functions[] = {
	PHP_FE(build_trie,	NULL)		/* For testing, remove later. */
	PHP_FE(markred,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in markred_functions[] */
};
/* }}} */

/* {{{ markred_module_entry
 */
zend_module_entry markred_module_entry = {
	STANDARD_MODULE_HEADER,
	"markred",
	markred_functions,
	PHP_MINIT(markred),
	PHP_MSHUTDOWN(markred),
	PHP_RINIT(markred),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(markred),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(markred),
	PHP_MARKRED_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MARKRED
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(markred)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
