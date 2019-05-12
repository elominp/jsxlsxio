#include "xlsxioread_sheet_next_cell_string.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheet_next_cell_string_wrapper(
    napi_env env, napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  xlsxioreadersheet sheethandle;
  XLSXIOCHAR* value;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void**)&sheethandle) == napi_ok);
  if (xlsxioread_sheet_next_cell_string(sheethandle, &value) && value != NULL) {
    ASSERT(napi_create_string_utf8(env, value, strlen(value), &ret) == napi_ok);
#ifndef _WIN32  // TODO : freeing value on windows cause node to stop without
                // any log but works on UNIX
    free(value);
#endif  // _WIN32
  } else {
    ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  }
  return ret;
}

napi_value create_xlsxioread_sheet_next_cell_string_wrapper(napi_env env) {
  napi_value xlsxioread_sheet_next_cell_string_function;

  ASSERT(napi_create_function(
             env, "xlsxioread_sheet_next_cell_string", NAPI_AUTO_LENGTH,
             xlsxioread_sheet_next_cell_string_wrapper, NULL,
             &xlsxioread_sheet_next_cell_string_function) == napi_ok);
  return xlsxioread_sheet_next_cell_string_function;
}

napi_status set_xlsxioread_sheet_next_cell_string_wrapper(napi_env env,
                                                          napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_sheet_next_cell_string",
      create_xlsxioread_sheet_next_cell_string_wrapper(env));
}
