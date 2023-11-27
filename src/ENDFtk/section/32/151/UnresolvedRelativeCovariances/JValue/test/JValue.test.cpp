// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using JValue =
section::Type< 32, 151 >::UnresolvedRelativeCovariances::JValue< std::vector< double > >;

void verifyChunk( const JValue& );

SCENARIO( "JValue" ) {

  GIVEN( "valid data for a JValue" ) {

    WHEN( "the data is given explicitly" ) {

      JValue chunk( { 1., 2., 3., 4., 5., 6. } );

      THEN( "a JValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const JValue& chunk ) {

  CHECK_THAT( 2., WithinRel( chunk.AJ() ) );
  CHECK_THAT( 2., WithinRel( chunk.spin() ) );
  CHECK_THAT( 1., WithinRel( chunk.D() ) );
  CHECK_THAT( 1., WithinRel( chunk.averageLevelSpacing() ) );
  CHECK_THAT( 3., WithinRel( chunk.GNO() ) );
  CHECK_THAT( 3., WithinRel( chunk.averageNeutronWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.GG() ) );
  CHECK_THAT( 4., WithinRel( chunk.averageGammaWidth() ) );
  CHECK_THAT( 5., WithinRel( chunk.GF() ) );
  CHECK_THAT( 5., WithinRel( chunk.averageFissionWidth() ) );
  CHECK_THAT( 6., WithinRel( chunk.GX() ) );
  CHECK_THAT( 6., WithinRel( chunk.averageCompetitiveWidth() ) );
}
