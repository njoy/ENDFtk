if(${verbose_traversal})
  message(STATUS "Entered SectionBase directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels SectionBase )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting SectionBase directory")
endif(${verbose_traversal})
