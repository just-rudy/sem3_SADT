#!/bin/bash

gcc main.c -o main.exe

#!/bin/bash

inn=$1
out_expect=$2
out="TMP_output.txt"

program="../../app.exe"

launch=$program < "$inn" > $out

comparator="./comparator.sh"

if $launch; then
    if bash ./comparator.sh "$out" "$out_expect"; then
        exit 0
        echo Тест пройдет
    else
        exit 1
        echo Ошибка
    fi
else
    exit 1
    echo Ошибка
fi