#ifndef XLSXIOREAD_PROCESS_H
#define XLSXIOREAD_PROCESS_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxioread_process_wrapper(napi_env env);
napi_status set_xlsxioread_process_wrapper(napi_env env, napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOREAD_PROCESS_H
