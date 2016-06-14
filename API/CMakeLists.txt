if(${verbose_traversal})
  message(STATUS "Entered API directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${nuclearData_HEADER_DIR}/API/${header}.hpp"
    COPYONLY
    )
endforeach(header)

set(nuclearData_src "${nuclearData_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting API directory")
endif(${verbose_traversal})
