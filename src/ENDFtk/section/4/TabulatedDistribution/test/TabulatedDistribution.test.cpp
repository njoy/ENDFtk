#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using TabulatedDistribution = section::Type< 4 >::TabulatedDistribution;

std::string chunk();
void verifyChunk( const TabulatedDistribution& );
std::string invalidChunk();

SCENARIO( "TabulatedDistribution" ) {

  GIVEN( "valid data for a TabulatedDistribution" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< long > boundaries = { 3 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > cosines = { -1.0, 0.0, 1.0 };
      std::vector< double > probabilities = { 0.0, 1.0, 0.0 };

      TabulatedDistribution chunk( energy,
                                   std::move( boundaries ),
      	                           std::move( interpolants ),
      	                           std::move( cosines ),
      	                           std::move( probabilities ) );

      THEN( "an TabulatedDistribution can be constructed and members can be "
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

      TabulatedDistribution chunk( begin, end, lineNumber, 9228, 4, 2 );
      
      THEN( "a TabulatedDistribution can be constructed and members can be "
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

  GIVEN( "invalid data for a TabulatedDistribution" ) {

    WHEN( "the data with an error is given" ) {

      double energy = 1e-5;
      std::vector< long > wrongBoundaries = { 3, 4 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > cosines = { -1.0, 0.0, 1.0 };
      std::vector< double > probabilities = { 0.0, 1.0, 0.0 };

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( TabulatedDistribution( energy,
                                               std::move( wrongBoundaries ),
      	                                       std::move( interpolants ),
      	                                       std::move( cosines ),
      	                                       std::move( probabilities ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( TabulatedDistribution( begin, end, lineNumber,
                                              9228, 4, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0          1          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}

void verifyChunk( const TabulatedDistribution& chunk ) {

  REQUIRE( 1e-5 == Approx( chunk.E() ) );
  REQUIRE( 1e-5 == Approx( chunk.incidentEnergy() ) );
  REQUIRE( 3 == chunk.NP() );
  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 3 == chunk.boundaries()[0] );
  REQUIRE( 2 == chunk.interpolants()[0] );
  REQUIRE( 3 == chunk.cosines().size() );
  REQUIRE( -1.0  == Approx( chunk.cosines()[0] ) );
  REQUIRE( 0.0 == Approx( chunk.cosines()[1] ) );
  REQUIRE( 1.0 == Approx( chunk.cosines()[2] ) );
  REQUIRE( 3 == chunk.probabilities().size() );
  REQUIRE( 0.0  == Approx( chunk.probabilities()[0] ) );
  REQUIRE( 1.0 == Approx( chunk.probabilities()[1] ) );
  REQUIRE( 0.0 == Approx( chunk.probabilities()[2] ) );

  REQUIRE( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 1.000000-5          0          0          2          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}
