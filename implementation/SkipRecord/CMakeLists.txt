if(${verbose_traversal})
  message(STATUS "Entered SkipRecord directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels SkipRecord )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting SkipRecord directory")
endif(${verbose_traversal})
