#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< InterpolationRecord() > makeTAB2;

SCENARIO( "InterpolationRecord L2",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( tab2.L2() == 4l );
}
