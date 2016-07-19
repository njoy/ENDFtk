if(${verbose_traversal})
  message(STATUS "Entered Section3 directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
  list( APPEND testLabels Section3 )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(ENDFtk_src "${ENDFtk_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting Section3 directory")
endif(${verbose_traversal})
