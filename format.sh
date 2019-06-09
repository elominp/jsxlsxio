#!/usr/bin/env bash

function format {
  clang-format -i --style=google $@
}

cd lib
format $(find . -name "*.c")
format $(find . -name "*.cpp")
format $(find . -name "*.h")
format $(find . -name "*.hpp")
