if(${verbose_traversal})
  message(STATUS "Entered StructureDivision directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels StructureDivision )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting StructureDivision directory")
endif(${verbose_traversal})
