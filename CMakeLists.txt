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

option( ENDFtk.tests "Build the ENDFtk unit tests" OFF )
option( ENDFtk.python "Build ENDFtk python bindings" ON )
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

add_library( ENDFtk INTERFACE )
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

if( ENDFtk.python )
  pybind11_add_module( ENDFtk.python
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ENDFtk.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/record/ControlRecord.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/record/ListRecord.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/record/TabulationRecord.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/record/InterpolationRecord.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/record/DirectoryRecord.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/record/TapeIdentification.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/CovariancePairs.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/SquareMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/covariance.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/RectangularMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/TabulatedMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/PolynomialMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/451.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/452.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/455.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/455/DecayConstants.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/455/EnergyIndependentConstants.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/455/EnergyDependentConstants.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/456.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/458.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/458/EnergyReleaseComponent.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/458/ThermalPointComponents.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/458/PolynomialComponents.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/458/TabulatedComponents.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/460.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/460/DiscretePhotonMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/460/DiscretePhotons.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/1/460/ContinuousPhotons.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/Isotope.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ScatteringRadius.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ResonanceRange.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/SpecialCase.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/BreitWignerLValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ReichMooreLValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/SingleLevelBreitWigner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/MultiLevelBreitWigner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ReichMoore.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ParticlePairs.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ResonanceChannels.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/ResonanceParameters.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/NoBackgroundRMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/SammyBackgroundRMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/FrohnerBackgroundRMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/TabulatedBackgroundRMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/BackgroundChannels.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/SpinGroup.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/RMatrixLimited.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyDependentFissionWidthsJValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyDependentJValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyIndependentLValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyDependentFissionWidthsLValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyDependentLValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyDependent.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyDependentFissionWidths.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/151/UnresolvedEnergyIndependent.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/2/152.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/23.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/Multiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/EnergyTransfer.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/LAW1/LegendreCoefficients.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/LAW2/TabulatedDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/ContinuumEnergyAngle.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/DiscreteTwoBodyScattering.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/26/ReactionProduct.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/27.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/28/SubshellData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/28.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/3.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/BreitWignerLValue.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/LimitedSingleLevelBreitWigner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/LimitedMultiLevelBreitWigner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/ShortRangeBreitWignerBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/ShortRangeReichMooreBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/ShortRangeRMatrixLimitedBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/ReichMooreScatteringRadiusUncertainties.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/ResonanceParameters.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/CovarianceMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/GeneralSingleLevelBreitWigner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/GeneralMultiLevelBreitWigner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/GeneralReichMoore.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/GeneralRMatrixLimited.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/CompactCorrelationMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/ResonanceRange.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/32/151/Isotope.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4/Isotropic.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4/LegendreCoefficients.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4/TabulatedDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4/LegendreDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4/TabulatedDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/4/MixedDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/Parameter.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/OutgoingEnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/TabulatedSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/DistributionFunction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/EffectiveTemperature.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/GeneralEvaporationSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/EvaporationSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/MaxwellianFissionSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/WattSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/MadlandNixSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/Probability.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/5/PartialDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/Multiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/DefinedElsewhere.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/Unknown.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW1/LegendreCoefficients.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW1/TabulatedDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW1/KalbachMann.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW1/ThermalScatteringData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/ContinuumEnergyAngle.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW2/LegendreCoefficients.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW2/TabulatedDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/DiscreteTwoBodyScattering.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/IsotropicDiscreteEmission.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/DiscreteTwoBodyRecoils.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/ChargedParticleElasticScattering.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW5/LegendreCoefficients.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW5/NuclearAmplitudeExpansion.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW5/NuclearPlusInterference.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/NBodyPhaseSpace.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW7/EnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LAW7/AngularDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/LaboratoryAngleEnergy.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/6/ReactionProduct.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/2.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/2/CoherentElastic.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/2/IncoherentElastic.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/2/MixedElastic.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/4.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/4/EffectiveTemperature.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/4/ScatteringLawConstants.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/4/AnalyticalFunctions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/4/TabulatedFunctions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/7/4/ScatteringFunction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/FissionYieldData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/454.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457/AverageDecayEnergies.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457/DecayMode.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457/DecayModes.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457/DiscreteSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457/ContinuousSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/457/DecaySpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/8/459.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/9.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/9/ReactionProduct.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/10.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/10/ReactionProduct.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/12.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/12/TotalMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/12/PartialMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/12/Multiplicities.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/12/TransitionProbabilities.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/13.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/13/TotalCrossSection.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/13/PartialCrossSection.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/14.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/14/IsotropicDiscretePhoton.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/14/LegendreCoefficients.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/14/TabulatedDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/14/LegendreDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/14/TabulatedDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/15.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/15/OutgoingEnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/15/TabulatedSpectrum.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/15/Probability.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/15/PartialDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/33.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/33/DerivedRedundant.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/33/DerivedRatioToStandard.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/33/ReactionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/34.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/34/LegendreBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/section/34/ReactionBlock.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/1.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/2.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/3.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/4.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/5.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/6.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/7.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/8.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/9.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/10.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/12.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/13.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/14.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/15.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/23.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/26.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/27.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/28.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/32.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/33.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/file/34.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Material.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/tree/Section.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/tree/File.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/tree/Material.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/tree/Tape.python.cpp
      )

  target_link_libraries( ENDFtk.python PRIVATE ENDFtk )
  target_include_directories( ENDFtk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( ENDFtk.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( ENDFtk.python PROPERTIES OUTPUT_NAME ENDFtk )
  set_target_properties( ENDFtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( ENDFtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON)

  message( STATUS "Building ENDFtk's python API" )

  list( APPEND ENDFTK_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( ENDFtk.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
