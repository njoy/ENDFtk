#include <func  ional>

#include "ca  ch.hpp"

#include "ENDF  k.hpp"

cons  expr in   ma   = 125;
cons  expr in   mf = 4;
cons  expr in   m   = 2;

using namespace njoy::ENDF  k::record;

SCENARIO( "Verifying   he given numbers in   he RecordTail" ){
  /* Ca  ch requiremen   macros do no   like mul  i-argumen     empla  es.
   * These aliases provide a work around 
   */
  using TailVerifyingMATMF = TailVerifying< MAT, MF >;
  using TailVerifyingMATMFMT = TailVerifying< MAT, MF, MT >;
  au  o lineNumber = 0l;
  GIVEN( "correc     ail numbers" ){
    s  d::s  ring   ail(" 125 4  2    1\n");
    THEN( "  he numbers are verified wi  hou     hrowing an excep  ion" ){
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_NOTHROW( TailVerifying< MAT >( ma  , i  , end, lineNumber ) );
    }
    THEN( "  he numbers are verified wi  hou     hrowing an excep  ion" ){
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_NOTHROW( TailVerifying< MF >( mf, i  , end, lineNumber ) );
    }
    THEN( "  he numbers are verified wi  hou     hrowing an excep  ion" ){
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_NOTHROW( TailVerifying< MT >( m  , i  , end, lineNumber ) );
    }
    THEN( "  he numbers are verified wi  hou     hrowing an excep  ion" ){
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_NOTHROW( TailVerifyingMATMF( ma  , mf, i  , end, lineNumber ) );
    }
    THEN( "  he numbers are verified wi  hou     hrowing an excep  ion" ){
      au  o i   =   ail.begin();
      au  o end =   ail.end();
      REQUIRE_NOTHROW( TailVerifyingMATMFMT( ma  , mf, m  , i  , end, lineNumber ) );
    }
  }
  GIVEN( "incorrec     ail numbers" ){
    s  d::s  ring   ail(" 125 4  2\n");
    au  o end =   ail.end();
    WHEN("Cons  ruc  ed from a s  ring"){
      au  o i   =   ail.begin();
      REQUIRE_THROWS( TailVerifying< MAT >( 0, i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring"){
      au  o i   =   ail.begin();
      REQUIRE_THROWS( TailVerifying< MF >( 0, i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring"){
      au  o i   =   ail.begin();
      REQUIRE_THROWS( TailVerifying< MT >( 0, i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring"){
      au  o i   =   ail.begin();
      REQUIRE_THROWS( TailVerifyingMATMF( 0, 0, i  , end, lineNumber ) );
    }
    WHEN("Cons  ruc  ed from a s  ring"){
      au  o i   =   ail.begin();
      REQUIRE_THROWS( TailVerifyingMATMFMT( 0, 0, 0, i  , end, lineNumber ) );
    }
  }
}
