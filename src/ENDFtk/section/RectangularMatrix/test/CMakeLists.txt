
add_executable( ENDFtk.section.RectangularMatrix.test RectangularMatrix.test.cpp )
target_compile_options( ENDFtk.section.RectangularMatrix.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ENDFtk_appended_flags} )
target_link_libraries( ENDFtk.section.RectangularMatrix.test PUBLIC ENDFtk )
add_test( NAME ENDFtk.section.RectangularMatrix COMMAND ENDFtk.section.RectangularMatrix.test )
