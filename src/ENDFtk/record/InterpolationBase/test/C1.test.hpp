SCENARIO( "InterpolationBase C1",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.C1() == 1.0 );
}
