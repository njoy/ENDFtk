cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( hana-adapter
    GIT_REPOSITORY  https://github.com/njoy/hana-adapter
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  https://github.com/njoy/header-utilities
    GIT_TAG         origin/build/fetchcontent-guards
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( range-v3-adapter
    GIT_REPOSITORY  https://github.com/njoy/range-v3-adapter
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         v2.5.0
    GIT_SHALLOW     TRUE
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    Log
    catch-adapter
    disco
    hana-adapter
    header-utilities
    range-v3-adapter
    pybind11
    )
