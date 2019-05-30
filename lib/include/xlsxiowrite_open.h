#ifndef XLSXIOWRITE_OPEN_H
#define XLSXIOWRITE_OPEN_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxiowrite_open_wrapper(napi_env env);
napi_status set_xlsxiowrite_open_wrapper(napi_env env, napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOWRITE_OPEN_H
