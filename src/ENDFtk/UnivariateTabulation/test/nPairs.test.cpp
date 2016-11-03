#include "catch.hpp"

#include "ENDFtk.hpp"


extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation nPairs",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.NP() == 6 );
  REQUIRE( tab1.nPairs() == 6 );
}
