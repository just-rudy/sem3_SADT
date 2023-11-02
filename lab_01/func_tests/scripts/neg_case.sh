#!/bin/bash

inn=$1
out="TMP_output.txt"

#launch=../../app.exe < "$inn" > "$out"

# valgrind -q --track-origins=yes --show-leak-kinds=definite,possible --leak-check=full --show-leak-kinds=all ../../app.exe < "$inn" > $out 2> "valgrind.txt"
# cat "valgrind.txt"

if ../../app.exe < "$inn" > "$out"; then
    #echo Ошибка
    exit 1
else
    #echo Not Ошибка
    exit 0
fi