#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/455.hpp"

using namespace njoy::ENDFtk;
using Constant = section::Type< 1, 455 >::Constant;

std::string chunk();

SCENARIO( "Constant" ) {

  GIVEN( "a string representation of a valid Constant" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a Constant can be constructed and members can be tested" ) {
      Constant chunk( begin, end, lineNumber, 9228, 1, 455 );

      auto lambdas = chunk.lambdas();

      REQUIRE( 2 == chunk.NC() );
      REQUIRE( 0 == chunk.LDG() );
      REQUIRE( 6 == chunk.NNF() );
      REQUIRE( 6 == lambdas.size() );
      REQUIRE( 0.013336 == Approx( lambdas[0] ) );
      REQUIRE( 0.032739 == Approx( lambdas[1] ) );
      REQUIRE( 0.12078 == Approx( lambdas[2] ) );
      REQUIRE( 0.30278 == Approx( lambdas[3] ) );
      REQUIRE( 0.84949 == Approx( lambdas[4] ) );
      REQUIRE( 2.853000 == Approx( lambdas[5] ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of Constant" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    Constant chunk( begin, end, lineNumber, 9228, 1, 455 );

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
    " 0.000000+0 0.000000+0          0          0          6          09228 1455     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n";
}
