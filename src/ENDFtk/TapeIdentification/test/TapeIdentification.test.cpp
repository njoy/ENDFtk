#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing TapeIdentification",
          "[ENDFtk], [TapeIdentification]"){
  GIVEN( "valid tape IDs" ){
    std::string ID{" $Rev:: 1056     $  $Date:: 2017-01-26#$                             1 0  0     "};

    THEN( "a TapeIdentification can be created" ){
      long lineNumber{0};
      auto begin = ID.begin();
      auto end = ID.end();

      TapeIdentification TPID( begin, end, lineNumber );

      REQUIRE( ID.substr(0, 66) == TPID.text() );
      REQUIRE( 1 == TPID.tapeNumber() );
    }
  }

  GIVEN( "invalid tape IDs" ){
    std::string ID{" $Rev:: 1056     $  $Date:: 2017-01-26#$                            -1 0  0     "};

    THEN( "an exception is thrown" ){
      long lineNumber{0};
      auto begin = ID.begin();
      auto end = ID.end();

      // REQUIRE_THROWS( TapeIdentification( begin, end, lineNumber ) );
    }
  }
}
