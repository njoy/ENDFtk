if(ENDFtk.python)

    find_package( Python3 REQUIRED )
    pybind11_add_module( ENDFtk.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/record/ControlRecord.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/record/ListRecord.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/record/TabulationRecord.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/record/InterpolationRecord.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/record/DirectoryRecord.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/record/TapeIdentification.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/CovariancePairs.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/SquareMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/RectangularMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/DerivedRedundant.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/DerivedRatioToStandard.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/ReactionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/covariance.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/TabulatedMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/PolynomialMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/451.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/452.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/455.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/455/DecayConstants.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/455/EnergyIndependentConstants.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/455/EnergyDependentConstants.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/456.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/458.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/458/EnergyReleaseComponent.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/458/ThermalPointComponents.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/458/PolynomialComponents.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/458/TabulatedComponents.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/460.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/460/DiscretePhotonMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/460/DiscretePhotons.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/1/460/ContinuousPhotons.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/Isotope.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ScatteringRadius.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ResonanceRange.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/SpecialCase.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/BreitWignerLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ReichMooreLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/SingleLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/MultiLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ReichMoore.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ParticlePairs.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ResonanceChannels.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/ResonanceParameters.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/NoBackgroundRMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/SammyBackgroundRMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/FrohnerBackgroundRMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/TabulatedBackgroundRMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/BackgroundChannels.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/SpinGroup.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/RMatrixLimited.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyDependentFissionWidthsJValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyDependentJValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyIndependentLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyDependentFissionWidthsLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyDependentLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyDependent.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyDependentFissionWidths.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/151/UnresolvedEnergyIndependent.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/2/152.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/23.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/Multiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/EnergyTransfer.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/LAW1/LegendreCoefficients.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/LAW2/TabulatedDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/ContinuumEnergyAngle.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/DiscreteTwoBodyScattering.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/26/ReactionProduct.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/27.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/28/SubshellData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/28.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/3.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/ScatteringRadiusCovariances.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LimitedBreitWignerLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LimitedSingleLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LimitedMultiLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/ShortRangeBreitWignerBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/ShortRangeReichMooreBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/ShortRangeRMatrixLimitedBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/ReichMooreScatteringRadiusUncertainties.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LCOMP1/ResonanceParameters.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LCOMP1/CovarianceMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/GeneralSingleLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/GeneralMultiLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/GeneralReichMoore.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/GeneralRMatrixLimited.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactCorrelationMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactBreitWignerUncertainties.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactReichMooreUncertainties.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactSingleLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactMultiLevelBreitWigner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactReichMoore.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LCOMP2/ParticlePairs.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LCOMP2/ResonanceChannels.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LCOMP2/ResonanceParameters.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/LCOMP2/SpinGroup.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactRMatrixLimitedUncertainties.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/CompactRMatrixLimited.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/UnresolvedCovarianceMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/UnresolvedLValue.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/UnresolvedRelativeCovariances.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/ResonanceRange.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/32/151/Isotope.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4/Isotropic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4/LegendreCoefficients.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4/TabulatedDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4/LegendreDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4/TabulatedDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/4/MixedDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/Parameter.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/OutgoingEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/TabulatedSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/DistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/EffectiveTemperature.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/GeneralEvaporationSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/EvaporationSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/MaxwellianFissionSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/WattSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/MadlandNixSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/Probability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/5/PartialDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/Multiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/DefinedElsewhere.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/Unknown.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW1/LegendreCoefficients.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW1/TabulatedDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW1/KalbachMann.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW1/ThermalScatteringData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/ContinuumEnergyAngle.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW2/LegendreCoefficients.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW2/TabulatedDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/DiscreteTwoBodyScattering.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/IsotropicDiscreteEmission.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/DiscreteTwoBodyRecoils.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/ChargedParticleElasticScattering.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW5/LegendreCoefficients.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW5/NuclearAmplitudeExpansion.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW5/NuclearPlusInterference.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/NBodyPhaseSpace.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW7/EnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LAW7/AngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/LaboratoryAngleEnergy.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/6/ReactionProduct.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/2.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/2/CoherentElastic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/2/IncoherentElastic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/2/MixedElastic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/4.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/4/EffectiveTemperature.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/4/ScatteringLawConstants.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/4/AnalyticalFunctions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/4/TabulatedFunctions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/4/ScatteringFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/451.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/7/451/ElementInformation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/FissionYieldData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/454.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457/AverageDecayEnergies.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457/DecayMode.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457/DecayModes.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457/DiscreteSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457/ContinuousSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/457/DecaySpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/8/459.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/9.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/9/ReactionProduct.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/10.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/10/ReactionProduct.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/12.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/12/TotalMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/12/PartialMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/12/Multiplicities.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/12/TransitionProbabilities.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/13.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/13/TotalCrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/13/PartialCrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/14.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/14/IsotropicDiscretePhoton.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/14/LegendreCoefficients.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/14/TabulatedDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/14/LegendreDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/14/TabulatedDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/15.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/15/OutgoingEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/15/TabulatedSpectrum.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/15/Probability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/15/PartialDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/31.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/33.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/34.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/34/LegendreBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/34/ReactionBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/35.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/35/SquareMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/40.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/section/40/LevelBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/3g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/1g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/5/18g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/5/455g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/6g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/33g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gsection/16g.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/1.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/2.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/3.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/4.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/5.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/6.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/7.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/8.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/9.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/10.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/12.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/13.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/14.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/15.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/16.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/23.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/26.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/27.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/28.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/31.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/32.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/33.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/34.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/35.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/40.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Material.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/Section.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/File.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/Material.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/Tape.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/GSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/GFile.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/GMaterial.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/GTape.python.cpp
    )

    target_link_libraries(ENDFtk.python PRIVATE njoy::ENDFtk)
    add_dependencies( ENDFtk.python njoy::tools.python)
    target_include_directories( ENDFtk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set_target_properties( ENDFtk.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( ENDFtk.python PROPERTIES OUTPUT_NAME ENDFtk )
    set_target_properties( ENDFtk.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( ENDFtk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( ENDFtk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with mcatk to the installed library rpath
    set_target_properties( ENDFtk.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( ENDFtk.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (ENDFtk.installation)
        install( TARGETS ENDFtk.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building ENDFtk's python API" )

    # Append potential installation and build paths for tools python module
    set(ENDFtk_PYTHONPATH "$<TARGET_FILE_DIR:ENDFtk.python>")
    set(tools_PYTHONPATH "$<TARGET_FILE_DIR:njoy::tools.python>")

    # Windows and unix have different delimiter for paths
    if (WIN32)
	    set(PATH_DELIM "\;")
    else()
	    set(PATH_DELIM ":")
    endif()

    if (tools_DIR)
	    set(tools_PYTHONPATH_PARTS ${tools_PYTHONPATH} "${tools_DIR}/../../../${CMAKE_INSTALL_LIBDIR}" )
	    string( JOIN "${PATH_DELIM}" tools_PYTHONPATH ${tools_PYTHONPATH_PARTS})
    endif()

    if( ENDFtk.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(PYTHONPATH_PARTS ${tools_PYTHONPATH} ${ENDFtk_PYTHONPATH} $ENV{PYTHONPATH})
    string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/ENDFtk")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET ENDFtk.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${pybind11stubgen_exe} ENDFtk -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/ENDFtk.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building ENDFtk's python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET ENDFtk.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (ENDFtk.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/ENDFtk/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end ENDFtk.python check
