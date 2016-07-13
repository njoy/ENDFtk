if(${verbose_traversal})
  message(STATUS "Entered Zipper directory")
endif(${verbose_traversal})

set(long_path "${ENDFtk_HEADER_DIR}/implementation/record/Zipper" )
set(headers "")
list(APPEND headers
  "src/expandReferencePack"
  "src/makeIteratorTuple"
  "src/process"
  "src/readLine"
  "src/readPartialLine"
  "src/reserve"
  "src/unpackIteratorTuple"
  "src/verifyTail"
  "src/increment"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

if(${local_testing})
 list( APPEND testLabels Zipper )
 add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting Zipper directory")
endif(${verbose_traversal})
