cmake_minimum_required( VERSION 3.27 )
include( FetchContent )

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         e0eb6b4f3e6d7afce7c2c521e68b4f223c50fe2d  # tag: v0.4.0
    )

#######################################################################
# Load dependencies
#######################################################################

if(ENDFtk.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
      )
  FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(ENDFtk.tests)
  FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )
  FetchContent_MakeAvailable(
      Catch2
    )
endif()

FetchContent_MakeAvailable(
    tools
    )
