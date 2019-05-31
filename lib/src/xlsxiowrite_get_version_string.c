#include "xlsxiowrite_get_version_string.h"
#include <assert.h>
#include <string.h>
#include <xlsxio_write.h>

static napi_value xlsxiowrite_get_version_string_wrapper(
    napi_env env, napi_callback_info info) {
  (void)info;
  const char* value;
  napi_value ret;

  value = xlsxiowrite_get_version_string();
  if (value != NULL) {
    ASSERT(napi_create_string_utf8(env, value, strlen(value), &ret) == napi_ok);
  } else {
    ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  }
  return ret;
}

napi_value create_xlsxiowrite_get_version_string_wrapper(napi_env env) {
  napi_value xlsxiowrite_get_version_string_function;

  ASSERT(napi_create_function(
             env, "xlsxiowrite_get_version_string", NAPI_AUTO_LENGTH,
             xlsxiowrite_get_version_string_wrapper, NULL,
             &xlsxiowrite_get_version_string_function) == napi_ok);
  return xlsxiowrite_get_version_string_function;
}

napi_status set_xlsxiowrite_get_version_string_wrapper(napi_env env,
                                                       napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxiowrite_get_version_string",
      create_xlsxiowrite_get_version_string_wrapper(env));
}
