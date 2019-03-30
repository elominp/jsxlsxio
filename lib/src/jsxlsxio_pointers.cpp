#include <cstddef>
#include <cstdint>

#define NAPI_VERSION 3
#include <node_api.h>

#if __cplusplus >= 201703L
#define IF_CONSTEXPR if constexpr
#define ELSE_IF_CONSTEXPR else if constexpr
#else
#define IF_CONSTEXPR if
#define ELSE_IF_CONSTEXPR else if
#endif  // __cplusplus >= 201703L

constexpr std::size_t get_pointer_size() { return sizeof(void *); }

static constexpr std::size_t pointer_size = get_pointer_size();

static napi_status jsxlsxio_get_8bit_pointer(napi_env env, napi_value value,
                                             void **dest) {
  napi_status status = napi_ok;
  std::uint32_t buf = 0;

  status = napi_get_value_uint32(env, value, &buf);
  buf &= 0xFF;
  *dest = reinterpret_cast<void *>(buf);
  return status;
}

static napi_status jsxlsxio_get_16bit_pointer(napi_env env, napi_value value,
                                              void **dest) {
  napi_status status = napi_ok;
  std::uint32_t buf = 0;

  status = napi_get_value_uint32(env, value, &buf);
  buf &= 0xFFFF;
  *dest = reinterpret_cast<void *>(buf);
  return status;
}

static napi_status jsxlsxio_get_32bit_pointer(napi_env env, napi_value value,
                                              void **dest) {
  napi_status status = napi_ok;
  std::uint32_t buf = 0;

  status = napi_get_value_uint32(env, value, &buf);
  *dest = reinterpret_cast<void *>(buf);
  return status;
}

static napi_status jsxlsxio_create_32bit_pointer(napi_env env, void *value,
                                                 napi_value *result) {
  return napi_create_uint32(env, (std::uint32_t)((std::size_t)value), result);
}

static napi_status jsxlsxio_get_64bit_pointer(napi_env env, napi_value value,
                                              void **dest) {
  napi_status status = napi_ok;
  std::int64_t buf = 0;

  status = napi_get_value_int64(env, value, &buf);
  *dest = reinterpret_cast<void *>(buf);
  return status;
}

static napi_status jsxlsxio_create_64bit_pointer(napi_env env, void *value,
                                                 napi_value *result) {
  return napi_create_int64(env, reinterpret_cast<std::int64_t>(value), result);
}

extern "C" {
napi_status jsxlsxio_get_pointer(napi_env env, napi_value value, void **dest) {
  IF_CONSTEXPR(pointer_size == 1) {  // Probably impossible
    return jsxlsxio_get_8bit_pointer(env, value, dest);
  }
  ELSE_IF_CONSTEXPR(pointer_size == 2) {
    return jsxlsxio_get_16bit_pointer(env, value, dest);
  }
  ELSE_IF_CONSTEXPR(pointer_size == 4) {
    return jsxlsxio_get_32bit_pointer(env, value, dest);
  }
  ELSE_IF_CONSTEXPR(pointer_size == 8) {
    return jsxlsxio_get_64bit_pointer(env, value, dest);
  }
  else {
    return napi_generic_failure;
  }
}

napi_status jsxlsxio_create_pointer(napi_env env, void *value,
                                    napi_value *result) {
  IF_CONSTEXPR(pointer_size <= 4) {
    return jsxlsxio_create_32bit_pointer(env, value, result);
  }
  ELSE_IF_CONSTEXPR(pointer_size <= 8) {
    return jsxlsxio_create_64bit_pointer(env, value, result);
  }
  else {
    return napi_generic_failure;
  }
}
}
