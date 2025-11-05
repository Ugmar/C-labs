#!/bin/bash

gcc -O3 -std=c99 -Wall -Werror -Wvla -o app.exe main.c matrix.c arr.c
