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

include_directories( python/src/ )

pybind11_add_module( ENDFtk.python
    python/src/ENDFtk.python.cpp
    python/src/record/DirectoryRecord.python.cpp
    python/src/record/TapeIdentification.python.cpp
    python/src/section/1/451.python.cpp
    python/src/section/2/151.python.cpp
    python/src/section/2/151/Isotope.python.cpp
    python/src/section/2/151/ScatteringRadius.python.cpp
    python/src/section/2/151/ResonanceRange.python.cpp
    python/src/section/2/151/SpecialCase.python.cpp
    python/src/section/2/151/BreitWignerLValue.python.cpp
    python/src/section/2/151/ReichMooreLValue.python.cpp
    python/src/section/2/151/SingleLevelBreitWigner.python.cpp
    python/src/section/2/151/MultiLevelBreitWigner.python.cpp
    python/src/section/2/151/ReichMoore.python.cpp
    python/src/section/2/151/ParticlePairs.python.cpp
    python/src/section/2/151/ResonanceChannels.python.cpp
    python/src/section/2/151/ResonanceParameters.python.cpp
    python/src/section/2/151/SpinGroup.python.cpp
    python/src/section/2/151/RMatrixLimited.python.cpp
    python/src/section/2/151/UnresolvedEnergyDependentFissionWidthsJValue.python.cpp
    python/src/section/2/151/UnresolvedEnergyDependentJValue.python.cpp
    python/src/section/2/151/UnresolvedEnergyIndependentLValue.python.cpp
    python/src/section/2/151/UnresolvedEnergyDependentFissionWidthsLValue.python.cpp
    python/src/section/2/151/UnresolvedEnergyDependentLValue.python.cpp
    python/src/section/2/151/UnresolvedEnergyDependent.python.cpp
    python/src/section/2/151/UnresolvedEnergyDependentFissionWidths.python.cpp
    python/src/section/2/151/UnresolvedEnergyIndependent.python.cpp
    python/src/section/2/152.python.cpp
    python/src/section/3.python.cpp
    python/src/section/4.python.cpp
    python/src/section/4/Isotropic.python.cpp
    python/src/section/4/LegendreCoefficients.python.cpp
    python/src/section/4/TabulatedDistribution.python.cpp
    python/src/section/4/LegendreDistributions.python.cpp
    python/src/section/4/TabulatedDistributions.python.cpp
    python/src/section/4/MixedDistributions.python.cpp
    python/src/section/5.python.cpp
    python/src/section/5/OutgoingEnergyDistribution.python.cpp
    python/src/file/1.python.cpp
    python/src/file/2.python.cpp
    python/src/file/3.python.cpp
    python/src/file/4.python.cpp
    python/src/file/5.python.cpp
    python/src/tree/Section.python.cpp
    python/src/tree/File.python.cpp
    python/src/tree/Material.python.cpp
    python/src/tree/Tape.python.cpp
    )
target_link_libraries( ENDFtk.python PUBLIC ENDFtk )
target_compile_options( ENDFtk.python PUBLIC "-fPIC" )
target_compile_options( ENDFtk.python PUBLIC "-fvisibility=hidden" )
set_target_properties( ENDFtk.python PROPERTIES OUTPUT_NAME ENDFtk )
set_target_properties( ENDFtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( ENDFtk_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
