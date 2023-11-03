#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

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

  CHECK( 2. == Approx( chunk.AJ() ) );
  CHECK( 2. == Approx( chunk.spin() ) );
  CHECK( 1. == Approx( chunk.D() ) );
  CHECK( 1. == Approx( chunk.averageLevelSpacing() ) );
  CHECK( 3. == Approx( chunk.GNO() ) );
  CHECK( 3. == Approx( chunk.averageNeutronWidth() ) );
  CHECK( 4. == Approx( chunk.GG() ) );
  CHECK( 4. == Approx( chunk.averageGammaWidth() ) );
  CHECK( 5. == Approx( chunk.GF() ) );
  CHECK( 5. == Approx( chunk.averageFissionWidth() ) );
  CHECK( 6. == Approx( chunk.GX() ) );
  CHECK( 6. == Approx( chunk.averageCompetitiveWidth() ) );
}
