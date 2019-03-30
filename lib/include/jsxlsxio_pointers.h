#ifndef JSXLSXIO_POINTERS_H
#define JSXLSXIO_POINTERS_H

#include "jsxlsxio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
napi_status jsxlsxio_get_pointer(napi_env env, napi_value value, void **dest);
napi_status jsxlsxio_create_pointer(napi_env env, void *value,
                                    napi_value *result);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // JSXLSXIO_POINTERS_H
