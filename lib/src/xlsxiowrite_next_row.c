#include "xlsxiowrite_next_row.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_next_row_wrapper(napi_env env,
                                          napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  xlsxiowriter writer;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  xlsxiowrite_next_row(writer);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_next_row_wrapper(napi_env env) {
  napi_value xlsxiowrite_next_row_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_next_row", NAPI_AUTO_LENGTH,
                              xlsxiowrite_next_row_wrapper, NULL,
                              &xlsxiowrite_next_row_function) == napi_ok);
  return xlsxiowrite_next_row_function;
}

napi_status set_xlsxiowrite_next_row_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_next_row",
                                 create_xlsxiowrite_next_row_wrapper(env));
}
