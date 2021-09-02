#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/2/153.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Table =
section::Type< 2, 153 >::Table< std::vector< double > >;

void verifyChunk( const Table& );

SCENARIO( "Table" ) {

  GIVEN( "valid data for a Table" ) {

    WHEN( "the data is given explicitly" ) {

      Table chunk( { 1., 2., 3.,  4.,  5.,  6.,  7.,
                         8., 9., 10., 11., 12., 13. }, 2 );

      THEN( "a Table can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Table& chunk ) {

  CHECK( 2 == chunk.NBIN() );
  CHECK( 2 == chunk.numberBins() );
  CHECK( 1. == Approx( chunk.EUNR() ) );
  CHECK( 1. == Approx( chunk.unresolvedResonanceEnergy() ) );

  CHECK( 2 == chunk.PROB().size() );
  CHECK( 2 == chunk.probabilities().size() );
  CHECK( 2 == chunk.TOTL().size() );
  CHECK( 2 == chunk.total().size() );
  CHECK( 2 == chunk.ELAS().size() );
  CHECK( 2 == chunk.elastic().size() );
  CHECK( 2 == chunk.FISS().size() );
  CHECK( 2 == chunk.fission().size() );
  CHECK( 2 == chunk.CAPT().size() );
  CHECK( 2 == chunk.capture().size() );
  CHECK( 2 == chunk.HEAT().size() );
  CHECK( 2 == chunk.heating().size() );

  CHECK( 2. == chunk.PROB()[0] );
  CHECK( 3. == chunk.PROB()[1] );
  CHECK( 2. == chunk.probabilities()[0] );
  CHECK( 3. == chunk.probabilities()[1] );
  CHECK( 4. == chunk.TOTL()[0] );
  CHECK( 5. == chunk.TOTL()[1] );
  CHECK( 4. == chunk.total()[0] );
  CHECK( 5. == chunk.total()[1] );
  CHECK( 6. == chunk.ELAS()[0] );
  CHECK( 7. == chunk.ELAS()[1] );
  CHECK( 6. == chunk.elastic()[0] );
  CHECK( 7. == chunk.elastic()[1] );
  CHECK( 8. == chunk.FISS()[0] );
  CHECK( 9. == chunk.FISS()[1] );
  CHECK( 8. == chunk.fission()[0] );
  CHECK( 9. == chunk.fission()[1] );
  CHECK( 10. == chunk.CAPT()[0] );
  CHECK( 11. == chunk.CAPT()[1] );
  CHECK( 10. == chunk.capture()[0] );
  CHECK( 11. == chunk.capture()[1] );
  CHECK( 12. == chunk.HEAT()[0] );
  CHECK( 13. == chunk.HEAT()[1] );
  CHECK( 12. == chunk.heating()[0] );
  CHECK( 13. == chunk.heating()[1] );  
}
