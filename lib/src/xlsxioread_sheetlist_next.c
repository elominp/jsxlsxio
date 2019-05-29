#include "xlsxioread_sheetlist_next.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheetlist_next_wrapper(napi_env env,
                                                     napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  xlsxioreadersheetlist sheetlist;
  const XLSXIOCHAR* value;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void**)&sheetlist) == napi_ok);
  value = xlsxioread_sheetlist_next(sheetlist);
  if (value != NULL) {
    ASSERT(napi_create_string_utf8(env, value, strlen(value), &ret) == napi_ok);
  } else {
    ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  }
  return ret;
}

napi_value create_xlsxioread_sheetlist_next_wrapper(napi_env env) {
  napi_value xlsxioread_sheetlist_next_function;

  ASSERT(napi_create_function(env, "xlsxioread_sheetlist_next",
                              NAPI_AUTO_LENGTH,
                              xlsxioread_sheetlist_next_wrapper, NULL,
                              &xlsxioread_sheetlist_next_function) == napi_ok);
  return xlsxioread_sheetlist_next_function;
}

napi_status set_xlsxioread_sheetlist_next_wrapper(napi_env env,
                                                   napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_sheetlist_next",
      create_xlsxioread_sheetlist_next_wrapper(env));
}
