// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

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
  CHECK_THAT( 6., WithinRel( chunk.GX() ) );
  CHECK_THAT( 6., WithinRel( chunk.competitiveWidth() ) );
}
