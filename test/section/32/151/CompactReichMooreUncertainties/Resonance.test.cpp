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

  CHECK_THAT( 1., WithinRel( chunk.ER() ) );
  CHECK_THAT( 1., WithinRel( chunk.resonanceEnergy() ) );
  CHECK_THAT( 2., WithinRel( chunk.AJ() ) );
  CHECK_THAT( 2., WithinRel( chunk.spin() ) );
  CHECK_THAT( 3., WithinRel( chunk.GN() ) );
  CHECK_THAT( 3., WithinRel( chunk.neutronWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.GG() ) );
  CHECK_THAT( 4., WithinRel( chunk.gammaWidth() ) );
  CHECK_THAT( 5., WithinRel( chunk.GFA() ) );
  CHECK_THAT( 5., WithinRel( chunk.firstFissionWidth() ) );
  CHECK_THAT( 6., WithinRel( chunk.GFB() ) );
  CHECK_THAT( 6., WithinRel( chunk.secondFissionWidth() ) );

  CHECK_THAT( 7., WithinRel( chunk.DER() ) );
  CHECK_THAT( 7., WithinRel( chunk.resonanceEnergyUncertainty() ) );
  CHECK_THAT( 8., WithinRel( chunk.DGN() ) );
  CHECK_THAT( 8., WithinRel( chunk.neutronWidthUncertainty() ) );
  CHECK_THAT( 9., WithinRel( chunk.DGG() ) );
  CHECK_THAT( 9., WithinRel( chunk.gammaWidthUncertainty() ) );
  CHECK_THAT( 10., WithinRel( chunk.DGFA() ) );
  CHECK_THAT( 10., WithinRel( chunk.firstFissionWidthUncertainty() ) );
  CHECK_THAT( 11., WithinRel( chunk.DGFB() ) );
  CHECK_THAT( 11., WithinRel( chunk.secondFissionWidthUncertainty() ) );
}
