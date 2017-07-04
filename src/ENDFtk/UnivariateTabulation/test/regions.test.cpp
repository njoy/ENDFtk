#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

extern std::function< UnivariateTabulation() > makeTAB1;

SCENARIO( "UnivariateTabulation regions",
          "[ENDFtk], [UnivariateTabulation]" ){
  auto tab1 = makeTAB1();
  std::vector< std::vector< double > > xValues { { 1.0, 2.0, 3.0, 4.0 },
                                                 { 4.0, 5.0 },
                                                 { 5.0, 6.0 } };

  std::vector< std::vector< double > > yValues { { 3.0, 4.0, 5.0, 6.0 },
                                                 { 6.0, 7.0 },
                                                 { 7.0, 8.0 } };

  auto regions = tab1.regions();
  
  for ( size_t index = 0; index < size_t(tab1.NR()); ++index ){
    ranges::equal( regions[index].first, xValues[index] );
    ranges::equal( regions[index].second, yValues[index] );
    
  }

  REQUIRE_THROWS( tab1.regions().at( -1 ) );
  REQUIRE_THROWS( tab1.regions().at( tab1.NR() ) );

  njoy::Log::info( "size of regions: {}", sizeof(regions) );
}
