#include "xlsxioread_list_sheets.h"
#include <assert.h>
#include <string.h>
#include <time.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_ref callback = NULL;
static napi_ref callback_data = NULL;
static napi_async_context async_context = NULL;
static napi_env async_env = NULL;

static int xlsxioread_list_sheets_init_napi_async(napi_env env) {
  napi_value name;
  const char *resource_name = "xlsxioread_list_sheets_async";

  async_env = env;
  ASSERT(napi_create_string_utf8(env, resource_name, strlen(resource_name),
                                 &name) == napi_ok);
  ASSERT(napi_async_init(env, NULL, name, &async_context) == napi_ok);
  return 0;
}

static int xlsxioread_list_sheets_destroy_napi_async(void) {
  if (async_context != NULL) {
    ASSERT(napi_async_destroy(async_env, async_context) == napi_ok);
    async_context = NULL;
  }
  return 0;
}

static int xlsxioread_list_sheets_callback(const XLSXIOCHAR *name,
                                           void *callbackdata) {
  (void)callbackdata;

  napi_value argv[2];
  napi_value tocall;
  napi_value global;
  napi_value ret;

  if (name != NULL) {
    ASSERT(napi_create_string_utf8(async_env, name, strlen(name), &argv[0]) ==
           napi_ok);
  } else {
    ASSERT(napi_get_undefined(async_env, &argv[0]) == napi_ok);
  }
  ASSERT(napi_get_reference_value(async_env, (napi_ref)callback_data,
                                  &argv[1]) == napi_ok);
  ASSERT(napi_get_reference_value(async_env, callback, &tocall) == napi_ok);
  ASSERT(napi_get_global(async_env, &global) == napi_ok);
  ASSERT(napi_make_callback(async_env, async_context, global, tocall, 2, argv,
                            &ret) == napi_ok);
  return 0;
}

static napi_value xlsxioread_list_sheets_wrapper(napi_env env,
                                                 napi_callback_info info) {
  napi_value argv[3];
  size_t argc = 3;
  xlsxioreader handle;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&handle) == napi_ok);
  if (callback != NULL) {
    xlsxioread_list_sheets_destroy_napi_async();
    ASSERT(napi_delete_reference(env, callback) == napi_ok);
  }
  ASSERT(napi_create_reference(env, argv[1], 1, &callback) == napi_ok);
  if (callback_data != NULL) {
    ASSERT(napi_delete_reference(env, callback_data) == napi_ok);
  }
  ASSERT(napi_create_reference(env, argv[2], 1, &callback_data) == napi_ok);
  xlsxioread_list_sheets_init_napi_async(env);
  xlsxioread_list_sheets(handle, xlsxioread_list_sheets_callback,
                         callback_data);
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value create_xlsxioread_list_sheets_wrapper(napi_env env) {
  napi_value xlsxioread_list_sheets_function;

  ASSERT(napi_create_function(env, "xlsxioread_list_sheets", NAPI_AUTO_LENGTH,
                              xlsxioread_list_sheets_wrapper, NULL,
                              &xlsxioread_list_sheets_function) == napi_ok);
  return xlsxioread_list_sheets_function;
}

napi_status set_xlsxioread_list_sheets_wrapper(napi_env env,
                                               napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_list_sheets",
                                 create_xlsxioread_list_sheets_wrapper(env));
}
