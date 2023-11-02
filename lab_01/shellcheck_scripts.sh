#!/bin/bash

CHECK_FILES="*.sh func_tests/scripts/*.sh"

for file in $CHECK_FILES; do
    echo "$file"
    shellcheck "$file"
done