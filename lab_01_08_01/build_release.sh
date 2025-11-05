#!/bin/bash

gcc -O3 -std=c99 -Wall -Werror -c main.c -o main.o
gcc main.o -o app.exe
