SCENARIO( "InterpolationBase nPairs",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.N2() == 6 );
}
