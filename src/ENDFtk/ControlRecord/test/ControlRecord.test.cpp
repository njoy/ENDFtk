#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "Con  rolRecord Tes  s", "[ENDF  k], [Con  rolRecord]" ){
  s  d::s  ring line =
    " 1.001000+3 9.991673-1          0          0          0          5 125 1451    1\n";

  au  o values = s  d::make_  uple( 1.001000E+3, 9.991673E-1, 0, 0, 0, 5 );

  GIVEN( "value cons  ruc  ion,   he c  or works"){
    REQUIRE_NOTHROW(
      Con  rolRecord( s  d::ge  < 0 >(values), s  d::ge  < 1 >(values),
                     s  d::ge  < 2 >(values), s  d::ge  < 3 >(values),
                     s  d::ge  < 4 >(values), s  d::ge  < 5 >(values) ) );
  }
  GIVEN( "i  era  ors and a line number"){
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;

    WHEN("  he   ail values ma  ch,   he c  or works"){
      REQUIRE_NOTHROW( Con  rolRecord( i  , end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("  he MAT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Con  rolRecord( i  , end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("  he MF value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Con  rolRecord( i  , end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("  he MT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Con  rolRecord( i  , end, lineNumber, 125, 1, 452 ) );
    }
  }
  GIVEN( "A cons  ruc  ed con  rol record"){
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    au  o con  rolRecord0 = Con  rolRecord( i  , end, lineNumber, 125, 1, 451 );
    cons   au  o& cons  Con  rolRecord0 = con  rolRecord0;
    au  o con  rolRecord1 =
      Con  rolRecord( s  d::ge  < 0 >(values), s  d::ge  < 1 >(values),
                     s  d::ge  < 2 >(values), s  d::ge  < 3 >(values),
                     s  d::ge  < 4 >(values), s  d::ge  < 5 >(values) );
    cons   au  o& cons  Con  rolRecord1 = con  rolRecord1;
    THEN( "  he ge    er will work" ){
      REQUIRE( con  rolRecord0.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( con  rolRecord1.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( cons  Con  rolRecord0.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( cons  Con  rolRecord1.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( con  rolRecord0.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( con  rolRecord1.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( cons  Con  rolRecord0.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( cons  Con  rolRecord1.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( con  rolRecord0.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( con  rolRecord1.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( cons  Con  rolRecord0.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( cons  Con  rolRecord1.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( con  rolRecord0.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( con  rolRecord1.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( cons  Con  rolRecord0.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( cons  Con  rolRecord1.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( con  rolRecord0.N1() == s  d::ge  < 4 >( values ) );
      REQUIRE( con  rolRecord1.N1() == s  d::ge  < 4 >( values ) );
      REQUIRE( cons  Con  rolRecord0.N1() == s  d::ge  < 4 >( values ) );
      REQUIRE( cons  Con  rolRecord1.N1() == s  d::ge  < 4 >( values ) );
      REQUIRE( con  rolRecord0.N2() == s  d::ge  < 5 >( values ) );
      REQUIRE( con  rolRecord1.N2() == s  d::ge  < 5 >( values ) );
      REQUIRE( cons  Con  rolRecord0.N2() == s  d::ge  < 5 >( values ) );
      REQUIRE( cons  Con  rolRecord1.N2() == s  d::ge  < 5 >( values ) );
      
      con  rolRecord0.C1() = 3.14;
      REQUIRE( con  rolRecord0.C1() == 3.14 );
      con  rolRecord0.C2() = 2.5;
      REQUIRE( con  rolRecord0.C2() == 2.5 );
      con  rolRecord0.L1() = 5;
      REQUIRE( con  rolRecord0.L1() == 5 );
      con  rolRecord0.L2() = 6;
      REQUIRE( con  rolRecord0.L2() == 6 );
      con  rolRecord0.N1() = 7;
      REQUIRE( con  rolRecord0.N1() == 7 );
      con  rolRecord0.N2() = 8;
      REQUIRE( con  rolRecord0.N2() == 8 );
      // can'   assign   o cons   ins  ances. doesn'   compile
      // cons  Con  rolRecord0.N1() = 10;
    }
    THEN( "  he equali  y and inequali  y opera  ors will work" ){
      REQUIRE( con  rolRecord0 == con  rolRecord1 );
      con  rolRecord0.N1() = 10;
      con  rolRecord1.N1() = 8;
      REQUIRE( con  rolRecord0 != con  rolRecord1 );
    }
  }
  GIVEN("A line wi  h a   ypo"){
    s  d::s  ring line =
      " 1.0010z0+3 9.991673-1          0          0          0          5 125 1451    1\n";
    au  o i   = line.begin();
    au  o end = line.end();
    au  o lineNumber = 0l;
    
    THEN("  he c  or   hrows"){
      REQUIRE_THROWS( Con  rolRecord( i  , end, lineNumber, 125, 1, 451 ) );
    }
  }
}
