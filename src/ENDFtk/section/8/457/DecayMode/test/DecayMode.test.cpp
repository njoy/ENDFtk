#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/8/457.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
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

      CHECK( 4. == Approx( chunk.RTYP() ) );
      CHECK( 4. == Approx( chunk.decayChain() ) );
      CHECK( 0. == Approx( chunk.RFS() ) );
      CHECK( 0. == Approx( chunk.finalIsomericState() ) );
      CHECK( 5.637120e+6 == Approx( chunk.Q()[0] ) );
      CHECK( 2.549510e+2 == Approx( chunk.Q()[1] ) );
      CHECK( 5.637120e+6 == Approx( chunk.qValue()[0] ) );
      CHECK( 2.549510e+2 == Approx( chunk.qValue()[1] ) );
      CHECK( 4.590000e-3 == Approx( chunk.BR()[0] ) );
      CHECK( 1.200000e-4 == Approx( chunk.BR()[1] ) );
      CHECK( 4.590000e-3 == Approx( chunk.branchingRatio()[0] ) );
      CHECK( 1.200000e-4 == Approx( chunk.branchingRatio()[1] ) );
    }
  } // GIVEN
} // SCENARIO
