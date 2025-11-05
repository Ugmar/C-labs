#!/bin/bash

if [ $# == 2 ];then
	if [ -f "$1" ] && [ -f "$2" ]; then
		file1=$1
		file2=$2
	else
		echo "Not found files"
		exit 2
	fi
else
	exit 3
fi
index_string1=$(($(grep -nm1 'string:.*' "$file1" | grep -Eo "^[0-9]+")+1))
after_string1=$(grep -om1 "string:.*" "$file1")
tail_after_string1=$(tail -n +$index_string1 "$file1")

index_string2=$(($(grep -nm1 'string:.*' "$file2" | grep -Eo "^[0-9]+")+1))
after_string2=$(grep -om1 "string:.*" "$file2")
tail_after_string2=$(tail -n +$index_string2 "$file2")
if [ "$after_string1" == "$after_string2" ] && [ "$tail_after_string1" == "$tail_after_string2" ];then
	exit 0
else
	exit 1
fi
