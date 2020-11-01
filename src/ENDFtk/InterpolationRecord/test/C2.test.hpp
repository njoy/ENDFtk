SCENARIO( "InterpolationRecord C2",
         "[ENDFtk], [InterpolationRecord]" ){
    auto tab2 = makeTAB2();
    REQUIRE( tab2.C2() == 2.0 );
}
