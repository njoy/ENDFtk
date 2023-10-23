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

  CHECK_THAT( 1., WithinRel( chunk.ER() ) );
  CHECK_THAT( 1., WithinRel( chunk.resonanceEnergy() ) );
  CHECK_THAT( 2., WithinRel( chunk.AJ() ) );
  CHECK_THAT( 2., WithinRel( chunk.spin() ) );
  CHECK_THAT( 12., WithinRel( chunk.GT() ) );
  CHECK_THAT( 12., WithinRel( chunk.totalWidth() ) );
  CHECK_THAT( 3., WithinRel( chunk.GN() ) );
  CHECK_THAT( 3., WithinRel( chunk.neutronWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.GG() ) );
  CHECK_THAT( 4., WithinRel( chunk.gammaWidth() ) );
  CHECK_THAT( 5., WithinRel( chunk.GF() ) );
  CHECK_THAT( 5., WithinRel( chunk.fissionWidth() ) );

  CHECK_THAT( 6., WithinRel( chunk.DER() ) );
  CHECK_THAT( 6., WithinRel( chunk.resonanceEnergyUncertainty() ) );
  CHECK_THAT( 9., WithinRel( chunk.DGN() ) );
  CHECK_THAT( 9., WithinRel( chunk.neutronWidthUncertainty() ) );
  CHECK_THAT( 10., WithinRel( chunk.DGG() ) );
  CHECK_THAT( 10., WithinRel( chunk.gammaWidthUncertainty() ) );
  CHECK_THAT( 11., WithinRel( chunk.DGF() ) );
  CHECK_THAT( 11., WithinRel( chunk.fissionWidthUncertainty() ) );
}
