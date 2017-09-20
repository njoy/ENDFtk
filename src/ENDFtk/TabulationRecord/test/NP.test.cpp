#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< TabulationRecord() > makeTAB1;

SCENARIO( "TabulationRecord nPairs",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.NP() == 6 );
}
