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

void verifyChunk( const Transition& );

SCENARIO( "Transition" ) {

  GIVEN( "valid data for a Transition" ) {

    WHEN( "the data is given explicitly" ) {

      Transition chunk( { 1., 2., 3., 4., 0., 0. } );

      THEN( "a Transition can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Transition& chunk ) {

  CHECK_THAT( 1, WithinRel( chunk.SUBJ() ) );
  CHECK_THAT( 1, WithinRel( chunk.secondarySubshellDesignator() ) );
  CHECK_THAT( 2, WithinRel( chunk.SUBK() ) );
  CHECK_THAT( 2, WithinRel( chunk.tertiarySubshellDesignator() ) );
  CHECK_THAT( 3., WithinRel( chunk.ETR() ) );
  CHECK_THAT( 3., WithinRel( chunk.transitionEnergy() ) );
  CHECK_THAT( 4., WithinRel( chunk.FTR() ) );
  CHECK_THAT( 4., WithinRel( chunk.transitionProbability() ) );
}
