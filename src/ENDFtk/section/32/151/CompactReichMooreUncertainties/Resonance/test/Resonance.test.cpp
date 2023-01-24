#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Resonance =
section::Type< 32, 151 >::CompactReichMooreUncertainties::Resonance< std::vector< double > >;

void verifyChunk( const Resonance& );

SCENARIO( "Resonance" ) {

  GIVEN( "valid data for a Resonance" ) {

    WHEN( "the data is given explicitly" ) {

      Resonance chunk( { 1., 2., 3., 4., 5., 6.,
                         7., 0., 8., 9., 10., 11. } );

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
  CHECK( 3. == Approx( chunk.GN() ) );
  CHECK( 3. == Approx( chunk.neutronWidth() ) );
  CHECK( 4. == Approx( chunk.GG() ) );
  CHECK( 4. == Approx( chunk.gammaWidth() ) );
  CHECK( 5. == Approx( chunk.GFA() ) );
  CHECK( 5. == Approx( chunk.firstFissionWidth() ) );
  CHECK( 6. == Approx( chunk.GFB() ) );
  CHECK( 6. == Approx( chunk.secondFissionWidth() ) );

  CHECK( 7. == Approx( chunk.DER() ) );
  CHECK( 7. == Approx( chunk.resonanceEnergyUncertainty() ) );
  CHECK( 8. == Approx( chunk.DGN() ) );
  CHECK( 8. == Approx( chunk.neutronWidthUncertainty() ) );
  CHECK( 9. == Approx( chunk.DGG() ) );
  CHECK( 9. == Approx( chunk.gammaWidthUncertainty() ) );
  CHECK( 10. == Approx( chunk.DGFA() ) );
  CHECK( 10. == Approx( chunk.firstFissionWidthUncertainty() ) );
  CHECK( 11. == Approx( chunk.DGFB() ) );
  CHECK( 11. == Approx( chunk.secondFissionWidthUncertainty() ) );
}
