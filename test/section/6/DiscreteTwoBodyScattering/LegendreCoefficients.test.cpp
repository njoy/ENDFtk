// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/6.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LegendreCoefficients =
section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreCoefficients& );
std::string invalidLANG();
std::string invalidSize();

SCENARIO( "LegendreCoefficients" ) {

  GIVEN( "valid data for a LegendreCoefficients" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< double > coefficients = { 1., 2., 3., 4. };

      LegendreCoefficients chunk( energy, std::move( coefficients ) );

      THEN( "a LegendreCoefficients can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LegendreCoefficients chunk(begin, end, lineNumber, 9228, 6, 5 );

      THEN( "a LegendreCoefficients can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 6, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string with an invalid LANG" ) {

    std::string string = invalidLANG();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                          9228, 6, 5 ) );
    }
  } // GIVEN

  GIVEN( "a string with inconsistent NW and NL" ) {

    std::string string = invalidSize();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an exception is thrown" ) {

      CHECK_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                          9228, 6, 5 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

void verifyChunk( const LegendreCoefficients& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 0 == chunk.LANG() );
  CHECK( 4 == chunk.NW() );
  CHECK( 4 == chunk.NL() );
  CHECK( 4 == chunk.legendreOrder() );
  CHECK( 4 == chunk.A().size() );
  CHECK( 4 == chunk.coefficients().size() );
  CHECK_THAT( 1., WithinRel( chunk.A()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.A()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.A()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.A()[3] ) );
  CHECK_THAT( 1., WithinRel( chunk.coefficients()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.coefficients()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.coefficients()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.coefficients()[3] ) );

  CHECK( 2 == chunk.NC() );
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
