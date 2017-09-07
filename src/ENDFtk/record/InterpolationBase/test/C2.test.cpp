#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk::record;

extern std::function< InterpolationBase() > makeInterpolationBase;

SCENARIO( "InterpolationBase C2",
         "[ENDFtk], [InterpolationBase]" ){
    auto interpolation = makeInterpolationBase();
    REQUIRE( interpolation.C2() == 2.0 );
}
