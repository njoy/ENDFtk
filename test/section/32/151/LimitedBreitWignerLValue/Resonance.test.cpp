// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Resonance =
section::Type< 32, 151 >::LimitedBreitWignerLValue::Resonance< std::vector< double > >;

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

  CHECK_THAT( 1., WithinRel( chunk.ER() ) );
  CHECK_THAT( 1., WithinRel( chunk.resonanceEnergy() ) );
  CHECK_THAT( 2., WithinRel( chunk.AJ() ) );
  CHECK_THAT( 2., WithinRel( chunk.spin() ) );
  CHECK_THAT( 18., WithinRel( chunk.GT() ) );
  CHECK_THAT( 18., WithinRel( chunk.totalWidth() ) );
  CHECK_THAT( 3., WithinRel( chunk.GN() ) );
  CHECK_THAT( 3., WithinRel( chunk.neutronWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.GG() ) );
  CHECK_THAT( 4., WithinRel( chunk.gammaWidth() ) );
  CHECK_THAT( 5., WithinRel( chunk.GF() ) );
  CHECK_THAT( 5., WithinRel( chunk.fissionWidth() ) );

  CHECK_THAT( 6., WithinRel( chunk.DE2() ) );
  CHECK_THAT( 6., WithinRel( chunk.resonanceEnergyVariance() ) );
  CHECK_THAT( 16., WithinRel( chunk.DJ2() ) );
  CHECK_THAT( 16., WithinRel( chunk.spinVariance() ) );
  CHECK_THAT( 7., WithinRel( chunk.DN2() ) );
  CHECK_THAT( 7., WithinRel( chunk.neutronWidthVariance() ) );
  CHECK_THAT( 9., WithinRel( chunk.DG2() ) );
  CHECK_THAT( 9., WithinRel( chunk.gammaWidthVariance() ) );
  CHECK_THAT( 12., WithinRel( chunk.DF2() ) );
  CHECK_THAT( 12., WithinRel( chunk.fissionWidthVariance() ) );
  CHECK_THAT( 8., WithinRel( chunk.DNDG() ) );
  CHECK_THAT( 8., WithinRel( chunk.neutronAndGammaWidthCovariance() ) );
  CHECK_THAT( 10., WithinRel( chunk.DNDF() ) );
  CHECK_THAT( 10., WithinRel( chunk.neutronAndFissionWidthCovariance() ) );
  CHECK_THAT( 11., WithinRel( chunk.DGDF() ) );
  CHECK_THAT( 11., WithinRel( chunk.gammaAndFissionWidthCovariance() ) );
  CHECK_THAT( 13., WithinRel( chunk.DJDN() ) );
  CHECK_THAT( 13., WithinRel( chunk.spinAndNeutronWidthCovariance() ) );
  CHECK_THAT( 14., WithinRel( chunk.DJDG() ) );
  CHECK_THAT( 14., WithinRel( chunk.spinAndGammaWidthCovariance() ) );
  CHECK_THAT( 15., WithinRel( chunk.DJDF() ) );
  CHECK_THAT( 15., WithinRel( chunk.spinAndFissionWidthCovariance() ) );
}
