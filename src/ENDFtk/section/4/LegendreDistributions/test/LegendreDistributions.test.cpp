#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using LegendreDistributions = section::Type< 4 >::LegendreDistributions;
using LegendreCoefficients = section::Type< 4 >::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreDistributions& );
std::string invalidChunk();

SCENARIO( "LegendreDistributions" ) {

  GIVEN( "valid data for a LegendreDistributions" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< LegendreCoefficients > sequence =
        { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
          { 2e+7, { 2.874390e-2, 3.19645e-11 } } };

      LegendreDistributions chunk( std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( sequence ) );

      THEN( "an LegendreDistributions can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4, 2 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LegendreDistributions chunk( begin, end, lineNumber, 9228, 4, 2 );
      
      THEN( "a LegendreDistributions can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4, 2 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreDistributions" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< LegendreCoefficients > sequence =
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 2e+7, { 2.874390e-2, 3.19645e-11 } } };

        REQUIRE_THROWS(
          LegendreDistributions( std::move( wrongBoundaries ),
                                 std::move( interpolants ),
                                 std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< LegendreCoefficients > sequence =
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } },
            { 2e+7, { 2.874390e-2, 3.19645e-11 } } };

        REQUIRE_THROWS(
          LegendreDistributions( std::move( boundaries ),
                                 std::move( wrongInterpolants ),
                                 std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< LegendreCoefficients > wrongSequence =
          { { 1e-5, { 7.392510e-5, 8.477139e-9, 1.17106e-13 } } };

        REQUIRE_THROWS(
          LegendreDistributions( std::move( boundaries ),
                                 std::move( interpolants ),
                                 std::move( wrongSequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (LIST takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( LegendreDistributions( begin, end, lineNumber,
                                              9228, 4, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          2          09228 4  2     \n"
    " 2.874390-2 3.19645-11                                            9228 4  2     \n";
}

void verifyChunk( const LegendreDistributions& chunk ) {

  REQUIRE( 1 == chunk.LTT() );
  REQUIRE( 1 == chunk.LAW() );

  REQUIRE( 2 == chunk.NE() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 1 == chunk.interpolants()[0] );
  REQUIRE( 2 == chunk.boundaries()[0] );

  auto distributions = chunk.angularDistributions();

  auto d = distributions[0];
  REQUIRE( 1e-5 == Approx( d.E() ) );
  REQUIRE( 1e-5 == Approx( d.incidentEnergy() ) );
  REQUIRE( 3 == d.NL() );
  REQUIRE( 3 == d.legendreOrder() );
  REQUIRE( 3 == d.coefficients().size() );
  REQUIRE( 7.392510e-5  == Approx( d.coefficients()[0] ) );
  REQUIRE( 8.477139e-9 == Approx( d.coefficients()[1] ) );
  REQUIRE( 1.17106e-13 == Approx( d.coefficients()[2] ) );

  d = distributions[1];
  REQUIRE( 2e+7 == Approx( d.E() ) );
  REQUIRE( 2e+7 == Approx( d.incidentEnergy() ) );
  REQUIRE( 2 == d.NL() );
  REQUIRE( 2 == d.legendreOrder() );
  REQUIRE( 2 == d.coefficients().size() );
  REQUIRE( 2.874390e-2   == Approx( d.coefficients()[0] ) );
  REQUIRE( 3.19645e-11 == Approx( d.coefficients()[1] ) );

  REQUIRE( 6 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          3          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          2          09228 4  2     \n"
    " 2.874390-2 3.19645-11                                            9228 4  2     \n";
}
