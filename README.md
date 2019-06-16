# jsxlsxio

jsxlsxio is a N-API wrapper exposing the functions of the C library xlsxio from brechtsanders (https://github.com/brechtsanders/xlsxio).

Note: it's currently only exposing the C part to Node.js and requires a JS abstraction layer to handle things such as memory management which shouldn't exist.

## How to install

Just use `npm i jsxlsxio` to install the package in your `node_modules` projects or `npm i jsxlsxio --save` to also add it to your `package.json`.

If no prebuilt native module exist for your system, the module will try to build it.
However, it requires a C/C++ compiler toolchain to be present in your system and the development versions of the `minizip`, `expat` and `xlsxio` libraries to be present on your system (at least the compiled libraries with their headers, such as `lib*-dev` packages on repositories).

You can also compile this module from the sources by cloning this repository and using the command `npm run compile`.
This way, you can also create a `deps/` directory inside the root of this module and it will look for the headers and libraries in the `include/` and `lib/`sub-directories if you don't want to use your system versions of the libraries.

The `compile` script has 4 variations:
- `npm run compile`: will compile the module in release version corresponding to your platform
- `npm run compile:debug`: will compile the module in release version corresponding to your platform
- `npm run compile:i686`: will cross-compile the module in release version for x86 variant of your platform (supposing your using an x86_64 processor)
- `npm run compile:i6868-debug`: will cross-compile the module in release version for x86 variant of your platform (supposing your using an x86_64 processor)

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

## Read functions

All functions related to the reading of an Excel file are exposed on the `xlsxioread_*` functions. Here's the list of them:

- `xlsxioread_open(filepath)`
  + Parameters:
    - `filepath`: the filepath of the workbook to open (as a `string`)
  + Return: a pointer on the opened workbook on success, else returns `undefined`
  + Description: opens a workbook by passing its path as parameter
- `xlsxioread_open_filehandle(fd)`
  + Parameters:
    - `fd`: the file descriptor of the workbook to open (a `number`)
  + Return: a pointer on the opened workbook on success, else returns `undefined`
  + Description: opens a workbook by giving the file descriptor associated to it
- `xlsxioread_open_memory(data, datalen, freedata)`
  + Parameters:
    - `data`: a pointer (a `number`) on the starting location of the workbook in memory
    - `datalen`: the length (in bytes, represented as a `number`) of the workbook in memory
    - `freedata`: a value (a `number`) representing if the memory where the workbook is stored will be freed or not (any non-0 values) when `xlsxioread_close` is called
  + Return: a pointer on the opened workbook on success, else returns `undefined`
  + Description: opens an in-memory stored workbook
- `xlsxioread_close(workbook)`
  + Parameters:
    - `workbook`: a pointer (a `number`) on the workbook to close
  + Return: nothing (`undefined`)
  + Description: closes the workbook on the pointer passed as parameter
- `xlsxioread_get_version()`
  + Parameters: nothing
  + Return: a list of integers representing the version of the C xlsxio library version (symver notation)
  + Description: get the version of the C xlsxio library used by the module
- `xlsxioread_get_version_string()`
  + Parameters: nothing
  + Return: a `string` representing the version of the C xlsxio library version (symver notation)
  + Description: get the version of the C xlsxio library used by the module
- `xlsxioread_list_sheets(workbook, callback, data)`
  + Parameters:
    - `workbook`: a pointer (a `number`) on an opened workbook
    - `callback`: a function to call back every time a sheet name is ready (taking two parameters: the name of the sheet as as string and a user defined variable as the second parameter). The function should be something like `function mycallback(sheet_name, data)`
    - `data:`a customisable user data to give as the second parameter of the callback
  + Return: nothing
  + Description: set a callback to call every time a workbook sheet name is found and start the parsing
- `xlsxioread_sheetlist_open(workbook)`
  + Parameters:
    - `workbook`: a pointer (a `number`) on an opened workbook
  + Return: a pointer (a `number`) on a list of workbook sheets names
  + Description: create a list of workbook sheets names which can be iterated using `xlsxioread_sheetlist_next` and freed using `xlsxioread_sheelist_close`
- `xlsxioread_sheetlist_next(sheetlist)`
  + Parameters:
    - `sheetlist`: a pointer (a `number`) on a list of workbook sheets
  + Return: the next sheet name as a `string` or `undefined` if there are no more sheets to retrieve names
  + Description: retrieve the next workbook sheet name
- `xlsxioread_sheetlist_close(sheetlist)`
  + Parameters:
    - `sheetlist`: close the sheetlist passed as a pointer (a `number`) and free its memory
  + Return: nothing (`undefined`)
  + Description: close the sheetlist passed as a pointer (a `number`) and free its memory
- `xlsxioread_process(workbook, sheet_name, flags, cell_callback, row_callback, data)`
  + Parameters:
    - `workbook`: a pointer on an opened workbook (a `number`)
    - `sheet_name`: the name of the sheet to open or `undefined` to open the first one
    - `flags`: flags (a `number`) to control how the xlsxio library will read the content of the worksheet
    - `cell_callback`: a function of the format `myfunction(row, col, value, data)` which will be called every time a cell is ready to be processed
      + `row`: a `number` representing the number of the row in the sheet
      + `col`: a `number` representing the column position in the sheet
      + `value`: a `string` representing the value in the cell
      + `data`: the object passed in the `data` parameter of the `xlsxioread_process` function
    - `row_callback`: a function of the format `myfunction(row, maxcol, data)` which will be called every time a row is ready to be processed
      + `row`: a `number` representing the number of the row in the sheet
      + `maxcol`: a `number` representing the index of the latest column in the row
      + `data`: the object passed in the `data` parameter of the `xlsxioread_process` function
    - `data`: an object to pass to callback functions when calling them
  + Return: nothing (`undefined`)
  + Description: open a workbook, process it automatically by calling callback functions passed as parameters and close the workbook once it finishes
- `xlsxioread_sheet_open(workbook, sheet_name, flags)`
  + Parameters:
    - `workbook`: a pointer on an opened workbook (a `number`)
    - `sheet_name`: the name of the sheet to open or `undefined` to open the first one
    - `flags`: flags (a `number`) to control how the xlsxio library will read the content of the worksheet
  + Return: a pointer on the opened worksheet (a `number`) and `undefined` in case of failure
  + Description: open a worksheet in the workbook and return a pointer on it so it can be processed manually by the user
- `xlsxioread_sheet_close(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: nothing (`undefined`)
  + Description: close the worksheet passed as parameter and free its memory
- `xlsxioread_sheet_next_row(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: the index of the new current row (a `number`) if there's one else return 0 (as the first row is 1)
  + Description: move the current row to the next in the worksheet
- `xlsxioread_sheet_next_cell(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: the value of the next cell to read in the row as a `string` if there's one else `undefined`
  + Description: read and return the value of the next cell in the worksheet and update the cursor
- `xlsxioread_sheet_next_cell_string(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: the value of the next cell to read in the row as a `string` if there's one else `undefined`
  + Description: read and return the value of the next cell in the worksheet and update the cursor
- `xlsxioread_sheet_next_cell_int(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: the value of the next cell to read in the row as a `number` if there's one else `undefined`
  + Description: read and return the value of the next cell in the worksheet and update the cursor
- `xlsxioread_sheet_next_cell_float(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: the value of the next cell to read in the row as a `number` if there's one else `undefined`
  + Description: read and return the value of the next cell in the worksheet and update the cursor
- `xlsxioread_sheet_next_cell_datetime(worksheet)`
  + Parameters:
    - `worksheet`: a pointer on a worksheet opened by `xlsxioread_sheet_open` (a `number`)
  + Return: the value of the next cell to read in the row as a `number` if there's one else `undefined`
  + Description: read and return the value of the next cell in the worksheet and update the cursor. The datetime is represented as a timestamp

## Write functions

All functions related to the reading of an Excel file are exposed on the `xlsxiowrite_*` functions. Here's the list of them:

- `xlsxiowrite_open(filepath, sheetname)`
  + Parameters:
    - `filepath`: the filepath of the workbook to open (as a `string`)
    - `sheetname`: the name of the sheet to write in the worksheet (as a `string`)
  + Return: a pointer on the opened worksheet on success, else returns `undefined`
  + Description: opens a worksheet by passing its path and name of the sheet as parameters
- `xlsxiowrite_close(worksheet)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to close
  + Return: 0 on success
  + Description: closes the worksheet on the pointer passed as parameter
- `xlsxiowrite_get_version()`
  + Parameters: nothing
  + Return: a list of integers representing the version of the C xlsxio library version (symver notation)
  + Description: get the version of the C xlsxio library used by the module
- `xlsxiowrite_get_version_string()`
  + Parameters: nothing
  + Return: a `string` representing the version of the C xlsxio library version (symver notation)
  + Description: get the version of the C xlsxio library used by the module
- `xlsxiowrite_set_detection_rows(worksheet, rows)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `rows`: the number of rows used to compute the width of columns (as a `number`)
  + Return: nothing (`undefined`)
  + Description: set the number of rows used to compute the width of the columns in the worksheet
- `xlsxiowrite_set_row_height(worksheet, height)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `height`: the height of the rows (in text lines, as a `number`) in the worksheet
  + Return: nothing (`undefined`)
  + Description: set the height of the rows in the worksheet
- `xlsxiowrite_add_column(worksheet, name, width)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `name`: name of the column to add (a `string`)
    - `width`: width of the column to add
  + Return: nothing (`undefined`)
  + Description: add a column to the worksheet. Must be called before any `xlsxiowrite_next_row` or `xlsxiowrite_add_cell_*` function
- `xlsxiowrite_next_row(worksheet)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
  + Return: nothing (`undefined`)
  + Description: end current row the row and create a new one next time a `xlsxiowrite_add_cell_*` function is called
- `xlsxiowrite_add_cell_string(worksheet, value)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `value`: content to write in the cell added in the worksheet as `string`
  + Return: nothing (`undefined`)
  + Description: set the content of the cell to add in worksheet
- `xlsxiowrite_add_cell_int(worksheet, value)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `value`: content to write in the cell added in the worksheet as a `number` (integer values only)
  + Return: nothing (`undefined`)
  + Description: set the content of the cell to add in worksheet
- `xlsxiowrite_add_cell_float(worksheet, value)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `value`: content to write in the cell added in the worksheet as a `number`
  + Return: nothing (`undefined`)
  + Description: set the content of the cell to add in worksheet
- `xlsxiowrite_add_cell_datetime(worksheet, value)`
  + Parameters:
    - `worksheet`: a pointer (a `number`) on the worksheet to use
    - `value`: content to write in the cell added in the worksheet as a `number` (represented by a timestamp)
  + Return: nothing (`undefined`)
  + Description: set the content of the cell to add in worksheet
