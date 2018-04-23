#!/bin/bash - 
# set -x

export FC=$(which gfortran)
export CC=$(which clang)
export CXX=$(which clang++)

compiler_family="clang"
./.AWS/compiler_test.sh ${compiler_family}

compiler_test=$?
if [ ${compiler_test} -ne 0 ]; then
  exit 1
fi
