#!/bin/bash

inn=$1
out_expect=$2
out="TMP_output.txt"

# program="../../app.exe"

# valgrind -q --track-origins=yes --show-leak-kinds=definite,possible --leak-check=full --show-leak-kinds=all ../../app.exe < "$inn" > $out 2> "valgrind.txt"
# cat "valgrind.txt"

if ../../app.exe < "$inn" > "$out"; then
    if bash ./comparator.sh "$out" "$out_expect"; then
        #echo Тест пройден
        exit 0
    else
        #echo Ошибка
        exit 1
    fi
else
    #echo Ошибка
    exit 1
fi