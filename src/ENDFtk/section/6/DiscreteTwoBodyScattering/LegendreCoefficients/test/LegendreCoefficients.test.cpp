#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using LegendreCoefficients = 
section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients;

std::string chunk();
std::string invalidLANG();
std::string invalidSize();

SCENARIO( "LegendreCoefficients" ) {

  GIVEN( "valid data for a LegendreCoefficients" ) {

    double energy = 1e-5;
    std::vector< double > coefficients = { 1., 2., 3., 4. };

    THEN( "a LegendreCoefficients can "
          "be constructed and members can be tested" ) {
      LegendreCoefficients chunk( energy, std::move( coefficients ) );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.LANG() );
      REQUIRE( 4 == chunk.NW() );
      REQUIRE( 4 == chunk.NL() );
      REQUIRE( 4 == chunk.coefficients().size() );
      REQUIRE( 1. == Approx( chunk.coefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.coefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.coefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.coefficients()[3] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid LegendreCoefficients" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a LegendreCoefficients can "
          "be constructed and members can be tested" ) {
      LegendreCoefficients chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 1e-5 == Approx( chunk.energy() ) );

      REQUIRE( 0 == chunk.LANG() );
      REQUIRE( 4 == chunk.NW() );
      REQUIRE( 4 == chunk.NL() );
      REQUIRE( 4 == chunk.coefficients().size() );
      REQUIRE( 1. == Approx( chunk.coefficients()[0] ) );
      REQUIRE( 2. == Approx( chunk.coefficients()[1] ) );
      REQUIRE( 3. == Approx( chunk.coefficients()[2] ) );
      REQUIRE( 4. == Approx( chunk.coefficients()[3] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string with an invalid LANG" ) {

    std::string string = invalidLANG();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                            9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a string with inconsistent NW and NL" ) {

    std::string string = invalidSize();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                            9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of LegendreCoefficients" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    LegendreCoefficients
      chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

std::string invalidLANG() {
  return
    " 0.000000+0 1.000000-5          1          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

std::string invalidSize() {
  return
    " 0.000000+0 1.000000-5          0          0          4          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}
