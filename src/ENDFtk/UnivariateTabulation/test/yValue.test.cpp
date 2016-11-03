#include "catch.hpp"

#include "ENDFtk.hpp"


extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation yValue",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< double > yValues{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
  for ( long index = 0; index < tab1.nPairs(); ++index ){
    REQUIRE( yValues[ index ] == tab1.yValue( index ) );
  }
  REQUIRE_THROWS( tab1.yValue( -1 ) );
  REQUIRE_THROWS( tab1.yValue( tab1.NP() ) );
  const auto& ctab1 = tab1;
  for ( long index = 0; index < ctab1.nPairs(); ++index ){
    REQUIRE( yValues[ index ] == ctab1.yValue( index ) );
  }
  REQUIRE_THROWS( ctab1.yValue( -1 ) );
  REQUIRE_THROWS( ctab1.yValue( ctab1.NP() ) );
}
