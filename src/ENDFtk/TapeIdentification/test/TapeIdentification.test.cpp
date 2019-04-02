#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing TapeIdentification",
          "[ENDFtk], [TapeIdentification]"){
  GIVEN( "valid tape IDs" ){
    std::string ID{" $Rev:: 1056     $  $Date:: 2017-01-26#$                             1 0  0     \n"};

    THEN( "a TapeIdentification can be created" ){
      long lineNumber{0};
      auto begin = ID.begin();
      auto end = ID.end();

      TapeIdentification TPID( begin, end, lineNumber );

      REQUIRE( ID.substr(0, 66) == TPID.text() );
      REQUIRE( 1 == TPID.tapeNumber() );
      REQUIRE( 1 == TPID.NTAPE() );
      REQUIRE( 1 == TPID.NC() );
    }


    THEN( "a TapeIdentification can be printed" ){

      long lineNumber{0};
      auto begin = ID.begin();
      auto end = ID.end();
      TapeIdentification TPID( begin, end, lineNumber );

      std::string buffer;
      auto output = std::back_inserter( buffer );
      TPID.print( output, 1, 0, 0 );
      REQUIRE( buffer == ID );
    }
  }

  GIVEN( "invalid tape IDs" ){
    std::string ID{" $Rev:: 1056     $  $Date:: 2017-01-26#$                            -1 1  0     \n"};

    THEN( "an exception is thrown" ){
      long lineNumber{0};
      auto begin = ID.begin();
      auto end = ID.end();

      REQUIRE_THROWS( TapeIdentification( begin, end, lineNumber ) );
    }
  }
}
