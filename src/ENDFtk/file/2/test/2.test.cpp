#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string getFile( int MF );
std::string chunk151();
void verifyChunk151( const file::Type< 2 >& );
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string validTEND();
std::string validHEAD();

SCENARIO( "Testing special case of file 2" ) {

  GIVEN( "valid data for a File 2" ) {

    WHEN( "a file::Type< 2 > is constructed using only mt151" ) {

      // section::Type< 2, 151 > mt451( /* complete this */ );

      // file::Type< 2 > mf2( std::move( mt451 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        // verifyChunk151( mf2 );
      } // THEN

      THEN( "it can be printed" ) {

        // std::string buffer;
        // auto output = std::back_inserter( buffer );
        // mf2.print( output, 3988 );

        // CHECK( buffer == chunk451() + validFEND() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of File 2 with errors in the END records" ) {

    WHEN( "there is a SEND instead of FEND" ) {

      // std::string string = chunk151() + validSEND();
      // auto begin = string.begin();
      // auto end = string.end();
      // long lineNumber = 0;

      // StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        // CHECK_THROWS( file::Type< 2 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a MEND instead of FEND" ) {

      // std::string string = chunk151() + validMEND();
      // auto begin = string.begin();
      // auto end = string.end();
      // long lineNumber = 0;

      // StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        // CHECK_THROWS( file::Type< 2 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a TEND instead of FEND" ) {

      // std::string string = chunk151() + validTEND();
      // auto begin = string.begin();
      // auto end = string.end();
      // long lineNumber = 0;

      // StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        // CHECK_THROWS( file::Type< 2 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a HEAD instead of FEND" ) {

      // std::string string = chunk151() + validHEAD();
      // auto begin = string.begin();
      // auto end = string.end();
      // long lineNumber = 0;

      // StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        // CHECK_THROWS( file::Type< 2 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN

  std::string file2string = getFile( 2 );

  GIVEN( "a string representation of of File 2" ) {

    WHEN( "a file::Type< 2 > is constructed from the string" ) {

      auto begin = file2string.begin();
      auto end = file2string.end();
      long lineNumber = 0;

      StructureDivision head( begin, end, lineNumber );
      file::Type< 2 > file( head, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        CHECK( file.hasMT( 151 ) );
        CHECK( not file.hasMT( 1 ) );
        CHECK( file.hasSection( 151 ) );
        CHECK( not file.hasSection( 1 ) );

        CHECK( 11022. == Approx( file.section( 151_c ).ZA() ) );
        CHECK( 11022. == Approx( file.MT( 151_c ).ZA() ) );
      }
    }

    WHEN( "a file::Type< 2 > is constructed from a syntaxTree" ) {

      auto begin = file2string.begin();
      auto start = file2string.begin();
      auto end = file2string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      syntaxTree::File< std::string >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 2 > can be constructed" ) {

        CHECK_NOTHROW( fileTree.parse< 2 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type< 2 > is constructed from the string twice" ) {

      std::string twice( file2string.begin(), file2string.end() - 81 );
      twice += file2string;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 2 >
                        ( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 2 >" ) {

    auto begin = file2string.begin();
    auto end = file2string.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 2 > file2( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      file2.print( output, 1122 );

      CHECK( buffer == file2string );
    }
  } // GIVEN
} // SCENARIO

std::string getFile( int MF ){
  static std::string tape =
    njoy::utility::slurpFileToMemory( "n-011_Na_022.endf" );
  syntaxTree::Tape< std::string > tapeTree( njoy::utility::copy( tape ) );
  auto fileTree = tapeTree.materialNumber( 1122 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}

std::string chunk151() {
  return
    "TO BE COMPLETED     \n";
}

void verifyChunk151( const file::Type< 2 >& chunk ) {

  CHECK( 2 == chunk.MF() );
  CHECK( 2 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 151 ) );
  CHECK( not chunk.hasMT( 4 ) );
  CHECK( chunk.hasSection( 151 ) );
  CHECK( not chunk.hasSection( 4 ) );

  CHECK_NOTHROW( chunk.MT( 151_c ) );
  CHECK_NOTHROW( chunk.section( 151_c ) );

  CHECK( 11022. == Approx( chunk.MT( 151_c ).ZA() ) );
}

std::string validSEND() {
  return
    "                                                                  1122 2  0     \n";
}

std::string validFEND() {
  return
    "                                                                  1122 0  0     \n";
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
