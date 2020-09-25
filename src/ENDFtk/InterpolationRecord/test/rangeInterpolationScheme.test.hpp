SCENARIO( "InterpolationRecord rangeInterpolationScheme",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  std::vector< long > interpolationScheme{1,2,3};

  for ( long index = 0; index < tab2.NR(); ++index ){
    REQUIRE( interpolationScheme[ index ] == tab2.interpolants()[ index ] );
  }

  REQUIRE_THROWS( ranges::at( tab2.interpolants(), -1 ) );
  REQUIRE_THROWS( ranges::at( tab2.interpolants(), tab2.NR() ) );

}
