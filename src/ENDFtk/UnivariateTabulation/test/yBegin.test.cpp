#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation yBegin",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( *(tab1.yBegin()) == 3.0 );
  const auto& ctab1 = tab1;
  REQUIRE( *(ctab1.yBegin()) == 3.0 );
}
