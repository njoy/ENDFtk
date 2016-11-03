add_executable( Tail.test
                Tail.test.cpp
                TailVerifiers.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( Tail.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Tail.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( Tail.test PUBLIC ENDFtk )
add_test( NAME Tail COMMAND Tail.test ) 
