#define CATCH_CONFIG_RUNNER

#include <string>

#include "catch.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "UnivariateTabulation Tests";
  LOG(INFO) << "======================";  
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "UnivariateTabulation Complete!";
  return result;
}

using namespace ENDFtk::implementation;

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
    utility::copy( regionPairs ), utility::copy( orderedPairs ) );
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
    utility::copy( regionPairs ), utility::copy( orderedPairs ) );

  auto mismatchedOrderedPairs =
    std::make_tuple( std::vector< double >{1.0, 2.0, 3.0, 4.0, 5.0},
                     std::vector< double >{3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );

  REQUIRE_THROWS( UnivariateTabulation
                  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
                    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
                    utility::copy( regionPairs ),
                    utility::copy( mismatchedOrderedPairs ) ) );

  auto mismatchedRegionPairs =
    std::make_tuple( std::vector< long >{4,5,6}, std::vector< long >{1,2,3,4} );

  REQUIRE_THROWS( UnivariateTabulation
                  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
                    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
                    utility::copy( mismatchedRegionPairs ),
                    utility::copy( orderedPairs ) ) );
  
  std::string tab1String = 
    " 0.000000+0 0.000000+0         33          0          1          49228 1460  438\n"
    "          4          4                                            9228 1460  439\n"
    " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.900000+1 1.975000+09228 1460  440\n"
    " 2.700000+1 1.605000+1                                            9228 1460  441\n";
  auto tab1It = tab1String.begin();
  auto tab1End = tab1String.end();
  auto lineNumber = 438l;
  int MAT = 9228;
  int MF = 1;
  int MT = 460;
  
  auto tab1_1 =
    UnivariateTabulation( tab1It, tab1End, lineNumber, MAT, MF, MT );

  REQUIRE_THROWS(
    UnivariateTabulation( tab1It, tab1End, lineNumber, 9225, MF, MT ) );
  
  REQUIRE( tab1_1.xValues.size() == 4 );
  REQUIRE( tab1_1.boundaryIndices.size() == 1 );
}
