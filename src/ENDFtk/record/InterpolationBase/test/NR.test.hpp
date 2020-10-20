SCENARIO( "InterpolationBase nRanges",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( 3 == interpolation.NR() );
}
