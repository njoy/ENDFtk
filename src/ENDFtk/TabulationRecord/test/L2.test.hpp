SCENARIO( "TabulationRecord L2",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.L2() == 4l );
}
