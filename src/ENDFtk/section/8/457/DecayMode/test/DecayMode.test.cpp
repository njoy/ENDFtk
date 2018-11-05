#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using DecayMode = section::Type< 8, 457 >::DecayMode;

SCENARIO( "DecayMode" ) {

  GIVEN( "valid data for a DecayMode" ) {

    double rtyp = 4.;
    double rfs = 0.;
    double q = 5.637120e+6;
    double dq = 2.549510e+2;
    double br = 4.590000e-3;
    double dbr = 1.200000e-4;
    
    THEN( "a DecayMode can be constructed and members can be tested" ) {

      DecayMode chunk( rtyp, rfs, q, dq, br, dbr );

      REQUIRE( 4. == Approx( chunk.decayChain() ) );
      REQUIRE( 0. == Approx( chunk.finalIsomericState() ) );
      REQUIRE( 5.637120e+6 == Approx( std::get< 0 >( chunk.qValue() ) ) );
      REQUIRE( 2.549510e+2 == Approx( std::get< 1 >( chunk.qValue() ) ) );
      REQUIRE( 4.590000e-3 == Approx( std::get< 0 >( chunk.branchingRatio() ) ) );
      REQUIRE( 1.200000e-4 == Approx( std::get< 1 >( chunk.branchingRatio() ) ) );
    }
  } // GIVEN
} // SCENARIO
