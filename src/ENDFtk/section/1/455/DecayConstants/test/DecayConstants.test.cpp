// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/1/455.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DecayConstants = section::Type< 1, 455 >::DecayConstants;

std::string chunk();
void verifyChunk( const DecayConstants& );
std::string invalidChunk();

SCENARIO( "DecayConstants" ) {

  GIVEN( "valid data for a DecayConstants" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< double > constants = { 1., 2., 3., 4., 5., 6. };
      std::vector< double > abundances = { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 };

      DecayConstants chunk( energy, std::move( constants ),
                            std::move( abundances ) );

      THEN( "an DecayConstants can be constructed and members can "
            "be tested" ) {

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

      DecayConstants chunk( begin, end, lineNumber, 9228, 1, 455 );

      THEN( "a DecayConstants can be constructed and members can "
            "be tested" ) {

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

  GIVEN( "invalid data for a DecayConstants" ) {

    WHEN( "inconsistent sizes are used" ) {

      double energy = 1e-5;
      std::vector< double > constants = { 1., 2., 3., 4., 5., 6. };
      std::vector< double > wrongsize = { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1 };

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( DecayConstants( energy, std::move( constants ),
                                      std::move( wrongsize ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a DecayConstants with inconsistent sizes" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( DecayConstants( begin, end, lineNumber, 9228, 1, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n";
}

void verifyChunk( const DecayConstants& chunk ) {

  CHECK( 6 == chunk.NNF() );
  CHECK( 6 == chunk.numberPrecursors() );

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 6 == chunk.lambdas().size() );
  CHECK( 6 == chunk.decayConstants().size() );
  CHECK_THAT( 1., WithinRel( chunk.lambdas()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.lambdas()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.lambdas()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.lambdas()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.lambdas()[4] ) );
  CHECK_THAT( 6., WithinRel( chunk.lambdas()[5] ) );
  CHECK_THAT( 1., WithinRel( chunk.decayConstants()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.decayConstants()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.decayConstants()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.decayConstants()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.decayConstants()[4] ) );
  CHECK_THAT( 6., WithinRel( chunk.decayConstants()[5] ) );
  CHECK( 6 == chunk.alphas().size() );
  CHECK( 6 == chunk.abundances().size() );
  CHECK_THAT( 1.1, WithinRel( chunk.alphas()[0] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.alphas()[1] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.alphas()[2] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.alphas()[3] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.alphas()[4] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.alphas()[5] ) );
  CHECK_THAT( 1.1, WithinRel( chunk.abundances()[0] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.abundances()[1] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.abundances()[2] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.abundances()[3] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.abundances()[4] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.abundances()[5] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 1.000000-5          0          0         13          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n"
    " 7.000000+0                                                       9228 1455     \n";
}
