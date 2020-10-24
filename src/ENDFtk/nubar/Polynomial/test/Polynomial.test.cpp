#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/nubar.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

SCENARIO( "nubar::Polynomial" ) {

  GIVEN( "a string representation of a valid nubar::Polynomial" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a nubar::Polynomial can be constructed and members can be tested" ) {
      nubar::Polynomial chunk( begin, end, lineNumber, 9228, 1, 455 );

      auto coefficients = chunk.coefficients();

      REQUIRE( 2 == chunk.NC() );
      REQUIRE( 2 == chunk.NCO() );
      REQUIRE( 1 == chunk.LNU() );
      REQUIRE( 2 == coefficients.size() );
      REQUIRE( 2.4367 == Approx( coefficients[0] ) );
      REQUIRE( 0.05 == Approx( coefficients[1] ) );
    }
  } // GIVEN

  GIVEN( "a valid instance of nubar::Polynomial" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    nubar::Polynomial chunk( begin, end, lineNumber, 9228, 1, 455 );

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
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}
