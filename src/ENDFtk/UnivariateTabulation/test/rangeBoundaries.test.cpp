#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation rangeBoundaries",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< std::vector< double > > xValues
  { { 1.0, 2.0, 3.0, 4.0 }, { 4.0, 5.0 }, { 5.0, 6.0 } };
  for ( long index = 0; index < tab1.nRanges(); ++index ){
    auto range = tab1.rangeBoundaries( index );
    auto reference = xValues[index].begin();
    auto begin = range.begin();
    auto end = range.end();
    while ( begin != end){
      REQUIRE( *begin == *reference );
      ++begin; ++reference;
    }
  }
  REQUIRE_THROWS( tab1.rangeBoundaries( -1 ) );
  REQUIRE_THROWS( tab1.rangeBoundaries( tab1.NR() ) );
}
