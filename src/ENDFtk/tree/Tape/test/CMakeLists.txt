
add_executable( ENDFtk.tree.Tape.test Tape.test.cpp )
target_compile_options( ENDFtk.tree.Tape.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${ENDFtk_appended_flags} )
target_link_libraries( ENDFtk.tree.Tape.test PUBLIC ENDFtk ) 
file( GLOB resources "resources/*" )
foreach( resource ${resources})
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
endforeach()
add_test( NAME ENDFtk.tree.Tape COMMAND ENDFtk.tree.Tape.test )