#!/bin/bash

path="../data"
if [ $# == 3 ]; then
    if [ -f "$path/$1" ] && [ -f "$path/$2" ] && [ -f "$path/$3" ]; then
        file_in="$path/$1"
        file_out_expect="$path/$2"
        file_args=$(cat $path/"$3")
    else
        exit 2
    fi
else
    exit 3
fi

if [ ! -e "../../debug.exe" ]; then
    exit 4
fi

../../debug.exe "../../$file_args" <"$file_in" >"$1.file_out_result"
result=$?

if [ $result -ne 0 ]; then
    exit 5
fi

./comparator.sh "$file_out_expect" "$1.file_out_result"
result=$?

if [ $result -eq 0 ]; then
    exit 0
elif [ $result -eq 1 ]; then
    exit 1
else
    exit 6
fi
