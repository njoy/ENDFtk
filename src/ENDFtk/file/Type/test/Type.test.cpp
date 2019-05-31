#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string getFile( int MF );
std::string chunk();
void verifyChunk( const file::Type< 3 >& );
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string validTEND();

SCENARIO( "Testing generic case using file 3" ) {

  GIVEN( "valid data for a File 3" ) {

    std::vector< section::Type< 3 > > sorted =
      { { 1, 1001., 0.9991673, 0., 0., 0,
          { 2l }, { 5l }, { 1e-5, 2e+7 }, { 37.13628, 0.4827735 } },
        { 2, 1001., 0.9991673, 0., 0., 0,
          { 2l }, { 2l }, { 1e-5, 2e+7 }, { 20.43634, 0.4827462 } },
        { 102, 1001., 0.9991673, 2.224631e+6, 2.224631e+6, 0,
          { 2l }, { 5l }, { 1e-5, 2e+7 }, { 16.69994, 2.722354e-5 } } };
    auto unsorted = sorted | ranges::view::reverse | ranges::to_vector;

    WHEN( "a file::Type<3> is constructed from a sorted vector" ) {

      file::Type< 3 > mf3( std::move( sorted ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk( mf3 );
      } // THEN

      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        CHECK_THROWS( mf3.MT( 4 ) );
        CHECK_THROWS( mf3.section( 4 ) );
      } // THEN

      THEN( "we can iterate over the sections and they will be in order" ) {

        auto iter = mf3.begin();

        CHECK( 1 == iter->MT() ); iter++;
        CHECK( 2 == iter->MT() ); iter++;
        CHECK( 102 == iter->MT() ); iter++;
        CHECK( iter == mf3.end() );
      } // THEN

      THEN( "it can be printed and the sections will be in order" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf3.print( output, 125 );

        CHECK( buffer == chunk() + validFEND() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<3> is constructed from an unsorted vector" ) {

      file::Type< 3 > mf3( std::move( unsorted ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk( mf3 );
      } // THEN

      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        CHECK_THROWS( mf3.MT( 4 ) );
        CHECK_THROWS( mf3.section( 4 ) );
      } // THEN

      THEN( "we can iterate over the sections and they will be in order" ) {

        auto iter = mf3.begin();

        CHECK( 1 == iter->MT() ); iter++;
        CHECK( 2 == iter->MT() ); iter++;
        CHECK( 102 == iter->MT() ); iter++;
        CHECK( iter == mf3.end() );
      } // THEN

      THEN( "it can be printed and the sections will be in order" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf3.print( output, 125 );

        CHECK( buffer == chunk() + validFEND() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<3> is constructed from individual elements" ) {

      file::Type< 3 > mf3( std::move( unsorted[0] ),
                           std::move( unsorted[1] ),
                           std::move( unsorted[2] ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk( mf3 );
      } // THEN

      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        CHECK_THROWS( mf3.MT( 4 ) );
        CHECK_THROWS( mf3.section( 4 ) );
      } // THEN

      THEN( "we can iterate over the sections and they will be in order" ) {

        auto iter = mf3.begin();

        CHECK( 1 == iter->MT() ); iter++;
        CHECK( 2 == iter->MT() ); iter++;
        CHECK( 102 == iter->MT() ); iter++;
        CHECK( iter == mf3.end() );
      } // THEN

      THEN( "it can be printed and the sections will be in order" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf3.print( output, 125 );

        CHECK( buffer == chunk() + validFEND() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of File 3" ) {

    std::string file3string = getFile( 3 );

    WHEN( "a file::Type<3> is constructed from the string" ) {

      auto begin = file3string.begin();
      auto end = file3string.end();
      long lineNumber = 0;
      
      StructureDivision division( begin, end, lineNumber);
      file::Type< 3 > mf3(division, begin, end, lineNumber );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk( mf3 );
      } // THEN

      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        CHECK_THROWS( mf3.MT( 4 ) );
        CHECK_THROWS( mf3.section( 4 ) );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<3> is constructed from a syntaxTree" ) {

      auto begin = file3string.begin();
      auto start = file3string.begin();
      auto end = file3string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber);
      syntaxTree::File< std::string::iterator > 
          fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type<3> can be constructed" ) {

        CHECK_NOTHROW( fileTree.parse< 3 >() );
        CHECK_NOTHROW( fileTree.parse< 3 >( lineNumber ) );
        CHECK_NOTHROW( fileTree.parse( 3_c ) );
        CHECK_NOTHROW( fileTree.parse( 3_c, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<3> is constructed from the string twice" ) {

      std::string twice(file3string.begin(), file3string.end()-81);
      twice += file3string;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber);
      
      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type<3>(division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 3 >" ) {

    std::string file3string = getFile( 3 );
    auto begin = file3string.begin();
    auto end = file3string.end();
    long lineNumber = 0;
      
    StructureDivision division( begin, end, lineNumber);
    file::Type< 3 > file3(division, begin, end, lineNumber );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      file3.print( output, 125 );
      CHECK( buffer == file3string );
    } // THEN
  } // GIVEN

  GIVEN( "a string representation of File 3 with errors in the END records" ) {

    WHEN( "there is a SEND instead of FEND" ) {

      std::string string = chunk() + validSEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 3 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a MEND instead of FEND" ) {

      std::string string = chunk() + validMEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 3 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a TEND instead of FEND" ) {

      std::string string = chunk() + validTEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 3 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string getFile( int MF ) {
  static std::string tape =
    njoy::utility::slurpFileToMemory( "n-001_H_001.endf" );
  syntaxTree::Tape< std::string > tapeTree( njoy::utility::copy( tape ) );
  auto fileTree = tapeTree.materialNumber( 125 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}

std::string chunk() {
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 0.000000+0 0.000000+0          0          0          1          2 125 3  1     \n"
    "          2          5                                             125 3  1     \n"
    " 1.000000-5 3.713628+1 2.000000+7 4.827735-1                       125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  2     \n"
    " 0.000000+0 0.000000+0          0          0          1          2 125 3  2     \n"
    "          2          2                                             125 3  2     \n"
    " 1.000000-5 2.043634+1 2.000000+7 4.827462-1                       125 3  2     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 2.224631+6 2.224631+6          0          0          1          2 125 3102     \n"
    "          2          5                                             125 3102     \n"
    " 1.000000-5 1.669994+1 2.000000+7 2.722354-5                       125 3102     \n"
    "                                                                   125 3  0     \n";
}

void verifyChunk( const file::Type< 3 >& chunk ) {

  CHECK( 3 == chunk.MF() );
  CHECK( 3 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 1 ) );
  CHECK( chunk.hasMT( 2 ) );
  CHECK( chunk.hasMT( 102 ) );
  CHECK( chunk.hasSection( 1 ) );
  CHECK( chunk.hasSection( 2 ) );
  CHECK( chunk.hasSection( 102 ) );

  CHECK( not chunk.hasMT( 12 ) );
  CHECK( not chunk.hasSection( 12 ) );

  CHECK_NOTHROW( chunk.MT( 1 ) );
  CHECK_NOTHROW( chunk.MT( 2 ) );
  CHECK_NOTHROW( chunk.MT( 102 ) );
  CHECK_NOTHROW( chunk.section( 1 ) );
  CHECK_NOTHROW( chunk.section( 2 ) );
  CHECK_NOTHROW( chunk.section( 102 ) );

  CHECK( 1001. == Approx( chunk.MT( 1 ).ZA() ) );
  CHECK( 0.0 == Approx( chunk.MT( 1 ).QM() ) );
  CHECK( 0.0 == Approx( chunk.MT( 1 ).QI() ) );
  CHECK( 5 == chunk.MT( 1 ).interpolants()[0] );
  CHECK( 1001. == Approx( chunk.section( 1 ).ZA() ) );
  CHECK( 0.0 == Approx( chunk.section( 1 ).QM() ) );
  CHECK( 0.0 == Approx( chunk.section( 1 ).QI() ) );
  CHECK( 5 == chunk.section( 1 ).interpolants()[0] );

  CHECK( 1001. == Approx( chunk.MT( 2 ).ZA() ) );
  CHECK( 0.0 == Approx( chunk.MT( 2 ).QM() ) );
  CHECK( 0.0 == Approx( chunk.MT( 2 ).QI() ) );
  CHECK( 2 == chunk.MT( 2 ).interpolants()[0] );
  CHECK( 1001. == Approx( chunk.section( 2 ).ZA() ) );
  CHECK( 0.0 == Approx( chunk.section( 2 ).QM() ) );
  CHECK( 0.0 == Approx( chunk.section( 2 ).QI() ) );
  CHECK( 2 == chunk.section( 2 ).interpolants()[0] );

  CHECK( 1001. == Approx( chunk.MT( 102 ).ZA() ) );
  CHECK( 2.224631e+6 == Approx( chunk.MT( 102 ).QM() ) );
  CHECK( 2.224631e+6 == Approx( chunk.MT( 102 ).QI() ) );
  CHECK( 5 == chunk.MT( 102 ).interpolants()[0] );
  CHECK( 1001. == Approx( chunk.section( 102 ).ZA() ) );
  CHECK( 2.224631e+6 == Approx( chunk.section( 102 ).QM() ) );
  CHECK( 2.224631e+6 == Approx( chunk.section( 102 ).QI() ) );
  CHECK( 5 == chunk.section( 102 ).interpolants()[0] );
}

std::string validSEND() {
  return
    "                                                                   125 3  0     \n";
}

std::string validFEND() {
  return
    "                                                                   125 0  0     \n";
}

std::string validMEND() {
  return
    "                                                                     0 0  0     \n";
}

std::string validTEND() {
  return
    "                                                                    -1 0  0     \n";
}

