#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< TabulationRecord() > makeTAB1;

SCENARIO( "TabulationRecord rangeInterpolationScheme",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  std::vector< long > interpolationScheme{1,2,3};
  
  for ( long index = 0; index < tab1.NR(); ++index ){
    REQUIRE( interpolationScheme[ index ] == tab1.interpolants()[ index ] );
  }

  REQUIRE_THROWS( ranges::at( tab1.interpolants(), -1 ) );
  REQUIRE_THROWS( ranges::at( tab1.interpolants(), tab1.NR() ) );

}
