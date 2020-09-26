#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LegendreCoefficients = 
section::Type< 6 >::ChargedParticleElasticScattering::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreCoefficients& );
std::string invalidLTP();
std::string invalidSize();

SCENARIO( "LegendreCoefficients" ) {

  GIVEN( "valid data for a LegendreCoefficients" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< double > values = { 1, 2, 3, 4 };

      THEN( "a LegendreCoefficients can be constructed "
            "and members can be tested" ) {

        LegendreCoefficients chunk( energy, std::move( values ) );
        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a LegendreCoefficients can be constructed "
            "and members can be tested" ) {

        LegendreCoefficients chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of LegendreCoefficients" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    LegendreCoefficients chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "a string representation is used with an invalid LTP" ) {

      std::string string = invalidLTP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS(
          LegendreCoefficients( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NW and NL" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS(
          LegendreCoefficients( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          2          0          4          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

void verifyChunk( const LegendreCoefficients& chunk ) {

  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  REQUIRE( 2 == chunk.LTP() );
  REQUIRE( 4 == chunk.NW() );
  REQUIRE( 3 == chunk.NL() );
  REQUIRE( 4 == chunk.coefficients().size() );
  REQUIRE( 1. == Approx( chunk.coefficients()[0] ) );
  REQUIRE( 2. == Approx( chunk.coefficients()[1] ) );
  REQUIRE( 3. == Approx( chunk.coefficients()[2] ) );
  REQUIRE( 4. == Approx( chunk.coefficients()[3] ) );

  REQUIRE( 2 == chunk.NC() );
}

std::string invalidLTP() {
  return
    " 0.000000+0 1.000000-5         12          0          4          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          2          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}
