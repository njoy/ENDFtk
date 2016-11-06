add_executable( ENDFtk.record.Sequence.test
                read.test.cpp
                Sequence.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( ENDFtk.record.Sequence.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( ENDFtk.record.Sequence.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( ENDFtk.record.Sequence.test PUBLIC ENDFtk )
add_test( NAME ENDFtk.record.Sequence COMMAND ENDFtk.record.Sequence.test ) 
