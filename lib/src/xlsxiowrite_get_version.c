#include "xlsxiowrite_get_version.h"
#include <assert.h>
#include <xlsxio_write.h>

static napi_value xlsxiowrite_get_version_wrapper(napi_env env,
                                                 napi_callback_info info) {
  (void)info;

  napi_value ret;
  napi_value ret_major;
  napi_value ret_minor;
  napi_value ret_micro;
  int major;
  int minor;
  int micro;

  xlsxiowrite_get_version(&major, &minor, &micro);
  ASSERT(napi_create_object(env, &ret) == napi_ok);
  EXPECT(napi_create_int64(env, major, &ret_major) == napi_ok);
  EXPECT(napi_create_int64(env, minor, &ret_minor) == napi_ok);
  EXPECT(napi_create_int64(env, micro, &ret_micro) == napi_ok);
  EXPECT(napi_set_named_property(env, ret, "major", ret_major) == napi_ok);
  EXPECT(napi_set_named_property(env, ret, "minor", ret_minor) == napi_ok);
  EXPECT(napi_set_named_property(env, ret, "micro", ret_micro) == napi_ok);
  return ret;
}

napi_value create_xlsxiowrite_get_version_wrapper(napi_env env) {
  napi_value xlsxiowrite_get_version_function;

  ASSERT(napi_create_function(env, "xlsxiowrite_get_version", NAPI_AUTO_LENGTH,
                              xlsxiowrite_get_version_wrapper, NULL,
                              &xlsxiowrite_get_version_function) == napi_ok);
  return xlsxiowrite_get_version_function;
}

napi_status set_xlsxiowrite_get_version_wrapper(napi_env env,
                                               napi_value result) {
  return napi_set_named_property(env, result, "xlsxiowrite_get_version",
                                 create_xlsxiowrite_get_version_wrapper(env));
}
