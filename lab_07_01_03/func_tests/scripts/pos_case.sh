#!/bin/bash

path="../data"
if [ $# == 4 ]; then
    if [ -f "$path/$1" ] && [ -f "$path/$2" ] && [ -f "$path/$3" ]; then
        file_in="$path/$1"
        file_out_expect="$path/$3"
        file_args=$(cat $path/"$2")
        file_out_res="$path/$4"
    else
        exit 2
    fi
else
    exit 3
fi

if [ ! -e "../../app.exe" ]; then
    exit 4
fi

cd ../.. || exit
./app.exe ./$file_args
result=$?
cd func_tests/scripts/ || exit

if [ $result -ne 0 ]; then
    exit 5
fi

./comparator.sh "$file_out_expect" "$file_out_res"
result=$?

if [ $result -eq 0 ]; then
    exit 0
elif [ $result -eq 1 ]; then
    exit 1
else
    exit 6
fi
