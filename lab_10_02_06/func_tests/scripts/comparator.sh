#!/bin/bash
# echo $1
# echo $2
# read
if [ $# == 2 ];then
    if [ -f "$1" ] && [ -f "$2" ]; then
        file1=$1
        file2=$2
    else
        echo "Not found files"
        exit 2
        fi
else
    echo "Uncorrect count value"
    exit 3
fi
if  diff $file1 $file2; then
    exit 0
else
    exit 1
fi
