#!/bin/bash

gcc -std=c99 -Wall -Werror --coverage main.c -o app.exe
cd func_tests/scripts/
./func_tests.sh
cd ../..
echo
gcov app-main.c
lcov -c -d ./ --output-file coverage.info
