#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< TabulationRecord() > makeTAB1;

SCENARIO( "TabulationRecord C2",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.C2() == 2.0 );
}
