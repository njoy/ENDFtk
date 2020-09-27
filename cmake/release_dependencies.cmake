cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( range-v3-adapter
    GIT_REPOSITORY  https://github.com/njoy/range-v3-adapter
    GIT_TAG         4d1a3bde6aba47ca59a65713f9cab7877ad2cc87
    )

FetchContent_Declare( hana-adapter
    GIT_REPOSITORY  https://github.com/njoy/hana-adapter
    GIT_TAG         f58e8973c9a614dc4f3720b5581a762c61bdbb40
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  https://github.com/njoy/header-utilities
    GIT_TAG         04f988c2b576630ef10fc0c3838c915f4a6e15d6
    )

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         fb84b82ebf7a4789aa43cea560680cf745c6ee4f
    )

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         e0f371dfef22b655bbd52e8783d037e6c594824a
    )

FetchContent_Declare( fmt-adapter
    GIT_REPOSITORY  http://github.com/njoy/fmt-adapter
    GIT_TAG         a6db6c8cf9534b028eb3dea4549934f7ae6abf9f
    )

FetchContent_Declare( spdlog-adapter
    GIT_REPOSITORY  http://github.com/njoy/spdlog-adapter
    GIT_TAG         39cd17919b2be662a45b9c33342b5a5f4f1feb4c
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         178a03cf4a571fee028b008ffac85e20f6059ade
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    range-v3-adapter
    hana-adapter
    header-utilities
    catch-adapter
    Log
    fmt-adapter
    spdlog-adapter
    disco
    )
