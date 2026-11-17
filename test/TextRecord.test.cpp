// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/TextRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const TextRecord& );
std::string invalidChunk();

SCENARIO( "TextRecord" ) {

  GIVEN( "valid data for a TextRecord" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string description = "The new R-matrix analysis of the N-N system on which the ENDF/B-  ";

      TextRecord chunk( std::move( description ) );

      THEN( "a TextRecord can be constructed and members can be tested" ) {

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

      TextRecord chunk( begin, end, lineNumber, 125, 1, 451 );

      THEN( "a TextRecord can be constructed and members can be tested" ) {

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
} // SCENARIO

std::string chunk() {

  return
    "The new R-matrix analysis of the N-N system on which the ENDF/B-   125 1451     \n";
}

void verifyChunk( const TextRecord& chunk ) {

  CHECK( "The new R-matrix analysis of the N-N system on which the ENDF/B-  " == chunk.text() );
  CHECK( 1 == chunk.NC() );
}
