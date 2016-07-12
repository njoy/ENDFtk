if(${verbose_traversal})
  message(STATUS "Entered DirectoryRecord directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels DirectoryRecord )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting DirectoryRecord directory")
endif(${verbose_traversal})
