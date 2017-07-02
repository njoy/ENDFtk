
add_executable( ENDFtk.UnivariateTabulation.test
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
target_compile_options( ENDFtk.UnivariateTabulation.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ENDFtk_appended_flags} )
target_link_libraries( ENDFtk.UnivariateTabulation.test PUBLIC ENDFtk ) 
add_test( NAME ENDFtk.UnivariateTabulation COMMAND ENDFtk.UnivariateTabulation.test )
