SCENARIO( "InterpolationBase L1",
          "[ENDFtk], [InterpolationBase]" ){
  auto interpolation = makeInterpolationBase();
  REQUIRE( interpolation.L1() == 3l );
}
