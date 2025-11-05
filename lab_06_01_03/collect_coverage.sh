#!/bin/bash

if [ ! -e debug.exe ]; then
    echo "Not main.exe"
else
    cd func_tests/scripts/ || exit
    ./func_tests.sh
    cd ../..
    echo
    gcov ./*.c
fi
