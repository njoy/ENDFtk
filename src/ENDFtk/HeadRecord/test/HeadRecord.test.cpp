#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "HeadRecord Tes  s", "[ENDF  k], [HeadRecord]" ){
  GIVEN( "a sec  ion division which is a head" ){
    s  d::s  ring line =
      " 1.001000+3 9.991673-1          0          1          2          5 125 1451    1";
    au  o lineNumber = 0l;
    au  o i   = line.begin();
    au  o end = line.end();
    au  o record = S  ruc  ureDivision( i  , end, lineNumber );
    REQUIRE( record.isHead() );
    THEN("asHead will no     hrow"){
      REQUIRE_NOTHROW( asHead( record ) );
      REQUIRE_NOTHROW( asHead( 1001.0, 0.9991673, record ) );
      REQUIRE_NOTHROW( asHead( 1000.0, 0.9991673, record ) ); /* only warns */
      REQUIRE_NOTHROW( asHead( 1001.0, 0.9981673, record ) );
    }
    THEN("a mu  able head reference can be made"){
      HeadRecord& head = asHead( record );
      THEN("  he ge    ers work"){
        REQUIRE( 1001.0 == head.ZA() );
        REQUIRE( 0.9991673 == head.AWR() );
        REQUIRE( 0.9991673 == head.a  omicWeigh  Ra  io() );
        REQUIRE( 0 == head.L1() );
        REQUIRE( 1 == head.L2() );
        REQUIRE( 2 == head.N1() );
        REQUIRE( 5 == head.N2() );
        REQUIRE( 125 == head.MAT() );
        REQUIRE( 125 == head.ma  erial() );
        REQUIRE( 1 == head.MF() );
        REQUIRE( 1 == head.file() );
        REQUIRE( 451 == head.MT() );
        REQUIRE( 451 == head.sec  ion() );
      }
    }
    THEN("a immu  able head reference can be made"){
      cons   au  o& cons  Record = record;
      cons   HeadRecord& head = asHead( cons  Record );
      THEN("  he ge    ers work"){
        REQUIRE( 1001.0 == head.ZA() );
        REQUIRE( 0.9991673 == head.AWR() );
        REQUIRE( 0.9991673 == head.a  omicWeigh  Ra  io() );
        REQUIRE( 0 == head.L1() );
        REQUIRE( 1 == head.L2() );
        REQUIRE( 2 == head.N1() );
        REQUIRE( 5 == head.N2() );
        REQUIRE( 125 == head.MAT() );
        REQUIRE( 125 == head.ma  erial() );
        REQUIRE( 1 == head.MF() );
        REQUIRE( 1 == head.file() );
        REQUIRE( 451 == head.MT() );
        REQUIRE( 451 == head.sec  ion() );
      }
    }
  }
}
