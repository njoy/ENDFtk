#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Resonance =
section::Type< 2, 151 >::BreitWignerLValue::Resonance< std::vector< double > >;

void verifyChunk( const Resonance& );

SCENARIO( "Resonance" ) {

  GIVEN( "valid data for a Resonance" ) {

    WHEN( "the data is given explicitly" ) {

      Resonance chunk( { 1., 2., 18., 3., 4., 5. } );

      THEN( "a Resonance can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Resonance& chunk ) {

  CHECK( 1. == Approx( chunk.ER() ) );
  CHECK( 1. == Approx( chunk.resonanceEnergy() ) );
  CHECK( 2. == Approx( chunk.AJ() ) );
  CHECK( 2. == Approx( chunk.spin() ) );
  CHECK( 18. == Approx( chunk.GT() ) );
  CHECK( 18. == Approx( chunk.totalWidth() ) );
  CHECK( 3. == Approx( chunk.GN() ) );
  CHECK( 3. == Approx( chunk.neutronWidth() ) );
  CHECK( 4. == Approx( chunk.GG() ) );
  CHECK( 4. == Approx( chunk.gammaWidth() ) );
  CHECK( 5. == Approx( chunk.GF() ) );
  CHECK( 5. == Approx( chunk.fissionWidth() ) );
  CHECK( 6. == Approx( chunk.GX() ) );
  CHECK( 6. == Approx( chunk.competitiveWidth() ) );
}
