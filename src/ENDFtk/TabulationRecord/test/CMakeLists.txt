
add_executable( ENDFtk.TabulationRecord.test
                C1.test.cpp
                C2.test.cpp
                equality.test.cpp
                L1.test.cpp
                L2.test.cpp
                NP.test.cpp
                NR.test.cpp
                pairs.test.cpp
                print.test.cpp
                rangeInterpolationScheme.test.cpp
                regions.test.cpp
                TabulationRecord.test.cpp
                x.test.cpp
                y.test.cpp )
target_compile_options( ENDFtk.TabulationRecord.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ENDFtk_appended_flags} )
target_link_libraries( ENDFtk.TabulationRecord.test PUBLIC ENDFtk ) 
add_test( NAME ENDFtk.TabulationRecord COMMAND ENDFtk.TabulationRecord.test )