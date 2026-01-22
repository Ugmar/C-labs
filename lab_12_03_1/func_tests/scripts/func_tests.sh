#!/bin/bash

i=1
failed_tests=0

echo "Start testing..."
for file_input in ../data/pos_*_in.txt; do

    echo -n "Positive test $i: "
    in_file="$(basename "$file_input" in.txt)in.txt"
    file_args="$(basename "$file_input" in.txt)args.txt"
    out_file="$(basename "$file_input" in.txt)out_file.txt"
    out_file_res="$(basename "$file_input" in.txt)out_file_res.txt"

    ./pos_case.sh "$in_file" "$file_args" "$out_file" "$out_file_res"
    result=$?

    if [ $result -eq 0 ]; then
        echo "Pass"
    elif [ $result -eq 2 ]; then
        echo "Files not founds"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 3 ]; then
        echo "Uncorrect count value"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 4 ]; then
        echo "app.exe not found"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 5 ]; then
        echo "app failed witn error"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 6 ]; then
        echo "Error comparator"
        failed_tests=$((failed_tests + 1))
    else
        echo "Failed"
        failed_tests=$((failed_tests + 1))
    fi

    i=$((i + 1))
done

echo
i=1
for file_input in ../data/neg_*_in.txt; do
    echo -n "Negative test $i: "

    file_args="$(basename "$file_input" in.txt)args.txt"
    ./neg_case.sh "$file_args"

    result=$?
    if [ $result -eq 2 ]; then
        echo "File not found"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 3 ]; then
        echo "Uncorrect count value"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 4 ]; then
        echo "app.exe not found"
        failed_tests=$((failed_tests + 1))
    elif [ $result -eq 0 ]; then
        echo "Pass"
    else
        echo "Failed"
        failed_tests=$((failed_tests + 1))
    fi

    i=$((i + 1))
done

echo "Finish testing"
if [ $failed_tests -eq 0 ]; then
    echo "All tests passed"
    exit 0
else
    echo "$failed_tests tests failed"
    exit $failed_tests
fi
