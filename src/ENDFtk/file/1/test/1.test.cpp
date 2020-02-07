#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string getFile( int MF );
std::string chunk451();
void verifyChunk451( const file::Type< 1 >& );
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string validTEND();
std::string validHEAD();

SCENARIO( "Testing special case of file 1" ) {

  GIVEN( "valid data for a File 1" ) {

    double za = 39088.;
    double awr = 87.15432;
    int lrp = 0;
    int lfi = 0;
    int nlib = 0;
    int nmod = 0;
    double elis = 0.0;
    double sta = 0;
    int lis = 0;
    int liso =0;
    int nfor = 6;
    double awi = 1.0;
    double emax = 2e+7;
    int lrel = 0;
    int nsub = 10;
    int nver = 0;
    double temp = 293.6;
    int ldrv = 1;
    std::string description =
        " 39- Y- 88 LANL                                                   \n"
        "LANL                                                              \n"
        "----LANL/RC-III       MATERIAL 3988                               \n"
        "-----INCIDENT NEUTRON DATA                                        \n"
        "------ENDF-6 FORMAT                                               \n"
        "***************************************************               \n";
    int nc = 4 + ranges::count( description, '\n' ) + 2;

    WHEN( "a file::Type< 1 > is constructed using only mt451" ) {

      section::Type< 1, 451 > mt451( za, awr, lrp, lfi, nlib, nmod,
                                     elis, sta, lis, liso, nfor,
                                     awi, emax, lrel, nsub, nver,
                                     temp, ldrv,
                                     description,
                                     { { 1, 451, nc, 0 },
                                       { 3, 1, 4, 0 } } );

      file::Type< 1 > mf1( std::move( mt451 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk451( mf1 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf1.print( output, 3988 );

        CHECK( buffer == chunk451() + validFEND() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of File 1 with errors in the END records" ) {

    WHEN( "there is a SEND instead of FEND" ) {

      std::string string = chunk451() + validSEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a MEND instead of FEND" ) {

      std::string string = chunk451() + validMEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a TEND instead of FEND" ) {

      std::string string = chunk451() + validTEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a HEAD instead of FEND" ) {

      std::string string = chunk451() + validHEAD();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN

  std::string file1string = getFile( 1 );

  GIVEN( "a string representation of of File 1" ) {

    WHEN( "a file::Type< 1 > is constructed from the string" ) {

      auto begin = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision head( begin, end, lineNumber );
      file::Type< 1 > file( head, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        CHECK( file.hasMT( 451 ) );
        CHECK( not file.hasMT( 1 ) );
        CHECK( file.hasSection( 451 ) );
        CHECK( not file.hasSection( 1 ) );

        CHECK( 1001. == Approx( file.section( 451_c ).ZA() ) );
        CHECK( 1001. == Approx( file.MT( 451_c ).ZA() ) );
      }
    }

    WHEN( "a file::Type< 1 > is constructed from a syntaxTree" ){
      auto begin = file1string.begin();
      auto start = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      syntaxTree::File< std::string >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 1 > can be constructed" ){
        CHECK_NOTHROW( fileTree.parse< 1 >( lineNumber ) );
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
        CHECK_THROWS( file::Type< 1 >
                        ( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 1 >" ) {
    auto begin = file1string.begin();
    auto end = file1string.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 1 > file1( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file1.print( output, 125 );
      CHECK( buffer == file1string );
    }
  } // GIVEN
} // SCENARIO

std::string getFile( int MF ){
  static std::string tape =
    njoy::utility::slurpFileToMemory( "n-001_H_001.endf" );
  syntaxTree::Tape< std::string > tapeTree( njoy::utility::copy( tape ) );
  auto fileTree = tapeTree.materialNumber( 125 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}

std::string chunk451() {
  return
    " 3.908800+4 8.715432+1          0          0          0          03988 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          63988 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          03988 1451     \n"
    " 2.936000+2 0.000000+0          1          0          6          23988 1451     \n"
    " 39- Y- 88 LANL                                                   3988 1451     \n"
    "LANL                                                              3988 1451     \n"
    "----LANL/RC-III       MATERIAL 3988                               3988 1451     \n"
    "-----INCIDENT NEUTRON DATA                                        3988 1451     \n"
    "------ENDF-6 FORMAT                                               3988 1451     \n"
    "***************************************************               3988 1451     \n"
    "                                1        451         12          03988 1451     \n"
    "                                3          1          4          03988 1451     \n"
    "                                                                  3988 1  0     \n";
}

void verifyChunk451( const file::Type< 1 >& chunk ) {

  CHECK( 1 == chunk.MF() );
  CHECK( 1 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 451 ) );
  CHECK( not chunk.hasMT( 4 ) );
  CHECK( chunk.hasSection( 451 ) );
  CHECK( not chunk.hasSection( 4 ) );

  CHECK_NOTHROW( chunk.MT( 451_c ) );
  CHECK_NOTHROW( chunk.section( 451_c ) );

  CHECK( 39088. == Approx( chunk.MT( 451_c ).ZA() ) );
  CHECK( 6 == chunk.MT( 451_c ).NWD() );
  CHECK( 2 == chunk.MT( 451_c ).NXC() );
  CHECK( 12 == chunk.MT( 451_c ).NC() );
}

std::string validSEND() {
  return
    "                                                                  3988 3  0     \n";
}

std::string validFEND() {
  return
    "                                                                  3988 0  0     \n";
}

std::string validMEND() {
  return
    "                                                                     0 0  0     \n";
}

std::string validTEND() {
  return
    "                                                                    -1 0  0     \n";
}

std::string validHEAD() {
  return
    " 3.908800+4 8.715432+1          0          0          0          03988 1451     \n";
}

