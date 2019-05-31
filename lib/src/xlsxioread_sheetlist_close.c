#include "xlsxioread_sheetlist_close.h"
#include <assert.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheetlist_close_wrapper(napi_env env,
                                                     napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  xlsxioreadersheetlist sheetlist;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&sheetlist) == napi_ok);
  xlsxioread_sheetlist_close(sheetlist);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_sheetlist_close_wrapper(napi_env env) {
  napi_value xlsxioread_sheetlist_close_function;

  ASSERT(napi_create_function(env, "xlsxioread_sheetlist_close",
                              NAPI_AUTO_LENGTH,
                              xlsxioread_sheetlist_close_wrapper, NULL,
                              &xlsxioread_sheetlist_close_function) == napi_ok);
  return xlsxioread_sheetlist_close_function;
}

napi_status set_xlsxioread_sheetlist_close_wrapper(napi_env env,
                                                   napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_sheetlist_close",
      create_xlsxioread_sheetlist_close_wrapper(env));
}
