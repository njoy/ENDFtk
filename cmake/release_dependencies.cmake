cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2
    GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
    )

FetchContent_Declare( fast_float
    GIT_REPOSITORY  https://github.com/fastfloat/fast_float
    GIT_TAG         f476bc713fda06fbd34dc621b466745a574b3d4c # tag: v6.1.1
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
    )


FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 # tag: v1.11.0
    )
set( SPDLOG_BUILD_PIC CACHE INTERNAL BOOL ON )

FetchContent_Declare( tools
    GIT_REPOSITORY  https://github.com/njoy/tools
    GIT_TAG         7d456c11021cd9866b695ef27609455179a0c793
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    fast_float
    spdlog
    tools
    )
