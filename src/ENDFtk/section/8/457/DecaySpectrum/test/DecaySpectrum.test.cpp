#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/8/457.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
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

    std::string string = chunkWithLCONZero();

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

      DecaySpectrum chunk( styp, fd, erav, std::move( discrete ) );

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        verifyChunkWithLCONZero( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        verifyChunkWithLCONZero( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DecaySpectrum with LCON=1" ) {

    std::string string = chunkWithLCONOne();

    WHEN( "the data is given explicitly" ) {

      double styp = 0.0;
      std::array< double, 2 > fd = {{ 1., 0. }};
      std::array< double, 2 > fc = {{ 0.5, 0.25 }};
      std::array< double, 2 > erav = {{ 2.107044e+2, 1.576284e+1 }};

      ContinuousSpectrum continuous =
        { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
          { 6.133200e-7, 6.133300e-7, 6.02040e-17 } };

      DecaySpectrum chunk( styp, fc, erav, std::move( continuous ) );

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        verifyChunkWithLCONOne( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        verifyChunkWithLCONOne( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DecaySpectrum with LCON=2" ) {

    std::string string = chunkWithLCONTwo();

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

      DecaySpectrum chunk( styp, fd, fc, erav, std::move( discrete ),
                           std::move( continuous ) );

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        verifyChunkWithLCONTwo( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DecaySpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DecaySpectrum can be constructed and members can be tested" ) {

        verifyChunkWithLCONTwo( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DecaySpectrum" ) {

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

        CHECK_THROWS( DecaySpectrum( styp, fd, fc, erav,
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

        CHECK_THROWS( DecaySpectrum( begin, end, lineNumber, 3580, 8, 457 ) );
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

  CHECK( 0. == chunk.STYP() );
  CHECK( 0. == chunk.radiationType() );

  CHECK( 0 == chunk.LCON() );
  CHECK( 0 == chunk.spectralTypeFlag() );
  CHECK( 0 == chunk.LCOV() );
  CHECK( 0 == chunk.covarianceFlag() );
  CHECK( 2 == chunk.NER() );
  CHECK( 2 == chunk.numberDiscreteSpectra() );

  CHECK( 1. == Approx( chunk.FD()[0] ) );
  CHECK( 0. == Approx( chunk.FD()[1] ) );
  CHECK( 1. == Approx( chunk.discreteNormalisationFactor()[0] ) );
  CHECK( 0. == Approx( chunk.discreteNormalisationFactor()[1] ) );
  CHECK( 0. == Approx( chunk.FC()[0] ) );
  CHECK( 0. == Approx( chunk.FC()[1] ) );
  CHECK( 0. == Approx( chunk.continuousNormalisationFactor()[0] ) );
  CHECK( 0. == Approx( chunk.continuousNormalisationFactor()[1] ) );
  CHECK( 2.107044e+2 == Approx( chunk.ERAV()[0] ) );
  CHECK( 1.576284e+1 == Approx( chunk.ERAV()[1] ) );
  CHECK( 2.107044e+2 == Approx( chunk.averageDecayEnergy()[0] ) );
  CHECK( 1.576284e+1 == Approx( chunk.averageDecayEnergy()[1] ) );

  CHECK( std::nullopt == chunk.continuousSpectrum() );

  auto discrete = chunk.discreteSpectra();
  CHECK( 3. == discrete[0].RTYP() );
  CHECK( 3. == discrete[0].decayChain() );
  CHECK( 12 == discrete[0].NT() );
  CHECK( 4.863000e+4 == Approx( discrete[0].ER()[0] ) );
  CHECK( 5.000000e+1 == Approx( discrete[0].ER()[1] ) );
  CHECK( 4.863000e+4 == Approx( discrete[0].discreteEnergy()[0] ) );
  CHECK( 5.000000e+1 == Approx( discrete[0].discreteEnergy()[1] ) );
  CHECK( 1.420112e-6 == Approx( discrete[0].RI()[0] ) );
  CHECK( 2.85306e-10 == Approx( discrete[0].RI()[1] ) );
  CHECK( 1.420112e-6 == Approx( discrete[0].relativeIntensity()[0] ) );
  CHECK( 2.85306e-10 == Approx( discrete[0].relativeIntensity()[1] ) );
  CHECK( 0. == discrete[0].TYPE() );
  CHECK( 0. == discrete[0].type() );
  CHECK( 0.0 == Approx( discrete[0].RIS()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].RIS()[1] ) );
  CHECK( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[1] ) );
  CHECK( 7.010000e+5 == Approx( discrete[0].RICC()[0] ) );
  CHECK( 1.106180e-2 == Approx( discrete[0].RICC()[1] ) );
  CHECK( 7.010000e+5 == Approx( discrete[0].totalInternalConversionCoefficient()[0] ) );
  CHECK( 1.106180e-2 == Approx( discrete[0].totalInternalConversionCoefficient()[1] ) );
  CHECK( 0.0 == Approx( discrete[0].RICK()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].RICK()[1] ) );
  CHECK( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[1] ) );
  CHECK( 3.315735e+5 == Approx( discrete[0].RICL()[0] ) );
  CHECK( 5.608008e+3 == Approx( discrete[0].RICL()[1] ) );
  CHECK( 3.315735e+5 == Approx( discrete[0].internalConversionCoefficientLShell()[0] ) );
  CHECK( 5.608008e+3 == Approx( discrete[0].internalConversionCoefficientLShell()[1] ) );
  CHECK( 4. == discrete[1].RTYP() );
  CHECK( 4. == discrete[1].decayChain() );
  CHECK( 12 == discrete[1].NT() );
  CHECK( 4.935000e+4 == Approx( discrete[1].ER()[0] ) );
  CHECK( 2.000000e+1 == Approx( discrete[1].ER()[1] ) );
  CHECK( 4.935000e+4 == Approx( discrete[1].discreteEnergy()[0] ) );
  CHECK( 2.000000e+1 == Approx( discrete[1].discreteEnergy()[1] ) );
  CHECK( 1.335690e-3 == Approx( discrete[1].RI()[0] ) );
  CHECK( 5.409179e-5 == Approx( discrete[1].RI()[1] ) );
  CHECK( 1.335690e-3 == Approx( discrete[1].relativeIntensity()[0] ) );
  CHECK( 5.409179e-5 == Approx( discrete[1].relativeIntensity()[1] ) );
  CHECK( 0. == discrete[1].TYPE() );
  CHECK( 0. == discrete[1].type() );
  CHECK( 0.0 == Approx( discrete[1].RIS()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].RIS()[1] ) );
  CHECK( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[1] ) );
  CHECK( 8.209999e-1 == Approx( discrete[1].RICC()[0] ) );
  CHECK( 0.000000e+0 == Approx( discrete[1].RICC()[1] ) );
  CHECK( 8.209999e-1 == Approx( discrete[1].totalInternalConversionCoefficient()[0] ) );
  CHECK( 0.000000e+0 == Approx( discrete[1].totalInternalConversionCoefficient()[1] ) );
  CHECK( 0.0 == Approx( discrete[1].RICK()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].RICK()[1] ) );
  CHECK( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[1] ) );
  CHECK( 6.160000e-1 == Approx( discrete[1].RICL()[0] ) );
  CHECK( 8.999999e-3 == Approx( discrete[1].RICL()[1] ) );
  CHECK( 6.160000e-1 == Approx( discrete[1].internalConversionCoefficientLShell()[0] ) );
  CHECK( 8.999999e-3 == Approx( discrete[1].internalConversionCoefficientLShell()[1] ) );

  CHECK( 8 == chunk.NC() );
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

  CHECK( 0. == chunk.STYP() );
  CHECK( 0. == chunk.radiationType() );

  CHECK( 1 == chunk.LCON() );
  CHECK( 1 == chunk.spectralTypeFlag() );
  CHECK( 0 == chunk.LCOV() );
  CHECK( 0 == chunk.covarianceFlag() );
  CHECK( 0 == chunk.NER() );
  CHECK( 0 == chunk.numberDiscreteSpectra() );

  CHECK( 0. == Approx( chunk.FD()[0] ) );
  CHECK( 0. == Approx( chunk.FD()[1] ) );
  CHECK( 0. == Approx( chunk.discreteNormalisationFactor()[0] ) );
  CHECK( 0. == Approx( chunk.discreteNormalisationFactor()[1] ) );
  CHECK( 0.5 == Approx( chunk.FC()[0] ) );
  CHECK( 0.25 == Approx( chunk.FC()[1] ) );
  CHECK( 0.5 == Approx( chunk.continuousNormalisationFactor()[0] ) );
  CHECK( 0.25 == Approx( chunk.continuousNormalisationFactor()[1] ) );
  CHECK( 2.107044e+2 == Approx( chunk.ERAV()[0] ) );
  CHECK( 1.576284e+1 == Approx( chunk.ERAV()[1] ) );
  CHECK( 2.107044e+2 == Approx( chunk.averageDecayEnergy()[0] ) );
  CHECK( 1.576284e+1 == Approx( chunk.averageDecayEnergy()[1] ) );

  CHECK( std::nullopt != chunk.continuousSpectrum() );

  ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
  CHECK( 4. == continuous.RTYP() );
  CHECK( 4. == continuous.decayChain() );
  CHECK( 3 == continuous.NP() );
  CHECK( 1 == continuous.NR() );
  CHECK( 1 == continuous.interpolants().size() );
  CHECK( 1 == continuous.boundaries().size() );
  CHECK( 1 == continuous.interpolants()[0] );
  CHECK( 3 == continuous.boundaries()[0] );
  CHECK( 3 == continuous.energies().size() );
  CHECK( 3 == continuous.spectralValues().size() );
  CHECK( 0.0 == Approx( continuous.energies()[0] ) );
  CHECK( 5e+5 == Approx( continuous.energies()[1] ) );
  CHECK( 7.3e+6 == Approx( continuous.energies()[2] ) );
  CHECK( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
  CHECK( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
  CHECK( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

  CHECK( 5 == chunk.NC() );
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

  CHECK( 0. == chunk.STYP() );
  CHECK( 0. == chunk.radiationType() );

  CHECK( 2 == chunk.LCON() );
  CHECK( 2 == chunk.spectralTypeFlag() );
  CHECK( 0 == chunk.LCOV() );
  CHECK( 0 == chunk.covarianceFlag() );
  CHECK( 2 == chunk.NER() );
  CHECK( 2 == chunk.numberDiscreteSpectra() );

  CHECK( 1. == Approx( chunk.FD()[0] ) );
  CHECK( 0. == Approx( chunk.FD()[1] ) );
  CHECK( 1. == Approx( chunk.discreteNormalisationFactor()[0] ) );
  CHECK( 0. == Approx( chunk.discreteNormalisationFactor()[1] ) );
  CHECK( 0.5 == Approx( chunk.FC()[0] ) );
  CHECK( 0.25 == Approx( chunk.FC()[1] ) );
  CHECK( 0.5 == Approx( chunk.continuousNormalisationFactor()[0] ) );
  CHECK( 0.25 == Approx( chunk.continuousNormalisationFactor()[1] ) );
  CHECK( 2.107044e+2 == Approx( chunk.ERAV()[0] ) );
  CHECK( 1.576284e+1 == Approx( chunk.ERAV()[1] ) );
  CHECK( 2.107044e+2 == Approx( chunk.averageDecayEnergy()[0] ) );
  CHECK( 1.576284e+1 == Approx( chunk.averageDecayEnergy()[1] ) );

  CHECK( std::nullopt != chunk.continuousSpectrum() );

  auto discrete = chunk.discreteSpectra();
  CHECK( 3. == discrete[0].RTYP() );
  CHECK( 3. == discrete[0].decayChain() );
  CHECK( 12 == discrete[0].NT() );
  CHECK( 4.863000e+4 == Approx( discrete[0].ER()[0] ) );
  CHECK( 5.000000e+1 == Approx( discrete[0].ER()[1] ) );
  CHECK( 4.863000e+4 == Approx( discrete[0].discreteEnergy()[0] ) );
  CHECK( 5.000000e+1 == Approx( discrete[0].discreteEnergy()[1] ) );
  CHECK( 1.420112e-6 == Approx( discrete[0].RI()[0] ) );
  CHECK( 2.85306e-10 == Approx( discrete[0].RI()[1] ) );
  CHECK( 1.420112e-6 == Approx( discrete[0].relativeIntensity()[0] ) );
  CHECK( 2.85306e-10 == Approx( discrete[0].relativeIntensity()[1] ) );
  CHECK( 0. == discrete[0].TYPE() );
  CHECK( 0. == discrete[0].type() );
  CHECK( 0.0 == Approx( discrete[0].RIS()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].RIS()[1] ) );
  CHECK( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[1] ) );
  CHECK( 7.010000e+5 == Approx( discrete[0].RICC()[0] ) );
  CHECK( 1.106180e-2 == Approx( discrete[0].RICC()[1] ) );
  CHECK( 7.010000e+5 == Approx( discrete[0].totalInternalConversionCoefficient()[0] ) );
  CHECK( 1.106180e-2 == Approx( discrete[0].totalInternalConversionCoefficient()[1] ) );
  CHECK( 0.0 == Approx( discrete[0].RICK()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].RICK()[1] ) );
  CHECK( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[0] ) );
  CHECK( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[1] ) );
  CHECK( 3.315735e+5 == Approx( discrete[0].RICL()[0] ) );
  CHECK( 5.608008e+3 == Approx( discrete[0].RICL()[1] ) );
  CHECK( 3.315735e+5 == Approx( discrete[0].internalConversionCoefficientLShell()[0] ) );
  CHECK( 5.608008e+3 == Approx( discrete[0].internalConversionCoefficientLShell()[1] ) );
  CHECK( 4. == discrete[1].RTYP() );
  CHECK( 4. == discrete[1].decayChain() );
  CHECK( 12 == discrete[1].NT() );
  CHECK( 4.935000e+4 == Approx( discrete[1].ER()[0] ) );
  CHECK( 2.000000e+1 == Approx( discrete[1].ER()[1] ) );
  CHECK( 4.935000e+4 == Approx( discrete[1].discreteEnergy()[0] ) );
  CHECK( 2.000000e+1 == Approx( discrete[1].discreteEnergy()[1] ) );
  CHECK( 1.335690e-3 == Approx( discrete[1].RI()[0] ) );
  CHECK( 5.409179e-5 == Approx( discrete[1].RI()[1] ) );
  CHECK( 1.335690e-3 == Approx( discrete[1].relativeIntensity()[0] ) );
  CHECK( 5.409179e-5 == Approx( discrete[1].relativeIntensity()[1] ) );
  CHECK( 0. == discrete[1].TYPE() );
  CHECK( 0. == discrete[1].type() );
  CHECK( 0.0 == Approx( discrete[1].RIS()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].RIS()[1] ) );
  CHECK( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[1] ) );
  CHECK( 8.209999e-1 == Approx( discrete[1].RICC()[0] ) );
  CHECK( 0.000000e+0 == Approx( discrete[1].RICC()[1] ) );
  CHECK( 8.209999e-1 == Approx( discrete[1].totalInternalConversionCoefficient()[0] ) );
  CHECK( 0.000000e+0 == Approx( discrete[1].totalInternalConversionCoefficient()[1] ) );
  CHECK( 0.0 == Approx( discrete[1].RICK()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].RICK()[1] ) );
  CHECK( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[0] ) );
  CHECK( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[1] ) );
  CHECK( 6.160000e-1 == Approx( discrete[1].RICL()[0] ) );
  CHECK( 8.999999e-3 == Approx( discrete[1].RICL()[1] ) );
  CHECK( 6.160000e-1 == Approx( discrete[1].internalConversionCoefficientLShell()[0] ) );
  CHECK( 8.999999e-3 == Approx( discrete[1].internalConversionCoefficientLShell()[1] ) );

  ContinuousSpectrum continuous = *( chunk.continuousSpectrum() );
  CHECK( 4. == continuous.RTYP() );
  CHECK( 4. == continuous.decayChain() );
  CHECK( 3 == continuous.NP() );
  CHECK( 1 == continuous.NR() );
  CHECK( 1 == continuous.interpolants().size() );
  CHECK( 1 == continuous.boundaries().size() );
  CHECK( 1 == continuous.interpolants()[0] );
  CHECK( 3 == continuous.boundaries()[0] );
  CHECK( 3 == continuous.energies().size() );
  CHECK( 3 == continuous.spectralValues().size() );
  CHECK( 0.0 == Approx( continuous.energies()[0] ) );
  CHECK( 5e+5 == Approx( continuous.energies()[1] ) );
  CHECK( 7.3e+6 == Approx( continuous.energies()[2] ) );
  CHECK( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
  CHECK( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
  CHECK( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

  CHECK( 11 == chunk.NC() );
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
