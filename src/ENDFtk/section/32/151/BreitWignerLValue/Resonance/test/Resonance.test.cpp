#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Resonance =
section::Type< 32, 151 >::BreitWignerLValue::Resonance< std::vector< double > >;

void verifyChunk( const Resonance& );

SCENARIO( "Resonance" ) {

  GIVEN( "valid data for a Resonance" ) {

    WHEN( "the data is given explicitly" ) {

      Resonance chunk( { 1., 2., 18., 3., 4., 5.,
                         6., 7., 8., 9., 10., 11.,
                         12., 13., 14., 15., 16. } );

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

  CHECK( 6. == Approx( chunk.DE2() ) );
  CHECK( 6. == Approx( chunk.resonanceEnergyVariance() ) );
  CHECK( 16. == Approx( chunk.DJ2() ) );
  CHECK( 16. == Approx( chunk.spinVariance() ) );
  CHECK( 7. == Approx( chunk.DN2() ) );
  CHECK( 7. == Approx( chunk.neutronWidthVariance() ) );
  CHECK( 9. == Approx( chunk.DG2() ) );
  CHECK( 9. == Approx( chunk.gammaWidthVariance() ) );
  CHECK( 12. == Approx( chunk.DF2() ) );
  CHECK( 12. == Approx( chunk.fissionWidthVariance() ) );
  CHECK( 8. == Approx( chunk.DNDG() ) );
  CHECK( 8. == Approx( chunk.neutronAndGammaWidthCovariance() ) );
  CHECK( 10. == Approx( chunk.DNDF() ) );
  CHECK( 10. == Approx( chunk.neutronAndFissionWidthCovariance() ) );
  CHECK( 11. == Approx( chunk.DGDF() ) );
  CHECK( 11. == Approx( chunk.gammaAndFissionWidthCovariance() ) );
  CHECK( 13. == Approx( chunk.DJDN() ) );
  CHECK( 13. == Approx( chunk.spinAndNeutronWidthCovariance() ) );
  CHECK( 14. == Approx( chunk.DJDG() ) );
  CHECK( 14. == Approx( chunk.spinAndGammaWidthCovariance() ) );
  CHECK( 15. == Approx( chunk.DJDF() ) );
  CHECK( 15. == Approx( chunk.spinAndFissionWidthCovariance() ) );
}
