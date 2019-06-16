const jsxlsxio = require('../jsxlsxio');

var workbook;
var sheetlist;
var sheet;

test('Opening a non-existing file for reading should return undefined', () => {
    expect(workbook = jsxlsxio.xlsxioread_open('lol.xlsx')).toBeUndefined();
});

test('Opening an existing xlsx file for reading should return a pointer', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
});

test('Closing an opened xlsxs file for reading should return undefined', () => {
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

if (process.platform !== 'win32') {
    test('Opening a file by its file descriptor should return a pointer', () => {
        var fd = fs.openSync(fd, 'r');
        expect(fd).toBeDefined();
        expect(typeof(workbook = jsxlsxio.xlsxioread_open_filehandle(fd))).toEqual('number');
    });

    test('Closing a file opened by its file descriptor should return undefined', () => {
        expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
    });
}

test('Opening a file located in memory by its pointer should return a pointer', () => {
    expect(true).toBeTruthy();
});

test('Closing a file opened in memory by its pointer should return undefined', () => {
    expect(true).toBeTruthy();
});

test('Requesting the version of the internal read library should return an object', () => {
    expect(typeof(jsxlsxio.xlsxioread_get_version())).toEqual('object');
});

test('Requesting the version string of the internal read library should return a string', () => {
    expect(typeof(jsxlsxio.xlsxioread_get_version_string())).toEqual('string');
});

test('Requesting asynchronous sheets listing should call a callback and give it the name of a sheet', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    jsxlsxio.xlsxioread_list_sheets(workbook, (name) => {
        expect(typeof(name)).toEqual('string');
    });
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Opening a list of sheets names from a null pointer should return undefined', () => {
    expect(sheetlist = jsxlsxio.xlsxioread_sheetlist_open(null)).toBeUndefined();
});

test('Opening a list of sheets names from an opened workbook should return a pointer', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheetlist = jsxlsxio.xlsxioread_sheetlist_open(workbook))).toEqual('number');
});

test('Closing an opened list of sheets names should return undefined', () => {
    expect(jsxlsxio.xlsxioread_sheetlist_close(sheetlist)).toBeUndefined();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Iterating through a list of sheets names from an opened workbook should return a string at each call terminated by undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheetlist = jsxlsxio.xlsxioread_sheetlist_open(workbook))).toEqual('number');
    var name;
    while (name = jsxlsxio.xlsxioread_sheetlist_next(sheetlist)) {
        expect(typeof(name)).toEqual('string');
    }
    expect(typeof(name)).toEqual('undefined');
    expect(jsxlsxio.xlsxioread_sheetlist_close(sheetlist)).toBeUndefined();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Iterating asynchronously through a sheet should call both row and cell callbacks and return undefined', (done) => {
    var cell_called = false;
    var row_called = false;
    const foo = ['hello', 'world'];
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(jsxlsxio.xlsxioread_process(workbook, 'Feuil1', 0, (row, col, value, data) => {
        cell_called = true;
        expect(typeof(row)).toEqual('number');
        expect(typeof(col)).toEqual('number');
        expect(typeof(value)).toEqual('string');
        expect(typeof(data)).toEqual('object');
        expect(data[0]).toEqual('hello');
        expect(data[1]).toEqual('world');
        done();
    },
    (row, maxcol, data) => {
        row_called = true;
        expect(typeof(row)).toEqual('number');
        expect(typeof(maxcol)).toEqual('number');
        expect(typeof(data)).toEqual('object');
        expect(data[0]).toEqual('hello');
        expect(data[1]).toEqual('world');
    },
    foo));
    expect(cell_called).toBeTruthy();
    expect(row_called).toBeTruthy();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Iterating asynchronously through a sheet without specifying its name should use the first sheet and call both row and cell callbacks then return undefined', (done) => {
    var cell_called = false;
    var row_called = false;
    const foo = ['hello', 'world'];
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(jsxlsxio.xlsxioread_process(workbook, undefined, 0, (row, col, value, data) => {
        cell_called = true;
        expect(typeof(row)).toEqual('number');
        expect(typeof(col)).toEqual('number');
        expect(typeof(value)).toEqual('string');
        expect(typeof(data)).toEqual('object');
        expect(data[0]).toEqual('hello');
        expect(data[1]).toEqual('world');
        done();
    },
    (row, maxcol, data) => {
        row_called = true;
        expect(typeof(row)).toEqual('number');
        expect(typeof(maxcol)).toEqual('number');
        expect(typeof(data)).toEqual('object');
        expect(data[0]).toEqual('hello');
        expect(data[1]).toEqual('world');
    },
    foo));
    expect(cell_called).toBeTruthy();
    expect(row_called).toBeTruthy();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Opening an existing sheet of a workbook using its name should return a pointer', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, 'Feuil1', 0))).toEqual('number');
});

