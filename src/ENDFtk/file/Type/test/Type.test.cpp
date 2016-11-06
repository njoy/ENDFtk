#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

const std::string& cachedTape();
std::string file( int MF );

SCENARIO( "Testing generic case using file 3" ){
  std::string file3string = file( 3 );
  GIVEN( "a string representation of of File 3" ){
    WHEN( "a file::Type<3> is constructed from the string" ){
      auto begin = file3string.begin();
      auto end = file3string.end();
      long lineNumber = 0;
      
      StructureDivision division( begin, end, lineNumber);
      REQUIRE_NOTHROW( file::Type<3>(division, begin, end, lineNumber ) );
    }
    WHEN( "a file::Type<3> is constructed from the string twice" ){
      std::string twice(file3string.begin(), file3string.end()-81);
      twice += file3string;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber);
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( file::Type<3>(division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN
} // SCENARIO

const std::string& cachedTape(){
  const static std::string tape =
    njoy::utility::slurpFileToMemory( "n-001_H_001.endf" );
  return tape;
}

std::string file( int MF ){
  syntaxTree::Tape< std::string::iterator >
    tapeTree( cachedTape().begin(), cachedTape().end() );
  auto fileTree = tapeTree.materialNumber( 125 ).at( 0 ).fileNumber( MF );
  return std::string( fileTree.bufferBegin(), fileTree.bufferEnd() );
}
