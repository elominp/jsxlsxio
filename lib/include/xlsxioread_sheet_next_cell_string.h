#ifndef XLSXIOREAD_SHEET_NEXT_CELL_STRING_H
#define XLSXIOREAD_SHEET_NEXT_CELL_STRING_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxioread_sheet_next_cell_string_wrapper(napi_env env);
napi_status set_xlsxioread_sheet_next_cell_string_wrapper(napi_env env,
                                                          napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOREAD_SHEET_NEXT_CELL_STRING_H