if(${verbose_traversal})
  message(STATUS "Entered implementation directory")
endif(${verbose_traversal})

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  "record"
  "HeadRecord"
  "ListRecord"
  "UnivariateTabulation"
  )

foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${ENDFtk_HEADER_DIR}/implementation/${subdir}"))
    file(MAKE_DIRECTORY "${ENDFtk_HEADER_DIR}/implementation/${subdir}")
  endif(NOT(EXISTS "${ENDFtk_HEADER_DIR}/implementation/${subdir}"))
endforeach (subdir)

set(subdirs "")
list(APPEND subdirs
  "TextRecord"
  "ControlRecord"
  "DirectoryRecord"
  "StructureDivision"
  "SectionBase"
  "SectionSkeleton"
  ${header_only_subdirs}
  )

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

set(headers "")
list(APPEND headers
  "TapeIdentification"
  ${subdirs}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${ENDFtk_HEADER_DIR}/implementation/${header}.hpp"
    COPYONLY
    )
endforeach(header)

set(ENDFtk_src "${ENDFtk_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting implementation directory")
endif(${verbose_traversal})
