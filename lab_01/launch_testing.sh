#!/bin/bash

bash ./build_release.sh

cd ./func_tests/scripts/ || exit
bash ./func_testing.sh
cd ../../

bash ./collect_coverage.sh
bash ./clear.sh