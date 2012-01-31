#!/bin/sh

cd ./pdns-2.9.22
./bootstrap && ./configure --without-modules --with-dynmodules="python"
cd ./modules/pythonbackend/
make clean && make && strip ./.libs/libpythonbackend.so
