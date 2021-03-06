#include "jsxlsxio.h"
#include <assert.h>
#include <stdlib.h>
#include "xlsxioread_close.h"
#include "xlsxioread_get_version.h"
#include "xlsxioread_get_version_string.h"
#include "xlsxioread_list_sheets.h"
#include "xlsxioread_open.h"
#include "xlsxioread_open_filehandle.h"
#include "xlsxioread_open_memory.h"
#include "xlsxioread_process.h"
#include "xlsxioread_sheet_close.h"
#include "xlsxioread_sheet_next_cell.h"
#include "xlsxioread_sheet_next_cell_datetime.h"
#include "xlsxioread_sheet_next_cell_float.h"
#include "xlsxioread_sheet_next_cell_int.h"
#include "xlsxioread_sheet_next_cell_string.h"
#include "xlsxioread_sheet_next_row.h"
#include "xlsxioread_sheet_open.h"
#include "xlsxioread_sheetlist_close.h"
#include "xlsxioread_sheetlist_next.h"
#include "xlsxioread_sheetlist_open.h"
#include "xlsxiowrite_add_cell_datetime.h"
#include "xlsxiowrite_add_cell_float.h"
#include "xlsxiowrite_add_cell_int.h"
#include "xlsxiowrite_add_cell_string.h"
#include "xlsxiowrite_add_column.h"
#include "xlsxiowrite_close.h"
#include "xlsxiowrite_get_version.h"
#include "xlsxiowrite_get_version_string.h"
#include "xlsxiowrite_next_row.h"
#include "xlsxiowrite_open.h"
#include "xlsxiowrite_set_detection_rows.h"
#include "xlsxiowrite_set_row_height.h"

static const wrapper_setter setters[] = {
    set_xlsxioread_close_wrapper,
    set_xlsxioread_get_version_string_wrapper,
    set_xlsxioread_get_version_wrapper,
    set_xlsxioread_list_sheets_wrapper,
    set_xlsxioread_open_wrapper,
    set_xlsxioread_open_filehandle_wrapper,
    set_xlsxioread_open_memory_wrapper,
    set_xlsxioread_process_wrapper,
    set_xlsxioread_sheet_close_wrapper,
    set_xlsxioread_sheet_next_cell_wrapper,
    set_xlsxioread_sheet_next_cell_datetime_wrapper,
    set_xlsxioread_sheet_next_cell_float_wrapper,
    set_xlsxioread_sheet_next_cell_int_wrapper,
    set_xlsxioread_sheet_next_cell_string_wrapper,
    set_xlsxioread_sheet_next_row_wrapper,
    set_xlsxioread_sheet_open_wrapper,
    set_xlsxioread_sheetlist_close_wrapper,
    set_xlsxioread_sheetlist_next_wrapper,
    set_xlsxioread_sheetlist_open_wrapper,
    set_xlsxiowrite_add_cell_datetime_wrapper,
    set_xlsxiowrite_add_cell_float_wrapper,
    set_xlsxiowrite_add_cell_int_wrapper,
    set_xlsxiowrite_add_cell_string_wrapper,
    set_xlsxiowrite_add_column_wrapper,
    set_xlsxiowrite_close_wrapper,
    set_xlsxiowrite_get_version_string_wrapper,
    set_xlsxiowrite_get_version_wrapper,
    set_xlsxiowrite_next_row_wrapper,
    set_xlsxiowrite_open_wrapper,
    set_xlsxiowrite_set_detection_rows_wrapper,
    set_xlsxiowrite_set_row_height_wrapper,
    NULL};

void init_log_streams(void) {
  log_stdout = stdout;
  log_stdinf = stdout;
  log_stddbg = stdout;
  log_stdwrn = stdout;
  log_stderr = stderr;
  atexit(flush_logs);
}

napi_value Init(napi_env env, napi_value exports) {
  init_log_streams();
  for (size_t i = 0; setters[i] != NULL; i++) {
    EXPECT(setters[i](env, exports) == napi_ok);
  }
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
