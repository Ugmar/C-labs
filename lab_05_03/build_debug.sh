#!/bin/bash

gcc -std=c99 -Wall -Werror -g -O0 --coverage -c ./*.c
gcc --coverage ./*.o -o debug.exe -lm
