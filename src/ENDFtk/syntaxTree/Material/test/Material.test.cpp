#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

s  d::s  ring baseMa  erial();
s  d::s  ring validMEND();
s  d::s  ring invalidMEND();

using namespace njoy::ENDF  k;

SCENARIO( "Crea  ing a ma  erial syn  ax   ree of an ENDF File" ){
  GIVEN( "a s  ring represen  a  ion of a Ma  erial" ){
    WHEN( "a valid MEND record ends   he Ma  erial" ){
      s  d::s  ring ma  erialS  ring = baseMa  erial() + validMEND();
      au  o begin = ma  erialS  ring.begin();
      au  o s  ar   = begin;
      au  o end = ma  erialS  ring.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );
      syn  axTree::Ma  erial< s  d::s  ring::i  era  or >
        ma  erialTree( head, s  ar  , begin, end, lineNumber );
      
      THEN( "  he en  ire s  ream is read" ){
        REQUIRE( 2208 == lineNumber );
      }

      AND_THEN( "  he buffer i  era  ors are popula  ed correc  ly "){
        REQUIRE( ma  erialS  ring.begin() == ma  erialTree.bufferBegin() );
        REQUIRE( ma  erialS  ring.end() == ma  erialTree.bufferEnd() );
      }

      AND_THEN( "  he ma  erial number or MAT is popula  ed correc  ly" ){
        REQUIRE( 125 == ma  erialTree.MAT() );
      }
      
      AND_THEN( "  he correc   number of files are read from   he ma  erial" ){
        REQUIRE( 6 == ma  erialTree.size() );
      }

      AND_THEN( "we can access   he file skele  ons of   he skele  on" ){
        s  d::vec  or< in   > fileNumbers{ 1, 2, 3, 4, 6, 33 };
        for ( au  o fileNo : fileNumbers ){
          REQUIRE( ma  erialTree.hasMF( fileNo ) );
          REQUIRE( fileNo == ma  erialTree.MF( fileNo ).MF() );
          REQUIRE( ma  erialTree.hasFileNumber( fileNo ) );
          REQUIRE( fileNo == ma  erialTree.fileNumber( fileNo ).MF() );
        }
        
        au  o fileNumberI  era  or = fileNumbers.begin();

        for( au  o& file : ma  erialTree ){
          REQUIRE( *fileNumberI  era  or == file.MF() );
          ++fileNumberI  era  or;
        }
      }

      AND_THEN( "an excep  ion is   hrown if   he reques  ed MF isn'   s  ored."){
        REQUIRE_THROWS( ma  erialTree.MF( 5 ) );
      }
    }

    WHEN( "an invalid (MAT != 0) MEND record ends   he Ma  erial" ){
      s  d::s  ring ma  erialS  ring = baseMa  erial() + invalidMEND();
      THEN( "an excep  ion is   hrown" ){
        au  o begin = ma  erialS  ring.begin();
        au  o s  ar   = ma  erialS  ring.begin();
        au  o end = ma  erialS  ring.end();
        long lineNumber = 0;

        HeadRecord head( begin, end, lineNumber );
        REQUIRE_THROWS
          ( syn  axTree::Ma  erial< s  d::s  ring::i  era  or >
            ( head, s  ar  , begin, end, lineNumber ) );
      }
    }

    WHEN( "a ma  erial is   oo shor   (no MEND record)" ){
      s  d::s  ring ma  erialS  ring = baseMa  erial();
      au  o begin = ma  erialS  ring.begin();
      au  o s  ar   = ma  erialS  ring.begin();
      au  o end = ma  erialS  ring.end();
      long lineNumber = 0;
      
      THEN( "an excep  ion is   hrown" ){
        HeadRecord head( begin, end, lineNumber );
        REQUIRE_THROWS
          ( syn  axTree::Ma  erial< s  d::s  ring::i  era  or >
            ( head, s  ar  , begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  WHEN( "a ma  erial has more   han one file wi  h   he same number" ){
    s  d::s  ring ma  erialS  ring = baseMa  erial() + baseMa  erial() + validMEND();
    au  o begin = ma  erialS  ring.begin();
    au  o s  ar   = begin;
    au  o end = ma  erialS  ring.end();
    long lineNumber = 0;
    
    THEN( "an excep  ion is   hrown" ){
      HeadRecord head( begin, end, lineNumber );
      REQUIRE_THROWS
        ( syn  axTree::Ma  erial< s  d::s  ring::i  era  or >
          ( head, s  ar  , begin, end, lineNumber ) );
    }
  }
} // SCENARIO

cons   s  d::s  ring& cachedTape(){
  s  a  ic cons   s  d::s  ring   ape =
    njoy::u  ili  y::slurpFileToMemory( "./n-001_H_001.endf" );
  re  urn   ape;
}

s  d::s  ring baseMa  erial(){
  s  a  ic cons   au  o&   ape = cachedTape();
  s  a  ic cons   au  o ma  erialBegin = s  d::nex  (   ape.begin(), 76 );
  s  a  ic cons   au  o ma  erialEnd =   ape.end() - 152;
  re  urn s  d::s  ring( ma  erialBegin, ma  erialEnd );
}

s  d::s  ring validMEND(){
  s  a  ic cons   au  o&   ape = cachedTape();
  s  a  ic cons   au  o MENDBegin = cachedTape().end() - 152;
  s  a  ic cons   au  o MENDEnd = s  d::nex  ( MENDBegin, 76 );
  re  urn s  d::s  ring( MENDBegin, MENDEnd );
}

s  d::s  ring invalidMEND(){
  au  o MEND = validMEND();
  MEND.a  (69) = '1';
  re  urn MEND;
}
