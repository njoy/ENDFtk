if(${verbose_traversal})
  message(STATUS "Entered SectionSkeleton directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels SectionSkeleton )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting SectionSkeleton directory")
endif(${verbose_traversal})
