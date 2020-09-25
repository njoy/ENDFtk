SCENARIO( "TabulationRecord L1",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.L1() == 3l );
}
