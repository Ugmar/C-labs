#!/bin/bash

clang -std=c99 -Wall -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g main.c -o msan.exe
