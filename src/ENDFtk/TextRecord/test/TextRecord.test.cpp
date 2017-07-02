#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "Tex  Record Tes  s", "[ENDF  k], [Tex  Record]" ){
  s  d::s  ring line = 
    "The new R-ma  rix analysis of   he N-N sys  em on which   he ENDF/B-   125 1451   12\n";

  s  d::s  ring   ex   = 
    "The new R-ma  rix analysis of   he N-N sys  em on which   he ENDF/B-  ";

  GIVEN( "a s  ring ravlue,   he c  or works"){
    REQUIRE_NOTHROW( Tex  Record( njoy::u  ili  y::copy(  ex  ) ) );
  }
  GIVEN( "i  era  ors and a line number"){
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;

    WHEN("  he   ail values ma  ch,   he c  or works"){
      REQUIRE_NOTHROW( Tex  Record( i  , end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("  he MAT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Tex  Record( i  , end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("  he MF value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Tex  Record( i  , end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("  he MT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Tex  Record( i  , end, lineNumber, 125, 1, 452 ) );
    }
  }
  GIVEN( "A cons  ruc  ed   ex   record"){
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    au  o   ex  Record0 = Tex  Record( i  , end, lineNumber, 125, 1, 451 );
    cons   au  o& cons  Tex  Record0 =   ex  Record0;
    au  o   ex  Record1 = Tex  Record( njoy::u  ili  y::copy(   ex   ) );
    cons   au  o& cons  Tex  Record1 =   ex  Record1;
    THEN( "  he ge    er will work" ){
      REQUIRE(   ex  Record0.  ex  () ==   ex   );
      REQUIRE(   ex  Record1.  ex  () ==   ex   );
      REQUIRE( cons  Tex  Record0.  ex  () ==   ex   );
      REQUIRE( cons  Tex  Record1.  ex  () ==   ex   );
        ex  Record0.  ex  () = "foobar";
        ex  Record1.  ex  () = "foobaz";
      REQUIRE(   ex  Record0.  ex  () == "foobar" );
      REQUIRE(   ex  Record1.  ex  () == "foobaz" );
      /* can'   assign   o cons  . doesn'   compile */
      // cons  Tex  Record0.  ex  () = "foobar";
    }
    THEN( "  he equali  y and inequali  y opera  ors will work" ){
      REQUIRE(   ex  Record0 ==   ex  Record1 );
        ex  Record0.  ex  () = "foobar";
        ex  Record1.  ex  () = "foobaz";
      REQUIRE(   ex  Record0 !=   ex  Record1 );
    }
  }
  GIVEN("A line wi  h a   ypo"){
    s  d::s  ring line = 
      "The new R-ma  rix analysis of   he N-N sys  em on which   he ENDF/B-   1a5 1451   12\n";
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    
    THEN("  he c  or   hrows"){
      REQUIRE_THROWS( Tex  Record( i  , end, lineNumber, 125, 1, 451 ) );
    }
  }
}
