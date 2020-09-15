#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using EqualProbabilityBins =
section::Type< 6 >::ContinuumEnergyAngle::EqualProbabilityBins;

std::string chunk();
void verifyChunk( const EqualProbabilityBins& );

SCENARIO( "EqualProbabilityBins" ) {

  GIVEN( "valid data for a EqualProbabilityBins" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {


      THEN( "a EqualProbabilityBins can be constructed and members can be "
            "tested" ) {

        //EqualProbabilityBins chunk(  );
        //verifyChunkNA1( chunk );
      }
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a EqualProbabilityBins can be constructed and members can be "
            "tested" ) {

        EqualProbabilityBins chunk( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0        102          61301 6222     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n"
    " 9.999999-6 9.477167+1-5.379121-1 0.21062848 0.70490082 9.552579-11301 6222     \n"
    " 1.265100-1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01301 6222     \n";
}

void verifyChunk( const EqualProbabilityBins& chunk ) {

  REQUIRE( 3 == chunk.LANG() );
  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  REQUIRE( 3 == chunk.NEP() );
  REQUIRE( 3 == chunk.numberSecondaryEnergies() );
  REQUIRE( 3 == chunk.energies().size() );
  REQUIRE( 0. == Approx( chunk.energies()[0] ) );
  REQUIRE( 9.999999e-6 == Approx( chunk.energies()[1] ) );
  REQUIRE( 0.12651 == Approx( chunk.energies()[2] ) );

  REQUIRE( 4 == chunk.NC() );
}
