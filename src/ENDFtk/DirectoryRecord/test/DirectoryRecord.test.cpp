// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/DirectoryRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const DirectoryRecord& );
std::string invalidChunk();

SCENARIO( "DirectoryRecord" ) {

  GIVEN( "valid data for a DirectoryRecord" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int mf = 1;
      int mt = 451;
      int nc = 101;
      int mod = 5;

      DirectoryRecord chunk( mf, mt, nc, mod );

      THEN( "a DirectoryRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1, 451 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DirectoryRecord chunk( begin, end, lineNumber, 125, 1, 451 );

      THEN( "a DirectoryRecord can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 1, 451 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DirectoryRecord" ) {

    WHEN( "a string representation with an error is given" ) {

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DirectoryRecord( begin, end, lineNumber, 125, 1, 451 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation has a mismatch in tha MAT, MF or MT number" ) {

      std::string string = chunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DirectoryRecord( begin, end, lineNumber, 5, 1, 451 ) ); // MAT
        CHECK_THROWS( DirectoryRecord( begin, end, lineNumber, 125, 2, 451 ) ); // MF
        CHECK_THROWS( DirectoryRecord( begin, end, lineNumber, 125, 1, 452 ) ); // MT
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    "                                1        451        101          5 125 1451     \n";
}

void verifyChunk( const DirectoryRecord& chunk ) {

  CHECK( 1 == chunk.MF() );
  CHECK( 451 == chunk.MT() );
  CHECK( 101 == chunk.NC() );
  CHECK( 5 == chunk.MOD() );
}

std::string invalidChunk() {

  return
    "                                1        4z1        101          5 125 1451     \n";
}
