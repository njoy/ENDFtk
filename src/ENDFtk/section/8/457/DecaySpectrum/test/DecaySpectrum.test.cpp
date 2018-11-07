#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using DiscreteSpectrum = section::Type< 8, 457 >::DiscreteSpectrum;
using ContinuousSpectrum = section::Type< 8, 457 >::ContinuousSpectrum;
using DecaySpectrum = section::Type< 8, 457 >::DecaySpectrum;

std::string chunk1();
std::string chunk2();
std::string chunk3();

SCENARIO( "DecaySpectrum" ) {

  GIVEN( "valid data for a DecaySpectrum" ) {

    double styp = 0.0;
    std::tuple< double, double > fd = { 1., 0. };
    std::tuple< double, double > fc = { 0.5, 0.25 };
    std::tuple< double, double > erav = { 2.107044e+2, 1.576284e+1 };

    std::vector< DiscreteSpectrum > discrete1 = 
      { { 3., { 4.863000e+4, 5.000000e+1 }, { 1.420112e-6, 2.85306e-10 }, 0.0,
          { 0.0, 0.0 }, { 7.010000e+5, 1.106180e-2 }, { 0.0, 0.0 },
          { 3.315735e+5, 5.608008e+3 } },
        { 4., { 4.935000e+4, 2.000000e+1 }, { 1.335690e-3, 5.409179e-5 }, 0.0,
          { 0.0, 0.0 }, { 8.209999e-1, 0.000000e+0 }, { 0.0, 0.0 },
          { 6.160000e-1, 8.999999e-3 } } };
    std::vector< DiscreteSpectrum > discrete2 = discrete1;
    
    ContinuousSpectrum continuous1 =
      { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
        { 6.133200e-7, 6.133300e-7, 6.02040e-17 } };
    ContinuousSpectrum continuous2 = continuous1;

    THEN( "a DecaySpectrum can be constructed and members can be "
          "tested for discrete spectra only (LCON=0)" ) {
      DecaySpectrum chunk( styp, fd, erav, std::move( discrete1 ) );

      REQUIRE( 0. == chunk.radiationType() );

      REQUIRE( 0 == chunk.LCON() );
      REQUIRE( 0 == chunk.LCOV() );

      REQUIRE( 1. == Approx( std::get< 0 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 0 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 2.107044e+2 == Approx( std::get< 0 >( chunk.averageDecayEnergy() ) ) );
      REQUIRE( 1.576284e+1 == Approx( std::get< 1 >( chunk.averageDecayEnergy() ) ) );

      REQUIRE( std::nullopt != chunk.discreteSpectra() );
      REQUIRE( std::nullopt == chunk.continuousSpectrum() );

      std::vector< DiscreteSpectrum > discrete = *( chunk.discreteSpectra() );
      REQUIRE( 3. == discrete[0].decayChain() );
      REQUIRE( 12 == discrete[0].NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[0].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RIS() ) ) );
      REQUIRE( 7.010000e+5 == Approx( std::get< 0 >( discrete[0].RICC() ) ) );
      REQUIRE( 1.106180e-2 == Approx( std::get< 1 >( discrete[0].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RICK() ) ) );
      REQUIRE( 3.315735e+5 == Approx( std::get< 0 >( discrete[0].RICL() ) ) );
      REQUIRE( 5.608008e+3 == Approx( std::get< 1 >( discrete[0].RICL() ) ) );
      REQUIRE( 4. == discrete[1].decayChain() );
      REQUIRE( 12 == discrete[1].NT() );
      REQUIRE( 4.935000e+4 == Approx( std::get< 0 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 2.000000e+1 == Approx( std::get< 1 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 1.335690e-3 == Approx( std::get< 0 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 5.409179e-5 == Approx( std::get< 1 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[1].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RIS() ) ) );
      REQUIRE( 8.209999e-1 == Approx( std::get< 0 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.000000e+0 == Approx( std::get< 1 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RICK() ) ) );
      REQUIRE( 6.160000e-1 == Approx( std::get< 0 >( discrete[1].RICL() ) ) );
      REQUIRE( 8.999999e-3 == Approx( std::get< 1 >( discrete[1].RICL() ) ) );

      REQUIRE( 8 == chunk.NC() );
    }

    THEN( "a DecaySpectrum can be constructed and members can be "
          "tested for a continuous spectrum only (LCON=1)" ) {
      DecaySpectrum chunk( styp, fc, erav, std::move( continuous1 ) );

      REQUIRE( 0. == chunk.radiationType() );

      REQUIRE( 1 == chunk.LCON() );
      REQUIRE( 0 == chunk.LCOV() );

      REQUIRE( 0. == Approx( std::get< 0 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0.5 == Approx( std::get< 0 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 0.25 == Approx( std::get< 1 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 2.107044e+2 == Approx( std::get< 0 >( chunk.averageDecayEnergy() ) ) );
      REQUIRE( 1.576284e+1 == Approx( std::get< 1 >( chunk.averageDecayEnergy() ) ) );

      REQUIRE( std::nullopt == chunk.discreteSpectra() );
      REQUIRE( std::nullopt != chunk.continuousSpectrum() );

      ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
      REQUIRE( 4. == continuous.decayChain() );
      REQUIRE( 3 == continuous.NP() );
      REQUIRE( 1 == continuous.NR() );
      REQUIRE( 1 == continuous.interpolants().size() );
      REQUIRE( 1 == continuous.boundaries().size() );
      REQUIRE( 1 == continuous.interpolants()[0] );
      REQUIRE( 3 == continuous.boundaries()[0] );
      REQUIRE( 3 == continuous.energies().size() );
      REQUIRE( 3 == continuous.spectralValues().size() );
      REQUIRE( 0.0 == Approx( continuous.energies()[0] ) );
      REQUIRE( 5e+5 == Approx( continuous.energies()[1] ) );
      REQUIRE( 7.3e+6 == Approx( continuous.energies()[2] ) );
      REQUIRE( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
      REQUIRE( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
      REQUIRE( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

      REQUIRE( 5 == chunk.NC() );
    }

    THEN( "a DecaySpectrum can be constructed and members can be "
          "tested for discrete and continuous spectra (LCON=2)" ) {
      DecaySpectrum chunk( styp, fd, fc, erav, std::move( discrete2 ),
                           std::move( continuous2 ) );

      REQUIRE( 0. == chunk.radiationType() );

      REQUIRE( 2 == chunk.LCON() );
      REQUIRE( 0 == chunk.LCOV() );

      REQUIRE( 1. == Approx( std::get< 0 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0.5 == Approx( std::get< 0 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 0.25 == Approx( std::get< 1 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 2.107044e+2 == Approx( std::get< 0 >( chunk.averageDecayEnergy() ) ) );
      REQUIRE( 1.576284e+1 == Approx( std::get< 1 >( chunk.averageDecayEnergy() ) ) );

      REQUIRE( std::nullopt != chunk.discreteSpectra() );
      REQUIRE( std::nullopt != chunk.continuousSpectrum() );

      std::vector< DiscreteSpectrum > discrete = *( chunk.discreteSpectra() );
      REQUIRE( 3. == discrete[0].decayChain() );
      REQUIRE( 12 == discrete[0].NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[0].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RIS() ) ) );
      REQUIRE( 7.010000e+5 == Approx( std::get< 0 >( discrete[0].RICC() ) ) );
      REQUIRE( 1.106180e-2 == Approx( std::get< 1 >( discrete[0].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RICK() ) ) );
      REQUIRE( 3.315735e+5 == Approx( std::get< 0 >( discrete[0].RICL() ) ) );
      REQUIRE( 5.608008e+3 == Approx( std::get< 1 >( discrete[0].RICL() ) ) );
      REQUIRE( 4. == discrete[1].decayChain() );
      REQUIRE( 12 == discrete[1].NT() );
      REQUIRE( 4.935000e+4 == Approx( std::get< 0 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 2.000000e+1 == Approx( std::get< 1 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 1.335690e-3 == Approx( std::get< 0 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 5.409179e-5 == Approx( std::get< 1 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[1].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RIS() ) ) );
      REQUIRE( 8.209999e-1 == Approx( std::get< 0 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.000000e+0 == Approx( std::get< 1 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RICK() ) ) );
      REQUIRE( 6.160000e-1 == Approx( std::get< 0 >( discrete[1].RICL() ) ) );
      REQUIRE( 8.999999e-3 == Approx( std::get< 1 >( discrete[1].RICL() ) ) );

      ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
      REQUIRE( 4. == continuous.decayChain() );
      REQUIRE( 3 == continuous.NP() );
      REQUIRE( 1 == continuous.NR() );
      REQUIRE( 1 == continuous.interpolants().size() );
      REQUIRE( 1 == continuous.boundaries().size() );
      REQUIRE( 1 == continuous.interpolants()[0] );
      REQUIRE( 3 == continuous.boundaries()[0] );
      REQUIRE( 3 == continuous.energies().size() );
      REQUIRE( 3 == continuous.spectralValues().size() );
      REQUIRE( 0.0 == Approx( continuous.energies()[0] ) );
      REQUIRE( 5e+5 == Approx( continuous.energies()[1] ) );
      REQUIRE( 7.3e+6 == Approx( continuous.energies()[2] ) );
      REQUIRE( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
      REQUIRE( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
      REQUIRE( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid DecaySpectrum with only discrete "
         "spectra (LCON=0)" ) {

    std::string string = chunk1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
      
    THEN( "a DecaySpectrum can be constructed and members can be tested" ) {
      DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      REQUIRE( 0. == chunk.radiationType() );

      REQUIRE( 0 == chunk.LCON() );
      REQUIRE( 0 == chunk.LCOV() );

      REQUIRE( 1. == Approx( std::get< 0 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 0 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 2.107044e+2 == Approx( std::get< 0 >( chunk.averageDecayEnergy() ) ) );
      REQUIRE( 1.576284e+1 == Approx( std::get< 1 >( chunk.averageDecayEnergy() ) ) );

      REQUIRE( std::nullopt != chunk.discreteSpectra() );
      REQUIRE( std::nullopt == chunk.continuousSpectrum() );

      std::vector< DiscreteSpectrum > discrete = *( chunk.discreteSpectra() );
      REQUIRE( 3. == discrete[0].decayChain() );
      REQUIRE( 12 == discrete[0].NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[0].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RIS() ) ) );
      REQUIRE( 7.010000e+5 == Approx( std::get< 0 >( discrete[0].RICC() ) ) );
      REQUIRE( 1.106180e-2 == Approx( std::get< 1 >( discrete[0].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RICK() ) ) );
      REQUIRE( 3.315735e+5 == Approx( std::get< 0 >( discrete[0].RICL() ) ) );
      REQUIRE( 5.608008e+3 == Approx( std::get< 1 >( discrete[0].RICL() ) ) );
      REQUIRE( 4. == discrete[1].decayChain() );
      REQUIRE( 12 == discrete[1].NT() );
      REQUIRE( 4.935000e+4 == Approx( std::get< 0 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 2.000000e+1 == Approx( std::get< 1 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 1.335690e-3 == Approx( std::get< 0 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 5.409179e-5 == Approx( std::get< 1 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[1].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RIS() ) ) );
      REQUIRE( 8.209999e-1 == Approx( std::get< 0 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.000000e+0 == Approx( std::get< 1 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RICK() ) ) );
      REQUIRE( 6.160000e-1 == Approx( std::get< 0 >( discrete[1].RICL() ) ) );
      REQUIRE( 8.999999e-3 == Approx( std::get< 1 >( discrete[1].RICL() ) ) );

      REQUIRE( 8 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid DecaySpectrum with only a "
         "continuous spectrum (LCON=1)" ) {

    std::string string = chunk2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
      
    THEN( "a DecaySpectrum can be constructed and members can be tested" ) {
      DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      REQUIRE( 0. == chunk.radiationType() );

      REQUIRE( 1 == chunk.LCON() );
      REQUIRE( 0 == chunk.LCOV() );

      REQUIRE( 0. == Approx( std::get< 0 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0.5 == Approx( std::get< 0 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 0.25 == Approx( std::get< 1 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 2.107044e+2 == Approx( std::get< 0 >( chunk.averageDecayEnergy() ) ) );
      REQUIRE( 1.576284e+1 == Approx( std::get< 1 >( chunk.averageDecayEnergy() ) ) );

      REQUIRE( std::nullopt == chunk.discreteSpectra() );
      REQUIRE( std::nullopt != chunk.continuousSpectrum() );

      ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
      REQUIRE( 4. == continuous.decayChain() );
      REQUIRE( 3 == continuous.NP() );
      REQUIRE( 1 == continuous.NR() );
      REQUIRE( 1 == continuous.interpolants().size() );
      REQUIRE( 1 == continuous.boundaries().size() );
      REQUIRE( 1 == continuous.interpolants()[0] );
      REQUIRE( 3 == continuous.boundaries()[0] );
      REQUIRE( 3 == continuous.energies().size() );
      REQUIRE( 3 == continuous.spectralValues().size() );
      REQUIRE( 0.0 == Approx( continuous.energies()[0] ) );
      REQUIRE( 5e+5 == Approx( continuous.energies()[1] ) );
      REQUIRE( 7.3e+6 == Approx( continuous.energies()[2] ) );
      REQUIRE( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
      REQUIRE( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
      REQUIRE( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

      REQUIRE( 5 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid DecaySpectrum with discrete and "
         "continuous spectra (LCON=2)" ) {

    std::string string = chunk3();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
      
    THEN( "a DecaySpectrum can be constructed and members can be tested" ) {
      DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      REQUIRE( 0. == chunk.radiationType() );

      REQUIRE( 2 == chunk.LCON() );
      REQUIRE( 0 == chunk.LCOV() );

      REQUIRE( 1. == Approx( std::get< 0 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( chunk.discreteNormalisationFactor() ) ) );
      REQUIRE( 0.5 == Approx( std::get< 0 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 0.25 == Approx( std::get< 1 >( chunk.continuousNormalisationFactor() ) ) );
      REQUIRE( 2.107044e+2 == Approx( std::get< 0 >( chunk.averageDecayEnergy() ) ) );
      REQUIRE( 1.576284e+1 == Approx( std::get< 1 >( chunk.averageDecayEnergy() ) ) );

      REQUIRE( std::nullopt != chunk.discreteSpectra() );
      REQUIRE( std::nullopt != chunk.continuousSpectrum() );

      std::vector< DiscreteSpectrum > discrete = *( chunk.discreteSpectra() );
      REQUIRE( 3. == discrete[0].decayChain() );
      REQUIRE( 12 == discrete[0].NT() );
      REQUIRE( 4.863000e+4 == Approx( std::get< 0 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( discrete[0].discreteEnergy() ) ) );
      REQUIRE( 1.420112e-6 == Approx( std::get< 0 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 2.85306e-10 == Approx( std::get< 1 >( discrete[0].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[0].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RIS() ) ) );
      REQUIRE( 7.010000e+5 == Approx( std::get< 0 >( discrete[0].RICC() ) ) );
      REQUIRE( 1.106180e-2 == Approx( std::get< 1 >( discrete[0].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[0].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[0].RICK() ) ) );
      REQUIRE( 3.315735e+5 == Approx( std::get< 0 >( discrete[0].RICL() ) ) );
      REQUIRE( 5.608008e+3 == Approx( std::get< 1 >( discrete[0].RICL() ) ) );
      REQUIRE( 4. == discrete[1].decayChain() );
      REQUIRE( 12 == discrete[1].NT() );
      REQUIRE( 4.935000e+4 == Approx( std::get< 0 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 2.000000e+1 == Approx( std::get< 1 >( discrete[1].discreteEnergy() ) ) );
      REQUIRE( 1.335690e-3 == Approx( std::get< 0 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 5.409179e-5 == Approx( std::get< 1 >( discrete[1].relativeIntensity() ) ) );
      REQUIRE( 0. == discrete[1].type() );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RIS() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RIS() ) ) );
      REQUIRE( 8.209999e-1 == Approx( std::get< 0 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.000000e+0 == Approx( std::get< 1 >( discrete[1].RICC() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 0 >( discrete[1].RICK() ) ) );
      REQUIRE( 0.0 == Approx( std::get< 1 >( discrete[1].RICK() ) ) );
      REQUIRE( 6.160000e-1 == Approx( std::get< 0 >( discrete[1].RICL() ) ) );
      REQUIRE( 8.999999e-3 == Approx( std::get< 1 >( discrete[1].RICL() ) ) );

      ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
      REQUIRE( 4. == continuous.decayChain() );
      REQUIRE( 3 == continuous.NP() );
      REQUIRE( 1 == continuous.NR() );
      REQUIRE( 1 == continuous.interpolants().size() );
      REQUIRE( 1 == continuous.boundaries().size() );
      REQUIRE( 1 == continuous.interpolants()[0] );
      REQUIRE( 3 == continuous.boundaries()[0] );
      REQUIRE( 3 == continuous.energies().size() );
      REQUIRE( 3 == continuous.spectralValues().size() );
      REQUIRE( 0.0 == Approx( continuous.energies()[0] ) );
      REQUIRE( 5e+5 == Approx( continuous.energies()[1] ) );
      REQUIRE( 7.3e+6 == Approx( continuous.energies()[2] ) );
      REQUIRE( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
      REQUIRE( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
      REQUIRE( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

      REQUIRE( 11 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of DecaySpectrum with discrete spectra only "
         "(LCON=0)" ) {

    std::string string = chunk1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DecaySpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of DecaySpectrum with a continuous spectrum only "
         "(LCON=1)" ) {

    std::string string = chunk2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DecaySpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of DecaySpectrum with discrete and continuous "
         "spectra (LCON=2)" ) {

    std::string string = chunk3();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DecaySpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk1() {
  return
    " 0.000000+0 0.000000+0          0          0          6          23580 8457     \n"
    " 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n"
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n"
    " 4.935000+4 2.000000+1          0          0         12          03580 8457     \n"
    " 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n"
    " 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n";
}

std::string chunk2() {
  return
    " 0.000000+0 0.000000+0          1          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 2.107044+2 1.576284+1 5.000000-1 2.500000-13580 8457     \n"
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}

std::string chunk3() {
  return
    " 0.000000+0 0.000000+0          2          0          6          23580 8457     \n"
    " 1.000000+0 0.000000+0 2.107044+2 1.576284+1 5.000000-1 2.500000-13580 8457     \n"
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n"
    " 4.935000+4 2.000000+1          0          0         12          03580 8457     \n"
    " 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n"
    " 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n"
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}
