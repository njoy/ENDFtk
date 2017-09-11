#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk::record;

extern std::function< InterpolationBase() > makeInterpolationBase;

SCENARIO( "InterpolationBase L2",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.L2() == 4l );
}
