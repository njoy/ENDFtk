// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

  CHECK_THAT( 2., WithinRel( chunk.AJ() ) );
  CHECK_THAT( 2., WithinRel( chunk.spin() ) );
  CHECK_THAT( 1., WithinRel( chunk.D() ) );
  CHECK_THAT( 1., WithinRel( chunk.averageLevelSpacing() ) );
  CHECK( 3 == chunk.AMUN() );
  CHECK( 3 == chunk.neutronWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUG() );
  CHECK( 0 == chunk.gammaWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUF() );
  CHECK( 0 == chunk.fissionWidthDegreesFreedom() );
  CHECK( 0 == chunk.AMUX() );
  CHECK( 0 == chunk.competitiveWidthDegreesFreedom() );
  CHECK_THAT( 4., WithinRel( chunk.GN() ) );
  CHECK_THAT( 4., WithinRel( chunk.averageNeutronWidth() ) );
  CHECK_THAT( 5., WithinRel( chunk.GG() ) );
  CHECK_THAT( 5., WithinRel( chunk.averageGammaWidth() ) );
  CHECK_THAT( 0., WithinRel( chunk.GF() ) );
  CHECK_THAT( 0., WithinRel( chunk.averageFissionWidth() ) );
  CHECK_THAT( 0., WithinRel( chunk.GX() ) );
  CHECK_THAT( 0., WithinRel( chunk.averageCompetitiveWidth() ) );
}
