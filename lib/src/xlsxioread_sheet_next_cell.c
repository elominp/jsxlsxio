#include "xlsxioread_sheet_next_cell.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheet_next_cell_wrapper(napi_env env,
                                                     napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  xlsxioreadersheet sheethandle;
  XLSXIOCHAR* value;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void**)&sheethandle) == napi_ok);
  value = xlsxioread_sheet_next_cell(sheethandle);
  if (value != NULL) {
    ASSERT(napi_create_string_utf8(env, value, strlen(value), &ret) == napi_ok);
    free(value);
  } else {
    ASSERT(napi_get_undefined(env, &ret) == napi_ok);
  }
  return ret;
}

napi_value create_xlsxioread_sheet_next_cell_wrapper(napi_env env) {
  napi_value xlsxioread_sheet_next_cell_function;

  ASSERT(napi_create_function(env, "xlsxioread_sheet_next_cell",
                              NAPI_AUTO_LENGTH,
                              xlsxioread_sheet_next_cell_wrapper, NULL,
                              &xlsxioread_sheet_next_cell_function) == napi_ok);
  return xlsxioread_sheet_next_cell_function;
}

napi_status set_xlsxioread_sheet_next_cell_wrapper(napi_env env,
                                                   napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_sheet_next_cell",
      create_xlsxioread_sheet_next_cell_wrapper(env));
}
