SCENARIO( "InterpolationBase L2",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.L2() == 4l );
}
