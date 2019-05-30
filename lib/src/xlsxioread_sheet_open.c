#include "xlsxioread_sheet_open.h"
#include <assert.h>
#include <string.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheet_open_wrapper(napi_env env,
                                                napi_callback_info info) {
  napi_value argv[3];
  size_t argc = 3;
  xlsxioreader handle;
  char buffer[BUFFER_SIZE];
  const char *sheetname = NULL;
  napi_valuetype sheetname_type;
  size_t sheetname_length;
  unsigned int flags;
  xlsxioreadersheet sheet;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&handle) == napi_ok);
  if (argv[1] != NULL) {
    ASSERT(napi_typeof(env, argv[1], &sheetname_type) == napi_ok);
    if (sheetname_type == napi_string) {
      ASSERT(napi_get_value_string_utf8(env, argv[1], buffer, BUFFER_SIZE,
                                        &sheetname_length) == napi_ok);
      ASSERT(sheetname_length >= 0 && sheetname_length < BUFFER_SIZE);
      buffer[sheetname_length] = '\0';
    }
  }
  ASSERT(napi_get_value_uint32(env, argv[2], &flags) == napi_ok);
  sheet = xlsxioread_sheet_open(handle, sheetname, flags);
  ASSERT(jsxlsxio_create_pointer(env, sheet, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_sheet_open_wrapper(napi_env env) {
  napi_value xlsxioread_sheet_open_function;

  ASSERT(napi_create_function(env, "xlsxioread_sheet_open", NAPI_AUTO_LENGTH,
                              xlsxioread_sheet_open_wrapper, NULL,
                              &xlsxioread_sheet_open_function) == napi_ok);
  return xlsxioread_sheet_open_function;
}

napi_status set_xlsxioread_sheet_open_wrapper(napi_env env, napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_sheet_open",
                                 create_xlsxioread_sheet_open_wrapper(env));
}
