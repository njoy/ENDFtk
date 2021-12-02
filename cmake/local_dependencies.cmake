cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( catch-adapter
    URL             ${CMAKE_SOURCE_DIR}/dependencies/catch-adapter-src
    )

FetchContent_Declare( disco
    URL             ${CMAKE_SOURCE_DIR}/dependencies/disco-src
    )

FetchContent_Declare( hana-adapter
    URL             ${CMAKE_SOURCE_DIR}/dependencies/hana-adapter-src
    )

FetchContent_Declare( header-utilities
    URL             ${CMAKE_SOURCE_DIR}/dependencies/header-utilities-src
    )

FetchContent_Declare( Log
    URL             ${CMAKE_SOURCE_DIR}/dependencies/log-src
    )

FetchContent_Declare( pybind11
    URL             ${CMAKE_SOURCE_DIR}/dependencies/pybind11-src
    )

FetchContent_Declare( range-v3
    URL             ${CMAKE_SOURCE_DIR}/dependencies/range-v3-src
    )

FetchContent_Declare( spdlog
    URL             ${CMAKE_SOURCE_DIR}/dependencies/spdlog-src
    )
set( SPDLOG_BUILD_TESTING CACHE BOOL OFF )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    catch-adapter
    disco
    hana-adapter
    header-utilities
    Log
    pybind11
    range-v3
    spdlog
    )
