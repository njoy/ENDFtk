########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( ENDFtk
  VERSION 1.3.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  ENDFtk.tests
  "Build the ENDFtk unit tests and integrate with ctest" OFF
  "BUILD_TESTING AND NOT ${subproject}" OFF
)

cmake_dependent_option(
  ENDFtk.python
  "Build ENDFtk python bindings" ON
  "NOT ${subproject} OR DEFINED require.ENDFtk.python " OFF
)

if ( ENDFtk.python )
  set( require.tools.python CACHE BOOL ON )
endif()

option( ENDFtk.installation "Install ENDFtk" ON )

########################################################################
# Dependencies
########################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( cmake/dependencies.cmake )

########################################################################
# Project targets
########################################################################

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ENDFtk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( ENDFtk INTERFACE )
add_library( njoy::ENDFtk ALIAS ENDFtk)

target_include_directories( ENDFtk INTERFACE ${prefix} )

target_link_libraries( ENDFtk
  INTERFACE
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ENDFtk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if (ENDFtk.python AND NOT TARGET njoy::tools.python)
  message(WARNING "njoy::tools was not built with python enabled.  Disabling build of ENDFtk's python API.")
  set(ENDFtk.python OFF)
endif()

if ( ENDFtk.python )
  add_subdirectory( python )
endif()

if( ${ENDFtk.tests} )
  add_subdirectory( test )
endif()

#######################################################################
# Installation
#######################################################################

if(ENDFtk.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS ENDFtk EXPORT ENDFtk-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT ENDFtk-targets
      FILE "ENDFtk-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/ENDFtk
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER ENDFtk lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/ENDFtk
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/ENDFtk
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()

########################################################################
# Windows-specific setup
########################################################################

# enable Edit and Continue in Visual Studio (for debugging)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(MSVC)
    target_compile_options(${PROJECT_NAME}  INTERFACE "/ZI")
    target_link_options(${PROJECT_NAME} INTERFACE "/INCREMENTAL")
  endif()
endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE "/bigobj")
endif()
