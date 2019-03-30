#ifndef XLSXIOREAD_SHEET_OPEN_H
#define XLSXIOREAD_SHEET_OPEN_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxioread_sheet_open_wrapper(napi_env env);
napi_status set_xlsxioread_sheet_open_wrapper(napi_env env, napi_value result);

#endif  // XLSXIOREAD_SHEET_OPEN_H