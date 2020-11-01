SCENARIO( "InterpolationRecord nPairs",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( tab2.NZ() == 6 );
}
