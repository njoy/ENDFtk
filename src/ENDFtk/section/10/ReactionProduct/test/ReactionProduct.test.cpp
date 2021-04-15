#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/10.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionProduct = section::Type< 10 >::ReactionProduct;

std::string chunk();
void verifyChunk( const ReactionProduct& );
std::string invalidChunk();

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      long za = 95242;
      long lfs = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 5 };
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      ReactionProduct chunk( qm, qi, za, lfs,
                             std::move( boundaries ),
                             std::move( interpolants ),
                             std::move( x ),
                             std::move( y ) );

      THEN( "a ReactionProduct can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9534, 10, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9534, 10, 102 );

      THEN( "a ReactionProduct can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9534, 10, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionProduct" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      long za = 95242;
      long lfs = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > wrongInterpolants = { 5, 2 };
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReactionProduct( qm, qi, za, lfs,
                                       std::move( boundaries ),
                                       std::move( wrongInterpolants ),
                                       std::move( x ),
                                       std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReactionProduct( begin, end, lineNumber,
                                              9534, 10, 102 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
  " 2.224648+6 3.224648+6      95242          2          1          2953410102     \n"
  "          2          5                                            953410102     \n"
  " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      953410102     \n";
}

void verifyChunk( const ReactionProduct& chunk ) {

  CHECK( 2.224648e+6 == Approx( chunk.QM() ) );
  CHECK( 2.224648e+6 == Approx( chunk.massDifferenceQValue() ) );
  CHECK( 3.224648e+6 == Approx( chunk.QI() ) );
  CHECK( 3.224648e+6 == Approx( chunk.reactionQValue() ) );
  CHECK( 95242 == chunk.IZAP() );
  CHECK( 95242 == chunk.productIdentifier() );
  CHECK( 2 == chunk.LFS() );
  CHECK( 2 == chunk.excitedLevel() );

  CHECK( 2 == chunk.NP() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 5 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.x().size() );
  CHECK( 2 == chunk.XS().size() );
  CHECK( 2 == chunk.crossSections().size() );
  CHECK( 2 == chunk.y().size() );
  CHECK( 1. == Approx( chunk.E()[0] ) );
  CHECK( 3. == Approx( chunk.E()[1] ) );
  CHECK( 1. == Approx( chunk.energies()[0] ) );
  CHECK( 3. == Approx( chunk.energies()[1] ) );
  CHECK( 1. == Approx( chunk.x()[0] ) );
  CHECK( 3. == Approx( chunk.x()[1] ) );
  CHECK( 2. == Approx( chunk.XS()[0] ) );
  CHECK( 4. == Approx( chunk.XS()[1] ) );
  CHECK( 2. == Approx( chunk.crossSections()[0] ) );
  CHECK( 4. == Approx( chunk.crossSections()[1] ) );
  CHECK( 2. == Approx( chunk.y()[0] ) );
  CHECK( 4. == Approx( chunk.y()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 2.224648+6 3.224648+6      95242          2          2          2953410102     \n"
    "          2          2                                            953410102     \n"
    " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      953410102     \n";
}
