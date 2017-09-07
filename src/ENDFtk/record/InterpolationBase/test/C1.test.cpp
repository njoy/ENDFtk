#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk::record;

extern std::function< InterpolationBase() > makeInterpolationBase;

SCENARIO( "InterpolationBase C1",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.C1() == 1.0 );
}
