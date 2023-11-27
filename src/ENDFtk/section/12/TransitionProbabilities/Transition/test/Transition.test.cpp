// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/12.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Transition =
section::Type< 12 >::TransitionProbabilities::Transition< std::vector< double > >;

void verifyChunkWithSize2( const Transition& );
void verifyChunkWithSize3( const Transition& );

SCENARIO( "Transition" ) {

  GIVEN( "valid data for a Transition" ) {

    WHEN( "the data is given explicitly for a size 2 chunk" ) {

      Transition chunk( { 3., 2. } );

      THEN( "a Transition can be constructed and members can be "
            "tested" ) {

        verifyChunkWithSize2( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly for a size 3 chunk" ) {

      Transition chunk( { 1., 2., 3. } );

      THEN( "a Transition can be constructed and members can be "
            "tested" ) {

        verifyChunkWithSize3( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithSize2( const Transition& chunk ) {

  CHECK_THAT( 3., WithinRel( chunk.E() ) );
  CHECK_THAT( 3., WithinRel( chunk.energy() ) );
  CHECK_THAT( 2., WithinRel( chunk.TP() ) );
  CHECK_THAT( 2., WithinRel( chunk.transitionProbability() ) );
  CHECK_THAT( 1., WithinRel( chunk.GP() ) );
  CHECK_THAT( 1., WithinRel( chunk.conditionalProbability() ) );
}

void verifyChunkWithSize3( const Transition& chunk ) {

  CHECK_THAT( 1., WithinRel( chunk.E() ) );
  CHECK_THAT( 1., WithinRel( chunk.energy() ) );
  CHECK_THAT( 2., WithinRel( chunk.TP() ) );
  CHECK_THAT( 2., WithinRel( chunk.transitionProbability() ) );
  CHECK_THAT( 3., WithinRel( chunk.GP() ) );
  CHECK_THAT( 3., WithinRel( chunk.conditionalProbability() ) );
}
