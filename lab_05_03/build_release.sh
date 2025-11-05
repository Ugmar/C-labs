#!/bin/bash

gcc -O3 -std=c99 -Wall -Werror -c ./*.c
gcc ./*.o -o app.exe -lm
