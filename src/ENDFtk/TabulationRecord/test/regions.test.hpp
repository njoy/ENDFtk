SCENARIO( "TabulationRecord regions", "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  std::vector< std::vector< double > > xValues { { 1.0, 2.0, 3.0, 4.0 },
                                                 { 4.0, 5.0 },
                                                 { 5.0, 6.0 } };

  std::vector< std::vector< double > > yValues { { 3.0, 4.0, 5.0, 6.0 },
                                                 { 6.0, 7.0 },
                                                 { 7.0, 8.0 } };

  // regions acts like an array of pairs of arrays.
  // Hence...

  // regions are iterable
  int index = 0;
  for ( auto region : tab1.regions() ){
    ranges::equal( region.first, xValues[index] );
    ranges::equal( region.second, yValues[index++] );
  }

  // regions are indexible, with and without bound checking
  auto regions = tab1.regions();
  for ( size_t index = 0; index < size_t(tab1.NR()); ++index ){
    ranges::equal( regions.at(index).first, xValues[index] );
    ranges::equal( regions[index].first, xValues[index] );
    ranges::equal( regions.at(index).second, yValues[index] );
    ranges::equal( regions[index].second, yValues[index] );
  }
  REQUIRE_THROWS( tab1.regions().at( -1 ) );
  REQUIRE_THROWS( tab1.regions().at( tab1.NR() ) );

  // the result of regions() is actually a view of views
  // views don't actually own the data they serve.
  // Consequently the result of `regions()`
  //   + doesn't require a heap allocation
  //   + and is only modestly sized (the same as an array of 6 doubles).

  REQUIRE( sizeof( tab1.regions() ) == 48 );

}
