#!/bin/bash

if [ ! -e debug.exe ]; then
    echo "Not main.exe"
else
    cd func_tests/scripts/
    ./func_tests.sh
    cd ../..
    echo
    gcov debug-main.c
fi
