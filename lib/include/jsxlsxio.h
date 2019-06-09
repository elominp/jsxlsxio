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
void flush_logs(void);
#ifdef __cplusplus
}
#endif  // __cplusplus

#ifdef __cplusplus
#include <cassert>
#include <cstdio>
#include <cstdlib>
#else
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#endif  // __cplusplus

extern FILE *log_stdout;
extern FILE *log_stdinf;
extern FILE *log_stddbg;
extern FILE *log_stdwrn;
extern FILE *log_stderr;

extern const char *assert_header;
extern const char *expect_header;

#define LOG_WRITER(stream, fmt, ...) fprintf(stream, fmt, __VA_ARGS__)
#define LOG_I(fmt, ...) LOG_WRITER(log_stdinf, fmt, __VA_ARGS__)
#define LOG_D(fmt, ...) LOG_WRITER(log_stddbg, fmt, __VA_ARGS__)
#define LOG_W(fmt, ...) LOG_WRITER(log_stdwrn, fmt, __VA_ARGS__)
#define LOG_E(fmt, ...) LOG_WRITER(log_stderr, fmt, __VA_ARGS__)

#ifndef ASSERTION_EXIT
#define ASSERTION_EXIT 1
#endif  // ASSERTION_EXIT

#ifdef NDEBUG
#if ASSERTION_EXIT
#define ASSERT(cdt)                                                      \
  if (!(cdt)) {                                                          \
    LOG_E("%s %s %s - line %d: %s\n", assert_header, __FILE__, __func__, \
          __LINE__, #cdt);                                               \
    exit(1);                                                             \
  }
#else
#define ASSERT(cdt)                                                      \
  if (!(cdt)) {                                                          \
    LOG_E("%s %s %s - line %d: %s\n", assert_header, __FILE__, __func__, \
          __LINE__, #cdt);                                               \
    return 0;                                                            \
  }
#endif  // ASSERTION_EXIT
#else
#define ASSERT(cdt) assert(cdt);
#endif  // NDEBUG
#define EXPECT(cdt)                                                      \
  if (!(cdt)) {                                                          \
    LOG_W("%s %s %s - line %d: %s\n", expect_header, __FILE__, __func__, \
          __LINE__, #cdt);                                               \
  }

#endif  // JSXLSXIO_H
