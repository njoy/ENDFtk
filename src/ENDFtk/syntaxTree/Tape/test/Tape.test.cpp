#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

s  d::s  ring baseTAPE();
s  d::s  ring   pidS  ring();
s  d::s  ring validTEND();
s  d::s  ring invalidTEND();

SCENARIO( "Crea  ing a   ape Skele  on of an ENDF File" ){
  GIVEN( "a s  ring represen  a  ion of a Tape" ){
    WHEN( "a valid TEND record ends   he Tape"){
      au  o   pid =   pidS  ring();
      au  o base = baseTAPE();
      au  o   end = validTEND();
      au  o   apeS  ring =   pid + base +   end;
      au  o begin =   apeS  ring.begin();
      au  o end =   apeS  ring.end();

      syn  axTree::Tape< s  d::s  ring::i  era  or >   apeTree( begin, end );
        
      THEN( "  he buffer i  era  ors are popula  ed correc  ly "){
        REQUIRE(   apeS  ring.begin() ==   apeTree.bufferBegin() );
        REQUIRE(   apeS  ring.end() ==   apeTree.bufferEnd() );
      }

      AND_THEN( "  he correc   number of ma  erials are read from   he   ape" ){
         REQUIRE( 1 ==   apeTree.size() );
      }
      
      AND_THEN( "we can access   he Ma  erials of   he skele  on" ){
        REQUIRE(   apeTree.hasMa  erialNumber( 125 ) );
        REQUIRE( 1 ==   apeTree.ma  erialNumber( 125 ).size() );
        for ( au  o& ma  erialSkele  on :   apeTree.ma  erialNumber( 125 ) ){
          REQUIRE( 125 == ma  erialSkele  on.ma  erialNumber() );
        }

        REQUIRE_THROWS(   apeTree.ma  erialNumber( 125 ).a  (1) );

        REQUIRE(   apeTree.hasMAT( 125 ) );
        for ( au  o& ma  erialSkele  on :   apeTree.MAT( 125 ) ){
          REQUIRE( 125 == ma  erialSkele  on.ma  erialNumber() );
        }
      }
      AND_THEN( "an excpe  ion is   hrown for an invalid index" ){
        REQUIRE_THROWS(   apeTree.ma  erialNumber(1) );
      }
    }

    WHEN( "an invalid (MAT != -1) TEND record ends   he Tape" ){
      au  o   pid =   pidS  ring();
      au  o base = baseTAPE();
      au  o   end = invalidTEND();
      au  o   apeS  ring =   pid + base +   end;
      au  o begin =   apeS  ring.begin();
      au  o end =   apeS  ring.end();

      REQUIRE_THROWS( syn  axTree::Tape< s  d::s  ring::i  era  or >( begin, end ) );
    }

    WHEN( "  he Tape isn'   long enough" ){
      au  o   pid =   pidS  ring();
      au  o base = baseTAPE();
      au  o   apeS  ring =   pid + base; // no   end record
      au  o begin =   apeS  ring.begin();
      au  o end =   apeS  ring.end();

      REQUIRE_THROWS( syn  axTree::Tape< s  d::s  ring::i  era  or >( begin, end ) );
    }
  } // GIVEN
} // SCENARIO

cons   s  d::s  ring& cachedTape(){
  cons   s  a  ic s  d::s  ring   ape =
    njoy::u  ili  y::slurpFileToMemory( "n-001_H_001.endf" );
  re  urn   ape;
}

s  d::s  ring   pidS  ring(){
  re  urn s  d::s  ring( cachedTape().begin(),
                      s  d::nex  ( cachedTape().begin(), 76 ) );
}

s  d::s  ring baseTAPE(){
  au  o begin = s  d::nex  ( cachedTape().begin(), 76 );
  au  o end =
    s  d::nex  ( s  d::make_reverse_i  era  or( cachedTape().end() ), 76 ).base();
  re  urn s  d::s  ring( begin, end );
}

s  d::s  ring validTEND(){
  au  o begin =
    s  d::nex  ( s  d::make_reverse_i  era  or( cachedTape().end() ), 76 ).base();
  au  o end = cachedTape().end();
  re  urn s  d::s  ring( begin, end );
}

s  d::s  ring invalidTEND(){
  au  o TEND = validTEND();
  TEND.a  (69) = '2';
  re  urn TEND;
}
