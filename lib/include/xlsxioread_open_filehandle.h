#ifndef XLSXIOREAD_OPEN_FILEHANDLE_H
#define XLSXIOREAD_OPEN_FILEHANDLE_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_value create_xlsxioread_open_filehandle_wrapper(napi_env env);
napi_status set_xlsxioread_open_filehandle_wrapper(napi_env env,
                                                   napi_value result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // XLSXIOREAD_OPEN_FILEHANDLE_H