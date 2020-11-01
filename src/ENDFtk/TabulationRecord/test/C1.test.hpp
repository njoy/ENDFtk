SCENARIO( "TabulationRecord C1",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.C1() == 1.0 );
}
