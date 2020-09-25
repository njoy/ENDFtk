SCENARIO( "InterpolationRecord nRanges",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( 3 == tab2.NR() );
}
