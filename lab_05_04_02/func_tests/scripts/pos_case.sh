#!/bin/bash

path="../data"
if [ $# == 5 ]; then
    if [ -f "$path/$1" ] && [ -f "$path/$2" ] && [ -f "$path/$3" ] && [ -f "$path/$4" ] && [ -f "$path/$5" ]; then
        input="$path/$1"
        output="$path/$2"
        file_args=$(cat $path/"$3")
        file_input="$path/$4"
        file_output="$path/$5"
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
    ../../debug.exe $key "../../$arg1" "../../$arg2"
    result=$?

    if [ $result -ne 0 ]; then
        exit 5
    fi

    work=${file_input/pos/out}
    ./comparator.sh "$work" "$file_output"
elif [ "$key" == "ft" ]; then
    ../../debug.exe "$key" "../../$arg1" "$arg2" > "../../$arg1.file_out_result"
    result=$?

    if [ $result -ne 0 ]; then
        exit 5
    fi

    ./comparator.sh "$output" "../../$arg1.file_out_result"
else
    work=${file_input/pos/work}
    cp $file_input $work

    ../../debug.exe $key "../../$arg1" <$input
    result=$?

    if [ $result -ne 0 ]; then
        exit 5
    fi
    ./comparator.sh "$work" "$file_output"
fi

result=$?

if [ $result -eq 0 ]; then
    exit 0
elif [ $result -eq 1 ]; then
    exit 1
else
    exit 6
fi
