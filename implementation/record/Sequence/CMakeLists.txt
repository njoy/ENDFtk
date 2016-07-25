if(${verbose_traversal})
  message(STATUS "Entered Sequence directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/record/Sequence" )
set(headers "")
list(APPEND headers
  "src/read"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
 list( APPEND testLabels Sequence )
 add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting Sequence directory")
endif(${verbose_traversal})
