#!/bin/bash

if [ ! -e "./app.exe" ]; then
    exit 4
fi

./app.exe <"$1"
result=$?

if [ $result -ne 0 ]; then
    exit 0
else
    exit 1
fi
