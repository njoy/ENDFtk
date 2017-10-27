#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string getFile( const std::string& file, int MAT, int MF );

SCENARIO( "Testing special case of file 1" ){

  std::string file1string = getFile( "n-001_H_001.endf", 125, 1 );
  GIVEN( "a string representation of of File 1 for H1" ){
    WHEN( "a file::Type< 1 > is constructed from the string" ){
      auto begin = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 1 > file1( division, begin, end, lineNumber );

      THEN( "the members can be accessed" ){

        REQUIRE( 1 == file1.MF() );
        REQUIRE( 1 == file1.fileNumber() );

        REQUIRE( file1.hasMT( 451 ) );
        REQUIRE( not file1.hasMT( 452 ) );
        REQUIRE( not file1.hasMT( 455 ) );
        REQUIRE( not file1.hasMT( 456 ) );
        REQUIRE( not file1.hasMT( 458 ) );
        REQUIRE( not file1.hasMT( 460 ) );
        REQUIRE( not file1.hasMT( 1 ) );
      }
      THEN( "the sections can be extracted" ){

        REQUIRE_NOTHROW( file1.MT( 451_c ) );
      }
      THEN( "an exception is thrown if invalid MT" ){
//        REQUIRE_THROWS( file1.MT( 1_c ) );
        REQUIRE_THROWS( file1.MT( 452_c ) );
        REQUIRE_THROWS( file1.MT( 455_c ) );
        REQUIRE_THROWS( file1.MT( 456_c ) );
        REQUIRE_THROWS( file1.MT( 458_c ) );
        REQUIRE_THROWS( file1.MT( 460_c ) );
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
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 1 > for H1" ) {
    auto begin = file1string.begin();
    auto end = file1string.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 1 > file1( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file1.print( output, 125 );
      REQUIRE( buffer == file1string );
    }
  } // GIVEN

  file1string = getFile( "n-092_U_235.endf", 9228, 1 );
  GIVEN( "a string representation of of File 1 for U235" ){
    WHEN( "a file::Type< 1 > is constructed from the string" ){
      auto begin = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 1 > file1( division, begin, end, lineNumber );

      THEN( "the members can be accessed" ){

        REQUIRE( 1 == file1.MF() );
        REQUIRE( 1 == file1.fileNumber() );

        REQUIRE( file1.hasMT( 451 ) );
        REQUIRE( file1.hasMT( 452 ) );
        REQUIRE( file1.hasMT( 455 ) );
        REQUIRE( file1.hasMT( 456 ) );
        REQUIRE( file1.hasMT( 458 ) );
        REQUIRE( file1.hasMT( 460 ) );
        REQUIRE( not file1.hasMT( 1 ) );
      }
      THEN( "the sections can be extracted" ){

        REQUIRE_NOTHROW( file1.MT( 451_c ) );
        REQUIRE_NOTHROW( file1.MT( 452_c ) );
        REQUIRE_NOTHROW( file1.MT( 455_c ) );
        REQUIRE_NOTHROW( file1.MT( 456_c ) );
        REQUIRE_NOTHROW( file1.MT( 458_c ) );
        REQUIRE_NOTHROW( file1.MT( 460_c ) );
      }
      THEN( "an exception is thrown if invalid MT" ){
//        REQUIRE_THROWS( file1.MT( 1_c ) );
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
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 1 > for U235" ) {
    auto begin = file1string.begin();
    auto end = file1string.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 1 > file1( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file1.print( output, 9228 );
      REQUIRE( buffer == file1string );
    }
  } // GIVEN

  GIVEN( "a File 1 string in which section 451 is not the first section" ) {
    std::string mf1 =
      " 1.001000+3 9.991673-1          0          0          0          3 125 1452     \n"
      " 0.000000+0 0.000000+0          0          0          0          6 125 1452     \n"
      " 1.000000+0 2.000000+7          0          0         10          8 125 1452     \n";

    auto begin = mf1.begin();
    auto end = mf1.end();
    long lineNumber = 1;
    StructureDivision division( begin, end, lineNumber );

    THEN( "an exception is thrown at construction" ) {

      REQUIRE_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
    }
  } // GIVEN

  GIVEN( "a File 1 string in which an illegal section is present" ) {
    std::string mf1 =
      " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
      " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
      " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
      " 0.000000+0 0.000000+0          0          0          1          1 125 1451     \n"
      "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
      "                                1        451        122          5 125 1451     \n"
      "                                                                   125 1  0     \n"
      " 1.001000+3 9.991673-1          0          0          0          3 125 1453     \n"
      " 0.000000+0 0.000000+0          0          0          0          0 125 1453     \n";

    auto begin = mf1.begin();
    auto end = mf1.end();
    long lineNumber = 1;
    StructureDivision division( begin, end, lineNumber );

    THEN( "an exception is thrown at construction" ) {

      REQUIRE_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
    }
  } // GIVEN

  GIVEN( "a File 1 string in which a MEND record is used instead of FEND" ) {
    std::string mf1 =
      " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
      " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
      " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
      " 0.000000+0 0.000000+0          0          0          1          1 125 1451     \n"
      "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
      "                                1        451        122          5 125 1451     \n"
      "                                                                   125 1  0     \n"
      "                                                                     0 0  0     \n";

    auto begin = mf1.begin();
    auto end = mf1.end();
    long lineNumber = 1;
    StructureDivision division( begin, end, lineNumber );

    THEN( "an exception is thrown at construction" ) {

      REQUIRE_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
    }
  } // GIVEN

  GIVEN( "a File 1 string in which a TEND record is used instead of FEND" ) {
    std::string mf1 =
      " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
      " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
      " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
      " 0.000000+0 0.000000+0          0          0          1          1 125 1451     \n"
      "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
      "                                1        451        122          5 125 1451     \n"
      "                                                                   125 1  0     \n"
      "                                                                    -1 0  0     \n";

    auto begin = mf1.begin();
    auto end = mf1.end();
    long lineNumber = 1;
    StructureDivision division( begin, end, lineNumber );

    THEN( "an exception is thrown at construction" ) {

      REQUIRE_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
    }
  } // GIVEN
} // SCENARIO

std::string getFile( const std::string& file, int MAT, int MF ){
  std::string tape = njoy::utility::slurpFileToMemory( file );
  auto begin = tape.begin();
  auto end = tape.end();
  syntaxTree::Tape< std::string::iterator > tapeTree( begin, end );
  auto fileTree = tapeTree.materialNumber( MAT ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}

