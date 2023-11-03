#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Resonance =
section::Type< 32, 151 >::CompactBreitWignerUncertainties::Resonance< std::vector< double > >;

void verifyChunk( const Resonance& );

SCENARIO( "Resonance" ) {

  GIVEN( "valid data for a Resonance" ) {

    WHEN( "the data is given explicitly" ) {

      Resonance chunk( { 1., 2., 12., 3., 4., 5.,
                         6., 0., 0., 9., 10., 11. } );

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
  CHECK( 12. == Approx( chunk.GT() ) );
  CHECK( 12. == Approx( chunk.totalWidth() ) );
  CHECK( 3. == Approx( chunk.GN() ) );
  CHECK( 3. == Approx( chunk.neutronWidth() ) );
  CHECK( 4. == Approx( chunk.GG() ) );
  CHECK( 4. == Approx( chunk.gammaWidth() ) );
  CHECK( 5. == Approx( chunk.GF() ) );
  CHECK( 5. == Approx( chunk.fissionWidth() ) );

  CHECK( 6. == Approx( chunk.DER() ) );
  CHECK( 6. == Approx( chunk.resonanceEnergyUncertainty() ) );
  CHECK( 9. == Approx( chunk.DGN() ) );
  CHECK( 9. == Approx( chunk.neutronWidthUncertainty() ) );
  CHECK( 10. == Approx( chunk.DGG() ) );
  CHECK( 10. == Approx( chunk.gammaWidthUncertainty() ) );
  CHECK( 11. == Approx( chunk.DGF() ) );
  CHECK( 11. == Approx( chunk.fissionWidthUncertainty() ) );
}
