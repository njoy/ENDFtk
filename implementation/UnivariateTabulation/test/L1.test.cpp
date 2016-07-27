#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation L1",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.L1() == 3l );
}
