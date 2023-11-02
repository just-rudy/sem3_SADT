#!/bin/bash

file1=$1
file2=$2

#regular="[-]?[0-9]+([.]{1}[0-9]+)?"
regular="(?<=\s|^)(([+-]?\d+([.]\d*)?|[.]\d+)([Ee][+-]?\d+)?)(?=\s|$)"
#at $file1
#look ahead look behind
from_f1=$(grep -oP "$regular" "$file1")
from_f2=$(grep -oP "$regular" "$file2")
echo f1  "$from_f1"
echo f2  "$from_f2"



if [ "$from_f1" == "$from_f2" ]; then
    exit 0
else
    exit 1
fi