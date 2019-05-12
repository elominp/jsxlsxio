#include "xlsxioread_sheet_next_row.h"
#include <assert.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheet_next_row_wrapper(napi_env env,
                                                    napi_callback_info info) {
  napi_value argv[1];
  size_t argc = 1;
  xlsxioreadersheet sheethandle;
  int row;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&sheethandle) == napi_ok);
  row = xlsxioread_sheet_next_row(sheethandle);
  ASSERT(napi_create_int32(env, (int32_t)row, &ret) == napi_ok);
  return ret;
}

napi_value create_xlsxioread_sheet_next_row_wrapper(napi_env env) {
  napi_value xlsxioread_sheet_next_row_function;

  ASSERT(napi_create_function(env, "xlsxioread_sheet_next_row",
                              NAPI_AUTO_LENGTH,
                              xlsxioread_sheet_next_row_wrapper, NULL,
                              &xlsxioread_sheet_next_row_function) == napi_ok);
  return xlsxioread_sheet_next_row_function;
}

napi_status set_xlsxioread_sheet_next_row_wrapper(napi_env env,
                                                  napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_sheet_next_row",
                                 create_xlsxioread_sheet_next_row_wrapper(env));
}
