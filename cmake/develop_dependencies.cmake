cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( tools
    GIT_REPOSITORY  https://github.com/njoy/tools
    GIT_TAG         feature/std23-zip_transform
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2
    GIT_TAG         v3.3.2
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         v2.10.4
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    tools
    )
