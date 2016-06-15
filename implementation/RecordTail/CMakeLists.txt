if(${verbose_traversal})
  message(STATUS "Entered RecordTail directory")
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

# traverse subdirectories
if(${local_testing})
  list( APPEND testLabels RecordTail )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

list(APPEND ENDFtk_src
  "${CMAKE_CURRENT_SOURCE_DIR}/src/RecordTail.cpp"
  )

set(ENDFtk_src "${ENDFtk_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting RecordTail directory")
endif(${verbose_traversal})
