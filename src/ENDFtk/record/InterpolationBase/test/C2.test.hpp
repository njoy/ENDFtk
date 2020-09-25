SCENARIO( "InterpolationBase C2",
         "[ENDFtk], [InterpolationBase]" ){
    auto interpolation = makeInterpolationBase();
    REQUIRE( interpolation.C2() == 2.0 );
}
