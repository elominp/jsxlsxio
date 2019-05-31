#include "xlsxiowrite_add_column.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_add_column_wrapper(napi_env env,
                                                 napi_callback_info info) {
  napi_value argv[3];
  size_t argc = 3;
  size_t width;
  xlsxiowriter writer;
  char name[BUFFER_SIZE];
  size_t name_length;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&writer) == napi_ok);
  ASSERT(napi_get_value_string_utf8(env, argv[1], name, BUFFER_SIZE,
                                    &name_length) == napi_ok);
  ASSERT(name_length >= 0 && name_length < BUFFER_SIZE);
  name[name_length] = '\0';
  ASSERT(napi_get_value_int64(env, argv[2], (int64_t *)&width) == napi_ok);
  xlsxiowrite_add_column(writer, name, width);
  ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_add_column_wrapper(napi_env env) {
  napi_value xlsxiowrite_add_column_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_add_column", NAPI_AUTO_LENGTH,
                              xlsxiowrite_add_column_wrapper, NULL,
                              &xlsxiowrite_add_column_function) == napi_ok);
  return xlsxiowrite_add_column_function;
}

napi_status set_xlsxiowrite_add_column_wrapper(napi_env env,
                                               napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_add_column",
                                 create_xlsxiowrite_add_column_wrapper(env));
}
