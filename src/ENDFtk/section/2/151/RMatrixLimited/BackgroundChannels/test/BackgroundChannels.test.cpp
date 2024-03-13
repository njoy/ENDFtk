// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using BackgroundChannels =
section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels;
using BackgroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::BackgroundRMatrix;
using SammyBackgroundRMatrix =
section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix;

std::string chunk();
void verifyChunk( const BackgroundChannels& );

SCENARIO( "BackgroundChannels" ) {

  GIVEN( "valid data for a BackgroundChannels" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      int nch = 3;
      std::vector< BackgroundRMatrix > channels = {

        SammyBackgroundRMatrix( 2, 1., 2., 3., 4., 5., 6., 7. )
      };

      BackgroundChannels chunk( nch, std::move( channels ) );

      THEN( "a BackgroundChannels can be constructed and members can be "
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

      BackgroundChannels chunk( begin, end, lineNumber, 2625, 2, 151, 3, 1 );

      THEN( "a BackgroundChannels can be constructed and members can be "
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
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          2          2          0          02625 2151     \n"
    " 1.000000+0 2.000000+0          0          0          5          02625 2151     \n"
    " 3.000000+0 4.000000+0 5.000000+0 6.000000+0 7.000000+0           2625 2151     \n";
}

void verifyChunk( const BackgroundChannels& chunk ) {

  CHECK( 3 == chunk.NCH() );
  CHECK( 3 == chunk.numberChannels() );
  CHECK( 1 == chunk.KBK() );
  CHECK( 1 == chunk.numberBackgroundChannels() );

  CHECK( 3 == chunk.backgroundRMatrices().size() );
  CHECK( false == bool( chunk.backgroundRMatrices()[0] ) );
  CHECK( true == bool( chunk.backgroundRMatrices()[1] ) );
  CHECK( false == bool( chunk.backgroundRMatrices()[2] ) );

  auto background =
  std::get< SammyBackgroundRMatrix >( chunk.backgroundRMatrices()[1].value() );

  CHECK( 2 == background.LBK() );
  CHECK( 2 == background.representation() );
  CHECK( 2 == background.LCH() );
  CHECK( 2 == background.channelIndex() );

  CHECK_THAT( 1., WithinRel( background.ED() ) );
  CHECK_THAT( 2., WithinRel( background.EU() ) );
  CHECK_THAT( 3., WithinRel( background.R0() ) );
  CHECK_THAT( 4., WithinRel( background.R1() ) );
  CHECK_THAT( 5., WithinRel( background.R2() ) );
  CHECK_THAT( 6., WithinRel( background.S0() ) );
  CHECK_THAT( 7., WithinRel( background.S1() ) );

  CHECK( 3 == chunk.NC() );
}
