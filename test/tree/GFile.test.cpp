// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/tree/GFile.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

SCENARIO( "tree::GFile" ) {

  GIVEN( "an empty tree::GFile" ) {

    WHEN( "it is created" ) {

      tree::GFile file( 9228, 3 );

      THEN( "it is empty except for the MAT and MF" ) {

        CHECK( 9228 == file.MAT() );
        CHECK( 9228 == file.materialNumber() );
        CHECK( 3 == file.MF() );
        CHECK( 3 == file.fileNumber() );

        auto sectionNumbers = file.sectionNumbers();
        CHECK( 0 == file.size() );
        CHECK( 0 == sectionNumbers.size() );

        CHECK( "" == file.content() );
      }
    } // WHEN
  } // GIVEN
} // SCENARIO
