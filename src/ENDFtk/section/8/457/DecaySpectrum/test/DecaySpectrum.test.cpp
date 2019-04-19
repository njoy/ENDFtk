#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using DiscreteSpectrum = section::Type< 8, 457 >::DiscreteSpectrum;
using ContinuousSpectrum = section::Type< 8, 457 >::ContinuousSpectrum;
using DecaySpectrum = section::Type< 8, 457 >::DecaySpectrum;

std::string chunkWithLCONZero();
void verifyChunkWithLCONZero( const DecaySpectrum& );
std::string chunkWithLCONOne();
void verifyChunkWithLCONOne( const DecaySpectrum& );
std::string chunkWithLCONTwo();
void verifyChunkWithLCONTwo( const DecaySpectrum& );
std::string chunkWithUnsupportedLCOV();

SCENARIO( "DecaySpectrum" ) {

  GIVEN( "valid data for a DecaySpectrum with LCON=0" ) {

    WHEN( "the data is given explicitly" ) {

      double styp = 0.0;
      std::array< double, 2 > fd = {{ 1., 0. }};
      std::array< double, 2 > fc = {{ 0.5, 0.25 }};
      std::array< double, 2 > erav = {{ 2.107044e+2, 1.576284e+1 }};

      std::vector< DiscreteSpectrum > discrete = 
        { { 3., {{ 4.863000e+4, 5.000000e+1 }},
            {{ 1.420112e-6, 2.85306e-10 }}, 0.0,
            {{ 0.0, 0.0 }}, {{ 7.010000e+5, 1.106180e-2 }}, {{ 0.0, 0.0 }},
            {{ 3.315735e+5, 5.608008e+3 }} },
          { 4., {{ 4.935000e+4, 2.000000e+1 }},
            {{ 1.335690e-3, 5.409179e-5 }}, 0.0,
            {{ 0.0, 0.0 }}, {{ 8.209999e-1, 0.000000e+0 }}, {{ 0.0, 0.0 }},
            {{ 6.160000e-1, 8.999999e-3 }} } };

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        DecaySpectrum chunk( styp, fd, erav, std::move( discrete ) );
        verifyChunkWithLCONZero( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithLCONZero();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      
      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkWithLCONZero( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DecaySpectrum with LCON=1" ) {

    WHEN( "the data is given explicitly" ) {

      double styp = 0.0;
      std::array< double, 2 > fd = {{ 1., 0. }};
      std::array< double, 2 > fc = {{ 0.5, 0.25 }};
      std::array< double, 2 > erav = {{ 2.107044e+2, 1.576284e+1 }};
    
      ContinuousSpectrum continuous =
        { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
          { 6.133200e-7, 6.133300e-7, 6.02040e-17 } };

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        DecaySpectrum chunk( styp, fc, erav, std::move( continuous ) );
        verifyChunkWithLCONOne( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithLCONOne();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      
      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkWithLCONOne( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DecaySpectrum with LCON=2" ) {

    WHEN( "the data is given explicitly" ) {

      double styp = 0.0;
      std::array< double, 2 > fd = {{ 1., 0. }};
      std::array< double, 2 > fc = {{ 0.5, 0.25 }};
      std::array< double, 2 > erav = {{ 2.107044e+2, 1.576284e+1 }};

      std::vector< DiscreteSpectrum > discrete = 
        { { 3., {{ 4.863000e+4, 5.000000e+1 }},
            {{ 1.420112e-6, 2.85306e-10 }}, 0.0,
            {{ 0.0, 0.0 }}, {{ 7.010000e+5, 1.106180e-2 }}, {{ 0.0, 0.0 }},
            {{ 3.315735e+5, 5.608008e+3 }} },
          { 4., {{ 4.935000e+4, 2.000000e+1 }},
            {{ 1.335690e-3, 5.409179e-5 }}, 0.0,
            {{ 0.0, 0.0 }}, {{ 8.209999e-1, 0.000000e+0 }}, {{ 0.0, 0.0 }},
            {{ 6.160000e-1, 8.999999e-3 }} } };
    
      ContinuousSpectrum continuous =
        { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
          { 6.133200e-7, 6.133300e-7, 6.02040e-17 } };

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        DecaySpectrum chunk( styp, fd, fc, erav, std::move( discrete ),
                             std::move( continuous ) );
        verifyChunkWithLCONTwo( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithLCONTwo();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;
      
      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkWithLCONTwo( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of DecaySpectrum with discrete spectra only "
         "(LCON=0)" ) {

    std::string string = chunkWithLCONZero();
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

    std::string string = chunkWithLCONOne();
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

    std::string string = chunkWithLCONTwo();
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

  GIVEN( "invalid data for a DecaySpectrum" ) {

    WHEN( "an empty vector is used for the discrete spectra for LCON=0" ) {

      double styp = 0.0;
      std::array< double, 2 > fd = {{ 1., 0. }};
      std::array< double, 2 > fc = {{ 0.5, 0.25 }};
      std::array< double, 2 > erav = {{ 2.107044e+2, 1.576284e+1 }};

      std::vector< DiscreteSpectrum > discrete = {};

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( DecaySpectrum( styp, fd, erav,
                                       std::move( discrete ) ) );
      } // THEN
    } // WHEN

    WHEN( "an empty vector is used for the discrete spectra for LCON=2" ) {

      double styp = 0.0;
      std::array< double, 2 > fd = {{ 1., 0. }};
      std::array< double, 2 > fc = {{ 0.5, 0.25 }};
      std::array< double, 2 > erav = {{ 2.107044e+2, 1.576284e+1 }};

      std::vector< DiscreteSpectrum > discrete = {};
    
      ContinuousSpectrum continuous =
        { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
          { 6.133200e-7, 6.133300e-7, 6.02040e-17 } };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( DecaySpectrum( styp, fd, fc, erav,
                                       std::move( discrete ),
                                       std::move( continuous ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string is used with an unsupported LCOV" ) {

      std::string string = chunkWithUnsupportedLCOV();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( DecaySpectrum( begin, end, lineNumber, 3580, 8, 457 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunkWithLCONZero() {
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

void verifyChunkWithLCONZero( const DecaySpectrum& chunk ) {

  REQUIRE( 0. == chunk.STYP() );
  REQUIRE( 0. == chunk.radiationType() );

  REQUIRE( 0 == chunk.LCON() );
  REQUIRE( 0 == chunk.continuumSpectrumFlag() );
  REQUIRE( 0 == chunk.LCOV() );
  REQUIRE( 0 == chunk.covarianceFlag() );
  REQUIRE( 2 == chunk.NER() );
  REQUIRE( 2 == chunk.numberDiscreteSpectra() );

  REQUIRE( 1. == Approx( chunk.FD()[0] ) );
  REQUIRE( 0. == Approx( chunk.FD()[1] ) );
  REQUIRE( 1. == Approx( chunk.discreteNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( chunk.discreteNormalisationFactor()[1] ) );
  REQUIRE( 0. == Approx( chunk.FC()[0] ) );
  REQUIRE( 0. == Approx( chunk.FC()[1] ) );
  REQUIRE( 0. == Approx( chunk.continuousNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( chunk.continuousNormalisationFactor()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( chunk.ERAV()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( chunk.ERAV()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( chunk.averageDecayEnergy()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( chunk.averageDecayEnergy()[1] ) );

  REQUIRE( std::nullopt == chunk.continuousSpectrum() );

  auto discrete = chunk.discreteSpectra();
  REQUIRE( 3. == discrete[0].RTYP() );
  REQUIRE( 3. == discrete[0].decayChain() );
  REQUIRE( 12 == discrete[0].NT() );
  REQUIRE( 4.863000e+4 == Approx( discrete[0].ER()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( discrete[0].ER()[1] ) );
  REQUIRE( 4.863000e+4 == Approx( discrete[0].discreteEnergy()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( discrete[0].discreteEnergy()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( discrete[0].RI()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( discrete[0].RI()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( discrete[0].relativeIntensity()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( discrete[0].relativeIntensity()[1] ) );
  REQUIRE( 0. == discrete[0].TYPE() );
  REQUIRE( 0. == discrete[0].type() );
  REQUIRE( 0.0 == Approx( discrete[0].RIS()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RIS()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( discrete[0].RICC()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( discrete[0].RICC()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( discrete[0].totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( discrete[0].totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RICK()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RICK()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( discrete[0].RICL()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( discrete[0].RICL()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( discrete[0].internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( discrete[0].internalConversionCoefficientLShell()[1] ) );
  REQUIRE( 4. == discrete[1].RTYP() );
  REQUIRE( 4. == discrete[1].decayChain() );
  REQUIRE( 12 == discrete[1].NT() );
  REQUIRE( 4.935000e+4 == Approx( discrete[1].ER()[0] ) );
  REQUIRE( 2.000000e+1 == Approx( discrete[1].ER()[1] ) );
  REQUIRE( 4.935000e+4 == Approx( discrete[1].discreteEnergy()[0] ) );
  REQUIRE( 2.000000e+1 == Approx( discrete[1].discreteEnergy()[1] ) );
  REQUIRE( 1.335690e-3 == Approx( discrete[1].RI()[0] ) );
  REQUIRE( 5.409179e-5 == Approx( discrete[1].RI()[1] ) );
  REQUIRE( 1.335690e-3 == Approx( discrete[1].relativeIntensity()[0] ) );
  REQUIRE( 5.409179e-5 == Approx( discrete[1].relativeIntensity()[1] ) );
  REQUIRE( 0. == discrete[1].TYPE() );
  REQUIRE( 0. == discrete[1].type() );
  REQUIRE( 0.0 == Approx( discrete[1].RIS()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RIS()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[1] ) );
  REQUIRE( 8.209999e-1 == Approx( discrete[1].RICC()[0] ) );
  REQUIRE( 0.000000e+0 == Approx( discrete[1].RICC()[1] ) );
  REQUIRE( 8.209999e-1 == Approx( discrete[1].totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 0.000000e+0 == Approx( discrete[1].totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RICK()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RICK()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 6.160000e-1 == Approx( discrete[1].RICL()[0] ) );
  REQUIRE( 8.999999e-3 == Approx( discrete[1].RICL()[1] ) );
  REQUIRE( 6.160000e-1 == Approx( discrete[1].internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 8.999999e-3 == Approx( discrete[1].internalConversionCoefficientLShell()[1] ) );

  REQUIRE( 8 == chunk.NC() );
}

std::string chunkWithLCONOne() {
  return
    " 0.000000+0 0.000000+0          1          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 2.107044+2 1.576284+1 5.000000-1 2.500000-13580 8457     \n"
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}

void verifyChunkWithLCONOne( const DecaySpectrum& chunk ) {

  REQUIRE( 0. == chunk.STYP() );
  REQUIRE( 0. == chunk.radiationType() );

  REQUIRE( 1 == chunk.LCON() );
  REQUIRE( 1 == chunk.continuumSpectrumFlag() );
  REQUIRE( 0 == chunk.LCOV() );
  REQUIRE( 0 == chunk.covarianceFlag() );
  REQUIRE( 0 == chunk.NER() );
  REQUIRE( 0 == chunk.numberDiscreteSpectra() );

  REQUIRE( 0. == Approx( chunk.FD()[0] ) );
  REQUIRE( 0. == Approx( chunk.FD()[1] ) );
  REQUIRE( 0. == Approx( chunk.discreteNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( chunk.discreteNormalisationFactor()[1] ) );
  REQUIRE( 0.5 == Approx( chunk.FC()[0] ) );
  REQUIRE( 0.25 == Approx( chunk.FC()[1] ) );
  REQUIRE( 0.5 == Approx( chunk.continuousNormalisationFactor()[0] ) );
  REQUIRE( 0.25 == Approx( chunk.continuousNormalisationFactor()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( chunk.ERAV()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( chunk.ERAV()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( chunk.averageDecayEnergy()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( chunk.averageDecayEnergy()[1] ) );

  REQUIRE( std::nullopt != chunk.continuousSpectrum() );

  ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
  REQUIRE( 4. == continuous.RTYP() );
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

std::string chunkWithLCONTwo() {
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

void verifyChunkWithLCONTwo( const DecaySpectrum& chunk ) {

  REQUIRE( 0. == chunk.STYP() );
  REQUIRE( 0. == chunk.radiationType() );

  REQUIRE( 2 == chunk.LCON() );
  REQUIRE( 2 == chunk.continuumSpectrumFlag() );
  REQUIRE( 0 == chunk.LCOV() );
  REQUIRE( 0 == chunk.covarianceFlag() );
  REQUIRE( 2 == chunk.NER() );
  REQUIRE( 2 == chunk.numberDiscreteSpectra() );

  REQUIRE( 1. == Approx( chunk.FD()[0] ) );
  REQUIRE( 0. == Approx( chunk.FD()[1] ) );
  REQUIRE( 1. == Approx( chunk.discreteNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( chunk.discreteNormalisationFactor()[1] ) );
  REQUIRE( 0.5 == Approx( chunk.FC()[0] ) );
  REQUIRE( 0.25 == Approx( chunk.FC()[1] ) );
  REQUIRE( 0.5 == Approx( chunk.continuousNormalisationFactor()[0] ) );
  REQUIRE( 0.25 == Approx( chunk.continuousNormalisationFactor()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( chunk.ERAV()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( chunk.ERAV()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( chunk.averageDecayEnergy()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( chunk.averageDecayEnergy()[1] ) );

  REQUIRE( std::nullopt != chunk.continuousSpectrum() );

  auto discrete = chunk.discreteSpectra();
  REQUIRE( 3. == discrete[0].RTYP() );
  REQUIRE( 3. == discrete[0].decayChain() );
  REQUIRE( 12 == discrete[0].NT() );
  REQUIRE( 4.863000e+4 == Approx( discrete[0].ER()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( discrete[0].ER()[1] ) );
  REQUIRE( 4.863000e+4 == Approx( discrete[0].discreteEnergy()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( discrete[0].discreteEnergy()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( discrete[0].RI()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( discrete[0].RI()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( discrete[0].relativeIntensity()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( discrete[0].relativeIntensity()[1] ) );
  REQUIRE( 0. == discrete[0].TYPE() );
  REQUIRE( 0. == discrete[0].type() );
  REQUIRE( 0.0 == Approx( discrete[0].RIS()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RIS()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( discrete[0].RICC()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( discrete[0].RICC()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( discrete[0].totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( discrete[0].totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RICK()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RICK()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( discrete[0].RICL()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( discrete[0].RICL()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( discrete[0].internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( discrete[0].internalConversionCoefficientLShell()[1] ) );
  REQUIRE( 4. == discrete[1].RTYP() );
  REQUIRE( 4. == discrete[1].decayChain() );
  REQUIRE( 12 == discrete[1].NT() );
  REQUIRE( 4.935000e+4 == Approx( discrete[1].ER()[0] ) );
  REQUIRE( 2.000000e+1 == Approx( discrete[1].ER()[1] ) );
  REQUIRE( 4.935000e+4 == Approx( discrete[1].discreteEnergy()[0] ) );
  REQUIRE( 2.000000e+1 == Approx( discrete[1].discreteEnergy()[1] ) );
  REQUIRE( 1.335690e-3 == Approx( discrete[1].RI()[0] ) );
  REQUIRE( 5.409179e-5 == Approx( discrete[1].RI()[1] ) );
  REQUIRE( 1.335690e-3 == Approx( discrete[1].relativeIntensity()[0] ) );
  REQUIRE( 5.409179e-5 == Approx( discrete[1].relativeIntensity()[1] ) );
  REQUIRE( 0. == discrete[1].TYPE() );
  REQUIRE( 0. == discrete[1].type() );
  REQUIRE( 0.0 == Approx( discrete[1].RIS()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RIS()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[1] ) );
  REQUIRE( 8.209999e-1 == Approx( discrete[1].RICC()[0] ) );
  REQUIRE( 0.000000e+0 == Approx( discrete[1].RICC()[1] ) );
  REQUIRE( 8.209999e-1 == Approx( discrete[1].totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 0.000000e+0 == Approx( discrete[1].totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RICK()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RICK()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 6.160000e-1 == Approx( discrete[1].RICL()[0] ) );
  REQUIRE( 8.999999e-3 == Approx( discrete[1].RICL()[1] ) );
  REQUIRE( 6.160000e-1 == Approx( discrete[1].internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 8.999999e-3 == Approx( discrete[1].internalConversionCoefficientLShell()[1] ) );

  ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
  REQUIRE( 4. == continuous.RTYP() );
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

std::string chunkWithUnsupportedLCOV() {
  return
    " 0.000000+0 0.000000+0          0          1          6          23580 8457     \n"
    " 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n"
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n"
    " 4.935000+4 2.000000+1          0          0         12          03580 8457     \n"
    " 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n"
    " 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n";
}

