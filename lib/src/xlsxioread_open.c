#include "xlsxioread_open.h"
#include <assert.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_open_wrapper(napi_env env,
                                          napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  char filename[BUFFER_SIZE];
  size_t filename_length;
  xlsxioreader reader;
  napi_value ret;

  assert(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  assert(napi_get_value_string_utf8(env, argv[0], filename, BUFFER_SIZE,
                                    &filename_length) == napi_ok);
  assert(filename_length >= 0);
  filename[filename_length] = '\0';
  assert((reader = xlsxioread_open(filename)) != NULL);
  assert(jsxlsxio_create_pointer(env, reader, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_open_wrapper(napi_env env) {
  napi_value xlsxioread_open_function;

  assert(napi_create_function(env, "xlsxioread_open", NAPI_AUTO_LENGTH,
                              xlsxioread_open_wrapper, NULL,
                              &xlsxioread_open_function) == napi_ok);
  return xlsxioread_open_function;
}

napi_status set_xlsxioread_open_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_open",
                                 create_xlsxioread_open_wrapper(env));
}
