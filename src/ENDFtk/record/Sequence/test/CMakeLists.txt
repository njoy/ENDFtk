add_executable( Sequence.test
                read.test.cpp
                Sequence.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( Sequence.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Sequence.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( Sequence.test PUBLIC ENDFtk )
add_test( NAME Sequence COMMAND Sequence.test ) 
