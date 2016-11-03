add_executable( UnivariateTabulation.test
                C1.test.cpp
                C2.test.cpp
                equality.test.cpp
                L1.test.cpp
                L2.test.cpp
                nPairs.test.cpp
                nRanges.test.cpp
                rangeBoundaries.test.cpp
                rangeInterpolationScheme.test.cpp
                UnivariateTabulation.test.cpp
                xBegin.test.cpp
                xEnd.test.cpp
                xValues.test.cpp
                yBegin.test.cpp
                yEnd.test.cpp
                yValue.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( UnivariateTabulation.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( UnivariateTabulation.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( UnivariateTabulation.test PUBLIC ENDFtk )
add_test( NAME UnivariateTabulation COMMAND UnivariateTabulation.test ) 
