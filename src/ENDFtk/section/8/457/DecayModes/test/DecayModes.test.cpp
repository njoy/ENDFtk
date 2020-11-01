#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/8/457.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using DecayModes = section::Type< 8, 457 >::DecayModes;
using DecayMode = section::Type< 8, 457 >::DecayMode;

std::string chunk();
void verifyChunk( const DecayModes& );
std::string chunkStableNuclide();
void verifyChunkStableNuclide( const DecayModes& );
std::string wrongNDK();
std::string wrongStableNDK();

SCENARIO( "DecayModes" ) {

  GIVEN( "valid data for a DecayModes for an unstable nuclide" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spin = 5.;
      double parity = -1.0;
      std::vector< DecayMode > decayModes =
        { { 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 1.200000e-4 },
          { 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 1.200000e-4 },
          { 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 } };

      DecayModes chunk( spin, parity, std::move( decayModes ) );

      THEN( "a DecayModes can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DecayModes chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DecayModes can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a DecayModes for a stable nuclide" ) {

    std::string string = chunkStableNuclide();

    WHEN( "the data is given explicitly" ) {

      double spin = 5.;
      double parity = -1.0;

      DecayModes chunk( spin, parity );

      THEN( "a DecayModes can be constructed and members can be tested" ) {

        verifyChunkStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      DecayModes chunk( begin, end, lineNumber, 3580, 8, 457 );

      THEN( "a DecayModes can be constructed and members can be tested" ) {

        verifyChunkStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8, 457 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ContinuousSpectrum" ) {

    WHEN( "a string representation of a DecayModes with inconsistent NDK "
          "is given" ) {

      std::string string = wrongNDK();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DecayModes( begin, end, lineNumber, 3580, 8, 457 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a DecayModes for a stable nuclide with "
           "inconsistent NDK is given" ) {

      std::string string = wrongStableNDK();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DecayModes( begin, end, lineNumber, 3580, 8, 457 ) );
      } // THEN
    } // WHEN
  } // WHEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000+0-1.000000+0          0          0         18          33580 8457     \n"
    " 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n"
    " 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n"
    " 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n";
}

void verifyChunk( const DecayModes& chunk )
{
  CHECK( 5.0 == Approx( chunk.spin() ) );
  CHECK( -1. == Approx( chunk.parity() ) );

  auto modes = chunk.decayModes();
  CHECK( 3 == chunk.NDK() );
  CHECK( 3 == modes.size() );
  CHECK( 4. == Approx( modes[0].decayChain() ) );
  CHECK( 0. == Approx( modes[0].finalIsomericState() ) );
  CHECK( 5.637120e+6 == Approx( modes[0].qValue()[0] ) );
  CHECK( 2.549510e+2 == Approx( modes[0].qValue()[1] ) );
  CHECK( 4.590000e-3 == Approx( modes[0].branchingRatio()[0] ) );
  CHECK( 1.200000e-4 == Approx( modes[0].branchingRatio()[1] ) );
  CHECK( 3. == Approx( modes[1].decayChain() ) );
  CHECK( 0. == Approx( modes[1].finalIsomericState() ) );
  CHECK( 4.860000e+4 == Approx( modes[1].qValue()[0] ) );
  CHECK( 5.000000e+1 == Approx( modes[1].qValue()[1] ) );
  CHECK( 9.954100e-1 == Approx( modes[1].branchingRatio()[0] ) );
  CHECK( 1.200000e-4 == Approx( modes[1].branchingRatio()[1] ) );
  CHECK( 6. == Approx( modes[2].decayChain() ) );
  CHECK( 0. == Approx( modes[2].finalIsomericState() ) );
  CHECK( 1.884000e+8 == Approx( modes[2].qValue()[0] ) );
  CHECK( 3.700000e+6 == Approx( modes[2].qValue()[1] ) );
  CHECK( 1.60000e-10 == Approx( modes[2].branchingRatio()[0] ) );
  CHECK( 6.00000e-11 == Approx( modes[2].branchingRatio()[1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string chunkStableNuclide() {
  return
    " 5.000000+0-1.000000+0          0          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n";
}

void verifyChunkStableNuclide( const DecayModes& chunk )
{
  CHECK( 5.0 == Approx( chunk.spin() ) );
  CHECK( -1. == Approx( chunk.parity() ) );

  auto modes = chunk.decayModes();
  CHECK( 0 == chunk.NDK() );
  CHECK( 1 == modes.size() );
  CHECK( 0. == Approx( modes[0].decayChain() ) );
  CHECK( 0. == Approx( modes[0].finalIsomericState() ) );
  CHECK( 0. == Approx( modes[0].qValue()[0] ) );
  CHECK( 0. == Approx( modes[0].qValue()[1] ) );
  CHECK( 0. == Approx( modes[0].branchingRatio()[0] ) );
  CHECK( 0. == Approx( modes[0].branchingRatio()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string wrongNDK() {
  return
    " 5.000000+0-1.000000+0          0          0         18          23580 8457     \n"
    " 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n"
    " 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n"
    " 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n";
}

std::string wrongStableNDK() {
  return
    " 5.000000+0-1.000000+0          0          0         12          03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n";
}
