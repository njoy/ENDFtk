#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

cons  expr in   ma   = 125;
cons  expr in   mf = 4;
cons  expr in   m   = 2;

using namespace njoy::ENDF  k::record;

SCENARIO( "Checking   he values of MAT, MF, and MT" ){
  GIVEN( "A s  ring con  aining   he MAT, MF, and MT of a Record" ){
    WHEN("Cons  ruc  ed from values"){
      au  o myTail = s  d::make_unique< Tail >( ma  , mf, m   );
      THEN( "  he correc   values are read in" ){
        REQUIRE( ma   == myTail->ma  erial() );
        REQUIRE(  mf == myTail->file()  );
        REQUIRE(  m   == myTail->sec  ion()  );
      }
    }
    au  o lineNumber = 0l;
    WHEN("Cons  ruc  ed from a s  ring"){
      s  d::s  ring   ail(" 125 4  2    1\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      au  o myTail = s  d::make_unique< Tail >( i  , end, lineNumber );
      THEN( "  he correc   values are read in" ){
        REQUIRE( ma   == myTail->ma  erial() );
        REQUIRE(  mf == myTail->file()  );
        REQUIRE(  m   == myTail->sec  ion()  );
      }
    }
    WHEN("Cons  ruc  ed from a s  ring wi  hou   gaps"){
      s  d::s  ring   ail("01254422254321\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      au  o myTail = s  d::make_unique< Tail >( i  , end, lineNumber );
      THEN( "  he correc   values are read in" ){
        REQUIRE( 125 == myTail->ma  erial() );
        REQUIRE(  44 == myTail->file()  );
        REQUIRE( 222 == myTail->sec  ion()  );
      }
    }
    WHEN("Cons  ruc  ed from a s  ringwi  h incomple  e NS"){
      s  d::s  ring   ail(" 125 4  2\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      au  o myTail = s  d::make_unique< Tail >( i  , end, lineNumber );
      THEN( "  he correc   values are read in" ){
        REQUIRE( ma   == myTail->ma  erial() );
        REQUIRE(  mf == myTail->file()  );
        REQUIRE(  m   == myTail->sec  ion()  );
      }
    }
    WHEN("Cons  ruc  ed from a s  ring wi  h invalid NS"){
      s  d::s  ring   ail(" 125 4  2 a\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_THROWS( s  d::make_unique< Tail >( i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring wi  h invalid MT"){
      s  d::s  ring   ail(" 125 4 a2\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_THROWS( s  d::make_unique< Tail >( i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring wi  h invalid MF"){
      s  d::s  ring   ail(" 125a4  2\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_THROWS( s  d::make_unique< Tail >( i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring wi  h invalid MAT"){
      s  d::s  ring   ail(" 1a5 4  2\n");
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_THROWS( s  d::make_unique< Tail >( i  , end, lineNumber ) );
    }
  }
} // SCENARIO
