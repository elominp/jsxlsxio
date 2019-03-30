const jsxlsxio = require('../build/Release/JsXlsxio.node');
const fs = require('fs');

console.log(jsxlsxio.xlsxioread_get_version());

const file = jsxlsxio.xlsxioread_open('shared/place-de-la-nation-flux.xlsx');
const fd = fs.openSync('log.txt', 'w');
const buf_length = 8388608;
var buf = Buffer.allocUnsafe(buf_length).fill('\0');
var idx = 0;

function print_sheet_name(name, data) {
    console.log(name);
    return name;
}

console.log('Printing sheet names...');
jsxlsxio.xlsxioread_list_sheets(file, print_sheet_name, [fd]);

function flush_buffered_write(fd) {
    fs.writeSync(fd, buf.toString('utf8', 0, idx));
}

function buffered_write(fd, data) {
    const res = String(data)
    if (idx + res.length < buf_length) {
        idx += buf.write(res, idx);
    } else {
        flush_buffered_write(fd);
        idx = buf.write(res);
    }
}

const sheet = jsxlsxio.xlsxioread_sheet_open(file, undefined, 0);

while (jsxlsxio.xlsxioread_sheet_next_row(sheet)) {
    var line = '';
    while (1) {
        const value = jsxlsxio.xlsxioread_sheet_next_cell(sheet);
        if (typeof (value) === 'undefined') {
            break;
        }
        line += value + ';'
    }
    line += '\n'
    buffered_write(fd, line);
}

jsxlsxio.xlsxioread_sheet_close(sheet);
jsxlsxio.xlsxioread_close(file);
flush_buffered_write(fd);
fs.closeSync(fd);
console.log('End of program...');
