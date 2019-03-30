#include "xlsxioread_get_version.h"
#include <assert.h>
#include <xlsxio_read.h>

static napi_value xlsxioread_get_version_wrapper(napi_env env,
                                                 napi_callback_info info) {
  (void)info;

  napi_value ret;
  napi_value ret_major;
  napi_value ret_minor;
  napi_value ret_micro;
  int major;
  int minor;
  int micro;

  xlsxioread_get_version(&major, &minor, &micro);
  assert(napi_create_object(env, &ret) == napi_ok);
  assert(napi_create_int64(env, major, &ret_major) == napi_ok);
  assert(napi_create_int64(env, minor, &ret_minor) == napi_ok);
  assert(napi_create_int64(env, micro, &ret_micro) == napi_ok);
  assert(napi_set_named_property(env, ret, "major", ret_major) == napi_ok);
  assert(napi_set_named_property(env, ret, "minor", ret_minor) == napi_ok);
  assert(napi_set_named_property(env, ret, "micro", ret_micro) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_get_version_wrapper(napi_env env) {
  napi_value xlsxioread_get_version_function;

  assert(napi_create_function(env, "xlsxioread_get_version", NAPI_AUTO_LENGTH,
                              xlsxioread_get_version_wrapper, NULL,
                              &xlsxioread_get_version_function) == napi_ok);
  return xlsxioread_get_version_function;
}

napi_status set_xlsxioread_get_version_wrapper(napi_env env,
                                               napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_get_version",
                                 create_xlsxioread_get_version_wrapper(env));
}
