#!/bin/bash

gcc -std=c99 -Wall -Werror -Wvla -g -O0 --coverage -o debug.exe main.c matrix.c utils.c arr.c
