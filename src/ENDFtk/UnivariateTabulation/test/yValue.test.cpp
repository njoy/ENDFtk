#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation yValue",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< double > yValues{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };

  for ( long index = 0; index < tab1.NP(); ++index ){
    REQUIRE( yValues[ index ] == tab1.y()[ index ] );
    //REQUIRE( yValues[ index ] == tab1.y().at( index ) );
  }

  //REQUIRE_THROWS( ranges::at( tab1.y(), -1 ) );
  REQUIRE_THROWS( ranges::at( tab1.y(), tab1.NP() ) );
}
