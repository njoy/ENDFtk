########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( ENDFtk LANGUAGES CXX )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( ENDFtk_unit_tests
    "Compile the ENDFtk unit tests and integrate with ctest" ON
    )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" )
set( strict_flags "-Werror" )
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )

########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()

########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# elementary : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include_directories( src/ )

add_library( ENDFtk INTERFACE
    )
target_include_directories( ENDFtk INTERFACE src/ )
target_link_libraries( ENDFtk
    INTERFACE Log
    INTERFACE catch-adapter
    INTERFACE disco
    INTERFACE hana-adapter
    INTERFACE header-utilities
    INTERFACE range-v3-adapter
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# elementary : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC" )

include_directories( python/src/ )

pybind11_add_module( ENDFtk.python
    python/src/ENDFtk.python.cpp
    python/src/record/DirectoryRecord.python.cpp
    python/src/section/1/451.python.cpp
    python/src/section/3.python.cpp
    )
target_link_libraries( ENDFtk.python PUBLIC ENDFtk )
set_target_properties( ENDFtk.python PROPERTIES OUTPUT_NAME ENDFtk )

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( ENDFtk_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
