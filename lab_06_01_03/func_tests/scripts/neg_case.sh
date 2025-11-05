#!/bin/bash

path="../data"
if [ $# == 1 ]; then
    if [ -f "$path/$1" ]; then
        file_args=$(cat $path/"$1")
    else
        exit 2
    fi
else
    exit 3
fi

if [ ! -e "../../debug.exe" ]; then
    exit 4
fi

../../debug.exe "$file_args"
result=$?

if [ $result -ne 0 ]; then
    exit 0
else
    exit 1
fi
