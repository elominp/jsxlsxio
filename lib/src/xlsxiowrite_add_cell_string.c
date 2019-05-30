#include "xlsxiowrite_add_cell_string.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_add_cell_string_wrapper(napi_env env,
                                          napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  xlsxiowriter writer;
  char value[BUFFER_SIZE];
  size_t value_length;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  ASSERT(napi_get_value_string_utf8(env, argv[1], value, BUFFER_SIZE, &value_length) == napi_ok);
  ASSERT(value_length >= 0 && value_length < BUFFER_SIZE);
  value[value_length] = '\0';
  xlsxiowrite_add_cell_string(writer, value);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_add_cell_string_wrapper(napi_env env) {
  napi_value xlsxiowrite_add_cell_string_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_add_cell_string", NAPI_AUTO_LENGTH,
                              xlsxiowrite_add_cell_string_wrapper, NULL,
                              &xlsxiowrite_add_cell_string_function) == napi_ok);
  return xlsxiowrite_add_cell_string_function;
}

napi_status set_xlsxiowrite_add_cell_string_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_add_cell_string",
                                 create_xlsxiowrite_add_cell_string_wrapper(env));
}
