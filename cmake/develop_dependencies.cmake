cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         origin/master
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         origin/master
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         origin/master
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( hana
    GIT_REPOSITORY  https://github.com/boostorg/hana
    GIT_TAG         boost-1.77.0
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  https://github.com/njoy/header-utilities
    GIT_TAG         origin/master
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( range-v3
    GIT_REPOSITORY  https://github.com/ericniebler/range-v3
    GIT_TAG         0.11.0
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         v2.6.1
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    Log
    catch-adapter
    disco
    hana
    header-utilities
    range-v3
    pybind11
    )
