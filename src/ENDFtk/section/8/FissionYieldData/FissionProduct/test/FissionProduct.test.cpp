#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/8/FissionYieldData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using FissionProduct = section::FissionYieldData::FissionProduct< std::vector< double > >;

void verifyChunk( const FissionProduct& );

SCENARIO( "FissionProduct" ) {

  GIVEN( "valid data for a FissionProduct" ) {

    WHEN( "the data is given explicitly" ) {

      FissionProduct chunk( { 1001., 1., 1e-3, 1e-5 } );

      THEN( "a FissionProduct can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const FissionProduct& chunk ) {

  CHECK( 1001 == Approx( chunk.ZAFP() ) );
  CHECK( 1001 == Approx( chunk.fissionProductIdentifier() ) );
  CHECK( 1 == Approx( chunk.FPS() ) );
  CHECK( 1 == Approx( chunk.isomericState() ) );
  CHECK( 1e-3 == Approx( chunk.YI() ) );
  CHECK( 1e-3 == Approx( chunk.fissionYield() ) );
  CHECK( 1e-5 == Approx( chunk.DYI() ) );
  CHECK( 1e-5 == Approx( chunk.fissionYieldUncertainty() ) );
}
