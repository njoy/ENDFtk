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

message( STATUS "Using ${REPOSITORIES} repositories" )

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
# ENDFtk : library
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
    INTERFACE range-v3
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ENDFtk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include_directories( python/src/ )

pybind11_add_module( ENDFtk.python
    EXCLUDE_FROM_ALL
    python/src/ENDFtk.python.cpp
    python/src/record/ControlRecord.python.cpp
    python/src/record/ListRecord.python.cpp
    python/src/record/TabulationRecord.python.cpp
    python/src/record/InterpolationRecord.python.cpp
    python/src/record/DirectoryRecord.python.cpp
    python/src/record/TapeIdentification.python.cpp
    python/src/section/CovariancePairs.python.cpp
    python/src/section/SquareMatrix.python.cpp
    python/src/section/covariance.python.cpp
    python/src/section/RectangularMatrix.python.cpp
    python/src/section/1/TabulatedMultiplicity.python.cpp
    python/src/section/1/PolynomialMultiplicity.python.cpp
    python/src/section/1/451.python.cpp
    python/src/section/1/452.python.cpp
    python/src/section/1/455.python.cpp
    python/src/section/1/455/DecayConstants.python.cpp
    python/src/section/1/455/EnergyIndependentConstants.python.cpp
    python/src/section/1/455/EnergyDependentConstants.python.cpp
    python/src/section/1/456.python.cpp
    python/src/section/1/458.python.cpp
    python/src/section/1/458/EnergyReleaseComponent.python.cpp
    python/src/section/1/458/ThermalPointComponents.python.cpp
    python/src/section/1/458/PolynomialComponents.python.cpp
    python/src/section/1/458/TabulatedComponents.python.cpp
    python/src/section/1/460.python.cpp
    python/src/section/1/460/DiscretePhotonMultiplicity.python.cpp
    python/src/section/1/460/DiscretePhotons.python.cpp
    python/src/section/1/460/ContinuousPhotons.python.cpp
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
    python/src/section/2/151/NoBackgroundRMatrix.python.cpp
    python/src/section/2/151/SammyBackgroundRMatrix.python.cpp
    python/src/section/2/151/FrohnerBackgroundRMatrix.python.cpp
    python/src/section/2/151/TabulatedBackgroundRMatrix.python.cpp
    python/src/section/2/151/BackgroundChannels.python.cpp
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
    python/src/section/23.python.cpp
    python/src/section/26.python.cpp
    python/src/section/26/Multiplicity.python.cpp
    python/src/section/26/EnergyTransfer.python.cpp
    python/src/section/26/LAW1/LegendreCoefficients.python.cpp
    python/src/section/26/LAW2/TabulatedDistribution.python.cpp
    python/src/section/26/ContinuumEnergyAngle.python.cpp
    python/src/section/26/DiscreteTwoBodyScattering.python.cpp
    python/src/section/26/ReactionProduct.python.cpp
    python/src/section/27.python.cpp
    python/src/section/28/SubshellData.python.cpp
    python/src/section/28.python.cpp
    python/src/section/3.python.cpp
    python/src/section/32/151.python.cpp
    python/src/section/32/151/BreitWignerLValue.python.cpp
    python/src/section/32/151/LimitedSingleLevelBreitWigner.python.cpp
    python/src/section/32/151/LimitedMultiLevelBreitWigner.python.cpp
    python/src/section/32/151/ShortRangeBreitWignerBlock.python.cpp
    python/src/section/32/151/ShortRangeReichMooreBlock.python.cpp
    python/src/section/32/151/ReichMooreScatteringRadiusUncertainties.python.cpp
    python/src/section/32/151/ResonanceParameters.python.cpp
    python/src/section/32/151/GeneralSingleLevelBreitWigner.python.cpp
    python/src/section/32/151/GeneralMultiLevelBreitWigner.python.cpp
    python/src/section/32/151/GeneralReichMoore.python.cpp
    python/src/section/32/151/ResonanceRange.python.cpp
    python/src/section/32/151/Isotope.python.cpp
    python/src/section/4.python.cpp
    python/src/section/4/Isotropic.python.cpp
    python/src/section/4/LegendreCoefficients.python.cpp
    python/src/section/4/TabulatedDistribution.python.cpp
    python/src/section/4/LegendreDistributions.python.cpp
    python/src/section/4/TabulatedDistributions.python.cpp
    python/src/section/4/MixedDistributions.python.cpp
    python/src/section/5.python.cpp
    python/src/section/5/Parameter.python.cpp
    python/src/section/5/OutgoingEnergyDistribution.python.cpp
    python/src/section/5/TabulatedSpectrum.python.cpp
    python/src/section/5/DistributionFunction.python.cpp
    python/src/section/5/EffectiveTemperature.python.cpp
    python/src/section/5/GeneralEvaporationSpectrum.python.cpp
    python/src/section/5/EvaporationSpectrum.python.cpp
    python/src/section/5/MaxwellianFissionSpectrum.python.cpp
    python/src/section/5/WattSpectrum.python.cpp
    python/src/section/5/MadlandNixSpectrum.python.cpp
    python/src/section/5/Probability.python.cpp
    python/src/section/5/PartialDistribution.python.cpp
    python/src/section/6.python.cpp
    python/src/section/6/Multiplicity.python.cpp
    python/src/section/6/DefinedElsewhere.python.cpp
    python/src/section/6/Unknown.python.cpp
    python/src/section/6/LAW1/LegendreCoefficients.python.cpp
    python/src/section/6/LAW1/TabulatedDistribution.python.cpp
    python/src/section/6/LAW1/KalbachMann.python.cpp
    python/src/section/6/LAW1/ThermalScatteringData.python.cpp
    python/src/section/6/ContinuumEnergyAngle.python.cpp
    python/src/section/6/LAW2/LegendreCoefficients.python.cpp
    python/src/section/6/LAW2/TabulatedDistribution.python.cpp
    python/src/section/6/DiscreteTwoBodyScattering.python.cpp
    python/src/section/6/IsotropicDiscreteEmission.python.cpp
    python/src/section/6/DiscreteTwoBodyRecoils.python.cpp
    python/src/section/6/ChargedParticleElasticScattering.python.cpp
    python/src/section/6/LAW5/LegendreCoefficients.python.cpp
    python/src/section/6/LAW5/NuclearAmplitudeExpansion.python.cpp
    python/src/section/6/LAW5/NuclearPlusInterference.python.cpp
    python/src/section/6/NBodyPhaseSpace.python.cpp
    python/src/section/6/LAW7/EnergyDistribution.python.cpp
    python/src/section/6/LAW7/AngularDistribution.python.cpp
    python/src/section/6/LaboratoryAngleEnergy.python.cpp
    python/src/section/6/ReactionProduct.python.cpp
    python/src/section/7/2.python.cpp
    python/src/section/7/2/CoherentElastic.python.cpp
    python/src/section/7/2/IncoherentElastic.python.cpp
    python/src/section/7/2/MixedElastic.python.cpp
    python/src/section/7/4.python.cpp
    python/src/section/7/4/EffectiveTemperature.python.cpp
    python/src/section/7/4/ScatteringLawConstants.python.cpp
    python/src/section/7/4/AnalyticalFunctions.python.cpp
    python/src/section/7/4/TabulatedFunctions.python.cpp
    python/src/section/7/4/ScatteringFunction.python.cpp
    python/src/section/8/FissionYieldData.python.cpp
    python/src/section/8/454.python.cpp
    python/src/section/8/457.python.cpp
    python/src/section/8/457/AverageDecayEnergies.python.cpp
    python/src/section/8/457/DecayMode.python.cpp
    python/src/section/8/457/DecayModes.python.cpp
    python/src/section/8/457/DiscreteSpectrum.python.cpp
    python/src/section/8/457/ContinuousSpectrum.python.cpp
    python/src/section/8/457/DecaySpectrum.python.cpp
    python/src/section/8/459.python.cpp
    python/src/section/9.python.cpp
    python/src/section/9/ReactionProduct.python.cpp
    python/src/section/10.python.cpp
    python/src/section/10/ReactionProduct.python.cpp
    python/src/section/12.python.cpp
    python/src/section/12/TotalMultiplicity.python.cpp
    python/src/section/12/PartialMultiplicity.python.cpp
    python/src/section/12/Multiplicities.python.cpp
    python/src/section/12/TransitionProbabilities.python.cpp
    python/src/section/13.python.cpp
    python/src/section/13/TotalCrossSection.python.cpp
    python/src/section/13/PartialCrossSection.python.cpp
    python/src/section/14.python.cpp
    python/src/section/14/IsotropicDiscretePhoton.python.cpp
    python/src/section/14/LegendreCoefficients.python.cpp
    python/src/section/14/TabulatedDistribution.python.cpp
    python/src/section/14/LegendreDistributions.python.cpp
    python/src/section/14/TabulatedDistributions.python.cpp
    python/src/section/15.python.cpp
    python/src/section/15/OutgoingEnergyDistribution.python.cpp
    python/src/section/15/TabulatedSpectrum.python.cpp
    python/src/section/15/Probability.python.cpp
    python/src/section/15/PartialDistribution.python.cpp
    python/src/section/33.python.cpp
    python/src/section/33/DerivedRedundant.python.cpp
    python/src/section/33/DerivedRatioToStandard.python.cpp
    python/src/section/33/ReactionBlock.python.cpp
    python/src/section/34.python.cpp
    python/src/section/34/LegendreBlock.python.cpp
    python/src/section/34/ReactionBlock.python.cpp
    python/src/file/1.python.cpp
    python/src/file/2.python.cpp
    python/src/file/3.python.cpp
    python/src/file/4.python.cpp
    python/src/file/5.python.cpp
    python/src/file/6.python.cpp
    python/src/file/7.python.cpp
    python/src/file/8.python.cpp
    python/src/file/9.python.cpp
    python/src/file/10.python.cpp
    python/src/file/12.python.cpp
    python/src/file/13.python.cpp
    python/src/file/14.python.cpp
    python/src/file/15.python.cpp
    python/src/file/23.python.cpp
    python/src/file/26.python.cpp
    python/src/file/27.python.cpp
    python/src/file/28.python.cpp
    python/src/file/32.python.cpp
    python/src/file/33.python.cpp
    python/src/file/34.python.cpp
    python/src/Material.python.cpp
    python/src/tree/Section.python.cpp
    python/src/tree/File.python.cpp
    python/src/tree/Material.python.cpp
    python/src/tree/Tape.python.cpp
    )
target_link_libraries( ENDFtk.python PRIVATE ENDFtk )
target_compile_options( ENDFtk.python PRIVATE "-fPIC" )
target_compile_options( ENDFtk.python PRIVATE "-fvisibility=hidden" )
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
