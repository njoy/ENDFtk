#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< InterpolationRecord() > makeTAB2;

SCENARIO( "InterpolationRecord nRanges",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( 3 == tab2.NR() );
}
