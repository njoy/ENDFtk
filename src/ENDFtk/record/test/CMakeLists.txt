add_executable( record.test
                record.test.cpp
                skip.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( record.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( record.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( record.test PUBLIC ENDFtk )
add_test( NAME record COMMAND record.test ) 
