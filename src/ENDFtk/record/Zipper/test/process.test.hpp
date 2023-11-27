SCENARIO( "The Zipper process function ", "[ENDFtk], [Zipper]" ){
  GIVEN("a line with zipped values" ){
    std::string line =
      " 1.000000+0          1 2.000000+0          2 3.000000+0          3 125 1451    1\n";

    using Zip = Zipper::Zipped< Real, Integer<11> >;

    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    auto pack =
      Zipper::ReadingPack< decltype(it) >( it, end, lineNumber, 125, 1, 451 );
    std::array< double, 3 > dsink;
    std::array< long, 3 > isink;

    WHEN("passed to the zipper's process function"){
      THEN( "the extracted values will be correct"){
        Zipper::process< Zip >( pack, dsink[0], isink[0],
                                      dsink[1], isink[1],
                                      dsink[2], isink[2] );
        for ( int i = 0; i < 3; ++i ){
          CHECK_THAT( dsink[i], WithinRel( double(i + 1) ) );
          CHECK( isink[i] == i + 1 );
        }
      }
    }
  }
}
