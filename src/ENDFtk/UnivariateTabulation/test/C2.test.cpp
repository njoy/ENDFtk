#include "catch.hpp"

#include "ENDFtk.hpp"


extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation C2",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.C2() == 2.0 );
}
