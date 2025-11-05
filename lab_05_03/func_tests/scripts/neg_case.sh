#!/bin/bash

path="../data"
if [ $# == 2 ]; then
    if [ -f "$path/$1" ] && [ -f "$path/$2" ]; then
        file_in="$path/$1"
        file_args="$path/$2"
    else
        exit 2
    fi
else
    exit 3
fi

if [ ! -e "../../debug.exe" ]; then
    exit 4
fi

read -r key file_args <<< "$file_args"

if [ "$key" == "p" ]; then
    ../../debug.exe import "$file_in" "../../$file_args" 
    ../../debug.exe p "../../$file_args" >"$1.file_out_result"
else
     ../../debug.exe import "$file_in" "../../$file_args" 
    ../../debug.exe s "../../$file_args"
fi

result=$?

if [ $result -ne 0 ]; then
    exit 0
else
    exit 1
fi
