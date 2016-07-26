if(${verbose_traversal})
  message(STATUS "Entered SectionSkeleton directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/SectionSkeleton" )

set(headers "")
list(APPEND headers
  "src/SectionSkeleton"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
  list( APPEND testLabels SectionSkeleton )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting SectionSkeleton directory")
endif(${verbose_traversal})
