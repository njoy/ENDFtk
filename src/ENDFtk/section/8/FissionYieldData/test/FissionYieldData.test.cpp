#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/8/FissionYieldData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using FissionYieldData = section::FissionYieldData;

std::string chunk();
void verifyChunk( const FissionYieldData& );
std::string invalidChunk();

SCENARIO( "FissionYieldData" ) {

  GIVEN( "valid data for a FissionYieldData" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 0.0253;
      int interpolation = 2;
      std::vector< unsigned int > identifiers = { 23066, 54135, 72171 };
      std::vector< unsigned int > states = { 0, 0, 0 };
      std::vector< std::array< double, 2 > > yields = { {{ 2.05032e-19, 1.31220e-19 }},
                                                        {{ 7.851250e-4, 4.710750e-5 }},
                                                        {{ 0., 0. }} };

      FissionYieldData chunk( std::move( identifiers ), std::move( states ),
                              std::move( yields ),
                              energy, interpolation );

      THEN( "an FissionYieldData can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8, 454 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      FissionYieldData chunk( begin, end, lineNumber, 9228, 8, 454 );

      THEN( "a FissionYieldData can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8, 454 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a FissionYieldData" ) {

    WHEN( "a string representation with an error is given" ) {

      // NPL != 4*NFP
      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( FissionYieldData( begin, end, lineNumber, 9228, 8, 454 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 2.530000-2 0.000000+0          2          0         12          39228 8454     \n"
    " 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8454     \n"
    " 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8454     \n";
}

void verifyChunk( const FissionYieldData& chunk ) {

  CHECK( 2 == chunk.I() );
  CHECK( 2 == chunk.interpolationType() );
  CHECK( false == chunk.LE() );
  CHECK( false == chunk.isEnergyIndependent() );
  CHECK( 3 == chunk.NFP() );
  CHECK( 3 == chunk.numberFissionProducts() );
  CHECK( 0.0253 == Approx( chunk.E() ) );
  CHECK( 0.0253 == Approx( chunk.incidentEnergy() ) );

  CHECK( 3 == chunk.fissionProducts().size() );
  CHECK( 23066 == chunk.fissionProducts()[0].ZAFP() );
  CHECK( 54135 == chunk.fissionProducts()[1].ZAFP() );
  CHECK( 72171 == chunk.fissionProducts()[2].ZAFP() );
  CHECK( 23066 == chunk.fissionProducts()[0].fissionProductIdentifier() );
  CHECK( 54135 == chunk.fissionProducts()[1].fissionProductIdentifier() );
  CHECK( 72171 == chunk.fissionProducts()[2].fissionProductIdentifier() );
  CHECK( 0 == chunk.fissionProducts()[0].FPS() );
  CHECK( 0 == chunk.fissionProducts()[1].FPS() );
  CHECK( 0 == chunk.fissionProducts()[2].FPS() );
  CHECK( 0 == chunk.fissionProducts()[0].isomericState() );
  CHECK( 0 == chunk.fissionProducts()[1].isomericState() );
  CHECK( 0 == chunk.fissionProducts()[2].isomericState() );
  CHECK( 2.05032e-19 == Approx( chunk.fissionProducts()[0].Y()[0] ) );
  CHECK( 1.31220e-19 == Approx( chunk.fissionProducts()[0].Y()[1] ) );
  CHECK( 7.851250e-4 == Approx( chunk.fissionProducts()[1].Y()[0] ) );
  CHECK( 4.710750e-5 == Approx( chunk.fissionProducts()[1].Y()[1] ) );
  CHECK( 0 == Approx( chunk.fissionProducts()[2].Y()[0] ) );
  CHECK( 0 == Approx( chunk.fissionProducts()[2].Y()[1] ) );

  CHECK( 3 == chunk.ZAFP().size() );
  CHECK( 3 == chunk.fissionProductIdentifiers().size() );
  CHECK( 3 == chunk.FPS().size() );
  CHECK( 3 == chunk.isomericStates().size() );
  CHECK( 3 == chunk.Y().size() );
  CHECK( 3 == chunk.fissionYields().size() );
  CHECK( 23066 == chunk.ZAFP()[0] );
  CHECK( 54135 == chunk.ZAFP()[1] );
  CHECK( 72171 == chunk.ZAFP()[2] );
  CHECK( 23066 == chunk.fissionProductIdentifiers()[0] );
  CHECK( 54135 == chunk.fissionProductIdentifiers()[1] );
  CHECK( 72171 == chunk.fissionProductIdentifiers()[2] );
  CHECK( 0 == chunk.FPS()[0] );
  CHECK( 0 == chunk.FPS()[1] );
  CHECK( 0 == chunk.FPS()[2] );
  CHECK( 0 == chunk.isomericStates()[0] );
  CHECK( 0 == chunk.isomericStates()[1] );
  CHECK( 0 == chunk.isomericStates()[2] );
  CHECK( 2 == chunk.Y()[0].size() );
  CHECK( 2 == chunk.Y()[1].size() );
  CHECK( 2 == chunk.Y()[2].size() );
  CHECK( 2 == chunk.fissionYields()[0].size() );
  CHECK( 2 == chunk.fissionYields()[1].size() );
  CHECK( 2 == chunk.fissionYields()[2].size() );
  CHECK( 2.05032e-19 == Approx( chunk.Y()[0][0] ) );
  CHECK( 1.31220e-19 == Approx( chunk.Y()[0][1] ) );
  CHECK( 7.851250e-4 == Approx( chunk.Y()[1][0] ) );
  CHECK( 4.710750e-5 == Approx( chunk.Y()[1][1] ) );
  CHECK( 0 == Approx( chunk.Y()[2][0] ) );
  CHECK( 0 == Approx( chunk.Y()[2][1] ) );
  CHECK( 2.05032e-19 == Approx( chunk.fissionYields()[0][0] ) );
  CHECK( 1.31220e-19 == Approx( chunk.fissionYields()[0][1] ) );
  CHECK( 7.851250e-4 == Approx( chunk.fissionYields()[1][0] ) );
  CHECK( 4.710750e-5 == Approx( chunk.fissionYields()[1][1] ) );
  CHECK( 0 == Approx( chunk.fissionYields()[2][0] ) );
  CHECK( 0 == Approx( chunk.fissionYields()[2][1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 2.530000-2 0.000000+0          2          0         16          39228 8454     \n"
    " 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8454     \n"
    " 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8454     \n";
}
