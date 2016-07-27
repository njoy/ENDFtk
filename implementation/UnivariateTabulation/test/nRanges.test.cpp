#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation nRanges",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  REQUIRE( 3 == tab1.nRanges() );
}
