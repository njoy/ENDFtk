#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/460.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "section::Type< 1, 460 >::DiscretePhoton" ) {

  GIVEN( "a string representation of a valid section::Type< 1, 460 >::DiscretePhoton" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a section::Type< 1, 460 >::DiscretePhoton can be constructed and members can be tested" ) {
      section::Type< 1, 460 >::DiscretePhoton chunk( begin, end, lineNumber, 9228, 1, 460 );

      REQUIRE( 0.1 == Approx( chunk.E() ) );
      REQUIRE( 1 == chunk.index() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 2 == chunk.NP() );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 4 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.boundaries()[0] );
      REQUIRE( 2 == chunk.time().size() );
      REQUIRE( 2 == chunk.multiplicity().size() );
      REQUIRE( 0. == Approx( chunk.time()[0] ) );
      REQUIRE( 4. == Approx( chunk.time()[1] ) );
      REQUIRE( 4.877451e-1 == Approx( chunk.multiplicity()[0] ) );
      REQUIRE( 1.715686e-1 == Approx( chunk.multiplicity()[1] ) );

      REQUIRE( 3 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 460 >::DiscretePhoton" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    section::Type< 1, 460 >::DiscretePhoton chunk( begin, end, lineNumber, 9228, 1, 460 );

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
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n";
}
