#!/bin/bash

err_cnt=0

files="../data/pos_??_in.txt"
for file_in in $files; do
	number=$(echo "$file_in" | grep -o "[0-9]*")
    if ! [[ $number =~ ^[0-9]{2}$ ]]; then
        break
    fi

	file_out=../data/pos_"$number"_out.txt
    
    #echo $file_in
    #echo $file_out

    # command=bash ./pos_case.sh "$file_in" "$file_out"
    # res=$($command)
    if bash ./pos_case.sh "$file_in" "$file_out";then
        echo -e "\033[0;32m"PASS pos test pos_${number}_in.txt"\033[0m"
    else
        echo -e "\033[0;31m"FAIL pos test pos_${number}_in.txt"\033[0m"
        err_cnt=$((err_cnt + 1))
    fi
done


files="../data/neg_??_in.txt"
for file_in in $files; do
    number=$(echo "$file_in" | grep -o "[0-9]*")
    
    if ! [[ $number =~ ^[0-9]{2}$ ]]; then
        break
    fi

	#file_out=func_tests/data/pos_"$number"_out.txt
    
    #echo $file_in
    #echo $file_out

    # command=bash ./neg_case.sh "$file_in" "$file_out"
    # res=$($command)
    if bash ./neg_case.sh "$file_in" "$file_out"; then
        echo -e "\033[0;32m"PASS neg test neg_${number}_in.txt"\033[0m"
    else
        echo -e "\033[0;31m"FAIL neg test neg_${number}_in.txt"\033[0m"
        err_cnt=$((err_cnt + 1))
    fi
done

exit $err_cnt