if(${verbose_traversal})
  message(STATUS "Entered TapeSkeleton directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/TapeSkeleton" )

set(headers "")
list(APPEND headers
  "src/ctor"
  "src/createVector"
  "src/createMap"
  "src/materialNumber"
  "src/MatchIterator"
  "src/Range"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
  list( APPEND testLabels TapeSkeleton )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting TapeSkeleton directory")
endif(${verbose_traversal})

