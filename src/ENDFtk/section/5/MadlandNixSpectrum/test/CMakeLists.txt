
add_executable( ENDFtk.section.5.MadlandNixSpectrum.test MadlandNixSpectrum.test.cpp )
target_compile_options( ENDFtk.section.5.MadlandNixSpectrum.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ENDFtk_appended_flags} )
target_link_libraries( ENDFtk.section.5.MadlandNixSpectrum.test PUBLIC ENDFtk ) 
add_test( NAME ENDFtk.section.5.MadlandNixSpectrum COMMAND ENDFtk.section.5.MadlandNixSpectrum.test )