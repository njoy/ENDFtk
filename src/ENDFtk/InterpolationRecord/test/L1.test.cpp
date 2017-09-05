#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< InterpolationRecord() > makeTAB2;

SCENARIO( "InterpolationRecord L1",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( tab2.L1() == 3l );
}
