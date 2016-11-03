add_executable( Zipper.test
                expandReferencePack.test.cpp
                makeIteratorTuple.test.cpp
                process.test.cpp
                readLine.test.cpp
                readPartialLine.test.cpp
                reserve.test.cpp
                unzip.test.cpp
                Zipper.test.cpp )
set( test_flags ${ENDFtk_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( Zipper.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Zipper.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( Zipper.test PUBLIC ENDFtk )
add_test( NAME Zipper COMMAND Zipper.test ) 