test('Closing an opened sheet of a workbook should return undefined', () => {
    expect(jsxlsxio.xlsxioread_sheet_close(sheet)).toBeUndefined();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Opening the first sheet of a workbook should return a pointer', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
});

test('Closing the first sheet of a workbook should return undefined', () => {
    expect(jsxlsxio.xlsxioread_sheet_close(sheet)).toBeUndefined();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Opening an non-existant sheet of a workbook should return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, 'lol', 0))).toEqual('number');
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Reading the next row from a sheet should return a number', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Trying to read the next row from a sheet having reached its end should return 0', () => {
    var idx;
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    while (idx = jsxlsxio.xlsxioread_sheet_next_row(sheet));
    expect(idx).toEqual(0);
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Reading the next cell value from a sheet should return a string', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_cell(sheet))).toEqual('string');
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Trying to read the next cell value from a row having reached its end should return undefined', () => {
    var cell;
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    while (typeof(cell = jsxlsxio.xlsxioread_sheet_next_cell(sheet)) === 'string');
    expect(cell).toBeUndefined();
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Reading the next cell value from a sheet as a string should return a string', () => {
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_cell_string(sheet))).toEqual('string');
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Reading the next cell value from a sheet as an integer should return a number', () => {
    var cell;
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(typeof(cell = jsxlsxio.xlsxioread_sheet_next_cell_int(sheet))).toEqual('number');
    expect(cell).toEqual(1);
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Reading the next cell value from a sheet as a float should return a number', () => {
    var cell;
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(typeof(cell = jsxlsxio.xlsxioread_sheet_next_cell_float(sheet))).toEqual('number');
    expect(cell).toEqual(1.23);
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Reading the next cell value from a sheet as a date should return a number', () => {
    var cell;
    expect(typeof(workbook = jsxlsxio.xlsxioread_open('./test/example.xlsx'))).toEqual('number');
    expect(typeof(sheet = jsxlsxio.xlsxioread_sheet_open(workbook, undefined, 0))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(typeof(jsxlsxio.xlsxioread_sheet_next_row(sheet))).toEqual('number');
    expect(typeof(cell = jsxlsxio.xlsxioread_sheet_next_cell_datetime(sheet))).toEqual('number');
    expect(jsxlsxio.xlsxioread_close(workbook)).toBeUndefined();
});

test('Opening a workbook in writing mode should return a pointer', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('unit_test.xlsx', 'test'))).toEqual('number');
});

test('Closing a workbook opened in writing mode should return 0', () => {
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Requesting the version of the internal write library should return an object', () => {
    expect(typeof(jsxlsxio.xlsxiowrite_get_version())).toEqual('object');
});

test('Requesting the version string of the internal write library should return a string', () => {
    expect(typeof(jsxlsxio.xlsxiowrite_get_version_string())).toEqual('string');
});

test('Setting the number of detection rows in a workbook should return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_rows.xlsx', 'test_rows'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_set_detection_rows(workbook, 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Setting the row height in a workbook should return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_height.xlsx', 'test_height'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_set_row_height(workbook, 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Adding a column in a workbook should return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_column.xlsx', 'test_column'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_add_column(workbook, 'Foo', 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Moving to the next row in a workbook should create a new one and return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_next_row.xlsx', 'test_next_row'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_add_column(workbook, 'Foo', 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_next_row(workbook)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Adding a cell using a string value should write its content in a new cell and return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_string.xlsx', 'test_string'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_add_column(workbook, 'Foo', 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_next_row(workbook)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_add_cell_string(workbook, 'Hello, World!')).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Adding a cell using an integer value should write its content in a new cell and return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_int.xlsx', 'test_int'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_add_column(workbook, 'Foo', 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_next_row(workbook)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_add_cell_int(workbook, 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Adding a cell using a float value should write its content in a new cell and return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_float.xlsx', 'test_float'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_add_column(workbook, 'Foo', 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_next_row(workbook)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_add_cell_float(workbook, 3.14)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});

test('Adding a cell using a datetime value should write its content in a new cell and return undefined', () => {
    expect(typeof(workbook = jsxlsxio.xlsxiowrite_open('test_date.xlsx', 'test_date'))).toEqual('number');
    expect(jsxlsxio.xlsxiowrite_add_column(workbook, 'Foo', 42)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_next_row(workbook)).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_add_cell_datetime(workbook, Date.now())).toBeUndefined();
    expect(jsxlsxio.xlsxiowrite_close(workbook)).toEqual(0);
});
