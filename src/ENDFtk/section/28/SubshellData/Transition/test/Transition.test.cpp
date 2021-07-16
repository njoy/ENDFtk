#define CATCH_CONFIG_MAIN

#include "catch.hpp"
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

  CHECK( 1 == Approx( chunk.SUBJ() ) );
  CHECK( 1 == Approx( chunk.secondarySubshellDesignator() ) );
  CHECK( 2 == Approx( chunk.SUBK() ) );
  CHECK( 2 == Approx( chunk.tertiarySubshellDesignator() ) );
  CHECK( 3. == Approx( chunk.ETR() ) );
  CHECK( 3. == Approx( chunk.transitionEnergy() ) );
  CHECK( 4. == Approx( chunk.FTR() ) );
  CHECK( 4. == Approx( chunk.transitionProbability() ) );
}
