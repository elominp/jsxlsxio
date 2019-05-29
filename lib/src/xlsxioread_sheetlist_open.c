#include "xlsxioread_sheetlist_open.h"
#include <assert.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheetlist_open_wrapper(napi_env env,
                                          napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  xlsxioreader reader;
  xlsxioreadersheetlist sheetlist;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&reader) == napi_ok);
  sheetlist = xlsxioread_sheetlist_open(reader);
  ASSERT(jsxlsxio_create_pointer(env, sheetlist, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_sheetlist_open_wrapper(napi_env env) {
  napi_value xlsxioread_sheetlist_open_function;

  ASSERT(napi_create_function(env, "xlsxioread_sheetlist_open", NAPI_AUTO_LENGTH,
                              xlsxioread_sheetlist_open_wrapper, NULL,
                              &xlsxioread_sheetlist_open_function) == napi_ok);
  return xlsxioread_sheetlist_open_function;
}

napi_status set_xlsxioread_sheetlist_open_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_sheetlist_open",
                                 create_xlsxioread_sheetlist_open_wrapper(env));
}
