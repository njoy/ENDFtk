if(${verbose_traversal})
  message(STATUS "Entered RecordTail directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/RecordTail")

if(NOT(EXISTS "${long_path}/src"))
  file(MAKE_DIRECTORY "${long_path}/src")
endif(NOT(EXISTS "${long_path}/src"))

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

set(ENDFtk_src "${ENDFtk_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting RecordTail directory")
endif(${verbose_traversal})
