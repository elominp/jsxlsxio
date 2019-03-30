#include "xlsxioread_sheet_next_cell_datetime.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xlsxio_read.h>
#include "jsxlsxio_pointers.h"

static napi_value xlsxioread_sheet_next_cell_datetime_wrapper(
    napi_env env, napi_callback_info info) {
  napi_value argv[2];
  size_t argc = 2;
  xlsxioreadersheet sheethandle;
  time_t value;
  napi_value ret;

  assert(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  assert(jsxlsxio_get_pointer(env, argv[0], (void **)&sheethandle) == napi_ok);
  if (xlsxioread_sheet_next_cell_datetime(sheethandle, &value)) {
    assert(napi_create_int64(env, value, &ret) == napi_ok);
  } else {
    assert(napi_get_undefined(env, &ret) == napi_ok);
  }
  return ret;
}

napi_value create_xlsxioread_sheet_next_cell_datetime_wrapper(napi_env env) {
  napi_value xlsxioread_sheet_next_cell_datetime_function;

  assert(napi_create_function(
             env, "xlsxioread_sheet_next_cell_datetime", NAPI_AUTO_LENGTH,
             xlsxioread_sheet_next_cell_datetime_wrapper, NULL,
             &xlsxioread_sheet_next_cell_datetime_function) == napi_ok);
  return xlsxioread_sheet_next_cell_datetime_function;
}

napi_status set_xlsxioread_sheet_next_cell_datetime_wrapper(napi_env env,
                                                            napi_value result) {
  return napi_set_named_property(
      env, result, "xlsxioread_sheet_next_cell_datetime",
      create_xlsxioread_sheet_next_cell_datetime_wrapper(env));
}
