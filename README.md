# jsxlsxio

jsxlsxio is a N-API wrapper exposing the functions of the C library xlsxio from brechtsanders (https://github.com/brechtsanders/xlsxio).

## Get started

To use this wrapper, you just need to include the module in your script using `require('jsxlsxio')` and all functions are available through it.

For example, importing it and printing the content of the module in a node CLI will show this kind of output:

```
> const jsxlsxio = require('jsxlsxio');
undefined
> jsxlsxio
{ xlsxioread_close: [Function: xlsxioread_close],
  xlsxioread_get_version_string: [Function: xlsxioread_get_version_string],
  xlsxioread_get_version: [Function: xlsxioread_get_version],
  xlsxioread_list_sheets: [Function: xlsxioread_list_sheets],
  xlsxioread_open: [Function: xlsxioread_open],
  xlsxioread_open_filehandle: [Function: xlsxioread_open_filehandle],
  xlsxioread_open_memory: [Function: xlsxioread_open_memory],
  xlsxioread_process: [Function: xlsxioread_process],
  xlsxioread_sheet_close: [Function: xlsxioread_sheet_close],
  xlsxioread_sheet_next_cell: [Function: xlsxioread_sheet_next_cell],
  xlsxioread_sheet_next_cell_datetime: [Function: xlsxioread_sheet_next_cell_dat
etime],
  xlsxioread_sheet_next_cell_float: [Function: xlsxioread_sheet_next_cell_float]
,
  xlsxioread_sheet_next_cell_int: [Function: xlsxioread_sheet_next_cell_int],
  xlsxioread_sheet_next_cell_string: [Function: xlsxioread_sheet_next_cell_strin
g],
  xlsxioread_sheet_next_row: [Function: xlsxioread_sheet_next_row],
  xlsxioread_sheet_open: [Function: xlsxioread_sheet_open],
  xlsxioread_sheetlist_close: [Function: xlsxioread_sheetlist_close],
  xlsxioread_sheetlist_next: [Function: xlsxioread_sheetlist_next],
  xlsxioread_sheetlist_open: [Function: xlsxioread_sheetlist_open],
  xlsxiowrite_add_cell_datetime: [Function: xlsxiowrite_add_cell_datetime],
  xlsxiowrite_add_cell_float: [Function: xlsxiowrite_add_cell_float],
  xlsxiowrite_add_cell_int: [Function: xlsxiowrite_add_cell_int],
  xlsxiowrite_add_cell_string: [Function: xlsxiowrite_add_cell_string],
  xlsxiowrite_add_column: [Function: xlsxiowrite_add_column],
  xlsxiowrite_close: [Function: xlsxiowrite_close],
  xlsxiowrite_get_version_string: [Function: xlsxiowrite_get_version_string],
  xlsxiowrite_get_version: [Function: xlsxiowrite_get_version],
  xlsxiowrite_next_row: [Function: xlsxiowrite_next_row],
  xlsxiowrite_open: [Function: xlsxiowrite_open],
  xlsxiowrite_set_detection_rows: [Function: xlsxiowrite_set_detection_rows],
  xlsxiowrite_set_row_height: [Function: xlsxiowrite_set_row_height],
}
```
