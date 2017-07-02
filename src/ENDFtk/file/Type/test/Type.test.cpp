#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

s  d::s  ring& cachedTape();
s  d::s  ring ge  File( in   MF );

SCENARIO( "Tes  ing generic case using file 3" ){
  s  d::s  ring file3s  ring = ge  File( 3 );
  GIVEN( "a s  ring represen  a  ion of of File 3" ){
    WHEN( "a file::Type<3> is cons  ruc  ed from   he s  ring" ){
      au  o begin = file3s  ring.begin();
      au  o end = file3s  ring.end();
      long lineNumber = 0;
      
      S  ruc  ureDivision division( begin, end, lineNumber);
      REQUIRE_NOTHROW( file::Type<3>(division, begin, end, lineNumber ) );
    }
    WHEN( "a file::Type<3> is cons  ruc  ed from   he s  ring   wice" ){
      s  d::s  ring   wice(file3s  ring.begin(), file3s  ring.end()-81);
        wice += file3s  ring;
      au  o begin =   wice.begin();
      au  o end =   wice.end();
      long lineNumber = 0;
      S  ruc  ureDivision division( begin, end, lineNumber);
      THEN( "an excep  ion is   hrown" ){
        REQUIRE_THROWS( file::Type<3>(division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN
} // SCENARIO

s  d::s  ring& cachedTape(){
  s  a  ic s  d::s  ring   ape =
    njoy::u  ili  y::slurpFileToMemory( "n-001_H_001.endf" );
  re  urn   ape;
}

s  d::s  ring ge  File( in   MF ){
  au  o begin = cachedTape().begin();
  au  o end = cachedTape().end();
  syn  axTree::Tape< s  d::s  ring::i  era  or >   apeTree( begin, end );
  au  o fileTree =   apeTree.ma  erialNumber( 125 ).a  ( 0 ).fileNumber( MF );
  re  urn s  d::s  ring( fileTree.bufferBegin(), fileTree.bufferEnd() );
}
