#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using SammyBackgroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix;

std::string chunk();
void verifyChunk( const SammyBackgroundRMatrix& );
std::string invalidLBK();

SCENARIO( "SammyBackgroundRMatrix" ) {

  GIVEN( "valid data for a SammyBackgroundRMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int index = 1;
      double ed = 1.;
      double eu = 2.;
      double r0 = 3.;
      double r1 = 4.;
      double r2 = 5.;
      double s0 = 6.;
      double s1 = 7.;

      SammyBackgroundRMatrix chunk( index, ed, eu, r0, r1, r2, s0, s1 );

      THEN( "a SammyBackgroundRMatrix can be constructed and members can be "
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

      SammyBackgroundRMatrix chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a SammyBackgroundRMatrix can be constructed and members can be "
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

        CHECK_THROWS( SammyBackgroundRMatrix( begin, end, lineNumber,
                                              2625, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          1          2          0          02625 2151     \n"
    " 1.000000+0 2.000000+0          0          0          5          02625 2151     \n"
    " 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2625 2151     \n";
}

void verifyChunk( const SammyBackgroundRMatrix& chunk ) {

  CHECK( 2 == chunk.LBK() );
  CHECK( 2 == chunk.representation() );
  CHECK( 1 == chunk.LCH() );
  CHECK( 1 == chunk.channelIndex() );

  CHECK( 1. == Approx( chunk.ED() ) );
  CHECK( 2. == Approx( chunk.EU() ) );
  CHECK( 3. == Approx( chunk.R0() ) );
  CHECK( 4. == Approx( chunk.R1() ) );
  CHECK( 5. == Approx( chunk.R2() ) );
  CHECK( 6. == Approx( chunk.S0() ) );
  CHECK( 7. == Approx( chunk.S1() ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidLBK() {
  return
  " 0.000000+0 0.000000+0          1          3          0          02625 2151     \n"
  " 1.000000+0 2.000000+0          0          0          5          02625 2151     \n"
  " 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2625 2151     \n";
}
