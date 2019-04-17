#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string& cachedTape();
std::string getFile( int MF );
std::string chunk();

SCENARIO( "Testing generic case using file 3" ) {

  GIVEN( "valid data for a File 3" ) {

    std::vector< section::Type< 3 > > sorted =
      { { 1, 1001., 0.9991673, 0., 0., 0,
          { 2l }, { 5l }, { 1e-5, 2e+7 }, { 37.13628, 0.4827735 } },
        { 2, 1001., 0.9991673, 0., 0., 0,
          { 2l }, { 2l }, { 1e-5, 2e+7 }, { 20.43634, 0.4827462 } },
        { 102, 1001., 0.9991673, 2.224631e+6, 2.224631e+6, 0,
          { 2l }, { 5l }, { 1e-5, 2e+7 }, { 16.69994, 2.722354e-5 } } };
    std::vector< section::Type< 3 > > unsorted =
      { { 102, 1001., 0.9991673, 2.224631e+6, 2.224631e+6, 0,
          { 2l }, { 5l }, { 1e-5, 2e+7 }, { 16.69994, 2.722354e-5 } },
        { 2, 1001., 0.9991673, 0., 0., 0,
          { 2l }, { 2l }, { 1e-5, 2e+7 }, { 20.43634, 0.4827462 } },
        { 1, 1001., 0.9991673, 0., 0., 0,
          { 2l }, { 5l }, { 1e-5, 2e+7 }, { 37.13628, 0.4827735 } } };

    WHEN( "a file::Type<3> is constructed from a sorted vector" ) {

      file::Type< 3 > MF3( std::move( sorted ) );

      THEN( "the sections can be extracted" ) {

        REQUIRE( MF3.hasMT( 102 ) );
        REQUIRE( not MF3.hasMT( 12 ) );

        REQUIRE_NOTHROW( MF3.MT( 1 ) );
        REQUIRE_NOTHROW( MF3.MT( 2 ) );
        REQUIRE_NOTHROW( MF3.MT( 102 ) );
      } // THEN

      THEN( "an exception is thrown if invalid MT" ) {

        REQUIRE_THROWS( MF3.MT( 4 ) );
      } // THEN

      THEN( "it can be printed and the sections will be in order" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        MF3.print( output, 125 );

        REQUIRE( buffer == chunk() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<3> is constructed from an unsorted vector" ) {

      file::Type< 3 > MF3( std::move( unsorted ) );

      THEN( "the sections can be extracted" ) {

        REQUIRE( MF3.hasMT( 102 ) );
        REQUIRE( not MF3.hasMT( 12 ) );

        REQUIRE_NOTHROW( MF3.MT( 1 ) );
        REQUIRE_NOTHROW( MF3.MT( 2 ) );
        REQUIRE_NOTHROW( MF3.MT( 102 ) );
      } // THEN

      THEN( "an exception is thrown if invalid MT" ) {

        REQUIRE_THROWS( MF3.MT( 4 ) );
      } // THEN

      THEN( "it can be printed and the sections will be in order" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        MF3.print( output, 125 );

        REQUIRE( buffer == chunk() );
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
      file::Type< 3 > MF3(division, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        REQUIRE( MF3.hasMT( 102 ) );
        REQUIRE( not MF3.hasMT( 12 ) );

        REQUIRE_NOTHROW( MF3.MT( 1 ) );
        REQUIRE_NOTHROW( MF3.MT( 2 ) );
        REQUIRE_NOTHROW( MF3.MT( 102 ) );
      }

      THEN( "an exception is thrown if invalid MT" ) {

        REQUIRE_THROWS( MF3.MT( 4 ) );
      }
    }

    WHEN( "a file::Type<3> is constructed from a syntaxTree" ) {

      auto begin = file3string.begin();
      auto start = file3string.begin();
      auto end = file3string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber);
      syntaxTree::File< std::string::iterator > 
          fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type<3> can be constructed" ) {

        REQUIRE_NOTHROW( fileTree.parse< 3 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type<3> is constructed from the string twice" ) {

      std::string twice(file3string.begin(), file3string.end()-81);
      twice += file3string;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber);
      
      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( file::Type<3>(division, begin, end, lineNumber ) );
      }
    }
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
      REQUIRE( buffer == file3string );
    }
  } // GIVEN
} // SCENARIO

std::string& cachedTape() {

  static std::string tape =
    njoy::utility::slurpFileToMemory( "n-001_H_001.endf" );
  return tape;
}

std::string getFile( int MF ) {

  auto begin = cachedTape().begin();
  auto end = cachedTape().end();
  syntaxTree::Tape< std::string::iterator > tapeTree( begin, end );
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
    "                                                                   125 3  0     \n"
    "                                                                   125 0  0     \n";
}
