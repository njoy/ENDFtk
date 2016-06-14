cmake_minimum_required( VERSION 3.2 )

set(projectName "ENDFtk")
set(projectVersion "0.1.0")

if(NOT DEFINED commonCMakeScripts_path)
  set(commonCMakeScripts_path "${CMAKE_SOURCE_DIR}/commonCMakeScripts")
endif(NOT DEFINED commonCMakeScripts_path)

include(subprojects.cmake)
include(${commonCMakeScripts_path}/objectOriented.cmake)

# Initialize a variable for collecting utility implementation components
list(APPEND ${projectName}_src) # (empty list)
list(APPEND ${projectName}_src_headers) # (empty list)
list(APPEND ${projectName}_bin_headers) # (empty list)

set(headers "")
list(APPEND headers
  "ENDFtk"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    "${ENDFtk_HEADER_DIR}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

include(${commonCMakeScripts_path}/assemble.cmake)
include(${commonCMakeScripts_path}/terminus.cmake)
