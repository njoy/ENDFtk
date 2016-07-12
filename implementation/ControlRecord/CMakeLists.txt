if(${verbose_traversal})
  message(STATUS "Entered ControlRecord directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels ControlRecord )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting ControlRecord directory")
endif(${verbose_traversal})
