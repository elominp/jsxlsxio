#ifndef XLSXIOWRITE_SET_ROW_HEIGHT_H
#define XLSXIOWRITE_SET_ROW_HEIGHT_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxiowrite_set_row_height_wrapper(napi_env env);
napi_status set_xlsxiowrite_set_row_height_wrapper(napi_env env,
                                                   napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOWRITE_SET_ROW_HEIGHT_H
