#!/bin/bash


path="./func_tests/data"
if [ $# == 5 ]; then
    in="$path/$1"
    out="$path/$2"
    in_file="$path/$3"
    out_file="$path/$4"
    # args=$(cat "$path/$5")
else
    exit 3
fi

if [ ! -e "./app.exe" ]; then
    exit 4
fi

./app.exe <$in >"$out".out_result.txt
result=$?

if [ $result -ne 0 ]; then
    exit 5
fi

# ./func_tests/scripts/comparator.sh "$out_file" "$out.file_out_result.txt"
result1=0
./func_tests/scripts/comparator.sh "$out" "$out.out_result.txt"
result2=$?

if [ $result1 -eq 0 ] && [ $result2 -eq 0 ]; then
    exit 0
elif [ $result1 -eq 1 ] || [ $result2 -eq 1 ]; then
    exit 1
else
    exit 6
fi
