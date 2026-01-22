#!/bin/bash

for i in {1..9..1}; do
    touch pos_0"$i"_in.txt
    touch pos_0"$i"_in_file1.txt
    touch pos_0"$i"_in_file2.txt
    touch pos_0"$i"_out.txt
    touch pos_0"$i"_out_file.txt
    touch pos_0"$i"_args.txt
done

for i in {10..17..1}; do
    touch pos_"$i"_in.txt
    touch pos_"$i"_in_file1.txt
    touch pos_"$i"_in_file2.txt
    touch pos_"$i"_out.txt
    touch pos_"$i"_out_file.txt
    touch pos_"$i"_args.txt
done


for i in {1..9..1}; do
    touch neg_0"$i"_in.txt
    touch neg_0"$i"_in_file1.txt
    touch neg_0"$i"_in_file2.txt
    touch neg_0"$i"_args.txt
done


for i in {10..12..1}; do
    touch neg_"$i"_in.txt
    touch neg_"$i"_in_file1.txt
    touch neg_"$i"_in_file2.txt
    touch neg_"$i"_args.txt
done

