#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation xBegin",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( *(tab1.x().begin()) == 1.0 );
}
