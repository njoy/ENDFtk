SCENARIO( "InterpolationRecord printing","[ENDFtk], [InterpolationRecord]" ){

  GIVEN( "single region TAB2" ){

    std::string tab1 =
      " 0.000000+0 0.000000+0         33          0          1          49228 1460     \n"
      "          4          4                                            9228 1460     \n";

    SECTION( "print" ){
      auto begin = tab1.begin();
      auto end = tab1.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      InterpolationRecord table( begin, end, lineNumber, MAT, MF, MT );
      std::string buffer;
      auto output = std::back_inserter( buffer );
      table.print( output, MAT, MF, MT );

      REQUIRE( buffer == tab1 );
    }
  }

  GIVEN( "long region TAB2" ){

    std::string tab1 =
      " 0.000000+0 0.000000+0         33          0          4          49228 1460     \n"
      "          1          4          2          3          3          29228 1460     \n"
      "          4          1                                            9228 1460     \n";

    SECTION( "print" ){
      auto begin = tab1.begin();
      auto end = tab1.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      InterpolationRecord table( begin, end, lineNumber, MAT, MF, MT );
      std::string buffer;
      auto output = std::back_inserter( buffer );
      table.print( output, MAT, MF, MT );

      REQUIRE( buffer == tab1 );
    }
  }
}
