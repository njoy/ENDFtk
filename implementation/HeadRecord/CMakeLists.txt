if(${verbose_traversal})
  message(STATUS "Entered HeadRecord directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/HeadRecord" )
set(headers "")
list(APPEND headers
  "src/asHead"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
  list( APPEND testLabels HeadRecord )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting HeadRecord directory")
endif(${verbose_traversal})
