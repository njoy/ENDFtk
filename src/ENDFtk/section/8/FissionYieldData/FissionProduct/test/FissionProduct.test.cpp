// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/8/FissionYieldData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using FissionProduct = section::FissionYieldData::FissionProduct< std::vector< double > >;

void verifyChunk( const FissionProduct& );

SCENARIO( "FissionProduct" ) {

  GIVEN( "valid data for a FissionProduct" ) {

    WHEN( "the data is given explicitly" ) {

      FissionProduct chunk( { 1001., 1., 1e-3, 1e-5 } );

      THEN( "a FissionProduct can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const FissionProduct& chunk ) {

  CHECK( 1001 == chunk.ZAFP() );
  CHECK( 1001 == chunk.fissionProductIdentifier() );
  CHECK( 1 == chunk.FPS() );
  CHECK( 1 == chunk.isomericState() );
  CHECK_THAT( 1e-3, WithinRel( chunk.FY() ) );
  CHECK_THAT( 1e-3, WithinRel( chunk.fissionYieldValue() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.DFY() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.fissionYieldUncertainty() ) );
  CHECK_THAT( 1e-3, WithinRel( chunk.Y()[0] ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.Y()[1] ) );
  CHECK_THAT( 1e-3, WithinRel( chunk.fissionYield()[0] ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.fissionYield()[1] ) );
}
