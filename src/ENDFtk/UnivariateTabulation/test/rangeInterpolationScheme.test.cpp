#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation rangeInterpolationScheme",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< long > interpolationScheme{1,2,3};
  
  for ( long index = 0; index < tab1.nRanges(); ++index ){
    REQUIRE( interpolationScheme[ index ] ==
             tab1.rangeInterpolationScheme( index ) );
  }
  REQUIRE_THROWS( tab1.rangeInterpolationScheme( -1 ) );
  REQUIRE_THROWS( tab1.rangeInterpolationScheme( tab1.NR() ) );
  const auto& ctab1 = tab1;
  for ( long index = 0; index < ctab1.nRanges(); ++index ){
    REQUIRE( interpolationScheme[ index ] ==
             tab1.rangeInterpolationScheme( index ) );
  }
  REQUIRE_THROWS( ctab1.rangeInterpolationScheme( -1 ) );
  REQUIRE_THROWS( ctab1.rangeInterpolationScheme( ctab1.NR() ) );  
}
