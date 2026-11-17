// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using namespace njoy::ENDFtk;
using TabulatedMultiplicity = section::TabulatedMultiplicity;

std::string chunk();
void verifyChunk( const TabulatedMultiplicity& );
std::string invalidChunk();

SCENARIO( "TabulatedMultiplicity" ) {

  GIVEN( "valid data for a TabulatedMultiplicity" ) {

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
  CHECK( 4 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 2 == chunk.INT()[0] );
  CHECK( 4 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 4 == chunk.boundaries()[0] );

  CHECK( 4 == chunk.E().size() );
  CHECK( 4 == chunk.energies().size() );
  CHECK( 4 == chunk.NU().size() );
  CHECK( 4 == chunk.multiplicities().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.E()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.E()[3] ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 0.0253, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 2.4367, WithinRel( chunk.NU()[0] ) );
  CHECK_THAT( 2.4367, WithinRel( chunk.NU()[1] ) );
  CHECK_THAT( 2.4367, WithinRel( chunk.NU()[2] ) );
  CHECK_THAT( 5.209845, WithinRel( chunk.NU()[3] ) );
  CHECK_THAT( 2.4367, WithinRel( chunk.multiplicities()[0] ) );
  CHECK_THAT( 2.4367, WithinRel( chunk.multiplicities()[1] ) );
  CHECK_THAT( 2.4367, WithinRel( chunk.multiplicities()[2] ) );
  CHECK_THAT( 5.209845, WithinRel( chunk.multiplicities()[3] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}
