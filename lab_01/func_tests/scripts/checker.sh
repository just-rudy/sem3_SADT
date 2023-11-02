#!/bin/bash

files="func_tests/data/pos_??_in.txt"
for file_in in $files; do
	number=$(echo "$file_in" | grep -o "[0-9]*")

	file_out="func_tests/data/pos_""$number""_out.txt"
    
    echo $file_in
    echo $file_out

    command="./func_tests/scripts/pos_case.sh $file_in $file_out"
    res=$($command)
    echo $res
done