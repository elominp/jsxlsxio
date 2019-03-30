#ifndef XLSXIOREAD_LIST_SHEETS_H
#define XLSXIOREAD_LIST_SHEETS_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxioread_list_sheets_wrapper(napi_env env);
napi_status set_xlsxioread_list_sheets_wrapper(napi_env env, napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOREAD_LIST_SHEETS_H