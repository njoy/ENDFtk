SCENARIO( "InterpolationBase rangeInterpolationScheme",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  std::vector< long > interpolationScheme{1,2,3};

  for ( long index = 0; index < interpolation.NR(); ++index ){
    REQUIRE( interpolationScheme[ index ] == interpolation.interpolants()[ index ] );
  }

  REQUIRE_THROWS( ranges::at( interpolation.interpolants(), -1 ) );
  REQUIRE_THROWS( ranges::at( interpolation.interpolants(), interpolation.NR() ) );

}
