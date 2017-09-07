#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk::record;

extern std::function< InterpolationBase() > makeInterpolationBase;

SCENARIO( "InterpolationBase nPairs",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.N2() == 6 );
}
