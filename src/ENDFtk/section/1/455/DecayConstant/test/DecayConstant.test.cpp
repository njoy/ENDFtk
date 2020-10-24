#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/455.hpp"

using namespace njoy::ENDFtk;
using DecayConstant = section::Type< 1, 455 >::DecayConstant;

std::string chunk();

SCENARIO( "DecayConstant" ) {

  GIVEN( "a string representation of a valid DecayConstant" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a DecayConstant can be constructed and members can be tested" ) {
      DecayConstant chunk( begin, end, lineNumber, 9228, 1, 455 );

      auto lambdas = chunk.lambdas();
      auto alphas = chunk.alphas();

      REQUIRE( 3 == chunk.NC() );
      REQUIRE( 1e-5 == Approx( chunk.energy() ) );
      REQUIRE( 6 == lambdas.size() );
      REQUIRE( 1. == Approx( lambdas[0] ) );
      REQUIRE( 2. == Approx( lambdas[1] ) );
      REQUIRE( 3. == Approx( lambdas[2] ) );
      REQUIRE( 4. == Approx( lambdas[3] ) );
      REQUIRE( 5. == Approx( lambdas[4] ) );
      REQUIRE( 6. == Approx( lambdas[5] ) );
      REQUIRE( 6 == alphas.size() );
      REQUIRE( 1.1 == Approx( alphas[0] ) );
      REQUIRE( 2.1 == Approx( alphas[1] ) );
      REQUIRE( 3.1 == Approx( alphas[2] ) );
      REQUIRE( 4.1 == Approx( alphas[3] ) );
      REQUIRE( 5.1 == Approx( alphas[4] ) );
      REQUIRE( 6.1 == Approx( alphas[5] ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of DecayConstant" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    DecayConstant chunk( begin, end, lineNumber, 9228, 1, 455 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 455 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0         12          09228 1455     \n"
    " 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n"
    " 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n";
}
