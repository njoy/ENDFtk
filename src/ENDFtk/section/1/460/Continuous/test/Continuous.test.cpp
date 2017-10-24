#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string invalidNG();

SCENARIO( "section::Type< 1, 460 >::Continuous" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 460 >::Continuous" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 1, 460 >::Continuous can be constructed and members can be tested" ) {
      section::Type< 1, 460 >::Continuous chunk(begin, end, lineNumber, 9228, 1, 460 );

      REQUIRE( 2 == chunk.LO() );
      REQUIRE( 0 == chunk.NG() );
      REQUIRE( 6 == chunk.NNF() );
      auto lambdas = chunk.lambdas();
      REQUIRE( 6 == lambdas.size() );
      REQUIRE( 0.013336 == Approx( lambdas[0] ) );
      REQUIRE( 0.032739 == Approx( lambdas[1] ) );
      REQUIRE( 0.12078 == Approx( lambdas[2] ) );
      REQUIRE( 0.30278 == Approx( lambdas[3] ) );
      REQUIRE( 0.84949 == Approx( lambdas[4] ) );
      REQUIRE( 2.853000 == Approx( lambdas[5] ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 460 >::Continuous" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 1, 460 >::Continuous chunk(begin, end, lineNumber, 9228, 1, 460 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 460 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          6          09228 1460     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1460     \n";
}

