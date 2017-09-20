#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< TabulationRecord() > makeTAB1;

SCENARIO( "TabulationRecord nRanges",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( 3 == tab1.NR() );
}
