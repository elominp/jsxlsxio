#include "xlsxiowrite_close.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_close_wrapper(napi_env env,
                                           napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  int value;
  xlsxiowriter writer;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  value = xlsxiowrite_close(writer);
  ASSERT(napi_create_int64(env, value, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_close_wrapper(napi_env env) {
  napi_value xlsxiowrite_close_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_close", NAPI_AUTO_LENGTH,
                              xlsxiowrite_close_wrapper, NULL,
                              &xlsxiowrite_close_function) == napi_ok);
  return xlsxiowrite_close_function;
}

napi_status set_xlsxiowrite_close_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_close",
                                 create_xlsxiowrite_close_wrapper(env));
}
