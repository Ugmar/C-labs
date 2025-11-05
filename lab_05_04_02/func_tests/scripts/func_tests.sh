#!/bin/bash

i=1
failed_tests=0

echo "Start testing..."
for file_input in ../data/pos_*_in.txt; do

    echo -n "Positive test $i: "
    input=$(basename "$file_input")
    output="$(basename "$file_input" in.txt)out.txt"
    file_args="$(basename "$file_input" in.txt)args.txt"
    file_output="$(basename "$file_input" in.txt)out_file.txt"
    file_input="$(basename "$file_input" in.txt)in_file.txt"

    ./pos_case.sh "$input" "$output" "$file_args" "$file_input" "$file_output"
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

    input=$(basename "$file_input")
    file_args="$(basename "$file_input" in.txt)args.txt"
    file_input=$(basename "$file_input" in.txt)in_file.txt

    ./neg_case.sh "$input" "$file_input" "$file_args"

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
