#!/bin/bash

gcc -O3 -std=c99 -Wall -Werror -Wvla -o app.exe main.c main.c matrix.c utils.c arr.c
