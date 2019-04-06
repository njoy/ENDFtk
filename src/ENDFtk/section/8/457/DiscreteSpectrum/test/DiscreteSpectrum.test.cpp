#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
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

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > discreteEnergy = {{ 4.863000e+4, 5.000000e+1 }};
      double decayChain = 3.;
      double type = 0.;
      std::array< double, 2 > relativeIntensity = {{ 1.420112e-6,
                                                     2.85306e-10 }};
      
      THEN( "a DiscreteSpectrum can be constructed and members can be "
            "tested" ) {

        DiscreteSpectrum chunk( decayChain, discreteEnergy,
                                relativeIntensity, type );
        verifyChunkWithSTYPNotZeroOrTwo( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithSTYPNotZeroOrTwo();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkWithSTYPNotZeroOrTwo( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DiscreteSpectrum with STYP equal to 2" ) {

    WHEN( "the data is given explicitly" ) {

      std::array< double, 2 > discreteEnergy = {{ 4.863000e+4, 5.000000e+1 }};
      double decayChain = 3.;
      double type = 0.;
      std::array< double, 2 > relativeIntensity = {{ 1.420112e-6,
                                                     2.85306e-10 }};
      std::array< double, 2 > ris = {{ 1.0, 2.0 }};
      
      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        DiscreteSpectrum chunk( decayChain, discreteEnergy,
                                relativeIntensity, type, ris );
        verifyChunkWithSTYPTwo( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithSTYPTwo();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkWithSTYPTwo( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DiscreteSpectrum with STYP equal to 0" ) {

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
      
      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        DiscreteSpectrum chunk( decayChain, discreteEnergy,
                                relativeIntensity, type, ris,
                                ricc, rick, ricl );
        verifyChunkWithSTYPZero( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkWithSTYPZero();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "a DiscreteSpectrum can be constructed and members can be tested" ) {

        DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );
        verifyChunkWithSTYPZero( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of DiscreteSpectrum for STYP not equal to 0 or 2" ) {

    std::string string = chunkWithSTYPNotZeroOrTwo();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteSpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of DiscreteSpectrum for STYP equal to 2" ) {

    std::string string = chunkWithSTYPTwo();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteSpectrum chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of DiscreteSpectrum for STYP equal to 0" ) {

    std::string string = chunkWithSTYPZero();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DiscreteSpectrum chunk( begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a DiscreteSpectrum" ) {

    WHEN( "a string with the wrong NT value is used" ) {

      std::string string = chunkWithWrongNT();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      
      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( DiscreteSpectrum( begin, end, lineNumber, 3580, 8, 457 ) );
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
  REQUIRE( 3. == chunk.RTYP() );
  REQUIRE( 3. == chunk.decayChain() );
  REQUIRE( 4 == chunk.NT() );
  REQUIRE( 4.863000e+4 == Approx( chunk.ER()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( chunk.ER()[1] ) );
  REQUIRE( 4.863000e+4 == Approx( chunk.discreteEnergy()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( chunk.discreteEnergy()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( chunk.RI()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( chunk.RI()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( chunk.relativeIntensity()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( chunk.relativeIntensity()[1] ) );
  REQUIRE( 0. == chunk.TYPE() );
  REQUIRE( 0. == chunk.type() );
  REQUIRE( 0.0 == Approx( chunk.RIS()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RIS()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.internalPairFormationCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.RICC()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RICC()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.RICK()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RICK()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.RICL()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RICL()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientLShell()[1] ) );

  REQUIRE( 2 == chunk.NC() );
}

std::string chunkWithSTYPTwo() {
  return
    " 4.863000+4 5.000000+1          0          0          6          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n";
}

void verifyChunkWithSTYPTwo( const DiscreteSpectrum& chunk )
{
  REQUIRE( 3. == chunk.RTYP() );
  REQUIRE( 3. == chunk.decayChain() );
  REQUIRE( 6 == chunk.NT() );
  REQUIRE( 4.863000e+4 == Approx( chunk.discreteEnergy()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( chunk.discreteEnergy()[1] ) );
  REQUIRE( 4.863000e+4 == Approx( chunk.ER()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( chunk.ER()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( chunk.relativeIntensity()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( chunk.relativeIntensity()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( chunk.RI()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( chunk.RI()[1] ) );
  REQUIRE( 0. == chunk.TYPE() );
  REQUIRE( 0. == chunk.type() );
  REQUIRE( 1.0 == Approx( chunk.RIS()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.RIS()[1] ) );
  REQUIRE( 1.0 == Approx( chunk.internalPairFormationCoefficient()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.internalPairFormationCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.RICC()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RICC()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.RICK()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RICK()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.RICL()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.RICL()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.internalConversionCoefficientLShell()[1] ) );

  REQUIRE( 2 == chunk.NC() );
}

std::string chunkWithSTYPZero() {
  return
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 1.378999-1 2.000000-3 3.315735+5 5.608008+33580 8457     \n";
}

void verifyChunkWithSTYPZero( const DiscreteSpectrum& chunk )
{
  REQUIRE( 3. == chunk.RTYP() );
  REQUIRE( 3. == chunk.decayChain() );
  REQUIRE( 12 == chunk.NT() );
  REQUIRE( 4.863000e+4 == Approx( chunk.ER()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( chunk.ER()[1] ) );
  REQUIRE( 4.863000e+4 == Approx( chunk.discreteEnergy()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( chunk.discreteEnergy()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( chunk.RI()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( chunk.RI()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( chunk.relativeIntensity()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( chunk.relativeIntensity()[1] ) );
  REQUIRE( 0. == chunk.type() );
  REQUIRE( 1.0 == Approx( chunk.RIS()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.RIS()[1] ) );
  REQUIRE( 1.0 == Approx( chunk.internalPairFormationCoefficient()[0] ) );
  REQUIRE( 2.0 == Approx( chunk.internalPairFormationCoefficient()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( chunk.RICC()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( chunk.RICC()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( chunk.totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( chunk.totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 1.378999e-1 == Approx( chunk.RICK()[0] ) );
  REQUIRE( 2.000000e-3 == Approx( chunk.RICK()[1] ) );
  REQUIRE( 1.378999e-1 == Approx( chunk.internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 2.000000e-3 == Approx( chunk.internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( chunk.RICL()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( chunk.RICL()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( chunk.internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( chunk.internalConversionCoefficientLShell()[1] ) );

  REQUIRE( 3 == chunk.NC() );
}

std::string chunkWithWrongNT() {
  return
    " 4.863000+4 5.000000+1          0          0         10          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 1.000000+0 2.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 1.378999-1 2.000000-3                      3580 8457     \n";
}
