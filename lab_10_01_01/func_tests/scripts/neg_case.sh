#!/bin/bash

path="./func_tests/data"
if [ $# == 1 ]; then
    file_args=$(cat "$path/$1")
else
    exit 3
fi

if [ ! -e "./app.exe" ]; then
    exit 4
fi

./app.exe "$file_args"
result=$?

if [ $result -ne 0 ]; then
    exit 0
else
    exit 1
fi
