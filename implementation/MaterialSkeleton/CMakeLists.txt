if(${verbose_traversal})
  message(STATUS "Entered MaterialSkeleton directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/MaterialSkeleton" )

set(headers "")
list(APPEND headers
  "src/MaterialSkeleton"
  "src/operator"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
  list( APPEND testLabels MaterialSkeleton )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting MaterialSkeleton directory")
endif(${verbose_traversal})

