#include "xlsxioread_get_version_string.h"
#include <assert.h>
#include <xlsxio_read.h>

static napi_value xlsxioread_get_version_string_wrapper(
    napi_env env, napi_callback_info info) {
  (void)info;
  const XLSXIOCHAR* value;
  napi_value ret;

  value = xlsxioread_get_version_string();
  if (value != NULL) {
    ASSERT(napi_create_string_utf8(env, value, strlen(value), &ret) == napi_ok);
  } else {
    ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  }
  return ret;
}

napi_value create_xlsxioread_get_version_string_wrapper(napi_env env) {
  napi_value xlsxioread_get_version_string_function;

  ASSERT(napi_create_function(
             env, "xlsxioread_get_version_string", NAPI_AUTO_LENGTH,
             xlsxioread_get_version_string_wrapper, NULL,
             &xlsxioread_get_version_string_function) == napi_ok);
  return xlsxioread_get_version_string_function;
}

napi_status set_xlsxioread_get_version_string_wrapper(napi_env env,
                                                      napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_get_version_string",
      create_xlsxioread_get_version_string_wrapper(env));
}
