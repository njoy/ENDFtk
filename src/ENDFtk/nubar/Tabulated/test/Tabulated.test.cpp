#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "nubar::Tabulated" ) {

  GIVEN( "a string representation of a valid nubar::Tabulated" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a nubar::Tabulated can be constructed and members can be tested" ) {
      nubar::Tabulated chunk( begin, end, lineNumber, 9228, 1, 455 );

      auto energy = chunk.energy();
      auto nubar = chunk.nubar();
      auto interpolants = chunk.interpolants();
      auto boundaries = chunk.boundaries();

      REQUIRE( 4 == chunk.NC() );
      REQUIRE( 2 == chunk.LNU() );
      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 1 == interpolants.size() );
      REQUIRE( 1 == boundaries.size() );
      REQUIRE( 4 == chunk.NP() );
      REQUIRE( 4 == energy.size() );
      REQUIRE( 4 == nubar.size() );
      REQUIRE( 1e-5 == Approx( energy[0] ) );
      REQUIRE( 0.0253 == Approx( energy[1] ) );
      REQUIRE( 0.05 == Approx( energy[2] ) );
      REQUIRE( 2e+7 == Approx( energy[3] ) );
      REQUIRE( 2.4367 == Approx( nubar[0] ) );
      REQUIRE( 2.4367 == Approx( nubar[1] ) );
      REQUIRE( 2.4367 == Approx( nubar[2] ) );
      REQUIRE( 5.209845 == Approx( nubar[3] ) );
      REQUIRE( 2 == interpolants[0] );
      REQUIRE( 4 == boundaries[0] );
    }
  } // GIVEN

  GIVEN( "a valid instance of nubar::Tabulated" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    nubar::Tabulated chunk( begin, end, lineNumber, 9228, 1, 455 );

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
    " 0.000000+0 0.000000+0          0          0          1          49228 1455     \n"
    "          4          2                                            9228 1455     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n"
    " 2.000000+7 5.209845+0                                            9228 1455     \n";
}

