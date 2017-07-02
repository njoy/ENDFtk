#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation rangeBoundaries",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< std::vector< double > > xValues { { 1.0, 2.0, 3.0, 4.0 },
                                                 { 4.0, 5.0 },
                                                 { 5.0, 6.0 } };

  auto regions = tab1.regions();
  for ( size_t index = 0; index < size_t(tab1.NR()); ++index ){
    const auto& reference = xValues[index];
    auto trial = regions[index].first;
    ranges::equal( trial, reference );
  }

  //REQUIRE_THROWS( ranges::at( tab1.boundaries(), -1 ) );
  REQUIRE_THROWS( ranges::at( tab1.boundaries(), tab1.NR() ) );
}
