#include "xlsxiowrite_add_cell_float.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_add_cell_float_wrapper(napi_env env,
                                          napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  xlsxiowriter writer;
  double value;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  ASSERT(napi_get_value_double(env, argv[1], &value) == napi_ok);
  xlsxiowrite_add_cell_float(writer, value);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_add_cell_float_wrapper(napi_env env) {
  napi_value xlsxiowrite_add_cell_float_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_add_cell_float", NAPI_AUTO_LENGTH,
                              xlsxiowrite_add_cell_float_wrapper, NULL,
                              &xlsxiowrite_add_cell_float_function) == napi_ok);
  return xlsxiowrite_add_cell_float_function;
}

napi_status set_xlsxiowrite_add_cell_float_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_add_cell_float",
                                 create_xlsxiowrite_add_cell_float_wrapper(env));
}
