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


########################################################################
# Dependencies
########################################################################

include( cmake/ENDFtk_dependencies.cmake )


########################################################################
# Project targets
########################################################################

add_library( ENDFtk INTERFACE )
target_include_directories( ENDFtk INTERFACE src/ )
target_link_libraries( ENDFtk
    INTERFACE range-v3-adapter
    INTERFACE catch-adapter
    INTERFACE disco
    INTERFACE hana-adapter
    INTERFACE header-utilities
    INTERFACE Log )


#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( ENDFtk_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
