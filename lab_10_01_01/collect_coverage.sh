#!/bin/bash

# cd func_tests/scripts/ || exit
./func_tests/scripts/func_tests.sh
# cd ../..
echo
gcov -o out/ src/*.c
mv *.gcov out/
