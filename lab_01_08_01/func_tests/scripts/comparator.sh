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
	echo "Uncorrect count value"
	exit 3
fi
res_file1=$(grep -Eo "[+-]?[0-9]+(\.[0-9]+)?" "$file1")
res_file2=$(grep -Eo "[+-]?[0-9]+(\.[0-9]+)?" "$file2")
if [ "$res_file1" == "$res_file2" ]; then
	exit 0
else
	exit 1
fi
