#!/bin/bash

path="../data"
if [ $# == 3 ]; then
    if [ -f "$path/$3" ]; then
        input="$path/$1"
        file_input="$path/$2"
        file_args="$path/$3"
    else
        exit 2
    fi
else
    exit 3
fi

if [ ! -e "../../debug.exe" ]; then
    exit 4
fi

read -r key arg1 arg2 <<< "$file_args"

if [ "$key" == "st" ]; then
    ../../debug.exe st "../../$arg1" "../../$arg2"
    result=$?
elif [ "$key" == "ft" ]; then
    ../../debug.exe ft "../../$arg1" "../../$arg2" >"$file_input.file_out_result"
    result=$?
else
    if [  -f $file_input ]; then
        work=${file_input/neg/work}
        cp $file_input $work
    fi
    
    ../../debug.exe at "../../$arg1"
    result=$?
fi

if [ $result -ne 0 ]; then
    exit 0
else
    exit 1
fi
