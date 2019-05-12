#include "xlsxioread_open_memory.h"
#include <assert.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_open_memory_wrapper(napi_env env,
                                                 napi_callback_info info) {
  napi_value argv[3];
  size_t argc = 3;
  int64_t data;
  int64_t datalen;
  int32_t freedata;
  xlsxioreader reader;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(napi_get_value_int64(env, argv[0], &data) == napi_ok);
  ASSERT(napi_get_value_int64(env, argv[1], &datalen) == napi_ok);
  ASSERT(napi_get_value_int32(env, argv[2], &freedata) == napi_ok);
  ASSERT((reader = xlsxioread_open_memory((void *)data, (uint64_t)datalen,
                                          (int)freedata)) != NULL);
  ASSERT(jsxlsxio_create_pointer(env, reader, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_open_memory_wrapper(napi_env env) {
  napi_value xlsxioread_open_memory_function;

  ASSERT(napi_create_function(env, "xlsxioread_open_memory", NAPI_AUTO_LENGTH,
                              xlsxioread_open_memory_wrapper, NULL,
                              &xlsxioread_open_memory_function) == napi_ok);
  return xlsxioread_open_memory_function;
}

napi_status set_xlsxioread_open_memory_wrapper(napi_env env,
                                               napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_open_memory",
                                 create_xlsxioread_open_memory_wrapper(env));
}
