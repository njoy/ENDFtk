#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using TabulatedDistributions = section::Type< 4 >::TabulatedDistributions;
using TabulatedDistribution = section::Type< 4 >::TabulatedDistribution;

std::string chunk();
void verifyChunk( const TabulatedDistributions& );
std::string invalidChunk();

SCENARIO( "TabulatedDistributions" ) {

  GIVEN( "valid data for a TabulatedDistributions" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 1 };
      std::vector< TabulatedDistribution > sequence =
        { { 1e-5, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
          { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } };

      TabulatedDistributions chunk( std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( sequence ) );

      THEN( "a TabulatedDistributions can be constructed and members can be "
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

      TabulatedDistributions chunk( begin, end, lineNumber, 9228, 4, 2 );
      
      THEN( "a TabulatedDistributions can be constructed and members can be "
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

  GIVEN( "invalid data for a TabulatedDistributions" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 };
        std::vector< long > interpolants = { 1 };
        std::vector< TabulatedDistribution > sequence =
          { { 1e-5, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
            { 2e+7, { 3 }, { 2 }, { -1.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } };

        REQUIRE_THROWS(
          TabulatedDistributions( std::move( wrongBoundaries ),
                                  std::move( interpolants ),
                                  std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 1, 2 };
        std::vector< TabulatedDistribution > sequence =
          { { 1e-5, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } },
            { 2e+7, { 3 }, { 2 }, { -1.0, 0.5, 1.0 }, { 0.0, 0.5, 0.0 } } };

        REQUIRE_THROWS(
          TabulatedDistributions( std::move( boundaries ),
                                  std::move( wrongInterpolants ),
                                  std::move( sequence ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 1 };
        std::vector< TabulatedDistribution > wrongSequence =
          { { 1e-5, { 2 }, { 2 }, { -1.0, 1.0 }, { 0.5, 0.5 } } };

        REQUIRE_THROWS(
          TabulatedDistributions( std::move( boundaries ),
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

        REQUIRE_THROWS( TabulatedDistributions( begin, end, lineNumber,
                                                9228, 4, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          1          29228 4  2     \n"
    "          2          2                                            9228 4  2     \n"
    "-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}

void verifyChunk( const TabulatedDistributions& chunk ) {

  REQUIRE( 2 == chunk.LTT() );
  REQUIRE( 2 == chunk.LAW() );

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
  REQUIRE( 2 == d.NP() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 2 == d.boundaries()[0] );
  REQUIRE( 2 == d.interpolants()[0] );
  REQUIRE( 2 == d.cosines().size() );
  REQUIRE( -1.0  == Approx( d.cosines()[0] ) );
  REQUIRE( 1.0 == Approx( d.cosines()[1] ) );
  REQUIRE( 2 == d.probabilities().size() );
  REQUIRE( 0.5  == Approx( d.probabilities()[0] ) );
  REQUIRE( 0.5 == Approx( d.probabilities()[1] ) );

  d = distributions[1];
  REQUIRE( 2e+7 == Approx( d.E() ) );
  REQUIRE( 2e+7 == Approx( d.incidentEnergy() ) );
  REQUIRE( 3 == d.NP() );
  REQUIRE( 1 == d.NR() );
  REQUIRE( 1 == d.boundaries().size() );
  REQUIRE( 1 == d.interpolants().size() );
  REQUIRE( 3 == d.boundaries()[0] );
  REQUIRE( 2 == d.interpolants()[0] );
  REQUIRE( 3 == d.cosines().size() );
  REQUIRE( -1.0  == Approx( d.cosines()[0] ) );
  REQUIRE( 0.0 == Approx( d.cosines()[1] ) );
  REQUIRE( 1.0 == Approx( d.cosines()[2] ) );
  REQUIRE( 3 == d.probabilities().size() );
  REQUIRE( 0.0  == Approx( d.probabilities()[0] ) );
  REQUIRE( 1.0 == Approx( d.probabilities()[1] ) );
  REQUIRE( 0.0 == Approx( d.probabilities()[2] ) );

  REQUIRE( 8 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          29228 4  2     \n"
    "          2          1                                            9228 4  2     \n"
    " 0.000000+0 1.000000-5          0          0          1          29228 4  2     \n"
    "          2          2                                            9228 4  2     \n"
    "-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n"
    " 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}
