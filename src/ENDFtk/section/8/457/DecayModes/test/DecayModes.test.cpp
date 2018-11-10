#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using DecayModes = section::Type< 8, 457 >::DecayModes;
using DecayMode = section::Type< 8, 457 >::DecayMode;

std::string chunk();
std::string wrongNDK();
std::string wrongStableNDK();

SCENARIO( "DecayModes" ) {

  GIVEN( "valid data for a DecayModes" ) {

    double spin = 5.;
    double parity = -1.0;
    std::vector< DecayMode > decayModes =
    { { 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 1.200000e-4 },
      { 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 1.200000e-4 },
      { 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 } };
    
    THEN( "a DecayModes can be constructed and members can be tested for an "
          "unstable nuclide" ) {
      DecayModes chunk( spin, parity, std::move( decayModes ) );

      REQUIRE( 5.0 == Approx( chunk.spin() ) );
      REQUIRE( -1. == Approx( chunk.parity() ) );

      auto modes = chunk.decayModes();
      REQUIRE( 3 == chunk.NDK() );
      REQUIRE( 3 == modes.size() );
      REQUIRE( 4. == Approx( modes[0].decayChain() ) );
      REQUIRE( 0. == Approx( modes[0].finalIsomericState() ) );
      REQUIRE( 5.637120e+6 == Approx( std::get< 0 >( modes[0].qValue() ) ) );
      REQUIRE( 2.549510e+2 == Approx( std::get< 1 >( modes[0].qValue() ) ) );
      REQUIRE( 4.590000e-3 == Approx( std::get< 0 >( modes[0].branchingRatio() ) ) );
      REQUIRE( 1.200000e-4 == Approx( std::get< 1 >( modes[0].branchingRatio() ) ) );
      REQUIRE( 3. == Approx( modes[1].decayChain() ) );
      REQUIRE( 0. == Approx( modes[1].finalIsomericState() ) );
      REQUIRE( 4.860000e+4 == Approx( std::get< 0 >( modes[1].qValue() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( modes[1].qValue() ) ) );
      REQUIRE( 9.954100e-1 == Approx( std::get< 0 >( modes[1].branchingRatio() ) ) );
      REQUIRE( 1.200000e-4 == Approx( std::get< 1 >( modes[1].branchingRatio() ) ) );
      REQUIRE( 6. == Approx( modes[2].decayChain() ) );
      REQUIRE( 0. == Approx( modes[2].finalIsomericState() ) );
      REQUIRE( 1.884000e+8 == Approx( std::get< 0 >( modes[2].qValue() ) ) );
      REQUIRE( 3.700000e+6 == Approx( std::get< 1 >( modes[2].qValue() ) ) );
      REQUIRE( 1.60000e-10 == Approx( std::get< 0 >( modes[2].branchingRatio() ) ) );
      REQUIRE( 6.00000e-11 == Approx( std::get< 1 >( modes[2].branchingRatio() ) ) );

      REQUIRE( 4 == chunk.NC() );
    }

    THEN( "a DecayModes can be constructed and members can be tested for a "
          "stable nuclide" ) {
      DecayModes chunk( spin, parity );

      REQUIRE( 5.0 == Approx( chunk.spin() ) );
      REQUIRE( -1. == Approx( chunk.parity() ) );
      
      auto modes = chunk.decayModes();
      REQUIRE( 0 == chunk.NDK() );
      REQUIRE( 1 == modes.size() );
      REQUIRE( 0. == Approx( modes[0].decayChain() ) );
      REQUIRE( 0. == Approx( modes[0].finalIsomericState() ) );
      REQUIRE( 0. == Approx( std::get< 0 >( modes[0].qValue() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( modes[0].qValue() ) ) );
      REQUIRE( 0. == Approx( std::get< 0 >( modes[0].branchingRatio() ) ) );
      REQUIRE( 0. == Approx( std::get< 1 >( modes[0].branchingRatio() ) ) );

      REQUIRE( 2 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid DecayModes" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "a DecayModes can be constructed and members can be tested" ) {
      DecayModes chunk( begin, end, lineNumber, 3580, 8, 457 );

      REQUIRE( 5.0 == Approx( chunk.spin() ) );
      REQUIRE( -1. == Approx( chunk.parity() ) );
      
      auto modes = chunk.decayModes();
      REQUIRE( 3 == chunk.NDK() );
      REQUIRE( 3 == modes.size() );
      REQUIRE( 4. == Approx( modes[0].decayChain() ) );
      REQUIRE( 0. == Approx( modes[0].finalIsomericState() ) );
      REQUIRE( 5.637120e+6 == Approx( std::get< 0 >( modes[0].qValue() ) ) );
      REQUIRE( 2.549510e+2 == Approx( std::get< 1 >( modes[0].qValue() ) ) );
      REQUIRE( 4.590000e-3 == Approx( std::get< 0 >( modes[0].branchingRatio() ) ) );
      REQUIRE( 1.200000e-4 == Approx( std::get< 1 >( modes[0].branchingRatio() ) ) );
      REQUIRE( 3. == Approx( modes[1].decayChain() ) );
      REQUIRE( 0. == Approx( modes[1].finalIsomericState() ) );
      REQUIRE( 4.860000e+4 == Approx( std::get< 0 >( modes[1].qValue() ) ) );
      REQUIRE( 5.000000e+1 == Approx( std::get< 1 >( modes[1].qValue() ) ) );
      REQUIRE( 9.954100e-1 == Approx( std::get< 0 >( modes[1].branchingRatio() ) ) );
      REQUIRE( 1.200000e-4 == Approx( std::get< 1 >( modes[1].branchingRatio() ) ) );
      REQUIRE( 6. == Approx( modes[2].decayChain() ) );
      REQUIRE( 0. == Approx( modes[2].finalIsomericState() ) );
      REQUIRE( 1.884000e+8 == Approx( std::get< 0 >( modes[2].qValue() ) ) );
      REQUIRE( 3.700000e+6 == Approx( std::get< 1 >( modes[2].qValue() ) ) );
      REQUIRE( 1.60000e-10 == Approx( std::get< 0 >( modes[2].branchingRatio() ) ) );
      REQUIRE( 6.00000e-11 == Approx( std::get< 1 >( modes[2].branchingRatio() ) ) );

      REQUIRE( 4 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of DecayModes" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    DecayModes chunk(begin, end, lineNumber, 3580, 8, 457 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 3580, 8, 457 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of a DecayModes with inconsistent NDK" ) {

    std::string string = wrongNDK();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( DecayModes( begin, end, lineNumber, 3580, 8, 457 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a DecayModes with inconsistent NDK" ) {

    std::string string = wrongNDK();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( DecayModes( begin, end, lineNumber, 3580, 8, 457 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of a DecayModes for a stable nuclide with "
         "inconsistent NDK" ) {

    std::string string = wrongStableNDK();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
      
    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( DecayModes( begin, end, lineNumber, 3580, 8, 457 ) );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 5.000000+0-1.000000+0          0          0         18          33580 8457     \n"
    " 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n"
    " 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n"
    " 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n";
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

