#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string& cachedTape();
std::string getFile( int MF );

SCENARIO( "Testing special case of file 1" ){
  std::string file1string = getFile( 1 );
  int MAT = 125;
  GIVEN( "a string representation of of File 1" ){
    WHEN( "a file::Type< 1 > is constructed from the string" ){
      auto begin = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 1 > file1( division, begin, end, lineNumber, MAT );

      THEN( "the sections can be extracted" ){
        REQUIRE( file1.hasMT( 451 ) );
        REQUIRE( not file1.hasMT( 1 ) );
      }
    }

    WHEN( "a file::Type< 1 > is constructed from a syntaxTree" ){
      auto begin = file1string.begin();
      auto start = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      syntaxTree::File< std::string::iterator >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 1 > can be constructed" ){
        REQUIRE_NOTHROW( fileTree.parse< 1 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type< 1 > is constructed from the string twice" ){
      std::string twice( file1string.begin(), file1string.end() - 81 );
      twice += file1string;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 1 >" ) {
      auto begin = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 1 > file1(division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file1.print( output, 125 );
      REQUIRE( buffer == file1string );
    }
  } // GIVEN
} // SCENARIO

std::string& cachedTape(){
  static std::string tape =
    njoy::utility::slurpFileToMemory( "n-001_H_001.endf" );
  return tape;
}

std::string getFile( int MF ){
  auto begin = cachedTape().begin();
  auto end = cachedTape().end();
  syntaxTree::Tape< std::string::iterator > tapeTree( begin, end );
  auto fileTree = tapeTree.materialNumber( 125 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}
