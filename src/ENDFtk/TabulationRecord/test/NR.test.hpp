SCENARIO( "TabulationRecord nRanges",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( 3 == tab1.NR() );
}
