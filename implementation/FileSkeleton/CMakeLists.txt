if(${verbose_traversal})
  message(STATUS "Entered FileSkeleton directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/FileSkeleton" )

set(headers "")
list(APPEND headers
  "src/ctor"
  "src/createVector"
  "src/createMap"
  "src/sectionNumber"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
  list( APPEND testLabels FileSkeleton )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting FileSkeleton directory")
endif(${verbose_traversal})
