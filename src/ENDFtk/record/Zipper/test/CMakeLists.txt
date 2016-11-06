add_executable( ENDFtk.record.Zipper.test
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
    target_compile_options( ENDFtk.record.Zipper.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( ENDFtk.record.Zipper.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( ENDFtk.record.Zipper.test PUBLIC ENDFtk )
add_test( NAME ENDFtk.record.Zipper COMMAND ENDFtk.record.Zipper.test ) 
