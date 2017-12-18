
gcc --version

mkdir bin
cd bin
cmake -D link_time_optimization=ON ../

make VERBOSE=1 -j2

ctest --output-on-failure -j2
export TEST_FAILURE=$?
if [ $TEST_FAILURE -ne 0 ];
then
    exit 1
fi
