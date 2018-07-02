#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string& cachedTape();
std::string getFile( int MF );

SCENARIO( "Testing special case of file 7" ){
  std::string fileString = getFile( 7 );
  GIVEN( "a string representation of of File 7" ){
    WHEN( "a file::Type< 7 > is constructed from the string" ){
      auto begin = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 7 > file( division, begin, end, lineNumber );

      THEN( "the sections can be extracted" ){
        REQUIRE( file.hasMT( 2 ) );
        REQUIRE( file.hasMT( 4 ) );
        REQUIRE( not file.hasMT( 1 ) );
      }
    }

    WHEN( "a file::Type< 7 > is constructed from a syntaxTree" ){
      auto begin = fileString.begin();
      auto start = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      syntaxTree::File< std::string::iterator >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 7 > can be constructed" ){
        REQUIRE_NOTHROW( fileTree.parse< 7 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type< 7 > is constructed from the string twice" ){
      std::string twice( fileString.begin(), fileString.end() - 81 );
      twice += fileString;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( file::Type< 7 >
                        ( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 7 >" ) {
    auto begin = fileString.begin();
    auto end = fileString.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 7 > file( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file.print( output, 27 );
//      REQUIRE( buffer == fileString );
    }
  } // GIVEN
} // SCENARIO

std::string& cachedTape(){
  static std::string tape =
    njoy::utility::slurpFileToMemory( "tsl-BeinBeO.endf" );
  return tape;
}

std::string getFile( int MF ){
  auto begin = cachedTape().begin();
  auto end = cachedTape().end();
  syntaxTree::Tape< std::string::iterator > tapeTree( begin, end );
  auto fileTree = tapeTree.materialNumber( 27 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}
