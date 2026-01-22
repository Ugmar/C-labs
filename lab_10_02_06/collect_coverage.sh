#!/bin/bash

./func_tests/scripts/func_tests.sh
echo
gcov -o out/ src/*.c
mv *.gcov out/
