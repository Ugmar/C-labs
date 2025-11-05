#!/bin/bash

gcc -std=c99 -Wall -Werror -g -O0 -c main.c -o main_debug.o
gcc main_debug.o -o app_debug.exe
