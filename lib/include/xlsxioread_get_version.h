#ifndef XLSXIOREAD_GET_VERSION_H
#define XLSXIOREAD_GET_VERSION_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxioread_get_version_wrapper(napi_env env);
napi_status set_xlsxioread_get_version_wrapper(napi_env env, napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOREAD_GET_VERSION_H