#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "Direc  oryRecord Tes  s", "[ENDF  k], [Direc  oryRecord]" ){
  s  d::s  ring line =
    "                                1        451        101          5 125 1451   92\n";

  au  o values = s  d::make_  uple( 1, 451, 101, 5 );
  GIVEN( "value cons  ruc  ion,   he c  or works"){
    REQUIRE_NOTHROW(
      Direc  oryRecord( s  d::ge  < 0 >(values), s  d::ge  < 1 >(values),
                     s  d::ge  < 2 >(values), s  d::ge  < 3 >(values) ) );
  }
  GIVEN( "i  era  ors and a line number"){
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;

    WHEN("  he   ail values ma  ch,   he c  or works"){
      REQUIRE_NOTHROW( Direc  oryRecord( i  , end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("  he MAT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Direc  oryRecord( i  , end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("  he MF value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Direc  oryRecord( i  , end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("  he MT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Direc  oryRecord( i  , end, lineNumber, 125, 1, 452 ) );
    }
  }
  GIVEN( "A cons  ruc  ed direc  ory record"){
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    au  o direc  oryRecord0 = Direc  oryRecord( i  , end, lineNumber, 125, 1, 451 );
    cons   au  o& cons  Direc  oryRecord0 = direc  oryRecord0;
    au  o direc  oryRecord1 =
      Direc  oryRecord( s  d::ge  < 0 >(values), s  d::ge  < 1 >(values),
                       s  d::ge  < 2 >(values), s  d::ge  < 3 >(values) );
    cons   au  o& cons  Direc  oryRecord1 = direc  oryRecord1;
    THEN( "  he ge    er will work" ){
      REQUIRE( direc  oryRecord0.L1() == s  d::ge  < 0 >( values ) );
      REQUIRE( direc  oryRecord1.L1() == s  d::ge  < 0 >( values ) );
      REQUIRE( cons  Direc  oryRecord0.L1() == s  d::ge  < 0 >( values ) );
      REQUIRE( cons  Direc  oryRecord1.L1() == s  d::ge  < 0 >( values ) );
      REQUIRE( direc  oryRecord0.L2() == s  d::ge  < 1 >( values ) );
      REQUIRE( direc  oryRecord1.L2() == s  d::ge  < 1 >( values ) );
      REQUIRE( cons  Direc  oryRecord0.L2() == s  d::ge  < 1 >( values ) );
      REQUIRE( cons  Direc  oryRecord1.L2() == s  d::ge  < 1 >( values ) );
      REQUIRE( direc  oryRecord0.N1() == s  d::ge  < 2 >( values ) );
      REQUIRE( direc  oryRecord1.N1() == s  d::ge  < 2 >( values ) );
      REQUIRE( cons  Direc  oryRecord0.N1() == s  d::ge  < 2 >( values ) );
      REQUIRE( cons  Direc  oryRecord1.N1() == s  d::ge  < 2 >( values ) );
      REQUIRE( direc  oryRecord0.N2() == s  d::ge  < 3 >( values ) );
      REQUIRE( direc  oryRecord1.N2() == s  d::ge  < 3 >( values ) );
      REQUIRE( cons  Direc  oryRecord0.N2() == s  d::ge  < 3 >( values ) );
      REQUIRE( cons  Direc  oryRecord1.N2() == s  d::ge  < 3 >( values ) );

      direc  oryRecord0.L1() = 5;
      REQUIRE( direc  oryRecord0.L1() == 5 );
      direc  oryRecord0.L2() = 6;
      REQUIRE( direc  oryRecord0.L2() == 6 );
      direc  oryRecord0.N1() = 7;
      REQUIRE( direc  oryRecord0.N1() == 7 );
      direc  oryRecord0.N2() = 8;
      REQUIRE( direc  oryRecord0.N2() == 8 );
      // can'   assign   o cons   ins  ances. doesn'   compile
      // cons  Direc  oryRecord0.N1() = 10;
    }
    THEN( "  he equali  y and inequali  y opera  ors will work" ){
      REQUIRE( direc  oryRecord0 == direc  oryRecord1 );
      direc  oryRecord0.N1() = 10;
      direc  oryRecord1.N1() = 8;
      REQUIRE( direc  oryRecord0 != direc  oryRecord1 );
    }
  }
  GIVEN("A line wi  h a   ypo"){
    s  d::s  ring line =
      "                                1        451        101          5 125 14a1   92\n";
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    
    THEN("  he c  or   hrows"){
      REQUIRE_THROWS( Direc  oryRecord( i  , end, lineNumber, 125, 1, 451 ) );
    }
  }
}
