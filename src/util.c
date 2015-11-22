
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_util.h"

/* If you declare any globals in php_util.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(util)
*/

/* True global resources - no need for thread safety here */
static int le_util;

/* {{{ util_functions[]
 *
 * Every user visible function must have an entry in util_functions[].
 */
const zend_function_entry util_functions[] = {
	PHP_FE(confirm_util_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in util_functions[] */
};
/* }}} */

zend_class_entry *util_ce;

/* {{{ util_method[]
 *
 * Every user visible function must have an entry in util_functions[].
 */
static zend_function_entry util_method[] = {
	ZEND_ME(util,	array_first,		NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(util,	array_last, 		NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(util,	array_first_key,	NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(util,	array_last_key,		NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(util,	array_flatten,		NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(util,	array_get,			NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};
/* }}} */

/* {{{ util_module_entry
 */
zend_module_entry util_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"util",
	util_functions,
	PHP_MINIT(util),
	PHP_MSHUTDOWN(util),
	PHP_RINIT(util),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(util),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(util),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_UTIL_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_UTIL
ZEND_GET_MODULE(util)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("util.global_value",	  "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_util_globals, util_globals)
	STD_PHP_INI_ENTRY("util.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_util_globals, util_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_util_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_util_init_globals(zend_util_globals *util_globals)
{
	util_globals->global_value = 0;
	util_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(util)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry ce;

	//Class name is "Util"
	INIT_CLASS_ENTRY(ce, "Util", util_method);
	util_ce = zend_register_internal_class(&ce TSRMLS_CC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(util)
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
PHP_RINIT_FUNCTION(util)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(util)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(util)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "util support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_util_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_util_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "util", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */

/* {{{ proto Util::array_first(array $arr)
   Return the first value from an array. */
ZEND_METHOD(util, array_first)
{
	zval *arr, **zvalue;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		RETURN_NULL();
	}
	if (Z_TYPE_P(arr) != IS_ARRAY) {
		RETURN_NULL();
	}
	zend_hash_internal_pointer_reset(Z_ARRVAL_P(arr));
	if (zend_hash_get_current_data(Z_ARRVAL_P(arr), (void**)&zvalue) == FAILURE) {
		RETURN_NULL();
	}

	*return_value = **zvalue;
	zval_copy_ctor(return_value);
	return;
}
/* }}} */

/* {{{ proto Util::array_last(array $arr)
   Return the last value from an array. */
ZEND_METHOD(util, array_last)
{
	zval *arr, **zvalue;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		RETURN_NULL();
	}
	if (Z_TYPE_P(arr) != IS_ARRAY) {
		RETURN_NULL();
	}
	zend_hash_internal_pointer_end(Z_ARRVAL_P(arr));
	if (zend_hash_get_current_data(Z_ARRVAL_P(arr), (void**)&zvalue) == FAILURE) {
		RETURN_NULL();
	}

	*return_value = **zvalue;
	zval_copy_ctor(return_value);
	return;
}
/* }}} */

/* {{{ proto Util::array_first_key(array $array)
   Return the first key from an array. */
ZEND_METHOD(util, array_first_key)
{
	char *key;
	uint keylen;
	ulong idx;
	zval *arr;
	int type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		RETURN_NULL();
	}
	if (Z_TYPE_P(arr) != IS_ARRAY) {
		RETURN_NULL();
	}
	zend_hash_internal_pointer_reset(Z_ARRVAL_P(arr));
	type = zend_hash_get_current_key_ex(Z_ARRVAL_P(arr), &key, &keylen, &idx, 0, NULL);
	if (type == HASH_KEY_IS_STRING) {
		RETURN_STRINGL(key, keylen, 0);
	} else if (type == HASH_KEY_IS_LONG) {
		RETURN_LONG(idx);
	}
	RETURN_NULL();
}
/* }}} */

/* {{{ proto Util::array_last_key(array $array)
   Return the last key from an array. */
ZEND_METHOD(util, array_last_key)
{
	char *key;
	uint keylen;
	ulong idx;
	zval *arr;
	int type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
		RETURN_NULL();
	}
	if (Z_TYPE_P(arr) != IS_ARRAY) {
		RETURN_NULL();
	}
	zend_hash_internal_pointer_end(Z_ARRVAL_P(arr));
	type = zend_hash_get_current_key_ex(Z_ARRVAL_P(arr), &key, &keylen, &idx, 0, NULL);
	if (type == HASH_KEY_IS_STRING) {
		RETURN_STRINGL(key, keylen, 0);
	} else if (type == HASH_KEY_IS_LONG) {
		RETURN_LONG(idx);
	}
	RETURN_NULL();
}
/* }}} */

void util_array_flatten(zval* arr, zval* result, zend_bool preserve_keys) {
	zval **zvalue;
	char *key;
	uint keylen;
	ulong idx;
	int type;
	HashTable* arr_hash;
	HashPosition pointer;

	// Copy a temp array
	zval temp;
	temp = *arr;
	zval_copy_ctor(&temp);

	arr_hash = Z_ARRVAL_P(&temp);
	zend_hash_internal_pointer_reset_ex(arr_hash, &pointer);
	while (zend_hash_get_current_data_ex(arr_hash, (void**) &zvalue, &pointer) == SUCCESS) {
		if (Z_TYPE_P(*zvalue) == IS_ARRAY) {
			util_array_flatten(*zvalue, result, preserve_keys);
		} else {
			type = zend_hash_get_current_key_ex(arr_hash, &key, &keylen, &idx, 0, &pointer);
			if (preserve_keys && type != HASH_KEY_IS_LONG) {
				add_assoc_zval(result, key, *zvalue);
			} else {
				add_next_index_zval(result, *zvalue);
			}
		}
		zend_hash_move_forward_ex(arr_hash, &pointer);
		//ALLOC_INIT_ZVAL(*zvalue);
	}
}

/* {{{ proto Util::array_flatten(array $array[, bool $preserve_keys = TRUE])
   Flattens a multi-dimensional array into a one dimensional array. */
ZEND_METHOD(util, array_flatten)
{
	zval *arr, *result;
	zend_bool preserve_keys = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|b", &arr, &preserve_keys) == FAILURE) {
		RETURN_NULL();
	}
	if (Z_TYPE_P(arr) != IS_ARRAY) {
		RETURN_NULL();
	}

	// Init return value as array
	array_init(return_value);

	util_array_flatten(arr, return_value, preserve_keys);
	return;
}
/* }}} */

/* {{{ proto Util::array_get($array, $key[, mixed $default = NULL])
   Return a value from an array, or return a given default if the index isn't set. */
ZEND_METHOD(util, array_get)
{
	zval *arr, **zvalue, *default_value;
	char *key;
	uint keylen;
	MAKE_STD_ZVAL(default_value);
	ZVAL_NULL(default_value);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "as|z", &arr, &key, &keylen, &default_value) == FAILURE) {
		RETURN_NULL();
	}

	if (zend_hash_find(Z_ARRVAL_P(arr), key, keylen, (void**) &zvalue) == SUCCESS) {
		*return_value = **zvalue;
	} else {
		*return_value = *default_value;
	}
	zval_copy_ctor(return_value);
	return;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
