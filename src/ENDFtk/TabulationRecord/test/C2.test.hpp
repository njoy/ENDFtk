SCENARIO( "TabulationRecord C2",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.C2() == 2.0 );
}
