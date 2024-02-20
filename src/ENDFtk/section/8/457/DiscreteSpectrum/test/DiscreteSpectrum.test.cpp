// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/8/457.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DiscreteSpectrum = section::Type< 8, 457 >::DiscreteSpectrum;

std::string chunkWithSTYPNotZeroOrTwo();
void verifyChunkWithSTYPNotZeroOrTwo( const DiscreteSpectrum& );
std::string chunkWithSTYPTwo();
void verifyChunkWithSTYPTwo( const DiscreteSpectrum& );
std::string chunkWithSTYPZero();
void verifyChunkWithSTYPZero( const DiscreteSpectrum& );
std::string chunkWithWrongNT();

SCENARIO( "DiscreteSpectrum" ) {

  GIVEN( "valid data for a DiscreteSpectrum with STYP not equal to 0 or 2" ) {

    std::string string = chunkWithSTYPNotZeroOrTwo();

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > discreteEnergy = {{ 4.863000e+4, 5.000000e+1 }};
      double decayChain = 3.;
      double type = 0.;
      std::array< double, 2 > relativeIntensity = {{ 1.420112e-6,
                                                     2.85306e-10 }};

      DiscreteSpectrum chunk( decayChain, discreteEnergy,
                              relativeIntensity, type );

      THEN( "a DiscreteSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunkWithSTYPNotZeroOrTwo( chunk );
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

      DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        verifyChunkWithSTYPNotZeroOrTwo( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DiscreteSpectrum with STYP equal to 2" ) {

    std::string string = chunkWithSTYPTwo();

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > discreteEnergy = {{ 4.863000e+4, 5.000000e+1 }};
      double decayChain = 3.;
      double type = 0.;
      std::array< double, 2 > relativeIntensity = {{ 1.420112e-6,
                                                     2.85306e-10 }};
      std::array< double, 2 > ris = {{ 1.0, 2.0 }};

      DiscreteSpectrum chunk( decayChain, discreteEnergy,
                              relativeIntensity, type, ris );

      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        verifyChunkWithSTYPTwo( chunk );
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

      DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        verifyChunkWithSTYPTwo( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DiscreteSpectrum with STYP equal to 0" ) {

    std::string string = chunkWithSTYPZero();

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > discreteEnergy = {{ 4.863000e+4, 5.000000e+1 }};
      double decayChain = 3.;
      double type = 0.;
      std::array< double, 2 > relativeIntensity = {{ 1.420112e-6,
                                                     2.85306e-10 }};
      std::array< double, 2 > ris = {{ 1.0, 2.0 }};
      std::array< double, 2 > ricc = {{ 7.010000e+5, 1.106180e-2 }};
      std::array< double, 2 > rick = {{ 1.378999e-1, 2.000000e-3 }};
      std::array< double, 2 > ricl = {{ 3.315735e+5, 5.608008e+3 }};

      DiscreteSpectrum chunk( decayChain, discreteEnergy,
                              relativeIntensity, type, ris,
                              ricc, rick, ricl );

      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        verifyChunkWithSTYPZero( chunk );
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

      DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        verifyChunkWithSTYPZero( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DiscreteSpectrum" ) {

    WHEN( "a string with the wrong NT value is used" ) {

      std::string string = chunkWithWrongNT();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DiscreteSpectrum( begin, end, lineNumber, 3580, 8, 457 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithSTYPNotZeroOrTwo() {
  return
    " 4.863000+4 5.000000+1          0          0          4          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10                      3580 8457     \n";
}

void verifyChunkWithSTYPNotZeroOrTwo( const DiscreteSpectrum& chunk )
{
  CHECK( 3. == chunk.RTYP() );
  CHECK( 3. == chunk.decayChain() );
  CHECK( 4 == chunk.NT() );
  CHECK_THAT( 4.863000e+4, WithinRel( chunk.ER()[0] ) );
  CHECK_THAT( 5.000000e+1, WithinRel( chunk.ER()[1] ) );
  CHECK_THAT( 4.863000e+4, WithinRel( chunk.discreteEnergy()[0] ) );
  CHECK_THAT( 5.000000e+1, WithinRel( chunk.discreteEnergy()[1] ) );
  CHECK_THAT( 1.420112e-6, WithinRel( chunk.RI()[0] ) );
  CHECK_THAT( 2.85306e-10, WithinRel( chunk.RI()[1] ) );
  CHECK_THAT( 1.420112e-6, WithinRel( chunk.relativeIntensity()[0] ) );
  CHECK_THAT( 2.85306e-10, WithinRel( chunk.relativeIntensity()[1] ) );
  CHECK( 0. == chunk.TYPE() );
  CHECK( 0. == chunk.type() );
  CHECK_THAT( 0.0, WithinRel( chunk.RIS()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RIS()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalPairFormationCoefficient()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalPairFormationCoefficient()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICC()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICC()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.totalInternalConversionCoefficient()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.totalInternalConversionCoefficient()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICK()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICK()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientKShell()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientKShell()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICL()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICL()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientLShell()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientLShell()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string chunkWithSTYPTwo() {
  return
    " 4.863000+4 5.000000+1          0          0          6          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n";
}

void verifyChunkWithSTYPTwo( const DiscreteSpectrum& chunk )
{
  CHECK( 3. == chunk.RTYP() );
  CHECK( 3. == chunk.decayChain() );
  CHECK( 6 == chunk.NT() );
  CHECK_THAT( 4.863000e+4, WithinRel( chunk.discreteEnergy()[0] ) );
  CHECK_THAT( 5.000000e+1, WithinRel( chunk.discreteEnergy()[1] ) );
  CHECK_THAT( 4.863000e+4, WithinRel( chunk.ER()[0] ) );
  CHECK_THAT( 5.000000e+1, WithinRel( chunk.ER()[1] ) );
  CHECK_THAT( 1.420112e-6, WithinRel( chunk.relativeIntensity()[0] ) );
  CHECK_THAT( 2.85306e-10, WithinRel( chunk.relativeIntensity()[1] ) );
  CHECK_THAT( 1.420112e-6, WithinRel( chunk.RI()[0] ) );
  CHECK_THAT( 2.85306e-10, WithinRel( chunk.RI()[1] ) );
  CHECK( 0. == chunk.TYPE() );
  CHECK( 0. == chunk.type() );
  CHECK_THAT( 1.0, WithinRel( chunk.RIS()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.RIS()[1] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.internalPairFormationCoefficient()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.internalPairFormationCoefficient()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICC()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICC()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.totalInternalConversionCoefficient()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.totalInternalConversionCoefficient()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICK()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICK()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientKShell()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientKShell()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICL()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.RICL()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientLShell()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.internalConversionCoefficientLShell()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string chunkWithSTYPZero() {
  return
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 1.378999-1 2.000000-3 3.315735+5 5.608008+33580 8457     \n";
}

void verifyChunkWithSTYPZero( const DiscreteSpectrum& chunk )
{
  CHECK( 3. == chunk.RTYP() );
  CHECK( 3. == chunk.decayChain() );
  CHECK( 12 == chunk.NT() );
  CHECK_THAT( 4.863000e+4, WithinRel( chunk.ER()[0] ) );
  CHECK_THAT( 5.000000e+1, WithinRel( chunk.ER()[1] ) );
  CHECK_THAT( 4.863000e+4, WithinRel( chunk.discreteEnergy()[0] ) );
  CHECK_THAT( 5.000000e+1, WithinRel( chunk.discreteEnergy()[1] ) );
  CHECK_THAT( 1.420112e-6, WithinRel( chunk.RI()[0] ) );
  CHECK_THAT( 2.85306e-10, WithinRel( chunk.RI()[1] ) );
  CHECK_THAT( 1.420112e-6, WithinRel( chunk.relativeIntensity()[0] ) );
  CHECK_THAT( 2.85306e-10, WithinRel( chunk.relativeIntensity()[1] ) );
  CHECK( 0. == chunk.type() );
  CHECK_THAT( 1.0, WithinRel( chunk.RIS()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.RIS()[1] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.internalPairFormationCoefficient()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.internalPairFormationCoefficient()[1] ) );
  CHECK_THAT( 7.010000e+5, WithinRel( chunk.RICC()[0] ) );
  CHECK_THAT( 1.106180e-2, WithinRel( chunk.RICC()[1] ) );
  CHECK_THAT( 7.010000e+5, WithinRel( chunk.totalInternalConversionCoefficient()[0] ) );
  CHECK_THAT( 1.106180e-2, WithinRel( chunk.totalInternalConversionCoefficient()[1] ) );
  CHECK_THAT( 1.378999e-1, WithinRel( chunk.RICK()[0] ) );
  CHECK_THAT( 2.000000e-3, WithinRel( chunk.RICK()[1] ) );
  CHECK_THAT( 1.378999e-1, WithinRel( chunk.internalConversionCoefficientKShell()[0] ) );
  CHECK_THAT( 2.000000e-3, WithinRel( chunk.internalConversionCoefficientKShell()[1] ) );
  CHECK_THAT( 3.315735e+5, WithinRel( chunk.RICL()[0] ) );
  CHECK_THAT( 5.608008e+3, WithinRel( chunk.RICL()[1] ) );
  CHECK_THAT( 3.315735e+5, WithinRel( chunk.internalConversionCoefficientLShell()[0] ) );
  CHECK_THAT( 5.608008e+3, WithinRel( chunk.internalConversionCoefficientLShell()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string chunkWithWrongNT() {
  return
    " 4.863000+4 5.000000+1          0          0         10          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 1.378999-1 2.000000-3                      3580 8457     \n";
}
