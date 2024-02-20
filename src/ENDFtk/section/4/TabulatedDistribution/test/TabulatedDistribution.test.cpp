// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/4.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
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

        CHECK( buffer == string );
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

        CHECK( buffer == string );
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

        CHECK_THROWS( TabulatedDistribution( energy,
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

        CHECK_THROWS( TabulatedDistribution( begin, end, lineNumber,
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

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );
  CHECK( 3 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 3 == chunk.cosines().size() );
  CHECK_THAT( -1.0 , WithinRel( chunk.MU()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.MU()[1] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.MU()[2] ) );
  CHECK_THAT( -1.0 , WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.cosines()[1] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.cosines()[2] ) );
  CHECK( 3 == chunk.probabilities().size() );
  CHECK_THAT( 0.0 , WithinRel( chunk.F()[0] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.F()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.F()[2] ) );
  CHECK_THAT( 0.0 , WithinRel( chunk.probabilities()[0] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.probabilities()[1] ) );
  CHECK_THAT( 0.0, WithinRel( chunk.probabilities()[2] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 1.000000-5          0          0          2          39228 4  2     \n"
    "          3          2                                            9228 4  2     \n"
    "-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n";
}
