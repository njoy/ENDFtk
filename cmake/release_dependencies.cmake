cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         fb84b82ebf7a4789aa43cea560680cf745c6ee4f
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         178a03cf4a571fee028b008ffac85e20f6059ade
    )

FetchContent_Declare( fmt-adapter
    GIT_REPOSITORY  http://github.com/njoy/fmt-adapter
    GIT_TAG         a6db6c8cf9534b028eb3dea4549934f7ae6abf9f
    )

FetchContent_Declare( hana-adapter
    GIT_REPOSITORY  https://github.com/njoy/hana-adapter
    GIT_TAG         f58e8973c9a614dc4f3720b5581a762c61bdbb40
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  https://github.com/njoy/header-utilities
    GIT_TAG         7d575429926e033acd18340d04e44d1bc51f19d5
    )

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         e0f371dfef22b655bbd52e8783d037e6c594824a
    )

FetchContent_Declare( range-v3-adapter
    GIT_REPOSITORY  https://github.com/njoy/range-v3-adapter
    GIT_TAG         4d1a3bde6aba47ca59a65713f9cab7877ad2cc87
    )

FetchContent_Declare( spdlog-adapter
    GIT_REPOSITORY  http://github.com/njoy/spdlog-adapter
    GIT_TAG         39cd17919b2be662a45b9c33342b5a5f4f1feb4c
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         v2.6.0rc3
    GIT_SHALLOW     TRUE
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    catch-adapter
    disco
    fmt-adapter
    hana-adapter
    header-utilities
    Log
    range-v3-adapter
    spdlog-adapter
    pybind11
    )
