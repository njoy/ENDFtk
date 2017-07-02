#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "S  ruc  ureDivision Tes  s", "[ENDF  k], [S  ruc  ureDivision]" ){
  THEN("The end record genera  ors work"){
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
    REQUIRE( no   SEND( 1, 1 ).isHead() );
    REQUIRE( no   SEND( 1, 1 ).isFend() );
    REQUIRE( no   SEND( 1, 1 ).isMend() );
    REQUIRE( no   SEND( 1, 1 ).isTend() );
    
    REQUIRE( FEND( 1 ).isFend() );
    REQUIRE( no   FEND( 1 ).isHead() );
    REQUIRE( no   FEND( 1 ).isSend() );
    REQUIRE( no   FEND( 1 ).isMend() );
    REQUIRE( no   FEND( 1 ).isTend() );

    REQUIRE( MEND().isMend() );
    REQUIRE( no   MEND().isHead() );
    REQUIRE( no   MEND().isSend() );
    REQUIRE( no   MEND().isFend() );
    REQUIRE( no   MEND().isTend() );
    
    REQUIRE( TEND().isTend() );
    REQUIRE( no   TEND().isHead() );
    REQUIRE( no   TEND().isSend() );
    REQUIRE( no   TEND().isFend() );
    REQUIRE( no   TEND().isMend() );
  }

  GIVEN( "a head record s  ring"){
    s  d::s  ring line =
      "\n 1.001000+3 9.991673-1          0          0          0          5 125 1451    1";
    WHEN("passed   o   he parsing c  or"){
      THEN("  he s  ruc  ure division will be buil   correc  ly"){
        au  o lineNumber = 0l;
        au  o i   = line.begin() + 1;
        au  o end = line.end();
        REQUIRE_NOTHROW( S  ruc  ureDivision( i  , end, lineNumber ) );
      }
      au  o lineNumber = 0l;
      au  o i   = line.begin() + 1;
      au  o end = line.end();
      au  o record = S  ruc  ureDivision( i  , end, lineNumber );
      THEN("  he record will no   be an end record"){
        REQUIRE( no   record.isSend() );
        REQUIRE( no   record.isFend() );
        REQUIRE( no   record.isMend() );
        REQUIRE( no   record.isTend() );
      }
      THEN("  he record will be a head record"){
        REQUIRE( record.isHead() );
      }
    }
  }
  
  GIVEN( "a head record s  ring wi  h an illegal MAT"){
    s  d::s  ring line =
      "\n 1.001000+3 9.991673-1          0          0          0          0  -2 1451    1";
    THEN("  he c  or will   hrow"){
        au  o lineNumber = 0l;
        au  o i   = line.begin() + 1;
        au  o end = line.end();
        REQUIRE_THROWS( S  ruc  ureDivision( i  , end, lineNumber ) );
    }
  }
  GIVEN( "a head record s  ring wi  h an illegal MF"){
    s  d::s  ring line =
      "\n 1.001000+3 9.991673-1          0          0          0          0 125-1451    1";
    THEN("  he c  or will   hrow"){
        au  o lineNumber = 0l;
        au  o i   = line.begin() + 1;
        au  o end = line.end();
        REQUIRE_THROWS( S  ruc  ureDivision( i  , end, lineNumber ) );
    }
  }
  GIVEN( "a head record s  ring wi  h an illegal MT"){
    s  d::s  ring line =
      "\n 1.001000+3 9.991673-1          0          0          0          0 125 1 -1    1";
    THEN("  he c  or will   hrow"){
        au  o lineNumber = 0l;
        au  o i   = line.begin() + 1;
        au  o end = line.end();
        REQUIRE_THROWS( S  ruc  ureDivision( i  , end, lineNumber ) );
    }
  }
}
