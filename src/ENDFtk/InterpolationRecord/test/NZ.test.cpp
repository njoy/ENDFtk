#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< InterpolationRecord() > makeTAB2;

SCENARIO( "InterpolationRecord nPairs",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( tab2.NZ() == 6 );
}
