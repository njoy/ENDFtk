#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "StructureDivision Tests", "[ENDFtk], [StructureDivision]" ){
  THEN("The end record generators work"){
    REQUIRE_THROWS( SEND( 0, 1) );
    REQUIRE_THROWS( SEND( 1, 0) );
    REQUIRE_NOTHROW( SEND( 1, 1) );
    REQUIRE_NOTHROW( SEND( 125, 2) );
    REQUIRE_THROWS( FEND( -2 ) );
    REQUIRE_THROWS( FEND( 0 ) );
    REQUIRE_NOTHROW( FEND( 1 ) );
    REQUIRE_NOTHROW( FEND( 125 ) );
    REQUIRE_NOTHROW( MEND() );
    REQUIRE_NOTHROW( TEND() );
  
    REQUIRE( SEND( 1, 1 ).isSend() );
    REQUIRE( not SEND( 1, 1 ).isHead() );
    REQUIRE( not SEND( 1, 1 ).isFend() );
    REQUIRE( not SEND( 1, 1 ).isMend() );
    REQUIRE( not SEND( 1, 1 ).isTend() );
    
    REQUIRE( FEND( 1 ).isFend() );
    REQUIRE( not FEND( 1 ).isHead() );
    REQUIRE( not FEND( 1 ).isSend() );
    REQUIRE( not FEND( 1 ).isMend() );
    REQUIRE( not FEND( 1 ).isTend() );

    REQUIRE( MEND().isMend() );
    REQUIRE( not MEND().isHead() );
    REQUIRE( not MEND().isSend() );
    REQUIRE( not MEND().isFend() );
    REQUIRE( not MEND().isTend() );
    
    REQUIRE( TEND().isTend() );
    REQUIRE( not TEND().isHead() );
    REQUIRE( not TEND().isSend() );
    REQUIRE( not TEND().isFend() );
    REQUIRE( not TEND().isMend() );
  }

  GIVEN( "a head record string"){
    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          5 125 1451    1";
    WHEN("passed to the parsing ctor"){
      THEN("the structure division will be built correctly"){
        auto lineNumber = 0l;
        auto it = line.begin() + 1;
        auto end = line.end();
        REQUIRE_NOTHROW( StructureDivision( it, end, lineNumber ) );
      }
      auto lineNumber = 0l;
      auto it = line.begin() + 1;
      auto end = line.end();
      auto record = StructureDivision( it, end, lineNumber );
      THEN("the record will not be an end record"){
        REQUIRE( not record.isSend() );
        REQUIRE( not record.isFend() );
        REQUIRE( not record.isMend() );
        REQUIRE( not record.isTend() );
      }
      THEN("the record will be a head record"){
        REQUIRE( record.isHead() );
      }
    }
  }
  
  GIVEN( "a head record string with an illegal MAT"){
    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          0  -2 1451    1";
    THEN("the ctor will throw"){
        auto lineNumber = 0l;
        auto it = line.begin() + 1;
        auto end = line.end();
        REQUIRE_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }
  GIVEN( "a head record string with an illegal MF"){
    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          0 125-1451    1";
    THEN("the ctor will throw"){
        auto lineNumber = 0l;
        auto it = line.begin() + 1;
        auto end = line.end();
        REQUIRE_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }
  GIVEN( "a head record string with an illegal MT"){
    std::string line =
      "\n 1.001000+3 9.991673-1          0          0          0          0 125 1 -1    1";
    THEN("the ctor will throw"){
        auto lineNumber = 0l;
        auto it = line.begin() + 1;
        auto end = line.end();
        REQUIRE_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }

  GIVEN( "a valid instance of a head record" ) {
    std::string string = 
    " 1.001000+3 9.991673-1          0          0          0          5 125 1451     \n";
    auto lineNumber = 0l;
    auto it = string.begin();
    auto end = string.end();
    auto record = StructureDivision( it, end, lineNumber );
    THEN( "the head record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      REQUIRE( buffer == string );
    }
  }
  GIVEN( "a valid instance of a SEND record" ) {
    std::string string = 
    "                                                                   125 1  0     \n";
    auto record = SEND( 125, 1 );
    THEN( "the SEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      REQUIRE( buffer == string );
    }
  }
  GIVEN( "a valid instance of a FEND record" ) {
    std::string string = 
    "                                                                   125 0  0     \n";
    auto record = FEND( 125 );
    THEN( "the SEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      REQUIRE( buffer == string );
    }
  }
  GIVEN( "a valid instance of a MEND record" ) {
    std::string string = 
    "                                                                     0 0  0     \n";
    auto record = MEND();
    THEN( "the MEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      REQUIRE( buffer == string );
    }
  }
  GIVEN( "a valid instance of a TEND record" ) {
    std::string string = 
    "                                                                    -1 0  0     \n";
    auto record = TEND();
    THEN( "the TEND record can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      record.print( output );
      REQUIRE( buffer == string );
    }
  }
}
