#define CATCH_CONFIG_RUNNER

#include <string>

#include "catch.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "StructureDivision Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "StructureDivision Complete!";
  return result;
}

using namespace ENDFtk::implementation;

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
      " 1.001000+3 9.991673-1          0          0          0          5 125 1451    1";
    WHEN("passed to the parsing ctor"){
      THEN("the structure division will be built correctly"){
        auto lineNumber = 0l;
        auto it = line.begin();
        auto end = line.end();
        REQUIRE_NOTHROW( StructureDivision( it, end, lineNumber ) );
      }
      auto lineNumber = 0l;
      auto it = line.begin();
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
      " 1.001000+3 9.991673-1          0          0          0          0  -2 1451    1";
    THEN("the ctor will throw"){
        auto lineNumber = 0l;
        auto it = line.begin();
        auto end = line.end();
        REQUIRE_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }
  GIVEN( "a head record string with an illegal MF"){
    std::string line =
      " 1.001000+3 9.991673-1          0          0          0          0 125-1451    1";
    THEN("the ctor will throw"){
        auto lineNumber = 0l;
        auto it = line.begin();
        auto end = line.end();
        REQUIRE_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }
  GIVEN( "a head record string with an illegal MT"){
    std::string line =
      " 1.001000+3 9.991673-1          0          0          0          0 125 1 -1    1";
    THEN("the ctor will throw"){
        auto lineNumber = 0l;
        auto it = line.begin();
        auto end = line.end();
        REQUIRE_THROWS( StructureDivision( it, end, lineNumber ) );
    }
  }
}
