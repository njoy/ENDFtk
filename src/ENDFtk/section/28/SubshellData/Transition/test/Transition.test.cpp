// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/28.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Transition = section::Type< 28 >::SubshellData::Transition< std::vector< double > >;

void verifyRadiativeChunk( const Transition& );
void verifyNonRadiativeChunk( const Transition& );

SCENARIO( "Transition" ) {

  GIVEN( "valid data for a Transition" ) {

    WHEN( "the data is given explicitly for a radiative transition" ) {

      Transition chunk( { 1., 0., 3., 4., 0., 0. } );

      THEN( "a Transition can be constructed and members can be tested" ) {

        verifyRadiativeChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly for a non-radiative transition" ) {

      Transition chunk( { 1., 2., 3., 4., 0., 0. } );

      THEN( "a Transition can be constructed and members can be tested" ) {

        verifyNonRadiativeChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyRadiativeChunk( const Transition& chunk ) {

  CHECK_THAT( 1, WithinRel( chunk.SUBJ() ) );
  CHECK_THAT( 1, WithinRel( chunk.secondarySubshellDesignator() ) );
  CHECK_THAT( 0, WithinRel( chunk.SUBK() ) );
  CHECK_THAT( 0, WithinRel( chunk.tertiarySubshellDesignator() ) );
  CHECK( true == chunk.isRadiative() );
  CHECK( false == chunk.isNonRadiative() );
  CHECK_THAT( 3., WithinRel( chunk.ETR() ) );
  CHECK_THAT( 3., WithinRel( chunk.transitionEnergy() ) );
  CHECK_THAT( 4., WithinRel( chunk.FTR() ) );
  CHECK_THAT( 4., WithinRel( chunk.transitionProbability() ) );
}

void verifyNonRadiativeChunk( const Transition& chunk ) {

  CHECK_THAT( 1, WithinRel( chunk.SUBJ() ) );
  CHECK_THAT( 1, WithinRel( chunk.secondarySubshellDesignator() ) );
  CHECK_THAT( 2, WithinRel( chunk.SUBK() ) );
  CHECK_THAT( 2, WithinRel( chunk.tertiarySubshellDesignator() ) );
  CHECK( false == chunk.isRadiative() );
  CHECK( true == chunk.isNonRadiative() );
  CHECK_THAT( 3., WithinRel( chunk.ETR() ) );
  CHECK_THAT( 3., WithinRel( chunk.transitionEnergy() ) );
  CHECK_THAT( 4., WithinRel( chunk.FTR() ) );
  CHECK_THAT( 4., WithinRel( chunk.transitionProbability() ) );
}
