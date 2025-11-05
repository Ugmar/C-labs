#!/bin/bash
path="../data"
if [ $# == 2 ];then
	if [ -f "$path/$1" ] && [ -f "$path/$2" ];then
		file_in="$path/$1"
        file_out="$path/$2"
	else
		exit 2
	fi
else
	exit 3
fi
if [ ! -e "../../debug.exe" ];then
	exit 4
fi
../../debug.exe < "$file_in" > "$1.file_out_result" 
result=$?
./comparator.sh "$file_out" "$1.file_out_result"
ans=$?
if [ $result -ne 0 ] && [ $ans -eq 0 ];then
	exit 0
else
	exit 1
fi
