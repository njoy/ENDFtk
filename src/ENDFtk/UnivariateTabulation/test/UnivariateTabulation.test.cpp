#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::function< UnivariateTabulation() > makeTAB1 = [](){
  auto metadata = std::make_tuple( 1.0, 2.0, 3ul, 4ul );
  auto regionPairs =
  std::make_tuple( std::vector< long >{4,5,6}, std::vector< long >{1,2,3} );
  auto orderedPairs =
  std::make_tuple( std::vector< double >{1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
                   std::vector< double >{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );
  return UnivariateTabulation
  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
    njoy::utility::copy( regionPairs ), njoy::utility::copy( orderedPairs ) );
};

SCENARIO( "UnivariateTabulation ctor",
          "[ENDFtk], [UnivariateTabulation]" ){

  auto metadata = std::make_tuple( 1.0, 2.0, 3ul, 4ul );
  auto regionPairs =
    std::make_tuple( std::vector< long >{4,5,6}, std::vector< long >{1,2,3} );

  auto orderedPairs =
  std::make_tuple( std::vector< double >{1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
                   std::vector< double >{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );
  auto tab1_0 = UnivariateTabulation
  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
    njoy::utility::copy( regionPairs ), njoy::utility::copy( orderedPairs ) );
  
  auto mismatchedOrderedPairs =
    std::make_tuple( std::vector< double >{1.0, 2.0, 3.0, 4.0, 5.0},
                     std::vector< double >{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );

  REQUIRE_THROWS( UnivariateTabulation
                  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
                    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
                    njoy::utility::copy( regionPairs ),
                    njoy::utility::copy( mismatchedOrderedPairs ) ) );

  auto outOfOrderOrderedPairs =
    std::make_tuple( std::vector< double >{1.0, 3.0, 2.0, 4.0, 5.0},
                     std::vector< double >{3.0, 4.0, 5.0, 6.0, 7.0} );

  REQUIRE_THROWS( UnivariateTabulation
                  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
                    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
                    njoy::utility::copy( regionPairs ),
                    njoy::utility::copy( outOfOrderOrderedPairs ) ) );

  auto outOfOrderRegionPairs =
    std::make_tuple( std::vector< long >{5,4,6}, std::vector< long >{1,2,3} );

  REQUIRE_THROWS( UnivariateTabulation
                  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
                    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
                    njoy::utility::copy( outOfOrderRegionPairs ),
                    njoy::utility::copy( orderedPairs ) ) );
  
  auto mismatchedRegionPairs =
    std::make_tuple( std::vector< long >{4,5,6}, std::vector< long >{1,2,3,4} );

  REQUIRE_THROWS( UnivariateTabulation
                  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
                    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
                    njoy::utility::copy( mismatchedRegionPairs ),
                    njoy::utility::copy( orderedPairs ) ) );
  std::string tab1String = 
    " 0.000000+0 0.000000+0         33          0          1          49228 1460  438\n"
    "          4          4                                            9228 1460  439\n"
    " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.900000+1 1.975000+09228 1460  440\n"
    " 2.700000+1 1.605000+1                                            9228 1460  441\n";
  {  
    auto tab1It = tab1String.begin();
    auto tab1End = tab1String.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
    
    auto tab1_1 =
      UnivariateTabulation( tab1It, tab1End, lineNumber, MAT, MF, MT );
    REQUIRE( tab1_1.xValues.size() == 4 );
    REQUIRE( tab1_1.boundaryIndices.size() == 1 );
  }
  {
    auto tab1It = tab1String.begin();
    auto tab1End = tab1String.end();
    auto lineNumber = 438l;
    int MF = 1;
    int MT = 460;
    REQUIRE_THROWS(
      UnivariateTabulation( tab1It, tab1End, lineNumber, 9225, MF, MT ) );
  }
  {
    std::string tab1String = 
      " 0.000000+0 0.000000+0         33          0         -1          49228 1460  438\n"
      "          4          4                                            9228 1460  439\n"
      " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.900000+1 1.975000+09228 1460  440\n"
      " 2.700000+1 1.605000+1                                            9228 1460  441\n";
    auto tab1It = tab1String.begin();
    auto tab1End = tab1String.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS(
      UnivariateTabulation( tab1It, tab1End, lineNumber, MAT, MF, MT ) );
  }
  {
    std::string tab1String = 
      " 0.000000+0 0.000000+0         33          0          1         -19228 1460  438\n"
      "          4          4                                            9228 1460  439\n"
      " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.900000+1 1.975000+09228 1460  440\n"
      " 2.700000+1 1.605000+1                                            9228 1460  441\n";
    auto tab1It = tab1String.begin();
    auto tab1End = tab1String.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS(
      UnivariateTabulation( tab1It, tab1End, lineNumber, MAT, MF, MT ) );
  }
  {
    std::string tab1String = 
      " 0.000000+0 0.000000+0         33          0          1          49228 1460  438\n"
      "          4          4                                            9228 1460  439\n"
      " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
      " 2.700000+1 1.605000+1                                            9228 1460  441\n";
    auto tab1It = tab1String.begin();
    auto tab1End = tab1String.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS(
      UnivariateTabulation( tab1It, tab1End, lineNumber, MAT, MF, MT ) );
  }
  {
    std::string tab1String = 
      " 0.000000+0 0.000000+0         33          0          2          49228 1460  438\n"
      "          4          4          2          1                      9228 1460  439\n"
      " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
      " 2.700000+1 1.605000+1                                            9228 1460  441\n";
    auto tab1It = tab1String.begin();
    auto tab1End = tab1String.end();
    auto lineNumber = 438l;
    int MAT = 9228;
    int MF = 1;
    int MT = 460;
   
    REQUIRE_THROWS(
      UnivariateTabulation( tab1It, tab1End, lineNumber, MAT, MF, MT ) );
  }
}
