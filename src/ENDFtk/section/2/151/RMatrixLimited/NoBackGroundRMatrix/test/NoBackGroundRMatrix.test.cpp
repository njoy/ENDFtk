#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using NoBackGroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::NoBackGroundRMatrix;

std::string chunk();
void verifyChunk( const NoBackGroundRMatrix& );
std::string invalidLBK();

SCENARIO( "NoBackGroundRMatrix" ) {

  GIVEN( "valid data for a NoBackGroundRMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int index = 1;

      NoBackGroundRMatrix chunk( index );

      THEN( "a NoBackGroundRMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      NoBackGroundRMatrix chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a NoBackGroundRMatrix can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "a string with the wrong LBK is used" ) {

      std::string string = invalidLBK();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( NoBackGroundRMatrix( begin, end, lineNumber, 2625, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          0          0          02625 2151     \n";
}

void verifyChunk( const NoBackGroundRMatrix& chunk ) {

  CHECK( 0 == chunk.LBK() );
  CHECK( 0 == chunk.representation() );
  CHECK( 1 == chunk.LCH() );
  CHECK( 1 == chunk.channelIndex() );

  CHECK( 1 == chunk.NC() );
}

std::string invalidLBK() {
  return
  " 0.000000+0 0.000000+0          1          1          0          02625 2151     \n";
}
