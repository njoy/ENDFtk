if(${verbose_traversal})
  message(STATUS "Entered record directory")
endif(${verbose_traversal})

set( long_path "${ENDFtk_HEADER_DIR}/implementation/record" )

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  "Zipper"
  )

foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${long_path}/${subdir}"))
    file(MAKE_DIRECTORY "${long_path}/${subdir}")
  endif(NOT(EXISTS "${long_path}/${subdir}"))
endforeach (subdir)

set(subdirs "")
list(APPEND subdirs
  "Tail"
  "Base"
  "Sequence"
  ${header_only_subdirs}
  )

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

set(headers "")
list(APPEND headers
  "Character"
  "Integer"
  "Real"
  ${subdirs}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

set(ENDFtk_src "${ENDFtk_src}" PARENT_SCOPE)

if(${local_testing})
 list( APPEND testLabels record )
 add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting record directory")
endif(${verbose_traversal})
