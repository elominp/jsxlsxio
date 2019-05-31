#include "xlsxiowrite_set_row_height.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_set_row_height_wrapper(napi_env env,
                                                     napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  size_t height;
  xlsxiowriter writer;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  ASSERT(napi_get_value_int64(env, argv[1], (int64_t *)&height) == napi_ok);
  xlsxiowrite_set_row_height(writer, height);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_set_row_height_wrapper(napi_env env) {
  napi_value xlsxiowrite_set_row_height_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_set_row_height",
                              NAPI_AUTO_LENGTH,
                              xlsxiowrite_set_row_height_wrapper, NULL,
                              &xlsxiowrite_set_row_height_function) == napi_ok);
  return xlsxiowrite_set_row_height_function;
}

napi_status set_xlsxiowrite_set_row_height_wrapper(napi_env env,
                                                   napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxiowrite_set_row_height",
      create_xlsxiowrite_set_row_height_wrapper(env));
}
