#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 6 >::NBodyPhaseSpace" ) {

  GIVEN( "a string representation of a valid section::Type< 6 >::NBodyPhaseSpace" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a section::Type< 6 >::NBodyPhaseSpace can be constructed and members can be tested" ) {
      section::Type< 6 >::NBodyPhaseSpace chunk(begin, end, lineNumber, 9228, 6, 5 );

      REQUIRE( 6 == chunk.LAW() );

      REQUIRE( 5. == Approx( chunk.APSX() ) );
      REQUIRE( 4 == chunk.NPSX() );

      REQUIRE( 1 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 6 >::NBodyPhaseSpace" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    section::Type< 6 >::NBodyPhaseSpace chunk(begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n";
}
