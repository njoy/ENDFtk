if(${verbose_traversal})
  message(STATUS "Entered TextRecord directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels TextRecord )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting TextRecord directory")
endif(${verbose_traversal})
