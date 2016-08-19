if [ "$TRAVIS_OS_NAME" = "osx" ]
then
    wget https://cmake.org/files/v3.5/cmake-3.5.0-Darwin-x86_64.tar.gz
    tar xfz cmake-3.5.0-Darwin-x86_64.tar.gz
    PATH="`pwd`/cmake-3.5.0-Darwin-x86_64/CMake.app/Contents/bin":$PATH
    export DEPTH="750"
    export SPECIFY_LD=""
elif [ "$TRAVIS_OS_NAME" = "linux" ]
then
    sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-6 90
    sudo update-alternatives --auto gcov
    export SPECIFY_LD="-fuse-ld=gold"
    if [ $CXX = "g++" ]
    then
        export CC="/usr/bin/gcc-6"
        export CXX="/usr/bin/g++-6"
        export AR="/usr/bin/gcc-ar-6"
        export RANLIB="/usr/bin/gcc-ranlib-6"
        export NM="/usr/bin/gcc-nm-6"
        export DEPTH="2048"
    else
        export DEPTH="750"
    fi
fi

./fetchDependencies.py
mkdir bin
cd bin
cmake -D build_type=$build_type \
      -D static_libraries=$static_libraries \
      -D appended_flags="-ftemplate-depth=$DEPTH -Werror ${SPECIFY_LD} ${SANITIZER}" ..
make -j 2
export COMPILATION_SUCCESS=$?
ctest --output-on-failure -j 2
export TEST_SUCCESS=$?

if [ "$build_type" = "coverage" ]
then
    pip install --user cpp-coveralls
    echo "loading coverage information"
    coveralls  --exclude "/usr/include/" --exclude-pattern ".*CMake.*|.*Catch.*|.*catch.*|.*easylogging.*|.*disco.*|.*utility.*|.*test\.cpp" --root ".." --build-root "." --gcov-options '\-lp'
fi

exit COMPILATION_SUCCESS && TEST_SUCCESS
