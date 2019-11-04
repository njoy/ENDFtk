#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
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

void verifyChunkSize2( const Transition& chunk ) {

  CHECK( 3. == Approx( chunk.E() ) );
  CHECK( 3. == Approx( chunk.energy() ) );
  CHECK( 2. == Approx( chunk.PT() ) );
  CHECK( 2. == Approx( chunk.transitionProbability() ) );
  CHECK( 1. == Approx( chunk.GP() ) );
  CHECK( 1. == Approx( chunk.conditionalProbability() ) );
}

void verifyChunkSize3( const Transition& chunk ) {

  CHECK( 1. == Approx( chunk.E() ) );
  CHECK( 1. == Approx( chunk.energy() ) );
  CHECK( 2. == Approx( chunk.PT() ) );
  CHECK( 2. == Approx( chunk.transitionProbability() ) );
  CHECK( 3. == Approx( chunk.GP() ) );
  CHECK( 3. == Approx( chunk.conditionalProbability() ) );
}
