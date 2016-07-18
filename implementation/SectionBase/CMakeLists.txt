if(${verbose_traversal})
  message(STATUS "Entered SectionBase directory")
endif(${verbose_traversal})

if(${local_testing})
  list( APPEND testLabels SectionBase )
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

set(ENDFtk_src "${ENDFtk_src}"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/SectionBase.cpp"
  PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting SectionBase directory")
endif(${verbose_traversal})
