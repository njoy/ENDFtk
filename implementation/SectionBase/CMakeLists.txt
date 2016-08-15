if(${verbose_traversal})
  message(STATUS "Entered SectionBase directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/SectionBase")

set( subdirectories "" )
list( APPEND subdirectories "Section3" )

set( headers "" )
list( APPEND headers
  "src/ctor"
  "src/readSEND"
  ${subdirectories}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

foreach( subdirectory ${subdirectories} )
  add_subdirectory( ${subdirectory} )
endforeach( subdirectory )

if(${local_testing})
  list( APPEND testLabels SectionBase )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting SectionBase directory")
endif(${verbose_traversal})
