// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

      CHECK_THAT( 4., WithinRel( chunk.RTYP() ) );
      CHECK_THAT( 4., WithinRel( chunk.decayChain() ) );
      CHECK_THAT( 0., WithinRel( chunk.RFS() ) );
      CHECK_THAT( 0., WithinRel( chunk.finalIsomericState() ) );
      CHECK_THAT( 5.637120e+6, WithinRel( chunk.Q()[0] ) );
      CHECK_THAT( 2.549510e+2, WithinRel( chunk.Q()[1] ) );
      CHECK_THAT( 5.637120e+6, WithinRel( chunk.qValue()[0] ) );
      CHECK_THAT( 2.549510e+2, WithinRel( chunk.qValue()[1] ) );
      CHECK_THAT( 4.590000e-3, WithinRel( chunk.BR()[0] ) );
      CHECK_THAT( 1.200000e-4, WithinRel( chunk.BR()[1] ) );
      CHECK_THAT( 4.590000e-3, WithinRel( chunk.branchingRatio()[0] ) );
      CHECK_THAT( 1.200000e-4, WithinRel( chunk.branchingRatio()[1] ) );
    }
  } // GIVEN
} // SCENARIO
