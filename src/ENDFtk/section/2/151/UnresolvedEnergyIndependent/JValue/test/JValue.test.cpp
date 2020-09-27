#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using JValue =
section::Type< 2, 151 >::UnresolvedEnergyIndependent::JValue< std::vector< double > >;

void verifyChunk( const JValue& );

SCENARIO( "JValue" ) {

  GIVEN( "valid data for a JValue" ) {

    WHEN( "the data is given explicitly" ) {

      JValue chunk( { 1., 2., 3., 4., 5., 0. } );

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
  CHECK( 3 == chunk.AMUN() );
  CHECK( 3 == chunk.neutronWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUG() );
  CHECK( 0 == chunk.gammaWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUF() );
  CHECK( 0 == chunk.fissionWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUX() );
  CHECK( 0 == chunk.competitiveWidthDegreesFreedom() );
  CHECK( 4. == Approx( chunk.GN() ) );
  CHECK( 4. == Approx( chunk.averageNeutronWidth() ) );
  CHECK( 5. == Approx( chunk.GG() ) );
  CHECK( 5. == Approx( chunk.averageGammaWidth() ) );
  CHECK( 0. == Approx( chunk.GF() ) );
  CHECK( 0. == Approx( chunk.averageFissionWidth() ) );
  CHECK( 0. == Approx( chunk.GX() ) );
  CHECK( 0. == Approx( chunk.averageCompetitiveWidth() ) );
}
