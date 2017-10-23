#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::function< InterpolationRecord() > makeTAB2 = [](){
  auto metadata = std::make_tuple( 1.0, 2.0, 3ul, 4ul );
  auto regionPairs = std::make_tuple( std::vector< long >{ 4, 5, 6 },
                                      std::vector< long >{ 1, 2, 3 } );
  
  return InterpolationRecord
  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
    njoy::utility::copy( regionPairs ) );
};

SCENARIO( "InterpolationRecord ctor",
          "[ENDFtk], [InterpolationRecord]" ){

  std::vector< long > regions{ 4, 5, 6 };
  std::vector< long > interpolation{ 1, 2, 3 };

  GIVEN( "a TAB2 object" ){
    InterpolationRecord tab2( 1.0, 2.0, 3ul, 4ul,
                              std::move( regions ),
                              std::move( interpolation ) );

    THEN( "TAB2 objects can be copied" ) {
      auto copy = tab2;
      REQUIRE( copy == tab2 );
    }
  }

  GIVEN( "mismatched region and interpolation arrays" ){
    std::vector< long > interpolation{ 1, 2, 3, 4 };

    REQUIRE_THROWS( InterpolationRecord
                    ( 1.0, 2.0, 3ul, 4ul,
                      std::make_tuple( regions, interpolation ) ) );
  }

  GIVEN( "out of order region" ){
    std::vector< long > regions{ 5, 4, 6 };

    REQUIRE_THROWS( InterpolationRecord
                    ( 1.0, 2.0, 3ul, 4ul,
                      std::make_tuple( regions, interpolation ) ) );
  }

  GIVEN( "single region TAB2" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          1          49228 1460  438\n"
      "          4          4                                            9228 1460  439\n";
    
    WHEN( "constructed with correct 'tail' values" ){
      auto begin = tab2.begin();
      auto end = tab2.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;
    
      InterpolationRecord tab2_1( begin, end, lineNumber, MAT, MF, MT );
      REQUIRE( tab2_1.NR() == 1 );
      REQUIRE( tab2_1.NZ() == 4 );

    } 
    
    WHEN( "constructed with incorrect 'tail' values" ){
      auto begin = tab2.begin();
      auto end = tab2.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;

      REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, 9328, MF, MT ) );
      REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, 17, MT ) );
      REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, 15 ) );
    }
  }

  GIVEN( "single region TAB2 with incorrect tail values" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          1          49328 1460  438\n"
      "          4          4                                            9228 1460  439\n";

    WHEN( "constructed with incorrect 'tail' values" ){
      auto begin = tab2.begin();
      auto end = tab2.end();
      auto lineNumber = 438l;
      int MAT = 9228;
      int MF = 1;
      int MT = 460;
            
      REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
    }
  }

  GIVEN( "Out of order region boundaries" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          2          49228 1460  438\n"
      "          4          4          2          1                      9228 1460  439\n";
    auto begin = tab2.begin();
    auto end = tab2.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
 
    REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
  }
  
  GIVEN( "Negative NR" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0         -1          49228 1460  438\n"
      "          2          4          4          1                      9228 1460  439\n";
    auto begin = tab2.begin();
    auto end = tab2.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
  }
  
  GIVEN( "Negative NZ value" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          1         -19228 1460  438\n"
      "          4          4                                            9228 1460  439\n";
    auto begin = tab2.begin();
    auto end = tab2.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
  }
  
  GIVEN( "Zero NR" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          0          49228 1460  438\n"
      "          2          4          4          1                      9228 1460  439\n";
    auto begin = tab2.begin();
    auto end = tab2.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Zero NZ" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          1          09228 1460  438\n"
      "          4          4                                            9228 1460  439\n";
    auto begin = tab2.begin();
    auto end = tab2.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
  }

  GIVEN( "Inconsistent NZ" ){
    std::string tab2 =
      " 0.000000+0 0.000000+0         33          0          1          39228 1460  438\n"
      "          3          4                                            9228 1460  439\n";
    auto begin = tab2.begin();
    auto end = tab2.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS( InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ) );
  }
}
