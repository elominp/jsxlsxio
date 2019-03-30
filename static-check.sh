#!/usr/bin/env bash

function cpp_check {
  cppcheck --includes-file=include $@
}

cd lib
cpp_check $(find . -name "*.c")
cpp_check $(find . -name "*.cpp")
cpp_check $(find . -name "*.h")
cpp_check $(find . -name "*.hpp")
cd -
