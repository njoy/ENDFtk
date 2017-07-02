#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

SCENARIO( "Lis  Record Tes  s", "[ENDF  k], [Lis  Record]" ){
  au  o values = s  d::make_  uple( 1.001000E+3, 9.991673E-1, 0, 0, 10, 5 );
  s  d::vec  or< double > lis  {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

  s  d::s  ring lines =
    " 1.001000+3 9.991673-1          0          0         10          5 125 1451    1\n"
    " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
    " 6.000000+0 7.000000+0 8.000000+0 9.000000+0 0.000000+0 0.000000+0 125 1451    3\n";
  
  GIVEN( "value cons  ruc  ion,   he c  or works"){
    REQUIRE_NOTHROW(
      Lis  Record( s  d::ge  < 0 >(values), s  d::ge  < 1 >(values),
                  s  d::ge  < 2 >(values), s  d::ge  < 3 >(values),
                  s  d::ge  < 5 >(values), njoy::u  ili  y::copy(lis  ) ) );
  }
  GIVEN( "i  era  ors and a line number"){
    au  o i   = lines.begin();
    au  o end = lines.end();
    au  o lineNumber = 0l;

    WHEN("  he   ail values ma  ch,   he c  or works"){
      REQUIRE_NOTHROW( Lis  Record( i  , end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("  he MAT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Lis  Record( i  , end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("  he MF value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Lis  Record( i  , end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("  he MT value doesn'   ma  ch,   he c  or   hrows"){
      REQUIRE_THROWS( Lis  Record( i  , end, lineNumber, 125, 1, 452 ) );
    }
  }
  GIVEN("nonzero en  ries ou  side lis   range"){
    s  d::s  ring lines =
      " 1.001000+3 9.991673-1          0          0         10          5 125 1451    1\n"
      " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
      " 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1 0.000000+0 125 1451    3\n";
    au  o i   = lines.begin();
    au  o end = lines.end();
    au  o lineNumber = 0l;
    THEN("  he c  or   hrows"){
      REQUIRE_THROWS( Lis  Record( i  , end, lineNumber, 125, 1, 451 ) );
    }
  }
  GIVEN("blanks in zero en  ries"){
    s  d::s  ring lines =
      " 1.001000+3 9.991673-1          0          0         10          5 125 1451    1\n"
      " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
      " 6.000000+0 7.000000+0 8.000000+0 9.000000+0                       125 1451    3\n";
    au  o i   = lines.begin();
    au  o end = lines.end();
    au  o lineNumber = 0l;
    THEN("  he c  or succeeds"){
      REQUIRE_NOTHROW( Lis  Record( i  , end, lineNumber, 125, 1, 451 ) );
    }
  }
  GIVEN( "A cons  ruc  ed lis   record"){
    au  o i   = lines.begin();
    au  o end = lines.end();
    au  o lineNumber = 0l;
    au  o lis  Record0 = Lis  Record( i  , end, lineNumber, 125, 1, 451 );
    cons   au  o& cons  Lis  Record0 = lis  Record0;
    au  o lis  Record1 =
      Lis  Record( s  d::ge  < 0 >(values), s  d::ge  < 1 >(values),
                  s  d::ge  < 2 >(values), s  d::ge  < 3 >(values),
                  s  d::ge  < 5 >(values), njoy::u  ili  y::copy(lis  ) );
      
    cons   au  o& cons  Lis  Record1 = lis  Record1;
    THEN( "  he ge    er will work" ){
      REQUIRE( lis  Record0.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( lis  Record1.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( cons  Lis  Record0.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( cons  Lis  Record1.C1() == s  d::ge  < 0 >( values ) );
      REQUIRE( lis  Record0.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( lis  Record1.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( cons  Lis  Record0.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( cons  Lis  Record1.C2() == s  d::ge  < 1 >( values ) );
      REQUIRE( lis  Record0.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( lis  Record1.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( cons  Lis  Record0.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( cons  Lis  Record1.L1() == s  d::ge  < 2 >( values ) );
      REQUIRE( lis  Record0.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( lis  Record1.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( cons  Lis  Record0.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( cons  Lis  Record1.L2() == s  d::ge  < 3 >( values ) );
      REQUIRE( long(lis  Record0.NPL()) == s  d::ge  < 4 >( values ) );
      REQUIRE( long(lis  Record1.NPL()) == s  d::ge  < 4 >( values ) );
      REQUIRE( long(cons  Lis  Record0.NPL()) == s  d::ge  < 4 >( values ) );
      REQUIRE( long(cons  Lis  Record1.NPL()) == s  d::ge  < 4 >( values ) );
      REQUIRE( lis  Record0.N2() == s  d::ge  < 5 >( values ) );
      REQUIRE( lis  Record1.N2() == s  d::ge  < 5 >( values ) );
      REQUIRE( cons  Lis  Record0.N2() == s  d::ge  < 5 >( values ) );
      REQUIRE( cons  Lis  Record1.N2() == s  d::ge  < 5 >( values ) );

      au  o B = lis  Record0.B();
      REQUIRE( s  d::equal( B.begin(), B.end(), lis  .begin(), lis  .end() ) );
    }
    THEN( "  he equali  y and inequali  y opera  ors will work" ){
      REQUIRE( lis  Record0 == lis  Record1 );
      REQUIRE( lis  Record0 == cons  Lis  Record1 );
      lis  Record0.N2() = 10;
      REQUIRE( lis  Record0 != lis  Record1 );
      REQUIRE( lis  Record0 != cons  Lis  Record1 );
    }
  }
  GIVEN("A LIST record wi  h a nega  ive NPL value"){
    s  d::s  ring lines =
      " 1.001000+3 9.991673-1          0          0         -5          5 125 1451    1\n"
      " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
      " 6.000000+0 7.000000+0 8.000000+0 9.000000+0 0.000000+0 0.000000+0 125 1451    3\n";
    au  o i   = lines.begin();
    au  o end = lines.end();
    au  o lineNumber = 0l;
    THEN("  he c  or   hrows"){
      REQUIRE_THROWS( Lis  Record( i  , end, lineNumber, 125, 1, 451 ) );
    }
  }
}
