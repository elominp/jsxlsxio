const jsxlsxio = require('bindings')('jsxlsxio');
const fs = require('fs');

console.log(jsxlsxio.xlsxioread_get_version());

const file = jsxlsxio.xlsxioread_open('place-de-la-nation-flux.xlsx');
const fd = fs.openSync('log2.txt', 'w');
const buf_length = 8388608;
var buf = Buffer.allocUnsafe(buf_length).fill('\0');
var idx = 0;
var finished = false;

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

jsxlsxio.xlsxioread_process(file, undefined, 0, (row, col, value, data) => {
    if (typeof(value) !== 'undefined') {
        buffered_write(fd, value + ';');
    } else {
        buffered_write(fd, ';');
    }
},
(row, maxcol, data) => {
    buffered_write(fd, '\n');
},
buf);

jsxlsxio.xlsxioread_close(file);
flush_buffered_write(fd);
fs.closeSync(fd);
console.log('End of program...');
