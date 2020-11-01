SCENARIO( "InterpolationRecord C1",
          "[ENDFtk], [InterpolationRecord]" ){
  auto tab2 = makeTAB2();
  REQUIRE( tab2.C1() == 1.0 );
}
