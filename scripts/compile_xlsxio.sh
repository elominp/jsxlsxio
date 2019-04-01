#!/usr/bin/env bash

LOCAL_PREFIX=$PWD/deps

mkdir -p deps/include
mkdir -p deps/lib
mkdir -p deps/bin
cd deps
git clone https://github.com/brechtsanders/xlsxio.git
mkdir xlsxio/tmp
cd xlsxio/tmp
cmake -DCMAKE_INSTALL_PREFIX=$LOCAL_PREFIX -DBUILD_TOOLS=OFF -DBUILD_EXAMPLES=OFF ..
make install
