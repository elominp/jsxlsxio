#ifndef XLSXIOWRITE_GET_VERSION_H
#define XLSXIOWRITE_GET_VERSION_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxiowrite_get_version_wrapper(napi_env env);
napi_status set_xlsxiowrite_get_version_wrapper(napi_env env, napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOWRITE_GET_VERSION_H
