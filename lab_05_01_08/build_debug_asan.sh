#!/bin/bash

clang -std=c99 -Wall -fsanitize=address -fno-omit-frame-pointer -g ./*.c -o asan.exe
