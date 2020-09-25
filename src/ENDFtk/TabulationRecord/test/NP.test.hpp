SCENARIO( "TabulationRecord nPairs",
          "[ENDFtk], [TabulationRecord]" ){
  auto tab1 = makeTAB1();
  REQUIRE( tab1.NP() == 6 );
}
