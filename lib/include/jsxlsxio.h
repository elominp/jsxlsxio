#ifndef JSXLSXIO_H
#define JSXLSXIO_H

#define NAPI_VERSION 3
#include <node_api.h>

#define BUFFER_SIZE 1024

#define CREATE_EMPTY_STRING(env, result) \
  napi_create_string_utf8(env, "", 0, result)

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
typedef napi_value (*wrapper_initializer)(napi_env);
typedef napi_status (*wrapper_setter)(napi_env, napi_value);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // JSXLSXIO_H