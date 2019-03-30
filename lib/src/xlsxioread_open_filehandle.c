#include "xlsxioread_open_filehandle.h"
#include <assert.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_open_filehandle_wrapper(napi_env env,
                                                     napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  int64_t fd;
  xlsxioreader reader;
  napi_value ret;

  assert(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  assert(napi_get_value_int64(env, argv[0], &fd) == napi_ok);
  assert((reader = xlsxioread_open_filehandle((int)fd)) != NULL);
  assert(jsxlsxio_create_pointer(env, reader, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_open_filehandle_wrapper(napi_env env) {
  napi_value xlsxioread_open_filehandle_function;

  assert(napi_create_function(env, "xlsxioread_open_filehandle",
                              NAPI_AUTO_LENGTH,
                              xlsxioread_open_filehandle_wrapper, NULL,
                              &xlsxioread_open_filehandle_function) == napi_ok);
  return xlsxioread_open_filehandle_function;
}

napi_status set_xlsxioread_open_filehandle_wrapper(napi_env env,
                                                   napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_open_filehandle",
      create_xlsxioread_open_filehandle_wrapper(env));
}
