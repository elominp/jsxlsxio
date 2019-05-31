#include "xlsxiowrite_add_cell_datetime.h"
#include <assert.h>
#include <time.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_add_cell_datetime_wrapper(
    napi_env env, napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  xlsxiowriter writer;
  time_t value;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  ASSERT(napi_get_value_int64(env, argv[1], (time_t *)&value) == napi_ok);
  xlsxiowrite_add_cell_datetime(writer, value);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_add_cell_datetime_wrapper(napi_env env) {
  napi_value xlsxiowrite_add_cell_datetime_function;

  ASSERT(napi_create_function(
             env, "xlsxiowrite_add_cell_datetime", NAPI_AUTO_LENGTH,
             xlsxiowrite_add_cell_datetime_wrapper, NULL,
             &xlsxiowrite_add_cell_datetime_function) == napi_ok);
  return xlsxiowrite_add_cell_datetime_function;
}

napi_status set_xlsxiowrite_add_cell_datetime_wrapper(napi_env env,
                                                      napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxiowrite_add_cell_datetime",
      create_xlsxiowrite_add_cell_datetime_wrapper(env));
}
