
add_executable( ENDFtk.resonanceParameters.resolved.BreitWignerLValue.test BreitWignerLValue.test.cpp )
target_compile_options( ENDFtk.resonanceParameters.resolved.BreitWignerLValue.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ENDFtk_appended_flags} )
target_link_libraries( ENDFtk.resonanceParameters.resolved.BreitWignerLValue.test PUBLIC ENDFtk ) 
add_test( NAME ENDFtk.resonanceParameters.resolved.BreitWignerLValue COMMAND ENDFtk.resonanceParameters.resolved.BreitWignerLValue.test )