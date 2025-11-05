#!/bin/bash

clang -std=c99 -Wall -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g main.c io_arr.c ops_matrix.c -o debug.exe
