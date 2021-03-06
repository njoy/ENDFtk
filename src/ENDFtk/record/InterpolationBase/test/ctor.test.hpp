SCENARIO( "InterpolationBase ctor",
          "[ENDFtk], [InterpolationBase]" ){

  std::vector< long > regions{ 4, 5, 6 };
  std::vector< long > interpolation{ 1, 2, 3 };

  GIVEN( "a InterpolationBase object" ){
    InterpolationBase base( 1.0, 2.0, 3ul, 4ul,
                            std::move( regions ),
                            std::move( interpolation ) );

    THEN( "InterpolationBase objects can be copied" ) {
      auto copy = base;
      REQUIRE( copy == base );
    }
  }

  GIVEN( "mismatched region and interpolation arrays" ){
    std::vector< long > interpolation{ 1, 2, 3, 4 };

    REQUIRE_THROWS( InterpolationBase
                    ( 1.0, 2.0, 3ul, 4ul,
                      std::make_tuple( regions, interpolation ) ) );
  }

  GIVEN( "out of order region" ){
    std::vector< long > regions{ 5, 4, 6 };

    REQUIRE_THROWS( InterpolationBase
                    ( 1.0, 2.0, 3ul, 4ul,
                      std::make_tuple( regions, interpolation ) ) );
  }

  GIVEN( "single region InterpolationBase" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0          1          49228 1460     \n"
      "          4          4                                            9228 1460     \n";

    WHEN( "constructed with correct 'tail' values" ){
      auto begin = interpolation.begin();
      auto end = interpolation.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      InterpolationBase interpolation_1( begin, end, lineNumber, MAT, MF, MT );
      REQUIRE( interpolation_1.NR() == 1 );
      REQUIRE( interpolation_1.N2() == 4 );

    }

    WHEN( "constructed with incorrect 'tail' values" ){
      auto begin = interpolation.begin();
      auto end = interpolation.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, 9328, MF, MT ) );
      REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, 17, MT ) );
      REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, 15 ) );
    }

    SECTION( "print" ){
      auto begin = interpolation.begin();
      auto end = interpolation.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      std::string buffer;
      auto output = std::back_inserter( buffer );

      const auto base = InterpolationBase( begin, end, lineNumber, MAT, MF, MT );
      base.print( output, MAT, MF, MT );

      REQUIRE( buffer == interpolation );
    }

    SECTION( "NC" ){
      auto begin = interpolation.begin();
      auto end = interpolation.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      std::string buffer;

      const auto base = InterpolationBase( begin, end, lineNumber, MAT, MF, MT );
      REQUIRE( base.NC() == 2 );
    }
  }

  GIVEN( "Out of order region boundaries" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0          2          49228 1460  438\n"
      "          4          4          2          1                      9228 1460  439\n";
    auto begin = interpolation.begin();
    auto end = interpolation.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;

    REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Negative NR" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0         -1          49228 1460  438\n"
      "          2          4          4          1                      9228 1460  439\n";
    auto begin = interpolation.begin();
    auto end = interpolation.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;

    REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Negative NZ value" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0          1         -19228 1460  438\n"
      "          4          4                                            9228 1460  439\n";
    auto begin = interpolation.begin();
    auto end = interpolation.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;

    REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Zero NR" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0          0          49228 1460  438\n"
      "          2          4          4          1                      9228 1460  439\n";
    auto begin = interpolation.begin();
    auto end = interpolation.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;

    REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Zero NZ" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0          1          09228 1460  438\n"
      "          4          4                                            9228 1460  439\n";
    auto begin = interpolation.begin();
    auto end = interpolation.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;

    REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Inconsistent NZ" ){
    std::string interpolation =
      " 0.000000+0 0.000000+0         33          0          1          39228 1460  438\n"
      "          4          4                                            9228 1460  439\n";
    auto begin = interpolation.begin();
    auto end = interpolation.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;

    REQUIRE_THROWS( InterpolationBase( begin, end, lineNumber, MAT, MF, MT ) );
  }
}
