#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using FrohnerBackGroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::FrohnerBackGroundRMatrix;

std::string chunk();
void verifyChunk( const FrohnerBackGroundRMatrix& );
std::string invalidLBK();

SCENARIO( "FrohnerBackGroundRMatrix" ) {

  GIVEN( "valid data for a FrohnerBackGroundRMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int index = 1;
      double ed = 1.;
      double eu = 2.;
      double r0 = 3.;
      double s0 = 4.;
      double ga = 5.;

      FrohnerBackGroundRMatrix chunk( index, ed, eu, r0, s0, ga );

      THEN( "a FrohnerBackGroundRMatrix can be constructed and members can be "
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

      FrohnerBackGroundRMatrix chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a FrohnerBackGroundRMatrix can be constructed and members can be "
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

        CHECK_THROWS( FrohnerBackGroundRMatrix( begin, end, lineNumber,
                                                2625, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          3          0          02625 2151     \n"
    " 1.000000+0 2.000000+0          0          0          3          02625 2151     \n"
    " 3.000000+0 4.000000+0 5.000000+0                                 2625 2151     \n";
}

void verifyChunk( const FrohnerBackGroundRMatrix& chunk ) {

  CHECK( 3 == chunk.LBK() );
  CHECK( 3 == chunk.representation() );
  CHECK( 1 == chunk.LCH() );
  CHECK( 1 == chunk.channelIndex() );

  CHECK( 1. == Approx( chunk.ED() ) );
  CHECK( 2. == Approx( chunk.EU() ) );
  CHECK( 3. == Approx( chunk.R0() ) );
  CHECK( 4. == Approx( chunk.S0() ) );
  CHECK( 5. == Approx( chunk.GA() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidLBK() {
  return
  " 0.000000+0 0.000000+0          1          4          0          02625 2151     \n"
  " 1.000000+0 2.000000+0          0          0          3          02625 2151     \n"
  " 3.000000+0 4.000000+0 5.000000+0                                 2625 2151     \n";
}
