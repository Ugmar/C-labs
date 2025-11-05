#!/bin/bash

gcc -std=c99 -Wall -Werror -g -O0 -c main.c -o main.o
gcc main.o -o app.exe -lm
