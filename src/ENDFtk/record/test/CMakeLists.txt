add_executable( ENDFtk.record.test
                record.test.cpp
                skip.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( ENDFtk.record.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( ENDFtk.record.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( ENDFtk.record.test PUBLIC ENDFtk )
add_test( NAME ENDFtk.record COMMAND ENDFtk.record.test ) 
