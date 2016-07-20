#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation xBegin",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( *(tab1.xBegin()) == 1.0 );
}
