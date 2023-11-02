#!/bin/bash

RM_FILES="func_tests/scripts/*.txt *.o *.exe *.out *.gcno *.gcda"

for file in $RM_FILES; do
    rm "$file" -f
done