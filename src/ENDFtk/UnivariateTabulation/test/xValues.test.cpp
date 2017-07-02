#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation xValue",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< double > xValues{1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

  for ( long index = 0; index < tab1.NP(); ++index ){
    REQUIRE( xValues[ index ] == tab1.x()[ index ] );
    // REQUIRE( xValues[ index ] == tab1.x().at( index ) );
  }
  // REQUIRE_THROWS( ranges::at( tab1.x(), -1 ) );
  REQUIRE_THROWS( ranges::at( tab1.x(), tab1.NP() ) );
}
