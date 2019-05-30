#include "xlsxiowrite_open.h"
#include <assert.h>
#include <xlsxio_write.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxiowrite_open_wrapper(napi_env env,
                                          napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  char filename[BUFFER_SIZE];
  char sheetname[BUFFER_SIZE];
  size_t filename_length;
  size_t sheetname_length;
  xlsxiowriter writer;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(napi_get_value_string_utf8(env, argv[0], filename, BUFFER_SIZE,
                                    &filename_length) == napi_ok);
  ASSERT(napi_get_value_string_utf8(env, argv[1], sheetname, BUFFER_SIZE, &sheetname_length) == napi_ok);
  ASSERT(filename_length >= 0 && filename_length < BUFFER_SIZE)
  ASSERT(sheetname_length >= 0 && sheetname_length < BUFFER_SIZE);
  filename[filename_length] = '\0';
  sheetname[sheetname_length] = '\0';
  ASSERT((writer = xlsxiowrite_open(filename, sheetname)) != NULL);
  ASSERT(jsxlsxio_create_pointer(env, writer, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_open_wrapper(napi_env env) {
  napi_value xlsxiowrite_open_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_open", NAPI_AUTO_LENGTH,
                              xlsxiowrite_open_wrapper, NULL,
                              &xlsxiowrite_open_function) == napi_ok);
  return xlsxiowrite_open_function;
}

napi_status set_xlsxiowrite_open_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_open",
                                 create_xlsxiowrite_open_wrapper(env));
}
