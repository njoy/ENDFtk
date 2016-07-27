#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation yEnd",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( (tab1.yEnd() - tab1.yBegin()) == tab1.nPairs() );
  const auto& ctab1 = tab1;
  REQUIRE( (ctab1.yEnd() - ctab1.yBegin()) == ctab1.nPairs() );
}
