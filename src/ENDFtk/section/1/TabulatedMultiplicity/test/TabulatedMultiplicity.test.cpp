#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using TabulatedMultiplicity = section::TabulatedMultiplicity;

std::string chunk();
void verifyChunk( const TabulatedMultiplicity& );
std::string invalidChunk();

SCENARIO( "TabulatedMultiplicity" ) {

  GIVEN( "valid data for a TabulatedDistribution" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 4 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 2.53e-2, 5e-2, 2e+7 };
      std::vector< double > multiplicities = { 2.4367, 2.4367,
                                               2.4367, 5.209845 };

      TabulatedMultiplicity chunk( std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( energies ),
                                   std::move( multiplicities ) );

      THEN( "an TabulatedMultiplicity can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TabulatedMultiplicity chunk( begin, end, lineNumber, 9228, 1, 455 );

      THEN( "a TabulatedMultiplicity can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TabulatedMultiplicity" ) {

    WHEN( "there are issues with the input data" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::vector< long > boundaries = { 4, 6 };
      std::vector< long > interpolants = { 2 };
      std::vector< double > energies = { 1e-5, 2.53e-2, 5e-2, 2e+7 };
      std::vector< double > multiplicities = { 2.4367, 2.4367,
                                               2.4367, 5.209845 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedMultiplicity( std::move( boundaries ),
                                             std::move( interpolants ),
                                             std::move( energies ),
                                             std::move( multiplicities ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedMultiplicity( begin, end, lineNumber,
                                             9228, 1, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

void verifyChunk( const TabulatedMultiplicity& chunk ) {

  CHECK( 2 == chunk.LNU() );
  CHECK( 2 == chunk.representation() );

  CHECK( 4 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 4 == chunk.boundaries()[0] );

  CHECK( 4 == chunk.E().size() );
  CHECK( 4 == chunk.energies().size() );
  CHECK( 4 == chunk.NU().size() );
  CHECK( 4 == chunk.multiplicities().size() );
  CHECK( 1e-5 == Approx( chunk.E()[0] ) );
  CHECK( 0.0253 == Approx( chunk.E()[1] ) );
  CHECK( 0.05 == Approx( chunk.E()[2] ) );
  CHECK( 2e+7 == Approx( chunk.E()[3] ) );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 0.0253 == Approx( chunk.energies()[1] ) );
  CHECK( 0.05 == Approx( chunk.energies()[2] ) );
  CHECK( 2e+7 == Approx( chunk.energies()[3] ) );
  CHECK( 2.4367 == Approx( chunk.NU()[0] ) );
  CHECK( 2.4367 == Approx( chunk.NU()[1] ) );
  CHECK( 2.4367 == Approx( chunk.NU()[2] ) );
  CHECK( 5.209845 == Approx( chunk.NU()[3] ) );
  CHECK( 2.4367 == Approx( chunk.multiplicities()[0] ) );
  CHECK( 2.4367 == Approx( chunk.multiplicities()[1] ) );
  CHECK( 2.4367 == Approx( chunk.multiplicities()[2] ) );
  CHECK( 5.209845 == Approx( chunk.multiplicities()[3] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}
