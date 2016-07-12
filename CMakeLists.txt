cmake_minimum_required( VERSION 3.2 )

set(projectName "ENDFtk")
set(projectVersion "0.1.0")

if(NOT DEFINED commonCMakeScripts_path)
  set(commonCMakeScripts_path "${CMAKE_SOURCE_DIR}/commonCMakeScripts")
endif(NOT DEFINED commonCMakeScripts_path)

include(subprojects.cmake)
include(${commonCMakeScripts_path}/objectOriented.cmake)
include(${commonCMakeScripts_path}/doxygen.cmake)

list(APPEND ${projectName}_src) # (empty list)

include(${commonCMakeScripts_path}/assemble.cmake)
include(${commonCMakeScripts_path}/terminus.cmake)
