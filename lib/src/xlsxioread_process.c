#include <xlsxio_read.h>
#include "xlsxioread_process.h"
#include "jsxlsxio_pointers.h"

static napi_ref cell_callback = NULL;
static napi_ref row_callback = NULL;
static napi_ref callback_data = NULL;
static napi_async_context async_context = NULL;
static napi_env async_env = NULL;

static int xlsxioread_process_init_napi_async(napi_env env) {
  napi_value name;
  const char *resource_name = "xlsxioread_process_async";

  async_env = env;
  ASSERT(napi_create_string_utf8(env, resource_name, strlen(resource_name),
                                 &name) == napi_ok);
  ASSERT(napi_async_init(env, NULL, name, &async_context) == napi_ok);
  return 0;
}

static int xlsxioread_process_destroy_napi_async(void) {
  if (async_context != NULL) {
    ASSERT(napi_async_destroy(async_env, async_context) == napi_ok);
    async_context = NULL;
  }
  return 0;
}

static int xlsxioread_process_row_callback(size_t row, size_t maxcol, void* callbackdata) {
  (void)callbackdata;

  napi_value argv[3];
  napi_value tocall;
  napi_value global;
  napi_value ret;

  ASSERT(napi_create_int64(async_env, (int64_t)row, &argv[0]) == napi_ok);
  ASSERT(napi_create_int64(async_env, (int64_t)maxcol, &argv[1]) == napi_ok);
  ASSERT(napi_get_reference_value(async_env, (napi_ref)callback_data,
                                  &argv[2]) == napi_ok);
  ASSERT(napi_get_reference_value(async_env, row_callback, &tocall) == napi_ok);
  ASSERT(napi_get_global(async_env, &global) == napi_ok);
  ASSERT(napi_make_callback(async_env, async_context, global, tocall, 3, argv,
                            &ret) == napi_ok);
  return 0;
}

static int xlsxioread_process_cell_callback(size_t row, size_t col, const XLSXIOCHAR* value, void* callbackdata) {
  (void)callbackdata;

  napi_value argv[4];
  napi_value tocall;
  napi_value global;
  napi_value ret;

  ASSERT(napi_create_int64(async_env, (int64_t)row, &argv[0]) == napi_ok);
  ASSERT(napi_create_int64(async_env, (int64_t)col, &argv[1]) == napi_ok);
  if (value != NULL) {
    ASSERT(napi_create_string_utf8(async_env, value, strlen(value), &argv[2]) ==
           napi_ok);
  } else {
    ASSERT(napi_get_undefined(async_env, &argv[2]) == napi_ok);
  }
  ASSERT(napi_get_reference_value(async_env, (napi_ref)callback_data,
                                  &argv[3]) == napi_ok);
  ASSERT(napi_get_reference_value(async_env, row_callback, &tocall) == napi_ok);
  ASSERT(napi_get_global(async_env, &global) == napi_ok);
  ASSERT(napi_make_callback(async_env, async_context, global, tocall, 4, argv,
                            &ret) == napi_ok);
  return 0;
}

static napi_value xlsxioread_process_wrapper(napi_env env,
                                                 napi_callback_info info) {
  napi_value argv[6];
  size_t argc = 6;
  xlsxioreader handle;
  char sheetname[BUFFER_SIZE];
  size_t sheetname_length;
  uint32_t flags;
  napi_value ret;

  ASSERT(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) == napi_ok);
  ASSERT(jsxlsxio_get_pointer(env, argv[0], (void **)&handle) == napi_ok);
  ASSERT(napi_get_value_string_utf8(env, argv[1], sheetname, BUFFER_SIZE,
                                    &sheetname_length) == napi_ok);
  ASSERT(sheetname_length >= 0 && sheetname_length < BUFFER_SIZE);
  sheetname[sheetname_length] = '\0';
  ASSERT(napi_get_value_uint32(env, argv[2], &flags) == napi_ok);
  if (cell_callback != NULL) {
    xlsxioread_process_destroy_napi_async();
    ASSERT(napi_delete_reference(env, cell_callback) == napi_ok);
  }
  ASSERT(napi_create_reference(env, argv[3], 1, &cell_callback) == napi_ok);
  if (row_callback != NULL) {
    xlsxioread_process_destroy_napi_async();
    ASSERT(napi_delete_reference(env, row_callback) == napi_ok);
  }
  ASSERT(napi_create_reference(env, argv[4], 1, &row_callback) == napi_ok);
  if (callback_data != NULL) {
    ASSERT(napi_delete_reference(env, callback_data) == napi_ok);
  }
  ASSERT(napi_create_reference(env, argv[5], 1, &callback_data) == napi_ok);
  xlsxioread_process_init_napi_async(env);
  xlsxioread_process(handle, sheetname, flags, xlsxioread_process_cell_callback, xlsxioread_process_row_callback,
                         callback_data);
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value create_xlsxioread_process_wrapper(napi_env env) {
  napi_value xlsxioread_process_function;

  ASSERT(napi_create_function(env, "xlsxioread_process", NAPI_AUTO_LENGTH,
                              xlsxioread_process_wrapper, NULL,
                              &xlsxioread_process_function) == napi_ok);
  return xlsxioread_process_function;
}

napi_status set_xlsxioread_process_wrapper(napi_env env,
                                               napi_value result) {
  return napi_set_named_property(env, result, "xlsxioread_process",
                                 create_xlsxioread_process_wrapper(env));
}
