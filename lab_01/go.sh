#!bin/bash/

for i in 1 2 3 4 5 6 7 8 9 10
do
    echo
    echo случай $i
    echo
    cd "/home/rudy/bmstu_sem3_TASD/sem3_TaSD/lab_1/" && gcc *.c -o main && "/home/rudy/bmstu_sem3_TASD/sem3_TaSD/lab_1/"main
done