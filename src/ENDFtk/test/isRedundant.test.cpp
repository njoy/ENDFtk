
#include "catch.hpp"
#include "ENDFtk.hpp"

SCENARIO( "Testing if MT number is a redundant ENDF reaction" ){
  const std::vector< int > redundantMTs{
    1, 3, 4, 16, 18, 27, 101, 103, 104, 105, 106, 107
  };
  GIVEN( "redundant MT numbers" ){
    for( auto MT : redundantMTs ){
      THEN( "isRedundant returns true for MT=" + std::to_string( MT ) ){
        CHECK( njoy::ENDFtk::isRedundant( MT ) );
      } // THEN
    }
  } // GIVEN

  GIVEN( "non-redundant MTs" ){
    auto nonRedundantMTs = ranges::view::iota( 1, 999 )
      | ranges::view::remove_if( 
        [&](int MT ){ return ranges::binary_search( redundantMTs, MT ); } );

    for( auto MT : nonRedundantMTs ){
      THEN( "isRedundant returns false for MT=" + std::to_string( MT ) ){
        CHECK( not njoy::ENDFtk::isRedundant( MT ) );
      } // THEN
    }
    
  } // GIVEN 
} // SCENARIO
